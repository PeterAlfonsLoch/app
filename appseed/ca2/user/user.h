#pragma once


#include "ca4/ca4.h"
#include "database/database.h"
#include "visual/visual.h"


namespace user
{
   class application;
} // namespace user

enum e_position
{
   position_none           = 0,
   position_top            = 1,
   position_left           = 2,
   position_top_left       = 3,
   position_right          = 4,
   position_top_right      = 5,
   position_hcenter        = 6,
   position_top_center     = 7,
   position_bottom         = 8,
   position_vcenter        = 9,
   position_bottom_left    = 10,
   position_left_center    = 11,
   position_bottom_right   = 12,
   position_right_center   = 13,
   position_bottom_center  = 14,
   position_center         = 15,
};


namespace user
{
   enum e_line_hit
   {
      line_hit_none,
      line_hit_normal,
      line_hit_link,
   }; 
}


#include "user_front_end_schema.h"
#include "user_front_end.h"

#include "user_view_container.h"
#include "user_view_creator.h"


#include "user_keyboard_layout.h"
#include "user_keyboard.h"

#include "user_control.h"

#include "user_place_holder.h"
#include "user_place_holder_container.h"

#include "html/data_callback.h"

#include "user_form_callback.h"
#include "user_list_header.h"
#include "user_scroll_bar.h"
#include "user_scroll_view.h"
#include "user_form.h"

#include "user_combo_box.h"

#include "user_list.h"
#include "user_list_cache_interface.h"
#include "user_list_cache.h"
#include "user_list_data.h"
#include "user_simple_list_data.h"


#include "user_tree.h"

#include "user_form_list.h"

#include "user_tab_callback.h"
#include "user_tab.h"

#include "user_plain_text_data.h"
#include "user_edit_plain_text.h"

#include "user_button.h"
#include "user_check_box.h"

#include "user_xfplayer_view_line.h"
#include "user_xfplayer_view_lines.h"

#include "user_tool_tip_tool.h"
#include "user_tool_tip_window.h"


#include "user_document_template.h"
#include "user_single_document_template.h"
#include "user_multiple_document_template.h"
#include "user_document_interface.h"
#include "user_document.h"
#include "user_create_context.h"


#include "user_document_manager.h"

#include "user_job.h"

#include "user_printer.h"

#include "user_print_job.h"





#include "user_application.h"


#include "ca2/ca2_user.h"