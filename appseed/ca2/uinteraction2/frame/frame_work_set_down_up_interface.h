#pragma once


namespace uinteraction
{

   namespace frame
   {

      class UpDownTarget;

      class CLASS_DECL_ca2 CWorkSetDownUpInterface:
         virtual public ::ca::object
      {
      public:


         sp(UpDownTarget)       m_pupdowntarget;
         int32_t                  m_iType;
         int32_t                  m_iIndex;


         CWorkSetDownUpInterface();


         virtual bool WndFrameworkDownUpGetUpEnable() = 0;
         virtual bool WndFrameworkDownUpGetDownEnable() = 0;

         virtual void frame_Attach();
         virtual void frame_Detach();


      };



   } // namespace frame



} // namespace uinteraction




