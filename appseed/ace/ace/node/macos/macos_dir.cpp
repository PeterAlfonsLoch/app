#include "framework.h"
#include "macos.h"



namespace macos
{


   dir::dir(::ace::application *   papp) :
      ::object(papp),
      ::file::dir::system(papp)
   {


   }



    ::file::listing & dir::root_ones(::file::listing & listing,::ace::application * papp)
    {
        
        listing.add("/");
        
        listing.m_straTitle.add("File System");
        
        return listing;
        
    }
    
    
    
    
    
    ::file::listing & dir::ls(::ace::application * papp,::file::listing & listing)
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
           
           ::file::patha  straPath;
           
           ::dir::ls(straPath, listing.m_path);
            
//            file_find file_find;
            
  //          bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != FALSE;
           
           for(auto & strPath : straPath)
           {

              bool bDir = is(strPath, papp);
              
              if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
              {
                 
                 if(!bDir && !matches_wildcard_criteria(listing.os_pattern(), strPath.name()))
                    continue;

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
            
           ::file::patha  straPath;
           
           ::dir::ls(straPath, listing.m_path);
           
           //            file_find file_find;
           
           //          bool bWorking = file_find.FindFile(listing.m_path / listing.os_pattern()) != FALSE;
           
           for(auto & strPath : straPath)
           {
              
              bool bDir = is(strPath, papp);
              
              if((listing.m_bDir && bDir) || (listing.m_bFile && !bDir))
              {
                 
                 if(!bDir && !matches_wildcard_criteria(listing.os_pattern(), strPath.name()))
                    continue;
                 
                 listing.add(strPath);
                 
                 listing.last().m_iDir = bDir ? 1 : 0;
                 
              }
              
           }

            
        }
        
        return listing;
        
    }

    
//    void dir::ls_pattern(::ace::application *   papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, int64_array * piaSize)
//   {
//
//      if(::file::dir::system::is(lpcsz, papp)) // if base class "already" "says" it is a dir, let it handle it: may be not a operational system dir, e.g., zip or compressed directory...
//      {
//
//         return ::file::dir::system::ls_pattern(papp, lpcsz, pszPattern, pstraPath, pstraTitle, pbaIsDir, piaSize);
//
//      }
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(!matches_wildcard_criteria(pszPattern, strName))
//            continue;
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add(strPath);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//         bool bIsDir = false;
//
//         if(pbaIsDir != NULL || piaSize != NULL)
//         {
//
//            bIsDir = ::dir::is(strPath);
//
//         }
//
//         if(pbaIsDir != NULL)
//         {
//
//            pbaIsDir->add(bIsDir);
//
//         }
//
//         if(piaSize != NULL)
//         {
//
//            if(bIsDir)
//            {
//
//               piaSize->add(0);
//
//            }
//            else
//            {
//
//               piaSize->add(file_length_dup(strPath));
//
//            }
//
//         }
//
//      }
//
//   }
//
//   void dir::rls(::ace::application *   papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, e_extract eextract)
//   {
//      rls_pattern(papp, lpcsz, "*.*", pstraPath, pstraTitle, pstraRelative, NULL, NULL, eextract);
//   }
//
//   void dir::rls_pattern(::ace::application *   papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, int64_array * piaSize, e_extract eextract)
//   {
//
//      stringa straDir;
//
//      ::dir::ls_dir(straDir, lpcsz);
//
//      for(int32_t i = 0; i < straDir.get_count(); i++)
//      {
//
//         string strDir = straDir[i];
//
//         if(strDir == lpcsz)
//            continue;
//
//         index iStart = 0;
//
//         if(pstraRelative != NULL)
//         {
//            iStart = pstraRelative->get_size();
//         }
//
//         rls_pattern(papp, strDir, pszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);
//
//         if(pstraRelative != NULL)
//         {
//
//            for(index i = iStart; i < pstraRelative->get_size(); i++)
//            {
//
//               pstraRelative->element_at(i) = System.dir().path(System.file().name_(strDir), pstraRelative->element_at(i));
//
//            }
//
//         }
//
//      }
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(!matches_wildcard_criteria(pszPattern, strName))
//            continue;
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add(strPath);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//         bool bIsDir = false;
//
//         if(pbaIsDir != NULL || piaSize != NULL)
//         {
//
//            bIsDir = ::dir::is(strPath);
//
//         }
//
//         if(pbaIsDir != NULL)
//         {
//
//            pbaIsDir->add(bIsDir);
//
//         }
//
//         if(piaSize != NULL)
//         {
//
//            if(bIsDir)
//            {
//
//               piaSize->add(0);
//
//            }
//            else
//            {
//
//               piaSize->add(file_length_dup(strPath));
//
//            }
//
//         }
//
//      }
//
//   }
//
//   void dir::rls_dir(::ace::application *   papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
//   {
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(!System.dir().is(strPath, papp))
//            continue;
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add((const char *) stra[i]);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//         if(pstraRelative != NULL)
//         {
//
//            pstraRelative->add(strName);
//
//         }
//
//         index iStart = 0;
//
//         if(pstraRelative != NULL)
//         {
//
//            iStart = pstraRelative->get_size();
//
//         }
//
//         rls_dir(papp, strPath, pstraPath, pstraTitle, pstraRelative);
//
//         if(pstraRelative != NULL)
//         {
//
//            for(index i = iStart; i < pstraRelative->get_size(); i++)
//            {
//
//               pstraRelative->element_at(i) = System.dir().path(strPath, pstraRelative->element_at(i));
//
//            }
//
//         }
//
//      }
//
//   }
//
//
//   void dir::ls_dir(::ace::application *   papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
//   {
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(!System.dir().is(strPath, papp))
//            continue;
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add((const char *) stra[i]);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//      }
//
//   }
//
//   void dir::ls_file(::ace::application *   papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
//   {
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(System.dir().is(strPath, papp))
//            continue;
//
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add((const char *) stra[i]);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//      }
//
//   }
//
//   void dir::ls(::ace::application *   papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, int64_array * piaSize)
//   {
//
//      stringa stra;
//
//      ::dir::ls(stra, lpcsz);
//
//      string strDir(lpcsz);
//
//      if(!::str::ends(strDir, "/"))
//      {
//
//         strDir += "/";
//
//      }
//
//
//      for(int32_t i = 0; i < stra.get_count(); i++)
//      {
//
//         string strPath = stra[i];
//
//         string strName = strPath;
//
//         if(!::str::begins_eat(strName, strDir))
//            continue;
//
//         if(pstraPath != NULL)
//         {
//
//            pstraPath->add((const char *) stra[i]);
//
//         }
//
//         if(pstraTitle != NULL)
//         {
//
//            pstraTitle->add(strName);
//
//         }
//
//
//         bool bIsDir = false;
//
//         if(pbaIsDir != NULL || piaSize != NULL)
//         {
//
//            bIsDir = System.dir().is(strPath, papp);
//
//         }
//
//         if(pbaIsDir != NULL)
//         {
//
//            pbaIsDir->add(bIsDir);
//
//         }
//
//         if(piaSize != NULL)
//         {
//
//            if(bIsDir)
//            {
//
//               piaSize->add(0);
//
//            }
//            else
//            {
//
//               piaSize->add(file_length_dup(strPath));
//
//            }
//
//         }
//
//
//      }
//
//   }

   bool dir::is(const ::file::path & lpcszPath, ::ace::application * papp)
   {

      bool bIsDir;

      DWORD dwLastError;

      if(m_isdirmap.lookup(lpcszPath, bIsDir, dwLastError))
      {

         if(!bIsDir)
         {

            SetLastError(dwLastError);

         }

         return bIsDir;

      }


      if(::file::dir::system::is(lpcszPath, papp))
         return true;


      string strPath(lpcszPath);
      if(strPath.get_length() >= MAX_PATH)
      {
         if(::str::begins(strPath, "\\\\"))
         {
            strPath = "\\\\?\\UNC" + strPath.Mid(1);
         }
         else
         {
            strPath = "\\\\?\\" + strPath;
         }
      }

      bIsDir = ::dir::is(strPath);

      m_isdirmap.set(lpcszPath, bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;
   }

//   bool dir::is(const string & strPath, ::ace::application *   papp)
//   {
//
//      if(::file::dir::system::is(strPath, papp))
//         return true;
//
//      bool bIsDir;
//
//      DWORD dwLastError;
//
//      if(m_isdirmap.lookup(strPath, bIsDir, dwLastError))
//      {
//
//         if(!bIsDir)
//         {
//
//            SetLastError(dwLastError);
//
//         }
//
//         return bIsDir;
//
//      }
//
//
//      wstring wstrPath;
//
//      //strsize iLen = ::str::international::utf8_to_unicode_count(strPath);
//      //wstrPath.alloc(iLen + 32);
//      wstrPath = ::str::international::utf8_to_unicode(strPath);
//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, L"\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }
//
//      bIsDir = ::dir::is(::str::international::unicode_to_utf8(wstrPath));
//
//      m_isdirmap.set(strPath, bIsDir, bIsDir ? 0 : ::GetLastError());
//
//      return bIsDir;
//   }

   bool dir::name_is(const ::file::path & str, ::ace::application *   papp)
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

      DWORD dwLastError;

      if(m_isdirmap.lookup(str, bIsDir, dwLastError, (int32_t) iLast))
         return bIsDir;


      if(papp->m_bZipIsDir && iLast >= 3  && !strnicmp_dup(&((const char *) str)[iLast - 3], ".zip", 4))
      {
         m_isdirmap.set(str.Left(iLast + 1), true, 0);
         return true;
      }

      wstring wstrPath;

      //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);

      //wstrPath.alloc(iLen + 32);

      wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);

      //OutputDebugStringW(wstrPath);

//      if(wstrPath.get_length() >= MAX_PATH)
//      {
//         if(::str::begins(wstrPath, unitext("\\\\"))
//         {
//            ::str::begin(wstrPath, L"\\\\?\\UNC");
//         }
//         else
//         {
//            ::str::begin(wstrPath, L"\\\\?\\");
//         }
//      }

      bIsDir = ::dir::is(::str::international::unicode_to_utf8(wstrPath));

      m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;
   }


   bool dir::mk(const ::file::path & lpcsz, ::ace::application *   papp)
   {

      if(is(lpcsz, papp))
         return true;

      ::file::patha stra;
      
      lpcsz.ascendants_path(stra);
      
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         
         if(!is(stra[i], papp))
         {

            if(!::dir::mk(stra[i]))
            {
               
               DWORD dwError = ::GetLastError();
               
               if(dwError == ERROR_ALREADY_EXISTS)
               {
                  
                  string str;
                  str = "\\\\?\\" + stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     App(papp).file().del(str);
                  }
                  catch(...)
                  {
                  }
                  str = stra[i];
                  str.trim_right("\\/");
                  try
                  {
                     App(papp).file().del(str);
                  }
                  catch(...)
                  {
                  }
                  //if(::CreateDirectory(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), NULL))
                  if(::dir::mk("\\\\?\\" + stra[i]))
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
//               FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, (LPTSTR) &pszError, 8, NULL);
                              FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, (LPTSTR) &pszError, 8, NULL);

               //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
               // xxx               ::LocalFree(pszError);
               //m_isdirmap.set(stra[i], false);
            }
            else
            {
               m_isdirmap.set(stra[i], true, 0);
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

//   bool dir::rm(::ace::application *   papp, const ::file::path & psz, bool bRecursive)
//   {
//      if(bRecursive)
//      {
//         stringa straPath;
//         stringa straTitle;
//         ls(papp, psz, &straPath, &straTitle);
//         for(int32_t i = 0; i < straPath.get_count(); i++)
//         {
//            if(is(straPath[i], papp))
//            {
//               rm(papp, path(psz, straTitle[i]), true);
//            }
//            else
//            {
//               ::unlink(straPath[i]);
//            }
//         }
//      }
//      return ::rmdir(psz) != FALSE;
//   }
//
//
//   string dir::name(const char * path1)
//   {
//      const char * psz = path1 + strlen(path1) - 1;
//      while(psz >= path1)
//      {
//         if(*psz != '\\' && *psz != '/' && *psz != ':')
//            break;
//         psz--;
//      }
//      while(psz >= path1)
//      {
//         if(*psz == '\\' || *psz == '/' || *psz == ':')
//            break;
//         psz--;
//      }
//      if(psz >= path1) // strChar == "\\" || strChar == "/"
//      {
//         const char * pszEnd = psz;
//         /*while(psz >= path1)
//          {
//          if(*psz != '\\' && *psz != '/' && *psz != ':')
//          break;
//          psz--;
//          }*/
//         return string(path1, pszEnd - path1 + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//   string dir::name(const string & str)
//   {
//
//      strsize iLast = str.get_length() - 1;
//
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//            break;
//         iLast--;
//      }
//      while(iLast >= 0)
//      {
//         if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//            break;
//         iLast--;
//      }
//      if(iLast >= 0)
//      {
//         while(iLast >= 0)
//         {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//               break;
//            iLast--;
//         }
//         return str.Left(iLast + 1);
//      }
//      else
//      {
//         return "";
//      }
//   }
//
//
//   class ::file::path & dir::path()
//   {
//      return m_path;
//   }



   ::file::path dir::trash_that_is_not_trash(const ::file::path & psz)
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




//   string dir::usersystemappdata(::ace::application *   papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(papp);
//      return path(appdata(lpcszPrefix), lpcsz, lpcsz2);
//   }
//
//   string dir::userappdata(::ace::application *   papp, const char * lpcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "appdata"), lpcsz, lpcsz2);
//   }
//
//   string dir::userdata(::ace::application *   papp, const char * lpcsz, const char * lpcsz2)
//   {
//      return path(userfolder(papp, "data"), lpcsz, lpcsz2);
//   }

//   ::file::path dir::userfolder(::ace::application * papp)
//   {
//      
//      return App(papp).dir().userfolder();
//
//   }


   ::file::path dir::default_os_user_path_prefix(::ace::application *   papp)
   {
      
      return ::getlogin();
      
   }
   

//   string dir::default_userappdata(::ace::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "appdata"), pszRelativePath);
//   }
//
//   string dir::default_userdata(::ace::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//      return path(default_userfolder(papp, lpcszPrefix, lpcszLogin, "data"), pszRelativePath);
//   }
//
//   string dir::default_userfolder(::ace::application *   papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
//   {
//
//      return userfolder(papp, pszRelativePath);
//
//      /*      UNREFERENCED_PARAMETER(papp);
//       string str;
//       SHGetSpecialFolderPath(
//       NULL,
//       str,
//       CSIDL_APPDATA,
//       FALSE);
//       return path(path(str, "ca2\\user", lpcszPrefix), lpcszLogin, pszRelativePath);*/
//   }
//
//   string dir::userquicklaunch(::ace::application *   papp, const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(papp);
//      string str;
//      /*SHGetSpecialFolderPath(
//       NULL,
//       str,
//       CSIDL_APPDATA,
//       FALSE);*/
//      str = path(getenv("HOME"), "Microsoft\\Internet Explorer\\Quick Launch");
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   string dir::userprograms(::ace::application *   papp, const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      UNREFERENCED_PARAMETER(papp);
//      string str;
//      /*      SHGetSpecialFolderPath(
//       NULL,
//       str,
//       CSIDL_PROGRAMS,
//       FALSE);*/
//
//      str = "/usr/bin";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }
//
//   string dir::commonprograms(const char * lpcszRelativePath, const char * lpcsz2)
//   {
//      string str;
//      /*      SHGetSpecialFolderPath(
//       NULL,
//       str,
//       CSIDL_COMMON_PROGRAMS,
//       FALSE);*/
//      str = "/usr/share/";
//      return path(str, lpcszRelativePath, lpcsz2);
//   }

//   bool dir::is_inside_time(const char * pszPath, ::ace::application *   papp)
//   {
//      return is_inside(time(), pszPath, papp);
//   }
//
//   bool dir::is_inside(const char * pszDir, const char * pszPath, ::ace::application *   papp)
//   {
//      return ::str::begins_ci(pszDir, pszPath);
//   }
//
   bool dir::has_subdir(::ace::application *   papp, const ::file::path & pszDir)
   {
      ::file::listing stra(papp);
      stra.ls_dir(pszDir);
      return stra.get_size() > 0;

   }
   
    
    
    
    
//    bool dir::is(const ::file::path & lpcszPath, ::ace::application * papp)
//    {
//        
//        if(::file::dir::system::is(lpcszPath, papp))
//            return true;
//        
//        string strPath(lpcszPath);
//        
//        if(strPath.get_length() >= MAX_PATH)
//        {
//            
//            if(::str::begins(strPath,astr.strDoubleBackSlash))
//            {
//                
//                strPath = "\\\\?\\UNC" + strPath.Mid(1);
//                
//            }
//            else
//            {
//                
//                strPath = "\\\\?\\" + strPath;
//                
//            }
//            
//        }
//        
//        DWORD dwAttrib;
//        
//        dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(strPath));
//        
//        bool bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//        
//        m_isdirmap.set(lpcszPath, bIsDir, bIsDir ? 0 : ::GetLastError());
//        
//        return bIsDir;
//        
//    }
   
    
    //bool dir::is(const ::file::path & strPath, ::ace::application * papp)
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
    
//    bool dir::name_is(const ::file::path & str, ::ace::application * papp)
//    {
//        //OutputDebugString(str);
//        strsize iLast = str.get_length() - 1;
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                break;
//            iLast--;
//        }
//        while(iLast >= 0)
//        {
//            if(str.m_pszData[iLast] == '\\' || str.m_pszData[iLast] == '/' || str.m_pszData[iLast] == ':')
//                break;
//            iLast--;
//        }
//        if(iLast >= 0)
//        {
//            while(iLast >= 0)
//            {
//                if(str.m_pszData[iLast] != '\\' && str.m_pszData[iLast] != '/' && str.m_pszData[iLast] != ':')
//                {
//                    iLast++;
//                    break;
//                }
//                iLast--;
//            }
//        }
//        else
//        {
//            return true; // assume empty string is root_ones directory
//        }
//        
//        
//        bool bIsDir;
//        
//        
//        uint32_t uiLastError;
//        
//        if(m_isdirmap.lookup(str, bIsDir, uiLastError, (int32_t) iLast))
//        {
//            if(!bIsDir)
//            {
//                ::SetLastError(uiLastError);
//            }
//            return bIsDir;
//        }
//        
//        
//        if(::get_thread() != NULL && ::get_thread()->m_bZipIsDir && iLast >= 3 && !strnicmp_dup(&((const char *)str)[iLast - 3],".zip",4))
//        {
//            m_isdirmap.set(str.Left(iLast + 1), true, 0);
//            return true;
//        }
//        
//        
//        
//        
//        wstring wstrPath;
//        
//        //strsize iLen = ::str::international::utf8_to_unicode_count(str, iLast + 1);
//        
//        //wstrPath.alloc(iLen + 32);
//        
//        wstrPath = ::str::international::utf8_to_unicode(str, iLast + 1);
//        
//        //OutputDebugStringW(wstrPath);
//        
//        if(wstrPath.get_length() >= MAX_PATH)
//        {
//            if(::str::begins(wstrPath, L"\\\\"))
//            {
//                ::str::begin(wstrPath, L"\\\\?\\UNC");
//            }
//            else
//            {
//                ::str::begin(wstrPath, L"\\\\?\\");
//            }
//        }
//        DWORD dwAttrib;
//        dwAttrib = GetFileAttributesW(wstrPath);
//        /*if(dwAttrib == INVALID_FILE_ATTRIBUTES)
//         {
//         dwAttrib = GetFileAttributes(strPath);
//         }*/
//        
//        bIsDir = (dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
//        
//        m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());
//        
//        return bIsDir;
//    }
   
    
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
    
    
    ::file::path dir::time_square(::ace::application * papp,const string & strPrefix,const string & strSuffix)
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
   
    
//    bool dir::mk(const ::file::path & lpcsz,::ace::application * papp)
//    {
//        
//        if(is(lpcsz, papp))
//            return true;
//        
//        ::file::patha stra;
//        lpcsz.ascendants_path(stra);
//        for(int32_t i = 0; i < stra.get_size(); i++)
//        {
//            
//            string strDir = stra[i];
//            
//            if(!is(strDir, papp))
//            {
//                
//                if(::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + strDir), NULL))
//                {
//                    
//                    m_isdirmap.set(strDir, true, 0);
//                    
//                }
//                else
//                {
//                    
//                    DWORD dwError = ::GetLastError();
//                    
//                    if (dwError == ERROR_ALREADY_EXISTS)
//                    {
//                        
//                        if (::dir::is(strDir))
//                        {
//                            m_isdirmap.set(strDir, true, 0);
//                        }
//                        else
//                        {
//                            string str;
//                            str = "\\\\?\\" + strDir;
//                            str.trim_right("\\/");
//                            try
//                            {
//                                Application.file().del(str);
//                            }
//                            catch (...)
//                            {
//                            }
//                            str = stra[i];
//                            str.trim_right("\\/");
//                            try
//                            {
//                                Application.file().del(str);
//                            }
//                            catch (...)
//                            {
//                            }
//                            if (::CreateDirectoryW(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), NULL))
//                            {
//                                m_isdirmap.set(stra[i], true, 0);
//                                goto try1;
//                            }
//                            else
//                            {
//                                dwError = ::GetLastError();
//                            }
//                        }
//                        char * pszError;
//                        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, (LPTSTR)&pszError, 8, NULL);
//                        
//                        //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
//                        ::LocalFree(pszError);
//                        //m_isdirmap.set(stra[i], false);
//                    }
//                }
//            try1:
//                
//                if(!is(stra[i], papp))
//                {
//                    return false;
//                }
//                
//            }
//        }
//        return true;
//    }
   
    bool dir::rm(::ace::application * papp, const ::file::path & psz, bool bRecursive)
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
                    ::unlink(path);
                }
            }
        }
       return ::rmdir(psz) == 0;
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
//    ::file::path get_known_folder(REFKNOWNFOLDERID kfid)
//    {
//        ::file::path str;
//        PWSTR pszPath = NULL;
//        HANDLE hToken = NULL;
//        ::OpenProcessToken(::GetCurrentProcess(),TOKEN_QUERY | TOKEN_IMPERSONATE | TOKEN_DUPLICATE,&hToken);
//        HRESULT hr = SHGetKnownFolderPath(kfid,0,hToken,&pszPath);
//        if(SUCCEEDED(hr))
//        {
//            str = pszPath;
//            // The calling application is responsible for calling CoTaskMemFree
//            // to free this resource after use.
//            CoTaskMemFree(pszPath);
//        }
//        else
//        {
//        }
//        return str;
//    }
   

   bool dir::initialize()
   {
        
      update_module_path();
        
      string strCa2Module = ca2module();
        
      m_strCa2 = strCa2Module;
        
//#if !defined(CUBE) && !defined(VSNORD)
        
      m_strCa2 -= 2;
      
      ::str::ends_eat_ci(m_strCa2, ".app");
        
//#endif
      ::file::path pathHome;
      
      pathHome = ::file::path(getenv("HOME"));
      
      ::file::path str;
      
      if(pathHome.is_empty())
      {
         
         pathHome = "~/Library/Application Support";
         
         pathHome /= ".default_user";
         
         str =  pathHome / "ca2";
         
      }
      else
      {
      
         str =  pathHome / "Library/Application Support" / "ca2";
         
      }
 
      string strRelative;
      
      strRelative = element();
      //index iFind = strRelative.find(':');
      //if(iFind >= 0)
      {
         // strsize iFind1 = strRelative.reverse_find("\\", iFind);
         //strsize iFind2 = strRelative.reverse_find("/", iFind);
         //strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
          
         //strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
      }

      m_strCa2AppData = str / strRelative / "appdata";
      
      m_strCommonAppData = str / strRelative / "commonappdata";
      
      m_pathUser = str / strRelative / "user";
      
      xml::document doc(get_app());
          
      string strPath = appdata() / "configuration\\directory.xml";
          
      string strDocument = Application.file().as_string(strPath);
          
      if(doc.load(strDocument))
      {
             
          if(doc.get_root()->get_name() == "directory_configuration")
          {
                
             m_strTimeFolder = doc.get_root()->get_child_value("time");
                
             m_strNetSeedFolder = doc.get_root()->get_child_value("netseed");
                
          }
          
       }
          
       if(m_strTimeFolder.is_empty())
          m_strTimeFolder = appdata() / "time";
          
       if(m_strNetSeedFolder.is_empty())
          m_strNetSeedFolder = element() / "net/netseed";
          
       mk(m_strTimeFolder, get_app());
          
       if(!is(m_strTimeFolder, get_app()))
          return false;
          
       string strTime = m_strTimeFolder / "time";
          
       mk(strTime, get_app());
          
       if(!is(strTime, get_app()))
          return false;
      
      str = "/usr/bin";

      m_strPrograms = str;
   
      str = "/usr/share/";
      
      m_strCommonPrograms = str;
   
      return true;
      
   }
   
   
//    ::file::path dir::trash_that_is_not_trash(const ::file::path & psz)
//    {
//        if(psz.is_empty())
//            return "";
//        
//        if(psz[1] == ':')
//        {
//            string strDir = name(psz);
//            string str;
//            str = strDir.Left(2);
//            str += "\\trash_that_is_not_trash\\";
//            string strFormat;
//            ::datetime::time time;
//            time = ::datetime::time::get_current_time();
//            strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
//            str += strFormat;
//            if(strDir.m_pszData[2] == '\\')
//            {
//                str += strDir.Mid(3);
//            }
//            else
//            {
//                str += strDir.Mid(2);
//            }
//            return str;
//        }
//        
//        return "";
//    }
   
    ::file::path dir::appdata()
    {
        
        return m_strCa2AppData;
        
    }
    
    
    ::file::path dir::commonappdata_root()
    {
        
        return m_strCommonAppData;
        
    }
   ::file::path dir::commonappdata()
   {
      
      return m_strCommonAppData;
      
   }

    
    ::file::path dir::usersystemappdata(::ace::application * papp,const char * lpcszPrefix)
    {
        UNREFERENCED_PARAMETER(papp);
        return appdata() / lpcszPrefix;
    }
    
    ::file::path dir::userappdata(::ace::application * papp)
    {
        return userfolder(papp) / "appdata";
    }
    
    ::file::path dir::userdata(::ace::application * papp)
    {
        return userfolder(papp) / "data";
    }
    
//    ::file::path dir::userfolder(::ace::application * papp)
//    {
//        
//
//        
//    }
//    
//    ::file::path dir::default_os_user_path_prefix(::ace::application * papp)
//    {
//        UNREFERENCED_PARAMETER(papp);
//        unichar buf[MAX_PATH];
//        ULONG ulSize = sizeof(buf) / sizeof(unichar);
//        if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
//        {
//            if(!::GetUserNameW(buf, &ulSize))
//            {
//                memset(buf, 0, sizeof(buf));
//            }
//        }
//        return ::str::international::unicode_to_utf8(buf);
//    }
   
    ::file::path dir::default_userappdata(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
    {
        return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata" ;
    }
    
    ::file::path dir::default_userdata(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
    {
        return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
    }
    
    ::file::path dir::default_userfolder(::ace::application * papp,const string & lpcszPrefix,const string & lpcszLogin)
    {
        
        return userfolder(papp);
        
    }
    
    ::file::path dir::userquicklaunch(::ace::application * papp)
    {
        
        UNREFERENCED_PARAMETER(papp);
        
        return m_strAppData / "Microsoft\\Internet Explorer\\Quick Launch";
        
    }
    
    
    ::file::path dir::userprograms(::ace::application * papp)
    {
        
        UNREFERENCED_PARAMETER(papp);
        
        return m_strPrograms;
        
    }
    
    
    ::file::path dir::commonprograms()
    {
        
        return m_strCommonPrograms;
        
    }
    
    
    bool dir::is_inside_time(const ::file::path & pszPath, ::ace::application * papp)
    {
        
        return is_inside(time(), pszPath, papp);
        
    }
    
    
    bool dir::is_inside(const ::file::path & pszDir, const ::file::path & pszPath, ::ace::application * papp)
    {
        
        return ::str::begins_ci(pszDir, pszPath);
        
    }
    
    
//    bool dir::has_subdir(::ace::application * papp, const ::file::path & pszDir)
//    {
//        
//        file_find file_find;
//        
//        bool bWorking;
//        
//        bWorking = file_find.FindFile(pszDir / "*.*");
//        
//        while(bWorking)
//        {
//            
//            bWorking = file_find.FindNextFileA();
//            
//            if(file_find.IsDirectory() && !file_find.IsDots())
//            {
//                
//                return true;
//                
//            }
//            
//        }
//        
//        return false;
//        
//    }
   
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
    
    
    


} // namespace macos
