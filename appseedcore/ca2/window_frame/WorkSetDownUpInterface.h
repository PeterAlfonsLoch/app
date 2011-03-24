#pragma once

namespace window_frame
{

   class UpDownTarget;

   class CLASS_DECL_ca CWorkSetDownUpInterface  
   {
   public:
      CWorkSetDownUpInterface();
      virtual bool WndFrameworkDownUpGetUpEnable() = 0;
      virtual bool WndFrameworkDownUpGetDownEnable() = 0;

      UpDownTarget * m_pupdowntarget;

      virtual void window_frame_Attach();
      virtual void window_frame_Detach();

      int m_iType;
      int m_iIndex;

   };

} // namespace window_frame
