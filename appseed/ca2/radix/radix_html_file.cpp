#include "StdAfx.h"

namespace html
{

   file::file()
   {
      m_puistrcontext = NULL;
   }

   ::user::str_context * file::str_context()
   {
      return m_puistrcontext;
   }



   void file::print(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void file::printf(const char * lpcsz, ...)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void file::printstr(const char * lpcsz, ...)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

   void file::dprint(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception();
   }

}
