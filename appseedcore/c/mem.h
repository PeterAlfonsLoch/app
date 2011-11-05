#pragma once


CLASS_DECL_____ void * memset_dup(void * p, int uch, size_t iSize);
CLASS_DECL_____ void * memcpy_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_____ void * memmov_dup(void * dst, const void * src, size_t iSize);
CLASS_DECL_____ int  memcmp_dup(const void * sz1, const void * sz2, size_t iSize);

CLASS_DECL_____ wchar_t * wmemcpy_dup(wchar_t * dst, const wchar_t * src, size_t iSize);


