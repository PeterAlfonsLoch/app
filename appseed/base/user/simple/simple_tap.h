#pragma once


class CLASS_DECL_BASE simple_tap :
   virtual public ::simple_ui
{
public:


   bool m_bDown;
   bool m_bMouseMove;


   simple_tap();
   virtual ~simple_tap();
   
   
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




