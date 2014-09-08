#pragma once

#ifndef CA2_APP_AURA_AURA_AURA_AURA_H

#ifdef _WIN32
#define CLASS_DECL_EXPORT _declspec(dllexport) 
#define CLASS_DECL_IMPORT _declspec(dllexport)
#else
#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#endif



#if defined(__cplusplus)


#define DECL_EXTERN_C	   extern "C"
#define BEGIN_EXTERN_C		extern "C" {
#define END_EXTERN_C		   }


#else


#define DECL_EXTERN_C
#define BEGIN_EXTERN_C
#define END_EXTERN_C


#endif


#endif




#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_IMPORT
#endif





