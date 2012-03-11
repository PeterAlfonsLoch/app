#pragma once


CLASS_DECL_c int call_async(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int iShow);

CLASS_DECL_c DWORD call_sync(
   const char * pszPath, 
   const char * pszParam, 
   const char * pszDir,
   int iShow,
   int iRetry, 
   int iSleep, 
   int (* pfnOnRetry)(int iTry, DWORD_PTR dwParam),
   DWORD_PTR dwParam);


CLASS_DECL_c vsstring consume_param(const char * pszCommandLine, const char ** pszEndPtr);
