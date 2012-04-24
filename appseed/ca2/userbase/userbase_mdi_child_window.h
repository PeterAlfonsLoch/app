#pragma once


namespace userbase
{

   class CLASS_DECL_ca2 mdi_child_window :
      virtual public frame_window
   {
   public:

      BOOL m_bPseudoInactive;     // TRUE if ::ca::window is MDI active according to
                           //  windows, but not according to ca2 API...


      mdi_child_window(::ca::application * papp);


      virtual BOOL create(const char * lpszClassName,
               const char * lpszWindowName,
               DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
               const RECT& rect = rectDefault,
               mdi_frame_window* pParentWnd = NULL,
               ::ca::create_context* pContext = NULL);

      mdi_frame_window* GetMDIFrame();

      void MDIDestroy();
      void MDIActivate();
      void MDIMaximize();
      void MDIRestore();
      void SetHandles(HMENU hMenu, HACCEL hAccel);

      HMENU m_hMenuShared;        // menu when we are active

   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual BOOL pre_create_window(CREATESTRUCT& cs);
      virtual BOOL LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
                  ::user::interaction* pParentWnd, ::ca::create_context* pContext = NULL);
         // 'pParentWnd' parameter is required for MDI Child
      virtual BOOL DestroyWindow();
      virtual void pre_translate_message(gen::signal_object * pobj);
      virtual void ActivateFrame(int nCmdShow = -1);
      virtual void OnUpdateFrameMenu(BOOL bActive, ::user::interaction* pActivateWnd,
         HMENU hMenuAlt);


      virtual ::user::interaction* GetMessageBar();
      virtual void on_update_frame_title(BOOL bAddToTitle);
      virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
      BOOL UpdateClientEdge(LPRECT lpRect = NULL);

      //{{AFX_MSG(mdi_child_window)
      void OnMDIActivate(BOOL bActivate, ::user::interaction*, ::user::interaction*);
      int OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message);
      int OnCreate(LPCREATESTRUCT lpCreateStruct);
      BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
      void OnSize(UINT nType, int cx, int cy);
      void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
      BOOL OnNcActivate(BOOL bActive);
      void OnDestroy();
      BOOL OnToolTipText(UINT nID, NMHDR* pNMHDR, LRESULT* pResult);

   private:
      using ::frame_window::OnUpdateFrameMenu;
      using ::frame_window::create;

   };



} //namespace userbase
