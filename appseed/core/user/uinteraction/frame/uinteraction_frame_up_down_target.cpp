#include "framework.h"


namespace user
{

   namespace uinteraction
   {


      namespace frame
      {

         UpDownTarget::UpDownTarget()
         {
            m_eupdowntargettype = type_normal_frame;
         }

         void UpDownTarget::UpDownTargetAttach(CWorkSetDownUpInterface * pupdown)
         {

            bool bAttached = false;

            if(m_eupdowntargettype == type_normal_frame)
               m_eupdowntargettype = type_none;

            try
            {
               if(OnUpDownTargetAttach(pupdown))
                  bAttached = true;
            }
            catch(...)
            {
            }

            if(bAttached)
            {
               m_eupdowntargettype = type_down;
            }

         }


         void UpDownTarget::UpDownTargetDetach(CWorkSetDownUpInterface * pupdown)
         {

            bool bDetached = false;


            if(m_eupdowntargettype == type_normal_frame)
               m_eupdowntargettype = type_none;

            try
            {
               if(OnUpDownTargetDetach(pupdown))
                  bDetached = true;
            }
            catch(...)
            {
            }

            if(bDetached)
            {
               m_eupdowntargettype = type_up;
            }

         }


         bool UpDownTarget::up_down_target_is_up()
         {
            return m_eupdowntargettype == type_up;
         }

         bool UpDownTarget::up_down_target_is_down()
         {
            return m_eupdowntargettype == type_down;
         }

         bool UpDownTarget::is_up_down_target()
         {
            return m_eupdowntargettype != type_normal_frame;
         }



      } // namespace frame

   } // namespace uinteraction






} // namespace user




