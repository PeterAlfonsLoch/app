#include "StdAfx.h"


namespace ca
{


   namespace dir
   {


      system::system(::ca::application * papp) :
         ca(papp)
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

      bool system::path::is_equal(const char * lpcsz1, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz1);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::path(const string & strFolder, const string & strRelative, const string & str2)
      {
         UNREFERENCED_PARAMETER(strFolder);
         UNREFERENCED_PARAMETER(strRelative);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception("this is an interface");
      }

      string system::path(const string & strFolder, const string & strRelative, const char * lpcsz2)
      {

         string str2(lpcsz2);

         return path(strFolder, strRelative, str2);

      }

      string system::path(const string & strFolder, const string & strRelative)
      {

         string strEmpty;

         return path(strFolder, strRelative, strEmpty);

      }

      string system::path(const string & strFolder, const char * lpcszRelative, const string & str2)
      {

         string strRelative(lpcszRelative);

         return path(strFolder, strRelative, str2);

      }

      string system::path(const string & strFolder, const char * lpcszRelative, const char * lpcsz2)
      {

         string strRelative(lpcszRelative);
         string str2(lpcsz2);

         return path(strFolder, strRelative, str2);

      }

      string system::path(const string & strFolder, const char * lpcszRelative)
      {

         string strRelative(lpcszRelative);
         string strEmpty;

         return path(strFolder, strRelative, strEmpty);

      }

      
      string system::path(const char  * lpcszFolder, const string & strRelative, const string & str2)
      {
         
         string strFolder(lpcszFolder);
         string strEmpty;

         return path(strFolder, strRelative, strEmpty);

      }

      string system::path(const char * lpcszFolder, const string & strRelative, const char * lpcsz2)
      {

         string strFolder(lpcszFolder);
         string str2(lpcsz2);

         return path(strFolder, strRelative, str2);

      }

      string system::path(const char * lpcszFolder, const string & strRelative)
      {

         string strFolder(lpcszFolder);
         string strEmpty;

         return path(strFolder, strRelative, strEmpty);

      }

      string system::path(const char * lpcszFolder, const char * lpcszRelative, const string & str2)
      {

         string strFolder(lpcszFolder);
         string strRelative(lpcszRelative);

         return path(strFolder, strRelative, str2);

      }


      string system::path(const char * lpcszFolder, const char * lpcszRelative)
      {

         string strFolder(lpcszFolder);
         string strRelative(lpcszRelative);
         string strEmpty;

         return path(strFolder, strRelative, strEmpty);

      }
      


      string system::path(const char * lpcszFolder, const char * lpcszRelative, const char * psz2)
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
         string str2(psz2);
         return path(strFolder, strRelative, str2);
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
            
         int iFolderBeg = 0;
         int iFolderEnd = strFolder.get_length() - 1;
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
            //gen::str::ends_eat(strFolder, "\\");
            //gen::str::ends_eat(strFolder, "/");
            while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
               iFolderEnd--;
         }
         int iRelativeBeg = 0;
         int iRelativeEnd = strRelative.get_length() - 1;
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
            //gen::str::ends_eat(strFolder, "\\");
            //gen::str::ends_eat(strFolder, "/");
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
            psz[iFolderEnd - iFolderBeg + 1] = '\\';
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
            
         int iFolderBeg = 0;
         int iFolderEnd = strFolder.get_length() - 1;
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
            //gen::str::ends_eat(strFolder, "\\");
            //gen::str::ends_eat(strFolder, "/");
            while(iFolderBeg <= iFolderEnd && (strFolder[iFolderEnd] == '/' || strFolder[iFolderEnd] == '\\'))
               iFolderEnd--;
         }
         int iRelativeBeg = 0;
         int iRelativeEnd = strRelative.get_length() - 1;
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
            //gen::str::ends_eat(strFolder, "\\");
            //gen::str::ends_eat(strFolder, "/");
            while(iRelativeBeg <= iRelativeEnd && (strRelative[iRelativeBeg] == '/' || strRelative[iRelativeBeg] == '\\'))
               iRelativeBeg++;
         }

         int iBeg2 = 0;
         int iEnd2 = str2.get_length() - 1;
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
            //gen::str::ends_eat(strFolder, "\\");
            //gen::str::ends_eat(strFolder, "/");
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
               string_STRCAT2_beg_char_end(strPath, '\\', strRelative, str2, iRelativeBeg, iRelativeEnd, iBeg2, iEnd2);
               return strPath;
            }
         }
         else if(str2.is_empty())
         {
            string strPath;
            string_STRCAT2_beg_char_end(strPath, '\\', strFolder, strRelative, iFolderBeg, iFolderEnd, iRelativeBeg, iRelativeEnd);
            return strPath;
         }

         string strPath;

         char * psz = strPath.GetBufferSetLength(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
         strncpy(psz, &((const char *)strFolder)[iFolderBeg], iFolderEnd - iFolderBeg + 1);
         psz[iFolderEnd - iFolderBeg + 1] = '\\';
         strncpy(&psz[iFolderEnd - iFolderBeg + 2], &((const char *)strRelative)[iRelativeBeg], iRelativeEnd - iRelativeBeg + 1);
         psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1] = '\\';
         strncpy(&psz[iFolderEnd - iFolderBeg + 1 + 1 + iRelativeEnd - iRelativeBeg + 1 + 1], &((const char *)str2)[iBeg2], iEnd2 - iBeg2 + 1);
         strPath.ReleaseBuffer(iEnd2 - iBeg2 + 1 + iRelativeEnd - iRelativeBeg + 1 + iFolderEnd - iFolderBeg + 1 + 1 + 1);
   
         return strPath;

      }


      string system::relpath(const char * lpcszSource, const char * lpcszRelative, const char * psz2)
      {
         UNREFERENCED_PARAMETER(lpcszSource);
         UNREFERENCED_PARAMETER(lpcszRelative);
         UNREFERENCED_PARAMETER(psz2);
         throw interface_only_exception("this is an interface");
      }

      void system::root_ones(stringa & stra, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(stra);
         throw interface_only_exception("this is an interface");
      }

      void system::rls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(pstraRelative);
         UNREFERENCED_PARAMETER(pszPattern);
         if(papp->m_bZipIsDir && (gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0))
         {
            throw "should implement recursive zip";
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented_exception("is really a directory or compressed directory/file??");
      
      }


      void system::ls_pattern(::ca::application * papp, const char * lpcsz, const char * pszPattern, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(pszPattern);
         if(papp->m_bZipIsDir && (gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0))
         {
            m_pziputil->ls(papp, lpcsz, false, pstraPath, pstraTitle, NULL, pbaIsDir, piaSize);
            return;
         }
         throw not_implemented_exception("is really a directory or compressed directory/file??");
      
      }

      void system::ls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, base_array < bool, bool > * pbaIsDir, base_array < __int64, __int64 > * piaSize)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         UNREFERENCED_PARAMETER(pbaIsDir);
         UNREFERENCED_PARAMETER(piaSize);
         throw interface_only_exception("this is an interface");
      }

      void system::rls(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle, stringa * pstraRelative, e_extract eextract)
      {
         if(eextract != extract_none && papp->m_bZipIsDir && (gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0))
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
         throw interface_only_exception("this is an interface");
      }

      void system::ls_dir(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         if(papp->m_bZipIsDir && (gen::str::ends_ci(lpcsz, ".zip") || gen::str::find_ci(".zip:", lpcsz) >= 0))
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
         throw interface_only_exception("this is an interface");
      }

      void system::ls_file(::ca::application * papp, const char * lpcsz, stringa * pstraPath, stringa * pstraTitle)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(pstraPath);
         UNREFERENCED_PARAMETER(pstraTitle);
         throw interface_only_exception("this is an interface");
      }

      bool system::is(const char * lpcszPath, ::ca::application * papp)
      {
         if(papp->m_bZipIsDir && (gen::str::ends_ci(lpcszPath, ".zip")))
            return true;
         if(papp->m_bZipIsDir && (gen::str::find_ci(".zip:", lpcszPath) >= 0))
         {
            bool bHasSubFolder;
            if(m_isdirmap.lookup(lpcszPath, bHasSubFolder))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, lpcszPath);
            m_isdirmap.set(lpcszPath, bHasSubFolder);
            return bHasSubFolder;
         }
         return false;
      }

      bool system::is(const string & strPath, ::ca::application * papp)
      {
         if(papp->m_bZipIsDir && (gen::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true);
            return true;
         }
         if(papp->m_bZipIsDir && (gen::str::find_ci(".zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            if(m_isdirmap.lookup(strPath, bHasSubFolder))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder);
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
         if(papp->m_bZipIsDir && (gen::str::ends_ci(strPath, ".zip")))
         {
            m_isdirmap.set(strPath, true);
            return true;
         }
         if(papp->m_bZipIsDir && (gen::str::find_ci(".zip:", strPath) >= 0))
         {
            bool bHasSubFolder;
            if(m_isdirmap.lookup(strPath, bHasSubFolder))
               return bHasSubFolder;
            bHasSubFolder = m_pziputil->HasSubFolder(papp, strPath);
            m_isdirmap.set(strPath, bHasSubFolder);
            return bHasSubFolder;
         }
         return false;
      }

      bool system::name_is(const var & var, ::ca::application * papp)
      {
         return name_is((const string &) var, papp);
      }

      system::is_dir_map::is_dir_map() :
         ::collection::string_map < is_dir >(256) // block size
      {
         InitHashTable(16384, TRUE);
      }

      bool system::is_dir_map::lookup(const char * pszPath, bool &bIsDir)
      {
         return lookup(string(pszPath), bIsDir);
      }

      bool system::is_dir_map::lookup(const string & strPath, bool &bIsDir)
      {
         
         if(strPath.get_length() <= 0)
         {
            bIsDir = false;
            return true;
         }



         
         string strLookup(strPath);


         if(strLookup.last_char() != '\\' && strLookup.last_char() != '/' )
            strLookup += "\\";

         single_lock sl(&m_mutex, TRUE);

         ::collection::string_map < is_dir >::pair * ppair = this->PLookup(strLookup);

         if(ppair == NULL)
            return false;

         if(::GetTickCount() > ppair->m_value.m_dwLastCheck + m_dwTimeOut)
         {
            return false;
         }

         bIsDir = ppair->m_value.m_bIsDir;

         return true;

      }
      
      void system::is_dir_map::set(const char * pszPath, bool bIsDir)
      {
         is_dir isdir;
         isdir.m_bIsDir = bIsDir;
         isdir.m_dwLastCheck = ::GetTickCount();
         string strPath(pszPath);
         if(!gen::str::ends(strPath, "\\"))
            strPath += "\\";
         single_lock sl(&m_mutex, TRUE);
         set_at(strPath, isdir);
      }


      string system::votagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::time(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::stage(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::stageapp(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::netseed(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const string & str, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const char * lpcsz, const string & str2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const string & str, const string & str2)
      {
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2(const string & str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2()
      {
         throw interface_only_exception("this is an interface");
      }

      string system::module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::ca2module(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      void system::time_square(string &str)
      {
         UNREFERENCED_PARAMETER(str);
         throw interface_only_exception("this is an interface");
      }

      string system::time_log(const char * pszId)
      {
         UNREFERENCED_PARAMETER(pszId);
         throw interface_only_exception("this is an interface");
      }

      bool system::mk(const char * lpcsz, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception("this is an interface");
      }

      bool system::rm(::ca::application * papp, const char * psz, bool bRecursive)
      {
         UNREFERENCED_PARAMETER(psz);
         UNREFERENCED_PARAMETER(bRecursive);
         throw interface_only_exception("this is an interface");
      }

      string system::name(const char * path1)
      {
         UNREFERENCED_PARAMETER(path1);
         throw interface_only_exception("this is an interface");
      }

      string system::locale_style(::ca::application * papp, const string & strLocale, const string & strStyle)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(strLocale);
         UNREFERENCED_PARAMETER(strStyle);
         throw interface_only_exception("this is an interface");
      }

      string system::locale_style_matter(::ca::application * papp, const string & strLocale, const string & strStyle)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(strLocale);
         UNREFERENCED_PARAMETER(strStyle);
         throw interface_only_exception("this is an interface");
      }

      string system::matter(::ca::application * papp, const string & str, const string & str2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(str);
         UNREFERENCED_PARAMETER(str2);
         throw interface_only_exception("this is an interface");
      }

      string system::matter(::ca::application * papp, const string & str)
      {
         string str2;
         return matter(papp, str, str2);
      }

      string system::matter(::ca::application * papp)
      {
         string str;
         string str2;
         return matter(papp, str, str2);
      }

      class system::path & system::path()
      {
         throw interface_only_exception("this is an interface");
      }

      bool system::initialize()
      {
         throw interface_only_exception("this is an interface");
      }

      string system::trash_that_is_not_trash(const char * lpcsz)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         throw interface_only_exception("this is an interface");
      }

      string system::appdata(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::usersystemappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userappdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userdata(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userfolder(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::default_os_user_path_prefix(::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userappdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userdata(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::default_userfolder(::ca::application * papp, const char * lpcszPrefix, const char * lpcszLogin, const char * pszRelativePath)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszPrefix);
         UNREFERENCED_PARAMETER(lpcszLogin);
         UNREFERENCED_PARAMETER(pszRelativePath);
         throw interface_only_exception("this is an interface");
      }

      string system::userquicklaunch(::ca::application * papp, const char * lpcszRelativePath, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcszRelativePath);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::userprograms(::ca::application * papp, const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(papp);
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      string system::commonprograms(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         throw interface_only_exception("this is an interface");
      }

      bool system::is_inside_time(const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception("this is an interface");
      }

      bool system::is_inside(const char * pszDir, const char * pszPath, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(pszDir);
         UNREFERENCED_PARAMETER(pszPath);
         throw interface_only_exception("this is an interface");
      }

      string system::sensitive_ccvotagus(const char * lpcsz, const char * lpcsz2)
      {
         UNREFERENCED_PARAMETER(lpcsz);
         UNREFERENCED_PARAMETER(lpcsz2);
         return path(ca2("ccvotagus"), lpcsz, lpcsz2);
      }
 
   }  // namespace dir

} // namespace ca
