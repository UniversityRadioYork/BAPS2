#pragma once

#include "ActionMessage.h"

/**
	Sends two strings in the order passed in
**/

namespace BAPSPresenter
{
	ref class ActionMessageStringString: public ActionMessage
	{
		System::String ^s1, ^s2;

	public:

		ActionMessageStringString(Command _cmd, System::String^ _s1, System::String^ _s2)
			: ActionMessage(_cmd), s1(_s1), s2(_s2){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(8+s1->Length+s2->Length));
			clientSocket->send(s1);
			clientSocket->send(s2);
		}

	};
};