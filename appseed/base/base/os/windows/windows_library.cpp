#include "framework.h"


void * __node_library_open(const char * pszPath)
{

   void * plibrary = NULL;

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

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(strPath));

   }
   catch(...)
   {

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + strPath));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16(::dir::path(::dir::get_ca2_module_folder(),strPath)));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + ::dir::path(::dir::get_ca2_module_folder(),strPath)));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16(::dir::path(::dir::get_base_module_folder(),strPath)));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + ::dir::path(::dir::get_base_module_folder(),strPath)));

      }
      catch(...)
      {

      }

   }

   return plibrary;

}


bool __node_library_close(void * plibrary)
{

   if(plibrary == NULL)
      return false;

   bool bOk = false;

   try
   {

      bOk = ::FreeLibrary((HINSTANCE)plibrary) != FALSE;

   }
   catch(...)
   {

   }

   return bOk;

}


void * __node_library_open_ca2(const char * psz)
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

void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);

}


