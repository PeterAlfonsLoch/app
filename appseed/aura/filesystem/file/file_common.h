#pragma once


#include "aura/primitive/primitive_memory.h"

CLASS_DECL_AURA memory file_as_memory_dup(const char * path);
CLASS_DECL_AURA memory_size_t file_as_memory_dup(const char * path, void * p, memory_size_t s);
CLASS_DECL_AURA string file_as_string_dup(const char * path);
CLASS_DECL_AURA string file_extension_dup(const char * path);
CLASS_DECL_AURA string get_temp_file_name_dup(const char * pszName, const char * pszExtension);
CLASS_DECL_AURA string file_final_extension_dup(const char * path);
CLASS_DECL_AURA string url_dir_name_for_relative(const char * pszPath);
CLASS_DECL_AURA string solve_relative_compressions(const string & str);
CLASS_DECL_AURA string defer_solve_relative_name(const char * pszRelative, const char * pszAbsolute);
CLASS_DECL_AURA string ca2_module_dup();



template < class POD >
inline bool file_put_pod(const char * path, const POD & pod)
{
   return file_put_contents_dup(path, &pod, sizeof(pod));
}



template < class POD >
inline bool file_as_pod(POD & pod, const char * path)
{
   return file_as_memory_dup(path, &pod, sizeof(pod)) == sizeof(pod);
}



CLASS_DECL_AURA bool file_copy_dup(const string & strNew, const string & strSrc, bool bOverwrite = true);


#ifdef WINDOWSEX

bool write_memory_to_file(HANDLE hFile, const void * lpBuf, memory_size_t nCount, memory_size_t * puiWritten);

#endif


#include "aura/filesystem/file/file_dir.h"