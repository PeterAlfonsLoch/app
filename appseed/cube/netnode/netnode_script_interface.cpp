#include "StdAfx.h"

netnodeScriptInterface::netnodeScriptInterface()
{
}

netnodeScriptInterface::~netnodeScriptInterface()
{
}

void netnodeScriptInterface::run()
{
}


void netnodeScriptInterface::script_start()
{
}

void netnodeScriptInterface::script_step()
{
}

void netnodeScriptInterface::script_end()
{
}




void netnodeScriptInterface::get_output(string & strHeader, http::memory_file & memfile)
{
}

string & netnodeScriptInterface::gstr(const char * pszKey)
{
   return gprop(pszKey);
}

gen::property & netnodeScriptInterface::gprop(const char * pszKey)
{
   return gen::g_newproperty;
}

bool netnodeScriptInterface::isset(gen::property & prop)
{
   return !prop.is_new();
}












void netnodeScriptInterface::print(const char * lpcsz)
{
}

void netnodeScriptInterface::printf(const char * lpcsz, ...)
{
}

void netnodeScriptInterface::printstr(const char * lpcsz, ...)
{
}

bool netnodeScriptInterface::read_file(const char * lpcsz, array_ptr_alloc < int_array > * prangea)
{
   return false;
}


var netnodeScriptInterface::include(const char * lpcsz)
{
   return var();
}

void netnodeScriptInterface::launch(const char * lpcsz)
{
}



void netnodeScriptInterface::edgify(int iEdge, ::userbase::document_template * ptemplate, bool bMakeVisible)
{
}

void netnodeScriptInterface::edgify_app(int iEdge, ::ca::type_info prtcApp, bool bMakeVisible)
{
}



void netnodeScriptInterface::hand_root()
{
}

string netnodeScriptInterface::ui_exuri()
{
   return "";
}

void netnodeScriptInterface::ui_nav_printOut5(stringa & straLink, stringa & straTitle)
{
}

void netnodeScriptInterface::ui_nav_printOut3(stringa & straLink, stringa & straTitle)
{
}


void netnodeScriptInterface::ui_nav_printOut2(stringa & straLink, stringa & straTitle)
{
}


void netnodeScriptInterface::ui_nav_printOut1(stringa & straLink, stringa & straTitle)
{
}

bool netnodeScriptInterface::script_right()
{
   return false;
}



   void netnodeScriptInterface::dprint(const char * psz)
   {
   }
   
   void netnodeScriptInterface::dinit()
   {
   }
   
   
   void netnodeScriptInterface::dfinish()
   {
   }


   string netnodeScriptInterface::ui_redir(const char * pszLang, const char * pszStyle, const char * pszExUri, const char * pszRoot)
{
   return pszExUri;
}

   void netnodeScriptInterface::ui_redir_add(const char * pszRoot, const char * pszLang, const char * pszStyle, const char * pszTarget)
   {
   }

string netnodeScriptInterface::sys_get_include_path(const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
{
   return "";
}
string netnodeScriptInterface::named_sys_get_include_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, stringa * pstraAccept)
{
   return "";
}
string netnodeScriptInterface::sys_get_base_path(const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
{
   return "";
}
string netnodeScriptInterface::named_sys_get_base_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char *pszBase, stringa * pstraAccept)
{
   return "";
}
string netnodeScriptInterface::sys_get_subdomain_path(const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
{
   return "";
}
string netnodeScriptInterface::named_sys_get_subdomain_path(const char * pszSystemPath, const char * pszExt, const char * pszType, const char * pszDoc, const char * pszBase, const char * pszSubdomain, stringa * pstraAccept)
{
   return "";
}

netnodeSocket & netnodeScriptInterface::netnode()
{
   return *((netnodeSocket *) NULL);
}

string netnodeScriptInterface::this_url(const char * pszKey, var var)
{
   return System.url().set(this_url(), pszKey, var);
}

void netnodeScriptInterface::array_unshift(gen::property & varArray, const var varElement)
{
   array_unshift(varArray.get_value(), varElement);
}

bool      netnodeScriptInterface::mid_fs_read             (const char * pszFolder, const char * pszName)
{
   string strUser;
   __int64 iFolder;
   if(!low_folder(strUser, iFolder, pszFolder))
      return false;
   return low_fs_read(strUser, iFolder, pszName);
}

bool      netnodeScriptInterface::fs_add_user_file        (const char * pszFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite)
{
   string strUser;
   __int64 iFolder;
   if(!low_folder(strUser, iFolder, pszFolder))
      return false;
   return low_fs_add_user_file(strUser, iFolder, hash, key, size, mimetype, extension, pszName, bOverwrite);
}

bool      netnodeScriptInterface::fs_add_user_dir         (const char * pszFolder, const char * pszName)
{
   string strUser;
   __int64 iFolder;
   if(!low_folder(strUser, iFolder, pszFolder))
      return false;
   return low_fs_add_user_dir(strUser, iFolder, pszName);
}

void      netnodeScriptInterface::fs_ls_dir               (const char * pszFolder, int64_array & ia, stringa & stra)
{
   string strUser;
   __int64 iFolder;
   if(!low_folder(strUser, iFolder, pszFolder))
      return;
   return low_fs_ls_dir(strUser, iFolder, ia, stra);
}

void      netnodeScriptInterface::fs_ls_file              (const char * pszFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName)
{
   string strUser;
   __int64 iFolder;
   if(!low_folder(strUser, iFolder, pszFolder))
      return;
   return low_fs_ls_file(strUser, iFolder, straHash, iaKey, iaSize, straMime, straExt, straName);
}


bool      netnodeScriptInterface::fs_read                 (const char * pszPath)
{
   string strPath;
   int iFind = strPath.reverse_find('/');
   if(iFind < 0)
      return false;
   return mid_fs_read(strPath.Left(iFind), strPath.Mid(iFind + 1));
}


bool      netnodeScriptInterface::low_folder_lazy_file(string & strUser, __int64 & iFolder , string & strFile, const char * pszPath)
{
   string strPath(pszPath);
   int iFind = strPath.reverse_find('/');
   if(iFind < 0)
      return false;
   strFile = strPath.Mid(iFind + 1);
   if(strFile.is_empty())
      return false;
   return low_folder(strUser, iFolder, strPath.Left(iFind));
}

