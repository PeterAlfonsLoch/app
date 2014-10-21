#pragma once



namespace frame
{


   class FrameSchema;


}


namespace user
{


   class control_bar;


} // namespace user


class BaseDockBar;
class BaseReBar;
class BaseMiniDockFrameWnd;

class CLASS_DECL_CORE simple_frame_window :
   virtual public ::user::frame_window,
   virtual public database::user::interaction,
   virtual public ::user::wndfrm::frame::WorkSetClientInterface,
   virtual public ::user::wndfrm::frame::WorkSetListener,
   virtual public ::user::wndfrm::frame::CWorkSetDownUpInterface
{
public:



   ::database::id          m_datakeyFrame;

   sp(::user::wndfrm::frame::frame)       m_pframeschema;

   class helper_task:
      public thread
   {
   public:

      simple_frame_window *      m_pframe;
      bool                       m_bSaveWindowRect;


      helper_task(simple_frame_window * pframe);

      int32_t run();

   };


   helper_task *        m_phelpertask;
//   HDC                           m_hdcOpenGL;
//#ifdef WINDOWS
//   HGLRC                         m_hglrc;
//#endif
   bool                                m_bFullScreenAlt;
   bool                                m_bblur_Background;
   visual::dib_sp                      m_dibBk;
   bool                                m_bCustomFrameBefore;
   rect                                m_FullScreenWindowRect;
   visual::fastblur                    m_fastblur;

   mapsp(id, id, ::user::toolbar)     m_toolbarmap;


   simple_frame_window(sp(::aura::application) papp);
   virtual ~simple_frame_window();


   using ::user::frame_window::create_window;
   virtual bool create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle = WS_OVERLAPPEDWINDOW,const RECT & rect = ::null_rect(),sp(::user::interaction) pParentWnd = NULL,const char * lpszMenuName = NULL,uint32_t dwExStyle = 0,sp(::create_context) pContext = NULL);

   virtual bool create_bars();
   virtual bool on_create_bars();

   virtual void install_message_handling(::message::dispatch * pinterface);

   virtual bool on_before_set_parent(sp(::user::interaction) pinterface);
   virtual void on_set_parent(sp(::user::interaction) puiParent);

   virtual void GetClientRect(LPRECT lprect);

   virtual bool is_application_main_window();

   bool GetCustomFrame();
   void SetCustomFrame(bool bCustom);
   void SetBorderRect(const RECT & rect);
   virtual void GetBorderRect(LPRECT lprect);
   void ViewOnActivateFrame(sp(::user::impact) pview, UINT user, sp(::user::interaction) pframe);

   virtual void ToggleFullScreen();
   virtual bool IsFullScreen();
   virtual void WfiOnFullScreen();
   virtual void WfiOnExitFullScreen();
   virtual void ShowControlBars(bool bShow = true);


   void OnUpdateControlBarMenu(cmd_ui * pcmdui);

   virtual sp(::user::wndfrm::frame::frame) create_frame_schema();

   virtual bool LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, sp(::user::interaction) pParentWnd = NULL, sp(::create_context) pContext = NULL);

   DECL_GEN_SIGNAL(_001OnNcActivate);
   DECL_GEN_SIGNAL(_001OnDisplayChange);

   void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pdc);



   virtual bool LoadToolBar(sp(::type) sptype,id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

   template < class TOOLBAR >
   bool LoadToolBar(id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

   virtual bool LoadToolBar(id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP)
   {
      return LoadToolBar < simple_toolbar >(idToolBar,pszToolBar,dwCtrlStyle,dwStyle);
   }


   virtual void InitialFramePosition(bool bForceRestore = false);

   sp(::user::interaction) WindowDataGetWnd();
   virtual void layout();
   virtual void ActivateFrame(int32_t nCmdShow = -1);
   virtual bool on_create_client(::user::create_struct * lpcs, sp(::create_context) pContext);
   virtual bool pre_create_window(::user::create_struct& cs);
   virtual void pre_translate_message(signal_details * pobj);

   virtual void _000OnDraw(::draw2d::graphics * pdc);
   virtual void _010OnDraw(::draw2d::graphics * pdc);

   virtual void _001OnDraw(::draw2d::graphics * pdc);
   virtual void _011OnDraw(::draw2d::graphics * pdc);






   virtual bool _001CanEnterScreenSaver();

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDdeInitiate);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnSize);
   DECL_GEN_SIGNAL(_001OnMove);
   DECL_GEN_SIGNAL(_001OnClose);
   DECL_GEN_SIGNAL(_001OnSysCommand);
   DECL_GEN_SIGNAL(_001OnViewFullScreen);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnUpdateViewFullScreen);
   DECL_GEN_SIGNAL(_001OnToggleCustomFrame);
   DECL_GEN_SIGNAL(_001OnUpdateToggleCustomFrame);
   DECL_GEN_SIGNAL(_001OnGetMinMaxInfo);
   DECL_GEN_SIGNAL(_001OnUser184);

#ifdef WINDOWSEX
   void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#endif

   // persistent frame implemenation using updowntarget

   virtual bool WndFrameworkDownUpGetUpEnable();
   virtual bool WndFrameworkDownUpGetDownEnable();

   using ::user::wndfrm::frame::WorkSetListener::attach;
   DECL_GEN_VSIGNAL(guserbaseOnInitialUpdate);

   virtual class mini_dock_frame_window* CreateFloatingFrame(uint32_t dwStyle);
   virtual void NotifyFloatingWindows(uint32_t dwFlags);


   virtual void WfiOnDown();
   virtual void WfiOnUp();

   virtual bool calc_layered();


   virtual string get_window_default_matter();

   virtual void assert_valid() const;
   virtual void dump(dump_context & dumpcontext) const;
   void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   virtual bool on_simple_command(e_simple_command ecommand, lparam lparam, LRESULT & lresult);

   virtual void OnDropFiles(HDROP hDropInfo);
   virtual bool OnQueryEndSession();
   virtual void OnEndSession(bool bEnding);

   LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam);
   LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam);
   LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam);

   void _001OnQueryEndSession(signal_details * pobj);

   virtual bool BaseOnControlEvent(::user::control_event * pevent);

   virtual bool WfiOnMove(bool bTracking);
   virtual bool WfiOnSize(bool bTracking);

   virtual void WfiOnClose();
   virtual void WfiOnMaximize();
   virtual void WfiOnMinimize();
   virtual void WfiOnRestore();
   virtual void WfiOnDock(::user::EAppearance eappearance);

   virtual bool DeferFullScreen(bool bFullScreen, bool bRestore);

   virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);

   virtual void data_on_after_change(signal_details * pobj);



   virtual bool set_appearance(::user::EAppearance eappearance);

   virtual void InitialUpdateFrame(::user::document * pDoc,bool bMakeVisible);

};



