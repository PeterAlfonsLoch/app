#pragma once

#ifndef _DEBUG
#define _DEBUG
#endif

#if defined(_WIN64) && defined(_M_X64)

#define IMPLEMENT_VISTA_TOOLS

#define _AMD64_
#define core_level 3

#define WIN32

#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/win32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>


typedef std::type_info std_type_info;


#include "include/inttypes.h"



#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 

#elif (_MSC_VER <= 1200)  // vc6


// warning C4786: identifier was truncated to '255' characters in the debug information
#pragma warning( disable: 4786 )

// warning C4097: typedef-name '<short-name>' used as synonym for class-name '<long-name>'
#pragma warning( disable: 4097 )



#define core_level 1
#define _SECURE_ATL 0

#define WIN32
#define _X86_

#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/win32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>
typedef type_info std_type_info;














#include "include/inttypes.h"










#define errno_t int
#define DWORD_PTR unsigned long
#define ULONG_PTR unsigned long
#define LONG_PTR signed long
typedef long __time64_t;







/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif


/* Error codes used in the Secure CRT functions */

#ifndef RC_INVOKED
#if !defined(_SECURECRT_ERRCODE_VALUES_DEFINED)
#define _SECURECRT_ERRCODE_VALUES_DEFINED
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80
#endif
#endif









#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 



#elif (_MSC_VER <= 1310)  // vc71


#define VC71
//#pragma warning( disable: 4786 )

#define core_level 2

#define WIN32
#define _X86_


#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/win32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>
typedef type_info std_type_info;














#include "include/inttypes.h"










#define errno_t int
/*#define DWORD_PTR unsigned long
#define ULONG_PTR unsigned long
#define LONG_PTR signed long*/







/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif


/* Error codes used in the Secure CRT functions */

#ifndef RC_INVOKED
#if !defined(_SECURECRT_ERRCODE_VALUES_DEFINED)
#define _SECURECRT_ERRCODE_VALUES_DEFINED
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80
#endif
#endif









#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 



#elif (_MSC_VER <= 1400)  // vc80


#define VC8
//#pragma warning( disable: 4786 )

#define core_level 3

#define WIN32
#define _X86_


#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/win32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>
typedef type_info std_type_info;














#include "include/inttypes.h"










#define errno_t int
/*#define DWORD_PTR unsigned long
#define ULONG_PTR unsigned long
#define LONG_PTR signed long*/







/* _TRUNCATE */
#if !defined(_TRUNCATE)
#define _TRUNCATE ((size_t)-1)
#endif


/* Error codes used in the Secure CRT functions */

#ifndef RC_INVOKED
#if !defined(_SECURECRT_ERRCODE_VALUES_DEFINED)
#define _SECURECRT_ERRCODE_VALUES_DEFINED
#define EINVAL          22
#define ERANGE          34
#define EILSEQ          42
#define STRUNCATE       80
#endif
#endif









#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 



#else  // core level 3


#define core_level 4


#define IMPLEMENT_VISTA_TOOLS


#define WIN32
#define _X86_

#define DRAWDIB_INCLUDE_STRETCHDIB

#pragma pointers_to_members( full_generality, virtual_inheritance )
#include "include/win32_system.h"
#define _ApplicationFrameworkDLL

#include <typeinfo.h>


typedef std::type_info std_type_info;


#include "include/inttypes.h"



#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")
//#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")
//#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "shlwapi.lib")

#pragma comment(lib, "vfw32.lib") 
#pragma comment(lib, "opengl32.lib") 


#endif