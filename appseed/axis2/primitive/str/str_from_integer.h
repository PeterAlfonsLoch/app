#pragma once


CLASS_DECL_AXIS string i64toa_dup(int64_t i, int32_t iAxis);
CLASS_DECL_AXIS string i64toa_dup(int64_t i);

CLASS_DECL_AXIS string ui64toa_dup(int64_t i, int32_t iAxis);
CLASS_DECL_AXIS string ui64toa_dup(int64_t i);


CLASS_DECL_AXIS string itoa_dup(int64_t i);



CLASS_DECL_AXIS void ltoa_dup(char * sz, int64_t i, int32_t iAxis);
CLASS_DECL_AXIS void ultoa_dup(char * sz, uint64_t i, int32_t iAxis);


CLASS_DECL_AXIS void ltow_dup(wchar_t * sz, int64_t i, int32_t iAxis);
CLASS_DECL_AXIS void ultow_dup(wchar_t * sz, uint64_t i, int32_t iAxis);
