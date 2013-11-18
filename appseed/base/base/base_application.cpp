#include "framework.h"



base_application::base_application() :
   m_allocer(this)
{

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

   m_psignal = new class signal();

   m_pcommandthread           = new ::command_thread(this);

   m_bZipIsDir = true;

   m_pmapKeyPressed = NULL;

   m_bLicense = true;

}

base_application::~base_application()
{
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

   return NULL;

}

sp(::user::interaction) base_application::window_from_os_data_permanent(void * pdata)
{

   return NULL;

}
#else
sp(::user::window) base_application::window_from_os_data(void * pdata)
{

   return NULL;

}

sp(::user::window) base_application::window_from_os_data_permanent(void * pdata)
{
   
   return NULL;

}
#endif
