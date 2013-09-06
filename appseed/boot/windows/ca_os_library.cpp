#include "framework.h"
#include <windows.h>


namespace ca
{


   library::library()
   {
      m_bAutoClose = true;
      m_plibrary = NULL;
   }

   library::library(const char * pszOpen)
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


   bool library::open(const char * pszPath)
   {

      if(stricmp_dup(pszPath, "app_c") == 0)
      {
         pszPath = "c";
      }
      else if(stricmp_dup(pszPath, "app_ca") == 0)
      {
         pszPath = "ca";
      }
      else if(stricmp_dup(pszPath, "app_ca2") == 0)
      {
         pszPath = "ca2";
      }

      string strPath(pszPath);

      if(str_ends_ci_dup(strPath, ".ilk"))
         return false;

      if(str_ends_ci_dup(strPath, ".pdb"))
         return false;

      if(str_ends_ci_dup(strPath, ".lib"))
         return false;

      if(str_ends_ci_dup(strPath, ".exp"))
         return false;

      if(strstr_dup(file_title_dup(strPath), ".") == NULL)
         strPath += ".dll";

#ifdef _M_X64
      ::SetDllDirectory(dir::element("stage\\x64") + "\\");
#else
      ::SetDllDirectory(dir::element("stage\\x86") + "\\");
#endif


      m_plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));

      if(m_plibrary == NULL)
      {

         strPath = "\\\\?\\" + strPath;

         m_plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));

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
            bOk = ::FreeLibrary((HINSTANCE) m_plibrary) != FALSE;
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
      return ::GetProcAddress((HINSTANCE) m_plibrary, pszElement);
   }

   ca2_library::ca2_library()
   {
   }

   ca2_library::ca2_library(const char * pszOpen) :
      library(pszOpen)
   {

   }

   ca2_library::~ca2_library()
   {

   }

   bool ca2_library::open(const char * pszPath)
   {
      m_plibrary = ::ca2::open_ca2_library(pszPath);
      return m_plibrary != NULL;
   }




} // namespace ca


namespace ca2
{

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
      ::SetDllDirectory(dir::element("stage\\x64") + "\\");
   #else
      ::SetDllDirectory(dir::element("stage\\x86") + "\\");
   #endif*/

      return LoadLibrary(psz);

   }


} // namespace ca2




