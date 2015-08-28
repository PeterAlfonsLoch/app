#pragma once


#include "os_threading.h"

#include "cross.h"

/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/


#ifdef cplusplus

inline bool IsDirSep(WCHAR ch);



#endif

CLASS_DECL_AURA void set_splash(oswindow oswindow);
CLASS_DECL_AURA oswindow get_splash();

CLASS_DECL_AURA int get_processor_count();

CLASS_DECL_AURA void output_debug_string(const char * psz);



//CLASS_DECL_AURA int_bool ui_get_cursor_pos(POINT * ppt);


BEGIN_EXTERN_C

CLASS_DECL_AURA int_bool is_windows_98_or_lesser();

CLASS_DECL_AURA int_bool is_windows_nt();

CLASS_DECL_AURA int_bool is_windows_nt_lesser_than_2000();
CLASS_DECL_AURA int_bool is_windows_2000_or_greater();
CLASS_DECL_AURA int_bool is_windows_xp_or_greater();
CLASS_DECL_AURA int_bool is_windows_vista_or_greater();
CLASS_DECL_AURA int_bool is_windows_7_or_lower();
CLASS_DECL_AURA int_bool is_windows_8_or_greater();

CLASS_DECL_AURA int_bool is_windows_native_unicode();



END_EXTERN_C

#include "os_time.h"

/*
#if _POSIX_C_SOURCE == 200809L
#error "Only for test!! Good error!! _POSIX_C_SOURCE still 200809L"
#endf
*/