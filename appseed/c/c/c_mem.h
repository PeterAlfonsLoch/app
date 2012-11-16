#pragma once


CLASS_DECL_c void * memset_dup(void * p, int uch, size_t iSize);
CLASS_DECL_c void * memand_dup(void * p, const void * p1, const void * p2, size_t iSize);
CLASS_DECL_c void * memcpy_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_c void * memmov_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_c int  memcmp_dup(const void * sz1, const void * sz2, size_t iSize);
CLASS_DECL_c wchar_t * wmemcpy_dup(wchar_t * dst, const wchar_t * src, size_t iSize);

inline void * zero_memory_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zeroe_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero_memory(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zeroe(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero(void * p, size_t iSize) { memset(p, 0, iSize); return p; }



