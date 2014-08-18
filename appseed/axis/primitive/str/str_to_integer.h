#pragma once


CLASS_DECL_AXIS int32_t atoi_dup(const char * sz, const char ** pszEnd, int32_t iAxis);
CLASS_DECL_AXIS int32_t atoi_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_AXIS int32_t atoi_dup(const char * sz);

CLASS_DECL_AXIS uint32_t atoui_dup(const char * sz, const char ** pszEnd, int32_t iAxis);
CLASS_DECL_AXIS uint32_t atoui_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_AXIS uint32_t atoui_dup(const char * sz);

CLASS_DECL_AXIS int32_t natoi_dup(const char * sz, const char ** pszEnd, int32_t iAxis, size_t iLen);
CLASS_DECL_AXIS int32_t natoi_dup(const char * sz, const char ** pszEnd, size_t iLen);
CLASS_DECL_AXIS int32_t natoi_dup(const char * sz, size_t iLen);




CLASS_DECL_AXIS int32_t wtoi_dup(const wchar_t * sz);
CLASS_DECL_AXIS int32_t nwtoi_dup(const wchar_t * sz, int32_t iCount);



CLASS_DECL_AXIS int64_t atoi64_dup(const char * sz, char ** pszEnd, int32_t iAxis);
CLASS_DECL_AXIS int64_t atoi64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_AXIS int64_t atoi64_dup(const char * sz);

CLASS_DECL_AXIS uint64_t atoui64_dup(const char * sz, char ** pszEnd, int32_t iAxis);
CLASS_DECL_AXIS uint64_t atoui64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_AXIS uint64_t atoui64_dup(const char * sz);


CLASS_DECL_AXIS int64_t natoi64_dup(const char * sz, char ** pszEnd, int32_t iAxis, size_t iLen);
CLASS_DECL_AXIS int64_t natoi64_dup(const char * sz, char ** pszEnd, size_t iLen);
CLASS_DECL_AXIS int64_t natoi64_dup(const char * sz, size_t iLen);


#if defined(LINUX)

#define _strtoi64 atoi64_dup

#endif


CLASS_DECL_AXIS int64_t wtoi64_dup(const wchar_t * sz, const wchar_t ** pszEnd, int32_t iAxis);
CLASS_DECL_AXIS int64_t wtoi64_dup(const wchar_t * sz, const wchar_t ** pszEnd);
CLASS_DECL_AXIS int64_t wtoi64_dup(const wchar_t * sz);
