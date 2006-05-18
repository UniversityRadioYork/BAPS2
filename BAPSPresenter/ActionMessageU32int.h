#pragma once

#include "ActionMessage.h"

/**
	Sends a single integer
**/

namespace BAPSPresenter
{
	ref class ActionMessageU32int: public ActionMessage
	{
		u32int i;

	public:
		ActionMessageU32int(Command _cmd, u32int _i)
			: ActionMessage(_cmd), i(_i){};
		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)4);
			clientSocket->send(i);
		}
	};
};