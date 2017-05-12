#pragma once


namespace user
{

   enum e_event
   {
      event_initialize_control,
      event_button_down,
      event_button_clicked,
      event_m_button_down,
      event_m_button_up,
      event_list_clicked,
      event_mouse_enter,
      event_mouse_leave,
      event_set_check,
      event_timer,
      event_enter_key,
      event_escape,
      event_tab_key,
      event_key_down,
      event_after_change_text,
      event_after_change_cur_sel,
      event_timebar_change,
      event_menu_hover,
      event_context_menu_close,
      event_set_focus,
      event_kill_focus,
      event_on_create_view,
      event_on_create_tab,
      event_form_initialize,
      event_create,
      event_layout,
      event_calc_item_height,
      event_change_view_style
   };

   enum e_color
   {

      color_none,
      color_text,
      color_text_highlight,
      color_text_selected,
      color_text_selected_highlight,
      color_text_focused,
      color_background,
      color_background_selected,
      color_border_normal,
      color_border_hover,
      color_border_press,
      color_border_disabled,
      color_background_normal,
      color_background_hover,
      color_background_press,
      color_background_disabled,
      color_text_normal,
      color_text_hover,
      color_text_press,
      color_text_disabled,
      color_button_background_normal,
      color_button_background_hover,
      color_button_background_press,
      color_button_background_disabled,
      color_button_text_normal,
      color_button_text_hover,
      color_button_text_press,
      color_button_text_disabled,
      color_face,
      color_face_lite,
      color_list_header,
      color_list_header_background,
      color_list_header_separator,
      color_list_item_background,
      color_list_background,
      color_edit_text,
      color_edit_background,
      color_edit_text_selected,
      color_edit_background_selected,
      color_tree_background,
      color_view_background,
      color_scrollbar_background,
      color_toolbar_background,
      color_toolbar_separator,
      color_split_layout_background,
      color_tab_client_background,
      color_tab_layout_background,

   };

   enum e_font
   {

      font_none,
      font_button,
      font_plain_edit,
      font_tree,
      font_list_item,
      font_list_hover,
      font_static,
      font_toolbar,

   };


} // namespace user

