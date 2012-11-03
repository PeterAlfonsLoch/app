#pragma once


class file_system;
typedef ca::smart_pointer < file_system > file_system_sp;
class Ex1FactoryImpl;


namespace gen
{


   class command_line;


} // namespace gen

namespace visual
{


   class icon;


} // namespace visual


#if defined(LINUX) || defined(MACOS)

typedef ::visual::icon * HICON;

#endif


namespace ex2
{


   class CLASS_DECL_ca application :
      public gen::application,
      virtual public ca::smart_pointer < ex2::application >
   {
   public:


      ex1::file_system_sp m_spfilesystem;


      application();
      virtual ~application();


      virtual void construct();
      virtual void construct(const char * pszId);

      virtual void SetCurrentHandles();



      virtual bool set_main_init_data(::ca::main_init_data * pdata);

      virtual bool process_initialize();

      virtual bool initialize1(); // cgcl // first initialization
      virtual bool initialize2(); // cst  // second initialization
      virtual bool initialize3(); // third initialization and so on...

      virtual bool initialize(); // last initialization

      virtual bool finalize();

      virtual int exit_instance();

      virtual ::ex1::file_system & file_system();
      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual ::user::document_interface * _001OpenDocumentFile(var varFile);
      DECL_GEN_SIGNAL(_001OnFileNew);


      virtual ::ca::application * get_app() const;

      virtual string get_version();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual bool DeferRegisterClass(LONG fToRegister, const char ** ppszClass);

      // Temporary ::collection::map management (locks temp ::collection::map on current thread)
      virtual void LockTempMaps();
      virtual bool UnlockTempMaps(bool bDeleteTemps = TRUE);
      virtual const char * RegisterWndClass(UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

      virtual ::radix::thread * GetThread();
      virtual void set_thread(::radix::thread * pthread);
      virtual ::user::interaction * GetMainWnd();

      //virtual ::ca::graphics * graphics_from_os_data(void * pdata);

      virtual ::ca::window * window_from_os_data(void * pdata);
      virtual ::ca::window * window_from_os_data_permanent(void * pdata);

      virtual ::ca::window * get_desktop_window();

      virtual ::ca::window * FindWindow(const char * lpszClassName, const char * lpszWindowName);
      virtual ::ca::window * FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow);

#ifndef METROWIN
      virtual void get_time(timeval *p);
#endif
      virtual void set_env_var(const string & var,const string & value);
      virtual unsigned long get_thread_id();

   };

} // namespace ex2


