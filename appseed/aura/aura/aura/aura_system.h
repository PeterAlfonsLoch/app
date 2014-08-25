#pragma once



class CLASS_DECL_AURA ptra:
   virtual public spa(element)
{
public:


};


typedef ::map < sp(element),sp(element),sp(element),sp(element) > element_map;
typedef ::map < sp(element),sp(element),ptra,ptra > map_many;


namespace aura
{


   class CLASS_DECL_AURA system:
      virtual public ::aura::application
   {
   public:

      stridsp(type)                                m_typemap;
      spa(service_base)                            m_serviceptra;
      sp(base_factory)                             m_pfactory;
      sp(class ::xml::departament)                 m_pxml;
      const id_pool                                m_cidpool;
      sp(class ::aura::log)                        m_plog;
      sp(math::math)                               m_pmath;
      sp(geometry::geometry)                       m_pgeometry;


      ::exception::engine *                        m_peengine;


      static id_space *                            s_pidspace;
      static class id                              idEmpty;
      class ::str::base64                          m_base64;

      ::string_to_string                           m_mapAppLibrary;
      class machine_event_central *                m_pmachineeventcentral;
      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      ::aura::os_sp                                m_spos;
      spa(::aura::session)                         m_basesessionptra;
      sp(colorertake5::ParserFactory)              m_pparserfactory;


      sp(mutex)                                    m_spmutexUserAppData;
      sp(mutex)                                    m_spmutexSystemAppData;



      sp(mutex)                                    m_spmutexFactory;


      bool                                         m_bMatterFromHttpCache;
      bool                                         m_bGudoNetCache;

      string                                       m_strCa2ModulePath;
      string                                       m_strCa2ModuleFolder;
      string                                       m_strModulePath;
      string                                       m_strModuleFolder;

      class ::aura::process_departament            m_processsection;


      string                                       m_strCmdLine;
      int32_t                                      m_nCmdShow;
      size_t                                       m_nSafetyPoolSize;      // ideal size
      ::html::html *                               m_phtml; // only defined  in core;




      system(sp(::aura::application) papp);
      virtual ~system();






      virtual void construct(const char * pszAppId);

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      spa(::aura::session)                         & basesessionptra();
      application_ptra                                get_appptra();



      class ::aura::os                             & os();
      class base_factory                           & factory();
      ::xml::departament                           & xml();
      class ::str::base64                          & base64();

      class ::aura::log                            & log();

      class ::machine_event_central                & machine_event_central();

      geometry::geometry                           & geometry() { return *m_pgeometry; }
      ::colorertake5::ParserFactory                & parser_factory();




//      application_ptra           get_appptra();



      math::math & math() { return *m_pmath; }







      using ::aura::application::alloc;
      virtual sp(element) alloc(sp(::aura::application) papp,sp(type) info);
      virtual sp(element) alloc(sp(::aura::application) papp,const class id & idType);

      virtual sp(element) on_alloc(sp(::aura::application) papp,sp(type) info);
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

      ::aura::process_departament            & process();



      virtual UINT os_post_to_all_threads(UINT uiMessage,WPARAM wparam,lparam lparam);

      virtual bool process_initialize();

      virtual bool initialize2();

      virtual void wait_twf();

      virtual bool is_system();

      virtual void on_allocation_error(sp(::aura::application) papp,sp(type) info);
      //   sp(element) alloc(sp(::aura::application) papp, sp(type) info);
      sp(element) alloc(sp(::aura::application) papp,const std_type_info & info);
      //   virtual sp(element) on_alloc(sp(::aura::application) papp, sp(type) info);


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


      virtual ::user::interaction * get_focus_guie();


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


      virtual string get_ca2_module_folder();
      virtual string get_ca2_module_file_path();
      virtual string get_module_folder();
      virtual string get_module_file_path();
      virtual string get_module_title();
      virtual string get_module_name();


      virtual string dir_appmatter_locator(sp(::aura::application) papp);

   };


} // namespace aura




