#pragma once


namespace filemanager
{

   namespace syllomatter
   {

      class iconoverlayer :
         virtual public ::filemanager::iconoverlayer
      {
      public:
         iconoverlayer(::ca::application * papp);
         virtual ~iconoverlayer();

         virtual bool initialize();
         virtual bool finalize();


         // give a chance to cache and optimize
         virtual void on_open_directory(const char * pszPath);

         virtual void overlay(const char * pszPath, ::ca::graphics * pgraphics, LPCRECT lpcrect);

      };

   } // namespace syllomatter

} // namespace filemanager