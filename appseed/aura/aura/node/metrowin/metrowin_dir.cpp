#include "framework.h"
#include "metrowin.h"

namespace metrowin
{


   dir::dir(::aura::application *  papp):
      ::object(papp),
      ::file::dir::system(papp)
   {

      string strCa2Module = ca2module();

      m_strCa2 = strCa2Module;

      m_strCa2 -= 2;

   }

   inline bool myspace(char ch)
   {
      return ch == ' ' ||
         ch == '\t' ||
         ch == '\r' ||
         ch == '\n';
   }


   ::file::listing & dir::root_ones(::file::listing & listing,::aura::application *  papp)
   {

      listing.add(::file::path(Windows::Storage::KnownFolders::DocumentsLibrary->Path));

      listing.m_straTitle.add("Documents");

      return listing;

   }


   


   ::file::listing & dir::ls(::aura::application *  papp, ::file::listing & listing)
   {

      if(listing.m_bRecursive)
      {


         index iStart = listing.get_size();


         {

            RESTORE(listing.m_path);

            RESTORE(listing.m_eextract);

            if(::file::dir::system::ls(papp,listing))
            {

               listing.m_cres = cres(failure);

               return listing;

            }


            ::file::listing dira(papp);

            dira.ls_dir(listing.m_path);

            for(int32_t i = 0; i < dira.get_count(); i++)
            {

               ::file::path dir = dira[i];

               if(dir == listing.m_path)
                  continue;

               listing.m_path = dir;

               if(listing.m_eextract != extract_all)
               {

                  listing.m_eextract = extract_none;

               }

               listing.ls();

            }

         }

         stringa stra;

         ::dir::ls(stra,listing.m_path);

         for(int i = 0; i < stra.get_count(); i++)
         {

            ::file::path strPath = stra[i];

            string strName = strPath.name();

            if(!matches_wildcard_criteria(listing.m_strPattern,strName))
               continue;

            bool bDir = is(strPath, papp);

            if((listing.m_bFile && !bDir) || (listing.m_bDir && bDir))
            {

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_path.get_length() + 1;

         }

      }
      else
      {

         if(::file::dir::system::ls(papp,listing))
         {

            return listing;

         }

         stringa stra;

         ::dir::ls(stra,listing.m_path);

         for(int i = 0; i < stra.get_count(); i++)
         {
            
            ::file::path strPath = stra[i];

            string strName = strPath.name();

            if(!matches_wildcard_criteria(listing.m_strPattern,strName))
               continue;

            bool bDir = is(strPath, papp);

            if((listing.m_bFile && !bDir) || (listing.m_bDir && bDir))
            {

               listing.add(strPath);

               listing.last().m_iDir = bDir ? 1 : 0;

            }

         }

      }

      return listing;

   }






   bool dir::is(const ::file::path & lpcszPath,::aura::application *  papp)
   {

      bool bIsDir;

      uint32_t dwLastError;

      if(m_isdirmap.lookup(lpcszPath,bIsDir,dwLastError))
      {
         if(!bIsDir)
         {
            ::SetLastError(dwLastError);
         }
         return bIsDir;
      }

      bool bIs;

      if(::file::dir::system::is_or_definitively_not(bIs,lpcszPath,papp))
         return bIs;


      string strPath(lpcszPath);
      if(strPath.get_length() >= MAX_PATH)
      {
         if(::str::begins(strPath,"\\\\"))
         {
            strPath = "\\\\?\\UNC" + strPath.Mid(1);
         }
         else
         {
            strPath = "\\\\?\\" + strPath;
         }
      }
      /*
      uint32_t dwAttrib;
      dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(strPath));
      /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
      dwAttrib = GetFileAttributes(lpcszPath);
      }*/

      //bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      bIsDir = ::dir::is(strPath);

      m_isdirmap.set(lpcszPath,bIsDir,::GetLastError());

      return bIsDir;
   }

   bool dir::name_is(const ::file::path & str,::aura::application *  papp)
   {
      //OutputDebugString(str);
      strsize iLast = str.get_length() - 1;
      while(iLast >= 0)
      {
         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
            break;
         iLast--;
      }
      while(iLast >= 0)
      {
         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
            break;
         iLast--;
      }
      if(iLast >= 0)
      {
         while(iLast >= 0)
         {
            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
            {
               iLast++;
               break;
            }
            iLast--;
         }
      }
      else
      {
         return true; // assume empty string is root_ones directory
      }


      bool bIsDir;
      uint32_t dwLastError;


      if(m_isdirmap.lookup(str,bIsDir,dwLastError,(int)iLast))
         return bIsDir;


      if(papp->m_bZipIsDir && iLast >= 3 && !strnicmp_dup(&((const char *)str)[iLast - 3],".zip",4))
      {
         m_isdirmap.set(str.Left(iLast + 1),true,0);
         return true;
      }

      strsize iFind = ::str::find_ci(".zip:",str);

      //if(papp->m_bZipIsDir && iFind >= 0 && iFind < iLast)
      //{
      //   bool bHasSubFolder;
      //   uint32_t dwLastError;
      //   if(m_isdirmap.lookup(str,bHasSubFolder,dwLastError))
      //      return bHasSubFolder;
      //   bHasSubFolder = m_pziputil->HasSubFolder(papp,str);
      //   m_isdirmap.set(str.Left(iLast + 1),bHasSubFolder,::GetLastError());
      //   return bHasSubFolder;
      //}


      wstring wstrPath;

      //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);

      //wstrPath.alloc(iLen + 32);

      wstrPath = ::str::international::utf8_to_unicode(str,iLast + 1);

      //OutputDebugStringW(wstrPath);

      if(wstrPath.get_length() >= MAX_PATH)
      {
         if(::str::begins(wstrPath,L"\\\\"))
         {
            ::str::begin(wstrPath,L"\\\\?\\UNC");
         }
         else
         {
            ::str::begin(wstrPath,L"\\\\?\\");
         }
      }
      //      uint32_t dwAttrib;
      ///      dwAttrib = GetFileAttributesW(wstrPath);
      /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
      dwAttrib = GetFileAttributes(strPath);
      }*/

      //   bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);

      bIsDir = ::dir::is(::str::international::unicode_to_utf8(wstrPath));

      m_isdirmap.set(str.Left(iLast + 1),bIsDir,::GetLastError());

      return bIsDir;
   }

   ::file::path dir::votagus()
   {
      return System.get_ca2_module_folder();
   }

   ::file::path dir::time()
   {
      return m_strTimeFolder;
   }

   ::file::path dir::stage()
   {
      return element() / "stage";
   }

   ::file::path dir::stageapp()
   {
      return stage()/ "basis";
   }

   ::file::path dir::netseed()
   {
      return m_strNetSeedFolder;
   }

   // stage in ccvotagus spalib
   ::file::path dir::element()
   {

      single_lock sl(&m_mutex,true);

      return m_strCa2;

   }

   ::file::path dir::module()
   {
      return System.get_module_folder();
   }

   ::file::path dir::ca2module()
   {
      return System.get_ca2_module_folder();
   }


   ::file::path dir::time_square()
   {
      return time() / "time";
   }

   
   ::file::path dir::time_log()
   {
      return appdata() / "log";
   }

   
   bool dir::mk(const ::file::path & lpcsz,::aura::application *  papp)
   {

      if(is(lpcsz,papp))
         return true;

      ::file::patha stra;
      
      lpcsz.ascendants_path(stra);

      for(int i = 0; i < stra.get_size(); i++)
      {
         if(!is(stra[i],papp) && ::GetLastError() != ERROR_ACCESS_DENIED)
         {

            if(!::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]),NULL))
            {
               uint32_t dwError = ::GetLastError();
               if(dwError == ERROR_ALREADY_EXISTS)
               {
                  string str;
                  str = "\\\\?\\" + stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     Application.file().del(str);
                  }
                  catch(...)
                  {
                  }
                  str = stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     Application.file().del(str);
                  }
                  catch(...)
                  {
                  }
                  if(::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]),NULL))
                  {
                     m_isdirmap.set(stra[i],true,0);
                     goto try1;
                  }
                  else
                  {
                     dwError = ::GetLastError();
                  }
               }
               string strError = get_system_error_message(dwError);

               APPTRACE("dir::mk CreateDirectoryW last error(%d)=%s",dwError,strError);
               //m_isdirmap.set(stra[i], false);
            }
            else
            {
               m_isdirmap.set(stra[i],true,0);
            }
         try1:

            if(!is(stra[i],papp))
            {
               return false;
            }

         }
      }
      return true;
   }

   
   bool dir::rm(::aura::application *  papp,const ::file::path & psz,bool bRecursive)
   {

      if(bRecursive)
      {

         ::file::listing straPath(papp);

         straPath.ls(psz);
         
         for(int i = 0; i < straPath.get_count(); i++)
         {

            if(App(papp).dir().is(straPath[i]))
            {

               rm(papp,path(psz,straTitle[i]),true);

            }
            else
            {

               ::DeleteFileW(::str::international::utf8_to_unicode(straPath[i]));

            }

         }

      }

      return RemoveDirectoryW(::str::international::utf8_to_unicode(psz)) != FALSE;

   }




   bool dir::initialize()
   {

      xml::document doc(get_app());

      doc.load(Application.file().as_string(appdata("configuration\\directory.xml")));

      if(doc.get_root()->get_name() == "directory_configuration")
      {

         m_strTimeFolder = doc.get_root()->get_child_value("time");

         m_strNetSeedFolder = doc.get_root()->get_child_value("netseed");

      }
      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = appdata("time");

      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = element("net/netseed");

      mk(m_strTimeFolder,get_app());

      if(!is(m_strTimeFolder,get_app()))
         return false;

      mk(path(m_strTimeFolder,"time"),get_app());

      return true;

   }

   ::file::path dir::trash_that_is_not_trash(const char * psz)
   {
      if(psz == NULL)
         return "";

      if(psz[1] == ':')
      {
         string strDir = name(psz);
         string str;
         str = strDir.Left(2);
         str += "\\trash_that_is_not_trash\\";
         string strFormat;
         ::datetime::time time;
         time = ::datetime::time::get_current_time();
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\",time.GetYear(),time.GetMonth(),time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
         str += strFormat;
         if(strDir.m_pszData[2] == '\\')
         {
            str += strDir.Mid(3);
         }
         else
         {
            str += strDir.Mid(2);
         }
         return str;
      }

      return "";
   }

   ::file::path dir::appdata()
   {

      return path(::Windows::Storage::ApplicationData::Current->LocalFolder->Path,lpcsz,lpcsz2);

   }

   ::file::path dir::usersystemappdata(::aura::application *  papp,const char * lpcszPrefix,const char * lpcsz,const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(papp);
      return path(appdata(lpcszPrefix),lpcsz,lpcsz2);
   }

   ::file::path dir::userappdata(::aura::application *  papp,const char * lpcsz,const char * lpcsz2)
   {
      return path(userfolder(papp,"appdata"),lpcsz,lpcsz2);
   }

   ::file::path dir::userdata(::aura::application *  papp,const char * lpcsz,const char * lpcsz2)
   {
      return path(userfolder(papp,"data"),lpcsz,lpcsz2);
   }

   ::file::path dir::userfolder(::aura::application *  papp,const char * lpcsz,const char * lpcsz2)
   {
#ifdef WINDOWSEX
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_PROFILE,
         FALSE);


      string strRelative;
      strRelative = ca2();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
         strsize iFind1 = strRelative.reverse_find("\\",iFind);
         strsize iFind2 = strRelative.reverse_find("/",iFind);
         strsize iStart = MAX(iFind1 + 1,iFind2 + 1);
         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);
      }

      string strUserFolderShift;

      if(App(papp).directrix().m_varTopicQuery.has_property("user_folder_relative_path"))
      {
         strUserFolderShift = path(strRelative,App(papp).directrix().m_varTopicQuery["user_folder_relative_path"].get_string());
      }
      else
      {
         strUserFolderShift = strRelative;
      }

      return path(path(str,"ca2",strUserFolderShift),lpcsz,lpcsz2);

      //      return path(path(str, "ca2"), lpcsz);
      /*      if(&AppUser(papp) == NULL)
      {
      string str;
      SHGetSpecialFolderPath(
      NULL,
      str,
      CSIDL_PROFILE,
      FALSE);
      return path(path(str, "ca2\\_____default"), lpcsz);
      }
      else
      {
      return path(AppUser(papp).m_strPath, lpcsz, lpcsz2);
      }*/
#else

      string str = appdata();

      /*      string strRelative;
      strRelative = ca2();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
      strsize iFind1 = strRelative.reverse_find("\\", iFind);
      strsize iFind2 = strRelative.reverse_find("/", iFind);
      strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
      strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
      }*/

      string strUserFolderShift;

      if(App(papp).directrix()->m_varTopicQuery.has_property("user_folder_relative_path"))
      {
         strUserFolderShift = App(papp).directrix()->m_varTopicQuery["user_folder_relative_path"].get_string();
      }

      return path(path(str,"ca2",strUserFolderShift),lpcsz,lpcsz2);


#endif

   }

   ::file::path dir::default_os_user_path_prefix(::aura::application *  papp)
   {
      UNREFERENCED_PARAMETER(papp);
      //      wchar_t buf[MAX_PATH];
#ifdef WINDOWSEX
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(NameCanonical,buf,&ulSize))
      {
         if(!::GetUserNameW(buf,&ulSize))
         {
            memset(buf,0,sizeof(buf));
         }
      }
#else
      return "CurrentUser";
#endif
      //return ::str::international::unicode_to_utf8(buf);
   }

   ::file::path dir::default_userappdata(::aura::application *  papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath)
   {
      return path(default_userfolder(papp,lpcszPrefix,lpcszLogin,"appdata"),pszRelativePath);
   }

   ::file::path dir::default_userdata(::aura::application *  papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath)
   {
      return path(default_userfolder(papp,lpcszPrefix,lpcszLogin,"data"),pszRelativePath);
   }

   ::file::path dir::default_userfolder(::aura::application *  papp,const char * lpcszPrefix,const char * lpcszLogin,const char * pszRelativePath)
   {

      return userfolder(papp,pszRelativePath);

      /*      UNREFERENCED_PARAMETER(papp);
      string str;
      SHGetSpecialFolderPath(
      NULL,
      str,
      CSIDL_APPDATA,
      FALSE);
      return path(path(str, "ca2\\user", lpcszPrefix), lpcszLogin, pszRelativePath);*/
   }

   ::file::path dir::userquicklaunch(::aura::application *  papp,const char * lpcszRelativePath,const char * lpcsz2)
   {
      throw todo(get_app());
      //UNREFERENCED_PARAMETER(papp);
      //string str;
      //SHGetSpecialFolderPath(
      //   NULL,
      //   str,
      //   CSIDL_APPDATA,
      //   FALSE);
      //str = path(str, "Microsoft\\Internet Explorer\\Quick Launch");
      //return path(str, lpcszRelativePath, lpcsz2);
   }

   ::file::path dir::userprograms(::aura::application *  papp,const char * lpcszRelativePath,const char * lpcsz2)
   {
      throw todo(get_app());
      //UNREFERENCED_PARAMETER(papp);
      //string str;
      //SHGetSpecialFolderPath(
      //   NULL,
      //   str,
      //   CSIDL_PROGRAMS,
      //   FALSE);
      //return path(str, lpcszRelativePath, lpcsz2);
   }

   ::file::path dir::commonprograms(const char * lpcszRelativePath,const char * lpcsz2)
   {
      throw todo(get_app());
      //string str;
      //SHGetSpecialFolderPath(
      //   NULL,
      //   str,
      //   CSIDL_COMMON_PROGRAMS,
      //   FALSE);
      //return path(str, lpcszRelativePath, lpcsz2);
   }

   bool dir::is_inside_time(const char * pszPath,::aura::application *  papp)
   {
      return is_inside(time(),pszPath,papp);
   }

   bool dir::is_inside(const char * pszDir,const char * pszPath,::aura::application *  papp)
   {
      return ::str::begins_ci(pszDir,pszPath);
   }

   bool dir::has_subdir(::aura::application *  papp,const char * pszDir)
   {
      throw todo(get_app());

      /*      file_find filefind;
      bool bWorking;
      bWorking = filefind.FindFile(path(pszDir, "*.*"));
      while(bWorking)
      {
      bWorking = filefind.FindNextFileA();
      if(filefind.IsDirectory() && !filefind.IsDots())
      {
      return true;
      }
      }
      return false;*/
   }


   ::file::path dir::commonappdata()
   {

      return path(::Windows::Storage::ApplicationData::Current->LocalFolder->Path,"commonappdata");

   }


} // namespace metrowin
