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


   ::ax::brush       m_brushEllipse;
   ::ax::pen         m_penEllipse;
   COLORREF          m_crText;
   ::ax::brush       m_brushEllipseSel;
   ::ax::pen         m_penEllipseSel;
   COLORREF          m_crTextSel;
   ::ax::brush       m_brushEllipseFocus;
   ::ax::pen         m_penEllipseFocus;
   COLORREF          m_crTextFocus;
   ::ax::brush       m_brushEllipseDisabled;
   ::ax::pen         m_penEllipseDisabled;
   COLORREF          m_crTextDisabled;
   HWND              m_hwndPreviousFocus;

   ::ax::region_sp   m_spregion;

   //bool              m_bFocus;


   MetaButton(::ax::application * papp);
   virtual ~MetaButton();


   virtual int hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::ax::graphics * pdc);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   virtual void install_message_handling(::gen::message::dispatch *pinterface);
   void UpdateWndRgn();
   void SetEllipsePens(
        ::ax::pen * ppen,
        ::ax::pen * ppenSel = NULL,
        ::ax::pen * ppenFocus = NULL,
        ::ax::pen * ppenDisabled = NULL);
   void SetEllipseBrushs(
        ::ax::brush * pbrush,
        ::ax::brush * pbrushSel = NULL,
        ::ax::brush * pbrushFocus = NULL,
        ::ax::brush * pbrushDisabled = NULL);
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



