#include "StdAfx.h"

namespace win
{
   dir::dir(::ca::application * papp) :
      ::ca::ca(papp),
      m_path(papp)
   {
   }

   dir::path::path(::ca::application * papp) :
      ::ca::ca(papp)
   {
   }

   string dir::path(const char * lpcszFolder, const char * lpcszRelative, const char * psz2)
   {
      if(lpcszRelative == NULL)
      {
         if(psz2 == NULL)
            return lpcszFolder;
         psz2 = lpcszRelative;
         psz2 = NULL;
      }
      string strPath;
      string strFolder(lpcszFolder);
      string strRelative(lpcszRelative);
      strFolder.trim();
      gen::str::ends_eat(strFolder, "\\");
      gen::str::ends_eat(strFolder, "/");
      gen::str::begins_eat(strRelative, "\\");
      gen::str::begins_eat(strRelative, "/");
      if(strFolder.is_empty())
      {
         strPath = strRelative;
      }
      else
      {
         strPath = strFolder + "\\" + strRelative;
      }
      if(psz2 != NULL)
      {
         strPath = path(strPath, psz2);
      }
   #ifdef WIN32
      strPath.replace("/", "\\");
   #else
      strPath.replace("\\", "/");
   #endif
      return strPath;
   }

   bool dir::path::is_equal(const char * lpcsz1, const char * lpcsz2)
   {
      return Application.file_system().ComparePath(lpcsz1, lpcsz2);
   }

   void dir::root_ones(AStrArray & stra)
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
         stra.add(str);
         lpsz++;
      }

      free(lpszAlloc);
   }

   void dir::ls_pattern(const char * lpcsz, const char * pszPattern, AStrArray * pstraPath, AStrArray * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(Application.dir().path(lpcsz, pszPattern));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
            if(pbaIsDir != NULL)
            {
               pbaIsDir->add(filefind.IsDirectory() != FALSE);
            }
            if(piaSize != NULL)
            {
               piaSize->add(filefind.GetLength64());
            }
         }
      }
   }

   void dir::rls(const char * lpcsz, AStrArray * pstraPath, AStrArray * pstraTitle, AStrArray * pstraRelative)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(Application.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
            if(pstraRelative != NULL)
            {
               pstraRelative->add(filefind.GetFileName());
            }
            if(filefind.IsDirectory())
            {
               int iStart = 0;
               if(pstraRelative != NULL)
               {
                  iStart = pstraRelative->get_size();
               }
               rls(filefind.GetFilePath(), pstraPath, pstraTitle, pstraRelative);
               if(pstraRelative != NULL)
               {
                  for(int i = iStart; i < pstraRelative->get_size(); i++)
                  {
                     pstraRelative->element_at(i) = Application.dir().path(filefind.GetFileName(), pstraRelative->element_at(i));
                  }
               }
            }
         }
      }
   }

   void dir::rls_dir(const char * lpcsz, AStrArray * pstraPath, AStrArray * pstraTitle, AStrArray * pstraRelative)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(Application.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDots() && filefind.IsDirectory())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
            if(pstraRelative != NULL)
            {
               pstraRelative->add(filefind.GetFileName());
            }
            if(filefind.IsDirectory())
            {
               int iStart = 0;
               if(pstraRelative != NULL)
               {
                  iStart = pstraRelative->get_size();
               }
               rls_dir(filefind.GetFilePath(), pstraPath, pstraTitle, pstraRelative);
               if(pstraRelative != NULL)
               {
                  for(int i = iStart; i < pstraRelative->get_size(); i++)
                  {
                     pstraRelative->element_at(i) = Application.dir().path(filefind.GetFileName(), pstraRelative->element_at(i));
                  }
               }
            }
         }
      }
   }

   void dir::ls_dir(const char * lpcsz, AStrArray * pstraPath, AStrArray * pstraTitle)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(Application.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(filefind.IsDirectory() && !filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
         }
      }
   }

   void dir::ls_file(const char * lpcsz, AStrArray * pstraPath, AStrArray * pstraTitle)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(Application.dir().path(lpcsz, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(!filefind.IsDirectory() && !filefind.IsDots())
         {
            if(pstraPath != NULL)
            {
               pstraPath->add(filefind.GetFilePath());
            }
            if(pstraTitle != NULL)
            {
               pstraTitle->add(filefind.GetFileName());
            }
         }
      }
   }

   void dir::ls(const char * lpcsz, AStrArray * pstraPath, AStrArray * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
   {
      return ls_pattern(lpcsz, "*.*", pstraPath, pstraTitle, pbaIsDir, piaSize);
   }

   bool dir::is(const char * lpcszPath)
   {
      string strPath(lpcszPath);
      if(strPath.get_length() >= MAX_PATH)
      {
         if(gen::str::begins(strPath, "\\\\"))
	      {
	         strPath = "\\\\?\\UNC" + strPath.Mid(1);
	      }
         else
	      {
            strPath = "\\\\?\\" + strPath;
	      }
	   }
      DWORD dwAttrib;
      dwAttrib = GetFileAttributesW(gen::international::utf8_to_unicode(strPath));
	   if(dwAttrib == INVALID_FILE_ATTRIBUTES)
	   {
	      dwAttrib = GetFileAttributes(lpcszPath);
      }
      bool retval = ((dwAttrib != INVALID_FILE_ATTRIBUTES) && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
      return retval;
   }
   	


   string dir::votagus(const char * lpcsz, const char * lpcsz2)
   {
      string strVotagusFolder = Application.get_ca2_module_folder();
      Application.file().path().eat_end_level(strVotagusFolder, 2, "\\");
      return dir::path(strVotagusFolder, lpcsz, lpcsz2);
   }

   string dir::time(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(m_strTimeFolder, lpcsz, lpcsz2);
   }

   string dir::stage(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(ca2("stage"), lpcsz, lpcsz2);
   }

   string dir::stageapp(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(stage("basis", lpcsz), lpcsz2);
   }

   string dir::netseed(const char * lpcsz, const char * lpcsz2)
   {
      return dir::path(m_strNetSeedFolder, lpcsz, lpcsz2);
   }

   // stage in ccvotagus spalib
   string dir::ca2(const char * lpcsz, const char * lpcsz2)
   {
      string str = Application.get_ca2_module_folder();
      Application.file().path().eat_end_level(str, 2, "\\");
      return dir::path(str, lpcsz, lpcsz2);
   }

   string dir::module(const char * lpcsz, const char * lpcsz2)
   {
      string str = Application.get_module_folder();
      return dir::path(str, lpcsz, lpcsz2);
   }

   string dir::ca2module(const char * lpcsz, const char * lpcsz2)
   {
      string str = Application.get_ca2_module_folder();
      return dir::path(str, lpcsz, lpcsz2);
   }


   void dir::time_square(string &str)
   {
      str = time("time");
   }

   string dir::time_log(const char * pszId)
   {
      string strLogBaseDir;
      strLogBaseDir = appdata("log");
      return path(strLogBaseDir, pszId);
   }

   bool dir::mk(const char * lpcsz)
   {
      if(is(lpcsz))
         return true;
      AStrArray stra;
      Application.file().get_ascendants_path(lpcsz, stra);
      for(int i = 0; i < stra.get_size(); i++)
      {
         if(!is(stra[i]))
         {
            if(!::CreateDirectoryW(gen::international::utf8_to_unicode(stra[i]), NULL))
            {
               DWORD dwError = ::GetLastError();
               char * pszError;
               FormatMessage(
     FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
     NULL,
     dwError,
     0,
     (LPTSTR) &pszError,
     8,
     NULL);

               TRACE("dir::mk CreateDirectoryW last error(%d)=%s", dwError, pszError);
               ::LocalFree(pszError);
            }
            
            if(!is(stra[i]))
            {
               return false;
            }
         }
      }
      return true;
   }

   string dir::name(const char * path1)
   {
      string str;

      str = path1;
      int iPos1 = str.reverse_find('\\');
      int iPos2 = str.reverse_find('/');
      return str.Mid(0, max(max(iPos1 + 1, iPos2 + 1), 0));
   }

   string dir::locale_style()
   {
      return Application.get_locale_style_dir();
   }

   string dir::matter(const char * psz, const char * psz2)
   {
      string strMain = path(votagus(), "app\\appmatter\\main");
      string strMatter = path(strMain, locale_style()); 
      string strPath1 = path(strMatter, psz, psz2);
      if(Application.file().exists(strPath1))
         return strPath1;
      strMatter = path(strMain, "en/en");
      string strPath2 = path(strMatter, psz, psz2);
      if(Application.file().exists(strPath2))
         return strPath2;
      strMatter = path(strMain, "_std/_std");
      strPath2 = path(strMatter, psz, psz2);
      if(Application.file().exists(strPath2))
         return strPath2;
      strMatter = path(strMain, "se/se");
      strPath2 = path(strMatter, psz, psz2);
      if(Application.file().exists(strPath2))
         return strPath2;
      return strPath1;
   }


   class ::ca::dir::path & dir::path()
   {
      return m_path;
   }


   bool dir::initialize()
   {
      xml::node node;
      node.load(Application.file().as_string(appdata("configuration\\directory.xml")));
      if(node.m_strName == "directory_configuration")
      {
         m_strTimeFolder = node.get_child_value("time"); 
         m_strNetSeedFolder = node.get_child_value("netseed"); 
      }
      if(m_strTimeFolder.is_empty())
         m_strTimeFolder = ca2("time");
      if(m_strNetSeedFolder.is_empty())
         m_strNetSeedFolder = ca2("net/netseed");
      mk(m_strTimeFolder);
      if(!is(m_strTimeFolder))
         return false;
      mk(path(m_strTimeFolder, "time"));
      return true;
   }

   string dir::trash_that_is_not_trash(const char * psz)
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
         class time time;
         time = time::get_current_time();
         strFormat.Format("%04d-%02d-%02d %02d-%02d-%02d\\", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
         str += strFormat;
         if(strDir[2] == '\\')
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

   string dir::appdata(const char * lpcsz, const char * lpcsz2)
   {
      return path(ca2("appdata"), lpcsz, lpcsz2);
   }

   string dir::usersystemappdata(const char * lpcsz, const char * lpcsz2)
   {
      wchar_t buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }
      return path(ca2("appdata", gen::international::unicode_to_utf8(buf)), lpcsz, lpcsz2);
   }

   string dir::userappdata(const char * lpcsz, const char * lpcsz2)
   {
      return path(userfolder("appdata"), lpcsz, lpcsz2);
   }

   string dir::userdata(const char * lpcsz, const char * lpcsz2)
   {
      return path(userfolder("data"), lpcsz, lpcsz2);
   }

   string dir::userfolder(const char * lpcsz, const char * lpcsz2)
   {
      if(Application.user().get_user() == NULL)
      {

         return path(ca2("user\\___default"), lpcsz);
      }
      return path(Application.user().get_user()->m_strPath, lpcsz, lpcsz2);
   }

   string dir::default_userappdata(const char * lpcszLogin, const char * pszRelativePath)
   {
      return path(default_userfolder(lpcszLogin, "appdata"), pszRelativePath);
   }

   string dir::default_userdata(const char * lpcszLogin, const char * pszRelativePath)
   {
      return path(default_userfolder(lpcszLogin, "data"), pszRelativePath);
   }

   string dir::default_userfolder(const char * lpcszLogin, const char * pszRelativePath)
   {
      wchar_t buf[MAX_PATH];
      ULONG ulSize = sizeof(buf) / sizeof(wchar_t);
      if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
      {
         if(!::GetUserNameW(buf, &ulSize))
         {
            memset(buf, 0, sizeof(buf));
         }
      }
      return path(path(ca2("user"), 
         gen::international::unicode_to_utf8(buf), lpcszLogin), pszRelativePath);
   }

   string dir::userquicklaunch(const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_APPDATA,
         FALSE);
      str = path(str, "Microsoft\\Internet Explorer\\Quick Launch");
      return path(str, lpcszRelativePath, lpcsz2);
   }

   string dir::userprograms(const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_PROGRAMS,
         FALSE);
      return path(str, lpcszRelativePath, lpcsz2);
   }

   string dir::commonprograms(const char * lpcszRelativePath, const char * lpcsz2)
   {
      string str;
      SHGetSpecialFolderPath(
         NULL,
         str,
         CSIDL_COMMON_PROGRAMS,
         FALSE);
      return path(str, lpcszRelativePath, lpcsz2);
   }

   bool dir::is_inside_time(const char * pszPath)
   {
      return is_inside(time(), pszPath);
   }

   bool dir::is_inside(const char * pszDir, const char * pszPath)
   {
      return gen::str::begins_ci(pszDir, pszPath);
   }

   bool dir::has_subdir(const char * pszDir)
   {
      FileFind filefind;
      BOOL bWorking;
      bWorking = filefind.FindFile(path(pszDir, "*.*"));
      while(bWorking)
      {
         bWorking = filefind.FindNextFileA();
         if(filefind.IsDirectory() && !filefind.IsDots())
         {
            return true;
         }
      }
      return false;
   }

} // namespace win
