#pragma once


#ifdef WINDOWS

#define CLASS_DECL_EXPORT __declspec(dllexport)
#define CLASS_DECL_IMPORT __declspec(dllimport)
#define CLASS_DECL_THREAD __declspec(thread)
#else
#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#define CLASS_DECL_THREAD __thread
#endif



#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_IMPORT
#endif





