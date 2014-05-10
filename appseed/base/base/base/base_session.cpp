#include "framework.h"


base_session::base_session()
{

   m_pfontopus = create_fontopus();

   if (m_pfontopus == NULL)
      throw simple_exception(this, "could not create fontopus for ::base::application (::base::application::construct)");

   m_pfontopus->construct(this);

}

bool base_session::is_session()
{

   return true;

}

sp(::::base::application) base_session::start_application(const char * pszType, const char * pszAppId, sp(::create_context) pcreatecontext)
{

   throw interface_only_exception(this);

   return NULL;

}


::visual::cursor * base_session::get_cursor()
{
   return NULL;
/*   if (m_ecursor == ::visual::cursor_none)
      return NULL;
   else if (m_ecursor == ::visual::cursor_default)
      return System.visual().get_cursor(m_ecursorDefault);
   else
      return System.visual().get_cursor(m_ecursor);*/
}



::visual::cursor * base_session::get_default_cursor()
{
   return NULL;
}

::fontopus::user * base_session::safe_get_user()
{

   if (m_pfontopus == NULL)
      return NULL;

   return m_pfontopus->m_puser;

}


void base_session::set_cursor(::visual::e_cursor ecursor)
{
   m_ecursor = ecursor;
}

void base_session::set_default_cursor(::visual::e_cursor ecursor)
{
   if (ecursor == ::visual::cursor_default)
   {
      m_ecursorDefault = ::visual::cursor_arrow;
   }
   else
   {
      m_ecursorDefault = ecursor;
   }
}



COLORREF base_session::get_default_color(uint64_t ui)
{

   switch (ui)
   {
   case COLOR_3DFACE:
      return ARGB(127, 192, 192, 184);
   case COLOR_WINDOW:
      return ARGB(127, 255, 255, 255);
   case COLOR_3DLIGHT:
      return ARGB(127, 218, 218, 210);
   case COLOR_3DHIGHLIGHT:
      return ARGB(127, 238, 238, 230);
   case COLOR_3DSHADOW:
      return ARGB(127, 138, 138, 130);
   case COLOR_3DDKSHADOW:
      return ARGB(127, 84, 84, 77);
   default:
      break;
   }

   return ARGB(127, 0, 0, 0);

}





::core::copydesk & base_session::copydesk()
{

   return *m_spcopydesk;

}


::fontopus::user * base_session::get_user()
{

   return m_pfontopus->get_user();

}


bool base_session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
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

::fontopus::user * base_session::create_current_user()
{
   return NULL;
   /*   string str = get_current_user_login();
   return create_user(str);*/
}

/*string application::get_current_user_login()
{
return "";
}*/



bool base_session::is_licensed(const char * pszId, bool bInteractive)
{

   if (directrix()->m_varTopicQuery.has_property("install"))
      return true;

   if (directrix()->m_varTopicQuery.has_property("uninstall"))
      return true;

   return license().has(pszId, bInteractive);

}


::fontopus::fontopus * base_session::create_fontopus()
{

   return canew(::fontopus::fontopus(this));

}





