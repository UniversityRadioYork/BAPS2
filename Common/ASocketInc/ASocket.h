/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 17 08:36:56 2004
 */
/* Compiler settings for G:\ActiveSocket\VisualC\ASocket.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ASocket_h__
#define __ASocket_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISnmp_FWD_DEFINED__
#define __ISnmp_FWD_DEFINED__
typedef interface ISnmp ISnmp;
#endif 	/* __ISnmp_FWD_DEFINED__ */


#ifndef __ISocket_FWD_DEFINED__
#define __ISocket_FWD_DEFINED__
typedef interface ISocket ISocket;
#endif 	/* __ISocket_FWD_DEFINED__ */


#ifndef __IRSh_FWD_DEFINED__
#define __IRSh_FWD_DEFINED__
typedef interface IRSh IRSh;
#endif 	/* __IRSh_FWD_DEFINED__ */


#ifndef __INtp_FWD_DEFINED__
#define __INtp_FWD_DEFINED__
typedef interface INtp INtp;
#endif 	/* __INtp_FWD_DEFINED__ */


#ifndef __IWOL_FWD_DEFINED__
#define __IWOL_FWD_DEFINED__
typedef interface IWOL IWOL;
#endif 	/* __IWOL_FWD_DEFINED__ */


#ifndef __IIcmp_FWD_DEFINED__
#define __IIcmp_FWD_DEFINED__
typedef interface IIcmp IIcmp;
#endif 	/* __IIcmp_FWD_DEFINED__ */


#ifndef __IHttp_FWD_DEFINED__
#define __IHttp_FWD_DEFINED__
typedef interface IHttp IHttp;
#endif 	/* __IHttp_FWD_DEFINED__ */


#ifndef __ISnmpTrapIn_FWD_DEFINED__
#define __ISnmpTrapIn_FWD_DEFINED__
typedef interface ISnmpTrapIn ISnmpTrapIn;
#endif 	/* __ISnmpTrapIn_FWD_DEFINED__ */


#ifndef __ISnmpTrapOut_FWD_DEFINED__
#define __ISnmpTrapOut_FWD_DEFINED__
typedef interface ISnmpTrapOut ISnmpTrapOut;
#endif 	/* __ISnmpTrapOut_FWD_DEFINED__ */


#ifndef __IDns_FWD_DEFINED__
#define __IDns_FWD_DEFINED__
typedef interface IDns IDns;
#endif 	/* __IDns_FWD_DEFINED__ */


#ifndef __Snmp_FWD_DEFINED__
#define __Snmp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Snmp Snmp;
#else
typedef struct Snmp Snmp;
#endif /* __cplusplus */

#endif 	/* __Snmp_FWD_DEFINED__ */


#ifndef __Socket_FWD_DEFINED__
#define __Socket_FWD_DEFINED__

#ifdef __cplusplus
typedef class Socket Socket;
#else
typedef struct Socket Socket;
#endif /* __cplusplus */

#endif 	/* __Socket_FWD_DEFINED__ */


#ifndef __RSh_FWD_DEFINED__
#define __RSh_FWD_DEFINED__

#ifdef __cplusplus
typedef class RSh RSh;
#else
typedef struct RSh RSh;
#endif /* __cplusplus */

#endif 	/* __RSh_FWD_DEFINED__ */


#ifndef __Ntp_FWD_DEFINED__
#define __Ntp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ntp Ntp;
#else
typedef struct Ntp Ntp;
#endif /* __cplusplus */

#endif 	/* __Ntp_FWD_DEFINED__ */


#ifndef __WOL_FWD_DEFINED__
#define __WOL_FWD_DEFINED__

#ifdef __cplusplus
typedef class WOL WOL;
#else
typedef struct WOL WOL;
#endif /* __cplusplus */

#endif 	/* __WOL_FWD_DEFINED__ */


#ifndef __Icmp_FWD_DEFINED__
#define __Icmp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Icmp Icmp;
#else
typedef struct Icmp Icmp;
#endif /* __cplusplus */

#endif 	/* __Icmp_FWD_DEFINED__ */


#ifndef __Http_FWD_DEFINED__
#define __Http_FWD_DEFINED__

#ifdef __cplusplus
typedef class Http Http;
#else
typedef struct Http Http;
#endif /* __cplusplus */

#endif 	/* __Http_FWD_DEFINED__ */


#ifndef __SnmpTrapIn_FWD_DEFINED__
#define __SnmpTrapIn_FWD_DEFINED__

#ifdef __cplusplus
typedef class SnmpTrapIn SnmpTrapIn;
#else
typedef struct SnmpTrapIn SnmpTrapIn;
#endif /* __cplusplus */

#endif 	/* __SnmpTrapIn_FWD_DEFINED__ */


#ifndef __SnmpTrapOut_FWD_DEFINED__
#define __SnmpTrapOut_FWD_DEFINED__

#ifdef __cplusplus
typedef class SnmpTrapOut SnmpTrapOut;
#else
typedef struct SnmpTrapOut SnmpTrapOut;
#endif /* __cplusplus */

#endif 	/* __SnmpTrapOut_FWD_DEFINED__ */


#ifndef __Dns_FWD_DEFINED__
#define __Dns_FWD_DEFINED__

#ifdef __cplusplus
typedef class Dns Dns;
#else
typedef struct Dns Dns;
#endif /* __cplusplus */

#endif 	/* __Dns_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISnmp_INTERFACE_DEFINED__
#define __ISnmp_INTERFACE_DEFINED__

/* interface ISnmp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISnmp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BB426D5B-EB8B-47B8-B42A-6B85DDC30AFF")
    ISnmp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolVersion( 
            /* [in] */ long ProtocolVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout( 
            /* [in] */ long Milliseconds) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Port( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Port( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BSTR Agent,
            /* [in] */ BSTR Community) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ BSTR OID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNext( 
            /* [in] */ BSTR OID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetType( 
            /* [retval][out] */ long __RPC_FAR *plType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ BSTR OID,
            /* [in] */ BSTR Value,
            /* [in] */ LONG Type) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0015) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISnmpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISnmp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISnmp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISnmp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtocolVersion )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProtocolVersion )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ long ProtocolVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Timeout )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Timeout )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ long Milliseconds);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Port )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Port )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            ISnmp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ BSTR Agent,
            /* [in] */ BSTR Community);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            ISnmp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ BSTR OID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNext )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ BSTR OID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            ISnmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            ISnmp __RPC_FAR * This,
            /* [in] */ BSTR OID,
            /* [in] */ BSTR Value,
            /* [in] */ LONG Type);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            ISnmp __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0015);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ISnmp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            ISnmp __RPC_FAR * This);
        
        END_INTERFACE
    } ISnmpVtbl;

    interface ISnmp
    {
        CONST_VTBL struct ISnmpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISnmp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISnmp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISnmp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISnmp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISnmp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISnmp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISnmp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISnmp_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ISnmp_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define ISnmp_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define ISnmp_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define ISnmp_get_ProtocolVersion(This,pVal)	\
    (This)->lpVtbl -> get_ProtocolVersion(This,pVal)

#define ISnmp_put_ProtocolVersion(This,ProtocolVersion)	\
    (This)->lpVtbl -> put_ProtocolVersion(This,ProtocolVersion)

#define ISnmp_get_Timeout(This,pVal)	\
    (This)->lpVtbl -> get_Timeout(This,pVal)

#define ISnmp_put_Timeout(This,Milliseconds)	\
    (This)->lpVtbl -> put_Timeout(This,Milliseconds)

#define ISnmp_get_Port(This,pVal)	\
    (This)->lpVtbl -> get_Port(This,pVal)

#define ISnmp_put_Port(This,newVal)	\
    (This)->lpVtbl -> put_Port(This,newVal)

#define ISnmp_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define ISnmp_Open(This,Agent,Community)	\
    (This)->lpVtbl -> Open(This,Agent,Community)

#define ISnmp_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define ISnmp_Get(This,OID,pbstrRetVal)	\
    (This)->lpVtbl -> Get(This,OID,pbstrRetVal)

#define ISnmp_GetNext(This,OID,pbstrRetVal)	\
    (This)->lpVtbl -> GetNext(This,OID,pbstrRetVal)

#define ISnmp_GetType(This,plType)	\
    (This)->lpVtbl -> GetType(This,plType)

#define ISnmp_Set(This,OID,Value,Type)	\
    (This)->lpVtbl -> Set(This,OID,Value,Type)

#define ISnmp_GetErrorDescription(This,ErrorCode,__MIDL_0015)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0015)

#define ISnmp_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ISnmp_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_Version_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_ExpirationDate_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_LastError_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmp_put_Reserved_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISnmp_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_ProtocolVersion_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmp_put_ProtocolVersion_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ long ProtocolVersion);


void __RPC_STUB ISnmp_put_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_Timeout_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmp_put_Timeout_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ long Milliseconds);


void __RPC_STUB ISnmp_put_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmp_get_Port_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ISnmp_get_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmp_put_Port_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ISnmp_put_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Clear_Proxy( 
    ISnmp __RPC_FAR * This);


void __RPC_STUB ISnmp_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Open_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ BSTR Agent,
    /* [in] */ BSTR Community);


void __RPC_STUB ISnmp_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Close_Proxy( 
    ISnmp __RPC_FAR * This);


void __RPC_STUB ISnmp_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Get_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ BSTR OID,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ISnmp_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_GetNext_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ BSTR OID,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ISnmp_GetNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_GetType_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plType);


void __RPC_STUB ISnmp_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Set_Proxy( 
    ISnmp __RPC_FAR * This,
    /* [in] */ BSTR OID,
    /* [in] */ BSTR Value,
    /* [in] */ LONG Type);


void __RPC_STUB ISnmp_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_GetErrorDescription_Proxy( 
    ISnmp __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0015);


void __RPC_STUB ISnmp_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Initialize_Proxy( 
    ISnmp __RPC_FAR * This);


void __RPC_STUB ISnmp_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmp_Shutdown_Proxy( 
    ISnmp __RPC_FAR * This);


void __RPC_STUB ISnmp_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISnmp_INTERFACE_DEFINED__ */


#ifndef __ISocket_INTERFACE_DEFINED__
#define __ISocket_INTERFACE_DEFINED__

/* interface ISocket */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISocket;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7950B95E-256A-4E5B-A166-D3FCAE11ADBE")
    ISocket : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConnectionState( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            BSTR HostName,
            long PortNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartListening( 
            long PortNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopListening( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HasData( 
            /* [retval][out] */ BOOL __RPC_FAR *__MIDL_0016) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReceiveString( 
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0017) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sleep( 
            long MilliSecs) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendString( 
            BSTR DataString,
            BOOL Linefeed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Activate( 
            BSTR RegistrationCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Protocol( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PutByte( 
            short Byte) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetByte( 
            /* [retval][out] */ short __RPC_FAR *__MIDL_0018) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SendBytes( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReceiveBytes( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Build( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0019) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISocketVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISocket __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISocket __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISocket __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISocket __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISocket __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISocket __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISocket __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConnectionState )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            ISocket __RPC_FAR * This,
            BSTR HostName,
            long PortNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            ISocket __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartListening )( 
            ISocket __RPC_FAR * This,
            long PortNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopListening )( 
            ISocket __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HasData )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *__MIDL_0016);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveString )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0017);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sleep )( 
            ISocket __RPC_FAR * This,
            long MilliSecs);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendString )( 
            ISocket __RPC_FAR * This,
            BSTR DataString,
            BOOL Linefeed);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            ISocket __RPC_FAR * This,
            BSTR RegistrationCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Protocol )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Protocol )( 
            ISocket __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            ISocket __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutByte )( 
            ISocket __RPC_FAR * This,
            short Byte);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetByte )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *__MIDL_0018);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendBytes )( 
            ISocket __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveBytes )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Build )( 
            ISocket __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            ISocket __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0019);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            ISocket __RPC_FAR * This);
        
        END_INTERFACE
    } ISocketVtbl;

    interface ISocket
    {
        CONST_VTBL struct ISocketVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISocket_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISocket_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISocket_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISocket_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISocket_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISocket_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISocket_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISocket_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ISocket_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define ISocket_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define ISocket_get_ConnectionState(This,pVal)	\
    (This)->lpVtbl -> get_ConnectionState(This,pVal)

#define ISocket_Connect(This,HostName,PortNumber)	\
    (This)->lpVtbl -> Connect(This,HostName,PortNumber)

#define ISocket_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define ISocket_StartListening(This,PortNumber)	\
    (This)->lpVtbl -> StartListening(This,PortNumber)

#define ISocket_StopListening(This)	\
    (This)->lpVtbl -> StopListening(This)

#define ISocket_HasData(This,__MIDL_0016)	\
    (This)->lpVtbl -> HasData(This,__MIDL_0016)

#define ISocket_ReceiveString(This,__MIDL_0017)	\
    (This)->lpVtbl -> ReceiveString(This,__MIDL_0017)

#define ISocket_Sleep(This,MilliSecs)	\
    (This)->lpVtbl -> Sleep(This,MilliSecs)

#define ISocket_SendString(This,DataString,Linefeed)	\
    (This)->lpVtbl -> SendString(This,DataString,Linefeed)

#define ISocket_Activate(This,RegistrationCode)	\
    (This)->lpVtbl -> Activate(This,RegistrationCode)

#define ISocket_get_Protocol(This,pVal)	\
    (This)->lpVtbl -> get_Protocol(This,pVal)

#define ISocket_put_Protocol(This,newVal)	\
    (This)->lpVtbl -> put_Protocol(This,newVal)

#define ISocket_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define ISocket_PutByte(This,Byte)	\
    (This)->lpVtbl -> PutByte(This,Byte)

#define ISocket_GetByte(This,__MIDL_0018)	\
    (This)->lpVtbl -> GetByte(This,__MIDL_0018)

#define ISocket_SendBytes(This)	\
    (This)->lpVtbl -> SendBytes(This)

#define ISocket_ReceiveBytes(This,pVal)	\
    (This)->lpVtbl -> ReceiveBytes(This,pVal)

#define ISocket_get_Build(This,pVal)	\
    (This)->lpVtbl -> get_Build(This,pVal)

#define ISocket_GetErrorDescription(This,ErrorCode,__MIDL_0019)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0019)

#define ISocket_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_Version_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_ExpirationDate_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_LastError_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_ConnectionState_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_ConnectionState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_Connect_Proxy( 
    ISocket __RPC_FAR * This,
    BSTR HostName,
    long PortNumber);


void __RPC_STUB ISocket_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_Disconnect_Proxy( 
    ISocket __RPC_FAR * This);


void __RPC_STUB ISocket_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_StartListening_Proxy( 
    ISocket __RPC_FAR * This,
    long PortNumber);


void __RPC_STUB ISocket_StartListening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_StopListening_Proxy( 
    ISocket __RPC_FAR * This);


void __RPC_STUB ISocket_StopListening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_HasData_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *__MIDL_0016);


void __RPC_STUB ISocket_HasData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_ReceiveString_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0017);


void __RPC_STUB ISocket_ReceiveString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_Sleep_Proxy( 
    ISocket __RPC_FAR * This,
    long MilliSecs);


void __RPC_STUB ISocket_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_SendString_Proxy( 
    ISocket __RPC_FAR * This,
    BSTR DataString,
    BOOL Linefeed);


void __RPC_STUB ISocket_SendString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_Activate_Proxy( 
    ISocket __RPC_FAR * This,
    BSTR RegistrationCode);


void __RPC_STUB ISocket_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_Protocol_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISocket_put_Protocol_Proxy( 
    ISocket __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISocket_put_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISocket_put_Reserved_Proxy( 
    ISocket __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISocket_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_PutByte_Proxy( 
    ISocket __RPC_FAR * This,
    short Byte);


void __RPC_STUB ISocket_PutByte_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_GetByte_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *__MIDL_0018);


void __RPC_STUB ISocket_GetByte_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_SendBytes_Proxy( 
    ISocket __RPC_FAR * This);


void __RPC_STUB ISocket_SendBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_ReceiveBytes_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISocket_ReceiveBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISocket_get_Build_Proxy( 
    ISocket __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISocket_get_Build_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_GetErrorDescription_Proxy( 
    ISocket __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0019);


void __RPC_STUB ISocket_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISocket_Clear_Proxy( 
    ISocket __RPC_FAR * This);


void __RPC_STUB ISocket_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISocket_INTERFACE_DEFINED__ */


#ifndef __IRSh_INTERFACE_DEFINED__
#define __IRSh_INTERFACE_DEFINED__

/* interface IRSh */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IRSh;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("844E4159-8D81-466B-9D13-7CE8098D4A6B")
    IRSh : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Host( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Host( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Command( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Command( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StdOut( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StdErr( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScriptTimeOut( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScriptTimeOut( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0020) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRShVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRSh __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRSh __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRSh __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRSh __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRSh __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRSh __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRSh __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IRSh __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Host )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Host )( 
            IRSh __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Command )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Command )( 
            IRSh __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IRSh __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StdOut )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StdErr )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            IRSh __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScriptTimeOut )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScriptTimeOut )( 
            IRSh __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IRSh __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            IRSh __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IRSh __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0020);
        
        END_INTERFACE
    } IRShVtbl;

    interface IRSh
    {
        CONST_VTBL struct IRShVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRSh_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRSh_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRSh_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRSh_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRSh_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRSh_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRSh_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRSh_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IRSh_get_Host(This,pVal)	\
    (This)->lpVtbl -> get_Host(This,pVal)

#define IRSh_put_Host(This,newVal)	\
    (This)->lpVtbl -> put_Host(This,newVal)

#define IRSh_get_Command(This,pVal)	\
    (This)->lpVtbl -> get_Command(This,pVal)

#define IRSh_put_Command(This,newVal)	\
    (This)->lpVtbl -> put_Command(This,newVal)

#define IRSh_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IRSh_get_StdOut(This,pVal)	\
    (This)->lpVtbl -> get_StdOut(This,pVal)

#define IRSh_get_StdErr(This,pVal)	\
    (This)->lpVtbl -> get_StdErr(This,pVal)

#define IRSh_get_UserName(This,pVal)	\
    (This)->lpVtbl -> get_UserName(This,pVal)

#define IRSh_put_UserName(This,newVal)	\
    (This)->lpVtbl -> put_UserName(This,newVal)

#define IRSh_get_ScriptTimeOut(This,pVal)	\
    (This)->lpVtbl -> get_ScriptTimeOut(This,pVal)

#define IRSh_put_ScriptTimeOut(This,newVal)	\
    (This)->lpVtbl -> put_ScriptTimeOut(This,newVal)

#define IRSh_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define IRSh_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define IRSh_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IRSh_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define IRSh_GetErrorDescription(This,ErrorCode,__MIDL_0020)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0020)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRSh_Clear_Proxy( 
    IRSh __RPC_FAR * This);


void __RPC_STUB IRSh_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_Host_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_Host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRSh_put_Host_Proxy( 
    IRSh __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRSh_put_Host_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_Command_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_Command_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRSh_put_Command_Proxy( 
    IRSh __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRSh_put_Command_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRSh_Run_Proxy( 
    IRSh __RPC_FAR * This);


void __RPC_STUB IRSh_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_StdOut_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_StdOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_StdErr_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_StdErr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_UserName_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRSh_put_UserName_Proxy( 
    IRSh __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IRSh_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_ScriptTimeOut_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_ScriptTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRSh_put_ScriptTimeOut_Proxy( 
    IRSh __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IRSh_put_ScriptTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_LastError_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_ExpirationDate_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IRSh_get_Version_Proxy( 
    IRSh __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IRSh_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IRSh_put_Reserved_Proxy( 
    IRSh __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IRSh_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRSh_GetErrorDescription_Proxy( 
    IRSh __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0020);


void __RPC_STUB IRSh_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRSh_INTERFACE_DEFINED__ */


#ifndef __INtp_INTERFACE_DEFINED__
#define __INtp_INTERFACE_DEFINED__

/* interface INtp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_INtp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC932613-BE5F-43B3-9955-A40E1A8D736C")
    INtp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTime( 
            /* [in] */ BSTR TimeServer) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalOffsetSeconds( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Year( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Month( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Day( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Hour( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Minute( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Second( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0021) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct INtpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            INtp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            INtp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            INtp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            INtp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            INtp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            INtp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            INtp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            INtp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            INtp __RPC_FAR * This,
            /* [in] */ BSTR TimeServer);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalOffsetSeconds )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Year )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Month )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Day )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hour )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Minute )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Second )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            INtp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            INtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            INtp __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0021);
        
        END_INTERFACE
    } INtpVtbl;

    interface INtp
    {
        CONST_VTBL struct INtpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INtp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define INtp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define INtp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define INtp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define INtp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define INtp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define INtp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define INtp_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define INtp_GetTime(This,TimeServer)	\
    (This)->lpVtbl -> GetTime(This,TimeServer)

#define INtp_get_LocalOffsetSeconds(This,pVal)	\
    (This)->lpVtbl -> get_LocalOffsetSeconds(This,pVal)

#define INtp_get_Year(This,pVal)	\
    (This)->lpVtbl -> get_Year(This,pVal)

#define INtp_get_Month(This,pVal)	\
    (This)->lpVtbl -> get_Month(This,pVal)

#define INtp_get_Day(This,pVal)	\
    (This)->lpVtbl -> get_Day(This,pVal)

#define INtp_get_Hour(This,pVal)	\
    (This)->lpVtbl -> get_Hour(This,pVal)

#define INtp_get_Minute(This,pVal)	\
    (This)->lpVtbl -> get_Minute(This,pVal)

#define INtp_get_Second(This,pVal)	\
    (This)->lpVtbl -> get_Second(This,pVal)

#define INtp_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define INtp_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define INtp_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define INtp_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define INtp_GetErrorDescription(This,ErrorCode,__MIDL_0021)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0021)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INtp_Clear_Proxy( 
    INtp __RPC_FAR * This);


void __RPC_STUB INtp_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INtp_GetTime_Proxy( 
    INtp __RPC_FAR * This,
    /* [in] */ BSTR TimeServer);


void __RPC_STUB INtp_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_LocalOffsetSeconds_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_LocalOffsetSeconds_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Year_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Year_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Month_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Month_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Day_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Day_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Hour_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Hour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Minute_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Minute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Second_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Second_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_LastError_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB INtp_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE INtp_put_Reserved_Proxy( 
    INtp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB INtp_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_Version_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INtp_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE INtp_get_ExpirationDate_Proxy( 
    INtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB INtp_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE INtp_GetErrorDescription_Proxy( 
    INtp __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0021);


void __RPC_STUB INtp_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __INtp_INTERFACE_DEFINED__ */


#ifndef __IWOL_INTERFACE_DEFINED__
#define __IWOL_INTERFACE_DEFINED__

/* interface IWOL */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IWOL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18AD1230-A4C9-4A48-98B3-B3C669D28001")
    IWOL : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WakeUp( 
            BSTR MacAddress) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0022) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWOLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWOL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWOL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWOL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWOL __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWOL __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWOL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWOL __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IWOL __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            IWOL __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            IWOL __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WakeUp )( 
            IWOL __RPC_FAR * This,
            BSTR MacAddress);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IWOL __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0022);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IWOL __RPC_FAR * This);
        
        END_INTERFACE
    } IWOLVtbl;

    interface IWOL
    {
        CONST_VTBL struct IWOLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWOL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWOL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWOL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWOL_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWOL_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWOL_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWOL_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWOL_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IWOL_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define IWOL_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define IWOL_WakeUp(This,MacAddress)	\
    (This)->lpVtbl -> WakeUp(This,MacAddress)

#define IWOL_GetErrorDescription(This,ErrorCode,__MIDL_0022)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0022)

#define IWOL_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWOL_get_Version_Proxy( 
    IWOL __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWOL_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWOL_get_ExpirationDate_Proxy( 
    IWOL __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IWOL_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWOL_get_LastError_Proxy( 
    IWOL __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IWOL_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWOL_WakeUp_Proxy( 
    IWOL __RPC_FAR * This,
    BSTR MacAddress);


void __RPC_STUB IWOL_WakeUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWOL_GetErrorDescription_Proxy( 
    IWOL __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0022);


void __RPC_STUB IWOL_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWOL_Clear_Proxy( 
    IWOL __RPC_FAR * This);


void __RPC_STUB IWOL_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWOL_INTERFACE_DEFINED__ */


#ifndef __IIcmp_INTERFACE_DEFINED__
#define __IIcmp_INTERFACE_DEFINED__

/* interface IIcmp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IIcmp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A92A390F-E285-4A8E-ACE1-C9981CE951E9")
    IIcmp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ping( 
            /* [in] */ BSTR DestinationHost,
            /* [in] */ long TimeoutMsecs) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastDuration( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0023) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ttl( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Ttl( 
            /* [in] */ long Ttl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastTtl( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sleep( 
            long MilliSecs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIcmpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIcmp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIcmp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IIcmp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Ping )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ BSTR DestinationHost,
            /* [in] */ long TimeoutMsecs);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastDuration )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ long Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IIcmp __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0023);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IIcmp __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ttl )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Ttl )( 
            IIcmp __RPC_FAR * This,
            /* [in] */ long Ttl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastTtl )( 
            IIcmp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sleep )( 
            IIcmp __RPC_FAR * This,
            long MilliSecs);
        
        END_INTERFACE
    } IIcmpVtbl;

    interface IIcmp
    {
        CONST_VTBL struct IIcmpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIcmp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIcmp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIcmp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIcmp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IIcmp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IIcmp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IIcmp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IIcmp_Ping(This,DestinationHost,TimeoutMsecs)	\
    (This)->lpVtbl -> Ping(This,DestinationHost,TimeoutMsecs)

#define IIcmp_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define IIcmp_get_LastDuration(This,pVal)	\
    (This)->lpVtbl -> get_LastDuration(This,pVal)

#define IIcmp_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IIcmp_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define IIcmp_put_Reserved(This,Value)	\
    (This)->lpVtbl -> put_Reserved(This,Value)

#define IIcmp_GetErrorDescription(This,ErrorCode,__MIDL_0023)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0023)

#define IIcmp_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IIcmp_get_Ttl(This,pVal)	\
    (This)->lpVtbl -> get_Ttl(This,pVal)

#define IIcmp_put_Ttl(This,Ttl)	\
    (This)->lpVtbl -> put_Ttl(This,Ttl)

#define IIcmp_get_LastTtl(This,pVal)	\
    (This)->lpVtbl -> get_LastTtl(This,pVal)

#define IIcmp_Sleep(This,MilliSecs)	\
    (This)->lpVtbl -> Sleep(This,MilliSecs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIcmp_Ping_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [in] */ BSTR DestinationHost,
    /* [in] */ long TimeoutMsecs);


void __RPC_STUB IIcmp_Ping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_LastError_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_LastDuration_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_LastDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_Version_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_ExpirationDate_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIcmp_put_Reserved_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [in] */ long Value);


void __RPC_STUB IIcmp_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIcmp_GetErrorDescription_Proxy( 
    IIcmp __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0023);


void __RPC_STUB IIcmp_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIcmp_Clear_Proxy( 
    IIcmp __RPC_FAR * This);


void __RPC_STUB IIcmp_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_Ttl_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_Ttl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IIcmp_put_Ttl_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [in] */ long Ttl);


void __RPC_STUB IIcmp_put_Ttl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IIcmp_get_LastTtl_Proxy( 
    IIcmp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IIcmp_get_LastTtl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IIcmp_Sleep_Proxy( 
    IIcmp __RPC_FAR * This,
    long MilliSecs);


void __RPC_STUB IIcmp_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IIcmp_INTERFACE_DEFINED__ */


#ifndef __IHttp_INTERFACE_DEFINED__
#define __IHttp_INTERFACE_DEFINED__

/* interface IHttp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IHttp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F0938A42-5986-4AD2-A548-9F087D450312")
    IHttp : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            BSTR Url) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadData( 
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0024) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0025) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyServer( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyServer( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyPassword( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WebAccount( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WebAccount( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WebPassword( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WebPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseSSL( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseSSL( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHttpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHttp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHttp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHttp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IHttp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IHttp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IHttp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IHttp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IHttp __RPC_FAR * This,
            BSTR Url);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IHttp __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadData )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0024);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            IHttp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IHttp __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0025);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyServer )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyServer )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyAccount )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyAccount )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyPassword )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPassword )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WebAccount )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WebAccount )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WebPassword )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WebPassword )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseSSL )( 
            IHttp __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseSSL )( 
            IHttp __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IHttp __RPC_FAR * This);
        
        END_INTERFACE
    } IHttpVtbl;

    interface IHttp
    {
        CONST_VTBL struct IHttpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHttp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHttp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHttp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHttp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IHttp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IHttp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IHttp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IHttp_Connect(This,Url)	\
    (This)->lpVtbl -> Connect(This,Url)

#define IHttp_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define IHttp_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IHttp_ReadData(This,__MIDL_0024)	\
    (This)->lpVtbl -> ReadData(This,__MIDL_0024)

#define IHttp_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IHttp_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define IHttp_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define IHttp_GetErrorDescription(This,ErrorCode,__MIDL_0025)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0025)

#define IHttp_get_ProxyServer(This,pVal)	\
    (This)->lpVtbl -> get_ProxyServer(This,pVal)

#define IHttp_put_ProxyServer(This,newVal)	\
    (This)->lpVtbl -> put_ProxyServer(This,newVal)

#define IHttp_get_ProxyAccount(This,pVal)	\
    (This)->lpVtbl -> get_ProxyAccount(This,pVal)

#define IHttp_put_ProxyAccount(This,newVal)	\
    (This)->lpVtbl -> put_ProxyAccount(This,newVal)

#define IHttp_get_ProxyPassword(This,pVal)	\
    (This)->lpVtbl -> get_ProxyPassword(This,pVal)

#define IHttp_put_ProxyPassword(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPassword(This,newVal)

#define IHttp_get_WebAccount(This,pVal)	\
    (This)->lpVtbl -> get_WebAccount(This,pVal)

#define IHttp_put_WebAccount(This,newVal)	\
    (This)->lpVtbl -> put_WebAccount(This,newVal)

#define IHttp_get_WebPassword(This,pVal)	\
    (This)->lpVtbl -> get_WebPassword(This,pVal)

#define IHttp_put_WebPassword(This,newVal)	\
    (This)->lpVtbl -> put_WebPassword(This,newVal)

#define IHttp_get_UseSSL(This,pVal)	\
    (This)->lpVtbl -> get_UseSSL(This,pVal)

#define IHttp_put_UseSSL(This,newVal)	\
    (This)->lpVtbl -> put_UseSSL(This,newVal)

#define IHttp_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHttp_Connect_Proxy( 
    IHttp __RPC_FAR * This,
    BSTR Url);


void __RPC_STUB IHttp_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_LastError_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHttp_Disconnect_Proxy( 
    IHttp __RPC_FAR * This);


void __RPC_STUB IHttp_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHttp_ReadData_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0024);


void __RPC_STUB IHttp_ReadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_Version_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_ExpirationDate_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_Reserved_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IHttp_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHttp_GetErrorDescription_Proxy( 
    IHttp __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0025);


void __RPC_STUB IHttp_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_ProxyServer_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_ProxyServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_ProxyServer_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHttp_put_ProxyServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_ProxyAccount_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_ProxyAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_ProxyAccount_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHttp_put_ProxyAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_ProxyPassword_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_ProxyPassword_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHttp_put_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_WebAccount_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_WebAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_WebAccount_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHttp_put_WebAccount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_WebPassword_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_WebPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_WebPassword_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IHttp_put_WebPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IHttp_get_UseSSL_Proxy( 
    IHttp __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IHttp_get_UseSSL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IHttp_put_UseSSL_Proxy( 
    IHttp __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IHttp_put_UseSSL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IHttp_Clear_Proxy( 
    IHttp __RPC_FAR * This);


void __RPC_STUB IHttp_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHttp_INTERFACE_DEFINED__ */


#ifndef __ISnmpTrapIn_INTERFACE_DEFINED__
#define __ISnmpTrapIn_INTERFACE_DEFINED__

/* interface ISnmpTrapIn */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISnmpTrapIn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EF062158-79C0-43FD-8C1B-FEE1A3B9650D")
    ISnmpTrapIn : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Port( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Port( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentOID( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentValue( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentType( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartListening( 
            /* [in] */ BSTR Community) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopListening( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteAllTraps( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTrapCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFirstTrap( 
            BOOL Remove) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNextTrap( 
            BOOL Remove) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0026) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sleep( 
            /* [in] */ LONG MilliSecs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISnmpTrapInVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Port )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Port )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentOID )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentValue )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentType )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartListening )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ BSTR Community);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopListening )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteAllTraps )( 
            ISnmpTrapIn __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrapCount )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFirstTrap )( 
            ISnmpTrapIn __RPC_FAR * This,
            BOOL Remove);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNextTrap )( 
            ISnmpTrapIn __RPC_FAR * This,
            BOOL Remove);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            ISnmpTrapIn __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0026);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sleep )( 
            ISnmpTrapIn __RPC_FAR * This,
            /* [in] */ LONG MilliSecs);
        
        END_INTERFACE
    } ISnmpTrapInVtbl;

    interface ISnmpTrapIn
    {
        CONST_VTBL struct ISnmpTrapInVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISnmpTrapIn_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISnmpTrapIn_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISnmpTrapIn_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISnmpTrapIn_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISnmpTrapIn_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISnmpTrapIn_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISnmpTrapIn_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISnmpTrapIn_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ISnmpTrapIn_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define ISnmpTrapIn_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define ISnmpTrapIn_get_Port(This,pVal)	\
    (This)->lpVtbl -> get_Port(This,pVal)

#define ISnmpTrapIn_put_Port(This,newVal)	\
    (This)->lpVtbl -> put_Port(This,newVal)

#define ISnmpTrapIn_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define ISnmpTrapIn_get_CurrentOID(This,pVal)	\
    (This)->lpVtbl -> get_CurrentOID(This,pVal)

#define ISnmpTrapIn_get_CurrentValue(This,pVal)	\
    (This)->lpVtbl -> get_CurrentValue(This,pVal)

#define ISnmpTrapIn_get_CurrentType(This,pVal)	\
    (This)->lpVtbl -> get_CurrentType(This,pVal)

#define ISnmpTrapIn_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ISnmpTrapIn_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define ISnmpTrapIn_StartListening(This,Community)	\
    (This)->lpVtbl -> StartListening(This,Community)

#define ISnmpTrapIn_StopListening(This)	\
    (This)->lpVtbl -> StopListening(This)

#define ISnmpTrapIn_DeleteAllTraps(This)	\
    (This)->lpVtbl -> DeleteAllTraps(This)

#define ISnmpTrapIn_GetTrapCount(This,pVal)	\
    (This)->lpVtbl -> GetTrapCount(This,pVal)

#define ISnmpTrapIn_GetFirstTrap(This,Remove)	\
    (This)->lpVtbl -> GetFirstTrap(This,Remove)

#define ISnmpTrapIn_GetNextTrap(This,Remove)	\
    (This)->lpVtbl -> GetNextTrap(This,Remove)

#define ISnmpTrapIn_GetErrorDescription(This,ErrorCode,__MIDL_0026)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0026)

#define ISnmpTrapIn_Sleep(This,MilliSecs)	\
    (This)->lpVtbl -> Sleep(This,MilliSecs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_Version_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_ExpirationDate_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_put_Reserved_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISnmpTrapIn_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_Port_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_put_Port_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ISnmpTrapIn_put_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_LastError_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_CurrentOID_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_CurrentOID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_CurrentValue_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_CurrentValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_get_CurrentType_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_get_CurrentType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_Initialize_Proxy( 
    ISnmpTrapIn __RPC_FAR * This);


void __RPC_STUB ISnmpTrapIn_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_Shutdown_Proxy( 
    ISnmpTrapIn __RPC_FAR * This);


void __RPC_STUB ISnmpTrapIn_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_StartListening_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [in] */ BSTR Community);


void __RPC_STUB ISnmpTrapIn_StartListening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_StopListening_Proxy( 
    ISnmpTrapIn __RPC_FAR * This);


void __RPC_STUB ISnmpTrapIn_StopListening_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_DeleteAllTraps_Proxy( 
    ISnmpTrapIn __RPC_FAR * This);


void __RPC_STUB ISnmpTrapIn_DeleteAllTraps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_GetTrapCount_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapIn_GetTrapCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_GetFirstTrap_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    BOOL Remove);


void __RPC_STUB ISnmpTrapIn_GetFirstTrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_GetNextTrap_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    BOOL Remove);


void __RPC_STUB ISnmpTrapIn_GetNextTrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_GetErrorDescription_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0026);


void __RPC_STUB ISnmpTrapIn_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapIn_Sleep_Proxy( 
    ISnmpTrapIn __RPC_FAR * This,
    /* [in] */ LONG MilliSecs);


void __RPC_STUB ISnmpTrapIn_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISnmpTrapIn_INTERFACE_DEFINED__ */


#ifndef __ISnmpTrapOut_INTERFACE_DEFINED__
#define __ISnmpTrapOut_INTERFACE_DEFINED__

/* interface ISnmpTrapOut */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISnmpTrapOut;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E808B273-BE4B-4FCF-9342-A229B8DF5CC5")
    ISnmpTrapOut : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Port( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Port( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolVersion( 
            /* [in] */ long ProtocolVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0027) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddTrap( 
            /* [in] */ BSTR OID,
            /* [in] */ LONG Type,
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ BSTR Agent,
            /* [in] */ BSTR Community) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sleep( 
            /* [in] */ LONG MilliSecs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISnmpTrapOutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISnmpTrapOut __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISnmpTrapOut __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Port )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Port )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtocolVersion )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProtocolVersion )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ long ProtocolVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            ISnmpTrapOut __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            ISnmpTrapOut __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0027);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddTrap )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ BSTR OID,
            /* [in] */ LONG Type,
            /* [in] */ BSTR Value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ BSTR Agent,
            /* [in] */ BSTR Community);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ISnmpTrapOut __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            ISnmpTrapOut __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sleep )( 
            ISnmpTrapOut __RPC_FAR * This,
            /* [in] */ LONG MilliSecs);
        
        END_INTERFACE
    } ISnmpTrapOutVtbl;

    interface ISnmpTrapOut
    {
        CONST_VTBL struct ISnmpTrapOutVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISnmpTrapOut_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISnmpTrapOut_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISnmpTrapOut_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISnmpTrapOut_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISnmpTrapOut_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISnmpTrapOut_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISnmpTrapOut_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISnmpTrapOut_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define ISnmpTrapOut_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define ISnmpTrapOut_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define ISnmpTrapOut_get_Port(This,pVal)	\
    (This)->lpVtbl -> get_Port(This,pVal)

#define ISnmpTrapOut_put_Port(This,newVal)	\
    (This)->lpVtbl -> put_Port(This,newVal)

#define ISnmpTrapOut_get_ProtocolVersion(This,pVal)	\
    (This)->lpVtbl -> get_ProtocolVersion(This,pVal)

#define ISnmpTrapOut_put_ProtocolVersion(This,ProtocolVersion)	\
    (This)->lpVtbl -> put_ProtocolVersion(This,ProtocolVersion)

#define ISnmpTrapOut_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define ISnmpTrapOut_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define ISnmpTrapOut_GetErrorDescription(This,ErrorCode,__MIDL_0027)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0027)

#define ISnmpTrapOut_AddTrap(This,OID,Type,Value)	\
    (This)->lpVtbl -> AddTrap(This,OID,Type,Value)

#define ISnmpTrapOut_Send(This,Agent,Community)	\
    (This)->lpVtbl -> Send(This,Agent,Community)

#define ISnmpTrapOut_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ISnmpTrapOut_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define ISnmpTrapOut_Sleep(This,MilliSecs)	\
    (This)->lpVtbl -> Sleep(This,MilliSecs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_get_Version_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapOut_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_get_ExpirationDate_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapOut_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_put_Reserved_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ISnmpTrapOut_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_get_Port_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapOut_get_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_put_Port_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ISnmpTrapOut_put_Port_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_get_ProtocolVersion_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapOut_get_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_put_ProtocolVersion_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ long ProtocolVersion);


void __RPC_STUB ISnmpTrapOut_put_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_get_LastError_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ISnmpTrapOut_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_Clear_Proxy( 
    ISnmpTrapOut __RPC_FAR * This);


void __RPC_STUB ISnmpTrapOut_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_GetErrorDescription_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0027);


void __RPC_STUB ISnmpTrapOut_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_AddTrap_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ BSTR OID,
    /* [in] */ LONG Type,
    /* [in] */ BSTR Value);


void __RPC_STUB ISnmpTrapOut_AddTrap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_Send_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ BSTR Agent,
    /* [in] */ BSTR Community);


void __RPC_STUB ISnmpTrapOut_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_Initialize_Proxy( 
    ISnmpTrapOut __RPC_FAR * This);


void __RPC_STUB ISnmpTrapOut_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_Shutdown_Proxy( 
    ISnmpTrapOut __RPC_FAR * This);


void __RPC_STUB ISnmpTrapOut_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISnmpTrapOut_Sleep_Proxy( 
    ISnmpTrapOut __RPC_FAR * This,
    /* [in] */ LONG MilliSecs);


void __RPC_STUB ISnmpTrapOut_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISnmpTrapOut_INTERFACE_DEFINED__ */


#ifndef __IDns_INTERFACE_DEFINED__
#define __IDns_INTERFACE_DEFINED__

/* interface IDns */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDns;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("883E5419-8FB8-4DCF-B579-2A8BDF82CBE6")
    IDns : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExpirationDate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastError( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastResponse( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Reserved( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDns( 
            BSTR DnsServer,
            BSTR Owner,
            BOOL ARecord) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0028) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDnsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDns __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDns __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDns __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDns __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDns __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDns __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDns __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Version )( 
            IDns __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExpirationDate )( 
            IDns __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastError )( 
            IDns __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastResponse )( 
            IDns __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Reserved )( 
            IDns __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDns )( 
            IDns __RPC_FAR * This,
            BSTR DnsServer,
            BSTR Owner,
            BOOL ARecord);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IDns __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IDns __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IDns __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetErrorDescription )( 
            IDns __RPC_FAR * This,
            long ErrorCode,
            /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0028);
        
        END_INTERFACE
    } IDnsVtbl;

    interface IDns
    {
        CONST_VTBL struct IDnsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDns_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDns_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDns_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDns_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDns_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDns_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDns_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDns_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IDns_get_ExpirationDate(This,pVal)	\
    (This)->lpVtbl -> get_ExpirationDate(This,pVal)

#define IDns_get_LastError(This,pVal)	\
    (This)->lpVtbl -> get_LastError(This,pVal)

#define IDns_get_LastResponse(This,pVal)	\
    (This)->lpVtbl -> get_LastResponse(This,pVal)

#define IDns_put_Reserved(This,newVal)	\
    (This)->lpVtbl -> put_Reserved(This,newVal)

#define IDns_QueryDns(This,DnsServer,Owner,ARecord)	\
    (This)->lpVtbl -> QueryDns(This,DnsServer,Owner,ARecord)

#define IDns_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IDns_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IDns_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define IDns_GetErrorDescription(This,ErrorCode,__MIDL_0028)	\
    (This)->lpVtbl -> GetErrorDescription(This,ErrorCode,__MIDL_0028)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDns_get_Version_Proxy( 
    IDns __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDns_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDns_get_ExpirationDate_Proxy( 
    IDns __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDns_get_ExpirationDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDns_get_LastError_Proxy( 
    IDns __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDns_get_LastError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDns_get_LastResponse_Proxy( 
    IDns __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDns_get_LastResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDns_put_Reserved_Proxy( 
    IDns __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDns_put_Reserved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDns_QueryDns_Proxy( 
    IDns __RPC_FAR * This,
    BSTR DnsServer,
    BSTR Owner,
    BOOL ARecord);


void __RPC_STUB IDns_QueryDns_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDns_Clear_Proxy( 
    IDns __RPC_FAR * This);


void __RPC_STUB IDns_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDns_Initialize_Proxy( 
    IDns __RPC_FAR * This);


void __RPC_STUB IDns_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDns_Shutdown_Proxy( 
    IDns __RPC_FAR * This);


void __RPC_STUB IDns_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IDns_GetErrorDescription_Proxy( 
    IDns __RPC_FAR * This,
    long ErrorCode,
    /* [retval][out] */ BSTR __RPC_FAR *__MIDL_0028);


void __RPC_STUB IDns_GetErrorDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDns_INTERFACE_DEFINED__ */



#ifndef __ASOCKETLib_LIBRARY_DEFINED__
#define __ASOCKETLib_LIBRARY_DEFINED__

/* library ASOCKETLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ASOCKETLib;

EXTERN_C const CLSID CLSID_Snmp;

#ifdef __cplusplus

class DECLSPEC_UUID("705BB2A2-D316-4CEC-AA21-CF8D3AE45BEE")
Snmp;
#endif

EXTERN_C const CLSID CLSID_Socket;

#ifdef __cplusplus

class DECLSPEC_UUID("4F986D6D-E04F-4BEE-B8C7-8252577CB282")
Socket;
#endif

EXTERN_C const CLSID CLSID_RSh;

#ifdef __cplusplus

class DECLSPEC_UUID("5A128291-2445-441C-A8E9-ED886D053019")
RSh;
#endif

EXTERN_C const CLSID CLSID_Ntp;

#ifdef __cplusplus

class DECLSPEC_UUID("9591DC19-DD2F-4AD4-A3B6-65CDC428ABD1")
Ntp;
#endif

EXTERN_C const CLSID CLSID_WOL;

#ifdef __cplusplus

class DECLSPEC_UUID("454BE66D-12D0-43D0-87FE-99EE02E2C05B")
WOL;
#endif

EXTERN_C const CLSID CLSID_Icmp;

#ifdef __cplusplus

class DECLSPEC_UUID("743A672A-9985-4866-BC54-9C89087E01AE")
Icmp;
#endif

EXTERN_C const CLSID CLSID_Http;

#ifdef __cplusplus

class DECLSPEC_UUID("ACFF15A9-A9F6-4515-AD74-B325A796B877")
Http;
#endif

EXTERN_C const CLSID CLSID_SnmpTrapIn;

#ifdef __cplusplus

class DECLSPEC_UUID("497D6B4E-AD7F-4849-9CF0-55FED1794789")
SnmpTrapIn;
#endif

EXTERN_C const CLSID CLSID_SnmpTrapOut;

#ifdef __cplusplus

class DECLSPEC_UUID("FD91E7FC-A8AF-44A2-B9F1-6D816BB55A8F")
SnmpTrapOut;
#endif

EXTERN_C const CLSID CLSID_Dns;

#ifdef __cplusplus

class DECLSPEC_UUID("88D6BA65-7AA1-46B5-82C2-945889169EF7")
Dns;
#endif
#endif /* __ASOCKETLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
