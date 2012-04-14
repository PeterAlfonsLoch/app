#pragma once


#ifndef WINDOWS
#define INFINITE 0xffffffff
#endif


class id;


namespace ca
{


   class CLASS_DECL_ca ptra :
      virtual public ::comparable_array < ::ca::ca * >
   {
   public:
   };

   typedef ::collection::map < ::ca::ca *, ::ca::ca *, ::ca::ca *, ::ca::ca * > map;
   typedef ::collection::map < ::ca::ca *, ::ca::ca *, ptra, ptra > map_many;


} // namespace ca


#undef __str
#define __str(x) (m_papp->m_psystem->m_cstrpool.str_##x)
#undef __id
#define __id(x) (m_papp->m_psystem->m_cstrpool.id_##x)



namespace plane
{


   class CLASS_DECL_ca str_pool
   {
   public:

      id id_cc;
      id id_se;


      id id_at;
      id id_de_at;
      id id_de;
      id id_de_de;

      id id_br;
      id id_pt_br;
      id id_pt;

      id id_es;

      id id_cn;
      id id_zh_cn;
      id id_zh_tw;
      id id_hk;

      id id_ja;
      id id_jp;

      id id_en;
      id id_std;

      id id_pe;
      id id_mx;
      id id_ec;

      id id_tw;

      id id_earth;
      id id_vg;
      id id_ae;
      id id_il;


      string str_http_host;
      string str_http_version;
      string str_http_status_code;
      string str_http_status;
      string str_http_method;
      string str_http_protocol;
      string str_http_referer;
      string str_https;

      string str_query_string;

      string str_content_length;
      string str_content_type;
      string str_connection;
      string str_location;
      string str_set_cookie;
      string str_cookie;
      string str_cache_control;
      string str_pragma;
      string str_expires;
      string str_host;
      string str_referer;

      string str_close;

      string str_put;

      string str_remote_addr;
      string str_request_uri;


      


      str_pool()
      { 
      
         reset();
      
      }


      void reset() const
      {
         (const_cast < str_pool * > (this))->_reset();
      }


   protected:

      void _reset()
      {

         id_at = "at";
         id_de_at = "de-at";
         id_de = "de";
         id_de_de = "de-de";
         
         id_br = "br";
         id_pt_br = "pt-br";
         id_pt = "pt";
         
         id_es = "es";
         
         id_cn = "cn";
         id_zh_cn = "zh-cn";
         id_zh_tw = "zh-tw";
         id_hk = "hk";
         
         id_ja = "ja";
         id_jp = "jp";
         
         id_en = "en";
         id_std = "_std";
         
         id_pe = "pe";
         id_mx = "mx";
         id_ec = "ec";
         
         id_tw = "tw";
         
         str_http_host = "http_host";
         str_http_version = "http_version";
         str_http_status_code = "http_status_code";
         str_http_status = "http_status";
         str_http_method = "http_method";
         str_http_protocol = "http_protocol";
         str_http_referer = "http_referer";
         str_https = "https";
         
         str_query_string = "query_string";
         
         str_content_length = "content-length";
         str_content_type = "content-type";
         str_connection = "connection";
         str_location = "location";
         str_set_cookie = "set-cookie";
         str_cookie = "cookie";
         str_cache_control = "cache-control";
         str_pragma = "pragma";
         str_expires = "expires";
         str_host = "host";
         str_referer = "referer";
         
         str_close = "close";
         
         str_put = "put";
         
         str_remote_addr = "remote_addr";
         str_request_uri = "request_uri";

      }

   };


   class CLASS_DECL_ca system :
      virtual public ::plane::application,
      virtual public ::gen::system,
      virtual public debug_reporter
   {
   public:


      sp(::ca2::filehandler::handler)              m_spfilehandler;
      ::cube::cube *                  m_pcube;
      ::plane::application *          m_pcubeInterface;


#ifdef WINDOWS
/*      Gdiplus::GdiplusStartupInput *   m_pgdiplusStartupInput;
      Gdiplus::GdiplusStartupOutput *  m_pgdiplusStartupOutput;
      ULONG_PTR                        m_gdiplusToken;
      ULONG_PTR                        m_gdiplusHookToken;*/
      mutex                            m_mutexGdiplus;
#endif

      const str_pool                   m_cstrpool;

      ::collection::strid_map < ::ca::type_info > m_typemap;

      mutex                            m_mutexDelete;
      ::ca::application_ptra           m_appptra;
      class ::ca::file::system         m_file;
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
      ::ca4::copydesk_sp               m_spcopydesk;
      ::ca4::port_forward_sp           m_spportforward;
      ::string_to_string_map           m_mapAppLibrary;


      class ::fontopus::user_set       m_userset;
      string_to_string_map             m_mapFontopusServer;


      plane::session::run_start_installer *  m_prunstartinstaller;
      plane::session::map *          m_pbergedgemap;


      class ::ca2::log *               m_plog;
      class factory *                  m_pfactory;
      class ::ca::history *            m_phistory;
      class ::ca::window_draw *        m_ptwf;
//      sp(::ca2::filehandler::handler)  m_spfilehandler;


      fontopus::authentication_map     m_authmap;


      index                            m_iNewEdge;

      class machine_event_central *    m_pmachineeventcentral;

      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                             m_bInitApplication;
      BOOL                             m_bInitApplicationResult;
      bool                             m_bProcessInitialize;
      bool                             m_bProcessInitializeResult;


      bool                             m_bLibCharGuess;

      ::user::str *                    m_puserstr;

     ::collection::string_map < ::collection::int_map < string, string >, const ::collection::int_map < string, string > & > m_mapEnumToName;
     ::collection::string_map < ::collection::string_map < int, int >, const ::collection::string_map < int, int > & > m_mapNameToEnum;


     bool                              m_bDoNotExitIfNoApplications;


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

      virtual bool finalize();
      virtual int exit_instance();

      virtual index get_new_bergedge(::ca::application_bias * pbiasCreation = NULL);

      virtual void register_bergedge_application(::ca::application * papp);
      virtual void unregister_bergedge_application(::ca::application * papp);

      using ::plane::application::alloc;
      virtual ::ca::ca * alloc(::ca::application * papp, ::ca::type_info & info);
      virtual ::ca::ca * alloc(::ca::application * papp, const class id & idType);

      virtual ::ca::ca * on_alloc(::ca::application * papp, ::ca::type_info & info);
      virtual ::ca::ca * clone();
      virtual ::ca::ca * clone(::ca::ca * pobj);
      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast < T * > (clone(dynamic_cast < ::ca::ca * > (pt)));
      }

      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale, bool bUser);
      virtual void appa_set_schema(const char * pszStyle, bool bUser);

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

      virtual void on_allocation_error(::ca::application * papp, ::ca::type_info & info);

      // file & dir
      virtual string matter_as_string(::ca::application * papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual string dir_matter(::ca::application * papp, const char * pszMatter, const char * pszMatter2 = NULL);
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

      inline ::ca::file::system        & file() { return m_file; }
      inline ::ca::dir::system         & dir() { return m_spdir; }
      ::ca2::stra                      & stra();
      inline ::ca2::url                & url() { return m_url; }
      ::ca2::html                      & html();
      ::ca2::xml                       & xml();
      ::ca2::install                   & install();
      ::ca2::service                   & service();
      class ::machine_event_central    & machine_event_central();
      ::ca::osi                        & osi();
      using ::plane::application::process;
      ::ca2::process                   & process();
      class ::ca2::net                 & net();

      ::ca::history                    & hist();

      class ::ca4::compress            & compress();
      class ::ca4::patch               & patch();
      class ::ca4::crypt               & crypt();
      class ::ca4::http::system        & http();
      class ::ca4::email               & email();
      class ::ca4::file                & file36();
      class ::ca4::copydesk            & copydesk();

      ::fontopus::user_set             & userset();

      ::user::str                      & str();

      ::ca2::filehandler::handler      & filehandler();

      virtual void on_delete(::ca::ca * pca);


      virtual bool base_support();

      bool sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser = NULL, ::http::cookies * pcookies = NULL);

      DECL_GEN_SIGNAL(on_application_signal);

      virtual void http_config_proxy(const char * pszUrl, ::sockets::http_tunnel * psocket);

      bool set_history(::ca::history * phistory);


      unsigned long guess_code_page(const char * pszText);



      plane::session * get_session(index iEdge, ::ca::application_bias * pbiasCreation = NULL);
      plane::session * query_session(index iEdge);


      void on_request(::ca::create_context * pcreatecontext);

      ::ca::application * application_get(index iEdge, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = NULL);

      void open_by_file_extension(index iEdge, const char * pszPathName);

      static void register_delete(::ca::ca * plistened, ::ca::ca * plistener);
      static void unregister_delete(::ca::ca * plistened, ::ca::ca * plistenerOld);

      virtual bool wait_twf(DWORD dwTimeOut = INFINITE);

      template < class T >
      ::ca::type_info & type_info()
      {
         return get_type_info(typeid(T));
      }

      virtual ::ca::type_info & get_type_info(const ::std_type_info & info);
      inline ::ca::type_info & get_type_info(const class id & idType)
      {
         return m_typemap[idType];
      }

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
         b = enum_from_name(System.template type_info < E > (), psz, iDefault);
      }

      template < class E , E edefault>
      string get_name(const base_enum < E, edefault > & b)
      {
         return get_enum_name(System.template type_info < E > (), (int) (E) b);
      }


      int enum_from_name(::ca::type_info info, const char * psz, int iDefault = 0)
      {
         return m_mapNameToEnum[info.raw_name()].get(psz, iDefault);
      }
      int enum_from_name(const std_type_info & info, const char * psz, int iDefault = 0)
      {
          #ifdef WINDOWS
         return m_mapNameToEnum[info.raw_name()].get(psz, iDefault);
         #else
         return m_mapNameToEnum[info.name()].get(psz, iDefault);
         #endif
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
         set_enum_name(System.template type_info < TYPE > (), (int) e, psz);
      }
      template < class TYPE >
      string get_enum_name(TYPE e)
      {
         return get_enum_name(System.template type_info < TYPE > (), (int) e);
      }

      virtual bool create_twf();

      virtual bool is_system();

      virtual void discard_to_factory(::ca::ca * pca);

      virtual bool verb();

      virtual ::ca::application * get_new_app(::ca::application * pappNewApplicationParent, const char * pszId);

      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache();
      virtual bool map_application_library(const char * pszLibrary);


      virtual bool set_main_init_data(::ca::main_init_data * pdata);

      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/Cube
      //
      ::document * hold(::user::interaction * pui);

      virtual count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);
      virtual FileManagerTemplate * GetStdFileManagerTemplate();

	   virtual ::gen::command_thread & command_thread();


      virtual bool on_install();

      virtual string get_fontopus_server(const char * pszUrl, ::ca::application * papp, int iRetry = -1);

      virtual string get_host_location_url();

   };


   //CLASS_DECL_ca class heap_item_array * get_heap_itema();

   //CLASS_DECL_ca void set_heap_itema(class heap_item_array * pitema);


} // namespace cube8


namespace gen
{


   template < class T >
   holder < T > ::~holder()
   {
      if(m_pca != NULL)
      {
         Sys(m_pca->m_papp).unregister_delete(m_pca, this);
      }
   }

   template < class T >
   void holder < T > ::set_p(T * p)
   {
      if(m_p == p)
         return;
      if(m_pca != NULL)
      {
         Sys(m_pca->m_papp).unregister_delete(m_p, this);
      }
      m_pca = dynamic_cast < ::ca::ca * > (p);
      if(m_pca == NULL)
      {
         m_p = NULL;
      }
      else
      {
         m_p = p;
         Sys(m_pca->m_papp).register_delete(m_pca, this);
      }
   }


   template < class T >
   holder_array < T > ::holder_array(const holder_array & a)
   {
      m_ptra      = a.m_ptra;
      m_captra    = a.m_captra;
      for(index i = 0; i < m_captra.get_count(); i++)
      {
         Sys(m_captra[i]->m_papp).register_delete(m_captra[i], this);
      }
      if(m_captra.get_count() > 0)
      {
         m_papp = m_captra.last_element()->m_papp;
      }
   }

   template < class T >
   count holder_array < T >::remove_all()
   {
      for(index i = 0; i < m_captra.get_count(); i++)
      {
        Sys(m_papp).unregister_delete(m_captra[i], this);
      }
      m_ptra.remove_all();
      return m_captra.remove_all();
   }

   template < class T >
   index holder_array < T > ::remove_at(index iRemove, count count)
   {
      for(index i = iRemove; i < m_captra.get_count() && i < (iRemove + count); i++)
      {
         Sys(m_papp).unregister_delete(m_captra[i], this);
      }
      m_ptra.remove_at(iRemove, count);
      return m_captra.remove_at(iRemove, count);
   }

   template < class T >
   index holder_array < T >::add_unique(T * p)
   {
      ::ca::ca * pca = dynamic_cast < ::ca::ca * > (p);
      if(pca == NULL)
         return -1;
      if(pca->m_papp == NULL)
         return -1;
      if(pca->m_papp->m_psystem == NULL)
         return -1;
      index iFind = find(p);
      if(iFind >= 0)
         return iFind;
      m_papp = pca->m_papp;
      Sys(pca->m_papp).register_delete(pca, this);
      m_ptra.add(p);
      return m_captra.add(pca);
   }

   template < class T >
   index holder_array < T > ::insert_at(index i, T * p)
   {
      ::ca::ca * pca = dynamic_cast < ::ca::ca * > (p);
      if(pca == NULL)
         return -1;
      if(pca->m_papp == NULL)
         return -1;
      if(pca->m_papp->m_psystem == NULL)
         return -1;
      index iFind = find(p);
      if(iFind >= 0)
      {
         if(iFind != i)
         {
            throw "Could not insert the element at the specified position. The array already contains this element.";
         }
         return iFind;
      }
      m_papp = pca->m_papp;
      Sys(pca->m_papp).register_delete(pca, this);
      m_ptra.insert_at(i, p);
      m_captra.insert_at(i, pca);
      return i;
   }


   template < class T >
   index holder_array < T > ::set_at(index i, T * p)
   {
      ::ca::ca * pca = dynamic_cast < ::ca::ca * > (p);
      if(pca == NULL)
         return -1;
      if(pca->m_papp == NULL)
         return -1;
      if(pca->m_papp->m_psystem == NULL)
         return -1;
      index iFind = find(p);
      if(iFind >= 0)
      {
         if(iFind != i)
         {
            throw "Could not set the element to the specified position. The array already contains this element.";
         }
         return iFind;
      }
      Sys(m_captra[i]->m_papp).unregister_delete(m_captra[i], this);
      m_papp = pca->m_papp;
      Sys(pca->m_papp).register_delete(pca, this);
      m_ptra.set_at(i, p);
      m_captra.set_at(i, pca);
      return i;
   }


   template < class T >
   count holder_array < T > ::remove(T * p, bool bCallNativeArrayBaseTypeOnDelete)
   {
      count count = 0;
      for(index i = 0; i < m_captra.get_size(); )
      {
         if(m_ptra[i] == p)
         {
            try
            {
               Sys(m_captra[i]->m_papp).unregister_delete(m_captra[i], this);
            }
            catch(...)
            {
            }
            m_captra.remove_at(i);
            if(bCallNativeArrayBaseTypeOnDelete)
            {
               try
               {
                  on_delete(m_ptra.element_at(i));
               }
               catch(...)
               {
               }
            }
            m_ptra.remove_at(i);
            count++;
         }
         else
         {
            i++;
         }
      }
      return count;
   }

   template < class T >
   holder_array < T > & holder_array < T > ::operator = (const holder_array < T > & a)
   {
      if(&a != this)
      {
         remove_all();
         m_ptra      = a.m_ptra;
         m_captra    = a.m_captra;
         for(index i = 0; i < m_captra.get_count(); i++)
         {
            Sys(m_captra[i]->m_papp).register_delete(m_captra[i], this);
         }
         if(m_captra.get_count() > 0)
         {
            m_papp = m_captra.last_element()->m_papp;
         }
      }
      return *this;
   }



} // namespace gen


#ifdef LINUX


template < class T >
bool ::ca::file::system::output(::ca::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::writer &, const char *), const char * lpszSource)
{

    App(papp).dir().mk(System.dir().name(pszOutput));

    ex1::filesp fileOut = App(papp).get_file(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write);

    if(fileOut.is_null())
        return false;

    return (p->*lpfnOuput)(fileOut, lpszSource);

}


 template < class T >
 bool ::ca::file::system::output(::ca::application * papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ex1::writer &, ::ex1::reader &), const char * lpszInput)
 {

    App(papp).dir().mk(System.dir().name(pszOutput));

    ex1::filesp fileOut = App(papp).get_file(pszOutput, ex1::file::mode_create | ex1::file::type_binary | ex1::file::mode_write);

    if(fileOut.is_null())
        return false;

    ex1::filesp fileIn = App(papp).get_file(lpszInput, ex1::file::type_binary | ex1::file::mode_read);

    if(fileIn.is_null())
       return false;

    return (p->*lpfnOuput)(fileOut, fileIn);

 }

 #endif // defined LINUX



template < class TYPE, class ARG_TYPE >
inline TYPE * array_app_alloc < TYPE, ARG_TYPE >::add_new()
{
    ::ca::type_info & ti = System.template type_info < TYPE > ();
   TYPE * pt = dynamic_cast < TYPE * > (System.alloc(this->get_app(), ti));
   this->ptra().add(pt);
   return pt;
}


template < class TYPE, class ARG_TYPE >
inline index array_app_alloc < TYPE, ARG_TYPE >::add(
   const TYPE & t)
{
    ::ca::type_info & ti = System.template type_info < TYPE > ();
   TYPE * pt = dynamic_cast < TYPE * > (System.alloc(this->get_app(), ti));
   *pt = t;
   return this->ptra().add(pt);
}











































template <class TYPE, class ARG_TYPE, class BASE_PTRA>
inline TYPE * array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::add_new()
{
   TYPE * p = System.alloc(this->get_app(), System.type_info());
   array_release_ptr < TYPE, ARG_TYPE >::add(p);
   return p;
}


template < class TYPE, class ARG_TYPE, class BASE_PTRA >
void array_smart_ptr < TYPE, ARG_TYPE, BASE_PTRA >::set_at_grow(index iIndex, ARG_TYPE t)
{
   ASSERT(iIndex >= 0);

   if(iIndex < this->ptra().get_size())
   {
      this->element_at(iIndex) = t;
   }
   else
   {
      for(index i = this->get_size(); i < iIndex; i++)
      {
         this->ptra().add(System.alloc(this->get_app(), System.type_info()));
      }
      this->ptra().add(System.alloc(this->get_app(), System.type_info()));
   }
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::insert_at(index iIndex, ARG_TYPE t)
{
   
   TYPE * pt = dynamic_cast < TYPE * > (System.alloc(this->get_app(), System.template type_info < TYPE > ()));
   
   *pt = t;

   this->ptra().insert_at(iIndex, pt);

}


template <class TYPE, class ARG_TYPE>
inline array_app_alloc <TYPE, ARG_TYPE> & array_app_alloc < TYPE, ARG_TYPE >::operator = (const array_app_alloc <TYPE, ARG_TYPE> & a)
{
   
   remove_all();

   for(index i = 0; i < a.ptra().get_size(); i++)
   {

      TYPE * pt = dynamic_cast < TYPE * > (System.alloc(this->get_app(), System.template type_info < TYPE > ()));

      *pt = *a.ptra()[i];

      this->ptra().add(pt);

   }

   this->ptra().set_size(a.ptra().get_size());

   return *this;

}



template<class TYPE, class ARG_TYPE>
void array_app_alloc<TYPE, ARG_TYPE>::set_at_grow(index iIndex, ARG_TYPE t)
{

   ASSERT(iIndex >= 0);

   if(iIndex < this->ptra().get_size())
   {
      this->element_at(iIndex) = t;
   }
   else
   {
      INT_PTR iOldSize = this->ptra().get_size();
      this->ptra().set_size(iIndex + 1);
      INT_PTR iEmptySize = this->ptra().get_size() - 1;
      index i;
      if(this->get_app() == NULL)
         set_app(t.get_app());
      for(i = iOldSize; i < iEmptySize; i++)
      {
         this->ptra().element_at(i) = dynamic_cast < TYPE * > (System.alloc(this->get_app(), System.template type_info < TYPE > ()));
      }
      this->ptra().element_at(i) = dynamic_cast < TYPE * > (System.clone(dynamic_cast < ::ca::ca * > (const_cast < TYPE * > (&t))));
   }
}

template <class TYPE, class ARG_TYPE>
inline void array_app_alloc < TYPE, ARG_TYPE >::
set_size(::count iSize)
{
   while(this->get_size() < iSize)
   {
      TYPE * pt = dynamic_cast < TYPE * > (System.alloc(this->get_app(), System.template type_info < TYPE > ()));
      add(pt);
   }
   while(this->get_size() > iSize)
   {
      remove_at(this->get_size() - 1);
   }
}


#include "ca/collection/gen_lemon_array.h"



template < class VIEW >
inline VIEW * view::create_view(::user::document_interface * pdoc, ::user::interaction * pwndParent, id id, ::user::interaction * pviewLast)
{
   return dynamic_cast < VIEW * > (create_view(System.template type_info < VIEW > (), pdoc, pwndParent, id, pviewLast));
}


template < class VIEW >
inline VIEW * view::create_view(::user::interaction * pwndParent, id id, ::user::interaction * pviewLast)
{
   return create_view < VIEW > (NULL, pwndParent, id, pviewLast);
}

template < class VIEW >
inline VIEW * view::create_view(::user::view_creator_data * pcreatordata, ::user::interaction * pviewLast)
{
   return create_view < VIEW > (pcreatordata->m_pholder, pcreatordata->m_id, pviewLast);
}



   template < class DOCUMENT >
   ::ca::data * view::get_data()
    { 
       ASSERT(this != NULL); 
       DOCUMENT * pdocument = get_typed_document < DOCUMENT > ();
       if(pdocument == NULL)
          return NULL;
       return pdocument->get_data();
   }

   template < class DOCUMENT >
   DOCUMENT * view::get_typed_document()
   {
      if(m_spdocument.is_null())
         return NULL;
      return dynamic_cast < DOCUMENT * > (m_spdocument.m_p);
   }
