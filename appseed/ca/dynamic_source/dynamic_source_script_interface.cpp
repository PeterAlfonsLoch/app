#include "StdAfx.h"


namespace dynamic_source
{


   script_interface::script_interface()
   {
   }

   script_interface::~script_interface()
   {
   }

   void script_interface::run()
   {
   }


   void script_interface::script_start()
   {
   }

   void script_interface::script_step()
   {
   }

   void script_interface::script_end()
   {
   }




   void script_interface::get_output(string & strHeader, http::memory_file & memfile)
   {
      UNREFERENCED_PARAMETER(strHeader);
      UNREFERENCED_PARAMETER(memfile);
   }

   string & script_interface::gstr(const char * pszKey)
   {
      return gprop(pszKey);
   }

   gen::property & script_interface::gprop(const char * pszKey)
   {
      UNREFERENCED_PARAMETER(pszKey);
      return gen::g_newproperty;
   }

   bool script_interface::isset(gen::property & prop)
   {
      return !prop.is_new();
   }












   void script_interface::print(const char *)
   {
   }

   void script_interface::printf(const char *  ,...)
   {
   }

   void script_interface::printstr(const char * , ...)
   {
   }

   bool script_interface::read_file(const char * , array_ptr_alloc < int_array > * , const char * )
   {
      return false;
   }


   var script_interface::include(const char *, bool )
   {
      return var();
   }

   void script_interface::launch(const char * )
   {
   }


/*
   void script_interface::edgify(int , ::userbase::document_template * , bool )
   {
   }

   void script_interface::edgify_app(int , ::ca::type_info , bool )
   {
   }
   */


   void script_interface::hand_root()
   {
   }

   string script_interface::ui_exuri()
   {
      return "";
   }

   void script_interface::ui_nav_printOut5(stringa & , stringa & )
   {
   }

   void script_interface::ui_nav_printOut3(stringa & , stringa & )
   {
   }


   void script_interface::ui_nav_printOut2(stringa & , stringa & )
   {
   }


   void script_interface::ui_nav_printOut1(stringa & , stringa & )
   {
   }

   bool script_interface::script_right()
   {
      return false;
   }



   void script_interface::dprint(const char * )
   {
   }

   void script_interface::dinit()
   {
   }


   void script_interface::dfinish()
   {
   }


   string script_interface::ui_redir(const char * , const char * , const char * pszExUri, const char * )
   {
      return pszExUri;
   }

   void script_interface::ui_redir_add(const char * , const char * , const char * , const char * )
   {
   }

   string script_interface::sys_get_include_path(const char * , const char * , const char * , stringa * )
   {
      return "";
   }
   string script_interface::named_sys_get_include_path(const char * , const char * , const char * , const char * , stringa * )
   {
      return "";
   }
   string script_interface::sys_get_base_path(const char * , const char * , const char * , const char *, stringa * )
   {
      return "";
   }
   string script_interface::named_sys_get_base_path(const char * , const char * , const char * , const char * , const char *, stringa * )
   {
      return "";
   }
   string script_interface::sys_get_subdomain_path(const char * , const char * , const char * , const char * , const char * , stringa * )
   {
      return "";
   }
   string script_interface::named_sys_get_subdomain_path(const char * , const char * , const char * , const char * , const char * , const char * , stringa * )
   {
      return "";
   }

   netnode::socket & script_interface::netnode()
   {
      return *((netnode::socket *) NULL);
   }

   string script_interface::this_url(const char * pszKey, var var)
   {
      return System.url().set_key(this_url(), pszKey, var);
   }

   void script_interface::array_unshift(gen::property & varArray, const var varElement)
   {
      array_unshift(varArray.get_value(), varElement);
   }

   bool      script_interface::mid_fs_read             (const char * pszFolder, const char * pszName)
   {
      string strUser;
      __int64 iFolder;
      if(!low_folder(strUser, iFolder, pszFolder))
         return false;
      return low_fs_read(strUser, iFolder, pszName);
   }

   bool      script_interface::fs_add_user_file        (const char * pszFolder, const char * hash, __int64 key, __int64 size, const char * mimetype, const char * extension, const char * pszName, bool bOverwrite)
   {
      string strUser;
      __int64 iFolder;
      if(!low_folder(strUser, iFolder, pszFolder))
         return false;
      return low_fs_add_user_file(strUser, iFolder, hash, key, size, mimetype, extension, pszName, bOverwrite);
   }

   __int64      script_interface::fs_add_user_dir         (const char * pszFolder, const char * pszName)
   {
      string strUser;
      __int64 iFolder;
      if(!low_folder(strUser, iFolder, pszFolder))
         return false;
      return low_fs_add_user_dir(strUser, iFolder, pszName);
   }

   void      script_interface::fs_ls_dir               (const char * pszFolder, int64_array & ia, stringa & stra)
   {
      string strUser;
      __int64 iFolder;
      if(!low_folder(strUser, iFolder, pszFolder))
         return;
      return low_fs_ls_dir(strUser, iFolder, ia, stra);
   }

   void      script_interface::fs_ls_file              (const char * pszFolder, stringa & straHash, int64_array & iaKey, int64_array & iaSize, stringa & straMime, stringa & straExt, stringa & straName)
   {
      string strUser;
      __int64 iFolder;
      if(!low_folder(strUser, iFolder, pszFolder))
         return;
      return low_fs_ls_file(strUser, iFolder, straHash, iaKey, iaSize, straMime, straExt, straName);
   }


   bool      script_interface::fs_read                 (const char * pszPath)
   {
      string strPath(pszPath);
      strsize iFind = strPath.reverse_find('/');
      if(iFind < 0)
         return false;
      return mid_fs_read(strPath.Left(iFind), strPath.Mid(iFind + 1));
   }


   bool      script_interface::low_folder_lazy_file(string & strUser, __int64 & iFolder , string & strFile, const char * pszPath)
   {
      string strPath(pszPath);
      strsize iFind = strPath.reverse_find('/');
      if(iFind < 0)
         return false;
      strFile = strPath.Mid(iFind + 1);
      if(strFile.is_empty())
         return false;
      if(iFind >= 2 && strPath.get_length() >= iFind + 1 && strPath.Mid(iFind - 2, 3) == "://")
         return low_folder(strUser, iFolder, strPath.Left(iFind + 1));
      else
         return low_folder(strUser, iFolder, strPath.Left(iFind));
   }

   gen::international::locale_style & script_interface::localestyle()
   {
      gen::international::locale_style * plocalestyle = get_session_value("locale_style").ca2 < gen::international::locale_style >();
      if(plocalestyle == NULL)
      {
         plocalestyle = new gen::international::locale_style(get_app());
         set_session_value("locale_style", plocalestyle);
      }
      return *plocalestyle;
   }


} // namespace dynamic_source

