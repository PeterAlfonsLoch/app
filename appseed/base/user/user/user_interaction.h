#ifndef CA2_APP_BASE_USER_INTERACTION_H
#define CA2_APP_BASE_USER_INTERACTION_H


#define DRAWDD() virtual void _001OnDraw(::draw2d::graphics * pgraphics)


namespace user
{


   class interaction_impl_base;


   class CLASS_DECL_BASE interaction:
      virtual public interaction_base
   {
   public:


      bool                                m_bVisible;
      bool                                m_bVoidPaint;
      bool                                m_bLockWindowUpdate;
      bool                                m_bEnableSaveWindowRect;

      draw_interface *                    m_pdrawinterfaceBackground;
      bool                                m_bBackgroundBypass;
      

      ::user::interaction *               m_pparent;

      sp(mutex)                           m_spmutex;
      EAppearance                         m_eappearance;
      EAppearance                         m_eappearanceBefore;
      sp(interaction_impl_base)           m_pimpl;


      ptr_array < interaction >           m_uiptraChild;
      string                              m_strName;
      id                                  m_id;
      interaction *                       m_puiOwner;
      UINT                                m_nFlags;      // see WF_ flags above
      bool                                m_bCursorInside;
      ::visual::e_cursor                  m_ecursor;
      int32_t                             m_iModal;
      int32_t                             m_iModalCount;
      bool                                m_bRectOk;
      sp(::base::session)                 m_psession;
      bool                                m_bMessageWindow;

#if defined(WINDOWS) || defined(LINUX) || defined(APPLEOS)

      comparable_array < int_ptr >        m_iaModalThread;

#else

      comparable_array < pthread_t >      m_iaModalThread;

#endif

      id                                  m_idModalResult; // for return values from interaction_impl::RunModalLoop

      sp(::user::menu_base)               m_spmenuPopup;

      int32_t                             m_nModalResult; // for return values from ::interaction_impl::RunModalLoop


      interaction();
      interaction(sp(::base::application) papp);
      virtual ~interaction();

      void user_interaction_common_construct();


      virtual bool create_message_queue(const char * pszName,::message_queue_listener * pcallback = NULL);
#if defined(METROWIN) || defined(APPLE_IOS)
      virtual bool initialize(native_window_initialize * pinitialize);
#endif



      virtual void on_select();

      virtual bool is_place_holder();

      ::visual::e_cursor get_cursor();
      void set_cursor(::visual::e_cursor ecursor);


      void set_timer(spa(timer_item) timera);


      virtual bool IsWindow() const;

      virtual LONG get_window_long(int32_t nIndex) const;
      virtual LONG set_window_long(int32_t nIndex,LONG lValue);

      virtual LONG_PTR get_window_long_ptr(int32_t nIndex) const;
      virtual LONG_PTR set_window_long_ptr(int32_t nIndex,LONG_PTR lValue);

      virtual bool on_before_set_parent(sp(interaction) pinterface);
      virtual void on_set_parent(sp(interaction) pinterface);


      virtual sp(interaction) get_bottom_child();
      virtual sp(interaction) get_top_child();
      virtual sp(interaction) under_sibling();
      virtual sp(interaction) above_sibling();

      virtual sp(interaction) above_sibling(sp(interaction) pui);
      virtual sp(interaction) under_sibling(sp(interaction) pui);


      virtual void mouse_hover_add(sp(::user::interaction) pinterface);
      virtual void mouse_hover_remove(sp(::user::interaction) pinterface);


      virtual bool CheckAutoCenter();

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      // dialog support
      void UpdateDialogControls(command_target* pTarget,bool bDisableIfNoHndler);
      virtual void CenterWindow(sp(interaction) pAlternateOwner = NULL);
      virtual id   run_modal_loop(::user::interaction * pui,uint32_t dwFlags = 0,::base::live_object * pliveobject = NULL);
      virtual id   RunModalLoop(uint32_t dwFlags = 0,::base::live_object * pliveobject = NULL);
      virtual id   _001RunModalLoop(uint32_t dwFlags = 0,::base::live_object * pliveobject = NULL);
      virtual bool ContinueModal(int32_t iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual sp(::user::interaction) get_os_focus_uie();


      virtual void on_keyboard_focus(::user::keyboard_focus * pfocus);


      virtual void _001UpdateWindow();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();

      using ::user::interaction_base::GetWindowRect;
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


      virtual bool pre_create_window(CREATESTRUCT& cs);


      virtual bool subclass_window(oswindow posdata);
      virtual oswindow unsubclass_window();


      virtual bool create(sp(interaction)pparent,id id);
      virtual bool create_window(const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd,id id,
         sp(::create_context) pContext = NULL);
      using ::request_interface::create;
      virtual bool create(const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd,id id,
         sp(::create_context) pContext = NULL);
      virtual bool CreateEx(uint32_t dwExStyle,const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd,id id,
         LPVOID lpParam = NULL);
      virtual bool create_window_ex(uint32_t dwExStyle,const char * lpszClassName,
         const char * lpszWindowName,uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd,id id,
         LPVOID lpParam = NULL);
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
      virtual uint_ptr SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t));
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = TRUE);

      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnNcDraw(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);


      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(class id id);


      virtual sp(interaction) SetCapture(sp(interaction) pinterface = NULL);
      virtual sp(interaction) GetCapture();
      virtual sp(interaction) ReleaseCapture();


      virtual bool has_focus();
      virtual sp(interaction) SetFocus();
      virtual bool SetForegroundWindow();
      virtual sp(interaction) GetActiveWindow();
      virtual sp(interaction) SetActiveWindow();

      virtual void WalkPreTranslateTree(signal_details * pobj);
      virtual void WalkPreTranslateTree(sp(::user::interaction) puiStop,signal_details * pobj);

      virtual sp(interaction) GetDescendantWindow(id id) const;

      virtual void SetWindowText(const char * lpszString);
      virtual strsize GetWindowText(LPTSTR lpszStringBuf,int32_t nMaxCount);
      virtual string get_window_text();
      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();

      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool IsWindowVisible();

      virtual void _000OnMouse(::message::mouse * pmouse);
      virtual void _000OnKey(::message::key * pkey);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseEnter);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnTimer);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnMove);
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


      DECL_GEN_VSIGNAL(_001OnBaseWndGetProperty);


      virtual LRESULT _001BaseWndGetProperty(EProperty eproperty,LPARAM lparam);



      virtual bool _001IsPointInside(point64 pt);
      virtual sp(interaction) _001FromPoint(point64 pt,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz,const char * pszTarget = NULL);

      virtual void pre_translate_message(signal_details * pobj);


      sp(interaction) get_child_by_name(const char * pszName,int32_t iLevel = -1);
      sp(interaction) get_child_by_id(id id,int32_t iLevel = -1);


      virtual bool IsAscendant(const interaction * puiIsAscendant) const;
      virtual bool IsParent(const interaction * puiIsParent) const;
      virtual bool IsChild(const interaction * puiIsChild) const;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const;


      virtual sp(::user::interaction) GetWindow() const;
      virtual sp(::user::interaction) GetWindow(UINT nCmd) const;


      virtual sp(::user::interaction) SetParent(sp(::user::interaction) pui);
      virtual sp(::user::interaction) SetOwner(sp(::user::interaction) pui);


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


      virtual int32_t get_descendant_level(sp(::user::interaction) pui);
      virtual bool is_descendant(sp(::user::interaction) pui,bool bIncludeSelf = false);



      virtual oswindow GetParentHandle() const;


      virtual sp(::user::interaction) get_focusable_descendant(sp(::user::interaction) pui = NULL);



      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,UINT nFlag = reposDefault,LPRECT lpRectParam = NULL,LPCRECT lpRectClient = NULL,bool bStretch = TRUE);


      virtual sp(interaction) ChildWindowFromPoint(POINT point);
      virtual sp(interaction) ChildWindowFromPoint(POINT point,UINT nFlags);


#ifdef WINDOWSEX
      virtual sp(interaction) GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual sp(interaction) GetNextWindow(UINT nFlag = 0);
#endif

      virtual sp(interaction) GetTopWindow();

      virtual sp(interaction) get_next(bool bIgnoreChildren = false,int32_t * piLevel = NULL);

      virtual sp(interaction) GetLastActivePopup();

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


      oswindow get_safe_handle() const;
      virtual oswindow get_handle() const;
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();


      template < class T >
      T * GetTypedParent() const
      {

         ::user::interaction * pthis = (::user::interaction *)this;

         ASSERT_VALID(pthis);

         sp(interaction) pParentWnd = GetParent();  // start with one parent up
         while(pParentWnd != NULL)
         {
            if(dynamic_cast <T *> (pParentWnd.m_p) != NULL)
            {
               return dynamic_cast <T *> (pParentWnd.m_p);
            }
            pParentWnd = pParentWnd->GetParent();
         }
         return NULL;
      }


      virtual bool can_merge(sp(::user::interaction) pui);
      virtual bool merge(sp(::user::interaction) pui);


      virtual ::user::schema *      get_user_schema();

      //virtual bool _001SetSchema(::user::schema * pschema);
      //virtual bool _008SetSchema(::user::schema * pschema); // _008 - Descendants
      //virtual bool _009SetSchema(::user::schema * pschema); // _009 - Own and Descendants

      virtual COLORREF              get_background_color();
      virtual COLORREF              get_color();
      virtual ::draw2d::font_sp     get_font();
      virtual ETranslucency         _001GetTranslucency();
      virtual bool                  _001IsBackgroundBypass();
      virtual bool                  _001IsTransparent();
      virtual bool                  _001IsTranslucent();
      virtual bool                  _001HasTranslucency();





      virtual void _001OnTriggerMouseInside();

      //#ifdef METROWIN
      //      Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window();
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

      virtual sp(place_holder) place(sp(::user::interaction) pui);

#if defined(METROWIN) && defined(__cplusplus_winrt)
      static Platform::Agile<Windows::UI::Core::CoreWindow>(*s_get_os_window)(interaction * pui);
      Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window()
      {
         return get_os_window(this);
      }
      static Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window(interaction * pui)
      {
         return (*s_get_os_window)(pui);
      }
      static Platform::Agile<Windows::UI::Core::CoreWindow> get_os_window_default(interaction * pui)
      {
         UNREFERENCED_PARAMETER(pui);
         return nullptr;
      }
#endif
      virtual bool _001HasCommandHandler(id id);



      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,int32_t x,int32_t y);
      virtual bool track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,int32_t x,int32_t y);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,int32_t x,int32_t y);

      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags,signal_details * pobj);
      virtual bool track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags,signal_details * pobj);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags,signal_details * pobj);

      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem,int32_t iFlags);
      virtual bool track_popup_menu(sp(::xml::node) lpnode,int32_t iFlags);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter,int32_t iFlags);


      virtual void WfiEnableFullScreen(bool bEnable = true);
      virtual bool WfiIsFullScreen();
      virtual bool WfiIsFullScreenEnabled();
      virtual bool WfiIsZoomed();
      virtual bool WfiIsIconic();


      virtual bool WfiClose();
      virtual bool WfiRestore(bool bForceNormal = false);
      virtual bool WfiMinimize();
      virtual bool WfiMaximize();
      virtual bool WfiFullScreen();
      virtual bool WfiUp();
      virtual bool WfiDown();
      virtual bool WfiNotifyIcon();

      virtual EAppearance get_appearance();
      virtual EAppearance get_appearance_before();

      virtual bool set_appearance(EAppearance eappearance);
      virtual bool set_appearance_before(EAppearance eappearance);


      virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::base::live_object * pliveobject = NULL);

      virtual sp(::user::interaction) best_top_level_parent(LPRECT lprect);

      virtual index best_monitor(LPRECT lprect,LPCRECT lpcrect=NULL,bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index best_wkspace(LPRECT lprect,LPCRECT lpcrect=NULL,bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index good_restore(LPRECT lprect,LPCRECT lpcrect=NULL,bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);
      virtual index good_iconify(LPRECT lprect,LPCRECT lpcrect=NULL,bool bSet = false,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);

      virtual index good_move(LPRECT lprect,LPCRECT lpcrect=NULL,UINT uiSwpFlags = SWP_SHOWWINDOW | SWP_FRAMECHANGED,int_ptr iZOrder = ZORDER_TOP);

      virtual bool get_rect_normal(LPRECT lprect);

      virtual point get_scroll_position();
      virtual point get_parent_scroll_position();
      virtual point get_ascendant_scroll_position();




   };


} // namespace user


#endif // CA2_APP_BASE_USER_INTERACTION_H







