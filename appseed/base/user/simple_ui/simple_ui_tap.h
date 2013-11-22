#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE tap :
      virtual public interaction
   {
   public:


      bool m_bDown;
      bool m_bMouseMove;


      tap();
      virtual ~tap();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      virtual void draw_simple(::draw2d::graphics * pgraphics);
      virtual void draw_volume(::draw2d::graphics * pgraphics);

      virtual void draw_text(::draw2d::graphics * pgraphics);


      virtual bool on_char(int32_t iKey, const string & strChar);
      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);
      virtual bool on_mouse_move(int32_t x, int32_t y);

      virtual bool is_focusable();
      virtual bool is_hover();

   };




} // namespace simple_ui




