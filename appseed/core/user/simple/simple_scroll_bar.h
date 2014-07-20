#pragma once


class CLASS_DECL_CORE simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   //::draw2d::brush_sp       m_brushNull;
   ::draw2d::pen_sp           m_penDraw;
   ::draw2d::brush_sp         m_brushDraw;
   point                      m_ptTrackOffset;
   rect                       m_rectA;
   rect                       m_rectB;
   point                      m_ptaA[4]; // pontos da primeira seta
   point                      m_ptaB[4]; // pontos da segunda seta
   ::draw2d::region_sp        m_rgnA; // região da primeira seta
   ::draw2d::region_sp        m_rgnB; // região da segunda seta
   UINT                       m_uiTimer;


   simple_scroll_bar(sp(::base::application) papp);
   virtual ~simple_scroll_bar();



   virtual void pre_translate_message(signal_details * pobj);
   using ::user::scroll_bar::create;
   virtual bool create(const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT& rect, sp(::user::interaction) pParentWnd, UINT nID, sp(::create_context) pContext = NULL);
   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual void _001OnDraw(::draw2d::graphics * pdc);

   void update_drawing_objects();



   int32_t ScrollLineA();
   int32_t ScrollLineB();
   int32_t ScrollPageB();
   int32_t ScrollPageA();
   bool GetPageARect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   bool GetPageBRect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   void UpdateBitmaps();
   void OnDisplayChange(int32_t iBitsPerPixel, size sizeScreen);
   //virtual void OnDraw(::draw2d::graphics * pgraphics);
   virtual int32_t _001GetScrollPos();
   virtual int32_t _001SetScrollPos(int32_t iPos);
   virtual bool _001GetScrollInfo(::user::scroll_info * psi);
   virtual bool _001SetScrollInfo(::user::scroll_info * psi, bool bRedraw = true);

   bool create(e_orientation eorientation, uint32_t dwStyle, rect & rect, sp(::user::interaction) pParentWnd, UINT nID);

   int32_t SetTrackingPos(point point);
   int32_t GetTrackSize(size & size);
   bool GetTrackClientRect(LPRECT lpRect);
   bool GetTrackRect(LPRECT lpRect);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnLButtonDown);
   DECL_GEN_SIGNAL(_001OnLButtonUp);
   DECL_GEN_SIGNAL(_001OnHScroll);
   DECL_GEN_SIGNAL(_001OnSize);
   DECL_GEN_SIGNAL(_001OnTimer);
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnDestroy);
   LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);


};


