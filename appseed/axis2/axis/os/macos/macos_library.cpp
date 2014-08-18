#include "framework.h"
#include <dlfcn.h>



   void * __node_library_open(const char * pszPath)
   {
   
      string strPath(pszPath);
      
      if(strPath == "os")
      {
         strPath = "ca2os";
      }
      else if(strPath == "os2")
      {
         strPath = "ca2os2";
      }
      
      if(!str_ends_dup(strPath, ".dylib"))
         strPath += ".dylib";

      if(!str_begins_dup(strPath, "lib"))
         strPath = "lib" + strPath;
      
      void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
      
      return plibrary;
      
   }
   

   bool __node_library_close(void * plibrary)
   {
      
      if(plibrary != NULL)
      {
   
         dlclose(plibrary);
         
      }
      
      return true;
      
   }


   void * __node_library_raw_get(void * plibrary, const char * pszElement)
   {
      
      return dlsym(plibrary, pszElement);
      
   }
   
   


   
   
void * __node_library_open_ca2(const char * pszPath)
{
   
   string strPath(pszPath);
   
   void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
   
   return plibrary;
   
}
