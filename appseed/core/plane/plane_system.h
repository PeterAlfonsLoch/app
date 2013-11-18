#pragma once


#ifdef WINDOWS

interface ID2D1DeviceContext;

#endif

#ifdef METROWIN

#include <agile.h>

#endif

class id;

namespace plane
{


   class CLASS_DECL_CORE system :
      virtual public ::plane::application,
      virtual public ::core::system
   {
   public:


      //plane::session::run_start_installer *        m_prunstartinstaller;
      //plane::session::map *                        m_pbergedgemap;
      index                                        m_iNewEdge;

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
      class ::core::stra                             m_stra;
      class ::core::service                          m_service;
      class ::core::install                          m_install;
      ::core::os_sp                                  m_spos;
#ifndef METROWIN
      class ::core::process_departament              m_processsection;
#endif

      class ::core::compress                         m_compress;
      class ::core::patch                            m_patch;
      ::net::email_departament                        m_emaildepartament;
      ::core::copydesk_sp                            m_spcopydesk;
      sp(colorertake5::ParserFactory)              m_pparserfactory;

      ::net::port_forward_sp                        m_spportforward;

      sp(::plane::session::run_start_installer)      m_prunstartinstaller;
      sp(::plane::session::map)                      m_pbergedgemap;


      sp(class ::core::log)                          m_plog;
      sp(class ::core::history)                      m_phistory;
      //      ::sockets::net                               m_net;
      //      sp(::core::filehandler::handler)  m_spfilehandler;


      // certain instantiators like npca2plugin and iexca2plugin rely
      // on the functionality of these variables cached information,
      // to avoid multiple initialization.
      bool                                         m_bInitApplication;
      bool                                         m_bInitApplicationResult;
      bool                                         m_bProcessInitialize;
      bool                                         m_bProcessInitializeResult;


      bool                                         m_bLibCharGuess;

      sp(::user::str)                              m_puserstr;

       ::boot::library m_libraryDraw2d;





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
      virtual void on_request(sp(::create_context) pcreatecontext);
      virtual sp(base_application) application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate = true, bool bSynch = true, application_bias * pbiasCreate = NULL);
      virtual void open_by_file_extension(index iEdge, const char * pszPathName);
      virtual bool is_system();

//      virtual sp(::command_thread) command_thread();





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

      FT_Library                             & ftlibrary();

      application_ptra                       & appptra();

      ::core::stra                           & stra();
      ::core::install                        & install();
      ::core::service                        & service();
      class ::core::os                       & os();
#ifndef METROWIN
      ::core::process_departament            & process();
#endif
      ::core::history                        & hist();

      class ::core::patch                    & patch();
      class ::core::copydesk                 & copydesk();

      ::http::system                         & http();
      ::net::email_departament               & email();

      ::user::str                            & str();

      ::filehandler::handler                 & filehandler();

      ::colorertake5::ParserFactory          & parser_factory();

      static ::exception::engine             & eengine();
      inline class ::visual::visual          & visual()     { return m_visual       ; }






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


      virtual bool create_twf();

      //virtual void discard_to_factory(sp(element) pca);

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

      //virtual sp(::command_thread) command_thread();


      virtual bool on_install();

      virtual string get_host_location_url();

      virtual bool add_library(::core::library * plibrary);

      virtual void get_cursor_pos(LPPOINT lppoint);


      virtual bool set_main_init_data(::core::main_init_data * pdata);


      void enum_display_monitors();

#if defined(WINDOWS)

      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);

      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);

#endif

      void assert_valid() const;
      void dump(dump_context & context) const;


      virtual UINT os_post_to_all_threads(UINT uiMessage, WPARAM wparam, lparam lparam);


   };


} // namespace plane



#if defined(LINUX) || defined(MACOS)


template < class T >
bool ::file::system::output(sp(base_application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, const char *), const char * lpszSource)
{

   App(papp).dir().mk(System.dir().name(pszOutput));

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(pszOutput, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::output_stream ostream(fileOut);

   return (p->*lpfnOuput)(ostream, lpszSource);

}


template < class T >
bool ::file::system::output(sp(base_application) papp, const char * pszOutput, T * p, bool (T::*lpfnOuput)(::file::output_stream &, ::file::input_stream &), const char * lpszInput)
{

   App(papp).dir().mk(System.dir().name(pszOutput));
   
   string strDownloading = pszOutput;

   strDownloading += ".downloading";

   ::file::binary_buffer_sp fileOut = App(papp).file().get_file(strDownloading, ::file::mode_create | ::file::type_binary | ::file::mode_write);

   if(fileOut.is_null())
      return false;

   ::file::binary_buffer_sp fileIn = App(papp).file().get_file(lpszInput, ::file::type_binary | ::file::mode_read);

   if(fileIn.is_null())
      return false;
   
   {

      ::file::output_stream ostream(fileOut);

      ::file::input_stream istream(fileIn);

      if(!(p->*lpfnOuput)(ostream, istream))
         return false;
      
   }
   
   try
   {
      
      fileOut->close();
      
   }
   catch(...)
   {
      
   }
   
   
   try
   {
      
      fileIn->close();
      
   }
   catch(...)
   {
      
   }

   if(::rename(strDownloading, pszOutput) != 0)
   {
      del(strDownloading);
      return false;
   }

   return true;

}

#endif // defined LINUX









































//#include "core/collection/collection_array.h"


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
   ::data::data * view::get_data()
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

