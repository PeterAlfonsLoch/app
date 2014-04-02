#pragma once


namespace uinteraction
{


namespace frame
{

   class WorkSet;
   class WorkSetListenerArray;

   class CLASS_DECL_CORE WorkSetListener :
      public spa(WorkSetListenerArray)
   {
   public:
      
      void attach(WorkSetListenerArray * plistenerpa);
      
      WorkSetListener();
      virtual ~WorkSetListener();

      virtual void WFLOnSizingGripMove(
         WorkSet * pwf,
         sp(::user::interaction) pwnd,
         EGrip egrip);

      virtual void WFLOnDock(
         WorkSet * pwf,
         sp(::user::interaction) pwnd);

      virtual void WFLOnClose(
         WorkSet * pwf,
         sp(::user::interaction) pwnd);

      virtual void WFLOnNcLButtonDown(
         WorkSet * pworkset,
         sp(::user::interaction) pwnd,
         UINT nHitTest,
         point point);

   protected:
      spa(WorkSetListenerArray) m_listenerpapa;

   };

} // namespace frame





} // namespace uinteraction






