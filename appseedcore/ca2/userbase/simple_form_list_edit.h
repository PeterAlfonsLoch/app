#pragma once

class ::user::list;

class CLASS_DECL_ca SimpleFormListEdit : public ::userbase::edit_plain_text
{
public:
   SimpleFormListEdit(::ca::application * papp);

   ::user::list * m_plistinterface;

   ::user::interaction * GetNotifyWnd();
   ::user::list * GetBaseListInterface();
   virtual ~SimpleFormListEdit();

   BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   int OnCreate(LPCREATESTRUCT lpCreateStruct);
   void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   int OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message);

};