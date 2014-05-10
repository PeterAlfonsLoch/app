#ifndef CA2_APP_BASE_USER_INTERACTION_H
#define CA2_APP_BASE_USER_INTERACTION_H


#define DRAWDD() virtual void _001OnDraw(::draw2d::graphics * pgraphics)

namespace user
{


   class CLASS_DECL_BASE interaction :
      virtual public window_interface
   {
   public:


      enum e_message
      {

         message_simple_command = WM_APP + 1985

      };


      enum e_simple_command
      {

         simple_command_load_window_rect,
         simple_command_update_frame_title,
         simple_command_set_edit_file,
         simple_command_layout

      };


      enum e_type
      {
         
         type_window,
         type_frame,
         type_view

      };



      class CLASS_DECL_BASE timer_item :
         virtual public element
      {
      public:


         sp(interaction)        m_pui;
         uint_ptr             m_uiId;
         UINT                 m_uiElapse;
         UINT                 m_uiLastSent;

         bool check(single_lock & sl);


      };

      class CLASS_DECL_BASE timer_array :
         virtual public spa(interaction)
      {
      public:


         mutex                               m_mutex;
         spa(timer_item)                     m_timera;
         index                               m_iItem;


         timer_array(sp(base_application) papp);


         uint_ptr set(sp(interaction) pui, uint_ptr uiId, UINT uiElapse);
         void check();
         bool unset(sp(interaction) pui, uint_ptr uiId);
         void unset(sp(interaction) pui);
         void detach(spa(timer_item) & timera, sp(interaction) pui);
         void transfer(::window_sp pwindow, sp(interaction) pui);
         sp(interaction) find(sp(element) pca);
         index find(sp(interaction) pui, uint_ptr uiId);
         index find_from(sp(interaction) pui, index iStart);

         virtual void assert_valid() const;
         virtual void dump(dump_context & dc) const;

         };



      virtual bool create_message_queue(const char * pszName, ::message_queue_listener * pcallback = NULL);
#if defined(METROWIN) || defined(APPLE_IOS)
      virtual bool initialize(::r::native_window_initialize * pinitialize);
#endif



      sp(mutex)                           m_spmutex;
      EAppearance                         m_eappearance;
      sp(interaction)                     m_pimpl;
      static sp(interaction)                g_puiMouseMoveCapture;
      spa(interaction)                    m_uiptraChild;
      string                              m_strName;
      id                                  m_id;
      sp(interaction)                       m_puiOwner;
      UINT                                m_nFlags;      // see WF_ flags above
      bool                                m_bCursorInside;
      ::visual::e_cursor                  m_ecursor;
      int32_t                                 m_iModal;
      int32_t                                 m_iModalCount;
      bool                                m_bRectOk;
      sp(base_session)                  m_psession;
      bool                                m_bMessageWindow;

#if defined(WINDOWS) || defined(LINUX) || defined(APPLEOS)

      comparable_array < int_ptr >        m_iaModalThread;

#else

      comparable_array < pthread_t >      m_iaModalThread;

#endif

      id                                  m_idModalResult; // for return values from window::RunModalLoop
      COLORREF                            m_crDefaultBackgroundColor;
      sp(::thread)                        m_pthread;

      sp(::user::menu_base)               m_spmenuPopup;

      COLORREF                            m_crText;


      interaction();
      interaction(sp(base_application) papp);
      virtual ~interaction();


      virtual void on_select();

      virtual bool is_place_holder();

      ::visual::e_cursor get_cursor();
      void set_cursor(::visual::e_cursor ecursor);


      void set_timer(spa(timer_item) timera);


      virtual bool IsWindow();

      virtual LONG GetWindowLong(int32_t nIndex);
      virtual LONG SetWindowLong(int32_t nIndex, LONG lValue);


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
      void UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHndler);
      virtual void CenterWindow(sp(interaction) pAlternateOwner = NULL);
      virtual id   RunModalLoop(uint32_t dwFlags = 0, ::core::live_object * pliveobject = NULL);
      virtual bool ContinueModal(int32_t iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);

      // Dialog data support
      virtual bool update_data(bool bSaveAndValidate = true);


      virtual sp(::user::interaction) get_os_focus_uie();


      virtual void _001WindowMinimize();
      virtual void _001WindowMaximize();
      virtual void _001WindowFullScreen();
      virtual void _001WindowRestore();


      virtual void GetClientRect(LPRECT lprect);
      virtual void GetClientRect(__rect64 * lprect);
      virtual void GetWindowRect(LPRECT lprect);
      virtual void GetWindowRect(__rect64 * lprect);
      virtual rect GetWindowRect();
      virtual rect64 GetWindowRect64();
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
      virtual bool SetWindowPos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags = SWP_SHOWWINDOW);
      virtual bool defer_set_window_pos(int32_t z, int32_t x, int32_t y, int32_t cx, int32_t cy, UINT nFlags); // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
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


      virtual bool create(sp(interaction)pparent, id id);
      virtual bool create_window(const char * lpszClassName,
         const char * lpszWindowName, uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd, id id,
         sp(::create_context) pContext = NULL);
      using ::request_interface::create;
      virtual bool create(const char * lpszClassName,
         const char * lpszWindowName, uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd, id id,
         sp(::create_context) pContext = NULL);
      virtual bool CreateEx(uint32_t dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd, id id,
         LPVOID lpParam = NULL);
      virtual bool create_window_ex(uint32_t dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, uint32_t dwStyle,
         const RECT& rect,
         sp(interaction) pParentWnd, id id,
         LPVOID lpParam = NULL);
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
      virtual sp(::user::frame_window) GetParentFrame();

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
      virtual bool GetUpdateRect(LPRECT lpRect, bool bErase = FALSE);
      virtual int32_t GetUpdateRgn(::draw2d::region* pRgn, bool bErase = FALSE);
      virtual void Invalidate(bool bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect, bool bErase = TRUE);
      virtual void InvalidateRgn(::draw2d::region* pRgn, bool bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::draw2d::region* pRgn);
      virtual void ShowOwnedPopups(bool bShow = TRUE);


      virtual uint32_t GetStyle();
      virtual uint32_t GetExStyle();
      virtual LRESULT Default();

      virtual LRESULT send(::message::base * pbase);
      virtual bool post(::message::base * pbase);
      virtual LRESULT send_message(UINT uiMessage, WPARAM wparam = 0, lparam lparam = 0);

#ifdef LINUX

      virtual LRESULT send_message(XEvent * pevent);

#endif

      virtual bool post_message(UINT message, WPARAM wParam = 0, lparam lParam = 0);
      virtual bool post_simple_command(e_simple_command ecommand, lparam lParam = 0);

      virtual bool ModifyStyle(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags = 0);
      virtual bool ModifyStyleEx(uint32_t dwRemove, uint32_t dwAdd, UINT nFlags = 0);
      virtual bool ShowWindow(int32_t nCmdShow);
      virtual bool is_frame_window();

      // timer Functions
      virtual uint_ptr SetTimer(uint_ptr nIDEvent, UINT nElapse, void (CALLBACK* lpfnTimer)(oswindow, UINT, uint_ptr, uint32_t));
      virtual bool KillTimer(uint_ptr nIDEvent);

      virtual bool is_window_enabled();
      virtual bool enable_window(bool bEnable = TRUE);

      virtual void _001Print(::draw2d::graphics * pdc);
      virtual void _000OnDraw(::draw2d::graphics *pdc);
      virtual void _001DrawThis(::draw2d::graphics *pdc);
      virtual void _001DrawChildren(::draw2d::graphics *pdc);
      virtual void _001OnDraw(::draw2d::graphics *pdc);
      virtual void draw_control_background(::draw2d::graphics *pdc);

      virtual bool IsChild(interaction * pui);
      virtual window_interface * window_interface_get_parent();
      virtual ::user::interaction * get_parent();
      virtual ::user::interaction * set_parent(::user::interaction * puiParent);
      virtual oswindow get_parent_handle();
      virtual ::user::interaction * get_parent_base();
      virtual ::user::interaction * set_parent_base(::user::interaction * puiParent);

      virtual id GetDlgCtrlId();
      virtual id SetDlgCtrlId(class id id);

      virtual sp(interaction) set_capture(sp(interaction) pinterface = NULL);
      virtual sp(interaction) get_capture();
      virtual sp(interaction) release_capture();


      virtual bool has_focus();
      virtual sp(interaction) SetFocus();
      virtual bool SetForegroundWindow();
      virtual sp(interaction) GetActiveWindow();
      virtual sp(interaction) SetActiveWindow();

      virtual void WalkPreTranslateTree(signal_details * pobj);
      virtual void WalkPreTranslateTree(sp(::user::interaction) puiStop, signal_details * pobj);

      virtual sp(interaction) GetDescendantWindow(id id);

      virtual void SetWindowText(const char * lpszString);
      virtual strsize GetWindowText(LPTSTR lpszStringBuf, int32_t nMaxCount);
      virtual string get_window_text();
      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();
      virtual void SetFont(::draw2d::font* pFont, bool bRedraw = TRUE);
      virtual ::draw2d::font* GetFont();

      virtual void set_text_color(COLORREF crText);

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



      virtual DECL_GEN_SIGNAL(_002OnLButtonDown);
         virtual DECL_GEN_SIGNAL(_002OnLButtonUp);
         virtual DECL_GEN_SIGNAL(_002OnMouseMove);
         virtual DECL_GEN_SIGNAL(_002OnMouseEnter);
         virtual DECL_GEN_SIGNAL(_002OnMouseLeave);
         virtual DECL_GEN_SIGNAL(_002OnKeyDown);
         virtual DECL_GEN_SIGNAL(_002OnKeyUp);
         virtual DECL_GEN_SIGNAL(_002OnTimer);



         virtual bool _001IsPointInside(point64 pt);
      virtual sp(interaction) _001FromPoint(point64 pt, bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz, const char * pszTarget = NULL);

      sp(interaction) get_child_by_name(const char * pszName, int32_t iLevel = -1);
      sp(interaction) get_child_by_id(id id, int32_t iLevel = -1);

      virtual sp(::user::frame_window) EnsureParentFrame();
      virtual sp(interaction) GetTopLevelParent();
      virtual sp(interaction) EnsureTopLevelParent();
      virtual sp(::user::frame_window) GetTopLevelFrame();
      virtual void SendMessageToDescendants(UINT message, WPARAM wParam = 0, lparam lParam = 0, bool bDeep = TRUE, bool bOnlyPerm = FALSE);
      virtual void pre_translate_message(signal_details * pobj);


      virtual int32_t get_descendant_level(sp(::user::interaction) pui);
      virtual bool is_descendant(sp(::user::interaction) pui, bool bIncludeSelf = false);
      virtual sp(::user::interaction) get_focusable_descendant(sp(::user::interaction) pui = NULL);


      virtual window * get_wnd();

      
      enum RepositionFlags
      {
         
         reposDefault = 0,
         reposQuery = 1,
         reposExtra = 2,
         reposNoPosLeftOver = 0x8000
            
      };
      

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlag = reposDefault, LPRECT lpRectParam = NULL, LPCRECT lpRectClient = NULL, bool bStretch = TRUE);

      virtual sp(interaction) get_owner();
      virtual void set_owner(sp(interaction) pui);

      virtual sp(interaction) ChildWindowFromPoint(POINT point);
      virtual sp(interaction) ChildWindowFromPoint(POINT point, UINT nFlags);


#ifdef WINDOWSEX
      virtual sp(interaction) GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual sp(interaction) GetNextWindow(UINT nFlag = 0);
#endif

      virtual sp(interaction) GetTopWindow();

      virtual sp(interaction) get_next(bool bIgnoreChildren = false, int32_t * piLevel = NULL);

      virtual sp(interaction) GetWindow(UINT nCmd);
      virtual sp(interaction) GetLastActivePopup();

      virtual bool is_message_only_window() const;

      virtual void pre_subclass_window();

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, lparam lparam);
      virtual void message_handler(signal_details * pobj);
      virtual LRESULT message_handler(LPMESSAGE lpmessage);
      virtual void GuieProc(signal_details * pobj);

      virtual void _001DeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);


      oswindow get_safe_handle();
      virtual oswindow get_handle();
      virtual bool attach(oswindow oswindow_New);
      virtual oswindow detach();


      template < class T >
      T * GetTypedParent()
      {
         ASSERT_VALID(this);

         sp(interaction) pParentWnd = get_parent();  // start with one parent up
         while (pParentWnd != NULL)
         {
            if (dynamic_cast < T * > (pParentWnd.m_p) != NULL)
            {
               return dynamic_cast < T * > (pParentWnd.m_p);
            }
            pParentWnd = pParentWnd->get_parent();
         }
         return NULL;
      }


      virtual bool can_merge(sp(::user::interaction) pui);
      virtual bool merge(sp(::user::interaction) pui);


      virtual COLORREF get_background_color();
      virtual void set_default_background_color(COLORREF crDefaultBackgroundColor);

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


      virtual bool on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult);


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



      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags, int32_t x, int32_t y);
      virtual bool track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags, int32_t x, int32_t y);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags, int32_t x, int32_t y);

      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags, signal_details * pobj);
      virtual bool track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags, signal_details * pobj);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags, signal_details * pobj);

      virtual bool track_popup_menu(sp(::user::menu_base_item) pitem, int32_t iFlags);
      virtual bool track_popup_menu(sp(::xml::node) lpnode, int32_t iFlags);
      virtual bool track_popup_xml_matter_menu(const char * pszMatter, int32_t iFlags);

      
      virtual void WfiEnableFullScreen(bool bEnable = true);
      virtual bool WfiIsFullScreen();
      virtual bool WfiIsFullScreenEnabled();
      virtual bool WfiIsZoomed();
      virtual bool WfiIsIconic();


      virtual bool WfiClose();
      virtual bool WfiRestore();
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

   };


} // namespace user


#endif // CA2_APP_BASE_USER_INTERACTION_H







