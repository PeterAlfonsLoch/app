#pragma once


CLASS_DECL_c void * memset_dup(void * p, int32_t uch, size_t iSize);
CLASS_DECL_c void * memand_dup(void * p, const void * p1, const void * p2, size_t iSize);
CLASS_DECL_c void * memcpy_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_c void * memmov_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_c int32_t  memcmp_dup(const void * sz1, const void * sz2, size_t iSize);
CLASS_DECL_c wchar_t * wmemcpy_dup(wchar_t * dst, const wchar_t * src, size_t iSize);

CLASS_DECL_c void * mem_reverse(void * p, size_t iSize);

inline void * zero_memory_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zeroe_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero_dup(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero_memory(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zeroe(void * p, size_t iSize) { memset(p, 0, iSize); return p; }
inline void * zero(void * p, size_t iSize) { memset(p, 0, iSize); return p; }

inline bool is_zero(void * p, size_t iSize)
{ 
   byte * pb = (byte *) p; 
   while(*pb == '\0' && iSize > 0)
   {
      pb++; 
      iSize--;
   }
   return iSize == 0;
}


#define ZEROP(px) zero(px, sizeof(*px));
#define ZERO(x) zero(&x, sizeof(x));
#define IS_ZEROP(px) (is_zero(px, sizeof(*px)))
#define IS_ZERO(x) (is_zero(&x, sizeof(x)))
#define ISNT_ZEROP(px) (!IS_ZEROP(px))
#define ISNT_ZERO(x) (!IS_ZERO(x))



