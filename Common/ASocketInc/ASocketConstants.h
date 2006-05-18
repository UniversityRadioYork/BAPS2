#ifndef _ASCONSTANTS_H_
#define _ASCONSTANTS_H_


// Socket Object - Protocol definitions

#define asPROTOCOL_RAW						1 // The TCP/IP protocol, without any protocol on top of it 
#define asPROTOCOL_TELNET					2 // The Telnet protocol 


// Socket Object - Protocol definitions

#define asCONN_DISCONNECTED					1 // Theres no connection (anymore) 
#define asCONN_LISTENING					2 // Waiting for an incoming client to connect 
#define asCONN_CONNECTED					3 // Connection is established 


// Snmp Object - Type definitions

#define asASN_UNDEFINED						0
#define asASN_INTEGER						2
#define asASN_INTEGER32						2
#define asASN_BITS							3
#define asASN_OCTETSTRING					4
#define asASN_NULL							5
#define asASN_OBJECTIDENTIFIER				6
#define asASN_SEQUENCE						48
#define asASN_SEQUENCEOF					48
#define asASN_IPADDRESS						64
#define asASN_COUNTER32						65
#define asASN_GAUGE32						66
#define asASN_TIMETICKS						67
#define asASN_OPAQUE						68
#define asASN_COUNTER64						70
#define asASN_UNSIGNED32					71

// Snmp Object - Protocol Version definitions

#define asASN_PROTOCOLVERSION_V1		1
#define asASN_PROTOCOLVERSION_V2C		2


// Errors - Generic

#define asERR_SUCCESS						0
#define asERR_INVALIDPARAMETER				1	// Invalid parameter
#define asERR_CREATETHREADFAILED			2	// Unable to create thread
#define asERR_EVALUATIONEXPIRED				3	// Evaluation period has expired
#define asERR_INVALIDLICENSE				4	// Invalid license code


// Errors - Socket related

#define asERR_BUFFEROVERFLOW				10	  // Buffer overflow
#define asERR_NOBYTESINBUFFER				11	  // No more bytes in buffer
#define asERR_LISTENFAILED					12	  // Unable to start listener
#define asERR_NOTLISTENING					13	  // Socket is not listening

#define asERR_WSAEINTR						10004 // A blocking operation was interrupted by a call to WSACancelBlockingCall 
#define asERR_WSAEBADF						10009 // The file handle supplied is not valid 
#define asERR_WSAEACCES						10013 // An attempt was made to access a socket in a way forbidden by its access permissions 
#define asERR_WSAEFAULT						10014 // The system detected an invalid pointer address in attempting to use a pointer argument in a call 
#define asERR_WSAEINVAL						10022 // An invalid argument was supplied 
#define asERR_WSAEMFILE						10024 // Too many open sockets 
#define asERR_WSAEWOULDBLOCK				10035 // A non-blocking socket operation could not be completed immediately 
#define asERR_WSAEINPROGRESS				10036 // A blocking operation is currently executing 
#define asERR_WSAEALREADY					10037 // An operation was attempted on a non-blocking socket that already had an operation in progress 
#define asERR_WSAENOTSOCK					10038 // An operation was attempted on something that is not a socket 
#define asERR_WSAEDESTADDRREQ				10039 // A required address was omitted from an operation on a socket 
#define asERR_WSAEMSGSIZE					10040 // A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself 
#define asERR_WSAEPROTOTYPE					10041 // A protocol was specified in the socket function call that does not support the semantics of the socket type requested 
#define asERR_WSAENOPROTOOPT				10042 // An unknown, invalid, or unsupported option or level was specified in a getsockopt or setsockopt call 
#define asERR_WSAEPROTONOSUPPORT			10043 // The requested protocol has not been configured into the system, or no implementation for it exists 
#define asERR_WSAESOCKTNOSUPPORT			10044 // The support for the specified socket type does not exist in this address family 
#define asERR_WSAEOPNOTSUPP					10045 // The attempted operation is not supported for the type of object referenced 
#define asERR_WSAEPFNOSUPPORT				10046 // The protocol family has not been configured into the system or no implementation for it exists 
#define asERR_WSAEAFNOSUPPORT				10047 // An address incompatible with the requested protocol was used. 
#define asERR_WSAEADDRINUSE					10048 // Only one usage of each socket address (protocol/network address/port) is normally permitted 
#define asERR_WSAEADDRNOTAVAIL				10049 // The requested address is not valid in its context 
#define asERR_WSAENETDOWN					10050 // A socket operation encountered a dead network 
#define asERR_WSAENETUNREACH				10051 // A socket operation was attempted to an unreachable network. 
#define asERR_WSAENETRESET					10052 // The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress 
#define asERR_WSAECONNABORTED				10053 // An established connection was aborted by the software in your host machine 
#define asERR_WSAECONNRESET					10054 // An existing connection was forcibly closed by the remote host 
#define asERR_WSAENOBUFS					10055 // An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full 
#define asERR_WSAEISCONN					10056 // A connect request was made on an already connected socket 
#define asERR_WSAENOTCONN					10057 // A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplie. 
#define asERR_WSAESHUTDOWN					10058 // A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call 
#define asERR_WSAETOOMANYREFS				10059 // Too many references to some kernel object 
#define asERR_WSAETIMEDOUT					10060 // A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond. 
#define asERR_WSAECONNREFUSED				10061 // No connection could be made because the target machine actively refused it 
#define asERR_WSAELOOP						10062 // Cannot translate name 
#define asERR_WSAENAMETOOLONG				10063 // Name component or name was too long 
#define asERR_WSAEHOSTDOWN					10064 // A socket operation failed because the destination host was down 
#define asERR_WSAEHOSTUNREACH				10065 // A socket operation was attempted to an unreachable host 
#define asERR_WSAENOTEMPTY					10066 // Cannot remove a directory that is not empty 
#define asERR_WSAEPROCLIM					10067 // A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously 
#define asERR_WSAEUSERS						10068 // Ran out of quota 
#define asERR_WSAEDQUOT						10069 // Ran out of disk quota 
#define asERR_WSAESTALE						10070 // File handle reference is no longer available 
#define asERR_WSAEREMOTE					10071 // Item is not available locally 
#define asERR_WSASYSNOTREADY				10091 // WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable 
#define asERR_WSAVERNOTSUPPORTED			10092 // The Windows Sockets version requested is not supported 
#define asERR_WSANOTINITIALISED				10093 // Either the application has not called WSAStartup, or WSAStartup failed 
#define asERR_WSAEDISCON					10101 // Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence 
#define asERR_WSAENOMORE					10102 // No more results can be returned by WSALookupServiceNext 
#define asERR_WSAECANCELLED					10103 // A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled 
#define asERR_WSAEINVALIDPROCTABLE			10104 // The procedure call table is invalid 
#define asERR_WSAEINVALIDPROVIDER			10105 // The requested service provider is invalid 
#define asERR_WSAEPROVIDERFAILEDINIT		10106 // The requested service provider could not be loaded or initialized 
#define asERR_WSASYSCALLFAILURE				10107 // A system call that should never fail has failed 
#define asERR_WSASERVICE_NOT_FOUND			10108 // No such service is known. The service cannot be found in the specified name space 
#define asERR_WSATYPE_NOT_FOUND				10109 // The specified class was not found 
#define asERR_WSA_E_NO_MORE					10110 // No more results can be returned by WSALookupServiceNext 
#define asERR_WSA_E_CANCELLED				10111 // A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled 
#define asERR_WSAEREFUSED					10112 // A database query failed because it was actively refused 
#define asERR_WSAHOST_NOT_FOUND				11001 // No such host is known 
#define asERR_WSATRY_AGAIN					11002 // This is usually a temporary error during hostname resolution and means that the local server did not receive a response from an authoritative server 
#define asERR_WSANO_RECOVERY				11003 // A non-recoverable error occurred during a database lookup. 
#define asERR_WSANO_DATA					11004 // The requested name is valid and was found in the database, but it does not have the correct associated data being resolved for 
#define asERR_WSA_QOS_RECEIVERS				11005 // At least one reserve has arrived 
#define asERR_WSA_QOS_SENDERS				11006 // At least one path has arrived 
#define asERR_WSA_QOS_NO_SENDERS			11007 // There are no senders 
#define asERR_WSA_QOS_NO_RECEIVERS			11008 // There are no receivers 
#define asERR_WSA_QOS_REQUEST_CONFIRMED		11009 // Reserve has been confirmed 
#define asERR_WSA_QOS_ADMISSION_FAILURE		11010 // Error due to lack of resources 
#define asERR_WSA_QOS_POLICY_FAILURE		11011 // Rejected for administrative reasons - bad credentials 
#define asERR_WSA_QOS_BAD_STYLE				11012 // Unknown or conflicting style 
#define asERR_WSA_QOS_BAD_OBJECT			11013 // Problem with some part of the filterspec or providerspecific buffer in general 
#define asERR_WSA_QOS_TRAFFIC_CTRL_ERROR	11014 // Problem with some part of the flowspec 
#define asERR_WSA_QOS_GENERIC_ERROR			11015 // General QOS error 
#define asERR_WSA_QOS_ESERVICETYPE			11016 // An invalid or unrecognized service type was found in the flowspec 
#define asERR_WSA_QOS_EFLOWSPEC				11017 // An invalid or inconsistent flowspec was found in the QOS structure 
#define asERR_WSA_QOS_EPROVSPECBUF			11018 // Invalid QOS provider-specific buffer 
#define asERR_WSA_QOS_EFILTERSTYLE			11019 // An invalid QOS filter style was used 
#define asERR_WSA_QOS_EFILTERTYPE			11020 // An invalid QOS filter type was used 
#define asERR_WSA_QOS_EFILTERCOUNT			11021 // An incorrect number of QOS FILTERSPECs were specified in the FLOWDESCRIPTOR 
#define asERR_WSA_QOS_EOBJLENGTH			11022 // An object with an invalid ObjectLength field was specified in the QOS provider-specific buffer 
#define asERR_WSA_QOS_EFLOWCOUNT			11023 // An incorrect number of flow descriptors was specified in the QOS structure 
#define asERR_WSA_QOS_EUNKNOWNPSOBJ			11024 // An unrecognized object was found in the QOS provider-specific buffer 
#define asERR_WSA_QOS_EPOLICYOBJ			11025 // An invalid policy object was found in the QOS provider-specific buffer. 
#define asERR_WSA_QOS_EFLOWDESC				11026 // An invalid QOS flow descriptor was found in the flow descriptor list 
#define asERR_WSA_QOS_EPSFLOWSPEC			11027 // An invalid or inconsistent flowspec was found in the QOS provider-specific buffer 
#define asERR_WSA_QOS_EPSFILTERSPEC			11028 // An invalid FILTERSPEC was found in the QOS provider-specific buffer 
#define asERR_WSA_QOS_ESDMODEOBJ			11029 // An invalid shape discard mode object was found in the QOS provider-specific buffer 
#define asERR_WSA_QOS_ESHAPERATEOBJ			11030 // An invalid shaping rate object was found in the QOS provider-specific buffer 
#define asERR_WSA_QOS_RESERVED_PETYPE		11031 // A reserved policy element was found in the QOS provider-specific buffer 


// Errors - SNMP related

#define asERR_LIBSNMPAPINOTFOUND			100	// SNMPAPI.DLL could not be loaded because DLL was not found
#define asERR_LIBMGMTAPINOTFOUND			101 // MGMTAPI.DLL could not be loaded because DLL was not found 
#define asERR_LIBSNMPAPIBINDINGFAILURE		102 // One or more exported functions missing in SNMPAPI.DLL
#define asERR_LIBMGMTAPIBINDINGFAILURE		103 // One or more exported functions missing in MGMTAPI.DLL
#define asERR_LIBWSNMP2APINOTFOUND			104	// WSNMP32.DLL could not be loaded because DLL was not found
#define asERR_LIBWSNMP2APIBINDINGFAILURE	105	// One or more exported functions missing in WSNMP32.DLL

#define asERR_SNMP_LIBRARIESNOTLOADED		110	// SNMP Libraries not loaded; operation not allowed
#define asERR_SNMP_WINSNMPINITFAILED		111	// Unable to intialize WinSNMP
#define asERR_SNMP_LIBNOTINITIALIZED		112	// Library not initialized. 
#define asERR_SNMP_OPENSESSIONFAILED		113	// Unable to open SNMP session
#define asERR_SNMP_SESSIONALREADYOPENED		114	// Session already opened
#define asERR_SNMP_SESSIONNOTOPENED			115	// Open a session first
#define asERR_SNMP_MEMALLOCAFAILED			116	// Memory allocation failed
#define asERR_SNMP_INVALIDPARAM				117	// Invalid parameter
#define asERR_SNMP_REQUESTTIMEDOUT			118	// Request operation timed out
#define asERR_SNMP_REQUESTFAILED			119	// Request operation failed
#define asERR_SNMP_INVALIDHOST				120	// Invalid hostname
#define asERR_SNMP_INVALIDPORT				121	// Unable to set port other than 161
#define asERR_SNMP_TYPENOTSUPPORTED			122	// OID type not supported by ActiveSocket
#define asERR_SNMP_ADDTRAPFAILED			140	// Unable to add trap
#define asERR_SNMP_NOMOREOIDS				141	// No more OID's in SNMP tree
#define asERR_SNMP_NOTRAPSTOSEND			142	// No traps to send. Use the Add function to add traps before calling Send

#define asERR_SNMP_NOMORETRAPSINQUEUE		150	// No traps in receive queue
#define asERR_SNMP_INVALIDOPERATION			151	// Invalid call. Call GetFirstTrap before calling GetNextTrap


// Errors - NTP related

#define asERR_NTP_INVALIDHOSTNAME			200 // Invalid NTP host name
#define asERR_NTP_CREATESOCKETFAILED		201 // Create socket failed
#define asERR_NTP_CONNECTFAILEDFAILED		202 // Unable to connect to NTP server
#define asERR_NTP_TIMEREQUESTFAILED			203 // Connection to NTP server established, but request failed
#define asERR_NTP_REQUESTFAILED				204 // Request failed
#define asERR_NTP_NORESPONSERECEIVED		205 // No response received


// Errors - ICMP Related

#define asERR_ICMP_CREATESOCKETFAILED		300	// Creation of socket failed
#define asERR_ICMP_INVALIDHOSTNAME			301	// Invalid host name
#define asERR_ICMP_TIMEOUT					302	// Timeout
#define asERR_ICMP_HOSTUNREACHABLE			303	// Destination host unreachable
#define asERR_ICMP_NETUNREACHABLE			304	// Destination net unreachable
#define asERR_ICMP_INTERNALAPIERROR			307	// Internal API error
#define asERR_ICMP_BADOPTION				308	// Bad option
#define asERR_ICMP_HWFAILED					309	// Hardware error
#define asERR_ICMP_PACKETTOOBIG				310	// Packet too big
#define asERR_ICMP_BADREQUEST				311	// Bad request
#define asERR_ICMP_BADROUTE					312	// Bad route
#define asERR_ICMP_TTLEXPIRED				313	// TTL expired
#define asERR_ICMP_SOURCEQUENCH				314	// Source Quench
#define asERR_ICMP_BADDESTINATION			315	// Bad Destination


// Errors - HTTP Related

#define asERR_HTTP_LOADWINHTTPFAILED		400	// Unable to load WinHTTP libraries
#define asERR_HTTP_CREATESESSIONFAILED		401	// Create WinHTTP session failed
#define asERR_HTTP_SESSIONNOTOPENED			402	// Open a session first
#define asERR_HTTP_ALREADYCONNECTED			403	// Connection already established
#define asERR_HTTP_OPENCONNECTIONFAILED		404	// Unable to establish a connection to remote web server
#define asERR_HTTP_SETPROXYCREDENTIALSFAILED		405	// Unable to logon to proxy
#define asERR_HTTP_SENDREQUESTFAILED		406	// Unable to send the request to the remote web server
#define asERR_HTTP_NORESPONSERECEIVED		407	// No response received from remote server
#define asERR_HTTP_QUERYHEADERSFAILED		408	// Unable to query headers
#define asERR_HTTP_QUERYAUTHSCHEMESFAILED	409	// Unable to query authentication schemes
#define asERR_HTTP_OPENCONNECTIONTIMEOUT	410	// Unable to establish connection, operation timed out
#define asERR_HTTP_CONNECTIONNOTOPENED		411	// Establish a connection first
#define asERR_HTTP_SETCREDENTIALSFAILED		412	// Unable to logon to web site
#define asERR_HTTP_QUERYDATASIZEFAILED		413	// Unable to read data, query for data size failed
#define asERR_HTTP_DATAALLOCATIONFAILED		414	// Unable to read data, internal memory allocation failed
#define asERR_HTTP_READFAILED				415	// Unable to read data, read operation failed


// Errors - WOL Related

#define asERR_WOL_INVALIDMACADDRESS			500	// Invalid MAC address


// Errors - DNS Related

#define asERR_DNS_GENERICERROR				600	// Generic error	
#define asERR_DNS_LOADDNSFAILED				601	// Unable to load DNS library
#define asERR_DNS_LIBNOTINITIALIZED			602	// Library not initialized
#define asERR_DNS_DNSSERVERRESOLVEFAILED    604	// Unable to resolve DNS host to IP address		
#define asERR_DNS_DNSCONNECTFAILED          610	// Unable to connect to DNS server
#define asERR_DNS_HOSTNOTFOUND              611	// DNS server was queried successfully, but specified entry was not found





#endif // _ASCONSTANTS_H_
