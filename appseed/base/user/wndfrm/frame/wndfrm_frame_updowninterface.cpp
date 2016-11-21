#include "framework.h"


namespace user
{


   namespace wndfrm
   {


      namespace frame
      {


         WorkSetUpDownInterface::WorkSetUpDownInterface()
         {

            m_pupdowntarget            = NULL;

            m_eupdown                  = ::user::interaction::updown_normal_frame;     

         }

         WorkSetUpDownInterface::~WorkSetUpDownInterface()
         {

         }

         
         bool WorkSetUpDownInterface::wfi_is_up()
         {

            return m_eupdown == updown_up;

         }


         bool WorkSetUpDownInterface::wfi_is_down()
         {

            return m_eupdown == updown_down;

         }


         bool WorkSetUpDownInterface::wfi_is_up_down()
         {

            return m_eupdown != updown_normal_frame;

         }




      } // namespace frame


   } // namespace wndfrm


} // namespace user



