#pragma once


//#ifndef WINDOWS
//#define INFINITE 0xffffffff
//#endif

#ifdef METROWIN

#include <agile.h>

#endif

class id;


namespace ca2
{


   class CLASS_DECL_ca2 ptra :
      virtual public spa(::ca2::ca2)
   {
   public:
   };

   typedef ::map < sp(::ca2::ca2), sp(::ca2::ca2), sp(::ca2::ca2), sp(::ca2::ca2) > map;
   typedef ::map < sp(::ca2::ca2), sp(::ca2::ca2), ptra, ptra > map_many;


} // namespace ca2


#undef __id
#define __id(x) (m_papp->m_psystem->m_cidpool.id_##x)



namespace plane
{


   class CLASS_DECL_ca2 id_pool
   {
   public:

      id id_eu;
      id id_uk;
      id id_fi;
      id id_gr;
      id id_nl;
      id id_be;
      id id_it;
      id id_cz;


      id id_dk;
      id id_en_uk;
      id id_lu;
      id id_ie;
      id id_no;
      id id_cy;
      id id_su;
      id id_lv;
      id id_li;
      id id_hu;
      id id_sk;
      id id_si;
      id id_ro;
      id id_kz;
      id id_ru;
      id id_pl;
      id id_tr;
      id id_ee;
      id id_asia;
      id id_vn;
      id id_in;
      id id_kg;
      id id_kr;
      id id_my;
      id id_ph;
      id id_sg;


      id id_zh;
      id id_sy;
      id id_ps;
      id id_ar;
      id id_bo;
      id id_cl;
      id id_co;
      id id_gs;
      id id_py;
      id id_uy;
      id id_ve;
      id id_amdesur;
      id id_au;
      id id_oceania;
      id id_nz;
      id id_tl;
      id id_ug;
      id id_sc;
      id id_cm;
      id id_za;
      id id_africa;
      id id_us;
      id id_caribe;
      id id_ht;
      id id_cu;
      id id_tc;
      id id_centralam;
      id id_bz;
      id id_america;

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


      id id_http_host;
      id id_http_version;
      id id_http_status_code;
      id id_http_status;
      id id_http_method;
      id id_http_protocol;
      id id_http_referer;
      id id_https;

      id id_query_string;

      id id_content_length;
      id id_content_type;
      id id_connection;
      id id_location;
      id id_set_cookie;
      id id_cookie;
      id id_cache_control;
      id id_pragma;
      id id_expires;
      id id_host;
      id id_referer;

      id id_close;

      id id_put;

      id id_remote_addr;
      id id_request_uri;

      id id_accept_encoding;
      id id_content_encoding;

      id id_keep_alive;

      id id_user_agent;
      id id_from;
      id id_accept_language;


      id id_accept;


      id_pool()
      {

         reset();

      }


      void reset() const
      {
         (const_cast < id_pool * > (this))->_reset();
      }


   protected:

      void _reset()
      {


         id_eu = "eu";
         id_uk = "uk";
         id_fi = "fi";
         id_gr = "gr";
         id_nl = "nl";
         id_be = "be";
         id_it = "it";
         id_cz = "cz";

         id_dk = "dk";
         id_en_uk = "en-uk";
         id_lu = "lu";
         id_ie = "ie";
         id_no = "no";
         id_cy = "cy";
         id_su = "su";
         id_lv = "lv";
         id_li = "li";
         id_hu = "hu";
         id_sk = "sk";
         id_si = "si";
         id_ro = "ro";
         id_kz = "kz";
         id_ru = "ru";
         id_pl = "pl";
         id_tr = "tr";
         id_ee = "ee";
         id_asia = "asia";
         id_vn = "vn";
         id_in = "in";
         id_kg = "kg";
         id_kr = "kr";
         id_my = "my";
         id_ph = "ph";
         id_sg = "sg";


         id_zh = "zh";
         id_sy = "sy";
         id_ps = "ps";
         id_ar = "ar";
         id_bo = "bo";
         id_cl = "cl";
         id_co = "co";
         id_gs = "gs";
         id_py = "py";
         id_uy = "uy";
         id_ve = "ve";
         id_amdesur = "amdesur";
         id_au = "au";
         id_oceania = "oceania";
         id_nz = "nz" ;
         id_tl = "tl" ;
         id_ug = "ug" ;
         id_sc = "sc" ;
         id_cm = "cm" ;
         id_za = "za" ;
         id_africa = "africa";
         id_us = "us";
         id_caribe = "caribe";
         id_ht = "ht" ;
         id_cu = "cu" ;
         id_tc = "tc" ;
         id_centralam = "centralam";
         id_bz = "bz";
         id_america = "america";

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
         id_fr_ca = "fr-ca2";
         id_ca = "ca2";

         id_en = "en";
         id_en_us = "en-us";
         id_en_ca = "en-ca2";
         id_std = "_std";

         id_pe = "pe";
         id_mx = "mx";
         id_ec = "ec";

         id_tw = "tw";

         id_earth = "earth";
         id_vg = "vg";
         id_ae = "ae";
         id_il = "il";



         id_http_host = "http_host";
         id_http_version = "http_version";
         id_http_status_code = "http_status_code";
         id_http_status = "http_status";
         id_http_method = "http_method";
         id_http_protocol = "http_protocol";
         id_http_referer = "http_referer";
         id_https = "https";

         id_query_string = "query_string";

         id_content_length = "content-length";
         id_content_type = "content-type";
         id_connection = "connection";
         id_location = "location";
         id_set_cookie = "set-cookie";
         id_cookie = "cookie";
         id_cache_control = "cache-control";
         id_pragma = "pragma";
         id_expires = "expires";
         id_host = "host";
         id_referer = "referer";

         id_close = "close";

         id_put = "put";

         id_remote_addr = "remote_addr";
         id_request_uri = "request_uri";

         id_accept_encoding = "accept-encoding";
         id_content_encoding = "content-encoding";

         id_keep_alive = "keep-alive";

         id_user_agent = "user-agent";
         id_from = "from";
         id_accept_language = "accept-language";


         id_accept = "accept";

      }

   };


   class CLASS_DECL_ca2 system :
      virtual public ::plane::application,
      virtual public ::ca2::system
   {
   public:
      //plane::session::run_start_installer *        m_prunstartinstaller;
      //plane::session::map *                        m_pbergedgemap;
      index                                        m_iNewEdge;
      class machine_event_central *                m_pmachineeventcentral;

      mutex                                        m_mutex;
#ifdef METROWIN
      sp(::user::interaction)                      m_pui;
      ::ca2::system_window ^                       m_pwindow;
      ID2D1DeviceContext *                         m_pdevicecontext;
      sp(mutex)                                    m_pmutexDc;
#endif
      sp(::filehandler::handler)                   m_spfilehandler;


      const id_pool                                m_cidpool;

      spa(service_base)                            m_serviceptra;

      stridsp(::ca2::type_info)                     m_typemap;

      FT_Library                                   m_ftlibrary;
      mutex                                        m_mutexDelete;
      ::ca2::application_ptra                       m_appptra;
      ::ca2::file_system_sp                         m_spfile;
      ::ca2::dir::system_sp                         m_spdir;
      class ::ca2::stra                             m_stra;
      class ::ca2::url                              m_url;
      sp(class ::xml::xml)                         m_pxml;
      class ::ca2::service                          m_service;
      class ::ca2::install                          m_install;
      ::ca2::os_sp                                  m_spos;
#ifndef METROWIN
      class ::ca2::process_section                  m_processsection;
#endif
      sp(class ::ca2::datetime)                     m_pdatetime;
      class ::sockets::net                         m_net;

      class ::ca2::compress                         m_compress;
      class ::ca2::patch                            m_patch;
      ::ca2::crypt_sp                               m_spcrypt;
      class ::ca2::http::system                     m_http;
      class ::ca2::email                            m_email;
      ::ca2::copydesk_sp                            m_spcopydesk;
      ::ca2::port_forward_sp                        m_spportforward;
      ::string_to_string_map                       m_mapAppLibrary;
      sp(colorertake5::ParserFactory)              m_pparserfactory;


      class ::fontopus::user_set                   m_userset;
      string_to_string_map                         m_mapFontopusServer;


      sp(::plane::session::run_start_installer)      m_prunstartinstaller;
      sp(::plane::session::map)                      m_pbergedgemap;


      sp(class ::ca2::log)                          m_plog;
      sp(class ::ca2::factory)                      m_pfactory;
      sp(class ::ca2::history)                      m_phistory;
      sp(::ca2::window_draw)                        m_ptwf;
      //      ::sockets::net                               m_net;
      //      sp(::ca2::filehandler::handler)  m_spfilehandler;


      fontopus::authentication_map                 m_authmap;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                                         m_bInitApplication;
      bool                                         m_bInitApplicationResult;
      bool                                         m_bProcessInitialize;
      bool                                         m_bProcessInitializeResult;


      bool                                         m_bLibCharGuess;

      sp(::user::str)                              m_puserstr;

      string_map < int_map < string, string >, const int_map < string, string > & >
         m_mapEnumToName;

      string_map < string_map < int32_t, int32_t >, const string_map < int32_t, int32_t > & >
         m_mapNameToEnum;


      bool                                          m_bDoNotExitIfNoApplications;

      strid_map < ::ca2::library * >  m_idmapCreateViewLibrary;

      comparable_array < ::ca2::library * >         m_libraryptra;

#ifdef METROWIN
      Platform::Agile < Windows::UI::Core::CoreWindow > m_window;
#endif

      ::visual::visual                    m_visual;

      system(sp(::ca2::application) papp = NULL);
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

      virtual index get_new_bergedge(::ca2::application_bias * pbiasCreation = NULL);

      virtual void register_bergedge_application(sp(::ca2::application) papp);
      virtual void unregister_bergedge_application(sp(::ca2::application) papp);


      virtual bool base_support();


      DECL_GEN_SIGNAL(on_application_signal);


      using ::plane::application::process;
      bool set_history(::ca2::history * phistory);


      virtual sp(::plane::session)             get_session(index iEdge, ::ca2::application_bias * pbiasCreation = NULL);
      virtual sp(::platform::document)             get_platform(index iEdge, ::ca2::application_bias * pbiasCreation = NULL);
      virtual sp(::nature::document)               get_nature(index iEdge, ::ca2::application_bias * pbiasCreation = NULL);

      virtual sp(::plane::session)             query_bergedge(index iEdge);
      virtual void on_request(sp(::ca2::create_context) pcreatecontext);
      virtual sp(::ca2::application) application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, ::ca2::application_bias * pbiasCreate = NULL);
      virtual void open_by_file_extension(index iEdge, const char * pszPathName);
      virtual bool is_system();

      virtual sp(::ca2::command_thread) command_thread();





      //virtual int32_t main();


      using ::plane::application::alloc;
      virtual sp(::ca2::ca2) alloc(sp(::ca2::application) papp, sp(::ca2::type_info) info);
      virtual sp(::ca2::ca2) alloc(sp(::ca2::application) papp, const class id & idType);

      virtual sp(::ca2::ca2) on_alloc(sp(::ca2::application) papp, sp(::ca2::type_info) info);
      virtual sp(::ca2::ca2) clone();
      virtual sp(::ca2::ca2) clone(sp(::ca2::ca2) pobj);
      template < typename T >
      inline T * cast_clone(T * pt)
      {
         return dynamic_cast < T * > (clone(dynamic_cast < sp(::ca2::ca2) > (pt)));
      }

      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale, bool bUser);
      virtual void appa_set_schema(const char * pszStyle, bool bUser);

      virtual bool assert_running_global(const char * pszAppName, const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName, const char * pszId = NULL);

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

      virtual void on_allocation_error(sp(::ca2::application) papp, sp(::ca2::type_info) info);

      // file & dir
      virtual string matter_as_string(sp(::ca2::application) papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual string dir_matter(sp(::ca2::application) papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(sp(::ca2::application) papp, const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);

      class ::ca2::factory                 & factory();
      class ::ca2::log                     & log();

      sp(::ca2::window_draw )              get_twf();

      FT_Library                          & ftlibrary();

      ::ca2::application_ptra              & appptra();
      ::ca2::datetime                      & datetime();

      inline ::ca2::file_system            & file()    { return m_spfile; }
      inline ::ca2::dir::system            & dir()     { return m_spdir; }
      ::ca2::stra                          & stra();
      inline ::ca2::url                    & url()     { return m_url; }
      ::xml::xml                          & xml();
      ::ca2::install                       & install();
      ::ca2::service                       & service();
      class ::machine_event_central       & machine_event_central();
      class ::ca2::os                      & os();
#ifndef METROWIN
      ::ca2::process_section               & process();
#endif
      class ::sockets::net                & net();

      ::ca2::history                    & hist();

      class ::ca2::compress            & compress();
      class ::ca2::patch               & patch();
      class ::ca2::crypt               & crypt();
      class ::ca2::http::system        & http();
      class ::ca2::email               & email();
      class ::ca2::copydesk            & copydesk();

      ::fontopus::user_set             & userset();

      ::user::str                      & str();

      ::filehandler::handler           & filehandler();

      ::colorertake5::ParserFactory    & parser_factory();

      static ::exception::engine       & eengine();
      inline class ::visual::visual             & visual()     { return m_visual       ; }






      bool sync_load_url(string & str, const char * lpszUrl, ::fontopus::user * puser = NULL, ::http::cookies * pcookies = NULL);




      uint32_t guess_code_page(const char * pszText);

#ifdef METROWIN

      virtual bool get_window_rect(LPRECT lprect);

#endif

      virtual void post_fork_uri(const char * pszUri, ::ca2::application_bias * pbiasCreate);


      //      sp(::plane::session) get_session(index iEdge, ::ca2::application_bias * pbiasCreation = NULL);
      sp(::plane::session) query_session(index iEdge);


      //static void register_delete(sp(::ca2::ca2) plistened, sp(::ca2::ca2) plistener);
      //static void unregister_delete(sp(::ca2::ca2) plistened, sp(::ca2::ca2) plistenerOld);

      virtual bool wait_twf(uint32_t dwTimeOut = INFINITE);

      template < class T >
      sp(::ca2::type_info) type_info()
      {
         return get_type_info(typeid(T));
      }

      virtual sp(::ca2::type_info) get_type_info(const ::std_type_info & info);
      sp(::ca2::type_info) get_type_info(const class id & idType)
      {
         return m_typemap[idType];
      }

      void set_enum_name(sp(::ca2::type_info) etype, int32_t i, const char * psz)
      {
         m_mapEnumToName[etype->name()][i] = psz;
         m_mapNameToEnum[etype->name()][psz] = i;
      }
      string get_enum_name(sp(::ca2::type_info) info, int32_t i)
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
      ENUM enum_from_name(sp(::ca2::type_info) info, const char * psz, int32_t iDefault = 0)
      {
         return (ENUM) m_mapNameToEnum[info->name()].get(psz, iDefault);
      }
      int32_t enum_from_name(sp(::ca2::type_info) info, const char * psz, int32_t iDefault = 0)
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
      void set_enum_name(sp(::ca2::type_info) etype, TYPE e, const char * psz)
      {
         set_enum_name(etype, (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(sp(::ca2::type_info) etype, TYPE e)
      {
         return get_enum_name(etype, (int32_t) e);
      }

      template < class TYPE >
      void set_enum_name(const std_type_info & info, TYPE e, const char * psz)
      {
         set_enum_name(get_type_info(info), (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(const std_type_info & info, TYPE e)
      {
         return get_enum_name(get_type_info(info), (int32_t) e);
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

      virtual void discard_to_factory(sp(::ca2::ca2) pca);

      virtual bool verb();

      virtual sp(::ca2::application) get_new_app(sp(::ca2::application) pappNewApplicationParent, const char * pszType, const char * pszId);

      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache();
      virtual bool map_application_library(const char * pszLibrary);


      //////////////////////////////////////////////////////////////////////////////////////////////////
      // System/System
      //
      sp(::user::document) hold(sp(::user::interaction) pui);

      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index i, LPRECT lprect);
      virtual index get_best_intersection_monitor(LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index i, LPRECT lprect);

      //virtual sp(::ca2::command_thread) command_thread();


      virtual bool on_install();

      virtual string get_fontopus_server(const char * pszUrl, sp(::ca2::application) papp, int32_t iRetry = -1);

      virtual string get_host_location_url();

      virtual bool add_library(::ca2::library * plibrary);

      virtual void get_cursor_pos(LPPOINT lppoint);


      virtual bool set_main_init_data(::ca2::main_init_data * pdata);


      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif


   };


   //CLASS_DECL_ca2 class heap_item_array * get_heap_itema();

   //CLASS_DECL_ca2 void set_heap_itema(class heap_item_array * pitema);


} // namespace cube


namespace ca2
{





} // namespace ca2


#if defined(LINUX) || defined(MACOS)


template < class T >
bool ::ca2::file_system::output(sp(::ca2::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca2::writer &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::ca2::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca2::file::mode_create | ::ca2::file::type_binary | ::ca2::file::mode_write);

   if(fileOut.is_null())
      return false;

   return (p->*lpfnOuput)(fileOut, lpszSource);

}


template < class T >
bool ::ca2::file_system::output(sp(::ca2::application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::ca2::writer &, ::ca2::reader &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::ca2::filesp fileOut = App(papp).file().get_file(pszOutput, ::ca2::file::mode_create | ::ca2::file::type_binary | ::ca2::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::ca2::filesp fileIn = App(papp).file().get_file(lpszInput, ::ca2::file::type_binary | ::ca2::file::mode_read);

   if(fileIn.is_null())
      return false;

   return (p->*lpfnOuput)(fileOut, fileIn);

}

#endif // defined LINUX









































#include "base/collection/collection_lemon_array.h"


namespace user
{


   template < class VIEW >
   inline sp(VIEW) view::create_view(::user::document_interface * pdoc, sp(::user::interaction) pwndParent, id id, sp(::user::interaction) pviewLast)
   {
      return create_view(System.type_info < VIEW > (), pdoc, pwndParent, id, pviewLast);
   }


   template < class VIEW >
   inline sp(VIEW) view::create_view(::user::interaction * pwndParent, id id, sp(::user::interaction) pviewLast)
   {
      return create_view < VIEW > (NULL, pwndParent, id, pviewLast);
   }

   template < class VIEW >
   inline sp(VIEW) view::create_view(::user::view_creator_data * pcreatordata, sp(::user::interaction) pviewLast)
   {

      VIEW * pview = create_view < VIEW > (pcreatordata->m_pholder, pcreatordata->m_id, pviewLast);

      if(pview != NULL)
      {
         pcreatordata->m_pdoc = get_document();
      }

      return pview;

   }



   template < class DOCUMENT >
   ::ca2::data * view::get_data()
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


} //   namespace user

namespace xml
{

   inline disp_option::disp_option(sp(::ca2::application) papp)
   {
      newline = true;
      reference_value = true;
      m_pentities = &papp->m_psystem->m_pxml->m_entities;
      tab_base = 0;
      value_quotation_mark = '"';
   }


} // namespace xml


