#pragma once


#include "base/user/user/user_scroll_bar.h"


class CLASS_DECL_BASE simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   ::draw2d::pen_sp           m_penDraw;
   ::draw2d::brush_sp         m_brushDraw;
   point                      m_ptTrackOffset;
   rect                       m_rectA;
   rect                       m_rectB;
   point                      m_ptaA[4]; // pontos da primeira seta
   point                      m_ptaB[4]; // pontos da segunda seta
   ::draw2d::region_sp        m_rgnA; // regi�o da primeira seta
   ::draw2d::region_sp        m_rgnB; // regi�o da segunda seta
   UINT                       m_uiTimer;
   ::user::e_element          m_eelement;

   COLORREF                   m_cr;
   COLORREF                   m_crStrong;
   COLORREF                   m_crBorder;
   COLORREF                   m_crLiteBorder;
   COLORREF                   m_crHover;
   COLORREF                   m_crHoverStrong;
   COLORREF                   m_crHoverBorder;
   COLORREF                   m_crHoverLiteBorder;


   simple_scroll_bar(::aura::application * papp);
   virtual ~simple_scroll_bar();



   virtual void pre_translate_message(signal_details * pobj);
   virtual bool create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,UINT nID, ::create * pcreate = NULL);
   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual void _001OnDraw(::draw2d::graphics * pgraphics);
   virtual void _001OnVerisimpleDraw(::draw2d::graphics * pgraphics);

   void update_drawing_objects();



   bool GetPageARect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   bool GetPageBRect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   void UpdateBitmaps();
   void OnDisplayChange(int32_t iBitsPerPixel, size sizeScreen);
   //virtual void OnDraw(::draw2d::dib * pdib);
   virtual int32_t _001GetScrollPos();
   virtual int32_t _001SetScrollPos(int32_t iPos);
   virtual bool _001GetScrollInfo(::user::scroll_info * psi);
   virtual bool _001SetScrollInfo(::user::scroll_info * psi, bool bRedraw = true);

   bool create_window(e_orientation eorientation,uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,UINT nID);

   int32_t SetTrackingPos(point point);
   int32_t GetTrackSize(size & size);
   bool GetTrackClientRect(LPRECT lpRect);
   bool GetTrackRect(LPRECT lpRect);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnHScroll);
   void _001OnTimer(::timer * ptimer);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnDestroy);
   LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);

   void draw_mac_thumb_simple(::draw2d::graphics * pgraphics,LPCRECT lpcrectDraw,LPCRECT lpcrectClip,byte uchAlpha);
   void draw_mac_thumb_dots(::draw2d::graphics * pgraphics,LPCRECT lpcrectDraw,LPCRECT lpcrectClip,byte uchAlpha);


   virtual void on_layout();

   virtual index hit_test(point point, ::user::e_element & eelement);

   virtual bool scrollbar_action(::user::e_element eelement, point pt);

   virtual bool scrollbar_lineA();
   virtual bool scrollbar_lineB();
   virtual bool scrollbar_pageB(point pt);
   virtual bool scrollbar_pageA(point pt);

   virtual COLORREF scrollbar_color_strong(::user::e_element eelement);
   virtual COLORREF scrollbar_color(::user::e_element eelement);
   virtual COLORREF scrollbar_border_color(::user::e_element eelement);
   virtual COLORREF scrollbar_lite_border_color(::user::e_element eelement);

};


