#pragma once

CLASS_DECL_c void strcat_dup(char * dest, const char * cat);
CLASS_DECL_c void strcpy_dup(char * dest, const char * cat);
CLASS_DECL_c void strncpy_dup(char * dest, const char * cat, count iLen);
CLASS_DECL_c count  strlen_dup(const char * cat);
CLASS_DECL_c char * strdup_dup(const char * src);
CLASS_DECL_c char * strndup_dup(const char * src, count iLen);
CLASS_DECL_c char * strstr_dup(const char * src, const char * find);
CLASS_DECL_c char * stristr_dup(const char * src, const char * find);
CLASS_DECL_c int stricmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_c int strcmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_c int strnicmp_dup(const char * sz1, const char * sz2, count iLen);
CLASS_DECL_c int strncmp_dup(const char * sz1, const char * sz2, count iLen);
CLASS_DECL_c char * str_begins_inc_dup(const char * sz1, const char * prefix);
CLASS_DECL_c int str_begins_dup(const char * sz1, const char * prefix);
CLASS_DECL_c int str_begins_ci_dup(const char * sz1, const char * prefix);
CLASS_DECL_c char * strrchr_dup(char * sz, char ch);


CLASS_DECL_c void uitoa_dup(char * sz, unsigned int i, int iBase);
CLASS_DECL_c void itoa_dup(char * sz, int i, int iBase);


//CLASS_DECL_c void l64toa_dup(char * sz, __int64 i, __int64 iBase);
//CLASS_DECL_c void i64toa_dup(char * sz, __int64 i);
CLASS_DECL_c void str_reverse(char * sz);
CLASS_DECL_c void zero_pad(char * sz, count iPad);
CLASS_DECL_c int str_ends_ci_dup(const char * psz, const char * pszSuffix);
CLASS_DECL_c char * strchr_dup(const char * sz, char ch);
CLASS_DECL_c char * strpbrk_dup(char * sz, const char * szFind);

CLASS_DECL_c char to_lower(int ch);
CLASS_DECL_c char * to_lower(char * pch);
CLASS_DECL_c int isdigit_dup(int ch);
CLASS_DECL_c int isalpha_dup(int ch);
CLASS_DECL_c int isspace_dup(int ch);

CLASS_DECL_c void wcscat_dup(wchar_t * dest, const wchar_t * cat);
CLASS_DECL_c void wcscpy_dup(wchar_t * dest, const wchar_t * src);
CLASS_DECL_c int iswalnum_dup(int wch);
CLASS_DECL_c count wcslen_dup(const wchar_t * pwsz);
CLASS_DECL_c wchar_t * wcschr_dup(const wchar_t * sz, wchar_t ch);
CLASS_DECL_c int wcscmp_dup(const wchar_t * sz1, const wchar_t * sz2);
CLASS_DECL_c int wcsicmp_dup(const wchar_t * sz1, const wchar_t * sz2);
CLASS_DECL_c wchar_t w_to_lower(int wch);

CLASS_DECL_c int iswalpha_dup(int ch);
CLASS_DECL_c int iswdigit_dup(int ch);
CLASS_DECL_c int iswspace_dup(int ch);


CLASS_DECL_c void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, int * numargs, int * numchars);
CLASS_DECL_c void __cdecl parse_cmdline(char *cmdstart, char **argv, char *args, int * numargs, int * numchars);

CLASS_DECL_c char * strtok_r_dup(char *s1, const char *s2, char **lasts);

CLASS_DECL_c count utf16_len(const char * psz);
CLASS_DECL_c void utf8_to_16(wchar_t * pwsz, const char * psz);
CLASS_DECL_c wchar_t * utf8_to_16(const char * psz);
CLASS_DECL_c char * utf16_to_8(const wchar_t * psz);


