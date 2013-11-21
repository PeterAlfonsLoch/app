#pragma once


class CLASS_DECL_BASE simple_edit_box :
   virtual public ::simple_ui
{
public:

   
   int_ptr         m_iPos;


   simple_edit_box();
   virtual ~simple_edit_box();
   
   
   virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   virtual bool on_char(int32_t iKey, const string & strChar);
   virtual bool on_lbutton_down(int32_t x, int32_t y);
   virtual bool on_lbutton_up(int32_t x, int32_t y);

   virtual bool is_focusable();

   
};



