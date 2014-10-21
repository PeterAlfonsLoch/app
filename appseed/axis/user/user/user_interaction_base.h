#pragma once


namespace user
{


   class CLASS_DECL_AXIS interaction_base:
      virtual public elemental,
      virtual public command_target,
      virtual public text_interface,
      virtual public check_interface,
      virtual public draw_interface,
      virtual public ::user::schema
   {
   public:

      enum RepositionFlags
      {

         reposDefault = 0,
         reposQuery = 1,
         reposExtra = 2,
         reposNoPosLeftOver = 0x8000

      };


      enum e_message
      {

         MessageBaseWndGetProperty = WM_USER + 96,
         MessageProperty,
         MessageGeneralEvent,
         message_simple_command = WM_APP + 1985,
         message_set_schema = WM_APP + 1984 + 23 + 49,

      };


      enum EProperty
      {

         PropertyBaseWndInterface = 0,
         PropertyDrawBaseWndInterface

      };


      enum EGeneralEvent
      {

         GeneralEventPosCreate1,
         GeneralEventPosCreate2,
         GeneralEventPosCreate3,
         GeneralEventPosCreate4,
         GeneralEventPosCreate5

      };

      enum e_simple_command
      {

         simple_command_load_window_rect,
         simple_command_update_frame_title,
         simple_command_set_edit_file,
         simple_command_layout,
         simple_command_full_screen

      };


      enum e_type
      {

         type_window,
         type_frame,
         type_view

      };





      interaction_base();
      interaction_base(sp(::aura::application) papp);
      virtual ~interaction_base();


      virtual bool create_message_queue(const char * pszName);


#if defined(METROWIN) || defined(APPLE_IOS)
      virtual bool initialize(native_window_initialize * pinitialize);
#endif


//      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = true);
      virtual void _000OnDraw(::draw2d::graphics * pdc);

      virtual void PreSubClassWindow();


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
      virtual void ScreenToClient(__point64 * lppoint);
      virtual rect GetWindowRect();
      virtual rect64 GetWindowRect64();

      virtual bool SetPlacement(const RECT & lprect,UINT nFlags = SWP_SHOWWINDOW);
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
      virtual bool defer_set_window_pos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags); // only set_windows_pos if GetParent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      virtual int32_t SetWindowRgn(HRGN hRgn,bool bRedraw);
      virtual int32_t GetWindowRgn(HRGN hRgn);


      virtual void install_message_handling(::message::dispatch * pinterface);

      virtual void _on_start_user_message_handler();


      virtual void UpdateWindow();
      virtual void Invalidate(bool bErase = TRUE);


      virtual bool RedrawOptimize(LPRECT lprectOut,LPCRECT lpcrect1,LPCRECT lpcrect2);
      virtual void RedrawOptimize(rect_array & array);






      virtual void _001RedrawWindow();




      enum EOptimize
      {

         OptimizeNone,
         OptimizeThis

      };


      void Optimize008(
         ::user::oswindow_tree::Array & oswindowtreea,
         const RECT & rect);

      EOptimize Optimize008(
         ::user::oswindow_tree::Array & oswindowtreea,
         HRGN hrgn);

      EOptimize Optimize008(
         ::user::oswindow_tree & oswindowtree,
         HRGN hrgn);



      void TwfGetWndArray(::user::interaction_spa & wndpa);
      void TwfGetWndArray(::user::oswindow_array & oswindowa);

      virtual bool Redraw(rect_array & recta);
      virtual bool Redraw(LPCRECT lprect = NULL,::draw2d::region * prgn = NULL);
      virtual bool Redraw(::draw2d::graphics * pdc);

      void _001BaseWndInterfaceMap();

      virtual void message_handler(signal_details * pobj);
      virtual LRESULT message_handler(LPMESSAGE lpmessage);
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



      virtual sp(interaction) first_child();
      virtual sp(interaction) last_child();
      virtual sp(interaction) last_sibling();
      virtual sp(interaction) next_sibling();
      virtual sp(interaction) previous_sibling();
      virtual sp(interaction) first_sibling();
      virtual sp(interaction) next_sibling(sp(interaction) pui);
      virtual sp(interaction) previous_sibling(sp(interaction) pui);

      virtual sp(interaction) bottom_child();
      virtual sp(interaction) top_child();
      virtual sp(interaction) bottom_sibling();
      virtual sp(interaction) under_sibling();
      virtual sp(interaction) above_sibling();
      virtual sp(interaction) top_sibling();
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
      virtual id   run_modal_loop(::user::interaction * pui,uint32_t dwFlags = 0,::aura::live_object * pliveobject = NULL);
      virtual id   RunModalLoop(uint32_t dwFlags = 0,::aura::live_object * pliveobject = NULL);
      virtual id   _001RunModalLoop(uint32_t dwFlags = 0,::aura::live_object * pliveobject = NULL);
      virtual bool ContinueModal(int32_t iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual sp(::user::interaction) get_os_focus_uie();


      virtual void on_keyboard_focus(::user::keyboard_focus * pfocus);


      virtual void _001UpdateScreen();
      virtual void _001UpdateBuffer();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();




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


      virtual bool create_window(const RECT & rect, sp(interaction)pparent,id id);
      virtual bool create_window(const char * lpszClassName, const char * lpszWindowName,uint32_t dwStyle, const RECT & rect, sp(interaction) pParentWnd,id id, sp(::create_context) pContext = NULL);
      virtual bool create_window_ex(uint32_t dwExStyle,const char * lpszClassName, const char * lpszWindowName,uint32_t dwStyle, const RECT & rect,  sp(interaction) pParentWnd,id id,LPVOID lpParam = NULL);
      enum AdjustType { adjustBorder = 0,adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect,UINT nAdjustType = adjustBorder);

      virtual bool IsTopParentActive();
      virtual void ActivateTopParent();

      virtual bool DestroyWindow();


#ifdef WINDOWS

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL, ::draw2d::region* prgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

#else

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL, ::draw2d::region* prgnUpdate = NULL, UINT flags = 0);

#endif


//      virtual void UpdateWindow();
      virtual void SetRedraw(bool bRedraw = TRUE);
      virtual bool GetUpdateRect(LPRECT lpRect,bool bErase = FALSE);
      virtual int32_t GetUpdateRgn(::draw2d::region* pRgn,bool bErase = FALSE);
//      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect,bool bErase = TRUE);
      virtual void InvalidateRgn(::draw2d::region* pRgn,bool bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = TRUE);


      virtual uint32_t GetStyle() const;
      virtual uint32_t GetExStyle() const;
      virtual LRESULT Default();

      virtual LRESULT send(::message::base * pbase);
      virtual bool post(::message::base * pbase);
      virtual LRESULT send_message(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0);

#ifdef LINUX

      virtual LRESULT send_message(XEvent * pevent);

#endif

      virtual bool post_message(UINT message,WPARAM wParam = 0,lparam lParam = 0);
      virtual bool post_simple_command(e_simple_command ecommand,lparam lParam = 0);

      virtual bool ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);
      virtual bool ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0);
      virtual bool ShowWindow(int32_t nCmdShow);

      // timer Functions
      virtual uint_ptr SetTimer(uint_ptr nIDEvent,UINT nElapse,void (CALLBACK* lpfnTimer)(oswindow,UINT,uint_ptr,uint32_t));
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual bool is_window_enabled();
//      virtual bool enable_window(bool bEnable = TRUE);

      virtual void _001Print(::draw2d::graphics * pdc);
//      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);


      virtual bool IsAscendant(const interaction * puiIsAscendant) const;
      virtual bool IsParent(const interaction * puiIsParent) const;
      virtual bool IsChild(const interaction * puiIsChild) const;
      virtual bool IsDescendant(const interaction * puiIsDescendant) const;


      virtual id GetDlgCtrlId() const;
      virtual id SetDlgCtrlId(class id id);

      virtual sp(interaction) SetCapture(sp(interaction) pinterface = NULL);
      virtual sp(interaction) GetCapture();
      virtual sp(interaction) ReleaseCapture();


      virtual bool has_focus();
      virtual sp(interaction) SetFocus();
      virtual bool SetForegroundWindow();
      virtual interaction * GetActiveWindow();
      virtual interaction * SetActiveWindow();


      virtual interaction * GetDescendantWindow(id id) const;

      virtual void SetWindowText(const char * lpszString);
      virtual strsize GetWindowText(LPTSTR lpszStringBuf,int32_t nMaxCount);
      virtual string get_window_text();
      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();


      virtual bool IsWindowVisible();



      virtual bool _001IsPointInside(point64 pt);
      virtual sp(interaction) _001FromPoint(point64 pt,bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz,const char * pszTarget = NULL);

      sp(interaction) get_child_by_name(const char * pszName,int32_t iLevel = -1);
      sp(interaction) get_child_by_id(id id,int32_t iLevel = -1);


      virtual sp(::user::interaction) GetWindow() const;
      virtual sp(::user::interaction) GetWindow(UINT nCmd) const;


      virtual sp(::user::interaction) SetParent(sp(::user::interaction) pui);
      virtual sp(::user::interaction) SetOwner(sp(::user::interaction) pui);


      virtual sp(::user::interaction) GetTopWindow() const;
      virtual ::user::interaction * GetParent() const;
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


      virtual int32_t get_descendant_level(sp(::user::interaction) pui);
      virtual bool is_descendant(sp(::user::interaction) pui,bool bIncludeSelf = false);
      virtual sp(::user::interaction) get_focusable_descendant(sp(::user::interaction) pui = NULL);


//      virtual interaction_impl * get_wnd() const;




      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIDLeftOver,UINT nFlag = reposDefault,LPRECT lpRectParam = NULL,LPCRECT lpRectClient = NULL,bool bStretch = TRUE);


      virtual sp(interaction) ChildWindowFromPoint(POINT point);
      virtual sp(interaction) ChildWindowFromPoint(POINT point,UINT nFlags);


#ifdef WINDOWSEX
      virtual sp(interaction) GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual sp(interaction) GetNextWindow(UINT nFlag = 0);
#endif

      virtual sp(interaction) get_next(bool bIgnoreChildren = false,int32_t * piLevel = NULL);

      virtual sp(interaction) GetLastActivePopup();

      virtual bool is_message_only_window() const;

      virtual void pre_subclass_window();

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      virtual LRESULT DefWindowProc(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual LRESULT call_message_handler(UINT message,WPARAM wparam,LPARAM lparam);

//      virtual void message_handler(signal_details * pobj);
//      virtual LRESULT message_handler(LPMESSAGE lpmessage);
      virtual void GuieProc(signal_details * pobj);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);


      oswindow get_safe_handle() const;
      virtual oswindow get_handle() const;
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();


      virtual bool can_merge(sp(::user::interaction) pui);
      virtual bool merge(sp(::user::interaction) pui);


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

      virtual sp(place_holder) place(sp(::user::interaction) pui);

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

      virtual EAppearance get_appearance();
      virtual EAppearance get_appearance_before();

      virtual bool set_appearance(EAppearance eappearance);
      virtual bool set_appearance_before(EAppearance eappearance);


      virtual void show_keyboard(bool bShow = true);

      virtual void keep_alive(::aura::live_object * pliveobject = NULL);


      virtual window_graphics * & get_window_graphics();


      virtual bool is_composite();

   };


} // namespace user





