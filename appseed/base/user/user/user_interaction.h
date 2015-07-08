#ifndef CA2_APP_BASE_USER_INTERACTION_H
#define CA2_APP_BASE_USER_INTERACTION_H


namespace user
{



   class CLASS_DECL_BASE interaction:
      virtual public interaction_base,
      virtual public ::user::schema
   {
   public:

      enum e_updown
      {
         type_normal_frame,
         type_none,
         type_up,
         type_down,
      };

      point                               m_ptScrollPassword1;
      e_updown                            m_eupdown;
      bool                                m_bMoving;
      bool                                m_bMoveWindow;
      bool                                m_bMayProDevian;
      bool                                m_bVisible;
      bool                                m_bVoidPaint;
      bool                                m_bLockWindowUpdate;
      bool                                m_bEnableSaveWindowRect;


      point                               m_ptMoveCursor;

      bool                                m_bDefaultWalkPreTranslateParentTree;

      draw_interface *                    m_pdrawinterfaceBackground;
      bool                                m_bBackgroundBypass;

      uint32_t                            m_dwLastFullUpdate;

      bool                                m_bSizeMove;
      uint32_t                            m_dwLastSizeMove; // instead of u32, dw for dWindows the The Windows, sake of hating crisis... (now its like a old Honda Civic (TM))... the difference (one is Fatty the Other is Slim [and Cuts {The Head Out} unless you are Japanese or Sushi fan (in case of Civic), no hatings...)...)


      sp(::user::interaction)             m_pparent;

//      sp(mutex)                           m_spmutex;
      EAppearance                         m_eappearance;
      EAppearance                         m_eappearanceBefore;
      sp(interaction_impl_base)           m_pimpl;


      interaction_spa                     m_uiptraChild;
      string                              m_strName;
      id                                  m_id;
      interaction *                       m_puiOwner;
      UINT                                m_nFlags;      // see WF_ flags above
      bool                                m_bCursorInside;
      ::visual::e_cursor                  m_ecursor;
      int32_t                             m_iModal;
      int32_t                             m_iModalCount;
      bool                                m_bRectOk;
      sp(::axis::session)                 m_psession;
      bool                                m_bMessageWindow;

      string                              m_strWindowText;


#if defined(WINDOWS) || defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      comparable_array < int_ptr >        m_iaModalThread;

#else

      comparable_array < pthread_t >      m_iaModalThread;

#endif

      id                                  m_idModalResult; // for return values from interaction_impl::RunModalLoop

      sp(::user::menu_base)               m_spmenuPopup;

      int32_t                             m_nModalResult; // for return values from ::interaction_impl::RunModalLoop
      ptr_array < thread >                m_threadptra;


      //ptr_array < bool >                  m_bptraTellMeDestroyed; // Telmo why!! :-)


      interaction();
      interaction(::aura::application * papp);
      virtual ~interaction();


      void user_interaction_common_construct();

      virtual bool defer_check_layout();
      virtual bool check_need_layout();
      virtual void clear_need_layout();
      virtual void set_need_layout();


      virtual bool create_message_queue(const char * pszName);





#if defined(METROWIN) || defined(APPLE_IOS)
      virtual bool initialize(::user::native_window_initialize * pinitialize);
#endif



      virtual void on_select();

      virtual bool is_place_holder();

      ::visual::e_cursor get_cursor();
      void set_cursor(::visual::e_cursor ecursor);


      void set_timer(spa(::aura::timer_item) timera);

      virtual bool set_may_pro_devian(bool bSet = true);
      virtual void on_set_may_pro_devian();

      virtual bool IsWindow() const;

      virtual LONG get_window_long(int32_t nIndex) const;
      virtual LONG set_window_long(int32_t nIndex,LONG lValue);

      virtual LONG_PTR get_window_long_ptr(int32_t nIndex) const;
      virtual LONG_PTR set_window_long_ptr(int32_t nIndex,LONG_PTR lValue);

      virtual bool on_before_set_parent(::user::interaction * pinterface);
      virtual void on_set_parent(::user::interaction * pinterface);

      virtual ::user::elemental * first_child_elemental();
      virtual ::user::elemental * top_elemental();
      virtual ::user::elemental * under_elemental();
      virtual ::user::elemental * above_elemental();
      virtual ::user::elemental * next_elemental();
      virtual ::user::elemental * previous_elemental();



      virtual ::user::interaction * first_child();
      virtual ::user::interaction * last_child();
      virtual ::user::interaction * last_sibling();
      virtual ::user::interaction * next_sibling();
      virtual ::user::interaction * previous_sibling();
      virtual ::user::interaction * first_sibling();
      virtual ::user::interaction * next_sibling(::user::interaction * pui);
      virtual ::user::interaction * previous_sibling(::user::interaction * pui);


      virtual void mouse_hover_add(::user::interaction * pinterface);
      virtual void mouse_hover_remove(::user::interaction * pinterface);


      virtual bool CheckAutoCenter();

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      // dialog support
      void UpdateDialogControls(command_target* pTarget,bool bDisableIfNoHndler);
      virtual void CenterWindow(::user::interaction * pAlternateOwner = NULL);
      virtual id   run_modal_loop(::user::interaction * pui,uint32_t dwFlags = 0,::object * pliveobject = NULL);
      virtual id   RunModalLoop(uint32_t dwFlags = 0,::object * pliveobject = NULL);
      virtual id   _001RunModalLoop(uint32_t dwFlags = 0,::object * pliveobject = NULL);
      virtual bool ContinueModal(int32_t iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual ::user::interaction * get_os_focus_uie();


      virtual void on_keyboard_focus(::user::elemental * pfocus);


      virtual void _001UpdateScreen(bool bUpdateBuffer = true);
      virtual void _001UpdateBuffer();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();
      virtual void _001WindowDock(::user::EAppearance eappearance);

      using ::user::interaction_base::GetWindowRect;
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
      virtual bool SetPlacement(const RECT & rect,UINT nFlags = 0);
      virtual bool RepositionWindow(const RECT & rect, UINT nFlags = 0);
      virtual bool RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = 0);
      virtual bool MoveWindow(int32_t x,int32_t y,UINT nFlags = 0);
      virtual bool MoveWindow(POINT pt,UINT nFlags = 0);
      virtual bool SizeWindow(int32_t x,int32_t y,UINT nFlags = 0);
      virtual bool SizeWindow(SIZE sz,UINT nFlags = 0);
      virtual bool ResizeWindow(int32_t cx,int32_t cy,UINT nFlags = 0);
      virtual bool ResizeWindow(SIZE sz,UINT nFlags = 0);
      virtual bool SetWindowPos(int32_t z,const RECT & rect,UINT nFlags = 0);
      virtual bool SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = 0);
      virtual bool defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags); // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      virtual int32_t SetWindowRgn(HRGN hRgn,bool bRedraw);
      virtual int32_t GetWindowRgn(HRGN hRgn);

      virtual void layout();

      virtual void BringToTop(int32_t nCmdShow);
      virtual bool BringWindowToTop();

#ifdef WINDOWSEX
      virtual bool GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual bool SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);
#endif

      //virtual bool SendChildNotifyLastMsg(LRESULT* pResult = NULL);


      virtual bool pre_create_window(::user::create_struct& cs);


      virtual bool subclass_window(oswindow posdata);
      virtual oswindow unsubclass_window();


      virtual bool create_window(const RECT & rect, ::user::interaction *pparent,id id);
      virtual bool create_window(const char * lpszClassName, const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction * pParentWnd,id id,sp(::create) pContext = NULL);
      virtual bool create_window_ex(uint32_t dwExStyle = 0,const char * lpszClassName = NULL,const char * lpszWindowName= NULL,uint32_t dwStyle = 0,const RECT & rect=null_rect(),::user::interaction * pParentWnd=NULL,id id=::id(),LPVOID lpParam = NULL);
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType = adjustBorder);

      virtual bool IsTopParentActive();
      virtual void ActivateTopParent();

      virtual bool DestroyWindow();


#ifdef WINDOWS
      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::draw2d::region* prgnUpdate = NULL,
         UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
#else
      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::draw2d::region* prgnUpdate = NULL,
         UINT flags = 0);
#endif


      virtual void register_drop_target();




      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(LPRECT lpRect,bool bErase = FALSE);
      virtual int32_t GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE);
      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect,bool bErase = TRUE);
      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = TRUE);


      virtual uint32_t GetStyle() const;
      virtual uint32_t GetExStyle() const;
      virtual bool ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);
      virtual bool ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);
      virtual LRESULT Default();

      virtual LRESULT send(::message::base * pbase);
      virtual bool post(::message::base * pbase);
      virtual LRESULT send_message(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0);

#ifdef LINUX

      virtual LRESULT send_message(XEvent * pevent);

#endif

      virtual bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0);
      virtual bool post_simple_command(e_simple_command ecommand,lparam lParam = 0);

      virtual bool ShowWindow(int32_t nCmdShow);

      // timer Functions
      virtual bool SetTimer(uint_ptr nIDEvent,UINT nElapse,PFN_TIMER pfnTimer);
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = TRUE);

      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnNcDraw(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void _001OnClip(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);

      virtual bool is_custom_draw();

      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(class id id);


      virtual ::user::interaction * SetCapture(::user::interaction * pinterface = NULL);
      virtual ::user::interaction * GetCapture();
      virtual ::user::interaction * ReleaseCapture();


      virtual bool has_focus();
      virtual ::user::interaction * SetFocus();
      virtual ::user::interaction * GetFocus();
      virtual bool SetForegroundWindow();
      virtual interaction * GetActiveWindow();
      virtual interaction * SetActiveWindow();

      virtual void walk_pre_translate_tree(signal_details * pobj, ::user::interaction * puiStop = NULL);

      virtual interaction * GetDescendantWindow(id id) const;

      virtual void SetWindowText(const char * lpszString);
      virtual strsize GetWindowText(LPSTR lpszStringBuf,int32_t nMaxCount);
      virtual string GetWindowText();
      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();

      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool IsWindowVisible();

      virtual void _000OnMouse(::message::mouse * pmouse);
      virtual void _000OnKey(::message::key * pkey);
      virtual void _000OnDrag(::message::drag_and_drop * pdrag);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseEnter);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      virtual void _001OnTimer(timer * ptimer);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnUser184);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnCommand);
      DECL_GEN_SIGNAL(_001OnSimpleCommand);
      //DECL_GEN_SIGNAL(_001OnSetSchema);



      virtual DECL_GEN_SIGNAL(_002OnLButtonDown);
      virtual DECL_GEN_SIGNAL(_002OnLButtonUp);
      virtual DECL_GEN_SIGNAL(_002OnMouseMove);
      virtual DECL_GEN_SIGNAL(_002OnMouseEnter);
      virtual DECL_GEN_SIGNAL(_002OnMouseLeave);
      virtual DECL_GEN_SIGNAL(_002OnKeyDown);
      virtual DECL_GEN_SIGNAL(_002OnKeyUp);
      virtual DECL_GEN_SIGNAL(_002OnTimer);


      DECL_GEN_SIGNAL(_001OnBaseWndGetProperty);


      virtual LRESULT _001BaseWndGetProperty(EProperty eproperty,LPARAM lparam);



      virtual bool _001IsPointInside(point64 pt);
      virtual ::user::interaction * _001FromPoint(point64 pt,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz,const char * pszTarget = NULL);

      virtual void pre_translate_message(signal_details * pobj);


      ::user::interaction * get_child_by_name(const char * pszName,int32_t iLevel = -1);
      ::user::interaction * get_child_by_id(id id,int32_t iLevel = -1);


      virtual bool IsAscendant(const interaction * puiIsAscendant) const;
      virtual bool IsParent(const interaction * puiIsParent) const;
      virtual bool IsChild(const interaction * puiIsChild) const;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const;

      virtual ::user::elemental * get_wnd_elemental() const;
      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(UINT nCmd) const;


      virtual ::user::interaction * SetParent(::user::interaction * pui);
      virtual ::user::interaction * SetOwner(::user::interaction * pui);

      virtual ::user::elemental * get_parent() const;

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


      virtual int32_t get_descendant_level(::user::interaction * pui);
      virtual bool is_descendant(::user::interaction * pui,bool bIncludeSelf = false);



      virtual oswindow GetParentHandle() const;


      virtual ::user::interaction * get_focusable_descendant(::user::interaction * pui = NULL);



      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,UINT nFlag = reposDefault,LPRECT lpRectParam = NULL,LPCRECT lpRectClient = NULL,bool bStretch = TRUE);


      virtual ::user::interaction * ChildWindowFromPoint(POINT point);
      virtual ::user::interaction * ChildWindowFromPoint(POINT point,UINT nFlags);


#ifdef WINDOWSEX
      virtual ::user::interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual ::user::interaction * GetNextWindow(UINT nFlag = 0);
#endif

      virtual ::user::interaction * GetTopWindow();

      virtual ::user::interaction * get_next(bool bIgnoreChildren = false,int32_t * piLevel = NULL);

      virtual ::user::interaction * GetLastActivePopup();

      virtual bool is_message_only_window() const;

      virtual void pre_subclass_window();

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      virtual LRESULT DefWindowProc(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual LRESULT call_message_handler(UINT message,WPARAM wparam,LPARAM lparam);

      virtual void message_handler(signal_details * pobj);
      virtual LRESULT message_handler(LPMESSAGE lpmessage);
      virtual void GuieProc(signal_details * pobj);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);


      virtual oswindow get_handle() const;
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();


      template < class T >
      T * GetTypedParent() const
      {

         ::user::interaction * pthis = (::user::interaction *)this;

         ASSERT_VALID(pthis);

         ::user::interaction * pParentWnd = GetParent();  // start with one parent up
         while(pParentWnd != NULL)
         {
            if(dynamic_cast <T *> (pParentWnd) != NULL)
            {
               return dynamic_cast <T *> (pParentWnd);
            }
            pParentWnd = pParentWnd->GetParent();
         }
         return NULL;
      }


      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);







      virtual void _001OnTriggerMouseInside();

      //#ifdef METROWIN
      //      Agile<Windows::UI::Core::CoreWindow> get_os_window();
      //#endif


      virtual void set_viewport_org(::draw2d::graphics * pgraphics);

      virtual void viewport_screen_to_client(POINT * ppt);
      virtual void viewport_client_to_screen(POINT * ppt);
      virtual void viewport_client_to_screen(RECT * ppt);
      virtual void viewport_screen_to_client(RECT * ppt);


      virtual string get_window_default_matter();
      virtual string get_window_icon_matter();
      virtual uint32_t get_window_default_style();
      virtual e_type get_window_type();


      virtual bool on_simple_command(e_simple_command ecommand,lparam lparam,LRESULT & lresult);


      // Window-Management message handler member functions
      virtual bool OnCommand(::message::base * pbase);
      virtual bool OnNotify(::message::base * pbase);
      virtual bool OnChildNotify(::message::base * pbase);



      virtual bool is_selected(::data::item * pitem);

      virtual sp(place_holder) place(::user::interaction * pui);

#if defined(METROWIN) && defined(__cplusplus_winrt)
      static_function Agile<Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction * pui);
      Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static_function Agile<Windows::UI::Core::CoreWindow> get_os_window(interaction * pui)
      {
         return (*s_get_os_window)(pui);
      }
      static_function Agile<Windows::UI::Core::CoreWindow> get_os_window_default(interaction * pui)
      {
         UNREFERENCED_PARAMETER(pui);
         return nullptr;
      }
#endif
      virtual bool _001HasCommandHandler(id id);



      virtual bool track_popup_menu(::user::menu_base_item * pitem,int32_t iFlags,int32_t x,int32_t y);
      virtual bool track_popup_menu(::xml::node * lpnode,int32_t iFlags,int32_t x,int32_t y);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,int32_t x,int32_t y);

      virtual bool track_popup_menu(::user::menu_base_item * pitem,int32_t iFlags,signal_details * pobj);
      virtual bool track_popup_menu(::xml::node * lpnode,int32_t iFlags,signal_details * pobj);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,signal_details * pobj);

      virtual bool track_popup_menu(::user::menu_base_item * pitem,int32_t iFlags);
      virtual bool track_popup_menu(::xml::node * lpnode,int32_t iFlags);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags);


      virtual void WfiEnableFullScreen(bool bEnable = true);
      virtual bool WfiIsFullScreen();
      virtual bool WfiIsFullScreenEnabled();
      virtual bool WfiIsZoomed();
      virtual bool WfiIsIconic();


      virtual bool Wfi(EAppearance eapperance = AppearanceCurrent);

      virtual bool WfiDock(EAppearance eapperance);
      virtual bool WfiClose();
      virtual bool WfiRestore(bool bForceNormal = false);
      virtual bool WfiMinimize();
      virtual bool WfiMaximize();
      virtual bool WfiFullScreen();
      virtual bool WfiUp();
      virtual bool WfiDown();
      virtual bool WfiNotifyIcon();

      virtual bool WfiIsMoving();
      virtual bool WfiIsSizing();

      virtual EAppearance get_appearance();
      virtual EAppearance get_appearance_before();

      virtual bool set_appearance(EAppearance eappearance);
      virtual bool set_appearance_before(EAppearance eappearance);


      virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::object * pliveobject = NULL);

      virtual ::user::interaction * best_top_level_parent(LPRECT lprect);

      virtual index make_zoneing(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,::user::EAppearance * peappearance = NULL,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index best_zoneing(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,::user::EAppearance * peappearance = NULL,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index best_monitor(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index best_wkspace(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index good_restore(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index good_iconify(LPRECT lprect,const RECT & rect=::null_rect(),bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);

      virtual index good_move(LPRECT lprect,const RECT & rect=::null_rect(),UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);

      virtual bool get_rect_normal(LPRECT lprect);


      virtual void set_viewport_offset_x(int x);
      virtual void set_viewport_offset_y(int y);
      virtual void set_viewport_offset(int x,int y);
      virtual void offset_viewport_offset_x(int x);
      virtual void offset_viewport_offset_y(int y);
      virtual void offset_viewport_offset(int x, int y);
      virtual void on_change_viewport_offset();
      virtual void on_viewport_offset(::draw2d::graphics * pgraphics);
      virtual point get_viewport_offset();
      virtual size get_total_size();
      virtual void on_change_view_size();
      virtual size get_page_size();
      virtual point get_parent_viewport_offset();
      virtual point get_ascendant_viewport_offset();
      virtual void get_margin_rect(LPRECT lprectMargin);
      virtual int get_final_x_scroll_bar_width();
      virtual int get_final_y_scroll_bar_width();



      virtual ::user::schema * get_parent_user_schema();


      /*

      static_function sp(::message::base) peek_message(LPMESSAGE lpmsg,::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      static_function sp(::message::base) get_message(LPMESSAGE lpmsg,::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);
      static_function sp(::message::base) peek_message(::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      static_function sp(::message::base) get_message(::user::interaction * pwnd,UINT wMsgFilterMin,UINT wMsgFilterMax);

      virtual sp(::message::base) peek_message(LPMESSAGE lpmsg,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      virtual sp(::message::base) get_message(LPMESSAGE lpmsg,UINT wMsgFilterMin,UINT wMsgFilterMax);
      virtual sp(::message::base) peek_message(UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
      virtual sp(::message::base) get_message(UINT wMsgFilterMin,UINT wMsgFilterMax);

      */


      sp(::message::base) get_base(UINT uiMessage,WPARAM wparam,LPARAM lparam);


      //void transfer_from(::aura::timer_array & ta, interaction * pui);

      virtual window_graphics ** get_window_graphics();

      virtual bool is_composite();

      virtual bool get_window_minimum_size(::size & sizeMin);



      // Up Down Target();


      virtual void UpDownTargetAttach(::user::wndfrm::frame::WorkSetClientInterface * pupdown);
      virtual void UpDownTargetDetach(::user::wndfrm::frame::WorkSetClientInterface * pupdown);

      virtual bool OnUpDownTargetAttach(::user::wndfrm::frame::WorkSetClientInterface * pupdown);
      virtual bool OnUpDownTargetDetach(::user::wndfrm::frame::WorkSetClientInterface * pupdown);

      virtual bool up_down_target_is_up();
      virtual bool up_down_target_is_down();
      virtual bool is_up_down_target();


      void user_interaction_on_destroy();
      void user_interaction_on_hide();


      virtual string calc_data_id();


      virtual void _001GetXScrollInfo(scroll_info & info);
      virtual void _001GetYScrollInfo(scroll_info & info);
      virtual void layout_scroll_bar();

      // view support
      virtual void on_update(::user::impact * pSender,LPARAM lHint,::object* pHint);

      virtual void keyboard_focus_OnKeyDown(signal_details * pobj);

   };


} // namespace user

// timer_ui works correctly when timer is originated from SetTimer call
inline ::user::interaction * timer_ui(::timer * ptimer)
{

   return (::user::interaction *) ptimer->m_pvoidData;

}


#endif // CA2_APP_BASE_USER_INTERACTION_H



