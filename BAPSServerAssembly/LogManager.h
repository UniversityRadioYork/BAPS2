#pragma once

namespace BAPSServerAssembly
{
	/** WORK NEEDED: make this list into something printable **/
	enum LogLevel
	{
		LOG_ERROR		= 0,
		LOG_WARNING		= 1,
		LOG_INFO		= 2
	};

	enum LogEvent
	{
		LOG_OTHER		= 0,
		LOG_DATABASE	= 1,
		LOG_REGISTRY	= 2,
		LOG_OBJECTS		= 3,
		LOG_DECODE		= 4,
		LOG_PLAYBACK	= 5,
		LOG_COMMS		= 6,
		LOG_PLAYLIST	= 7,
		LOG_SECURITY	= 8,
		LOG_CONFIG		= 9,
		LOG_SYSTEM		= 10,
		LOG_EMAIL		= 11
	};
	/**
	 *  This class provides global Logging functionality
	**/

	ref class LogManager
	{
	public:
		/** Log Manager must be initialised before use, this is assumed to be called **/
		static void initLogManager();
		/** It would be nice to close properly so this is also assumed to be called **/
		static void closeLogManager();
		/** All logs are written through this function levels and events as above **/
		static void write(System::String^ message, LogLevel level, LogEvent event);
		/** When the Log Manager fails to initialize then the application log is used **/
		static void emergency(System::String^ message);
		/** Accessor for emergencyRaised **/
		static bool hasBeenEmergency() { return emergencyRaised; }
	private:
		/** The open log handle **/
		static System::Diagnostics::EventLog^ log;
		static bool emergencyRaised = false;
	};
};