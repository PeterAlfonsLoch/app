#pragma once

class CLASS_DECL_ca MetaButton :
   public ::userbase::button,
   public window_frame::ControlBoxButton
{
public:
   

   enum ETimer
   {
      TimerCheckFocus,
   };


   ::ca::brush *     m_pbrushEllipse;
   ::ca::pen   *     m_ppenEllipse;
   COLORREF          m_crText;
   ::ca::brush *     m_pbrushEllipseSel;
   ::ca::pen   *     m_ppenEllipseSel;
   COLORREF          m_crTextSel;
   ::ca::brush *     m_pbrushEllipseFocus;
   ::ca::pen   *     m_ppenEllipseFocus;
   COLORREF          m_crTextFocus;
   ::ca::brush *     m_pbrushEllipseDisabled;
   ::ca::pen   *     m_ppenEllipseDisabled;
   COLORREF          m_crTextDisabled;
   HWND              m_hwndPreviousFocus;

   ::ca::brush_sp    m_brushEllipse;
   ::ca::pen_sp      m_penEllipse;

   ::ca::dib_sp      m_dib1;
   ::ca::dib_sp      m_dib2;

   bool              m_bFocus;


   MetaButton(::ca::application * papp);


   virtual void _001OnDraw(::ca::graphics * pdc);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual void install_message_handling(::user::win::message::dispatch *pinterface);
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

   virtual ~MetaButton();

   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnMouseLeave)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnTimer)
   LRESULT OnAppForwardSyncMessage(WPARAM wParam, LPARAM lParam);
};

