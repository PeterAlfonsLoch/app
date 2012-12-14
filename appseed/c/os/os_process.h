#pragma once


#if !defined(METROWIN)

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
   int (* pfnOnRetry)(int iTry, dword_ptr dwParam),
   dword_ptr dwParam);

#endif


#if !defined(METROWIN) && !defined(LINUX) && !defined(MACOS)

CLASS_DECL_c int get_current_processor_index();

CLASS_DECL_c int get_current_process_maximum_affinity();

CLASS_DECL_c int get_current_process_affinity_order();

#endif




CLASS_DECL_c vsstring consume_param(const char * pszCommandLine, const char ** pszEndPtr);
CLASS_DECL_c vsstring get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam);
CLASS_DECL_c vsstring get_command_line_param(const char * pszCommandLine, const char * pszParam);



