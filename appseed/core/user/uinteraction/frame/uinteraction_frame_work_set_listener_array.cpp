#include "framework.h"


namespace user
{


   namespace uinteraction
   {


      namespace frame
      {


         WorkSetListenerArray::WorkSetListenerArray()
         {

         }


         WorkSetListenerArray::~WorkSetListenerArray()
         {

         }

         void WorkSetListenerArray::WFLOnSizingGripMove(
            WorkSet * pwf,
            sp(::user::interaction) pwnd,
            EGrip egrip)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
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
            sp(::user::interaction) pwnd)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               WorkSetListener * plistener = this->element_at(i);
               plistener->WFLOnDock(
                  pwf,
                  pwnd);
            }
         }

         void WorkSetListenerArray::WFLOnClose(
            WorkSet * pwf,
            sp(::user::interaction) pwnd)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
            {
               WorkSetListener * plistener = this->element_at(i);
               plistener->WFLOnClose(
                  pwf,
                  pwnd);
            }
         }

         void WorkSetListenerArray::WFLOnNcLButtonDown(
            WorkSet * pworkset,
            sp(::user::interaction) pwnd,
            UINT nHitTest,
            point point)
         {
            for(int32_t i = 0; i < this->get_size(); i++)
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

         void WorkSetListenerArray::attach(WorkSetListener * plistener)
         {
            add(plistener);
            plistener->attach(this);
         }


      } // namespace frame


   } // namespace uinteraction









} // namespace user






