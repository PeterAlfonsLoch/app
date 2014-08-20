#pragma once


class __rect64;

int32_t spaboot_start(const char * pszVersion, const char * pszId);


namespace primitive
{
   class memory;
}


namespace core
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

   class CLASS_DECL_CORE plugin :
      virtual public hotplugin::plugin,
      virtual public ::object
   {
   public:


      host_interaction *            m_puiHost;
      primitive::memory             m_memory;
      //::plugin::system *            m_psystem;
      index                           m_iEdge;
      bool                          m_bMainReady;
      string                        m_strCa2LoginRuri;
      string                        m_strCa2LogoutRuri;
      ::visual::dib_sp              m_dib;
      

      plugin(sp(::axis::application) papp);


      virtual host_interaction * create_host_interaction() = 0;

      virtual void set_window_rect(const RECT & rect);

      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszRun);


      virtual bool finalize();

      virtual bool os_native_bergedge_start();

      virtual void on_paint(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual int32_t  start_ca2_system();

      virtual void on_ready();

      virtual void ready_on_main_thread();

      virtual void open_ca2_string(const char * psz);

#ifdef WINDOWS

      virtual LRESULT message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam);

#elif defined(METROWIN)

#else

      virtual int32_t message_handler(XEvent * pevent);

#endif

      void start_ca2_login();
      void start_ca2_logout();
      void ca2_login();
      void ca2_logout();
      static UINT c_cdecl thread_proc_ca2_login(LPVOID pvoid);
      static UINT c_cdecl thread_proc_ca2_logout(LPVOID pvoid);





   };



} // namespace npca2
