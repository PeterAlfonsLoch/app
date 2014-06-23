#pragma once


namespace user
{


   class CLASS_DECL_BASE interaction_impl_base:
      virtual public ::user::interaction_base
   {
   public:


      interaction * m_pui;


      interaction_impl_base();
      virtual ~interaction_impl_base();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();

      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIdLeftOver,UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch);

      virtual void GetClientRect(LPRECT lprect);
      virtual void GetClientRect(__rect64 * lprect);
      virtual void GetWindowRect(LPRECT lprect);
      virtual void GetWindowRect(__rect64 * lprect);
      virtual void ClientToScreen(LPRECT lprect);
      virtual void ClientToScreen(__rect64 * lprect);
      virtual void ClientToScreen(LPPOINT lppoint);
      virtual void ClientToScreen(__point64 * lppoint);
      virtual void ScreenToClient(LPRECT lprect);
      virtual void ScreenToClient(__rect64 * lprect);
      virtual void ScreenToClient(LPPOINT lppoint);
      virtual void ScreenToClient(__point64 * lprect);
      virtual rect GetWindowRect();
      virtual rect64 GetWindowRect64();
      virtual bool SetPlacement(LPCRECT lprect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool RepositionWindow(LPCRECT lpcrect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool MoveWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool MoveWindow(POINT pt,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SizeWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool ResizeWindow(int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool ResizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SetWindowPos(int32_t z,LPCRECT lpcrect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags); // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      //virtual int32_t SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual int32_t GetWindowRgn(HRGN hRgn);


      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);



   };


} // namespace user



