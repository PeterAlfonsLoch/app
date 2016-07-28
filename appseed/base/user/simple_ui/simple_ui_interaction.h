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
         element_search_ok,
         element_scrollbar_rect,
         element_scrollbar_rectA,
         element_scrollbar_rectB,
         element_scrollbar_pageA,
         element_scrollbar_pageB,


         element_split = 10000,
      };



      style *                             m_pstyle;


      interaction();
      virtual ~interaction();


      virtual      void install_message_handling(::message::dispatch * pdispatch);


      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics);

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void simple_ui_draw_focus_rect(::draw2d::graphics * pgraphics);


      virtual void simple_ui_draw_auth_box(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_frame_window_rect(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_dark_glass(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_pestana(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_fuzzy_color_spread(::draw2d::graphics * pgraphics);

      virtual void simple_ui_draw_back_01_old(style::e_schema eschema,rect m_rect,::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_back_01_new(rect m_rect,::draw2d::graphics * pgraphics);

      virtual bool has_action_hover();
      virtual bool has_text_input();
      virtual COLORREF get_action_hover_border_color();

      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);


      virtual bool on_action(const char * pszId);


      virtual bool keyboard_focus_is_focusable();

      virtual style * get_style();


      virtual index hit_test(point point,e_element & eelement);

   };


} // namespace simple_ui





