#include "framework.h"


namespace uinteraction
{


namespace frame
{

   CWorkSetDownUpInterface::CWorkSetDownUpInterface()
   {
      m_pupdowntarget = ::null();
   }
   void CWorkSetDownUpInterface::frame_Attach()
   {
      if(m_pupdowntarget != ::null())
      {
         m_pupdowntarget->UpDownTargetAttach(this);
      }
   }
   void CWorkSetDownUpInterface::frame_Detach()
   {
      if(m_pupdowntarget != ::null())
      {
         m_pupdowntarget->UpDownTargetDetach(this);
      }
   }

} // namespace frame

} // namespace uinteraction






