#pragma once

#include "ConfigManager.h"
#include "utility.h"

namespace BAPSServerAssembly
{
	#define USERCHECK(x) ((GETPERM(username) & x) == x)

	#define USERCHECKS(x) ((GETPERM(username) & (x | UP_SUPERUSER)) != 0)

	#define PASSKEY(x) md5sum(System::String::Concat(x->ToLower(),"-PSWD"))
	#define SETPASS(x,y) ConfigManager::setConfigValue(PASSKEY(x), y)
	#define GETPASS(x) ConfigManager::getConfigValueString(PASSKEY(x), "")
	#define PERMKEY(x) md5sum(System::String::Concat(x->ToLower(),"-PERM"))
	#define SETPERM(x,y) ConfigManager::setConfigValue(PERMKEY(x), y)
	#define GETPERM(x) ((UserPermission)ConfigManager::getConfigValueInt(PERMKEY(x), 0))


	enum UserPermission
	{
		/** Standard no permission **/
		UP_NONE					= 0x0,
		/** Superuser group **/
		UP_SUPERUSER			= 0x1,
		/** User control	- (add / edit / remove) -- basic security level **/
		UP_USERMANAGEMENT		= 0x2,
		/** Channel control - (alter number of channels / devices) **/
		UP_CHANNELMANAGEMENT	= 0x4,
		/** Stats/Log retrieval - (view usage statistics / preview logs) **/
		UP_STATSACCESS			= 0x8,
		/** Locked out **/
		UP_LOCKEDOUT			= 0x10
	};

	ref struct PermissionLookup
	{
		UserPermission permission;
		System::String^ description;
		PermissionLookup(UserPermission _permission, System::String^ _description)
			: permission(_permission), description(_description)
		{}
	};

	ref struct IPRestriction
	{
		System::String^ ipaddress;
		int mask;
		IPRestriction(System::String^ _ipaddress, int _mask)
			:ipaddress(_ipaddress), mask(_mask)
		{}
	};

	enum LoginResult
	{
		LR_SUCCESS		= 0,
		LR_USERNOTEXIST,
		LR_BADARGS,
		LR_WRONGPASSWORD,
		LR_IPNOTALLOWED,
		LR_IPDENIED,
		LR_LOCKEDOUT,
		LR_SYSTEMERROR,
		LR_LAST
	};

	enum UserResult
	{
		UR_SUCCESS		= 0,
		UR_NOTLOGGEDIN,
		UR_USEREXISTS,
		UR_USERNOTEXIST,
		UR_PASSWORDERROR,
		UR_USERNAMEERROR,
		UR_NOPERMISSION,
		UR_INVALIDPERMISSION,
		UR_LAST
	};

	ref class UserManager
	{
	public:
		/** WORK NEEDED: initialize should create any settings for first run, ie first admin user **/
		static void initUserManager();
		static void closeUserManager();
		System::String^ getSeed(bool recreate);
		System::String^ getSeed();
		LoginResult login(System::String^ _username, System::String^ password, System::Net::IPAddress^ _address);

		UserResult addUser(System::String^ _username, System::String^ password);
		UserResult removeUser(System::String^ _username);
		UserResult setPassword(System::String^ _username, System::String^ password);
		UserResult grantPermission(System::String^ _username, UserPermission permission);
		UserResult revokePermission(System::String^ _username, UserPermission permission);

		/** Get a collection of the usernames **/
		static System::Collections::ArrayList^ getUserList();
		/** Return the allowed ip list as an array of IPRestrictions **/
		static System::Collections::ArrayList^ getAllowedIPList();
		/** Return the denied ip list as an array of IPRestrictions **/
		static System::Collections::ArrayList^ getDeniedIPList();
		/** Add an ipaddress/mask to the allow list **/
		static ConfigError addIPMaskToAllowList(System::String^ ipaddress, int mask);
		/** Add an ipaddress/mask to the deny list **/
		static ConfigError addIPMaskToDenyList(System::String^ ipaddress, int mask);
		/** Remove an ipaddress/mask from the allow list **/
		static ConfigError removeIPMaskFromAllowList(System::String^ ipaddress, int mask);
		/** Remove an ipaddress/mask from the deny list **/
		static ConfigError removeIPMaskFromDenyList(System::String^ ipaddress, int mask);

		UserManager();
		~UserManager();

		inline System::String^ getUsername()
		{
			return username;
		}

		inline bool isSuperuser()
		{
			return USERCHECK(UP_SUPERUSER);
		}
		inline bool isLockedOut()
		{
			return USERCHECK(UP_LOCKEDOUT);
		}
		inline bool isUserManager()
		{
			return USERCHECKS(UP_USERMANAGEMENT);
		}
		inline bool isChannelManager()
		{
			return USERCHECKS(UP_CHANNELMANAGEMENT);
		}
		inline bool isAllowedStats()
		{
			return USERCHECKS(UP_STATSACCESS);
		}

		static array<System::String^>^ loginResultText = {"Success.",
														  "User does not exist.",
														  "Username or password blank.",
														  "Password Incorrect.",
														  "IP address not allowed.",
														  "IP address denied.",
														  "User is locked out.",
														  "Server Program Error."};

		static array<System::String^>^ UserResultText  = {"Success.",
														  "You have not authenticated properly.",
														  "User already exists.",
														  "User does not exist.",
														  "No password specified.",
														  "No username specified.",
														  "Insufficient privilidge.",
														  "Permission code invalid"};
		static array<PermissionLookup^>^ permissions = {gcnew PermissionLookup(UP_NONE, "No Permission"),
														gcnew PermissionLookup(UP_SUPERUSER, "Is Superuser"),
														gcnew PermissionLookup(UP_USERMANAGEMENT, "Is User Manager"),
														gcnew PermissionLookup(UP_CHANNELMANAGEMENT, "Is Channel Manager"),
														gcnew PermissionLookup(UP_STATSACCESS, "Has Stats access"),
														gcnew PermissionLookup(UP_LOCKEDOUT, "Is Locked out")};
	private:
		/** Add a new ipaddress/mask to a list **/
		static ConfigError addIPMaskToList(System::String^ listName, System::String^ ipaddress, int mask);
		/** Remove an ipaddress/mask from a list **/
		static ConfigError removeIPMaskFromList(System::String^ listName, System::String^ ipaddress, int mask);
		/** Convert a dotted notation string to an ip address in bytes **/
		static array<System::Byte>^ convertIPStringToBytes(System::String^ ipaddress);
		/** Get an ip list as an array of IPRestrictions **/
		static System::Collections::ArrayList^ getIPMaskList(array<System::Byte>^ bytes);
		/** Generic form of searching a masked IP list **/
		bool isInIPMaskArray(unsigned int _address, array<System::Byte>^ list, bool defaultResult);
		/** All restriction checks are done separately to the user authentication **/
		LoginResult checkRestrictions(System::Net::IPAddress^ _address);

		/** Check if a username is already in use **/
		static bool userExists(System::String^ _username);
		/** Add a user to the list **/
		static bool addUserToList(System::String^ _username);
		/** Remove a user from the list **/
		static bool removeUserFromList(System::String^ _username);
		/** Count users in list **/
		static int countUsersInList();
		/** Set the list of users back to the registry **/
		static void setUserList(System::Collections::ArrayList^ list);
		/** Check if a permission code is valid **/
		static bool isPermissionValid(UserPermission up);

		/** The user associated with this information **/
		System::String^ username;
		/** The address the user has connected from **/
		System::Net::IPAddress^ address;
		/** The last seed used for encrypted comms **/
		System::String^ seed;

		/** WORK NEEDED: urm do something with this **/
		/** Maximum number of clients that can connect -- excluding admins **/
		static int clientLimit;
	};
};