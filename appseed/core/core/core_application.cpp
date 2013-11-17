#include "framework.h"



#ifdef LINUX
#include <dlfcn.h>
#include <link.h>
#include <ctype.h>
#include <unistd.h>
#elif defined(MACOS)
#include <dlfcn.h>
#include <mach-o/dyld.h>
#endif






mutex g_mutexStr(NULL);

//int32_t nibble_to_low_hex(byte nibble);


UINT application::APPM_LANGUAGE = WM_APP + 117;
WPARAM application::WPARAM_LANGUAGE_UPDATE = 1;

CLASS_DECL_CORE HMODULE g_hmoduleOs = NULL;

const char application::gen_FileSection[] = "Recent File List";
const char application::gen_FileEntry[] = "File%d";
const char application::gen_PreviewSection[] = "Settings";
const char application::gen_PreviewEntry[] = "PreviewPages";




application::application() :
   element(this), // start m_pbaseapp as this for constructor referencing this app
   m_mutex(this),
   thread(NULL),
   m_mutexMatterLocator(this),
   //m_allocer(this),
   OAUTHLIB_CONSUMERKEY_KEY      ("oauth_consumer_key"),
   OAUTHLIB_CALLBACK_KEY         ("oauth_callback"),
   OAUTHLIB_VERSION_KEY          ("oauth_version"),
   OAUTHLIB_SIGNATUREMETHOD_KEY  ("oauth_signature_method"),
   OAUTHLIB_SIGNATURE_KEY        ("oauth_signature"),
   OAUTHLIB_TIMESTAMP_KEY        ("oauth_timestamp"),
   OAUTHLIB_NONCE_KEY            ("oauth_nonce"),
   OAUTHLIB_TOKEN_KEY            ("oauth_token"),
   OAUTHLIB_TOKENSECRET_KEY      ("oauth_token_secret"),
   OAUTHLIB_VERIFIER_KEY         ("oauth_verifier"),
   OAUTHLIB_SCREENNAME_KEY       ("screen_name"),


   OAUTHLIB_TWITTER_REQUEST_TOKEN_URL  ("http://twitter.com/oauth/request_token"),
   OAUTHLIB_TWITTER_AUTHORIZE_URL      ("http://twitter.com/oauth/authorize?oauth_token="),
   OAUTHLIB_TWITTER_ACCESS_TOKEN_URL   ("http://twitter.com/oauth/access_token"),


   /* Constants */
   TWIT_COLON ( ":"),
   TWIT_EOS ( '\0'),

   /* Miscellaneous data used to build twitter URLs*/
   TWIT_SEARCHQUERYSTRING ( "?q("),
   TWIT_SCREENNAME ( "?screen_name("),
   TWIT_USERID ( "?user_id("),
   TWIT_EXTENSIONFORMAT ( ".xml"),
   TWIT_TARGETSCREENNAME ( "?target_screen_name("),
   TWIT_TARGETUSERID ( "?target_id("),

   /* Search URLs */
   TWIT_SEARCH_URL ( "http://search.twitter.com/search.atom"),

   /* Status URLs */
   TWIT_STATUSUPDATE_URL ( "http://twitter.com/statuses/update.xml"),
   TWIT_STATUSSHOW_URL ( "http://twitter.com/statuses/show/"),
   TWIT_STATUDESTROY_URL ( "http://twitter.com/statuses/destroy/"),

   /* Timeline URLs */
   TWIT_PUBLIC_TIMELINE_URL ( "http://twitter.com/statuses/public_timeline.xml"),
   TWIT_FEATURED_USERS_URL ( "http://twitter.com/statuses/featured.xml"),
   TWIT_FRIENDS_TIMELINE_URL ( "http://twitter.com/statuses/friends_timeline.xml"),
   TWIT_MENTIONS_URL ( "http://twitter.com/statuses/mentions.xml"),
   TWIT_USERTIMELINE_URL ( "http://twitter.com/statuses/user_timeline.xml"),

   /* Users URLs */
   TWIT_SHOWUSERS_URL ( "http://twitter.com/users/show.xml"),
   TWIT_SHOWFRIENDS_URL ( "http://twitter.com/statuses/friends.xml"),
   TWIT_SHOWFOLLOWERS_URL ( "http://twitter.com/statuses/followers.xml"),

   /* Direct messages URLs */
   TWIT_DIRECTMESSAGES_URL ( "http://twitter.com/direct_messages.xml"),
   TWIT_DIRECTMESSAGENEW_URL ( "http://twitter.com/direct_messages/new.xml"),
   TWIT_DIRECTMESSAGESSENT_URL ( "http://twitter.com/direct_messages/sent.xml"),
   TWIT_DIRECTMESSAGEDESTROY_URL ( "http://twitter.com/direct_messages/destroy/"),

   /* Friendships URLs */
   TWIT_FRIENDSHIPSCREATE_URL ( "http://twitter.com/friendships/create.xml"),
   TWIT_FRIENDSHIPSDESTROY_URL ( "http://twitter.com/friendships/destroy.xml"),
   TWIT_FRIENDSHIPSSHOW_URL ( "http://twitter.com/friendships/show.xml"),

   /* Social graphs URLs */
   TWIT_FRIENDSIDS_URL ( "http://twitter.com/friends/ids.xml"),
   TWIT_FOLLOWERSIDS_URL ( "http://twitter.com/followers/ids.xml"),

   /* Ac::count URLs */
   TWIT_ACCOUNTRATELIMIT_URL ( "http://twitter.com/account/rate_limit_status.xml"),

   /* Favorites URLs */
   TWIT_FAVORITESGET_URL ( "http://twitter.com/favorites.xml"),
   TWIT_FAVORITECREATE_URL ( "http://twitter.com/favorites/create/"),
   TWIT_FAVORITEDESTROY_URL ( "http://twitter.com/favorites/destroy/"),

   /* Block URLs */
   TWIT_BLOCKSCREATE_URL ( "http://twitter.com/blocks/create/"),
   TWIT_BLOCKSDESTROY_URL ( "http://twitter.com/blocks/destroy/"),

   /* Saved Search URLs */
   TWIT_SAVEDSEARCHGET_URL ( "http://twitter.com/saved_searches.xml"),
   TWIT_SAVEDSEARCHSHOW_URL ( "http://twitter.com/saved_searches/show/"),
   TWIT_SAVEDSEARCHCREATE_URL ( "http://twitter.com/saved_searches/create.xml"),
   TWIT_SAVEDSEARCHDESTROY_URL ( "http://twitter.com/saved_searches/destroy/"),

   /* Trends URLs */
   TWIT_TRENDS_URL ( "http://api.twitter.com/1/trends.json"),
   TWIT_TRENDSDAILY_URL ( "http://api.twitter.com/1/trends/daily.json"),
   TWIT_TRENDSCURRENT_URL ( "http://api.twitter.com/1/trends/current.json"),
   TWIT_TRENDSWEEKLY_URL ( "http://api.twitter.com/1/trends/weekly.json"),
   TWIT_TRENDSAVAILABLE_URL ( "http://api.twitter.com/1/trends/available.json")

{


   if(m_pbaseapp.is_null())
   {
      set_app(this);
   }

   m_bInitializeProDevianMode = true;

   // almost always forgotten, assumed, as exception, responsability of application to add first ref on constructor.
   ::add_ref(this);

   //_setmbcp(CP_UTF8);
   //      uint32_t dw = ::_getmbcp();
   srand(::get_tick_count());

   m_pinitmaindata      = NULL;
   m_bService           = false;

   m_psession           = NULL;
   m_psystem            = NULL;


   //      m_plemonarray              = new ::lemon::array(this);
   //    m_base64.set_app(this);
   m_pmath                    = new math::math(this);
   m_pgeometry                = new geometry::geometry(this);
   //m_pidspace = new id_space("veribell-{E856818A-2447-4a4e-B9CC-4400C803EE7A}", NULL);
   m_iResourceId              = 8001;
   m_psavings                 = new class ::core::savings(this);
//   m_pcommandthread           = new command_thread(this);

   ::core::profiler::initialize();

   m_pszRegistryKey              = NULL;
   m_pszHelpFilePath             = NULL;
   m_pszProfileName              = NULL;
   m_pframea                     = NULL;


   m_nSafetyPoolSize             = 512;        // default size

   m_pwndMain                    = NULL;
   m_puserstrcontext             = NULL;
   m_bShouldInitializeGTwf       = true;
   m_bSessionSynchronizedCursor  = true;
   m_bSessionSynchronizedScreen  = true;

   m_pdocmanager                 = NULL;

   m_nCmdShow                    = -1;

   m_strInstallType              = "application";

   m_pinitmaindata = NULL;

   m_psignal->connect(this, &application::on_application_signal);

   m_eexclusiveinstance       = ExclusiveInstanceNone;
   m_peventReady              = NULL;
   m_pmapKeyPressed           = NULL;
   m_bLicense                 = true;
   m_strLocale                = "_std";
   m_strSchema                = "_std";

   m_pcalculator              = NULL;
   m_pcolorertake5            = NULL;
   m_psockets                 = NULL;

   // initialize wait cursor state
   m_iWaitCursorCount = 0;
   m_hcurWaitCursorRestore = NULL;


}

application::~application()
{
}



void application::construct(const char * pszId)
{
   UNREFERENCED_PARAMETER(pszId);
}

application * application::get_app() const
{
   return (application *) this;
}


int32_t application::exit()
{

   int32_t iExit = 0;

   try
   {
      thread::exit();
   }
   catch(...)
   {
   }

   return iExit;

}


bool application::is_system()
{
   return false;
}

bool application::is_session()
{
   return false;
}

bool application::is_installing()
{
   return false;
}

bool application::is_uninstalling()
{
   return false;
}

bool application::is_serviceable()
{
   return false;
}

bool application::init_main_data(::core::main_init_data * pdata)
{
   m_pinitmaindata = pdata;
   return true;
}

/*   bool application::set_main_init_data(main_init_data * pdata)
{
return true;
}*/

int32_t application::main()
{
   return 0;
}

/*   bool application::bergedge_start()
{
return true;
}*/

bool application::os_native_bergedge_start()
{
   return true;
}

bool application::process_initialize()
{



   if(is_system())
   {
      System.factory().cloneable_large < stringa > ();
      System.factory().cloneable_large < ::primitive::memory > ();
      System.factory().cloneable_large < int_array > ();
      //System.factory().cloneable_large < property > ();
   }

   m_pframea = new ::user::interaction_ptr_array(this);

   if(is_system())
   {
      Ex1OnFactoryExchange();
   }

   thread::s_bAllocReady = true;

   if(thread::m_p == NULL)
   {

      thread::m_p.create(allocer());
      thread::m_p->m_p = this;

   }

   ::application_base::m_p.create(allocer());
   ::application_base::m_p->construct();
   ::application_base::m_p->::application_base::m_p = this;

   if(::get_thread() == NULL)
   {
      set_thread(dynamic_cast < thread * > (this));
   }

   if(!update_module_paths())
      return false;

   m_spfs = canew(::fs::fs(this));

   if(m_spfs == NULL)
      return false;

   m_spfs->construct(this);


   if(!m_spfs->initialize())
      return false;

   if(!ca_process_initialize())
      return false;

   if(is_system())
   {
      draw2d_factory_exchange();
   }

   if(!::application_base::m_p->process_initialize())
      return false;

   return true;

}


bool application::update_module_paths()
{

   if(is_system())
   {

      if(!::application_base::m_p->update_module_paths())
         return false;

      application * pappOs = dynamic_cast < application * > (::application_base::m_p.m_p);

      if(pappOs->m_strCa2ModuleFolder.is_empty())
         pappOs->m_strCa2ModuleFolder = pappOs->m_strModuleFolder;

      m_strModulePath       = pappOs->m_strModulePath;
      m_strModuleFolder     = pappOs->m_strModuleFolder;
      m_strCa2ModulePath    = pappOs->m_strCa2ModulePath;
      m_strCa2ModuleFolder  = pappOs->m_strCa2ModuleFolder;

   }
   else
   {

      m_strModulePath   = System.m_strModulePath;
      m_strModuleFolder = System.m_strModuleFolder;

   }

   return true;

}


bool application::initialize1()
{


   m_psockets = canew(::sockets::sockets(this));

   m_psockets->construct(this);

   if(!m_psockets->initialize1())
      return false;


   m_puinteraction = canew(::uinteraction::uinteraction(this));

   m_puinteraction->construct(this);

   if(!m_puinteraction->initialize())
      return false;

   /*
   if(is_system())
   {
   m_strFontopusServer     = System.get_fontopus_server("http://account.ca2.cc/get_fontopus", this, 8);
   if(m_strFontopusServer.is_empty())
   m_strFontopusServer = "server.ca2.cc";
   else
   {
   m_strFontopusServer.replace("account", "server");
   }
   m_strMatterUrl          = "http://" + m_strFontopusServer + "/matter/";
   m_strMatterSecureUrl    = "https://" + m_strFontopusServer + "/matter/";
   }
   else
   {
   m_strFontopusServer     = System.m_strFontopusServer;
   m_strMatterUrl          = System.m_strMatterUrl;
   m_strMatterSecureUrl    = System.m_strMatterSecureUrl;
   }
   */


   m_dwAlive = ::get_tick_count();


   m_strMatterLocator = System.dir().appmatter_locator(this);


   m_puserstrcontext = canew(::user::str_context(this));
   if(m_puserstrcontext == NULL)
      return false;


   if(!ca_initialize1())
      return false;

   string strLocaleSystem;

   string strSchemaSystem;

   string strPath = System.dir().appdata("langstyle_settings.xml");

   if(Application.file().exists(strPath))
   {

      string strSystem = Application.file().as_string(strPath);

      ::xml::document docSystem(get_app());

      if(docSystem.load(strSystem))
      {

         if(docSystem.get_child("lang") != NULL)
         {

            strLocaleSystem = docSystem.get_child("lang")->get_value();

         }

         if(docSystem.get_child("style") != NULL)
         {

            strSchemaSystem = docSystem.get_child("style")->get_value();

         }

      }

   }



   string strLocale;

   string strSchema;

#ifdef METROWIN

   stringa stra;

   try
   {

      stra.explode("-", ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

   }
   catch (long)
   {


   }

   strLocale = stra[0];

   strSchema = stra[0];

#elif defined(WINDOWS)
   LANGID langid = ::GetUserDefaultLangID();
#define SPR_DEUTSCH LANG_GERMAN
   if(langid == LANG_SWEDISH)
   {
      strLocale = "se";
      strSchema = "se";
   }
   else if(langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
   {
      strLocale = "pt-br";
      strSchema = "pt-br";
   }
   else if(PRIMARYLANGID(langid) == SPR_DEUTSCH)
   {
      strLocale = "de";
      strSchema = "de";
   }
   else if(PRIMARYLANGID(langid) == LANG_ENGLISH)
   {
      strLocale = "en";
      strSchema = "en";
   }
   else if(PRIMARYLANGID(langid) == LANG_JAPANESE)
   {
      strLocale = "jp";
      strSchema = "jp";
   }
   else if(PRIMARYLANGID(langid) == LANG_POLISH)
   {
      strLocale = "pl";
      strSchema = "pl";
   }
#endif

   if(strLocale.is_empty())
      strLocale = "se";

   if(strSchema.is_empty())
      strSchema = "se";

   if(strLocaleSystem.has_char())
      strLocale = strLocaleSystem;

   if(strSchemaSystem.has_char())
      strSchema = strSchemaSystem;

   if(Sys(this).directrix()->m_varTopicQuery["locale"].get_string().has_char())
      strLocale = Sys(this).directrix()->m_varTopicQuery["locale"];

   if(Sys(this).directrix()->m_varTopicQuery["schema"].get_string().has_char())
      strSchema = Sys(this).directrix()->m_varTopicQuery["schema"];

   if(App(this).directrix()->m_varTopicQuery["locale"].get_string().has_char())
      strLocale = App(this).directrix()->m_varTopicQuery["locale"];

   if(App(this).directrix()->m_varTopicQuery["schema"].get_string().has_char())
      strSchema = App(this).directrix()->m_varTopicQuery["schema"];



   set_locale(strLocale, false);
   set_schema(strSchema, false);


   str_context()->localeschema().m_idaLocale.add(strLocale);
   str_context()->localeschema().m_idaSchema.add(strSchema);

   //Sleep(15 * 1000);



   if(!::application_base::m_p->initialize1())
      return false;

   return true;

}


bool application::initialize2()
{

   if(!::application_base::m_p->initialize2())
      return false;

   application_signal_details signal(this, m_psignal, application_signal_initialize2);
   m_psignal->emit(&signal);
   return signal.m_bOk;

}


bool application::initialize3()
{

   application_signal_details signal(this, m_psignal, application_signal_initialize3);
   m_psignal->emit(&signal);
   if(!signal.m_bOk)
      return false;

   if(!::application_base::m_p->initialize3())
      return false;

   return true;

}



::fontopus::user * application::get_safe_user()
{

   if(m_psession == NULL)
      return NULL;

   if(m_psession->m_pplanesession->m_pfontopus == NULL)
      return NULL;

   return m_psession->m_pplanesession->m_pfontopus->m_puser;

}




void application::Ex1OnFactoryExchange()
{

   System.factory().creatable_large < ::file::exception > ();

   ::boot::library library;

   if(!library.open("os"))
      throw "failed to do factory exchange";

   PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library.get < PFN_ca2_factory_exchange > ("ca2_factory_exchange");

   pfn_ca2_factory_exchange(this);

}


void application::draw2d_factory_exchange()
{

   string strLibrary = draw2d_get_default_library_name();

   if(strLibrary.is_empty())
      strLibrary = "draw2d_cairo";

   ::boot::library & library = System.m_libraryDraw2d;

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


   PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library.get < PFN_ca2_factory_exchange > ("ca2_factory_exchange");

   pfn_ca2_factory_exchange(this);

}

void application::on_request(sp(::create_context) pcreatecontext)
{

   ::request_interface::on_request(pcreatecontext);

}




math::math & application::math()
{
   return *m_pmath;
}


geometry::geometry & application::geometry()
{

   return *m_pgeometry;

}


::core::savings & application::savings()
{

   return *m_psavings;

}


/*   ::lemon::array & application::array()
{

return *m_plemonarray;

}
*/

bool application::initialize_instance()
{

   if(!is_system())
   {
      if(!check_exclusive())
         return false;
   }

   m_dwAlive = ::get_tick_count();


   if(!initialize1())
      return false;

   string strWindow;
   if(m_strAppName.has_char())
      strWindow = m_strAppName;
   else
      strWindow = typeid(*this).name();

#ifndef METROWIN

   if(!create_message_queue(this, strWindow))
   {
      TRACE("Fatal error: could not initialize application message window (name=\"%s\").", strWindow);
      return false;
   }

#endif

   m_dwAlive = ::get_tick_count();

   if(!initialize2())
      return false;

   m_dwAlive = ::get_tick_count();

   if(!initialize3())
      return false;

   m_dwAlive = ::get_tick_count();

   try
   {
      if(!initialize())
         return false;
   }
   catch(const char * psz)
   {
      if(!strcmp(psz, "You have not logged in! Exiting!"))
      {
         return false;
      }
      return false;
   }

   if(!::application_base::m_p->initialize2())
      return false;

   return application::initialize2();

}


int32_t application::exit_instance()
{

   try
   {
      if(is_system())
      {
         if(System.m_spcopydesk.is_set())
         {
            System.m_spcopydesk->finalize();
            System.m_spcopydesk.release();
         }
         System.m_splicense.release();
      }
   }
   catch(...)
   {
   }


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


   try
   {
      if(m_pmath != NULL)
      {
         delete m_pmath;
      }
   }
   catch(...)
   {
   }
   m_pmath = NULL;



   try
   {
      if(m_pgeometry != NULL)
      {
         delete m_pgeometry;
      }
   }
   catch(...)
   {
   }
   m_pgeometry = NULL;



   try
   {
      if(m_psavings != NULL)
      {
         delete m_psavings;
      }
   }
   catch(...)
   {
   }
   m_psavings = NULL;


   m_pcommandthread.release();

   release_exclusive();

   if(!destroy_message_queue())
   {
      TRACE("Could not finalize message window");
   }

   application_signal_details signal(this, m_psignal, application_signal_exit_instance);
   try
   {
      m_psignal->emit(&signal);
   }
   catch(...)
   {
   }

   try
   {
      if(!is_system())
      {
         System.unregister_bergedge_application(this);
      }
   }
   catch(...)
   {
   }

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

      thread         * pthread      = thread::m_p.detach();

      if(pthread != NULL)
      {

         try
         {
            // avoid calling CloseHandle() on our own thread handle
            // during the thread destructor
            // avoid thread object data auto deletion on thread termination,
            // letting thread function terminate
            pthread->m_bAutoDelete = false;

            pthread->set_os_data(NULL);

            pthread->set_run(false);

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

      ::application_base   * papp         = ::application_base::m_p.detach();

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
   /*      int32_t nReturnValue=0;
   if(__get_current_message())
   {
   nReturnValue=static_cast<int32_t>(__get_current_message()->wParam);
   }*/
   //      return nReturnValue; // returns the value from PostQuitMessage

}

LRESULT application::GetPaintMsgProc(int32_t nCode, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(nCode);
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   return 0;
}





bool application::CreateFileFromRawResource(UINT nID, const char * lpcszType, const char * lpcszFilePath)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lpcszType);
   UNREFERENCED_PARAMETER(lpcszFilePath);
   /*      HINSTANCE hinst = ::core::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);
   if(hinst == NULL)
   return false;
   HRSRC hrsrc = ::FindResource(
   hinst,
   MAKEINTRESOURCE(nID),
   lpcszType);
   if(hrsrc == NULL)
   return false;
   HGLOBAL hres = ::LoadResource(hinst, hrsrc);
   if(hres == NULL)
   return false;
   uint32_t dwResSize = ::SizeofResource(hinst, hrsrc);

   if(hres != NULL)
   {
   UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
   try
   {
   // create the .mdb file
   ::file::binary_buffer_sp f(get_app());

   if(f->open(lpcszFilePath, ::file::mode_create | ::file::mode_write ))
   {
   // write the ::fontopus::user-defined resource to the .mdb file
   f->write(lpnRes, dwResSize);
   f->flush();
   }
   else
   {
   #ifdef DEBUG
   g_dumpcontext << "File could not be opened \n";
   #endif
   }
   }
   catch(::core::file_exception_sp * pe)
   {
   #ifdef DEBUG
   //         g_dumpcontext << "File could not be opened " << pe->m_cause << "\n";
   #endif
   }


   #ifndef WIN32 //unlock Resource is obsolete in the Win32 API
   ::UnlockResource(hres);
   #endif
   ::FreeResource(hres);
   }
   return true;*/

   return false;
}

#ifdef WINDOWS

bool application::OnMessageWindowMessage(LPMESSAGE lpmsg)
{
   UNREFERENCED_PARAMETER(lpmsg);
   return false;
}

#elif defined(LINUX)

bool application::OnMessageWindowMessage(XEvent * pevent)
{
   UNREFERENCED_PARAMETER(pevent);
   return false;
}

#endif

void application::OnAppLanguage(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   m_signalAppLanguageChange.emit();
}

string application::get_ca2_module_folder()
{
   single_lock sl(&m_mutex, true);
   return m_strCa2ModuleFolder;
}

string application::get_ca2_module_file_path()
{

   string strModuleFileName;

#ifdef WINDOWSEX

   char lpszModuleFilePath[MAX_PATH + 1];

   if(GetModuleFileName(::GetModuleHandleA("core.dll"), lpszModuleFilePath, MAX_PATH + 1))
   {

      strModuleFileName = lpszModuleFilePath;

   }

#elif defined(METROWIN)

   throw todo(this);

#else

#ifdef RTLD_DI_LINKMAP

   {

      void * handle = dlopen("core.so", 0);

      if(handle == NULL)
         return false;

      link_map * plm;

      dlinfo(handle, RTLD_DI_LINKMAP, &plm);

      strModuleFileName = plm->l_name;

      dlclose(handle);

      //         m_strCa2ModuleFolder = dir::name(strModuleFileName);

   }

#else

   {

      char * pszCurDir = getcwd(NULL, 0);

      string strCurDir = pszCurDir;

      free(pszCurDir);

      if(App(this).file().exists(System.dir().path(strCurDir, "core.dylib")))
      {
         m_strCa2ModuleFolder = strCurDir;
         goto finishedCa2Module;
      }


      if(App(this).file().exists(System.dir().path(m_strModuleFolder, "core.dylib")))
      {
         m_strCa2ModuleFolder = m_strModuleFolder;
         goto finishedCa2Module;
      }

      strModuleFileName = App(this).dir().pathfind(getenv("LD_LIBRARY_PATH"), "core.dylib", "rfs"); // readable - normal file - non zero sized

   }

finishedCa2Module:;

#endif

#endif

   return strModuleFileName;


}

string application::get_module_folder()
{
   return m_strModuleFolder;
}

string application::get_module_file_path()
{

#ifdef WINDOWSEX

   char lpszModuleFilePath[MAX_PATH + 1];

   GetModuleFileName(NULL, lpszModuleFilePath, MAX_PATH + 1);

   string strModuleFileName(lpszModuleFilePath);

   return strModuleFileName;

#elif defined(METROWIN)

   return "m_app.exe";

#else

   char * lpszModuleFilePath = br_find_exe_dir("app");

   if(lpszModuleFilePath == NULL)
      return "";

   string strModuleFileName(lpszModuleFilePath);

   free(lpszModuleFilePath);

   return strModuleFileName;

#endif

}


void application::OnUpdateRecentFileMenu(cmd_ui * pcmdui)
{
   UNREFERENCED_PARAMETER(pcmdui);
   /*TRACE("\nCVmsGenApp::OnUpdateRecentFileMenu");
   if(m_pRecentFileList == NULL)
   {
   pcmdui->Enable(FALSE);
   //string str;
   //str.load_string(IDS_RECENT_FILE);
   //pcmdui->SetText(str);
   for (int32_t iMRU = 1; iMRU < 10; iMRU++)
   pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);
   return;
   }

   ASSERT(m_pRecentFileList->m_arrNames != NULL);

   ::user::menu* pMenu = pcmdui->m_pMenu;
   if (m_pRecentFileList->m_strOriginal.is_empty() && pMenu != NULL)
   pMenu->GetMenuString(pcmdui->m_nID, m_pRecentFileList->m_strOriginal, MF_BYCOMMAND);

   if (m_pRecentFileList->m_arrNames[0].is_empty())
   {
   // no MRU files
   if (!m_pRecentFileList->m_strOriginal.is_empty())
   pcmdui->SetText(m_pRecentFileList->m_strOriginal);
   pcmdui->Enable(FALSE);
   return;
   }

   if (pcmdui->m_pMenu == NULL)
   return;

   ::user::menu * pmenu = CMenuUtil::FindPopupMenuFromID(pcmdui->m_pMenu, pcmdui->m_nID);

   //if(pmenu == NULL)
   //{
   // pmenu = pcmdui->m_pMenu;
   //}

   bool bCmdUIMenu = pmenu == pcmdui->m_pMenu;

   if(!bCmdUIMenu)
   return;

   int32_t nID = pcmdui->m_nID;
   int32_t nIndex = CMenuUtil::GetMenuPosition(pmenu, nID);

   for (int32_t iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
   pcmdui->m_pMenu->DeleteMenu(pcmdui->m_nID + iMRU, MF_BYCOMMAND);



   char szCurDir[_MAX_PATH];
   GetCurrentDirectory(_MAX_PATH, szCurDir);
   int32_t nCurDir = lstrlen(szCurDir);
   ASSERT(nCurDir >= 0);
   szCurDir[nCurDir] = '\\';
   szCurDir[++nCurDir] = '\0';

   string strName;
   string strTemp;
   for (iMRU = 0; iMRU < m_pRecentFileList->m_nSize; iMRU++)
   {
   if (!m_pRecentFileList->GetDisplayName(strName, iMRU, szCurDir, nCurDir))
   break;

   // double up any '&' characters so they are not underlined
   const char * lpszSrc = strName;
   LPTSTR lpszDest = strTemp.GetBuffer(strName.get_length()*2);
   while (*lpszSrc != 0)
   {
   if (*lpszSrc == '&')
   *lpszDest++ = '&';
   if (_istlead(*lpszSrc))
   *lpszDest++ = *lpszSrc++;
   *lpszDest++ = *lpszSrc++;
   }
   *lpszDest = 0;
   strTemp.ReleaseBuffer();

   // insert mnemonic + the file name
   char buf[10];
   wsprintf(buf, "&%d ", (iMRU+1+m_pRecentFileList->m_nStart) % 10);

   //      pcmdui->m_pMenu->InsertMenu(pcmdui->m_nIndex++,
   //         MF_STRING | MF_BYPOSITION, pcmdui->m_nID++,
   //         string(buf) + strTemp);
   pmenu->InsertMenu(nIndex,
   MF_STRING | MF_BYPOSITION, nID,
   string(buf) + strTemp);
   nIndex++;
   nID++;
   if(bCmdUIMenu)
   {
   pcmdui->m_nIndex = nIndex;
   pcmdui->m_nID = nID;
   }
   }

   // update end menu count
   if(bCmdUIMenu)
   {
   pcmdui->m_nIndex--; // point to last menu added
   pcmdui->m_nIndexMax = pcmdui->m_pMenu->GetMenuItemCount();
   }

   pcmdui->m_bEnableChanged = TRUE;    // all the added items are enabled*/

}

bool application::GetResourceData(UINT nID, const char * lpcszType, primitive::memory &storage)
{
   UNREFERENCED_PARAMETER(nID);
   UNREFERENCED_PARAMETER(lpcszType);
   UNREFERENCED_PARAMETER(storage);
   /*      HINSTANCE hinst = ::core::FindResourceHandle(MAKEINTRESOURCE(nID), lpcszType);

   if(hinst == NULL)
   return false;

   HRSRC hrsrc = ::FindResource(
   hinst,
   MAKEINTRESOURCE(nID),
   lpcszType);

   if(hrsrc == NULL)
   return false;

   HGLOBAL hres = ::LoadResource(hinst, hrsrc);
   if(hres == NULL)
   return false;

   uint32_t dwResSize = ::SizeofResource(hinst, hrsrc);

   if(hres != NULL)
   {
   UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
   try
   {
   storage.set_data(lpnRes, dwResSize);
   }
   catch(::core::file_exception_sp * pe)
   {
   #ifdef DEBUG
   //            g_dumpcontext << "File could not be opened " << pe->m_cause << "\n";
   #endif
   }


   #ifndef WIN32 //unlock Resource is obsolete in the Win32 API
   ::UnlockResource(hres);
   #endif
   ::FreeResource(hres);
   }
   return true;*/
   return false;

}

#ifdef WINDOWSEX

HENHMETAFILE application::LoadEnhMetaFile(UINT uiResource)
{
   primitive::memory storage;
   if(!GetResourceData(uiResource, "EnhMetaFile", storage))
   {
      return NULL;
   }
   return SetEnhMetaFileBits((UINT) storage.get_size(), storage.get_data());
}

#endif

/////////////////////////////////////////////////////////////////////////////
// WinApp UI related functions

void application::EnableModelessEx(bool bEnable)
{
   UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
   UNUSED(bEnable);
#endif

   // no-op if main ::user::window is NULL or not a frame_window_interface
   /*      sp(::user::interaction) pMainWnd = System.GetMainWnd();
   if (pMainWnd == NULL || !pMainWnd->is_frame_window())
   return;*/

#ifndef ___NO_OLE_SUPPORT
   // check if notify hook installed
   /*   ::core::frame_window_interface* pFrameWnd =
   dynamic_cast < ::core::frame_window_interface * > (pMainWnd);
   ASSERT(pFrameWnd != NULL);
   if (pFrameWnd->GetNotifyHook() != NULL)
   pFrameWnd->GetNotifyHook()->OnEnableModeless(bEnable);*/
#endif
}


/*id_space * application::GetGenIdSpace()
{
return m_pidspace;
}*/

/*
string application::load_string(const id_space * pspace, int32_t iKey)
{
string str;
int32_t iId = GetResourceId(pspace, iKey);
if(iId == -1)
return str;
str.load_string(iId);
return str;
}
*/





// Main running routine until application exits
int32_t application::run()
{
   /*   if (GetMainWnd() == NULL) // may be a service or console application ::user::window
   {
   // Not launched /Embedding or /Automation, but has no main ::user::window!
   TRACE(::core::trace::category_AppMsg, 0, "Warning: GetMainWnd() is NULL in application::run - quitting application.\n");
   __post_quit_message(0);
   }*/
   //      return application::run();
   return thread::run();
}


/////////////////////////////////////////////////////////////////////////////
// application idle processing
bool application::on_idle(LONG lCount)
{
   /*      if (lCount <= 0)
   {
   thread::on_idle(lCount);

   // call doc-template idle hook
   ::count count = 0;
   if (m_pdocmanager != NULL)
   count = m_pdocmanager->get_template_count();

   for(index index = 0; index < count; index++)
   {
   sp(document_template) ptemplate = m_pdocmanager->get_template(index);
   ASSERT_KINDOF(document_template, ptemplate);
   ptemplate->on_idle();
   }
   }
   else if (lCount == 1)
   {
   VERIFY(!thread::on_idle(lCount));
   }
   return lCount < 1;  // more to do if lCount < 1*/
   return 0;
}

/////////////////////////////////////////////////////////////////////////////
// Special exception handling

void application::ProcessWndProcException(::exception::base* e, signal_details * pobj)
{
   ENSURE_ARG(e != NULL);
   ENSURE_ARG(pobj != NULL);
   SCAST_PTR(::message::base, pbase, pobj);
   // handle certain messages in thread
   switch (pbase->m_uiMessage)
   {
   case WM_CREATE:
   case WM_PAINT:
      return thread::ProcessWndProcException(e, pobj);
   }

   // handle all the rest
   //linux UINT nIDP = __IDP_INTERNAL_FAILURE;   // generic message string
   const char * nIDP = "Internal Failure";
   pbase->set_lresult(0);        // sensible default
   if (pbase->m_uiMessage == WM_COMMAND)
   {
      if (pbase->m_lparam == 0)
         //linux nIDP = __IDP_COMMAND_FAILURE; // command (not from a control)
            nIDP = "Command Failure";
      pbase->set_lresult((LRESULT)TRUE);        // pretend the command was handled
   }
   if (base < memory_exception >::bases(e))
   {
      e->ReportError(MB_ICONEXCLAMATION|MB_SYSTEMMODAL, nIDP);
   }
   else if (base < user_exception >::bases(e))
   {
      // ::fontopus::user has not been alerted yet of this catastrophic problem
      e->ReportError(MB_ICONSTOP, nIDP);
   }
}

bool application::_001OnCmdMsg(base_cmd_msg * pcmdmsg)

{
   if(command_target_interface::_001OnCmdMsg(pcmdmsg))
      return TRUE;
   return 0;
}

string application::get_module_title()
{
   return file_title(get_module_file_path());
}

string application::get_module_name()
{
   return file_name(get_module_file_path());
}

string application::get_local_mutex_id()
{
   return command()->m_varTopicQuery["local_mutex_id"];
}

string application::get_global_mutex_id()
{
   return command()->m_varTopicQuery["global_mutex_id"];
}

bool application::hex_to_memory(primitive::memory & memory, const char * pszHex)
{
   ::count len = strlen(pszHex);
   ::count count = (len + 1) / 2;
   memory.allocate(count);
   index i = 0;
   byte b;
   while(*pszHex != '\0')
   {
      char ch = (char) tolower(*pszHex);
      if(ch >= '0' && ch <= '9')
      {
         b = ch - '0';
      }
      else if(ch >= 'a' && ch <= 'f')
      {
         b = ch - 'a' + 10;
      }
      else
      {
         return false;
      }
      pszHex++;
      if(*pszHex == '\0')
      {
         memory.get_data()[i] = b;
         return true;
      }
      b = b << 4;
      ch = (char) tolower(*pszHex);
      if(ch >= '0' && ch <= '9')
      {
         b |= (ch - '0');
      }
      else if(ch >= 'a' && ch <= 'f')
      {
         b |= (ch - 'a' + 10);
      }
      else
      {
         return false;
      }
      pszHex++;
      memory.get_data()[i] = b;
      i++;
   }
   return true;
}


void application::memory_to_hex(string & strHex, primitive::memory & memory)
{
   ::count count = memory.get_size();
   LPSTR lpsz = strHex.GetBufferSetLength(count * 2);
   for(index i = 0; i < count; i++)
   {
      *lpsz++ = ::hex::lower_from((byte) ((memory.get_data()[i] >> 4) & 0xf));
      *lpsz++ = ::hex::lower_from((byte) (memory.get_data()[i] & 0xf));
   }
   strHex.ReleaseBuffer(count * 2);
}





#include "framework.h"

#ifdef WINDOWS
#include <cderr.h>      // Commdlg Error definitions
#include <winspool.h>
#endif


CLASS_DECL_CORE extern fixed_alloc_array * g_pfixedallocaWstring;

CLASS_DECL_CORE fixed_alloc_array * new_wstring_manager();




// // BEGIN_MESSAGE_MAP(application, command_target)
//{{__MSG_MAP(application)
// Global File commands
//   ON_COMMAND(ID_APP_EXIT, &application::OnAppExit)
// MRU - most recently used file menu
//   ON_UPDATE_COMMAND_UI(ID_FILE_MRU_FILE1, &application::OnUpdateRecentFileMenu)
//   ON_COMMAND_EX_RANGE(ID_FILE_MRU_FILE1, ID_FILE_MRU_FILE16, &application::OnOpenRecentFile)
//}}__MSG_MAP
// // END_MESSAGE_MAP()

/*#ifdef WINDOWS


typedef LANGID (WINAPI*PFNGETUSERDEFAULTUILANGUAGE)();
typedef LANGID (WINAPI*PFNGETSYSTEMDEFAULTUILANGUAGE)();


class CActivationContext
{
protected :
HANDLE m_hCtxt;
uint_ptr m_uCookie;

// If pointers are NULL then we are on a platform that does not support WinSXS.
typedef HANDLE (WINAPI * PFNCreateActCtx)(PCACTCTX);
static PFNCreateActCtx s_pfnCreateActCtx;

typedef void (WINAPI * PFNReleaseActCtx)(HANDLE);
static PFNReleaseActCtx s_pfnReleaseActCtx;

typedef bool (WINAPI * PFNActivateActCtx)(HANDLE, uint_ptr*);
static PFNActivateActCtx s_pfnActivateActCtx;

typedef bool (WINAPI * PFNDeactivateActCtx)(uint32_t, uint_ptr);
static PFNDeactivateActCtx s_pfnDeactivateActCtx;

static bool s_bPFNInitialized;

public:
CActivationContext(HANDLE hCtxt = INVALID_HANDLE_VALUE) : m_hCtxt( hCtxt ), m_uCookie( 0 )
{
// Multiple threads initializing is fine since they will initialize the pointers to the
// same value.
if (!s_bPFNInitialized)
{
HMODULE hKernel = GetModuleHandle("KERNEL32");
ENSURE (hKernel != NULL);
#ifdef _UNICODE
s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxW");
#else
s_pfnCreateActCtx = (PFNCreateActCtx) GetProcAddress(hKernel, "CreateActCtxA");
#endif
s_pfnReleaseActCtx = (PFNReleaseActCtx) GetProcAddress(hKernel, "ReleaseActCtx");
s_pfnActivateActCtx = (PFNActivateActCtx) GetProcAddress(hKernel, "ActivateActCtx");
s_pfnDeactivateActCtx = (PFNDeactivateActCtx) GetProcAddress(hKernel, "DeactivateActCtx");
if (s_pfnCreateActCtx != NULL)
{
// If one of the functions is present then all the functions have to be present.
ENSURE( s_pfnReleaseActCtx != NULL &&
s_pfnActivateActCtx != NULL &&
s_pfnDeactivateActCtx != NULL);
}
else
{
// If one of the functions is not present then all the functions should not be present.
ENSURE( s_pfnReleaseActCtx == NULL &&
s_pfnActivateActCtx == NULL &&
s_pfnDeactivateActCtx == NULL);
}
s_bPFNInitialized = true;
}
};

~CActivationContext()
{
Release();
}

bool create( PCACTCTX pactctx )
{
// NULL on a platform that do not support WinSXS
if (s_pfnCreateActCtx == NULL)
{
return true;
}

ASSERT( pactctx != NULL );
if ( pactctx == NULL )
{
return false;
}

ASSERT( m_hCtxt == INVALID_HANDLE_VALUE );
if ( m_hCtxt != INVALID_HANDLE_VALUE )
{
return false;
}

return ( ( m_hCtxt = s_pfnCreateActCtx( pactctx ) ) != INVALID_HANDLE_VALUE );
}

void Release()
{
// NULL on a platform that do not support WinSXS
if (s_pfnReleaseActCtx == NULL)
{
return;
}

if ( m_hCtxt != INVALID_HANDLE_VALUE )
{
Deactivate();
s_pfnReleaseActCtx( m_hCtxt );
}
}

bool Activate()
{
// NULL on a platform that do not support WinSXS
if (s_pfnActivateActCtx == NULL)
{
return true;
}

ASSERT( m_hCtxt != INVALID_HANDLE_VALUE );
if ( m_hCtxt == INVALID_HANDLE_VALUE )
{
return false;
}

ASSERT( m_uCookie == 0 );
if ( m_uCookie != 0 )
{
return false;
}

return ( s_pfnActivateActCtx( m_hCtxt, &m_uCookie) == TRUE );
}

bool Deactivate()
{
// NULL on a platform that do not support WinSXS
if (s_pfnDeactivateActCtx == NULL)
{
return true;
}

if ( m_uCookie != 0 )
{
uint_ptr uCookie = m_uCookie;
m_uCookie = 0;
return ( s_pfnDeactivateActCtx(0, uCookie) == TRUE );
}
return true;
}
};


CActivationContext::PFNCreateActCtx CActivationContext::s_pfnCreateActCtx = NULL;
CActivationContext::PFNReleaseActCtx CActivationContext::s_pfnReleaseActCtx = NULL;
CActivationContext::PFNActivateActCtx CActivationContext::s_pfnActivateActCtx = NULL;
CActivationContext::PFNDeactivateActCtx CActivationContext::s_pfnDeactivateActCtx = NULL;
bool CActivationContext::s_bPFNInitialized = false;


// HINSTANCE of the module
extern "C" IMAGE_DOS_HEADER __ImageBase;

*/


bool application::LoadSysPolicies()
{
   return _LoadSysPolicies();
}

// This function is not exception safe - will leak a registry key if exceptions are thrown from some places
// To reduce risk of leaks, I've declared the whole function throw(). This despite the fact that its callers have
// no dependency on non-throwing.
bool application::_LoadSysPolicies() throw()
{

#ifdef WINDOWSEX

   HKEY hkPolicy = NULL;
   DWORD dwValue = 0;
   DWORD dwDataLen = sizeof(dwValue);
   DWORD dwType = 0;

   // clear current policy settings.
   m_dwPolicies = ___SYSPOLICY_NOTINITIALIZED;

   static __system_policy_data rgExplorerData[] =
   {
      {"NoRun", ___SYSPOLICY_NORUN},
      {"NoDrives", ___SYSPOLICY_NODRIVES},
      {"RestrictRun", ___SYSPOLICY_RESTRICTRUN},
      {"NoNetConnectDisconnect", ___SYSPOLICY_NONETCONNECTDISCONNECTD},
      {"NoRecentDocsHistory", ___SYSPOLICY_NORECENTDOCHISTORY},
      {"NoClose", ___SYSPOLICY_NOCLOSE},
      {NULL, 0}
   };

   static __system_policy_data rgNetworkData[] =
   {
      {"NoEntireNetwork", ___SYSPOLICY_NOENTIRENETWORK},
      {NULL, 0}
   };

   static __system_policy_data rgComDlgData[] =
   {
      {"NoPlacesBar", ___SYSPOLICY_NOPLACESBAR},
      {"NoBackButton", ___SYSPOLICY_NOBACKBUTTON},
      {"NoFileMru", ___SYSPOLICY_NOFILEMRU},
      {NULL, 0}
   };

   static __system_policies rgPolicies[] =
   {
      {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer",
      rgExplorerData},
      {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Network",
      rgNetworkData},
      {"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Comdlg32",
      rgComDlgData},
      {NULL, 0}
   };

   __system_policies *pPolicies = rgPolicies;
   __system_policy_data *pData = NULL;

   while (pPolicies->szPolicyKey != NULL)
   {

      if (ERROR_SUCCESS == ::RegOpenKeyEx(
         HKEY_CURRENT_USER,
         pPolicies->szPolicyKey,
         0,
         KEY_QUERY_VALUE,
         &hkPolicy
         ))
      {
         pData = pPolicies->pData;
         while (pData->szPolicyName)
         {
            if (ERROR_SUCCESS == ::RegQueryValueEx(
               hkPolicy,
               pData->szPolicyName,
               NULL,
               &dwType,
               (BYTE*)&dwValue,
               &dwDataLen))
            {
               if (dwType == REG_DWORD)
               {
                  if (dwValue != 0)
                     m_dwPolicies |= pData->dwID;
                  else
                     m_dwPolicies &= ~pData->dwID;
               }
            }
            dwValue = 0;
            dwDataLen = sizeof(dwValue);
            dwType = 0;
            pData++;
         }
         ::RegCloseKey(hkPolicy);
         hkPolicy = NULL;
      }
      pPolicies++;
   };

#endif

   return TRUE;


}

bool application::GetSysPolicyValue(uint32_t dwPolicyID, bool *pbValue)
{
   if (!pbValue)
      return FALSE; // bad pointer
   *pbValue = (m_dwPolicies & dwPolicyID) != 0;
   return TRUE;
}

bool application::InitApplication()
{
   /*if(::get_app() == NULL)
   {
   ::set_app(get_system());
   systemsp(::application) pApp = dynamic_cast < systemsp(::application) > (::get_app());
   thread * pThread = ::get_app();
   // App global initializations (rare)
   if (pApp != NULL && !pApp->InitApplication())
   goto InitFailure;

   pThread->translator::attach();

   // Perform specific initializations
   try
   {
   try
   {
   if(!pApp->process_initialize())
   {
   if (pThread->GetMainWnd() != NULL)
   {
   TRACE(::core::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
   pThread->GetMainWnd()->DestroyWindow();
   }
   goto InitFailure;
   }
   }
   catch(const ::exception::exception &)
   {
   if (pThread->GetMainWnd() != NULL)
   {
   pThread->GetMainWnd()->DestroyWindow();
   pThread->SetMainWnd(NULL);
   }
   goto InitFailure;
   }
   try
   {
   if(!pThread->initialize_instance())
   {
   if (pThread->GetMainWnd() != NULL)
   {
   TRACE(::core::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
   pThread->GetMainWnd()->DestroyWindow();
   }
   pThread->exit_instance();
   goto InitFailure;
   }
   }
   catch(const ::exception::exception &)
   {
   if(pThread->on_run_exception((::exception::exception &) e))
   goto run;
   if (pThread->GetMainWnd() != NULL)
   {
   TRACE(::core::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
   try
   {
   pThread->GetMainWnd()->DestroyWindow();
   }
   catch(::exception::exception &)
   {
   }
   pThread->SetMainWnd(NULL);
   }
   if(pApp->final_handle_exception((::exception::exception &) e))
   goto run;
   if (pThread->GetMainWnd() != NULL)
   {
   TRACE(::core::trace::category_AppMsg, 0, "Warning: Destroying non-NULL GetMainWnd()\n");
   try
   {
   pThread->GetMainWnd()->DestroyWindow();
   }
   catch(::exception::exception &)
   {
   }
   pThread->SetMainWnd(NULL);
   }
   pThread->exit_instance();
   goto InitFailure;
   }

   }
   catch(...)
   {
   }
   }
   run:*/

   LoadSysPolicies();

   return TRUE;

   /*InitFailure:

   return FALSE;*/

}



/*   void application::LoadStdProfileSettings(UINT nMaxMRU)
{
UNREFERENCED_PARAMETER(nMaxMRU);
ASSERT_VALID(this);

// 0 by default means not set
m_nNumPreviewPages = GetProfileInt(gen_PreviewSection, gen_PreviewEntry, 0);
}*/

/*void application::ParseCommandLine(CCommandLineInfo& rCmdInfo)
{
for (int32_t i = 1; i < __argc; i++)
{
const char * pszParam = __targv[i];
bool bFlag = FALSE;
bool bLast = ((i + 1) == __argc);
if (pszParam[0] == '-' || pszParam[0] == '/')
{
// remove flag specifier
bFlag = TRUE;
++pszParam;
}
rCmdInfo.ParseParam(pszParam, bFlag, bLast);
}
}*/

/////////////////////////////////////////////////////////////////////////////
// CCommandLineInfo implementation

/*CCommandLineInfo::CCommandLineInfo()
{
m_bShowSplash = TRUE;
m_bRunEmbedded = FALSE;
m_bRunAutomated = FALSE;
m_nShellCommand = FileNew;
}

CCommandLineInfo::~CCommandLineInfo()
{
}

void CCommandLineInfo::ParseParam(const char* pszParam,bool bFlag,bool bLast)
{
if (bFlag)
{
const astring strParam(pszParam);
ParseParamFlag(strParam.GetString());
}
else
ParseParamNotFlag(pszParam);

ParseLast(bLast);
}*/

/*
#ifdef UNICODE
void CCommandLineInfo::ParseParam(const char* pszParam, bool bFlag, bool bLast)
{
if (bFlag)
ParseParamFlag(pszParam);
else
ParseParamNotFlag(pszParam);

ParseLast(bLast);
}
#endif // UNICODE
*/

/*
void CCommandLineInfo::ParseParamFlag(const char* pszParam)
{
// OLE command switches are case insensitive, while
// shell command switches are case sensitive

if (lstrcmpA(pszParam, "pt") == 0)
m_nShellCommand = FilePrintTo;
else if (lstrcmpA(pszParam, "p") == 0)
m_nShellCommand = FilePrint;
else if (::__invariant_stricmp(pszParam, "Register") == 0 ||
::__invariant_stricmp(pszParam, "Regserver") == 0)
m_nShellCommand = AppRegister;
else if (::__invariant_stricmp(pszParam, "Unregister") == 0 ||
::__invariant_stricmp(pszParam, "Unregserver") == 0)
m_nShellCommand = AppUnregister;
else if (lstrcmpA(pszParam, "dde") == 0)
{
m_nShellCommand = FileDDE;
}
else if (::__invariant_stricmp(pszParam, "Embedding") == 0)
{
m_bRunEmbedded = TRUE;
m_bShowSplash = FALSE;
}
else if (::__invariant_stricmp(pszParam, "Automation") == 0)
{
m_bRunAutomated = TRUE;
m_bShowSplash = FALSE;
}
}

void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
{
if (m_strFileName.is_empty())
m_strFileName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
m_strPrinterName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
m_strDriverName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
m_strPortName = pszParam;
}

#ifdef UNICODE
void CCommandLineInfo::ParseParamNotFlag(const char* pszParam)
{
if (m_strFileName.is_empty())
m_strFileName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strPrinterName.is_empty())
m_strPrinterName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strDriverName.is_empty())
m_strDriverName = pszParam;
else if (m_nShellCommand == FilePrintTo && m_strPortName.is_empty())
m_strPortName = pszParam;
}
#endif

void CCommandLineInfo::ParseLast(bool bLast)
{
if (bLast)
{
if (m_nShellCommand == FileNew && !m_strFileName.is_empty())
m_nShellCommand = FileOpen;
m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
}
}
*/

/////////////////////////////////////////////////////////////////////////////
// App termination

void application::SaveStdProfileSettings()
{
   ASSERT_VALID(this);


   //      if (m_nNumPreviewPages != 0)
   //       WriteProfileInt(gen_PreviewSection, gen_PreviewEntry, m_nNumPreviewPages);
}






#ifdef WINDOWSEX


/////////////////////////////////////////////////////////////////////////////
// WinHelp Helper


void application::WinHelp(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   sp(::user::interaction) pMainWnd = System.GetMainWnd();
   ENSURE_VALID(pMainWnd);

   // return global cast help mode state to FALSE (backward compatibility)
   m_bHelpMode = FALSE;
   // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

   //trans pMainWnd->WinHelp(dwData, nCmd);
}

/////////////////////////////////////////////////////////////////////////////
// HtmlHelp Helper

void application::HtmlHelp(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   sp(::user::interaction) pMainWnd = System.GetMainWnd();
   ENSURE_VALID(pMainWnd);

   // return global cast help mode state to FALSE (backward compatibility)
   m_bHelpMode = FALSE;
   // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update

   // trans pMainWnd->HtmlHelp(dwData, nCmd);
}


void application::WinHelpInternal(uint_ptr dwData, UINT nCmd)
{
   UNREFERENCED_PARAMETER(dwData);
   UNREFERENCED_PARAMETER(nCmd);
   //   sp(::user::interaction) pMainWnd = System.GetMainWnd();
   //   ENSURE_VALID(pMainWnd);

   // return global cast help mode state to FALSE (backward compatibility)
   m_bHelpMode = FALSE;
   // trans pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update
   // trans pMainWnd->WinHelpInternal(dwData, nCmd);
}


#endif





/////////////////////////////////////////////////////////////////////////////
// application idle processing

void application::DevModeChange(LPTSTR lpDeviceName)
{
   UNREFERENCED_PARAMETER(lpDeviceName);

#ifdef WINDOWS
   if (m_hDevNames == NULL)
      return;

#endif

}



bool application::on_run_exception(::exception::exception & e)
{

   TRACE("An unexpected error has occurred and no special exception handling is available.");

   if(typeid(e) == typeid(not_installed))
   {

      not_installed & notinstalled = dynamic_cast < not_installed & > (e);

      if(::is_debugger_attached())
      {

         try
         {

            if(!(bool)System.oprop("not_installed_message_already_shown"))
            {

               MessageBox(NULL, "Debug only message, please install:\n\n\n\t" + notinstalled.m_strId + "\n\ttype = " + notinstalled.m_strType + "\n\tlocale = " + notinstalled.m_strLocale + "\n\tschema = " + notinstalled.m_strSchema + "\n\tbuild number = " + notinstalled.m_strBuild + "\n\n\nThere are helper scripts under <solution directory>/nodeapp/stage/install/", "Debug only message, please install.", MB_ICONINFORMATION | MB_OK);

               System.oprop("not_installed_message_already_shown") = true;

            }

         }
         catch(...)
         {

         }

      }
      else
      {

         hotplugin::host::starter_start_sync(": app=session session_start=" + notinstalled.m_strId + " app_type=" + notinstalled.m_strType + " install locale=" + notinstalled.m_strLocale + " schema=" + notinstalled.m_strSchema, NULL);

      }

      return false;

   }

   //simple_message_box_timeout("An unexpected error has occurred and no special exception handling is available.<br>Timeout: $simple_message_box_timeout", 5000);

   return true; // continue or exit application? by default: continue by returning true

}



HCURSOR application::LoadStandardCursor(const char * lpszCursorName) const
{

#ifdef WINDOWSEX

   return ::LoadCursor(NULL, lpszCursorName);

#else

   return NULL;

#endif

}


bool application::ca_process_initialize()
{
   application_signal_details signal(this, m_psignal, application_signal_process_initialize);
   m_psignal->emit(&signal);
   return true;
}

bool application::ca_initialize1()
{
   application_signal_details signal(this, m_psignal, application_signal_initialize1);
   m_psignal->emit(&signal);
   return signal.m_bOk;
}



bool application::ca_finalize()
{
   application_signal_details signal(this, m_psignal, application_signal_finalize);
   try
   {
      m_psignal->emit(&signal);
   }
   catch(...)
   {
   }




   return signal.m_bOk;
}



bool application::final_handle_exception(::exception::exception & e)
{
   UNREFERENCED_PARAMETER(e);
   //linux      exit(-1);

   if(!is_system())
   {

      // get_app() may be it self, it is ok...
      if(Sys(get_app()).final_handle_exception((::exception::exception & ) e))
         return true;


   }

   return false;
}


/*   bool application::open_link(const char * pszLink, const char * pszTarget)
{
UNREFERENCED_PARAMETER(pszLink);
UNREFERENCED_PARAMETER(pszTarget);
return false;
}
*/



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
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
   MutexAttributes.nLength = sizeof( MutexAttributes );
   MutexAttributes.bInheritHandle = FALSE; // object uninheritable
   // declare and initialize a security descriptor
   SECURITY_DESCRIPTOR SD;
   bool bInitOk = InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION) != FALSE;
   if ( bInitOk )
   {
      // give the security descriptor a Null Dacl
      // done using the  "TRUE, (PACL)NULL" here
      bSetOk = SetSecurityDescriptorDacl( &SD,
         TRUE,
         (PACL)NULL,
         FALSE ) != FALSE;
   }

   if(bSetOk)
   {

      MutexAttributes.lpSecurityDescriptor = &SD;

      lpsa = &MutexAttributes;

   }

#else

   bSetOk = true;

#endif

   if ( bSetOk )
   {
      // Make the security attributes point
      // to the security descriptor
      bResourceException = false;
      try
      {
         m_pmutexGlobal = new mutex(this, FALSE, get_global_mutex_name(), lpsa);
      }
      catch(resource_exception &)
      {
         try
         {
            m_pmutexGlobal = new mutex(this, FALSE, get_global_mutex_name());
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
            m_pmutexGlobalId = new mutex(this, FALSE, get_global_id_mutex_name(), lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexGlobalId = new mutex(this, FALSE, get_global_id_mutex_name());
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
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName)+ "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");
            on_exclusive_instance_conflict(ExclusiveInstanceGlobalId);
            return false;
         }
      }
      bResourceException = false;
      try
      {
         m_pmutexLocal = new mutex(this, FALSE, get_local_mutex_name(), lpsa);
      }
      catch(resource_exception &)
      {
         try
         {
            m_pmutexLocal = new mutex(this, FALSE, get_local_mutex_name());
         }
         catch(resource_exception & )
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
            m_pmutexLocalId = new mutex(this, FALSE, get_local_id_mutex_name(), lpsa);
         }
         catch(resource_exception &)
         {
            try
            {
               m_pmutexLocalId = new mutex(this, FALSE, get_local_id_mutex_name());
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

string application::get_mutex_name_gen()
{
   return m_strAppName;
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


::user::interaction_ptr_array & application::frames()
{
   return *m_pframea;
}

void application::add_frame(sp(::user::interaction) pwnd)
{
   m_pframea->add_unique(pwnd);
}

void application::remove_frame(sp(::user::interaction) pwnd)
{
   m_pframea->remove(pwnd);
   if(GetMainWnd() == pwnd)
   {
      if(m_pframea->get_size() > 0)
      {
         SetMainWnd(m_pframea->element_at(0));
      }
      else
      {
         SetMainWnd(NULL);
      }
   }
}


void application::delete_temp()
{

}

// This is core API library.
//
//
//
//
//
//
//
//


void application::_001OnFileNew()
{
   /*      if (m_pdocmanager != NULL)
   m_pdocmanager->_001OnFileNew();*/
}

void application::on_file_open()
{
   ENSURE(m_pdocmanager != NULL);
   //m_pdocmanager->on_file_open();
}

// prompt for file name - used for open and save as
bool application::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::document_template) ptemplate, sp(::user::document_interface) pdocument)
   // if ptemplate==NULL => all document templates
{
   if(m_pfilemanager != NULL)
   {
      return m_pfilemanager->do_prompt_file_name(varFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);
   }
   ENSURE(m_pdocmanager != NULL);
   /*      return m_pdocmanager->do_prompt_file_name(fileName, nIDSTitle, lFlags,
   bOpenFileDialog, ptemplate);*/
   return FALSE;
}

// This is core API library.
//
//
//
//
//
//
//
//




/*void ::core::FormatString1(string & rString, UINT nIDS, const char * lpsz1)
{
__format_strings(rString, nIDS, &lpsz1, 1);
}

void ::core::FormatString2(string & rString, UINT nIDS, const char * lpsz1,
const char * lpsz2)
{
const char * rglpsz[2];
rglpsz[0] = lpsz1;
rglpsz[1] = lpsz2;
__format_strings(rString, nIDS, rglpsz, 2);
}*/

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Basic Help support (for backward compatibility to core API 2.0)

void application::OnHelp()  // use context to derive help context
{
   if (m_dwPromptContext != 0)
   {
      // do not call WinHelp when the error is failing to lauch help
      //         if (m_dwPromptContext != HID_BASE_PROMPT+__IDP_FAILED_TO_LAUNCH_HELP)
      //          WinHelpInternal(m_dwPromptContext);
      return;
   }

   // otherwise, use ::user::window::OnHelp implementation
   /* trans sp(::user::window) pWnd = System.GetMainWnd();
   ENSURE_VALID(pWnd);
   if (!pWnd->is_frame_window())
   pWnd->OnHelp();
   else
   ((pWnd))->OnHelp();*/
}


void application::OnHelpIndex()
{

#ifdef WINDOWSEX

   WinHelpInternal(0L, HELP_INDEX);

#endif

}


void application::OnHelpFinder()
{

#ifdef WINDOWSEX

   WinHelpInternal(0L, HELP_FINDER);

#endif

}


void application::OnHelpUsing()
{

#ifdef WINDOWSEX

   WinHelpInternal(0L, HELP_HELPONHELP);

#endif

}


/////////////////////////////////////////////////////////////////////////////
// Context Help Mode support (backward compatibility to core API 2.0)

void application::OnContextHelp()
{
   // just use frame_window::OnContextHelp implementation
   /* trans   m_bHelpMode = HELP_ACTIVE;
   sp(::user::frame_window) pMainWnd = (System.GetMainWnd());
   ENSURE_VALID(pMainWnd);
   ENSURE(pMainWnd->is_frame_window());
   pMainWnd->OnContextHelp();
   m_bHelpMode = pMainWnd->m_bHelpMode;
   pMainWnd->PostMessage(WM_KICKIDLE); // trigger idle update */
}

/////////////////////////////////////////////////////////////////////////////


// This is core API library.
//
//
//
//
//
//
//
//




/////////////////////////////////////////////////////////////////////////////
// WinApp support for printing

/*bool application::GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg)
{
UpdatePrinterSelection(m_hDevNames == NULL); //force default if no current
if (m_hDevNames == NULL)
return FALSE;               // no printer defaults

ENSURE_ARG(pPrintDlg != NULL);
pPrintDlg->hDevNames = m_hDevNames;
pPrintDlg->hDevMode = m_hDevMode;

::GlobalUnlock(m_hDevNames);
::GlobalUnlock(m_hDevMode);
return TRUE;
}*/

void application::UpdatePrinterSelection(bool bForceDefaults)
{
   UNREFERENCED_PARAMETER(bForceDefaults);
}


void application::OnFilePrintSetup()
{
}

void application::SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld)
{
   UNREFERENCED_PARAMETER(hDevNames);
   UNREFERENCED_PARAMETER(hDevMode);
   UNREFERENCED_PARAMETER(bFreeOld);
   throw not_implemented(get_app());
   /*if (m_hDevNames != hDevNames)
   {
   if (m_hDevNames != NULL && bFreeOld)
   __global_free(m_hDevNames);
   m_hDevNames = hDevNames;
   }
   if (m_hDevMode != hDevMode)
   {
   if (m_hDevMode != NULL && bFreeOld)
   __global_free(m_hDevMode);
   m_hDevMode = hDevMode;
   }*/
}

::draw2d::graphics * application::CreatePrinterDC()
{
   //      UNREFERENCED_PARAMETER(spgraphics);
   throw not_implemented(get_app());
   /*
   HDC hDC = ::core::CreateDC(m_hDevNames, m_hDevMode);
   if (hDC != NULL)
   {
   spgraphics->DeleteDC();
   bool bRet = spgraphics->attach(hDC);
   ASSERT(bRet);
   return bRet;
   }*/
   //return FALSE;
}

/////////////////////////////////////////////////////////////////////////////


// This is core API library.
//
//
//
//
//
//
//
//



/////////////////////////////////////////////////////////////////////////////
// application User Interface Extensions

void application::OnAppExit()
{

   // same as double-clicking on main ::user::window close box

   ASSERT(GetMainWnd() != NULL);

   GetMainWnd()->send_message(WM_CLOSE);

}


void application::HideApplication()
{
   try
   {
      if(GetMainWnd() == NULL)
         return;

      // hide the application's windows before closing all the documents
      GetMainWnd()->ShowWindow(SW_HIDE);
      // trans    GetMainWnd()->ShowOwnedPopups(FALSE);

      // put the ::user::window at the bottom of zorder, so it isn't activated
      GetMainWnd()->SetWindowPos(ZORDER_BOTTOM, 0, 0, 0, 0,
         SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
   }
   catch(...)
   {
   }

}


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

   if(::application_base::m_p == NULL)
      return;

   ::application_base::m_p->ShowWaitCursor(bShow);

}



bool application::save_all_modified()
{
   /*      if (m_pdocmanager != NULL)
   return m_pdocmanager->save_all_modified();*/
   return TRUE;
}

void application::close_all_documents(bool bEndSession)
{
   /*if (m_pdocmanager != NULL)
   m_pdocmanager->close_all_documents(bEndSession);*/
}


bool application::OnDDECommand(LPTSTR lpszCommand)
{
   /*      if (m_pdocmanager != NULL)
   return m_pdocmanager->OnDDECommand(lpszCommand);
   else*/
   return FALSE;
}



void application::EnableModeless(bool bEnable)
{
   DoEnableModeless(bEnable);
}

void application::DoEnableModeless(bool bEnable)
{
   UNREFERENCED_PARAMETER(bEnable);
#ifdef ___NO_OLE_SUPPORT
   UNUSED(bEnable);
#endif

   // no-op if main ::user::window is NULL or not a frame_window
   /*   sp(::user::interaction) pMainWnd = System.GetMainWnd();
   if (pMainWnd == NULL || !pMainWnd->is_frame_window())
   return;*/

#ifndef ___NO_OLE_SUPPORT
   // check if notify hook installed
   /*xxx
   ASSERT_KINDOF(frame_window, pMainWnd);
   sp(::user::frame_window) pFrameWnd = (sp(::user::frame_window))pMainWnd;
   if (pFrameWnd->m_pNotifyHook != NULL)
   pFrameWnd->m_pNotifyHook->OnEnableModeless(bEnable);
   */
#endif
}

int32_t application::DoMessageBox(const char * lpszPrompt, UINT nType, UINT nIDPrompt)
{
   return ShowAppMessageBox(this, lpszPrompt, nType, nIDPrompt);
}

int32_t application::simple_message_box_timeout(sp(::user::interaction) pwndOwner, const char * pszMessage, ::duration durationTimeOut,  UINT fuStyle)
{
   UNREFERENCED_PARAMETER(durationTimeOut);
   return simple_message_box(pwndOwner, pszMessage, fuStyle);
}

int32_t application::simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle)
{

#if defined(WINDOWSEX)

   return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
      wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(MACOS) || defined(ANDROID)

   return MessageBox((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

   return MessageBox(m_psystem->m_pui->get_handle(), pszMessage, m_strAppName, fuStyle);

#endif

}

#ifdef WINDOWS

int32_t application::simple_message_box(sp(::user::interaction) pwndOwner,  UINT fuStyle, const char * pszFormat, ...)
{
   va_list va;
   va_start(va, pszFormat);
   string str;
   str.FormatV(pszFormat, va);
   va_end(va);
   return simple_message_box(pwndOwner, str, fuStyle);
}

#endif


// Helper for message boxes; can work when no application can be found
int32_t application::ShowAppMessageBox(sp(application)pApp, const char * lpszPrompt, UINT nType, UINT nIDPrompt)
{

   throw not_implemented(pApp);

   /*
   // disable windows for modal dialog
   DoEnableModeless(FALSE);
   ::oswindow oswindow_Top;
   ::oswindow oswindow = ::user::window::get_safe_owner(NULL, &oswindow_Top);

   // re-enable the parent ::user::window, so that focus is restored
   // correctly when the dialog is dismissed.
   if (oswindow != oswindow_Top)
   EnableWindow(oswindow, TRUE);

   // set help context if possible
   uint32_t* pdwContext = NULL;

   #ifdef WINDOWS

   {

   uint32_t dwWndPid=0;
   GetWindowThreadProcessId(oswindow, &dwWndPid);

   if (oswindow != NULL && dwWndPid==GetCurrentProcessId() )
   {
   // use cast-level context or frame level context
   LRESULT lResult = ::SendMessage(oswindow, WM_HELPPROMPTADDR, 0, 0);
   if (lResult != 0)
   pdwContext = (uint32_t*)lResult;
   }

   }

   #endif
   // for backward compatibility use cast context if possible
   if (pdwContext == NULL && pApp != NULL)
   pdwContext = &pApp->m_dwPromptContext;

   uint32_t dwOldPromptContext = 0;
   if (pdwContext != NULL)
   {
   // save old prompt context for restoration later
   dwOldPromptContext = *pdwContext;
   if (nIDPrompt != 0)
   *pdwContext = HID_BASE_PROMPT+nIDPrompt;
   }

   // determine icon based on type specified
   if ((nType & MB_ICONMASK) == 0)
   {
   switch (nType & MB_TYPEMASK)
   {
   case MB_OK:
   case MB_OKCANCEL:
   nType |= MB_ICONEXCLAMATION;
   break;

   case MB_YESNO:
   case MB_YESNOCANCEL:
   nType |= MB_ICONQUESTION;
   break;

   case MB_ABORTRETRYIGNORE:
   case MB_RETRYCANCEL:
   // No default icon for these types, since they are rarely used.
   // The caller should specify the icon.
   break;
   }
   }

   #ifdef DEBUG
   //    if ((nType & MB_ICONMASK) == 0)
   //         TRACE(::core::trace::category_AppMsg, 0, "Warning: no icon specified for message box.\n");
   #endif

   char szAppName[_MAX_PATH];
   szAppName[0] = '\0';
   const char * pszAppName;
   if (pApp != NULL)
   pszAppName = pApp->m_strAppName;
   else
   {

   #ifdef WINDOWS
   pszAppName = szAppName;
   uint32_t dwLen = GetModuleFileName(NULL, szAppName, _MAX_PATH);
   if (dwLen == _MAX_PATH)
   szAppName[_MAX_PATH - 1] = '\0';
   #else

   throw not_implemented(get_thread_app());

   #endif
   }

   int32_t nResult;
   if(pApp == NULL)
   {
   nResult = ::MessageBox(oswindow, lpszPrompt, pszAppName, nType);
   }
   else
   {
   nResult = pApp->simple_message_box(pApp->window_from_os_data, lpszPrompt, nType);
   }

   // restore prompt context if possible
   if (pdwContext != NULL)
   *pdwContext = dwOldPromptContext;

   // re-enable windows
   if (oswindow_Top != NULL)
   ::EnableWindow(oswindow_Top, TRUE);

   DoEnableModeless(TRUE);

   return nResult;
   */
}


/* int32_t ::core::MessageBox(const char * lpszText, UINT nType, UINT nIDHelp)
{
application* papp = &System;
if (papp != NULL)
{
return papp->m_pplaneapp->DoMessageBox(lpszText, nType, nIDHelp);
}
else
{
return application::ShowAppMessageBox(NULL, lpszText, nType, nIDHelp);
}
}
*/

/*int32_t System.simple_message_box(UINT nIDPrompt, UINT nType, UINT nIDHelp)
{
string string;
if (!string.load_string(nIDPrompt))
{
TRACE(::core::trace::category_AppMsg, 0, "Error: failed to load message box prompt string 0x%04x.\n",
nIDPrompt);
ASSERT(FALSE);
}
if (nIDHelp == (UINT)-1)
nIDHelp = nIDPrompt;
return System.simple_message_box(string, nType, nIDHelp);
}*/



/////////////////////////////////////////////////////////////////////////////


sp(::user::interaction) application::get_active_guie()
{

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

   return window_from_os_data(::GetActiveWindow());

#else

   if(frames().get_size() <= 0)
      return NULL;

   return frames()(0);

#endif

}


sp(::user::interaction) application::get_focus_guie()
{

#ifdef METROWIN

   return GetFocus()->window();

#elif defined(WINDOWSEX) || defined(LINUX)

   sp(::user::window) pwnd = System.window_from_os_data_permanent(::GetFocus());
   if(pwnd != NULL)
   {
      if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
         || ::user::window_util::IsAscendant(System.get_active_guie()->get_safe_handle(), pwnd->get_safe_handle()))
      {
         return pwnd;
      }
      else
      {
         return NULL;
      }
   }
   pwnd = System.window_from_os_data(::GetFocus());
   if(pwnd != NULL)
   {
      if(System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
         || ::user::window_util::IsAscendant(System.get_active_guie()->get_safe_handle(), pwnd->get_safe_handle()))
      {
         return pwnd;
      }
      else
      {
         return NULL;
      }
   }
   return NULL;

#else

   return System.get_active_guie();

#endif

}





/*bool application::ProcessShellCommand(CCommandLineInfo& rCmdInfo)
{
bool bResult = TRUE;
switch (rCmdInfo.m_nShellCommand)
{
case CCommandLineInfo::FileNew:
if (!System._001SendCommand("file::new"))
_001OnFileNew();
if (GetMainWnd() == NULL)
bResult = FALSE;
break;

// If we've been asked to open a file, call open_document_file()

case CCommandLineInfo::FileOpen:
if (!open_document_file(rCmdInfo.m_strFileName))
bResult = FALSE;
break;

// If the ::fontopus::user wanted to print, hide our main ::user::window and
// fire a message to ourselves to start the printing

case CCommandLineInfo::FilePrintTo:
case CCommandLineInfo::FilePrint:
m_nCmdShow = SW_HIDE;
ASSERT(m_pCmdInfo == NULL);
if(open_document_file(rCmdInfo.m_strFileName))
{
m_pCmdInfo = &rCmdInfo;
ENSURE_VALID(GetMainWnd());
GetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_PRINT_DIRECT);
m_pCmdInfo = NULL;
}
bResult = FALSE;
break;

// If we're doing DDE, hide ourselves

case CCommandLineInfo::FileDDE:
m_pCmdInfo = (CCommandLineInfo*)(uint_ptr)m_nCmdShow;
m_nCmdShow = SW_HIDE;
break;

// If we've been asked to register, exit without showing UI.
// Registration was already done in initialize_instance().
case CCommandLineInfo::AppRegister:
{
Register();
bResult = FALSE;    // that's all we do

// If nobody is using it already, we can use it.
// We'll flag that we're unregistering and not save our state
// on the way out. This new object gets deleted by the
// cast object destructor.

if (m_pCmdInfo == NULL)
{
m_pCmdInfo = new CCommandLineInfo;
m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
}
break;
}

// If we've been asked to unregister, unregister and then terminate
case CCommandLineInfo::AppUnregister:
{
bool bUnregistered = Unregister();

// if you specify /EMBEDDED, we won't make an success/failure box
// this use of /EMBEDDED is not related to OLE

if (!rCmdInfo.m_bRunEmbedded)
{
/* linux
if (bUnregistered)
System.simple_message_box(__IDP_UNREG_DONE);
else
System.simple_message_box(__IDP_UNREG_FAILURE);
*/

/*if (bUnregistered)
System.simple_message_box("System unregistered");
else
System.simple_message_box("Failed to unregister application");

}
bResult = FALSE;    // that's all we do

// If nobody is using it already, we can use it.
// We'll flag that we're unregistering and not save our state
// on the way out. This new object gets deleted by the
// cast object destructor.

if (m_pCmdInfo == NULL)
{
m_pCmdInfo = new CCommandLineInfo;
m_pCmdInfo->m_nShellCommand = CCommandLineInfo::AppUnregister;
}
}
break;
}
return bResult;
}*/

/*   void application::InitLibId()
{
}

bool application::Register()
{
return TRUE;
}

bool application::Unregister()
{
HKEY    hKey = 0;
char   szBuf[_MAX_PATH+1];
LONG    cSize = 0;
bool    bRet = TRUE;

/*xxx POSITION pos = get_template_count();
while (pos != NULL)
{
sp(document_template) pTempl = get_template(pos);
if (pTempl != NULL)
pTempl->_001OnCommand(0, CN_OLE_UNREGISTER, NULL, NULL);
}*/

// remove profile information -- the registry entries exist if
// SetRegistryKey() was used.

/*    if (m_pszRegistryKey)
{
ENSURE(m_pszProfileName != NULL);

string strKey = "Software\\";
strKey += m_pszRegistryKey;
string strSubKey = strKey + "\\" + m_pszProfileName;

DelRegTree(HKEY_CURRENT_USER, strSubKey);

// If registry key is is_empty then remove it

uint32_t   dwResult;
if ((dwResult = ::RegOpenKey(HKEY_CURRENT_USER, strKey, &hKey)) ==
ERROR_SUCCESS)
{
if (::RegEnumKey(hKey, 0, szBuf, _MAX_PATH) == ERROR_NO_MORE_ITEMS)
DelRegTree(HKEY_CURRENT_USER, strKey);
::RegCloseKey(hKey);
}
if (RegQueryValue(HKEY_CURRENT_USER, strSubKey, szBuf, &cSize) == ERROR_SUCCESS)
bRet = TRUE;
}
return bRet;
}*/

//   LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName);

// Under Win32, a reg key may not be deleted unless it is is_empty.
// Thus, to delete a tree,  one must recursively enumerate and
// delete all of the sub-keys.

/*LONG application::DelRegTree(HKEY hParentKey, const string & strKeyName)
{
return delete_registry_tree_helper(hParentKey, strKeyName);
}

LONG delete_registry_tree_helper(HKEY hParentKey, const string & strKeyName)
{
char   szSubKeyName[MAX_PATH + 1];
HKEY    hCurrentKey;
uint32_t   dwResult;

if ((dwResult = RegOpenKey(hParentKey, strKeyName, &hCurrentKey)) ==
ERROR_SUCCESS)
{
// remove all subkeys of the key to delete
while ((dwResult = RegEnumKey(hCurrentKey, 0, szSubKeyName, MAX_PATH)) ==
ERROR_SUCCESS)
{
try
{
// temp string constructed from szSubKeyName can throw in Low Memory condition.
if ((dwResult = delete_registry_tree_helper(hCurrentKey, szSubKeyName)) != ERROR_SUCCESS)
break;
}
catch(memory_exception* e)
{
dwResult = ERROR_NOT_ENOUGH_MEMORY;
e->Delete();
break;
}
}

// If all went well, we should now be able to delete the requested key
if ((dwResult == ERROR_NO_MORE_ITEMS) || (dwResult == ERROR_BADKEY))
{
dwResult = RegDeleteKey(hParentKey, strKeyName);
}
RegCloseKey(hCurrentKey);
}

return dwResult;
}*/

//void application::EnableShellOpen()
//{
/*   ASSERT(m_atomApp == NULL && m_atomSystemTopic == NULL); // do once
if (m_atomApp != NULL || m_atomSystemTopic != NULL)
{
return;
}

// Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
// int16_t file name so we need to use the int16_t file name.
string strShortName;
__get_module_short_file_name(System.m_hInstance, strShortName);

// strip out path
string strFileName = ::PathFindFileName(strShortName);
// strip out extension
LPTSTR pszFileName = strFileName.GetBuffer();
::PathRemoveExtension(pszFileName);
strFileName.ReleaseBuffer();

m_atomApp = ::GlobalAddAtom(strFileName);
m_atomSystemTopic = ::GlobalAddAtom("system");*/
//}

void application::RegisterShellFileTypes(bool bCompat)
{
   ENSURE(m_pdocmanager != NULL);
   //      m_pdocmanager->RegisterShellFileTypes(bCompat);
}

void application::UnregisterShellFileTypes()
{
   ENSURE(m_pdocmanager != NULL);
   //    m_pdocmanager->UnregisterShellFileTypes();
}


int32_t application::get_open_document_count()
{
   ENSURE(m_pdocmanager != NULL);
   //  return m_pdocmanager->get_open_document_count();
   return 0;
}


// This is core API library.
//
//
//
//
//
//
//
//

/////////////////////////////////////////////////////////////////////////////
// application Settings Helpers


void application::SetRegistryKey(const char * lpszRegistryKey)
{
   ASSERT(m_pszRegistryKey == NULL);
   ASSERT(lpszRegistryKey != NULL);
   ASSERT(m_strAppName.has_char());

   //bool bEnable = __enable_memory_tracking(FALSE);
   free((void *)m_pszRegistryKey);
   m_pszRegistryKey = strdup(lpszRegistryKey);
   free((void *)m_pszProfileName);
   m_pszProfileName = strdup(m_strAppName);
   //__enable_memory_tracking(bEnable);
}

void application::SetRegistryKey(UINT nIDRegistryKey)
{
   UNREFERENCED_PARAMETER(nIDRegistryKey);
   ASSERT(m_pszRegistryKey == NULL);
   throw not_implemented(get_app());
   /*char szRegistryKey[256];
   VERIFY(::core::LoadString(nIDRegistryKey, szRegistryKey));
   SetRegistryKey(szRegistryKey);*/
}


#ifdef WINDOWSEX

// returns key for HKEY_CURRENT_USER\"Software"\RegistryKey\ProfileName
// creating it if it doesn't exist
// responsibility of the caller to call RegCloseKey() on the returned HKEY
HKEY application::GetAppRegistryKey()
{
   ASSERT(m_pszRegistryKey != NULL);
   ASSERT(m_pszProfileName != NULL);

   HKEY hAppKey = NULL;
   HKEY hSoftKey = NULL;
   HKEY hCompanyKey = NULL;
   if (RegOpenKeyEx(HKEY_CURRENT_USER, "software", 0, KEY_WRITE|KEY_READ,
      &hSoftKey) == ERROR_SUCCESS)
   {
      DWORD dw;
      if (RegCreateKeyEx(hSoftKey, m_pszRegistryKey, 0, REG_NONE,
         REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
         &hCompanyKey, &dw) == ERROR_SUCCESS)
      {
         RegCreateKeyEx(hCompanyKey, m_pszProfileName, 0, REG_NONE,
            REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
            &hAppKey, &dw);
      }
   }
   if (hSoftKey != NULL)
      RegCloseKey(hSoftKey);
   if (hCompanyKey != NULL)
      RegCloseKey(hCompanyKey);

   return hAppKey;
}

// returns key for:
//      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\lpszSection
// creating it if it doesn't exist.
// responsibility of the caller to call RegCloseKey() on the returned HKEY
HKEY application::GetSectionKey(const char * lpszSection)
{
   ASSERT(lpszSection != NULL);

   HKEY hSectionKey = NULL;
   HKEY hAppKey = GetAppRegistryKey();
   if (hAppKey == NULL)
      return NULL;

   DWORD dw;
   RegCreateKeyEx(hAppKey, lpszSection, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL, &hSectionKey, &dw);
   RegCloseKey(hAppKey);
   return hSectionKey;
}

#endif

/*   UINT application::GetProfileInt(const char * lpszSection, const char * lpszEntry,
int32_t nDefault)
{
ASSERT(lpszSection != NULL);
ASSERT(lpszEntry != NULL);
if (m_pszRegistryKey != NULL) // use registry
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return nDefault;
uint32_t dwValue;
uint32_t dwType;
uint32_t dwCount = sizeof(uint32_t);
LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
(LPBYTE)&dwValue, &dwCount);
RegCloseKey(hSecKey);
if (lResult == ERROR_SUCCESS)
{
ASSERT(dwType == REG_DWORD);
ASSERT(dwCount == sizeof(dwValue));
return (UINT)dwValue;
}
return nDefault;
}
else
{
ASSERT(m_pszProfileName != NULL);
return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault,
m_pszProfileName);
}
}

string application::GetProfileString(const char * lpszSection, const char * lpszEntry,
const char * lpszDefault)
{
ASSERT(lpszSection != NULL);
ASSERT(lpszEntry != NULL);
if (m_pszRegistryKey != NULL)
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return lpszDefault;
string strValue;
uint32_t dwType=REG_NONE;
uint32_t dwCount=0;
LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
NULL, &dwCount);
if (lResult == ERROR_SUCCESS)
{
ASSERT(dwType == REG_SZ);
lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
(LPBYTE)strValue.GetBuffer(dwCount/sizeof(char)), &dwCount);
strValue.ReleaseBuffer();
}
RegCloseKey(hSecKey);
if (lResult == ERROR_SUCCESS)
{
ASSERT(dwType == REG_SZ);
return strValue;
}
return lpszDefault;
}
else
{
ASSERT(m_pszProfileName != NULL);

if (lpszDefault == NULL)
lpszDefault = "";   // don't pass in NULL
char szT[4096];
uint32_t dw = ::GetPrivateProfileString(lpszSection, lpszEntry,
lpszDefault, szT, _countof(szT), m_pszProfileName);
ASSERT(dw < 4095);
return szT;
}
}

bool application::GetProfileBinary(const char * lpszSection, const char * lpszEntry,
BYTE** ppData, UINT* pBytes)
{
ASSERT(lpszSection != NULL);
ASSERT(lpszEntry != NULL);
ASSERT(ppData != NULL);
ASSERT(pBytes != NULL);
*ppData = NULL;
*pBytes = 0;
if (m_pszRegistryKey != NULL)
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
{
return FALSE;
}

// ensure destruction

// linux ::core::CRegKey rkSecKey(hSecKey);

uint32_t dwType=0;
uint32_t dwCount=0;
LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
*pBytes = dwCount;
if (lResult == ERROR_SUCCESS)
{
ASSERT(dwType == REG_BINARY);
*ppData = new BYTE[*pBytes];
lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
*ppData, &dwCount);
}
if (lResult == ERROR_SUCCESS)
{
ASSERT(dwType == REG_BINARY);
return TRUE;
}
else
{
delete [] *ppData;
*ppData = NULL;
}
return FALSE;
}
else
{
ASSERT(m_pszProfileName != NULL);

string str = GetProfileString(lpszSection, lpszEntry, NULL);
if (str.is_empty())
return FALSE;
ASSERT(str.get_length()%2 == 0);
int_ptr nLen = str.get_length();
*pBytes = UINT(nLen)/2;
*ppData = new BYTE[*pBytes];
for (int32_t i=0;i<nLen;i+=2)
{
(*ppData)[i/2] = (BYTE)
(((str[i+1] - 'A') << 4) + (str[i] - 'A'));
}
return TRUE;
}
}


bool application::WriteProfileInt(const char * lpszSection, const char * lpszEntry,
int32_t nValue)
{
ASSERT(lpszSection != NULL);
ASSERT(lpszEntry != NULL);
if (m_pszRegistryKey != NULL)
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return FALSE;
LONG lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD,
(LPBYTE)&nValue, sizeof(nValue));
RegCloseKey(hSecKey);
return lResult == ERROR_SUCCESS;
}
else
{
ASSERT(m_pszProfileName != NULL);

char szT[16];
_stprintf_s(szT, _countof(szT), "%d", nValue);
return ::WritePrivateProfileString(lpszSection, lpszEntry, szT,
m_pszProfileName);
}
}

bool application::WriteProfileString(const char * lpszSection, const char * lpszEntry,
const char * lpszValue)
{
ASSERT(lpszSection != NULL);
if (m_pszRegistryKey != NULL)
{
LONG lResult;
if (lpszEntry == NULL) //delete whole departament
{
HKEY hAppKey = GetAppRegistryKey();
if (hAppKey == NULL)
return FALSE;
lResult = ::RegDeleteKey(hAppKey, lpszSection);
RegCloseKey(hAppKey);
}
else if (lpszValue == NULL)
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return FALSE;
// necessary to cast away const below
lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
RegCloseKey(hSecKey);
}
else
{
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return FALSE;
lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
(LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(char));
RegCloseKey(hSecKey);
}
return lResult == ERROR_SUCCESS;
}
else
{
ASSERT(m_pszProfileName != NULL);
ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue,
m_pszProfileName);
}
}

bool application::WriteProfileBinary(const char * lpszSection, const char * lpszEntry,
LPBYTE pData, UINT nBytes)
{
ASSERT(lpszSection != NULL);
if (m_pszRegistryKey != NULL)
{
LONG lResult;
HKEY hSecKey = GetSectionKey(lpszSection);
if (hSecKey == NULL)
return FALSE;
lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,
pData, nBytes);
RegCloseKey(hSecKey);
return lResult == ERROR_SUCCESS;
}

// convert to string and write out
LPTSTR lpsz = new char[nBytes*2+1];
UINT i;
for (i = 0; i < nBytes; i++)
{
lpsz[i*2] = (char)((pData[i] & 0x0F) + 'A'); //low nibble
lpsz[i*2+1] = (char)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
}
lpsz[i*2] = 0;

ASSERT(m_pszProfileName != NULL);

bool bResult = WriteProfileString(lpszSection, lpszEntry, lpsz);
delete[] lpsz;
return bResult;
}

#include "framework.h"*/




/*   property_set & application::propset(object * pobject)
{
single_lock sl(&m_mapObjectSet, TRUE);
return m_mapObjectSet[pobject];
}

property_set * application::existing_propset(object * pobject)
{
single_lock sl(&m_mapObjectSet, TRUE);
auto p = m_mapObjectSet.PLookup(pobject);
if(p == NULL)
return NULL;
return &p->m_value;
}*/



bool application::does_launch_window_on_startup()
{
   return true;
}

bool application::activate_app()
{
   if(GetMainWnd() != NULL)
   {
      GetMainWnd()->ShowWindow(SW_SHOWNORMAL);
   }
   return true;
}






/*   int32_t application::GetResourceId(const id_space * pspace, int32_t iKey)
{
int32_t iId;
if(!m_imapResource.get(pspace, iKey, iId))
{
m_imapResource.set(pspace, iKey, m_iResourceId);
m_iResourceId++;
if(!m_imapResource.get(pspace, iKey, iId))
{
return -1;
}
}
return iId;
}

int32_t application::GetResourceId(const id_space * pspace, const char * lpcszKey)
{
int32_t iId;
if(!m_strmapResource.get(pspace, lpcszKey, iId))
{
m_strmapResource.set(pspace, lpcszKey, m_iResourceId);
m_iResourceId++;
if(!m_strmapResource.get(pspace, lpcszKey, iId))
{
return -1;
}
}
return iId;
}


int32_t application::GetResourceId(const id_space & space, int32_t iKey)
{
return GetResourceId(&space, iKey);
}

int32_t application::GetResourceId(const id_space & space, const char * lpcszKey)
{
return GetResourceId(&space, lpcszKey);
}
*/

string application::matter_as_string(const char * pszMatter, const char * pszMatter2)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(pszMatter2);
   throw not_implemented(get_app());
}

string application::dir_matter(const char * pszMatter, const char * pszMatter2)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(pszMatter2);
   throw not_implemented(get_app());
}

bool application::is_inside_time_dir(const char * pszPath)
{
   UNREFERENCED_PARAMETER(pszPath);
   throw not_implemented(get_app());
}

bool application::file_is_read_only(const char * pszPath)
{
   UNREFERENCED_PARAMETER(pszPath);
   throw not_implemented(get_app());
}

/*
string application::file_as_string(const char * pszPath)
{
UNREFERENCED_PARAMETER(pszPath);
throw not_implemented(get_app());
}*/

string application::dir_path(const char * psz1, const char * psz2, const char * psz3)
{
   UNREFERENCED_PARAMETER(psz1);
   UNREFERENCED_PARAMETER(psz2);
   UNREFERENCED_PARAMETER(psz3);
   throw not_implemented(get_app());
}

string application::dir_name(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
   throw not_implemented(get_app());
}

bool application::dir_mk(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
   throw not_implemented(get_app());
}

string application::file_title(const char * psz)
{
   return System.file_title(psz);
}

string application::file_name(const char * psz)
{
   return System.file_name(psz);
}




oswindow application::get_ca2_app_wnd(const char * psz)
{
   UNREFERENCED_PARAMETER(psz);
   return NULL;
}


sp(::user::interaction) application::release_capture_uie()
{

#if defined(LINUX)

   oswindow oswindowCapture = ::GetCapture();
   if(oswindowCapture == NULL)
      return NULL;
   return oswindowCapture->get_user_interaction()->release_capture();

#elif defined(WINDOWS)

   oswindow oswindowCapture = ::GetCapture();
   if(oswindowCapture == NULL)
      return NULL;
   return System.window_from_os_data(oswindowCapture)->release_capture();

#elif defined(MACOS)

   oswindow oswindowCapture = ::GetCapture();
   if(oswindowCapture == NULL)
      return NULL;
   return oswindowCapture->get_user_interaction()->release_capture();

#else

   throw not_implemented(get_app());

#endif

}


sp(::user::interaction) application::get_capture_uie()
{

#ifdef METROWIN

   oswindow oswindowCapture = ::GetCapture();

   if(oswindowCapture == NULL)
      return NULL;

   ::user::interaction * pui = oswindowCapture->window();

   if(pui == NULL)
      return NULL;

   return pui->get_capture();

#elif defined(WINDOWS)

   oswindow oswindowCapture = ::GetCapture();

   if(oswindowCapture == NULL)
      return NULL;

   return System.window_from_os_data(oswindowCapture).cast < ::user::window >()->get_capture();

#else

   //      throw not_implemented(get_app());

   oswindow oswindowCapture = ::GetCapture();

   if(oswindowCapture == NULL)
      return NULL;

   return ::GetCapture()->get_user_interaction()->m_pimpl.cast < ::user::window >()->get_capture();

#endif

}


::user::str_context * application::str_context()
{

   return m_puserstrcontext;

}


void application::get_cursor_pos(LPPOINT lppoint)
{
   if(is_system())
   {
      if(m_bSessionSynchronizedCursor)
      {
         ::GetCursorPos(&m_ptCursor);
      }
      if(lppoint != NULL)
      {
         *lppoint = m_ptCursor;
      }
   }
   else if(is_session())
   {
      if(m_bSessionSynchronizedCursor)
      {
         System.get_cursor_pos(&m_ptCursor);
      }
      if(lppoint != NULL)
      {
         *lppoint = m_ptCursor;
      }
   }
   else
   {
      Session.get_cursor_pos(lppoint);
   }
}

void application::get_screen_rect(LPRECT lprect)
{
#ifdef METROWIN
   if(m_bSessionSynchronizedScreen)
   {
      System.get_window_rect(m_rectScreen);
   }
#elif defined(LINUX)
   if(m_bSessionSynchronizedScreen)
   {
      System.get_monitor_rect(0, m_rectScreen);
   }
#elif defined(MACOS)
   if(m_bSessionSynchronizedScreen)
   {
      System.get_monitor_rect(0, m_rectScreen);
   }
#else
   if(m_bSessionSynchronizedScreen)
   {
      oswindow oswindowDesktop = ::GetDesktopWindow();
      ::GetWindowRect(oswindowDesktop, &m_rectScreen);
   }
#endif
   if(lprect != NULL)
   {
      *lprect = m_rectScreen;
   }
}

int32_t application::get_document_count()
{
   //      return m_pdocmanager->get_document_count();
   return 0;
}



// Temporary map management (locks temp map on current thread)
void application::LockTempMaps()
{
   ::application_base::m_p->LockTempMaps();
}

bool application::UnlockTempMaps(bool bDeleteTemp)
{
   return ::application_base::m_p->UnlockTempMaps(bDeleteTemp);
}

void application::TermThread(HINSTANCE hInstTerm)
{
   UNREFERENCED_PARAMETER(hInstTerm);
}

/*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
{
UNREFERENCED_PARAMETER(pdata);
return NULL;
}*/

#ifdef METROWIN
sp(::user::interaction) application::window_from_os_data(void * pdata)
{
   return ::application_base::m_p->window_from_os_data(pdata);
}

sp(::user::interaction) application::window_from_os_data_permanent(void * pdata)
{
   return ::application_base::m_p->window_from_os_data_permanent(pdata);
}
#else
sp(::user::window) application::window_from_os_data(void * pdata)
{

   if(::application_base::m_p == NULL)
      return NULL;

   return ::application_base::m_p->window_from_os_data(pdata);

}

sp(::user::window) application::window_from_os_data_permanent(void * pdata)
{
   return ::application_base::m_p->window_from_os_data_permanent(pdata);
}
#endif


sp(::user::window) application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
{
   return ::application_base::m_p->FindWindow(lpszClassName, lpszWindowName);
}

sp(::user::window) application::FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow)
{
   return ::application_base::m_p->FindWindowEx(oswindowParent, oswindowChildAfter, lpszClass, lpszWindow);
}

string application::get_local_mutex_name(const char * pszAppName)
{
   string strMutex;
   strMutex.Format("Local\\ca2_application_local_mutex:%s", pszAppName);
   return strMutex;
}

string application::get_local_id_mutex_name(const char * pszAppName, const char * pszId)
{
   string strId(pszId);
   string strMutex;
   strMutex.Format("Local\\ca2_application_local_mutex:%s, id:%s", pszAppName, strId);
   return strMutex;
}

string application::get_global_mutex_name(const char * pszAppName)
{
   string strMutex;
   strMutex.Format("Global\\ca2_application_global_mutex:%s", pszAppName);
   return strMutex;
}

string application::get_global_id_mutex_name(const char * pszAppName, const char * pszId)
{
   string strId(pszId);
   string strMutex;
   strMutex.Format("Global\\ca2_application_global_mutex:%s, id:%s", pszAppName,  strId);
   return strMutex;
}

string application::get_local_mutex_name()
{
   return get_local_mutex_name(get_mutex_name_gen());
}

string application::get_local_id_mutex_name()
{
   return get_local_id_mutex_name(get_mutex_name_gen(), get_local_mutex_id());
}

string application::get_global_mutex_name()
{
   return get_global_mutex_name(get_mutex_name_gen());
}

string application::get_global_id_mutex_name()
{
   return get_global_id_mutex_name(get_mutex_name_gen(), get_global_mutex_id());
}


/*
application_signal_details::application_signal_details(sp(base_application) papp, ::signal * psignal, e_application_signal esignal) :
element(papp),
signal_details(psignal)
{

m_esignal         = esignal;
m_bOk             = true;

}

*/



bool application::finalize()
{

   bool bFinalize = true;

   try
   {
      thread::finalize();
   }
   catch(...)
   {
      bFinalize = false;
   }

   return bFinalize;

}


/*   sp(::user::interaction) application::get_place_holder_container()
{
if(m_puiInitialPlaceHolderContainer != NULL)
return m_puiInitialPlaceHolderContainer;
if(m_psession != NULL)
{
try
{
if(m_psession->m_pplanesession->m_puiInitialPlaceHolderContainer != NULL)
return m_psession->m_pplanesession->m_puiInitialPlaceHolderContainer;
}
catch(...)
{
}
}
if(m_psystem != NULL)
{
try
{
if(m_psystem->m_puiInitialPlaceHolderContainer != NULL)
return m_psystem->m_puiInitialPlaceHolderContainer;
}
catch(...)
{
}
}
return NULL;
}
*/


sp(::user::interaction) application::get_request_parent_ui(sp(::user::interaction) pinteraction, sp(::create_context) pcreatecontext)
{

   sp(::user::interaction) puiParent = NULL;

   if(puiParent == NULL)
   {
      puiParent = pcreatecontext->m_puiParent;
   }

   if(puiParent == NULL && pcreatecontext->m_spApplicationBias.is_set())
   {
      puiParent = pcreatecontext->m_spApplicationBias->m_puiParent;
   }

   if(puiParent == NULL && m_psession != NULL && !pcreatecontext->m_bClientOnly
      && !pcreatecontext->m_bOuterPopupAlertLike && m_psession != this)
   {
      puiParent = Sess(this).get_request_parent_ui(pinteraction, pcreatecontext);
   }

   return puiParent;

}





void application::construct()
{
}


void application::_001OnFileNew(signal_details * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   var varFile;
   var varQuery;

   varQuery["command"] = "new_file";

   request_file_query(varFile, varQuery);

   //::application_base::m_p->_001OnFileNew();
}


sp(::user::document_interface) application::_001OpenDocumentFile(var varFile)
{

   return ::application_base::m_p->_001OpenDocumentFile(varFile);

}


void application::_001EnableShellOpen()
{

   ::application_base::m_p->_001EnableShellOpen();

}


bool application::_001OnDDECommand(const char * lpcsz)
{
   throw not_implemented(get_app());
   //return ::application_base::m_p->_001OnDDECommand(lpcsz);
}

//   ::core::file_system & application::file_system()
// {
//  return m_spfilesystem;
//}





string application::get_version()
{
   return ::application_base::m_p->get_version();
}


bool application::Ex2OnAppInstall()
{
   return true;
}

bool application::Ex2OnAppUninstall()
{
   return true;
}


thread * application::GetThread()
{

   if(::application_base::m_p == NULL)
      return NULL;

   return ::application_base::m_p->GetThread();

}


void application::set_thread(thread * pthread)
{
   ::application_base::m_p->set_thread(pthread);
}

/*   ::draw2d::graphics * application::graphics_from_os_data(void * pdata)
{
return ::application_base::m_p->graphics_from_os_data(pdata);
}*/



sp(::user::window) application::get_desktop_window()
{
#if defined(METROWIN) || defined(MACOS)
   throw todo(this);
   /*#elif defined(LINUX)

   synch_lock sl(&user_mutex());

   xdisplay pdisplay.
   pdisplay.open(NULL) = XOpenDisplay(NULL);

   oswindow window(pdisplay, DefaultRootWindow(pdisplay));

   XCloseDisplay(pdisplay);

   return window_from_os_data(window);
   */
#else
   return window_from_os_data(::GetDesktopWindow());
#endif
}

void application::SetCurrentHandles()
{
   ::application_base::m_p->SetCurrentHandles();
}


#ifndef METROWIN

void application::get_time(timeval *p)
{
   ::application_base::m_p->get_time(p);
}

#endif

void application::set_env_var(const string & var,const string & value)
{
   ::application_base::m_p->set_env_var(var, value);
}

uint32_t application::get_thread_id()
{
   return ::application_base::m_p->get_thread_id();
}

bool application::set_main_init_data(::core::main_init_data * pdata)
{
   return ::application_base::m_p->set_main_init_data(pdata);
}


///////////////////////////////////////////////////////////////////////////
// application diagnostics

void application::assert_valid() const
{
   thread::assert_valid();


   if (System.GetThread() != (thread*)this)
      return;     // only do subset if called from different thread

   ASSERT(System.GetThread() == this);
   //ASSERT(afxCurrentInstanceHandle == m_hInstance);

   /*      if (m_pdocmanager != NULL)
   ASSERT_VALID(m_pdocmanager);*/
}

void application::dump(dump_context & dumpcontext) const
{

   thread::dump(dumpcontext);

#ifdef WINDOWS
   dumpcontext << "m_hInstance = " << (void *)m_hInstance;
#endif

   dumpcontext << "\nm_lpCmdLine = " << m_strCmdLine;
   dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
   dumpcontext << "\nm_pszAppName = " << m_strAppName;
   dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
   dumpcontext << "\nm_pszHelpFilePath = " << m_pszHelpFilePath;
   dumpcontext << "\nm_pszProfileName = " << m_pszProfileName;

#ifdef WINDOWS
   dumpcontext << "\nm_hDevMode = " << (void *)m_hDevMode;
   dumpcontext << "\nm_hDevNames = " << (void *)m_hDevNames;
#endif

   dumpcontext << "\nm_dwPromptContext = " << (UINT) m_dwPromptContext;
   //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;


   /*      if (m_pdocmanager != NULL)
   m_pdocmanager->dump(dumpcontext);*/

   dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
   dumpcontext << "\nm_hcurWaitCursorRestore = " << (void *)m_hcurWaitCursorRestore;
   dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

   /*   ___THREAD_STATE* pState = __get_thread_state();
   dumpcontext << "\nm_msgCur = {";
   dumpcontext << "\n\toswindow = " << (void *)pState->m_msgCur.oswindow;
   dumpcontext << "\n\tmessage = " << (UINT)pState->m_msgCur.message;
   dumpcontext << "\n\twParam = " << (UINT)pState->m_msgCur.wParam;
   dumpcontext << "\n\tlParam = " << (void *)pState->m_msgCur.lParam;
   dumpcontext << "\n\ttime = " << pState->m_msgCur.time;
   dumpcontext << "\n\tpt = " << point(pState->m_msgCur.pt);
   dumpcontext << "\n}";
   */
   dumpcontext << "\n";
}






void __post_quit_message(int32_t nExitCode)
{

#ifdef WINDOWSEX

   ::PostQuitMessage(nExitCode);

#else

   throw not_implemented(get_thread_app());

#endif

}


void application::install_message_handling(::message::dispatch * pdispatch)
{
   thread::install_message_handling(pdispatch);
   IGUI_WIN_MSG_LINK(WM_APP + 2043, pdispatch, this, &application::_001OnApplicationRequest);
}


string application::get_locale()
{
   return m_strLocale;
}

string application::get_schema()
{
   return m_strSchema;
}

string application::get_locale_schema_dir()
{

   return System.dir().simple_path(get_locale(), get_schema());

}

string application::get_locale_schema_dir(const string & strLocale)
{

   if(strLocale.is_empty())
      return System.dir().simple_path(get_locale(), get_schema());
   else
      return System.dir().simple_path(strLocale, get_schema());

}

string application::get_locale_schema_dir(const string & strLocale, const string & strSchema)
{
   if(strLocale.is_empty())
   {
      if(strSchema.is_empty())
         return System.dir().simple_path(get_locale(), get_schema());
      else
         return System.dir().simple_path(get_locale(), strSchema);
   }
   else
   {
      if(strSchema.is_empty())
         return System.dir().simple_path(strLocale, get_schema());
      else
         return System.dir().simple_path(strLocale, strSchema);
   }
}

void application::set_locale(const string & lpcsz, bool bUser)
{
   m_strLocale = lpcsz;
   on_set_locale(lpcsz, bUser);
}

void application::set_schema(const string & lpcsz, bool bUser)
{
   m_strSchema = lpcsz;
   on_set_schema(lpcsz, bUser);
}

void application::on_set_locale(const string & lpcsz, bool bUser)
{
   UNREFERENCED_PARAMETER(bUser);
   UNREFERENCED_PARAMETER(lpcsz);
   //System.appa_load_string_table();
}

void application::on_set_schema(const string & lpcsz, bool bUser)
{
   UNREFERENCED_PARAMETER(bUser);
   UNREFERENCED_PARAMETER(lpcsz);
   //System.appa_load_string_table();
}


bool application::base_support()
{

   //if(!application::base_support())
   // return false;

   if(m_strBaseSupportId.is_empty())
   {

      property_set propertyset;

      message_box("err\\developer\\base_support\\support_id_not_specified.xml", propertyset);

      return false;

   }

   return true;
}

string application::message_box(const string & pszMatter, property_set & propertyset)
{
   UNREFERENCED_PARAMETER(propertyset);
   UNREFERENCED_PARAMETER(pszMatter);
   return "";
}

bool application::bergedge_start()
{
   return true;
}

void application::load_string_table()
{
   load_string_table("", "");
}

/*::fontopus::user * application::create_user(const string & pszLogin)
{
return NULL;
}*/

::fontopus::user * application::create_current_user()
{
   return NULL;
   /*   string str = get_current_user_login();
   return create_user(str);*/
}

/*string application::get_current_user_login()
{
return "";
}*/


bool application::get_auth(const string & pszForm, string & strUsername, string & strPassword)
{
   UNREFERENCED_PARAMETER(pszForm);
   UNREFERENCED_PARAMETER(strUsername);
   UNREFERENCED_PARAMETER(strPassword);
   return false;
}




#ifdef WINDOWSEX
bool Is_Vista_or_Later ()
{
   OSVERSIONINFOEX osvi;
   DWORDLONG dwlConditionMask = 0;
   byte op=VER_GREATER_EQUAL;

   // Initialize the OSVERSIONINFOEX structure.

   ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
   osvi.dwMajorVersion = 6;
   //   osvi.dwMinorVersion = 1;
   //   osvi.wServicePackMajor = 0;
   //   osvi.wServicePackMinor = 0;

   // Initialize the condition mask.

   VER_SET_CONDITION( dwlConditionMask, VER_MAJORVERSION, op );
   //VER_SET_CONDITION( dwlConditionMask, VER_MINORVERSION, op );
   //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMAJOR, op );
   //VER_SET_CONDITION( dwlConditionMask, VER_SERVICEPACKMINOR, op );

   // Perform the test.

   return VerifyVersionInfo(
      &osvi,
      VER_MAJORVERSION | VER_MINORVERSION |
      VER_SERVICEPACKMAJOR | VER_SERVICEPACKMINOR,
      dwlConditionMask) != FALSE;
}
#endif

bool application::initialize()
{



   m_pcalculator = new ::calculator::calculator(this);

   m_pcalculator->construct(this);

   if(!m_pcalculator->initialize())
      return false;


   m_pcolorertake5 = new ::colorertake5::colorertake5(this);

   m_pcolorertake5->construct(this);

   if(!m_pcolorertake5->initialize())
      return false;

   if(!m_psockets->initialize())
      return false;



   m_dwAlive = ::get_tick_count();

   if(is_system())
   {
      if(guideline()->m_varTopicQuery.propset().has_property("save_processing"))
      {
         System.savings().save(::core::resource_processing);
      }
      if(guideline()->m_varTopicQuery.propset().has_property("save_blur_back"))
      {
         System.savings().save(::core::resource_blur_background);
      }
      if(guideline()->m_varTopicQuery.propset().has_property("save_transparent_back"))
      {
         System.savings().save(::core::resource_translucent_background);
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

   if(is_system())
   {

      System.m_spcopydesk.create(allocer());

      if(!System.m_spcopydesk->initialize())
         return false;

   }

   if(is_system()
      && command_thread()->m_varTopicQuery["app"] != "core_netnodelite"
      && command_thread()->m_varTopicQuery["app"] != "app-core/netnode_dynamic_web_server"
      && command_thread()->m_varTopicQuery["app"] != "app-gtech/alarm"
      && command_thread()->m_varTopicQuery["app"] != "app-gtech/sensible_service")
   {
      System.http().defer_auto_initialize_proxy_configuration();
   }



   m_dwAlive = ::get_tick_count();

   if(is_system())
   {
      System.factory().creatable_small < ::userex::keyboard_layout > ();
   }

   //      if(!::cubebase::application::initialize())
   //       return false;


   //      m_puserbase = new ::user::user();

   //    m_puserbase->construct(this);

   //  if(!m_puserbase->initialize())
   //return false;

   m_pfilemanager =canew(::filemanager::filemanager(this));

   application::m_pfilemanager = m_pfilemanager;

   m_pfilemanager->construct(this);

   if(!m_pfilemanager->initialize())
      return false;

   m_pusermail = canew(::usermail::usermail(this));

   m_pusermail->construct(this);

   if(!m_pusermail->initialize())
      return false;

   m_dwAlive = ::get_tick_count();





   m_dwAlive = ::get_tick_count();

   //m_splicense(new class ::fontopus::license(this));


   if(!is_system())
   {
      System.register_bergedge_application(this);
   }


   m_dwAlive = ::get_tick_count();

   ensure_app_interest();

   application_signal_details signal(this, m_psignal, application_signal_initialize);
   m_psignal->emit(&signal);
   if(!signal.m_bOk)
      return false;
   return true;
}

void application::pre_translate_message(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_USER + 124 && pbase->m_pwnd == NULL)
   {
      /*      OnMachineEvent((flags < machine_event::e_flag> *) pmsg->lParam);
      delete (flags < machine_event::e_flag> *) pmsg->lParam;*/
      pbase->m_bRet = true;
      return;
   }
   return thread::pre_translate_message(pobj);
}

void application::_001OnApplicationRequest(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_wparam == 2)
   {
      // when wparam == 2 lparam is a pointer to a ::core::command_fork
      // that should be treated as command_line on request, i.e.,
      // a fork whose Forking part has been done, now
      // the parameters are going to be passed to this new application
      sp(::create_context) pcreatecontext(pbase->m_lparam);
      try
      {
         on_request(pcreatecontext);
      }
      catch(not_installed & e)
      {

         throw e;

      }
      catch(exit_exception & e)
      {
         throw e;
      }
      catch(...)
      {
      }
      sp(::plane::session) pbergedge = pcreatecontext->m_spCommandLine->m_varQuery["bergedge_callback"].cast < ::plane::session >();
      // todobergedge
      /*if(pbergedge != NULL)
      {
      pbergedge->on_app_request_bergedge_callback(this);
      }*/
      pcreatecontext->m_spCommandLine->m_eventReady.SetEvent();

   }
}


::mutex * application::get_local_mutex()
{
   return m_pmutexLocal;
}

::mutex * application::get_global_mutex()
{
   return m_pmutexGlobal;
}

void application::_001CloseApplication()
{
   set_run(false);
   post_thread_message(WM_QUIT);
}


string application::get_license_id()
{

   return m_strAppId;

}


void application::process(machine_event_data * pdata)
{
   if(pdata->m_fixed.m_bRequestCloseApplication)
   {
      _001CloseApplication();
   }
}


void application::EnableShellOpen()
{
   ASSERT(m_atomApp == 0 && m_atomSystemTopic == 0); // do once
   if (m_atomApp != 0 || m_atomSystemTopic != 0)
   {
      return;
   }

   // Win95 & Win98 sends a WM_DDE_INITIATE with an atom that points to the
   // int16_t file name so we need to use the int16_t file name.
   string strShortName;
   strShortName = get_module_file_path();

   // strip out path
   //string strFileName = ::PathFindFileName(strShortName);
   // strip out extension
   //LPTSTR pszFileName = strFileName.GetBuffer();
   //::PathRemoveExtension(pszFileName);
   //strFileName.ReleaseBuffer();

   //      m_atomApp = ::GlobalAddAtom(strFileName);
   //    m_atomSystemTopic = ::GlobalAddAtom("system");
}


string application::load_string(id id)
{
   string str;
   if(!load_string(str, id))
   {
      return (const string &) id;
   }
   return str;
}

bool application::load_string(string & str, id id)
{
   if(!load_cached_string(str, id, true))
   {
      return false;
   }
   return true;
}

bool application::load_cached_string(string & str, id id, bool bLoadStringTable)
{
   ::xml::document doc(this);
   if(!doc.load(id))
   {
      return load_cached_string_by_id(str, id, "", bLoadStringTable);
   }
   sp(::xml::node) pnodeRoot = doc.get_root();
   if(pnodeRoot->get_name() == "string")
   {
      string strId = pnodeRoot->attr("id");
      string strValue = pnodeRoot->get_value();
      return load_cached_string_by_id(str, strId, strValue, bLoadStringTable);
   }
   str = doc.get_name();
   return true;
}

bool application::load_cached_string_by_id(string & str, id id, const string & pszFallbackValue, bool bLoadStringTable)
{

   single_lock sl(&g_mutexStr, true);

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
      strTable = strId.Mid(0, iFind);
      strString = strId.Mid(iFind + 1);
   }
   if(m_stringtablemapStd.Lookup(strTable, pmap))
   {
      if(pmap->Lookup(strString, str))
      {
         return true;
      }
   }
   else if(m_stringtablemap.Lookup(strTable, pmap))
   {
      if(pmap->Lookup(strString, str))
      {
         return true;
      }
   }
   else if(bLoadStringTable)
   {
      load_string_table(strTable, "");
      return load_cached_string_by_id(str, id, pszFallbackValue, false);
   }
   if(pszFallbackValue.is_empty())
      str = strId;
   else
      str = pszFallbackValue;
   return true;
}

void application::load_string_table(const string & pszApp, const string & pszId)
{

   single_lock sl(&g_mutexStr, true);

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
   string strFilePath = System.dir().matter_from_locator(App(this).str_context(), strLocator, strMatter);
   if(!System.file().exists(strFilePath, this))
   {
      try
      {
         if(m_stringtablemap[pszId] != NULL)
            delete m_stringtablemap[pszId];
      }
      catch(...)
      {
      }
      m_stringtablemap.set_at(pszId, new string_to_string);
      return;
   }
   string strFile = Application.file().as_string(strFilePath);
   if(!doc.load(strFile))
      return;
   string_to_string * pmapNew = new string_to_string;
   for(int32_t i = 0; i < doc.get_root()->children().get_count(); i++)
   {
      string strId      = doc.get_root()->child_at(i)->attr("id");
      string strValue   = doc.get_root()->child_at(i)->get_value();
      pmapNew->set_at(strId, strValue);
   }

   string_to_string * pmapOld = m_stringtablemap[strTableId];

   m_stringtablemap[strTableId] = NULL;

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

   m_stringtablemap[strTableId] = pmapNew;
   ASSERT(m_stringtablemap[strTableId] == pmapNew);
}

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
#endif

bool application::open_link(const string & strLink, const string & pszTarget)
{
   if(is_system())
   {
#ifdef WINDOWSEX
      string strUrl = strLink;
      if(!::str::begins_ci(strUrl, "http://")
         && !::str::begins_ci(strUrl, "https://"))
      {
         strUrl = "http://" + strUrl;
      }
      ::ShellExecuteA(NULL, "open", strUrl, NULL, NULL, SW_SHOW);
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
#elif defined(MACOS)
      openURL(strLink);
      return true;
#else
      throw not_implemented(get_app());
#endif
   }
   else
   {
      return System.open_link(strLink, pszTarget);
   }

   return false;

}

sp(::user::interaction) application::uie_from_point(point pt)
{
   user::interaction_ptr_array wnda = frames();
   user::oswindow_array oswindowa;
   wnda.get_wnda(oswindowa);
   user::window_util::SortByZOrder(oswindowa);
   for(int32_t i = 0; i < oswindowa.get_count(); i++)
   {
      sp(::user::interaction) puieWindow = wnda.find_first(oswindowa[i]);
      sp(::user::interaction) puie = puieWindow->_001FromPoint(pt);
      if(puie != NULL)
         return puie;
   }
   return NULL;
}

void application::message_queue_message_handler(signal_details * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_uiMessage == WM_TIMER)
   {
      SCAST_PTR(::message::timer, ptimer, pobj);
      if(ptimer->m_nIDEvent == 123)
      {
         m_spuiMessage->KillTimer(ptimer->m_nIDEvent);
         frames().send_message_to_descendants(application::APPM_LANGUAGE);
         System.appa_load_string_table();
      }
   }
}

bool application::on_install()
{
   return true;
}

bool application::on_run_install()
{
   if(m_strId == "session" || m_strAppName == "session")
   {
      if(!directrix()->m_varTopicQuery.has_property("session_start"))
      {
         System.post_thread_message(WM_QUIT);
      }
   }
   else
   {
      System.post_thread_message(WM_QUIT);
   }


   return true;
}

bool application::on_uninstall()
{
   return true;
}

bool application::on_run_uninstall()
{

   if(m_strId == "session")
   {
      if(!directrix()->m_varTopicQuery.has_property("session_start"))
      {
         System.post_thread_message(WM_QUIT);
      }
   }
   else
   {
      System.post_thread_message(WM_QUIT);
   }

   return true;
}


bool application::is_key_pressed(::user::e_key ekey)
{

   if(is_session())
   {
      if(m_pmapKeyPressed  == NULL)
      {
         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;
      }
      bool bPressed = false;
      if(ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->Lookup(::user::key_shift, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lshift, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rshift, bPressed);
         if(bPressed)
            goto ret;
      }
      else if(ekey == ::user::key_control)
      {
         m_pmapKeyPressed->Lookup(::user::key_control, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lcontrol, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rcontrol, bPressed);
         if(bPressed)
            goto ret;
      }
      else if(ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->Lookup(::user::key_alt, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lalt, bPressed);
         if(bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_ralt, bPressed);
         if(bPressed)
            goto ret;
      }
      else
      {
         m_pmapKeyPressed->Lookup(ekey, bPressed);
      }
ret:
      return bPressed;
   }
   else if(m_psession != NULL)
   {
      return Sess(this).is_key_pressed(ekey);
   }
   else if(m_psystem != NULL)
   {
      return Sys(this).is_key_pressed(ekey);
   }
   else
   {
      throw "not expected";
   }

}

void application::set_key_pressed(::user::e_key ekey, bool bPressed)
{
   if(is_session())
   {
      if(m_pmapKeyPressed  == NULL)
      {
         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;
      }
      (*m_pmapKeyPressed)[ekey] = bPressed;
   }
   else if(m_psession != NULL)
   {
      return Sess(this).set_key_pressed(ekey, bPressed);
   }
   else if(m_psystem != NULL)
   {
      return Sys(this).set_key_pressed(ekey, bPressed);
   }
   else
   {
      throw "not expected";
   }
}

bool application::start_application(bool bSynch, application_bias * pbias)
{
   /*      try
   {
   if(pbias != NULL)
   {
   papp->m_pplaneapp->m_puiInitialPlaceHolderContainer = pbias->m_puiParent;
   }
   }
   catch(...)
   {
   }*/
   try
   {
      if(pbias != NULL)
      {
         if(pbias->m_pcallback != NULL)
         {
            pbias->m_pcallback->connect_to(this);
         }
      }
   }
   catch(...)
   {
   }

   manual_reset_event * peventReady = NULL;

   if(bSynch)
   {
      peventReady = new manual_reset_event(get_app());
      m_peventReady = peventReady;
      peventReady->ResetEvent();
   }

   thread::m_p.create(allocer());
   //dynamic_cast < thread * > (papp->m_pplaneapp->thread::m_p)->m_p = papp->m_pplaneapp->thread::m_p;
   thread::m_p->m_p = this;
   if(pbias != NULL)
   {
      m_biasCalling = *pbias;
   }
   begin();

   if(bSynch)
   {
      try
      {
         keep_alive();
      }
      catch(...)
      {
      }
      try
      {
         //            MESSAGE msg;
         while(get_run())
         {
            // phase1: check to see if we can do idle work
            while (!has_message())
            {
               if(!is_alive())
               {
                  return false;
               }
               if(m_bReady)
               {
                  if(m_iReturnCode == 0)
                     goto ok;
                  return false;
               }
               Sleep(84);
            }
            pump_message();
         }
      }
      catch(...)
      {
         return false;
      }
ok:;
   }

   return true;

}

bool application::is_running()
{
   return is_alive();
}




void application::on_application_signal(signal_details * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   //      SCAST_PTR(signal_details, psignal, pobj);
   /*if(psignal->m_esignal == signal_exit_instance)
   {
   if(m_copydesk.is_set()
   && m_copydesk->IsWindow())
   {
   m_copydesk->DestroyWindow();
   }
   }*/
}

void application::defer_add_document_template(sp(::user::document_template) ptemplate)
{

   Application.user()->defer_add_document_template(ptemplate);

}


::user::printer * application::get_printer(const char * pszDeviceName)
{

   return ::application_base::m_p->get_printer(pszDeviceName);

}

::count application::get_monitor_count()
{

   return System.get_monitor_count();

}


bool application::get_monitor_rect(index iMonitor, LPRECT lprect)
{

   return System.get_monitor_rect(iMonitor, lprect);

}


::count application::get_desk_monitor_count()
{

   return System.get_desk_monitor_count();

}



bool application::get_desk_monitor_rect(index iMonitor, LPRECT lprect)
{

   return System.get_desk_monitor_rect(iMonitor, lprect);

}




bool application::set_keyboard_layout(const char * pszPath, bool bUser)
{

   return Application.user()->keyboard().load_layout(pszPath, bUser);

}

string application::message_box(const char * pszMatter, property_set & propertyset)
{
   ::userex::message_box box(this);
   box.show(pszMatter, &propertyset);
   return box.m_strResponse;
}


int32_t application::track_popup_menu(const char * pszMatter, point pt, sp(::user::interaction) puie)
{
   UNREFERENCED_PARAMETER(pszMatter);
   UNREFERENCED_PARAMETER(pt);
   UNREFERENCED_PARAMETER(puie);
   return 1;
}



bool application::get_fs_size(string & strSize, const char * pszPath, bool & bPending)
{
   int64_t i64Size;
   if(!get_fs_size(i64Size, pszPath, bPending))
   {
      strSize.Empty();
      return false;
   }
   if(i64Size > 1024 * 1024 * 1024)
   {
      double d = (double) i64Size / (1024.0 * 1024.0 * 1024.0);
      strSize.Format("%0.2f GB", d);
   }
   else if(i64Size > 1024 * 1024)
   {
      double d = (double) i64Size / (1024.0 * 1024.0);
      strSize.Format("%0.1f MB", d);
   }
   else if(i64Size > 1024)
   {
      double d = (double) i64Size / (1024.0);
      strSize.Format("%0.0f KB", d);
   }
   else if(i64Size > 0)
   {
      strSize.Format("1 KB");
   }
   else
   {
      strSize.Format("0 KB");
   }
   if(bPending)
   {
      strSize = "~" + strSize;
   }
   return true;
}

bool application::get_fs_size(int64_t & i64Size, const char * pszPath, bool & bPending)
{
   db_server * pcentral = dynamic_cast < db_server * > (&System.m_simpledb.db());
   if(pcentral == NULL)
      return false;
   return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size, pszPath, bPending);
}


void application::set_title(const char * pszTitle)
{

   Session.set_app_title(m_strInstallType, m_strAppName, pszTitle);

}


bool application::_001CloseApplicationByUser(sp(::user::interaction) pwndExcept)
{

   // attempt to save all documents
   if(!save_all_modified())
      return false;     // don't close it

   // hide the application's windows before closing all the documents
   HideApplication();

   // close all documents first
   close_all_documents(FALSE);


   Application.user()->_001CloseAllDocuments(FALSE);


   // there are cases where destroying the documents may destroy the
   //  main ::user::window of the application.
   //bool b::core::ContextIsDll = afxContextIsDLL;
   //if (!b::core::ContextIsDll && papp->m_pplaneapp->GetVisibleFrameCount() <= 0)
   if(Application.user()->GetVisibleTopLevelFrameCountExcept(pwndExcept) <= 0)
   {

      post_thread_message(WM_QUIT);

   }

   return true;

}

int32_t application::send_simple_command(const char * psz, void * osdataSender)
{
   string strApp;
   stringa stra;
   stra.add_tokens(psz, "::", true);
   if(stra.get_size() > 0)
   {
      strApp = stra[0];
      oswindow oswindow = get_ca2_app_wnd(strApp);
      if(oswindow != NULL)
      {
         return send_simple_command((void *) oswindow, psz, osdataSender);
      }
   }
   return -1;
}

int32_t application::send_simple_command(void * osdata, const char * psz, void * osdataSender)
{
#ifdef WINDOWSEX
   ::oswindow oswindow = (::oswindow) osdata;
   if(!::IsWindow(oswindow))
      return -1;
   COPYDATASTRUCT cds;
   memset(&cds, 0, sizeof(cds));
   cds.dwData = 198477;
   cds.cbData = (uint32_t) strlen(psz);
   cds.lpData = (PVOID) psz;
   return (int32_t) SendMessage(oswindow, WM_COPYDATA, (WPARAM) osdataSender, (LPARAM) &cds);
#else
   throw todo(get_app());
#endif
}


void application::ensure_app_interest()
{

#ifndef METROWIN

   for(int32_t i = 0; i < m_straAppInterest.get_count(); i++)
   {
      if(m_straAppInterest[i] != m_strAppName && !::IsWindow(m_mapAppInterest[m_straAppInterest[i]]))
      {
         System.assert_running_local(m_straAppInterest[i]);
      }
   }

#else

   //throw todo(get_app());

#endif

}


string application::veriwell_multimedia_music_midi_get_default_library_name()
{

   if(::application_base::m_p == NULL)
      return "";

   return ::application_base::m_p->veriwell_multimedia_music_midi_get_default_library_name();

}



string application::multimedia_audio_mixer_get_default_library_name()
{

   if(::application_base::m_p == NULL)
      return "";

   return ::application_base::m_p->multimedia_audio_mixer_get_default_library_name();

}



string application::multimedia_audio_get_default_library_name()
{

   if(::application_base::m_p == NULL)
      return "";

   return ::application_base::m_p->multimedia_audio_get_default_library_name();

}



string application::draw2d_get_default_library_name()
{

   if(::application_base::m_p == NULL)
      return "draw2d_cairo";

   return ::application_base::m_p->draw2d_get_default_library_name();

}


::visual::icon * application::set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon)
{

   ::visual::icon * piconOld = get_icon(pobject, bBigIcon);

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


::visual::icon * application::get_icon(object * pobject, bool bBigIcon) const
{

   if(bBigIcon)
   {

      return const_cast < object * > (pobject)->oprop("big_icon").cast < ::visual::icon >();

   }
   else
   {

      return const_cast < object * > (pobject)->oprop("small_icon").cast < ::visual::icon >();

   }

}


string application::file_as_string(var varFile)
{

   return m_pplaneapp->file().as_string(varFile);

}


//namespace _001ca1api00001 + [core = (//namespace cube // ca8 + cube)]




