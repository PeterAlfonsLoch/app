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


using user_interaction = ::user::interaction;

#include "axis/user/user/user.h"

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


#include "base/user/simple_ui/simple_ui_style.h"
#include "base/user/simple_ui/simple_ui_interaction.h"
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


#include "base/user/user/user.h"
#include "base/base/base_print_job.h"
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


#include "base/base/base_core_copydesk.h"
















#include "app/appseed/base/base/node/node.h"



#include "base/user/simple/simple.h"
#include "base/user/simple_ui/simple_ui.h"

#include "base/user/userpresence/userpresence.h"




#include "base/user/user.inl"






