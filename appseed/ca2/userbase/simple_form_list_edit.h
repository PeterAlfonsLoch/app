#pragma once


namespace user
{


   class list;


} // namespace user



class CLASS_DECL_ca2 simple_form_list_edit :
   public ::userbase::edit_plain_text
{
public:


   ::user::list * m_plistinterface;


   simple_form_list_edit(::ca::application * papp);
   virtual ~simple_form_list_edit();


   ::user::interaction * GetNotifyWnd();
   ::user::list * GetBaseListInterface();


   bool OnEraseBkgnd(::ca::graphics * pgraphics);
   int OnCreate(LPCREATESTRUCT lpCreateStruct);
   void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   int OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message);


};


