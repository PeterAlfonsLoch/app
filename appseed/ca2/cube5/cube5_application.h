#pragma once


namespace cube5
{


   class CLASS_DECL_ca2 application :
      virtual public ::userstack::application
   {
   public:


      ::filemanager::filemanager          m_filemanager;


      application();
      virtual ~application();

#ifdef WINDOWSEX
      base_array < MONITORINFO > m_monitorinfoa;
      base_array < MONITORINFO > m_monitorinfoaDesk;
#endif

      
      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);



      virtual bool final_handle_exception(::ca::exception & e);
      virtual bool initialize();
      virtual bool initialize1();

      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif


      filemanager::_shell::ImageSet * m_pshellimageset;


      application();
      virtual ~application();

      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      filemanager::_shell::ImageSet & shellimageset();

      virtual bool initialize1();
      virtual bool initialize();
      
      string message_box(const char * pszMatter, gen::property_set & propertyset);
      using ::radix::application::simple_message_box;
      virtual int32_t simple_message_box_timeout(::user::interaction * puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(::user::interaction * puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, ::user::interaction * puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);
   
      virtual void data_on_after_change(gen::signal_object * pobj);


   };



} // namespace cube4


