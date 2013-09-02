#pragma


class CLASS_DECL_ca simple_tap :
   public simple_ui
{
public:


   bool m_bDown;
   bool m_bMouseMove;


   simple_tap();
   virtual ~simple_tap();
   
   
   virtual void draw_this(simple_graphics & g);

   virtual void draw_simple(simple_graphics & g);
   virtual void draw_volume(simple_graphics & g);

   virtual void draw_text(simple_graphics & g);


   virtual void on_char(int32_t iKey, const vsstring & strChar);
   virtual void on_lbutton_down(int32_t x, int32_t y);
   virtual void on_lbutton_up(int32_t x, int32_t y);
   virtual void on_mouse_move(int32_t x, int32_t y);

   virtual bool is_focusable();
   virtual bool is_hover();

};




