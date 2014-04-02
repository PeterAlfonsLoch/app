#include "framework.h"


namespace uinteraction
{


   namespace frame
   {


      WorkSetListener::WorkSetListener()
      {

      }


      WorkSetListener::~WorkSetListener()
      {

      }


      void WorkSetListener::WFLOnSizingGripMove(WorkSet *pwf, sp(::user::interaction)pwnd, EGrip egrip)
      {
         UNREFERENCED_PARAMETER(pwf);
         UNREFERENCED_PARAMETER(pwnd);
         UNREFERENCED_PARAMETER(egrip);
      }

      void WorkSetListener::WFLOnDock(
         WorkSet *pwf,
         sp(::user::interaction)pwnd)
      {
         UNREFERENCED_PARAMETER(pwf);
         UNREFERENCED_PARAMETER(pwnd);
      }

      void WorkSetListener::WFLOnClose(
         WorkSet *pwf,
         sp(::user::interaction)pwnd)
      {
         UNREFERENCED_PARAMETER(pwf);
         UNREFERENCED_PARAMETER(pwnd);
      }

      void WorkSetListener::WFLOnNcLButtonDown(
         WorkSet * pworkset,
         sp(::user::interaction) pwnd,
         UINT nHitTest,
         point point)
      {
         UNREFERENCED_PARAMETER(pworkset);
         UNREFERENCED_PARAMETER(pwnd);
         UNREFERENCED_PARAMETER(nHitTest);
         UNREFERENCED_PARAMETER(point);
      }

      void WorkSetListener::attach(WorkSetListenerArray *plistenerpa)
      {
         add(plistenerpa);
         m_listenerpapa.add(plistenerpa);
      }


   } // namespace frame



} // namespace uinteraction









