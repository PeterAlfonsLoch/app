#pragma once



#define session_parent session( )


namespace aura
{


   class CLASS_DECL_AURA session:
      virtual public ::aura::application,
      virtual public ::aura::session_interface
   {
   public:

      


      bool                                                     m_bMatterFromHttpCache;



      string_map < sp(::aura::application) >                   m_mapApplication;



      application_ptra                                         m_appptra;
      sp(::aura::savings)                                      m_psavings;
 





      session(sp(::aura::application) papp);
      virtual ~session_parent;


      application_ptra & appptra();

      virtual bool is_session();


      void construct(sp(::aura::application) papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();


      inline ::aura::savings &                  savings()      { return *m_psavings; }

      virtual string get_locale();
      virtual string get_schema();
      virtual string get_locale_schema_dir(const string & strLocale,const string & strSchema);
      virtual string get_locale_schema_dir(const string & strLocale);
      virtual string get_locale_schema_dir();

      virtual void set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void set_schema(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_schema(const string & lpcsz,::action::context actioncontext);


      virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::str::international::locale_schema & localeschema,const char * pszLocale,const char * pszSchema);

      virtual sp(::aura::application) start_application(const char * pszType,const char * pszAppId,sp(::create_context) pcreatecontext);

      
      virtual COLORREF get_default_color(uint64_t ui);


      //virtual index initial_frame_position(LPRECT lprect,const RECT & rect, bool bMove);

      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      virtual void frame_pre_translate_message(signal_details * pobj);


      virtual ::user::interaction * get_active_guie();
      virtual ::user::interaction * get_focus_guie();


      virtual bool is_licensed(const char * pszId,bool bInteractive = true);


   };


} // namespace aura





































