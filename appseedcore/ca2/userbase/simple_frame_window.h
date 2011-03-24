#pragma once

namespace window_frame
{
   class FrameSchema;
}

class ::userbase::control_bar;
class BaseDockBar;
class BaseReBar;
class BaseMiniDockFrameWnd;

class CLASS_DECL_ca simple_frame_window :
   virtual public userbase::frame_window,
   virtual public window_frame::CWorkSetDownUpInterface
{
   friend class BaseReBar;
public:

   window_frame::FrameSchema *   m_pframeschema;

   HDC                           m_hdcOpenGL;
   HGLRC                         m_hglrc;
   bool                          m_bblur_Background;
   visual::dib_sp                m_dibBk;
   bool                          m_bCustomFrameBefore;
   rect                          m_FullScreenWindowRect;
   visual::fastblur              m_fastblur;

   phm(id, id, ::user::interaction)    m_toolbarmap;
   
   simple_frame_window(::ca::application * papp);
   virtual ~simple_frame_window();


   virtual void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);

   virtual bool WndFrameworkDownUpGetUpEnable();
   virtual bool WndFrameworkDownUpGetDownEnable();

   virtual void on_set_parent(::user::interaction* pguieParent);

   virtual void GetClientRect(LPRECT lprect);

   virtual bool is_application_main_window();
      
   bool GetCustomFrame();
   void SetCustomFrame(bool bCustom);
   void SetBorderRect(LPCRECT lpcrect);
   virtual void GetBorderRect(LPRECT lprect);
   void ViewOnActivateFrame(::userbase::view * pview, UINT user, ::user::interaction * pframe);

   virtual void ToggleFullScreen();
   virtual bool IsFullScreen();
   virtual void WfiOnFullScreen(bool bFullScreen);
   virtual void ShowControlBars(bool bShow = true);
   virtual void WfiOnDown();
   virtual void WfiOnUp();


   afx_msg void OnUpdateControlBarMenu(cmd_ui * pcmdui);
   
   virtual window_frame::FrameSchema * create_frame_schema();

   virtual BOOL LoadFrame(const char * pszMatter,
            DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
            ::user::interaction* pParentWnd = NULL,
            create_context* pContext = NULL);

   DECL_GEN_SIGNAL(_001OnNcActivate);
   
   void _001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc);

   void LoadToolBar(id idToolBar, const char * pszToolBar);


   virtual void InitialFramePosition(bool bForceRestore = false);

   ::user::interaction* WindowDataGetWnd();
   virtual void layout();
   virtual void ActivateFrame(int nCmdShow = -1);
   protected:
   virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, create_context* pContext);
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
   virtual void pre_translate_message(gen::signal_object * pobj);

   virtual void _000OnDraw(::ca::graphics * pdc);
   virtual void _001OnDraw(::ca::graphics * pdc);


   



   virtual bool _001CanEnterScreenSaver();
   
   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDdeInitiate);
   DECL_GEN_SIGNAL(_001OnDestroy)
   DECL_GEN_SIGNAL(_001OnSize)
   DECL_GEN_SIGNAL(_001OnMove)
   DECL_GEN_SIGNAL(_001OnClose)
   DECL_GEN_SIGNAL(_001OnSysCommand);
   DECL_GEN_SIGNAL(_001OnViewFullScreen)
   DECL_GEN_SIGNAL(_001OnUpdateViewFullScreen) 
   DECL_GEN_SIGNAL(_001OnToggleCustomFrame)
   DECL_GEN_SIGNAL(_001OnUpdateToggleCustomFrame)
   DECL_GEN_SIGNAL(_001OnGetMinMaxInfo)
   DECL_GEN_SIGNAL(_001OnUser184)

   afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
};
