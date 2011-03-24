#pragma once


#include "radix.h"


#include "_/_.h"


#pragma pointers_to_members( full_generality, virtual_inheritance )


#include "operational_system/operational_system.h"        // Target version control


// Since ca2 API itself is built with wchar_t as a native type, it will not have
// the correct type info for types built with wchar_t typedef'd to unsigned
// short.  Make sure that the ::fontopus::user's cast builds this type info in this case.
#ifndef _NATIVE_WCHAR_T_DEFINED
#define _AFX_FULLTYPEINFO
#endif


#ifdef __ATLDBGMEM_H__
#error <atldbgmem.h> cannot be used in ca2 API projects. See AfxEnableMemoryTracking
#endif

#if defined(_MFC_DLL_BLD) && defined(_DEBUG)
#ifndef _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#endif
#endif



#if core_level_1


#include <new.h>
#include <new>
#include <memory>


#elif defined(_INC_NEW) && defined(WIN32)

   #include <new.h>

#endif

#ifdef XXXXXXXXXXXXXXXXXXXX


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <locale>
#include <iosfwd>
#include <stdlib.h>
#include <vector>
#include <bitset>
#include <limits.h>
#include <list>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <wchar.h>
#include <malloc.h>
#if defined(WIN32)
#include <mbstring.h>
#endif
#include <errno.h>
#if defined(WIN32)
#include <tchar.h>
#endif
#include <string.h>
#include <stddef.h>
#include <tchar.h>
#include <limits.h>
#include <errno.h>
#include <process.h>    // for _beginthreadex, _endthreadex
#include <stdio.h>
#include <stdarg.h>




#ifndef _WIN32
#include <sys/select.h>
#include <sys/time.h>
#endif


#endif

CLASS_DECL_ca HMODULE LoadCa2Library(const char * psz);


#ifdef _WIN64
#ifndef _AFX_NO_DAO_SUPPORT
#define _AFX_NO_DAO_SUPPORT
#endif
#endif


/////////////////////////////////////////////////////////
// Forward declations
namespace radix
{
   class object;               
}
class base_exception;            
class simple_exception;          
class memory_exception;          
class not_supported_exception;   
class invalid_argument_exception;      
namespace ex1
{
   class file_exception;
   class file;
}
class stdio_file;
namespace primitive
{
   template < class MEMORY >
   class memory_file;
}
namespace ex1
{
   struct file_status;
}
struct memory_state;
class dump_context;

/////////////////////////////////////////////////////////////////////////////
// Other includes from standard "C" runtimes

#ifndef _INC_STRING
   #include <string.h>
#endif
#ifndef _INC_STDIO
   #include <stdio.h>
#endif
#ifndef _INC_STDLIB
   #include <stdlib.h>
#endif
#ifndef _INC_TIME
   #include <time.h>
#endif
#ifndef _INC_LIMITS
   #include <limits.h>
#endif
#ifndef _INC_STDDEF
   #include <stddef.h>
#endif
#ifndef _INC_STDARG
   #include <stdarg.h>
#endif
#ifndef _INC_ERRNO
#include <errno.h>
#endif

#include <malloc.h>

#ifndef _AFX_NO_DEBUG_CRT
#ifndef _INC_CRTDBG
   #include <crtdbg.h>
#endif
#endif // _AFX_NO_DEBUG_CRT

#ifdef _AFX_OLD_EXCEPTIONS
#error ca2 API does not support MFC setjmp/longjmp exception handling.
#endif

/////////////////////////////////////////////////////////////////////////////
// Basic types
// abstract iteration position
struct __POSITION {};
typedef __POSITION* POSITION;

// Standard constants
#undef FALSE
#undef TRUE
#undef NULL

#define FALSE   0
#define TRUE    1
#define NULL    0

/////////////////////////////////////////////////////////////////////////////
// _AFX_FUNCNAME definition
#ifdef UNICODE
#define _AFX_FUNCNAME(_Name) _Name##W
#else
#define _AFX_FUNCNAME(_Name) _Name##A
#endif

/////////////////////////////////////////////////////////////////////////////
// Turn off warnings for /W4
// To resume any of these warning: #pragma warning(default: 4xxx)
// which should be placed after the AFX include files

#pragma warning(disable: 4505)  // unreferenced local function has been removed
#pragma warning(disable: 4511)  // private copy constructors are good to have
#pragma warning(disable: 4512)  // private operator= are good to have
#pragma warning(disable: 4514)  // unreferenced inlines are common
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4660)  // template is already instantiated
#pragma warning(disable: 4127)  // constant expression used in macros do while(0);

// warnings specific to _ApplicationFrameworkDLL version
#ifdef _ApplicationFrameworkDLL
#pragma warning(disable: 4275)  // deriving exported class from non-exported
#pragma warning(disable: 4251)  // using non-exported as public in exported
#endif

#ifdef _AFX_ALL_WARNINGS
#pragma warning( push )
#endif

// warnings generated with common ca2 API/Windows code
#pragma warning(disable: 4134)  // message ::collection::map member fxn casts
#pragma warning(disable: 4201)  // nameless unions are part of C++
#pragma warning(disable: 4320)  // structs with uuid handled as interfaces
#pragma warning(disable: 4705)  // statement has no effect in optimized code
#pragma warning(disable: 4191)  // pointer-to-function casting
// warnings caused by normal optimizations
#ifndef _DEBUG
#pragma warning(disable: 4701)  // local var *may* be used without init
#pragma warning(disable: 4702)  // unreachable code caused by optimizations
#pragma warning(disable: 4791)  // loss of debugging info in release version
#pragma warning(disable: 4189)  // initialized but unused var
#pragma warning(disable: 4390)  // is_empty controlled statement
#endif
// warnings specific to _ApplicationFrameworkDLL version
#ifdef _ApplicationFrameworkDLL
#pragma warning(disable: 4204)  // non-constant aggregate initializer
#endif
#pragma warning(disable: 4263 4264)  // base class method is hidden


/////////////////////////////////////////////////////////////////////////////
// Other implementation helpers

#define BEFORE_START_POSITION ((POSITION)-1L)


#undef AFX_DATA
#define AFX_DATA AFX_CORE_DATA


#ifndef _OLEAUTO_H_
   typedef wchar_t * BSTR;// must (semantically) match typedef in oleauto.h
#endif

#undef new



#define new DEBUG_NEW



#include "primitive/primitive.h"


#include "base.h"
#include "composite.h"
#include "comparable.h"

#include "gen/gen_ptri.h"
#include "gen/gen_object.h"

#include "radix_object.h"

#include "exception/exception.h"


#include "ca/ca_smart_pointer.h"

namespace ex1
{
   class file_exception;         // file exception
   class file;
   typedef ca::smart_pointer < file_exception > file_exception_sp;
   typedef ca::smart_pointer < file > filesp;
}


#define ASSERT_KINDOF(class_name, object) ASSERT(base < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(AfxStaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(AfxStaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))

// optional bit for schema number that enables object versioning
#define VERSIONABLE_SCHEMA  (0x80000000)

/////////////////////////////////////////////////////////////////////////////
// other helpers

// zero fill everything after the vtbl pointer
#define AFX_ZERO_INIT_OBJECT(base_class) memset(((base_class*)this)+1, 0, sizeof(*this) - sizeof(class base_class));


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _AFX_ENABLE_INLINES
#define _AFX_INLINE inline

#if !defined(_AFX_CORE_IMPL) || !defined(_ApplicationFrameworkDLL) || defined(_DEBUG)
#define _AFX_PUBLIC_INLINE inline
#else
#define _AFX_PUBLIC_INLINE
#endif

#endif

#include "inline.h"


#undef AFX_DATA
#define AFX_DATA CLASS_DECL_ca


#ifdef _AFX_ALL_WARNINGS
#pragma warning( pop )
#endif



#include "allocate.h"

#include "pointer_object.h"
#include "plex.h"

#include "collection/collection.h"
#include "template/template.h"

#include "ca/ca_interlocked_long.h"
#include "ca/ca_interlocked_long_pulse.h"

#include "ca/ca_data.h"
#include "ca/ca_data_container.h"
#include "ca/ca_data_listener.h"

#include "ca/ca_type_info.h"
#include "factory.h"

