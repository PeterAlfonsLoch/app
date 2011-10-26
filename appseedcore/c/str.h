#pragma once

CLASS_DECL_____ void strcat_dup(char * dest, const char * cat);
CLASS_DECL_____ void strcpy_dup(char * dest, const char * cat);
CLASS_DECL_____ void strncpy_dup(char * dest, const char * cat, int iLen);
CLASS_DECL_____ int  strlen_dup(const char * cat);
CLASS_DECL_____ char * strdup_dup(const char * src);
CLASS_DECL_____ char * strndup_dup(const char * src, int iLen);
CLASS_DECL_____ char * strstr_dup(const char * src, const char * find);
CLASS_DECL_____ char * stristr_dup(const char * src, const char * find);
CLASS_DECL_____ int stricmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_____ int strcmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_____ int strnicmp_dup(const char * sz1, const char * sz2, int iLen);
CLASS_DECL_____ int strncmp_dup(const char * sz1, const char * sz2, int iLen);
CLASS_DECL_____ char * str_begins_inc_dup(const char * sz1, const char * prefix);
CLASS_DECL_____ int str_begins_dup(const char * sz1, const char * prefix);
CLASS_DECL_____ int str_begins_ci_dup(const char * sz1, const char * prefix);
CLASS_DECL_____ char * strrchr_dup(char * sz, char ch);


CLASS_DECL_____ void uitoa_dup(char * sz, unsigned int i, int iBase);
CLASS_DECL_____ void itoa_dup(char * sz, int i, int iBase);


//CLASS_DECL_____ void l64toa_dup(char * sz, __int64 i, __int64 iBase);
//CLASS_DECL_____ void i64toa_dup(char * sz, __int64 i);
CLASS_DECL_____ void str_reverse(char * sz);
CLASS_DECL_____ void zero_pad(char * sz, int iPad);
CLASS_DECL_____ int str_ends_ci_dup(const char * psz, const char * pszSuffix);
CLASS_DECL_____ char * strchr_dup(const char * sz, char ch);
CLASS_DECL_____ char * strpbrk_dup(char * sz, const char * szFind);

CLASS_DECL_____ char to_lower(int ch);
CLASS_DECL_____ char * to_lower(char * pch);
CLASS_DECL_____ int isdigit_dup(int ch);
CLASS_DECL_____ int isalpha_dup(int ch);
CLASS_DECL_____ int isspace_dup(int ch);

CLASS_DECL_____ void wcscat_dup(wchar_t * dest, const wchar_t * cat);
CLASS_DECL_____ void wcscpy_dup(wchar_t * dest, const wchar_t * src);
CLASS_DECL_____ int iswalnum_dup(int wch);
CLASS_DECL_____ int wcslen_dup(const wchar_t * pwsz);
CLASS_DECL_____ wchar_t * wcschr_dup(const wchar_t * sz, wchar_t ch);
CLASS_DECL_____ int wcsicmp_dup(const wchar_t * sz1, const wchar_t * sz2);
CLASS_DECL_____ wchar_t w_to_lower(int wch);

CLASS_DECL_____ int iswalpha_dup(int ch);
CLASS_DECL_____ int iswdigit_dup(int ch);
CLASS_DECL_____ int iswspace_dup(int ch);


CLASS_DECL_____ void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, int * numargs, int * numchars);
CLASS_DECL_____ void __cdecl parse_cmdline(char *cmdstart, char **argv, char *args, int * numargs, int * numchars);

CLASS_DECL_____ char * strtok_r_dup(char *s1, const char *s2, char **lasts);


CLASS_DECL_____ wchar_t * utf8_to_16(const char * psz);
CLASS_DECL_____ char * utf16_to_8(const wchar_t * psz);
