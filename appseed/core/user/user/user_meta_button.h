#pragma once


class CLASS_DECL_CORE MetaButton :
   public ::user::button,
   public ::uinteraction::frame::control_box_button
{
public:


   enum ETimer
   {
      TimerCheckFocus,
   };


   ::draw2d::brush_sp   m_brushEllipse;
   ::draw2d::pen_sp     m_penEllipse;
   ::draw2d::brush_sp   m_brushText;
   ::draw2d::brush_sp   m_brushEllipseSel;
   ::draw2d::pen_sp     m_penEllipseSel;
   ::draw2d::brush_sp   m_brushTextSel;
   COLORREF             m_crTextSel;
   ::draw2d::brush_sp   m_brushEllipseFocus;
   ::draw2d::pen_sp     m_penEllipseFocus;
   ::draw2d::brush_sp   m_brushTextFocus;
   COLORREF             m_crTextFocus;
   ::draw2d::brush_sp   m_brushEllipseDisabled;
   ::draw2d::pen_sp     m_penEllipseDisabled;
   ::draw2d::brush_sp   m_brushTextDisabled;
   COLORREF             m_crTextDisabled;
   oswindow             m_oswindowPreviousFocus;

   ::draw2d::region_sp  m_spregion;

   //bool              m_bFocus;


   MetaButton(sp(base_application) papp);
   virtual ~MetaButton();


   virtual index hit_test(point point, e_element & eelement);


   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual bool pre_create_window(CREATESTRUCT& cs);

   virtual void install_message_handling(::message::dispatch *pinterface);
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



