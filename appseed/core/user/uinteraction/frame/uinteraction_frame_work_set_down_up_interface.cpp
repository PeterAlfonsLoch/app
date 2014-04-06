#include "framework.h"


namespace user
{

   namespace uinteraction
   {


      namespace frame
      {

         CWorkSetDownUpInterface::CWorkSetDownUpInterface()
         {
            m_pupdowntarget = NULL;
         }
         void CWorkSetDownUpInterface::frame_Attach()
         {
            if(m_pupdowntarget != NULL)
            {
               m_pupdowntarget->UpDownTargetAttach(this);
            }
         }
         void CWorkSetDownUpInterface::frame_Detach()
         {
            if(m_pupdowntarget != NULL)
            {
               m_pupdowntarget->UpDownTargetDetach(this);
            }
         }

      } // namespace frame

   } // namespace uinteraction






} // namespace user





