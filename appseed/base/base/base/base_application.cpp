#include "framework.h"


#if defined(CUBE)


void draw2d_factory_exchange(sp(::base::application) papp);


#endif


#if defined(APPLEOS)

void openURL(const string &url_str);

#endif

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


void dappy(const char * psz)
{

   //printf("app._ : %s : %s\n",_argv[2],psz);
   //printf("hello!!    : %s\n",psz);
   //::OutputDebugString("hello!!    : " + string(psz) + "\n");

}


namespace base
{
   application_signal_details::application_signal_details(sp(::base::application) papp,class ::signal * psignal,e_application_signal esignal):
      element(papp),
      ::signal_details(psignal)
   {

         m_esignal = esignal;
         m_bOk = true;

      }

   UINT application::APPM_LANGUAGE = WM_APP + 117;
   WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;


   application::application():
      m_allocer(this),
      m_mutexMatterLocator(this),
      m_mutexStr(this),
      m_framea(this)
   {

      m_peventReady = NULL;


#ifdef WINDOWS

      m_hinstance                = NULL;

#endif

      if(m_pbaseapp == NULL)
      {

         m_pbaseapp              = this;

      }

      if(m_pbaseapp != NULL)
      {

         m_pbasesystem           = m_pbaseapp->m_pbasesystem;

         if(m_pbaseapp->m_pbasesession == NULL && m_pbasesystem != NULL)
         {

            m_pbasesession       = m_pbasesystem->m_pbasesession;

         }
         else
         {

            m_pbasesession       = m_pbaseapp->m_pbasesession;

         }

#ifdef WINDOWS

         m_hinstance             = m_pbaseapp->m_hinstance;

#endif

      }
      else
      {

         m_pbasesystem           = NULL;

      }

      m_pplaneapp                = NULL;



      m_psignal                  = canew(class signal());

      m_pcommandthread           = canew(::command_thread(this));


      m_bLicense                 = true;

      // initialize wait cursor state
      m_iWaitCursorCount         = 0;

      m_bBaseProcessInitialize         = false;
      m_bBaseProcessInitializeResult   = false;

      m_bBaseInitialize1               = false;
      m_bBaseInitialize1Result         = false;

      m_bBaseInitialize                = false;
      m_bBaseInitializeResult          = false;

      m_bBaseInitializeInstance        = false;
      m_bBaseInitializeInstanceResult  = false;


      m_bShouldInitializeGTwf = true;
      m_bInitializeProDevianMode = true;

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


   int32_t application::simple_message_box(sp(::user::interaction) puiOwner,const char * pszMessage,UINT fuStyle)
   {

#if defined(WINDOWSEX)

      return ::simple_message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);
      //return MessageBoxW(puiOwner->get_safe_handle(),wstring(pszMessage),wstring(m_strAppName),fuStyle);
      //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
      //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      return ::simple_message_box(puiOwner->get_safe_handle(),pszMessage,m_strAppName,fuStyle);
      //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

      return ::simple_message_box(puiOwner->get_safe_handle(), pszMessage, m_strAppName, fuStyle);

#endif

   }

   /*
   int32_t application::simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle)
   {

   #if defined(WINDOWSEX)

   return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   wstring(pszMessage), wstring(m_strAppName), fuStyle);

   #elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

   #else

   return simple_message_box(m_psystem->m_posdata->m_pui->get_handle(), pszMessage, m_strAppName, fuStyle);

   #endif

   }
   */

   int32_t application::simple_message_box(const char * pszMessage,UINT fuStyle)
   {

#if defined(WINDOWSEX)

      return ::simple_message_box(NULL,pszMessage,m_strAppName,fuStyle);
      //return MessageBoxW(NULL,wstring(pszMessage),wstring(m_strAppName),fuStyle);
      //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
      //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

      return ::simple_message_box(NULL, pszMessage, m_strAppName, fuStyle);
      //   return simple_message_box((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

      return ::simple_message_box(NULL, pszMessage, m_strAppName, fuStyle);

#endif

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

      synch_lock sl(&m_mutexStr);

      string strApp(pszApp);
      string strMatter;
      string strLocator;

      if(strApp.is_empty())
      {
         strLocator = System.dir().appmatter_locator(this);
      }
      else
      {
         strLocator = System.dir().appmatter_locator(strApp);
      }

      if(strMatter.is_empty())
      {
         strMatter = "stringtable.xml";
      }
      else if(System.file().extension(strMatter) != "xml")
      {
         strMatter += ".xml";
      }

      string strTableId = strApp;

      if(pszId.has_char() && *pszId != '\0')
      {
         strTableId += "\\";
         strTableId += pszId;
      }

      ::xml::document doc(get_app());
      string strFilePath = System.dir().matter_from_locator(Sess(this).str_context(),strLocator,strMatter);
      if(!System.file().exists(strFilePath,this))
      {
         try
         {
            if(m_stringtable[pszId] != NULL)
               delete m_stringtable[pszId];
         }
         catch(...)
         {
         }
         m_stringtable.set_at(pszId,new string_to_string);
         return;
      }
      string strFile = session().file().as_string(strFilePath);
      if(!doc.load(strFile))
         return;
      string_to_string * pmapNew = new string_to_string;
      for(int32_t i = 0; i < doc.get_root()->children().get_count(); i++)
      {
         string strId = doc.get_root()->child_at(i)->attr("id");
         string strValue = doc.get_root()->child_at(i)->get_value();
         pmapNew->set_at(strId,strValue);
      }

      string_to_string * pmapOld = m_stringtable[strTableId];

      m_stringtable[strTableId] = NULL;

      if(pmapOld != NULL)
      {

         try
         {

            delete pmapOld;

         }
         catch(...)
         {

         }

      }

      m_stringtable[strTableId] = pmapNew;
      ASSERT(m_stringtable[strTableId] == pmapNew);
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
#ifdef WINDOWSEX
         string strUrl = strLink;
         if(!::str::begins_ci(strUrl,"http://")
            && !::str::begins_ci(strUrl,"https://"))
         {
            strUrl = "http://" + strUrl;
         }
         ::ShellExecuteA(NULL,"open",strUrl,NULL,NULL,SW_SHOW);
         return true;
#elif defined METROWIN
#pragma push_macro("System")
#undef System
         ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(strLink);
         ::Windows::System::LauncherOptions ^ options = ref new ::Windows::System::LauncherOptions();
         options->TreatAsUntrusted = false;
         bool success = ::wait(::Windows::System::Launcher::LaunchUriAsync(uri, options));
#pragma pop_macro("System")
#elif defined(LINUX)
         ::system("xdg-open " + strLink);
         return true;
#elif defined(APPLEOS)
         openURL(strLink);
         return true;
#else
         throw not_implemented(get_app());
#endif
      }
      else
      {
         return System.open_link(strLink,pszTarget);
      }

      return false;

   }


   ptr_array < ::user::interaction > application::frames()
   {

      return m_framea.base_ptra();

   }


   void application::add_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_framea.m_mutex); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      m_framea.add(pwnd);

      if(m_puiMain == NULL)
      {

         m_puiMain = pwnd;

      }

   }


   void application::remove_frame(sp(::user::interaction) pwnd)
   {

      synch_lock sl(&m_framea.m_mutex); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if(m_puiMain == pwnd)
      {

         m_puiMain = NULL;

      }

      m_framea.remove(pwnd);

   }




#if defined(METROWIN) || defined(APPLE_IOS)

   sp(::user::interaction) application::window_from_os_data(void * pdata)
   {

      return window_from_handle((oswindow)pdata);

   }

#else

   sp(::user::interaction) application::window_from_os_data(void * pdata)
   {

      return window_from_handle((oswindow)pdata);

   }

#endif



   void application::DoWaitCursor(int32_t nCode)
   {

      if(nCode < 0)
      {

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else if(nCode == 0)
      {

         if(m_iWaitCursorCount > 0)
         {
            m_iWaitCursorCount--;
         }

         if(m_iWaitCursorCount > 0)
         {

            ShowWaitCursor(true);

         }

         m_iWaitCursorCount = 0;
         ShowWaitCursor(false);

      }
      else
      {

         if(m_iWaitCursorCount < 0)
         {
            m_iWaitCursorCount = 0;
         }

         m_iWaitCursorCount++;

         ShowWaitCursor(true);

      }



   }

   void application::ShowWaitCursor(bool bShow)
   {

      if(m_pimpl == NULL)
         return;

      m_pimpl->ShowWaitCursor(bShow);

   }



   void application::construct()
   {

   }



   void application::TermThread(HINSTANCE hInstTerm)
   {

      throw interface_only_exception(this);

   }



   sp(::user::interaction) application::FindWindow(const char * lpszClassName,const char * lpszWindowName)
   {

      throw interface_only_exception(this);

   }


   sp(::user::interaction) application::FindWindowEx(oswindow oswindowParent,oswindow oswindowChildAfter,const char * lpszClass,const char * lpszWindow)
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
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles 2 : " + ::str::from(m_iReturnCode));

      m_pimpl->set_os_int(::get_current_thread_id());

      m_pimpl->SetCurrentHandles();
      dappy(string(typeid(*this).name()) + " : SetCurrentHandles impled : " + ::str::from(m_iReturnCode));

      if(is_installing() || is_uninstalling())
      {

         if(is_system())
         {

            System.install().trace().initialize();

            System.install().m_progressApp.m_scalar                           = int_scalar(&System.install(),scalar_app_install_progress);

            System.install().::int_scalar_source::m_plistener                 = &System.install().m_progressApp;

            System.install().m_progressApp.m_plistener                        = &System.install().trace();

            System.install().m_progressApp.m_dProgressStart                   = 0.84;

            System.install().m_progressApp.m_dProgressEnd                     = 0.998;

            System.install().m_iProgressAppInstallStart                       = 0;

            if(directrix()->m_varTopicQuery["session_start"] == "session")
            {

               System.install().m_iProgressAppInstallEnd = 2 * 5;

            }
            else
            {

               System.install().m_iProgressAppInstallEnd = 3 * 5;

            }

         }

      }

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


   sp(::user::object) application::_001OpenDocumentFile(var varFile)
   {

      throw interface_only_exception(this);

   }


   void application::_001OnFileNew(signal_details * pobj)
   {

      throw interface_only_exception(this);

   }


   sp(::user::printer) application::get_printer(const char * pszDeviceName)
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










   void application::process(machine_event_data * pdata)
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





   sp(::user::interaction) application::release_capture_uie()
   {

#if defined(LINUX)

      oswindow oswindowCapture = ::GetCapture();
      if (oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#elif defined(WINDOWS)

      oswindow oswindowCapture = ::GetCapture();
      if(oswindowCapture == NULL)
         return NULL;
      return System.window_from_os_data(oswindowCapture)->ReleaseCapture();

#elif defined(APPLEOS)

      oswindow oswindowCapture = ::GetCapture();
      if (oswindowCapture == NULL)
         return NULL;
      return oswindowCapture->get_user_interaction()->ReleaseCapture();

#else

      throw not_implemented(get_app());

#endif

   }


   sp(::user::interaction) application::get_capture_uie()
   {

#if defined(METROWIN)

      oswindow oswindowCapture = ::GetCapture();

      if (oswindowCapture == NULL)
         return NULL;

      ::user::interaction * pui = oswindowCapture->interaction_impl();

      if (pui == NULL)
         return NULL;

      return pui->get_capture();

#elif defined(WINDOWS) || defined(APPLE_IOS)

      oswindow oswindowCapture = ::GetCapture();

      if(oswindowCapture == NULL)
         return NULL;

      sp(::user::interaction) pui = System.window_from_os_data(oswindowCapture);

      if(pui == NULL)
         return NULL;

      return pui->GetCapture();

#else

      //      throw not_implemented(get_app());

      oswindow oswindowCapture = ::GetCapture();

      if (oswindowCapture == NULL)
         return NULL;

      return ::GetCapture()->get_user_interaction()->m_pimpl->GetCapture();

#endif

   }







   uint32_t application::get_thread_id()
   {
      return m_pimpl->get_thread_id();
   }





#ifndef METROWIN

   void application::get_time(timeval *p)
   {
      m_pimpl->get_time(p);
   }

#endif


   bool application::do_prompt_file_name(var & varFile,UINT nIDSTitle,uint32_t lFlags,bool bOpenFileDialog,sp(::user::impact_system) ptemplate,sp(::user::object) pdocument)
   {

      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(nIDSTitle);

      return false;

   }

   string CLASS_DECL_BASE application::get_cred(LPCRECT lprect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   {

      return ::fontopus::get_cred(this,lprect,strUsername,strPassword,strToken,strTitle,bInteractive);

   }




   bool application::get_temp_file_name_template(string & strRet,const char * pszName,const char * pszExtension,const char * pszTemplate)
   {

#ifdef METROWIN

      string str(::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path);

#else

      char lpPathBuffer[MAX_PATH * 4];

      uint32_t dwRetVal = GetTempPath(sizeof(lpPathBuffer),lpPathBuffer);

      if(dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
      {

         return FALSE;

      }

      string str(lpPathBuffer);

#endif

      char bufItem[64];

      string strRelative;

      SYSTEMTIME st;

      memset_dup(&st,0,sizeof(st));

      GetSystemTime(&st);

      itoa_dup(bufItem,st.wYear,10);
      zero_pad(bufItem,4);
      strRelative += bufItem;

      itoa_dup(bufItem,st.wMonth,10);
      zero_pad(bufItem,2);
      strRelative += "-";
      strRelative += bufItem;

      itoa_dup(bufItem,st.wDay,10);
      zero_pad(bufItem,2);
      strRelative += "-";
      strRelative += bufItem;

      itoa_dup(bufItem,st.wHour,10);
      zero_pad(bufItem,2);
      strRelative += " ";
      strRelative += bufItem;

      itoa_dup(bufItem,st.wMinute,10);
      zero_pad(bufItem,2);
      strRelative += "-";
      strRelative += bufItem;

      itoa_dup(bufItem,st.wSecond,10);
      zero_pad(bufItem,2);
      strRelative += "-";
      strRelative += bufItem;

      for(int32_t i = 0; i < (1024 * 1024); i++)
      {
         strRet = System.dir().path(str,strRelative + "-" + hex::lower_from(i + 1),string(pszName) + string(".") + pszExtension);
         if(pszTemplate != NULL)
         {
            if(System.install().is_file_ok(strRet,pszTemplate,""))
               return true;
         }
         if(file_exists_dup(strRet))
         {
            try
            {

               m_pbasesystem->file().del(strRet);

            }
            catch(...)
            {

               continue;

            }

            return true;

         }
         else
         {
            return true;
         }
      }
      return false;

   }


   bool application::get_temp_file_name(string & strRet,const char * pszName,const char * pszExtension)
   {

      return get_temp_file_name_template(strRet,pszName,pszExtension,NULL);

   }






   void application::Ex1OnFactoryExchange()
   {

      __node_factory_exchange(this);

   }



   ::visual::icon * application::set_icon(object * pobject,::visual::icon * picon,bool bBigIcon)
   {

      ::visual::icon * piconOld = get_icon(pobject,bBigIcon);

      if(bBigIcon)
      {

         pobject->oprop("big_icon").operator =((sp(element)) picon);

      }
      else
      {

         pobject->oprop("small_icon").operator =((sp(element)) picon);

      }

      return piconOld;

   }


   ::visual::icon * application::get_icon(object * pobject,bool bBigIcon) const
   {

      if(bBigIcon)
      {

         return const_cast <object *> (pobject)->oprop("big_icon").cast < ::visual::icon >();

      }
      else
      {

         return const_cast <object *> (pobject)->oprop("small_icon").cast < ::visual::icon >();

      }

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

         post_to_all_threads(WM_QUIT,0,0);

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

            post_to_all_threads(WM_QUIT,0,0);

            Sleep(5000);

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

#ifdef WINDOWSEX

      MESSAGE msg;

      // Create Windows Message Queue
      ::PeekMessageA(&msg,NULL,0,0xffff,0);

      if(!is_system() && (bool)oprop("SessionSynchronizedInput"))
      {
         ::AttachThreadInput(GetCurrentThreadId(),(uint32_t)System.m_pthreadimpl->get_os_int(),TRUE);
      }

#endif

      m_iReturnCode = 0;

      m_dwAlive = ::get_tick_count();

      if(!InitApplication())
      {
         dappy(string(typeid(*this).name()) + " : InitApplication failure : " + ::str::from(m_iReturnCode));
         goto InitFailure;
      }


      //::simple_message_box(NULL,"e1","e1",MB_OK);

      m_dwAlive = ::get_tick_count();

      try
      {
         try
         {
            if(!process_initialize())
            {
               dappy(string(typeid(*this).name()) + " : process_initialize failure : " + ::str::from(m_iReturnCode));
               goto InitFailure;
            }
         }
         catch(::exit_exception & e)
         {

            throw e;

         }
         catch(const ::exception::exception &)
         {
            goto InitFailure;
         }


         dappy(string(typeid(*this).name()) + " : e2 : " + ::str::from(m_iReturnCode));
         //::simple_message_box(NULL,"e2","e2",MB_OK);

         System.install().m_progressApp()++;
         m_dwAlive = ::get_tick_count();
         try
         {

            if(!initialize_instance())
            {
               dappy(string(typeid(*this).name()) + " : initialize_instance failure : " + ::str::from(m_iReturnCode));
               try
               {
                  exit();
               }
               catch(...)
               {
               }
               goto InitFailure;
            }
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
            catch(...)
            {
               m_iReturnCode = -1;
            }
            if(m_iReturnCode == 0)
               m_iReturnCode = -1;
            goto InitFailure;
         }
      }
      catch(::exit_exception & e)
      {

         throw e;

      }
      catch(...)
      {
      }
      goto run;
   InitFailure:
      if(m_iReturnCode == 0)
         m_iReturnCode = -1;
   run:
      return m_iReturnCode;
   }



   bool application::InitApplication()
   {

      return true;

   }



   bool application::initial_check_directrix()
   {

      if(directrix()->m_varTopicQuery.has_property("install"))
      {

         if(!on_install())
            return false;

         string strId = m_strAppId;

         xxdebug_box("on_install1",strId,0);

         if(strId.is_empty())
            strId = m_strAppName;

         if(strId.has_char() && command()->m_varTopicQuery.has_property("app") && strId == command()->m_varTopicQuery["app"])
         {

            system_add_app_install(strId);

         }
         else if(strId.has_char() && command()->m_varTopicQuery.has_property("session_start") && strId == command()->m_varTopicQuery["session_start"])
         {

            system_add_app_install(strId);

         }
         else if(m_strInstallToken.has_char())
         {

            system_add_app_install(m_strInstallToken);

         }

      }
      else if(directrix()->m_varTopicQuery.has_property("uninstall"))
      {

         if(!on_uninstall())
            return false;

         System.install().remove_spa_start(m_strInstallType,m_strInstallToken);

      }

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

      synch_lock sl(System.m_spmutexSystemAppData);

      string strId(pszId);
      string strSystemLocale = System.m_strLocale;
      string strSystemSchema = System.m_strSchema;
      stringa straLocale = command()->m_varTopicQuery["locale"].stra();
      stringa straSchema = command()->m_varTopicQuery["schema"].stra();

      System.install().remove_spa_start(m_strInstallType,strId);
      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,strSystemLocale,m_strSchema);
      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,strSystemLocale,strSystemSchema);
      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,m_strLocale,m_strSchema);

      for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,straLocale[iLocale],m_strSchema);

      }

      for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,m_strLocale,straSchema[iSchema]);

      }

      for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,straLocale[iLocale],straSchema[iSchema]);

         }

      }

      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,strSystemLocale,"");
      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,m_strLocale,"");

      for(index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,straLocale[iLocale],"");

      }

      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,"",m_strSchema);
      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,"",strSystemSchema);

      for(index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,"",straSchema[iSchema]);

      }


      System.install().add_app_install(System.command()->m_varTopicQuery["build_number"],m_strInstallType,strId,"","");


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

   //   ::application::construct();

   //}




   //void application::_001OnFileNew()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   ::application::_001OnFileNew(NULL);
   //}


   //bool application::bergedge_start()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::application::bergedge_start();
   //}



   //bool application::on_install()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::application::on_install();
   //}

   //bool application::on_uninstall()
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::application::on_uninstall();
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
   //   return ::application::is_serviceable();
   //}

   //service_base * application::allocate_new_service()
   //{

   //   return NULL;

   //}


   //sp(::user::object) application::_001OpenDocumentFile(var varFile)
   //{
   //   string strId = m_strId;
   //   char chFirst = '\0';
   //   if (strId.get_length() > 0)
   //   {
   //      chFirst = strId[0];
   //   }
   //   return ::application::_001OpenDocumentFile(varFile);

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

      papp = session().m_appptra.find_running_defer_try_quit_damaged(pszAppId);

      if(papp.is_null())
      {

         sp(::create_context) spcreatecontext(allocer());

         papp = session().start_application("application",pszAppId,spcreatecontext);

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

      if(m_bBaseProcessInitialize)
         return m_bBaseProcessInitializeResult;

      m_bBaseProcessInitialize = true;
      m_bBaseProcessInitializeResult = false;

      if(is_system())
      {
         System.factory().cloneable_large < stringa >();
         System.factory().cloneable_large < ::primitive::memory >();
         System.factory().cloneable_large < int_array >();
      }

      if(is_system())
      {

         Ex1OnFactoryExchange();

      }

      thread::s_bAllocReady = true;

      if(m_pthreadimpl == NULL)
      {

         m_pthreadimpl.create(allocer());

         m_pthreadimpl->m_pthread = this;

      }

      m_pimpl.create(allocer());

      m_pimpl->construct();

      m_pimpl->m_pimpl = this;

      if(::get_thread() == NULL)
      {
         set_thread(dynamic_cast <thread *> (this));
      }

      if(is_system())
      {

         if(!update_module_paths())
            return false;

      }


      if(!ca_process_initialize())
         return false;

      if(is_system())
      {

         draw2d_factory_exchange();

      }

      if(!m_pimpl->process_initialize())
         return false;


      m_bBaseProcessInitializeResult = true;

      return true;

   }


   bool application::initialize_instance()
   {

      if(m_bBaseInitializeInstance)
         return m_bBaseInitializeInstanceResult;

      m_bBaseInitializeInstance = true;
      m_bBaseInitializeInstanceResult = false;

      xxdebug_box("check_exclusive","check_exclusive",MB_ICONINFORMATION);

      if(!is_system())
      {
         if(!check_exclusive())
            return false;
      }

      xxdebug_box("check_exclusive ok","check_exclusive ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      //::simple_message_box(NULL,"e2.b","e2.b",MB_OK);

      if(!initialize1())
      {
         dappy(string(typeid(*this).name()) + " : initialize1 failure : " + ::str::from(m_iReturnCode));
         return false;
      }



      //::simple_message_box(NULL,"e3","e3",MB_OK);


      System.install().m_progressApp()++; // 2

      xxdebug_box("initialize1 ok","initialize1 ok",MB_ICONINFORMATION);

      string strWindow;

      if(m_strAppName.has_char())
         strWindow = m_strAppName;
      else
         strWindow = typeid(*this).name();

#ifndef METROWIN

      if(!create_message_queue(this,strWindow))
      {
         dappy(string(typeid(*this).name()) + " : create_message_queue failure : " + ::str::from(m_iReturnCode));
         TRACE("Fatal error: could not initialize application message interaction_impl (name=\"%s\").",strWindow.c_str());
         return false;
      }

#endif

      m_dwAlive = ::get_tick_count();

      if(!initialize2())
      {
         dappy(string(typeid(*this).name()) + " : initialize2 failure : " + ::str::from(m_iReturnCode));
         return false;
      }

      System.install().m_progressApp()++; // 3

      xxdebug_box("initialize2 ok","initialize2 ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      if(!initialize3())
      {
         dappy(string(typeid(*this).name()) + " : initialize3 failure : " + ::str::from(m_iReturnCode));
         return false;
      }

      System.install().m_progressApp()++; // 4

      xxdebug_box("initialize3 ok","initialize3 ok",MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();


      dappy(string(typeid(*this).name()) + " : initialize3 ok : " + ::str::from(m_iReturnCode));
      try
      {

         if(!initialize())
         {
            dappy(string(typeid(*this).name()) + " : initialize failure : " + ::str::from(m_iReturnCode));
            return false;
         }
      }
      catch(const char * psz)
      {
         if(!strcmp(psz,"You have not logged in! Exiting!"))
         {
            return false;
         }
         return false;
      }


      System.install().m_progressApp()++; // 5

      m_bBaseInitializeInstanceResult = true;

      return true;

   }


   bool application::initialize1()
   {

      if(m_bBaseInitialize1)
         return m_bBaseInitialize1Result;

      m_bBaseInitialize1 = true;

      m_bBaseInitialize1Result = false;

      m_splicense = new class ::fontopus::license(this);

      m_dwAlive = ::get_tick_count();

      m_straMatterLocator.add_unique(System.dir().appmatter_locator(this));

      if(!ca_initialize1())
         return false;





      if(!m_pimpl->initialize1())
         return false;

      m_bBaseInitialize1Result = true;

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

      if(m_bBaseInitialize)
         return m_bBaseInitializeResult;

      m_bBaseInitialize = true;
      m_bBaseInitializeResult = false;

      application_signal_details signal(this,m_psignal,application_signal_initialize);

      m_psignal->emit(&signal);

      if(!signal.m_bOk)
         return false;

      m_dwAlive = ::get_tick_count();

      if(is_system())
      {
         if(guideline()->m_varTopicQuery.propset().has_property("save_processing"))
         {
            session().savings().save(::base::resource_processing);
         }
         if(guideline()->m_varTopicQuery.propset().has_property("save_blur_back"))
         {
            session().savings().save(::base::resource_blur_background);
         }
         if(guideline()->m_varTopicQuery.propset().has_property("save_transparent_back"))
         {
            session().savings().save(::base::resource_translucent_background);
         }
      }

      if(directrix()->m_varTopicQuery.propset().has_property("install"))
      {
         // core level app install
         if(!Ex2OnAppInstall())
            return false;
      }
      else if(directrix()->m_varTopicQuery.propset().has_property("uninstall"))
      {
         // core level app uninstall
         if(!Ex2OnAppUninstall())
            return false;
      }
      else
      {
#ifdef WINDOWSEX
         // when this process is started in the context of a system account,
         // for example, this code ensure that the process will
         // impersonate a loggen on ::fontopus::user
         HANDLE hprocess;
         HANDLE htoken;

         hprocess = ::GetCurrentProcess();

         if(!OpenProcessToken(
            hprocess,
            TOKEN_ALL_ACCESS,
            &htoken))
            return false;

         if(!ImpersonateLoggedOnUser(htoken))
         {
            TRACELASTERROR();
            return false;
         }
#endif
      }

      m_dwAlive = ::get_tick_count();

      if(is_system()
         && command_thread()->m_varTopicQuery["app"] != "app-core/netnodelite"
         && command_thread()->m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
         && command_thread()->m_varTopicQuery["app"] != "app-gtech/alarm"
         && command_thread()->m_varTopicQuery["app"] != "app-gtech/sensible_service")
      {
         System.http().defer_auto_initialize_proxy_configuration();
      }

      m_dwAlive = ::get_tick_count();

      m_bBaseInitializeResult = true;

      dappy(string(typeid(*this).name()) + " : initialize ok : " + ::str::from(m_iReturnCode));

      return true;

   }


   int32_t application::exit_instance()
   {


      try
      {

         destroy_message_queue();

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

         if(m_spuiMessage.is_set())
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

         try
         {

            m_pthreadimpl.release();

         }
         catch(...)
         {

         }


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

         if(session().appptra().get_count() <= 1)
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


   void application::draw2d_factory_exchange()
   {

#ifdef CUBE

      ::draw2d_factory_exchange(this);

#else

      string strLibrary = draw2d_get_default_library_name();

      if(strLibrary.is_empty())
         strLibrary = "draw2d_cairo";

      ::base::library & library = System.m_libraryDraw2d;

      if(library.is_opened())
         return;

      if(!library.open(strLibrary))
      {
         if(strLibrary != "draw2d_cairo")
         {
            if(!library.open("draw2d_cairo"))
            {
               throw "failed to do draw2d factory exchange";
            }
         }
         else
         {
            throw "failed to do draw2d factory exchange";
         }
      }


      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library.get < PFN_ca2_factory_exchange >("ca2_factory_exchange");

      pfn_ca2_factory_exchange(this);

#endif

   }



   bool application::update_appmatter(::sockets::http_session * & psession,const char * pszRoot,const char * pszRelative)
   {

      ::str::international::locale_schema localeschema(this);

      session().fill_locale_schema(localeschema);

      bool bIgnoreStdStd = string(pszRoot) == "app" && (string(pszRelative) == "main" || string(pszRelative) == "bergedge");

      //update_appmatter(h, psession, pszRoot, pszRelative, localeschema.m_idLocale, localeschema.m_idSchema);

      ::count iCount = localeschema.m_idaLocale.get_count();

      for(index i = 0; i < iCount; i++)
      {
         if(localeschema.m_idaLocale[i] == __id(std) && localeschema.m_idaSchema[i] == __id(std) && bIgnoreStdStd)
            continue;
         update_appmatter(psession,pszRoot,pszRelative,localeschema.m_idaLocale[i],localeschema.m_idaSchema[i]);
         System.install().m_progressApp()++;
      }


      return true;

   }

   bool application::update_appmatter(::sockets::http_session * & psession,const char * pszRoot,const char * pszRelative,const char * pszLocale,const char * pszStyle)
   {

      string strLocale;
      string strSchema;
      TRACE("update_appmatter(root=%s, relative=%s, locale=%s, style=%s)",pszRoot,pszRelative,pszLocale,pszStyle);
      string strRelative = System.dir().path(System.dir().path(pszRoot,"appmatter",pszRelative),Sess(this).get_locale_schema_dir(pszLocale,pszStyle)) + ".zip";
      string strFile = System.dir().element(strRelative);
      string strUrl;
      if(_ca_is_basis())
      {
         strUrl = "http://basis.spaignition.api.server.ca2.cc/download?authnone&version=basis&stage=";
      }
      else
      {
         strUrl = "http://stage.spaignition.api.server.ca2.cc/download?authnone&version=stage&stage=";
      }

      strUrl += System.url().url_encode(strRelative);


      if(psession == NULL)
      {

         while(true)
         {

            property_set setEmpty(get_app());

            psession = System.http().open(System.url().get_server(strUrl),System.url().get_protocol(strUrl),setEmpty,NULL,NULL);

            if(psession != NULL)
               break;

            Sleep(184);

         }

      }

      property_set set;

      set["get_memory"] = "";

      psession = System.http().request(psession,strUrl,set);

      ::file::memory_buffer file(get_app(),set["get_memory"].cast < primitive::memory >());

      if(set["get_memory"].cast < primitive::memory >() != NULL && set["get_memory"].cast < primitive::memory >()->get_size() > 0)
      {

         zip::Util util;

         string strDir = strFile;

         ::str::ends_eat_ci(strDir,".zip");

         try
         {

            util.extract_all(strDir,&file);

         }
         catch(...)
         {

            // spa app.install.exe would recover by retrying or someone would fix the resource packaging problem and then zip extraction at least should work.

            return false;

         }

         //System.compress().extract_all(strFile, this);

      }

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


   int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(durationTimeOut);
      return simple_message_box(pwndOwner,pszMessage,fuStyle);
   }



   service_base * application::get_service()
   {

      return m_pservice;

   }





   void application::message_queue_message_handler(signal_details * pobj)
   {
      SCAST_PTR(::message::base,pbase,pobj);
      if(pbase->m_uiMessage == WM_TIMER)
      {
         SCAST_PTR(::message::timer,ptimer,pobj);
         if(ptimer->m_nIDEvent == 123)
         {
            m_spuiMessage->KillTimer(ptimer->m_nIDEvent);
            ::user::interaction_ptr_array(frames()).send_message_to_descendants(application::APPM_LANGUAGE);
            System.appa_load_string_table();
         }
      }
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




   ::user::user * application::create_user()
   {

      return canew(::user::user(this));

   }



   bool application::defer_initialize_twf()
   {

      if(System.m_ptwf == NULL && (System.m_bShouldInitializeGTwf && m_bShouldInitializeGTwf && m_bInitializeProDevianMode))
      {

         if(!System.initialize_twf())
            return false;

      }

      return true;

   }

   bool application::gudo_get(const string & strKey,::file::serializable & obj)
   {

      string strPath(strKey);

      strPath.replace("::","/");

      synch_lock sl(System.m_spmutexUserAppData);

      {

         ::file::binary_buffer_sp file = session().file_get_file(session().dir().userappdata(strPath),::file::mode_read);

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

         ::file::binary_buffer_sp file = session().file_get_file(session().dir().userappdata(strPath),::file::mode_write | ::file::mode_create | ::file::defer_create_directory);

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


   void application::assert_user_logged_in()
   {

      if(&AppUser(this) == NULL)
         throw exit_exception(get_app(),"You have not logged in!! db_str_set::load");

   }

   bool application::init_main_data(::base::main_init_data * pdata)
   {

      m_pinitmaindata = pdata;

      return true;

   }

   bool application::set_main_init_data(::base::main_init_data * pdata)
   {

      return m_pimpl->set_main_init_data(pdata);

   }


   sp(::user::interaction) application::get_active_guie()
   {

      return session().get_active_guie();

   }


   sp(::user::interaction) application::get_focus_guie()
   {

      return session().get_focus_guie();

   }


} // namespace base




#if defined(MACOS)

void openURL(const string &url_str);


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes (
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   LSOpenCFURLRef(url,0);
   CFRelease(url);
}

#elif defined(APPLE_IOS)

void openURL(const string &url_str);


void openURL(const string &url_str) {
   CFURLRef url = CFURLCreateWithBytes (
      NULL,                        // allocator
      (UInt8*)url_str.c_str(),     // URLBytes
      url_str.length(),            // length
      kCFStringEncodingASCII,      // encoding
      NULL                         // baseURL
      );
   //    LSOpenCFURLRef(url,0);
   CFRelease(url);
}


#endif
