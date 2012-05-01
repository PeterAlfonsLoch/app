#pragma once


CLASS_DECL_ca int64_t atoi64_dup(const char * sz, char ** pszEnd, int iBase);
CLASS_DECL_ca int64_t atoi64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_ca int64_t atoi64_dup(const char * sz);

CLASS_DECL_ca int64_t natoi64_dup(const char * sz, char ** pszEnd, int iBase, int iLen);
CLASS_DECL_ca int64_t natoi64_dup(const char * sz, char ** pszEnd, int iLen);
CLASS_DECL_ca int64_t natoi64_dup(const char * sz, int iLen);


#if defined(LINUX)

#define _strtoi64 atoi64_dup

#endif
