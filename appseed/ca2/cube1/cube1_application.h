#pragma once


namespace cube1
{


   class CLASS_DECL_ca application :
      virtual public calculator::application,
      virtual public filemanager::application
   {
   public:

      application();
      virtual ~application();

#ifdef WINDOWS
      base_array < MONITORINFO > m_monitorinfoa;
      base_array < MONITORINFO > m_monitorinfoaDesk;
#endif

      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);



      virtual bool final_handle_exception(::ax::exception & e);
      virtual bool initialize();
      virtual bool initialize1();

      void enum_display_monitors();

#if defined(WINDOWS)
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

   inline application & app_cast(::ax::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

} // namespace ax
