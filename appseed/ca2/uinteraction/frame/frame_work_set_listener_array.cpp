#include "framework.h"


namespace uinteraction
{


namespace frame
{

   //////////////////////////////////////////////////////////////////////
   // Construction/Destruction
   //////////////////////////////////////////////////////////////////////

   WorkSetListenerArray::WorkSetListenerArray()
   {

   }

   WorkSetListenerArray::~WorkSetListenerArray()
   {

   }

   void WorkSetListenerArray::WFLOnSizingGripMove(
      WorkSet * pwf,
      ::user::interaction * pwnd,
      EGrip egrip)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         WorkSetListener * plistener = this->element_at(i);
         plistener->WFLOnSizingGripMove(
            pwf,
            pwnd,
            egrip);
      }
   }

   void WorkSetListenerArray::WFLOnDock(
      WorkSet * pwf,
      ::user::interaction * pwnd)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         WorkSetListener * plistener = this->element_at(i);
         plistener->WFLOnDock(
            pwf,
            pwnd);
      }
   }

   void WorkSetListenerArray::WFLOnClose(
      WorkSet * pwf,
      ::user::interaction * pwnd)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         WorkSetListener * plistener = this->element_at(i);
         plistener->WFLOnClose(
            pwf,
            pwnd);
      }
   }

   void WorkSetListenerArray::WFLOnNcLButtonDown(
      WorkSet * pworkset,
      ::user::interaction * pwnd,
      UINT nHitTest,
      point point)
   {
      for(int i = 0; i < this->get_size(); i++)
      {
         WorkSetListener * plistener = this->element_at(i);
         plistener->WFLOnNcLButtonDown(
            pworkset,
            pwnd,
            nHitTest,
            point);
      }
   }

   /*void WorkSetListenerArray::add(WorkSetListener *plistener)
   {
      Carray<WorkSetListener *, WorkSetListener *>
         ::add(plistener);
   }*/

   void WorkSetListenerArray::Attach(WorkSetListener * plistener)
   {
      add(plistener);
      plistener->Attach(this);
   }

   void WorkSetListenerArray::on_delete(::ca::ca * p)
   {
      UNREFERENCED_PARAMETER(p);
   }

} // namespace frame


} // namespace uinteraction






