#include "framework.h"
#include "ca_opened_files.h"

#ifndef METROWIN
#include <openssl/ssl.h>
#include <openssl/md5.h>
#endif


#ifndef WINDOWS
#include <sys/stat.h>
#include <ctype.h>
#endif

CLASS_DECL_c void NESSIEinit(struct NESSIEstruct * const structpointer);
CLASS_DECL_c void NESSIEadd(const uchar * const source, uint_ptr sourceBits, struct NESSIEstruct * const structpointer);
CLASS_DECL_c void NESSIEfinalize(struct NESSIEstruct * const structpointer, uchar * const result);






struct PROCESS_INFO_t
{
    string csProcess;
    uint32_t dwImageListIndex;
};


namespace ca
{


      bool file_system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
      {
         string stra(lpszFilPathA);
         string wstrb(lpszFilPathB);

      //   ::ca::international::ACPToUnicode(stra, lpszFilPathA);
      //   ::ca::international::ACPToUnicode(wstrb, lpszFilPathB);
         if(stra == wstrb)
            return true;

         /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
            return false;
         if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
            return false;*/
         return stra == wstrb;

      }


      bool file_system::path::eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator)
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

      bool file_system::path::is_relative(const char * psz)
      {
         string strPath(psz);
         if(strPath.find(':') != -1 && strPath.find(':') < 10)
            return false;
         if(strPath.find('/') == 0 || strPath.find('\\') == 0)
            return false;
         return true;
      }

      void file_system::get_ascendants_path(const char * lpcsz, stringa & straParam)
      {
         stringa stra;
         get_ascendants_name(lpcsz, stra);
         string str;
         bool bUrl = System.url().is_url(lpcsz);
#if defined(LINUX) || defined(MACOS)
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

      void file_system::get_ascendants_name(const char * lpcsz, stringa & straParam)
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

      var file_system::length(const char * pszPath)
      {

         var varRet;

#ifdef WINDOWS

         WIN32_FILE_ATTRIBUTE_DATA data;

         if(!GetFileAttributesExW(::ca::international::utf8_to_unicode(pszPath), GetFileExInfoStandard, &data))
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


      string file_system::time_square(sp(::ca::application) papp, const char * pszPrefix, const char * pszSuffix)
      {
         string str;
         System.dir().time_square(str);
         return time(papp, str, 25, pszPrefix, pszSuffix);
      }

      string file_system::time_log(sp(::ca::application) papp, const char * pszId)
      {
         return time(papp, System.dir().time_log(pszId), 9);
      }

      string file_system::time(sp(::ca::application) papp, const char * psz, int32_t iMaxLevel, const char * pszPrefix, const char * pszSuffix)
      {
         mutex_lock lockMachineEvent(
            (&System.machine_event_central() != ::null()) ?
               System.machine_event_central().m_machineevent.m_mutex
               : *((simple_mutex *) ::null()), true);
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
            System.dir().ls(papp, str, ::null(), &straTitle);
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
               System.dir().ls(papp, str, ::null(), &straTitle);
               int32_t iMax = filterex_time_square(pszPrefix, straTitle);
               if(iMax == -1)
               {
                  str = System.dir().path(str, strPrefix+"00"+strSuffix);
                  if(file_system::mk_time(str))
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
                  if(file_system::mk_time(str))
                     break;
               }
               return "";
            }
         }
         return str;
      }

      int32_t file_system::filterex_time_square(const char * pszPrefix, stringa & stra)
      {
         int32_t iMax = -1;
         int32_t iIndex;
         for(int32_t i = 0; i < stra.get_size(); i++)
         {
            string str = stra[i];
            if(::ca::str::begins_eat_ci(str, pszPrefix))
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
      bool file_system::mk_time(const char * lpcszCandidate)
      {
         ::ca::filesp spfile(allocer());
         if(System.file().exists(lpcszCandidate, get_app()))
            return false;
         try
         {
            if(!spfile->open(lpcszCandidate, ::ca::file::mode_create | ::ca::file::type_binary))
               return false;
         }
         catch(...)
         {
            return false;
         }
         return true;
      }

      string file_system::as_string(var varFile, sp(::ca::application) papp)
      {
          var varQuery;
          return as_string(varFile, varQuery, papp);
      }

      string file_system::as_string(var varFile, var & varQuery, sp(::ca::application) papp)
      {
         primitive::memory storage;
         if(varFile.ca < ::ca::file > () != ::null())
         {
            storage.FullLoad(*varFile.ca < ::ca::file >());
         }
         else
         {
            string strFilePath(varFile);
            if(papp->m_bZipIsDir && (::ca::str::find_ci(".zip:", strFilePath) >= 0))
            {
               if(!exists(strFilePath, papp))
                  return "";
               ::primitive::memory_file memfile(papp, &storage);
               zip::InFile infile(get_app());
               if(!infile.unzip_open(strFilePath, 0))
                  return "";
               if(!infile.dump(&memfile))
                  return "";
            }
            else if(::ca::str::begins_eat_ci(strFilePath, "file:///"))
            {
               if(!exists(strFilePath, papp))
                  return "";
               as_memory(strFilePath, storage, papp);
            }
            else if(::ca::str::begins_eat_ci(strFilePath, "file:\\\\\\"))
            {
               if(!exists(strFilePath, papp))
                  return "";
               as_memory(strFilePath, storage, papp);
            }
            else if(::ca::str::begins_ci(strFilePath, "http://")
            || ::ca::str::begins_ci(strFilePath, "https://"))
            {
               if(!exists(strFilePath, &varQuery, papp))
                  return "";
               ::ca::property_set post;
               ::ca::property_set headers;
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
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), ::null(), ::null());
               }
               else if(varQuery.propset()["optional_ca2_sessid"])
               {
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), ::null(), ::null());
               }
               else if(strFilePath.contains("/matter.ca2.cc/") || strFilePath.contains(".matter.ca2.cc/"))
               {
                  try
                  {
                     storage.FullLoad(App(papp).file().get_file(strFilePath, ::ca::file::type_binary | ::ca::file::mode_read));
                  }
                  catch(...)
                  {
                  }
               }
               else
               {
                  App(papp).http().get(strFilePath, storage, post, headers, varQuery.propset(), ::null(), &AppUser(papp));
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
            ::ca::international::unicode_to_utf8(strResult, (const wchar_t *) &storage.get_data()[2], (int32_t)(storage.get_size() - 2));
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

      void file_system::as_memory(var varFile, primitive::memory_base & mem, sp(::ca::application) papp)
      {

         mem.allocate(0);

         if(varFile.get_type() == var::type_string)
         {

            string strPath = varFile.get_string();

            if(strPath.is_empty())
            {

               TRACE("::ca::file::file_system::as_memory varFile is a empty file name!!");

               return;

            }

            strPath.trim("\"'");

            if((::ca::str::begins(strPath, "http://") || ::ca::str::begins(strPath, "https://")))
            {

               App(papp).http().get(strPath, mem, &AppUser(papp));

               return;

            }

         }

         ::ca::filesp spfile;

         try
         {

            spfile = App(papp).file().get_file(varFile, ::ca::file::type_binary | ::ca::file::mode_read | ::ca::file::shareDenyNone);

            if(spfile.is_null())
               return;

            mem.FullLoad(spfile);

         }
         catch(...)
         {
         }



      }

      void file_system::lines(stringa & stra, var varFile, sp(::ca::application) papp)
      {
         UNREFERENCED_PARAMETER(papp);
         ::ca::text_file_sp spfile(allocer());

         try
         {
            if(!spfile->open(varFile, ::ca::file::type_text | ::ca::file::mode_read))
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

      bool file_system::put_contents(var varFile, const void * pvoidContents, ::count count, sp(::ca::application) papp)
      {

         ::ca::filesp spfile;

         spfile = App(papp).file().get_file(varFile, ::ca::file::type_binary | ::ca::file::mode_write | ::ca::file::mode_create | ::ca::file::shareDenyNone | ::ca::file::defer_create_directory);

         if(spfile.is_null())
            return false;

         spfile->write(pvoidContents, count);

         return true;

      }

      bool file_system::put_contents(var varFile, const char * lpcszContents, sp(::ca::application) papp)
      {
         if(lpcszContents == ::null())
         {
            return put_contents(varFile, "", 0, papp);
         }
         else
         {
            return put_contents(varFile, lpcszContents, strlen(lpcszContents), papp);
         }
      }

      bool file_system::put_contents(var varFile, ::ca::file & file, sp(::ca::application) papp)
      {
         ::ca::filesp spfile;
         spfile = App(papp).file().get_file(varFile, ::ca::file::type_binary | ::ca::file::mode_write | ::ca::file::mode_create | ::ca::file::shareDenyNone | ::ca::file::defer_create_directory);
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

      bool file_system::put_contents(var varFile, primitive::memory & mem, sp(::ca::application) papp)
      {
         return put_contents(varFile, mem.get_data(), (count) mem.get_size(), papp);
      }

      bool file_system::put_contents_utf8(var varFile, const char * lpcszContents, sp(::ca::application) papp)
      {
         ::ca::filesp spfile;
         spfile = App(papp).file().get_file(varFile, ::ca::file::type_binary | ::ca::file::mode_write | ::ca::file::mode_create | ::ca::file::shareDenyNone | ::ca::file::defer_create_directory);
         if(spfile.is_null())
            return false;
         ::ca::byte_output_stream(spfile) << "\xef\xbb\xbf";
         spfile->write(lpcszContents, strlen(lpcszContents));
         return true;
      }

      void file_system::path::split(stringa & stra, const char * lpcszPath)
      {
         stringa straSeparator;
         straSeparator.add("\\");
         straSeparator.add("/");
         stra.add_smallest_tokens(lpcszPath, straSeparator, FALSE);
      }

      class file_system::path & file_system::path()
      {
         return m_path;
      }

      file_system::file_system()
      {
      m_path.m_pfile = this;

      }

      string file_system::title_(const char * path)
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

      string file_system::name_(const char * path)
      {

         string str(path);

         while(::ca::str::ends_eat(str, "\\"));

         while(::ca::str::ends_eat(str, "/"));

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

      string file_system::extension(const char * path)
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

      void file_system::copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, sp(::ca::application) papp)
      {
         if(bFailIfExists)
         {
            if(exists(pszNew, papp))
               throw "Failed to copy file";
         }
         if(System.dir().is(psz, papp) && (eextract == extract_first || eextract == extract_all || !(::ca::str::ends_ci(psz, ".zip"))))
         {
            stringa straPath;
            System.dir().rls(papp, psz, &straPath);
            string strDst;
            string strSrc;
            string strDirSrc(psz);
            string strDirDst(pszNew);
            if(papp->m_bZipIsDir && (::ca::str::ends(strDirSrc, ".zip")))
            {
               strDirSrc += ":";
            }
            for(int32_t i = 0; i < straPath.get_size(); i++)
            {
               strSrc = straPath[i];
               strDst = strSrc;
               ::ca::str::begins_eat_ci(strDst, strDirSrc);
               strDst = System.dir().path(strDirDst, strDst);
               if(System.dir().is(strSrc, papp))
               {
                  if((eextract == extract_first || eextract == extract_none) && (::ca::str::ends_ci(psz, ".zip")))
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

            ::ca::filesp ofile;
            ofile = App(papp).file().get_file(strNew, ::ca::file::mode_write | ::ca::file::type_binary | ::ca::file::mode_create | ::ca::file::defer_create_directory | ::ca::file::shareDenyWrite);
            if(ofile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            ::ca::filesp ifile;
            ifile = App(papp).file().get_file(psz, ::ca::file::mode_read | ::ca::file::type_binary | ::ca::file::shareDenyNone);
            if(ifile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            System.compress().null(ofile, ifile);



            bool bOutputFail = false;
            bool bInputFail = false;
            bool bStatusFail = false;
            ::ca::file_status st;

            try
            {

               ifile->GetStatus(st);

            }
            catch(...)
            {

               bStatusFail = true;
               TRACE("During copy, failed to get status from input file \"%s\" bFailIfExists=%d", psz, bFailIfExists);
            }

            if(!bStatusFail)
            {
               try
               {

                  ifile->GetStatus(st);

               }
               catch(...)
               {

                  bStatusFail = true;
                  TRACE("During copy, failed to set status to output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);

               }

            }

            try
            {
               ofile->flush();
            }
            catch(...)
            {
            }

            try
            {
               ofile->close();
            }
            catch(...)
            {
               bOutputFail = true;
            }

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

      void file_system::move(const char * pszNew, const char * psz)
      {
#ifdef WINDOWSEX
         if(!::MoveFileW(
            ::ca::international::utf8_to_unicode(psz),
            ::ca::international::utf8_to_unicode(pszNew)))
         {
            uint32_t dwError = ::GetLastError();
            string strError;
            strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
            throw strError;
         }
#elif defined(METROWIN)

         ::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, ::null(), OPEN_EXISTING, 0, ::null());

         if(file == nullptr)
            throw "file::file_system::move Could not move file, could not open source file";

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
               ::wait(file->RenameAsync(strNameNew));
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
               ::wait(file->MoveAsync(folder, strNameNew));
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

      void file_system::del(const char * psz)
      {
#ifdef WINDOWS
         if(!::DeleteFileW(
            ::ca::international::utf8_to_unicode(psz)))
         {
            uint32_t dwError = ::GetLastError();
            if(dwError == 2) // the file does not exist, so delete "failed"
               return;
            string strError;
            strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
            throw io_exception(get_app(), strError);
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


      string file_system::copy(const char * psz, sp(::ca::application) papp)
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


      bool file_system::exists(const char * pszPath, sp(::ca::application) papp)
      {

         return exists(pszPath, ::null(), papp);

      }


      bool file_system::exists(const char * pszPath, var * pvarQuery, sp(::ca::application) papp)
      {

         if(::ca::str::begins_ci_iws(pszPath, "uifs://"))
         {
            return AppUser(papp).m_pifs->file_exists(pszPath);
         }
         else if(::ca::str::begins_ci_iws(pszPath, "http://") || ::ca::str::begins_ci_iws(pszPath, "https://"))
         {
            return App(papp).http().exists(pszPath, pvarQuery, papp->get_safe_user());
         }

         if(papp->m_bZipIsDir)
         {

            strsize iFind = ::ca::str::find_ci(".zip:", pszPath);

            zip::Util ziputil;

            if(iFind >= 0)
               return ziputil.exists(papp, pszPath);

            if(!Sys(papp).dir().name_is(pszPath, papp))
               return false;

         }

#ifdef WINDOWS


         return file_exists_dup(pszPath);

         //return ::GetFileAttributesW(::ca::international::utf8_to_unicode(pszPath)) != INVALID_FILE_ATTRIBUTES;

#else

         struct stat st;

         if(stat(pszPath, &st) != 0)
            return false;

         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

      }


      bool file_system::exists(const string & strPath, sp(::ca::application) papp)
      {

         return exists(strPath, ::null(), papp);

      }


      bool file_system::exists(const string & strPath, var * pvarQuery, sp(::ca::application) papp)
      {

         if(::ca::str::begins_ci_iws(strPath, "uifs://"))
         {
            return AppUser(papp).m_pifs->file_exists(strPath);
         }

         if(::ca::str::begins_ci_iws(strPath, "http://")
         || ::ca::str::begins_ci_iws(strPath, "https://"))
         {
            return App(papp).http().exists(strPath, pvarQuery, papp->get_safe_user());
         }


         if(papp->m_bZipIsDir)
         {

            strsize iFind = ::ca::str::find_ci(".zip:", strPath);

            zip::Util ziputil;

            if(iFind >= 0)
            {

               if(!exists(strPath.Mid(0, iFind + 4), papp))
                  return false;

               return ziputil.exists(papp, strPath);

            }


         }

         if(!papp->m_psystem->dir().name_is(strPath, papp))
            return false;

#ifdef WINDOWS


         return file_exists_dup(strPath);
           // return true;

         //return App(papp).m_spfsdata->file_exists(strPath);
         //return ::GetFileAttributesW(::ca::international::utf8_to_unicode(strPath)) != INVALID_FILE_ATTRIBUTES;

#else

         struct stat st;

         if(stat(strPath, &st) != 0)
            return false;

         return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

      }

      string file_system::paste(const char * pszLocation, const char * path, sp(::ca::application) papp)
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

      void file_system::trash_that_is_not_trash(stringa & stra, sp(::ca::application) papp)
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

      void file_system::trash_that_is_not_trash(const char * psz, sp(::ca::application) papp)
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

      void file_system::replace(const char * pszContext, const char * pszFind, const char * pszReplace, sp(::ca::application) papp)
      {
         stringa straTitle;
         System.dir().ls(papp, pszContext, ::null(), &straTitle);
         string strOld;
         string strNew;
         string strFail;
         for(int32_t i = 0; i < straTitle.get_size(); i++)
         {
            strOld = straTitle[i];
            strNew = strOld;
            strNew.replace(pszFind, pszReplace);
            if(strNew != strOld)
            {
#ifdef WINDOWS
//               ::MoveFileW(
  //                ::ca::international::utf8_to_unicode(System.dir().path(pszContext, strOld)),
    //              ::ca::international::utf8_to_unicode(System.dir().path(pszContext, strNew)));
               try
               {
               move(System.dir().path(pszContext, strNew), System.dir().path(pszContext, strOld));
               }
               catch(...)
               {
                  strFail += "failed to move " + System.dir().path(pszContext, strOld) + " to " + System.dir().path(pszContext, strNew);
               }
#else
               ::rename(
                  System.dir().path(pszContext, strOld),
                  System.dir().path(pszContext, strNew));
#endif
            }
         }
         if(strFail.has_char())
         {
            Application.simple_message_box(::null(), strFail);
         }
      }

      bool file_system::is_read_only(const char * psz)
      {

#ifdef WINDOWSEX

         uint32_t dwAttrib = GetFileAttributesW(::ca::international::utf8_to_unicode(psz));
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

      string file_system::sys_temp(const char * pszName, const char * pszExtension, sp(::ca::application) papp)
      {

         string strTempDir = get_sys_temp_path();

         if(!::ca::str::ends(strTempDir, "\\") && !::ca::str::ends(strTempDir, "/"))
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

      string file_system::sys_temp_unique(const char * pszName)
      {

         return System.dir().path(get_sys_temp_path(), pszName);

      }

      ::ca::filesp file_system::time_square_file(sp(::ca::application) papp, const char * pszPrefix, const char * pszSuffix)
      {

         return get(time_square(papp, pszPrefix, pszSuffix), papp);

      }

      ::ca::filesp file_system::get(const char * name, sp(::ca::application) papp)
      {

         System.dir().mk(System.dir().name(name), papp);

         ::ca::filesp fileOut = App(papp).file().get_file(name, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write);

         if(fileOut.is_null())
            throw ::ca::file_exception(papp, -1, ::ca::file_exception::none, name);

         return fileOut;

      }

      string file_system::replace_extension(const char * pszFile, const char * pszExtension)
      {
         string strFile(pszFile);
         set_extension(strFile, pszExtension);
         return strFile;
      }

      void file_system::set_extension(string & strFile, const char * pszExtension)
      {
         strsize iEnd = strFile.reverse_find('.');
         if(iEnd < 0)
            iEnd = strFile.get_length();
         strFile = strFile.Left(iEnd) + ::ca::str::has_char(pszExtension, ".");
      }

   void file_system::normalize(string & str)
   {
      if(str.is_empty())
         return;
      while(str.has_char() &&
         (str.Right(1) == "\\" ||
         str.Right(1) == "/"))
      {
         str = str.Left(str.get_length() - 1);
      }
   }

   int32_t file_system::cmp(const char * psz1, const char * psz2)
   {
      string str1(psz1);
      normalize(str1);
      string str2(psz2);
      normalize(str2);
      return str1.CompareNoCase(str2);
   }



      bool file_system::path::rename(const char *pszNew, const char *psz, sp(::ca::application) papp)
   {
      string strDir = System.dir().name(psz);
      string strDirNew = System.dir().name(pszNew);
      if(strDir == strDirNew)
      {
         string strOld = System.file().name_(psz);
      }
      throw not_implemented(get_app());
      //if(!System.file_as_string().move(psz, pszNew))
      {
         ::ca::property_set propertyset;
         System.message_box("err\\::fontopus::user\\file_system\\could_not_rename_file.xml", propertyset);
         return false;
      }
      return true;
   }

   string file_system::md5(const char * psz)
   {

      ::ca::filesp spfile(allocer());

      try
      {
         if(!spfile->open(psz, ::ca::file::type_binary | ::ca::file::mode_read))
            return "";
      }
      catch(::ca::file_exception &)
      {
         return "";
      }


      int32_t iBufSize = 1024 * 256;

      primitive::memory buf;

      buf.allocate(1024 * 256);

      ::crypto::md5::context ctx(get_app());

      int32_t iRead;

      while((iRead = (int32_t) spfile->read(buf, iBufSize)) > 0)
      {

         ctx.update(buf.get_data(), iRead);

      }

      return ctx.to_hex();

   }


   void file_system::dtf(const char * pszFile, const char * pszDir, sp(::ca::application) papp)
   {
      stringa stra;
      stringa straRelative;
      System.dir().rls(papp, pszDir, &stra, ::null(), &straRelative);
      dtf(pszFile, stra, straRelative, papp);
   }

   void file_system::dtf(const char * pszFile, stringa & stra, stringa & straRelative, sp(::ca::application) papp)
   {

      ::ca::filesp spfile = App(papp).file().get_file(pszFile, ::ca::file::mode_create | ::ca::file::mode_write  | ::ca::file::type_binary);

      if(spfile.is_null())
         throw "failed";

      string strVersion;

      strVersion = "fileset v1";

      ::crypto::md5::context ctx(get_app());

      write_gen_string(spfile, ::null(), strVersion);

      ::ca::filesp file2(allocer());

      ::primitive::memory_size iBufSize = 1024 * 1024;

      ::primitive::memory_size uiRead;

      primitive::memory buf;

      buf.allocate(iBufSize);

      string strMd5 = "01234567012345670123456701234567";

      uint64_t iPos;

      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         if(::ca::str::ends_ci(stra[i], ".zip"))
         {
         }
         else if(System.dir().is(stra[i], get_app()))
            continue;
         write_n_number(spfile, ::null(), 1);
         iPos = spfile->get_position();
         write_gen_string(spfile, ::null(), strMd5);
         ctx.reset();
         write_gen_string(spfile, &ctx, straRelative[i]);
         if(!file2->open(stra[i], ::ca::file::mode_read | ::ca::file::type_binary))
            throw "failed";
         write_n_number(spfile, &ctx, (int32_t) file2->get_length());
         while((uiRead = file2->read(buf, iBufSize)) > 0)
         {
            spfile->write(buf, uiRead);
            ctx.update(buf, uiRead);
         }
         spfile->seek(iPos, ::ca::seek_begin);
         strMd5 = ctx.to_hex();
         write_gen_string(spfile, ::null(), strMd5);
         spfile->seek_to_end();

      }
      write_n_number(spfile, ::null(), 2);
   }

   void file_system::ftd(const char * pszDir, const char * pszFile, sp(::ca::application) papp)
   {
      string strVersion;
      ::ca::filesp spfile = App(papp).file().get_file(pszFile, ::ca::file::mode_read  | ::ca::file::type_binary);
      if(spfile.is_null())
         throw "failed";
      read_gen_string(spfile, ::null(), strVersion);
      int64_t n;
      string strRelative;
      string strMd5;
      string strMd5New;
      int32_t iBufSize = 1024 * 1024;
      primitive::memory buf;
      buf.allocate(iBufSize);
      int64_t iLen;
      ::crypto::md5::context ctx(get_app());
      ::ca::filesp file2(get_app());
      ::primitive::memory_size uiRead;
      if(strVersion == "fileset v1")
      {
         while(true)
         {
            read_n_number(spfile, ::null(), n);
            if(n == 2)
               break;
            read_gen_string(spfile, ::null(), strMd5);
            ctx.reset();
            read_gen_string(spfile, &ctx, strRelative);
            string strPath = System.dir().path(pszDir, strRelative);
            App(papp).dir().mk(System.dir().name(strPath));
            if(!file2->open(strPath, ::ca::file::mode_create | ::ca::file::type_binary | ::ca::file::mode_write))
               throw "failed";
            read_n_number(spfile, &ctx, iLen);
            while(iLen > 0)
            {
             uiRead = spfile->read(buf, (UINT)  (min(iBufSize, iLen )));
             if(uiRead == 0)
                break;
               file2->write(buf, uiRead);
               ctx.update(buf, uiRead);
               iLen -= uiRead;
            }
            file2->close();
            strMd5New = ctx.to_hex();
            if(strMd5 != strMd5New)
               throw "failed";
         }
      }
   }

   void file_system::write_n_number(sp(::ca::file) pfile, ::crypto::md5::context * pctx, int64_t iNumber)
   {

      string str;

      str.Format("%I64dn", iNumber);

      pfile->write((const char *) str, str.get_length());

      if(pctx != ::null())
      {

         pctx->update((const char *) str, (int32_t) str.get_length());

      }

   }

   void file_system::read_n_number(sp(::ca::file) pfile, ::crypto::md5::context * pctx, int64_t & iNumber)
   {

      uint64_t uiRead;

      string str;

      char ch;

      while((uiRead = pfile->read(&ch, 1)) == 1)
      {

         if(ch >= '0' && ch <= '9')
            str += ch;
         else
            break;

         if(pctx != ::null())
         {
            pctx->update(&ch, 1);
         }

      }

      if(ch != 'n')
         throw "failed";

      if(pctx != ::null())
      {
         pctx->update(&ch, 1);
      }

      iNumber = ::ca::str::to_int64(str);

   }

   void file_system::write_gen_string(sp(::ca::file) pfile, ::crypto::md5::context * pctx, string & str)
   {
      ::count iLen = str.get_length();
      write_n_number(pfile, pctx, iLen);
      pfile->write((const char *) str, str.get_length());
      if(pctx != ::null())
      {
         pctx->update((const char *) str, (int32_t) str.get_length());
      }
   }

   void file_system::read_gen_string(sp(::ca::file) pfile, ::crypto::md5::context * pctx, string & str)
   {
      int64_t iLen;
      read_n_number(pfile, pctx, iLen);
      LPSTR lpsz = str.GetBufferSetLength((strsize) (iLen + 1));
      pfile->read(lpsz, (primitive::memory_size) iLen);
      if(pctx != ::null())
      {
         int64_t iProcessed = 0;
         while(iLen - iProcessed > 0)
         {
            int32_t iProcess = (int32_t) min(1024 * 1024, iLen - iProcessed);
            pctx->update(&lpsz[iProcessed], iProcess);
            iProcessed += iProcess;
         }
      }
      lpsz[iLen] = '\0';
      str.ReleaseBuffer();
   }




} // namespace ca






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


        HMODULE hModule = GetModuleHandle(_T("ca.dll"));
        if( !hModule )
        {
            OutputDebugStringW( L"GetModuleHandle(_T(\"ca.dll\")); failed" );
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
            MessageBox(::null(), "Cannot find driver " + csFilePath, "Cannot find driver " + csFilePath, MB_OK );
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
      HANDLE hDriver = ::null();
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

	// Get the list of all handles in the file_system
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
			string csFileName( ::ca::international::unicode_to_utf8(&ThreadParams.lpPath[nCmpStart]));
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
         wstrCallback = ::ca::international::utf8_to_unicode(csFileName);
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
			bool bSuccess = DeviceIoControl( hDriver, IOCTL_LISTDRV_BUFFERED_IO, &stAddress, sizeof(ADDRESS_INFO), &stHandle, sizeof(HANDLE_INFO), &dwReturn, ::null() ) != FALSE;


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
      wstrCallback = ::ca::international::utf8_to_unicode(csFileName);
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

            wstrCallback = ::ca::international::utf8_to_unicode(csModule);

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



