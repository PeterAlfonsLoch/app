#include "StdAfx.h"

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
         m_pupdowntarget->Attach(this);
      }
   }
   void CWorkSetDownUpInterface::window_frame_Detach()
   {
      if(m_pupdowntarget != NULL)
      {
         m_pupdowntarget->Detach(this);
      }
   }

} // namespace window_frame