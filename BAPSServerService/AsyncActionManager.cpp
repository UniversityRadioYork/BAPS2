#include "StdAfx.h"
#include "AsyncActionManager.h"
#include "ClientInstance.h"
#include "LogManager.h"

void AsyncActionManager::doActions(System::Object^)
{
	if (updateInProgress)
	{
		return;
	}
	asyncActionMutex->WaitOne();
	updateInProgress = true;
	try
	{
		if (introPositions->Count != 0)
		{
			System::String^ connStr = System::String::Concat("Server=", CONFIG_GETSTR(CONFIG_DBSERVER), ";");
			connStr = System::String::Concat(connStr, "Database=", CONFIG_GETSTR(CONFIG_LIBRARYDBNAME), ";");
			connStr = System::String::Concat(connStr, "User Id=", CONFIG_GETSTR(CONFIG_DBUSERNAME), ";");
			connStr = System::String::Concat(connStr, "Password=", CONFIG_GETSTR(CONFIG_DBPASSWORD), ";");
			connStr = System::String::Concat(connStr, "Port=", CONFIG_GETSTR(CONFIG_DBPORT), ";");

			/** Connect to the baps database **/
			NpgsqlConnection^ recordlibDB = gcnew NpgsqlConnection(connStr);
			
			System::Data::DataSet^ updateDataset = gcnew System::Data::DataSet();
			NpgsqlDataAdapter^ recordlibDataAdapter = gcnew NpgsqlDataAdapter("",recordlibDB);
			
			asyncDataMutex->WaitOne();
			System::Collections::Generic::Dictionary<int, int>^ introPositionsCopy = introPositions;
			introPositions = gcnew System::Collections::Generic::Dictionary<int, int>();
			asyncDataMutex->ReleaseMutex();

			for each (System::Collections::Generic::KeyValuePair<int,int>^ introInfo in introPositionsCopy)
			{
				int introPosition = introInfo->Value/1000;
				recordlibDataAdapter->SelectCommand->CommandText = System::String::Concat("UPDATE track SET intro=interval '",
																		introPosition.ToString(),
																		"' WHERE trackid=",
																		introInfo->Key.ToString());

				/** Clean up just for safety sake **/
				updateDataset->Reset();
				try
				{
					recordlibDataAdapter->Fill(updateDataset);
				}
				catch (System::IO::IOException^ e)
				{
					LogManager::write(System::String::Concat("IO Exception in npgsql:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
					return;
				}
				catch (NpgsqlException^ e)
				{
					/** Normally this will be a cannot connect as we should be able to guarantee a correct
					 *  sql command
					**/
					System::String^ errorMessages = "PGSQL ERROR:\n";
					/** Get all the errors returned from the db server **/
					errorMessages = System::String::Concat(
									errorMessages,
									"Message: \n", e->Message, "\n",
									"Error SQL: \n", e->ErrorSql, "\n",
									"Error Position: \n", e->Position, "\n",
									"Detail: \n", e->Detail, "\n",
									"Hint: \n", e->Hint, "\n",
									"Stack Trace: \n", e->StackTrace);
					/** Log an error - **/
					LogManager::write(errorMessages, LOG_ERROR, LOG_DATABASE);
				}
				catch (System::InvalidOperationException^ e)
				{
					/** Bad programming is the only thing that gets us here,
					 *  Log an error
					**/
					LogManager::write(System::String::Concat("bapsdb connection already open, program error:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
				}
			}
		}
		if (playCounts->Count > 0)
		{
			System::String^ connStr = System::String::Concat("Server=", CONFIG_GETSTR(CONFIG_DBSERVER), ";");
			connStr = System::String::Concat(connStr, "Database=", CONFIG_GETSTR(CONFIG_BAPSDBNAME), ";");
			connStr = System::String::Concat(connStr, "User Id=", CONFIG_GETSTR(CONFIG_DBUSERNAME), ";");
			connStr = System::String::Concat(connStr, "Password=", CONFIG_GETSTR(CONFIG_DBPASSWORD), ";");
			connStr = System::String::Concat(connStr, "Port=", CONFIG_GETSTR(CONFIG_DBPORT), ";");

			/** Connect to the baps database **/
			NpgsqlConnection^ bapsDB = gcnew NpgsqlConnection(connStr);
			
			System::Data::DataSet^ updateDataset = gcnew System::Data::DataSet();
			NpgsqlDataAdapter^ bapsDataAdapter = gcnew NpgsqlDataAdapter("",bapsDB);
			asyncDataMutex->WaitOne();
			System::Collections::Generic::List<PlayCountInfo^>^ playCountsCopy = playCounts;
			playCounts = gcnew System::Collections::Generic::List<PlayCountInfo^>();
			asyncDataMutex->ReleaseMutex();

			/** Clean up just for safety sake **/
			updateDataset->Reset();
			try
			{

				System::String ^ ServerID;
				NpgsqlCommand^ oldCommand = bapsDataAdapter->SelectCommand;
				// Declare the parameter in the query string
				NpgsqlCommand^ command = gcnew NpgsqlCommand("SELECT serverid "
															  "FROM baps_server "
															  "WHERE servername=:sname", bapsDB);
			    
				// Now add the parameter to the parameter collection of the command specifying its type.
				command->Parameters->Add(gcnew NpgsqlParameter("sname", System::Data::DbType::AnsiString));

				// Now, add a value to it and later execute the command as usual.
				command->Parameters[0]->Value = CONFIG_GETSTR(CONFIG_SERVERID);
				bapsDataAdapter->SelectCommand = command;

				bapsDataAdapter->Fill(updateDataset);
				if (updateDataset->Tables->Count == 1 &&
					updateDataset->Tables[0]->Rows->Count != 0)
				{
					ServerID = updateDataset->Tables[0]->Rows[0][0]->ToString();
				}
				else
				{
					updateDataset->Reset();
					bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																  "INSERT INTO baps_server "
																  "(servername) "
																  "VALUES "
																  "(:sname); "
																  "SELECT serverid "
																  "FROM baps_server "
																  "WHERE servername=:sname");
					bapsDataAdapter->Fill(updateDataset);
					ServerID = updateDataset->Tables[0]->Rows[0][0]->ToString();
				}
				bapsDataAdapter->SelectCommand = oldCommand;
				updateDataset->Reset();
				for each (PlayCountInfo^ playCountUpdate in playCountsCopy)
				{
					System::String^ AudioID = nullptr;

					if (playCountUpdate->trackid != -1)
					{
						bapsDataAdapter->SelectCommand->CommandText = System::String::Concat("SELECT audioid "
																							 "FROM baps_audio "
																							  "WHERE trackid='",
																							  playCountUpdate->trackid.ToString(),
																							  "'");
						bapsDataAdapter->Fill(updateDataset);
						if (updateDataset->Tables->Count == 1 &&
							updateDataset->Tables[0]->Rows->Count != 0)
						{
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
						updateDataset->Reset();
					}
					if (AudioID == nullptr)
					{
						NpgsqlCommand^ oldCommand = bapsDataAdapter->SelectCommand;
						// Declare the parameter in the query string
						NpgsqlCommand^ command = gcnew NpgsqlCommand("SELECT audioid "
																	 "FROM baps_audio "
																	 "WHERE filename= :fname", bapsDB);
					    
						// Now add the parameter to the parameter collection of the command specifying its type.
						command->Parameters->Add(gcnew NpgsqlParameter("fname", System::Data::DbType::AnsiString));

						// Now, add a value to it and later execute the command as usual.
						command->Parameters[0]->Value = playCountUpdate->filename;
						bapsDataAdapter->SelectCommand = command;

						bapsDataAdapter->Fill(updateDataset);
						if (updateDataset->Tables->Count == 1 &&
							updateDataset->Tables[0]->Rows->Count != 0)
						{
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
						else
						{
							if (playCountUpdate->trackid == -1)
							{
								bapsDataAdapter->SelectCommand->CommandText = "INSERT INTO baps_audio"
																			  "(filename) "
																			  "VALUES "
																			  "(:fname); "
																			  "SELECT audioid "
																			  "FROM baps_audio "
																			  "WHERE filename=:fname";
							}
							else
							{
								bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																			  "INSERT INTO baps_audio "
																			  "(trackid,filename) "
																			  "VALUES "
																			  "('", playCountUpdate->trackid.ToString(),"',"
																			  ":fname);"
																			  "SELECT audioid "
																			  "FROM baps_audio "
																			  "WHERE trackid='",playCountUpdate->trackid.ToString(),"'");
							}
							
							bapsDataAdapter->Fill(updateDataset);
							System::Object^ fred  = updateDataset->Tables[0]->Rows[0][0];
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
						bapsDataAdapter->SelectCommand = oldCommand;
					}
					bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																  "INSERT INTO baps_audiolog "
																  "(serverid,audioid) "
																  "VALUES "
																  "('",ServerID, "','",AudioID,"')"); 
					bapsDataAdapter->Fill(updateDataset);
				}
			}
			catch (System::IO::IOException^ e)
			{
				LogManager::write(System::String::Concat("IO Exception in npgsql:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			}
			catch (NpgsqlException^ e)
			{
				/** Normally this will be a cannot connect as we should be able to guarantee a correct
				 *  sql command
				**/
				System::String^ errorMessages = "PGSQL ERROR:\n";
				/** Get all the errors returned from the db server **/
				errorMessages = System::String::Concat(
								errorMessages,
								"Message: \n", e->Message, "\n",
								"Error SQL: \n", e->ErrorSql, "\n",
								"Error Position: \n", e->Position, "\n",
								"Detail: \n", e->Detail, "\n",
								"Hint: \n", e->Hint, "\n",
								"Stack Trace: \n", e->StackTrace);
				/** Log an error - **/
				LogManager::write(errorMessages, LOG_ERROR, LOG_DATABASE);
			}
			catch (System::InvalidOperationException^ e)
			{
				/** Bad programming is the only thing that gets us here,
				 *  Log an error
				**/
				LogManager::write(System::String::Concat("bapsdb connection already open, program error:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			}
		}
	}
	catch (System::Exception^ e) 
	{
		System::String^ errorMessages = "GENERAL ASYNC UPDATE ERROR:\n";
		/** Get all the errors returned from the db server **/
		errorMessages = System::String::Concat(
						errorMessages,
						"Message: \n", e->Message, "\n",
						"Stack Trace: \n", e->StackTrace);
		/** Log an error - **/
		LogManager::write(errorMessages, LOG_ERROR, LOG_DATABASE);	
	}
	finally
	{
		updateInProgress = false;
		asyncActionMutex->ReleaseMutex();
	}
}

void AsyncActionManager::addIntroPosition(int trackid, int introPosition)
{
	if (CONFIG_GETINT(CONFIG_SAVEINTROPOSITIONS) == 1)
	{
		asyncDataMutex->WaitOne();
		try
		{
			introPositions[trackid] = introPosition;
		}
		finally
		{
			asyncDataMutex->ReleaseMutex();
		}
	}
}
void AsyncActionManager::incPlayCount(Track^ track)
{
	if (CONFIG_GETINT(CONFIG_STOREPLAYCOUNTS) == 1)
	{
		asyncDataMutex->WaitOne();
		try
		{
			if (track->getType() == BAPSNET_LIBRARYITEM)
			{
				LibraryTrack^ ltrack = safe_cast<LibraryTrack^>(track);
				playCounts->Add(gcnew PlayCountInfo(ltrack->getFileLocation(),ltrack->TrackID));
			}
			else
			{
				
				playCounts->Add(gcnew PlayCountInfo(track->getFileLocation()));
			}
		}
		finally
		{
			asyncDataMutex->ReleaseMutex();
		}
	}
}