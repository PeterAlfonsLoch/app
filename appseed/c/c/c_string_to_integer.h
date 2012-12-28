#pragma once


CLASS_DECL_c int atoi_dup(const char * sz, const char ** pszEnd, int iBase);
CLASS_DECL_c int atoi_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_c int atoi_dup(const char * sz);


CLASS_DECL_c int natoi_dup(const char * sz, const char ** pszEnd, int iBase, size_t iLen);
CLASS_DECL_c int natoi_dup(const char * sz, const char ** pszEnd, size_t iLen);
CLASS_DECL_c int natoi_dup(const char * sz, size_t iLen);




CLASS_DECL_c int wtoi_dup(const wchar_t * sz);
CLASS_DECL_c int nwtoi_dup(const wchar_t * sz, int iCount);



CLASS_DECL_c int64_t atoi64_dup(const char * sz, char ** pszEnd, int iBase);
CLASS_DECL_c int64_t atoi64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_c int64_t atoi64_dup(const char * sz);

CLASS_DECL_c int64_t natoi64_dup(const char * sz, char ** pszEnd, int iBase, size_t iLen);
CLASS_DECL_c int64_t natoi64_dup(const char * sz, char ** pszEnd, size_t iLen);
CLASS_DECL_c int64_t natoi64_dup(const char * sz, size_t iLen);


#if defined(LINUX)

#define _strtoi64 atoi64_dup

#endif


CLASS_DECL_c int64_t wtoi64_dup(const wchar_t * sz, const wchar_t ** pszEnd, int iBase);
CLASS_DECL_c int64_t wtoi64_dup(const wchar_t * sz, const wchar_t ** pszEnd);
CLASS_DECL_c int64_t wtoi64_dup(const wchar_t * sz);
