#pragma once



class CLASS_DECL_BASE ptra:
   virtual public spa(element)
{
public:


};


typedef ::map < sp(element),sp(element),sp(element),sp(element) > element_map;
typedef ::map < sp(element),sp(element),ptra,ptra > map_many;


namespace base
{


   class CLASS_DECL_BASE system:
      virtual public ::base::application
   {
   public:

#if defined METROWIN && defined(__cplusplus_winrt)

      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;
         ::core::system_window ^                      m_pwindow;


      };

#elif defined(APPLE_IOS)
      class os_data
      {
      public:

         sp(::user::interaction)                      m_pui;


      };

#else

      class os_data;

#endif

      ::sockets::SSLInitializer *                    m_psslinit;

      ::user::interaction *                      m_psimpleui;
      os_data *                                    m_posdata;


      stridsp(type)                                m_typemap;
      spa(service_base)                            m_serviceptra;
      sp(base_factory)                             m_pfactory;
      ::url::departament                           m_urldepartament;
      sp(class ::xml::departament)                 m_pxml;
      const id_pool                                m_cidpool;
      sp(class ::base::log)                        m_plog;
      sp(math::math)                               m_pmath;
      sp(geometry::geometry)                       m_pgeometry;


      ::exception::engine *                        m_peengine;


      static id_space *                            s_pidspace;
      static class id                              idEmpty;
      class ::str::base64                          m_base64;

      ::file::system_sp                            m_spfile;
      ::file::dir::system_sp                       m_spdir;
      sp(::sockets::net)                           m_spnet;
      ::net::port_forward_sp                       m_spportforward;
      ::http::system                               m_httpsystem;
      ::string_to_string                           m_mapAppLibrary;
      class machine_event_central *                m_pmachineeventcentral;
      class ::fontopus::user_set                   m_userset;
      ::crypto::crypto_sp                          m_spcrypto;
      sp(class ::datetime::departament)            m_pdatetime;
      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      sp(::user::window_draw)                      m_ptwf;
      class ::base::compress                       m_compress;
      sp(::user::str)                              m_puserstr;
      sp(::install::install)                       m_spinstall;
      ::base::os_sp                                m_spos;
      spa(::base::session)                         m_basesessionptra;

      sp(mutex)                                    m_spmutexUserAppData;
      sp(mutex)                                    m_spmutexSystemAppData;


#ifdef WINDOWS
      ID2D1DeviceContext *                         m_pdevicecontext;
      sp(mutex)                                    m_pmutexDc;
#endif

      sp(mutex)                                    m_spmutexFactory;

      ::base::library                              m_libraryDraw2d;


      bool                                         m_bMatterFromHttpCache;
      bool                                         m_bSystemSynchronizedCursor;
      bool                                         m_bSystemSynchronizedScreen;
      bool                                         m_bGudoNetCache;

      string                                       m_strCa2ModulePath;
      string                                       m_strCa2ModuleFolder;
      string                                       m_strModulePath;
      string                                       m_strModuleFolder;

      string                                       m_strCmdLine;
      int32_t                                      m_nCmdShow;
      size_t                                       m_nSafetyPoolSize;      // ideal size
      ::html::html *                               m_phtml; // only defined  in core;


#ifdef WINDOWSEX

      class interaction_impl:
         virtual public ::user::interaction
      {
      public:

         interaction_impl(sp(::base::application) papp);

         void install_message_handling(::message::dispatch * pdispath);

         DECL_GEN_SIGNAL(_001MessageHub);


      };

      sp(interaction_impl)                                   m_spwindow;

      raw_array < MONITORINFO >                    m_monitorinfoa;
      raw_array < HMONITOR >                       m_hmonitora;
      raw_array < MONITORINFO >                    m_monitorinfoaDesk;



#endif


      system(sp(::base::application) papp);
      virtual ~system();






      virtual void construct();

      virtual bool initialize_instance();

      virtual int32_t exit_instance();
      virtual bool finalize();

      spa(::base::session)                         & basesessionptra();
      application_ptra                                get_appptra();



      class ::base::os                             & os();
      class base_factory                           & factory();
      inline ::url::departament                    & url()     { return m_urldepartament; }
      ::xml::departament                           & xml();
      class ::str::base64                          & base64();

      class ::base::log                            & log();

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



//      application_ptra           get_appptra();



      math::math & math() { return *m_pmath; }







      using ::base::application::alloc;
      virtual sp(element) alloc(sp(::base::application) papp,sp(type) info);
      virtual sp(element) alloc(sp(::base::application) papp,const class id & idType);

      virtual sp(element) on_alloc(sp(::base::application) papp,sp(type) info);
      virtual sp(element) clone();
      virtual sp(element) clone(sp(element) pobj);
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


      virtual void on_allocation_error(sp(::base::application) papp,sp(type) info);
      //   sp(element) alloc(sp(::base::application) papp, sp(type) info);
      sp(element) alloc(sp(::base::application) papp,const std_type_info & info);
      //   virtual sp(element) on_alloc(sp(::base::application) papp, sp(type) info);


      static inline class id id(const ::std_type_info & info);
      static inline class id id(const char * psz);
      static inline class id id(const string & str);
      static inline class id id(int64_t i);
      static inline class id_space & id();
      inline class id id(const var & var);
      inline class id id(const property & prop);


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

      virtual sp(::user::object) place_hold(sp(::user::interaction) pui);

      virtual sp(::base::session) query_session(index iEdge);

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



template < size_t _Bits >
inline ::file::output_stream & operator << (::file::output_stream & _Ostr,const bitset<_Bits>& _Right)
{
   // insert bitset as a string
   return (_Ostr << _Right.template to_string());
}

// TEMPLATE operator>>
template < size_t _Bits >
inline ::file::input_stream & operator >>(::file::input_stream &  _Istr,bitset<_Bits>& _Right)
{
   // extract bitset as a string
   string _Str;

   _Istr >> _Str;

   _Right = bitset<_Bits>(_Str);	// convert string and store

   return (_Istr);

}




void CLASS_DECL_BASE __start_system(::base::system * psystem);




