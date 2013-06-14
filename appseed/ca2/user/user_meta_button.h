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


   ::ca2::brush       m_brushEllipse;
   ::ca2::pen         m_penEllipse;
   COLORREF          m_crText;
   ::ca2::brush       m_brushEllipseSel;
   ::ca2::pen         m_penEllipseSel;
   COLORREF          m_crTextSel;
   ::ca2::brush       m_brushEllipseFocus;
   ::ca2::pen         m_penEllipseFocus;
   COLORREF          m_crTextFocus;
   ::ca2::brush       m_brushEllipseDisabled;
   ::ca2::pen         m_penEllipseDisabled;
   COLORREF          m_crTextDisabled;
   oswindow              m_oswindowPreviousFocus;

   ::ca2::region_sp   m_spregion;

   //bool              m_bFocus;


   MetaButton(sp(::ca2::application) papp);
   virtual ~MetaButton();


   virtual index hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::ca2::graphics * pdc);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual void install_message_handling(::ca2::message::dispatch *pinterface);
   void UpdateWndRgn();
   void SetEllipsePens(
        ::ca2::pen * ppen,
        ::ca2::pen * ppenSel = NULL,
        ::ca2::pen * ppenFocus = NULL,
        ::ca2::pen * ppenDisabled = NULL);
   void SetEllipseBrushs(
        ::ca2::brush * pbrush,
        ::ca2::brush * pbrushSel = NULL,
        ::ca2::brush * pbrushFocus = NULL,
        ::ca2::brush * pbrushDisabled = NULL);
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



