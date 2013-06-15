#pragma once


typedef int_ptr strsize;


CLASS_DECL_ca void strcat_dup(char * dest, const char * cat);
CLASS_DECL_ca void strcpy_dup(char * dest, const char * cat);
CLASS_DECL_ca void strncpy_dup(char * dest, const char * cat, strsize iLen);
CLASS_DECL_ca ::count strlen_dup(const char * cat);
CLASS_DECL_ca char * strdup_dup(const char * src);
CLASS_DECL_ca char * strndup_dup(const char * src, strsize iLen);
CLASS_DECL_ca char * strstr_dup(const char * src, const char * find);
CLASS_DECL_ca char * stristr_dup(const char * src, const char * find);
CLASS_DECL_ca char * strnstr_dup(const char * src, const char * find, strsize iLen);
CLASS_DECL_ca char * strnistr_dup(const char * src, const char * find, strsize iLen);
CLASS_DECL_ca int32_t stricmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_ca int32_t strcmp_dup(const char * sz1, const char * sz2);
CLASS_DECL_ca int32_t strnicmp_dup(const char * sz1, const char * sz2, strsize iLen);
CLASS_DECL_ca int32_t strncmp_dup(const char * sz1, const char * sz2, strsize iLen);
CLASS_DECL_ca char * str_begins_inc_dup(const char * sz1, const char * prefix);
CLASS_DECL_ca int32_t str_begins_dup(const char * sz1, const char * prefix);
CLASS_DECL_ca int32_t str_ends_dup(const char * sz1, const char * suffix);
CLASS_DECL_ca int32_t str_begins_ci_dup(const char * sz1, const char * prefix);
CLASS_DECL_ca char * strrchr_dup(char * sz, char ch);


CLASS_DECL_ca void uitoa_dup(char * sz, uint64_t i, int32_t iBase);
CLASS_DECL_ca void itoa_dup(char * sz, int64_t i, int32_t iBase);


//CLASS_DECL_ca void l64toa_dup(char * sz, int64_t i, int64_t iBase);
//CLASS_DECL_ca void i64toa_dup(char * sz, int64_t i);
CLASS_DECL_ca void str_reverse(char * sz);
CLASS_DECL_ca void zero_pad(char * sz, ::count iPad);
CLASS_DECL_ca int32_t str_ends_ci_dup(const char * psz, const char * pszSuffix);
CLASS_DECL_ca char * strchr_dup(const char * sz, char ch);
CLASS_DECL_ca char * strpbrk_dup(char * sz, const char * szFind);

CLASS_DECL_ca char to_lower(int32_t ch);
CLASS_DECL_ca char * to_lower(char * pch);
CLASS_DECL_ca int32_t isdigit_dup(int32_t ch);
CLASS_DECL_ca int32_t isxdigit_dup(int32_t ch);
CLASS_DECL_ca int32_t isalpha_dup(int32_t ch);
CLASS_DECL_ca int32_t isspace_dup(int32_t ch);

#if defined(LINUX)

CLASS_DECL_ca char * strlwr(char * psz);
CLASS_DECL_ca char * strupr(char * psz);

#endif

CLASS_DECL_ca void wcscat_dup(wchar_t * dest, const wchar_t * cat);
CLASS_DECL_ca void wcscpy_dup(wchar_t * dest, const wchar_t * src);
CLASS_DECL_ca void wcsncpy_dup(wchar_t * dest, const wchar_t * src, strsize n);
CLASS_DECL_ca int32_t iswalnum_dup(int32_t wch);
CLASS_DECL_ca ::count wcslen_dup(const wchar_t * pwsz);
CLASS_DECL_ca wchar_t * wcschr_dup(const wchar_t * sz, wchar_t ch);
CLASS_DECL_ca int32_t wcscmp_dup(const wchar_t * sz1, const wchar_t * sz2);
CLASS_DECL_ca int32_t wcsicmp_dup(const wchar_t * sz1, const wchar_t * sz2);


CLASS_DECL_ca void uitow_dup(wchar_t * sz, uint64_t i, int32_t iBase);
CLASS_DECL_ca void itow_dup(wchar_t * sz, int64_t i, int32_t iBase);


//CLASS_DECL_ca void l64toa_dup(char * sz, int64_t i, int64_t iBase);
//CLASS_DECL_ca void i64toa_dup(char * sz, int64_t i);
CLASS_DECL_ca void wcs_reverse(wchar_t * sz);
CLASS_DECL_ca void w_zero_pad(char * sz, strsize iPad);


CLASS_DECL_ca wchar_t w_to_lower(int32_t wch);
CLASS_DECL_ca wchar_t w_to_upper(int32_t wch);

CLASS_DECL_ca errno_t wcslwr_s_dup(wchar_t * sz, strsize size);
CLASS_DECL_ca errno_t wcsupr_s_dup(wchar_t * sz, strsize size);

CLASS_DECL_ca int32_t iswalpha_dup(int32_t ch);
CLASS_DECL_ca int32_t iswdigit_dup(int32_t ch);
CLASS_DECL_ca int32_t iswspace_dup(int32_t ch);


CLASS_DECL_ca void __cdecl wparse_cmdline(WCHAR *cmdstart, WCHAR **argv, WCHAR *args, int32_t * numargs, int32_t * numchars);
CLASS_DECL_ca void __cdecl parse_cmdline(char *cmdstart, char **argv, char *args, int32_t * numargs, int32_t * numchars);

CLASS_DECL_ca char * strtok_r_dup(char *s1, const char *s2, char **lasts);

CLASS_DECL_ca ::count utf16_len(const char * psz);
CLASS_DECL_ca void utf8_to_16(wchar_t * pwsz, const char * psz);
CLASS_DECL_ca wchar_t * utf8_to_16(const char * psz);
CLASS_DECL_ca char * utf16_to_8(const wchar_t * psz);




#if defined(LINUX)

#define _strdup strdup

#endif



inline size_t safe_strlen(const char * psz)
{
   if(psz == NULL || *psz == '\0')
      return 0;
   return strlen_dup(psz);
}




CLASS_DECL_ca bool matches_wildcard_criteria(const char * pszCriteria, const char * pszValue);
CLASS_DECL_ca bool matches_wildcard_criteria_ci(const char * pszCriteria, const char * pszValue);


