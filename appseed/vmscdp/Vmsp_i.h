/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 04 09:58:08 2002
 */
/* Compiler settings for C:\veriwell\_ms\vmsp\vmsp.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __Vmsp_i_h__
#define __Vmsp_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IXfplayer_FWD_DEFINED__
#define __IXfplayer_FWD_DEFINED__
typedef interface IXfplayer IXfplayer;
#endif 	/* __IXfplayer_FWD_DEFINED__ */


#ifndef __IMidDocument_FWD_DEFINED__
#define __IMidDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class IMidDocument IMidDocument;
#else
typedef struct IMidDocument IMidDocument;
#endif /* __cplusplus */

#endif 	/* __IMidDocument_FWD_DEFINED__ */


#ifndef __IKarDocument_FWD_DEFINED__
#define __IKarDocument_FWD_DEFINED__

#ifdef __cplusplus
typedef class IKarDocument IKarDocument;
#else
typedef struct IKarDocument IKarDocument;
#endif /* __cplusplus */

#endif 	/* __IKarDocument_FWD_DEFINED__ */


#ifndef __ISt3Document_FWD_DEFINED__
#define __ISt3Document_FWD_DEFINED__

#ifdef __cplusplus
typedef class ISt3Document ISt3Document;
#else
typedef struct ISt3Document ISt3Document;
#endif /* __cplusplus */

#endif 	/* __ISt3Document_FWD_DEFINED__ */


#ifndef __IPlaylistDoc_FWD_DEFINED__
#define __IPlaylistDoc_FWD_DEFINED__
typedef interface IPlaylistDoc IPlaylistDoc;
#endif 	/* __IPlaylistDoc_FWD_DEFINED__ */


#ifndef __PlaylistDoc_FWD_DEFINED__
#define __PlaylistDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class PlaylistDoc PlaylistDoc;
#else
typedef struct PlaylistDoc PlaylistDoc;
#endif /* __cplusplus */

#endif 	/* __PlaylistDoc_FWD_DEFINED__ */


#ifndef __IButtonV007_FWD_DEFINED__
#define __IButtonV007_FWD_DEFINED__
typedef interface IButtonV007 IButtonV007;
#endif 	/* __IButtonV007_FWD_DEFINED__ */


#ifndef __ButtonV007_FWD_DEFINED__
#define __ButtonV007_FWD_DEFINED__

#ifdef __cplusplus
typedef class ButtonV007 ButtonV007;
#else
typedef struct ButtonV007 ButtonV007;
#endif /* __cplusplus */

#endif 	/* __ButtonV007_FWD_DEFINED__ */


#ifndef __IVmsPlayer_FWD_DEFINED__
#define __IVmsPlayer_FWD_DEFINED__
typedef interface IVmsPlayer IVmsPlayer;
#endif 	/* __IVmsPlayer_FWD_DEFINED__ */


#ifndef ___IVmsPlayerEvents_FWD_DEFINED__
#define ___IVmsPlayerEvents_FWD_DEFINED__
typedef interface _IVmsPlayerEvents _IVmsPlayerEvents;
#endif 	/* ___IVmsPlayerEvents_FWD_DEFINED__ */


#ifndef __VmsPlayer_FWD_DEFINED__
#define __VmsPlayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class VmsPlayer VmsPlayer;
#else
typedef struct VmsPlayer VmsPlayer;
#endif /* __cplusplus */

#endif 	/* __VmsPlayer_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __VmsPlayer_LIBRARY_DEFINED__
#define __VmsPlayer_LIBRARY_DEFINED__

/* library VmsPlayer */
/* [version][uuid] */ 


DEFINE_GUID(LIBID_VmsPlayer,0x8661C139,0x6E87,0x4310,0x80,0xA4,0x9C,0x1F,0xBA,0xD7,0xB7,0x38);

#ifndef __IXfplayer_DISPINTERFACE_DEFINED__
#define __IXfplayer_DISPINTERFACE_DEFINED__

/* dispinterface IXfplayer */
/* [uuid] */ 


DEFINE_GUID(DIID_IXfplayer,0x93535E2A,0xF1A0,0x4FD6,0xA5,0x4C,0xDA,0xDA,0xDF,0x31,0x4C,0x93);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("93535E2A-F1A0-4FD6-A54C-DADADF314C93")
    IXfplayer : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IXfplayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXfplayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXfplayer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXfplayer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IXfplayer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IXfplayer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IXfplayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IXfplayer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IXfplayerVtbl;

    interface IXfplayer
    {
        CONST_VTBL struct IXfplayerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXfplayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXfplayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXfplayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXfplayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IXfplayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IXfplayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IXfplayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IXfplayer_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_IMidDocument,0xF53B78E0,0xA6F5,0x41CF,0xB4,0xFB,0x9F,0x9F,0xE4,0x9D,0xD4,0x16);

#ifdef __cplusplus

class DECLSPEC_UUID("F53B78E0-A6F5-41CF-B4FB-9F9FE49DD416")
IMidDocument;
#endif

DEFINE_GUID(CLSID_IKarDocument,0xF53B78E0,0xA6F5,0x41CF,0xB4,0xFB,0x9F,0x9F,0xE4,0x9D,0xD4,0x17);

#ifdef __cplusplus

class DECLSPEC_UUID("F53B78E0-A6F5-41CF-B4FB-9F9FE49DD417")
IKarDocument;
#endif

DEFINE_GUID(CLSID_ISt3Document,0xF53B78E0,0xA6F5,0x41CF,0xB4,0xFB,0x9F,0x9F,0xE4,0x9D,0xD4,0x18);

#ifdef __cplusplus

class DECLSPEC_UUID("F53B78E0-A6F5-41CF-B4FB-9F9FE49DD418")
ISt3Document;
#endif

#ifndef __IPlaylistDoc_DISPINTERFACE_DEFINED__
#define __IPlaylistDoc_DISPINTERFACE_DEFINED__

/* dispinterface IPlaylistDoc */
/* [uuid] */ 


DEFINE_GUID(DIID_IPlaylistDoc,0x6674CF8E,0x90F7,0x4F8E,0x9B,0xC7,0x7E,0xF3,0x74,0x5A,0xE4,0x35);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6674CF8E-90F7-4F8E-9BC7-7EF3745AE435")
    IPlaylistDoc : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IPlaylistDocVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPlaylistDoc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPlaylistDoc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPlaylistDoc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPlaylistDoc __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPlaylistDoc __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPlaylistDoc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPlaylistDoc __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IPlaylistDocVtbl;

    interface IPlaylistDoc
    {
        CONST_VTBL struct IPlaylistDocVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlaylistDoc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPlaylistDoc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPlaylistDoc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPlaylistDoc_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPlaylistDoc_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPlaylistDoc_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPlaylistDoc_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IPlaylistDoc_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_PlaylistDoc,0x91C474A6,0x42D2,0x4203,0x8F,0x04,0xA3,0xEE,0x75,0xA8,0xA9,0x06);

#ifdef __cplusplus

class DECLSPEC_UUID("91C474A6-42D2-4203-8F04-A3EE75A8A906")
PlaylistDoc;
#endif

#ifndef __IButtonV007_DISPINTERFACE_DEFINED__
#define __IButtonV007_DISPINTERFACE_DEFINED__

/* dispinterface IButtonV007 */
/* [uuid] */ 


DEFINE_GUID(DIID_IButtonV007,0x2030DF2B,0xAEE2,0x4E57,0x98,0x03,0x30,0x5A,0x5B,0xDA,0xCA,0x08);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2030DF2B-AEE2-4E57-9803-305A5BDACA08")
    IButtonV007 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IButtonV007Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IButtonV007 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IButtonV007 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IButtonV007 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IButtonV007 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IButtonV007 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IButtonV007 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IButtonV007 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IButtonV007Vtbl;

    interface IButtonV007
    {
        CONST_VTBL struct IButtonV007Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IButtonV007_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IButtonV007_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IButtonV007_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IButtonV007_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IButtonV007_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IButtonV007_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IButtonV007_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IButtonV007_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_ButtonV007,0x6BD1EEB9,0x4646,0x4608,0xA3,0x54,0x93,0x33,0x1C,0x0B,0xAA,0x45);

#ifdef __cplusplus

class DECLSPEC_UUID("6BD1EEB9-4646-4608-A354-93331C0BAA45")
ButtonV007;
#endif

#ifndef __IVmsPlayer_INTERFACE_DEFINED__
#define __IVmsPlayer_INTERFACE_DEFINED__

/* interface IVmsPlayer */
/* [unique][helpstring][dual][uuid][object] */ 


DEFINE_GUID(IID_IVmsPlayer,0x12165CC8,0xB12C,0x4080,0x94,0x37,0x27,0xD0,0x36,0xB9,0xC5,0x5B);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12165CC8-B12C-4080-9437-27D036B9C55B")
    IVmsPlayer : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReserveSongs( 
            VARIANT __RPC_FAR *pvar) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVmsPlayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVmsPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVmsPlayer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVmsPlayer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVmsPlayer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVmsPlayer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVmsPlayer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVmsPlayer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReserveSongs )( 
            IVmsPlayer __RPC_FAR * This,
            VARIANT __RPC_FAR *pvar);
        
        END_INTERFACE
    } IVmsPlayerVtbl;

    interface IVmsPlayer
    {
        CONST_VTBL struct IVmsPlayerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVmsPlayer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVmsPlayer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVmsPlayer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVmsPlayer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVmsPlayer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVmsPlayer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVmsPlayer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVmsPlayer_ReserveSongs(This,pvar)	\
    (This)->lpVtbl -> ReserveSongs(This,pvar)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVmsPlayer_ReserveSongs_Proxy( 
    IVmsPlayer __RPC_FAR * This,
    VARIANT __RPC_FAR *pvar);


void __RPC_STUB IVmsPlayer_ReserveSongs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVmsPlayer_INTERFACE_DEFINED__ */


#ifndef ___IVmsPlayerEvents_DISPINTERFACE_DEFINED__
#define ___IVmsPlayerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IVmsPlayerEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__IVmsPlayerEvents,0x12141E1A,0x4783,0x4EC4,0xBE,0xC4,0xB4,0xBC,0x80,0x80,0x2C,0x09);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("12141E1A-4783-4EC4-BEC4-B4BC80802C09")
    _IVmsPlayerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IVmsPlayerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IVmsPlayerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IVmsPlayerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IVmsPlayerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IVmsPlayerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IVmsPlayerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IVmsPlayerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IVmsPlayerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IVmsPlayerEventsVtbl;

    interface _IVmsPlayerEvents
    {
        CONST_VTBL struct _IVmsPlayerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IVmsPlayerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IVmsPlayerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IVmsPlayerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IVmsPlayerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IVmsPlayerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IVmsPlayerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IVmsPlayerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IVmsPlayerEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_VmsPlayer,0x1211A311,0x6D5F,0x4A8A,0x8A,0x7B,0x43,0x79,0x1B,0x23,0x60,0x81);

#ifdef __cplusplus

class DECLSPEC_UUID("1211A311-6D5F-4A8A-8A7B-43791B236081")
VmsPlayer;
#endif
#endif /* __VmsPlayer_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
