#include "framework.h"
#include <dlfcn.h>


CLASS_DECL_BASE void * __node_library_open(const char * pszPath)
{

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

   void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);

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

   return plibrary;

}


CLASS_DECL_BASE void * __node_library_open_ca2(const char * pszPath)
{

   void * plibrary = dlopen(pszPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);

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

   return plibrary;

}


CLASS_DECL_BASE bool __node_library_close(void * plibrary)
{

   return dlclose(plibrary) == 0;

}


CLASS_DECL_BASE void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return dlsym(plibrary, pszEntryName);

}




























