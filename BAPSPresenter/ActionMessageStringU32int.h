#pragma once

#include "ActionMessage.h"

/**
	Sends a single string followed by a u32int
**/

namespace BAPSPresenter
{
	ref class ActionMessageStringU32int: public ActionMessage
	{
		System::String^ s1;
		u32int i2;

	public:
		ActionMessageStringU32int(Command _cmd, System::String^ _s, u32int _i)
			: ActionMessage(_cmd), s1(_s), i2(_i){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(8+s1->Length));
			clientSocket->send(s1);
			clientSocket->send(i2);
		}

	};
};