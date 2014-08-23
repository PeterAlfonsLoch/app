#include "framework.h"
#include <dlfcn.h>


::axis::library::axis::library(sp(::aura::application) papp) : element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

}


::axis::library::axis::library(sp(::aura::application) papp, const char * pszOpen) :
element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

   open(pszOpen);

}


::axis::library::~::axis::library()
{

   if (m_bAutoClose)
   {

      close();

   }

}


bool ::axis::library::open(const char * pszPath, bool bAutoClose)
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


bool ::axis::library::close()
{
   if (m_plibrary != NULL)
   {
      dlclose(m_plibrary);
   }
}


void * ::axis::library::raw_get(const char * pszElement)
{
   return dlsym(m_plibrary, pszElement);
}

ca2_library::ca2_library(sp(::aura::application) papp) :
element(papp),
::axis::library(papp)
{
}

ca2_library::ca2_library(sp(::aura::application) papp, const char * pszOpen) :
element(papp),
::axis::library(papp, pszOpen)
{

}


ca2_library::~ca2_library()
{
   
}


bool ca2_library::open(const char * pszPath, bool bAutoClose)
{

   return ::axis::library::open(pszPath, bAutoClose);

}


bool ::axis::library::is_opened()
{

   return m_plibrary != NULL;

}


bool ::axis::library::is_closed()
{

   return !is_opened();

}



