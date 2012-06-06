#pragma once


namespace uinteraction
{


// User Message Frame Work Version 33
#define UM_FRAMEWORKV033_COMMAND WM_USER + 101
#define APPM_FORWARDSYNCMESSAGE WM_APP + 317

namespace frame
{

   class appearance;
   class MoveManager;
   class SysMenuManager;
   class WorkSetListener;

   class CLASS_DECL_ca2 WorkSet :
      virtual public ::database::client,
      virtual public gen::signalizable
   {
   public:
      friend class appearance;

      bool                          m_bHoverModeOn;
      bool                          m_bHoverActive;
      bool                          m_bSizingCapture;
      bool                          m_bEnableMouse;
      ::uinteraction::frame::frame *   m_pframeschema;
      rect                          m_rectPending;
      bool                          m_bEnable;

      ::user::interaction *         m_pwndRegion;
      ::user::interaction *         m_pwndDraw;
      ::user::interaction *         m_pwndEvent;
      ::user::interaction *         m_pwndCommand;

      bool                          m_bDockEnable;
      bool                          m_bNotifyIconEnable;
      bool                          m_bFullScreenEnable;

      UINT                          m_uiSWPFlags;

      WorkSetListenerArray          m_wfla;

      MoveManager *                 m_pmovemanager;
      SizeManager *                 m_psizemanager;
      SysMenuManager *              m_psystemmenumanager;
      DockManager *                 m_pdockmanager;

      bool                          m_bMovingEnabled;
      bool                          m_bSizingEnabled;
      bool                          m_bSysMenuEnabled;

      appearance *                  m_pappearance;


      WorkSet();
      virtual ~WorkSet();


      void OnNcCalcSize(LPRECT lprect);
      bool IsEnabled();
      void Enable(bool bEnable);
      void _000OnBeforeSize(LPCRECT lpcrect);

      ::user::interaction * GetEventWindow();
      ::user::interaction * GetRegionWindow();
      ::user::interaction * GetDrawWindow();
      ::user::interaction * GetCommandWindow();


      appearance * GetAppearance();
      DockManager * GetDockManager();
      MoveManager * GetMovingManager();
      SizeManager * GetSizingManager();


      void AttachFrameSchema(::uinteraction::frame::frame * pframeschema);
      void _001InstallEventHandling(::gen::message::dispatch * pdispatch);

      DECL_GEN_SIGNAL(_001OnLButtonDown)
         DECL_GEN_SIGNAL(_001OnMouseMove)
         DECL_GEN_SIGNAL(_001OnLButtonUp)
         DECL_GEN_SIGNAL(_001OnNcLButtonDown)
         DECL_GEN_SIGNAL(_001OnNcMouseMove)
         DECL_GEN_SIGNAL(_001OnNcLButtonUp)
         DECL_GEN_SIGNAL(_001OnNcHitTest)
         DECL_GEN_SIGNAL(_001OnTimer)
         DECL_GEN_SIGNAL(_001OnSize)
         DECL_GEN_SIGNAL(_001OnMove)

         // point should be in screen coordinates
         EHitTest hit_test(point ptCursor);


      bool IsNotifyIconEnabled();
      void EnableNotifyIcon(bool bEnable = true);
      void EnableFullScreen(bool bEnable = true);
      bool IsFullScreenEnabled();
      void WindowClose();
      void UpdateApperanceMode(bool bFullScreen);
      //void UpdateControlBox();
      void SetDownUpInterface(CWorkSetDownUpInterface *pinterface);
      void WindowProcBefore(::user::interaction * pwnd, gen::signal_object * pobj);
      void WindowProcHover(::user::interaction * pwnd, gen::signal_object * pobj);
      DECL_GEN_SIGNAL(_001OnActivate)
         DECL_GEN_SIGNAL(_001OnCommand)
         DECL_GEN_SIGNAL(_001OnNcActivate)
         void RemoveListener(WorkSetListener * plistener);
      void AddListener(WorkSetListener * plistener);
      void OnSizingGripMove(EGrip egrip);

      bool IsHoverModeOn();
      bool IsHoverActive();
      void OnMoving();
      void OnMove();
      void SetDockMask(EDock emask);

      virtual void OnDock();
      void EnableDock(bool bEnable = true);
      void layout();
      bool Hover(bool bHoverActive);
      void hover_relay_event(gen::signal_object * pobj);
      void ChildWnd(::user::interaction * pwnd, ::user::interaction * pwndParent);
      void FrameWnd(::user::interaction * pwnd);
      bool Start();
      //void OnDown();
      //void OnUp();
      void AppearanceUpdateControlBox();
      ::user::interaction * GetWndDraw();
      ::user::interaction * GetWndRegion();

      bool update(
         ::user::interaction * pwndDraw,
         ::user::interaction * pwndRegion,
         ::user::interaction * pwndEvent,
         ::user::interaction * pwndCommand);

      void SetAppearanceTransparency(EAppearanceTransparency nTransparency);
      void SetFrameSchemaStyle(int nStyle);
      void SetActiveFlag(bool fActive);
      void SetSWPFlags(UINT uiFlags);

      EAppearanceMode GetAppearanceMode();
      void SetAppearanceMode(EAppearanceMode nMode);
      void SetAppearanceMode();

      void GetRegionClientRect(LPRECT lprect);
      void GetDrawClientRect(LPRECT lprect);
      //void SetWindow(::user::interaction * pwnd);
      void relay_event(gen::signal_object * pobj);
      void message_handler(gen::signal_object * pobj);

      void _001OnDraw(::ca::graphics * pdc);

      virtual bool BaseOnControlEvent(::user::control_event * pevent);


      void EnableMove(bool bEnable);
      void EnableSize(bool bEnable);
      void EnableSysMenu(bool bEnable);
      void EnableApperance(bool bEnable);

      bool IsMovingEnabled();
      bool IsSizingEnabled();
      bool IsSysMenuEnabled();
      bool IsAppearanceEnabled();

      bool IsFullScreen();
      bool ViewFullScreen(bool bFullScreen);

      virtual bool _001OnCmdMsg(BaseCmdMsg * pcmdmsg); 

      virtual void OnSize(UINT nType, int cx, int cy);


   };


} // namespace frame






} // namespace uinteraction






