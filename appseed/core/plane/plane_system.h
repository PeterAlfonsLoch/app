#pragma once


//#ifndef WINDOWS
//#define INFINITE 0xffffffff
//#endif

#ifdef WINDOWS
interface ID2D1DeviceContext;
#endif

#ifdef METROWIN

#include <agile.h>

#endif

class id;






namespace plane
{



   class CLASS_DECL_ca2 system :
      virtual public ::plane::application,
      virtual public ::core::system
   {
   public:
      //plane::session::run_start_installer *        m_prunstartinstaller;
      //plane::session::map *                        m_pbergedgemap;
      index                                        m_iNewEdge;
      class machine_event_central *                m_pmachineeventcentral;

      mutex                                        m_mutex;
#ifdef METROWIN
      sp(::user::interaction)                      m_pui;
      ::core::system_window ^                       m_pwindow;
#endif
#ifdef WINDOWS
      ID2D1DeviceContext *                         m_pdevicecontext;
      sp(mutex)                                    m_pmutexDc;
#endif
      sp(::filehandler::handler)                   m_spfilehandler;


      FT_Library                                   m_ftlibrary;
      mutex                                        m_mutexDelete;
      application_ptra                       m_appptra;
      ::core::file_system_sp                         m_spfile;
      ::core::dir::system_sp                         m_spdir;
      class ::core::stra                             m_stra;
      class ::core::service                          m_service;
      class ::core::install                          m_install;
      ::core::os_sp                                  m_spos;
#ifndef METROWIN
      class ::core::process_section                  m_processsection;
#endif
      sp(class ::core::datetime)                     m_pdatetime;
      class ::sockets::net                         m_net;

      class ::core::compress                         m_compress;
      class ::core::patch                            m_patch;
      ::core::crypt_sp                               m_spcrypt;
      class ::core::http::system                     m_http;
      class ::core::email                            m_email;
      ::core::copydesk_sp                            m_spcopydesk;
      ::core::port_forward_sp                        m_spportforward;
      ::string_to_string                       m_mapAppLibrary;
      sp(colorertake5::ParserFactory)              m_pparserfactory;


      class ::fontopus::user_set                   m_userset;
      string_to_string                         m_mapFontopusServer;


      sp(::plane::session::run_start_installer)      m_prunstartinstaller;
      sp(::plane::session::map)                      m_pbergedgemap;


      sp(class ::core::log)                          m_plog;
      sp(class ::core::history)                      m_phistory;
      sp(::core::window_draw)                        m_ptwf;
      //      ::sockets::net                               m_net;
      //      sp(::core::filehandler::handler)  m_spfilehandler;


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
       
       ::ca::library m_libraryDraw2d;
       
       
       
       

      string_map < int_map < string, string >, const int_map < string, string > & >
         m_mapEnumToName;

      string_map < string_map < int32_t, int32_t >, const string_map < int32_t, int32_t > & >
         m_mapNameToEnum;


      bool                                          m_bDoNotExitIfNoApplications;

      strid_map < ::core::library * >  m_idmapCreateViewLibrary;

      comparable_array < ::core::library * >         m_libraryptra;

#ifdef METROWIN
      Platform::Agile < Windows::UI::Core::CoreWindow > m_window;
#endif

      ::visual::visual                    m_visual;

      system(sp(base_application) papp = NULL);
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

      virtual index get_new_bergedge(application_bias * pbiasCreation = NULL);

      virtual void register_bergedge_application(sp(base_application) papp);
      virtual void unregister_bergedge_application(sp(base_application) papp);


      virtual bool base_support();


      DECL_GEN_SIGNAL(on_application_signal);


      using ::plane::application::process;
      bool set_history(::core::history * phistory);


      virtual sp(::plane::session)             get_session(index iEdge, application_bias * pbiasCreation = NULL);
      virtual sp(::platform::document)             get_platform(index iEdge, application_bias * pbiasCreation = NULL);
      virtual sp(::nature::document)               get_nature(index iEdge, application_bias * pbiasCreation = NULL);

      virtual sp(::plane::session)             query_bergedge(index iEdge);
      virtual void on_request(sp(create_context) pcreatecontext);
      virtual sp(base_application) application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);
      virtual void open_by_file_extension(index iEdge, const char * pszPathName);
      virtual bool is_system();

      virtual sp(command_thread) command_thread();





      //virtual int32_t main();



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

      virtual void on_allocation_error(sp(base_application) papp, sp(type) info);

      // file & dir
      virtual string matter_as_string(sp(base_application) papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual string dir_matter(sp(base_application) papp, const char * pszMatter, const char * pszMatter2 = NULL);
      virtual bool is_inside_time_dir(const char * pszPath);
      virtual bool file_is_read_only(const char * pszPath);
      virtual string file_as_string(sp(base_application) papp, const char * pszPath);
      virtual string dir_path(const char * psz1, const char * psz2, const char * psz3 = NULL);
      virtual string dir_name(const char * psz);
      virtual bool dir_mk(const char * psz);
      virtual string file_title(const char * psz);
      virtual string file_name(const char * psz);

      class ::core::log                     & log();

      sp(::core::window_draw )              get_twf();

      FT_Library                          & ftlibrary();

      application_ptra              & appptra();
      ::core::datetime                      & datetime();

      inline ::core::file_system            & file()    { return m_spfile; }
      inline ::core::dir::system            & dir()     { return m_spdir; }
      ::core::stra                          & stra();
      ::core::install                       & install();
      ::core::service                       & service();
      class ::machine_event_central       & machine_event_central();
      class ::core::os                      & os();
#ifndef METROWIN
      ::core::process_section               & process();
#endif
      class ::sockets::net                & net();

      ::core::history                    & hist();

      class ::core::compress            & compress();
      class ::core::patch               & patch();
      class ::core::crypt               & crypt();
      class ::core::http::system        & http();
      class ::core::email               & email();
      class ::core::copydesk            & copydesk();

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

      virtual void post_fork_uri(const char * pszUri, application_bias * pbiasCreate);


      //      sp(::plane::session) get_session(index iEdge, application_bias * pbiasCreation = NULL);
      sp(::plane::session) query_session(index iEdge);


      //static void register_delete(sp(element) plistened, sp(element) plistener);
      //static void unregister_delete(sp(element) plistened, sp(element) plistenerOld);

      virtual bool wait_twf(uint32_t dwTimeOut = INFINITE);


      void set_enum_name(sp(type) etype, int32_t i, const char * psz)
      {
         m_mapEnumToName[etype->name()][i] = psz;
         m_mapNameToEnum[etype->name()][psz] = i;
      }
      string get_enum_name(sp(type) info, int32_t i)
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
      ENUM enum_from_name(sp(type) info, const char * psz, int32_t iDefault = 0)
      {
         return (ENUM) m_mapNameToEnum[info->name()].get(psz, iDefault);
      }
      int32_t enum_from_name(sp(type) info, const char * psz, int32_t iDefault = 0)
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
      void set_enum_name(sp(type) etype, TYPE e, const char * psz)
      {
         set_enum_name(etype, (int32_t) e, psz);
      }
      template < class TYPE >
      string get_enum_name(sp(type) etype, TYPE e)
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

      virtual void discard_to_factory(sp(element) pca);

      virtual bool verb();

      virtual sp(base_application) get_new_app(sp(base_application) pappNewApplicationParent, const char * pszType, const char * pszId);

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

      //virtual sp(command_thread) command_thread();


      virtual bool on_install();

      virtual string get_fontopus_server(const char * pszUrl, sp(base_application) papp, int32_t iRetry = -1);

      virtual string get_host_location_url();

      virtual bool add_library(::core::library * plibrary);

      virtual void get_cursor_pos(LPPOINT lppoint);


      virtual bool set_main_init_data(::core::main_init_data * pdata);


      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif

      virtual UINT os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam);


   };


   //CLASS_DECL_ca2 class heap_item_array * get_heap_itema();

   //CLASS_DECL_ca2 void set_heap_itema(class heap_item_array * pitema);


} // namespace cube


namespace core
{





} // namespace core


#if defined(LINUX) || defined(MACOS)


template < class T >
bool ::core::file_system::output(sp(base_application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::writer &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(pszOutput, ::file::binary_buffer::mode_create | ::file::type_binary | ::file::binary_buffer::mode_write);

   if(fileOut.is_null())
      return false;

   return (p->*lpfnOuput)(fileOut, lpszSource);

}


template < class T >
bool ::core::file_system::output(sp(base_application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::writer &, ::file::reader &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));
   
   string strDownloading = pszOutput;
   
   strDownloading += ".downloading";

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(strDownloading, ::file::binary_buffer::mode_create | ::file::type_binary | ::file::binary_buffer::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::binary_buffer_sp fileIn = App(papp).file().get_file(lpszInput, ::file::type_binary | ::file::mode_read);

   if(fileIn.is_null())
      return false;

   if(!(p->*lpfnOuput)(fileOut, fileIn))
      return false;
   
   if(::rename(strDownloading, pszOutput) != 0)
   {
      del(strDownloading);
      return false;
   }
   
   return true;

}

#endif // defined LINUX









































#include "core/collection/collection_lemon_array.h"


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
   ::data * view::get_data()
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

