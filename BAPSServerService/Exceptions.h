#pragma once

/** Currently simply a recognition that a BAPS custom exception has occured **/

public ref class BAPSConfigException : public System::Exception
{
public:
	BAPSConfigException() : System::Exception()
    {}
	BAPSConfigException(System::String^ str) : System::Exception(str)
    {}
};

public ref class BAPSTerminateException : public System::Exception
{
public:
	BAPSTerminateException() : System::Exception()
	{}
	BAPSTerminateException(System::String^ str) : System::Exception(str)
    {}
};

public ref class BAPSProgramErrorException : public System::Exception
{
public:
	BAPSProgramErrorException() : System::Exception()
	{}
	BAPSProgramErrorException(System::String^ str) : System::Exception(str)
    {}
};