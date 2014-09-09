#pragma once


#include "cross.h"

#ifdef cplusplus

inline bool IsDirSep(WCHAR ch);

#endif

CLASS_DECL_AURA void set_splash(oswindow oswindow);
CLASS_DECL_AURA oswindow get_splash();



CLASS_DECL_AURA void output_debug_string(const char * psz);



CLASS_DECL_AURA int_bool ui_get_cursor_pos(POINT * ppt);


BEGIN_EXTERN_C

CLASS_DECL_AURA int_bool is_windows_98_or_lesser();

CLASS_DECL_AURA int_bool is_windows_nt();

CLASS_DECL_AURA int_bool is_windows_nt_lesser_than_2000();
CLASS_DECL_AURA int_bool is_windows_2000_or_greater();
CLASS_DECL_AURA int_bool is_windows_xp_or_greater();
CLASS_DECL_AURA int_bool is_windows_vista_or_greater();

CLASS_DECL_AURA int_bool is_windows_native_unicode();

END_EXTERN_C



