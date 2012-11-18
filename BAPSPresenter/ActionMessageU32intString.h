#pragma once

#include "ActionMessage.h"

/**
	Sends an integer followed by a float
**/

namespace BAPSPresenter
{
	ref class ActionMessageU32intString: public ActionMessage
	{
		u32int i;
		System::String^ s;

	public:
		ActionMessageU32intString(Command _cmd, u32int _i, System::String^ _s)
			: ActionMessage(_cmd), i(_i), s(_s){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(8+s->Length));
			clientSocket->send(i);
			clientSocket->send(s);
		}
	};
};