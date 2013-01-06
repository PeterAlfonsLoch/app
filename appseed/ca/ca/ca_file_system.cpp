#include "framework.h"


#ifndef WINDOWS
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#endif


struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


namespace ca
{


   namespace file
   {


      bool system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
      {
         string stra(lpszFilPathA);
         string wstrb(lpszFilPathB);

      //   gen::international::ACPToUnicode(stra, lpszFilPathA);
      //   gen::international::ACPToUnicode(wstrb, lpszFilPathB);
         if(stra == wstrb)
            return true;

         /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
            return false;
         if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
            return false;*/
         return stra == wstrb;

      }


      bool system::path::eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator)
      {

         strsize iLast = str.length() - 1;

         if(iLast < 0)
            return iLevelCount <= 0;

         while(str[iLast] == '/' || str[iLast] == '\\')
            iLast--;

         for(int32_t i = 0; i < iLevelCount; i++)
         {

            strsize iFind1 = str.reverse_find('/', iLast);

            strsize iFind2 = str.reverse_find('\\', iLast);

            strsize iFind = max(iFind1, iFind2);

            if(iFind >= iLast)
               return false;

            if(iFind < 0)
               return false;

            iLast = iFind;

            while(str[iLast] == '/' || str[iLast] == '\\')
               iLast--;

         }

         str.Truncate(iLast + 1);

         return true;

      }

      bool system::path::is_relative(const char * psz)
      {
         string strPath(psz);
         if(strPath.find(':') != -1 && strPath.find(':') < 10)
            return false;
         if(strPath.find('/') == 0 || strPath.find('\\') == 0)
            return false;
         return true;
      }

      void system::get_ascendants_path(const char * lpcsz, stringa & straParam)
      {
         stringa stra;
         get_ascendants_name(lpcsz, stra);
         string str;
         bool bUrl = System.url().is_url(lpcsz);
#ifdef LINUX
         bool bLinux = true;
         str += "/";
#else
         bool bLinux = false;
#endif

         for(int32_t i = 0; i < stra.get_size(); i++)
         {
            str += stra[i];
            if(stra[i].find('/') < 0 && stra[i].find('\\') < 0)
            {
               str += "\\";
            }
            if(bUrl || bLinux)
            {
               str.replace("\\", "/");
            }
            else
            {
               str.replace("/", "\\");
            }
            straParam.add(str);
         }
      }

      void system::get_ascendants_name(const char * lpcsz, stringa & straParam)
      {
         stringa straSeparator;
         straSeparator.add("/");
         straSeparator.add("\\");
         straParam.add_smallest_tokens(lpcsz, straSeparator, FALSE);
         if(straParam.get_count() > 0)
         {
            strsize iFind = straParam[0].find(':');
            if(iFind >= 2)
            {
               straParam[0] += "//";
            }
            else if(iFind == 1)
            {
               straParam[0] += "\\";
            }
         }
      }

      var system::length(const char * pszPath)
      {

         var varRet;

#ifdef WINDOWS

         WIN32_FILE_ATTRIBUTE_DATA data;

         if(!GetFileAttributesExW(gen::international::utf8_to_unicode(pszPath), GetFileExInfoStandard, &data))
         {
            varRet.set_type(var::type_null);
         }
         else
         {
            varRet = (uint32_t) data.nFileSizeLow;
         }

#else

         struct stat stat;

         if(::stat(pszPath, &stat)  == -1)
         {
            varRet.set_type(var::type_null);
         }
         else
         {
            varRet = stat.st_size;
         }

#endif

         return varRet;

      }


      string system::time_square(::ca::application * papp, const char * pszPrefix, const char * pszSuffix)
      {
         string str;
         System.dir().time_square(str);
         return time(papp, str, 25, pszPrefix, pszSuffix);
      }

      string system::time_log(::ca::application * papp, const char * pszId)
      {
         return time(papp, System.dir().time_log(pszId), 9);
      }

      string system::time(::ca::application * papp, const char * psz, int32_t iMaxLevel, const char * pszPrefix, const char * pszSuffix)
      {
         mutex_lock lockMachineEvent(
            (&System.machine_event_central() != NULL) ?
               System.machine_event_central().m_machineevent.m_mutex
               : *((simple_mutex *) NULL), true);
         int32_t iIncLevel = -1;
         string str;
         string strPrefix(pszPrefix);
         string strSuffix(pszSuffix);
      restart:
         str.Empty();
         str = psz;
         System.dir().mk(str, papp);
         stringa straTitle;
         string strFormat;
         for(int32_t i = 1; i <= iMaxLevel;)
         {
            System.dir().mk(str, papp);
           if(!System.dir().is(str, papp))
              throw "time square dir does not exist";
           straTitle.remove_all();
            System.dir().ls(papp, str, NULL, &straTitle);
            if(i < iMaxLevel)
            {
               int32_t iMax = filterex_time_square("", straTitle);
               if(iMax == -1)
               {
                  str = System.dir().path(str, "00");
                  System.dir().mk(str, papp);
               }
               else if(iMax == 99)
               {
                  iIncLevel = i - 1;
                  goto restart;
               }
               else
               {
                  if(i == iIncLevel)
                  {
                     iMax++;
                  }
                  strFormat.Format("%02d", iMax);
                  str = System.dir().path(str, strFormat);
                  if(i == iIncLevel)
                  {
                     System.dir().mk(str, papp);
                  }
               }
               i++;
            }
            else // if i == iMaxLevel
            {
               System.dir().ls(papp, str, NULL, &straTitle);
               int32_t iMax = filterex_time_square(pszPrefix, straTitle);
               if(iMax == -1)
               {
                  str = System.dir().path(str, strPrefix+"00"+strSuffix);
                  if(system::mk_time(str))
                     break;
               }
               else if(iMax == 99)
               {
                  iIncLevel = iMaxLevel - 1;
                  goto restart;
               }
               else
               {
                  iMax++;
                  strFormat.Format("%02d", iMax);
                  str = System.dir().path(str, strPrefix+strFormat+strSuffix);
                  if(system::mk_time(str))
                     break;
               }
               return "";
            }
         }
         return str;
      }

      int32_t system::filterex_time_square(const char * pszPrefix, stringa & stra)
      {
         int32_t iMax = -1;
         int32_t iIndex;
         for(int32_t i = 0; i < stra.get_size(); i++)
         {
            string str = stra[i];
            if(gen::str::begins_eat_ci(str, pszPrefix))
            {
               if(str.get_length() < 2)
               {
                  stra.remove_at(i);
                  i--;
                  continue;
               }
               if(!isdigit((uchar) str[0]) || !isdigit((uchar) str[1]))
               {
                  stra.remove_at(i);
                  i--;
                  continue;
               }
               iIndex = atoi(str.Mid(0, 2));
               if(iIndex > iMax)
                  iMax = iIndex;
            }
         }
         return iMax;
      }

      // fail if exists, create if not exists
      bool system::mk_time(const char * lpcszCandidate)
      {
         ex1::filesp spfile(get_app());
         if(System.file().exists(lpcszCandidate, get_app()))
            return false;
         try
         {
            if(!spfile->open(lpcszCandidate, ::ex1::file::mode_create | ::ex1::file::type_binary))
               return false;
         }
         catch(...)
         {
            return false;
         }
         return true;
      }

      string system::as_string(var varFile, ::ca::application * papp)
      {
          var varQuery;
          return as_string(varFile, varQuery, papp);
      }

      string system::as_string(var varFile, var & varQuery, ::ca::application * papp)
      {
         primitive::memory storage;
         if(varFile.ca2 < ::ex1::file > () != NULL)
         {
            storage.FullLoad(*varFile.ca2 < ::ex1::file >());
         }
         else
         {
            string strFilePath(varFile);
            if(papp->m_bZipIsDir && (gen::str::find_ci(".zip:", strFilePath) >= 0))
            {
               gen::memory_file memfile(papp, &storage);
               zip::InFile infile(get_app());
               if(!infile.unzip_open(strFilePath, 0))
                  return "";
               if(!infile.dump(&memfile))
                  return "";
            }
            else if(gen::str::begins_eat_ci(strFilePath, "file:///"))
            {
               as_memory(strFilePath, storage, papp);
            }
            else if(gen::str::begins_eat_ci(strFilePath, "file:\\\\\\"))
            {
               as_memory(strFilePath, storage, papp);
            }
            else if(gen::str::begins_ci(strFilePath, "http://")
            || gen::str::begins_ci(strFilePath, "https://"))
            {
               gen::property_set post;
               gen::property_set headers;
               if(varQuery.has_property("post"))
               {
                  post = varQuery["post"].propset();
               }
               if(varQuery.has_property("in_headers"))
               {
                  headers = varQuery["in_headers"].propset();
               }
               if(varQuery.propset()["disable_ca2_sessid"])
               {
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), NULL, NULL);
               }
               else if(varQuery.propset()["optional_ca2_sessid"])
               {
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), NULL, NULL);
               }
               else if(strFilePath.contains("/matter.ca2.cc/") || strFilePath.contains(".matter.ca2.cc/"))
               {
                  try
                  {
                     storage.FullLoad(App(papp).get_file(strFilePath, ::ex1::file::type_binary | ::ex1::file::mode_read));
                  }
                  catch(...)
                  {
                  }
               }
               else
               {
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), NULL, &AppUser(papp));
               }
               varQuery["out_headers"] = headers;
            }
            else
            {
               as_memory(strFilePath, storage, papp);
            }
         }
         string strResult;
         if(storage.get_size() >= 2
         && storage.get_data()[0] == 255
         && storage.get_data()[1] == 60)
         {
            gen::international::unicode_to_utf8(strResult, (const wchar_t *) &storage.get_data()[2], (int32_t)(storage.get_size() - 2));
         }
         else if(storage.get_size() >= 3
         && storage.get_data()[0] == 0xef
         && storage.get_data()[1] == 0xbb
         && storage.get_data()[2] == 0xbf)
         {
            strResult = string((const char *) (const wchar_t *) &storage.get_data()[3], (int32_t) (storage.get_size() - 3));
         }
         else
         {
            strResult = string((const char *) storage.get_data(), (int32_t) storage.get_size());
         }

         return strResult;
      }

      void system::as_memory(var varFile, primitive::memory_base & mem, ::ca::application * papp)
      {

         mem.allocate(0);

         if(varFile.get_type() == var::type_string)
         {

            string strPath = varFile.get_string();

            if(strPath.is_empty())
            {

               TRACE("::ca::file::system::as_memory varFile is a empty file name!!");

               return;

            }

            strPath.trim("\"'");

            if((gen::str::begins(strPath, "http://") || gen::str::begins(strPath, "https://")))
            {

               App(papp).http().get(strPath, mem, &AppUser(papp));

               return;

            }

         }

         ex1::filesp spfile;

         try
         {

            spfile = App(papp).get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone);

            mem.FullLoad(spfile);

         }
         catch(...)
         {
         }



      }

      void system::lines(stringa & stra, var varFile, ::ca::application * papp)
      {
         UNREFERENCED_PARAMETER(papp);
         ex1::text_file_sp spfile(get_app());

         try
         {
            if(!spfile->open(varFile, ::ex1::file::type_text | ::ex1::file::mode_read))
            {
               return;
            }
         }
         catch(...)
         {
            return;
         }
         string strLine;
         while(spfile->read_string(strLine))
         {
            stra.add(strLine);
         }

      }

      bool system::put_contents(var varFile, const void * pvoidContents, count count, ::ca::application * papp)
      {

         ex1::filesp spfile;

         spfile = App(papp).get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_write | ::ex1::file::mode_create | ::ex1::file::shareDenyNone | ::ex1::file::defer_create_directory);

         if(spfile.is_null())
            return false;

         spfile->write(pvoidContents, count);

         return true;

      }

      bool system::put_contents(var varFile, const char * lpcszContents, ::ca::application * papp)
      {
         if(lpcszContents == NULL)
         {
            return put_contents(varFile, "", 0, papp);
         }
         else
         {
            return put_contents(varFile, lpcszContents, strlen(lpcszContents), papp);
         }
      }

      bool system::put_contents(var varFile, ex1::file & file, ::ca::application * papp)
      {
         ex1::filesp spfile;
         spfile = App(papp).get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_write | ::ex1::file::mode_create | ::ex1::file::shareDenyNone | ::ex1::file::defer_create_directory);
         if(spfile.is_null())
            return false;
         primitive::memory mem;
         mem.allocate(1024 * 1024 * 8);
         ::primitive::memory_size uiRead;
         while((uiRead = file.read(mem.get_data(), mem.get_size())) > 0)
         {
            spfile->write(mem.get_data(), uiRead);
         }
         return true;
      }

      bool system::put_contents(var varFile, primitive::memory & mem, ::ca::application * papp)
      {
         return put_contents(varFile, mem.get_data(), (count) mem.get_size(), papp);
      }

      bool system::put_contents_utf8(var varFile, const char * lpcszContents, ::ca::application * papp)
      {
         ex1::filesp spfile;
         spfile = App(papp).get_file(varFile, ::ex1::file::type_binary | ::ex1::file::mode_write | ::ex1::file::mode_create | ::ex1::file::shareDenyNone | ::ex1::file::defer_create_directory);
         if(spfile.is_null())
            return false;
         ::ex1::byte_output_stream(spfile) << "\xef\xbb\xbf";
         spfile->write(lpcszContents, strlen(lpcszContents));
         return true;
      }

      void system::path::split(stringa & stra, const char * lpcszPath)
      {
         stringa straSeparator;
         straSeparator.add("\\");
         straSeparator.add("/");
         stra.add_smallest_tokens(lpcszPath, straSeparator, FALSE);
      }

      class system::path & system::path()
      {
         return m_path;
      }

      system::system()
      {
      }

      string system::title_(const char * path)
      {

         string str = name_(path);

         strsize iPos = str.reverse_find('.');

         if(iPos >= 0)
         {
            return str.Mid(0, iPos);
         }
         else
         {
            return str;
         }

      }

      string system::name_(const char * path)
      {

         string str(path);

         while(gen::str::ends_eat(str, "\\"));

         while(gen::str::ends_eat(str, "/"));

         strsize iPos;

         strsize iPos1 = str.reverse_find('\\');

         strsize iPos2 = str.reverse_find('/');

         if(iPos1 >= 0 && iPos2 >= 0)
         {

            if(iPos1 > iPos2)
            {

               iPos = iPos1 + 1;

            }
            else
            {

               iPos = iPos2 + 1;

            }

         }
         else if(iPos1 >= 0)
         {

            iPos = iPos1 + 1;

         }
         else if(iPos2 >= 0)
         {

            iPos = iPos2 + 1;

         }
         else
         {

            iPos = 0;

         }

         return str.Mid(iPos);

      }

      string system::extension(const char * path)
      {

         string str = name_(path);

         strsize iPos = str.reverse_find('.');

         if(iPos >= 0)
         {

            return str.Mid(iPos + 1);

         }
         else
         {

            return "";

         }

      }

      void system::copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::ca::application * papp)
      {
         if(bFailIfExists)
         {
            if(exists(pszNew, papp))
               throw "Failed to copy file";
         }
         if(System.dir().is(psz, papp) && (eextract == extract_first || eextract == extract_all || !(gen::str::ends_ci(psz, ".zip"))))
         {
            stringa straPath;
            System.dir().rls(papp, psz, &straPath);
            string strDst;
            string strSrc;
            string strDirSrc(psz);
            string strDirDst(pszNew);
            if(papp->m_bZipIsDir && (gen::str::ends(strDirSrc, ".zip")))
            {
               strDirSrc += ":";
            }
            for(int32_t i = 0; i < straPath.get_size(); i++)
            {
               strSrc = straPath[i];
               strDst = strSrc;
               gen::str::begins_eat_ci(strDst, strDirSrc);
               strDst = System.dir().path(strDirDst, strDst);
               if(System.dir().is(strSrc, papp))
               {
                  if((eextract == extract_first || eextract == extract_none) && (gen::str::ends_ci(psz, ".zip")))
                  {
                  }
                  else
                  {
                     System.dir().mk(strDst, papp);
                  }
               }
               else
               {
                  if(!System.dir().is(System.dir().name(strDst), papp))
                  {
                     System.dir().mk(System.dir().name(strDst), papp);
                  }
                  copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none, papp);
               }
            }
         }
         else
         {

            string strNew;

            if(System.dir().is(pszNew, papp))
            {
               strNew = System.dir().path(pszNew, name_(psz));
            }
            else
            {
               strNew = pszNew;
            }

            ::ex1::filesp ofile;
            ofile = App(papp).get_file(strNew, ex1::file::mode_write | ex1::file::type_binary | ex1::file::mode_create | ex1::file::defer_create_directory | ::ex1::file::shareDenyWrite);
            if(ofile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            ::ex1::filesp ifile;
            ifile = App(papp).get_file(psz, ::ex1::file::mode_read | ::ex1::file::type_binary | ::ex1::file::shareDenyNone);
            if(ifile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            System.compress().null(ofile, ifile);



            bool bOutputFail = false;
            bool bInputFail = false;
            try
            {
               ofile->close();
            }
            catch(...)
            {
               bOutputFail = true;
            }

            ::ex1::file_status st;

            ifile->GetStatus(st);

            System.os().set_file_status(strNew, st);

            try
            {
               ifile->close();
            }
            catch(...)
            {
               bInputFail = true;
            }
            if(bInputFail)
            {
               if(bOutputFail)
               {
                  string strError;
                  strError.Format("During copy, failed to close both input file \"%s\" and output file \"%s\" bFailIfExists=%d", psz, pszNew, bFailIfExists);
                  throw strError;
               }
               else
               {
                  string strError;
                  strError.Format("During copy, failed to close input file \"%s\" bFailIfExists=%d", psz, bFailIfExists);
                  throw strError;
               }
            }
            else if(bOutputFail)
            {
               string strError;
               strError.Format("During copy, failed to close output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);
               throw strError;
            }

         }

      }

      void system::move(const char * pszNew, const char * psz)
      {
#ifdef WINDOWSEX
         if(!::MoveFileW(
            gen::international::utf8_to_unicode(psz),
            gen::international::utf8_to_unicode(pszNew)))
         {
            uint32_t dwError = ::GetLastError();
            string strError;
            strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
            throw strError;
         }
#elif defined(METROWIN)

         ::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, NULL, OPEN_EXISTING, 0, NULL);

         if(file == nullptr)
            throw "file::system::move Could not move file, could not open source file";

         string strDirOld     = System.dir().name(psz);
         string strDirNew     = System.dir().name(pszNew);
         string strNameOld    = System.file().name_(psz);
         string strNameNew    = System.file().name_(pszNew);

         if(strDirOld == strDirNew)
         {
            if(strNameOld == strNameNew)
            {
               return;
            }
            else
            {
               ::wait(file->RenameAsync(rtstr(strNameNew)));
            }
         }
         else
         {
            ::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
            if(strNameOld == strNameNew)
            {
               ::wait(file->MoveAsync(folder));
            }
            else
            {
               ::wait(file->MoveAsync(folder, rtstr(strNameNew)));
            }
         }


#else
         if(rename(psz, pszNew) != 0)
         {
            int32_t err = errno;
            string strError;
            strError.Format("Failed to delete file error=%d", err);
            throw strError;
         }
#endif
      }

      void system::del(const char * psz)
      {
#ifdef WINDOWS
         if(!::DeleteFileW(
            gen::international::utf8_to_unicode(psz)))
         {
            uint32_t dwError = ::GetLastError();
            if(dwError == 2) // the file does not exist, so delete "failed"
               return;
            string strError;
            strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
            throw strError;
         }
#else
         if(remove(psz) != 0)
         {
            int32_t err = errno;
            string strError;
            strError.Format("Failed to delete file error=%d", err);
            throw strError;
         }
#endif

      }


      string system::copy(const char * psz, ::ca::application * papp)
      {
         string strCopy("copy");
         string strNew;
         if(System.dir().is(psz, papp))
         {
            int32_t i = 1;
            while( i <= 100)
            {
               strNew.Format("%s-%s-%d", psz, strCopy.c_str(), i);
               if(!exists(strNew, papp))
               {
                  copy(strNew, psz, false, extract_all, papp);
                  return strNew;
               }
               i++;
            }
         }
         else
         {
            string strExt = extension(psz);
            if(!strExt.is_empty())
            {
               strExt = "-" + strExt;
            }
            int32_t i = 1;
            while( i <= 100)
            {
               strNew.Format("%s-%s-%d%s", psz, strCopy.c_str(), i, strExt.c_str());
               if(!exists(strNew, papp))
               {
                  copy(strNew, psz, false, extract_all, papp);
                  return strNew;
               }
               i++;
            }
         }
         return "";
      }


      bool system::exists(const char * pszPath, ::ca::application * papp)
      {

         if(gen::str::begins_ci_iws(pszPath, "uifs://"))
         {
            return AppUser(papp).m_pifs->file_exists(pszPath);
         }
         else if(gen::str::begins_ci_iws(pszPath, "http://") || gen::str::begins_ci_iws(pszPath, "https://"))
         {
            return App(papp).http().exists(pszPath);
         }

         if(papp->m_bZipIsDir)
         {

            strsize iFind = gen::str::find_ci(".zip:", pszPath);

            zip::Util ziputil;

            if(iFind >= 0)
               return ziputil.exists(papp, pszPath);

            if(!Sys(papp).dir().name_is(pszPath, papp))
               return false;

         }

#ifdef WINDOWS


         return file_exists_dup(pszPath);

         //return ::GetFileAttributesW(gen::international::utf8_to_unicode(pszPath)) != INVALID_FILE_ATTRIBUTES;

#else

         struct stat st;

         if(stat(pszPath, &st) != 0)
            return false;

         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

      }


      bool system::exists(const string & strPath, ::ca::application * papp)
      {

         if(gen::str::begins_ci_iws(strPath, "uifs://"))
         {
            return AppUser(papp).m_pifs->file_exists(strPath);
         }

         if(gen::str::begins_ci_iws(strPath, "http://")
         || gen::str::begins_ci_iws(strPath, "https://"))
         {
            return App(papp).http().exists(strPath);
         }


         if(papp->m_bZipIsDir)
         {

            strsize iFind = gen::str::find_ci(".zip:", strPath);

            zip::Util ziputil;

            if(iFind >= 0)
            {

               if(!exists(strPath.Mid(0, iFind + 4), papp))
                  return false;

               return ziputil.exists(papp, strPath);

            }


         }

         //if(!papp->m_psystem->dir().name_is(strPath, papp))
           // return false;

#ifdef WINDOWS


         return file_exists_dup(strPath);
           // return true;

         //return App(papp).m_spfsdata->file_exists(strPath);
         //return ::GetFileAttributesW(gen::international::utf8_to_unicode(strPath)) != INVALID_FILE_ATTRIBUTES;

#else

         struct stat st;

         if(stat(strPath, &st) != 0)
            return false;

         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

      }

      string system::paste(const char * pszLocation, const char * path, ::ca::application * papp)
      {
         string strDir = System.dir().name(path);
         string strDest = System.dir().path(pszLocation, "");
         string strSrc = System.dir().path(strDir, "");
         if(strDest == strSrc)
         {
            return copy(path, papp);
         }
         else
         {
            string strNew = System.dir().path(strDest, name_(path));
            copy(strNew, path, false, extract_all, papp);
            return strNew;
         }
      }

      void system::trash_that_is_not_trash(stringa & stra, ::ca::application * papp)
      {

         if(stra.get_size() <= 0)
            return;

         string strDir = System.dir().trash_that_is_not_trash(stra[0]);

         System.dir().mk(strDir, papp);

         for(int32_t i = 0; i < stra.get_size(); i++)
         {
#ifdef WINDOWS
            move(System.dir().path(strDir, name_(stra[i])), stra[i]);
#else
            ::rename(stra[i], System.dir().path(strDir, name_(stra[i])));
#endif
         }

      }

      void system::trash_that_is_not_trash(const char * psz, ::ca::application * papp)
      {

         string strDir = System.dir().trash_that_is_not_trash(psz);

         System.dir().mk(strDir, papp);

#ifdef WINDOWS
//         ::MoveFile(psz, System.dir().path(strDir, name_(psz)));
         move(System.dir().path(strDir, name_(psz)), psz);
#else
         ::rename(psz, System.dir().path(strDir, name_(psz)));
#endif

      }

      void system::replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::ca::application * papp)
      {
         stringa straTitle;
         System.dir().ls(papp, pszContext, NULL, &straTitle);
         string strOld;
         string strNew;
         for(int32_t i = 0; i < straTitle.get_size(); i++)
         {
            strOld = straTitle[i];
            strNew = strOld;
            strNew.replace(pszFind, pszReplace);
            if(strNew != strOld)
            {
#ifdef WINDOWS
//               ::MoveFileW(
  //                gen::international::utf8_to_unicode(System.dir().path(pszContext, strOld)),
    //              gen::international::utf8_to_unicode(System.dir().path(pszContext, strNew)));
               move(System.dir().path(pszContext, strNew), System.dir().path(pszContext, strOld));
#else
               ::rename(
                  System.dir().path(pszContext, strOld),
                  System.dir().path(pszContext, strNew));
#endif
            }
         }
      }

      bool system::is_read_only(const char * psz)
      {

#ifdef WINDOWSEX

         uint32_t dwAttrib = GetFileAttributesW(gen::international::utf8_to_unicode(psz));
         if(dwAttrib & FILE_ATTRIBUTE_READONLY)
            return true;
         return false;

#elif defined(METROWIN)

         throw todo(get_app());

#else

         struct stat st;

         if(stat(psz, &st) != 0)
            return true;

         return !(st.st_mode & S_IWUSR);

#endif

      }

      string system::sys_temp(const char * pszName, const char * pszExtension, ::ca::application * papp)
      {

         string strTempDir = get_sys_temp_path();

         if(!gen::str::ends(strTempDir, "\\") && !gen::str::ends(strTempDir, "/"))
         {

            strTempDir += "\\";

         }

         string str;

         char buf[30];

         for(int32_t i = 0; i < 1000; i++)
         {

            sprintf(buf, "%d", i);

            str = strTempDir;
            str += pszName;
            str += "-";
            str += buf;
            str += ".";
            str += pszExtension;
            if(!exists(str, papp))
               return str;
         }

         return "";

      }

      string system::sys_temp_unique(const char * pszName)
      {

         return System.dir().path(get_sys_temp_path(), pszName);

      }

      ex1::filesp system::time_square_file(::ca::application * papp, const char * pszPrefix, const char * pszSuffix)
      {

         return get(time_square(papp, pszPrefix, pszSuffix), papp);

      }

      ex1::filesp system::get(const char * name, ::ca::application * papp)
      {

         System.dir().mk(System.dir().name(name), papp);

         ex1::filesp fileOut = App(papp).get_file(name, ::ex1::file::mode_create | ::ex1::file::type_binary | ::ex1::file::mode_write);

         if(fileOut.is_null())
            throw ex1::file_exception(papp, -1, ::ex1::file_exception::none, name);

         return fileOut;

      }

      string system::replace_extension(const char * pszFile, const char * pszExtension)
      {
         string strFile(pszFile);
         set_extension(strFile, pszExtension);
         return strFile;
      }

      void system::set_extension(string & strFile, const char * pszExtension)
      {
         strsize iEnd = strFile.reverse_find('.');
         if(iEnd < 0)
            iEnd = strFile.get_length();
         strFile = strFile.Left(iEnd) + gen::str::has_char(pszExtension, ".");
      }

   } // namespace file


} // namespace ca2






#include "OpenedFiles.h"

#if !defined(LINUX) && !defined(MACOS) && !defined(METROWIN)

#include <Tlhelp32.h>
#include <Psapi.h>


void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext );
void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext, HANDLE hDriver, GetFinalPathNameByHandleDef pGetFinalPathNameByHandle );

const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")


// This Function install the driver and starts it
HANDLE OnlyGetDrv()
{


        HMODULE hModule = GetModuleHandle(_T("ca2.dll"));
        if( !hModule )
        {
            OutputDebugStringW( L"GetModuleHandle(_T(\"ca2.dll\")); failed" );
            return 0;
        }
        string csFilePath;
        LPTSTR lpPath = csFilePath.GetBuffer( MAX_PATH );
        GetModuleFileName( hModule,lpPath , MAX_PATH );
        PathRemoveFileSpec( lpPath );
        csFilePath.ReleaseBuffer();
        if(IsWow64())
        {
         csFilePath += DRIVER_FILE_NAME_64;
        }
        else
        {
           csFilePath += DRIVER_FILE_NAME_32;
        }

        if( !PathFileExists( csFilePath ))
        {
            MessageBox(NULL, "Cannot find driver " + csFilePath, "Cannot find driver " + csFilePath, MB_OK );
            return 0;
        }



	// Delete the temp file...
	//DeleteFile( csPath );
	HANDLE hFile = CreateFile( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE,
								FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
								OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
	return hFile;
}

extern "C" __declspec(dllexport) void GetOpenedFiles( LPCWSTR lpPath, OF_TYPE Filter, OF_CALLBACK CallBackProc,
													  uint_ptr pUserContext )
{
	string csPath = lpPath;
	csPath.make_lower();
	EnableTokenPrivilege( SE_DEBUG_NAME );
	if( Filter& MODULES_ONLY )
	{
		EnumerateLoadedModules( csPath, CallBackProc, pUserContext );
	}

	if( Filter& FILES_ONLY )
	{


		// Extract the driver from the resource and install it.
		//HANDLE hDriver = ExtractAndInstallDrv();
      //HANDLE hDriver = OnlyGetDrv();
      HANDLE hDriver = NULL;
		GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = 0;
		if(  !hDriver )
		{
			pGetFinalPathNameByHandle = (GetFinalPathNameByHandleDef)GetProcAddress( GetModuleHandle(_T("kernel32.dll")), "GetFinalPathNameByHandleW" );
		}
		// Now walk all handles
		EnumerateOpenedFiles( csPath, CallBackProc, pUserContext, hDriver, pGetFinalPathNameByHandle );
		//if( hDriver )
		{	// Time to wind up
			//StopAndUninstallDrv( hDriver );
		}
	}
}

UINT g_CurrentIndex = 0;
struct THREAD_PARAMS
{
	PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
	GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
	LPWSTR lpPath;
	int32_t nFileType;
	HANDLE hStartEvent;
	HANDLE hFinishedEvent;
	bool bStatus;
};

uint32_t ThreadProc(void * lParam)
{
	THREAD_PARAMS* pThreadParam = (THREAD_PARAMS*)lParam;

   FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)new BYTE[MAX_PATH * 8];

	GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
	for( g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;  )
	{

		WaitForSingleObject( pThreadParam->hStartEvent, INFINITE );
		ResetEvent( pThreadParam->hStartEvent );
		pThreadParam->bStatus = false;
		SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
		g_CurrentIndex++;
		HANDLE hDup = (HANDLE)sh.wValue;
		HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE , FALSE, sh.dwProcessId );
		if( hProcess )
		{
			bool b = DuplicateHandle( hProcess, (HANDLE)sh.wValue, GetCurrentProcess(), &hDup, 0, FALSE, DUPLICATE_SAME_ACCESS ) != FALSE;
			if( !b )
			{
				hDup = (HANDLE)sh.wValue;
			}
			CloseHandle( hProcess );
		}
		//uint32_t dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //uint32_t dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
      uint32_t dwRet = GetFinalPathNameByHandleW( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //wcsncpy(pThreadParam->lpPath, pinfo->FileName, pinfo->FileNameLength);
		if( hDup && (hDup != (HANDLE)sh.wValue))
		{
			CloseHandle( hDup );
		}
		if(dwRet)
		{
			pThreadParam->bStatus = true;
		}
		SetEvent( pThreadParam->hFinishedEvent );

	}
   delete[] (BYTE *) pinfo;
	return 0;
}

void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext, HANDLE hDriver,
						   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle )
{
	int32_t nFileType = XP_FILETYPE;
	OSVERSIONINFO info = { 0 };
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&info);
	if( info.dwMajorVersion == 6 &&
		info.dwMinorVersion == 0 )
	{
		nFileType = VISTA_FILETYPE;
	}
	LPCTSTR lpPath = csPath;
	string csShortName;
	GetShortPathName( csPath, csShortName.GetBuffer( MAX_PATH), MAX_PATH );
	csShortName.ReleaseBuffer();
	csShortName.make_lower();
	bool bShortPath = false;
	LPCTSTR lpShortPath = csShortName;
	if(  csShortName != csPath && FALSE == csShortName.is_empty())
	{
		bShortPath = true;
	}

	HMODULE hModule = GetModuleHandle(_T("ntdll.dll"));
	PNtQuerySystemInformation NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress( hModule, "NtQuerySystemInformation" );
	if( 0 == NtQuerySystemInformation )
	{
		OutputDebugStringW( L"Getting proc of NtQuerySystemInformation failed" );
		return;
	}

	// Get the list of all handles in the system
	PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
	uint32_t size = sizeof(SYSTEM_HANDLE_INFORMATION);
	DWORD needed = 0;
	NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
	if( !NT_SUCCESS(status))
	{
		if( 0 == needed )
		{
			return;// some other error
		}
		// The previously supplied buffer wasn't enough.
		delete pSysHandleInformation;
		size = needed + 1024;
		pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)new BYTE[size];
		status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
		if( !NT_SUCCESS(status))
		{
			// some other error so quit.
			delete pSysHandleInformation;
			return;
		}
	}

	if( pGetFinalPathNameByHandle )// there is no driver, we have do it ugly way
	{
		g_CurrentIndex = 0;
//		TCHAR tcFileName[MAX_PATH+1];
		THREAD_PARAMS ThreadParams;
      wstring wstrFileName;

      wstrFileName.alloc(MAX_PATH * 8);
		ThreadParams.lpPath = wstrFileName;
		ThreadParams.nFileType = nFileType;
		ThreadParams.pGetFinalPathNameByHandle = pGetFinalPathNameByHandle;
		ThreadParams.pSysHandleInformation = pSysHandleInformation;
		ThreadParams.hStartEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
		ThreadParams.hFinishedEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
		HANDLE ThreadHandle = 0;
		while( g_CurrentIndex < pSysHandleInformation->dwCount )
		{
			if( !ThreadHandle )
			{
				ThreadHandle = create_thread( 0, 0, ThreadProc, &ThreadParams, 0, 0 );
			}
			ResetEvent( ThreadParams.hFinishedEvent );
			SetEvent( ThreadParams.hStartEvent );
			if( WAIT_TIMEOUT == WaitForSingleObject( ThreadParams.hFinishedEvent, 100 ))
			{
				string csError;
				csError.Format("Query hang for handle %d", (int32_t)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue);
				OutputDebugString(csError );
				TerminateThread( ThreadHandle, 0 );
				CloseHandle( ThreadHandle );
				ThreadHandle = 0;
				continue;
			}
			if( !ThreadParams.bStatus )
			{
				continue;
			}
			int32_t nCmpStart = 4;
			string csFileName( gen::international::unicode_to_utf8(&ThreadParams.lpPath[nCmpStart]));
			csFileName.make_lower();
         if(csFileName.find("vs11_dp_ctp") >= 0)
         {
            continue;
         }
			else if( 0 != _tcsncmp( lpPath, csFileName , csPath.get_length()))
			{
				continue;
			}
			OF_INFO_t stOFInfo;
			stOFInfo.dwPID = pSysHandleInformation->Handles[g_CurrentIndex - 1].dwProcessId;
         wstring wstrCallback;
         wstrCallback = gen::international::utf8_to_unicode(csFileName);
			stOFInfo.lpFile = wstrCallback;
			stOFInfo.hFile  = (HANDLE)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue;
			CallBackProc( stOFInfo, pUserContext );
		}
		if( ThreadHandle )
		{
			if( WAIT_TIMEOUT == WaitForSingleObject( ThreadHandle, 1000 ))
			{
				TerminateThread( ThreadHandle, 0 );
			}
			CloseHandle( ThreadHandle );
		}
		CloseHandle( ThreadParams.hStartEvent );
		CloseHandle( ThreadParams.hFinishedEvent );
		return;
	}

	// Walk through the handle list
	for ( uint32_t i = 0; i < pSysHandleInformation->dwCount; i++ )
	{
		SYSTEM_HANDLE& sh = pSysHandleInformation->Handles[i];
		if( sh.bObjectType != nFileType )// Under windows XP file handle is of type 28
		{
			continue;
		}

		string csFileName;
		string csDir;
		if( hDriver )
		{
			HANDLE_INFO stHandle = {0};
			ADDRESS_INFO stAddress;
			stAddress.pAddress = sh.pAddress;
			DWORD dwReturn = 0;
			bool bSuccess = DeviceIoControl( hDriver, IOCTL_LISTDRV_BUFFERED_IO, &stAddress, sizeof(ADDRESS_INFO), &stHandle, sizeof(HANDLE_INFO), &dwReturn, NULL ) != FALSE;


			if( bSuccess && stHandle.tcFileName[0] != 0 &&
				stHandle.uType != FILE_DEVICE_SOUND &&
				stHandle.uType != FILE_DEVICE_NAMED_PIPE )
			{

				if( stHandle.uType != FILE_DEVICE_NETWORK_FILE_SYSTEM  )
				{
					// Get the drive name from the dos device name
					if( !GetDrive( (LPCTSTR)stHandle.tcDeviceName, csFileName, true ))
					{
						OutputDebugStringW( L"GetDrive failed" );
					}
					csFileName += (LPCTSTR)stHandle.tcFileName;
				}
				else
				{
					csFileName = _T("\\");
					csFileName += (LPCTSTR)stHandle.tcFileName;
				}
			}
            else
            {
                continue;
            }
		}
		else
		{
			return;
		}


		csFileName.make_lower();
		// Check whether the file belongs to the specified folder
// 		if( -1 == csFileName.Find( csPath ))
// 		{
// 			if( bShortPath )
// 			{
// 				// Some times the file name may be in int16_t path form.
// 				if( -1 == csFileName.Find( csShortName ))
// 				{
// 					continue;
// 				}
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}

		if( 0 != _tcsncmp( lpPath, csFileName, csPath.get_length()))
		{
			if( bShortPath )
			{
				// Some times the file name may be in int16_t path form.
				if( 0 != _tcsncmp( lpShortPath, csFileName, csShortName.get_length()))
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
		OF_INFO_t stOFInfo;
		stOFInfo.dwPID = sh.dwProcessId;
      wstring wstrCallback;
      wstrCallback = gen::international::utf8_to_unicode(csFileName);
		stOFInfo.lpFile = wstrCallback;
		stOFInfo.hFile  = (HANDLE)sh.wValue;
		CallBackProc( stOFInfo, pUserContext );
	}
	delete pSysHandleInformation;

}


void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext )
{
	string csShortName;
	GetShortPathName( csPath, csShortName.GetBuffer( MAX_PATH), MAX_PATH );
	csShortName.ReleaseBuffer();
	csShortName.make_lower();
	bool bShortPath = false;
	if(  csShortName != csPath && FALSE == csShortName.is_empty())
	{
		bShortPath = true;
	}

	uint32_t dwsize = 300;
	PDWORD pDwId = (PDWORD)new BYTE[dwsize];
	DWORD dwReturned = dwsize;
	// Enum all the process first
	while( 1 )
	{
		EnumProcesses( pDwId, dwsize, &dwReturned );
		if( dwsize > dwReturned  )
		{
			break;
		}
		delete pDwId;
		dwsize += 50;
		pDwId = (PDWORD)new BYTE[dwsize];
	}
	int32_t nCount = dwReturned / sizeof(uint32_t);
	int32_t nItemCount = -1;
	// Enumerate modules of the above process
	for( int32_t nIdx = 0; nIdx < nCount;nIdx++ )
	{
		if( 0 != pDwId[nIdx] )
		{
			HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
			MODULEENTRY32 me32;
			// Take a snapshot of all modules in the specified process.
			hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pDwId[nIdx] );
			if( hModuleSnap == INVALID_HANDLE_VALUE )
			{
				continue;
			}
			me32.dwSize = sizeof( MODULEENTRY32 );
			if( !Module32First( hModuleSnap, &me32 ) )
			{
				CloseHandle( hModuleSnap );
				continue;
			}
			bool bFirst = true;
			PROCESS_INFO_t stInfo;
			do
			{
				string csModule;
				if( bFirst )
				{
					// First module is always the exe name
					bFirst = false;
					if( !PathFileExists( me32.szExePath ))
					{
						TCHAR tcFileName[MAX_PATH];
						HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, TRUE, pDwId[nIdx] );
						if( GetProcessImageFileName( hProcess, tcFileName, MAX_PATH ))
						{
							GetDrive( tcFileName, csModule, false );
						}
						CloseHandle( hProcess );
					}
					else
					{
						csModule = me32.szExePath;
					}
					csModule.make_lower();
				}
				else
				{
					csModule = me32.szExePath;
					csModule.make_lower();
				}
				if( -1 == csModule.find( csPath ))
				{
					if( bShortPath )
					{
						if( -1 == csModule.find( csShortName ))
						{
							continue;
						}
					}
					else
					{
						continue;
					}
				}
				OF_INFO_t stOFInfo;
				stOFInfo.dwPID = pDwId[nIdx];
            wstring wstrCallback;

            wstrCallback = gen::international::utf8_to_unicode(csModule);

				stOFInfo.lpFile = wstrCallback;
				CallBackProc( stOFInfo, pUserContext );
			}
			while( Module32Next( hModuleSnap, &me32 ) );
			CloseHandle( hModuleSnap );
		}
	}

	delete pDwId;

}



#endif // LINUX
