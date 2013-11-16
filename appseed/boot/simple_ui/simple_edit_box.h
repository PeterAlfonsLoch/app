#pragma


class CLASS_DECL_BOOT simple_edit_box :
   public simple_ui
{
public:

   
   int_ptr         m_iPos;


   simple_edit_box();
   virtual ~simple_edit_box();
   
   
   virtual void draw_this(simple_graphics & g);


   virtual bool on_char(int32_t iKey, const string & strChar);
   virtual bool on_lbutton_down(int32_t x, int32_t y);
   virtual bool on_lbutton_up(int32_t x, int32_t y);

   virtual bool is_focusable();

   
};



