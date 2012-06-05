#pragma once


class CLASS_DECL_ca2 MetaButton :
   public ::userbase::button,
   public ::uinteraction::frame::ControlBoxButton
{
public:
   

   enum ETimer
   {
      TimerCheckFocus,
   };


   ::ca::brush       m_brushEllipse;
   ::ca::pen         m_penEllipse;
   COLORREF          m_crText;
   ::ca::brush       m_brushEllipseSel;
   ::ca::pen         m_penEllipseSel;
   COLORREF          m_crTextSel;
   ::ca::brush       m_brushEllipseFocus;
   ::ca::pen         m_penEllipseFocus;
   COLORREF          m_crTextFocus;
   ::ca::brush       m_brushEllipseDisabled;
   ::ca::pen         m_penEllipseDisabled;
   COLORREF          m_crTextDisabled;
   HWND              m_hwndPreviousFocus;

   ::ca::region_sp   m_spregion;

   //bool              m_bFocus;


   MetaButton(::ca::application * papp);
   virtual ~MetaButton();


   virtual int hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual void install_message_handling(::gen::message::dispatch *pinterface);
   void UpdateWndRgn();
   void SetEllipsePens(
        ::ca::pen * ppen,
        ::ca::pen * ppenSel = NULL,
        ::ca::pen * ppenFocus = NULL,
        ::ca::pen * ppenDisabled = NULL);
   void SetEllipseBrushs(
        ::ca::brush * pbrush,
        ::ca::brush * pbrushSel = NULL,
        ::ca::brush * pbrushFocus = NULL,
        ::ca::brush * pbrushDisabled = NULL);
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



