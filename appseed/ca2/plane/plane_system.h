#pragma once


//#ifndef WINDOWS
//#define INFINITE 0xffffffff
//#endif

#ifdef METROWIN

#include <agile.h>

#endif

class id;


namespace ca
{


   class CLASS_DECL_ca2 ptra :
      virtual public spa(::ca::ca)
   {
   public:
   };

   typedef ::map < sp(::ca::ca), sp(::ca::ca), sp(::ca::ca), sp(::ca::ca) > map;
   typedef ::map < sp(::ca::ca), sp(::ca::ca), ptra, ptra > map_many;


} // namespace ca


#undef __str
#define __str(x) (m_papp->m_psystem->m_cstrpool.str_##x)
#undef __id
#define __id(x) (m_papp->m_psystem->m_cstrpool.id_##x)



namespace plane
{


   class CLASS_DECL_ca2 str_pool
   {
   public:

      id id_cc;
      id id_se;
      id id_sv_se;
      id id_sv;


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
      id id_ja_jp;

      id id_fr;
      id id_fr_ca;
      id id_ca;

      id id_en;
      id id_en_us;
      id id_en_ca;
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

      string str_accept_encoding;
      string str_content_encoding;



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
         id_cc = "cc";
         id_se = "se";
         id_sv_se = "sv-se";
         id_sv = "sv";

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

         id_ja_jp = "ja-jp";
         id_ja = "ja";
         id_jp = "jp";

         id_fr = "fr";
         id_fr_ca = "fr-ca";
         id_ca = "ca";

         id_en = "en";
         id_en_us = "en-us";
         id_en_ca = "en-ca";
         id_std = "_std";

         id_pe = "pe";
         id_mx = "mx";
         id_ec = "ec";

         id_tw = "tw";

         id_earth = "earth";
         id_vg = "vg";
         id_ae = "ae";
         id_il = "il";

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

         str_accept_encoding = "accept-encoding";
         str_content_encoding = "content-encoding";

      }

   };


   class CLASS_DECL_ca2 system :
      virtual public ::plane::application,
      virtual public ::ca::system
   {
   public:


      mutex                                        m_mutex;
#ifdef METROWIN
      sp(::user::interaction)                      m_pui;
      ::ca::system_window ^                        m_pwindow;
      sp(ID2D1DeviceContext)                       m_pdc;
      sp(mutex)                                    m_pmutexDc;
#endif
      sp(::filehandler::handler)                   m_spfilehandler;
      ::cube::cube *                               m_pcube;
      sp(::plane::application)                     m_pcubeInterface;


      const str_pool                               m_cstrpool;

      spa(service_base)                            m_serviceptra;

      strsp(::ca::type_info)                       m_typemap;

      FT_Library                                   m_ftlibrary;
      mutex                                        m_mutexDelete;
      ::ca::application_ptra                       m_appptra;
      ::ca::file_system_sp                         m_spfile;
      ::ca::dir::system_sp                         m_spdir;
      class ::ca::stra                             m_stra;
      class ::ca::url                              m_url;
      sp(class ::xml::xml)                         m_pxml;
      class ::ca::service                          m_service;
      class ::ca::install                          m_install;
      ::ca::os_sp                                  m_spos;
#ifndef METROWIN
      class ::ca::process_section                  m_processsection;
#endif
      sp(class ::ca::datetime)                     m_pdatetime;
      class ::sockets::net                         m_net;

      class ::ca::compress                         m_compress;
      class ::ca::patch                            m_patch;
      ::ca::crypt_sp                               m_spcrypt;
      class ::ca::http::system                     m_http;
      class ::ca::email                            m_email;
      ::ca::copydesk_sp                            m_spcopydesk;
      ::ca::port_forward_sp                        m_spportforward;
      ::string_to_string_map                       m_mapAppLibrary;
      sp(colorertake5::ParserFactory)              m_pparserfactory;


      class ::fontopus::user_set                   m_userset;
      string_to_string_map                         m_mapFontopusServer;


      sp(plane::session::run_start_installer)      m_prunstartinstaller;
      sp(plane::session::map)                      m_pbergedgemap;


      sp(class ::ca::log)                          m_plog;
      sp(class ::ca::factory)                      m_pfactory;
      sp(class ::ca::history)                      m_phistory;
      sp(::ca::window_draw)                        m_ptwf;
      //      ::sockets::net                               m_net;
      //      sp(::ca::filehandler::handler)  m_spfilehandler;


      fontopus::authentication_map                 m_authmap;


      index                                        m_iNewEdge;

      class machine_event_central *                m_pmachineeventcentral;

      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                                         m_bInitApplication;
      bool                                         m_bInitApplicationResult;
      bool                                         m_bProcessInitialize;
      bool                                         m_bProcessInitializeResult;


      bool                                         m_bLibCharGuess;

      ::user::str *                                m_puserstr;

      string_map < int_map < string, string >, const int_map < string, string > & >
         m_mapEnumToName;

      string_map < string_map < int32_t, int32_t >, const string_map < int32_t, int32_t > & >
         m_mapNameToEnum;


      bool                                          m_bDoNotExitIfNoApplications;

      strid_map < ::ca::library * >  m_idmapCreateViewLibrary;

      comparable_array < ::ca::library * >         m_libraryptra;

#ifdef METROWIN
      Platform::Agile < Windows::UI::Core::CoreWindow > m_window;
#endif

            ::visual::visual                    m_visual;


      system(sp(::ca::application) papp = ::null());
      virtual ~system();


      //virtual int32_t main();
      virtual bool InitApplication();

      virtual bool process_initialize();

      virtual bool initialize();
      virtual bool initialize1();
      virtual bool initialize3();

      virtual bool initialize_instance();

      virtual bool bergedge_start();

      virtual bool finalize();
      virtual int32_t exit_instance();

      virtual index get_new_bergedge(::ca::application_bias * pbiasCreation = ::null());

      virtual void register_bergedge_application(sp(::ca::application) papp);
      virtual void unregister_bergedge_application(sp(::ca::application) papp);

      using ::plane::application::alloc;
      virtual sp(::ca::ca) alloc(sp(::ca::application) papp, sp(::ca::type_info) info);
      virtual sp(::ca::ca) alloc(sp(::ca::application) papp, const class id & idType);

      virtual sp(::ca::ca) on_alloc(sp(::ca::application) papp, sp(::ca::type_info) info);
      virtual sp(::ca::ca) clone();
      virtual sp(::ca::ca) clone(sp(::ca::ca) pobj);
      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast < T * > (clone(dynamic_cast < sp(::ca::ca) > (pt)));
      }

      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale, bool bUser);
      virtual void appa_set_schema(const char * pszStyle, bool bUser);

      virtual bool assert_running_global(const char * pszAppName, const char * pszId = ::null());
      virtual bool assert_running_local(const char * pszAppName, const char * pszId = ::null());

      virtual bool initialize_log(const char * pszId);

      virtual int32_t _001OnDebugReport(int32_t i1, const char * psz1, int32_t i2, const char * psz2, const char * psz3, va_list args);

      virtual int32_t __ca2_logging_report(
         int32_t _ReportType,
         const char * _Filename,
         int32_t _Linenumber,
         const char * _ModuleName,
         const char * _Format,
         va_list list);

      virtual bool assert_failed_line(const char * lpszFileName, int32_t iLine);

      virtual void on_allocation_error(sp(::ca::application) papp, sp(::ca::type_info) info);

      // file & dir
      virtual string matter_as_string(sp(::ca::application) papp, const char * pszMatter, const char * pszMatter2 = ::null());
      virtual string dir_matter(sp(::ca::application) papp, const char * pszMatter, const char * pszMatter2 = ::null());
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(sp(::ca::application) papp, const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = ::null());
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);

      class ::ca::factory                 & factory();
      class ::ca::log                     & log();

      sp(::ca::window_draw )              get_twf();

      FT_Library                          & ftlibrary();

      ::ca::application_ptra              & appptra();
      ::ca::datetime                      & datetime();

      inline ::ca::file_system            & file()    { return m_spfile; }
      inline ::ca::dir::system            & dir()     { return m_spdir; }
      ::ca::stra                          & stra();
      inline ::ca::url                    & url()     { return m_url; }
      ::xml::xml                          & xml();
      ::ca::install                       & install();
      ::ca::service                       & service();
      class ::machine_event_central       & machine_event_central();
      class ::ca::os                      & os();
      using ::plane::application::process;
#ifndef METROWIN
      ::ca::process_section               & process();
#endif
      class ::sockets::net                & net();

      ::ca::history                    & hist();

      class ::ca::compress            & compress();
      class ::ca::patch               & patch();
      class ::ca::crypt               & crypt();
      class ::ca::http::system        & http();
      class ::ca::email               & email();
      class ::ca::copydesk            & copydesk();

      ::fontopus::user_set             & userset();

      ::user::str                      & str();

      ::filehandler::handler           & filehandler();

      ::colorertake5::ParserFactory    & parser_factory();

      static ::exception::engine       & eengine();
            inline class ::visual::visual             & visual()     { return m_visual       ; }


      


      virtual bool base_support();

      bool sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser = ::null(), ::http::cookies * pcookies = ::null());

      DECL_GEN_SIGNAL(on_application_signal);

      bool set_history(::ca::history * phistory);


      uint32_t guess_code_page(const char * pszText);

#ifdef METROWIN

      virtual bool get_window_rect(LPRECT lprect);

#endif

      virtual void post_fork_uri(const char * pszUri, ::ca::application_bias * pbiasCreate);


      sp(::plane::session) get_session(index iEdge, ::ca::application_bias * pbiasCreation = ::null());
      sp(::plane::session) query_session(index iEdge);


      void on_request(sp(::ca::create_context) pcreatecontext);

      sp(::ca::application) application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca::application_bias * pbiasCreate = ::null());

      void open_by_file_extension(index iEdge, const char * pszPathName);

      //static void register_delete(sp(::ca::ca) plistened, sp(::ca::ca) plistener);
      //static void unregister_delete(sp(::ca::ca) plistened, sp(::ca::ca) plistenerOld);

      virtual bool wait_twf(uint32_t dwTimeOut = INFINITE);

      template < class T >
      sp(::ca::type_info) type_info()
      {
         return get_type_info(typeid(T));
      }

      virtual sp(::ca::type_info) get_type_info(const ::std_type_info & info);
      sp(::ca::type_info) get_type_info(const class id & idType)
      {
         return m_typemap[idType];
      }

      void set_enum_name(sp(::ca::type_info) etype, int32_t i, const char * psz)
      {
         m_mapEnumToName[etype->name()][i] = psz;
         m_mapNameToEnum[etype->name()][psz] = i;
      }
      string get_enum_name(sp(::ca::type_info) info, int32_t i)
      {
         return m_mapEnumToName[info->name()].get(i, "");
      }

      template < class E , E edefault>
      void from_name(base_enum < E, edefault > & b, const char * psz, E iDefault = edefault)
      {
         b = enum_from_name(System.type_info < E > (), psz, iDefault);
      }

      template < class E , E edefault>
      string get_name(const base_enum < E, edefault > & b)
      {
         return get_enum_name(System.type_info < E > (), (int32_t) (E) b);
      }

      template < class ENUM >
      ENUM enum_from_name(sp(::ca::type_info) info, const char * psz, int32_t iDefault = 0)
      {
         return (ENUM) m_mapNameToEnum[info->name()].get(psz, iDefault);
      }
      int32_t enum_from_name(sp(::ca::type_info) info, const char * psz, int32_t iDefault = 0)
      {
         return m_mapNameToEnum[info->name()].get(psz, iDefault);
      }
      int32_t enum_from_name(const std_type_info & info, const char * psz, int32_t iDefault = 0)
      {
#ifdef WINDOWS
         return m_mapNameToEnum[info.name()].get(psz, iDefault);
#else
         return m_mapNameToEnum[info.name()].get(psz, iDefault);
#endif
      }

      template < class TYPE >
      void set_enum_name(sp(::ca::type_info) etype, TYPE e, const char * psz)
      {
         set_enum_name(etype, (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(sp(::ca::type_info) etype, TYPE e)
      {
         return get_enum_name(etype, (int32_t) e);
      }

      template < class TYPE >
      void set_enum_name(const std_type_info & info, TYPE e, const char * psz)
      {
         set_enum_name(sp(::ca::type_info)(info), (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(const std_type_info & info, TYPE e)
      {
         return get_enum_name(sp(::ca::type_info)(info), (int32_t) e);
      }

      template < class TYPE >
      void set_enum_name(TYPE e, const char * psz)
      {
         set_enum_name(System.type_info < TYPE > (), (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(TYPE e)
      {
         return get_enum_name(System.type_info < TYPE > (), (int32_t) e);
      }

      virtual bool create_twf();

      virtual bool is_system();

      virtual void discard_to_factory(sp(::ca::ca) pca);

      virtual bool verb();

      virtual sp(::ca::application) get_new_app(sp(::ca::application) pappNewApplicationParent, const char * pszType, const char * pszId);

      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache();
      virtual bool map_application_library(const char * pszLibrary);


      virtual bool set_main_init_data(::ca::main_init_data * pdata);

      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/Cube
      //
      sp(::document) hold(sp(::user::interaction) pui);

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual index get_best_intersection_monitor(LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);

      virtual sp(::ca::command_thread) command_thread();


      virtual bool on_install();

      virtual string get_fontopus_server(const char * pszUrl, sp(::ca::application) papp, int32_t iRetry = -1);

      virtual string get_host_location_url();

      virtual bool add_library(::ca::library * plibrary);

      virtual void get_cursor_pos(LPPOINT lppoint);


   };


   //CLASS_DECL_ca2 class heap_item_array * get_heap_itema();

   //CLASS_DECL_ca2 void set_heap_itema(class heap_item_array * pitema);


} // namespace cube


namespace ca
{





} // namespace ca


#if defined(LINUX) || defined(MACOS)


template < class T >
bool ::ca::file_system::output(sp(::ca::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::ca::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write);

   if(fileOut.is_null())
      return false;

   return (p->*lpfnOuput)(fileOut, lpszSource);

}


template < class T >
bool ::ca::file_system::output(sp(::ca::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca::writer &, ::ca::reader &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::ca::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::ca::filesp fileIn = App(papp).file().get_file(lpszInput, ::ca::file::type_binary | ::ca::file::mode_read);

   if(fileIn.is_null())
      return false;

   return (p->*lpfnOuput)(fileOut, fileIn);

}

#endif // defined LINUX









































#include "ca/collection/collection_lemon_array.h"



template < class VIEW >
inline sp(VIEW) view::create_view(::user::document_interface * pdoc, sp(::user::interaction) pwndParent, id id, sp(::user::interaction) pviewLast)
{
   return create_view(System.type_info < VIEW > (), pdoc, pwndParent, id, pviewLast);
}


template < class VIEW >
inline sp(VIEW) view::create_view(::user::interaction * pwndParent, id id, sp(::user::interaction) pviewLast)
{
   return create_view < VIEW > (::null(), pwndParent, id, pviewLast);
}

template < class VIEW >
inline sp(VIEW) view::create_view(::user::view_creator_data * pcreatordata, sp(::user::interaction) pviewLast)
{

   VIEW * pview = create_view < VIEW > (pcreatordata->m_pholder, pcreatordata->m_id, pviewLast);

   if(pview != ::null())
   {
      pcreatordata->m_pdoc = get_document();
   }

   return pview;

}



template < class DOCUMENT >
::ca::data * view::get_data()
{
   ASSERT(this != ::null());
   DOCUMENT * pdocument = get_typed_document < DOCUMENT > ();
   if(pdocument == ::null())
      return ::null();
   return pdocument->get_data();
}

template < class DOCUMENT >
DOCUMENT * view::get_typed_document()
{
   if(m_spdocument.is_null())
      return ::null();
   return dynamic_cast < DOCUMENT * > (m_spdocument.m_p);
}



namespace xml
{

   inline disp_option::disp_option(sp(::ca::application) papp)
   {
      newline = true;
      reference_value = true;
      m_pentities = &papp->m_psystem->m_pxml->m_entities;
      tab_base = 0;
      value_quotation_mark = '"';
   }


} // namespace xml
