#pragma once


namespace simple_ui
{


   class interaction;



   class CLASS_DECL_BASE interaction :
      virtual public ::user::interaction
   {
   public:
    
      enum e_element
      {
         element_none,
         element_tab,
         element_close_tab_button,
         element_status_image,
         element_text,
         element_icon,
         element_border,
         element_client,
         element_area,
         element_drop_down,
         element_item,
         element_search_edit,
         element_search_ok
      };



      //bool                             m_bVisible;
      //rect                             m_rect;
      //string                           m_strId;
      //string                           m_strText;
      //simple_ui_ptra                   m_uiptra;
      //interaction *                    m_puiParent;
      //interaction *                    m_puiFocus;
      style *                             m_pstyle;


      interaction();
      virtual ~interaction();


      virtual      void install_message_handling(::message::dispatch * pdispatch);


      //virtual void set_parent(interaction * puiParent);


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      //virtual void _001OnDraw(::draw2d::graphics * pgraphics);
      //virtual void draw_children(::draw2d::graphics * pgraphics);

      virtual void simple_ui_draw_focus_rect(::draw2d::graphics * pgraphics);


      virtual void simple_ui_draw_auth_box(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_frame_window_rect(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_dark_glass(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_pestana(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(::draw2d::graphics * pgraphics);

      virtual void simple_ui_draw_back_01_old(style::e_schema eschema,rect m_rect,::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_back_01_new(rect m_rect,::draw2d::graphics * pgraphics);



      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual bool on_action(const char * pszId);


      virtual bool keyboard_focus_is_focusable();
      //virtual void focus_next();
      //virtual void set_focus(interaction * pui);
      //virtual sp(::user::interaction) GetFocusget_focus();

      //virtual bool is_visible();

      virtual style * get_style();


      //virtual void viewport_client_to_screen(POINT * ppt);
      //virtual void viewport_screen_to_client(POINT * ppt);
      //virtual void viewport_client_to_screen(RECT * ppt);
      //virtual void viewport_screen_to_client(RECT * ppt);

      //virtual void client_to_screen(POINT * ppt);
      //virtual void client_to_screen(RECT * prect);
      //virtual void screen_to_client(POINT * ppt);
      //virtual void screen_to_client(RECT * prect);

      //virtual void get_window_rect(RECT * prect);
      //virtual void get_client_rect(RECT * prect);

      

      //virtual void layout();

      //interaction * get_top_level_parent();

      //virtual void set_capture();
      //virtual void release_capture();

      //virtual bool show_window(bool bShow = true);


      //virtual void redraw_window();

      //virtual void get_cursor_pos(POINT * ppt);

      //virtual void translate_mouse_message(int * px, int * py);


      //virtual bool DestroyWindow();

      //virtual LRESULT message_handler(UINT message, WPARAM wParam, LPARAM lParam);

      //virtual bool on_move(int32_t x, int32_t y);
      //virtual bool on_size(int32_t cx, int32_t cy);

      virtual index hit_test(point point,e_element & eelement);

   };


} // namespace simple_ui





