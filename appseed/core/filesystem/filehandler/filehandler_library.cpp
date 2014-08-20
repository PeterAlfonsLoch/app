#include "framework.h"




namespace filehandler
{


   library::library(sp(::axis::application) papp) :
      element(papp),
      ::axis::library(papp, 0, "app")
   {
   }

   library::~library()
   {
   }


   bool library::handles_extension(const char * pszExtension)
   {
         
      stringa stra;

      get_extension_list(stra);

      if(!stra.contains_ci(pszExtension))
         return false;

      return true;

   }

   bool library::handles_mime_type(const char * pszMimeType)
   {
         
      stringa stra;
         
      get_mime_type_list(stra);
         
      if(!stra.contains_ci(pszMimeType))
         return false;

      return true;

   }


   void library::get_extension_app(stringa & straAppId, const char * pszExtension)
   {

      if(!handles_extension(pszExtension))
         return;
         
      stringa stra;

      get_app_list(stra);

      if(stra.get_count() == 1)
      {
         straAppId.add(m_strRoot + "/" + stra[0]);
      }

   }

   void library::get_mime_type_app(stringa & straAppId, const char * pszMimeType)
   {
         
      if(!handles_mime_type(pszMimeType))
         return;

      stringa stra;

      get_app_list(stra);

      if(stra.get_count() == 1)
      {
         straAppId.add(m_strRoot + "/" + stra[0]);
      }

   }

   void library::get_extension_list(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }


   void library::get_mime_type_list(stringa & stra)
   {
      UNREFERENCED_PARAMETER(stra);
   }



   
} // namespace filehandler




