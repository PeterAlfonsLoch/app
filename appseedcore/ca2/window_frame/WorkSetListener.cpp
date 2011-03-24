#include "StdAfx.h"

namespace window_frame
{

   WorkSetListener::WorkSetListener()
   {
   }

   WorkSetListener::~WorkSetListener()
   {
   }

   void WorkSetListener::WFLOnSizingGripMove(
      WorkSet *pwf,
      ::user::interaction *pwnd,
      EGrip egrip)
   {
      UNREFERENCED_PARAMETER(pwf);
      UNREFERENCED_PARAMETER(pwnd);
      UNREFERENCED_PARAMETER(egrip);
   }

   void WorkSetListener::WFLOnDock(
      WorkSet *pwf,
      ::user::interaction *pwnd)
   {
      UNREFERENCED_PARAMETER(pwf);
      UNREFERENCED_PARAMETER(pwnd);
   }

   void WorkSetListener::WFLOnClose(
      WorkSet *pwf,
      ::user::interaction *pwnd)
   {
      UNREFERENCED_PARAMETER(pwf);
      UNREFERENCED_PARAMETER(pwnd);
   }

   void WorkSetListener::WFLOnNcLButtonDown(
         WorkSet * pworkset,
         ::user::interaction * pwnd,
         UINT nHitTest,
         point point)
   {
      UNREFERENCED_PARAMETER(pworkset);
      UNREFERENCED_PARAMETER(pwnd);
      UNREFERENCED_PARAMETER(nHitTest);
      UNREFERENCED_PARAMETER(point);
   }

   void WorkSetListener::Attach(WorkSetListenerArray *plistenerpa)
   {
      add(plistenerpa);
      m_listenerpapa.add(plistenerpa);
   }

   void WorkSetListener::on_delete(::ca::ca * p)
   {
      //m_listenerpapa.remove(p);
   }

} // namespace window_frame

