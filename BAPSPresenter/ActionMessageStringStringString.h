#pragma once

#include "ActionMessage.h"

/**
	Sends two strings in the order passed in
**/

namespace BAPSPresenter
{
	ref class ActionMessageStringStringString: public ActionMessage
	{
		System::String ^s1, ^s2, ^s3;

	public:

		ActionMessageStringStringString(Command _cmd, System::String^ _s1, System::String^ _s2, System::String^ _s3)
			: ActionMessage(_cmd), s1(_s1), s2(_s2), s3(_s3){};

		virtual void sendMsg(ClientSocket^ clientSocket) override
		{
			clientSocket->send(cmd);
			clientSocket->send((u32int)(12+s1->Length+s2->Length+s3->Length));
			clientSocket->send(s1);
			clientSocket->send(s2);
			clientSocket->send(s3);
		}

	};
};