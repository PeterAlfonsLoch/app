#pragma once


#include "core/core/core.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/user/user.h"
#include "html/html/html.h"


//#include "ft2build.h"
//#include FT_FREETYPE_H


#ifdef _APP_CORE_ATARI800_LIBRARY
    #define CLASS_DECL_APP_CORE_ATARI800  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_APP_CORE_ATARI800  CLASS_DECL_IMPORT
#endif


namespace user
{

   //typedef ::user::show < ::user::plain_edit > plain_edit_view;

   typedef ::user::show < ::user::button > button_view;

} // namespace user


namespace atari800
{

   class application;
   class top_view;
   class main_view;
   class document;
   class view;
   class font_view;

} // namespace flag


#undef App
#define App(pbaseapp) (pbaseapp->m_pcoreapp->cast_app < ::atari800::application > ())


#include "user_font_list.h"

#include "atari800_render.h"

#include "atari800_document.h"
#include "atari800_font_view.h"
#include "atari800_edit_view.h"
#include "atari800_toggle_view.h"
#include "atari800_top_view.h"
#include "atari800_view.h"
//#include "atari800_lite_view.h"
//#include "atari800_full_view.h"
#include "atari800_main_view.h"
#include "atari800_switcher_view.h"
#include "atari800_frame.h"
#include "atari800_pane_view_update_hint.h"
#include "atari800_pane_view.h"

#include "atari800_application.h"

