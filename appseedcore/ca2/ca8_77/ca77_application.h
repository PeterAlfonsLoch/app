#pragma once

namespace ca77
{

   class CLASS_DECL_ca application :
      virtual public calculator::application,
      virtual public filemanager::application
   {
   public:

      application();
      virtual ~application();

#if !core_level_1 && !core_level_2
      base_array < MONITORINFO > m_monitorinfoa;
      base_array < MONITORINFO > m_monitorinfoaDesk;
#endif

      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      


      virtual bool final_handle_exception(::ca::exception & e);
      virtual bool initialize();
      virtual bool initialize1();

      void enum_display_monitors();

#if !core_level_1 && !core_level_2
      static BOOL CALLBACK monitor_enum_proc(
        HMONITOR hmonitor,
        HDC hdcMonitor,
        LPRECT lprcMonitor,
        LPARAM dwData);

      void monitor_enum(
        HMONITOR hmonitor,
        HDC hdcMonitor,
        LPRECT lprcMonitor);
#endif

   };

   inline application & app_cast(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ca