#pragma once

#include "c/os/os.h"


int spaboot_start(const char * pszVersion, const char * pszId);


namespace spa
{


   enum e_check
   {
      check_before_auth,
      check_before_start,
   };


   class CLASS_DECL_c plugin :
      virtual public ::hotplugin::plugin,
      virtual public ::simple_ui,
      virtual public ::spa_login::callback
   {
   public:


      class CLASS_DECL_c thread_start_ca2 :
         public thread_layer
      {
      public:


        plugin * m_pplugin;

         virtual bool on_idle();


      } ;

      thread_start_ca2  m_startca2;
      spa_login      m_login;
      canvas         m_canvas;
      DWORD          m_dwLastInstallingCheck;
      DWORD          m_dwLastRestart;
      // logged in ? alatel comments
      bool           m_bLogged;
      // in login process, login screen should be shown
      bool           m_bLogin;
      bool           m_bRestartCa2;
      bool           m_bPendingStream;
      DWORD          m_dwLastOk;




      plugin();
      virtual ~plugin();


      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszType, const char * pszRun, const char * pszLocale, const char * pszSchema);


      virtual void start_ca2();

      virtual bool thread_start_ca2_on_idle();

      virtual bool calc_logged();

      //int starter_start(const char * pszId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

      virtual void login_result(spa_login::e_result eresult);

#ifdef WINDOWS

      virtual uint_ptr message_handler(uint_ptr uiMessage, WPARAM wparam, LPARAM lparam);

#else

      virtual int message_handler(XEvent * pevent);

#endif

      virtual void on_paint_progress(HDC hdc, LPCRECT lprect);

      virtual double extract_spa_progress_rate();

      virtual void deferred_prodevian_redraw();

      virtual void on_post(small_ipc_rx_channel * prxchannel, int a, int b);

      virtual void on_receive(small_ipc_rx_channel * prxchannel, int message, void * pdata, int len);

      virtual bool is_installing();

      virtual void restart_small_ipc_channel();

      virtual void set_window_rect(LPCRECT lpcrect);

      virtual void on_ready();

      virtual vsstring defer_get_plugin();

      virtual vsstring defer_get(const char * pszUrl);





   };


} // namespace spa



