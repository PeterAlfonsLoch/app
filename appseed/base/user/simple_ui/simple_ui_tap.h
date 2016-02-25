#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE tap :
      virtual public interaction
   {
   public:


      bool                 m_bAutoStockIconPenWidth;
      double               m_dStockIconPenWidth;
      e_stock_icon         m_estockicon;
      bool                 m_bDown;
      bool                 m_bMouseMove;


      tap(::aura::application * papp);
      virtual ~tap();

      IMH();
      DRAWDD();

      virtual void simple_ui_draw_simple(::draw2d::dib * pdib);
      virtual void simple_ui_draw_volume(::draw2d::dib * pdib);

      virtual void simple_ui_draw_text(::draw2d::dib * pdib);


      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);

      virtual bool keyboard_focus_is_focusable();
      virtual bool is_hover();

      virtual void layout();


      virtual void _000OnDraw(::draw2d::dib * pdib);
      virtual void _001DrawThis(::draw2d::dib * pdib);
      virtual void _001CallOnDraw(::draw2d::dib * pdib);

   };




} // namespace simple_ui




