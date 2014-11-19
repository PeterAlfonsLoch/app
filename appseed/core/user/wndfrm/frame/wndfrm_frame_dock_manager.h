#pragma once


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         class CLASS_DECL_CORE DockManager:
            virtual public signalizable
         {
         public:


            WorkSet *                  m_pworkset;
            EBorder                    m_eborderMask;
            EDock                      m_edockState;
            point                      m_ptCursorOrigin;
            point                      m_ptWindowOrigin;
            bool                       m_bDocking;
            UINT                       m_uiSWPFlags;
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

            void message_handler(sp(::user::interaction) pwnd,signal_details * pobj);
         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user







