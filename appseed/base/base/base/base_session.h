#pragma once


namespace base
{

   class CLASS_DECL_BASE session:
      virtual public ::base::application,
      virtual public ::base::session_interface
   {
   public:

      
      bool                                                     m_bMatterFromHttpCache;

      bool                                                     m_bSystemSynchronizedCursor;
      point                                                    m_ptCursor;
      bool                                                     m_bSystemSynchronizedScreen;
      rect_array                                               m_rectaScreen;
      index                                                    m_iMainMonitor;



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


      sp(::fontopus::fontopus)                                 m_pfontopus;
      application_ptra                                         m_appptra;
      sp(::user::interaction)                                  m_spuiFocus;




      session(sp(::base::application) papp);
      virtual ~session();

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }
      inline sp(::fontopus::fontopus)           fontopus()     { return m_pfontopus; }

      application_ptra & appptra();

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



      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual bool set_main_monitor(index iMonitor);
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

      
      virtual sp(::user::interaction) get_active_guie();
      virtual sp(::user::interaction) get_focus_guie();


   };


} // namespace base











