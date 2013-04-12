#include "framework.h"


namespace html
{


   file::file()
   {
      m_puistrcontext = ::null();
   }

   ::user::str_context * file::str_context()
   {
      return m_puistrcontext;
   }



   void file::print(const string & str)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

#ifdef WINDOWS

   void file::printf(const string & str, ...)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

   void file::printstr(const string & str, ...)
   {
      UNREFERENCED_PARAMETER(str);
      throw interface_only_exception(get_app());
   }

#else

   void file::trace(void *, const char * psz)
   {
      print(psz);
   }

#endif


   void file::dprint(const char * lpcsz)
   {
      UNREFERENCED_PARAMETER(lpcsz);
      throw interface_only_exception(get_app());
   }


} // namespace html


