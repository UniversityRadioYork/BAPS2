#pragma once

#include "ActionMessage.h"

/**
	Sends a single float
**/

namespace BAPSPresenter
{
	ref class ActionMessageFloat: public ActionMessage
	{
		float f;

	public:
		ActionMessageFloat(Command _cmd, float _f)
			: ActionMessage(_cmd), f(_f){};
		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)4);
			clientSocket->send(f);
		}
	};
};