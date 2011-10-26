

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_FREE_AX,0xCA211984,0x1984,0x1977,0xB3,0x8E,0x49,0x18,0xE3,0xDB,0xBA,0xB3);


MIDL_DEFINE_GUID(IID, IID_IAXControl,0xCA211984,0x1984,0x1977,0x95,0xA6,0xF1,0xFC,0xA1,0x89,0x71,0xF1);


MIDL_DEFINE_GUID(IID, DIID_DAXEvents,0xCA211984,0x1984,0x1977,0x8A,0x0D,0xFA,0xBF,0xDA,0x61,0x6C,0x0B);


MIDL_DEFINE_GUID(CLSID, CLSID_AXPlugin,0xCA211984,0x1984,0x1977,0xA8,0x61,0xF8,0xAA,0x2A,0x7A,0xEE,0x4B);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



