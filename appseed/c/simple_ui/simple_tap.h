#pragma


class CLASS_DECL_c simple_tap :
   public simple_ui
{
public:


   bool m_bDown;


   simple_tap(simple_ui * puiParent);
   virtual ~simple_tap();
   
   
   virtual void draw_this(HDC hdc);


   virtual void on_char(int ch);
   virtual void on_lbutton_down(int x, int y);
   virtual void on_lbutton_up(int x, int y);

   virtual bool is_focusable();

};