#pragma once


namespace simple_ui
{


   class CLASS_DECL_BASE edit_box :
      virtual public interaction
   {
   public:


      int_ptr         m_iPos;


      edit_box(sp(base_application) papp);
      virtual ~edit_box();


      virtual void draw_this(::draw2d::graphics * pgraphics);


      virtual bool on_char(int32_t iKey, const string & strChar);
      virtual bool on_lbutton_down(int32_t x, int32_t y);
      virtual bool on_lbutton_up(int32_t x, int32_t y);

      virtual bool is_focusable();


   };



} // namespace simple_ui



