#ifndef __GNUC__
#pragma once
#endif


#include "axis/axis/axis.h"

#ifdef __cplusplus

#include "aura/user/user.h"


#define new AURA_NEW


#include "user/user/user_keyboard_focus.h"
#include "user/user/user_mouse_focus.h"
#include "user/user/user_elemental.h"
#include "user/user/user_check_interface.h"
#include "graphics/visual/visual_const.h"
#include "axis/axis/message/message_user.h"
#include "user/user/user_schema_simple_impl.h"
#include "user/user/user_schema_layered_frame.h"
#include "user/user/user_text_interface.h"
#include "user/user/user_draw_interface.h"
#include "user/user/user_window_util.h"
#include "user/user/user_interaction_base.h"
#include "user/user/user_buffer.h"
#include "user/user/user_interaction.h"
#include "user/user/user_interaction_impl_base.h"
#include "user/user/user_interaction_child.h"
#include "user/user/user_interaction_impl.h"
#include "user/user/user_control_bar.h"
#include "user/user/user_wait_cursor.h"
#include "user/user/user_frame_window.h"
#include "user/user/user_server.h"
#include "user/user/user_impact_system.h"






#include "axis/user/simple_ui/simple_ui_style.h"
#include "axis/user/simple_ui/simple_ui_interaction.h"
#include "axis/database/sqlite/sqlite.h"
#include "user/user/user_document_data_map.h"
#include "user/user/user_document.h"
#include "database/database/database_user_interaction.h"
#include "user/user/user_impact.h"




#if defined(METROWIN)

#include "app/appseed/axis/axis/os/metrowin/metrowin_sockets.h"

#endif



#include "user/user/user_window_map.h"

#include "user/user/user_keyboard_layout.h"
#include "user/user/user_keyboard.h"
#include "user/user/user_user.h"



#include "user/user/user_create_context.h"


#include "user/user/user_window_draw.h"

#include "user/user/user_str_context.h"


#include "axis/user/user/user.h"
#include "axis/axis/axis_print_job.h"
#include "user/user/user_control_event.h"

#include "user/user/user_control.h"
#include "user/user/user_scroll_bar.h"
#include "user/user/user_scroll_view.h"
#include "user/user/user_form_interface.h"

#include "user/user/user_plain_text_data.h"
#include "user/user/user_edit_plain_text.h"




#include "user/user/user_place_holder.h"
#include "user/user/user_place_holder_container.h"
#include "user/user/user_view_creator_data.h"
#include "user/user/user_view_container.h"
#include "user/user/user_view_creator.h"


#include "axis/axis/axis_core_copydesk.h"
















#include "app/appseed/axis/axis/node/node.h"



#include "axis/user/simple/simple.h"
#include "axis/user/simple_ui/simple_ui.h"




#include "axis/user/user.inl"












#ifdef WINDOWSEX


namespace axis
{

   // top level window for receiving system messages broadcasted to top level windows in Windows

   class CLASS_DECL_AXIS system_interaction_impl:
      virtual public ::user::interaction
   {
   public:

      system_interaction_impl(sp(::aura::application) papp);

      void install_message_handling(::message::dispatch * pdispath);

      DECL_GEN_SIGNAL(_001MessageHub);


   };


} // namespace axis



#endif




#endif // __cplusplus




