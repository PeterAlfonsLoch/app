#pragma once

namespace window_frame
{

   class WorkSet;
   class WorkSetListenerArray;

   class CLASS_DECL_ca WorkSetListener :
      public pha(WorkSetListenerArray)
   {
   public:
      virtual void on_delete(::ca::ca * poc);
      void Attach(WorkSetListenerArray * plistenerpa);
      
      WorkSetListener();
      virtual ~WorkSetListener();

      virtual void WFLOnSizingGripMove(
         WorkSet * pwf,
         ::user::interaction * pwnd,
         EGrip egrip);

      virtual void WFLOnDock(
         WorkSet * pwf,
         ::user::interaction * pwnd);

      virtual void WFLOnClose(
         WorkSet * pwf,
         ::user::interaction * pwnd);

      virtual void WFLOnNcLButtonDown(
         WorkSet * pworkset,
         ::user::interaction * pwnd,
         UINT nHitTest,
         point point);

   protected:
      pha(WorkSetListenerArray) m_listenerpapa;

   };

} // namespace window_frame