#pragma once


class __rect64;

int spaboot_start(const char * pszVersion, const char * pszId);


namespace primitive
{
   class memory;
}


namespace ex1
{
   class file;
}


namespace plugin
{

   enum e_check
   {
      check_before_auth,
      check_before_start,
   };


   class host_interaction;
   class system;

   class CLASS_DECL_ca plugin :
      virtual public hotplugin::plugin,
      virtual public radix::object
   {
   public:


      host_interaction *            m_puiHost;
      primitive::memory             m_memory;
      ::plugin::system *            m_psystem;
      int                           m_iEdge;
      bool                          m_bMainReady;
      string                        m_strCa2LoginRuri;
      string                        m_strCa2LogoutRuri;
      string                        m_strOpenUrl;
      bool                          m_bOpenUrl;
      ::visual::dib_sp              m_dib;


      plugin();


      virtual host_interaction * create_host_interaction() = 0;

      virtual void set_window_rect(LPCRECT lpcrect);

      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszRun);


      virtual bool finalize();

      virtual bool os_native_bergedge_start();

      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual int  start_ca2_system();

      virtual void on_ready();

      virtual void ready_on_main_thread();

      virtual void open_ca2_string(const char * psz);

#ifdef _WINDOWS
      virtual UINT_PTR message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam);
#else
      virtual int message_handler(XEvent * pevent);
#endif

      void start_ca2_login();
      void start_ca2_logout();
      void ca2_login();
      void ca2_logout();
      static UINT AFX_CDECL thread_proc_ca2_login(LPVOID pvoid);
      static UINT AFX_CDECL thread_proc_ca2_logout(LPVOID pvoid);





   };

   ATOM MyRegisterClass(HINSTANCE hInstance);

} // namespace npca2
