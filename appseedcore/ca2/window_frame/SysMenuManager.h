#pragma once

namespace window_frame
{

   class CLASS_DECL_ca SysMenuManager  
   {
      friend class WorkSet;
      enum States
      {
         state_initial = 0,
         StateMBDown = 1 // MOUSE BUtton down
      };
   public:
      SysMenuManager(WorkSet * pwf);
      virtual ~SysMenuManager();

   public:
      bool OnLButtonDblClk(UINT nFlags, point point);
      void relay_event(gen::signal_object * pobj);

      bool update(WorkSet * pset);

   protected:
      WorkSet   * m_pworkset;
      States     m_enumState;
      void message_handler(::user::interaction * pwnd, gen::signal_object * pobj);
   };

} // namespace window_frame
