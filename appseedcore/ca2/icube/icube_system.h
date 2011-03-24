#pragma once

namespace ca
{
   typedef comparable_array < ::ca::ca * > ptra;
   typedef ::collection::map < ::ca::ca *, ::ca::ca *, ::ca::ca *, ::ca::ca * > map;
   typedef ::collection::map < ::ca::ca *, ::ca::ca *, ptra, ptra > map_many;
}


namespace icube
{
   

   class CLASS_DECL_ca system : 
      virtual public ::icube::application,
      virtual public ::gen::system,
      virtual public debug_reporter
   {
   public:

      class CLASS_DECL_ca heap_item
      {
      public:


         byte *      m_pbStart;
         byte *      m_pbEnd;


         inline heap_item()
         {
            m_pbStart = NULL;
            m_pbEnd = NULL;
         }


         inline heap_item(void * p, int iSize)
         {
            m_pbStart = (byte *) p;
            m_pbEnd = ((byte *) p) + (iSize - 1);
         }


         inline bool contains(void * p)
         {
            return (((byte *)p) >= m_pbStart) && (((byte *)p) <= m_pbEnd);
         }


      };

      class CLASS_DECL_ca heap_item_array :
         virtual public raw_array < heap_item, heap_item >
      {
      public:

         mutex m_mutex;

         inline void add_item(void * p, int iSize)
         {
            CSingleLock sl(&m_mutex, TRUE);
            add(heap_item(p, iSize));
         }

         index find(void * p)
         {
            CSingleLock sl(&m_mutex, TRUE);
            for(index i = 0; i < get_count(); i++)
            {
               if(element_at(i).contains(p))
                  return i;
            }
            return -1;
         }
      
         void set_heap_alloc(::ca::ca * pca)
         {
            CSingleLock sl(&m_mutex, TRUE);
            index i = find(pca);
            if(i >= 0)
            {
               remove_at(i);
               pca->m_ulFlags |= ::ca::ca::flag_heap_alloc;
            }
         }
      };

      mutex                            m_mutexDelete;               
      ::ca::map_many                   m_mapmanyDelete;
      ::ca::map_many                   m_mapmanyDeleteReverse;

      ::ca::application_ptra           m_appptra;
      class ::ca2::file::system        m_file;
      ::ca::dir::system_sp             m_spdir;
      class ::ca2::stra                m_stra;
      class ::ca2::url                 m_url;
      class ::ca2::html                m_html;
      class ::ca2::xml                 m_xml;
      class ::ca2::service             m_service;
      class ::ca2::install             m_install;
      ::ca::osi_sp                     m_sposi;
      class ::ca2::process             m_process;
      class ::ca2::datetime *          m_pdatetime;
      class ::ca2::net                 m_net;

      class ::ca4::compress            m_compress;
      class ::ca4::patch               m_patch;
      class ::ca4::crypt               m_crypt;
      class ::ca4::http::system        m_http;
      class ::ca4::email               m_email;
      class ::ca4::file                m_file4;
      class ::copydesk *               m_pcopydesk;
      class ::fontopus::license *      m_plicense;
      class ::fs::data *               m_pfsdata;


      class ::fontopus::user_set       m_userset;


      class ::ca2::log *               m_plog;
      class factory *                  m_pfactory;
      class ::ca::history *            m_phistory;
      class ::ca::window_draw *        m_ptwf; 

      bergedge::bergedge::run_start_installer *  m_prunstartinstaller;


      bergedge::bergedge::map *          m_pbergedgemap;

      index                            m_iNewEdge;

      class machine_event_central *    m_pmachineeventcentral;

      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                             m_bInitApplication;
      BOOL                             m_bInitApplicationResult;
      bool                             m_bProcessInitialize;
      bool                             m_bProcessInitializeResult;
      

     ::collection::map < string, string, ::collection::map < int, int, string, string >, ::collection::map < int, int, string, string > > m_mapEnumToName;
     ::collection::map < string, string, ::collection::map < string, string, int, int >, ::collection::map < string, string, int, int > > m_mapNameToEnum;


      system();
      virtual ~system();


      //virtual int main();
      virtual BOOL InitApplication();

      virtual bool process_initialize();

      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize3();

      virtual bool initialize_instance();

      virtual bool bergedge_start();
      virtual bool os_native_bergedge_start();

      virtual bool finalize();
      virtual int exit_instance();

      virtual index get_new_bergedge();

      virtual void register_bergedge_application(::ca::application * papp);
      virtual void unregister_bergedge_application(::ca::application * papp);

      using ::icube::application::alloc;
      virtual ::ca::ca * alloc(::ca::application * papp, const ::ca::type_info & info);

      virtual ::ca::ca * on_alloc(::ca::application * papp, const ::ca::type_info & info);
      virtual ::ca::ca * clone();
      virtual ::ca::ca * clone(::ca::ca * pobj);
      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast < T * > (clone(dynamic_cast < ::ca::ca * > (pt)));
      }

      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale, bool bUser);
      virtual void appa_set_style(const char * pszStyle, bool bUser);

      virtual bool assert_running_global(const char * pszAppName, const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName, const char * pszId = NULL);

      virtual bool initialize_log(const char * pszId);

      virtual int _001OnDebugReport(int i1, const char * psz1, int i2, const char * psz2, const char * psz3, va_list args);

      virtual int ________ca2_votagus_logging_Report(
                                                      int _ReportType, 
                                                      const char * _Filename, 
                                                      int _Linenumber, 
                                                      const char * _ModuleName,
                                                      const char * _Format, 
                                                      va_list list);

      virtual bool assert_failed_line(const char * lpszFileName, int iLine);

      virtual void on_allocation_error(::ca::application * papp, const ::ca::type_info & info);

      // file & dir
      virtual string matter_as_string(::ca::application * papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual string dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(::ca::application * papp, const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);

      virtual ::ca::window_draw        * _001GetTwf();

      class factory                    & factory();
      class ::ca2::log                 & log();

      ::ca::window_draw                * get_twf();

      ::ca::application_ptra           & appptra();
      ::ca2::datetime                  & datetime();

      ::ca2::file::system              & file();
      ::ca::dir::system                & dir();
      ::ca2::stra                      & stra();
      ::ca2::url                       & url();
      ::ca2::html                      & html();
      ::ca2::xml                       & xml();
      ::ca2::install                   & install();
      ::ca2::service                   & service();
      machine_event_central            & machine_event_central();
      ::ca::osi                        & osi();
      ::ca2::process                   & process();
      class ::ca2::net                 & net();

      ::ca::history                    & hist();

      class ::fs::data                 * fs();

      class ::ca4::compress            & compress();
      class ::ca4::patch               & patch();
      class ::ca4::crypt               & crypt();
      class ::ca4::http::system        & http();
      class ::ca4::email               & email();
      class ::ca4::file                & file36();
      class ::copydesk                 & copydesk();
      class ::fontopus::license        & license();

      ::fontopus::user_set             & userset();
      

      virtual void on_delete(::ca::ca * pca);


      virtual bool base_support();

      bool sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser = NULL, ::http::cookies * pcookies = NULL);

      DECL_GEN_SIGNAL(on_application_signal);


      virtual bool is_licensed(const char * pszId, bool bInteractive = true);




      virtual void http_config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);

      using ::icube::application::process;
      bool set_history(::ca::history * phistory);




      bergedge::bergedge *             get_bergedge(index iEdge, ::ca::application_bias * pbiasCreation = NULL);
      platform::document *             get_platform(index iEdge, ::ca::application_bias * pbiasCreation = NULL);
      nature::document *               get_nature(index iEdge, ::ca::application_bias * pbiasCreation = NULL);


      void request_application(index iEdge, const char * pszId, var varFile, var varQuery, ::ca::application_bias * pbiasCreate);
      void request_application(ca2::application_request * prequest);

      ::ca::application * application_get(index iEdge, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      void open_by_file_extension(index iEdge, const char * pszPathName);

      virtual void register_delete(::ca::ca * plistened, ::ca::ca * plistener);
      virtual void unregister_delete(::ca::ca * plistened, ::ca::ca * plistenerOld);

      virtual bool wait_twf(DWORD dwTimeOut = INFINITE);

      void set_enum_name(::ca::type_info etype, int i, const char * psz)
      {
         m_mapEnumToName[etype.raw_name()][i] = psz;
         m_mapNameToEnum[etype.raw_name()][psz] = i;
      }
      string get_enum_name(::ca::type_info info, int i)
      {
         return m_mapEnumToName[info.raw_name()].get(i, "");
      }

      template < class E , E edefault>
      void from_name(base_enum < E, edefault > & b, const char * psz, E iDefault = edefault)
      {
         b = enum_from_name(typeid(E), psz, iDefault);
      }
      
      template < class E , E edefault>
      string get_name(const base_enum < E, edefault > & b)
      {
         return get_enum_name(typeid(E), (int) (E) b);
      }


      int enum_from_name(::ca::type_info info, const char * psz, int iDefault = 0)
      {
         return m_mapNameToEnum[info.raw_name()].get(psz, iDefault);
      }
      int enum_from_name(const std_type_info & info, const char * psz, int iDefault = 0)
      {
         return m_mapNameToEnum[info.raw_name()].get(psz, iDefault);
      }

      template < class TYPE >
      void set_enum_name(::ca::type_info etype, TYPE e, const char * psz)
      {
         set_enum_name(etype, (int) e, psz);
      }
      template < class TYPE >
      string get_enum_name(::ca::type_info etype, TYPE e)
      {
         return get_enum_name(etype, (int) e);
      }

      template < class TYPE >
      void set_enum_name(const std_type_info & info, TYPE e, const char * psz)
      {
         set_enum_name(::ca::type_info(info), (int) e, psz);
      }
      template < class TYPE >
      string get_enum_name(const std_type_info & info, TYPE e)
      {
         return get_enum_name(::ca::type_info(info), (int) e);
      }

      template < class TYPE >
      void set_enum_name(TYPE e, const char * psz)
      {
         set_enum_name(typeid(TYPE), (int) e, psz);
      }
      template < class TYPE >
      string get_enum_name(TYPE e)
      {
         return get_enum_name(typeid(TYPE), (int) e);
      }

      virtual bool create_twf();



   
   };


   CLASS_DECL_ca class system::heap_item_array * get_heap_itema();

   CLASS_DECL_ca void set_heap_itema(class system::heap_item_array * pitema);


} // namespace icube

