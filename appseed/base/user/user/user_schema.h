#pragma once


class simple_scroll_bar;


namespace user
{

   class tab;

   class tab_pane;

   class toolbar;

   class scroll_bar;

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

   };

   class CLASS_DECL_BASE schema :
      virtual public ::object
   {
   public:

      
      ::user::schema *        m_puserschemaSchema;
      ::aura::library *       m_plibrary;

      schema();
      virtual ~schema();

      virtual ::user::schema * get_user_schema();
      virtual ::user::schema * get_parent_user_schema();

      virtual bool get_color(COLORREF & cr,e_color ecolor);
      virtual bool get_font(::draw2d::font_sp & sp);
      virtual bool get_translucency(ETranslucency & etranslucency);

      virtual COLORREF        _001GetColor(e_color ecolor, COLORREF crDefault);
      virtual COLORREF        _001GetColor(e_color ecolor);
      virtual ETranslucency   _001GetTranslucency(ETranslucency etranslucencyDefault = TranslucencyNone);

      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();

      virtual bool select_layered_frame();
      virtual bool select_text_color(::draw2d::graphics * pgraphics, e_color ecolor = color_text);
      virtual bool select_font(::draw2d::graphics * pgraphics);

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics);


      virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab);
      
      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText);

      virtual bool _001OnTabLayout(::user::tab * ptab);

      virtual bool _001GetMainFrameTranslucency(::user::ETranslucency & etranslucency);

      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame_window * pframe);


      virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck);

      virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar);

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar);

      virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar);

   };




} // namespace user




