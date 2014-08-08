#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE DockManager:
            virtual public signalizable
         {
         public:


            WorkSet *                  m_pworkset;
            uint32_t                   m_dwLastMoveTime;
            bool                       m_bPendingMove;
            point                      m_ptPendingMove;
            void *                     m_oswindowPendingMove;
            EBorder                    m_eborderMask;
            EDock                      m_edockState;
            point                      m_ptCursorOrigin;
            point                      m_ptWindowOrigin;
            bool                       m_bDocking;
            uint32_t                   m_dwLastMovingTime;
            UINT                       m_uiSWPFlags;
            uint32_t                   m_dwPaintDelay;
            ::user::EAppearance        m_eappearanceOrigin;
            size                       m_sizeOrigin;


            DockManager(WorkSet * pworkset);
            virtual ~DockManager();


            sp(::user::interaction) GetEventWindow();
            sp(::user::interaction) GetDockWindow();

            bool Relay(::message::mouse * pmouse);
            bool _000OnLButtonDown(::message::mouse * pmouse);
            bool _000OnMouseMove(::message::mouse * pmouse);
            bool _000OnLButtonUp(::message::mouse * pmouse);
            bool _000OnTimer(UINT nIDEvent);


            void SetBorderMask(EBorder emask);
            EBorder GetBorderMask();

            void SetDockMask(EDock emask);
            EDock GetDockState();

            bool IsMoving();
            void MoveWindow(void * oswindow,point pt);
            void SetSWPFlags(UINT uiFlags);
            bool relay_event(MESSAGE * lpMsg);
            bool update(WorkSet * pwf);

            static const uint32_t s_dwMoveTime;

            void message_handler(sp(::user::interaction) pwnd,signal_details * pobj);
         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user







