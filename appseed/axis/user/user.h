#ifndef __GNUC__
#pragma once
#endif


#include "axis/axis/axis.h"

#if defined(__cplusplus) || defined(__cplusplus_winrt)

#include "aura/user/user.h"


#define new AURA_NEW

namespace user
{


   class interaction;
   class create_struct;
   class control_event;


} // namespace user



namespace aura
{


   class menu_base_item;
   class menu;
   class menu_base;


}

namespace user
{

   class schema;
   class tree;


}


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}




namespace user
{

   class control_event;
   class create_context;
   class printer;
   class user;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user

namespace user
{

   class interaction;
   class interaction_impl;
   class view_creator_data;
   class schema;
   class tree;
   class str_context;
   class schema_simple_impl;
   class window_draw;
   class str;

}


namespace user
{

   class interaction;
   class control_event;
   class create_context;
   class user;
   class frame_window;

   class form_interface;
   class form_list;
   class form_callback;


} // namespace user


namespace simple_ui
{

   class label;
   class edit_box;
   class password;
   class tap;

}

namespace user
{


   class interaction;
   class interaction_impl;
   class frame_window;
   class create_struct;


} // namespace user


typedef sp(::user::interaction_impl) window_sp;


namespace user
{

   class place_holder;

#if defined METROWIN

   class CLASS_DECL_AXIS native_window_initialize
   {
   public:


      Agile<Windows::UI::Core::CoreWindow> window;
      ::base::system_window ^ pwindow;


   };

#elif defined(APPLE_IOS)

   class CLASS_DECL_AXIS native_window_initialize
   {
   public:

      RECT   m_rect;

   };

#else

   class native_window_initialize;

#endif


   class control_event;
   class frame_window;





   CLASS_DECL_AXIS bool is_descendant(::user::interaction * puiParent,::user::interaction * puiChild);


} // namespace user



#if defined(__cplusplus) || defined(__cplusplus_winrt)


namespace user
{


   class CLASS_DECL_AXIS create_struct:
      public CREATESTRUCTA
   {
   public:


      create_struct & operator = (const RECT & rect)
      {

         x = rect.left;
         y = rect.top;
         cx = rect.right - rect.left;
         cy = rect.bottom - rect.top;

         return *this;

      }


      create_struct & operator = (LPCRECT lpcrect)
      {

         if(lpcrect == NULL)
         {

            x = 0;
            y = 0;
            cx = 0;
            cy = 0;

         }
         else
         {

            operator = (*lpcrect);

         }

         return *this;

      }


   };


} // namespace user


#endif







#ifndef TBSTYLE_TOOLTIPS
#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
#endif

#include "user/user_enum.h"

#include "user/user_key_enum.h"

#include "user/user_schema.h"



using user_interaction = ::user::interaction;


//#include "user/user/user_keyboard_focus.h"
//#include "user/user/user_mouse_focus.h"
#include "user/user/user_elemental.h"
//#include "user/user/user_check_interface.h"
#include "graphics/visual/visual_const.h"
#include "axis/axis/message/message_user.h"
#include "user/user/user_schema_simple_impl.h"
#include "user/user/user_schema_layered_frame.h"
//#include "user/user/user_text_interface.h"
//#include "user/user/user_draw_interface.h"
#include "user/user/user_window_util.h"
#include "user/user/user_interaction_base.h"
//#include "user/user/user_buffer.h"
#include "user/user/user_interaction.h"
#include "user/user/user_interaction_impl_base.h"
#include "user/user/user_interaction_child.h"
#include "user/user/user_interaction_impl.h"
#include "user/user/user_control_bar.h"
#include "user/user/user_wait_cursor.h"
#include "user/user/user_frame_window.h"
#include "user/user/user_server.h"
#include "user/user/user_impact_system.h"



#include "user/user/user_form_callback.h"


#include "simple_ui/simple_ui_style.h"
#include "simple_ui/simple_ui_interaction.h"
#include "user/user/user_document_data_map.h"
#include "user/user/user_document.h"
#include "database/database/database_user_interaction.h"
#include "user/user/user_impact.h"




//#if defined(METROWIN)
//
//#include "app/appseed/base/base/os/metrowin/metrowin_sockets.h"
//
//#endif



#include "user/user/user_window_map.h"

#include "user/user/user_keyboard_layout.h"
#include "user/user/user_keyboard.h"
#include "user/user/user_user.h"



//#include "user/user/user_create_context.h"


#include "user/user/user_window_draw.h"

//#include "user/user/user_str_context.h"


#include "axis/user/user/user.h"
//#include "axis/base/base_print_job.h"
#include "user/user/user_control_event.h"

#include "user/user/user_control.h"
#include "user/user/user_scroll_bar.h"
#include "user/user/user_scroll_control.h"
#include "user/user/user_scroll_view.h"
#include "user/user/user_form_interface.h"

#include "user/user/user_plain_text_data.h"
#include "user/user/user_edit_plain_text.h"

#include "user/user/user_form.h"
#include "user/user/user_form_update_hint.h"



#include "user/user/user_place_holder.h"
#include "user/user/user_place_holder_container.h"
#include "user/user/user_view_creator_data.h"
#include "user/user/user_view_container.h"
#include "user/user/user_view_creator.h"


#include "user/user/user_copydesk.h"
















#include "app/appseed/axis/axis/node/node.h"



#include "axis/user/simple/simple.h"
#include "axis/user/simple_ui/simple_ui.h"

#include "axis/user/userpresence/userpresence.h"




#include "axis/user/user.inl"




#include "axis/user/user/user.h"



#endif // __cplusplus

