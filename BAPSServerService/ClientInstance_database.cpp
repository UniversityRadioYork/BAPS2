#include "stdafx.h"
#include "ClientInstance.h"
#include "LibraryTrack.h"
#include "TextEntry.h"

/**
 *  This file contains the implementations of all the MUSICLIB functionality
**/

bool ClientInstance::searchMusicLib(System::String^ artist, System::String^ title, int trackid, int page)
{
	bool byTrackid = (trackid != -1);
	System::String^ connStr = System::String::Concat("Server=", CONFIG_GETSTR(CONFIG_DBSERVER), ";");
	connStr = System::String::Concat(connStr, "Database=", CONFIG_GETSTR(CONFIG_LIBRARYDBNAME), ";");
	connStr = System::String::Concat(connStr, "User Id=", CONFIG_GETSTR(CONFIG_DBUSERNAME), ";");
	connStr = System::String::Concat(connStr, "Password=", CONFIG_GETSTR(CONFIG_DBPASSWORD), ";");
	connStr = System::String::Concat(connStr, "Port=", CONFIG_GETSTR(CONFIG_DBPORT), ";");

	recordlibDB = gcnew NpgsqlConnection(connStr);

	/** The client will send a string for part of the artist and then a string for part of the title
	 *  WORK NEEDED: extend this to allow for exact matching, matching of singles/albums, album titles
	**/

	int attempt = 0;
	bool success = false;

	while (!success)
	{
		System::String^ sql;
		/** Basic select statement WORK NEEDED: update this sql to be restricted to the correct level **/
		if (attempt == 0)
		{
			sql = "SELECT track.recordid, trackid, track.title, track.artist, extract(epoch from intro) as intro, track.location FROM track INNER JOIN record USING (recordid) WHERE ";
		}
		else
		{
			sql = "SELECT track.recordid, trackid, track.title, track.artist, extract(epoch from intro) as intro FROM track INNER JOIN record USING (recordid) WHERE ";
		}

		NpgsqlCommand^ command = gcnew NpgsqlCommand(sql, recordlibDB);
		if (byTrackid)
		{
			sql = System::String::Concat(sql, " trackid='",trackid.ToString(),"' ");
		}
		else
		{
			if (artist->Length !=0)
			{
				sql = System::String::Concat(sql, "LOWER(track.artist) LIKE LOWER('%'||:artist||'%')");
				command->Parameters->Add(gcnew NpgsqlParameter("artist", System::Data::DbType::AnsiString));
				command->Parameters["artist"]->Value = artist;
			}
			if (artist->Length !=0 && title->Length !=0)
			{
				sql = System::String::Concat(sql, " AND ");
			}
			if (title->Length !=0)
			{
				sql = System::String::Concat(sql, "LOWER(track.title) LIKE LOWER('%'||:title||'%')");
				command->Parameters->Add(gcnew NpgsqlParameter("title", System::Data::DbType::AnsiString));
				command->Parameters["title"]->Value = title;
			}
		}
		sql = sql + "AND digitised='t' ORDER BY ";
		System::String^ desasc = "";
		if (libraryAscDes == BAPSNET_ORDER_DESCENDING)
		{
			desasc = "DESC";
		}

		switch (libraryOrderBy)
		{
		case BAPSNET_ORDER_BYARTIST:
			sql = sql + "track.artist " + desasc + ", track.title";
			break;
		case BAPSNET_ORDER_BYTITLE:
			sql = sql + "track.title " + desasc + ", track.artist";
			break;
		case BAPSNET_ORDER_BYDATEADDED:
			sql = sql + "dateadded " + desasc;
			break;
		}
		sql = sql + " OFFSET "+(page*200).ToString()+" LIMIT 200";
		command->CommandText = sql;
		
		NpgsqlDataAdapter^ recordlibDataAdapter = gcnew NpgsqlDataAdapter();
		recordlibDataAdapter->SelectCommand = command;
		recordlibDataset = gcnew System::Data::DataSet();

		try
		{
			recordlibDataAdapter->Fill(recordlibDataset);
		}
		catch (System::IO::IOException^ e)
		{
			LogManager::write(System::String::Concat("IO Exception in npgsql:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			Command cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYERROR | 2;
			ClientManager::send(this, cmd, "Error: Check Database Server Name?");
			return false;
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

			if (attempt == 0)
			{
				attempt++;
				continue;
			}
			/** Send/Log an error and quit the function - **/
			LogManager::write(errorMessages, LOG_ERROR, LOG_DATABASE);
			Command cmd = BAPSNET_DATABASE | 1;
			if (byTrackid)
			{
				cmd |= BAPSNET_BAPSDBERROR;
			}
			else
			{
				cmd |= BAPSNET_LIBRARYERROR;
			}
			ClientManager::send(this, cmd, "Database connection failure");
			return false;
		}
		catch (System::InvalidOperationException^ e)
		{
			/** Bad programming is the only thing that gets us here,
			 *  Send/Log an error and quit the function
			**/
			LogManager::write(System::String::Concat("RecordLibrary connection already open, program error:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			Command cmd = BAPSNET_DATABASE | 2;
			if (byTrackid)
			{
				cmd |= BAPSNET_BAPSDBERROR;
			}
			else
			{
				cmd |= BAPSNET_LIBRARYERROR;
			}
			ClientManager::send(this, cmd, "Program error - seek technical advice");
			return false;
		}
		success=true;
	}

	if (!byTrackid)
	{
		/** Check if the server returned any tables **/
		if (recordlibDataset->Tables->Count != 1)
		{
			/** Say that there are no results following **/
			Command cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYRESULT;
			ClientManager::send(this, cmd, (u32int)0);
			return true;
		}
		/** It is safe to assume we both have a table and there will only be one **/
		System::Data::DataTable^ myTable = recordlibDataset->Tables[0];

		/** Say how many results are following **/
		Command cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYRESULT;
		ClientManager::send(this, cmd, (u32int)myTable->Rows->Count);
		/** Check if the server returned any rows **/
		if (myTable->Rows->Count == 0)
		{
			/** We are escaping for speed mainly **/
			return true;
		}

		/** Create placeholders for all the columns that are of interest **/
		System::Data::DataColumn ^title, ^artist;

		/** Find and assign the identifiers for each of the 'interesting' columns
		 *  Must ensure that all these columns are included in the select!
		**/
		int i;
		for (i = 0 ; i < myTable->Columns->Count ; i++)
		{
			System::String^ columnName = myTable->Columns[i]->ColumnName;
			if (System::String::Compare(columnName, "title") == 0)
			{
				title = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "artist") == 0)
			{
				artist = myTable->Columns[i];
			}
		}

		try
		{
			/** Iterate through the rows pulling out data as we need it.
			 *  WORK NEEDED: make this do less work, we only need strings and indices for now. see above
			**/
			int i;
			for (i = 0 ; i < myTable->Rows->Count ; i++)
			{
				System::Data::DataRow^ myRow = myTable->Rows[i];

				System::String^ description = System::String::Concat(myRow[title]->ToString(), " - ", myRow[artist]->ToString());
				Command cmd = BAPSNET_DATABASE | BAPSNET_LIBRARYRESULT | BAPSNET_DATABASE_MODEMASK;
				ClientManager::send(this, cmd, (u32int)i, description);
			}
		}
		catch (System::IndexOutOfRangeException^ e)
		{
			/** Bad programming will get us here, Check the sql statement includes all the columns
			 *  That we are pulling data out of!
			**/
			LogManager::write(System::String::Concat("Possible malformed recordlibrary sql, check coding:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			/** Just a helpful hint to a client **/
			Command cmd = BAPSNET_DATABASE | 3;
			ClientManager::send(this, cmd, "System Error - seek technical advice");
			return false;
		}
	}
	return true;
}
LibraryTrack^ ClientInstance::getLibraryTrack(int index)
{
	LibraryTrack^ tempTrack = gcnew LibraryTrack();
	try
	{
		/** It is safe to assume we both have a table and there will only be one **/
		System::Data::DataTable^ myTable = recordlibDataset->Tables[0];

		/** Create placeholders for all the columns that are of interest **/
		System::Data::DataColumn ^recordid, ^title, ^artist, ^trackid, ^intro, ^location;

		/** Find and assign the identifiers for each of the 'interesting' columns
		*  Must ensure that all these columns are included in the select!
		**/
		int i;
		for (i = 0 ; i < myTable->Columns->Count ; i++)
		{
			System::String^ columnName = myTable->Columns[i]->ColumnName;
			if (System::String::Compare(columnName, "recordid") == 0)
			{
				recordid = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "title") == 0)
			{
				title = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "artist") == 0)
			{
				artist = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "trackid") == 0)
			{
				trackid = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "location") == 0)
			{
				location = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "intro") == 0)
			{
				intro = myTable->Columns[i];
			}
		}
		System::Data::DataRow^ myRow = myTable->Rows[index];

		tempTrack->RecordID= System::Convert::ToInt32(myRow[recordid]);
		tempTrack->setTitle(myRow[title]->ToString());
		tempTrack->setArtist(myRow[artist]->ToString());
		tempTrack->TrackID =System::Convert::ToInt32(myRow[trackid]);
		if (location != nullptr && !myRow->IsNull(location))
		{
			tempTrack->setLocation(myRow[location]->ToString());
		}
		if (intro != nullptr && !myRow->IsNull(intro))
		{
			tempTrack->IntroPosition = System::Convert::ToInt32(myRow[intro]) *1000;
		}
		else
		{
			tempTrack->IntroPosition = 0;
		}
		return tempTrack;
	}
	catch (System::Exception^ e)
	{
		LogManager::write(System::String::Concat("Possible index out of range in getLibraryTrack:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_INFO, LOG_DATABASE);
		return nullptr;
	}
}

void ClientInstance::setupDatabaseConnection()
{
	System::String^ connStr = System::String::Concat("Server=", CONFIG_GETSTR(CONFIG_DBSERVER), ";");
	connStr = System::String::Concat(connStr, "Database=", CONFIG_GETSTR(CONFIG_BAPSDBNAME), ";");
	connStr = System::String::Concat(connStr, "User Id=", CONFIG_GETSTR(CONFIG_DBUSERNAME), ";");
	connStr = System::String::Concat(connStr, "Password=", CONFIG_GETSTR(CONFIG_DBPASSWORD), ";");
	connStr = System::String::Concat(connStr, "Port=", CONFIG_GETSTR(CONFIG_DBPORT), ";");

	/** Connect to the baps database **/
	bapsDB = gcnew NpgsqlConnection(connStr);

	bapsDataset = gcnew System::Data::DataSet();
}

bool ClientInstance::executeQuery(System::String^ sql)
{
	NpgsqlDataAdapter^ bapsDataAdapter = gcnew NpgsqlDataAdapter(sql,bapsDB);
	/** Clean up just for safety sake **/
	bapsDataset->Clear();
	try
	{
		bapsDataAdapter->Fill(bapsDataset);
	}
	catch (System::IO::IOException^ e)
	{
		LogManager::write(System::String::Concat("IO Exception in npgsql:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
		Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 3;
		ClientManager::send(this, cmd, "Error: Check Database Server Name?");
		return false;
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
		/** Send/Log an error and quit the function - **/
		LogManager::write(errorMessages, LOG_ERROR, LOG_DATABASE);
		Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 1;
		ClientManager::send(this, cmd, "Database connection failure");
		return false;
    }
	catch (System::InvalidOperationException^ e)
    {
		/** Bad programming is the only thing that gets us here,
		 *  Send/Log an error and quit the function
		**/
		LogManager::write(System::String::Concat("Possible: bapsdb connection already open, program error:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
		Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 2;
		ClientManager::send(this, cmd, "Program error - seek technical advice");
		return false;
	}
	return true;
}

void ClientInstance::getShows(System::String^ username, bool newShowsOnly)
{
	setupDatabaseConnection();
	System::String^ sql = System::String::Concat(
						  "SELECT baps_show.* "
						  "FROM baps_user, baps_show "
						  "WHERE baps_user.username='",
						   username,
						  "' "
						  "AND baps_user.userid=baps_show.userid ");
	if (newShowsOnly)
	{
		sql = System::String::Concat(sql,
									 "AND baps_show.broadcastdate > now()-interval '3 hour' ");
	}
	sql = System::String::Concat(sql, "ORDER BY broadcastdate, name");

	if (!executeQuery(sql))
	{
		// Escape if the query fails 
		return;
	}
	/** It is safe to assume we both have a table and there will only be one **/
	System::Data::DataTable^ myTable = bapsDataset->Tables[0];

	System::Collections::IEnumerator^ columnEnum = myTable->Columns->GetEnumerator();

	/** Create placeholders for all the columns that are of interest **/
	System::Data::DataColumn ^showid, ^name, ^broadcastdate;

	/** Find and assign the identifiers for each of the 'interesting' columns
	 *  Must ensure that all these columns are included in the select!
	**/
	while (columnEnum->MoveNext())
	{
		System::String^ columnName = static_cast<System::Data::DataColumn^>(columnEnum->Current)->ColumnName;
		if (System::String::Compare(columnName, "showid") == 0)
		{
			showid = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
		else if (System::String::Compare(columnName, "name") == 0)
		{
			name = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
		else if (System::String::Compare(columnName, "broadcastdate") == 0)
		{
			broadcastdate = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
	}
	System::Collections::IEnumerator^ rowEnum = myTable->Rows->GetEnumerator();
	Command cmd = BAPSNET_DATABASE | BAPSNET_SHOW;
	ClientManager::send(this, cmd, (u32int)myTable->Rows->Count);

	try
	{
		/** Iterate through the rows pulling out data as we need it. **/
		while (rowEnum->MoveNext())
		{
			System::Data::DataRow^ myRow = static_cast<System::Data::DataRow^>(rowEnum->Current);

			int currentShowid = safe_cast<int>(myRow[showid]);
			System::String^ currentDescription = myRow[broadcastdate]->ToString();
			currentDescription = System::String::Concat(currentDescription, " - ", static_cast<System::String^>(myRow[name]));
			cmd = BAPSNET_DATABASE | BAPSNET_SHOW | BAPSNET_DATABASE_MODEMASK;
			ClientManager::send(this, cmd, (u32int)currentShowid, currentDescription);
		}
	}
	catch (System::IndexOutOfRangeException^ e)
	{
		/** Bad programming will get us here, Check the sql statement includes all the columns
		 *  That we are pulling data out of!
		**/
		LogManager::write(System::String::Concat("Possible malformed getShows sql, check coding:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
		/** Just a helpful hint to a client **/
		Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 3;
		ClientManager::send(this, cmd, "System Error - seek technical advice");
		return;
	}
}
void ClientInstance::getListings(int showid)
{
	setupDatabaseConnection();
	System::String^ sql = System::String::Concat(
						  "SELECT baps_listing.* "
						  "FROM baps_listing "
						  "WHERE baps_listing.showid='",
						   showid.ToString(),
						  "' "
						  "ORDER BY channel");

	if (!executeQuery(sql))
	{
		// Escape if the query fails 
		return;
	}
	/** It is safe to assume we both have a table and there will only be one **/
	System::Data::DataTable^ myTable = bapsDataset->Tables[0];

	System::Collections::IEnumerator^ columnEnum = myTable->Columns->GetEnumerator();

	/** Create placeholders for all the columns that are of interest **/
	System::Data::DataColumn ^listingid, ^name, ^channel;

	/** Find and assign the identifiers for each of the 'interesting' columns
	 *  Must ensure that all these columns are included in the select!
	**/
	while (columnEnum->MoveNext())
	{
		System::String^ columnName = static_cast<System::Data::DataColumn^>(columnEnum->Current)->ColumnName;
		if (System::String::Compare(columnName, "listingid") == 0)
		{
			listingid = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
		else if (System::String::Compare(columnName, "name") == 0)
		{
			name = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
		else if (System::String::Compare(columnName, "channel") == 0)
		{
			channel = static_cast<System::Data::DataColumn^>(columnEnum->Current);
		}
	}
	System::Collections::IEnumerator^ rowEnum = myTable->Rows->GetEnumerator();
	Command cmd = BAPSNET_DATABASE | BAPSNET_LISTING;
	ClientManager::send(this, cmd, (u32int)myTable->Rows->Count);

	try
	{
		/** Iterate through the rows pulling out data as we need it. **/
		while (rowEnum->MoveNext())
		{
			System::Data::DataRow^ myRow = static_cast<System::Data::DataRow^>(rowEnum->Current);

			int currentListingid = safe_cast<int>(myRow[listingid]);
			System::String^ currentDescription = myRow[name]->ToString();
			int currentChannel = safe_cast<int>(myRow[channel]);
			cmd = BAPSNET_DATABASE | BAPSNET_LISTING | BAPSNET_DATABASE_MODEMASK;
			ClientManager::send(this, cmd, (u32int)currentListingid, (u32int)currentChannel, currentDescription);
		}
	}
	catch (System::IndexOutOfRangeException^ e)
	{
		/** Bad programming will get us here, Check the sql statement includes all the columns
		 *  That we are pulling data out of!
		**/
		LogManager::write(System::String::Concat("Possible malformed getListings sql, check coding:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
		/** Just a helpful hint to a client **/
		Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 3;
		ClientManager::send(this, cmd, "System Error - seek technical advice");
		return;
	}
}
void ClientInstance::assignListing(int channel, int listingid)
{
	if (channel < CHANNEL_COUNT)
	{
		setupDatabaseConnection();
		System::String^ sql = System::String::Concat(
								"SELECT "
								"baps_item.name1, "
								"baps_item.name2, "
								"baps_fileitem.filename, "
								"baps_libraryitem.trackid, "
								"baps_textitem.textinfo "
								"FROM "
								"((baps_item LEFT OUTER JOIN baps_fileitem USING (fileitemid)) "
								"LEFT OUTER JOIN baps_libraryitem USING (libraryitemid)) "
								"LEFT OUTER JOIN baps_textitem USING (textitemid) "
								"WHERE baps_item.listingid='",
								listingid.ToString(),
								"' "
								"ORDER BY position");

		if (!executeQuery(sql))
		{
			// Escape if the query fails 
			return;
		}
		/** It is safe to assume we both have a table and there will only be one **/
		System::Data::DataTable^ myTable = bapsDataset->Tables[0];

		/** Create placeholders for all the columns that are of interest **/
		System::Data::DataColumn ^name1, ^filename, ^name2;
		System::Data::DataColumn ^trackid, ^textinfo;

		/** Find and assign the identifiers for each of the 'interesting' columns
		*  Must ensure that all these columns are included in the select!
		**/
		int i;
		for (i = 0 ; i < myTable->Columns->Count ; i++)
		{
			System::String^ columnName = myTable->Columns[i]->ColumnName;
			if (System::String::Compare(columnName, "name1") == 0)
			{
				name1 = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "filename") == 0)
			{
				filename = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "name2") == 0)
			{
				name2 = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "trackid") == 0)
			{
				trackid = myTable->Columns[i];
			}
			else if (System::String::Compare(columnName, "textinfo") == 0)
			{
				textinfo = myTable->Columns[i];
			}

		} 
		try
		{
			/** Iterate through the rows pulling out data as we need it. **/
			for (i = 0 ; i < myTable->Rows->Count ; i++)
			{
				System::Data::DataRow^ myRow = myTable->Rows[i];
				System::String ^name1text = myRow[name1]->ToString();
				System::String ^name2text = myRow[name2]->ToString();
				if (!myRow->IsNull(filename))
				{
					System::String^ currentFilename = myRow[filename]->ToString();
					Track^ tempTrack = gcnew Track(currentFilename);
					ClientManager::getAudio()->getPlaylist(channel)->addEntry(tempTrack);
				}
				else if (!myRow->IsNull(trackid))
				{
					/** Will return false if an error occurred **/
					if (searchMusicLib(nullptr, nullptr, System::Convert::ToInt32(myRow[trackid]), 0))
					{
						/** Will return null if the track is not in the library or no longer digitised **/
						LibraryTrack^ tempTrack = getLibraryTrack(0);
						if (tempTrack != nullptr)
						{
							ClientManager::getAudio()->getPlaylist(channel)->addEntry(tempTrack);
						}
					}
				}
				else if (!myRow->IsNull(textinfo))
				{
					System::String^ currentTextinfo = myRow[textinfo]->ToString();
					TextEntry^ tempTrack = gcnew TextEntry(name1text,
														   currentTextinfo);
					ClientManager::getAudio()->getPlaylist(channel)->addEntry(tempTrack);
				}
			}
		}
		catch (System::IndexOutOfRangeException^ e)
		{
			/** Bad programming will get us here, Check the sql statement includes all the columns
			*  That we are pulling data out of!
			**/
			LogManager::write(System::String::Concat("Possible malformed assignListing sql, check coding:\n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_DATABASE);
			/** Just a helpful hint to a client **/
			Command cmd = BAPSNET_DATABASE | BAPSNET_BAPSDBERROR | 3;
			ClientManager::send(this, cmd, "System Error - seek technical advice");
			return;
		}
	}
	else
	{
		LogManager::write(System::String::Concat("Invalid channel: ", channel.ToString(), ", in assignListing command"), LOG_WARNING, LOG_DATABASE);
	}
}