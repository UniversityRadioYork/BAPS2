#pragma once

enum ConfigOption
{
	CONFIG_CHANNELCOUNT,
	CONFIG_DEVICE,
	CONFIG_CHANNELNAME,
	CONFIG_AUTOADVANCE,
	CONFIG_AUTOPLAY,
	CONFIG_REPEAT,
	CONFIG_DIRECTORYCOUNT,
	CONFIG_NICEDIRECTORYNAME,
	CONFIG_DIRECTORYLOCATION,
	CONFIG_SERVERID,
	CONFIG_PORT,
	CONFIG_MAXQUEUECONNS,
	CONFIG_CLIENTCONNLIMIT,
	CONFIG_DBSERVER,
	CONFIG_DBPORT,
	CONFIG_LIBRARYDBNAME,
	CONFIG_BAPSDBNAME,
	CONFIG_DBUSERNAME,
	CONFIG_DBPASSWORD,
	CONFIG_LIBRARYLOCATION,
	CONFIG_SAVEINTROPOSITIONS,
	CONFIG_STOREPLAYBACKEVENTS,
	CONFIG_LOGNAME,
	CONFIG_LOGSOURCE,
	CONFIG_SUPPORTADDRESS,
	CONFIG_SMTPSERVER,
	CONFIG_BAPSCONTROLLERENABLED,
	CONFIG_BAPSCONTROLLERBUTTONCOUNT,
	CONFIG_BAPSCONTROLLERBUTTONCODE,
	CONFIG_BAPSPADDLEMODE,
	CONFIG_CLEANMUSICONLY,
	CONFIG_BAPSCONTROLLER2ENABLED,
	CONFIG_BAPSCONTROLLER2DEVICECOUNT,
	CONFIG_BAPSCONTROLLER2SERIAL,
	CONFIG_BAPSCONTROLLER2OFFSET,
	CONFIG_BAPSCONTROLLER2BUTTONCOUNT,
	CONFIG_BAPSCONTROLLER2BUTTONCODE,
	CONFIG_LASTOPTION
};

enum ConfigType
{
	CONFIG_TYPE_INT = 0,
	CONFIG_TYPE_STR = 1,
	CONFIG_TYPE_CHOICE =2
};

enum ConfigResult
{
	CONFIG_RESULT_SUCCESS,
	CONFIG_RESULT_BADTYPE,
	CONFIG_RESULT_BADOPTION,
	CONFIG_RESULT_INDEXINGERROR,
	CONFIG_RESULT_INDEXOUTOFRANGE,
	CONFIG_RESULT_VALIDATIONERROR,
	CONFIG_RESULT_NOPERMISSION
};

ref class ConfigResultText
{
public:
	static array<System::String^>^ text = 
	{"Success",
	 "Incorrect type for option",
	 "Option does not exist",
	 "Incorrect indexing for option",
	 "Specified index exceeds limit",
	 "Setting failed validation check",
	 "You do not have permission"};
};