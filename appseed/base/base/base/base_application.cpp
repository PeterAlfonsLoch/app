#include "framework.h"


#if defined(MACOS)

void openURL(const string &url_str);

#endif

base_application::base_application() :
   m_allocer(this)
{

#ifdef WINDOWS

   m_hinstance = NULL;

#endif

   if(m_pbaseapp == NULL)
   {

      m_pbaseapp = this;

   }

   if(m_pbaseapp != NULL)
   {

      m_pbasesystem = m_pbaseapp->m_pbasesystem;

   }
   else
   {

      m_pbasesystem = NULL;

   }

   m_pplaneapp = NULL;

   m_pbasesession = NULL;

   m_nSafetyPoolSize = 512;        // default size


   m_dir.set_app(this);
   m_file.set_app(this);
   m_http.set_app(this);


   m_psignal                  = canew(class signal());

   m_pcommandthread           = canew(::command_thread(this));

   m_psavings                 = canew(class ::core::savings(this));
   m_pmath                    = canew(math::math(this));
   m_pgeometry                = canew(geometry::geometry(this));

   m_bZipIsDir = true;

   m_pmapKeyPressed = NULL;

   m_bLicense = true;

   // initialize wait cursor state
   m_iWaitCursorCount = 0;
   m_hcurWaitCursorRestore = NULL;


}

base_application::~base_application()
{
}


void base_application::assert_valid() const
{
   thread::assert_valid();


   if (System.GetThread() != (thread*)this)
      return;     // only do subset if called from different thread

   ASSERT(System.GetThread() == this);
   //ASSERT(afxCurrentInstanceHandle == m_hInstance);

   /*      if (m_pdocmanager != NULL)
   ASSERT_VALID(m_pdocmanager);*/
}

void base_application::dump(dump_context & dumpcontext) const
{

   thread::dump(dumpcontext);

#ifdef WINDOWS

   dumpcontext << "m_hinstance = " << (void *)m_hinstance;

#endif

   dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
   dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
   dumpcontext << "\nm_bHelpMode = " << m_strAppName;
//   dumpcontext << "\nm_bHelpMode = " << m_bHelpMode;
  // dumpcontext << "\nm_pszHelpFilePath = " << m_pszHelpFilePath;
   //dumpcontext << "\nm_pszProfileName = " << m_pszProfileName;

#ifdef WINDOWS
//   dumpcontext << "\nm_hDevMode = " << (void *)m_hDevMode;
  // dumpcontext << "\nm_hDevNames = " << (void *)m_hDevNames;
#endif

   //dumpcontext << "\nm_dwPromptContext = " << (UINT)m_dwPromptContext;
   //      dumpcontext << "\nm_eHelpType = " << m_eHelpType;


   /*      if (m_pdocmanager != NULL)
   m_pdocmanager->dump(dumpcontext);*/

   //dumpcontext << "\nm_nWaitCursorCount = " << m_iWaitCursorCount;
   dumpcontext << "\nm_hcurWaitCursorRestore = " << (void *)m_hcurWaitCursorRestore;
   //dumpcontext << "\nm_nNumPreviewPages = " << m_nNumPreviewPages;

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


int32_t base_application::simple_message_box(sp(::user::interaction) puiOwner, const char * pszMessage, UINT fuStyle)
{

#if defined(WINDOWSEX)

   return MessageBoxW(puiOwner->get_safe_handle(), wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(MACOS) || defined(ANDROID)

   return MessageBox(puiOwner->get_safe_handle(), pszMessage, m_strAppName, fuStyle);
   //   return MessageBox((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

   return MessageBox(puiOwner->get_safe_handle(), pszMessage, m_strAppName, fuStyle);

#endif

}


int32_t base_application::simple_message_box(const char * pszMessage, UINT fuStyle)
{

#if defined(WINDOWSEX)

   return MessageBoxW(NULL, wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(MACOS) || defined(ANDROID)

   return MessageBox(NULL, pszMessage, m_strAppName, fuStyle);
//   return MessageBox((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

   return MessageBox(NULL, pszMessage, m_strAppName, fuStyle);

#endif

}

string base_application::message_box(const string & pszMatter, property_set & propertyset)
{

   simple_message_box(pszMatter, 0);

   return "";

}

string base_application::load_string(id id)
{
   string str;
   if (!load_string(str, id))
   {
      return (const string &)id;
   }
   return str;
}

bool base_application::load_string(string & str, id id)
{
   UNREFERENCED_PARAMETER(id);
   str.Empty();
   return false;
}


sp(element) base_application::alloc(sp(type) info)
{
   return System.alloc(this, info);
}

sp(element) base_application::alloc(const  id & idType)
{
   return System.alloc(this, idType);
}

bool base_application::is_system()
{

   return false;

}

bool base_application::is_session()
{

   return false;

}


bool base_application::is_serviceable()
{

   return false;

}

//string base_application::matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);
//string base_application::dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
bool base_application::is_inside_time_dir(const char * pszPath)
{
   throw not_implemented(this);
   return false;
}

bool base_application::file_is_read_only(const char * pszPath)
{
   throw not_implemented(this);
   return false;
}

string base_application::file_as_string(var varFile)
{

   if(::str::begins_ci(varFile.get_string(), "http://")
   || ::str::begins_ci(varFile.get_string(), "https://"))
   {
      return Application.http().get(varFile.get_string());
   }
   else if(::str::begins_ci(varFile["url"].get_string(), "http://")
   || ::str::begins_ci(varFile["url"].get_string(), "https://"))
   {
      return Application.http().get(varFile["url"].get_string());
   }
   else
   {
      return file_as_string_dup(varFile.get_string());
   }

}

string base_application::dir_path(const char * psz1, const char * psz2, const char * psz3)
{
   return ::dir::path(psz1, psz2, psz3);
}

string base_application::dir_name(const char * psz)
{
   return ::dir::name(psz);
}

bool base_application::dir_mk(const char * psz)
{
   return ::dir::mk(psz);
}

string base_application::file_title(const char * psz)
{
   return ::file_title_dup(psz);
}
string base_application::file_name(const char * psz)
{
   return ::file_name_dup(psz);
}

bool base_application::app_map_lookup(const char * psz, void * & p)
{
   return m_appmap.Lookup(psz, p) != FALSE;
}

void base_application::app_map_set(const char * psz, void * p)
{
   m_appmap.set_at(psz, p);
}


sp(::command_thread) base_application::command_central()
{
   return m_pcommandthread;
}

sp(::command_thread) base_application::command_thread()
{
   return m_pcommandthread;
}

sp(::command_thread) base_application::command()
{
   return m_pcommandthread;
}

sp(::command_thread) base_application::guideline()
{
   return m_pcommandthread;
}

sp(::command_thread) base_application::directrix()
{
   return m_pcommandthread;
}

sp(::command_thread) base_application::axiom()
{
   return m_pcommandthread;
}

bool base_application::verb()
{
   axiom()->run();
   return true;
}

sp(::command_thread) base_application::creation()
{
   return m_pcommandthread;
}


::file::binary_buffer_sp base_application::file_get_file(var varFile, uint32_t uiFlags)
{

   return NULL;

}


application_signal_details::application_signal_details(sp(base_application) papp, class ::signal * psignal, e_application_signal esignal) :
   element(papp),
   ::signal_details(psignal)
{

   m_esignal         = esignal;
   m_bOk             = true;

}



::fontopus::user * base_application::safe_get_user()
{

   if (m_pfontopus == NULL)
      return NULL;

   return m_pfontopus->m_puser;

}


bool base_application::open_link(const string & strLink, const string & pszTarget)
{
   if (is_system())
   {
#ifdef WINDOWSEX
      string strUrl = strLink;
      if (!::str::begins_ci(strUrl, "http://")
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


::user::interaction_ptr_array & base_application::frames()
{
   return *m_pframea;
}

void base_application::add_frame(sp(::user::interaction) pwnd)
{
   m_pframea->add_unique(pwnd);
}

void base_application::remove_frame(sp(::user::interaction) pwnd)
{
   m_pframea->remove(pwnd);
   if (GetMainWnd() == pwnd)
   {
      if (m_pframea->get_size() > 0)
      {
         SetMainWnd(m_pframea->element_at(0));
      }
      else
      {
         SetMainWnd(NULL);
      }
   }
}


thread * base_application::GetThread()
{

   return NULL;

}


bool base_application::is_key_pressed(::user::e_key ekey)
{

   if (is_session())
   {
      if (m_pmapKeyPressed == NULL)
      {
         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;
      }
      bool bPressed = false;
      if (ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->Lookup(::user::key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_control)
      {
         m_pmapKeyPressed->Lookup(::user::key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->Lookup(::user::key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_ralt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {
         m_pmapKeyPressed->Lookup(ekey, bPressed);
      }
   ret:
      return bPressed;
   }
   else if (m_pbasesession != NULL)
   {
      return Sess(this).is_key_pressed(ekey);
   }
   else if (m_pbasesystem != NULL)
   {
      if (m_pbasesystem == this)
      {
         throw "not expected";
         return false;
      }
      return Sys(this).is_key_pressed(ekey);
   }
   else
   {
      throw "not expected";
   }

}

void base_application::set_key_pressed(::user::e_key ekey, bool bPressed)
{
   if (is_session())
   {
      if (m_pmapKeyPressed == NULL)
      {
         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;
      }
      (*m_pmapKeyPressed)[ekey] = bPressed;
   }
   else if (m_pbasesession != NULL)
   {
      return Sess(this).set_key_pressed(ekey, bPressed);
   }
   else if (m_pbasesystem != NULL)
   {
      
      if (m_pbasesystem == this)
      {

         return;

      }

      return Sys(this).set_key_pressed(ekey, bPressed);

   }
   else
   {
      throw "not expected";
   }
}



#ifdef METROWIN
sp(::user::interaction) base_application::window_from_os_data(void * pdata)
{

   return m_pimpl->window_from_os_data(pdata);

}

sp(::user::interaction) base_application::window_from_os_data_permanent(void * pdata)
{

   return m_pimpl->window_from_os_data_permanent(pdata);

}
#else
sp(::user::window) base_application::window_from_os_data(void * pdata)
{

   return m_pimpl->window_from_os_data(pdata);

}

sp(::user::window) base_application::window_from_os_data_permanent(void * pdata)
{

   return m_pimpl->window_from_os_data_permanent(pdata);

}
#endif



void base_application::DoWaitCursor(int32_t nCode)
{

   if (nCode < 0)
   {

      m_iWaitCursorCount = 0;
      ShowWaitCursor(false);

   }
   else if (nCode == 0)
   {

      if (m_iWaitCursorCount > 0)
      {
         m_iWaitCursorCount--;
      }

      if (m_iWaitCursorCount > 0)
      {

         ShowWaitCursor(true);

      }

      m_iWaitCursorCount = 0;
      ShowWaitCursor(false);

   }
   else
   {

      if (m_iWaitCursorCount < 0)
      {
         m_iWaitCursorCount = 0;
      }

      m_iWaitCursorCount++;

      ShowWaitCursor(true);

   }



}

void base_application::ShowWaitCursor(bool bShow)
{

   if (m_pimpl == NULL)
      return;

   m_pimpl->ShowWaitCursor(bShow);

}



void base_application::construct()
{

   if (::thread::m_p.is_null())
   {

      ::thread::m_p.create(allocer());

   }

   if (m_pimpl.is_null())
   {

      m_pimpl.create(allocer());

   }

   if (m_pfontopus.is_null())
   {

      m_pfontopus = create_fontopus();

      if (m_pfontopus == NULL)
         throw simple_exception(this, "could not create fontopus for base_application (base_application::construct)");

   }

   if (m_psockets.is_null())
   {

      m_psockets = canew(::sockets::sockets(this));

      m_psockets->construct(this);

      if (!m_psockets->initialize1())
         throw simple_exception(this, "could not initialize (1) sockets for base_application (base_application::construct)");


      if (!m_psockets->initialize())
         throw simple_exception(this, "could not initialize sockets for base_application (base_application::construct)");

   }

}


bool base_application::process_initialize()
{

   throw interface_only_exception(this);

}


bool base_application::initialize1()
{

   throw interface_only_exception(this);

}


bool base_application::initialize2()
{

   throw interface_only_exception(this);

}


bool base_application::initialize3()
{

   throw interface_only_exception(this);

}


bool base_application::initialize()
{

   throw interface_only_exception(this);

}


void base_application::LockTempMaps()
{

   throw interface_only_exception(this);

}


bool base_application::UnlockTempMaps(bool bDeleteTemps)
{

   throw interface_only_exception(this);

}


void base_application::TermThread(HINSTANCE hInstTerm)
{

   throw interface_only_exception(this);

}


/*#ifdef METROWIN
sp(::user::interaction) base_application::window_from_os_data(void * pdata)
{

   throw interface_only_exception(this);

}


sp(::user::interaction) base_application::window_from_os_data_permanent(void * pdata)
{

   throw interface_only_exception(this);

}


#endif*/

sp(::user::window) base_application::FindWindow(const char * lpszClassName, const char * lpszWindowName)
{

   throw interface_only_exception(this);

}


sp(::user::window) base_application::FindWindowEx(oswindow oswindowParent, oswindow oswindowChildAfter, const char * lpszClass, const char * lpszWindow)
{

   throw interface_only_exception(this);

}


string base_application::get_version()
{

   throw interface_only_exception(this);

}


void base_application::set_thread(thread * pthread)
{

   throw interface_only_exception(this);

}


void base_application::SetCurrentHandles()
{

   throw interface_only_exception(this);

}


void base_application::set_env_var(const string & var, const string & value)
{

   throw interface_only_exception(this);

}


bool base_application::set_main_init_data(::core::main_init_data * pdata)
{

   throw interface_only_exception(this);

}




bool base_application::_001OnDDECommand(const char * lpcsz)
{

   throw interface_only_exception(this);

}


void base_application::_001EnableShellOpen()
{

   throw interface_only_exception(this);

}


sp(::user::object) base_application::_001OpenDocumentFile(var varFile)
{

   throw interface_only_exception(this);

}


void base_application::_001OnFileNew(signal_details * pobj)
{

   throw interface_only_exception(this);

}


::user::printer * base_application::get_printer(const char * pszDeviceName)
{

   throw interface_only_exception(this);

}


bool base_application::update_module_paths()
{

   throw interface_only_exception(this);

}


string base_application::draw2d_get_default_library_name()
{

   throw interface_only_exception(this);

}


string base_application::multimedia_audio_get_default_library_name()
{

   throw interface_only_exception(this);

}


string base_application::multimedia_audio_mixer_get_default_library_name()
{

   throw interface_only_exception(this);

}


string base_application::veriwell_multimedia_music_midi_get_default_library_name()
{

   throw interface_only_exception(this);

}



::fontopus::user * base_application::get_user()
{

   return m_pfontopus->get_user();

}

bool base_application::get_auth(const string & pszForm, string & strUsername, string & strPassword)
{
   UNREFERENCED_PARAMETER(pszForm);
   UNREFERENCED_PARAMETER(strUsername);
   UNREFERENCED_PARAMETER(strPassword);
   return false;
}


/*::fontopus::user * application::create_user(const string & pszLogin)
{
return NULL;
}*/

::fontopus::user * base_application::create_current_user()
{
   return NULL;
   /*   string str = get_current_user_login();
   return create_user(str);*/
}

/*string application::get_current_user_login()
{
return "";
}*/


void base_application::set_locale(const string & lpcsz, bool bUser)
{
   m_strLocale = lpcsz;
   on_set_locale(lpcsz, bUser);
}

void base_application::set_schema(const string & lpcsz, bool bUser)
{
   m_strSchema = lpcsz;
   on_set_schema(lpcsz, bUser);
}

void base_application::on_set_locale(const string & lpcsz, bool bUser)
{
   UNREFERENCED_PARAMETER(bUser);
   UNREFERENCED_PARAMETER(lpcsz);
   //System.appa_load_string_table();
}

void base_application::on_set_schema(const string & lpcsz, bool bUser)
{
   UNREFERENCED_PARAMETER(bUser);
   UNREFERENCED_PARAMETER(lpcsz);
   //System.appa_load_string_table();
}



void base_application::process(machine_event_data * pdata)
{
   if (pdata->m_fixed.m_bRequestCloseApplication)
   {
      _001CloseApplication();
   }
}


void base_application::_001CloseApplication()
{

   throw todo(get_app());

}





sp(::user::interaction) base_application::release_capture_uie()
{

#if defined(LINUX)

   oswindow oswindowCapture = ::GetCapture();
   if (oswindowCapture == NULL)
      return NULL;
   return oswindowCapture->get_user_interaction()->release_capture();

#elif defined(WINDOWS)

   oswindow oswindowCapture = ::GetCapture();
   if (oswindowCapture == NULL)
      return NULL;
   return System.window_from_os_data(oswindowCapture)->release_capture();

#elif defined(MACOS)

   oswindow oswindowCapture = ::GetCapture();
   if (oswindowCapture == NULL)
      return NULL;
   return oswindowCapture->get_user_interaction()->release_capture();

#else

   throw not_implemented(get_app());

#endif

}


sp(::user::interaction) base_application::get_capture_uie()
{

#ifdef METROWIN

   oswindow oswindowCapture = ::GetCapture();

   if (oswindowCapture == NULL)
      return NULL;

   ::user::interaction * pui = oswindowCapture->window();

   if (pui == NULL)
      return NULL;

   return pui->get_capture();

#elif defined(WINDOWS)

   oswindow oswindowCapture = ::GetCapture();

   if (oswindowCapture == NULL)
      return NULL;

   ::user::window * pwindow = System.window_from_os_data(oswindowCapture).cast < ::user::window >();

   if(pwindow == NULL)
      return NULL;

   return pwindow->get_capture();

#else

   //      throw not_implemented(get_app());

   oswindow oswindowCapture = ::GetCapture();

   if (oswindowCapture == NULL)
      return NULL;

   return ::GetCapture()->get_user_interaction()->m_pimpl.cast < ::user::window >()->get_capture();

#endif

}



math::math & base_application::math()
{
   return *m_pmath;
}




::count base_application::get_monitor_count()
{

   return System.get_monitor_count();

}


bool base_application::get_monitor_rect(index iMonitor, LPRECT lprect)
{

   return System.get_monitor_rect(iMonitor, lprect);

}


::count base_application::get_desk_monitor_count()
{

   return System.get_desk_monitor_count();

}



bool base_application::get_desk_monitor_rect(index iMonitor, LPRECT lprect)
{

   return System.get_desk_monitor_rect(iMonitor, lprect);

}



bool base_application::is_licensed(const char * pszId, bool bInteractive)
{

   if (directrix()->m_varTopicQuery.has_property("install"))
      return true;

   if (directrix()->m_varTopicQuery.has_property("uninstall"))
      return true;

   return license().has(pszId, bInteractive);

}

string base_application::get_license_id()
{

   return m_strAppId;

}




string base_application::get_locale()
{
   return m_strLocale;
}

string base_application::get_schema()
{
   return m_strSchema;
}


::user::str_context * base_application::str_context()
{

   return m_puserstrcontext;

}


string base_application::get_locale_schema_dir()
{

   return System.dir().simple_path(get_locale(), get_schema());

}

string base_application::get_locale_schema_dir(const string & strLocale)
{

   if (strLocale.is_empty())
      return System.dir().simple_path(get_locale(), get_schema());
   else
      return System.dir().simple_path(strLocale, get_schema());

}

string base_application::get_locale_schema_dir(const string & strLocale, const string & strSchema)
{
   if (strLocale.is_empty())
   {
      if (strSchema.is_empty())
         return System.dir().simple_path(get_locale(), get_schema());
      else
         return System.dir().simple_path(get_locale(), strSchema);
   }
   else
   {
      if (strSchema.is_empty())
         return System.dir().simple_path(strLocale, get_schema());
      else
         return System.dir().simple_path(strLocale, strSchema);
   }
}



void base_application::get_cursor_pos(LPPOINT lppoint)
{
   if (is_system())
   {
      if (m_bSessionSynchronizedCursor)
      {
         ::GetCursorPos(&m_ptCursor);
      }
      if (lppoint != NULL)
      {
         *lppoint = m_ptCursor;
      }
   }
   else if (is_session())
   {
      if (m_bSessionSynchronizedCursor)
      {
         System.get_cursor_pos(&m_ptCursor);
      }
      if (lppoint != NULL)
      {
         *lppoint = m_ptCursor;
      }
   }
   else
   {
      Session.get_cursor_pos(lppoint);
   }
}



sp(::user::interaction) base_application::get_focus_guie()
{

#ifdef METROWIN

   return GetFocus()->window();

#elif defined(WINDOWSEX) || defined(LINUX)

   sp(::user::window) pwnd = System.window_from_os_data_permanent(::GetFocus());
   if (pwnd != NULL)
   {
      if (System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
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
   if (pwnd != NULL)
   {
      if (System.get_active_guie()->get_safe_handle() == pwnd->get_safe_handle()
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



uint32_t base_application::get_thread_id()
{
   return m_pimpl->get_thread_id();
}




sp(::user::interaction) base_application::get_active_guie()
{

#if defined(WINDOWSEX) || defined(LINUX) || defined(MACOS)

   return window_from_os_data(::GetActiveWindow());

#else

   if (frames().get_size() <= 0)
      return NULL;

   return frames()(0);

#endif

}


geometry::geometry & base_application::geometry()
{

   return *m_pgeometry;

}


#ifndef METROWIN

void base_application::get_time(timeval *p)
{
   m_pimpl->get_time(p);
}

#endif


bool base_application::do_prompt_file_name(var & varFile, UINT nIDSTitle, uint32_t lFlags, bool bOpenFileDialog, sp(::user::impact_system) ptemplate, sp(::user::object) pdocument)
{

   UNREFERENCED_PARAMETER(varFile);
   UNREFERENCED_PARAMETER(nIDSTitle);

   return false;

}

string CLASS_DECL_BASE base_application::show_auth_window(LPRECT lprect, string & strUsername, string & strSessId, string & strServerId, string & strLoginUrl, string strFontopusServer)
{

   return ::fontopus::show_auth_window(this, lprect, strUsername, strSessId, strServerId, strLoginUrl, strFontopusServer);

}




int_bool base_application::get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{

#ifdef METROWIN

   string str(::Windows::Storage::ApplicationData::Current->TemporaryFolder->Path);

#else

   char lpPathBuffer[MAX_PATH * 4];

   uint32_t dwRetVal = GetTempPath(sizeof(lpPathBuffer), lpPathBuffer);

   if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {

      return FALSE;

   }

   string str(lpPathBuffer);

#endif

   char bufItem[64];

   string strRelative;

   SYSTEMTIME st;

   memset_dup(&st, 0, sizeof(st));

   GetSystemTime(&st);

   itoa_dup(bufItem, st.wYear, 10);
   zero_pad(bufItem, 4);
   strRelative += bufItem;

   itoa_dup(bufItem, st.wMonth, 10);
   zero_pad(bufItem, 2);
   strRelative += "-";
   strRelative += bufItem;

   itoa_dup(bufItem, st.wDay, 10);
   zero_pad(bufItem, 2);
   strRelative += "-";
   strRelative += bufItem;

   itoa_dup(bufItem, st.wHour, 10);
   zero_pad(bufItem, 2);
   strRelative += " ";
   strRelative += bufItem;

   itoa_dup(bufItem, st.wMinute, 10);
   zero_pad(bufItem, 2);
   strRelative += "-";
   strRelative += bufItem;

   itoa_dup(bufItem, st.wSecond, 10);
   zero_pad(bufItem, 2);
   strRelative += "-";
   strRelative += bufItem;

   string strRet;

   for (int32_t i = 0; i < (1024 * 1024); i++)
   {
      strRet = System.dir().path(str, strRelative + "-" + hex::lower_from(i + 1), string(pszName) + string(".") + pszExtension);
      if (pszTemplate != NULL)
      {
         if (System.install().is_file_ok(szRet, pszTemplate))
            return true;
      }
      if (file_exists_dup(szRet))
      {
         try
         {

            m_pbasesystem->file().del(szRet);

         }
         catch(...)
         {

            return false;

         }

         return true;

      }
      else
      {
         return true;
      }
   }
   return FALSE;


}


int_bool base_application::get_temp_file_name(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension)
{

   return get_temp_file_name_template(szRet, iBufferSize, pszName, pszExtension, NULL);

}



void base_application::get_screen_rect(LPRECT lprect)
{
#ifdef METROWIN
   if (m_bSessionSynchronizedScreen)
   {
      System.get_monitor_rect(0, m_rectScreen);
   }
#elif defined(LINUX)
   if (m_bSessionSynchronizedScreen)
   {
      System.get_monitor_rect(0, m_rectScreen);
   }
#elif defined(MACOS)
   if (m_bSessionSynchronizedScreen)
   {
      System.get_monitor_rect(0, m_rectScreen);
   }
#else
   if (m_bSessionSynchronizedScreen)
   {
      oswindow oswindowDesktop = ::GetDesktopWindow();
      ::GetWindowRect(oswindowDesktop, &m_rectScreen);
   }
#endif
   if (lprect != NULL)
   {
      *lprect = m_rectScreen;
   }
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


void base_application::Ex1OnFactoryExchange()
{

   System.factory().creatable_large < ::file::exception >();

   static base_library library(this);

   if (!library.open("os"))
      throw "failed to do factory exchange";

   PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library.get < PFN_ca2_factory_exchange >("ca2_factory_exchange");

   pfn_ca2_factory_exchange(this);

}

::core::savings & base_application::savings()
{

   return *m_psavings;

}


string base_application::get_ca2_module_folder()
{
   single_lock sl(&m_mutex, true);
   return m_strCa2ModuleFolder;
}

string base_application::get_ca2_module_file_path()
{

   string strModuleFileName;

#ifdef WINDOWSEX

   char lpszModuleFilePath[MAX_PATH + 1];

   if (GetModuleFileName(::GetModuleHandleA("core.dll"), lpszModuleFilePath, MAX_PATH + 1))
   {

      strModuleFileName = lpszModuleFilePath;

   }

#elif defined(METROWIN)

   throw todo(this);

#else

#ifdef RTLD_DI_LINKMAP

   {

      void * handle = dlopen("core.so", 0);

      if (handle == NULL)
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

      if (App(this).file().exists(System.dir().path(strCurDir, "core.dylib")))
      {
         m_strCa2ModuleFolder = strCurDir;
         goto finishedCa2Module;
      }


      if (App(this).file().exists(System.dir().path(m_strModuleFolder, "core.dylib")))
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

string base_application::get_module_folder()
{
   return m_strModuleFolder;
}

string base_application::get_module_file_path()
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

   if (lpszModuleFilePath == NULL)
      return "";

   string strModuleFileName(lpszModuleFilePath);

   free(lpszModuleFilePath);

   return strModuleFileName;

#endif

}


string base_application::get_module_title()
{
   return file_title(get_module_file_path());
}

string base_application::get_module_name()
{
   return file_name(get_module_file_path());
}


::visual::icon * base_application::set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon)
{

   ::visual::icon * piconOld = get_icon(pobject, bBigIcon);

   if (bBigIcon)
   {

      pobject->oprop("big_icon").operator =((sp(element)) picon);

   }
   else
   {

      pobject->oprop("small_icon").operator =((sp(element)) picon);

   }

   return piconOld;

}


::visual::icon * base_application::get_icon(object * pobject, bool bBigIcon) const
{

   if (bBigIcon)
   {

      return const_cast < object * > (pobject)->oprop("big_icon").cast < ::visual::icon >();

   }
   else
   {

      return const_cast < object * > (pobject)->oprop("small_icon").cast < ::visual::icon >();

   }

}



bool base_application::final_handle_exception(::exception::exception & e)
{
   UNREFERENCED_PARAMETER(e);
   //linux      exit(-1);

   if (!is_system())
   {

      // get_app() may be it self, it is ok...
      if (Sys(get_app()).final_handle_exception((::exception::exception &) e))
         return true;


   }

   return false;
}


::fontopus::fontopus * base_application::create_fontopus()
{

   return canew(::fontopus::fontopus(this));

}


bool base_application::init_main_data(::core::main_init_data * pdata)
{

   return false;

}
