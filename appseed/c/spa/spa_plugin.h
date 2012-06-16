#pragma once


int spaboot_start(const char * pszVersion, const char * pszId);


namespace spa
{


   enum e_check
   {
      check_before_auth,
      check_before_start,
   };


   class CLASS_DECL_c plugin :
      virtual public ::hotplugin::plugin
   {
   public:

      canvas      m_canvas;
      DWORD       m_dwLastInstallingCheck;
      DWORD       m_dwLastRestart;
      



      plugin();
      virtual ~plugin();


      virtual bool hist(const char * pszUrl);
      virtual void run_start_install(const char * pszType, const char * pszRun);


      virtual void start_ca2();


      //int starter_start(const char * pszId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

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

      virtual void restart();

      virtual void set_window_rect(LPCRECT lpcrect);

   };


} // namespace spa



