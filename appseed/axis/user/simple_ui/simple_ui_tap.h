#pragma once


namespace simple_ui
{


   class CLASS_DECL_AXIS tap :
      virtual public interaction
   {
   public:


      bool                 m_bAutoStockIconPenWidth;
      double               m_dStockIconPenWidth;
      e_stock_icon         m_estockicon;
      bool                 m_bDown;
      bool                 m_bMouseMove;


      tap(sp(::aura::application) papp);
      virtual ~tap();

      IMH();
      DRAWDD();

      virtual void simple_ui_draw_simple(::draw2d::graphics * pgraphics);
      virtual void simple_ui_draw_volume(::draw2d::graphics * pgraphics);

      virtual void simple_ui_draw_text(::draw2d::graphics * pgraphics);


      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);

      virtual bool keyboard_focus_is_focusable();
      virtual bool is_hover();

      virtual void layout();

   };




} // namespace simple_ui




