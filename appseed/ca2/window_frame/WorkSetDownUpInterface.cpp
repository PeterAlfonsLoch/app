#include "framework.h"

namespace window_frame
{

   CWorkSetDownUpInterface::CWorkSetDownUpInterface()
   {
      m_pupdowntarget = NULL;
   }
   void CWorkSetDownUpInterface::window_frame_Attach()
   {
      if(m_pupdowntarget != NULL)
      {
         m_pupdowntarget->UpDownTargetAttach(this);
      }
   }
   void CWorkSetDownUpInterface::window_frame_Detach()
   {
      if(m_pupdowntarget != NULL)
      {
         m_pupdowntarget->UpDownTargetDetach(this);
      }
   }

} // namespace window_frame