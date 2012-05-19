#pragma once


class CLASS_DECL_ca2 SimpleMDIChildWindow :
   virtual public simple_frame_window
{
public:


   HMENU m_hMenuShared;        // menu when we are active


   SimpleMDIChildWindow(::ca::application * papp);


   using ::simple_frame_window::create;
   virtual bool create(const char * lpszClassName,
            const char * lpszWindowName,
            DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
            const RECT& rect = rectDefault,
            SimpleMDIFrameWindow* pParentWnd = NULL,
            ::ca::create_context* pContext = NULL);

   virtual void install_message_handling(::gen::message::dispatch * pinterface);

// Attributes
   SimpleMDIFrameWindow* GetMDIFrame();

// Operations
   void MDIDestroy();
   void MDIActivate();
   void MDIMaximize();
   void MDIRestore();
   void SetHandles(HMENU hMenu, HACCEL hAccel);


#ifdef _DEBUG
   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
#endif

   virtual bool pre_create_window(CREATESTRUCT& cs);
   virtual bool LoadFrame(const char * pszMatter, DWORD dwDefaultStyle,
               ::user::interaction* pParentWnd, ::ca::create_context* pContext = NULL);
      // 'pParentWnd' parameter is required for MDI Child
   virtual bool DestroyWindow();
   virtual void pre_translate_message(gen::signal_object * pobj);
   virtual void ActivateFrame(int nCmdShow = -1);
   using ::frame_window::OnUpdateFrameMenu;
   virtual void OnUpdateFrameMenu(bool bActive, ::user::interaction* pActivateWnd,
      HMENU hMenuAlt);

   bool m_bPseudoInactive;     // TRUE if ::ca::window is MDI active according to
                        //  windows, but not according to ca2 API...

   virtual ::user::interaction* GetMessageBar();
   virtual void on_update_frame_title(bool bAddToTitle);
   virtual LRESULT DefWindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam);
   bool UpdateClientEdge(LPRECT lpRect = NULL);

   //{{__MSG(SimpleMDIChildWindow)
   void OnMDIActivate(bool bActivate, ::user::interaction*, ::user::interaction*);
   int OnMouseActivate(::user::interaction* pDesktopWnd, UINT nHitTest, UINT message);
   DECL_GEN_SIGNAL(_001OnCreate)
   bool OnNcCreate(LPCREATESTRUCT lpCreateStruct);
   void OnSize(UINT nType, int cx, int cy);
   void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
   bool OnNcActivate(bool bActive);
   void OnDestroy();


};


