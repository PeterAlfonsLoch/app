#pragma once

#ifdef _DEBUG
   void CLASS_DECL_ca TRACELASTERROR();
#else
   #define TRACELASTERROR() ((void)0)
#endif


CLASS_DECL_ca string FormatMessageFromSystem(DWORD dwError);