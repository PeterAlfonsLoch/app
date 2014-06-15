#pragma once


namespace base
{

   class CLASS_DECL_BASE session:
      virtual public ::base::application,
      virtual public ::base::session_interface
   {
   public:

      
      bool                                                     m_bMatterFromHttpCache;

      bool                                                     m_bSessionSynchronizedCursor;
      point                                                    m_ptCursor;
      rect                                                     m_rectScreen;
      bool                                                     m_bSessionSynchronizedScreen;


#ifdef WINDOWSEX
      raw_array < MONITORINFO >                                m_monitorinfoa;
      raw_array < HMONITOR >                                   m_hmonitora;
      raw_array < MONITORINFO >                                m_monitorinfoaDesk;
#endif


      ::plane::session *                                       m_pplanesession;
      string_map < sp(::base::application) >                   m_mapApplication;
      sp(::userpresence::userpresence)                         m_puserpresence;
      sp(::ifs)                                                m_pifs;
      sp(::fs::remote_native)                                  m_prfs;
      sp(::fs::fs)                                             m_spfs;
      sp(class ::fs::data)                                     m_spfsdata;

      bool                                                     m_bDrawCursor;


      ::visual::e_cursor                                       m_ecursor;
      ::visual::e_cursor                                       m_ecursorDefault;
      ::base::copydesk_sp                                      m_spcopydesk;


      sp(::fontopus::fontopus)                        m_pfontopus;


      session(sp(::base::application) papp);
      virtual ~session();

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }
      inline sp(::fontopus::fontopus)           fontopus()     { return m_pfontopus; }

      virtual bool is_session();

      virtual bool initialize_instance();

      virtual bool initialize1();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();


      ::base::copydesk & copydesk();
      inline sp(class ::fs::data)               fs()           { return m_spfsdata; }


      virtual sp(::base::application) start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext);

      
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);

      
      virtual COLORREF get_default_color(uint64_t ui);
      virtual ::fontopus::fontopus * create_fontopus();


      virtual ::fontopus::user * safe_get_user();


      virtual ::fontopus::user * get_user();
      virtual ::fontopus::user * create_current_user();


      virtual bool is_licensed(const char * pszId,bool bInteractive = true);


      virtual bool get_auth(const string & pszForm,string & strUsername,string & strPassword);


      void enum_display_monitors();

#if defined(WINDOWS)
      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor,LPARAM dwData);
      void monitor_enum(HMONITOR hmonitor,HDC hdcMonitor,LPRECT lprcMonitor);
#endif

      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index initial_frame_position(LPRECT lprect,LPCRECT lpcrect, bool bMove);

      virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, LPCRECT lpcrect);

      virtual index get_best_monitor(LPRECT lprect,LPCRECT lpcrect);
      virtual index get_good_restore(LPRECT lprect,LPCRECT lpcrect);
      virtual index get_good_iconify(LPRECT lprect,LPCRECT lpcrect);

      virtual index get_good_move(LPRECT lprect,LPCRECT lpcrect);

      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      virtual void  get_cursor_pos(LPPOINT lppoint);

   };


} // namespace base











