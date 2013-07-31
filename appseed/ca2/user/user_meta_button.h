#pragma once


class CLASS_DECL_ca2 MetaButton :
   public ::user::button,
   public ::uinteraction::frame::ControlBoxButton
{
public:
   

   enum ETimer
   {
      TimerCheckFocus,
   };


   ::draw2d::brush       m_brushEllipse;
   ::draw2d::pen         m_penEllipse;
   COLORREF          m_crText;
   ::draw2d::brush       m_brushEllipseSel;
   ::draw2d::pen         m_penEllipseSel;
   COLORREF          m_crTextSel;
   ::draw2d::brush       m_brushEllipseFocus;
   ::draw2d::pen         m_penEllipseFocus;
   COLORREF          m_crTextFocus;
   ::draw2d::brush       m_brushEllipseDisabled;
   ::draw2d::pen         m_penEllipseDisabled;
   COLORREF          m_crTextDisabled;
   oswindow              m_oswindowPreviousFocus;

   ::draw2d::region_sp   m_spregion;

   //bool              m_bFocus;


   MetaButton(sp(::ca2::application) papp);
   virtual ~MetaButton();


   virtual index hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual void install_message_handling(::ca2::message::dispatch *pinterface);
   void UpdateWndRgn();
   void SetEllipsePens(
        ::draw2d::pen * ppen,
        ::draw2d::pen * ppenSel = NULL,
        ::draw2d::pen * ppenFocus = NULL,
        ::draw2d::pen * ppenDisabled = NULL);
   void SetEllipseBrushs(
        ::draw2d::brush * pbrush,
        ::draw2d::brush * pbrushSel = NULL,
        ::draw2d::brush * pbrushFocus = NULL,
        ::draw2d::brush * pbrushDisabled = NULL);
   void SetTextColors(
        COLORREF cr,
        COLORREF crSel,
        COLORREF crFocus,
        COLORREF crDisabled);


   virtual void layout();


   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnTimer)
   LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);


};



