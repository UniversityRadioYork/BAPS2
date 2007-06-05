#ifndef __DECODESTRUCTS_H__
#define __DECODESTRUCTS_H__

/** Universal Command constants **/

typedef unsigned int u32int;
typedef unsigned short Command;

/**
 * MASKS
**/
#define BAPSNET_GROUPMASK				0xE000
#define BAPSNET_PLAYBACK_OPMASK			0x1F80
#define BAPSNET_PLAYBACK_MODEMASK		0x40
#define BAPSNET_PLAYBACK_CHANNELMASK	0x3F
#define BAPSNET_PLAYLIST_OPMASK			0x1F80
#define BAPSNET_PLAYLIST_MODEMASK		0x40
#define BAPSNET_PLAYLIST_CHANNELMASK	0x3F
#define BAPSNET_TEXT_OPMASK				0x1C00
#define BAPSNET_DATABASE_OPMASK			0x1F00
#define BAPSNET_DATABASE_MODEMASK		0x80
#define BAPSNET_DATABASE_VALUEMASK		0x7F
#define BAPSNET_CONFIG_OPMASK			0x1F00
#define BAPSNET_CONFIG_MODEMASK			0x80
#define BAPSNET_CONFIG_USEVALUEMASK		0x40
#define BAPSNET_CONFIG_VALUEMASK		0x3F
#define BAPSNET_SYSTEM_OPMASK			0x1F00
#define BAPSNET_SYSTEM_MODEMASK			0x80
#define BAPSNET_SYSTEM_VALUEMASK		0x7F

/**
 * Operation categories
 **/
#define BAPSNET_PLAYBACK	(0<<13)
#define BAPSNET_PLAYLIST	(1<<13)
#define BAPSNET_BTEXT		(2<<13)
#define BAPSNET_DATABASE	(3<<13)
#define BAPSNET_CONFIG		(5<<13)
#define BAPSNET_SYSTEM		(7<<13)

/**
 * Playback
 **/
#define BAPSNET_PLAY			(0<<7)	//C-
#define BAPSNET_STOP			(1<<7)	//C-
#define BAPSNET_PAUSE			(2<<7)	//C-
#define BAPSNET_POSITION		(3<<7)  //SC-[0](set) u32int timeposition
										//C -[1](get) 
#define BAPSNET_VOLUME			(4<<7)  //SC-[0](set) float level
										//C -[1](get)
#define BAPSNET_LOAD			(5<<7)  //SC-[0](set) u32int playlistIndex
										//C -[1](get)
#define BAPSNET_CUEPOSITION		(6<<7)  //SC-[0](set) u32int cueposition
										//C -[1](get)
#define BAPSNET_INTROPOSITION	(7<<7)  //SC-[0](set) u32int introposition
										//C -[1](get)

/**
 * Playlist
 **/
#define BAPSNET_ADDITEM				(0<<7)  //C-u32int itemtype [VOID]
											//					[FILE]		u32int directory number, string filename
											//					[LIBRARY]	u32int searchItemIndex
											//					[TEXT]		string briefdescription, longstring details
#define BAPSNET_DELETEITEM			(1<<7)	//SC-u32int index
#define BAPSNET_MOVEITEMTO			(2<<7)	//C-u32int oldIndex, u32int newIndex
#define BAPSNET_ITEM				(3<<7)	//S-[0](count)	u32int count
											//  [1](data)	u32int index, string name
											//C-[1](get)	u32int index
#define BAPSNET_GETPLAYLIST			(4<<7)	//C-none
#define BAPSNET_RESETPLAYLIST		(5<<7)  //SC-none

/** PLAYLIST ITEMS **/
#define BAPSNET_VOIDITEM			0
#define BAPSNET_FILEITEM			1
#define BAPSNET_LIBRARYITEM			2
#define BAPSNET_TEXTITEM			3

/**
 * Text
 **/
#define BAPSNET_AUTOTXTON		(0<<10)	//UNUSED
#define BAPSNET_AUTOTXTOFF		(1<<10)	//UNUSED
#define BAPSNET_SENDTXTLIST		(2<<10)	//UNSUED
#define BAPSNET_READ			(3<<10)	//UNSUED
#define BAPSNET_UNREAD			(4<<10)	//UNUSED

/**
 * Database
 **/
#define BAPSNET_LIBRARYSEARCH	(0<<8)		//C  string artist, string title			MUSICLIBRESULT | BAPSNET_LIBRARYERROR
#define BAPSNET_LIBRARYORDERING (1<<8)		//C  u32int orderingfield, u32int reverseorder?
#define BAPSNET_LIBRARYRESULT	(2<<8)		//S  [0](count) u32int count
											//   [1](data) u32int index, string description
#define BAPSNET_LIBRARYERROR  	(3<<8)		//S  [-][VALUE-errorCode] string description
#define BAPSNET_GETSHOWS		(4<<8)		//C  [-][VALUE-0]		{current user's shows)		SHOW
											//   [-][VALUE-1]		{system shows}				SHOW
											//   [-][VALUE-2]		string username				SHOW
#define BAPSNET_SHOW			(5<<8)		//S  [0](count)	u32int count
											//   [1](data)	u32int showid, string description
#define BAPSNET_GETLISTINGS		(6<<8)		//C				u32int showid
#define BAPSNET_LISTING			(7<<8)		//S  [0](count) u32int count
											//   [1](data)  u32int listingid, u32int channel, string description
#define BAPSNET_ASSIGNLISTING	(8<<8)		//C  [-][channel] u32int listingid
#define BAPSNET_BAPSDBERROR		(9<<8)		//S  [-][VALUE-errorCode] string description

/**
 * Library orderings
**/
#define BAPSNET_ORDER_BYARTIST			0
#define BAPSNET_ORDER_BYTITLE			1
#define BAPSNET_ORDER_BYDATEADDED		2
#define BAPSNET_ORDER_BYDATERELEASED	3

#define BAPSNET_ORDER_ASCENDING		0
#define BAPSNET_ORDER_DESCENDING	1


/**
 * Config 
**/
#define BAPSNET_GETOPTIONS			(0<<8)	//(no args)			OPTION (count-data)
#define BAPSNET_GETOPTIONCHOICES	(1<<8)	//u32int optionid 	OPTIONCHOICE (count-data)
#define BAPSNET_GETCONFIGSETTINGS	(2<<8)	//(no args)			CONFIGSETTING (count-data)
#define BAPSNET_GETCONFIGSETTING	(3<<8)	//u32int optionid	CONFIGSETTING
#define BAPSNET_GETOPTION			(4<<8)	//string optionName	OPTION CONFIGSETTING  (COUNT-DATA)
#define BAPSNET_SETCONFIGVALUE		(5<<8)	//[x][0/1](uses index)[6bit index]	u32int optionid, u32int type, [string value | u32int value] CONFIGRESULT
#define BAPSNET_GETUSERS			(6<<8)	//(no args)			USER (count-data)
#define BAPSNET_GETPERMISSIONS		(7<<8)	//(no args)			PERMISSION (count-data)
#define BAPSNET_GETUSER				(8<<8)	//string username	USER

#define BAPSNET_ADDUSER				(9<<8)	//string username, string password		USERRESULT
#define BAPSNET_REMOVEUSER			(10<<8)	//string username						USERRESULT
#define BAPSNET_SETPASSWORD			(11<<8)	//string username, string password		USERRESULT
#define BAPSNET_GRANTPERMISSION		(12<<8)	//string username, u32int permission	USERRESULT
#define BAPSNET_REVOKEPERMISSION	(13<<8)	//string username, u32int permission	USERRESULT

#define BAPSNET_OPTION				(16<<8)	// [0](count)		u32int count
											// [1](data)[0/1](uses index)[6bit index]	u32int optionid, string optionDesc, u32int type
#define BAPSNET_OPTIONCHOICE		(17<<8)	// [0](count)		u32int count
											// [1](data)		u32int optionid, u32int optionValueid, string optionValueName
#define BAPSNET_CONFIGSETTING		(18<<8)	// [0](count)		u32int count
											// [1](data)[0/1](uses index)[6bit index]	u32int optionid, u32int type, [u32int value | string value]
#define BAPSNET_USER				(19<<8) // [0](count)		u32int count
											// [1](data)		string username, u32int permission
#define BAPSNET_PERMISSION			(20<<8) // [0](count)		u32int count
											// [1](data)		u32int permission, string name
#define BAPSNET_USERRESULT			(21<<8) // [RESULTVALUE] string resultText
#define BAPSNET_CONFIGRESULT		(22<<8) // [x][0/1](uses index)[6bit index] u32int optionid, u32int result
#define BAPSNET_CONFIGERROR			(23<<8) // [x][x][6bit errorcode]					string description
#define BAPSNET_GETIPRESTRICTIONS	(24<<8) // (no args)		IPRESTRICTION count/data *2(allow deny lists)
#define BAPSNET_IPRESTRICTION		(25<<8) // [0](count) [0/1](allow/deny) u32int count
											// [1](data)  [0/1](allow/deny)	string ipaddress, u32int mask
#define BAPSNET_ALTERIPRESTRICTION	(26<<8) // [0/1](add/remove) [0/1](allow/deny) string ipaddress, u32int mask


/**
 * System
 **/
#define BAPSNET_LISTFILES		(0<<8)	//C-[x][VALUE-dirnumber]
#define BAPSNET_FILENAME		(1<<8)	//S-[0](count)[VALUE-dirnumber] u32int count
										//	[1](data) [VALUE-dirnumber] u32int index, string filename
#define BAPSNET_SENDMESSAGE		(2<<8)	//C-	u32int clientid, string message
#define BAPSNET_AUTOUPDATE		(3<<8)	//C-[VALUE-1](on)
										//  [VALUE-X](off)
#define BAPSNET_END				(4<<8)	//CS-	string reason
#define BAPSNET_SENDLOGMESSAGE	(5<<8)	//S -	string description
#define BAPSNET_SETBINARYMODE	(6<<8)	//C-
#define BAPSNET_SEED			(7<<8)	//S- string encryptionSeed
#define BAPSNET_LOGIN			(8<<8)	//C- string username, string encryptedpass
#define BAPSNET_LOGINRESULT		(9<<8)	//S- [VALUE-resultCode] string resultText
#define BAPSNET_VERSION			(10<<8) //C-
										//S- string date, string time, string version, string author
#define BAPSNET_FEEDBACK		(11<<8) //C- string message
										//S- [VALUE-0/1] success/fail
#define BAPSNET_CLIENTCHANGE	(12<<8)	//S- [VALUE-0] string clientToRemove 
										//   [VALUE-1] string clientToAdd
#define BAPSNET_SCROLLTEXT		(13<<8) //S- [VALUE-0] scroll down
										//   [VALUE-1] scroll up
#define BAPSNET_TEXTSIZE		(14<<8) //S- [VALUE-0] text smaller
										//	 [VALUE-1] text bigger
#endif // __DECODESTRUCTS_H__
