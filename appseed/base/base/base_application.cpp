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

   m_psignal = new class signal();

   m_pcommandthread           = new ::command_thread(this);

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

   return true;

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



