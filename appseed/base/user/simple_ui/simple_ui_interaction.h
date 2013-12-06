#pragma once


namespace simple_ui
{


   class interaction;


   class CLASS_DECL_BASE simple_ui_ptra :
      public array < interaction * >
   {
   public:


   };


   class CLASS_DECL_BASE interaction :
      virtual public ::object
   {
   public:


      bool                             m_bVisible;
      rect                             m_rect;
      string                           m_strId;
      string                           m_strText;
      simple_ui_ptra                   m_uiptra;
      interaction *                    m_puiParent;
      interaction *                    m_puiFocus;
      style *                          m_pstyle;


      interaction(sp(base_application) papp);
      virtual ~interaction();


      virtual void set_parent(interaction * puiParent);


      virtual void draw(::draw2d::graphics * pgraphics);
      virtual void draw_this(::draw2d::graphics * pgraphics);
      virtual void draw_children(::draw2d::graphics * pgraphics);

      virtual void draw_focus_rect(::draw2d::graphics * pgraphics);


      virtual void draw_auth_box(::draw2d::graphics * pgraphics);
      virtual void draw_frame_window_rect(::draw2d::graphics * pgraphics);
      virtual void draw_dark_glass(::draw2d::graphics * pgraphics);
      virtual void draw_pestana(::draw2d::graphics * pgraphics);
      virtual void draw_fuzzy_color_spread(::draw2d::graphics * pgraphics);



      virtual bool on_char(int32_t iKey, const string & strChar);
      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);


      virtual bool on_action(const char * pszId);


      virtual bool is_focusable();
      virtual void focus_next();
      virtual void set_focus(interaction * pui);
      virtual interaction * get_focus();

      virtual bool is_visible();

      virtual style * get_style();


      virtual void viewport_client_to_screen(POINT * ppt);
      virtual void viewport_screen_to_client(POINT * ppt);
      virtual void viewport_client_to_screen(RECT * ppt);
      virtual void viewport_screen_to_client(RECT * ppt);

      virtual void client_to_screen(POINT * ppt);
      virtual void client_to_screen(RECT * prect);
      virtual void screen_to_client(POINT * ppt);
      virtual void screen_to_client(RECT * prect);

      virtual void get_window_rect(RECT * prect);
      virtual void get_client_rect(RECT * prect);

      void draw_back_01_old(style::e_schema eschema, rect m_rect, ::draw2d::graphics * pgraphics);

      virtual void layout();

      interaction * get_top_level_parent();

      virtual void set_capture();
      virtual void release_capture();

      virtual bool show_window(bool bShow = true);
      
      
      virtual void redraw_window();

      virtual void get_cursor_pos(POINT * ppt);

      virtual void translate_mouse_message(int * px, int * py);


      virtual void destroy_window();

   };


} // namespace simple_ui





