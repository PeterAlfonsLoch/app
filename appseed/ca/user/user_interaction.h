#pragma once


#include "gen/gen_holder.h"
#include "ca/user/user_window_interface.h"


namespace ca
{


   class window_callback;
   class live_object;


} // namespace ca


namespace user
{


   class control_event;


   class CLASS_DECL_ca interaction :
      virtual public window_interface
   {
   public:


      class CLASS_DECL_ca timer_item
      {
      public:


         interaction *        m_pguie;
         UINT_PTR             m_uiId;
         UINT                 m_uiElapse;
         UINT                 m_uiLastSent;

         bool check();


      };

      class CLASS_DECL_ca timer_array :
         virtual public pha(interaction)
      {
      public:


         mutex                      m_mutex;
         raw_array < timer_item >   m_timera;



         virtual void on_delete(interaction * poc);
         UINT_PTR set(interaction * pguie, UINT_PTR uiId, UINT uiElapse);
         void check();
         bool unset(interaction * pguie, UINT_PTR uiId);
         void unset(interaction * pguie);
         void detach(raw_array < timer_item > & timera, interaction * pguie);
         void transfer(::ca::window * pwindow, interaction * pguie);
         interaction * find(::ca::ca * pca);
         index find(interaction * pguie, UINT_PTR uiId);
         index find_from(interaction * pguie, index iStart);

         virtual void assert_valid() const;
         virtual void dump(dump_context & dc) const;

      };



      virtual bool create_message_window(const char * pszName, ::ca::window_callback * pcallback = NULL);



      enum e_appearance
      {
         appearance_normal,
         appearance_zoomed,
         appearance_iconic,
         appearance_notify,
      };

      e_appearance                        m_eappearance;
      interaction *                       m_pimpl;
      ::radix::thread *                   m_pthread;
      static interaction *                g_pguieMouseMoveCapture;
      pha(interaction)                    m_uiptraChild;
      string                              m_strName;
      id                                  m_id;
      interaction *                       m_pguieOwner;
      UINT                                m_nFlags;      // see WF_ flags above
      bool                                m_bCursorInside;
      ::visual::e_cursor                  m_ecursor;
      int                                 m_iModal;
      int                                 m_iModalCount;
      bool                                m_bRectOk;
      comparable_array < INT_PTR >        m_iaModalThread;
      id                                  m_idModalResult; // for return values from ::ca::window::RunModalLoop
      COLORREF                            m_crDefaultBackgroundColor;



      interaction();
      interaction(::ca::application * papp);
      virtual ~interaction();


      virtual void on_select();


      ::visual::e_cursor get_cursor();
      void set_cursor(::visual::e_cursor ecursor);


      void set_timer(raw_array < timer_item > timera);


      virtual BOOL IsWindow();

      virtual LONG GetWindowLong(int nIndex);
      virtual LONG SetWindowLong(int nIndex, LONG lValue);


      virtual void on_set_parent(interaction * pinterface);


      virtual interaction * get_bottom_child();
      virtual interaction * get_top_child();
      virtual interaction * under_sibling();
      virtual interaction * above_sibling();

      virtual interaction * above_sibling(interaction * pui);
      virtual interaction * under_sibling(interaction * pui);



      virtual BOOL CheckAutoCenter();

      virtual void track_mouse_hover();
      virtual void track_mouse_leave();

      // dialog support
      void UpdateDialogControls(command_target* pTarget, BOOL bDisableIfNoHndler);
      virtual void CenterWindow(interaction * pAlternateOwner = NULL);
      virtual id   RunModalLoop(DWORD dwFlags = 0, ::ca::live_object * pliveobject = NULL);
      virtual bool ContinueModal(int iLevel);
      virtual void EndModalLoop(id nResult);
      virtual void EndAllModalLoops(id nResult);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      virtual ::user::interaction * get_os_focus_uie();


      virtual void _001WindowMaximize();
      virtual void _001WindowRestore();
      virtual bool IsZoomed();
      virtual bool IsFullScreen();
      virtual bool ShowWindowFullScreen(bool bFullScreen = true);
      virtual bool IsIconic();
      virtual void MoveWindow(int x, int y, int nWidth, int nHeight,
               BOOL bRepaint = TRUE);
      virtual void MoveWindow(LPCRECT lpRect, BOOL bRepaint = TRUE);
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
      virtual bool SetWindowPos(int z, int x, int y, int cx, int cy, UINT nFlags);
      virtual bool set_placement(LPRECT lprect);
      virtual int SetWindowRgn(HRGN hRgn, BOOL bRedraw);
      virtual int GetWindowRgn(HRGN hRgn);

      virtual void layout();

      virtual bool BringWindowToTop();


      virtual BOOL GetWindowPlacement(WINDOWPLACEMENT* lpwndpl);
      virtual BOOL SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl);


      virtual BOOL SendChildNotifyLastMsg(LRESULT* pResult = NULL);


      virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


      virtual bool subclass_window(void * posdata);
      virtual void * unsubclass_window();


      virtual bool create(interaction *pparent, id id);
      virtual BOOL create_window(const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         ::ca::create_context* pContext = NULL);
      using ::ex1::request_interface::create;
      virtual BOOL create(const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         ::ca::create_context* pContext = NULL);
      virtual BOOL CreateEx(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam = NULL);
      virtual BOOL create_window_ex(DWORD dwExStyle, const char * lpszClassName,
         const char * lpszWindowName, DWORD dwStyle,
         const RECT& rect,
         interaction* pParentWnd, id id,
         LPVOID lpParam = NULL);
      enum AdjustType { adjustBorder = 0, adjustOutside = 1 };
      virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
      virtual frame_window * GetParentFrame();

      virtual BOOL IsTopParentActive();
      virtual void ActivateTopParent();

      virtual BOOL DestroyWindow();


#ifdef WINDOWS
      virtual BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::ca::region* prgnUpdate = NULL,
         UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
#else
      virtual BOOL RedrawWindow(LPCRECT lpRectUpdate = NULL,
         ::ca::region* prgnUpdate = NULL,
         UINT flags = 0);
#endif


      virtual void UpdateWindow();
      virtual void SetRedraw(BOOL bRedraw = TRUE);
      virtual BOOL GetUpdateRect(LPRECT lpRect, BOOL bErase = FALSE);
      virtual int GetUpdateRgn(::ca::region* pRgn, BOOL bErase = FALSE);
      virtual void Invalidate(BOOL bErase = TRUE);
      virtual void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
      virtual void InvalidateRgn(::ca::region* pRgn, BOOL bErase = TRUE);
      virtual void ValidateRect(LPCRECT lpRect);
      virtual void ValidateRgn(::ca::region* pRgn);
      virtual void ShowOwnedPopups(BOOL bShow = TRUE);


      virtual DWORD GetStyle();
      virtual DWORD GetExStyle();
      virtual LRESULT Default();

      virtual LRESULT SendMessage(::gen::message::base * pbase);
      virtual BOOL PostMessage(::gen::message::base * pbase);
      virtual LRESULT SendMessage(UINT uiMessage, WPARAM wparam = 0, LPARAM lparam = 0);
      virtual BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0);

      virtual BOOL ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      virtual BOOL ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags = 0);
      virtual BOOL ShowWindow(int nCmdShow);
      virtual BOOL IsFrameWnd();

   // Timer Functions
      virtual UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT nElapse,
         void (CALLBACK* lpfnTimer)(HWND, UINT, UINT_PTR, DWORD));
      virtual BOOL KillTimer(UINT_PTR nIDEvent);

      virtual BOOL IsWindowEnabled();
      virtual BOOL EnableWindow(BOOL bEnable = TRUE);

      virtual void _001Print(::ca::graphics * pdc);
      virtual void _000OnDraw(::ca::graphics *pdc);
      virtual void _001DrawThis(::ca::graphics *pdc);
      virtual void _001DrawChildren(::ca::graphics *pdc);
      virtual ::ca::graphics * GetDC();
      virtual BOOL ReleaseDC(::ca::graphics *);

      virtual BOOL IsChild(interaction *  pWnd);
      virtual window_interface * window_interface_get_parent();
      virtual interaction * GetParent();
      virtual interaction * SetParent(interaction * pguieParent);

      virtual id GetDlgCtrlId();
      virtual id SetDlgCtrlId(class id id);

      virtual interaction * set_capture(interaction * pinterface = NULL);
      virtual interaction * release_capture();

      virtual bool has_focus();
      virtual interaction * SetFocus();
      virtual BOOL SetForegroundWindow();
      virtual interaction * GetActiveWindow();
      virtual interaction * SetActiveWindow();

      virtual void WalkPreTranslateTree(gen::signal_object * pobj);
      virtual void WalkPreTranslateTree(::user::interaction * puiStop, gen::signal_object * pobj);

      virtual interaction * GetDescendantWindow(id id);

      virtual void SetWindowText(const char * lpszString);
      virtual strsize GetWindowText(LPTSTR lpszStringBuf, int nMaxCount);
      virtual void GetWindowText(string & rString);
      virtual strsize GetWindowTextLength();
      virtual void SetFont(::ca::font* pFont, BOOL bRedraw = TRUE);
      virtual ::ca::font* GetFont();

      virtual void install_message_handling(::gen::message::dispatch * pinterface);
      virtual BOOL IsWindowVisible();

      virtual void _000OnMouse(::gen::message::mouse * pmouse);
      virtual void _000OnKey(::gen::message::key * pkey);
      DECL_GEN_SIGNAL(_001OnMouseMove)
      DECL_GEN_SIGNAL(_001OnMouseEnter)
      DECL_GEN_SIGNAL(_001OnMouseLeave)
      DECL_GEN_SIGNAL(_001OnKeyDown)
      DECL_GEN_SIGNAL(_001OnKeyUp)
      DECL_GEN_SIGNAL(_001OnTimer)
      DECL_GEN_SIGNAL(_001OnChar)
      DECL_GEN_SIGNAL(_001OnDestroy)
      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnMove)
      DECL_GEN_SIGNAL(_001OnUser184)
      DECL_GEN_SIGNAL(_001OnNcCalcSize)

      virtual DECL_GEN_SIGNAL(_002OnLButtonDown)
      virtual DECL_GEN_SIGNAL(_002OnLButtonUp)
      virtual DECL_GEN_SIGNAL(_002OnMouseMove)
      virtual DECL_GEN_SIGNAL(_002OnMouseEnter)
      virtual DECL_GEN_SIGNAL(_002OnMouseLeave)
      virtual DECL_GEN_SIGNAL(_002OnKeyDown)
      virtual DECL_GEN_SIGNAL(_002OnKeyUp)
      virtual DECL_GEN_SIGNAL(_002OnTimer)


      virtual void on_delete(::ca::ca * poc);

      //virtual void _001SetWindowPos(const ::ca::window* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
      //virtual void _001SetFocus();
      //virtual void _001ShowWindow(int iShow);
      //virtual void _001ScreenToClient(LPPOINT lppoint);


   // trans   virtual bool _001IsVisible();
   // trans   virtual void _001SetVisible(bool bVisible);

      virtual bool _001IsPointInside(point64 pt);
      virtual interaction * _001FromPoint(point64 pt, bool bTestedIfParentVisible = false);

      virtual void OnLinkClick(const char * psz, const char * pszTarget = NULL);

      interaction * GetChildByName(const char * pszName, int iLevel = -1);
      interaction * GetChildById(id id, int iLevel = -1);

      virtual ::frame_window * EnsureParentFrame();
      virtual interaction* GetTopLevelParent();
      virtual interaction* EnsureTopLevelParent();
      virtual ::frame_window * GetTopLevelFrame();
      virtual void SendMessageToDescendants(UINT message, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bDeep = TRUE, BOOL bOnlyPerm = FALSE);
      virtual void pre_translate_message(gen::signal_object * pobj);


      virtual int get_descendant_level(::user::interaction * pui);
      virtual bool is_descendant(::user::interaction * pui, bool bIncludeSelf = false);
      virtual ::user::interaction * get_focusable_descendant(::user::interaction * pui = NULL);

      virtual ::ca::window * get_wnd();

      enum RepositionFlags
      {
         reposDefault = 0,
         reposQuery = 1,
         reposExtra = 2,
         reposNoPosLeftOver=0x8000
      };

      virtual void RepositionBars(UINT nIDFirst, UINT nIDLast, id nIDLeftOver, UINT nFlag = reposDefault, LPRECT lpRectParam = NULL, LPCRECT lpRectClient = NULL, BOOL bStretch = TRUE);

      virtual interaction * GetOwner();
      virtual void SetOwner(interaction * pguie);

      virtual interaction * ChildWindowFromPoint(POINT point);
      virtual interaction * ChildWindowFromPoint(POINT point, UINT nFlags);


#ifdef WINDOWS
      virtual interaction * GetNextWindow(UINT nFlag = GW_HWNDNEXT);
#else
      virtual interaction * GetNextWindow(UINT nFlag = 0);
#endif

      virtual interaction * GetTopWindow();

      virtual interaction * get_next(bool bIgnoreChildren = false, int * piLevel = NULL);

      virtual interaction * GetWindow(UINT nCmd);
      virtual interaction * GetLastActivePopup();

      virtual interaction * GetDlgItem(id nID);

      virtual void pre_subclass_window();

#ifdef WINDOWS
      virtual WNDPROC* GetSuperWndProcAddr();
#endif

      // for custom cleanup after WM_NCDESTROY
      virtual void PostNcDestroy();

      virtual LRESULT DefWindowProc(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual void message_handler(gen::signal_object * pobj);
      virtual void GuieProc(gen::signal_object * pobj);

      virtual void _001DeferPaintLayeredWindowBackground(::ca::graphics * pdc);

      virtual void _001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc);



   #ifdef WIN32
      HWND get_safe_handle();
      virtual HWND _get_handle();
      virtual BOOL Attach(HWND hWndNew);
      virtual HWND Detach();
   #else
      int get_safe_handle();
      virtual int _get_handle();
      virtual BOOL Attach(int hWndNew);
      virtual int Detach();
   #endif

      template < class T >
      T * GetTypedParent()
      {
         ASSERT_VALID(this);

         interaction * pParentWnd = GetParent();  // start with one parent up
         while (pParentWnd != NULL)
         {
            if(dynamic_cast < T * > (pParentWnd) != NULL)
            {
               return dynamic_cast < T * > (pParentWnd);
            }
            pParentWnd = pParentWnd->GetParent();
         }
         return NULL;
      }


      virtual bool can_merge(::user::interaction * pui);
      virtual bool merge(::user::interaction * pui);


      virtual COLORREF get_background_color();
      virtual void set_default_background_color(COLORREF crDefaultBackgroundColor);



   };

#ifdef WINDOWS
   inline HWND interaction::get_safe_handle()
   {
      if(((INT_PTR)this) < 16 * 1024) // consider invalid
      {
         return NULL;
      }
      return _get_handle();
   }
#else
   inline int interaction::get_safe_handle()
   {
      if(((byte *)this) < (byte *) (((byte *) NULL) + (16 * 1024))) // consider invalid
      {
         return 0;
      }
      return _get_handle();
   }
#endif



} // namespace user

CLASS_DECL_ca ::user::interaction * WINAPI CreateGuieEx(
   ::ca::application * papp,
    DWORD dwExStyle,
    const char * lpClassName,
    const char * lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    ::user::interaction * pguieParent,
    id id,
    HINSTANCE hInstance,
    LPVOID lpParam);
