#include "framework.h"



namespace base
{


   library::library(sp(::base::application) papp):
      element(papp)
   {
      m_bAutoClose = true;
      m_plibrary = NULL;
   }

   library::library(sp(::base::application) papp,const char * pszOpen):
      element(papp)
   {
      m_bAutoClose = true;
      m_plibrary = NULL;
      open(pszOpen);
   }

   library::~library()
   {
      if(m_bAutoClose)
      {
         close();
      }
   }

   bool library::is_opened()
   {
      return m_plibrary != NULL;
   }

   bool library::is_closed()
   {
      return !is_opened();
   }


   bool library::open(const char * pszPath,bool bAutoClose)
   {

      m_bAutoClose = bAutoClose;

      if(stricmp_dup(pszPath,"app_c") == 0)
      {
         pszPath = "c";
      }
      else if(stricmp_dup(pszPath,"app_ca") == 0)
      {
         pszPath = "ca";
      }
      else if(stricmp_dup(pszPath,"app_ca2") == 0)
      {
         pszPath = "ca2";
      }

      string strPath(pszPath);

      if(str_ends_ci_dup(strPath,".ilk"))
         return false;

      if(str_ends_ci_dup(strPath,".pdb"))
         return false;

      if(str_ends_ci_dup(strPath,".lib"))
         return false;

      if(str_ends_ci_dup(strPath,".exp"))
         return false;

      if(strstr_dup(file_title_dup(strPath),".") == NULL)
         strPath += ".dll";

#ifdef _M_X64
      //::SetDllDirectory(dir::element("stage\\x64") + "\\");
#else
      //::SetDllDirectory(dir::element("stage\\x86") + "\\");
#endif


      try
      {

         m_plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));

      }
      catch(...)
      {

      }

      if(m_plibrary == NULL)
      {

         try
         {

            m_plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + strPath));

         }
         catch(...)
         {

         }

      }

      if(m_plibrary == NULL)
      {

         try
         {

            m_plibrary = ::LoadLibraryW(gen_utf8_to_16(::dir::path(::dir::get_ca2_module_folder(),strPath)));

         }
         catch(...)
         {

         }

      }

      if(m_plibrary == NULL)
      {

         try
         {

            m_plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + ::dir::path(::dir::get_ca2_module_folder(),strPath)));

         }
         catch(...)
         {

         }

      }

      if(m_plibrary == NULL)
      {

         try
         {

            m_plibrary = ::LoadLibraryW(gen_utf8_to_16(::dir::path(::dir::get_base_module_folder(),strPath)));

         }
         catch(...)
         {

         }

      }

      if(m_plibrary == NULL)
      {

         try
         {

            m_plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + ::dir::path(::dir::get_base_module_folder(),strPath)));

         }
         catch(...)
         {

         }

      }

      return m_plibrary != NULL;

   }

   bool library::close()
   {
      if(m_plibrary != NULL)
      {
         bool bOk = false;
         try
         {
            bOk = ::FreeLibrary((HINSTANCE)m_plibrary) != FALSE;
         }
         catch(...)
         {
         }
         m_plibrary = NULL;
         return bOk;
      }
      return true;
   }


   void * library::raw_get(const char * pszElement)
   {
      return ::GetProcAddress((HINSTANCE)m_plibrary,pszElement);
   }


   void * open_ca2_library(const char * psz)
   {
      /*      string str(psz);
      if(str.find("..") >= 0)
      return FALSE;
      if(str.find(":") >= 0)
      return FALSE;
      if(str.find("\\\\") >= 0)
      return FALSE;
      if(str[0] == '\\')
      return FALSE;
      if(str[0] == '/')
      return FALSE;
      #ifdef _M_X64
      //::SetDllDirectory(dir::element("stage\\x64") + "\\");
      #else
      //::SetDllDirectory(dir::element("stage\\x86") + "\\");
      #endif*/

      return LoadLibrary(psz);

   }

} // namespace base





ca2_library::ca2_library(sp(::base::application) papp):
element(papp),
library(papp)
{
}



ca2_library::ca2_library(sp(::base::application) papp,const char * pszOpen):
element(papp),
library(papp,pszOpen)
{

}


ca2_library::~ca2_library()
{

}


bool ca2_library::open(const char * pszPath,bool bAutoClose)
{

   if(m_bAutoClose)
   {

      close();

   }

   m_bAutoClose = bAutoClose;

   m_plibrary = ::base::open_ca2_library(pszPath);

   return m_plibrary != NULL;

}


