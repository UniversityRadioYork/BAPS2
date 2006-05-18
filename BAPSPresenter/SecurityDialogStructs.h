#pragma once

ref struct PermissionInfo
{
	int permissionCode;
	System::String^ description;
	PermissionInfo(int _permissionCode, System::String^ _description)
		: permissionCode(_permissionCode), description(_description)
	{}
	virtual System::String^ ToString() override
	{
		return description;
	}
};

ref struct UserInfo
{
	System::String^ username;
	int permissions;
	UserInfo(System::String^ _username, int _permissions)
		: username(_username), permissions(_permissions)
	{}
	virtual System::String^ ToString() override
	{
		return username;
	}
};
ref struct IPRestriction
{
	System::String^ ipaddress;
	int mask;
	IPRestriction(System::String^ _ipaddress, int _mask)
		:ipaddress(_ipaddress), mask(_mask)
	{}
	virtual System::String^ ToString() override
	{
		return System::String::Concat(ipaddress, "/", mask.ToString());
	}
};