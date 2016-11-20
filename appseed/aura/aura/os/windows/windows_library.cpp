//#include "framework.h"


void * __node_library_open(const char * pszPath, string & strMessage)
{

   strMessage.Empty();

   string strError;

   string strPath(pszPath);

   uint32_t uiError;

   void * plibrary = NULL;

   if (str_ends_ci_dup(strPath, ".ilk"))
   {
    
      return false;

   }

   if(str_ends_ci_dup(strPath,".pdb"))
   {

      return false;

   }

   if(str_ends_ci_dup(strPath,".lib"))
   {

      return false;

   }

   if(str_ends_ci_dup(strPath,".exp"))
   {

      return false;

   }

   if (strstr_dup(file_name_dup(strPath), ".") == NULL)
   {
    
      strPath += ".dll";

   }

   ::output_debug_string("\n\nGoing to load library (1) " + string(strPath) + "\n");

   ::file::path path;

   path = strPath;

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch(...)
   {

   }

   if (plibrary != NULL)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (1) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + strPath;

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch (...)
   {

   }

   if (plibrary != NULL)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (2) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::ca2_module() / strPath;

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch (...)
   {

   }

   uiError = ::GetLastError();

   strError = "\n (3) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::ca2_module() / strPath);

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch (...)
   {

   }

   if (plibrary != NULL)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (4) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = ::dir::base_module() / strPath;

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch (...)
   {

   }

   if (plibrary != NULL)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (5) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;

   path = "\\\\?\\" + string(::dir::base_module() / strPath);

   try
   {

      plibrary = ::LoadLibraryW(gen_utf8_to_16(path));

   }
   catch (...)
   {

   }

   if (plibrary != NULL)
   {

      goto finished;

   }

   uiError = ::GetLastError();

   strError = "\n (6) LoadLibraryW " + path + " failed with (" + ::str::from(uiError) + ") " + get_error_string(uiError);

   strMessage += strError;


finished:

   if (plibrary != NULL)
   {

      strMessage = "node_library_open Success opening " + path;

   }
   else
   {

      strMessage = "node_library_open Failed opening " + strPath + strMessage;

   }

   ::output_debug_string(strMessage + "\n\n");

   return plibrary;

}


bool __node_library_close(void * plibrary)
{

   if(plibrary == NULL)
      return false;

   bool bOk = false;
//#ifndef MEMDLEAK
   try
   {

      bOk = ::FreeLibrary((HINSTANCE)plibrary) != FALSE;

   }
   catch(...)
   {

   }
//#endif
   return bOk;

}


void * __node_library_open_ca2(const char * psz, string & strMessage)
{

   ::output_debug_string("\n\nGoing to load library (2) " + string(psz));

   void * p = LoadLibrary(psz);

   if (p != NULL)
   {

      strMessage = "__node_library_open_ca2 Successfully Loaded " + string(psz);

   }
   else
   {

      uint32_t uiError = GetLastError();

      strMessage = "__node_library_open_ca2 Failed to Load " + string(psz) + " with error (" + str::from(uiError) +
   ")" + get_error_string(uiError);

   }

   ::output_debug_string("\n" + strMessage + "\n\n");

   return p;

}

void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return ::GetProcAddress((HINSTANCE)plibrary,pszEntryName);

}


