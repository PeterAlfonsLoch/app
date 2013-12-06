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




