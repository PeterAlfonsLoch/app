#include "framework.h"
#include "metrowin.h"

base_library::base_library(sp(::aura::application) papp) :
   element(papp)
{
   m_bAutoClose = true;
   m_plibrary = NULL;
}

base_library::base_library(sp(::aura::application) papp, const char * pszOpen) :
   element(papp)
{
   m_bAutoClose = true;
   m_plibrary = NULL;
   open(pszOpen);
}

base_library::~base_library()
{
   if(m_bAutoClose)
   {
      close();
   }
}

bool base_library::is_opened()
{
   return m_plibrary != NULL;
}

bool base_library::is_closed()
{
   return !is_opened();
}


bool base_library::open(const char * pszPath, bool bAutoClose)
{

   m_bAutoClose = bAutoClose;

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
   else if(stricmp_dup(pszPath, "app_sphere") == 0)
   {
      pszPath = "sphere";
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


#ifdef METROWIN
   //m_plibrary = ::
   m_plibrary = ::LoadPackagedLibrary(gen_utf8_to_16(strPath), 0);
#else
   m_plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));
#endif

#ifdef WINDOWSEX
   if(m_plibrary == NULL)
   {

      strPath = "\\\\?\\" + strPath;

      m_plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));

   }
#endif
   
   return m_plibrary != NULL;

}

bool base_library::close()
{
   if(m_plibrary != NULL)
   {
      bool bOk = ::FreeLibrary((HINSTANCE) m_plibrary) != FALSE;
      m_plibrary = NULL;
      return bOk;
   }
   return true;
}


void * base_library::raw_get(const char * pszElement)
{
   return ::GetProcAddress((HINSTANCE) m_plibrary, pszElement);
}

ca2_library::ca2_library(sp(::aura::application) papp) :
element(papp),
base_library(papp)
{
}

ca2_library::ca2_library(sp(::aura::application) papp, const char * pszOpen) :
element(papp),
base_library(papp, pszOpen)
{

}

ca2_library::~ca2_library()
{

}

bool ca2_library::open(const char * pszPath, bool bAutoClose)
{
   m_plibrary = ::core::open_ca2_library(pszPath);
   return m_plibrary != NULL;
}






namespace core
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
   ::SetDllDirectory(dir::ca2("stage\\x64") + "\\");
#else
   ::SetDllDirectory(dir::ca2("stage\\x86") + "\\");
#endif*/
   return LoadPackagedLibrary(wstring(psz), 0);
}

} // namespace core

