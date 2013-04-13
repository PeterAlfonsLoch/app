#pragma once


namespace ca2
{

   CLASS_DECL_ca2 UINT c_cdecl application_thread_procedure(LPVOID pvoid);

   typedef sp(::ca::application) (* LPFN_instantiate_application)(sp(::ca::application) pappParent, const char * pszId);

   extern CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application;


   class CLASS_DECL_ca2 application : 
      public ::cubebase::application
   {
   public:
      
      
      ::uinteraction::uinteraction      * m_puinteraction;
      ::user::user              * m_puserbase;
      ::userex::userex                  * m_puserex;
      ::filemanager::filemanager        * m_pfilemanager;
      ::mail::mail                      * m_pmail;
#ifdef WINDOWSEX
      array < MONITORINFO >          m_monitorinfoa;
      array < MONITORINFO >          m_monitorinfoaDesk;
#endif

      stringa m_straAppInterest;
      string_map < oswindow, oswindow > m_mapAppInterest;


      application();
      virtual ~application();


      using ::cubebase::application::construct;
      virtual void construct();
      

      virtual bool final_handle_exception(::ca::exception & e);
      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize2();

      virtual bool initialize_instance();
      virtual int32_t  exit_instance();

      virtual void _001OnFileNew();
      virtual bool bergedge_start();


      virtual bool is_serviceable();
      virtual service_base * allocate_new_service();


      virtual bool on_install();
      virtual bool on_uninstall();

      virtual int32_t run();

      virtual void on_request(sp(::ca::create_context) pcreatecontext);

      sp(::user::document_interface) _001OpenDocumentFile(var varFile);

      sp(::ca::application) get_system();

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);


      virtual void defer_add_document_template(sp(::document_template) ptemplate);

      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif





      virtual bool set_keyboard_layout(const char * pszPath, bool bUser);

      
      inline ::uinteraction::uinteraction          & uinteraction () { return *m_puinteraction  ; }
      inline ::user::user                  & user     () { return *m_puserbase      ; }
      inline ::userex::userex                      & userex       () { return *m_puserex        ; }
      inline ::filemanager::filemanager            & filemanager  () { return *m_pfilemanager   ; }
      inline ::mail::mail                          & mail         () { return *m_pmail          ; }

      
      string message_box(const char * pszMatter, ::ca::property_set & propertyset);
      using ::ca::application::simple_message_box;
      virtual int32_t simple_message_box_timeout(sp(::user::interaction) puiOwner, const char * pszMessage, int32_t iTimeout, UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle = MB_OK);
      virtual int32_t track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie);

      virtual bool get_fs_size(string & strSize, const char * pszPath, bool & bPending);
      virtual bool get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending);
   
      virtual void data_on_after_change(::ca::signal_object * pobj);



      virtual void set_title(const char * pszTitle);


      virtual bool _001CloseApplicationByUser(sp(::user::interaction) pwndExcept);


#ifdef WINDOWSEX

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam);

#endif

      void update_app_interest();
      void ensure_app_interest();


      virtual oswindow get_ca2_app_wnd(const char * psz);


      virtual void request_create(sp(::ca::create_context) pcreatecontext);

      virtual void on_exclusive_instance_local_conflict();

      virtual int32_t send_simple_command(const char * psz, void * osdataSender);
      virtual int32_t send_simple_command(void * osdata, const char * psz, void * osdataSender);




   };

   
} // namespace ca2



