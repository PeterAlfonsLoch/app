#pragma once

namespace window_frame
{

   class WorkSetListener;
   class WorkSet;

   class CLASS_DECL_ca WorkSetListenerArray :
      public pha(WorkSetListener)
   {
      friend class WorkSet;
      friend class WorkSetListener;
   public:
      virtual void on_delete(::ca::ca * poc);
      void Attach(WorkSetListener *plistener);
      //void add(WorkSetListener * plistener);
      WorkSetListenerArray();
      virtual ~WorkSetListenerArray();

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
   };

} //   namespace window_frame
