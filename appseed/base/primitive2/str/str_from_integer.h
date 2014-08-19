#pragma once


CLASS_DECL_BASE string i64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_BASE string i64toa_dup(int64_t i);

CLASS_DECL_BASE string ui64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_BASE string ui64toa_dup(int64_t i);


CLASS_DECL_BASE string itoa_dup(int64_t i);



CLASS_DECL_BASE void ltoa_dup(char * sz, int64_t i, int32_t iBase);
CLASS_DECL_BASE void ultoa_dup(char * sz, uint64_t i, int32_t iBase);


CLASS_DECL_BASE void ltow_dup(wchar_t * sz, int64_t i, int32_t iBase);
CLASS_DECL_BASE void ultow_dup(wchar_t * sz, uint64_t i, int32_t iBase);
