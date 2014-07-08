#include "framework.h"


#ifdef WINDOWS

#define DIR_SEPARATOR "\\"

#else

#define DIR_SEPARATOR "/"

#endif


namespace file
{


   bool path::is_equal(const char * lpcsz1, const char * lpcsz2)
   {
      UNREFERENCED_PARAMETER(lpcsz1);
      UNREFERENCED_PARAMETER(lpcsz2);
      throw interface_only_exception(get_app(), "this is an interface");
   }


   namespace dir
   {


      system::system(sp(::base::application) papp) :
         ::element(papp),
         m_mutex(papp),
         m_isdirmap(papp)
      {
//         m_pziputil = new zip::Util;
         m_isdirmap.m_dwTimeOut = 15000;
      }

      system::~system()
      {
         if(m_pziputil != NULL)
         {
//            delete m_pziputil;
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

      string system::path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, bool bUrl)
      {

         return path(pszFolder, iLenFolder, pszRelative, iLenRelative, NULL, 0, bUrl);

      }

      string system::path(const char * pszFolder, strsize iLenFolder, const char * pszRelative, strsize iLenRelative, const char * psz2, strsize iLen2)
      {

         return path(pszFolder, iLenFolder, pszRelative, iLenRelative, psz2, iLen2, ::url::is_url(pszFolder));

      }

      string system::path(const string & strFolder, const string & strRelative)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), NULL, 0, ::url::is_url(strFolder));

      }


      string system::path(const string & strFolder, const string & strRelative, const string & str2)
      {

         return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), str2, str2.get_length(), ::url::is_url(strFolder));

      }

      string system::path(const string & strFolder, const string & strRelative, const char * psz2)
      {
         if(psz2 == NULL)
         {
            return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), ::url::is_url(strFolder));
         }
         else
         {
            return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), psz2, strlen(psz2), ::url::is_url(strFolder));
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
            //::str::ends_eat(strFolder, "\\");
            //::str::ends_eat(strFolder, "/");
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
            //::str::ends_eat(strFolder, "\\");
            //::str::ends_eat(strFolder, "/");
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
            #if defined(LINUX) || defined(APPLEOS)
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
            //::str::ends_eat(strFolder, "\\");
            //::str::ends_eat(strFolder, "/");
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
            //::str::ends_eat(strFolder, "\\");
            //::str::ends_eat(strFolder, "/");
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
            //::str::ends_eat(strFolder, "\\");
            //::str::ends_eat(strFolder, "/");
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
               #if defined(LINUX) || defined(APPLEOS)
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
            #if defined(LINUX) || defined(APPLEOS)
            string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
            #else
            string_STRCAT2_beg_char_end(strPath, '/', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
            #endif
            return strPath;
         }

         string strPath;

         char * psz = strPath.GetBufferSetLength(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
         strncpy(psz, &((const char *)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
         #if defined(LINUX) || defined(APPLEOS)
         psz[iFolderEnd - iFolderBeg + 1] = '/';
         #else
         psz[iFolderEnd - iFolderBeg + 1] = '\\';
         #endif
         strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const char *)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
         #if defined(LINUX) || defined(APPLEOS)
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

      void system::root_ones(stringa & straPath, stringa & straTitle, sp(::base::application) papp)
      {
         UNREFERENCED_PARAMETER(straPath);
         UNREFERENCED_PARAMETER(straTitle);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::rls_pattern(sp(::base::application) papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, bool_array * pbaIsDir, int64_array * piaSize, e_extract eextract)
      {
         UNREFERENCED_PARAMETER(pstraRelative);
         UNREFERENCED_PARAMETER(pszPattern);
         if(eextract != extract_none && papp->m_bZipIsDir && (::str::ends_ci(lpcsz, ".zip") || ::str::find_ci(".zip:", lpcsz) >= 0))
         {
            throw "should implement recursive zip";
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize, eextract == extract_all ? extract_all : extract_none);
            return;
         }
         throw not_implemented(get_app(), "is really a directory or compressed directory/file??");

      }


      void system::ls_pattern(sp(::base::application) papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, int64_array * piaSize)
      {
         UNREFERENCED_PARAMETER(pszPattern);
         if(::str::begins_ci(lpcsz, "http://") || ::str::begins_ci(lpcsz, "https://"))
         {

            property_set set(get_app());

            string str = App(papp).http().get(lpcsz, set);

            if(pstraPath != NULL)
            {

               pstraPath->add_tokens(str, "\n", false);

            }

            return;

         }
         if(papp->m_bZipIsDir && (::str::ends_ci(lpcsz, ".zip") || ::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented(get_app(), "is really a directory or compressed directory/file??");

      }

      void system::ls(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, bool_array * pbaIsDir, int64_array * piaSize)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pbaIsDir);
         UNREFERENCED_PARAMETER(piaSize);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::rls(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, e_extract eextract)
      {
         if(eextract != extract_none && papp->m_bZipIsDir && (::str::ends_ci(lpcsz, ".zip") || ::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, pstraRelative, NULL, NULL, eextract == extract_all ? extract_all : extract_none);
            return;
         }
         else
         {
            return;
         }
      }

      void system::rls_dir(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pstraRelative);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::ls_dir(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         if(papp->m_bZipIsDir && (::str::ends_ci(lpcsz, ".zip") || ::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls_dir(papp, lpcsz, pstraPath, pstraTitle);
            return;
         }
         else
         {
            return;
         }
      }

      bool system::has_subdir(sp(::base::application) papp, const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      void system::ls_file(sp(::base::application) papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_or_definitively_not(bool & bIs, const char * lpcszPath, sp(::base::application) papp)
      {

         bIs = false;

         if (::str::begins_ci(lpcszPath, "http://") || ::str::begins_ci(lpcszPath, "https://"))
         {

            property_set set(get_app());

            bIs = App(papp).http().exists(lpcszPath, set);

            return true;

         }

         if (papp->m_bZipIsDir && (::str::ends_ci(lpcszPath, ".zip")))
         {

            bIs = true;

            return true;
         }

         if (papp->m_bZipIsDir && (::str::find_ci(".zip:", lpcszPath) >= 0))
         {

            bool bHasSubFolder;

            uint32_t dwLastError;

            if (m_isdirmap.lookup(lpcszPath, bHasSubFolder, dwLastError))
            {

               bIs = bHasSubFolder;

               return true;

            }

            bHasSubFolder = m_pziputil->HasSubFolder(papp, lpcszPath);

            m_isdirmap.set(lpcszPath, bHasSubFolder, ::GetLastError());

            bIs = bHasSubFolder;

            return true;

         }

#ifdef WINDOWSEX
#ifdef WINDOWSEX
         if(::str::ends_ci(lpcszPath,".lnk"))
         {
#endif

            string strTarget;

            if(System.os().resolve_link(strTarget,lpcszPath))
            {

               bIs = is(strTarget,papp);

               return true;

            }

#ifdef WINDOWSEX
         }
#endif
#endif

         return false;

      }


      bool system::is(const char * lpcszPath, sp(::base::application) papp)
      {

         bool bIs;

         if (!is_or_definitively_not(bIs, lpcszPath, papp) || !bIs)
            return false;

         return true;

      }

      bool system::is(const string & strPath, sp(::base::application) papp)
      {

         if(::str::begins_ci(strPath, "http://") || ::str::begins_ci(strPath, "https://"))
         {

            property_set set(get_app());

            return App(papp).http().exists(strPath, set);

         }


         if(papp->m_bZipIsDir && (::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if(papp->m_bZipIsDir && (::str::find_ci(".zip:", strPath) >= 0))
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

      bool system::is(const var & var, sp(::base::application) papp)
      {
         return is((const string &) var, papp);
      }

      bool system::name_is(const char * lpcszPath, sp(::base::application) papp)
      {
         return name_is((const string &) lpcszPath, papp);
      }

      bool system::name_is(const string & strPath, sp(::base::application) papp)
      {
         //OutputDebugString(strPath);
         if(papp->m_bZipIsDir && (::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if(papp->m_bZipIsDir && (::str::find_ci(".zip:", strPath) >= 0))
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

      bool system::name_is(const var & var, sp(::base::application) papp)
      {
         return name_is((const string &) var, papp);
      }


      system::is_dir_map::is_dir_map(sp(::base::application) papp) :
         string_map < is_dir >(papp, 256), // block size
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

#if defined(LINUX) || defined(APPLEOS)
         if(strLookup.last_char() != '\\' && strLookup.last_char() != '/' )
            strLookup += "/";
#else
         if(strLookup.last_char() != '\\' && strLookup.last_char() != '/' )
            strLookup += "\\";
#endif

         single_lock sl(&m_mutex, TRUE);

         string_map < is_dir >::pair * ppair = this->PLookup(strLookup);

         if(ppair == NULL)
            return false;

         if(::get_tick_count() > ppair->m_element2.m_dwLastCheck + m_dwTimeOut)
         {
            return false;
         }

         bIsDir = ppair->m_element2.m_bIsDir;

         dwLastError = ppair->m_element2.m_dwError;

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

         string_map < is_dir >::pair * ppair = this->PLookup(strLookup);

         if(ppair == NULL)
            return false;

         if(::get_tick_count() > ppair->m_element2.m_dwLastCheck + m_dwTimeOut)
         {
            return false;
         }

         bIsDir = ppair->m_element2.m_bIsDir;

         dwLastError = ppair->m_element2.m_dwError;

         return true;

      }

      void system::is_dir_map::set(const char * pszPath, bool bIsDir, uint32_t dwLastError)
      {
#if defined(LINUX) || defined(APPLEOS)
         static const char * strSep = "/";
#else
         static const char * strSep = "\\";
#endif
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwError = dwLastError;
         isdir.m_dwLastCheck = ::get_tick_count();
         string strPath(pszPath);
         if(!::str::ends(strPath, strSep))
            strPath += strSep;
         single_lock sl(&m_mutex, TRUE);
         set_at(strPath, isdir);
      }

      void system::is_dir_map::set(const string & strPath, bool bIsDir, uint32_t dwLastError)
      {
#if defined(LINUX) || defined(APPLEOS)
         static const char * strSep = "/";
#else
         static const char * strSep = "\\";
#endif
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwError = dwLastError;
         isdir.m_dwLastCheck = ::get_tick_count();
         if(::str::ends(strPath, strSep))
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

      string system::element(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::element(const string & str, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::element(const char * lpcsz, const string & str2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::element(const string & str, const string & str2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::element(const string & str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::element()
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

      bool system::mk(const char * lpcsz, sp(::base::application) papp)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::rm(sp(::base::application) papp, const char * psz, bool bRecursive)
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

      string system::locale_schema(sp(::base::application) papp, const string & strLocale, const string & strSchema)
      {

         return papp->get_locale_schema_dir(strLocale, strSchema);

      }

      stringa system::locale_schema_matter(sp(::base::application) papp, const string & strLocale, const string & strSchema, const char * pszRoot, const char * pszApp)
      {

         //single_lock sl(&papp->m_mutexMatterLocator, true);
         if (pszRoot != NULL && pszApp != NULL)
         {

            string strRoot(pszRoot);

            string strDomain(pszApp);

            if(BaseSession.m_bMatterFromHttpCache)
            {

               return path(simple_path(strRoot,"appmatter",strDomain),papp->get_locale_schema_dir(strLocale,strSchema));
            }
            else
            {
               return path(element(simple_path(strRoot,"appmatter",strDomain)),papp->get_locale_schema_dir(strLocale,strSchema));

            }

         }
         else
         {

            stringa stra;

            for (index i = 0; i < papp->m_straMatterLocator.get_count(); i++)
            {

               stra.add_unique(path(papp->m_straMatterLocator[i], papp->get_locale_schema_dir(strLocale, strSchema)));

            }

            return stra;

         }


      }

      stringa system::locale_schema_matter(const string & strLocator, const string & strLocale, const string & strSchema)
      {

         return path(strLocator, simple_path(strLocale, strSchema));

      }

      void system::matter_ls(sp(::base::application) papp, const string & str, stringa & stra)
      {

         string strDir = matter(papp, str, true);

         ls(papp, strDir, &stra);

      }

      void system::matter_ls_file(sp(::base::application) papp, const string & str, stringa & stra)
      {

         string strDir = matter(papp, str, true);

         if(BaseSess(papp).m_bMatterFromHttpCache)
         {

            property_set set(get_app());

            string strLs = App(papp).http().get("http://" + get_api_cc() + "/api/matter/list_dir?dir=" + System.url().url_encode(strDir),set);

            stringa straLs;

            stringa straSep;

            straSep.add("\r");
            straSep.add("\n");
            straSep.add("\r\n");

            straLs.add_smallest_tokens(strLs,straSep,false);

            for(index i = 0; i < straLs.get_count(); i++)
            {

               if(!::str::ends(straLs[i],"/"))
               {
                  string strPath  = System.dir().path(strDir,straLs[i]);
                  stra.add(strPath);
               }

            }

         }
         else
         {
            
            ls_file(papp,strDir,&stra);

         }
         

      }

      string system::matter(sp(::base::application) papp, const stringa & stra, bool bDir, const char * pszRoot, const char * pszApp)
      {

         ::user::str_context * pcontext = App(papp).str_context();

         ::index j;

         ::count ca = stra.get_count();

         string strPath;

         string strLocale;

         string strSchema;

         stringa straLs;

         string strLs;

         string strFile;

         if (pszRoot != NULL && pszApp != NULL && *pszRoot != '\0' && *pszApp != '\0')
         {

            string strRoot(pszRoot);

            string strApp(pszApp);

            ::index j;

            ::count ca = stra.get_count();

            if (ca <= 0)
               return "";

            ::user::str_context * pcontext = App(papp).str_context();

            string strFile;

            if(BaseSession.m_bMatterFromHttpCache)
            {


               stringa straPath;

               strLocale = pcontext->m_plocaleschema->m_idLocale;
               strSchema = pcontext->m_plocaleschema->m_idSchema;
               straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

               for(index l = 0; l < straLs.get_count(); l++)
               {

                  strLs = straLs[l];

                  strFile = System.dir().commonappdata(path("cache", papp->get_locale_schema_dir(strLocale, strSchema), stra.implode(",") + ".map_question"));

                  strsize iFind = strFile.find(DIR_SEPARATOR);

                  if (iFind > 0)
                  {

                     strFile.replace(":", "_", iFind + 1);

                  }

                  strPath = Application.file().as_string(strFile);

                  if (strPath.has_char())
                  {
                     // todo: keep cache timeout information;
                     return strPath;
                  }

                  for (j = 0; j < ca; j++)
                  {

                     straPath.add(path(strLs, stra[j]));

                  }

                  for (int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
                  {

                     strLocale = pcontext->localeschema().m_idaLocale[i];
                     strSchema = pcontext->localeschema().m_idaSchema[i];
                     straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

                     for(int k = 0; k < straLs.get_count(); k++)
                     {

                        string strLd = straLs[k];

                        for (j = 0; j < ca; j++)
                        {

                           straPath.add(path(strLs, stra[j]));

                        }

                     }

                  }

                  straLs = locale_schema_matter(papp, "en", "en");
                  for(int k = 0; k < straLs.get_count(); k++)
                  {

                     string strLd = straLs[k];

                     straPath.add(path(strLs, stra[0]));

                  }

                  property_set set(papp);

                  if (bDir)
                  {
                     strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")), set);
                  }
                  else
                  {
                     strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_file?candidate=" + System.url().url_encode(straPath.implode("|")), set);
                  }

                  if (strPath.has_char())
                     goto ret;

               }

            }

            else
            {

               strLocale = pcontext->m_plocaleschema->m_idLocale;
               strSchema = pcontext->m_plocaleschema->m_idSchema;
               straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

               for (index l = 0; l < straLs.get_count(); l++)
               {
                  strLs = straLs[l];

                  for (j = 0; j < ca; j++)
                  {

                     strPath = path(strLs, stra[j]);

                     if (bDir)
                     {
                        if (System.dir().is(strPath, get_app()))
                           return strPath;
                     }
                     else
                     {
                        if (System.file().exists(strPath, get_app()))
                           return strPath;
                     }

                  }


                  for (int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
                  {

                     strLocale = pcontext->localeschema().m_idaLocale[i];
                     strSchema = pcontext->localeschema().m_idaSchema[i];
                     straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

                     for (index l = 0; l < straLs.get_count(); l++)
                     {
                        strLs = straLs[l];

                        for (j = 0; j < ca; j++)
                        {

                           strPath = path(strLs, stra[j]);

                           if (bDir)
                           {
                              if (System.dir().is(strPath, get_app()))
                                 return strPath;
                           }
                           else
                           {
                              if (System.file().exists(strPath, get_app()))
                                 return strPath;
                           }

                        }

                     }

                  }

               }

            }




            straLs = locale_schema_matter(papp, "en", "en", strRoot, strApp);

            for (index l = 0; l < straLs.get_count(); l++)
            {

               strLs = straLs[l];

               for (j = 0; j < ca; j++)
               {

                  strPath = path(strLs, stra[j]);

                  if (bDir)
                  {
                     if (System.dir().is(strPath, get_app()))
                        goto ret;
                  }
                  else
                  {
                     if (System.file().exists(strPath, get_app()))
                        goto ret;
                  }

               }


            }


            if (ca <= 0)
               return "";

         }


         if(BaseSession.m_bMatterFromHttpCache)

         {


            stringa straPath;

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            straLs      = locale_schema_matter(papp, strLocale, strSchema);

            for(index l = 0; l < straLs.get_count(); l++)
            {
               strLs = straLs[l];

               strFile = System.dir().commonappdata(path("cache", papp->get_locale_schema_dir(strLocale, strSchema), stra.implode(",") + ".map_question"));

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

               for(j = 0; j < ca; j++)
               {

                  straPath.add(path(strLs, stra[j]));

               }

               for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
               {

                  strLocale         = pcontext->localeschema().m_idaLocale[i];
                  strSchema         = pcontext->localeschema().m_idaSchema[i];
                  straLs             = locale_schema_matter(papp, strLocale, strSchema);
                  for(int k = 0; k < straLs.get_count(); k++)
                  {

                     strLs = straLs[k];

                     for(j = 0; j < ca; j++)
                     {

                        straPath.add(path(strLs, stra[j]));

                     }

                  }

               }

               straLs      = locale_schema_matter(papp, "en", "en");
               for(int k = 0; k < straLs.get_count(); k++)
               {

                  strLs = straLs[k];
                  straPath.add(path(strLs, stra[0]));
               }

               property_set set(papp);

               if(bDir)
               {
                  strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")), set);
               }
               else
               {
                  strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_file?candidate=" + System.url().url_encode(straPath.implode("|")), set);
               }

               if(strPath.has_char())
                  goto ret;

            }

         }

else

            {

               strLocale = pcontext->m_plocaleschema->m_idLocale;
               strSchema = pcontext->m_plocaleschema->m_idSchema;
               straLs = locale_schema_matter(papp, strLocale, strSchema);


               for (index l = 0; l < straLs.get_count(); l++)
               {

                  strLs = straLs[l];

                  for (j = 0; j < ca; j++)
                  {

                     strPath = path(strLs, stra[j]);

                     if (bDir)
                     {
                        if (System.dir().is(strPath, get_app()))
                           return strPath;
                     }
                     else
                     {
                        if (System.file().exists(strPath, get_app()))
                           return strPath;
                     }

                  }

               }


               for (int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
               {

                  strLocale = pcontext->localeschema().m_idaLocale[i];
                  strSchema = pcontext->localeschema().m_idaSchema[i];
                  straLs = locale_schema_matter(papp, strLocale, strSchema);

                  for (index l = 0; l < straLs.get_count(); l++)
                  {

                     strLs = straLs[l];

                     for (j = 0; j < ca; j++)
                     {

                        strPath = path(strLs, stra[j]);

                        if (bDir)
                        {
                           if (System.dir().is(strPath, get_app()))
                              return strPath;
                        }
                        else
                        {
                           if (System.file().exists(strPath, get_app()))
                              return strPath;
                        }

                     }

                  }

               }

            }


            straLs = locale_schema_matter(papp, "en", "en");

            for (index l = 0; l < straLs.get_count(); l++)
            {

               strLs = straLs[l];


               for (j = 0; j < ca; j++)
               {

                  strPath = path(strLs, stra[j]);

                  if (bDir)
                  {
                     if (System.dir().is(strPath, get_app()))
                        goto ret;
                  }
                  else
                  {
                     if (System.file().exists(strPath, get_app()))
                        goto ret;
                  }

               }

            }


            if (papp->m_pbasesession != NULL && papp->m_pbasesession != papp &&
               (sp(::base::application)) papp->m_pbasesystem != (sp(::base::application)) papp)
            {
               strPath = matter(papp->m_pbasesession, stra, bDir);
               if (bDir)
               {
                  if (System.dir().is(strPath, get_app()))
                     goto ret;
               }
               else
               {
                  if (System.file().exists(strPath, get_app()))
                     goto ret;
               }
            }

            if (papp->m_pbasesystem != NULL && papp->m_pbasesystem != papp &&
               (sp(::base::application)) papp->m_pbasesystem != (sp(::base::application)) papp->m_pbasesession)
            {
               strPath = matter(papp->m_pbasesystem, stra, bDir);
               if (bDir)
               {
                  if (System.dir().is(strPath, get_app()))
                     goto ret;
               }
               else
               {
                  if (System.file().exists(strPath, get_app()))
                     goto ret;
               }
            }

            strPath = path(strLs, stra[0]);

         ret:

            if(BaseSession.m_bMatterFromHttpCache)
            {
               Application.file().put_contents(strFile,strPath);
            }

            return strPath;

      }

      string system::matter(sp(::base::application) papp, const char * psz, const char * psz2, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return matter(papp, string(psz), string(psz2), bDir, pszRoot, pszApp);
      }

      string system::matter(sp(::base::application) papp, const string & str, const char * psz, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return matter(papp, str, string(psz), bDir, pszRoot, pszApp);
      }

      string system::matter(sp(::base::application) papp, const char * psz, const string & str, bool bDir, const char * pszRoot, const char * pszApp)
      {
         return matter(papp, string(psz), str, bDir, pszRoot, pszApp);
      }


      string system::matter(sp(::base::application) papp, const string & str, const string & str2, bool bDir, const char * pszRoot, const char * pszApp)
      {

         ::user::str_context * pcontext = App(papp).str_context();

         string strLocale;

         string strSchema;

         string strLs;

         string strPath;
         
         string strFile;

         stringa straLs;

         string strExistsQuestion;
         
         if (pszRoot != NULL && pszApp != NULL && *pszRoot != '\0' && *pszApp != '\0')
         {

            string strRoot(pszRoot);

            string strApp(pszApp);


            if(BaseSession.m_bMatterFromHttpCache)

            {


               stringa straPath;

               strLocale = pcontext->m_plocaleschema->m_idLocale;
               strSchema = pcontext->m_plocaleschema->m_idSchema;
               straLs = locale_schema_matter(papp, strLocale, strSchema, pszRoot, pszApp);

               strFile = System.dir().commonappdata(path("cache", papp->get_locale_schema_dir(strLocale, strSchema), str + ::str::has_char(str2, ",") + ".map_question"));

               strsize iFind = strFile.find(DIR_SEPARATOR);

               if (iFind > 0)
               {

                  strFile.replace(":", "_", iFind + 1);

               }

               strPath = Application.file().as_string(strFile);

               if (strPath.has_char())
               {
                  // todo: keep cache timeout information;
                  return strPath;
               }


               for(int k = 0; k < straLs.get_count(); k++)
               {

                  strLs = straLs[k];

                  straPath.add(path(strLs, str, str2));
               }

               for (int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
               {
                  strLocale = pcontext->localeschema().m_idaLocale[i];
                  strSchema = pcontext->localeschema().m_idaSchema[i];
                  straLs = locale_schema_matter(papp, strLocale, strSchema, pszRoot, pszApp);
                  for(int k = 0; k < straLs.get_count(); k++)
                  {

                     strLs = straLs[k];

                     straPath.add(path(strLs, str, str2, true));
                  }
               }

               straLs = locale_schema_matter(papp, "en", "en");
               for(int k = 0; k < straLs.get_count(); k++)
               {

                  strLs = straLs[k];

                  straPath.add(path(strLs, str, str2));
               }

               property_set set(papp);

               set["raw_http"] = true;

               if (bDir)
               {
                  strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")), set);
               }
               else
               {
                  strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_file?candidate=" + System.url().url_encode(straPath.implode("|")), set);
               }

               strPath.trim();

               if (strPath.has_char())
                  goto ret;

            }

else

            {

               strLocale = pcontext->m_plocaleschema->m_idLocale;
               strSchema = pcontext->m_plocaleschema->m_idSchema;
               straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

               for (index l = 0; l < straLs.get_count(); l++)
               {
                  strLs = straLs[l];

                  strPath = path(strLs, str, str2);
                  if (bDir)
                  {
                     if (System.dir().is(strPath, papp))
                        goto ret;
                  }
                  else
                  {
                     if (System.file().exists(strPath, papp))
                        goto ret;
                  }

               }


               for (int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
               {

                  strLocale = pcontext->localeschema().m_idaLocale[i];
                  strSchema = pcontext->localeschema().m_idaSchema[i];
                  straLs = locale_schema_matter(papp, strLocale, strSchema, strRoot, strApp);

                  for (index l = 0; l < straLs.get_count(); l++)
                  {
                     strLs = straLs[l];

                     strPath = path(strLs, str, str2);
                     if (bDir)
                     {
                        if (System.dir().is(strPath, papp))
                           goto ret;
                     }
                     else
                     {
                        if (System.file().exists(strPath, papp))
                           goto ret;
                     }
                  }

               }


               straLs = locale_schema_matter(papp, "en", "en", strRoot, strApp);

               for (index l = 0; l < straLs.get_count(); l++)
               {
                  strLs = straLs[l];

                  strPath = path(strLs, str, str2);
                  if (bDir)
                  {
                     if (System.dir().is(strPath, papp))
                        goto ret;
                  }
                  else
                  {
                     if (System.file().exists(strPath, papp))
                        goto ret;
                  }
               }

            }




         }


         if(BaseSession.m_bMatterFromHttpCache)
         {


            stringa straPath;

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            straLs      = locale_schema_matter(papp, strLocale, strSchema);

            strFile = System.dir().commonappdata(path("cache", papp->get_locale_schema_dir(strLocale, strSchema), str + ::str::has_char(str2, ",") + ".map_question"));

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


            for(int k = 0; k < straLs.get_count(); k++)
            {

               strLs = straLs[k];

               straPath.add(path(strLs, str, str2));

            }

            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {
               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               straLs             = locale_schema_matter(papp, strLocale, strSchema);
               for(int k = 0; k < straLs.get_count(); k++)
               {

                  strLs = straLs[k];

                  straPath.add(path(strLs, str, str2, true));
               }
            }

            straLs             = locale_schema_matter(papp, "en", "en");
            for(int k = 0; k < straLs.get_count(); k++)
            {

               strLs = straLs[k];

               straPath.add(path(strLs, str, str2));
            }

            property_set set(papp);

            set["raw_http"] = true;

            if(bDir)
            {
               strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_dir?candidate=" + System.url().url_encode(straPath.implode("|")), set);
            }
            else
            {
               strPath = App(papp).http().get("http://" + get_api_cc() + "/api/matter/query_file?candidate=" + System.url().url_encode(straPath.implode("|")), set);
            }

            strPath.trim();

            if(strPath.has_char())
               goto ret;

         }

else

         {

            strLocale  = pcontext->m_plocaleschema->m_idLocale;
            strSchema  = pcontext->m_plocaleschema->m_idSchema;
            straLs      = locale_schema_matter(papp, strLocale, strSchema);

            for (index l = 0; l < straLs.get_count(); l++)
            {
               strLs = straLs[l];

               strPath = path(strLs, str, str2);
               if (bDir)
               {
                  if (System.dir().is(strPath, papp))
                     goto ret;
               }
               else
               {
                  if (System.file().exists(strPath, papp))
                     goto ret;
               }

            }


            for(int32_t i = 0; i < pcontext->localeschema().m_idaLocale.get_count(); i++)
            {

               strLocale         = pcontext->localeschema().m_idaLocale[i];
               strSchema         = pcontext->localeschema().m_idaSchema[i];
               straLs             = locale_schema_matter(papp, strLocale, strSchema);

               for (index l = 0; l < straLs.get_count(); l++)
               {
                  strLs = straLs[l];

                  strPath = path(strLs, str, str2);
                  if (bDir)
                  {
                     if (System.dir().is(strPath, papp))
                        goto ret;
                  }
                  else
                  {
                     if (System.file().exists(strPath, papp))
                        goto ret;
                  }

               }

            }


            straLs             = locale_schema_matter(papp, "en", "en");

            for (index l = 0; l < straLs.get_count(); l++)
            {
               strLs = straLs[l];

               strPath = path(strLs, str, str2);
               if (bDir)
               {
                  if (System.dir().is(strPath, papp))
                     goto ret;
               }
               else
               {
                  if (System.file().exists(strPath, papp))
                     goto ret;
               }

            }


            if(papp->m_pbasesession != NULL && papp->m_pbasesession != papp &&
               (sp(::base::application)) papp->m_pbasesystem != (sp(::base::application)) papp
               && papp->m_pbasesession->m_bBaseInitialize1)
            {
               strPath = matter(papp->m_pbasesession, str, str2, bDir);
               if(bDir)
               {
                  if(System.dir().is(strPath, papp))
                     goto ret;
               }
               else
               {
                  if(System.file().exists(strPath, papp))
                     goto ret;
               }
            }

         }



         if(papp->m_pbasesystem != NULL && papp->m_pbasesystem != papp &&
            (sp(::base::application)) papp->m_pbasesystem != (sp(::base::application)) papp->m_pbasesession
            && papp->m_pbasesystem->m_bBaseInitialize1)
         {
            strPath = matter(papp->m_pbasesystem, str, str2, bDir);
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

         if(BaseSession.m_bMatterFromHttpCache)

         {
            Application.file().put_contents(strFile,strPath);

            strFile = strPath;

            strFile.replace(":","_");
            strFile.replace("//","/");
            strFile.replace("?","%19");
            strFile = System.dir().appdata("cache/" + strFile + ".exists_question");

            Application.file().put_contents(strFile, "yes");


         }

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
            (sp(::base::application)) papp->m_psystem != (sp(::base::application)) papp)
         {
            strPath = matter(papp->m_psession, str, str2);
            if(System.file().exists(strPath, papp))
               return strPath;
         }
         if(papp->m_psystem != NULL && papp->m_psystem != papp &&
            (sp(::base::application)) papp->m_psystem != (sp(::base::application)) papp->m_psession)
         {
            strPath = matter(papp->m_psystem, str, str2);
            if(System.file().exists(strPath, papp))
               return strPath;
         }
         return path(locale_schema_matter(papp, strEmpty, strEmpty), str, str2);*/
      }

      string system::matter(sp(::base::application) papp, const char * psz, bool bDir, const char * pszRoot, const char * pszApp)
      {
         string str(psz);
         string str2;
         return matter(papp, str, str2, bDir, pszRoot, pszApp);
      }

      string system::matter(sp(::base::application) papp, const string & str, bool bDir, const char * pszRoot, const char * pszApp)
      {
         string str2;
         return matter(papp, str, str2, bDir, pszRoot, pszApp);
      }

      string system::matter(sp(::base::application) papp)
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

         stringa straLs;

         string strLs;

         string strLocale  = pcontext->m_plocaleschema->m_idLocale;
         string strSchema   = pcontext->m_plocaleschema->m_idSchema;
         straLs      = locale_schema_matter(strLocator, strLocale, strSchema);
         for (index l = 0; l < straLs.get_count(); l++)
         {
            strLs = straLs[l];

            strPath = path(strLs, str, str2);
            if (System.file().exists(strPath, get_app()))
               return strPath;

         }


         for(int32_t i = 0; i < pcontext->m_plocaleschema->m_idaLocale.get_count(); i++)
         {

            strLocale         = pcontext->m_plocaleschema->m_idaLocale[i];
            strSchema          = pcontext->m_plocaleschema->m_idaSchema[i];
            straLs             = locale_schema_matter(strLocator, strLocale, strSchema);

            for (index l = 0; l < straLs.get_count(); l++)
            {
               strLs = straLs[l];

               strPath = path(strLs, str, str2);
               if (System.file().exists(strPath, get_app()))
                  return strPath;

            }

         }


         straLs             = locale_schema_matter(strLocator, "en", "en");

         for (index l = 0; l < straLs.get_count(); l++)
         {

            strLs = straLs[l];

            strPath = path(strLs, str, str2);

            if (System.file().exists(strPath, get_app()))
               return strPath;

         }


         straLs = locale_schema_matter(strLocator, "se", "se");

         for (index l = 0; l < straLs.get_count(); l++)
         {

            strLs = straLs[l];

            strPath = path(strLs, str, str2);

            if (System.file().exists(strPath, get_app()))
               return strPath;

         }

         return path(strLs, str, str2);


      }

      void system::appmatter_locators(string & strRoot, string & strDomain, sp(::base::application) papp)
      {

         if(papp->is_system())
         {
            strRoot     = "app";
            strDomain   = "main";
         }
         else
         {

            appmatter_locators(strRoot, strDomain, papp->m_strLibraryName, papp->m_strAppId);


            if(strRoot.is_empty() || strDomain.is_empty())
            {

               strRoot     = "app";
               strDomain   = "main";

            }


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
            && ::str::begins_ci(strLibraryNameParam, "app_") && strLibraryNameParam.find("_", strlen("app_")) > 4)
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

      string system::appmatter_locator(sp(::base::application) papp)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot,strDomain,papp);

         if(BaseSession.m_bMatterFromHttpCache)
         {
            return simple_path(strRoot, "appmatter", strDomain);

         }
         else
         {
            return element(simple_path(strRoot,"appmatter",strDomain));

         }

      }

      string system::appmatter_locator(const string & strLibraryName, const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, strLibraryName, strAppName);

         return element(simple_path(strRoot, "appmatter", strDomain));

      }

      string system::appmatter_locator(const string & strAppName)
      {

         string strRoot;
         string strDomain;

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

#ifdef CUBE

         return simple_path(strRoot, "appmatter", strDomain);

#else

         return element(simple_path(strRoot, "appmatter", strDomain));

#endif

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


      class ::file::path & system::path()
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

      string system::commonappdata(const char * lpcsz,const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(),"this is an interface");
      }

      string system::usersystemappdata(sp(::base::application) papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userappdata(sp(::base::application) papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userdata(sp(::base::application) papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userfolder(sp(::base::application) papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_os_user_path_prefix(sp(::base::application) papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userappdata(sp(::base::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userdata(sp(::base::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::default_userfolder(sp(::base::application) papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userquicklaunch(sp(::base::application) papp, const char * lpcszRelativePath, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszRelativePath);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::userprograms(sp(::base::application) papp, const char * lpcsz, const char * lpcsz2)
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

      bool system::is_inside_time(const char * pszPath, sp(::base::application) papp)
      {
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_inside(const char * pszDir, const char * pszPath, sp(::base::application) papp)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      string system::pathfind(const char * pszEnv, const char * pszTopic, const char * pszMode, sp(::base::application) papp)
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

      string system::get_api_cc()
      {

         if(m_strApiCc.has_char())
            return m_strApiCc;

         synch_lock sl(&m_mutex);

         if(&BaseSession == NULL || BaseSession.fontopus().is_null())
            return "api.ca2.cc";

         string strApiServer;

         string strGetFontopus("http://api.ca2.cc/get_fontopus");

         string strFontopusServer = BaseSession.fontopus()->get_server(strGetFontopus,8);

         strApiServer = strFontopusServer;

         strApiServer.replace("account", "api");

         m_strApiCc = strApiServer;

         return m_strApiCc;

      }


   }  // namespace dir


} // namespace file




