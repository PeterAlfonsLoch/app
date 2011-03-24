#pragma once


namespace user
{
   class interaction;
}


namespace bergedge
{
   class bergedge;
}


namespace ca
{
   class type_info;
   class system;
   class window_draw;



   // Carlos Gustavo Cecyn Lundgren
   class CLASS_DECL_ca application :
      public ::radix::thread
   {
   public:

      enum e_signal
      {
         signal_initialize1, // cgcl // first initialization
         signal_initialize2, // cst  // second initialization
         signal_initialize3, // third initialization and so on...
         signal_initialize, // last initialization
         signal_process_initialize,
         signal_finalize,
         signal_exit_instance,
         signal_init_application,
         signal_none,
      };

      class CLASS_DECL_ca signal_object : 
            public gen::signal_object
      {
      public:
         signal_object(::gen::signal * psignal, e_signal esignal);
         e_signal    m_esignal;
         int         m_iRet;
         bool        m_bOk;
      };


      gen::signal                   m_signal;
      string                        m_strInstallToken;
      ::user::interaction *         m_puiInitialPlaceHolderContainer;
      bool                          m_bInitializeProDevianMode;
      ::bergedge::bergedge *        m_pbergedge;
      ::icube::system *             m_psystem;
      void *                        m_pinitmaindata;
      bool                          m_bService;
      application_bias              m_biasCalling;



      application();
      virtual ~application();


      virtual bool init_main_data(void * pdata);
      virtual bool set_main_init_data(void * pdata);

      using ::radix::thread::construct;
      virtual void construct();
      virtual void construct(const char * pszId);

      virtual bool process_initialize();

      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();

      virtual int exit();

      virtual bool finalize();

      virtual int exit_instance();

      virtual bool final_handle_exception(::ca::exception & e);

      virtual bool open_link(const char * pszLink, const char * pszTarget = NULL);

      virtual int main();

      //virtual int load_string(UINT uiId, char * lpBuffer, int nBufferMax);
      //virtual int load_string(UINT uiId, wchar_t * lpBuffer, int nBufferMax);

      virtual string load_string(id id);

      virtual application * get_app() const;

      // Temporary ::collection::map management (locks temp ::collection::map on current thread)
      virtual void LockTempMaps();
      virtual BOOL UnlockTempMaps(BOOL bDeleteTemps = TRUE);
      virtual void TermThread(HINSTANCE hInstTerm);

      virtual graphics * graphics_from_os_data(void * pdata);

      virtual window * window_from_os_data(void * pdata);
      virtual window * window_from_os_data_permanent(void * pdata);

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(HWND hwndParent, HWND hwndChildAfter, const char * lpszClass, const char * lpszWindow);

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName, const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName, const char * pszId);
      
      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();

      virtual string get_mutex_name_radix() = 0;
      virtual string get_local_mutex_id() = 0;
      virtual string get_global_mutex_id() = 0;

      virtual bool is_system();

      virtual ::ca::ca * alloc(const ::ca::type_info & info);

   };

   inline application & get(::ca::application * papp)
   {
      return *dynamic_cast < application * > (papp);
   }

   

} // namespace ca

