#pragma once


CLASS_DECL_ACE int32_t atoi_dup(const char * sz, const char ** pszEnd, int32_t iBase);
CLASS_DECL_ACE int32_t atoi_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_ACE int32_t atoi_dup(const char * sz);

CLASS_DECL_ACE uint32_t atoui_dup(const char * sz, const char ** pszEnd, int32_t iBase);
CLASS_DECL_ACE uint32_t atoui_dup(const char * sz, const char ** pszEnd);
CLASS_DECL_ACE uint32_t atoui_dup(const char * sz);

CLASS_DECL_ACE int32_t natoi_dup(const char * sz, const char ** pszEnd, int32_t iBase, size_t iLen);
CLASS_DECL_ACE int32_t natoi_dup(const char * sz, const char ** pszEnd, size_t iLen);
CLASS_DECL_ACE int32_t natoi_dup(const char * sz, size_t iLen);




CLASS_DECL_ACE int32_t wtoi_dup(const unichar * sz);
CLASS_DECL_ACE int32_t nwtoi_dup(const unichar * sz, int32_t iCount);



CLASS_DECL_ACE int64_t atoi64_dup(const char * sz, char ** pszEnd, int32_t iBase);
CLASS_DECL_ACE int64_t atoi64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_ACE int64_t atoi64_dup(const char * sz);

CLASS_DECL_ACE uint64_t atoui64_dup(const char * sz, char ** pszEnd, int32_t iBase);
CLASS_DECL_ACE uint64_t atoui64_dup(const char * sz, char ** pszEnd);
CLASS_DECL_ACE uint64_t atoui64_dup(const char * sz);


CLASS_DECL_ACE int64_t natoi64_dup(const char * sz, char ** pszEnd, int32_t iBase, size_t iLen);
CLASS_DECL_ACE int64_t natoi64_dup(const char * sz, char ** pszEnd, size_t iLen);
CLASS_DECL_ACE int64_t natoi64_dup(const char * sz, size_t iLen);


#if defined(LINUX)

#define _strtoi64 atoi64_dup

#endif


CLASS_DECL_ACE int64_t wtoi64_dup(const unichar * sz, const unichar ** pszEnd, int32_t iBase);
CLASS_DECL_ACE int64_t wtoi64_dup(const unichar * sz, const unichar ** pszEnd);
CLASS_DECL_ACE int64_t wtoi64_dup(const unichar * sz);


#ifdef __cplusplus
inline void atoui_dup(uint32_t & ui,const char * psz) { ui = atoui_dup(psz); }
inline void atoui_dup(uint64_t & ui,const char * psz) { ui = atoui64_dup(psz); }
inline uint_ptr atouiptr_dup(const char * psz) { uint_ptr ui; atoui_dup(ui,psz); return ui; }

#endif