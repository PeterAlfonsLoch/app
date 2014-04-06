#pragma once


class CLASS_DECL_CORE MetaButton :
   public ::user::button,
   public ::user::uinteraction::frame::control_box_button
{
public:


   enum ETimer
   {
      TimerCheckFocus,
   };


   oswindow             m_oswindowPreviousFocus;


   ::draw2d::region_sp  m_spregion;


   MetaButton(sp(base_application) papp);
   virtual ~MetaButton();


   virtual index hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual void install_message_handling(::message::dispatch *pinterface);
   void UpdateWndRgn();
   //void SetEllipsePens(
   //     ::draw2d::pen * ppen,
   //     ::draw2d::pen * ppenSel = NULL,
   //     ::draw2d::pen * ppenFocus = NULL,
   //     ::draw2d::pen * ppenDisabled = NULL);
   //void SetEllipseBrushs(
   //     ::draw2d::brush * pbrush,
   //     ::draw2d::brush * pbrushSel = NULL,
   //     ::draw2d::brush * pbrushFocus = NULL,
   //     ::draw2d::brush * pbrushDisabled = NULL);
   //void SetTextColors(
   //     COLORREF cr,
   //     COLORREF crSel,
   //     COLORREF crFocus,
   //     COLORREF crDisabled);


   virtual void layout();


   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);


};



