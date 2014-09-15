#pragma once


namespace hotplugin
{


   class host;


   class CLASS_DECL_BASE plugin :
      virtual public ::simple_ui::style,
      virtual public ::simple_ui::interaction,
      virtual public ::base::session
#ifndef METROWIN
      , virtual public ::small_ipc_channel
#endif
   {
   public:


      bool                          m_bOnPaint;
      bool                          m_bInitialized;
      FILE *                        m_pfile;
      bool                          m_bPreCheck;
      int32_t                       m_iHealingSurface;
      uint32_t                      m_last_redraw;
      int32_t                       m_iEdge;
      bool                          m_bAppStarted;
      bool *                        m_pbReady;
      bool                          m_bApp;
      host *                        m_phost;
      bool                          m_bOk;
      bool                          m_bStream;

      void *                        m_pbitmap;
      void *                        m_pgraphics;
      COLORREF *                    m_pcolorref;
      SIZE                          m_sizeBitmap;

      string                        m_strStatus;
      string                        m_strStatus2;

      uint32_t                      m_nCa2StarterStartThreadID;
      bool                          m_bReload;
      bool                          m_bInstalling;
      const char *                  m_pszReloadCommandLine;

#ifdef WINDOWS
      HANDLE                        m_hfileBitmap;
      HANDLE                        m_hfilemapBitmap;
#else
      int32_t                       m_hfileBitmap;
#endif
      mutex *                       m_pmutexBitmap;
      SIZE                          m_sizeBitmapData;
      string                        m_strBitmapChannel;
      POINT                         m_ptCursorPhase;


      plugin(sp(::aura::application) papp);
      virtual ~plugin();


      // host should implement
      virtual bool         open_link(const string & strLink,const string & pszTarget);
      virtual bool         reload_plugin();


      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual string     get_host_location_url();


      virtual void         redraw();
      virtual void         post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual oswindow         get_host_window();

      using ::simple_ui::interaction::ClientToScreen;
      virtual void ClientToScreen(POINT * ppt);

      using ::simple_ui::interaction::ScreenToClient;
      virtual void ScreenToClient(POINT * ppt);

      // client should implement
      //using ::simple_ui::interaction::SetWindowPos;
      //virtual bool SetWindowPos(int32_t z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW);

      using ::simple_ui::interaction::GetWindowRect;
      virtual void GetWindowRect(__rect64 * prect);

      using ::simple_ui::interaction::GetClientRect;
      virtual void GetClientRect(__rect64 * lprect);



      virtual void translate_mouse_message(int * px, int * py);

      //virtual bool ShowWindow(int nCmdShow);
      //virtual bool destroy_window();
      //
      // call host memory
      virtual void   set_memory(void * puchMemory, ::count c);
      virtual void   append_memory(void * puchMemory, ::count c);
      virtual ::count get_memory_length();
      virtual ::count read_memory(void * puchMemory, ::count c);
      virtual void   free_memory();
      //static  void   free_memory(byte ** ppuchMemory);


      virtual bool is_ok();
      virtual void set_ready();
      virtual void on_ready();

      virtual bool plugin_initialize();
      virtual bool plugin_finalize();

      virtual void start_plugin();

      virtual int32_t  start_ca2_system();

      virtual void on_paint(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual void deferred_prodevian_redraw();

      virtual void plugin_system_redraw();

      
#if !defined(WINDOWS) && !defined(APPLEOS)
      using ::user::interaction::message_handler;
      virtual int32_t message_handler(XEvent * pevent);
#endif
      virtual void message_handler(signal_details * pobj);


      virtual void on_bare_paint(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual void on_bare_paint_full_screen(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual void on_bare_paint_discreet(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual void start_ca2();

      virtual void set_progress_rate(double dRate);

      virtual double get_progress_rate();

      virtual void on_update_progress();

      virtual void on_paint_progress(::draw2d::graphics * pgraphics,const RECT & lprect);

      virtual double extract_spa_progress_rate();

      virtual void set_ca2_installation_ready(bool bReady = true);

      virtual void set_status(const char * pszStatus);

      virtual void restart_small_ipc_channel();

      virtual void ensure_bitmap_data(int32_t cx, int32_t cy, bool bCreateFile);

      virtual bool set_host(::hotplugin::host * phost);

      virtual void get_progress_color(BYTE & uchR, BYTE & uchG, BYTE & uchB, double dRate, int32_t iProfile);

      virtual void on_host_timer();
      
   };


} // namespace hotplugin



