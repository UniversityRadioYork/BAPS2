#pragma once

#include "ActionMessage.h"

/**
	Sends a single string
**/

namespace BAPSPresenter
{
	ref class ActionMessageString: public ActionMessage
	{
		System::String^ s;

	public:
		ActionMessageString(Command _cmd, System::String^ _s)
			: ActionMessage(_cmd), s(_s){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(4+s->Length));
			clientSocket->send(s);
		}

	};
};