#pragma once


namespace uinteraction
{



   namespace frame
   {


      class WorkSet;


      class CLASS_DECL_ca2 SysMenuManager
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
         void relay_event(::ca::signal_object * pobj);

         bool update(WorkSet * pset);

         void message_handler(sp(::user::interaction) pwnd, ::ca::signal_object * pobj);


      };


   } // namespace frame







} // namespace uinteraction






