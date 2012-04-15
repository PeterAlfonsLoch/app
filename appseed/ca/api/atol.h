#pragma once


CLASS_DECL_ca int64_t atoi64_dup(const char * sz, const char ** pszEnd, int iBase);
CLASS_DECL_ca int64_t atoi64_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_ca int64_t atoi64_dup(const char * sz);

CLASS_DECL_ca int64_t natoi64_dup(const char * sz, const char ** pszEnd, int iBase, int iLen);
CLASS_DECL_ca int64_t natoi64_dup(const char * sz, const char ** pszEnd, int iLen);
CLASS_DECL_ca int64_t natoi64_dup(const char * sz, int iLen);
