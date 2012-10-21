#pragma once


class simple_memory;


CLASS_DECL_c bool file_exists_dup(const char * path1);
#ifdef WINDOWS
CLASS_DECL_c bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif
CLASS_DECL_c vsstring get_file_md5(const char * file);
CLASS_DECL_c bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_c bool file_put_contents_dup(const char * path, const char * contents, ::count len = -1);
CLASS_DECL_c bool file_put_contents_dup(const char * path, const simple_memory & memory);
CLASS_DECL_c const char * file_get_contents_dup(const char * path);
CLASS_DECL_c bool file_get_memory_dup(simple_memory & memory, const char * path);
CLASS_DECL_c bool get_temp_file_name_dup(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_c bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_c uint64_t file_length_dup(const char * path);

CLASS_DECL_c vsstring file_title_dup(const char * path);
CLASS_DECL_c vsstring file_name_dup(const char * path);
CLASS_DECL_c vsstring file_module_path_dup();


CLASS_DECL_c bool file_is_equal_path(const char * pszPath1, const char * pszPath2);


CLASS_DECL_c bool file_ftd_dup(const char * pszDir, const char * pszFile);
#ifdef WINDOWS
CLASS_DECL_c void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int & iNumber);
CLASS_DECL_c void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str);
#else
CLASS_DECL_c void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int & iNumber);
CLASS_DECL_c void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, vsstring & str);
#endif


CLASS_DECL_c bool PrintModules(vsstring & strImage, DWORD processID, const char * pszDll );
CLASS_DECL_c void dll_processes(simple_uint_array & dwa, stra_dup & straProcesses, const char * pszDll);


CLASS_DECL_c bool file_copy_dup(const char * pszDup, const char * pszSrc, bool bOverwrite = true);







CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path();


typedef HANDLE handle;

CLASS_DECL_c handle create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_c bool close_handle(handle h);