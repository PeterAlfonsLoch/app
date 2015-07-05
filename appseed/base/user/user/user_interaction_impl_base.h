#pragma once


namespace user
{


   class CLASS_DECL_BASE interaction_impl_base:
      virtual public ::user::interaction_base,
      virtual public ::aura::timer_array
   {
   public:

      rect64                              m_rectParentClient;
      ::user::interaction *               m_pui;
      bool                                m_bIgnoreSizeEvent;
      bool                                m_bIgnoreMoveEvent;
      critical_section *                  m_pcsDisplay;

      interaction_impl_base();
      virtual ~interaction_impl_base();

      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::user::interaction_impl * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();


      virtual bool check_need_layout();
      virtual void clear_need_layout();
      virtual void set_need_layout();


      virtual void _001UpdateScreen(bool bUpdateBuffer = true);
      virtual void _001UpdateBuffer();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();
      virtual void _001WindowDock(::user::EAppearance eappearance);

      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIdLeftOver,UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch);

      virtual void GetClientRect(LPRECT lprect);
      virtual void GetClientRect(RECT64 * lprect);
      virtual void GetWindowRect(LPRECT lprect);
      virtual void GetWindowRect(RECT64 * lprect);
      virtual void ClientToScreen(LPRECT lprect);
      virtual void ClientToScreen(RECT64 * lprect);
      virtual void ClientToScreen(LPPOINT lppoint);
      virtual void ClientToScreen(POINT64 * lppoint);
      virtual void ScreenToClient(LPRECT lprect);
      virtual void ScreenToClient(RECT64 * lprect);
      virtual void ScreenToClient(LPPOINT lppoint);
      virtual void ScreenToClient(POINT64 * lprect);
      virtual rect GetWindowRect();
      virtual rect64 GetWindowRect64();
      virtual bool SetPlacement(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool RepositionWindow(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool MoveWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool MoveWindow(POINT pt,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SizeWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool ResizeWindow(int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool ResizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SetWindowPos(int32_t z,const RECT & rect,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);
      virtual bool defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags); // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      //virtual int32_t SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual int32_t GetWindowRgn(HRGN hRgn);


#ifdef WINDOWS

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

#else

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = 0);

#endif




      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);


      virtual ::user::interaction * get_wnd() const;


      virtual void set_viewport_org(::draw2d::graphics * pgraphics);

      virtual void viewport_screen_to_client(POINT * ppt);
      virtual void viewport_client_to_screen(POINT * ppt);
      virtual void viewport_client_to_screen(RECT * ppt);
      virtual void viewport_screen_to_client(RECT * ppt);



      
      virtual uint32_t GetStyle() const;
      virtual uint32_t GetExStyle() const;
      virtual bool ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);
      virtual bool ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);

      virtual LONG get_window_long(int32_t nIndex) const;
      virtual LONG set_window_long(int32_t nIndex,LONG lValue);

      virtual LONG_PTR get_window_long_ptr(int32_t nIndex) const;
      virtual LONG_PTR set_window_long_ptr(int32_t nIndex,LONG_PTR lValue);

      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(class id id);

      virtual ::user::interaction * first_child();
      virtual ::user::interaction * top_child();
      virtual ::user::interaction * under_sibling();
      virtual ::user::interaction * above_sibling();

      virtual ::user::interaction * above_sibling(::user::interaction * pui);
      virtual ::user::interaction * under_sibling(::user::interaction * pui);


      virtual UINT ArrangeIconicWindows();
      virtual void BringToTop(int nCmdShow);
      virtual bool BringWindowToTop();


      virtual bool IsAscendant(const ::user::interaction * puiIsAscendant) const;
      virtual bool IsParent(const ::user::interaction * puiIsParent) const;
      virtual bool IsChild(const ::user::interaction * puiIsChild) const;
      virtual bool IsDescendant(const ::user::interaction * puiIsDescendant) const;


//      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(UINT nCmd) const;


      virtual ::user::interaction * GetTopWindow() const;
      virtual ::user::interaction * GetParent() const;
      virtual ::user::interaction * GetTopLevel() const;
      virtual ::user::interaction * GetParentTopLevel() const;
      virtual ::user::interaction * EnsureTopLevel();
      virtual ::user::interaction * EnsureParentTopLevel();
      virtual ::user::interaction * GetOwner() const;
      virtual ::user::interaction * GetParentOwner() const;
      virtual ::user::interaction * GetTopLevelOwner() const;
      virtual ::user::frame_window * GetFrame() const;
      virtual ::user::frame_window * GetParentFrame() const;
      virtual ::user::frame_window * GetTopLevelFrame() const;
      virtual ::user::frame_window * GetParentTopLevelFrame() const;
      virtual ::user::frame_window * EnsureParentFrame();

      
      virtual void SendMessageToDescendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE);


      virtual void pre_translate_message(signal_details * pobj);


      virtual ::user::interaction * SetCapture(::user::interaction * pinterface = NULL);
      virtual ::user::interaction * ReleaseCapture();
      virtual ::user::interaction * GetCapture();


      virtual ::user::interaction * SetFocus();


      virtual bool get_rect_normal(LPRECT lprect);

      virtual bool SetTimer(uint_ptr nIDEvent,UINT nElapse, PFN_TIMER pfnTimer);
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual bool DestroyWindow();


      void mouse_hover_add(::user::interaction * pinterface);
      void mouse_hover_remove(::user::interaction * pinterface);


      virtual void register_drop_target();

   };


} // namespace user



















