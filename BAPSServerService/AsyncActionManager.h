#pragma once
#include "LibraryTrack.h"
#include "decodeStructs.h"
/**
	This class provides a method of running non critical actions in the background.
	Actions are queued up and then dispatched as and when the dispatch thread reaches them.
	There is no guarantee when an action will be dispatched, but all action updates
	should have bounded timeouts.
**/

ref struct PlayCountInfo
{
	PlayCountInfo(System::String^ _filename)
		:filename(_filename), trackid(-1)
	{}
	PlayCountInfo(System::String^ _filename, int _trackid)
		: filename(_filename), trackid(_trackid)
	{}
	System::String^ filename;
	int trackid;
};

ref class AsyncActionManager
{
public:
	static void initAsyncActionManager()
	{
		introPositions = gcnew System::Collections::Generic::Dictionary<int, int>;
		playCounts = gcnew System::Collections::Generic::List<PlayCountInfo^>;
		asyncActionMutex = gcnew System::Threading::Mutex();
		asyncDataMutex = gcnew System::Threading::Mutex();
		/** In 300ms run updateClients every 300ms **/
		updateInProgress = false;
		System::Threading::TimerCallback^ tc = gcnew System::Threading::TimerCallback(&AsyncActionManager::doActions);
		asyncActionTimer = gcnew System::Threading::Timer(tc,
												   nullptr,
												   5000,
												   5000);
	}
	static void closeAsyncActionManager()
	{
		/** Set the timer to never execute its delegate **/
		if (asyncActionTimer != nullptr)
		{
			asyncActionTimer->Change(System::Threading::Timeout::Infinite,System::Threading::Timeout::Infinite);
			asyncActionTimer->~Timer();
			asyncActionTimer = nullptr;
		}
	}

	static void doActions(System::Object^ name);
	static void addIntroPosition(int trackid, int introPosition);
	static void incPlayCount(Track^ track);

private:
	static System::Collections::Generic::Dictionary<int, int>^ introPositions;
	static System::Collections::Generic::List<PlayCountInfo^>^ playCounts;
	static System::Threading::Mutex^ asyncActionMutex;
	static System::Threading::Mutex^ asyncDataMutex;
	static System::Threading::Timer^ asyncActionTimer;
	static bool updateInProgress;
};