#pragma once



#define session_parent session( )



namespace ace
{


   class CLASS_DECL_AURA session:
      virtual public ::ace::application
   {
   public:


      class CLASS_DECL_AURA map:
         virtual public ::map < index,index, ::ace::session * , ::ace::session * >
      {


      };


      index                                                    m_iEdge;


      bool                                                     m_bMatterFromHttpCache;



      string_map < ::ace::application * >                     m_mapApplication;



      application_ptra                                         m_appptra;
      sp(::ace::savings)                                      m_psavings;
      ::sockets::sockets *                                     m_psockets;


 

      ::ace::application *                              m_pappCurrent;

      var                                                m_varTopicFile;
      var                                                m_varCurrentViewFile;
      bool                                               m_bShowPlatform;

      sp(::ace::str_context)                            m_puserstrcontext;





      session(::ace::application * papp);
      virtual ~session_parent;


      application_ptra & appptra();


      virtual ::sockets::sockets & sockets() { return *m_psockets;  }; // only usable from base.dll and dependants

      ::ace::str_context *                        str_context() { return m_puserstrcontext; }


      virtual bool is_session();

      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }
      virtual void construct(::ace::application * papp, int iPhase);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

      virtual bool initialize_instance();

      virtual bool initialize();

      virtual bool finalize();

      virtual int32_t exit_instance();

      virtual ::visual::cursor * get_cursor();

      virtual ::visual::cursor * get_default_cursor();

      //virtual sp(::ace::application) start_application(const char * pszType,const char * pszAppId,sp(::create) pcreatecontext);


      virtual void request_create(sp(::create) pcreatecontext);
      virtual bool open_by_file_extension(const char * pszPathName,application_bias * pbiasCreate = NULL);
      virtual bool open_by_file_extension(::create * pcc);

      ::ace::application * get_new_app(::ace::application * pappNewApplicationParent,const char * pszType,const char * pszAppId);

      inline ::ace::savings &                  savings()      { return *m_psavings; }



      using ::ace::application::start_application;
      virtual sp(::ace::application) start_application(const char * pszType,const char * pszAppId,sp(::create) pcreatecontext);

      
      virtual COLORREF get_default_color(uint64_t ui);


      //virtual index initial_frame_position(LPRECT lprect,const RECT & rect, bool bMove);

      virtual bool  get_window_minimum_size(LPSIZE lpsize);


      virtual void frame_pre_translate_message(signal_details * pobj);


      

      virtual bool is_licensed(const char * pszId,bool bInteractive = true);


      virtual void on_request(sp(::create) pcreatecontext);

      ::ace::application * application_get(const char * pszType,const char * pszId,bool bCreate,bool bSynch,application_bias * pbiasCreate);

   };


} // namespace ace





































