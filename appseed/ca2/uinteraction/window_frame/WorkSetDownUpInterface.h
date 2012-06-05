#pragma once

namespace window_frame
{

   class UpDownTarget;

   class CLASS_DECL_ca2 CWorkSetDownUpInterface  
   {
   public:
      

      UpDownTarget *       m_pupdowntarget;
      int                  m_iType;
      int                  m_iIndex;


      CWorkSetDownUpInterface();


      virtual bool WndFrameworkDownUpGetUpEnable() = 0;
      virtual bool WndFrameworkDownUpGetDownEnable() = 0;

      virtual void window_frame_Attach();
      virtual void window_frame_Detach();


   };

} // namespace window_frame
