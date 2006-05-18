#include "stdafx.h"
#include "LogManager.h"
#include "Exceptions.h"

/**
 *  This class provides global Logging functionality
**/

using namespace System::Diagnostics;
void LogManager::initLogManager()
{
	try
	{
		System::String^ logName = CONFIG_GETSTR(CONFIG_LOGNAME);
		System::String^ logSource = CONFIG_GETSTR(CONFIG_LOGSOURCE);
		// Does the Log already exist?
		if (!EventLog::Exists(logName))
		{
			// Does the event source already exist?
			if (EventLog::SourceExists(logSource))
			{
				// Delete the event source as it can 
				// only be associated with one log
				EventLog::DeleteEventSource(logSource);
			}
			// Create the event source and associate it 
			// with the new custom log.
			EventLog::CreateEventSource(logSource, logName);
		}
		log = gcnew EventLog(logName, ".", logSource);
	}
	catch (System::Exception^ e)
	{
		throw gcnew BAPSTerminateException(System::String::Concat("LogManager failed to initialize:\n", e->Message, "Stack Trace:\n",e->StackTrace));
	}
}
void LogManager::closeLogManager()
{
	try
	{
		if (log != nullptr)
		{
			log->Close();
		}
	}
	catch (System::Exception^ e)
	{
		emergency(System::String::Concat("LogManager failed to close:\n", e->Message, "Stack Trace:\n",e->StackTrace));
	}
}

void LogManager::emergency(System::String^ message)
{
	/**
		NO EXCEPTION HANDLING: This is emergency logging code and therefore there is
	    nowhere else to attempt to log after this attempt. The system will catch
		the exception and generate an Application Error log automatically
	**/
	System::Diagnostics::EventLog^ emergLog = gcnew EventLog("Application", ".", "BAPSServerService");
	emergLog->WriteEntry(message, EventLogEntryType::Error, 0);
	emergLog->Close();
}

void LogManager::write(System::String^ message, LogLevel level, LogEvent event)
{
	try
	{
		switch (level)
		{
		case LOG_INFO:
			{
				log->WriteEntry(message, EventLogEntryType::Information, event);
				break;
			}
		case LOG_WARNING:
			{
				log->WriteEntry(message, EventLogEntryType::Warning, event);
				break;
			}
		case LOG_ERROR:
			{
				/** WORK NEEDED: consider getting a backtrace/stack unwind **/
				log->WriteEntry(message, EventLogEntryType::Error, event);
				break;
			}
		default:
			{
				log->WriteEntry(System::String::Concat("INVALID LOG TYPE: ", System::Convert::ToString(level), "\n",message), EventLogEntryType::Error, event);
				break;
			}
		}
	}
	catch (System::Exception^ e)
	{
		emergency(System::String::Concat("Failed to write to custom BAPS log. Message being written was:\n", message, "\nException information:\n", e->Message, "Stack Trace:\n",e->StackTrace));
	}
}