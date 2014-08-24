#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {




         

         class CLASS_DECL_CORE MoveManager :
            virtual public signalizable
         {
         public:


            WorkSet *               m_pworkset;
            uint32_t                m_dwLastMoveTime;
            bool                    m_bPendingMove;
            point                   m_ptPendingMove;
            void *                  m_oswindowPendingMove;
            EBorder                 m_eborderMask;
            point                   m_ptCursorOrigin;
            point                   m_ptWindowOrigin;
            bool                    m_bMoving;
            uint32_t                m_dwLastMovingTime;
            UINT                    m_uiSWPFlags;
            uint32_t                m_dwPaintDelay;


            MoveManager(WorkSet * pworkset);
            virtual ~MoveManager();


            sp(::user::interaction) GetEventWindow();
            sp(::user::interaction) GetMoveWindow();

            bool Relay(::message::mouse * pmouse);
            bool _000OnLButtonDown(::message::mouse * pmouse);
            bool _000OnMouseMove(::message::mouse * pmouse);
            bool _000OnLButtonUp(::message::mouse * pmouse);
            bool _000OnTimer(UINT nIDEvent);


            void SetBorderMask(EBorder emask);
            EBorder GetBorderMask();

            bool IsMoving();
            void MoveWindow(void * oswindow, point pt);
            void SetSWPFlags(UINT uiFlags);
            bool relay_event(MESSAGE * lpMsg);
            bool update(WorkSet * pwf);

            static const uint32_t s_dwMoveTime;

            void message_handler(sp(::user::interaction) pwnd, signal_details * pobj);
         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user







