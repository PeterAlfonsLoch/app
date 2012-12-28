#pragma once


BEGIN_EXTERN_C


#ifdef WINDOWS

struct CLASS_DECL_c _struct_FILE
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
CLASS_DECL_c _FILE *__iob_func_dup();

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


CLASS_DECL_c void _init_file_dup();

CLASS_DECL_c _FILE * fopen_dup(const char *path, const char *attrs);
CLASS_DECL_c int32_t fprintf_dup(_FILE *fp, const char *s, ...);
CLASS_DECL_c int32_t fclose_dup(_FILE *fp);
CLASS_DECL_c int32_t feof_dup(_FILE *fp);
CLASS_DECL_c int32_t fseek_dup(_FILE *str, long offset, int32_t origin);
CLASS_DECL_c long ftell_dup(_FILE *fp);
CLASS_DECL_c size_t fread_dup(void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_c size_t fwrite_dup(const void *buffer, size_t size, size_t count, _FILE *str);
CLASS_DECL_c char *fgets_dup(char *str, int32_t n, _FILE *s);
CLASS_DECL_c int32_t fgetc_dup(_FILE *s);
CLASS_DECL_c int32_t ungetc_dup(int32_t c,_FILE *s);
CLASS_DECL_c int32_t ferror_dup(_FILE *s);
CLASS_DECL_c int32_t fflush_dup(_FILE *s);


#ifdef WINDOWS
CLASS_DECL_c _FILE *_wfopen_dup(const wchar_t *path, const wchar_t *attrs);
CLASS_DECL_c int32_t fwprintf_dup(_FILE *fp, const wchar_t *s, ...);
CLASS_DECL_c wchar_t *fgetws_dup(wchar_t *str, int32_t n, _FILE *s);
CLASS_DECL_c wint_t fgetwc_dup(_FILE *s);
CLASS_DECL_c wint_t ungetwc_dup(wint_t w, _FILE *s);
#endif


#ifdef WINDOWS
uint64_t fsize_dup(HANDLE h);
#else
uint64_t fsize_dup(FILE * fp);
#endif

END_EXTERN_C

