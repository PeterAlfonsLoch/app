#pragma


class CLASS_DECL_c simple_password :
   public simple_edit
{
public:

   int         m_iPos;


   simple_password(simple_ui * puiParent);
   virtual ~simple_password();
   
   
   virtual void draw_this(HDC hdc);




};