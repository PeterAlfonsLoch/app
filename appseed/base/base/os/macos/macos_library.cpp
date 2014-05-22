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

   
   library::library(sp(::base::application) papp, const char * pszOpen) :
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
   

   bool library::open(const char * pszPath, bool bAutoClose)
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
      else if(strPath == "os2")
      {
         strPath = "ca2os2";
      }
      
      if(!str_ends_dup(strPath, ".dylib"))
         strPath += ".dylib";

      if(!str_begins_dup(strPath, "lib"))
         strPath = "lib" + strPath;
      
      m_plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_LAZY);
      
      return true;
      
   }
   

   bool library::close()
   {
      
      if(m_plibrary != NULL)
      {
         
         dlclose(m_plibrary);
         
      }
      
      return true;
      
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
      
      return m_plibrary == NULL;
      
   }


   
   
} // namespace base




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