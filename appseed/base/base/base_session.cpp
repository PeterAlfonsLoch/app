#include "framework.h"



bool base_session::is_session()
{

   return true;

}

sp(::base_application) base_session::start_application(const char * pszType, const char * pszAppId, sp(::create_context) pcreatecontext)
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

