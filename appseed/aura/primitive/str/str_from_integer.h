#pragma once


CLASS_DECL_AURA string i64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_AURA string i64toa_dup(int64_t i);

CLASS_DECL_AURA string ui64toa_dup(int64_t i, int32_t iBase);
CLASS_DECL_AURA string ui64toa_dup(int64_t i);


CLASS_DECL_AURA string itoa_dup(int64_t i);



CLASS_DECL_AURA void ltoa_dup(char * sz, int64_t i, int32_t iBase);
CLASS_DECL_AURA void ultoa_dup(char * sz, uint64_t i, int32_t iBase);


CLASS_DECL_AURA void ltow_dup(unichar * sz, int64_t i, int32_t iBase);
CLASS_DECL_AURA void ultow_dup(unichar * sz, uint64_t i, int32_t iBase);
