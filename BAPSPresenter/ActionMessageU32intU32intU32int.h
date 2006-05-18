#pragma once

#include "ActionMessage.h"

/**
	Sends three integers in the order they are passed in
**/

namespace BAPSPresenter
{
	ref class ActionMessageU32intU32intU32int: public ActionMessage
	{
		u32int i1;
		u32int i2;
		u32int i3;

	public:
		ActionMessageU32intU32intU32int(Command _cmd, u32int _i1, u32int _i2, u32int _i3)
			: ActionMessage(_cmd), i1(_i1), i2(_i2), i3(_i3){};
		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)12);
			clientSocket->send(i1);
			clientSocket->send(i2);
			clientSocket->send(i3);
		}
	};
};