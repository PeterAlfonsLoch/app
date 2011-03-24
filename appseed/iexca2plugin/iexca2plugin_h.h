

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Jul 31 11:15:05 2010
 */
/* Compiler settings for iexca2.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __iexca2_h_h__
#define __iexca2_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAXControl_FWD_DEFINED__
#define __IAXControl_FWD_DEFINED__
typedef interface IAXControl IAXControl;
#endif 	/* __IAXControl_FWD_DEFINED__ */


#ifndef __DAXEvents_FWD_DEFINED__
#define __DAXEvents_FWD_DEFINED__
typedef interface DAXEvents DAXEvents;
#endif 	/* __DAXEvents_FWD_DEFINED__ */


#ifndef __AXPlugin_FWD_DEFINED__
#define __AXPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class AXPlugin AXPlugin;
#else
typedef struct AXPlugin AXPlugin;
#endif /* __cplusplus */

#endif 	/* __AXPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __FREE_AX_LIBRARY_DEFINED__
#define __FREE_AX_LIBRARY_DEFINED__

/* library FREE_AX */
/* [helpstring][version][uuid] */ 




EXTERN_C const IID LIBID_FREE_AX;

#ifndef __IAXControl_INTERFACE_DEFINED__
#define __IAXControl_INTERFACE_DEFINED__

/* interface IAXControl */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_IAXControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CA211984-1984-1977-95A6-F1FCA18971F1")
    IAXControl : public IDispatch
    {
    public:
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TestString( 
            /* [in] */ BSTR str) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TestString( 
            /* [retval][out] */ BSTR *str) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ VARIANT_BOOL isShow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAXControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAXControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAXControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAXControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAXControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAXControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAXControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAXControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TestString )( 
            IAXControl * This,
            /* [in] */ BSTR str);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TestString )( 
            IAXControl * This,
            /* [retval][out] */ BSTR *str);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetVisible )( 
            IAXControl * This,
            /* [in] */ VARIANT_BOOL isShow);
        
        END_INTERFACE
    } IAXControlVtbl;

    interface IAXControl
    {
        CONST_VTBL struct IAXControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAXControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAXControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAXControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAXControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAXControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAXControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAXControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAXControl_put_TestString(This,str)	\
    ( (This)->lpVtbl -> put_TestString(This,str) ) 

#define IAXControl_get_TestString(This,str)	\
    ( (This)->lpVtbl -> get_TestString(This,str) ) 

#define IAXControl_SetVisible(This,isShow)	\
    ( (This)->lpVtbl -> SetVisible(This,isShow) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAXControl_INTERFACE_DEFINED__ */


#ifndef __DAXEvents_DISPINTERFACE_DEFINED__
#define __DAXEvents_DISPINTERFACE_DEFINED__

/* dispinterface DAXEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID_DAXEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("CA211984-1984-1977-8A0D-FABFDA616C0B")
    DAXEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DAXEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            DAXEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            DAXEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            DAXEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            DAXEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            DAXEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            DAXEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            DAXEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } DAXEventsVtbl;

    interface DAXEvents
    {
        CONST_VTBL struct DAXEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DAXEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define DAXEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define DAXEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define DAXEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define DAXEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define DAXEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define DAXEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DAXEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AXPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("CA211984-1984-1977-A861-F8AA2A7AEE4B")
AXPlugin;
#endif
#endif /* __FREE_AX_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


