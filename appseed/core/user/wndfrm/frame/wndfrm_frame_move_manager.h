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
            EBorder                 m_eborderMask;
            point                   m_ptCursorOrigin;
            point                   m_ptWindowOrigin;
            bool                    m_bMoving;
            UINT                    m_uiSWPFlags;


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

            void message_handler(sp(::user::interaction) pwnd, signal_details * pobj);
         };


      } // namespace frame


   } // namespace wndfrm


} // namespace user







