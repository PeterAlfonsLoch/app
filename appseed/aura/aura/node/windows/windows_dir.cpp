#include "framework.h"
#include "windows.h"



namespace windows
{


   dir::dir(::aura::application * papp) :
      ::object(papp),
      ::file::dir::system(papp)
   {
      

   }

   inline bool myspace(char ch)
   {
      return ch == ' ' ||
             ch == '\t' ||
             ch == '\r' ||
             ch == '\n';
   }



   //string dir::path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl)
   //{

   //   bool bEmptyRelative = iLenRelative == 0 || pszRelative == NULL || *pszRelative == '\0';
   //   bool bEmpty2 = iLen2 == 0 || psz2 == NULL || *psz2 == '\0';

   //   if(bEmptyRelative && bEmpty2)
   //      return pszFolder;

   //   string strPath;
   //   LPSTR lpsz;

   //   if(bEmptyRelative)
   //   {
   //      pszRelative = psz2;
   //      iLenRelative = iLen2;
   //   }

   //   while((pszFolder[iLenFolder - 1] == '\\' || pszFolder[iLenFolder - 1] == '/') && iLenFolder > 0)
   //   {
   //      if(bUrl)
   //      {
   //         if((iLenFolder - 2) >= 0 && (pszFolder[iLenFolder - 2] == '\\' || pszFolder[iLenFolder - 2] == '/' || pszFolder[iLenFolder - 2] == ':'))
   //         {
   //            if(pszFolder[iLenFolder - 2] == ':')
   //            {
   //               break;
   //            }
   //            else
   //            {
   //               if((iLenFolder - 3) >= 0 && (pszFolder[iLenFolder - 3] == ':'))
   //               {
   //                  iLenFolder--;
   //                  break;
   //               }
   //            }
   //         }
   //         else
   //         {
   //            iLenFolder--;
   //         }
   //      }
   //      else
   //      {
   //         iLenFolder--;
   //      }
   //   }

   //   while(*pszRelative != '\0' && (*pszRelative == '\\' || *pszRelative == '/') && iLenRelative > 0)
   //   {
   //      pszRelative++;
   //      iLenRelative--;
   //   }

   //   if(bEmptyRelative || bEmpty2)
   //   {
   //      lpsz = strPath.GetBufferSetLength(iLenFolder + 1 + iLenRelative);
   //      strncpy(lpsz, pszFolder, iLenFolder);
   //      if(strnicmp(&lpsz[iLenFolder - 5], ".zip:", 5) == 0)
   //      {
   //         iLenFolder--;
   //      }
   //      else
   //      {
   //         lpsz[iLenFolder] = '/';
   //      }
   //      strncpy(&lpsz[iLenFolder + 1], pszRelative, iLenRelative);
   //      lpsz[iLenFolder + 1 + iLenRelative] = '\0';
   //      {
   //         if(bUrl)
   //         {
   //            while(*lpsz++ != '\0')
   //               if(*lpsz == '\\') *lpsz = '/';
   //         }
   //         else
   //         {
   //            while(*lpsz++ != '\0')
   //               if(*lpsz == '/') *lpsz = '\\';
   //         }
   //      }
   //      strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative);
   //      return strPath;
   //   }

   //   while((pszRelative[iLenRelative - 1] == '\\' || pszRelative[iLenRelative - 1] == '/') && iLenRelative > 0)
   //   {
   //      iLenRelative--;
   //   }

   //   while(*psz2 != '\0' && (*psz2 == '\\' || *psz2 == '/') && iLen2 > 0)
   //   {
   //      psz2++;
   //      iLen2--;
   //   }

   //   lpsz = strPath.GetBufferSetLength(iLenFolder + 1 + iLenRelative + 1 + iLen2);
   //   strncpy(lpsz, pszFolder, iLenFolder);
   //   lpsz[iLenFolder] = '/';
   //   strncpy(&lpsz[iLenFolder + 1], pszRelative, iLenRelative);
   //   lpsz[iLenFolder + 1 + iLenRelative] = '/';
   //   strncpy(&lpsz[iLenFolder + 1 + iLenRelative + 1], psz2, iLen2);
   //   lpsz[iLenFolder + 1 + iLenRelative + 1 + iLen2] = '\0';
   //   {
   //      if(bUrl)
   //      {
   //         while(*lpsz++ != '\0')
   //            if(*lpsz == '\\') *lpsz = '/';
   //      }
   //      else
   //      {
   //         while(*lpsz++ != '\0')
   //            if(*lpsz == '/') *lpsz = '\\';
   //      }
   //   }
   //   strPath.ReleaseBuffer(iLenFolder + 1 + iLenRelative + 1 + iLen2);
   //   return strPath;
   //}

   //string dir::relpath(const string & lpcszSource,const string & lpcszRelative)
   //{
   //   const char * pszRequest;
   //   if(::url::is_url(lpcszSource,&pszRequest))
   //   {
   //      if(::str::begins(lpcszRelative,astr.strSlash))
   //      {
   //         return path((const char *)string(lpcszSource,pszRequest - lpcszSource),lpcszRelative);
   //      }
   //      else if(*pszRequest == '\0' || ::str::ends(lpcszSource,"/"))
   //      {
   //         return path(lpcszSource,lpcszRelative);
   //      }
   //      else
   //      {
   //         return path((const char *)name(lpcszSource),lpcszRelative);
   //      }
   //   }
   //   else
   //   {
   //      if(::str::ends(lpcszSource,"\\") || ::str::ends(lpcszSource,"/"))
   //      {
   //         return path(lpcszSource,lpcszRelative);
   //      }
   //      else
   //      {
   //         return path((const char *)name(lpcszSource),lpcszRelative);
   //      }
   //   }
   //}


   //string dir::relpath(const string & lpcszSource, const string & lpcszRelative, const string & psz2)
   //{
   //   const char * pszRequest;
   //   if(::url::is_url(lpcszSource, &pszRequest))
   //   {
   //      if(::str::begins(lpcszRelative,astr.strSlash))
   //      {
   //         return path((const char *) string(lpcszSource, pszRequest - lpcszSource), lpcszRelative, psz2);
   //      }
   //      else if(*pszRequest == '\0' || ::str::ends(lpcszSource, "/"))
   //      {
   //         return path(lpcszSource, lpcszRelative, psz2);
   //      }
   //      else
   //      {
   //         return path((const char *) name(lpcszSource), lpcszRelative, psz2);
   //      }
   //   }
   //   else
   //   {
   //      if(::str::ends(lpcszSource, "\\") || ::str::ends(lpcszSource, "/"))
   //      {
   //         return path(lpcszSource, lpcszRelative, psz2);
   //      }
   //      else
   //      {
   //         return path((const char *) name(lpcszSource), lpcszRelative, psz2);
   //      }
   //   }
   //}

   ::file::listing & dir::root_ones(::file::listing & listing,::aura::application * papp)
   {
      DWORD dwSize = ::GetLogicalDriveStrings(0, NULL);
      LPTSTR lpszAlloc = (LPTSTR) malloc(dwSize + 1);
      LPTSTR lpsz = lpszAlloc;
      dwSize = ::GetLogicalDriveStrings(dwSize + 1, lpsz);

      string str;
      while(*lpsz)
      {
         str.Empty();
         while(*lpsz)
         {
            str += *lpsz;  
            lpsz++;
         }
         ::file::path & path = listing.add(::file::path(str));
         path.m_iDir = 1;
         str.trim(":/\\");
         listing.m_straTitle.add("Drive " + str);
         lpsz++;
      }

      free(lpszAlloc);

      return listing;

   }



   

   ::file::listing & dir::ls(::aura::application * papp,::file::listing & listing)
   {


      if(listing.m_bRecursive)
      {


         index iStart = listing.get_size();


         {

            RESTORE(listing.m_path);

            RESTORE(listing.m_eextract);

            if(::file::dir::system::ls(papp,listing).succeeded())
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

         file_find file_find;

         bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != FALSE;

         if(bWorking)
         {

            while(bWorking)
            {

               bWorking = file_find.FindNextFileA() != FALSE;

               if(!file_find.IsDots() && file_find.GetFilePath() != listing.m_path)
               {

                  if((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
                  {

                     listing.add(file_find.GetFilePath());

                     listing.last().m_iSize = file_find.get_length();

                     listing.last().m_iDir = file_find.IsDirectory() != FALSE;

                  }

               }

            }

         }
         else
         {

            listing.m_cres = cres(failure);

         }

         for(index i = iStart; i < listing.get_size(); i++)
         {

            listing[i].m_iRelative = listing.m_path.get_length() + 1;

         }

      }
      else
      {

         if(::file::dir::system::ls(papp,listing).succeeded())
         {

            return listing;

         }

         file_find file_find;

         bool bWorking;

         bWorking = file_find.FindFile(listing.m_path / listing.os_pattern());

         if(!bWorking)
         {

            return listing;

         }

         while(bWorking)
         {

            bWorking = file_find.FindNextFileA();

            if(!file_find.IsDots())
            {

               if((listing.m_bDir && file_find.IsDirectory()) || (listing.m_bFile && !file_find.IsDirectory()))
               {

                  listing.add(file_find.GetFilePath());

                  listing.last().m_iSize = file_find.get_length();

                  listing.last().m_iDir = file_find.IsDirectory() != FALSE;

               }

            }

         }

      }

      return listing;

   }


   bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp)
   {
      
      if(::file::dir::system::is(lpcszPath, papp))
         return true;

      string strPath(lpcszPath);

      if(strPath.get_length() >= MAX_PATH)
      {

         if(::str::begins(strPath,astr.strDoubleBackSlash))
         {

            strPath = "\\\\?\\UNC" + strPath.Mid(1);

         }
         else
         {

            strPath = "\\\\?\\" + strPath;

         }

      }

      DWORD dwAttrib;

      dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(strPath));
      
      bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
      
      m_isdirmap.set(lpcszPath, bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;

   }

      
   //bool dir::is(const ::file::path & strPath, ::aura::application * papp)
   //{
   //   
   //   if(::file::dir::system::is(strPath, papp))
   //      return true;

   //   bool bIsDir;

   //   uint32_t uiLastError;

   //   if(m_isdirmap.lookup(strPath, bIsDir, uiLastError))
   //   {
   //      if(!bIsDir)
   //      {
   //         ::SetLastError(uiLastError);
   //      }
   //      return bIsDir;
   //   }

   //   wstring wstrPath;
   //   
   //   //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
   //   //wstrPath.alloc(iLen + 32);
   //   wstrPath = ::str::international::utf8_to_unicode(strPath);
   //   if(wstrPath.get_length() >= MAX_PATH)
   //   {
   //      if(::str::begins(wstrPath, L"\\\\"))
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\UNC");
   //      }
   //      else
   //      {
   //         ::str::begin(wstrPath, L"\\\\?\\");
   //      }
   //   }
   //   DWORD dwAttrib;
   //   dwAttrib = GetFileAttributesW(wstrPath);
   //   /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
   //   {
   //      dwAttrib = GetFileAttributes(strPath);
   //   }*/
   //   
   //   bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
   //   
   //   m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::GetLastError());

   //   return bIsDir;
   //}

   bool dir::name_is(const ::file::path & str, ::aura::application * papp)
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


      uint32_t uiLastError;

      if(m_isdirmap.lookup(str, bIsDir, uiLastError, (int32_t) iLast))
      {
         if(!bIsDir)
         {
            ::SetLastError(uiLastError);
         }
         return bIsDir;
      }


      if(::get_thread() != NULL && ::get_thread()->m_bZipIsDir && iLast >= 3 && !strnicmp_dup(&((const char *)str)[iLast - 3],".zip",4))
      {
         m_isdirmap.set(str.Left(iLast + 1), true, 0);
         return true;
      }
      



      wstring wstrPath;
      
      //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);

      //wstrPath.alloc(iLen + 32);

      wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);

      //OutputDebugStringW(wstrPath);

      if(wstrPath.get_length() >= MAX_PATH)
      {
         if(::str::begins(wstrPath, L"\\\\"))
         {
            ::str::begin(wstrPath, L"\\\\?\\UNC");
         }
         else
         {
            ::str::begin(wstrPath, L"\\\\?\\");
         }
      }
      DWORD dwAttrib;
      dwAttrib = GetFileAttributesW(wstrPath);
      /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
         dwAttrib = GetFileAttributes(strPath);
      }*/
      
      bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
      
      m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;
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
      return stage() / "basis";
   }

   ::file::path dir::netseed()
   {
      return m_strNetSeedFolder;
   }

   // stage in ca2os spalib
   ::file::path dir::element()
   {
      
      single_lock sl(&m_mutex, true);

      return m_strCa2;

   }


   ::file::path dir::module()
   {

      return m_pathModule;

   }


   ::file::path dir::ca2module()
   {
      
      return m_pathCa2Module;

   }


   ::file::path dir::time_square(::aura::application * papp,const string & strPrefix,const string & strSuffix)
   {

      UNREFERENCED_PARAMETER(papp);
      UNREFERENCED_PARAMETER(strPrefix);
      UNREFERENCED_PARAMETER(strSuffix);
      return time() / "time";

   }


   ::file::path dir::time_log()
   {

      return appdata() / "log";

   }

   bool dir::mk(const ::file::path & lpcsz,::aura::application * papp)
   {

      if(is(lpcsz, papp))
         return true;

      ::file::patha stra;
      lpcsz.ascendants_path(stra);
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         
         string strDir = stra[i];

         if(!is(strDir, papp))
         {
            
            if(::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + strDir), NULL))
            {

               m_isdirmap.set(strDir, true, 0);

            }
            else
            {

               DWORD dwError = ::GetLastError();

               if (dwError == ERROR_ALREADY_EXISTS)
               {

                  if (::dir::is(strDir))
                  {
                     m_isdirmap.set(strDir, true, 0);
                  }
                  else
                  {
                     string str;
                     str = "\\\\?\\" + strDir;
                     str.trim_right("\\/");
                     try
                     {
                        Application.file().del(str);
                     }
                     catch (...)
                     {
                     }
                     str = stra[i];
                     str.trim_right("\\/");
                     try
                     {
                        Application.file().del(str);
                     }
                     catch (...)
                     {
                     }
                     if (::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), NULL))
                     {
                        m_isdirmap.set(stra[i], true, 0);
                        goto try1;
                     }
                     else
                     {
                        dwError = ::GetLastError();
                     }
                  }
                  char * pszError;
                  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, (LPTSTR)&pszError, 8, NULL);

                  //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
                  ::LocalFree(pszError);
                  //m_isdirmap.set(stra[i], false);
               }
            }
            try1:
            
            if(!is(stra[i], papp))
            {
               return false;
            }
            
         }
      }
      return true;
   }

   bool dir::rm(::aura::application * papp, const ::file::path & psz, bool bRecursive)
   {
      if(bRecursive)
      {
         ::file::listing patha(papp);
         patha.ls(psz);         
         for(auto & path : patha)
         {
            if(is(path, papp))
            {
               rm(papp, psz / path.name(), true);
            }
            else
            {
               ::DeleteFile(path);
            }
         }
      }
      return RemoveDirectory(psz) != FALSE;
   }


   //::file::path dir::name(const ::file::path & path1)
   //{
   //   const char * psz = path1 + strlen(path1) - 1;
   //   while(psz >= path1)
   //   {
   //      if(*psz != '\\' && *psz != '/' && *psz != ':')
   //         break;
   //      psz--;
   //   }
   //   while(psz >= path1)
   //   {
   //      if(*psz == '\\' || *psz == '/' || *psz == ':')
   //         break;
   //      psz--;
   //   }
   //   if(psz >= path1) // strChar == "\\" || strChar == "/"
   //   {
   //      const char * pszEnd = psz;
   //      /*while(psz >= path1)
   //      {
   //         if(*psz != '\\' && *psz != '/' && *psz != ':')
   //            break;
   //         psz--;
   //      }*/
   //      return string(path1, pszEnd - path1 + 1);
   //   }
   //   else
   //   {
   //      return "";
   //   }
   //}

   ::file::path dir::name(const ::file::path & str)
   {
      
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
               break;
            iLast--;
         }
         return str.Left(iLast + 1);
      }
      else
      {
         return "";
      }
   }


   //class ::file::file_path & dir::path()
   //{
   //   return m_path;
   //}

   /*!
   * Print a known folder.
   */
   ::file::path get_known_folder(REFKNOWNFOLDERID kfid)
   {
      ::file::path str;
      PWSTR pszPath = NULL;
      HANDLE hToken = NULL;
      ::OpenProcessToken(::GetCurrentProcess(),TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE,&hToken);
         HRESULT hr = SHGetKnownFolderPath(kfid,0,hToken,&pszPath);
      if(SUCCEEDED(hr))
      {
         str = pszPath;
         // The calling application is responsible for calling CoTaskMemFree 
         // to free this resource after use.
         CoTaskMemFree(pszPath);
      }
      else
      {
      }
      return str;
   }

   bool dir::initialize()
   {

      update_module_path();

      string strCa2Module = ca2module();

      m_strCa2 = strCa2Module;

      m_strCa2 -= 2;

      SHGetSpecialFolderPath(
         NULL,
         m_strCommonAppData,
         CSIDL_COMMON_APPDATA,
         FALSE);
      SHGetSpecialFolderPath(
         NULL,
         m_pathProfile,
         CSIDL_PROFILE,
         FALSE);
      //SHGetSpecialFolderPath(
      //   NULL,
      //   m_strAppData,
      //   CSIDL_APPDATA,
      //   FALSE);
      m_strAppData = get_known_folder(FOLDERID_RoamingAppData);

      SHGetSpecialFolderPath(
         NULL,
         m_strPrograms,
         CSIDL_PROGRAMS,
         FALSE);
      SHGetSpecialFolderPath(
         NULL,
         m_strCommonPrograms,
         CSIDL_COMMON_PROGRAMS,
         FALSE);

      {

         string strRelative;
         strRelative = element();
         index iFind = strRelative.find(':');
         if(iFind >= 0)
         {
            strsize iFind1 = strRelative.reverse_find("\\",iFind);
            strsize iFind2 = strRelative.reverse_find("/",iFind);
            strsize iStart = MAX(iFind1 + 1,iFind2 + 1);
            strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);
         }

         m_strCa2AppData = m_strAppData / "ca2" / strRelative;

         m_strCa2AppData /= System.install_get_platform();

         m_strCa2AppData /= System.install_get_version();

      }



      xml::document doc(get_app());

      doc.load(System.file().as_string(appdata() / "configuration/directory.xml",get_app()));

      xxdebug_box("win_dir::initialize (configuration)","win_dir::initialize",0);
      if(doc.get_root()->get_name() == "directory_configuration")
      {

         m_strTimeFolder = doc.get_root()->get_child_value("time");

         m_strNetSeedFolder = doc.get_root()->get_child_value("netseed");

      }
      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = appdata() / "time";

      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = element() / "net/netseed";

      mk(m_strTimeFolder,get_app());
      xxdebug_box("win_dir::initialize (m_strTimeFolder)","win_dir::initialize",0);

      if(!is(m_strTimeFolder,get_app()))
         return false;

      mk(m_strTimeFolder / "time",get_app());
      xxdebug_box("win_dir::initialize","win_dir::initialize",0);


      string str;
      str = System.dir().profile();


      ::file::path strRelative;
      strRelative = System.dir().element();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
         strsize iFind1 = strRelative.reverse_find("\\",iFind);
         strsize iFind2 = strRelative.reverse_find("/",iFind);
         strsize iStart = MAX(iFind1 + 1,iFind2 + 1);
         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);
      }

//      ::file::path strUserFolderShift;

//      if(App(papp).directrix()->m_varTopicQuery.has_property("user_folder_relative_path"))
//      {
//         strUserFolderShift = strRelative / App(papp).directrix()->m_varTopicQuery["user_folder_relative_path"].get_string();
//      }
//      else
//      {
  //       strUserFolderShift = strRelative;
//      }

      m_pathUser = ::file::path(str) / "ca2" / strRelative;



      return true;

   }

   ::file::path dir::trash_that_is_not_trash(const ::file::path & psz)
   {
      if(psz.is_empty())
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
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
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

      return m_strCa2AppData;

   }

   
   ::file::path dir::commonappdata_root()
   {

      return m_strCommonAppData;

   }


   ::file::path dir::usersystemappdata(::aura::application * papp,const char * lpcszPrefix)
   {
      UNREFERENCED_PARAMETER(papp);
      return appdata() / lpcszPrefix;
   }

   ::file::path dir::userappdata(::aura::application * papp)
   {
      return userfolder(papp) / "appdata";
   }

   ::file::path dir::userdata(::aura::application * papp)
   {
      return userfolder(papp) / "data";
   }


   ::file::path dir::default_os_user_path_prefix(::aura::application * papp)
   {
      UNREFERENCED_PARAMETER(papp);
      unichar buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(unichar);
      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }
      return ::str::international::unicode_to_utf8(buf);
   }

   ::file::path dir::default_userappdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
   {
      return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata" ;
   }

   ::file::path dir::default_userdata(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
   {
      return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
   }

   ::file::path dir::default_userfolder(::aura::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
   {

      return userfolder(papp);

   }

   ::file::path dir::userquicklaunch(::aura::application * papp)
   {
      
      UNREFERENCED_PARAMETER(papp);

      return m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";

   }

   
   ::file::path dir::userprograms(::aura::application * papp)
   {
      
      UNREFERENCED_PARAMETER(papp);
      
      return m_strPrograms;
      
   }

   
   ::file::path dir::commonprograms()
   {
      
      return m_strCommonPrograms;
      
   }


   bool dir::is_inside_time(const ::file::path & pszPath, ::aura::application * papp)
   {

      return is_inside(time(), pszPath, papp);

   }


   bool dir::is_inside(const ::file::path & pszDir, const ::file::path & pszPath, ::aura::application * papp)
   {
      
      return ::str::begins_ci(pszDir, pszPath);

   }

   
   bool dir::has_subdir(::aura::application * papp, const ::file::path & pszDir)
   {
      
      file_find file_find;

      bool bWorking;

      bWorking = file_find.FindFile(pszDir / "*.*");

      while(bWorking)
      {
         
         bWorking = file_find.FindNextFileA();

         if(file_find.IsDirectory() && !file_find.IsDots())
         {

            return true;

         }

      }

      return false;

   }

   //bool file::GetStatus(const char * lpszFileName,::file::file_status& rStatus)
   //{
   //   // attempt to fully qualify path first
   //   wstring wstrFullName;
   //   wstring wstrFileName;
   //   wstrFileName = ::str::international::utf8_to_unicode(lpszFileName);
   //   if(!vfxFullPath(wstrFullName,wstrFileName))
   //   {
   //      rStatus.m_strFullName.Empty();
   //      return FALSE;
   //   }
   //   ::str::international::unicode_to_utf8(rStatus.m_strFullName,wstrFullName);

   //   WIN32_FIND_DATA findFileData;
   //   HANDLE hFind = FindFirstFile((LPTSTR)lpszFileName,&findFileData);
   //   if(hFind == INVALID_HANDLE_VALUE)
   //      return FALSE;
   //   VERIFY(FindClose(hFind));

   //   // strip attribute of NORMAL bit, our API doesn't have a "normal" bit.
   //   rStatus.m_attribute = (BYTE)(findFileData.dwFileAttributes & ~FILE_ATTRIBUTE_NORMAL);

   //   // get just the low DWORD of the file size
   //   ASSERT(findFileData.nFileSizeHigh == 0);
   //   rStatus.m_size = (LONG)findFileData.nFileSizeLow;

   //   // convert times as appropriate
   //   rStatus.m_ctime = ::datetime::time(findFileData.ftCreationTime);
   //   rStatus.m_atime = ::datetime::time(findFileData.ftLastAccessTime);
   //   rStatus.m_mtime = ::datetime::time(findFileData.ftLastWriteTime);

   //   if(rStatus.m_ctime.get_time() == 0)
   //      rStatus.m_ctime = rStatus.m_mtime;

   //   if(rStatus.m_atime.get_time() == 0)
   //      rStatus.m_atime = rStatus.m_mtime;

   //   return TRUE;
   //}




} // namespace windows
























































