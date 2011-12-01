#pragma once


class CLASS_DECL_ca simple_scroll_bar :
   virtual public ::user::scroll_bar
{
public:


   //::ca::brush_sp       m_brushNull;
   ::ca::pen_sp         m_penDraw;
   point                m_ptTrackOffset;
   point                m_ptaA[4]; // pontos da primeira seta
   point                m_ptaB[4]; // pontos da segunda seta
   ::ca::region_sp         m_rgnA; // região da primeira seta
   ::ca::region_sp         m_rgnB; // região da segunda seta
   UINT                 m_uiTimer;


   simple_scroll_bar(::ca::application * papp);
   virtual ~simple_scroll_bar();



   virtual void pre_translate_message(gen::signal_object * pobj);
   using ::user::scroll_bar::create;
   virtual BOOL create(const char * lpszClassName, const char * lpszWindowName, DWORD dwStyle, const RECT& rect, ::user::interaction* pParentWnd, UINT nID, ::ca::create_context* pContext = NULL);
   virtual void install_message_handling(::gen::message::dispatch * pinterface);

   virtual void _001OnDraw(::ca::graphics * pdc);

   void UpdateDrawingObjects();



   int ScrollLineA();
   int ScrollLineB();
   int ScrollPageB();
   int ScrollPageA();
   BOOL GetPageARect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   BOOL GetPageBRect(LPRECT lpRectClient, LPRECT lpRectTrack,  LPRECT lpRect);
   void UpdateBitmaps();
   void OnDisplayChange(int iBitsPerPixel, size sizeScreen);
   //virtual void OnDraw(::ca::graphics * pgraphics);
   virtual int _001GetScrollPos();
   virtual int _001SetScrollPos(int iPos);
   virtual bool _001GetScrollInfo(::user::scroll_info * psi);
   virtual bool _001SetScrollInfo(::user::scroll_info * psi, bool bRedraw = true);

   BOOL create(e_orientation eorientation, DWORD dwStyle, rect & rect, ::user::interaction * pParentWnd, UINT nID);

   int SetTrackingPos(point point);
   int GetTrackSize(size & size);
   BOOL GetTrackClientRect(LPRECT lpRect);
   BOOL GetTrackRect(LPRECT lpRect);
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnLButtonDown)
   DECL_GEN_SIGNAL(_001OnLButtonUp)
   DECL_GEN_SIGNAL(_001OnHScroll)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnTimer)
   DECL_GEN_SIGNAL(_001OnCreate)
   DECL_GEN_SIGNAL(_001OnShowWindow)
   DECL_GEN_SIGNAL(_001OnDestroy)
   LRESULT OnEconoModeChange(WPARAM wParam, LPARAM lParam);


};


