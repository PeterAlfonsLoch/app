#pragma once



//class CLASS_DECL_BASE ptra:
//   virtual public spa(element)
//{
//public:
//
//
//};
//
//
//typedef ::map < sp(element),sp(element),sp(element),sp(element) > element_map;
//typedef ::map < sp(element),sp(element),ptra,ptra > map_many;
//

namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::axis::system,
      virtual public ::base::application
   {
   public:

#ifdef BSD_STYLE_SOCKETS

      ::sockets::SSLInitializer *                    m_psslinit;

#endif

      ::url::departament                           m_urldepartament;


      ::file::system_sp                            m_spfile;
      ::file::dir::system_sp                       m_spdir;
      sp(::sockets::net)                           m_spnet;
      ::net::port_forward_sp                       m_spportforward;
      ::http::system                               m_httpsystem;


      class ::fontopus::user_set                   m_userset;
      ::crypto::crypto_sp                          m_spcrypto;
      sp(class ::datetime::departament)            m_pdatetime;
      class ::base::compress                       m_compress;
      sp(::user::str)                              m_puserstr;
      sp(::install::install)                       m_spinstall;






      system(sp(::axis::application) papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      spa(::base::session)                         & basesessionptra();
      application_ptra                                get_appptra();

      class base_factory                           & factory();
      inline ::url::departament                    & url()     { return m_urldepartament; }
      ::xml::departament                           & xml();
      class ::str::base64                          & base64();

      class ::axis::log                            & log();

      inline class ::http::system                  & http()    { return m_httpsystem; }
      inline ::file::system                        & file()    { return *m_spfile; }
      inline ::file::dir::system                   & dir()     { return *m_spdir; }
      class ::sockets::net                         & net();
      class ::base::compress                       & compress();
      class ::machine_event_central                & machine_event_central();
      ::fontopus::user_set                         & userset();

      class ::crypto::crypto                       & crypto();
      ::datetime::departament                      & datetime();
      ::user::str                                  & str();
      ::install::install                           & install() { return *m_spinstall; }

      geometry::geometry                           & geometry() { return *m_pgeometry; }
      ::colorertake5::ParserFactory                & parser_factory();




//      application_ptra           get_appptra();



      math::math & math() { return *m_pmath; }







      using ::axis::application::alloc;
      virtual sp(element) alloc(sp(::axis::application) papp,sp(type) info);
      virtual sp(element) alloc(sp(::axis::application) papp,const class id & idType);

      virtual sp(element) on_alloc(sp(::axis::application) papp,sp(type) info);
      virtual sp(element) clone();
      template < class T >
      sp(T) clone(sp(T) p)
      {
         return System.factory().clone(p);
      }
      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast <T *> (clone(dynamic_cast <sp(element)> (pt)));
      }

      template < class T >
      sp(type) type_info()
      {
         return get_type_info(typeid(T));
      }

      virtual sp(::type) get_type_info(const ::std_type_info & info);
      sp(::type) get_type_info(const class id & idType)
      {

         synch_lock sl(m_spmutexFactory);

         return m_typemap[idType];

      }


      virtual void discard_to_factory(sp(element) pca);


      ::exception::engine & eengine();


      virtual UINT os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual bool process_initialize();

      virtual bool initialize2();

      virtual void wait_twf();

      virtual bool is_system();

      sp(::user::window_draw)               get_twf();


      virtual void on_allocation_error(sp(::axis::application) papp,sp(type) info);
      //   sp(element) alloc(sp(::axis::application) papp, sp(type) info);
      sp(element) alloc(sp(::axis::application) papp,const std_type_info & info);
      //   virtual sp(element) on_alloc(sp(::axis::application) papp, sp(type) info);


      static inline class id id(const ::std_type_info & info);
      static inline class id id(const char * psz);
      static inline class id id(const string & str);
      static inline class id id(int64_t i);
      static inline class id_space & id();
      inline class id id(const var & var);
      inline class id id(const property & prop);


      virtual int32_t _001OnDebugReport(int32_t i1,const char * psz1,int32_t i2,const char * psz2,const char * psz3,va_list args);
      virtual int32_t _debug_logging_report(int32_t iReportType, const char * pszFilename, int32_t iLinenumber, const char * iModuleName, const char * pszFormat, va_list list);
      virtual bool assert_failed_line(const char * lpszFileName,int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName,int32_t iLine);





      void set_enum_name(sp(type) etype,int32_t i,const char * psz)
      {
         m_mapEnumToName[etype->name()][i] = psz;
         m_mapNameToEnum[etype->name()][psz] = i;
      }
      string get_enum_name(sp(type) info,int32_t i)
      {
         return m_mapEnumToName[info->name()].get(i,"");
      }

      template < class E,E edefault>
      void from_name(base_enum < E,edefault > & b,const char * psz,E iDefault = edefault)
      {
         b = enum_from_name(System.type_info < E >(),psz,iDefault);
      }

      template < class E,E edefault>
      string get_name(const base_enum < E,edefault > & b)
      {
         return get_enum_name(System.type_info < E >(),(int32_t)(E)b);
      }

      template < class ENUM >
      ENUM enum_from_name(sp(type) info,const char * psz,int32_t iDefault = 0)
      {
         return (ENUM)m_mapNameToEnum[info->name()].get(psz,iDefault);
      }
      int32_t enum_from_name(sp(type) info,const char * psz,int32_t iDefault = 0)
      {
         return m_mapNameToEnum[info->name()].get(psz,iDefault);
      }
      int32_t enum_from_name(const std_type_info & info,const char * psz,int32_t iDefault = 0)
      {
#ifdef WINDOWS
         return m_mapNameToEnum[info.name()].get(psz,iDefault);
#else
         return m_mapNameToEnum[info.name()].get(psz, iDefault);
#endif
      }

      template < class TYPE >
      void set_enum_name(sp(type) etype,TYPE e,const char * psz)
      {
         set_enum_name(etype,(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(sp(type) etype,TYPE e)
      {
         return get_enum_name(etype,(int32_t)e);
      }

      template < class TYPE >
      void set_enum_name(const std_type_info & info,TYPE e,const char * psz)
      {
         set_enum_name(get_type_info(info),(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(const std_type_info & info,TYPE e)
      {
         return get_enum_name(get_type_info(info),(int32_t)e);
      }

      template < class TYPE >
      void set_enum_name(TYPE e,const char * psz)
      {
         set_enum_name(System.type_info < TYPE >(),(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(TYPE e)
      {
         return get_enum_name(System.type_info < TYPE >(),(int32_t)e);
      }

      virtual sp(::user::document) place_hold(sp(::user::interaction) pui);

      virtual sp(::axis::session) query_session(index iEdge);

      virtual bool initialize_log(const char * pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale,::action::context actioncontext);
      virtual void appa_set_schema(const char * pszStyle,::action::context actioncontext);

      virtual bool assert_running_global(const char * pszAppName,const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName,const char * pszId = NULL);


      virtual bool initialize_twf();


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

      virtual index get_ui_wkspace(::user::interaction * pui);
      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace,LPRECT lprect);
      virtual ::count get_desk_wkspace_count();
      virtual bool  get_desk_wkspace_rect(index iWkspace,LPRECT lprect);

      virtual sp(::user::interaction) get_active_guie();
      virtual sp(::user::interaction) get_focus_guie();


      virtual ::count get_application_count();


      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();



   };


} // namespace base







void CLASS_DECL_BASE __start_system(::base::system * psystem);




