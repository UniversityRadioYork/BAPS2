#include "stdafx.h"
#include "EmailWrapper.h"
#include "LogManager.h"
#include "ConfigManager.h"

using namespace BAPSServerAssembly;

/** Code obtained from codeproject... */

/** http://www.codeproject.com/managedcpp/sendmailmc__.asp **/

bool EmailWrapper::sendEmail( System::String ^ body )
{
	System::String^ from = "baps@unisoftware.co.uk";
	System::String^ subject = System::String::Concat("BAPS Server feedback from: ", CONFIG_GETSTR(CONFIG_SERVERID));
	System::Net::Sockets::TcpClient ^tcpServer = nullptr;
	System::Net::Sockets::NetworkStream  ^ ns = nullptr;
	System::IO::StreamReader   ^ sr = nullptr;
	System::String           ^ data;
	array<unsigned char>^  sendBytes;

	System::String^ server = CONFIG_GETSTR(CONFIG_SMTPSERVER);
	System::String^ to	   = CONFIG_GETSTR(CONFIG_SUPPORTADDRESS);

	try
	{
		tcpServer = gcnew System::Net::Sockets::TcpClient(server,25);
		System::String^ received;
		ns = tcpServer->GetStream();
		sr = gcnew System::IO::StreamReader(tcpServer->GetStream());

		received = sr->ReadLine();

		data  = "HELO server \r\n";    
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);    
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		data = System::String::Concat("MAIL FROM: ",
									"<", from, ">", "\r\n");     
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);    
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		data = System::String::Concat("RCPT TO: ", 
									"<", to, ">", "\r\n");    
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		data = "DATA\r\n";
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		data = System::String::Concat("FROM: ", from, "\r\n",
									"SUBJECT: ", subject, "\r\n", 
									body, "\r\n.\r\n");
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		data = "QUIT \r\n";
		sendBytes = System::Text::Encoding::ASCII->GetBytes(data);
		ns->Write(sendBytes, 0, sendBytes->Length);
		sendBytes = nullptr;
		data = nullptr;
		received = sr->ReadLine();

		ns->Close();
		ns = nullptr;
		sr->Close();
		sr=nullptr;
		tcpServer->Close();
		tcpServer=nullptr;
	}
	catch (System::Exception  ^ e )
	{
		LogManager::write(System::String::Concat("Mailserver rejected connection: \n", e->Message, "Stack Trace:\n",e->StackTrace), LOG_ERROR, LOG_EMAIL);
		if (ns != nullptr)
		{
			ns->Close();
		}
		if (sr != nullptr)
		{
			sr->Close();
		}
		if (tcpServer != nullptr)
		{
			tcpServer->Close();
		}
		sendBytes = nullptr;
		return false;
	}
	return true;
}