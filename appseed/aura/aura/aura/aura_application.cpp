#include "framework.h"


#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE
#endif
#define _GNU_SOURCE
#define __USE_GNU
#include <link.h>
#elif defined(APPLEOS)
#include <dlfcn.h>
#endif




namespace aura
{
   application_signal_details::application_signal_details(sp(application) papp,class ::signal * psignal,e_application_signal esignal):
      element(papp),
      ::signal_details(psignal)
   {

         m_esignal = esignal;
         m_bOk = true;

      }

   application::application():
      m_allocer(this),
      m_mutexMatterLocator(this),
      m_mutexStr(this)
   {

      m_peventReady = NULL;


#ifdef WINDOWS

      m_hinstance                = NULL;

#endif

      if(m_pauraapp == NULL)
      {

         m_pauraapp              = this;

      }

      if(m_pauraapp != NULL)
      {

         m_paurasystem           = m_pauraapp->m_paurasystem;

         if(m_pauraapp->m_paurasession == NULL && m_paurasystem != NULL)
         {

            m_paurasession       = m_paurasystem->m_paurasession;

         }
         else
         {

            m_paurasession       = m_pauraapp->m_paurasession;

         }

#ifdef WINDOWS

         m_hinstance             = m_pauraapp->m_hinstance;

#endif

      }
      else
      {

         m_paurasystem           = NULL;

      }

      m_pcoreapp                 = NULL;

      



      m_psignal                  = canew(class signal());

      m_pcommandthread           = canew(::command_thread(this));


      m_bLicense                 = true;

      m_bAuraProcessInitialize         = false;
      m_bAuraProcessInitializeResult   = false;

      m_bAuraInitialize1               = false;
      m_bAuraInitialize1Result         = false;

      m_bAuraInitialize                = false;
      m_bAuraInitializeResult          = false;

      m_bAuraInitializeInstance        = false;
      m_bAuraInitializeInstanceResult  = false;

      m_pinitmaindata = NULL;

   }


   application::~application()
   {

   }


   void application::assert_valid() const
   {

      thread::assert_valid();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      thread::dump(dumpcontext);

#ifdef WINDOWS

      dumpcontext << "m_hinstance = " << (void *)m_hinstance;

#endif

      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_bHelpMode = " << m_strAppName;

      dumpcontext << "\n";

   }


   int32_t application::simple_message_box(::user::interaction * puiOwner,const char * pszMessage,UINT fuStyle)
   {

      return ::simple_message_box(get_safe_handle(puiOwner), pszMessage, m_strAppName, fuStyle);

   }


   int32_t application::simple_message_box(const char * pszMessage,UINT fuStyle)
   {

      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);

   }

   string application::message_box(const string & pszMatter,property_set & propertyset)
   {

      simple_message_box(pszMatter,0);

      return "";

   }

   string application::load_string(id id)
   {
      string str;
      if(!load_string(str,id))
      {
         return (const string &)id;
      }
      return str;
   }

   bool application::load_string(string & str,id id)
   {
      if(!load_cached_string(str,id,true))
      {
         return false;
      }
      return true;
   }

   bool application::load_cached_string(string & str,id id,bool bLoadStringTable)
   {
      ::xml::document doc(this);
      if(!doc.load(id))
      {
         return load_cached_string_by_id(str,id,"",bLoadStringTable);
      }
      sp(::xml::node) pnodeRoot = doc.get_root();
      if(pnodeRoot->get_name() == "string")
      {
         string strId = pnodeRoot->attr("id");
         string strValue = pnodeRoot->get_value();
         return load_cached_string_by_id(str,strId,strValue,bLoadStringTable);
      }
      str = doc.get_name();
      return true;
   }

   bool application::load_cached_string_by_id(string & str,id id,const string & pszFallbackValue,bool bLoadStringTable)
   {

      synch_lock sl(&m_mutexStr);

      string strId(*id.m_pstr);
      string strTable;
      string strString;
      string_to_string * pmap = NULL;
      index iFind = 0;
      if((iFind = strId.find(':')) <= 0)
      {
         strTable = "";
         strString = strId;
      }
      else
      {
         strTable = strId.Mid(0,iFind);
         strString = strId.Mid(iFind + 1);
      }
      if(m_stringtableStd.Lookup(strTable,pmap))
      {
         if(pmap->Lookup(strString,str))
         {
            return true;
         }
      }
      else if(m_stringtable.Lookup(strTable,pmap))
      {
         if(pmap->Lookup(strString,str))
         {
            return true;
         }
      }
      else if(bLoadStringTable)
      {
         load_string_table(strTable,"");
         return load_cached_string_by_id(str,id,pszFallbackValue,false);
      }
      if(pszFallbackValue.is_empty())
         str = strId;
      else
         str = pszFallbackValue;
      return true;
   }

   void application::load_string_table(const string & pszApp,const string & pszId)
   {

   }




   void application::load_string_table()
   {
      load_string_table("","");
   }


   sp(element) application::alloc(sp(type) info)
   {
      return System.alloc(this,info);
   }

   sp(element) application::alloc(const  id & idType)
   {
      return System.alloc(this,idType);
   }

   bool application::is_system()
   {

      return false;

   }

   bool application::is_session()
   {

      return false;

   }


   bool application::is_serviceable()
   {

      return false;

   }

   

   bool application::app_map_lookup(const char * psz,void * & p)
   {
      return m_appmap.Lookup(psz,p) != FALSE;
   }

   void application::app_map_set(const char * psz,void * p)
   {
      m_appmap.set_at(psz,p);
   }


   sp(::command_thread) application::command_central()
   {
      return m_pcommandthread;
   }

   sp(::command_thread) application::command_thread()
   {
      return m_pcommandthread;
   }

   sp(::command_thread) application::command()
   {
      return m_pcommandthread;
   }

   sp(::command_thread) application::guideline()
   {
      return m_pcommandthread;
   }

   sp(::command_thread) application::directrix()
   {
      return m_pcommandthread;
   }

   sp(::command_thread) application::axiom()
   {
      return m_pcommandthread;
   }

   bool application::verb()
   {
      axiom()->run();
      return true;
   }

   sp(::command_thread) application::creation()
   {
      return m_pcommandthread;
   }



   bool application::open_link(const string & strLink,const string & pszTarget)
   {

      if(is_system())
      {
         return open_url::start(this, strLink, pszTarget);
      }
      else
      {
         return System.open_link(strLink,pszTarget);
      }

      return false;

   }


   void application::construct(const char * pszAppId)
   {

   }


   void application::TermThread(HINSTANCE hInstTerm)
   {

      throw interface_only_exception(this);

   }


   string application::get_version()
   {

      throw interface_only_exception(this);

   }


   void application::SetCurrentHandles()
   {

      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 1 : " + ::str::from(m_iReturnCode));
      m_pimpl->set_os_data(::get_current_thread());
      if(m_pthreadimpl->get_os_data() == NULL)
      {
         m_pthreadimpl->set_os_data(m_pimpl->get_os_data());
      }
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 2 : " + ::str::from(m_iReturnCode));
      m_pimpl->set_os_int(::get_current_thread_id());
      if(m_pthreadimpl->get_os_int() == 0)
      {
         m_pthreadimpl->set_os_int(m_pimpl->get_os_int());
      }

      m_pimpl->SetCurrentHandles();
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles impled : " + ::str::from(m_iReturnCode));



   }


   void application::set_env_var(const string & var,const string & value)
   {

      throw interface_only_exception(this);

   }




   bool application::_001OnDDECommand(const char * lpcsz)
   {

      throw interface_only_exception(this);

   }


   void application::_001EnableShellOpen()
   {

      throw interface_only_exception(this);

   }


   ::user::document *  application::_001OpenDocumentFile(var varFile)
   {

      throw interface_only_exception(this);

   }


   void application::_001OnFileNew(signal_details * pobj)
   {

      throw interface_only_exception(this);

   }


   bool application::update_module_paths()
   {


      if(is_system())
      {

         if(!m_pimpl->update_module_paths())
            return false;


      }

      return true;


   }



   string application::veriwell_multimedia_music_midi_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->veriwell_multimedia_music_midi_get_default_library_name();

   }



   string application::multimedia_audio_mixer_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_mixer_get_default_library_name();

   }



   string application::multimedia_audio_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "";

      return m_pimpl->multimedia_audio_get_default_library_name();

   }



   string application::draw2d_get_default_library_name()
   {

      if(m_pimpl == NULL)
         return "draw2d_cairo";

      return m_pimpl->draw2d_get_default_library_name();

   }










   void application::process_machine_event_data(machine_event_data * pdata)
   {

      if(pdata->m_fixed.m_bRequestCloseApplication)
      {

         _001CloseApplication();

      }

   }


   void application::_001CloseApplication()
   {

      throw todo(get_app());

   }











   uint32_t application::get_thread_id()
   {
      return m_pimpl->get_thread_id();
   }



   void application::DoWaitCursor(int32_t nCode) // 0 => restore, 1=> begin, -1=> end
   {

      UNREFERENCED_PARAMETER(nCode);

   }
      
   
   void application::ShowWaitCursor(bool bShow)
   {

      UNREFERENCED_PARAMETER(bShow);

   }


#ifndef METROWIN

   void application::get_time(timeval *p)
   {
      m_pimpl->get_time(p);
   }

#endif


   string CLASS_DECL_AURA application::get_cred(const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      throw not_implemented(this);

   }




   bool application::get_temp_file_name_template(string & strRet,const char * pszName,const char * pszExtension,const char * pszTemplate)
   {

      throw not_implemented(this);

      return false;

   }


   bool application::get_temp_file_name(string & strRet,const char * pszName,const char * pszExtension)
   {

      return get_temp_file_name_template(strRet,pszName,pszExtension,NULL);

   }











   bool application::final_handle_exception(::exception::exception & e)
   {
      UNREFERENCED_PARAMETER(e);
      //linux      exit(-1);

      if(!is_system())
      {

         // get_app() may be it self, it is ok...
         if(Sys(get_app()).final_handle_exception((::exception::exception &) e))
            return true;


      }

      return false;
   }





   int32_t application::main()
   {

      TRACE(string(typeid(*this).name()) + " main");;

      dappy(string(typeid(*this).name()) + " : application::main 1");

      try
      {

         TRACE(string(typeid(*this).name()) + " on_run");;
         dappy(string(typeid(*this).name()) + " : going to on_run : " + ::str::from(m_iReturnCode));
         m_iReturnCode = 0;
         m_bReady = true;
         m_bRun = true;
         m_iReturnCode = on_run();
         if(m_iReturnCode != 0)
         {
            dappy(string(typeid(*this).name()) + " : on_run failure : " + ::str::from(m_iReturnCode));
            ::OutputDebugStringW(L"application::main on_run termination failure");
         }

      }
      catch(::exit_exception &)
      {

         dappy(string(typeid(*this).name()) + " : on_run exit_exception");

         System.post_thread_message(WM_QUIT,0,0);

         goto exit_application;

      }
      catch(...)
      {

         dappy(string(typeid(*this).name()) + " : on_run general exception");

         goto exit_application;

      }

      try
      {

         if(is_system())
         {

            dappy(string(typeid(*this).name()) + " : quiting main");

            //post_to_all_threads(WM_QUIT,0,0);

            //Sleep(5000);

         }

      }
      catch(...)
      {

      }

   exit_application:

      try
      {

         m_iReturnCode = exit();

      }
      catch(::exit_exception &)
      {

         post_to_all_threads(WM_QUIT,0,0);

         m_iReturnCode = -1;

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      return m_iReturnCode;

   }




   bool application::pre_run()
   {

      TRACE(string(typeid(*this).name()) + " main_start");;
      try
      {

         m_dwAlive = ::get_tick_count();
         TRACE(string(typeid(*this).name()) + "application_pre_run");;
         int32_t m_iReturnCode = application_pre_run();
         if(m_iReturnCode != 0)
         {
            dappy(string(typeid(*this).name()) + " : applicationpre_run failure : " + ::str::from(m_iReturnCode));
            m_bReady = true;
            TRACE("application::main application_pre_run failure");
            return false;
         }

         xxdebug_box("pre_runnned","pre_runnned",MB_ICONINFORMATION);
         dappy(string(typeid(*this).name()) + " : pre_runned : " + ::str::from(m_iReturnCode));
         TRACE(string(typeid(*this).name()) + " initial_check_directrix");;
         if(!initial_check_directrix())
         {
            dappy(string(typeid(*this).name()) + " : initial_check_directrix failure");
            exit();
            m_iReturnCode = -1;
            m_bReady = true;
            ::OutputDebugStringW(L"exiting on check directrix");
            return false;
         }


         TRACE(string(typeid(*this).name()) + " os_native_bergedge_start");;
         m_dwAlive = ::get_tick_count();
         if(!os_native_bergedge_start())
         {
            dappy(string(typeid(*this).name()) + " : os_native_bergedge_start failure");
            exit();
            m_iReturnCode = -1;
            m_bReady = true;
            ::OutputDebugStringW(L"application::main os_native_bergedge_start failure");
            return false;
         }

         return true;
      }
      catch(::exit_exception &)
      {

         dappy(string(typeid(*this).name()) + " : main_start exit_exception");

         post_to_all_threads(WM_QUIT,0,0);

      }

      return false;

   }




   int32_t application::on_run()
   {
      int32_t m_iReturnCode = 0;

      try
      {
         application_signal_details signal(this,m_psignal,application_signal_start);
         m_psignal->emit(&signal);
      }
      catch(...)
      {
      }

      dappy(string(typeid(*this).name()) + " : starting on_run : " + ::str::from(m_iReturnCode));

      thread * pthread = ::get_thread();

      install_message_handling(pthread->m_pthreadimpl);

      dappy(string(typeid(*this).name()) + " : starting on_run 2 : " + ::str::from(m_iReturnCode));

      try
      {
         try
         {
            m_bReady = true;
            if(m_peventReady != NULL)
               m_peventReady->SetEvent();
         }
         catch(...)
         {
         }
      run:
         try
         {
            m_iReturnCode = run();

         }
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(const ::exception::exception & e)
         {
            if(on_run_exception((::exception::exception &) e))
               goto run;
            if(final_handle_exception((::exception::exception &) e))
               goto run;
            try
            {
               m_iReturnCode = exit();
            }
            catch(::exit_exception & e)
            {

               throw e;

            }
            catch(...)
            {
               m_iReturnCode = -1;
            }
            goto InitFailure;
         }
      }
      catch(::exit_exception & e)
      {

         throw e;

      }
      catch(...)
      {
         // linux-like exit style on crash, differently from general windows error message approach
         // to prevent or correct from crash, should:
         // - look at dumps - to do;
         // - look at trace and log - always doing;
         // - look at debugger with the visual or other tool atashed - to doing;
         // - fill other possibilities;
         // - restart and send information in the holy back, and stateful or self-heal as feedback from below;
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...
         // to pro-activia and overall benefits workaround:
         // - stateful applications:
         //      - browser urls, tabs, entire history, in the ca2computing cloud;
         //      - uint16_t - html document to simplify here - with all history of undo and redos per document optimized by cvs, svn, syllomatter;
         //           - not directly related but use date and title to name document;
         //      - save forms after every key press in .undo.redo.form file parallel to appmatter / form/undo.redo.file parity;
         //      - last ::ikaraoke::karaoke song and scoring, a little less motivated at time of writing;
         //
         // - ex-new-revolut-dynamic-news-self-healing
         //      - pre-history, antecendentes
         //            - sometimes we can't recover from the last state
         //            - to start from the beggining can be too heavy, waity, worky, bory(ing)
         //      - try to creativetily under-auto-domain with constrained-learning, or heuristcally recover from restart, shutdown, login, logoff;
         //           - reification :
         //           - if the document is corrupted, try to open the most of it
         //           - if can only detect that the document cannot be opened or damaged, should creatively workarounds as it comes, as could it be
         //              done, for example search in the web for a proper solution?
         //           - ::ikaraoke::karaoke file does not open? can open next? do it... may animate with a temporary icon...
         //           - import a little as pepper for the meal, prodevian technology into estamira, so gaming experience relativity can open ligh
         //               speed into cartesian dimensions of
         //               core, estamira and prodevian. Take care not to flood prodevian brand black ink over the floor of the estamira office...
         //               black letters, or colorful and pink are accepted and sometimes desired, for example, hello kity prodevian, pirarucu games,
         //               I think no one likes to be boring, but a entire background in black... I don't know... only for your personal office, may be...
         //           - could an online colaborator investigate crashes promptly in a funny way, and make news and jokes? Like terra and UOL for the real world?
         //               - new crash, two documents lost, weathers fault, too hot, can't think, my mother was angry with me, lead to buggy code;
         //               - new version with bug fixes;
         //      - new versions
         //      - automatic updates
         //      - upgrades
         //      - rearrangemntes
         //      - downgrade in the form of retro
         // - ...
         // - ..
         // - .
         // - .
         // - .
         // - .
         // -  .
         // - ...
         // - ...
         // - ...

      }
   InitFailure:
      try
      {
         if(m_peventReady != NULL)
            m_peventReady->SetEvent();
      }
      catch(...)
      {
      }
      try
      {
         thread * pthread = this;
         if(pthread != NULL && pthread->m_pbReady != NULL)
         {
            *pthread->m_pbReady = true;
         }
      }
      catch(...)
      {
      }
      /*try
      {
      thread * pthread = dynamic_cast < thread * > (this);
      ::SetEvent((HANDLE) pthread->m_peventReady);
      }
      catch(...)
      {
      }*/

      // let translator run undefinetely
      /*if(is_system())
      {
      translator::detach();
      }*/

      return m_iReturnCode;
   }




   int32_t application::application_pre_run()
   {

      return 0;

   }



   bool application::InitApplication()
   {

      return true;

   }



   bool application::initial_check_directrix()
   {

      return true;

   }


   bool application::on_install()
   {

      return true;

   }


   bool application::on_uninstall()
   {

      return true;

   }


   bool application::system_add_app_install(const char * pszId)
   {

      throw not_implemented(get_app());

      return true;

   }



   bool application::os_native_bergedge_start()
   {

      return true;

   }











   //   void application::construct(const char *pszId)
   //   {
   //      //if(m_strAppName.has_char())
   //      //   return;
   //      //m_strAppName.Empty();
   //      //m_strId.Empty();
   //      if (pszId == NULL)
   //      {
   //#ifdef WINDOWSEX
   //         wstring wstr = ::GetCommandLineW();
   //         string str = ::str::international::unicode_to_utf8(wstr);
   //         strsize iFind = str.find(" : ");
   //         if (iFind >= 0)
   //         {
   //            iFind = str.find("app=", iFind);
   //            if (iFind >= 0)
   //            {
   //               strsize iEnd = str.find(" ", iFind);
   //               if (iEnd < 0)
   //               {
   //                  m_strId = str.Mid(iFind + 4);
   //               }
   //               else
   //               {
   //                  m_strId = str.Mid(iFind + 4, iEnd - iFind - 4);
   //               }
   //               ::str::begins_eat(m_strId, "\"");
   //               ::str::ends_eat(m_strId, "\"");
   //            }
   //         }
   //#endif
   //      }
   //      else
   //      {
   //         m_strId = pszId;
   //      }
   //      if (m_strId.is_empty())
   //         m_strId = "mplite";
   //      construct();
   //      if (m_strAppName.is_empty())
   //      {
   //         if (m_strAppId.has_char())
   //            m_strAppName = m_strAppId;
   //         else if (m_strInstallToken.has_char())
   //            m_strAppName = m_strInstallToken;
   //      }
   //   }


   //void application::construct()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }

   //   ::core::application::construct();

   //}




   //void application::_001OnFileNew()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   ::core::application::_001OnFileNew(NULL);
   //}


   //bool application::bergedge_start()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::bergedge_start();
   //}



   //bool application::on_install()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::on_install();
   //}

   //bool application::on_uninstall()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::on_uninstall();
   //}


   void application::on_request(sp(::create_context) pcreatecontext)
   {

      ::request_interface::on_request(pcreatecontext);

      command()->consolidate(pcreatecontext);

   }

   //bool application::is_serviceable()
   //{


   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::is_serviceable();
   //}

   //service_base * application::allocate_new_service()
   //{

   //   return NULL;

   //}


   //::user::document *  application::_001OpenDocumentFile(var varFile)
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::core::application::_001OpenDocumentFile(varFile);

   //}


   int32_t application::run()
   {

      if(is_system() || is_session())
      {

         return ::thread::run();

      }
      else if((command()->m_varTopicQuery.has_property("install")
         || command()->m_varTopicQuery.has_property("uninstall"))
         &&
         ((is_session() && command()->m_varTopicQuery["session_start"] == "session")))
      {
      }
      else if(!is_system() && !is_session())
      {
         if(command()->m_varTopicQuery.has_property("install")
            || command()->m_varTopicQuery.has_property("uninstall"))
         {

         }
         else if(command()->m_varTopicQuery.has_property("service"))
         {
            create_new_service();
            ::service_base::serve(*m_pservice);
         }
         else if(command()->m_varTopicQuery.has_property("run") || is_serviceable())
         {
            create_new_service();
            m_pservice->Start(0);
            return ::thread::run();
         }
         else
         {
            return ::thread::run();
         }
      }
      else
      {
         return ::thread::run();
      }

      return 0;

   }


   bool application::safe_is_running()
   {

      bool bRunning = false;

      try
      {

         if(is_running())
         {

            bRunning = true;

         }

      }
      catch(...)
      {

         bRunning = false;

      }


      return bRunning;

   }


   sp(application) application::assert_running(const char * pszAppId)
   {

      sp(application) papp;

      papp = Session.m_appptra.find_running_defer_try_quit_damaged(pszAppId);

      if(papp.is_null())
      {

         sp(::create_context) spcreatecontext(allocer());

         papp = Session.start_application("application",pszAppId,spcreatecontext);

      }

      return papp;

   }





   typedef  void(*PFN_ca2_factory_exchange)(sp(application) papp);




   /*::file::binary_buffer_sp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

   try
   {

   return m_file.get_file(varFile, nOpenFlags);

   }
   catch (::file::exception & e)
   {

   string strMessage = e.get_message();

   App(this).simple_message_box(NULL, strMessage, MB_OK);

   return NULL;

   }

   }
   */




   bool application::is_installing()
   {

      return directrix()->has_property("install");

   }


   bool application::is_uninstalling()
   {

      return directrix()->has_property("uninstall");

   }


   bool application::create_new_service()
   {

      if(m_pservice != NULL)
         return false;

      m_pservice = allocate_new_service();

      if(m_pservice == NULL)
         return false;

      return true;

   }



   bool application::create_service()
   {

      return System.os().create_service(this);

   }

   bool application::remove_service()
   {

      return System.os().remove_service(this);

   }

   bool application::start_service()
   {

      return System.os().start_service(this);

   }

   bool application::stop_service()
   {

      return System.os().stop_service(this);

   }


   void application::on_service_request(sp(::create_context) pcreatecontext)
   {

      if(!is_serviceable())
         return;

      if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("create_service"))
      {
         create_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("start_service"))
      {
         start_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("stop_service"))
      {
         stop_service();
      }
      else if(pcreatecontext->m_spCommandLine->m_varQuery.has_property("remove_service"))
      {
         remove_service();
      }


   }







   bool application::process_initialize()
   {

      if(m_bAuraProcessInitialize)
         return m_bAuraProcessInitializeResult;

      m_bAuraProcessInitialize = true;
      m_bAuraProcessInitializeResult = false;


      

      if(m_pthreadimpl == NULL)
      {

         m_pthreadimpl.alloc(allocer());

         m_pthreadimpl->m_pthread = this;

      }

      m_pimpl.alloc(allocer());

      m_pimpl->construct(NULL);

      m_pimpl->m_pimpl = this;

      if(::get_thread() == NULL)
      {
         ::set_thread(dynamic_cast <thread *> (this));
      }

      if(is_system())
      {

         if(!update_module_paths())
            return false;

      }


      if(!ca_process_initialize())
         return false;

      if(!m_pimpl->process_initialize())
         return false;


      m_bAuraProcessInitializeResult = true;

      return true;

   }


   bool application::initialize_instance()
   {

      return true;

   }


   bool application::initialize1()
   {

      if(m_bAuraInitialize1)
         return m_bAuraInitialize1Result;

      m_bAuraInitialize1 = true;

      m_bAuraInitialize1Result = false;

      m_dwAlive = ::get_tick_count();

      m_straMatterLocator.add_unique(System.dir_appmatter_locator(this));

      if(!ca_initialize1())
         return false;





      if(!m_pimpl->initialize1())
         return false;

      m_bAuraInitialize1Result = true;

      return true;

   }


   bool application::initialize2()
   {

      if(!m_pimpl->initialize2())
         return false;

      if(!ca_initialize2())
         return false;

      return true;

   }


   bool application::initialize3()
   {

      if(!m_pimpl->initialize3())
         return false;

      if(!ca_initialize3())
         return false;

      return true;

   }


   bool application::initialize()
   {
      
      return true;


   }


   int32_t application::exit_instance()
   {


      try
      {

         
         //destroy_message_queue();

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }




      try
      {


         /*      try
         {
         if(m_plemonarray != NULL)
         {
         delete m_plemonarray;
         }
         }
         catch(...)
         {
         }
         m_plemonarray = NULL;
         */


         m_pcommandthread.release();

         release_exclusive();

//         if(m_spuiMessage.is_set())
         {

            //if(!destroy_message_queue())
            {

               // TRACE("Could not finalize message interaction_impl");

            }

         }


         if(m_psignal != NULL)
         {

            application_signal_details signal(this,m_psignal,application_signal_exit_instance);

            try
            {

               m_psignal->emit(&signal);

            }
            catch(...)
            {

            }

            m_psignal.release();

         }

         //try
         //{
         //   if (!is_system())
         //   {
         //      System.unregister_bergedge_application(this);
         //   }
         //}
         //catch (...)
         //{
         //}

         /*try
         {
         ::release(smart_pointer <thread>::m_p);
         }
         catch(...)
         {
         }*/


         if(is_system())
         {

            //         try
            //       {
            //        if(m_spfilesystem.m_p != NULL)
            //      {
            //       ::core::del(m_spfilesystem.m_p);
            //  }
            //         }
            //       catch(...)
            //     {
            //   }
         }



         try
         {

            sp(thread_impl) pthread = m_pthreadimpl;

            if(pthread != NULL)
            {

               try
               {
                  // avoid calling CloseHandle() on our own thread handle
                  // during the thread destructor
                  // avoid thread object data auto deletion on thread termination,
                  // letting thread function terminate
                  m_bAutoDelete = false;

                  set_run(false);

                  pthread->exit_instance();

               }
               catch(...)
               {

               }

            }

         }
         catch(...)
         {

         }

         /*try
         {

            m_pthreadimpl.release();

         }
         catch(...)
         {

         }
         */


         try
         {

            application   * papp = m_pimpl.detach();

            if(papp != NULL && papp != this && !papp->is_system())
            {

               try
               {

                  papp->exit_instance();

               }
               catch(...)
               {

               }

            }

         }
         catch(...)
         {

         }

         return 0;


      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      try
      {

         if(Session.appptra().get_count() <= 1)
         {

            if(System.thread::get_os_data() != NULL)
            {
               System.post_thread_message(WM_QUIT);

            }

         }

      }
      catch(...)
      {

         m_iReturnCode = -1;

      }

      return m_iReturnCode;

   }


   bool application::finalize()
   {

      bool bOk = false;

      try
      {

         bOk = thread::finalize();

      }
      catch(...)
      {

         bOk = false;

      }

      return bOk;

   }






   bool application::is_running()
   {
      return is_alive();
   }

   service_base * application::allocate_new_service()
   {

      return NULL;

   }







   bool application::ca_initialize2()
   {

      application_signal_details signal(this,m_psignal,application_signal_initialize2);
      m_psignal->emit(&signal);
      return signal.m_bOk;

   }


   bool application::ca_initialize3()
   {

      application_signal_details signal(this,m_psignal,application_signal_initialize3);
      m_psignal->emit(&signal);
      if(!signal.m_bOk)
         return false;

      return true;

   }










   bool application::check_exclusive()
   {

#ifdef METROWIN

      return true;

#endif

      bool bSetOk;

      LPSECURITY_ATTRIBUTES lpsa = NULL;

      bool bResourceException = false;

#ifdef WINDOWSEX

      bSetOk = false;

      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory(&MutexAttributes,sizeof(MutexAttributes));
      MutexAttributes.nLength = sizeof(MutexAttributes);
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD,SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if(bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         bSetOk = SetSecurityDescriptorDacl(&SD,
            TRUE,
            (PACL)NULL,
            FALSE) != FALSE;
      }

      if(bSetOk)
      {

         MutexAttributes.lpSecurityDescriptor = &SD;

         lpsa = &MutexAttributes;

      }

#else

      bSetOk = true;

#endif

      if(bSetOk)
      {
         // Make the security attributes point
         // to the security descriptor
         bResourceException = false;
         try
         {
            m_pmutexGlobal = new mutex(this,FALSE,get_global_mutex_name(),lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexGlobal = new mutex(this,FALSE,get_global_mutex_name());
            }
            catch(resource_exception &)
            {
               bResourceException = true;
            }
         }

         if(m_eexclusiveinstance == ExclusiveInstanceGlobal
            && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
         {
            // Should in some way activate the other instance, but this is global, what to do? do not know yet.
            //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            on_exclusive_instance_conflict(ExclusiveInstanceGlobal);
            return false;
         }
         if(m_eexclusiveinstance == ExclusiveInstanceGlobalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexGlobalId = new mutex(this,FALSE,get_global_id_mutex_name(),lpsa);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexGlobalId = new mutex(this,FALSE,get_global_id_mutex_name());
               }
               catch(resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               // Should in some way activate the other instance
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceGlobalId);
               return false;
            }
         }
         bResourceException = false;
         try
         {
            m_pmutexLocal = new mutex(this,FALSE,get_local_mutex_name(),lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexLocal = new mutex(this,FALSE,get_local_mutex_name());
            }
            catch(resource_exception &)
            {
               bResourceException = true;
            }
         }
         if(m_eexclusiveinstance == ExclusiveInstanceLocal && (::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException))
         {
            // Should in some way activate the other instance
            //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
            on_exclusive_instance_conflict(ExclusiveInstanceLocal);
            return false;
         }
         if(m_eexclusiveinstance == ExclusiveInstanceLocalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexLocalId = new mutex(this,FALSE,get_local_id_mutex_name(),lpsa);
            }
            catch(resource_exception &)
            {
               try
               {
                  m_pmutexLocalId = new mutex(this,FALSE,get_local_id_mutex_name());
               }
               catch(resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if(::GetLastError() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               // Should in some way activate the other instance
               //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same ac::count with the same id.<br><br>Exiting this new instance.");
               on_exclusive_instance_conflict(ExclusiveInstanceLocalId);
               return false;
            }
         }
      }
      else
      {
         return false;
      }

      return true;

   }

   bool application::release_exclusive()
   {
      if(m_pmutexGlobal.is_set())
      {
         m_pmutexGlobal.release();
      }
      if(m_pmutexGlobalId.is_set())
      {
         m_pmutexGlobalId.release();
      }
      if(m_pmutexLocal.is_set())
      {
         m_pmutexLocal.release();
      }
      if(m_pmutexLocalId.is_set())
      {
         m_pmutexLocalId.release();
      }
      return true;
   }



   bool application::ca_process_initialize()
   {
      application_signal_details signal(this,m_psignal,application_signal_process_initialize);
      m_psignal->emit(&signal);
      return true;
   }

   bool application::ca_initialize1()
   {
      application_signal_details signal(this,m_psignal,application_signal_initialize1);
      m_psignal->emit(&signal);
      return signal.m_bOk;
   }



   bool application::ca_finalize()
   {
      application_signal_details signal(this,m_psignal,application_signal_finalize);
      try
      {
         m_psignal->emit(&signal);
      }
      catch(...)
      {
      }




      return signal.m_bOk;
   }



   string application::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s",pszAppName);
      return strMutex;
   }

   string application::get_local_id_mutex_name(const char * pszAppName,const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s, id:%s",pszAppName,strId.c_str());
      return strMutex;
   }

   string application::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s",pszAppName);
      return strMutex;
   }

   string application::get_global_id_mutex_name(const char * pszAppName,const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s, id:%s",pszAppName,strId.c_str());
      return strMutex;
   }

   string application::get_local_mutex_name()
   {
      return get_local_mutex_name(get_mutex_name_gen());
   }

   string application::get_local_id_mutex_name()
   {
      return get_local_id_mutex_name(get_mutex_name_gen(),get_local_mutex_id());
   }

   string application::get_global_mutex_name()
   {
      return get_global_mutex_name(get_mutex_name_gen());
   }

   string application::get_global_id_mutex_name()
   {
      return get_global_id_mutex_name(get_mutex_name_gen(),get_global_mutex_id());
   }




   void application::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   {
      if(eexclusive == ExclusiveInstanceLocal)
      {
         on_exclusive_instance_local_conflict();
      }
   }

   void application::on_exclusive_instance_local_conflict()
   {
   }


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }

   string application::get_local_mutex_id()
   {
      return command()->m_varTopicQuery["local_mutex_id"];
   }

   string application::get_global_mutex_id()
   {
      return command()->m_varTopicQuery["global_mutex_id"];
   }

   ::mutex * application::get_local_mutex()
   {
      return m_pmutexLocal;
   }

   ::mutex * application::get_global_mutex()
   {
      return m_pmutexGlobal;
   }



   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   void application::on_set_scalar(e_scalar escalar,int64_t iValue)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         return ::int_scalar_source::on_set_scalar(escalar,iValue);

      }

   }


   void application::get_scalar_minimum(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar,i);

      }

   }

   void application::get_scalar(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         ::int_scalar_source::get_scalar(escalar,i);

      }

   }

   void application::get_scalar_maximum(e_scalar escalar,int64_t & i)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar,i);

      }

   }


   int32_t application::simple_message_box_timeout(::user::interaction * pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(durationTimeOut);
      return simple_message_box(pwndOwner,pszMessage,fuStyle);
   }



   service_base * application::get_service()
   {

      return m_pservice;

   }








   application * application_ptra::find_by_app_name(const string & strAppName)
   {

      application * papp = NULL;

      for(int32_t i = 0; i < get_count(); i++)
      {
         try
         {

            papp = element_at(i).m_p;

            if(papp == NULL)
               continue;

            if(papp->m_strAppName == strAppName)
            {

               return papp;

            }

         }
         catch(...)
         {

         }

      }

      return NULL;


   }


   application * application_ptra::find_running_defer_try_quit_damaged(const string & strAppName)
   {

      sp(application) papp = find_by_app_name(strAppName);

      if(papp.is_null())
         return NULL;

      if(papp->safe_is_running())
         return papp;

      try
      {

         papp->post_thread_message(WM_QUIT);

      }
      catch(...)
      {

      }

      try
      {

         papp.release();

      }
      catch(...)
      {

      }

      return NULL;

   }




   string application::get_license_id()
   {

      return m_strAppId;

   }





   bool application::gudo_get(const string & strKey,::file::serializable & obj)
   {

      string strPath(strKey);

      strPath.replace("::","/");

      synch_lock sl(System.m_spmutexUserAppData);

      {

         ::file::binary_buffer_sp file = file_get_file(Application.dir_userappdata(strPath),::file::mode_read);

         if(file.is_null())
         {

            return false;

         }

         ::file::buffered_buffer buffer(this,file);

         ::file::byte_input_stream is(&buffer);

         try
         {

            obj.read(is);

         }
         catch(...)
         {

         }

      }

      return true;

   }

   bool application::gudo_set(const string & strKey,::file::serializable & obj)
   {

      string strPath(strKey);

      strPath.replace("::","/");

      synch_lock sl(System.m_spmutexUserAppData);

      {

         ::file::binary_buffer_sp file = file_get_file(Application.dir_userappdata(strPath),::file::mode_write | ::file::mode_create | ::file::defer_create_directory);

         if(file.is_null())
         {

            return false;

         }

         ::file::buffered_buffer buffer(this, file);

         ::file::byte_output_stream os(&buffer);

         try
         {

            obj.write(os);

         }
         catch(...)
         {

         }

      }

      return true;

   }


   bool application::assert_user_logged_in()
   {

      return false;

   }

   bool application::init_main_data(main_init_data * pdata)
   {

      m_pinitmaindata = pdata;

      return true;

   }

   bool application::set_main_init_data(main_init_data * pdata)
   {

      return m_pimpl->set_main_init_data(pdata);

   }


   ::user::interaction * application::get_active_guie()
   {

      return Session.get_active_guie();

   }


   ::user::interaction * application::get_focus_guie()
   {

      return Session.get_focus_guie();

   }


   void application::dir_matter_ls_file(const string & str,stringa & stra)
   {

      throw not_implemented(get_app());

   }


   string application::file_as_string(var varFile)
   {

      return ::file_as_string_dup(varFile.get_string());

   }

   
   string application::file_as_string(var varFile,var & varQuery)
   {

      return file_as_string(varFile);

   }


   string application::matter_as_string(const char * pszMatter,const char * pszMatter2)
   {

      var varQuery;

      varQuery["disable_ca2_sessid"] = true;

      return file_as_string(dir_matter(pszMatter,pszMatter2),varQuery);

   }

   string application::dir_matter(const char * pszMatter,const char * pszMatter2)
   {

      return dir_matter(pszMatter,pszMatter2);

   }

   bool application::is_inside_time_dir(const char * pszPath)
   {
      throw not_implemented(this);
      return false;
   }

   bool application::file_is_read_only(const char * pszPath)
   {
      throw not_implemented(this);
      return false;
   }


   bool application::file_exists(const char * pszPath)
   {

      return ::file_exists_dup(pszPath) != FALSE;

   }


   bool application::file_is_equal_path(const char * pszPath1,const char * pszPath2)
   {

      return ::file_is_equal_path_dup(pszPath1,pszPath2) != FALSE;

   }


   bool application::dir_is(const char * psz)
   {

      return ::dir::is(psz);

   }


   bool application::file_del(const char * psz)
   {

      return file_delete_dup(psz) != FALSE;
   
   }

   string application::file_extension(const char * pszPath)
   {

      return ::file_extension_dup(pszPath);

   }


   string application::dir_userappdata(const char * lpcsz,const char * lpcsz2)
   {

      throw not_implemented(this);

   }

   string application::dir_appdata(const char * lpcsz,const char * lpcsz2)
   {

      throw not_implemented(this);

   }


   string application::dir_simple_path(const string & str1,const string & str2)
   {
      
      return dir_path(str1,str2);

   }


   string application::dir_path(const char * psz1,const char * psz2,const char * psz3)
   {

      return ::dir::path(psz1,psz2,psz3);

   }


   string application::dir_element(const char * psz)
   {

      return ::dir::path(::dir::element(),psz);

   }

   string application::dir_ca2module(const char * psz)
   {

      return ::dir::path(::dir::get_ca2_module_folder(),psz);

   }

   string application::dir_name(const char * psz)
   {

      return ::dir::name(psz);

   }


   void application::dir_ls_dir(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle)
   {

      throw not_implemented(get_app());

   }


   void application::dir_rls(const char * lpcsz,stringa * pstraPath,stringa * pstraTitle,stringa * pstraRelative)
   {

      throw not_implemented(get_app());

   }


   bool application::dir_mk(const char * psz)
   {

      return ::dir::mk(psz);

   }


   string application::file_title(const char * psz)
   {

      return ::file_title_dup(psz);

   }


   string application::file_name(const char * psz)
   {

      return ::file_name_dup(psz);

   }


   string application::file_time_square()
   {

      //return get_temp_file_name_template(
      throw not_implemented(get_app());

   }


   string application::http_get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema)
   {

      throw not_implemented(get_app());

   }


   ::file::buffer_sp application::file_get_file(var varFile,uint32_t uiFlags)
   {

      ::file::buffer_sp buffer(allocer());

      if(!buffer->open(varFile,uiFlags))
         return NULL;

      return buffer;

   }



   void application::process_message_filter(int32_t code,signal_details * pobj)
   {

      //if(pobj == NULL)
      //   return;   // not handled

      //SCAST_PTR(::message::base,pbase,pobj);

      //sp(::user::frame_window) pTopFrameWnd;
      //::user::interaction * pMainWnd;
      //::user::interaction * pMsgWnd;
      //switch(code)
      //{
      ////case MSGF_DDEMGR:
      //   // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //   //  never call the next hook.
      //   // By returning FALSE, the message will be dispatched
      //   //  instead (the default behavior).
      //   //return;

      //case MSGF_MENU:
      //   pMsgWnd = pbase->m_pwnd;
      //   if(pMsgWnd != NULL)
      //   {
      //      pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
      //      if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
      //         pTopFrameWnd->m_bHelpMode)
      //      {
      //         //pMainWnd = __get_main_window();
      //         //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
      //         //{
      //         //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
      //         //   pbase->m_bRet = true;
      //         //   return;
      //         //}
      //      }
      //   }
      //   // fall through...

      //case MSGF_DIALOGBOX:    // handles message boxes as well.
      //   //pMainWnd = __get_main_window();
      //   if(code == MSGF_DIALOGBOX && m_pthread->m_puiActive != NULL &&
      //      pbase->m_uiMessage >= WM_KEYFIRST && pbase->m_uiMessage <= WM_KEYLAST)
      //   {
      //      //// need to translate messages for the in-place container
      //      //___THREAD_STATE* pThreadState = __get_thread_state();
      //      //ENSURE(pThreadState);

      //      //if (pThreadState->m_bInMsgFilter)
      //      //   return;
      //      //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
      //      //if (m_puiActive->is_window_enabled())
      //      //{
      //      //   pre_translate_message(pobj);
      //      //   if(pobj->m_bRet)
      //      //   {
      //      //      pThreadState->m_bInMsgFilter = FALSE;
      //      //      return;
      //      //   }
      //      //}
      //      //pThreadState->m_bInMsgFilter = FALSE;    // ok again
      //   }
      //   break;
      //}
      //// default to not handled

   }

   bool application::on_thread_on_idle(::thread_impl * pimpl,LONG lCount)
   {

      UNREFERENCED_PARAMETER(pimpl);

      return lCount < 0;

   }


   bool application::post_user_message(::thread_impl * pimpl,::user::interaction * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      UNREFERENCED_PARAMETER(pimpl);
      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

      return false;

   }

   
   void application::message_handler(signal_details * pobj)
   {



   }


   bool application::is_window(::user::interaction * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return false;

   }

   LRESULT application::send_message(::user::interaction * pui,UINT message,WPARAM wparam,lparam lparam)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

      return 0;

   }

   oswindow application::get_safe_handle(::user::interaction * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }


   void application::dispatch_user_message(::message::base * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

   }


   ::user::interaction * application::get_parent(::user::interaction * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }

   bool application::enable_window(::user::interaction * pui,bool bEnable)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(bEnable);

      return false;

   }


   bool application::set_window_text(::user::interaction * pui,const string & strText)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(strText);

      return false;

   }


   ::thread * application::get_thread(::user::interaction * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }


   void application::set_thread(::user::interaction * pui,::thread * pthread)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(pthread);

   }

   
   sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   {

      return NULL;

   }


   void application::process_message(signal_details * pobj)
   {

      message_handler(pobj);

   }


} // namespace aura
