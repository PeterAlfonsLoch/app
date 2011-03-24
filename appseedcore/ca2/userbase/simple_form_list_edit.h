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

   afx_msg BOOL OnEraseBkgnd(::ca::graphics * pgraphics);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg int OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message);

};