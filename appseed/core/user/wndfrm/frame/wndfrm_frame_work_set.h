#pragma once


namespace user
{


   namespace wndfrm
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

         class CLASS_DECL_CORE WorkSet :
            virtual public ::database::client,
            virtual public signalizable
         {
         public:
            friend class appearance;

            bool                          m_bHoverModeOn;
            bool                          m_bHoverActive;
            bool                          m_bSizingCapture;
            bool                          m_bEnableMouse;
            sp(frame)                     m_pframeschema;
            rect                          m_rectPending;
            bool                          m_bEnable;

            ::user::interaction *         m_pwndRegion;
            ::user::interaction *         m_pwndDraw;
            ::user::interaction *         m_pwndEvent;
            ::user::interaction *         m_pwndCommand;


            UINT                          m_uiSWPFlags;

            WorkSetListenerArray          m_wfla;

            MoveManager *                 m_pmovemanager;
            SizeManager *                 m_psizemanager;
            SysMenuManager *              m_psystemmenumanager;
            DockManager *                 m_pdockmanager;

            bool                          m_bDockingEnabled;
            bool                          m_bMovingEnabled;
            bool                          m_bSizingEnabled;
            bool                          m_bSysMenuEnabled;
            bool                          m_bNotifyIconEnable;
            bool                          m_bFullScreenEnable;


            appearance *                  m_pappearance;


            WorkSet();
            virtual ~WorkSet();


            void OnNcCalcSize(LPRECT lprect);
            bool IsEnabled();
            void Enable(bool bEnable);
            void _000OnBeforeSize(const RECT & rect);

            ::user::interaction * GetEventWindow();
            ::user::interaction * GetRegionWindow();
            ::user::interaction * get_draw_window();
            ::user::interaction * GetCommandWindow();


            appearance * get_appearance();
            DockManager * GetDockingManager();
            MoveManager * GetMovingManager();
            SizeManager * GetSizingManager();


            void AttachFrameSchema(sp(frame) pframeschema);
            void _001InstallEventHandling(::message::dispatch * pdispatch);

            DECL_GEN_SIGNAL(_001OnLButtonDown);
            DECL_GEN_SIGNAL(_001OnMouseMove);
            DECL_GEN_SIGNAL(_001OnLButtonUp);
            DECL_GEN_SIGNAL(_001OnNcLButtonDown);
            DECL_GEN_SIGNAL(_001OnNcMouseMove);
            DECL_GEN_SIGNAL(_001OnNcLButtonUp);
            DECL_GEN_SIGNAL(_001OnNcHitTest);
            DECL_GEN_SIGNAL(_001OnTimer);
            DECL_GEN_SIGNAL(_001OnSize);
            DECL_GEN_SIGNAL(_001OnMove);

               // point should be in screen coordinates
               EHitTest hit_test(point ptCursor);


            bool IsNotifyIconEnabled();
            void EnableNotifyIcon(bool bEnable = true);
            void EnableFullScreen(bool bEnable = true);
            bool IsFullScreenEnabled();
            void WindowClose();
            void UpdateApperanceMode(bool bFullScreen);
            void SetDownUpInterface(CWorkSetDownUpInterface *pinterface);
            void WindowProcBefore(::user::interaction * pwnd, signal_details * pobj);
            void WindowProcHover(::user::interaction * pwnd, signal_details * pobj);
            DECL_GEN_SIGNAL(_001OnActivate);
               DECL_GEN_SIGNAL(_001OnCommand);
               DECL_GEN_SIGNAL(_001OnNcActivate);
               void RemoveListener(WorkSetListener * plistener);
            void AddListener(WorkSetListener * plistener);
            void OnSizingGripMove(EGrip egrip);

            bool IsHoverModeOn();
            bool IsHoverActive();
            void OnMoving();
            void OnMove();
            void SetDockMask(EDock emask);

            virtual void OnDock();
            void layout();
            bool Hover(bool bHoverActive);
            void hover_relay_event(signal_details * pobj);
            void ChildWnd(::user::interaction * pwnd, ::user::interaction * pwndParent);
            void FrameWnd(::user::interaction * pwnd);
            bool Start();
            //void OnDown();
            //void OnUp();


            void appearance_title_bar_layout(bool bInitialControlBoxPosition);


            ::user::interaction * GetWndDraw();
            ::user::interaction * GetWndRegion();

            bool update(
               ::user::interaction * pwndDraw,
               ::user::interaction * pwndRegion,
               ::user::interaction * pwndEvent,
               ::user::interaction * pwndCommand);

            void SetAppearanceTransparency(EAppearanceTransparency nTransparency);
            void SetFrameSchemaStyle(int32_t nStyle);
            void SetActiveFlag(bool fActive);
            void SetSWPFlags(UINT uiFlags);

            ::user::EAppearance GetAppearance();
            void SetAppearance(::user::EAppearance nMode);
            void SetAppearance();

            void GetRegionClientRect(LPRECT lprect);
            void get_draw_client_rect(LPRECT lprect);
            //void SetWindow(::user::interaction * pwnd);
            void relay_event(signal_details * pobj);
            void message_handler(signal_details * pobj);

            void _001OnDraw(::draw2d::graphics * pdc);

            virtual bool BaseOnControlEvent(::user::control_event * pevent);


            void EnableDock(bool bEnable);
            void EnableMove(bool bEnable);
            void EnableSize(bool bEnable);
            void EnableSysMenu(bool bEnable);
            void EnableApperance(bool bEnable);

            bool IsDockingEnabled();
            bool IsMovingEnabled();
            bool IsSizingEnabled();
            bool IsSysMenuEnabled();
            bool IsAppearanceEnabled();

            bool IsFullScreen();
            bool ViewFullScreen(bool bFullScreen);

            virtual bool _001OnCmdMsg(::aura::cmd_msg * pcmdmsg);

            virtual void OnSize(UINT nType, int32_t cx, int32_t cy);


         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user








