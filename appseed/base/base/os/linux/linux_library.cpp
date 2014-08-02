#include "framework.h"
#include <dlfcn.h>

namespace base
{
library::library(sp(::base::application) papp) :
element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

}


library::library(sp(::base::application) papp, int iDesambig, const char * pszOpen) :
element(papp)
{

   m_plibrary = NULL;

   m_bAutoClose = false;

   open(pszOpen);

}


library::~library()
{

   if(m_bAutoClose)
   {

      close();

   }

}


bool library::open(const char * pszPath, bool bAutoClose, bool bCa2)
{

   if(m_bAutoClose)
   {

      close();

   }

   m_bAutoClose = bAutoClose;

   string strPath(pszPath);

   if(strPath == "os")
   {

      strPath = "ca2os";

   }
   else if(strPath == "app_sphere")
   {

      strPath = "basesphere";

   }

   if(strstr_dup(strPath, ".") == NULL)
      strPath += ".so";

   if(strstr((const char *) strPath, "/") == NULL && !str_begins_dup(strPath, "lib"))
      strPath = "lib" + strPath;

   m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);
   int iError = errno;

   const char * psz = strerror(iError);

   if(psz != NULL)
   {

      fprintf(stderr, "%s\n", psz);

   }

   const char * psz2 = dlerror();

   if(psz2 != NULL)
   {

      fprintf(stderr, "%s\n", psz2);

   }

   return m_plibrary != NULL;

}


bool library::close()
{
   if(m_plibrary != NULL)
   {
      dlclose(m_plibrary);
   }
}


void * library::raw_get(const char * pszElement)
{
   return dlsym(m_plibrary, pszElement);
}




bool library::is_opened()
{

   return m_plibrary != NULL;

}


bool library::is_closed()
{

   return !is_opened();

}



} // namespace base



