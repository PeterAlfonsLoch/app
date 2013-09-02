#include "framework.h"



application::application()
{

   m_psignal = new signal();


}

int32_t application::simple_message_box(const char * pszMessage, UINT fuStyle)
{

#if defined(WINDOWSEX)

   return MessageBoxW(NULL, wstring(pszMessage), wstring(m_strAppName), fuStyle);
   //return MessageBoxW((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())),
   //   wstring(pszMessage), wstring(m_strAppName), fuStyle);

#elif  defined(LINUX) || defined(MACOS) || defined(ANDROID)

   return MessageBox((puiOwner == NULL ? NULL : (puiOwner->get_wnd() == NULL ? NULL : puiOwner->get_handle())), pszMessage, m_strAppName, fuStyle);

#else

   return MessageBox(m_psystem->m_pui->get_handle(), pszMessage, m_strAppName, fuStyle);

#endif

}


bool application::load_string(string & str, id id)
{
   UNREFERENCED_PARAMETER(id);
   str.Empty();
   return false;
}


sp(element) application::alloc(sp(type) info)
{
   return System.alloc(this, info);
}

sp(element) application::alloc(const  id & idType)
{
   return System.alloc(this, idType);
}

bool application::is_system()
{

   return true;

}



//string application::matter_as_string(const char * pszMatter, const char * pszMatter2 = NULL);
//string application::dir_matter(const char * pszMatter, const char * pszMatter2 = NULL);
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

string application::file_as_string(var varFile)
{

   if(::str::begins_ci(varFile.get_string(), "http://")
   || ::str::begins_ci(varFile.get_string(), "https://"))
   {
      return http_get_dup(varFile.get_string());
   }
   else if(::str::begins_ci(varFile["url"].get_string(), "http://")
   || ::str::begins_ci(varFile["url"].get_string(), "https://"))
   {
      return http_get_dup(varFile["url"].get_string());
   }
   else
   {
      return file_as_string_dup(varFile.get_string());
   }

}

string application::dir_path(const char * psz1, const char * psz2, const char * psz3)
{
   return ::dir::path(psz1, psz2, psz3);
}

string application::dir_name(const char * psz)
{
   return ::dir::name(psz);
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


sp(command_thread) application::command_central()
{
   return m_pcommandthread;
}

sp(command_thread) application::command()
{
   return m_pcommandthread;
}

sp(command_thread) application::guideline()
{
   return m_pcommandthread;
}

sp(command_thread) application::directrix()
{
   return m_pcommandthread;
}

sp(command_thread) application::axiom()
{
   return m_pcommandthread;
}

bool application::verb()
{
   axiom()->run();
   return true;
}

sp(command_thread) application::creation()
{
   return m_pcommandthread;
}


