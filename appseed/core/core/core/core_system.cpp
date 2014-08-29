#include "framework.h"
#include "charguess.h"



#ifdef WINDOWS
#undef new
//#include <GdiPlus.h>
#define new AURA_NEW
#endif



namespace core
{


   system::system(sp(::aura::application) papp):
      ::element(papp),
      ::aura::system(papp),
      ::axis::system(papp),
      ::base::system(papp),
      m_mutexDelete(this),
      m_mutex(this),
      m_emaildepartament(this)
   {

#ifdef METROWIN
         m_window                                  = nullptr;
#endif

         m_pcoresystem                            = this;
         set_app(this);


         if(papp == NULL)
         {

            oprop("parent_system") = (sp(element)) NULL;

         }
         else
         {

            oprop("parent_system") = papp->m_pcoresystem;

         }

         m_bDoNotExitIfNoApplications              = true;

         string strId;
         //strId = m_strAppName;
         //strId += ::str::has_char(m_strAppId, ".");
         //strId += ::str::has_char(m_strBaseSupportId, ".");




         /*
         if(psystemParent == NULL)
         {

         m_peengine                                = new ::exception::engine(this);

         }
         else
         {

         m_peengine                                = psystemParent->m_peengine;

         }
         */






         m_stra.set_app(this);
         //      m_url.set_app(this);
         m_userset.set_app(this);
         m_service.set_app(this);
         m_pdatetime = new class ::datetime::departament(this);
         //      m_email.set_app(this);






         m_bInitApplication         = false;
         m_bInitApplicationResult   = FALSE;
         m_bProcessInitialize       = false;
         m_bProcessInitializeResult = false;

         m_puserstr                 = NULL;

         m_pparserfactory           = NULL;

         m_bLicense                 = false;

         m_prunstartinstaller       = NULL;
         m_bLicense                 = false;
         m_strAppName               = "system";
         m_strInstallToken          = "system";


      }


   system::~system()
   {

   }



   void system::construct(const char * pszAppId)
   {

      ::core::application::construct(pszAppId);

      ::base::system::construct(pszAppId);

   }




   void system::discard_to_factory(sp(element) pca)
   {
      UNREFERENCED_PARAMETER(pca);
   }


   bool system::is_system()
   {

      return true;

   }

   bool system::initialize2()
   {

      if(!::core::application::initialize2())
         return false;

      if(!::base::system::initialize2())
         return false;

      return true;

   }


   bool system::InitApplication()
   {

      if(m_bInitApplication)
         return m_bInitApplicationResult;

      m_bInitApplicationResult      = FALSE;
      m_bInitApplication            = true;

      m_bInitApplicationResult = ::core::application::InitApplication();

      return m_bInitApplicationResult;
   }


   bool system::process_initialize()
   {



      if(m_bProcessInitialize)
         return m_bProcessInitializeResult;

      m_bProcessInitializeResult    = false;
      m_bProcessInitialize          = true;

      if(!::core::application::process_initialize())
         return false;

      if(!::base::system::process_initialize())
         return false;




      ::core::profiler::initialize();


      //      System.factory().creatable < ::base::log >(System.type_info < ::base::log > (), 1);

      /*      if(!::core::application::process_initialize())
      {
      return false;
      }*/



      m_spportforward.alloc(allocer());


      m_phtml = create_html();

      m_phtml->add_ref();

      if(m_phtml == NULL)
         return false;

      m_phtml->construct(this);


      m_bProcessInitializeResult = true;
      return true;
   }


   bool system::initialize()
   {

      if(!m_visual.initialize())
         return false;



#ifndef APPLEOS

      if(m_pparserfactory == NULL)
      {



      }

#endif


      if(!::core::application::initialize())
         return false;

      return true;
   }



   bool system::initialize1()
   {



      m_visual.construct(this);

      if(!m_visual.initialize1())
         return false;



      m_spfilehandler = new ::filehandler::handler(this);




      if(!::core::application::initialize1())
         return false;


      //if(Session.fontopus()->create_system_user("system") == NULL)
      // return false;


      m_puserstr = new ::user::str(this);
      if(m_puserstr == NULL)
         return false;

      if(!str().initialize())
         return false;


#if !defined(DEBUG) || defined(WINDOWS)
      try
      {
#endif
         find_applications_from_cache();
#if !defined(DEBUG) || defined(WINDOWS)
      }
      catch(...)
      {
      }
#endif

      if(!m_phtml->initialize())
         return false;



      return true;

   }


   bool system::find_applications_from_cache()
   {

      m_spfilehandler->m_sptree->remove_all();

      if(directrix()->m_varTopicQuery.has_property("install"))
         return true;

      ::file::binary_buffer_sp file = Session.m_file.get_file(System.dir().appdata("applibcache.bin"),::file::type_binary | ::file::mode_read);

      if(file.is_null())
         return false;

      ::file::byte_input_stream is(file);

      is >> m_mapAppLibrary;

      is >> *m_spfilehandler.m_p;

      return true;

   }


   ::filehandler::handler & system::filehandler()
   {

      return *m_spfilehandler;

   }




   bool system::find_applications_to_cache()
   {

      /*      m_spfilehandler(new ::core::filehandler::handler(this));*/

      m_mapAppLibrary.remove_all();

      string strLibraryId;
      stringa straTitle;

      Application.dir().ls_pattern(System.dir().ca2module(),"*.*",NULL,& straTitle);

      for(int32_t i = 0; i < straTitle.get_count(); i++)
      {

         strLibraryId = straTitle[i];

         if(::str::ends_eat_ci(strLibraryId,".dll")
            || ::str::ends_eat_ci(strLibraryId,".so")
            || ::str::ends_eat_ci(strLibraryId,".dylib"))
         {

            if(::str::begins_ci(strLibraryId,"libdraw2d_")
               || ::str::begins_ci(strLibraryId,"libbase"))
            {
               continue;
            }

            map_application_library(strLibraryId);

         }

      }

      ::file::binary_buffer_sp file;

      try
      {

         file = Session.m_file.get_file(System.dir().appdata("applibcache.bin"),::file::defer_create_directory | ::file::type_binary | ::file::mode_create | ::file::mode_write);

      }
      catch(::exception::base &)
      {

         return false;

      }

      ::file::byte_output_stream os(file);

      os << m_mapAppLibrary;

      os << *m_spfilehandler.m_p;

      return true;

   }

   bool system::map_application_library(const char * pszLibrary)
   {

      ::aura::library library(this,0, NULL);

      if(!strcmp(pszLibrary,"app_core_rdpclient"))
      {
         TRACE("reach");
      }

      if(!stricmp_dup(pszLibrary,"app_core_hellomultiverse"))
      {
         TRACE("reach app_core_hellomultiverse");
      }

      if(!stricmp_dup(pszLibrary,"wndfrm_core"))
      {
         TRACE("reach wndfrm_core");
      }

      if(!stricmp_dup(pszLibrary,"app_core_hellomultiverse"))
      {
         TRACE("reach app_core_hellomultiverse");
      }

      if(!library.open(pszLibrary,true))
         return false;

      if(!library.open_ca2_library())
         return false;

      m_spfilehandler->defer_add_library(library.m_pca2library);

      stringa stra;

      string strRoot = library.get_root();

      library.get_app_list(stra);

      if(stra.get_count() <= 0)
         return false;

      strRoot += "/";

      if(stra.get_count() == 1)
      {

         m_mapAppLibrary.set_at(strRoot + stra[0],pszLibrary);

      }

      string strLibrary(pszLibrary);

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      if(strLibrary == "libbase")
      {

         strLibrary = "base";

      }
      else if(!::str::begins_eat(strLibrary,"libbase"))
      {

         ::str::begins_eat(strLibrary,"lib");

      }

#endif

      string strPrefix = strRoot;

      strPrefix.replace("-","_");

      strPrefix.replace("/","_");

      ::str::begins_eat_ci(strLibrary,strPrefix);

      strRoot += strLibrary;

      strRoot += "/";

      for(int32_t i = 0; i < stra.get_count(); i++)
      {

         m_mapAppLibrary.set_at(strRoot + stra[i],pszLibrary);

      }

      return true;

   }



   bool system::initialize3()
   {

      if(!::core::application::initialize3())
         return false;

      if(m_phistory == NULL)
      {
         m_phistory = new os_history(this);
      }

      return true;
   }

   bool system::initialize_instance()
   {

      if(!::base::system::initialize_instance())
      {
         return false;
      }

      /*set_enum_name(var::type_null      , "NULL");
      set_enum_name(var::type_empty     , "is_empty");
      set_enum_name(var::type_string    , "string");
      set_enum_name(var::type_int32   , "integer");
      set_enum_name(var::type_uint32     , "ulong");
      set_enum_name(var::type_element       , "ca2");
      set_enum_name(var::type_bool      , "bool");
      set_enum_name(var::type_double    , "double");*/



      if(!::core::application::initialize_instance())
         return false;

      m_pbergedgemap = new ::core::platform::map;



      return true;

   }


   bool system::bergedge_start()
   {
      return true;
   }

   bool system::verb()
   {

      static uint32_t dwStart = ::get_tick_count();

      if(directrix()->m_varTopicQuery.has_property("install") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(directrix()->m_varTopicQuery.has_property("uninstall") && (get_tick_count() - dwStart) > (5 * 184 * 1000))
         return false;

      if(!m_bDoNotExitIfNoApplications)
      {

         ::aura::application_ptra appptra;

         appptra = get_appptra();

         for(int32_t i = 0; i < appptra.get_size();)
         {

            try
            {

               if(&appptra[i]==NULL || appptra[i].is_session() || appptra[i].is_system())
               {

                  appptra.remove_at(i);

                  continue;

               }
               else if(appptra[i].is_serviceable() && appptra[i].m_strAppId != directrix()->m_varTopicQuery["app"].get_string())
               {

                  appptra.remove_at(i);

                  continue;

               }

            }
            catch(...)
            {

               appptra.remove_at(i);

               continue;

            }

            i++;

         }

         if(appptra.get_size() <= 0)
         {

            return false;

         }

         if(appptra.get_size() == 1 && appptra.contains(this))
         {

            return false;

         }

      }

      return ::core::application::verb();
      

   }


   int32_t system::exit_instance()
   {

      __wait_threading_count(::millis((5000) * 8));



      int32_t iRet = 0;


      try
      {

         iRet = ::base::system::exit_instance();

      }
      catch(...)
      {

      }



      try
      {
         m_spportforward.release();
      }
      catch(...)
      {
      }



      try
      {
         if(m_spos.is_set())
         {
            m_spos.release();
         }
      }
      catch(...)
      {
      }
      try
      {
         m_spdir.release();
      }
      catch(...)
      {
      }


      try
      {
         m_spos.release();
      }
      catch(...)
      {
      }
      try
      {
         m_spdir.release();
      }
      catch(...)
      {
      }


      m_plog.release();

      m_typemap.remove_all();

      m_typemap.release();


      return iRet;
   }

   /*
   sp(element) system::on_alloc(sp(::aura::application) papp, sp(type) info)
   {
   /*string str;
   str.Format("Could not alloc %s", info.name());
   simple_message_box(str);*/
   /*sp(element) pobj = Sys(papp).factory().create(papp, info);
   if(pobj != NULL)
   return pobj;
   on_allocation_error(papp, info);
   return NULL;
   }
   */


   sp(::aura::session) system::query_session(index iEdge)
   {

      sp(::core::platform) pbergedge = NULL;

      if(m_pbergedgemap == NULL)
         return NULL;

      if(!m_pbergedgemap->Lookup(iEdge,pbergedge))
      {

         return NULL;

      }

      return pbergedge;

   }


   sp(::core::platform) system::get_session(index iEdge,application_bias * pbiasCreation)
   {
      sp(::core::platform) pbergedge = NULL;
      if(m_pbergedgemap == NULL)
         return NULL;
      if(!m_pbergedgemap->Lookup(iEdge,pbergedge))
      {
         pbergedge = create_application("application","session",true,pbiasCreation);
         if(pbergedge == NULL)
            return NULL;
         pbergedge->m_iEdge = iEdge;
         m_pbergedgemap->set_at(iEdge,pbergedge);
      }
      return pbergedge;
   }


   ::core::history & system::hist()
   {
      return *m_phistory;
   }


   bool system::set_history(::core::history * phistory)
   {
      m_phistory = phistory;
      return true;
   }

   ::core::stra & system::stra()
   {
      return m_stra;
   }

   ::core::service & system::service()
   {
      return m_service;
   }




   bool system::finalize()
   {

      bool bOk = true;

      if(!::base::system::finalize())
      {

         bOk = false;

      }

      return bOk;

   }



   void system::on_allocation_error(sp(::aura::application) papp,sp(type) info)
   {

      UNREFERENCED_PARAMETER(papp);

      App(papp).simple_message_box(NULL,MB_ICONINFORMATION,"Implement \"%s\" allocation\n",info->friendly_name());

   }



   bool system::wait_twf(uint32_t dwTimeOut)
   {
      if(dwTimeOut > 1984)
         dwTimeOut = 1984;
      if(m_ptwf != NULL && m_ptwf->m_bProDevianMode)
      {
         return m_ptwf->m_eventFree.wait(millis(dwTimeOut)).signaled();
      }
      /*else if(m_puiInitialPlaceHolderContainer != NULL)
      {
      #define InitialPlaceHolderContainer_TWF_FREE_EVENT 2010
      return App(this).event_lock(m_puiInitialPlaceHolderContainer, InitialPlaceHolderContainer_TWF_FREE_EVENT, dwTimeOut);
      }*/
      else
      {
         return true;
      }
   }

   void system::on_request(sp(::create_context) pcreatecontext)
   {

      sp(::core::platform) psession = get_session(pcreatecontext->m_spCommandLine->m_iEdge,pcreatecontext->m_spCommandLine->m_pbiasCreate);

      if(psession == NULL)
      {

         ::simple_message_box(get_splash(),"An error that prevents the application from starting has occurred.\r\n\r\nPlease run app-removal.exe and restart the application, or contact the administrator.","Startup Error",MB_ICONEXCLAMATION);

#ifdef WINDOWS

         ::ExitProcess(-17);

#endif

         return;

      }

      psession->request_create(pcreatecontext);

   }


   bool system::sync_load_url(string & str,const char * lpszUrl,::fontopus::user * puser,::http::cookies * pcookies)
   {
      string filename = System.file().time_square(get_app());
      property_set set;
      set["user"] = puser;
      set["cookies"] = pcookies;
      if(!http().download(lpszUrl,filename,set))
         return false;

      string strLocation = set["get_headers"]["Location"];

      if(strLocation.has_char())
      {

         property_set set;

         set["user"] = puser;

         set["cookies"] = pcookies;

         file().del(filename);

         return http().download(str,strLocation,set);

      }

      str = Application.file().as_string(filename);

      return true;

      /*   Parse pa(lpszUrl,":/");
      string protocol = pa.getword();
      string host = pa.getword();
      int32_t port;
      {
      Parse pa((const char *) host,":");
      pa.getword();
      port = pa.getvalue();
      }
      string url = "/";
      url += pa.getrest();
      string filename = System.file()time_square();

      bool bOk = false;
      bool bRead = false;
      if (protocol == "http" || protocol == "https")
      {
      socket_handler h;
      string strFilename;
      SpaHttpGet s(h, lpszUrl, "");
      if(pcookies != NULL)
      {
      string strCookie;
      for(int32_t i = 0; i < pcookies->get_size(); i++)
      {
      strCookie += (const char *) (pcookies->element_at(i).m_strName + "=" + pcookies->element_at(i).m_strValue);
      strCookie += ";";
      }
      s.AddResponseHeader("Cookie", strCookie);
      }
      s.m_pcookies = pcookies;
      //s.SetLineProtocol(false);
      s.SetFilename((const char *) filename);
      h.add(&s);
      h.Select(1,0);
      while (h.get_count())
      {
      h.Select(1,0);
      }
      bool bOk = s.Complete();
      if(!s.m_strHeaderLocation.is_empty())
      {
      ::DeleteFile(filename);
      sync_load_url(str, s.m_strHeaderLocation, pcookies);
      }
      else
      {
      bRead = true;
      }
      }
      else
      {
      printf("Unknown protocol: '%s'\n", protocol);
      }
      if(bRead)
      {
      int32_t iMaxpath = MAX_PATH;
      int32_t iLen = strlen(filename);
      gzFile gzf = gzopen(filename, "rb");
      int32_t iRead;
      ::file::memory_buffer memfile;
      int32_t iBufSize = (1024 * 256);
      char * buf = (char *) malloc(iBufSize);
      while((iRead = gzread(gzf, buf, iBufSize)) > 0)
      {
      memfile.write(buf, iRead);
      }
      free(buf);
      int32_t iErr;
      const char * pszErr = gzerror(gzf, &iErr);
      char ch = '\0';
      memfile.write(&ch, 1);
      str = (char *) memfile.get_data();
      ::DeleteFile(filename);
      }
      return bOk;*/
   }

   ::core::patch & system::patch()
   {
      return m_patch;
   }


   ::net::email_departament & system::email()
   {
      return m_emaildepartament;
   }

   ::http::system & system::http()
   {
      return m_httpsystem;
   }



   bool system::base_support()
   {
      return true;
   }

   index system::get_new_bergedge(application_bias * pbiasCreation)
   {
      index iNewEdge = m_iNewEdge;
      sp(::core::platform) pbergedge;
      while(m_pbergedgemap->Lookup(iNewEdge,pbergedge))
      {
         iNewEdge++;
      }
      if(get_session(iNewEdge,pbiasCreation) == NULL)
         return -1;
      m_iNewEdge = iNewEdge + 1;
      return iNewEdge;
   }



   uint32_t system::guess_code_page(const string & str)
   {

      return charguess(str)();

   }



   sp(::user::document) system::place_hold(sp(::user::interaction) pui)
   {


      //if(m_pcubeInterface != NULL)
      //{
      // return m_pcubeInterface->hold(pui);
      //}

      return NULL;

   }





   bool system::on_install()
   {

      try
      {
         xxdebug_box("system::on_install","system::on_install",0);
         if(!::core::application::on_install())
            return false;

      }
      catch(...)
      {

         return false;

      }


      try
      {

         if(!find_applications_to_cache())
            return false;

      }
      catch(...)
      {

         return false;

      }


      return true;

   }




   string system::get_host_location_url()
   {

      return "";

   }


   bool system::add_library(::aura::library * plibrary)
   {

      m_libraryptra.add(plibrary);

      ::array < ::id > ida;

      plibrary->get_create_view_id_list(ida);

      for(int32_t i = 0; i < ida.get_count(); i++)
      {

         m_idmapCreateViewLibrary.set_at(ida[i],plibrary);

      }

      return true;

   }

   

   void system::post_fork_uri(const char * pszUri,application_bias * pbiasCreate)
   {

      command()->add_fork_uri(pszUri,pbiasCreate);

      if(command()->m_varTopicQuery["locale"].array_get_count() > 0 && command()->m_varTopicQuery["locale"].stra().get_count_except_ci("_std") > 0)
      {
         Session.set_locale(command()->m_varTopicQuery["locale"].stra()[0],::action::source::user());
      }

      if(command()->m_varTopicQuery["schema"].array_get_count() > 0)
      {
         Session.set_schema(command()->m_varTopicQuery["schema"].stra()[0],::action::source::user());
      }

   }

#ifdef METROWIN

   bool system::GetWindowRect(LPRECT lprect)
   {

      Windows::Foundation::Rect rect;
      try
      {
         rect = m_posdata->m_pwindow->get_window_rect();
      }
      catch(...)
      {
         return false;
      }

      lprect->left      = (LONG)rect.X;
      lprect->top       = (LONG)rect.Y;
      lprect->right     = (LONG)(lprect->left + rect.Width);
      lprect->bottom    = (LONG)(lprect->top + rect.Height);


      return true;

   }
#endif


   bool system::set_main_init_data(::aura::main_init_data * pdata)
   {

      if(pdata != NULL)
      {
         if(!::core::application::set_main_init_data(pdata))
            return false;
      }

      if(pdata == NULL)
         return true;

      property_set set(this);

      var varFile;
      string strApp;

      set._008ParseCommandFork(pdata->m_vssCommandLine,varFile,strApp);

      if((varFile.is_empty() && ((!set.has_property("app") && !directrix()->m_varTopicQuery.has_property("appid") && !set.has_property("show_platform"))
         || set["app"] == "bergedge" || directrix()->m_varTopicQuery["appid"] == "bergedge")) &&
         !(set.has_property("install") || set.has_property("uninstall")))
      {
         if(!set.has_property("show_platform") || set["show_platform"] == 1)
         {
            command()->add_line(" : show_platform=1");
         }
      }
      else
      {
         string strCommandLine = pdata->m_vssCommandLine;
         strCommandLine.trim();
         if(strCommandLine[0] == '\"')
         {
            strsize iFind = strCommandLine.find("\"",1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         else
         {
            strsize iFind = strCommandLine.find(" ",1);
            strCommandLine = strCommandLine.Mid(iFind + 1);
         }
         command()->add_line(strCommandLine);
      }

      //if(!::core::application::set_main_init_data(pdata))
      // return false;

      return true;

   }


   /*   sp(::command_thread) system::command_thread()
   {
   return m_pcommandthread;
   }
   */

   /*   ::system::system * system::get_cube()
   {

   return this;

   }
   */


   /*   sp(::core::platform) system::get_session(index iEdge, application_bias * pbiasCreation)
   {
   sp(::core::platform) psession = NULL;
   if(m_pbergedgemap == NULL)
   return NULL;
   if(!m_pbergedgemap->Lookup(iEdge, psession))
   {
   psession = (create_application("application", "session", true, pbiasCreation));
   if(psession == NULL)
   return NULL;
   psession->m_iEdge = iEdge;
   m_pbergedgemap->set_at(iEdge, psession);
   }
   return  psession;
   }


   sp(platform::document) system::get_platform(index iEdge, application_bias * pbiasCreation)
   {
   sp(::core::platform) pbergedge = get_session(iEdge, pbiasCreation);
   return pbergedge->get_platform();
   }

   sp(nature::document) system::get_nature(index iEdge, application_bias * pbiasCreation)
   {
   sp(::core::platform) pbergedge = get_session(iEdge, pbiasCreation);
   return pbergedge->get_nature();
   }

   sp(::aura::application) system::application_get(index iEdge, const char * pszType, const char * pszId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {
   sp(::core::platform) pbergedge = get_session(iEdge, pbiasCreate);
   return pbergedge->application_get(pszType, pszId, bCreate, bSynch, pbiasCreate);
   }
   */

   void system::assert_valid() const
   {

      application::assert_valid();
      //::database::server::assert_valid();

   }


   void system::dump(dump_context & context) const
   {

      application::dump(context);
      //::database::server::dump(context);

   }




   int32_t system::main()
   {

      int iRet = ::base::system::main();

      return iRet;

   }


   spa(::core::platform) & system::planesessionptra()
   {

      return m_planesessionptra;

   }


} // namespace plane





uint32_t _thread_proc_start_core_system(void * p);



uint32_t _thread_proc_start_core_system(void * p)
{

   ::base::system * psystem = (::base::system *)p;

   ::core::system * pplanesystem = dynamic_cast < ::core::system * > (psystem);

   ::set_thread(pplanesystem);

   try
   {

      if(!pplanesystem->pre_run())
      {

         return pplanesystem->m_iReturnCode;

      }

   }
   catch(...)
   {

      return -1;

   }

   return pplanesystem->::core::system::main();

}


CLASS_DECL_CORE void __start_core_system(::base::system * psystem)
{

   ::create_thread(NULL,0,&_thread_proc_start_core_system,(LPVOID)psystem,0,0);

}
