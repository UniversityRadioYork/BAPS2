#pragma once

#include "ActionMessage.h"

/**
	Sends two strings in the order passed in
**/

namespace BAPSPresenter
{
	ref class ActionMessageStringStringU32int: public ActionMessage
	{
		System::String ^s1, ^s2;
		u32int u3;

	public:

		ActionMessageStringStringU32int(Command _cmd, System::String^ _s1, System::String^ _s2, u32int _u3)
			: ActionMessage(_cmd), s1(_s1), s2(_s2), u3(_u3){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(12+s1->Length+s2->Length));
			clientSocket->send(s1);
			clientSocket->send(s2);
			clientSocket->send(u3);
		}

	};
};