#pragma once


namespace user
{


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

            sp(::user::interaction)         m_pwndRegion;
            sp(::user::interaction)         m_pwndDraw;
            sp(::user::interaction)         m_pwndEvent;
            sp(::user::interaction)         m_pwndCommand;

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

            sp(::user::interaction) GetEventWindow();
            sp(::user::interaction) GetRegionWindow();
            sp(::user::interaction) get_draw_window();
            sp(::user::interaction) GetCommandWindow();


            appearance * get_appearance();
            DockManager * GetDockManager();
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
            void WindowProcBefore(sp(::user::interaction) pwnd, signal_details * pobj);
            void WindowProcHover(sp(::user::interaction) pwnd, signal_details * pobj);
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
            void EnableDock(bool bEnable = true);
            void layout();
            bool Hover(bool bHoverActive);
            void hover_relay_event(signal_details * pobj);
            void ChildWnd(sp(::user::interaction) pwnd, sp(::user::interaction) pwndParent);
            void FrameWnd(sp(::user::interaction) pwnd);
            bool Start();
            //void OnDown();
            //void OnUp();


            void appearance_title_bar_layout(bool bInitialControlBoxPosition);


            sp(::user::interaction) GetWndDraw();
            sp(::user::interaction) GetWndRegion();

            bool update(
               sp(::user::interaction) pwndDraw,
               sp(::user::interaction) pwndRegion,
               sp(::user::interaction) pwndEvent,
               sp(::user::interaction) pwndCommand);

            void SetAppearanceTransparency(EAppearanceTransparency nTransparency);
            void SetFrameSchemaStyle(int32_t nStyle);
            void SetActiveFlag(bool fActive);
            void SetSWPFlags(UINT uiFlags);

            ::user::EAppearance GetAppearance();
            void SetAppearance(::user::EAppearance nMode);
            void SetAppearance();

            void GetRegionClientRect(LPRECT lprect);
            void get_draw_client_rect(LPRECT lprect);
            //void SetWindow(sp(::user::interaction) pwnd);
            void relay_event(signal_details * pobj);
            void message_handler(signal_details * pobj);

            void _001OnDraw(::draw2d::graphics * pdc);

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

            virtual bool _001OnCmdMsg(::base::cmd_msg * pcmdmsg);

            virtual void OnSize(UINT nType, int32_t cx, int32_t cy);


         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user








