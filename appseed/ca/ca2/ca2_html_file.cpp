#include "StdAfx.h"


namespace ca2
{


   html_file::html_file()
   {
      m_puistrcontext = NULL;
   }

   ::user::str_context * html_file::str_context()
   {
      return m_puistrcontext;
   }



   void html_file::print(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void html_file::printf(const char * lpcsz, ...)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void html_file::printstr(const char * lpcsz, ...)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void html_file::dprint(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }


}


