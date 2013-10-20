#pragma once


int32_t spaboot_start(const char * pszVersion, const char * pszId);


namespace spa_install
{

   enum e_check
   {
      
      check_before_auth,
      check_before_start

   };


   class CLASS_DECL_BOOT plugin :
      virtual public ::hotplugin::plugin,
      virtual public ::simple_ui,
      virtual public ::spa_login::callback
   {
   public:


      class CLASS_DECL_BOOT thread_start_ca2 :
         public thread_layer
      {
      public:


        plugin * m_pplugin;

         virtual bool on_idle();


      } ;

      thread_start_ca2  m_startca2;
      spa_login      m_login;
      canvas         m_canvas;
      uint32_t          m_dwLastInstallingCheck;
      uint32_t          m_dwLastRestart;
      // logged in ? alarm comments
      bool           m_bLogged;
      // in login process, login screen should be shown
      bool           m_bLogin;
      bool           m_bRestartCa2;
      bool           m_bPendingStream;
      uint32_t          m_dwLastOk;

      bool              m_bPluginShiftKey;




      plugin();
      virtual ~plugin();


      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszType, const char * pszRun, const char * pszLocale, const char * pszSchema);


      virtual void start_ca2();

      virtual bool thread_start_ca2_on_idle();

      virtual bool calc_logged();

      //int32_t starter_start(const char * pszId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(simple_graphics & gWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

      virtual void login_result(spa_login::e_result eresult);

#ifdef WINDOWS

      virtual LRESULT message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam);

#else

      virtual int32_t message_handler(XEvent * pevent);

#endif

      virtual void on_paint_progress(simple_graphics & g, LPCRECT lprect);

      virtual double extract_spa_progress_rate();

      virtual void deferred_prodevian_redraw();

#ifndef METROWIN

      virtual void on_post(small_ipc_rx_channel * prxchannel, int64_t a, int64_t b);

      using ::hotplugin::plugin::on_receive;

      virtual void on_receive(small_ipc_rx_channel * prxchannel, int32_t message, void * pdata, int32_t len);

#endif

      virtual bool is_installing();

      virtual void restart_small_ipc_channel();

      virtual void set_window_rect(LPCRECT lpcrect);

      virtual void on_ready();

      virtual string defer_get_plugin();

      virtual string defer_get(const char * pszUrl);


   };


} // namespace spa_install



