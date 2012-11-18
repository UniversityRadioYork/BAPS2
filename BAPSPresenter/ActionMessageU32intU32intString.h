#pragma once

#include "ActionMessage.h"

/**
	Sends two integers in the order they were passed in
	followed by a string
**/

namespace BAPSPresenter
{
	ref class ActionMessageU32intU32intString: public ActionMessage
	{
		u32int i1;
		u32int i2;
		System::String^ s;

	public:
		ActionMessageU32intU32intString(Command _cmd, u32int _i1, u32int _i2, System::String^ _s)
			: ActionMessage(_cmd), i1(_i1), i2(_i2), s(_s){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(8+s->Length));
			clientSocket->send(i1);
			clientSocket->send(i2);
			clientSocket->send(s);
		}
	};
};