#pragma once


namespace hotplugin
{


   class host;


   class CLASS_DECL_c plugin 
#ifndef METROWIN
      : virtual public ::small_ipc_channel
#endif
   {
   public:

      enum e_schema
      {

         schema_normal,
         schema_darker,

      };

      vsstring                      m_strPluginUrl;
      vsstring                      m_strPluginHeaders;
      BYTE *                        m_lpbMemory;
      int32_t                           m_iMemory;
      bool                          m_bOnPaint;
      RECT                          m_rect;
      bool                          m_bInitialized;
      FILE *                        m_pfile;
      bool                          m_bPreCheck;
      int32_t                           m_iHealingSurface;
      DWORD                         m_last_redraw;
      int32_t                           m_iEdge;
      bool                          m_bAppStarted;
      bool *                        m_pbReady;
      bool                          m_bApp;
      host *                        m_phost;
      bool                          m_bOk;
      bool                          m_bStream;

      void *                        m_pbitmap;
      void *                        m_pgraphics;
      DWORD *                       m_pcolorref;
      SIZE                          m_sizeBitmap;

      vsstring                      m_strStatus;

      DWORD                         m_nCa2StarterStartThreadID;
      bool                          m_bReload;
      bool                          m_bInstalling;
      const char *                  m_pszReloadCommandLine;

#ifdef WINDOWS
      HANDLE                        m_hfileBitmap;
      HANDLE                        m_hfilemapBitmap;
#else
      int32_t                           m_hfileBitmap;
#endif
      simple_mutex *                m_pmutexBitmap;
      SIZE                          m_sizeBitmapData;
      vsstring                      m_strBitmapChannel;
      POINT                         m_ptCursorPhase;

      e_schema                      m_eschema;
      vsstring                      m_strLocale;
      vsstring                      m_strSchema;
      vsstring                      m_strRuri;


      plugin();
      virtual ~plugin();


      // host should implement
      virtual bool         open_url(const char * psz);
      virtual bool         reload_plugin();


      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual vsstring     get_host_location_url();


      virtual void         redraw();
      virtual void         post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual oswindow         get_host_window();
      virtual void         get_window_rect(LPRECT lprect);


      // client should implement
      virtual void   set_window_rect(LPCRECT lpcrect);


      // call host memory
      virtual void   set_memory(void * puchMemory, count c);
      virtual void   append_memory(void * puchMemory, count c);
      virtual count  get_memory_length();
      virtual count  read_memory(void * puchMemory, count c);
      virtual void   free_memory();
      static  void   free_memory(byte ** ppuchMemory);


      virtual bool is_ok();
      virtual void set_ready();
      virtual void on_ready();

      virtual bool initialize();
      virtual bool finalize();

      virtual void start_plugin();

      virtual int32_t  start_ca2_system();

      virtual void on_paint(simple_graphics & gWindow, LPCRECT lprect);

      virtual void deferred_prodevian_redraw();

      virtual void plugin_system_redraw();

#ifdef WINDOWS
      virtual LRESULT message_handler(UINT uiMessage, WPARAM wparam, LPARAM lparam);
#else
      virtual int32_t message_handler(XEvent * pevent);
#endif

      virtual void on_bare_paint(simple_graphics & g, LPCRECT lprect);

      virtual void start_ca2();

      virtual void set_progress_rate(double dRate);

      virtual double get_progress_rate();

      virtual void on_paint_progress(simple_graphics & g, LPCRECT lprect);

      virtual void set_ca2_installation_ready(bool bReady = true);

      virtual void set_status(const char * pszStatus);

      virtual void restart_small_ipc_channel();

      virtual void ensure_bitmap_data(int32_t cx, int32_t cy, bool bCreateFile);

   };


} // namespace hotplugin
