#pragma once


CLASS_DECL_c int atoi_dup(const char * sz, const char ** pszEnd, int iBase);
CLASS_DECL_c int atoi_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_c int atoi_dup(const char * sz);


CLASS_DECL_c int natoi_dup(const char * sz, const char ** pszEnd, int iBase, int iLen);
CLASS_DECL_c int natoi_dup(const char * sz, const char ** pszEnd, int iLen);
CLASS_DECL_c int natoi_dup(const char * sz, int iLen);




CLASS_DECL_c int wtoi_dup(const wchar_t * sz);
CLASS_DECL_c int nwtoi_dup(const wchar_t * sz, int iCount);
