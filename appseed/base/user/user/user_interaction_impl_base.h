#pragma once


namespace user
{


   class CLASS_DECL_BASE interaction_impl_base:
      virtual public ::user::interaction_base
   {
   public:


      interaction *                 m_pui;
      bool                          m_bIgnoreSizeEvent;
      bool                          m_bIgnoreMoveEvent;


      interaction_impl_base();
      virtual ~interaction_impl_base();

      virtual sp(mutex) mutex_graphics();

      virtual void _001UpdateWindow();


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


#ifdef WINDOWS

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

#else

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = 0);

#endif


      virtual void SetFont(::draw2d::font* pFont,bool bRedraw = true);
      virtual ::draw2d::font* GetFont();


      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);


      virtual interaction * get_wnd() const;


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


      virtual sp(interaction) get_bottom_child();
      virtual sp(interaction) get_top_child();
      virtual sp(interaction) under_sibling();
      virtual sp(interaction) above_sibling();

      virtual sp(interaction) above_sibling(sp(interaction) pui);
      virtual sp(interaction) under_sibling(sp(interaction) pui);


      virtual UINT ArrangeIconicWindows();
      virtual void BringToTop(int nCmdShow);
      virtual bool BringWindowToTop();


      virtual bool IsAscendant(const interaction * puiIsAscendant) const;
      virtual bool IsParent(const interaction * puiIsParent) const;
      virtual bool IsChild(const interaction * puiIsChild) const;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const;


      virtual sp(::user::interaction) GetWindow() const;
      virtual sp(::user::interaction) GetWindow(UINT nCmd) const;


      virtual sp(::user::interaction) GetTopWindow() const;
      virtual sp(::user::interaction) GetParent() const;
      virtual sp(::user::interaction) GetTopLevel() const;
      virtual sp(::user::interaction) GetParentTopLevel() const;
      virtual sp(::user::interaction) EnsureTopLevel();
      virtual sp(::user::interaction) EnsureParentTopLevel();
      virtual sp(::user::interaction) GetOwner() const;
      virtual sp(::user::interaction) GetParentOwner() const;
      virtual sp(::user::interaction) GetTopLevelOwner() const;
      virtual sp(::user::frame_window) GetFrame() const;
      virtual sp(::user::frame_window) GetParentFrame() const;
      virtual sp(::user::frame_window) GetTopLevelFrame() const;
      virtual sp(::user::frame_window) GetParentTopLevelFrame() const;
      virtual sp(::user::frame_window) EnsureParentFrame();

      
      virtual void SendMessageToDescendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE);


      virtual void pre_translate_message(signal_details * pobj);


      virtual sp(::user::interaction) SetCapture(sp(::user::interaction) pinterface = NULL);
      virtual sp(::user::interaction) ReleaseCapture();
      virtual sp(::user::interaction) GetCapture();


      virtual sp(::user::interaction) SetFocus();


      virtual bool get_rect_normal(LPRECT lprect);


   };


} // namespace user



