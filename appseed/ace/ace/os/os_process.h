#pragma once


#if !defined(METROWIN)

CLASS_DECL_ACE int32_t call_async(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, bool bPrivileged);

typedef int32_t CALLSYNCONRETRY(int32_t iTry,uint_ptr dwParam);

typedef CALLSYNCONRETRY * PFNCALLSYNCONRETRY;

CLASS_DECL_ACE uint32_t call_sync(const char * pszPath, const char * pszParam, const char * pszDir, int32_t iShow, int32_t iRetry, int32_t iSleep,PFNCALLSYNCONRETRY pfnOnRetry, uint_ptr dwParam);

#endif


#if !defined(METROWIN) && !defined(LINUX) && !defined(APPLEOS)

CLASS_DECL_ACE int32_t get_current_processor_index();

CLASS_DECL_ACE int32_t get_current_process_maximum_affinity();

CLASS_DECL_ACE int32_t get_current_process_affinity_order();

#endif




CLASS_DECL_ACE string consume_param(const char * pszCommandLine, const char ** pszEndPtr);
CLASS_DECL_ACE string get_command_line_param(const char * pszCommandLine, const char * pszParam, const char * pszIfParamValue, const char * pszReplaceParam);
CLASS_DECL_ACE bool get_command_line_param(string & strValue, const char * pszCommandLine, const char * pszParam);
CLASS_DECL_ACE string get_command_line_param2(const char * pszCommandLine,const char * pszParam);


CLASS_DECL_ACE string time_binary_platform(string strPlatform);
CLASS_DECL_ACE string process_platform_dir_name();
CLASS_DECL_ACE string process_version_dir_name();


#if !defined(METROWIN)


CLASS_DECL_ACE string module_path_from_pid(uint32_t pid);
CLASS_DECL_ACE int_array module_path_get_pid(const char * pszModuleName);


#ifndef WINDOWS

CLASS_DECL_ACE stringa cmdline_from_pid(uint32_t pid);
CLASS_DECL_ACE int_array app_get_pid(const char * pszModuleName);


#endif


#endif



