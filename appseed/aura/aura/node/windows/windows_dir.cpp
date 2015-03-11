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

   void dir::root_ones(::file::patha & patha, stringa & straTitle, ::aura::application * papp)
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
         patha.add(::file::path(str));
         str.trim(":/\\");
         straTitle.add("Drive " + str);
         lpsz++;
      }

      free(lpszAlloc);
   }


   bool dir::ls_pattern(::aura::application * papp, const ::file::path & path, const string & pszPattern, ::file::patha * ppatha, ::file::patha * ppathaName, bool_array * pbaIsDir, int64_array * piaSize)
   {
      
      if(::file::dir::system::ls_pattern(papp, path, pszPattern, ppatha, ppathaName, pbaIsDir, piaSize))
      {

         return true;

      }

      file_find file_find;
      
      bool bWorking;
      
      bWorking = file_find.FindFile(path / pszPattern);

      if(!bWorking)
      {
         return false;

      }


      while(bWorking)
      {
         bWorking = file_find.FindNextFileA();
         if(!file_find.IsDots())
         {
            if(ppatha != NULL)
            {
               ppatha->add(file_find.GetFilePath());
            }
            if(ppathaName != NULL)
            {
               ppathaName->add(file_find.GetFileName());
            }
            if(pbaIsDir != NULL)
            {
               pbaIsDir->add(file_find.IsDirectory() != FALSE);
            }
            if(piaSize != NULL)
            {
               piaSize->add(file_find.get_length());
            }
         }
      }
      
      return true;

   }

   
   bool dir::rls(::aura::application * papp, const ::file::path & psz,::file::patha * ppatha,::file::patha * ppathaName,::file::patha * ppathaRelative,e_extract eextract)
   {

      if(::file::dir::system::rls(papp,psz,ppatha,ppathaName,ppathaRelative,eextract))
      {

         return true;

      }

      return rls_pattern(papp, psz, "*.*", ppatha, ppathaName, ppathaRelative, NULL, NULL, eextract);

   }


   bool dir::rls_pattern(::aura::application * papp, const ::file::path & path,const string & lpszPattern,::file::patha * ppatha,::file::patha * ppathaName,::file::patha * ppathaRelative,bool_array * pbaIsDir,int64_array * piaSize,e_extract eextract)
   {

      if(::file::dir::system::rls_pattern(papp,path,lpszPattern,ppatha,ppathaName,ppathaRelative, pbaIsDir, piaSize, eextract))
      {

         return true;

      }

      ::file::patha straDir;

      ls_dir(papp, path, &straDir);

      for(int32_t i = 0; i < straDir.get_count(); i++)
      {

         ::file::path strDir = straDir[i];

         if(strDir == path)
            continue;

         index iStart = 0;

         if(ppathaRelative != NULL)
         {
            iStart = ppathaRelative->get_size();
         }
         rls_pattern(papp, strDir, lpszPattern, ppatha, ppathaName, ppathaRelative, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);
         if(ppathaRelative != NULL)
         {
            for(index i = iStart; i < ppathaRelative->get_size(); i++)
            {
               ppathaRelative->element_at(i) = strDir * ppathaRelative->element_at(i);
            }
         }
      }

      file_find file_find;
      bool bWorking = file_find.FindFile(path /  lpszPattern) != FALSE;
      if(bWorking)
      {
         while(bWorking)
         {
            bWorking = file_find.FindNextFileA() != FALSE;
            if(!file_find.IsDots() && file_find.GetFilePath() != path)
            {
               if(ppatha != NULL)
               {
                  ppatha->add(file_find.GetFilePath());
               }
               if(ppathaName != NULL)
               {
                  ppathaName->add(file_find.GetFileName());
               }
               if(ppathaRelative != NULL)
               {
                  ppathaRelative->add(file_find.GetFileName());
               }
               if(pbaIsDir != NULL)
               {
                  pbaIsDir->add(file_find.IsDirectory() != FALSE);
               }
               if(piaSize != NULL)
               {
                  piaSize->add(file_find.get_length());
               }
               /*if(file_find.IsDirectory())
               {
                  int32_t iStart = 0;
                  if(ppathaRelative != NULL)
                  {
                     iStart = ppathaRelative->get_size();
                  }
                  rls_pattern(file_find.GetFilePath(), lpszPattern, ppatha, ppathaName, ppathaRelative, pbaIsDir, piaSize);
                  if(ppathaRelative != NULL)
                  {
                     for(int32_t i = iStart; i < ppathaRelative->get_size(); i++)
                     {
                        ppathaRelative->element_at(i) = System.dir().path(file_find.GetFileName(), ppathaRelative->element_at(i));
                     }
                  }
               }*/
            }
         }
         
         return true;

      }
      else
      {
         return ::file::dir::system::rls(papp, path, ppatha, ppathaName, ppathaRelative, eextract == extract_all ? extract_all : extract_none);
      }
   }


   bool dir::rls_dir(::aura::application * papp, const ::file::path & path,::file::patha * ppatha,::file::patha * ppathaName,::file::patha * ppathaRelative)
   {


      if(::file::dir::system::rls_dir(papp,path,ppatha,ppathaName,ppathaRelative))
      {

         return true;

      }

      file_find file_find;

      bool bWorking;

      bWorking = file_find.FindFile(path /"*.*");

      if(!bWorking)
      {

         return false;

      }

      while(bWorking)
      {
         bWorking = file_find.FindNextFileA();
         if(!file_find.IsDots() && file_find.IsDirectory())
         {
            if(ppatha != NULL)
            {
               ppatha->add(file_find.GetFilePath());
            }
            if(ppathaName != NULL)
            {
               ppathaName->add(file_find.GetFileName());
            }
            if(ppathaRelative != NULL)
            {
               ppathaRelative->add(file_find.GetFileName());
            }
            if(file_find.IsDirectory())
            {
               index iStart = 0;
               if(ppathaRelative != NULL)
               {
                  iStart = ppathaRelative->get_size();
               }
               rls_dir(papp, file_find.GetFilePath(), ppatha, ppathaName, ppathaRelative);
               if(ppathaRelative != NULL)
               {
                  for(index i = iStart; i < ppathaRelative->get_size(); i++)
                  {
                     ppathaRelative->element_at(i) = file_find.GetFileName() / ppathaRelative->element_at(i);
                  }
               }
            }
         }
      }

      return true;

   }

   bool dir::ls_dir(::aura::application * papp, const ::file::path & path,::file::patha * ppatha,::file::patha * ppathaName)
   {

      if(::file::dir::system::ls_dir(papp,path,ppatha,ppathaName))
      {

         return true;

      }
      
      file_find file_find;
      bool bWorking;
      bWorking = file_find.FindFile(path / "*.*");
      
      if(!bWorking)
      {
         
         return false;

      }

      while(bWorking)
      {
         bWorking = file_find.FindNextFileA();
         if(file_find.IsDirectory() && !file_find.IsDots())
         {
            if(ppatha != NULL)
            {
               ppatha->add(file_find.GetFilePath());
            }
            if(ppathaName != NULL)
            {
               ppathaName->add(file_find.GetFileName());
            }
         }
      }

      return true;

   }


   bool dir::ls_file(::aura::application * papp, const ::file::path & path,::file::patha * ppatha,::file::patha * ppathaName)
   {


      if(::file::dir::system::ls_pattern(papp,path,"*.*",ppatha,ppathaName))
      {

         return true;

      }

      file_find file_find;
      bool bWorking;
      bWorking = file_find.FindFile(path / "*.*");

      if(!bWorking)
      {

         return false;

      }

      while(bWorking)
      {
         bWorking = file_find.FindNextFileA();
         if(!file_find.IsDirectory() && !file_find.IsDots())
         {
            if(ppatha != NULL)
            {
               ppatha->add(file_find.GetFilePath());
            }
            if(ppathaName != NULL)
            {
               ppathaName->add(file_find.GetFileName());
            }
         }
      }

      return true;

   }


   bool dir::ls(::aura::application * papp, const ::file::path & path,::file::patha * ppatha,::file::patha * ppathaName,bool_array * pbaIsDir,int64_array * piaSize)
   {

      return ls_pattern(papp,path,"*.*",ppatha,ppathaName,pbaIsDir,piaSize);

   }


   bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp)
   {
      
      bool bIsDir;

      uint32_t uiLastError;

      if(m_isdirmap.lookup(lpcszPath, bIsDir, uiLastError))
      {
         if(!bIsDir)
         {
            ::SetLastError(uiLastError);
         }
         return bIsDir;
      }

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
      /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
      {
         dwAttrib = GetFileAttributes(lpcszPath);
      }*/
      
      bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
      
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
         ::file::patha patha;
         ::file::patha straTitle;
         ls(papp, psz, &patha, &straTitle);         
         for(int32_t i = 0; i < patha.get_count(); i++)
         {
            if(is(patha[i], papp))
            {
               rm(papp, psz / straTitle[i], true);
            }
            else
            {
               ::DeleteFile(patha[i]);
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
      

         string strCa2Module = ca2module();

         m_strCa2 = strCa2Module;

#ifndef CUBE

         m_strCa2 -= 2;

#endif

         SHGetSpecialFolderPath(
            NULL,
            m_strCommonAppData,
            CSIDL_COMMON_APPDATA,
            FALSE);
         SHGetSpecialFolderPath(
            NULL,
            m_strProfile,
            CSIDL_PROFILE,
            FALSE);
         SHGetSpecialFolderPath(
            NULL,
            m_strAppData,
            CSIDL_APPDATA,
            FALSE);
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

      xml::document doc(get_app());
      
      doc.load(System.file().as_string(appdata() / "configuration\\directory.xml",get_app()));
      
      xxdebug_box("win_dir::initialize (configuration)", "win_dir::initialize", 0);
      if(doc.get_root()->get_name() == "directory_configuration")
      {

         m_strTimeFolder = doc.get_root()->get_child_value("time"); 

         m_strNetSeedFolder = doc.get_root()->get_child_value("netseed"); 

      }
      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = appdata() /"time";

      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = element()/"net/netseed";

      mk(m_strTimeFolder, get_app());
      xxdebug_box("win_dir::initialize (m_strTimeFolder)", "win_dir::initialize", 0);

      if(!is(m_strTimeFolder, get_app()))
         return false;

      mk(m_strTimeFolder/ "time", get_app());
      xxdebug_box("win_dir::initialize", "win_dir::initialize", 0);
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
      string str;
      str = m_strAppData;

      string strRelative;
      strRelative = element();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
         strsize iFind1 = strRelative.reverse_find("\\", iFind);
         strsize iFind2 = strRelative.reverse_find("/", iFind);
         strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
      }
      
      return ::file::path(str) / "ca2";

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

   ::file::path dir::userfolder(::aura::application * papp)
   {

      string str;
      str = m_strProfile;


      ::file::path strRelative;
      strRelative = element();
      index iFind = strRelative.find(':');
      if(iFind >= 0)
      {
         strsize iFind1 = strRelative.reverse_find("\\", iFind);
         strsize iFind2 = strRelative.reverse_find("/", iFind);
         strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
      }

      ::file::path strUserFolderShift;

      if(App(papp).directrix()->m_varTopicQuery.has_property("user_folder_relative_path"))
      {
         strUserFolderShift = strRelative / App(papp).directrix()->m_varTopicQuery["user_folder_relative_path"].get_string();
      }
      else
      {
         strUserFolderShift = strRelative;
      }

      return ::file::path(str)/"ca2"/strUserFolderShift;

   }

   ::file::path dir::default_os_user_path_prefix(::aura::application * papp)
   {
      UNREFERENCED_PARAMETER(papp);
      wchar_t buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }
      return ::str::international::unicode_to_utf8(buf);
   }

   ::file::path dir::default_userappdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin)
   {
      return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata" ;
   }

   ::file::path dir::default_userdata(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin)
   {
      return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
   }

   ::file::path dir::default_userfolder(::aura::application * papp,const char * lpcszPrefix,const char * lpcszLogin)
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
























































