//#include "framework.h"
//#include "android.h"


//#include <unistd.h>


namespace android
{


   dir::dir(::aura::application * papp) :
      ::object(papp),
      ::file::dir::system(papp)
   {

      //string strCa2Module = ca2module();

      string strCacheDir = string(System.m_pandroidinitdata->m_pszCacheDir);

      m_strCa2 = strCacheDir;

      //m_strCa2 -=2;

   }

   inline bool myspace(char ch)
   {
      return ch == ' ' ||
             ch == '\t' ||
             ch == '\r' ||
             ch == '\n';
   }


   ::file::listing & dir::root_ones(::file::listing & listing, ::aura::application *  papp)
   {
      listing.add("/");
	  listing.m_straTitle.add("File System");
/*      DWORD dwSize = ::GetLogicalDriveStrings(0, NULL);
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
         stra.add(str);
         lpsz++;
      }

      free(lpszAlloc);*/
   }

   ::file::listing & dir::ls(::aura::application * papp, ::file::listing & listing)
   {

	   if (::file::dir::system::ls(papp, listing))
	   {

		   return listing;

	   }


	   if (listing.m_bRecursive)
	   {

		   index iStart = listing.get_count();

		   {

			   RESTORE(listing.m_path);

			   RESTORE(listing.m_eextract);

			   ::file::listing straDir(papp);

			   straDir.ls_dir(listing.m_path);

			   for (int32_t i = 0; i < straDir.get_count(); i++)
			   {

				   string strDir = straDir[i];

				   if (strDir == listing.m_path)
					   continue;

				   if (listing.m_bDir)
				   {

					   ::file::path & path = listing.add(::file::path(strDir));

					   path.m_iSize = 0;

					   path.m_iDir = 1;

				   }

				   listing.m_path = strDir;

				   listing.ls();


			   }

		   }

		   if (listing.m_bFile)
		   {

			   RESTORE(listing.m_bRecursive);

			   listing.m_bRecursive = false;

			   listing.ls_file(listing.m_path);

		   }

		   for (index i = iStart; i < listing.get_size(); i++)
		   {

			   listing[i].m_iRelative = listing.m_path.get_length() + 1;

		   }

	   }
	   else
	   {


		   ::file::patha stra;

		   ::dir::ls(stra, listing.m_path);

		   for (int32_t i = 0; i < stra.get_count(); i++)
		   {

			   ::file::path strPath = stra[i];

			   if (!::str::begins(strPath, listing.m_path))
				   continue;

			   bool bIsDir;

			   bIsDir = ::dir::is(strPath);

			   if (!bIsDir && listing.m_strPattern.has_char() && listing.m_strPattern != "*.*" && !matches_wildcard_criteria(listing.m_strPattern, strPath.name()))
				   continue;

			   if ((bIsDir && !listing.m_bDir) || (!bIsDir && !listing.m_bFile))
				   continue;

			   ::file::path & path = listing.add(strPath);

			   path.m_iDir = bIsDir ? 1 : 0;

			   if (bIsDir)
			   {

				   path.m_iSize = 0;

			   }
			   else
			   {

				   path.m_iSize = file_length_dup(strPath);

			   }

		   }

	   }

	   return listing;

   }


   //bool dir::rls(::aura::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, e_extract eextract)
   //{

   //   if(::file::dir::system::rls(papp,lpcsz,pstraPath,pstraTitle,pstraRelative,eextract))
   //   {

   //      return true;

   //   }

   //   return rls_pattern(papp, lpcsz, "*.*", pstraPath, pstraTitle, pstraRelative, NULL, NULL, eextract);

   //}


   //bool dir::rls_pattern(::aura::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, int64_array * piaSize, e_extract eextract)
   //{


   //   if(::file::dir::system::rls_pattern(papp,lpcsz,pszPattern,pstraPath,pstraTitle,pstraRelative,pbaIsDir,piaSize,eextract))
   //   {

   //      return true;

   //   }

   //   stringa straDir;

   //   ::dir::ls_dir(straDir, lpcsz);

   //   for(int32_t i = 0; i < straDir.get_count(); i++)
   //   {

   //      string strDir = straDir[i];

   //      if(strDir == lpcsz)
   //         continue;

   //      index iStart = 0;

   //      if(pstraRelative != NULL)
   //      {
   //         iStart = pstraRelative->get_size();
   //      }

   //      rls_pattern(papp, strDir, pszPattern, pstraPath, pstraTitle, pstraRelative, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);

   //      if(pstraRelative != NULL)
   //      {

   //         for(index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = System.dir().path(System.file().name_(strDir), pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }

   //   stringa stra;

   //   ::dir::ls(stra, lpcsz);

   //   for(int32_t i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!matches_wildcard_criteria(pszPattern, strName))
   //         continue;

   //      if(pstraPath != NULL)
   //      {

   //         pstraPath->add(strPath);

   //      }

   //      if(pstraTitle != NULL)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //      if(pstraRelative != NULL)
   //      {

   //         pstraRelative->add(strName);

   //      }

   //      bool bIsDir;

   //      if(pbaIsDir != NULL || piaSize != NULL)
   //      {

   //         bIsDir = ::dir::is(strPath);

   //      }

   //      if(pbaIsDir != NULL)
   //      {

   //         pbaIsDir->add(bIsDir);

   //      }

   //      if(piaSize != NULL)
   //      {

   //         if(bIsDir)
   //         {

   //            piaSize->add(0);

   //         }
   //         else
   //         {

   //            piaSize->add(file_length_dup(strPath));

   //         }

   //      }

   //   }

   //   return true;

   //}


   //bool dir::rls_dir(::aura::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
   //{

   //   if(::file::dir::system::rls_dir(papp,lpcsz,pstraPath,pstraTitle,pstraRelative))
   //   {

   //      return true;

   //   }

   //   stringa stra;

   //   ::dir::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(int32_t i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!System.dir().is(strPath, papp))
   //         continue;

   //      if(pstraPath != NULL)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != NULL)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //      if(pstraRelative != NULL)
   //      {

   //         pstraRelative->add(strName);

   //      }

   //      index iStart = 0;

   //      if(pstraRelative != NULL)
   //      {

   //         iStart = pstraRelative->get_size();

   //      }

   //      rls_dir(papp, strPath, pstraPath, pstraTitle, pstraRelative);

   //      if(pstraRelative != NULL)
   //      {

   //         for(index i = iStart; i < pstraRelative->get_size(); i++)
   //         {

   //            pstraRelative->element_at(i) = System.dir().path(strPath, pstraRelative->element_at(i));

   //         }

   //      }

   //   }

   //   return true;

   //}


   //bool dir::ls_dir(::aura::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   //{

   //   if(::file::dir::system::ls_dir(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   stringa stra;

   //   ::dir::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(int32_t i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(!System.dir().is(strPath, papp))
   //         continue;

   //      if(pstraPath != NULL)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != NULL)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //   }

   //   return true;

   //}


   //bool dir::ls_file(::aura::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
   //{

   //   if(::file::dir::system::ls_file(papp,lpcsz,pstraPath,pstraTitle))
   //   {

   //      return true;

   //   }

   //   stringa stra;

   //   ::dir::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(int32_t i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(System.dir().is(strPath, papp))
   //         continue;


   //      if(pstraPath != NULL)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != NULL)
   //      {

   //         pstraTitle->add(strName);

   //      }

   //   }

   //   return true;

   //}


   //bool dir::ls(::aura::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, int64_array * piaSize)
   //{


   //   if(::file::dir::system::ls(papp,lpcsz,pstraPath,pstraTitle,pbaIsDir,piaSize))
   //   {

   //      return true;

   //   }


   //   stringa stra;

   //   ::dir::ls(stra, lpcsz);

   //   string strDir(lpcsz);

   //   if(!::str::ends(strDir, "/"))
   //   {

   //      strDir += "/";

   //   }


   //   for(int32_t i = 0; i < stra.get_count(); i++)
   //   {

   //      string strPath = stra[i];

   //      string strName = strPath;

   //      if(!::str::begins_eat(strName, strDir))
   //         continue;

   //      if(pstraPath != NULL)
   //      {

   //         pstraPath->add((const char *) stra[i]);

   //      }

   //      if(pstraTitle != NULL)
   //      {

   //         pstraTitle->add(strName);

   //      }


   //      bool bIsDir;

   //      if(pbaIsDir != NULL || piaSize != NULL)
   //      {

   //         bIsDir = System.dir().is(strPath, papp);

   //      }

   //      if(pbaIsDir != NULL)
   //      {

   //         pbaIsDir->add(bIsDir);

   //      }

   //      if(piaSize != NULL)
   //      {

   //         if(bIsDir)
   //         {

   //            piaSize->add(0);

   //         }
   //         else
   //         {

   //            piaSize->add(file_length_dup(strPath));

   //         }

   //      }


   //   }

   //   return true;

   //}

   bool dir::is(const ::file::path & lpcszPath, ::aura::application * papp)
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

   //bool dir::is(const string & strPath, ::aura::application * papp)
   //{

   //   if(::file::dir::system::is(strPath, papp))
   //      return true;

   //   bool bIsDir;

   //   DWORD dwLastError;

   //   if(m_isdirmap.lookup(strPath, bIsDir, dwLastError))
   //   {

   //      if(!bIsDir)
   //      {

   //         SetLastError(dwLastError);

   //      }

   //      return bIsDir;

   //   }


   //   wstring wstrPath;

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

   //   bIsDir = ::dir::is(::str::international::unicode_to_utf8(wstrPath));

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

      DWORD dwLastError;

      if(m_isdirmap.lookup(str, bIsDir, dwLastError, (int32_t) iLast))
         return bIsDir;


      if(papp->m_bZipIsDir && iLast >= 3  && !strnicmp_dup(&((const char *) str)[iLast - 3], ".zip", 4))
      {
         m_isdirmap.set(str.Left(iLast + 1), true, 0);
         return true;
      }

      //strsize iFind = ::str::find_ci(".zip:", str);

      //if(papp->m_bZipIsDir && iFind >= 0 && iFind < iLast)
      //{
      //   bool bHasSubFolder;
      //   if(m_isdirmap.lookup(str, bHasSubFolder, dwLastError))
      //      return bHasSubFolder;
      //   bHasSubFolder = m_pziputil->HasSubFolder(papp, str);
      //   m_isdirmap.set(str.Left(iLast + 1), bHasSubFolder, bHasSubFolder ? 0 : ::GetLastError());
      //   return bHasSubFolder;
      //}


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

      bIsDir = ::dir::is(::str::international::unicode_to_utf8(wstrPath));

      m_isdirmap.set(str.Left(iLast + 1), bIsDir, bIsDir ? 0 : ::GetLastError());

      return bIsDir;
   }

   //::file::path dir::votagus()
   //{
   //   string strVotagusFolder = System.get_ca2_module_folder();
   //   System.file().path().eat_end_level(strVotagusFolder, 2, "\\");
   //   return dir::path(strVotagusFolder, lpcsz, lpcsz2);
   //}


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

   // stage in ccvotagus spalib
   ::file::path dir::element()
   {

      single_lock sl(&m_mutex, true);

      return m_strCa2;

   }

   
   //::file::path dir::module()
   //{

	  // return System.get_module_folder();

   //}


   //::file::path dir::ca2module()
   //{
   //   
	  // return System.get_ca2_module_folder();
   //   
   //}


   ::file::path dir::time_square(::aura::application * papp, const string & strPrefix, const string & strSuffix)
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

   bool dir::mk(const ::file::path & lpcsz, ::aura::application * papp)
   {

	   if (is(lpcsz, papp))
		   return true;

	   ::file::patha stra;

	   lpcsz.ascendants_path(stra);

	   for (int32_t i = 0; i < stra.get_size(); i++)
	   {

		   if (!is(stra[i], papp))
		   {

			   if (!::dir::mk(stra[i]))
			   {
				   DWORD dwError = ::GetLastError();
				   if (dwError == ERROR_ALREADY_EXISTS)
				   {
					   string str;
					   str = "\\\\?\\" + stra[i];
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
					   //if(::CreateDirectory(::str::international::utf8_to_unicode("\\\\?\\" + stra[i]), NULL))
					   if (::dir::mk("\\\\?\\" + stra[i]))
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
				   FormatMessage(FORMAT_MESSAGE_ALLOcaTE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwError, 0, (LPTSTR)&pszError, 8, NULL);

				   //TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
				   // xxx               ::LocalFree(pszError);
				   //m_isdirmap.set(stra[i], false);
			   }
			   else
			   {
				   m_isdirmap.set(stra[i], true, 0);
			   }
		   try1:

			   if (!is(stra[i], papp))
			   {
				   return false;
			   }

		   }
	   }
	   return true;

   }

   bool dir::rm(::aura::application * papp, const ::file::path & psz, bool bRecursive)
   {
	   if (bRecursive)
	   {

		   ::file::listing straPath(papp);

		   straPath.ls(psz);

		   for (int32_t i = 0; i < straPath.get_count(); i++)
		   {

			   if (is(straPath[i], papp))
			   {

				   rm(papp, psz / straPath[i].name(), true);

			   }
			   else
			   {

				   ::unlink(straPath[i]);

			   }

		   }

	   }

	   return ::rmdir(psz) != FALSE;
   }


   bool dir::initialize()
   {

      xml::document doc(get_app());

      doc.load(Application.file().as_string(appdata() / "configuration\\directory.xml"));

      m_pathUser = m_strCa2 / "userfolder";

      m_strCommonAppData = m_strCa2 / "commonappdata"; 

      mk(m_strCommonAppData, get_app());

      if (!is(m_strCommonAppData, get_app()))
         return false;


      if(doc.get_root()->get_name() == "directory_configuration")
      {

         m_strTimeFolder = doc.get_root()->get_child_value("time");

         m_strNetSeedFolder = doc.get_root()->get_child_value("netseed");

      }

      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = appdata()/ "time";

      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = element()/ "net/netseed";

      mk(m_strTimeFolder, get_app());

      if(!is(m_strTimeFolder, get_app()))
         return false;

      mk(m_strTimeFolder / "time", get_app());

      return true;

   }

   ::file::path dir::trash_that_is_not_trash(const ::file::path & pszParam)
   {
      
	   if(pszParam == NULL)
         return "";

	   ::file::path psz(pszParam);

      if(psz[1] == ':')
      {
         string strDir = psz.folder();
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
      /*SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_COMMON_APPDATA,
         FALSE);*/

      str = string(System.m_pandroidinitdata->m_pszCacheDir) / ".ca2/appdata";
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
      return str /  "ca2";
   }

   ::file::path dir::commonappdata()
   {

      return m_strCommonAppData;

   }


   ::file::path dir::element_commonappdata(const string & strElement)
   {

      string strRelative;

      strRelative = strElement;

      index iFind = strRelative.find(':');

      if(iFind >= 0)
      {

         strsize iFind1 = strRelative.reverse_find("\\",iFind);

         strsize iFind2 = strRelative.reverse_find("/",iFind);

         strsize iStart = MAX(iFind1 + 1,iFind2 + 1);

         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart,iFind - iStart) + strRelative.Mid(iFind + 1);

      }

      return m_strCommonAppData / "ca2" / strRelative;

   }

   ::file::path dir::usersystemappdata(::aura::application * papp, const string & lpcszPrefix)
   {
      UNREFERENCED_PARAMETER(papp);
      return appdata() / lpcszPrefix;
   }

   ::file::path dir::userappdata(::aura::application * papp)
   {
      return userfolder(papp) /  "appdata";
   }

   ::file::path dir::userdata(::aura::application * papp)
   {
      return userfolder(papp) / "data";
   }

//   ::file::path dir::userfolder(::aura::application * papp)
//   {
//
//      string str;
//      /*SHGetSpecialFolderPath(
//         NULL,
//         str,
//         CSIDL_PROFILE,
//         FALSE);*/
//
//      str = getenv("HOME");
//
//      ::file::path strRelative;
//      strRelative = element();
//      index iFind = strRelative.find(':');
//      if(iFind >= 0)
//      {
//         strsize iFind1 = strRelative.reverse_find("\\", iFind);
//         strsize iFind2 = strRelative.reverse_find("/", iFind);
//         strsize iStart = MAX(iFind1 + 1, iFind2 + 1);
//         strRelative = strRelative.Left(iFind - 1) + "_" + strRelative.Mid(iStart, iFind - iStart) + strRelative.Mid(iFind + 1);
//      }
//
//	  ::file::path strUserFolderShift;
//
//      if(App(papp).directrix()->m_varTopicQuery.has_property("user_folder_relative_path"))
//      {
//         strUserFolderShift = strRelative / App(papp).directrix()->m_varTopicQuery["user_folder_relative_path"].get_string();
//      }
//      else
//      {
//         strUserFolderShift = strRelative;
//      }
//
//      return str / "ca2" / strUserFolderShift;
//
////      return path(path(str, "ca2"), lpcsz);
///*      if(&AppUser(papp) == NULL)
//      {
//         string str;
//         SHGetSpecialFolderPath(
//            NULL,
//            str,
//            CSIDL_PROFILE,
//            FALSE);
//         return path(path(str, "ca2\\_____default"), lpcsz);
//      }
//      else
//      {
//         return path(AppUser(papp).m_strPath, lpcsz, lpcsz2);
//      }*/
//   }

   ::file::path dir::default_os_user_path_prefix(::aura::application * papp)
   {
      /*UNREFERENCED_PARAMETER(papp);
      wchar_t buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(Namecanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }*/
      /*return ::str::international::unicode_to_utf8(buf);*/
      return ::getlogin();
   }

   ::file::path dir::default_userappdata(::aura::application * papp, const string & lpcszPrefix, const string & lpcszLogin)
   {
      return default_userfolder(papp, lpcszPrefix, lpcszLogin) /  "appdata";
   }

   ::file::path dir::default_userdata(::aura::application * papp, const string & lpcszPrefix, const string & lpcszLogin)
   {
	   return default_userfolder(papp, lpcszPrefix, lpcszLogin) / "data";
   }

   ::file::path dir::default_userfolder(::aura::application *  papp, const string & lpcszPrefix, const string & lpcszLogin)
   {

	   return userfolder(papp);

   }

   
   ::file::path dir::userquicklaunch(::aura::application * papp)
   {
   
	   return string(System.m_pandroidinitdata->m_pszCacheDir) /  "Microsoft\\Internet Explorer\\Quick Launch";
   
   }


   ::file::path dir::userprograms(::aura::application * papp)
   {

	   return  "/usr/bin";

   }


   ::file::path dir::commonprograms()
   {

	   return "/usr/share/";

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
	   ::file::listing ls(papp);
      ls.ls_dir(pszDir);
      return ls.get_size() > 0;

   }

} // namespace android
