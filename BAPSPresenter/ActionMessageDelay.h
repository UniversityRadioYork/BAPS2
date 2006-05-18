#pragma once

#include "ActionMessage.h"

/**
	Pauses the sender loop for a given amount of time (ms)
**/

namespace BAPSPresenter
{
	ref class ActionMessageDelay: public ActionMessage
	{
		unsigned int delayLength;

	public:
		ActionMessageDelay(unsigned int _delayLength)
			: ActionMessage(0), delayLength(_delayLength){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			System::Threading::Thread::Sleep(delayLength);
		}

	};
};