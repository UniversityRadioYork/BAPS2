#pragma once
#include "ClientSocket.h"

/** 
	Basic Message and base class for all other messages
	Sends just a command
**/

namespace BAPSPresenter
{
	ref class ActionMessage
	{
	protected:
		Command cmd;

	public:
		ActionMessage(Command _cmd)
			: cmd(_cmd){};


		virtual void sendMsg(ClientSocket^ clientSocket)
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)0);
		}

	};
};