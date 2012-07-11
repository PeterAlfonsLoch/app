#pragma


class CLASS_DECL_c simple_edit_box :
   public simple_ui
{
public:

   int         m_iPos;


   simple_edit_box();
   virtual ~simple_edit_box();
   
   
   virtual void draw_this(HDC hdc);


   virtual void on_char(int ch, UINT uScan);
   virtual void on_lbutton_down(int x, int y);
   virtual void on_lbutton_up(int x, int y);

   virtual bool is_focusable();

};