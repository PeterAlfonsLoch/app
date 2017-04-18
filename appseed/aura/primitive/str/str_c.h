#pragma once


#include "str_str1.h"


#ifdef __cplusplus


#include "str_stdstring.h"


#include "str_wstring.h"


#include "str_wtostring.h"


#include "str_to_integer.h"



#endif

#ifdef __cplusplus

CLASS_DECL_AURA unichar32 * utf16_to_utf32(const unichar * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf16_to_utf32(unichar32 * pwsz, const unichar * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf16_to_utf32_len(const unichar * pcwsz, strsize input_size = -1);

CLASS_DECL_AURA unichar32 * utf8_to_utf32(const char * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf8_to_utf32(unichar32 * pwsz, const char * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf8_to_utf32_len(const char * pcwsz, strsize input_size = -1);

CLASS_DECL_AURA wstring utf32_to_utf16(const unichar32 * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf32_to_utf16(unichar * pwsz, const unichar32 * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf32_to_utf16_len(const unichar32 * pcwsz, strsize input_size = -1);

CLASS_DECL_AURA string utf32_to_utf8(const unichar32 * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf32_to_utf8(char * pwsz, const unichar32 * pcwsz, strsize input_size = -1);
CLASS_DECL_AURA strsize utf32_to_utf8_len(const unichar32 * pcwsz, strsize input_size = -1);

CLASS_DECL_AURA string w_to_8(const wchar_t * pcwsz, strsize input_size = -1);


#else

CLASS_DECL_AURA strsize utf16_to_utf32(unichar32 * pwsz, const unichar * pcwsz, strsize input_size);
CLASS_DECL_AURA strsize utf16_to_utf32_len(const unichar * pcwsz, strsize input_size);

CLASS_DECL_AURA strsize utf8_to_utf32(unichar32 * pwsz, const char * pcwsz, strsize input_size);
CLASS_DECL_AURA strsize utf8_to_utf32_len(const char * pcwsz, strsize input_size);

CLASS_DECL_AURA strsize utf32_to_utf16(unichar * pwsz, const unichar32 * pcwsz, strsize input_size);
CLASS_DECL_AURA strsize utf32_to_utf16_len(const unichar32 * pcwsz, strsize input_size);

CLASS_DECL_AURA strsize utf32_to_utf8(char * pwsz, const unichar32 * pcwsz, strsize input_size);
CLASS_DECL_AURA strsize utf32_to_utf8_len(const unichar32 * pcwsz, strsize input_size);

#endif

#ifdef WINDOWS
#define unincpy wcsncpy
#else
#define unincpy wcsncpy_dup
#endif

BEGIN_EXTERN_C

CLASS_DECL_AURA char * c_utf8_str(const wchar_t * str);
CLASS_DECL_AURA wchar_t * c_wide_str(const char * str);

CLASS_DECL_AURA int is_surrogated(uint32_t ui);
CLASS_DECL_AURA int is_surrogate(unichar uc);
CLASS_DECL_AURA int is_high_surrogate(unichar uc);
CLASS_DECL_AURA int is_low_surrogate(unichar uc);

END_EXTERN_C
