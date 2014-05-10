#pragma once


namespace user
{


   class list;


} // namespace user



class CLASS_DECL_CORE simple_form_list_edit :
   public ::user::edit_plain_text
{
public:


   ::user::list * m_plistinterface;


   simple_form_list_edit(sp(::base::application) papp);
   virtual ~simple_form_list_edit();


   sp(::user::interaction) GetNotifyWnd();
   ::user::list * GetBaseListInterface();


   bool OnEraseBkgnd(::draw2d::graphics * pgraphics);
   DECL_GEN_SIGNAL(_001OnCreate);
   void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   int32_t OnMouseActivate(sp(::user::interaction) pDesktopWnd, UINT nHitTest, UINT message);


};


