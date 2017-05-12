#pragma once


class simple_scroll_bar;


namespace user
{

   class tab;

   class tab_pane;

   class toolbar;

   class scroll_bar;



   enum e_object
   {

      object_list,
      object_tree

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
      virtual bool get_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui);
      virtual bool get_translucency(ETranslucency & etranslucency);

      virtual COLORREF        _001GetColor(e_color ecolor, COLORREF crDefault);
      virtual COLORREF        _001GetColor(e_color ecolor);
      virtual ETranslucency   _001GetTranslucency(ETranslucency etranslucencyDefault = TranslucencyUndefined);

      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();

      virtual bool select_layered_frame();
      virtual bool select_text_color(::draw2d::graphics * pgraphics, e_color ecolor = color_text);
      virtual bool select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui);

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics);

      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui);

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




