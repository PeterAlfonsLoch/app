#include "framework.h"


#include "zlib.h"
#include "zutil.h"
#include "aura/aura/compress/zip/zip.h"



#ifdef WINDOWS

   #define DIR_SEPARATOR "\\"

#else

   #define DIR_SEPARATOR "/"

#endif


namespace file
{


   namespace dir
   {


      system::system(::aura::application * papp) :
         ::object(papp),
         m_isdirmap(papp),
         m_mutex(papp),
         ::file_watcher::file_watcher(papp),
         ::file_watcher::listener_thread(papp)

      {

         m_isdirmap.m_dwTimeOut = 15000;

         m_strCa2 = ::dir::root();

      }

      system::~system()
      {
//         if(m_pziputil != NULL)
//         {
////            delete m_pziputil;
//         }
      }



      //::file::path system::path(const string & pszFolder, strsize iLenFolder, const string & pszRelative, strsize iLenRelative, const string & psz2, strsize iLen2, bool bUrl)
      //{
      //   UNREFERENCED_PARAMETER(pszFolder);
      //   UNREFERENCED_PARAMETER(iLenFolder);
      //   UNREFERENCED_PARAMETER(pszRelative);
      //   UNREFERENCED_PARAMETER(iLenRelative);
      //   UNREFERENCED_PARAMETER(psz2);
      //   UNREFERENCED_PARAMETER(iLen2);
      //   UNREFERENCED_PARAMETER(bUrl);
      //   throw interface_only_exception(get_app(), "this is an interface");
      //}

      //::file::path system::path(const string & pszFolder, strsize iLenFolder, const string & pszRelative, strsize iLenRelative, bool bUrl)
      //{

      //   return path(pszFolder, iLenFolder, pszRelative, iLenRelative, NULL, 0, bUrl);

      //}

      //::file::path system::path(const string & pszFolder, strsize iLenFolder, const string & pszRelative, strsize iLenRelative, const string & psz2, strsize iLen2)
      //{

      //   return path(pszFolder, iLenFolder, pszRelative, iLenRelative, psz2, iLen2, ::url::is_url(pszFolder));

      //}

      //::file::path system::path(const string & strFolder, const string & strRelative)
      //{

      //   return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), NULL, 0, ::url::is_url(strFolder));

      //}


      //::file::path system::path(const string & strFolder, const string & strRelative, const string & str2)
      //{

      //   return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), str2, str2.get_length(), ::url::is_url(strFolder));

      //}


      //::file::path system::sibling(const string & strPath,const string & strRelative,bool bUrl)
      //{

      //   return path(name(strPath),strRelative,bUrl);

      //}


      //::file::path system::sibling(const string & strPath,const string & strRelative,const string & str2,bool bUrl)
      //{

      //   return path(name(strPath),strRelative,str2,bUrl);

      //}


      //::file::path system::sibling(const string & strPath,const string & strRelative)
      //{

      //   return sibling(strPath,strRelative,::url::is_url(strPath));

      //}


      //::file::path system::sibling(const string & strPath,const string & strRelative,const string & str2)
      //{

      //   return sibling(strPath,strRelative, str2,::url::is_url(strPath));

      //}


      //::file::path system::path(const string & strFolder, const string & strRelative, bool bUrl)
      //{

      //   return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), NULL, 0, bUrl);

      //}

      //::file::path system::path(const string & strFolder, const string & strRelative, const string & str2, bool bUrl)
      //{

      //   return path(strFolder, strFolder.get_length(), strRelative, strRelative.get_length(), str2, str2.get_length(), bUrl);

      //}

      inline bool myspace(char ch)
      {
         return ch == ' ' ||
                ch == '\t' ||
                ch == '\r' ||
                ch == '\n';
      }

#define string_STRCAT2_beg_char_end(strCat, ch, str1, str2, beg1, end1, beg2, end2) \
   { \
      string & psz = strCat.GetBufferSetLength(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
      strncpy(psz, &((const string &)str1)[beg1], end1 - beg1 + 1); \
      psz[end1 - beg1 + 1] = ch; \
      strncpy(&psz[end1 - beg1 + 2], &((const string &)str2)[beg2], end2 - beg2 + 1); \
      strPath.ReleaseBuffer(end1 - beg1 + 1 + end2 - beg2 + 1 + 1); \
   }

      //::file::path system::simple_path(const string & strFolder, const string & strRelative)
      //{

      //   if(strRelative.is_empty())
      //   {
      //      if(strFolder.is_empty())
      //         return "";
      //      return strFolder;
      //   }

      //   strsize iFolderBeg = 0;

      //   strsize iFolderEnd = strFolder.get_length() - 1;

      //   if(iFolderEnd >= iFolderBeg)
      //   {
      //      //strFolder.trim();
      //      // passive left trimming
      //      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
      //         iFolderBeg++;
      //      // passive right trimming
      //      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
      //         iFolderEnd--;
      //      //better than following 2 together
      //      //::str::ends_eat(strFolder, "\\");
      //      //::str::ends_eat(strFolder, "/");
      //      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
      //         iFolderEnd--;
      //   }

      //   strsize iRelativeBeg = 0;

      //   strsize iRelativeEnd = strRelative.get_length() - 1;

      //   if(iRelativeEnd >= iRelativeBeg)
      //   {
      //      //strFolder.trim();
      //      // passive left trimming
      //      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
      //         iFolderBeg++;
      //      // passive right trimming
      //      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
      //         iFolderEnd--;
      //      //better than following 2 together
      //      //::str::ends_eat(strFolder, "\\");
      //      //::str::ends_eat(strFolder, "/");
      //      while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
      //         iRelativeBeg++;
      //   }

      //   string strPath;
      //   if(iFolderBeg > iFolderEnd)
      //   {
      //      strPath = strRelative;
      //   }
      //   else
      //   {
      //      string & psz = strPath.GetBufferSetLength(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
      //      strncpy(psz, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
      //      #if defined(LINUX) || defined(APPLEOS)
      //      psz[iFolderEnd - iFolderBeg + 1] = '/';
      //      #else
      //      psz[iFolderEnd - iFolderBeg + 1] = '\\';
      //      #endif
      //      strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
      //      strPath.ReleaseBuffer(iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1);
      //   }


      //   return strPath;
      //}

      //::file::path system::simple_path(const string & strFolder, const string & strRelative, const string & str2)
      //{

      //   if(strRelative.is_empty())
      //   {
      //      if(str2.is_empty())
      //      {
      //         if(strFolder.is_empty())
      //            return "";
      //         return strFolder;
      //      }
      //      else
      //      {
      //         if(strFolder.is_empty())
      //            return str2;
      //         return simple_path(strFolder, str2);
      //      }
      //   }
      //   else if(strFolder.is_empty())
      //   {
      //      if(str2.is_empty())
      //      {
      //         return strRelative;
      //      }
      //      else
      //      {
      //         return simple_path(strRelative, str2);
      //      }
      //   }
      //   else if(str2.is_empty())
      //   {
      //      return simple_path(strFolder, strRelative);
      //   }

      //   // none of them - 3 - are empty

      //   strsize iFolderBeg = 0;

      //   strsize iFolderEnd = strFolder.get_length() - 1;

      //   if(iFolderEnd >= iFolderBeg)
      //   {
      //      //strFolder.trim();
      //      // passive left trimming
      //      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderBeg]))
      //         iFolderBeg++;
      //      // passive right trimming
      //      while(iFolderBeg <= iFolderEnd && myspace(strFolder[iFolderEnd]))
      //         iFolderEnd--;
      //      //better than following 2 together
      //      //::str::ends_eat(strFolder, "\\");
      //      //::str::ends_eat(strFolder, "/");
      //      while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
      //         iFolderEnd--;
      //   }

      //   strsize iRelativeBeg = 0;

      //   strsize iRelativeEnd = strRelative.get_length() - 1;

      //   if(iRelativeEnd >= iRelativeBeg)
      //   {
      //      //strFolder.trim();
      //      // passive left trimming
      //      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeBeg]))
      //         iFolderBeg++;
      //      // passive right trimming
      //      while(iRelativeBeg <= iRelativeEnd && myspace(strRelative[iRelativeEnd]))
      //         iFolderEnd--;
      //      //better than following 2 together
      //      //::str::ends_eat(strFolder, "\\");
      //      //::str::ends_eat(strFolder, "/");
      //      while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
      //         iRelativeBeg++;
      //   }


      //   strsize iBeg2 = 0;

      //   strsize iEnd2 = str2.get_length() - 1;

      //   if(iEnd2 >= iBeg2)
      //   {
      //      //strFolder.trim();
      //      // passive left trimming
      //      while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iBeg2]))
      //         iBeg2++;
      //      // passive right trimming
      //      while(iBeg2 <= iEnd2 && myspace(str2.m_pszData[iEnd2]))
      //         iEnd2--;
      //      //better than following 2 together
      //      //::str::ends_eat(strFolder, "\\");
      //      //::str::ends_eat(strFolder, "/");
      //      while(iBeg2 <= iEnd2 && (str2[iBeg2] == '/' || str2[iBeg2] == '\\'))
      //         iBeg2++;
      //   }

      //   if(iRelativeBeg > iRelativeEnd)
      //   {
      //      if(iBeg2 > iEnd2)
      //      {
      //         if(iFolderBeg > iFolderEnd)
      //            return "";
      //         return strFolder.Mid(iFolderBeg, iFolderEnd - iFolderBeg + 1);
      //      }
      //      else
      //      {
      //         if(iFolderBeg > iFolderEnd)
      //            return str2.Mid(iBeg2, iEnd2 - iBeg2 + 1);
      //         string strPath;
      //         string_STRCAT2_beg_char_end(strPath, '\\', strFolder, str2, iFolderBeg, iFolderEnd, iBeg2, iEnd2);
      //         return strPath;
      //      }
      //   }
      //   else if(strFolder.is_empty())
      //   {
      //      if(str2.is_empty())
      //      {
      //         return strRelative;
      //      }
      //      else
      //      {
      //         string strPath;
      //         #if defined(LINUX) || defined(APPLEOS)
      //         string_STRCAT2_beg_char_end(strPath, '/', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
      //         #else
      //         string_STRCAT2_beg_char_end(strPath, '\\', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
      //         #endif
      //         return strPath;
      //      }
      //   }
      //   else if(str2.is_empty())
      //   {
      //      string strPath;
      //      #if defined(LINUX) || defined(APPLEOS)
      //      string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
      //      #else
      //      string_STRCAT2_beg_char_end(strPath, '/', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
      //      #endif
      //      return strPath;
      //   }

      //   string strPath;

      //   string & psz = strPath.GetBufferSetLength(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
      //   strncpy(psz, &((const string &)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
      //   #if defined(LINUX) || defined(APPLEOS)
      //   psz[iFolderEnd - iFolderBeg + 1] = '/';
      //   #else
      //   psz[iFolderEnd - iFolderBeg + 1] = '\\';
      //   #endif
      //   strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const string &)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
      //   #if defined(LINUX) || defined(APPLEOS)
      //   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '/';
      //   #else
      //   psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '\\';
      //   #endif
      //   strncpy(&psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1 + 1], &((const string &)str2)[iBeg2], iEnd2 - iBeg2 + 1);
      //   strPath.ReleaseBuffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);

      //   return strPath;

      //}


      //::file::path system::relpath(const string & lpcszSource,const string & lpcszRelative)
      //{
      //   UNREFERENCED_PARAMETER(lpcszSource);
      //   UNREFERENCED_PARAMETER(lpcszRelative);
      //   throw interface_only_exception(get_app(),"this is an interface");
      //}


      //::file::path system::relpath(const string & lpcszSource, const string & lpcszRelative, const string & psz2)
      //{
      //   UNREFERENCED_PARAMETER(lpcszSource);
      //   UNREFERENCED_PARAMETER(lpcszRelative);
      //   UNREFERENCED_PARAMETER(psz2);
      //   throw interface_only_exception(get_app(), "this is an interface");
      //}


      ::file::listing & system::root_ones(::file::listing & listing,::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(listing);

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::listing & system::ls(::aura::application * papp, listing & l)
      {

         if (l.m_bRecursive)
         {

            if (l.m_eextract != extract_none && ::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (icmp(l.m_path.ext(), ".zip") == 0 || l.m_path.find_ci("zip:") >= 0))
            {

               //throw "should implement recursive zip";

               //m_pziputil->ls(papp,l);

               l.m_cres = failure_no_log;

            }
            else
            {

               l.m_cres = failure_no_log;


            }


         }
         else
         {

            if (::str::begins_ci(l.m_path, "http://") || ::str::begins_ci(l.m_path, "https://"))
            {

               property_set set(get_app());

               string str = Sess(papp).http().get(l.m_path, set);

               l.add_tokens(str, "\n", false);

            }
            else if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::ends_ci(l.m_path, ".zip") || ::str::find_file_extension("zip:", l.m_path) >= 0))
            {

               m_pziputil->ls(papp, l);

            }
            else
            {

               l.m_cres = failure_no_log;


            }

         }

         return l;

      }

      ::file::listing & system::ls_relative_name(::aura::application * papp, listing & l)
      {

         if (l.m_bRecursive)
         {

            if (l.m_eextract != extract_none && ::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (icmp(l.m_path.ext(), ".zip") == 0 || l.m_path.find_ci("zip:") >= 0))
            {

               //throw "should implement recursive zip";

               //m_pziputil->ls(papp,l);

               l.m_cres = failure_no_log;

            }
            else
            {

               l.m_cres = failure_no_log;


            }


         }
         else
         {

            if (::str::begins_ci(l.m_path, "http://") || ::str::begins_ci(l.m_path, "https://"))
            {

               property_set set(get_app());

               string str = Sess(papp).http().get(l.m_path, set);

               l.add_tokens(str, "\n", false);

            }
            else if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::ends_ci(l.m_path, ".zip") || ::str::find_file_extension("zip:", l.m_path) >= 0))
            {

               m_pziputil->ls(papp, l);

            }
            else
            {

               l.m_cres = failure_no_log;


            }

         }

         return l;

      }

      bool system::has_subdir(::aura::application * papp,const ::file::path & psz)
      {

         ::file::listing ls(papp);

         ls.ls_dir(psz);

         return ls.get_count() > 0;

      }


      bool system::is_or_definitively_not(bool & bIs, const ::file::path & lpcszPath, ::aura::application * papp)
      {

         bIs = false;



#ifdef WINDOWSEX
#ifdef WINDOWSEX
         if(::str::ends_ci(lpcszPath,".lnk"))
         {
#endif

            string strTarget;

            string strFolder;

            string strParams;

            if(System.file().resolve_link(strTarget,strFolder, strParams, lpcszPath))
            {

               bIs = is(strTarget,papp);

               return true;

            }

#ifdef WINDOWSEX
         }
#endif
#endif

         bIs = false;

         if (::str::begins_ci(lpcszPath, "http://") || ::str::begins_ci(lpcszPath, "https://"))
         {

            property_set set(get_app());

            bIs = !Sess(papp).http().exists(lpcszPath, set);

            return true;

         }

         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::ends_ci(lpcszPath, ".zip")))
         {

            bIs = true;

            return true;
         }

         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::find_file_extension("zip:", lpcszPath) >= 0))
         {

            bool bHasSubFolder;

            uint32_t dwLastError;

            if (m_isdirmap.lookup(lpcszPath, bHasSubFolder, dwLastError))
            {

               bIs = bHasSubFolder;

               return true;

            }

            bHasSubFolder = m_pziputil->has_sub_folder(papp, lpcszPath);

            m_isdirmap.set(lpcszPath, bHasSubFolder, ::GetLastError());

            bIs = bHasSubFolder;

            return true;

         }

#ifdef WINDOWSEX
#ifdef WINDOWSEX
         if (::str::ends_ci(lpcszPath, ".lnk"))
         {
#endif

            string strTarget;

            string strFolder;

            string strParams;

            if (System.file().resolve_link(strTarget, strFolder, strParams, lpcszPath))
            {

               bIs = is(strTarget, papp);

               return true;

            }

#ifdef WINDOWSEX
         }
#endif
#endif


         return false;

      }


      bool system::is(const ::file::path & strPath,::aura::application * papp)
      {

         bool bIs;

         if (strPath.ends_ci("://") || strPath.ends_ci(":/") || strPath.ends_ci(":"))
         {

            return true;

         }

         if (!is_or_definitively_not(bIs, strPath, papp) || !bIs)
            return false;

         if (::str::begins_ci(strPath, "http://") || ::str::begins_ci(strPath, "https://"))
         {

            property_set set(get_app());

            return Sess(papp).http().exists(strPath, set);

         }


         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::find_file_extension("zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            uint32_t dwLastError;
            if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->has_sub_folder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder, GetLastError());
            return bHasSubFolder;
         }


         return true;

      }


      bool system::name_is(const ::file::path & strPath,::aura::application * papp)
      {

         //OutputDebugString(strPath);
         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true, 0);
            return true;
         }
         if (::get_thread() != NULL && ::get_thread()->m_bZipIsDir && (::str::find_file_extension("zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            uint32_t dwLastError;
            if (m_isdirmap.lookup(strPath, bHasSubFolder, dwLastError))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->has_sub_folder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder, GetLastError());
            return bHasSubFolder;
         }
         return false;


      }


      system::is_dir_map::is_dir_map(::aura::application * papp) :
         file_path_map < is_dir >(papp, 256), // block size
         m_mutex(papp)
      {
         InitHashTable(16384, TRUE);
      }

      bool system::is_dir_map::lookup(const ::file::path & strPath,bool &bIsDir,uint32_t & dwLastError)
      {

         if(strPath.get_length() <= 0)
         {
            bIsDir = false;
            return true;
         }

         single_lock sl(&m_mutex, TRUE);

         pair * ppair = this->PLookup(strPath);

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

      bool system::is_dir_map::lookup(const ::file::path & strPath,bool &bIsDir,uint32_t &dwLastError,int32_t iLast)
      {

         if(iLast < 0)
         {
            bIsDir = true; // root_ones dir
            return true;
         }

         single_lock sl(&m_mutex, TRUE);

         pair * ppair = this->PLookup(strPath);

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

      void system::is_dir_map::set(const ::file::path & strPath,bool bIsDir,uint32_t dwLastError)
      {
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwError = dwLastError;
         isdir.m_dwLastCheck = ::get_tick_count();
         single_lock sl(&m_mutex, TRUE);
         set_at(strPath, isdir);
      }

      ::file::path system::time()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::stage()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::stageapp()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::netseed()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::element()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::profile()
      {

         synch_lock sl(m_pmutex);

         return m_pathProfile;

      }


      ::file::path system::home()
      {

         synch_lock sl(m_pmutex);

         return m_pathHome;

      }

      ::file::path system::userfolder(::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(papp);

         synch_lock sl(m_pmutex);

         return m_pathUser;

      }


      ::file::path system::module()
      {

         synch_lock sl(m_pmutex);

         return m_pathModule;

      }


      ::file::path system::ca2module()
      {

         synch_lock sl(m_pmutex);

         return m_pathCa2Module;

      }


      ::file::path system::time_square(::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(papp);

         return time() / "time";

      }


      ::file::path system::time_log(const string & pszId)
      {

         UNREFERENCED_PARAMETER(pszId);
         throw interface_only_exception(get_app(), "this is an interface");

      }


      bool system::mk(const ::file::path & psz,::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(psz);
         throw interface_only_exception(get_app(), "this is an interface");

      }


      bool system::rm(::aura::application * papp,const ::file::path & psz,bool bRecursive)
      {

         UNREFERENCED_PARAMETER(psz);
         UNREFERENCED_PARAMETER(bRecursive);
         throw interface_only_exception(get_app(), "this is an interface");

      }


      //::file::path system::name(const ::file::path & path1)
      //{
      //   UNREFERENCED_PARAMETER(path1);
      //   throw interface_only_exception(get_app(), "this is an interface");
      //}

      ::file::path system::locale_schema(::aura::application * papp, const string & strLocale, const string & strSchema)
      {

         return papp->m_paurasession->get_locale_schema_dir(strLocale, strSchema);

      }



      ::file::patha system::locale_schema_matter(::aura::application * papp,const string & strLocale,const string & strSchema,const ::file::path & strRoot,const ::file::path & strDomain)
      {

         //single_lock sl(&papp->m_mutexMatterLocator, true);
         if(strRoot.has_char() && strDomain.has_char())
         {

            ::file::patha patha;

            if(Session.m_bMatterFromHttpCache)
            {

               return   {strRoot / "appmatter" / strDomain / papp->m_paurasession->get_locale_schema_dir(strLocale,strSchema)};
            }
            else
            {
               return {element() / strRoot / "appmatter" / strDomain / papp->m_paurasession->get_locale_schema_dir(strLocale,strSchema) };

            }

         }
         else
         {

            ::file::patha stra;

            for (index i = 0; i < papp->m_straMatterLocator.get_count(); i++)
            {

               stra.add_unique(papp->m_straMatterLocator[i] / papp->m_paurasession->get_locale_schema_dir(strLocale, strSchema));

            }

            return stra;

         }


      }

      ::file::patha system::locale_schema_matter(const string & strLocator, const string & strLocale, const string & strSchema)
      {

         return{::file::path(strLocator) / strLocale / strSchema};

      }

      void system::matter_ls(::aura::application * papp,const ::file::path & str,::file::patha & patha)
      {

         string strDir = matter(papp, str, true);

         patha = ::file::listing(papp).ls(strDir);

      }

      void system::matter_ls_file(::aura::application * papp,const ::file::path & str,::file::patha & stra)
      {

         ::file::path strDir = matter(papp, str, true);

         if(Sess(papp).m_bMatterFromHttpCache)
         {

            property_set set(get_app());

            set["raw_http"] = true;

            string strFile = System.dir().commonappdata() / "cache"/ strDir/ "list_dir.list_dir";

            strsize iFind = strFile.find(DIR_SEPARATOR);

            if (iFind > 0)
            {

               strFile.replace(":", "_", iFind + 1);

            }

            strFile.replace("////", "//");
            strFile.replace("\\\\","\\", 1);

            string strLs;

            if(Application.file().exists(strFile))
            {

               strLs = Application.file().as_string(strFile);

            }


            ::file::patha straLs;

            stringa straSep;

            straSep.add("\r");
            straSep.add("\n");
            straSep.add("\r\n");

            straLs.add_smallest_tokens(strLs,straSep,false);

            for(index i = 0; i < straLs.get_count(); i++)
            {

               if(!::str::ends(straLs[i],"/"))
               {
                  ::file::path strPath  = strDir / straLs[i];
                  stra.add(strPath);
               }

            }

         }
         else
         {

            stra = listing(papp).ls(strDir);

         }


      }

      ::file::path system::matter(::aura::application * papp,const ::file::patha & stra,bool bDir,const ::file::path & pszRoot,const ::file::path & pszApp)
      {
         throw interface_only_exception(get_app());

         return "";

      }

      ::file::path system::matter(::aura::application * papp,const ::file::path & path,bool bDir,const ::file::path & pszRoot,const ::file::path & pszApp)
      {
         throw interface_only_exception(get_app());

         return "";
      }

      ::file::path system::appmatter(string strApp, ::file::path pathRel)
      {

         ::file::path e = element();

         strsize iFind = strApp.find('/');

         string strRepo;

         if (iFind > 0)
         {

            strRepo = strApp.Left(iFind);

            strApp = strApp.Mid(iFind + 1);

         }
         else
         {

            strApp.replace("-", "_");

            strApp.replace("\\", "_");

            if (::str::begins_eat_ci(strApp, "app_veriwell_"))
            {

               strRepo = "app-veriwell";

            }
            else if (::str::begins_eat_ci(strApp, "app_core_"))
            {

               strRepo = "app-core";

            }
            else if (::str::begins_eat_ci(strApp, "app_cidadedecuritiba_"))
            {

               strRepo = "app-cidadedecuritiba";

            }
            else if (::str::begins_eat_ci(strApp, "app_"))
            {

               strRepo = "app";

            }
            else
            {

               return "";

            }

         }

         ::file::path p = e / strRepo / "appmatter" / strApp / "_std" / "_std" / pathRel;

         return p;

      }


      /* static const string strEn("en");
         static const string strStd("_std");
         static const string strEmpty("");

         string strPath;
         string strLs = locale_schema_matter(strLocator, App(papp).get_locale(), App(papp).get_style());
         strPath = strLs + str + str2;
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strLs = locale_schema_matter(strLocator, strEn, App(papp).get_style());
         strPath = strLs + str + str2;
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
         strPath = strLs + str + str2;
         if(System.file().exists(strPath, get_app()))
            return strPath;
         strPath = path(locale_schema_matter(strLocator, strStd, strStd), str, str2);
         if(System.file().exists(strPath, get_app()))
            return strPath;
      */

      ::file::path system::matter_from_locator(::aura::str_context * pcontext, const string & strLocator,  const ::file::path & str)
      {

         ::file::path strPath;

         ::file::patha straLs;

         string strLs;

         string strLocale  = pcontext->m_plocaleschema->m_idLocale;
         string strSchema   = pcontext->m_plocaleschema->m_idSchema;
         straLs      = locale_schema_matter(strLocator, strLocale, strSchema);
         for (index l = 0; l < straLs.get_count(); l++)
         {
            strLs = straLs[l];

            strPath = strLs / str;
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

               strPath = strLs / str;
               if (System.file().exists(strPath, get_app()))
                  return strPath;

            }

         }


         straLs             = locale_schema_matter(strLocator, "en", "en");

         for (index l = 0; l < straLs.get_count(); l++)
         {

            strLs = straLs[l];

            strPath = strLs / str;

            if (System.file().exists(strPath, get_app()))
               return strPath;

         }


         straLs = locale_schema_matter(strLocator, "se", "se");

         for (index l = 0; l < straLs.get_count(); l++)
         {

            strLs = straLs[l];

            strPath = strLs / str;

            if (System.file().exists(strPath, get_app()))
               return strPath;

         }

         return strLs + str;


      }

      void system::appmatter_locators(::file::path & strRoot,::file::path & strDomain,::aura::application * papp)
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

      void system::appmatter_locators(::file::path & strRoot,::file::path & strDomain,const string & strAppName)
      {

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

      }

      void system::appmatter_locators(::file::path & strRoot,::file::path & strDomain,const string & strLibraryNameParam,const string & strAppNameParam)
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
            ::file::patha stra2;
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

      ::file::path system::appmatter_locator(::aura::application * papp)
      {

         ::file::path strRoot;
         ::file::path strDomain;

         appmatter_locators(strRoot,strDomain,papp);

         if(Session.m_bMatterFromHttpCache)
         {
            return strRoot/ "appmatter"/ strDomain;

         }
         else
         {
            return element()/ strRoot/"appmatter"/strDomain;

         }

      }

      ::file::path system::appmatter_locator(const string & strLibraryName, const string & strAppName)
      {

         ::file::path strRoot;
         ::file::path strDomain;

         appmatter_locators(strRoot, strDomain, strLibraryName, strAppName);

         return element() / strRoot / "appmatter"/ strDomain;

      }

      ::file::path system::appmatter_locator(const string & strAppName)
      {

         ::file::path strRoot;
         ::file::path strDomain;

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

#if defined(CUBE) || defined(VSNORD) || defined(METROWIN)

         return strRoot /  "appmatter" /  strDomain;

#else

         return element() / strRoot / "appmatter"/ strDomain;

#endif

      }

      ::file::path system::base_appmatter_locator(const ::file::path & strBase,const string & strLibraryName,const string & strAppName)
      {

         ::file::path strRoot;
         ::file::path strDomain;

         appmatter_locators(strRoot, strDomain, strLibraryName, strAppName);

         return strBase / strRoot / "appmatter" / strDomain;

      }

      ::file::path system::base_appmatter_locator(const ::file::path & strBase,const string & strAppName)
      {

         ::file::path strRoot;
         ::file::path strDomain;

         appmatter_locators(strRoot, strDomain, System.m_mapAppLibrary[strAppName], strAppName);

         return strBase /strRoot / "appmatter" / strDomain;

      }


      //class ::file::file_path & system::path()
      //{
      //   throw interface_only_exception(get_app(), "this is an interface");
      //}

      bool system::initialize()
      {

         if(!update_module_path())
         {

            return false;

         }

         return true;

      }
      
      
      ::file::path system::commonappdata(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration)
      {

         synch_lock sl(m_pmutex);

         string strAppId(pszAppId);

         string strPlatform(pszPlatform);

         if (strPlatform.is_empty())
         {

            strPlatform = System.get_system_platform();

         }

         string strConfiguration(pszConfiguration);

         if (strConfiguration.is_empty())
         {

            strConfiguration = System.get_system_configuration();

         }

         string strBuild(pszBuild);

         return commonappdata() / strBuild / strPlatform / strConfiguration / strAppId;

      }


      ::file::path system::commonappdata_locale_schema(const char * pszAppId, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema)
      {

         synch_lock sl(m_pmutex);

         string strLocale(pszLocale);

         if (strLocale.is_empty())
         {

            strLocale = Session.m_strLocale;

         }

         string strSchema(pszSchema);

         if (strSchema.is_empty())
         {

            strSchema = Session.m_strSchema;

         }

         return commonappdata(pszAppId, pszBuild, pszPlatform, pszConfiguration) / strLocale / strSchema;

      }


      ::file::path system::trash_that_is_not_trash(const ::file::path & psz)
      {

         UNREFERENCED_PARAMETER(psz);

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::path system::appdata()
      {

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::path system::commonappdata_root()
      {

         return "/var/lib";

      }

      ::file::path system::commonappdata()
      {

         return element_commonappdata(element());

      }

      ::file::path system::element_commonappdata(const string & strElement)
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

         return commonappdata_root()/ strRelative;

      }


      ::file::path system::usersystemappdata(::aura::application * papp, const string & lpcszPrefix)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         throw interface_only_exception(get_app(), "this is an interface");
      }


      ::file::path system::userappdata(::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(papp);

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::path system::userdata(::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(papp);

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::path system::default_os_user_path_prefix(::aura::application * papp)
      {

         UNREFERENCED_PARAMETER(papp);

         throw interface_only_exception(get_app(), "this is an interface");

      }


      ::file::path system::default_userappdata(::aura::application * papp, const string & lpcszPrefix, const string & lpcszLogin)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::default_userdata(::aura::application * papp, const string & lpcszPrefix, const string & lpcszLogin)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::default_userfolder(::aura::application * papp, const string & lpcszPrefix, const string & lpcszLogin)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::userquicklaunch(::aura::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::userprograms(::aura::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::commonprograms()
      {
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_inside_time(const ::file::path & pszPath,::aura::application * papp)
      {
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      bool system::is_inside(const ::file::path & pszDir,const ::file::path & pszPath,::aura::application * papp)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception(get_app(), "this is an interface");
      }

      ::file::path system::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode, ::aura::application * papp)
      {

         ::file::patha stra;

         stra.add_tokens(pszEnv, ":", false);

         string strCandidate;

         for(int32_t i = 0; i < stra.get_count(); i++)
         {

            strCandidate = stra[i] / pszTopic;

            if(Sess(papp).file().exists(strCandidate))
            {
               return strCandidate;
            }

         }

         return "";

      }

      ::file::path system::get_api_cc()
      {

         if(m_strApiCc.has_char())
            return m_strApiCc;

         synch_lock sl(&m_mutex);



         return m_strApiCc;

      }


      bool system::update_module_path()
      {

         if(!System.file().update_module_path())
         {

            return false;

         }

         m_pathModule = System.file().module().folder();

         m_pathCa2Module = System.file().ca2module().folder();

         return true;

      }

      
      ::file::path system::get_home_folder()
      {
         
         return ::dir::home();
         
      }

      ::file::path system::get_desktop_folder()
      {
         
         return get_home_folder() / "Desktop";
         
      }

      
      ::file::path system::get_document_folder()
      {

         return get_home_folder() / "Document";

      }

      
      
      ::file::path system::get_download_folder()
      {
         
         return get_home_folder() / "Download";
         
      }


      ::file::path system::get_music_folder()
      {

         return get_home_folder() / "Music";

      }


      ::file::path system::get_video_folder()
      {

         return get_home_folder() / "Video";

      }


      ::file::path system::get_image_folder()
      {

         return get_home_folder() / "Image";

      }


   }  // namespace dir


} // namespace file




