#include "framework.h"
#include <dlfcn.h>


::base::library::base::library(sp(::base::application) papp) : element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

}


::base::library::base::library(sp(::base::application) papp, const char * pszOpen) :
element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

   open(pszOpen);

}


::base::library::~::base::library()
{

   if (m_bAutoClose)
   {

      close();

   }

}


bool ::base::library::open(const char * pszPath, bool bAutoClose)
{

   if (m_bAutoClose)
   {

      close();

   }

   m_bAutoClose = bAutoClose;

   string strPath(pszPath);

   if (strPath == "os")
   {

      strPath = "ca2os";

   }
   else if (strPath == "app_sphere")
   {

      strPath = "ca2sphere";

   }

   if (strstr_dup(strPath, ".") == NULL)
      strPath += ".so";

   if (strstr((const char *)strPath, "/") == NULL && !str_begins_dup(strPath, "lib"))
      strPath = "lib" + strPath;

   //m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
   m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW);
   int iError = errno;

   const char * psz = strerror(iError);

   const char * psz2 = dlerror();

   return m_plibrary != NULL;

}


bool ::base::library::close()
{
   if (m_plibrary != NULL)
   {
      dlclose(m_plibrary);
   }
}


void * ::base::library::raw_get(const char * pszElement)
{
   return dlsym(m_plibrary, pszElement);
}

ca2_library::ca2_library(sp(::base::application) papp) :
element(papp),
::base::library(papp)
{
}

ca2_library::ca2_library(sp(::base::application) papp, const char * pszOpen) :
element(papp),
::base::library(papp, pszOpen)
{

}


ca2_library::~ca2_library()
{
   
}


bool ca2_library::open(const char * pszPath, bool bAutoClose)
{

   return ::base::library::open(pszPath, bAutoClose);

}


bool ::base::library::is_opened()
{

   return m_plibrary != NULL;

}


bool ::base::library::is_closed()
{

   return !is_opened();

}



