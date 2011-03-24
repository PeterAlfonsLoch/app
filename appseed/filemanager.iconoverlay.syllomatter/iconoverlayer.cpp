#include "StdAfx.h"


namespace filemanager
{

   namespace syllomatter
   {

      iconoverlayer::iconoverlayer(::ca::application * papp) :
         ca(papp),
         ::filemanager::iconoverlayer(papp)
      {
      }

      iconoverlayer::~iconoverlayer()
      {
      }


      bool iconoverlayer::initialize()
      {
         return true;
      }

      bool iconoverlayer::finalize()
      {
         return true;
      }


      // give a chance to cache and optimize
      void iconoverlayer::on_open_directory(const char * pszPath)
      {
      }


      void iconoverlayer::overlay(const char * pszPath, ::ca::graphics * pgraphics, LPCRECT lpcrect)
      {
      }

   } // namespace syllomatter

} // namespace filemanager