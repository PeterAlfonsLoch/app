#pragma once


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         class CLASS_DECL_CORE SysMenuManager
         {
         public:


            friend class WorkSet;

            enum States
            {
               state_initial = 0,
               StateMBDown = 1 // MOUSE BUtton down
            };

            WorkSet *      m_pworkset;
            States         m_enumState;


            SysMenuManager(WorkSet * pwf);
            virtual ~SysMenuManager();

            bool OnLButtonDblClk(UINT nFlags, point point);
            void relay_event(signal_details * pobj);

            bool update(WorkSet * pset);

            void message_handler(sp(::user::interaction) pwnd, signal_details * pobj);


         };


      } // namespace frame


   } // namespace uinteraction


} // namespace user










