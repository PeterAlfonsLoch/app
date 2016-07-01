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
   
   if(!::str::begins_ci(strPath, "/") && !str_begins_dup(strPath, "lib"))
      strPath = "lib" + strPath;
   
   ::output_debug_string("\n\nGoing to dlopen(\"" + strPath + "\", RTLD_LOCAL | RTLD_LAZY)\n\n");
   
   void * plibrary = dlopen(::file::path(::get_exe_path()).folder() / strPath, RTLD_LOCAL | RTLD_LAZY);
   
   if(plibrary == NULL)
   {
      
      string strError(dlerror());
      
      ::output_debug_string("\n\n__node_library_open Failed " + strPath + " with the error: \""+strError+"\"\n\n");
      
      plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
      
   }
   else
   {
      
      ::output_debug_string("\n\n__node_library_open Succeeded " + strPath + "\n\n");
      
   }
   
   
   if(plibrary == NULL)
   {
      
      string strError(dlerror());
      
      ::output_debug_string("\n\n__node_library_open Failed " + strPath + " with the error: \""+strError+"\"\n\n");
      
      plibrary = dlopen(::file::path(::ca2_module_folder_dup()) / strPath, RTLD_LOCAL | RTLD_LAZY);
      
   }
   else
   {
      
      ::output_debug_string("\n\n__node_library_open Succeeded " + strPath + "\n\n");
      
   }
   
   if(plibrary == NULL)
   {
      
      string strError(dlerror());
      
      ::output_debug_string("\n\n__node_library_open Failed " + strPath + " with the error: \""+strError+"\"\n\n");
      
   }
   else
   {
      
      ::output_debug_string("\n\n__node_library_open Succeeded " + strPath + "\n\n");
      
   }
   
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