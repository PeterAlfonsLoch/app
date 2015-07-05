#pragma once


#ifdef _WIN32
#define CLASS_DECL_EXPORT __declspec(dllexport)
#define CLASS_DECL_IMPORT __declspec(dllimport)
#else
#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#endif



#ifdef _FREERDP_RDPCLIENT_DLL
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_RDPCLIENT  CLASS_DECL_IMPORT
#endif





