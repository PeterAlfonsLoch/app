#pragma once



class CLASS_DECL_AURA ptra:
   virtual public spa(object)
{
public:


};


typedef ::map < sp(object),sp(object),sp(object),sp(object) > element_map;
typedef ::map < sp(object),sp(object),ptra,ptra > map_many;


namespace aura
{


   class CLASS_DECL_AURA system:
      virtual public ::aura::application
   {
   public:

      sp(::aura::session::map)                     m_paurabergedgemap;

      sp(class ::datetime::departament)            m_pdatetime;

      stridsp(type)                                m_typemap;
      spa(service_base)                            m_serviceptra;
      sp(base_factory)                             m_pfactory;
      sp(class ::xml::departament)                 m_pxml;
      const id_pool                                m_cidpool;
      sp(class ::aura::log)                        m_plog;
      sp(math::math)                               m_pmath;
      sp(geometry::geometry)                       m_pgeometry;

      ::aura::str *                                m_puserstr;
      ::exception::engine *                        m_peengine;


      static class id                              idEmpty;
      class ::str::base64                          m_base64;

      ::string_to_string                           m_mapAppLibrary;
      class machine_event_central *                m_pmachineeventcentral;
      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      ::aura::os_sp                                m_spos;
      spa(::aura::session)                         m_basesessionptra;
      colorertake5::ParserFactory *                m_pparserfactory;

#ifdef WINDOWS
      float                                        m_dpi;
      ID2D1DeviceContext *                         m_pdevicecontext;
      mutex                                        m_mutexDc;
#elif defined(VSNORD)
      android_init_data *                          m_pandroidinitdata;
#endif

      void *                                       m_ftlibrary;



      sp(mutex)                                    m_spmutexUserAppData;
      sp(mutex)                                    m_spmutexSystemAppData;



      mutex                                        m_mutexFactory;


      bool                                         m_bMatterFromHttpCache;
      bool                                         m_bGudoNetCache;


      ::process::departament                       m_process;


      string                                       m_strCmdLine;
      int32_t                                      m_nCmdShow;
      size_t                                       m_nSafetyPoolSize;      // ideal size
//      ::html::html *                               m_phtml; // only defined  in core;


      bool                                         m_bDoNotExitIfNoApplications;

      bool (system::*                              m_pfnVerb)();

      bool                                         m_bAdvancedGUI;

      ::html::html *                               m_phtml; // only defined and set in html library/component
      ::url::departament *                         m_purldepartament;
      ::axis::compress *                           m_pcompress;

      ::file::system_sp                            m_spfile;
      ::file::dir::system_sp                       m_spdir;

      string                                       m_strInstallVersion;
      string                                       m_strInstallPlatform;

      DWORD                                        m_dwMainStartTime;
      DWORD                                        m_dwAfterApplicationFirstRequest;



      system(::aura::application * papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      application_ptra                                get_appptra();


      spa(::aura::session)                         &  basesessionptra();


      class ::aura::os                             &  os();
      class base_factory                           &  factory();
      ::exception::engine                          &  eengine();

      ::aura::str                                  & str();
      ::process::departament                       &  process();


      ::xml::departament                           &  xml();
      class ::str::base64                          &  base64();

      class ::aura::log                            &  log();

      class ::machine_event_central                &  machine_event_central();

      geometry::geometry                           &  geometry() { return *m_pgeometry; }
      math::math                                   &  math() { return *m_pmath; }
      ::colorertake5::ParserFactory                &  parser_factory();
      inline ::url::departament                    & url() { return *m_purldepartament; } // only usable from base.dll and dependants
      inline class ::axis::compress                & compress() { return *m_pcompress; } // only usable from base.dll and dependants

      inline ::file::system                        & file()    { return *m_spfile; }
      inline ::file::dir::system                   & dir()     { return *m_spdir; }

      ::datetime::departament                      & datetime();



      virtual void on_allocation_error(::aura::application * papp, ::type * ptype);
      //   sp(object) alloc(::aura::application * papp, sp(type) info);
      object * alloc(::aura::application * papp,const std_type_info & info);
      //   virtual sp(object) on_alloc(::aura::application * papp, sp(type) info);



      using ::aura::application::alloc;
      virtual object * alloc(::aura::application * papp,::type * ptype);
      virtual object * alloc(::aura::application * papp,const class id & idType);

      virtual object * on_alloc(::aura::application * papp,::type * ptype);
      virtual object * clone();


      //template < class T >
      //sp(T) clone(sp(T) p)
      //{

      //   return System.factory().clone(p);

      //}


      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast <T *> (::clone(dynamic_cast <sp(object)> (pt)));
      }

      template < class T >
      ::type * type_info()
      {
         return get_type_info(typeid(T));
      }

      virtual ::type * get_type_info(const ::std_type_info & info);

      ::type * get_type_info(const class id & idType)
      {

         if(idType.is_empty())
            return NULL;

         synch_lock sl(&m_mutexFactory);

         return m_typemap[idType].m_p;

      }


      virtual void discard_to_factory(sp(object) pca);





      virtual UINT os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual bool process_initialize();

      virtual bool initialize1();

      virtual bool initialize2();

//      virtual mutex * wait_twf();



      virtual bool verb();
      virtual bool common_verb();
      virtual bool install_uninstall_verb();



      virtual bool is_system();



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


//      virtual ::user::primitive * get_focus_guie();


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

      virtual sp(::aura::session) query_session(index iEdge);

      virtual bool initialize_log(const char * pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale,::action::context actioncontext);
      virtual void appa_set_schema(const char * pszStyle,::action::context actioncontext);

      virtual bool assert_running_global(const char * pszAppName,const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName,const char * pszId = NULL);



      virtual ::count get_application_count();


      //virtual ::file::path get_ca2_module_folder();
      //virtual ::file::path get_ca2_module_file_path();
      //virtual ::file::path get_module_folder();
      //virtual ::file::path get_module_file_path();
      //virtual ::file::path get_module_title();
      //virtual ::file::path get_module_name();


      virtual ::file::path dir_appmatter_locator(::aura::application * papp);

      virtual string crypto_md5_text(const string & str);


      virtual void * & ftlibrary();


      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache(bool bSave = true);
      virtual bool map_application_library(const char * pszLibrary);


      virtual void install_progress_add_up(int iAddUp = 1);

      virtual bool alloc_session();

      virtual ::aura::session * on_create_session();


      virtual sp(::aura::session)             get_session(index iEdge,application_bias * pbiasCreation = NULL);


      virtual void on_request(sp(::create) pcreate);


      virtual string install_get_version();
      virtual void install_set_version(const char * pszVersion);
      virtual ::file::path install_meta_dir(const char * pszVersion,const char * pszBuild,const char * pszType,const char * pszId,const char * pszLocale,const char * pszSchema);
      virtual string install_get_platform();
      virtual void install_set_platform(const char * pszPlatform);
      virtual bool install_is(const char * pszVersion,const char * pszBuild,const char * pszType,const char * pszId,const char * pszLocale,const char * pszSchema);
      virtual string install_get_latest_build_number(const char * pszVersion);
      virtual int32_t install_start(const char * pszCommandLine,const char * pszBuild);
      virtual int32_t install_progress_app_add_up(int iAddUp);

      virtual void on_start_find_applications_from_cache();
      virtual void on_end_find_applications_from_cache(::file::byte_istream & is);

      virtual void on_end_find_applications_to_cache(::file::byte_ostream & os);

      virtual void on_map_application_library(::aura::library & library);

      virtual bool set_main_init_data(::aura::main_init_data * pdata);

   };


} // namespace aura




