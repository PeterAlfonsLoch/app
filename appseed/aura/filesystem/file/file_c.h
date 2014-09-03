#pragma once



#if defined(METROWIN) || defined(APPLEOS) || defined(CUBE)

#define MATTER_CACHE_FROM_HTTP_SERVER

#endif




BEGIN_EXTERN_C


typedef uint64_t  file_size;
typedef uint64_t  file_position;
typedef int64_t   file_offset;

CLASS_DECL_AURA int_bool file_path_is_relative_dup(const char * psz);



CLASS_DECL_AURA int_bool file_exists_dup(const char * path1);
#ifdef WINDOWS
CLASS_DECL_AURA int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif
//CLASS_DECL_AURA int_bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents, count len);
//CLASS_DECL_AURA int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_AURA int_bool get_temp_file_name_template(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_AURA uint64_t file_length_dup(const char * path);



CLASS_DECL_AURA int_bool file_is_equal_path_dup(const char * pszPath1, const char * pszPath2);


CLASS_DECL_AURA int_bool file_ftd_dup(const char * pszDir, const char * pszFile);



CLASS_DECL_AURA int_bool file_copy_dup(const char * pszDup, const char * pszSrc, int_bool bOverwrite);


//CLASS_DECL_AURA void sprint_hex(char * sz, int32_t iValue);

typedef HANDLE handle;

CLASS_DECL_AURA handle create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_AURA int_bool close_handle(handle h);




#ifdef WINDOWS

struct CLASS_DECL_AURA _struct_FILE
{
   char *_ptr;
   int32_t   _cnt;
   char *_base;			//	Used to store HANDLE
   int32_t   _flag;
   int32_t   _file;
   int32_t   _charbuf;
   int32_t   _bufsiz;
   char *_tmpfname;
   int32_t   _err;
};

#define _FILE struct _struct_FILE

#define EOF (-1)
#define _FILE_TEXT		0x0001
#define _FILE_EOF		0x0002
#define _FILE_ERROR		0x0004


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  (&__iob_func_dup()[0])
#define stdout_dup (&__iob_func_dup()[1])
#define stderr_dup (&__iob_func_dup()[2])
#define _STDSTREAM_DUP_DEFINED
#endif
CLASS_DECL_AURA _FILE *__iob_func_dup();

#else
#define _FILE FILE


#define EOF (-1)
#define _FILE_TEXT		FILE_TEXT
#define _FILE_EOF		FILE_EOF
#define _FILE_ERROR		FILE_ERROR


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  stdin
#define stdout_dup stdout
#define stderr_dup stderr
#define _STDSTREAM_DUP_DEFINED
#endif

#endif


CLASS_DECL_AURA void _init_file_dup();

CLASS_DECL_AURA _FILE * fopen_dup(const char *path, const char *attrs);
CLASS_DECL_AURA int32_t fprintf_dup(_FILE *fp, const char *s, ...);
CLASS_DECL_AURA int32_t fclose_dup(_FILE *fp);
CLASS_DECL_AURA int32_t feof_dup(_FILE *fp);
CLASS_DECL_AURA file_position fseek_dup(_FILE *str, file_offset offset, int32_t origin);
CLASS_DECL_AURA long ftell_dup(_FILE *fp);
CLASS_DECL_AURA size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_AURA size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_AURA char *fgets_dup(char *str, int32_t n, _FILE *s);
CLASS_DECL_AURA int32_t fgetc_dup(_FILE *s);
CLASS_DECL_AURA int32_t ungetc_dup(int32_t c,_FILE *s);
CLASS_DECL_AURA int32_t ferror_dup(_FILE *s);
CLASS_DECL_AURA int32_t fflush_dup(_FILE *s);
CLASS_DECL_AURA uint64_t flen_dup(_FILE *s);


#ifdef WINDOWS
CLASS_DECL_AURA _FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs);
CLASS_DECL_AURA int32_t fwprintf_dup(_FILE *fp, const wchar_t *s, ...);
CLASS_DECL_AURA wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s);
CLASS_DECL_AURA wint_t fgetwc_dup(_FILE *s);
CLASS_DECL_AURA wint_t ungetwc_dup(wint_t w, _FILE *s);
#endif


#ifdef WINDOWS
uint64_t fsize_dup(HANDLE h);
#else
uint64_t fsize_dup(FILE * fp);
#endif

END_EXTERN_C



//   #pragma once



//typedef uint64_t  file_size;
//typedef uint64_t  file_position;
//typedef int64_t   file_offset;





CLASS_DECL_AURA int_bool file_exists_dup(const char * path1);

#ifdef WINDOWS
CLASS_DECL_AURA int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif

//CLASS_DECL_AURA int_bool is_file_ok(const char * path1, const char * pszTemplate);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents, count len);
//CLASS_DECL_AURA int_bool get_temp_file_name_dup(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension);
CLASS_DECL_AURA int_bool get_temp_file_name_template(char * szRet, count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate);
CLASS_DECL_AURA uint64_t file_length_dup(const char * path);



CLASS_DECL_AURA int_bool file_is_equal_path(const char * pszPath1, const char * pszPath2);


CLASS_DECL_AURA int_bool file_ftd_dup(const char * pszDir, const char * pszFile);

CLASS_DECL_AURA int_bool file_copy_dup(const char * pszDup, const char * pszSrc, int_bool bOverwrite);


//CLASS_DECL_AURA void sprint_hex(char * sz, int32_t iValue);




//typedef HANDLE handle;

CLASS_DECL_AURA handle create_file(const char * lpcszFileName, dword dwDesiredAcces, dword dwShareMode, LPSECURITY_ATTRIBUTES lpSA, dword dwCreationDisposition, dword dwFlagsAndAttributes, HANDLE hTemplateFile);
CLASS_DECL_AURA int_bool close_handle(handle h);


BEGIN_EXTERN_C


#ifdef WINDOWS

   /*
struct CLASS_DECL_AURA _struct_FILE
{
   char *_ptr;
   int32_t   _cnt;
   char *_base;			//	Used to store HANDLE
   int32_t   _flag;
   int32_t   _file;
   int32_t   _charbuf;
   int32_t   _bufsiz;
   char *_tmpfname;
   int32_t   _err;
};
*/

#define _FILE struct _struct_FILE

#define EOF (-1)
#define _FILE_TEXT		0x0001
#define _FILE_EOF		0x0002
#define _FILE_ERROR		0x0004


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  (&__iob_func_dup()[0])
#define stdout_dup (&__iob_func_dup()[1])
#define stderr_dup (&__iob_func_dup()[2])
#define _STDSTREAM_DUP_DEFINED
#endif
CLASS_DECL_AURA _FILE *__iob_func_dup();

#else
#define _FILE FILE


#define EOF (-1)
#define _FILE_TEXT		FILE_TEXT
#define _FILE_EOF		FILE_EOF
#define _FILE_ERROR		FILE_ERROR


#ifndef _STDSTREAM_DUP_DEFINED
#define stdin_dup  stdin
#define stdout_dup stdout
#define stderr_dup stderr
#define _STDSTREAM_DUP_DEFINED
#endif

#endif


CLASS_DECL_AURA void _init_file();

CLASS_DECL_AURA _FILE * fopen_dup(const char *path, const char *attrs);
CLASS_DECL_AURA int32_t fprintf_dup(_FILE *fp, const char *s, ...);
CLASS_DECL_AURA int32_t fclose_dup(_FILE *fp);
CLASS_DECL_AURA int32_t feof_dup(_FILE *fp);
CLASS_DECL_AURA file_position fseek_dup(_FILE *str, file_offset offset, int32_t origin);
CLASS_DECL_AURA long ftell_dup(_FILE *fp);
CLASS_DECL_AURA size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_AURA size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_AURA char *fgets_dup(char *str, int32_t n, _FILE *s);
CLASS_DECL_AURA int32_t fgetc_dup(_FILE *s);
CLASS_DECL_AURA int32_t ungetc_dup(int32_t c,_FILE *s);
CLASS_DECL_AURA int32_t ferror_dup(_FILE *s);
CLASS_DECL_AURA int32_t fflush_dup(_FILE *s);


#ifdef WINDOWS
CLASS_DECL_AURA _FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs);
CLASS_DECL_AURA int32_t fwprintf_dup(_FILE *fp, const wchar_t *s, ...);
CLASS_DECL_AURA wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s);
CLASS_DECL_AURA wint_t fgetwc_dup(_FILE *s);
CLASS_DECL_AURA wint_t ungetwc_dup(wint_t w, _FILE *s);
#endif


#ifdef WINDOWS
uint64_t fsize_dup(HANDLE h);
#else
uint64_t fsize_dup(FILE * fp);
#endif

END_EXTERN_C



#ifdef __cplusplus


namespace primitive
{


   class memory_base;


} // namespace primitive


CLASS_DECL_AURA bool file_put_contents_dup(const char * path, const ::primitive::memory_base & memory);
CLASS_DECL_AURA int_bool file_put_contents_dup(const char * path, const char * contents);
CLASS_DECL_AURA bool file_get_memory_dup(::primitive::memory_base & memory, const char * path);


namespace md5
{


   class md5;


} // namespace md5


#ifdef WINDOWS
CLASS_DECL_AURA void file_read_n_number_dup(HANDLE hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_AURA void file_read_gen_string_dup(HANDLE hfile, ::md5::md5 * pctx, string & str);
#else
CLASS_DECL_AURA void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int32_t & iNumber);
CLASS_DECL_AURA void file_read_gen_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);
#endif


template < typename N > class numeric_array;
typedef CLASS_DECL_AURA numeric_array < uint32_t > uint_array;
class stringa;

#ifndef METROWIN
CLASS_DECL_AURA bool PrintModules(string & strImage, uint32_t processID, const char * pszDll );
CLASS_DECL_AURA void dll_processes(uint_array & dwa, stringa & straProcesses, const char * pszDll);
#endif

CLASS_DECL_AURA string file_title_dup(const char * path);
CLASS_DECL_AURA string file_name_dup(const char * path);
CLASS_DECL_AURA string file_module_path_dup();

CLASS_DECL_AURA int_bool file_copy_dup(const char * pszDup, const char * pszSrc); // , bool bOverwrite = true);

CLASS_DECL_AURA string get_sys_temp_path();

CLASS_DECL_AURA string file_get_mozilla_firefox_plugin_container_path();



#endif



CLASS_DECL_AURA int_bool file_set_length(const char * pszName, size_t iSize);


CLASS_DECL_AURA int_bool file_move_dup(const char * lpszNewName,const char * lpszOldName);
CLASS_DECL_AURA int_bool file_delete_dup(const char * lpszFileName);


