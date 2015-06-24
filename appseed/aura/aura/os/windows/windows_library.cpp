//#include "framework.h"


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

   if(strstr_dup(file_name_dup(strPath),".") == NULL)
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

         plibrary = ::LoadLibraryW(gen_utf8_to_16(::dir::ca2_module() / strPath));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + string(::dir::ca2_module() / strPath)));

      }
      catch(...)
      {

      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16(string(::dir::base_module()/strPath)));

      }
      catch(...)
      {

      }

      if(plibrary == NULL)
      {
         DWORD dwError = ::GetLastError();
         char * pszError;
         FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,dwError,0,(LPTSTR)&pszError,8,NULL);
         string strError(pszError);
         //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
         ::LocalFree(pszError);

         ::OutputDebugString(strPath + " : LoadLibrary Error (" + ::str::from((uint32_t) dwError) + ") : " + strError);
         if(dwError == 126)
         {
            ::SetDllDirectoryW(gen_utf8_to_16(::dir::base_module()));
            plibrary = ::LoadLibraryW(gen_utf8_to_16(string(::dir::base_module()/strPath)));
         }
      }

   }

   if(plibrary == NULL)
   {

      try
      {

         plibrary = ::LoadLibraryW(gen_utf8_to_16("\\\\?\\" + string(::dir::base_module() / strPath)));

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


