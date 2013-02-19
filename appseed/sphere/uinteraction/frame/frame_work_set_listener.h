#pragma once


namespace uinteraction
{


namespace frame
{

   class WorkSet;
   class WorkSetListenerArray;

   class CLASS_DECL_ca2 WorkSetListener :
      public pha(WorkSetListenerArray)
   {
   public:
      virtual void on_delete(::ca::ca * poc);
      void attach(WorkSetListenerArray * plistenerpa);
      
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

} // namespace frame





} // namespace uinteraction






