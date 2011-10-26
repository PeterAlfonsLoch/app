#pragma once


namespace hotplugin
{


   class host;


   class CLASS_DECL_____ plugin
   {
   public:

      vsstring                      m_strPluginUrl;
      vsstring                      m_strPluginHeaders;
      small_ipc_rx_channel          m_rxchannel;
      BYTE *                        m_lpbMemory;
      int                           m_iMemory;
      bool                          m_bOnPaint;
      RECT                          m_rect;
      bool                          m_bInitialized;
      FILE *                        m_pfile;
      bool                          m_bPreCheck;
      int                           m_iHealingSurface;
      DWORD                         m_last_redraw;
      int                           m_iEdge;
      bool                          m_bAppStarted;
      HANDLE                        m_hEventReady;
      bool                          m_bApp;
      host *                        m_phost;
      bool                          m_bOk;
      HBITMAP                       m_hbitmap;
      DWORD *                       m_pcolorref;
      BITMAPINFO                    m_info;
      SIZE                          m_sizeBitmap;


      plugin();
      virtual ~plugin();


      // host should implement
      virtual bool         open_url(const char * psz);


      // Host location is not the updated url - if there is a way to update the url and
      // maintain the same plugin instance, what would lead to an out-of-date location url.
      // It is the location url of the page that hosts the plugin when the plugin was created.
      virtual vsstring     get_host_location_url();


      virtual void         redraw();
      virtual void         post_message(UINT uiMessage, WPARAM wparam, LPARAM lparam);
      virtual HWND         get_host_window();
      virtual void         get_window_rect(LPRECT lprect);


      // client should implement
      virtual void   set_window_rect(LPCRECT lpcrect);


      // call host memory
      virtual void   set_memory(void * puchMemory, count c);
      virtual void   append_memory(void * puchMemory, count c);
      virtual count  get_memory_length();
      virtual int    read_memory(void * puchMemory, count c);
      virtual void   free_memory();
      static  void   free_memory(byte ** ppuchMemory);


      virtual bool is_ok();
      virtual void set_ready();
      virtual void on_ready();

      virtual bool initialize();
      virtual bool finalize();

      virtual void start_plugin();

      virtual int  start_ca2_system();

      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void deferred_prodevian_redraw();

      virtual void plugin_system_redraw();

#ifdef WINDOWS
      virtual UINT_PTR message_handler(UINT_PTR uiMessage, WPARAM wparam, LPARAM lparam);
#else
      virtual int message_handler(XEvent * pevent);
#endif

      virtual void on_bare_paint(HDC hdc, LPCRECT lprect);

      virtual void start_ca2();

      virtual void set_progress_rate(double dRate);

      virtual double get_progress_rate();

      virtual void on_paint_progress(HDC hdc, LPCRECT lprect);

      virtual void set_ca2_installation_ready(bool bReady = true);

   };


} // namespace hotplugin
