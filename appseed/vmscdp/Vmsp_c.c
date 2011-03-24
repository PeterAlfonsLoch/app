
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon May 06 10:08:05 2002
 */
/* Compiler settings for D:\vms\current\vmsp\vmsp.odl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

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

MIDL_DEFINE_GUID(IID, LIBID_VmsPlayer,0x8661C139,0x6E87,0x4310,0x80,0xA4,0x9C,0x1F,0xBA,0xD7,0xB7,0x38);


MIDL_DEFINE_GUID(IID, DIID_IXfplayer,0x93535E2A,0xF1A0,0x4FD6,0xA5,0x4C,0xDA,0xDA,0xDF,0x31,0x4C,0x93);


MIDL_DEFINE_GUID(CLSID, CLSID_Document,0xF53B78E0,0xA6F5,0x41CF,0xB4,0xFB,0x9F,0x9F,0xE4,0x9D,0xD4,0x16);


MIDL_DEFINE_GUID(IID, DIID_IPlaylistDoc,0x6674CF8E,0x90F7,0x4F8E,0x9B,0xC7,0x7E,0xF3,0x74,0x5A,0xE4,0x35);


MIDL_DEFINE_GUID(CLSID, CLSID_PlaylistDoc,0x91C474A6,0x42D2,0x4203,0x8F,0x04,0xA3,0xEE,0x75,0xA8,0xA9,0x06);


MIDL_DEFINE_GUID(IID, DIID_IButtonV007,0x2030DF2B,0xAEE2,0x4E57,0x98,0x03,0x30,0x5A,0x5B,0xDA,0xCA,0x08);


MIDL_DEFINE_GUID(CLSID, CLSID_ButtonV007,0x6BD1EEB9,0x4646,0x4608,0xA3,0x54,0x93,0x33,0x1C,0x0B,0xAA,0x45);


MIDL_DEFINE_GUID(IID, DIID_ITransparentWnd,0x93535E2B,0xF1A0,0x4FD6,0xA5,0x4C,0xDA,0xDA,0xDF,0x31,0x4C,0x93);


MIDL_DEFINE_GUID(IID, IID_IVmsPlayer,0x12165CC8,0xB12C,0x4080,0x94,0x37,0x27,0xD0,0x36,0xB9,0xC5,0x5B);


MIDL_DEFINE_GUID(IID, DIID__IVmsPlayerEvents,0x12141E1A,0x4783,0x4EC4,0xBE,0xC4,0xB4,0xBC,0x80,0x80,0x2C,0x09);


MIDL_DEFINE_GUID(CLSID, CLSID_VmsPlayer,0x1211A311,0x6D5F,0x4A8A,0x8A,0x7B,0x43,0x79,0x1B,0x23,0x60,0x81);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

