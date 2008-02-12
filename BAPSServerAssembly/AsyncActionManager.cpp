#include "StdAfx.h"
#include "AsyncActionManager.h"
#include "ClientInstance.h"
#include "LogManager.h"

using namespace BAPSServerAssembly;

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
				recordlibDataAdapter->SelectCommand->CommandText = System::String::Concat("UPDATE rec_track SET intro=interval '",
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
		if (playbackEvents->Count > 0)
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
			System::Collections::Generic::List<PlaybackEventInfo^>^ playbackEventsCopy = playbackEvents;
			playbackEvents = gcnew System::Collections::Generic::List<PlaybackEventInfo^>();
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

				updateDataset->Reset();
				bapsDataAdapter->Fill(updateDataset);
				if (updateDataset->Tables->Count == 1 &&
					updateDataset->Tables[0]->Rows->Count != 0)
				{
					ServerID = updateDataset->Tables[0]->Rows[0][0]->ToString();
				}
				else
				{
					bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																  "INSERT INTO baps_server "
																  "(servername) "
																  "VALUES "
																  "(:sname); "
																  "SELECT serverid "
																  "FROM baps_server "
																  "WHERE servername=:sname");
					updateDataset->Reset();
					bapsDataAdapter->Fill(updateDataset);
					ServerID = updateDataset->Tables[0]->Rows[0][0]->ToString();
				}
				bapsDataAdapter->SelectCommand = oldCommand;

				for each (PlaybackEventInfo^ playbackEvent in playbackEventsCopy)
				{
					System::String^ AudioID = nullptr;
					if (playbackEvent->trackid != -1)
					{
						bapsDataAdapter->SelectCommand->CommandText = System::String::Concat("SELECT audioid "
																							 "FROM baps_audio "
																							  "WHERE trackid='",
																							  playbackEvent->trackid.ToString(),
																							  "'");
						updateDataset->Reset();
						bapsDataAdapter->Fill(updateDataset);
						if (updateDataset->Tables->Count == 1 &&
							updateDataset->Tables[0]->Rows->Count != 0)
						{
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
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
						command->Parameters[0]->Value = playbackEvent->filename;
						bapsDataAdapter->SelectCommand = command;

						updateDataset->Reset();
						bapsDataAdapter->Fill(updateDataset);
						if (updateDataset->Tables->Count == 1 &&
							updateDataset->Tables[0]->Rows->Count != 0)
						{
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
						else
						{
							if (playbackEvent->trackid == -1)
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
																			  "('", playbackEvent->trackid.ToString(),"',"
																			  ":fname);"
																			  "SELECT audioid "
																			  "FROM baps_audio "
																			  "WHERE trackid='",playbackEvent->trackid.ToString(),"'");
							}
							
							updateDataset->Reset();
							bapsDataAdapter->Fill(updateDataset);
							System::Object^ fred  = updateDataset->Tables[0]->Rows[0][0];
							AudioID = updateDataset->Tables[0]->Rows[0][0]->ToString();
						}
						bapsDataAdapter->SelectCommand = oldCommand;
					}
					if (playbackEvent->isStartEvent)
					{
						/** A start event **/
						bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																	  "INSERT INTO baps_audiolog "
																	  "(serverid,channel,audioid) "
																	  "VALUES "
																	  "('",ServerID, "','",playbackEvent->channel,"','",AudioID,"')"); 
						
						updateDataset->Reset();
						bapsDataAdapter->Fill(updateDataset);
						LogManager::write("playcommit on channel: "+playbackEvent->channel.ToString()+playbackEvent->filename+"--"+AudioID, LOG_INFO, LOG_DATABASE);
					}
					else
					{
						/** A stop event **/
						bapsDataAdapter->SelectCommand->CommandText = System::String::Concat(
																	  "UPDATE baps_audiolog "
																	  "SET timestopped=now()"
																	  "WHERE audiologid=(SELECT audiologid "
																	  " 				 FROM baps_audiolog "
																	  "				     WHERE serverid='",ServerID, "' "
																	  "                  AND channel='",playbackEvent->channel,"' "
																	  "                  AND audioid='",AudioID,"' "
																	  "                  ORDER BY timeplayed DESC "
																	  "                  LIMIT 1)");
						
						updateDataset->Reset();
						bapsDataAdapter->Fill(updateDataset);
						LogManager::write("stopcommit on channel: "+playbackEvent->channel.ToString()+playbackEvent->filename+"--"+AudioID, LOG_INFO, LOG_DATABASE);
					}
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
		saveServerState();
		updateInProgress = false;
		asyncActionMutex->ReleaseMutex();
	}
}

void AsyncActionManager::saveServerState()
{
	System::Xml::XmlWriterSettings^ xws = gcnew System::Xml::XmlWriterSettings();
	xws->CloseOutput = true;
	xws->Indent = true;
	xws->IndentChars = "  ";
	System::String^ path = System::Reflection::Assembly::GetExecutingAssembly()->Location;
	path = System::IO::Path::GetDirectoryName(path);
	System::Xml::XmlWriter^ xw = System::Xml::XmlWriter::Create(System::String::Concat(path,"\\serverstate.xml"), xws);
	xw->WriteStartElement("bapsserverstate");
	ClientManager::getAudio()->dumpAsXML(xw);
	xw->WriteEndElement();
	xw->Flush();
	xw->Close();

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
void AsyncActionManager::logPlayEvent(int channel, Track^ track)
{
	if (CONFIG_GETINT(CONFIG_STOREPLAYBACKEVENTS) != CONFIG_PLAYBACKEVENT_STORE_NONE)
	{
		asyncDataMutex->WaitOne();
		try
		{
			if (track->getType() == BAPSNET_LIBRARYITEM)
			{
				LibraryTrack^ ltrack = safe_cast<LibraryTrack^>(track);
				playbackEvents->Add(gcnew PlaybackEventInfo(ltrack->getFileLocation(),channel, true,ltrack->TrackID));
			}
			else
			{
				
			LogManager::write("playevent on channel: "+channel.ToString()+track->getFileLocation(), LOG_INFO, LOG_DATABASE);
				playbackEvents->Add(gcnew PlaybackEventInfo(track->getFileLocation(), channel,true));
			}
		}
		finally
		{
			asyncDataMutex->ReleaseMutex();
		}
	}
}

void AsyncActionManager::logStopEvent(int channel, Track^ track)
{
	if (CONFIG_GETINT(CONFIG_STOREPLAYBACKEVENTS) != CONFIG_PLAYBACKEVENT_STORE_NONE)
	{
		asyncDataMutex->WaitOne();
		try
		{
			if (track->getType() == BAPSNET_LIBRARYITEM)
			{
				LibraryTrack^ ltrack = safe_cast<LibraryTrack^>(track);
				playbackEvents->Add(gcnew PlaybackEventInfo(ltrack->getFileLocation(), channel, false, ltrack->TrackID));
			}
			else
			{
							LogManager::write("stopevent on channel: "+channel.ToString()+track->getFileLocation(), LOG_INFO, LOG_DATABASE);

				playbackEvents->Add(gcnew PlaybackEventInfo(track->getFileLocation(), channel, false));
			}
		}
		finally
		{
			asyncDataMutex->ReleaseMutex();
		}
	}
}