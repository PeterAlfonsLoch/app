#include "StdAfx.h"


namespace tesseract
{


   void library::get_app_list(stringa & stra)
   {

         stra.add("biteditor");
         stra.add("devedge");
         stra.add("eluce");
         stra.add("i2com");
         stra.add("mail");
         stra.add("netnodecfg");
         stra.add("paint");
         stra.add("simpledb");
         stra.add("status");
         stra.add("syllomatter");
         stra.add("tarsila");
         stra.add("vericalc");
         stra.add("veriedit");
         stra.add("verifile");
         stra.add("verisimplevideo");
         stra.add("veriview");
         stra.add("vmsp");
         stra.add("whiteboard");
         stra.add("winservice_filesystemsize");

   }


   void library::get_extension_app(stringa & straApp, const char * pszExtension)
   {
      
      
      string strExtension(pszExtension);

      
      strExtension.make_lower();


      if(strExtension == "*")
      {
         straApp.add_unique("default_file_handler");
      }
/*      else if(strExtension == "mid" || strExtension == "kar" || strExtension == "st3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }
      else if(strExtension == "mp3")
      {
         straApp.add_unique("mplite");
         straApp.add_unique("vmsp");
      }*/
      else if(strExtension == "jpg" || strExtension == "jpeg" || strExtension == "gif" || strExtension == "png")
      {
         straApp.add_unique("eluce");
      }
      else if(strExtension == "mkv" || strExtension == "mpg")
      {
         straApp.add_unique("verisimplevideo");
      }

   }

   void library::get_extension_list(stringa & stra)
   {


      stra.add_unique("mid");
      stra.add_unique("kar");
      stra.add_unique("st3");
      stra.add_unique("jpg");
      stra.add_unique("gif");
      stra.add_unique("jpeg");
      stra.add_unique("png");
      stra.add_unique("mkv");
      stra.add_unique("mpg");


   }


} // namespace tesseract


::ca2::library * get_new_library()
{
   return new ::tesseract::library;
}

