#pragma once


namespace cube8
{


   class CLASS_DECL_ca2 application : 
      virtual public ::cube5::application
   {
   public:


      stringa m_straAppInterest;
      ::collection::string_map < oswindow, oswindow > m_mapAppInterest;


      application();
      virtual ~application();


      virtual int32_t exit_instance();


      virtual bool initialize();
      virtual bool initialize1();

      virtual bool initialize_instance();

      virtual void set_title(const char * pszTitle);


      virtual bool _001CloseApplicationByUser(::user::interaction * pwndExcept);


#ifdef WINDOWSEX

      static BOOL CALLBACK GetAppsEnumWindowsProc(oswindow oswindow, LPARAM lParam);

#endif

      void update_app_interest();
      void ensure_app_interest();


      virtual oswindow get_ca2_app_wnd(const char * psz);


      using cubebase::application::request;
      virtual void request(::ca::create_context * pcreatecontext);

      virtual void on_exclusive_instance_local_conflict();

      virtual int32_t send_simple_command(const char * psz, void * osdataSender);
      virtual int32_t send_simple_command(void * osdata, const char * psz, void * osdataSender);


   };


   CLASS_DECL_ca2 UINT c_cdecl application_thread_procedure(LPVOID pvoid);

   typedef ::ca::application * (* LPFN_instantiate_application)(::ca::application * pappParent, const char * pszId);

   extern CLASS_DECL_ca2 LPFN_instantiate_application g_lpfn_instantiate_application;


} // namespace cube8


