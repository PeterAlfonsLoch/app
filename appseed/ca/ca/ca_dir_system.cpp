#include "framework.h"


#ifdef WINDOWS

#define DIR_SEPARATOR "\\"

#else

#define DIR_SEPARATOR "/"

#endif

namespace ca
{


   bool path::is_equal(const char * lpcsz1, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz1);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception(get_app(), "this is an interface");
   }


   namespace dir
   {


      system::system(::ca::application * papp) :
         ca(papp),
         m_mutex(papp),
         m_isdirmap(papp)
      {
         m_pziputil = new zip::Util;
         m_isdirmap.m_dwTimeOut = 15000;
      }

      system::~system()
      {
         if(m_pziputil != NULL)
         {
            delete m_pziputil;
         }
      }



      string system::path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2, bool bUrl)
      {
         UNREFERENCED_PARAMETER(pszFolder);
         UNREFERENCED_PARAMETER(iLenFolder);
         UNREFERENCED_PARAMETER(pszRelative);
         UNREFERENCED_PARAMETER(iLenRelative);
         UNREFERENCED_PARAMETER(psz2);
         UNREFERENCED_PARAMETER(iLen2);
         UNREFERENCED_PARAMETER(bUrl);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2)
      {

         return path(pszFolder, iLenFolder, pszRelative, iLenRelative, psz2, iLen2, ::ca::is_url(pszFolder));

      }

      string system::path(const string & strFolder, const string & strRelative)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), NULL, 0, ::ca::is_url(strFolder));

      }


      string system::path(const string & strFolder, const string & strRelative, const string & str2)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), str2, str2.get_length(), ::ca::is_url(strFolder));

      }

      string system::path(const string & strFolder, const string & strRelative, const char * psz2)
      {
         if(psz2 == NULL)
         {
            return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), psz2, 0, ::ca::is_url(strFolder));
         }
         else
         {
            return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), psz2, strlen(psz2), ::ca::is_url(strFolder));
         }

      }

      string system::path(const string & strFolder, const string & strRelative, bool bUrl)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), NULL, 0, bUrl);

      }

      string system::path(const string & strFolder, const string & strRelative, const string & str2, bool bUrl)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), str2, str2.get_length(), bUrl);

      }

      inline bool myspace(char ch)
      {
         return ch == ' ' ||
                ch == '\t' ||
                ch == '\r' ||
                ch == '\n';
      }

#define string_STRCAT2_beg_char_end(strCat, ch, str1, str2, beg1, end1, beg2, end2) \
         { \
            char * psz = strCat.GetBufferSetLength(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
            strncpy(psz, &((const char *)str1)[beg1], end1 - beg1 + 1); \
            psz[end1 - beg1 + 1] = ch; \
            strncpy(&psz[end1 - beg1 + 2], &((const char *)str2)[beg2], end2 - beg2 + 1); \
            strPath.ReleaseBuffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
         }

      string system::simple_path(const string & strFolder, const string & strRelative)
      {

         if(strRelative.is_empty())
         {
            if(strFolder.is_empty())
               return "";
            return strFolder;
         }

         strsize iFolderBeg = 0;

         strsize iFolderEnd = strFolder.get_length() - 1;

         if(iFolderEnd >= iFolderBeg)
         {
            //strFolder.trim();
            // passive left trimming
            while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
               iFolderBeg++;
            // passive right trimming
            while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
               iFolderEnd--;
            //better than following 2 together
            //ca::str::ends_eat(strFolder, "\\");
            //ca::str::ends_eat(strFolder, "/");
            while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
               iFolderEnd--;
         }

         strsize iRelativeBeg = 0;

         strsize iRelativeEnd = strRelative.get_length() - 1;

         if(iRelativeEnd >= iRelativeBeg)
         {
            //strFolder.trim();
            // passive left trimming
            while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
               iFolderBeg++;
            // passive right trimming
            while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
               iFolderEnd--;
            //better than following 2 together
            //ca::str::ends_eat(strFolder, "\\");
            //ca::str::ends_eat(strFolder, "/");
            while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
               iRelativeBeg++;
         }

         string strPath;
         if(iFolderBeg > iFolderEnd)
         {
            strPath = strRelative;
         }
         else
         {
            char * psz = strPath.GetBufferSetLength(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
            strncpy(psz, &((const char *)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
            #ifdef LINUX
            psz[iFolderEnd - iFolderBeg + 1] = '/';
            #else
            psz[iFolderEnd - iFolderBeg + 1] = '\\';
            #endif
            strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const char *)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
            strPath.ReleaseBuffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
         }


         return strPath;
      }

      string system::simple_path(const string & strFolder, const string & strRelative, const string & str2)
      {

         if(strRelative.is_empty())
         {
            if(str2.is_empty())
            {
               if(strFolder.is_empty())
                  return "";
               return strFolder;
            }
            else
            {
               if(strFolder.is_empty())
                  return str2;
               return simple_path(strFolder, str2);
            }
         }
         else if(strFolder.is_empty())
         {
            if(str2.is_empty())
            {
               return strRelative;
            }
            else
            {
               return simple_path(strRelative, str2);
            }
         }
         else if(str2.is_empty())
         {
            return simple_path(strFolder, strRelative);
         }

         // none of them - 3 - are empty

         strsize iFolderBeg = 0;

         strsize iFolderEnd = strFolder.get_length() - 1;

         if(iFolderEnd >= iFolderBeg)
         {
            //strFolder.trim();
            // passive left trimming
            while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
               iFolderBeg++;
            // passive right trimming
            while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
               iFolderEnd--;
            //better than following 2 together
            //ca::str::ends_eat(strFolder, "\\");
            //ca::str::ends_eat(strFolder, "/");
            while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
               iFolderEnd--;
         }

         strsize iRelativeBeg = 0;

         strsize iRelativeEnd = strRelative.get_length() - 1;

         if(iRelativeEnd >= iRelativeBeg)
         {
            //strFolder.trim();
            // passive left trimming
            while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
               iFolderBeg++;
            // passive right trimming
            while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
               iFolderEnd--;
            //better than following 2 together
            //ca::str::ends_eat(strFolder, "\\");
            //ca::str::ends_eat(strFolder, "/");
            while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
               iRelativeBeg++;
         }


         strsize iBeg2 = 0;

         strsize iEnd2 = str2.get_length() - 1;

         if(iEnd2 >= iBeg2)
         {
            //strFolder.trim();
            // passive left trimming
            while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iBeg2]))
               iBeg2++;
            // passive right trimming
            while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iEnd2]))
               iEnd2--;
            //better than following 2 together
            //ca::str::ends_eat(strFolder, "\\");
            //ca::str::ends_eat(strFolder, "/");
            while(iBeg2 <= iEnd2 && (str2[iBeg2] == '/' || str2[iBeg2] == '\\'))
               iBeg2++;
         }

         if(iRelativeBeg > iRelativeEnd)
         {
            if(iBeg2 > iEnd2)
            {
               if(iFolderBeg > iFolderEnd)
                  return "";
               return strFolder.Mid(iFolderBeg, iFolderEnd - iFolderBeg + 1);
            }
            else
            {
               if(iFolderBeg > iFolderEnd)
                  return str2.Mid(iBeg2, iEnd2 - iBeg2 + 1);
               string strPath;
               string_STRCAT2_beg_char_end(strPath, '\\', strFolder, str2, iFolderBeg, iFolderEnd, iBeg2, iEnd2);
               return strPath;
            }
         }
         else if(strFolder.is_empty())
         {
            if(str2.is_empty())
            {
               return strRelative;
            }
            else
            {
               string strPath;
               #ifdef LINUX
               string_STRCAT2_beg_char_end(strPath, '/', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
               #else
               string_STRCAT2_beg_char_end(strPath, '\\', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
               #endif
               return strPath;
            }
         }
         else if(str2.is_empty())
         {
            string strPath;
            #ifdef LINUX
            string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
            #else
            string_STRCAT2_beg_char_end(strPath, '/', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
            #endif
            return strPath;
         }

         string strPath;

         char * psz = strPath.GetBufferSetLength(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
         strncpy(psz, &((const char *)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
         #ifdef LINUX
         psz[iFolderEnd - iFolderBeg + 1] = '/';
         #else
         psz[iFolderEnd - iFolderBeg + 1] = '\\';
         #endif
         strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const char *)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
         #ifdef LINUX
         psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '/';
         #else
         psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '\\';
         #endif
         strncpy(&psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1 + 1], &((const char *)str2)[iBeg2], iEnd2 - iBeg2 + 1);
         strPath.ReleaseBuffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);

         return strPath;

      }


      string system::relpath(const char * lpcszSource, const char * lpcszRelative, const char * psz2)
      {
         UNREFERENCED_PARAMETER(lpcszSource);
         UNREFERENCED_PARAMETER(lpcszRelative);
         UNREFERENCED_PARAMETER(psz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::root_ones(stringa & stra, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(stra);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::rls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, base_array < bool, bool > * pbaIsDir, base_array < int64_t, int64_t > * piaSize, e_extract eextract)
      {
         UNREFERENCED_PARAMETER(pstraRelative);
         UNREFERENCED_PARAMETER(pszPattern);
         if(eextract != extract_none && papp->m_bZipIsDir && (ca::str::ends_ci(lpcsz, ".zip") || ca::str::find_ci(".zip:", lpcsz) >= 0))
         {
            throw "should implement recursive zip";
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);
            return;
         }
         throw not_implemented(get_app(), "is really a directory or compressed directory/file??");

      }


      void system::ls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < int64_t, int64_t > * piaSize)
      {
         UNREFERENCED_PARAMETER(pszPattern);
         if(ca::str::begins_ci(lpcsz, "http://") || ca::str::begins_ci(lpcsz, "https://"))
         {
            string str = App(papp).http().get(lpcsz);
            if(pstraPath != NULL)
            {
               pstraPath->add_tokens(str, "\n", false);
            }
            return;
         }
         if(papp->m_bZipIsDir && (ca::str::ends_ci(lpcsz, ".zip") || ca::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented(get_app(), "is really a directory or compressed directory/file??");

      }

      void system::ls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < int64_t, int64_t > * piaSize)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pbaIsDir);
         UNREFERENCED_PARAMETER(piaSize);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::rls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, e_extract eextract)
      {
         if(eextract != extract_none && papp->m_bZipIsDir && (ca::str::ends_ci(lpcsz, ".zip") || ca::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, pstraRelative, NULL, NULL, eextract == extract_all ? extract_all : extract_none);
            return;
         }
         else
         {
            return;
         }
      }

      void system::rls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pstraRelative);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::ls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         if(papp->m_bZipIsDir && (ca::str::ends_ci(lpcsz, ".zip") || ca::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls_dir(papp, lpcsz, pstraPath, pstraTitle);
            return;
         }
         else
         {
            return;
         }
      }

      bool system::has_subdir(::ca::application * papp, const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::ls_file(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is(const char * lpcszPath, ::ca::application * papp)
      {
         if(ca::str::begins_ci(lpcszPath, "http://") || ca::str::begins_ci(lpcszPath, "https://"))
         {
            return App(papp).http().exists(lpcszPath);
         }
         if(papp->m_bZipIsDir && (ca::str::ends_ci(lpcszPath, ".zip")))
            return true;
         if(papp->m_bZipIsDir && (ca::str::find_ci(".zip:", lpcszPath) >= 0))
         {
            bool bHasSubFolder;
            uint32_t dwLastError;
            if(m_isdirmap.lookup(lpcszPath, bHasSubFolder, dwLastError))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, lpcszPath);
            m_isdirmap.set(lpcszPath, bHasSubFolder, ::GetLastError());
            return bHasSubFolder;
         }
         return false;
      }

      bool system::is(const string & strPath, ::ca::application * papp)
      {
         if(ca::str::begins_ci(strPath, "http://") || ca::str::begins_ci(strPath, "https://"))
         {
            return App(papp).http().exists(strPath);
         }

         if(papp->m_bZipIsDir && (ca::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if(papp->m_bZipIsDir && (ca::str::find_ci(".zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            uint32_t dwLastError;
            if(m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder, GetLastError());
            return bHasSubFolder;
         }
         return false;
      }

      bool system::is(const var & var, ::ca::application * papp)
      {
         return is((const string &) var, papp);
      }

      bool system::name_is(const char * lpcszPath, ::ca::application * papp)
      {
         return name_is((const string &) lpcszPath, papp);
      }

      bool system::name_is(const string & strPath, ::ca::application * papp)
      {
         //OutputDebugString(strPath);
         if(papp->m_bZipIsDir && (ca::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if(papp->m_bZipIsDir && (ca::str::find_ci(".zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            uint32_t dwLastError;
            if(m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder, GetLastError());
            return bHasSubFolder;
         }
         return false;
      }

      bool system::name_is(const var & var, ::ca::application * papp)
      {
         return name_is((const string &) var, papp);
      }


      system::is_dir_map::is_dir_map(::ca::application * papp) :
         ::collection::string_map < is_dir >(256), // block size
         m_mutex(papp)
      {
         InitHashTable(16384, TRUE);
      }

      bool system::is_dir_map::lookup(const char * pszPath, bool &bIsDir, uint32_t & dwLastError)
      {
         return lookup(string(pszPath), bIsDir, dwLastError);
      }

      bool system::is_dir_map::lookup(const string & strPath, bool &bIsDir, uint32_t & dwLastError)
      {

         if(strPath.get_length() <= 0)
         {
            bIsDir = false;
            return true;
         }




         string strLookup(strPath);

#ifdef LINUX
         if(strLookup.last_char() != '\\' && strLookup.last_char() != '/' )
            strLookup += "/";
#else
         if(strLookup.last_char() != '\\' && strLookup.last_char() != '/' )
            strLookup += "\\";
#endif

         single_lock sl(&m_mutex, TRUE);

         ::collection::string_map < is_dir >::pair * ppair = this->PLookup(strLookup);

         if(ppair == NULL)
            return false;

         if(::get_tick_count() > ppair->m_value.m_dwLastCheck + m_dwTimeOut)
         {
            return false;
         }

         bIsDir = ppair->m_value.m_bIsDir;

         dwLastError = ppair->m_value.m_dwError;

         return true;

      }

      bool system::is_dir_map::lookup(const string & strPath, bool &bIsDir, uint32_t &dwLastError, int32_t iLast)
      {

         if(iLast < 0)
         {
            bIsDir = true; // root_ones dir
            return true;
         }

         string strLookup(strPath, iLast + 1);

         single_lock sl(&m_mutex, TRUE);

         ::collection::string_map < is_dir >::pair * ppair = this->PLookup(strLookup);

         if(ppair == NULL)
            return false;

         if(::get_tick_count() > ppair->m_value.m_dwLastCheck + m_dwTimeOut)
         {
            return false;
         }

         bIsDir = ppair->m_value.m_bIsDir;

         dwLastError = ppair->m_value.m_dwError;

         return true;

      }

      void system::is_dir_map::set(const char * pszPath, bool bIsDir, uint32_t dwLastError)
      {
#ifdef LINUX
         static string strSep = "/";
#else
         static string strSep = "\\";
#endif
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwError = dwLastError;
         isdir.m_dwLastCheck = ::get_tick_count();
         string strPath(pszPath);
         if(!ca::str::ends(strPath, strSep))
            strPath += strSep;
         single_lock sl(&m_mutex, TRUE);
         set_at(strPath, isdir);
      }

      void system::is_dir_map::set(const string & strPath, bool bIsDir, uint32_t dwLastError)
      {
#ifdef LINUX
         static string strSep = "/";
#else
         static string strSep = "\\";
#endif
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwError = dwLastError;
         isdir.m_dwLastCheck = ::get_tick_count();
         if(ca::str::ends(strPath, strSep))
         {
            single_lock sl(&m_mutex, TRUE);
            set_at(strPath, isdir);
         }
         else
         {
            string strPath2(strPath);
            strPath2 += strSep;
            single_lock sl(&m_mutex, TRUE);
            set_at(strPath2, isdir);
         }
      }

      string system::votagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::time(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::stage(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::stageapp(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::netseed(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca(const string & str, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca(const char * lpcsz, const string & str2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca(const string & str, const string & str2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca(const string & str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::ca2module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::time_square(string &str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::time_log(const char * pszId)
      {
         UNREFERENCED_PARAMETER(pszId);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::mk(const char * lpcsz, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::rm(::ca::application * papp, const char * psz, bool bRecursive)
      {
         UNREFERENCED_PARAMETER(psz);
         UNREFERENCED_PARAMETER(bRecursive);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::name(const char * path1)
      {
         UNREFERENCED_PARAMETER(path1);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::locale_schema(::ca::application * papp, const string & strLocale, const string & strSchema)
      {

         return papp->m_pappThis->get_locale_schema_dir(strLocale, strSchema);

      }

      string system::locale_schema_matter(::ca::application * papp, const string & strLocale, const string & strSchema)
      {

         single_lock sl(&papp->m_pappThis->m_mutexMatterLocator, true);

         return path(papp->m_pappThis->m_strMatterLocator, papp->m_pappThis->get_locale_schema_dir(strLocale, strSchema));

      }

      string system::locale_schema_matter(const string & strLocator, const string & strLocale, const string & strSchema)
      {

         return path(strLocator, simple_path(strLocale, strSchema));

      }

      void system::matter_ls(::ca::application * papp, const string & str, stringa & stra)
      {

         string strDir = matter(papp, str, true);

         ls(papp, strDir, &stra);

      }

      void system::matter_ls_file(::ca::application * papp, const string & str, stringa & stra)
      {

         string strDir = matter(papp, str, true);

         ls_file(papp, strDir, &stra);

      }

      string system::matter(::ca::application * papp, const stringa & stra, bool bDir)
      {

         ::index j;

         ::count c = stra.get_count();

         if(c <= 0)
            return "";

         ::user::str_context * pcontext = App(papp).str_context();

         string strLocale;
         
         string strSchema;
         
         string strLs;

         string strPath;

#ifdef MATTER_CACHE_FROM_HTTP_SERVER

         string strFile;

         {


            stringa straPath;

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            strLs      = locale_schema_matter(papp, strLocale, strSchema);

            strFile = System.dir().appdata(path("cache", papp->m_pappThis->get_locale_schema_dir(strLocale, strSchema), stra.implode(",") + ".map_question"));

            strsize iFind = strFile.find(DIR_SEPARATOR);

            if(iFind > 0)
            {
               
               strFile.replace(":", "_", iFind + 1);

            }

            strPath = Application.file().as_string(strFile);

            if(strPath.has_char())
            {
               // todo: keep cache timeout information;
               return strPath;
            }

            for(j = 0; j < c; j++)
            {

               straPath.add(path(strLs, stra[j]));

            }
         
            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {

               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               strLs             = locale_schema_matter(papp, strLocale, strSchema);

               for(j = 0; j < c; j++)
               {

                  straPath.add(path(strLs, stra[j]));

               }

            }

            strLs      = locale_schema_matter(papp, "en", "en");
            straPath.add(path(strLs, stra[0]));

            if(bDir)
            {
               strPath = System.http().get("http://api-matter.ca.cc/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")));
            }
            else
            {
               strPath = System.http().get("http://api-matter.ca.cc/query_file?candidate=" + System.url().url_encode(straPath.implode("|")));
            }

            if(strPath.has_char())
               goto ret;

         }

#else
         
         {

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            strLs      = locale_schema_matter(papp, strLocale, strSchema);

            for(j = 0; j < c; j++)
            {

               strPath = path(strLs, stra[j]);

               if(bDir)
               {
                  if(System.dir().is(strPath, get_app()))
                     return strPath;
               }
               else
               {
                  if(System.file().exists(strPath, get_app()))
                     return strPath;
               }

            }


            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {

               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               strLs             = locale_schema_matter(papp, strLocale, strSchema);

               for(j = 0; j < c; j++)
               {

                  strPath = path(strLs, stra[j]);

                  if(bDir)
                  {
                     if(System.dir().is(strPath, get_app()))
                        return strPath;
                  }
                  else
                  {
                     if(System.file().exists(strPath, get_app()))
                        return strPath;
                  }

               }

            }

         }

#endif

         strLs = locale_schema_matter(papp, "en", "en");

         for(j = 0; j < c; j++)
         {

            strPath = path(strLs, stra[j]);

            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }

         }


         if(papp->m_psession != NULL && papp->m_psession != papp &&
            (::ca::application *) papp->m_psystem != (::ca::application *) papp)
         {
            strPath = matter(papp->m_psession, stra, bDir);
            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }
         }

         if(papp->m_psystem != NULL && papp->m_psystem != papp &&
            (::ca::application *) papp->m_psystem != (::ca::application *) papp->m_psession)
         {
            strPath = matter(papp->m_psystem, stra, bDir);
            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }
         }

         strPath = path(strLs, stra[0]);

ret:

#ifdef MATTER_CACHE_FROM_HTTP_SERVER

         Application.file().put_contents(strFile, strPath);
#endif

         return strPath;

      }

      string system::matter(::ca::application * papp, const char * psz, const char * psz2, bool bDir)
      {
         return matter(papp, string(psz), string(psz2), bDir);
      }

      string system::matter(::ca::application * papp, const string & str, const char * psz, bool bDir)
      {
         return matter(papp, str, string(psz), bDir);
      }

      string system::matter(::ca::application * papp, const char * psz, const string & str, bool bDir)
      {
         return matter(papp, string(psz), str, bDir);
      }


      string system::matter(::ca::application * papp, const string & str, const string & str2, bool bDir)
      {

         ::user::str_context * pcontext = App(papp).str_context();

         string strLocale;
         
         string strSchema;
         
         string strLs;

         string strPath;

#ifdef MATTER_CACHE_FROM_HTTP_SERVER

         string strFile;

         {


            stringa straPath;

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            strLs      = locale_schema_matter(papp, strLocale, strSchema);

            strFile = System.dir().appdata(path("cache", papp->m_pappThis->get_locale_schema_dir(strLocale, strSchema), str + ca::str::has_char(str2, ",") + ".map_question"));

            strsize iFind = strFile.find(DIR_SEPARATOR);

            if(iFind > 0)
            {
               
               strFile.replace(":", "_", iFind + 1);

            }

            strPath = Application.file().as_string(strFile);

            if(strPath.has_char())
            {
               // todo: keep cache timeout information;
               return strPath;
            }



            straPath.add(path(strLs, str, str2));
         
            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {
               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               strLs             = locale_schema_matter(papp, strLocale, strSchema);
               straPath.add(path(strLs, str, str2));
            }
            
            strLs             = locale_schema_matter(papp, "en", "en");
            straPath.add(path(strLs, str, str2));
            
            if(bDir)
            {
               strPath = System.http().get("http://api-matter.ca.cc/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")));
            }
            else
            {
               strPath = System.http().get("http://api-matter.ca.cc/query_file?candidate=" + System.url().url_encode(straPath.implode("|")));
            }

            if(strPath.has_char())
               goto ret;

         }

#else

         {

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            strLs      = locale_schema_matter(papp, strLocale, strSchema);
            strPath           = path(strLs, str, str2);
            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }


            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {

               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               strLs             = locale_schema_matter(papp, strLocale, strSchema);
               strPath           = path(strLs, str, str2);
               if(bDir)
               {
                  if(System.dir().is(strPath, get_app()))
                     goto ret;
               }
               else
               {
                  if(System.file().exists(strPath, get_app()))
                     goto ret;
               }

            }


            strLs             = locale_schema_matter(papp, "en", "en");
            strPath           = path(strLs, str, str2);
            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }


            if(papp->m_psession != NULL && papp->m_psession != papp &&
               (::ca::application *) papp->m_psystem != (::ca::application *) papp)
            {
               strPath = matter(papp->m_psession, str, str2);
               if(bDir)
               {
                  if(System.dir().is(strPath, get_app()))
                     goto ret;
               }
               else
               {
                  if(System.file().exists(strPath, get_app()))
                     goto ret;
               }
            }

         }

#endif


         if(papp->m_psystem != NULL && papp->m_psystem != papp &&
            (::ca::application *) papp->m_psystem != (::ca::application *) papp->m_psession)
         {
            strPath = matter(papp->m_psystem, str, str2);
            if(bDir)
            {
               if(System.dir().is(strPath, get_app()))
                  goto ret;
            }
            else
            {
               if(System.file().exists(strPath, get_app()))
                  goto ret;
            }

         }

         strPath = path(strLs, str, str2);

ret:

#ifdef MATTER_CACHE_FROM_HTTP_SERVER

         Application.file().put_contents(strFile, strPath);
#endif

         return strPath;


         /*static const string strEn("en");
         static const string strStd("_std");
         static const string strEmpty("");
         string strPath;
         string strLs = locale_schema_matter(papp, strEmpty, strEmpty);
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strLs = locale_schema_matter(papp, strEn, strEmpty);
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, strStd, strEmpty), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, strEmpty, App(papp).get_locale()), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, strEmpty, strEn), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, strEmpty, strStd), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strLs = locale_schema_matter(papp, strEn, strEn);
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, strStd, strStd), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         strPath = path(locale_schema_matter(papp, "se", "se"), str, str2);
         if(System.file().exists(strPath, papp))
            return strPath;
         if(papp->m_psession != NULL && papp->m_psession != papp &&
            (::ca::application *) papp->m_psystem != (::ca::application *) papp)
         {
            strPath = matter(papp->m_psession, str, str2);
            if(System.file().exists(strPath, papp))
               return strPath;
         }
         if(papp->m_psystem != NULL && papp->m_psystem != papp &&
            (::ca::application *) papp->m_psystem != (::ca::application *) papp->m_psession)
         {
            strPath = matter(papp->m_psystem, str, str2);
            if(System.file().exists(strPath, papp))
               return strPath;
         }
         return path(locale_schema_matter(papp, strEmpty, strEmpty), str, str2);*/
      }

      string system::matter(::ca::application * papp, const char * psz, bool bDir)
      {
         string str(psz);
         string str2;
         return matter(papp, str, str2, bDir);
      }

      string system::matter(::ca::application * papp, const string & str, bool bDir)
      {
         string str2;
         return matter(papp, str, str2, bDir);
      }

      string system::matter(::ca::application * papp)
      {
         string str;
         string str2;
         return matter(papp, str, str2);
      }

      string system::matter_from_locator(::user::str_context * pcontext, const string & strLocator)
      {
         string str;


         string str2;

         return matter_from_locator(pcontext, strLocator, str, str2);

      }

      string system::matter_from_locator(::user::str_context * pcontext, const string & strLocator, const string & str)
      {

         string str2;

         return matter_from_locator(pcontext, strLocator, str, str2);

      }

      /* static const string strEn("en");
         static const string strStd("_std");
         static const string strEmpty("");

         string strPath;
         string strLs = locale_schema_matter(strLocator, App(papp).get_locale(), App(papp).get_style());
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strLs = locale_schema_matter(strLocator, strEn, App(papp).get_style());
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, strStd, App(papp).get_style()), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, App(papp).get_locale(), App(papp).get_locale()), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, App(papp).get_locale(), strEn), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, App(papp).get_locale(), strStd), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strLs = locale_schema_matter(strLocator, strEn, strEn);
         strPath = path(strLs, str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, strStd, strStd), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
      */

      string system::matter_from_locator(::user::str_context * pcontext, const string & strLocator,  const string & str, const string & str2)
      {

         string strPath;

         string strLocale  = pcontext->m_plocaleschema->m_idLocale;
         string strSchema   = pcontext->m_plocaleschema->m_idSchema;
         string strLs      = locale_schema_matter(strLocator, strLocale, strSchema);
         strPath           = path(strLs, str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;


         for(int32_t i = 0; i < pcontext->m_plocaleschema->m_idaLocale.get_count(); i++)
         {

            strLocale         = pcontext->m_plocaleschema->m_idaLocale[i];
            strSchema          = pcontext->m_plocaleschema->m_idaSchema[i];
            strLs             = locale_schema_matter(strLocator, strLocale, strSchema);
            strPath           = path(strLs, str, str2);
            if(System.file().exists(strPath, get_app()))
               return strPath;

         }


         strLs             = locale_schema_matter(strLocator, "en", "en");
         strPath           = path(locale_schema_matter(strLocator, "se", "se"), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;


         return path(strLs, str, str2);


      }

      void system::appmatter_locators(string & strRoot, string & strDomain, ::ca::application * papp)
      {

         if(papp->is_system())
         {
            strRoot     = "app";
            strDomain   = "main";
         }
         else if(papp->is_bergedge())
         {
            strRoot     = "app";
            strDomain   = "bergedge";
         }
         else
         {
            appmatter_locators(strRoot, strDomain, papp->m_pappThis->m_strLibraryName, papp->m_pappThis->m_strAppId);
         }

      }

      void system::appmatter_locators(string & strRoot, string & strDomain, const string & strAppName)
      {

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

      }

      void system::appmatter_locators(string & strRoot, string & strDomain, const string & strLibraryNameParam, const string & strAppNameParam)
      {

         strsize iFind = strAppNameParam.find('/');

         if(iFind < 0)
            return;

         strRoot = strAppNameParam.Left(iFind);

         strsize iFind2 = strAppNameParam.find('/', iFind + 1);

         if(iFind2 > iFind + 1)
         {
            strDomain = "_" + strAppNameParam.Mid(iFind + 1);
            return;
         }
         else
         {
            strDomain = strAppNameParam.Mid(iFind + 1);
         }


         /*string strLibraryRoot;
         string strLibraryName;
         if(strLibraryNameParam.has_char() && strLibraryNameParam != "app_" + strAppNameParam
            && ca::str::begins_ci(strLibraryNameParam, "app_") && strLibraryNameParam.find("_", strlen("app_")) > 4)
         {
            stringa stra2;
            stra2.add_tokens(strLibraryNameParam, "_", FALSE);
            strLibraryRoot = stra2[1];
            strLibraryName = stra2.implode("_", 2);
         }
         else
         {
            strLibraryName = strLibraryNameParam;
         }

         int32_t iFind = strAppNameParam.find("/");

         if(iFind > 0)
         {

            strRoot = strAppNameParam.Left(iFind);

         }
         else if(strLibraryRoot.has_char())
         {

            strRoot = "app-" + strLibraryRoot;

         }
         else
         {

            strRoot = "app";

         }

         if(iFind > 0)
         {

            int32_t iFind2 = strAppNameParam.find('/', iFind + 1);

            if(iFind2 < 0)
            {

               strDomain = strAppNameParam.Mid(iFind + 1);

            }
            else
            {

               strDomain = "_" + strAppNameParam.Mid(iFind + 1);

            }


         }
         else
         {

            strDomain += strAppNameParam;

         }

         */
      }

      string system::appmatter_locator(::ca::application * papp)
      {
#if defined(METROWIN) || defined(MACOS)
         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, papp);

         return path("http://matter.ca.cc/", path(strRoot, "appmatter", strDomain));
#else
         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, papp);

         return ca(simple_path(strRoot, "appmatter", strDomain));
#endif

      }

      string system::appmatter_locator(const string & strLibraryName, const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, strLibraryName, strAppName);

         return ca(simple_path(strRoot, "appmatter", strDomain));

      }

      string system::appmatter_locator(const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

         return ca(simple_path(strRoot, "appmatter", strDomain));

      }

      string system::base_appmatter_locator(const string & strBase, const string & strLibraryName, const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, strLibraryName, strAppName);

         return path(strBase, simple_path(strRoot, "appmatter", strDomain));

      }

      string system::base_appmatter_locator(const string & strBase, const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

         return path(strBase, simple_path(strRoot, "appmatter", strDomain));

      }


      class ::ca::path & system::path()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::initialize()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::trash_that_is_not_trash(const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::appdata(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userappdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userfolder(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_os_user_path_prefix(::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userquicklaunch(::ca::application * papp, const char * lpcszRelativePath, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszRelativePath);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userprograms(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::commonprograms(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_inside_time(const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_inside(const char * pszDir, const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::sensitive_ccvotagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         return path(ca("ccvotagus"), lpcsz, lpcsz2);
      }

      string system::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode, ::ca::application * papp)
      {

         stringa stra;

         stra.add_tokens(pszEnv, ":", false);

         string strCandidate;

         for(int32_t i = 0; i < stra.get_count(); i++)
         {

            strCandidate = path(stra[i], pszTopic);

            if(App(papp).file().exists(strCandidate))
            {
               return strCandidate;
            }

         }

         return "";

      }


   }  // namespace dir

} // namespace ca
