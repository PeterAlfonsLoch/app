#pragma once


namespace frame
{


   class FrameSchema;


}


namespace userbase
{


   class control_bar;


} // namespace userbase


class BaseDockBar;
class BaseReBar;
class BaseMiniDockFrameWnd;

class CLASS_DECL_ca2 simple_frame_window :
   virtual public ::userbase::frame_window,
   virtual public ::uinteraction::frame::CWorkSetDownUpInterface
{
public:


   ::uinteraction::frame::frame *       m_pframeschema;


//   HDC                           m_hdcOpenGL;
//#ifdef WINDOWS
//   HGLRC                         m_hglrc;
//#endif
   bool                          m_bFullScreenAlt;
   bool                          m_bblur_Background;
   visual::dib_sp                m_dibBk;
   bool                          m_bCustomFrameBefore;
   rect                          m_FullScreenWindowRect;
   visual::fastblur              m_fastblur;

   phm(id, id, ::user::interaction)    m_toolbarmap;


   simple_frame_window(::ca::application * papp);
   virtual ~simple_frame_window();


   using ::userbase::frame_window::create;
   virtual bool create(const char * lpszClassName,
            const char * lpszWindowName,
            uint32_t dwStyle = WS_OVERLAPPEDWINDOW,
            const RECT & rectParam = rect(0, 0, 0, 0),
            ::user::interaction* pParentWnd = NULL,        // != NULL for popups
            const char * lpszMenuName = NULL,
            uint32_t dwExStyle = 0,
            ::ca::create_context* pContext = NULL);



   virtual void install_message_handling(::ca::message::dispatch * pinterface);

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


   void OnUpdateControlBarMenu(cmd_ui * pcmdui);

   virtual ::uinteraction::frame::frame * create_frame_schema();

   virtual bool LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, ::user::interaction* pParentWnd = NULL, ::ca::create_context* pContext = NULL);

   DECL_GEN_SIGNAL(_001OnNcActivate);

   void _001OnDeferPaintLayeredWindowBackground(::ca::graphics * pdc);




#ifdef WINDOWSEX
   void LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle = TBSTYLE_FLAT, uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#else
   void LoadToolBar(id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle = 0, uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
#endif

   virtual void InitialFramePosition(bool bForceRestore = false);

   ::user::interaction* WindowDataGetWnd();
   virtual void layout();
   virtual void ActivateFrame(int32_t nCmdShow = -1);
   virtual bool OnCreateClient(LPCREATESTRUCT lpcs, ::ca::create_context* pContext);
   virtual bool pre_create_window(CREATESTRUCT& cs);
   virtual void pre_translate_message(::ca::signal_object * pobj);

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
   DECL_GEN_SIGNAL(_001OnMouseMove)
   DECL_GEN_SIGNAL(_001OnUpdateViewFullScreen)
   DECL_GEN_SIGNAL(_001OnToggleCustomFrame)
   DECL_GEN_SIGNAL(_001OnUpdateToggleCustomFrame)
   DECL_GEN_SIGNAL(_001OnGetMinMaxInfo)
   DECL_GEN_SIGNAL(_001OnUser184)

#ifdef WINDOWSEX
   void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#endif

   // persistent frame implemenation using updowntarget

   virtual bool WndFrameworkDownUpGetUpEnable();
   virtual bool WndFrameworkDownUpGetDownEnable();

   virtual void WfiOnDown();
   virtual void WfiOnUp();

};
