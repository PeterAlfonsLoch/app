#pragma once


namespace userpresence
{


   class userpresence;


} // namespace userpresence


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session,
      virtual public ::axis::application
   {
   public:


      ::map < ::user::e_key,::user::e_key,bool,bool > *         m_pmapKeyPressed;





      ::user::elemental *                             m_pkeyboardfocus;
      ::user::keyboard *                              m_pkeyboard;



      ::userpresence::userpresence *                           m_puserpresence;
      sp(::ftpfs)                                              m_pftpfs;
      sp(::fs::remote_native)                                  m_prfs;
      sp(::fs::fs)                                             m_spfs;
      sp(class ::fs::data)                                     m_spfsdata;


      //::sockets::sockets *                                     m_psockets;
      bool                                                     m_bIfs;
      


      //::user::schema_simple_impl                               m_schemasimple;

      ::user::interaction *                                    m_puiMouseMoveCapture;
      ::user::interaction *                                    m_puiLastLButtonDown;

      bool                                                     m_bMatterFromHttpCache;

      bool                                                     m_bSystemSynchronizedCursor;
      point                                                    m_ptCursor;
      bool                                                     m_bSystemSynchronizedScreen;
      rect_array                                               m_rectaMonitor;
      rect_array                                               m_rectaWkspace;
      index                                                    m_iMainMonitor;
      index                                                    m_iMainWkspace;




      bool                                                     m_bDrawCursor;


      ::user::copydesk *                                       m_pcopydesk;






      session(::aura::application * papp);
      virtual ~session_parent;

      inline ::userpresence::userpresence & userpresence() { return *m_puserpresence; }

      //application_ptra & appptra();

      virtual bool is_session();


      void construct(::aura::application * papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_application() override;

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_application() override;


      inline sp(class ::fs::data)               fs()           { return m_spfsdata; }
      //inline ::sockets::sockets &               sockets()      { return *m_psockets; }


      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      //virtual void  get_cursor_pos(LPPOINT lppoint);


      virtual void on_request(::create * pcreate);
      

      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      //virtual string dir().matter(const char * pszMatter,const char * pszMatter2);

      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);


      virtual void defer_initialize_user_presence();


      virtual string fontopus_get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive, ::user::interactive * pinteractive = NULL) override;
      //virtual bool is_session();


      //void construct(::aura::application * papp,int iPhase);

      //virtual bool process_initialize();

      //virtual bool initialize1();

      /*virtual bool initialize2();*/

      //virtual bool initialize_application() override;

      //virtual bool initialize();

      //virtual bool finalize();

      /*virtual int32_t exit_instance();*/


      ::user::copydesk &                           copydesk();



      //virtual bool get_auth(const string & pszForm,string & strUsername,string & strPassword);


      virtual bool on_create_frame_window();



      virtual COLORREF get_default_color(uint64_t ui);






      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual bool set_main_monitor(index iMonitor);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor,LPRECT lprect);

      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual bool set_main_wkspace(index iWkspace);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace,LPRECT lprect);

      virtual bool wkspace_to_monitor(LPRECT lprect,index iMonitor,index iWkspace);
      virtual bool monitor_to_wkspace(LPRECT lprect,index iWkspace,index iMonitor);

      virtual bool wkspace_to_monitor(LPRECT lprect);
      virtual bool monitor_to_wkspace(LPRECT lprect);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor,LPRECT lprect);

      virtual void  get_monitor(rect_array & rectaMonitor,rect_array & rectaIntersect,const RECT & rect);

      virtual index get_zoneing(LPRECT lprect,const RECT & rect,::user::EAppearance eappearance);
      virtual index get_best_zoneing(::user::EAppearance * peappearance,LPRECT lprect,const RECT & rect);
      virtual index get_best_monitor(LPRECT lprect,const RECT & rect);
      virtual index get_best_wkspace(LPRECT lprect,const RECT & rect);
      virtual index get_good_iconify(LPRECT lprect,const RECT & rect);


//      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      virtual void  get_cursor_pos(LPPOINT lppoint);










      //virtual bool is_licensed(const char * pszId,bool bInteractive = true);

      //virtual void defer_initialize_user_presence();

      //virtual string get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive);

      //virtual void on_request(::create * pcreate);


      virtual void on_user_login(::fontopus::user * puser);

      ::user::keyboard & keyboard();

      virtual bool is_key_pressed(::user::e_key ekey);

      virtual void set_key_pressed(::user::e_key ekey,bool bPressed);

      virtual ::user::elemental * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::elemental * pkeyboardfocus);

      virtual ::user::primitive * get_active_ui();
      virtual ::user::primitive * get_focus_ui();

      virtual void on_finally_focus_set(::user::elemental * pelementalFocus);


      virtual string fontopus_get_user_sessid(const string & str) override;

   };


} // namespace axis








//inline ::axis::session & Sess(::aura::application * papp);




























