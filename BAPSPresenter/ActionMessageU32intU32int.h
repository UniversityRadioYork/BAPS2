#pragma once

#include "ActionMessage.h"

/**
	Sends two integers in the order passed in
**/

namespace BAPSPresenter
{
	ref class ActionMessageU32intU32int: public ActionMessage
	{
		u32int i1;
		u32int i2;

	public:
		ActionMessageU32intU32int(Command _cmd, u32int _i1, u32int _i2)
			: ActionMessage(_cmd), i1(_i1), i2(_i2){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)8);
			clientSocket->send(i1);
			clientSocket->send(i2);
		}
	};
};