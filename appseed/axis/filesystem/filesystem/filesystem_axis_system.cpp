#include "framework.h"



#ifndef METROWIN
   #include <openssl/ssl.h>
#endif

#include <openssl/md5.h>
#include <openssl/whrlpool.h>

#ifndef WINDOWS
   #include <sys/stat.h>
   //#include <ctype.h>
#endif


namespace file
{


   namespace axis
   {


      system::system(::aura::application * papp) :
         ::object(papp),
         ::file::system(papp)
      {

      }


      system::~system()
      {

      }

      //      void system::get_ascendants_path(const ::file::path & lpcsz,::file::patha & straParam)
      //   {
      //      ::file::patha stra;
      //      get_ascendants_name(lpcsz, stra);
      //      string str;
      //      bool bUrl = System.url().is_url(lpcsz);
      //#if defined(LINUX) || defined(APPLEOS)
      //      bool bLinux = true;
      //      str += "/";
      //#else
      //      bool bLinux = false;
      //#endif
      //
      //      for(int32_t i = 0; i < stra.get_size(); i++)
      //      {
      //         str += stra[i];
      //         if(stra[i].find('/') < 0 && stra[i].find('\\') < 0)
      //         {
      //            str += "\\";
      //         }
      //         if(bUrl || bLinux)
      //         {
      //            str.replace("\\", "/");
      //         }
      //         else
      //         {
      //            str.replace("/", "\\");
      //         }
      //         straParam.add(::file::path(str));
      //      }
      //   }
      //
      //      void system::get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam)
      //   {
      //      stringa straSeparator;
      //      straSeparator.add("/");
      //      straSeparator.add("\\");
      //      straParam.add_smallest_tokens(lpcsz, straSeparator, FALSE);
      //      if(straParam.get_count() > 0)
      //      {
      //         strsize iFind = straParam[0].find(':');
      //         if(iFind >= 2)
      //         {
      //            straParam[0] += "//";
      //         }
      //         else if(iFind == 1)
      //         {
      //            straParam[0] += "\\";
      //         }
      //      }
      //   }


      //bool system::exists(const char * pszPath, ::aura::application * papp)
      //{

      //   return exists(pszPath, NULL, papp);

      //}


      //bool system::exists(const char * pszPath, var * pvarQuery, ::aura::application * papp)
      //{

      //   return exists(string(pszPath), pvarQuery, papp);

      //}


      bool system::exists(const ::file::path & strPath, ::aura::application * papp)
      {

         return exists(strPath, NULL, papp);

      }


      bool system::exists(const ::file::path & path, var * pvarQuery, ::aura::application * papp)
      {

         if (::str::begins(path, astr.strUifsProtocol))
         {
            
            return AppUser(papp).m_pifs->file_exists(path);
            
         }
         
         return ::file::system::exists(path, pvarQuery, papp);

      }

      
      //var system::length(const char * pszPath, ::aura::application * papp)
      //{

      //   return length(pszPath, NULL, papp);

      //}


      //var system::length(const char * pszPath, var * pvarQuery, ::aura::application * papp)
      //{

      //   return length(string(pszPath), pvarQuery, papp);

      //}


      var system::length(const ::file::path & strPath, ::aura::application * papp)
      {

         return length(strPath, NULL, papp);

      }


      var system::length(const ::file::path & strPath, var * pvarQuery, ::aura::application * papp)
      {

         if (::str::begins_ci(strPath, "http://") || ::str::begins_ci(strPath, "https://"))
         {

            property_set set(papp);

            return App(papp).http().length(strPath, set);

         }

         if (::str::begins_ci(strPath, "uifs://"))
         {

            return AppUser(papp).m_pifs->file_length(strPath);

         }

         var varRet;

#ifdef WINDOWS

         WIN32_FILE_ATTRIBUTE_DATA data;

         if (!GetFileAttributesExW(::str::international::utf8_to_unicode(strPath), GetFileExInfoStandard, &data))
         {
            varRet.set_type(var::type_null);
         }
         else
         {
            varRet = (uint32_t)data.nFileSizeLow;
         }

#else

         struct stat stat;

         if (::stat(strPath, &stat) == -1)
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


      ::file::path system::time_square(::aura::application * papp, const string & pszPrefix, const string & pszSuffix)
      {

         return time(papp, System.dir().time_square(papp), 25, pszPrefix, pszSuffix);

      }


      ::file::path system::time_log(::aura::application * papp, const string & pszId)
      {

         return time(papp, System.dir().time_log(pszId), 9);

      }


      ::file::path system::time(::aura::application * papp, const ::file::path & psz, int32_t iMaxLevel, const string & pszPrefix, const string & pszSuffix)
      {
         synch_lock lockMachineEvent(
            (is_null(&System.machine_event_central())) ?
            &System.machine_event_central().m_machineevent.m_mutex
            : ((mutex *)NULL));
         int32_t iIncLevel = -1;
         ::file::path str;
         string strPrefix(pszPrefix);
         string strSuffix(pszSuffix);
restart:
         str.Empty();
         str = psz;
         System.dir().mk(str, papp);
         ::file::listing straTitle(papp);
         string strFormat;
         for (int32_t i = 1; i <= iMaxLevel;)
         {
            System.dir().mk(str, papp);
            if (!System.dir().is(str, papp))
               throw "time square dir does not exist";
            straTitle.ls(str);
            if (i < iMaxLevel)
            {
               int32_t iMax = filterex_time_square("", straTitle);
               if (iMax == -1)
               {
                  str += "00";
                  System.dir().mk(str, papp);
               }
               else if (iMax == 99)
               {
                  iIncLevel = i - 1;
                  goto restart;
               }
               else
               {
                  if (i == iIncLevel)
                  {
                     iMax++;
                  }
                  strFormat.Format("%02d", iMax);
                  str /= strFormat;
                  if (i == iIncLevel)
                  {
                     System.dir().mk(str, papp);
                  }
               }
               i++;
            }
            else // if i == iMaxLevel
            {
               straTitle.ls(str);
               int32_t iMax = filterex_time_square(pszPrefix, straTitle);
               if (iMax == -1)
               {
                  str /= (strPrefix + "00" + strSuffix);
                  if (system::mk_time(str))
                     break;
               }
               else if (iMax == 99)
               {
                  iIncLevel = iMaxLevel - 1;
                  goto restart;
               }
               else
               {
                  iMax++;
                  strFormat.Format("%02d", iMax);
                  str /= (strPrefix + strFormat + strSuffix);
                  if (system::mk_time(str))
                     break;
               }
               return "";
            }
         }
         return str;
      }

      int32_t system::filterex_time_square(const char * pszPrefix, ::file::patha & stra)
      {
         int32_t iMax = -1;
         int32_t iIndex;
         for (int32_t i = 0; i < stra.get_size(); i++)
         {
            ::file::path str = stra[i].name();
            if (::str::begins_eat_ci(str, pszPrefix))
            {
               if (str.get_length() < 2)
               {
                  stra.remove_at(i);
                  i--;
                  continue;
               }
               if (!isdigit((uchar)str[0]) || !isdigit((uchar)str[1]))
               {
                  stra.remove_at(i);
                  i--;
                  continue;
               }
               iIndex = atoi(str.Mid(0, 2));
               if (iIndex > iMax)
                  iMax = iIndex;
            }
         }
         return iMax;
      }

      // fail if exists, create if not exists
      bool system::mk_time(const ::file::path & lpcszCandidate)
      {
         ::file::file_sp spfile(allocer());
         if (System.file().exists(lpcszCandidate, get_app()))
            return false;
         try
         {
            if (spfile->open(lpcszCandidate, ::file::mode_create | ::file::type_binary).failed())
               return false;
         }
         catch (...)
         {
            return false;
         }
         return true;
      }

      string system::as_string(var varFile, ::aura::application * papp)
      {
         var varQuery;
         return as_string(varFile, varQuery, papp);
      }

      string system::as_string(var varFile, var & varQuery, ::aura::application * papp)
      {

         return ::file::system::system::as_string(varFile, varQuery, papp);
      }

      void system::as_memory(var varFile, primitive::memory_base & mem, ::aura::application * papp)
      {

         mem.allocate(0);

         if (varFile.get_type() == var::type_string)
         {

            string strPath = varFile.get_string();

            if (strPath.is_empty())
            {

               TRACE("::file::binary_file::system::as_memory varFile is a empty file name!!");

               return;

            }

            strPath.trim("\"'");

            if ((::str::begins(strPath, astr.strHttpProtocol) || ::str::begins(strPath, astr.strHttpsProtocol)))
            {

               property_set set(papp);

               //set["user"] = &AppUser(papp);

               App(papp).http().get(strPath, mem, set);

               return;

            }

#if MEMDLEAK
            mem.m_strTag = "memory://" + strPath;
#endif
         }

         ::file::file_sp spfile;

         try
         {

            if(varFile.get_string().find_ci("/left/") >= 0)
            {
               TRACE("left folder");
            }

            cres res;

            spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none, &res);

            if (res.failed())
            {

               return;

            }

            if (spfile.is_null())
            {

               return;

            }

            file_size_t filesize = spfile->get_length();

			if (filesize > ::numeric_info < memory_size_t> ::max())
			{

				throw memory_exception(papp);

			}

            mem.allocate((memory_size_t) filesize);

            byte * pdata = mem.get_data();

            memory_size_t memsize = mem.get_size();

            memory_size_t uiRead = (memory_size_t) spfile->read(pdata, memsize);

            mem.allocate(uiRead);

         }
         catch (...)
         {
         }



      }

      void system::lines(stringa & stra, var varFile, ::aura::application * papp)
      {

         ::file::text_buffer_sp spfile(papp == NULL ? allocer() : papp->allocer());

         try
         {
            if (spfile->open(varFile, ::file::type_text | ::file::mode_read).failed())
            {
               return;
            }
         }
         catch (...)
         {
            return;
         }
         string strLine;
         while (spfile->read_string(strLine))
         {
            stra.add(strLine);
         }

      }

      bool system::put_contents(var varFile, const void * pvoidContents, ::count count, ::aura::application * papp)
      {

         ::file::file_sp spfile;

         try
         {

            spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);

         }
         catch (...)
         {

            return false;

         }

         if (spfile.is_null())
            return false;

         spfile->write(pvoidContents, count);

         return true;

      }

      bool system::put_contents(var varFile, const char * lpcszContents, ::aura::application * papp)
      {
         if (lpcszContents == NULL)
         {
            return put_contents(varFile, "", 0, papp);
         }
         else
         {
            return put_contents(varFile, lpcszContents, strlen(lpcszContents), papp);
         }
      }

      bool system::put_contents(var varFile, ::file::reader & reader, ::aura::application * papp)
      {
         ::file::file_sp spfile;
         spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
         if (spfile.is_null())
            return false;
         memory mem;
         mem.allocate(1024 * 1024 * 8);
         memory_size_t uiRead;
         while ((uiRead = reader.read(mem.get_data(), mem.get_size())) > 0)
         {
            spfile->write(mem.get_data(), uiRead);
         }
         return true;
      }

      bool system::put_contents(var varFile, memory & mem, ::aura::application * papp)
      {
         return put_contents(varFile, mem.get_data(), (count)mem.get_size(), papp);
      }

      bool system::put_contents_utf8(var varFile, const char * lpcszContents, ::aura::application * papp)
      {
         ::file::file_sp spfile;
         spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_exclusive | ::file::defer_create_directory);
         if (spfile.is_null())
            return false;
         spfile->write("\xef\xbb\xbf", 3);
         spfile->write(lpcszContents, strlen(lpcszContents));
         return true;
      }

      //void system::path::split(stringa & stra, const char * lpcszPath)
      //{
      //   stringa straSeparator;
      //   straSeparator.add("\\");
      //   straSeparator.add("/");
      //   stra.add_smallest_tokens(lpcszPath, straSeparator, FALSE);
      //}

      //class system::path & system::path()
      //{
      //   return m_path;
      //}


      //string system::title_(const char * path)
      //{

      //   string str = name_(path);

      //   strsize iPos = str.reverse_find('.');

      //   if(iPos >= 0)
      //   {
      //      return str.Mid(0, iPos);
      //   }
      //   else
      //   {
      //      return str;
      //   }

      //}

      //string system::name_(const char * path)
      //{

      //   string str(path);

      //   while(::str::ends_eat(str, "\\"));

      //   while(::str::ends_eat(str, "/"));

      //   strsize iPos;

      //   strsize iPos1 = str.reverse_find('\\');

      //   strsize iPos2 = str.reverse_find('/');

      //   if(iPos1 >= 0 && iPos2 >= 0)
      //   {

      //      if(iPos1 > iPos2)
      //      {

      //         iPos = iPos1 + 1;

      //      }
      //      else
      //      {

      //         iPos = iPos2 + 1;

      //      }

      //   }
      //   else if(iPos1 >= 0)
      //   {

      //      iPos = iPos1 + 1;

      //   }
      //   else if(iPos2 >= 0)
      //   {

      //      iPos = iPos2 + 1;

      //   }
      //   else
      //   {

      //      iPos = 0;

      //   }

      //   return str.Mid(iPos);

      //}

      //string system::extension(const char * path)
      //{

      //   string str = name_(path);

      //   strsize iPos = str.reverse_find('.');

      //   if(iPos >= 0)
      //   {

      //      return str.Mid(iPos + 1);

      //   }
      //   else
      //   {

      //      return "";

      //   }

      //}

      ::cres system::copy(const ::file::path & pszNew, const ::file::path & psz, bool bFailIfExists, e_extract eextract, ::aura::application * papp)
      {

         if (System.dir().is(psz, papp) && (eextract == extract_first || eextract == extract_all || !(::str::ends_ci(psz, ".zip"))))
         {
            ::file::listing patha(papp);
            patha.rls(psz);
            ::file::path strDst;
            ::file::path strSrc;
            ::file::path strDirSrc(psz);
            ::file::path strDirDst(pszNew);
            if (App(papp).m_bZipIsDir && (::str::ends(strDirSrc, ".zip")))
            {
               strDirSrc += ":";
            }
            for (int32_t i = 0; i < patha.get_size(); i++)
            {
               strSrc = patha[i];
               strDst = strSrc;
               ::str::begins_eat_ci(strDst, strDirSrc);
               strDst = strDirDst / strDst;
               if (System.dir().is(strSrc, papp))
               {
                  if ((eextract == extract_first || eextract == extract_none) && (::str::ends_ci(psz, ".zip")))
                  {
                  }
                  else
                  {
                     System.dir().mk(strDst, papp);
                  }
               }
               else
               {
                  if (!System.dir().is(strDst.folder(), papp))
                  {
                     System.dir().mk(strDst.folder(), papp);
                  }
                  copy(strDst, strSrc, bFailIfExists, eextract == extract_all ? extract_all : extract_none, papp);
               }
            }
         }
         else
         {

            if(pszNew.m_epath == ::file::path_file
                  && psz.m_epath == ::file::path_file)
            {

               return ::file::system::copy(pszNew, psz, bFailIfExists, eextract, papp);

            }

            if(bFailIfExists)
            {

               if(exists(pszNew,papp))
               {
                  return failure;

               }

            }

            ::file::path strNew;

            if (System.dir().is(pszNew, papp))
            {
               strNew = ::file::path(pszNew) / psz.name();
            }
            else
            {
               strNew = pszNew;
            }

            ::file::file_sp ofile;
            ofile = App(papp).file().get_file(strNew, ::file::mode_write | ::file::type_binary | ::file::mode_create | ::file::defer_create_directory | ::file::share_deny_write);
            if (ofile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open output file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            ::file::file_sp ifile;
            ifile = App(papp).file().get_file(psz, ::file::mode_read | ::file::type_binary | ::file::share_deny_none);
            if (ifile.is_null())
            {
               string strError;
               strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=could not open input file", psz, pszNew, bFailIfExists);
               throw strError;
            }

            ::file::ostream ostream(ofile);

            ::file::istream istream(ifile);

            System.file().transfer(ostream, istream);



            bool bOutputFail = false;
            bool bInputFail = false;
            bool bStatusFail = false;
            ::file::file_status st;

            try
            {

               ifile->GetStatus(st);

            }
            catch (...)
            {

               bStatusFail = true;
               TRACE("During copy, failed to get status from input file \"%s\" bFailIfExists=%d", psz, bFailIfExists);
            }

            if (!bStatusFail)
            {
               try
               {

                  ifile->GetStatus(st);

               }
               catch (...)
               {

                  bStatusFail = true;
                  TRACE("During copy, failed to set status to output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);

               }

            }

            try
            {
               ofile->flush();
            }
            catch (...)
            {
            }

            try
            {
               ofile->close();
            }
            catch (...)
            {
               bOutputFail = true;
            }

            try
            {
               ifile->close();
            }
            catch (...)
            {
               bInputFail = true;
            }

            if (bInputFail)
            {
               if (bOutputFail)
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
            else if (bOutputFail)
            {
               string strError;
               strError.Format("During copy, failed to close output file \"%s\" bFailIfExists=%d", pszNew, bFailIfExists);
               throw strError;
            }

         }

         return no_exception;

      }

      ::cres system::move(const ::file::path & pszNew, const ::file::path & psz, ::aura::application * papp)
      {
#ifdef WINDOWSEX
         if (!::MoveFileW(
                  ::str::international::utf8_to_unicode(psz),
                  ::str::international::utf8_to_unicode(pszNew)))
         {
            
            uint32_t dwError = ::GetLastError();

            if (dwError == ERROR_ALREADY_EXISTS)
            {

               if (::CopyFileW(
                  ::str::international::utf8_to_unicode(psz),
                  ::str::international::utf8_to_unicode(pszNew),
                  FALSE))
               {

                  if (!::DeleteFileW(::str::international::utf8_to_unicode(psz)))
                  {

                     dwError = ::GetLastError();

                     string strError;

                     strError.Format("Failed to delete the file to move \"%s\" error=%d", psz, dwError);

                     TRACE0(strError);

                  }

                  return no_exception;

               }

               dwError = ::GetLastError();

            }

            string strError;

            strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);

            throw strError;

         }
#elif defined(METROWIN)

         ::Windows::Storage::StorageFile ^ file = get_os_file(psz, 0, 0, NULL, OPEN_EXISTING, 0, NULL);

         if (file == nullptr)
            throw "file::system::move Could not move file, could not open source file";

         string strDirOld = psz.folder();
         string strDirNew = pszNew.folder();
         string strNameOld = psz.name();
         string strNameNew = pszNew.name();

         if (strDirOld == strDirNew)
         {
            if (strNameOld == strNameNew)
            {
               return no_exception;
            }
            else
            {
               ::wait(file->RenameAsync(strNameNew));
            }
         }
         else
         {
            ::Windows::Storage::StorageFolder ^ folder = get_os_folder(strDirNew);
            if (strNameOld == strNameNew)
            {
               ::wait(file->MoveAsync(folder));
            }
            else
            {
               ::wait(file->MoveAsync(folder, strNameNew));
            }
         }


#else
         if (::rename(psz, pszNew) != 0)
         {
            int32_t err = errno;
            string strError;
            strError.Format("Failed to delete file error=%d", err);
            throw strError;
         }
#endif

         return no_exception;

      }

      ::cres system::del(const ::file::path & psz, ::aura::application * papp)
      {
#ifdef WINDOWSEX

         HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE, NULL);

         if (h == INVALID_HANDLE_VALUE)
         {
            uint32_t dwError = ::GetLastError();
            if (dwError == 2) // the file does not exist, so delete "failed"
               return failure;
            string strError;
            strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
            return failure;
         }
         else
         {
            ::FlushFileBuffers(h);
            ::CloseHandle(h);
         }

         /*      if(!::DeleteFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz)))
               {
                  uint32_t dwError = ::GetLastError();
                  if(dwError == 2) // the file does not exist, so delete "failed"
                     return;
                  string strError;
                  strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
                  throw io_exception(papp, strError);
               }*/
#else
         if (remove(psz) != 0)
         {
            int32_t err = errno;
            if (err != ENOENT) // already does not exist - consider removal successful - does not issue an exception
            {
               string strError;
               strError.Format("Failed to delete file error=%d", err);
               throw strError;
            }
         }
#endif


         return no_exception;
      }


      ::file::path system::copy(const ::file::path & psz, ::aura::application * papp)
      {
         string strCopy("copy");
         string strNew;
         if (System.dir().is(psz, papp))
         {
            int32_t i = 1;
            while (i <= 100)
            {
               strNew.Format("%s-%s-%d", psz, strCopy.c_str(), i);
               if (!exists(strNew, papp))
               {
                  copy(strNew, psz, false, extract_all, papp);
                  return strNew;
               }
               i++;
            }
         }
         else
         {
            string strExt = psz.extension();
            if (!strExt.is_empty())
            {
               strExt = "-" + strExt;
            }
            int32_t i = 1;
            while (i <= 100)
            {
               strNew.Format("%s-%s-%d%s", psz, strCopy.c_str(), i, strExt.c_str());
               if (!exists(strNew, papp))
               {
                  copy(strNew, psz, false, extract_all, papp);
                  return strNew;
               }
               i++;
            }
         }
         return "";
      }



      ::file::path system::paste(const ::file::path & pszLocation, const ::file::path & path, ::aura::application * papp)
      {
         ::file::path strDir = path.folder();
         ::file::path strDest = pszLocation;
         ::file::path strSrc = strDir;
         if (strDest == strSrc)
         {
            return copy(path, papp);
         }
         else
         {
            ::file::path strNew = strDest / path.name();
            copy(strNew, path, false, extract_all, papp);
            return strNew;
         }
      }

      void system::trash_that_is_not_trash(const ::file::patha & stra, ::aura::application * papp)
      {

         if (stra.get_size() <= 0)
            return;

         ::file::path strDir = System.dir().trash_that_is_not_trash(stra[0]);

         System.dir().mk(strDir, papp);

         for (int32_t i = 0; i < stra.get_size(); i++)
         {

            move(strDir / stra[i].name(), stra[i], papp);

         }

      }

      void system::trash_that_is_not_trash(const ::file::path & psz, ::aura::application * papp)
      {

         ::file::path strDir = System.dir().trash_that_is_not_trash(psz);

         System.dir().mk(strDir, papp);

         move(strDir / psz.name(), psz, papp);

      }


      ::cres system::replace(const ::file::path & pszContext, const string & pszFind, const string & pszReplace, ::aura::application * papp)
      {

         cres e;

         ::file::listing straTitle(papp);
         straTitle.ls(pszContext);
         string strOld;
         string strNew;
         string strFail;
         ::file::path pathContext = pszContext;
         for (int32_t i = 0; i < straTitle.get_size(); i++)
         {
            strOld = straTitle[i].name();
            strNew = strOld;
            strNew.replace(pszFind, pszReplace);
            if (strNew != strOld)
            {
               // TODO(camilo) : should there be a way to chain or return multiple exceptions... instead of cres specifile file smart...
               // why not a super smart chained super hand heroe smarter pointerer that can contain vector of any excepction based on
               // ::exception like (::file::exception) (I supposed ::file::exception is already based on ::exception OMG CAMILO!!!)
               // and may be then replace could do replace for example on HTTP servers and return may io_exception and not tighted
               // to a barely translated io exception into a empty ::file::exception with improper filled members....
               e.add(move(pathContext / strNew, pathContext / strOld, papp));

            }

         }
         if (strFail.has_char())
         {
            App(papp).simple_message_box(NULL, strFail, MB_ICONEXCLAMATION);
         }

         return e;

      }


      bool system::is_read_only(const ::file::path & psz)
      {

#ifdef WINDOWSEX

         uint32_t dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(psz));
         if (dwAttrib & FILE_ATTRIBUTE_READONLY)
            return true;
         return false;

#elif defined(METROWIN)

         throw todo(get_app());

#else

         struct stat st;

         if (stat(psz, &st) != 0)
            return true;

         return !(st.st_mode & S_IWUSR);

#endif

      }


      ::file::path system::sys_temp(const ::file::path & pszName, const string & pszExtension, ::aura::application * papp)
      {

         string strTempDir = ::dir::sys_temp();

         if (!::str::ends(strTempDir, "\\") && !::str::ends(strTempDir, "/"))
         {

            strTempDir += "\\";

         }

         string str;

         char buf[30];

         for (int32_t i = 0; i < 1000; i++)
         {

            sprintf(buf, "%d", i);

            str = strTempDir;
            str += pszName;
            str += "-";
            str += buf;
            str += ".";
            str += pszExtension;
            if (!exists(str, papp))
               return str;
         }

         return "";

      }


      ::file::path system::sys_temp_unique(const ::file::path & pszName)
      {

         return ::dir::sys_temp() / pszName;

      }


      ::file::file_sp system::time_square_file(::aura::application * papp, const string & pszPrefix, const string & pszSuffix)
      {

         return get(time_square(papp, pszPrefix, pszSuffix), papp);

      }


      ::file::file_sp system::get(const ::file::path & name, ::aura::application * papp)
      {

         System.dir().mk(name.folder(), papp);

         ::file::file_sp fileOut = App(papp).file().get_file(name, ::file::mode_create | ::file::type_binary | ::file::mode_write);

         if (fileOut.is_null())
            throw ::file::exception(papp, ::file::exception::none, -1L, name);

         return fileOut;

      }


      ::file::path system::replace_extension(const ::file::path & pszFile, const string & pszExtension)
      {

         ::file::path strFile(pszFile);

         set_extension(strFile, pszExtension);

         return strFile;

      }


      void system::set_extension(::file::path & strFile, const string & pszExtension)
      {

         strsize iEnd = strFile.reverse_find('.');

         if (iEnd < 0)
            iEnd = strFile.get_length();

         strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");

      }


      void system::normalize(::file::path & str)
      {

         if (str.is_empty())
            return;

         while (str.has_char() &&
                (str.Right(1) == "\\" ||
                 str.Right(1) == "/"))
         {

            str = str.Left(str.get_length() - 1);

         }

      }


      int32_t system::cmp(const ::file::path & psz1, const ::file::path & psz2)
      {
         ::file::path str1(psz1);
         normalize(str1);
         ::file::path str2(psz2);
         normalize(str2);
         return str1.compare_ci(str2);
      }



      //bool system::path::rename(const char *pszNew, const char *psz, ::aura::application * papp)
      //{
      //   string strDir = System.dir().name(psz);
      //   string strDirNew = System.dir().name(pszNew);
      //   if(strDir == strDirNew)
      //   {
      //      string strOld = System.file().name_(psz);
      //   }
      //   ::exception::throw_not_implemented(papp);
      //   //if(!System.file_as_string().move(psz, pszNew))
      //   {
      //      property_set propertyset;
      //      System.message_box("err\\::fontopus::user\\system\\could_not_rename_file.xml", propertyset);
      //      return false;
      //   }
      //   return true;
      //}

      string system::md5(const ::file::path & psz)
      {

         ::file::file_sp spfile(allocer());

         try
         {
            if (spfile->open(psz, ::file::type_binary | ::file::mode_read | ::file::share_deny_none).failed())
               return "";
         }
         catch (::file::exception &)
         {
            return "";
         }


         int32_t iBufSize = 1024 * 256;

         memory buf;

         buf.allocate(1024 * 256);

         MD5_CTX ctx;

         MD5_Init(&ctx);

         int32_t iRead;

         while ((iRead = (int32_t)spfile->read(buf, iBufSize)) > 0)
         {

            MD5_Update(&ctx, buf.get_data(), iRead);

         }

         return ::str::from(ctx);

      }


      void system::dtf(const ::file::path & pszFile, ::file::patha & stra, ::aura::application * papp)
      {

         ::file::file_sp spfile = App(papp).file().get_file(pszFile, ::file::mode_create | ::file::mode_write | ::file::type_binary);

         if (spfile.is_null())
            throw "failed";

         string strVersion;

         strVersion = "fileset v1";

         MD5_CTX ctx;

         write_gen_string(spfile, NULL, strVersion);

         ::file::file_sp file2(allocer());

         memory_size_t iBufSize = 1024 * 1024;

         memory_size_t uiRead;

         memory buf;

         buf.allocate(iBufSize);

         string strMd5 = "01234567012345670123456701234567";

         uint64_t iPos;

         for (int32_t i = 0; i < stra.get_size(); i++)
         {
            if (::str::ends_ci(stra[i], ".zip"))
            {
            }
            else if (System.dir().is(stra[i], papp))
               continue;
            write_n_number(spfile, NULL, 1);
            iPos = spfile->get_position();
            write_gen_string(spfile, NULL, strMd5);
            MD5_Init(&ctx);
            string strRelative = stra[i].relative();
            write_gen_string(spfile, &ctx, strRelative);
            if (file2->open(stra[i], ::file::mode_read | ::file::type_binary).failed())
               throw "failed";
            write_n_number(spfile, &ctx, (int32_t)file2->get_length());
            while ((uiRead = file2->read(buf, iBufSize)) > 0)
            {
               spfile->write(buf, uiRead);
               MD5_Update(&ctx, buf, uiRead);
            }
            spfile->seek(iPos, ::file::seek_begin);
            strMd5 = ::str::from(ctx);
            write_gen_string(spfile, NULL, strMd5);
            spfile->seek_to_end();

         }

         write_n_number(spfile, NULL, 2);

      }


      void system::ftd(const ::file::path & pszDir, const ::file::path & pszFile, ::aura::application * papp)
      {

         string strVersion;

         ::file::file_sp spfile = App(papp).file().get_file(pszFile, ::file::mode_read | ::file::type_binary);

         if (spfile.is_null())
            throw "failed";

         read_gen_string(spfile, NULL, strVersion);

         int64_t n;

         string strRelative;
         string strMd5;
         string strMd5New;
         int32_t iBufSize = 1024 * 1024;
         memory buf;
         buf.allocate(iBufSize);
         int64_t iLen;
         MD5_CTX ctx;
         ::file::file_sp file2(allocer());
         memory_size_t uiRead;
         if (strVersion == "fileset v1")
         {
            while (true)
            {
               read_n_number(spfile, NULL, n);
               if (n == 2)
                  break;
               read_gen_string(spfile, NULL, strMd5);
               MD5_Init(&ctx);
               read_gen_string(spfile, &ctx, strRelative);
               ::file::path strPath = ::file::path(pszDir) / strRelative;
               App(papp).dir().mk(strPath.folder());
               if (file2->open(strPath, ::file::mode_create | ::file::type_binary | ::file::mode_write).failed())
                  throw "failed";
               read_n_number(spfile, &ctx, iLen);
               while (iLen > 0)
               {
                  uiRead = spfile->read(buf, (UINT)(MIN(iBufSize, iLen)));
                  if (uiRead == 0)
                     break;
                  file2->write(buf, uiRead);
                  MD5_Update(&ctx, buf, uiRead);
                  iLen -= uiRead;
               }
               file2->close();
               strMd5New = ::str::from(ctx);
               if (strMd5 != strMd5New)
                  throw "failed";
            }
         }
      }

      void system::write_n_number(::file::file *  pfile, void * pctx, int64_t iNumber)
      {

         string str;

         str.Format("%I64dn", iNumber);

         pfile->write((const char *)str, str.get_length());

         if (pctx != NULL)
         {

            MD5_Update((MD5_CTX *)pctx, (const char *)str, (int32_t)str.get_length());

         }

      }

      void system::read_n_number(::file::file *  pfile, void * pctx, int64_t & iNumber)
      {

         uint64_t uiRead;

         string str;

         char ch;

         while ((uiRead = pfile->read(&ch, 1)) == 1)
         {

            if (ch >= '0' && ch <= '9')
               str += ch;
            else
               break;

            if (pctx != NULL)
            {
               MD5_Update((MD5_CTX *)pctx, &ch, 1);
            }

         }

         if (ch != 'n')
            throw "failed";

         if (pctx != NULL)
         {
            MD5_Update((MD5_CTX *)pctx, &ch, 1);
         }

         iNumber = ::str::to_int64(str);

      }

      void system::write_gen_string(::file::file *  pfile, void * pctx, string & str)
      {
         ::count iLen = str.get_length();
         write_n_number(pfile, pctx, iLen);
         pfile->write((const char *)str, str.get_length());
         if (pctx != NULL)
         {
            MD5_Update((MD5_CTX *)pctx, (const char *)str, (int32_t)str.get_length());
         }
      }

      void system::read_gen_string(::file::file * pfile, void * pctx, string & str)
      {
         int64_t iLen;
         read_n_number(pfile, pctx, iLen);
         LPSTR lpsz = str.GetBufferSetLength((strsize)(iLen + 1));
         pfile->read(lpsz, (memory_size_t) iLen);
         if (pctx != NULL)
         {
            int64_t iProcessed = 0;
            while (iLen - iProcessed > 0)
            {
               int32_t iProcess = (int32_t)MIN(1024 * 1024, iLen - iProcessed);
               MD5_Update((MD5_CTX *)pctx, &lpsz[iProcessed], iProcess);
               iProcessed += iProcess;
            }
         }
         lpsz[iLen] = '\0';
         str.ReleaseBuffer();
      }


      bool system::is_valid_fileset(const char * pszFile, ::aura::application * papp)
      {

         if (!::file::system::is_valid_fileset(pszFile, papp))
         {

            return false;

         }

         return true;

      }



      bool system::resolve_link(string & strTarget, string & strFolder, string & strParams, const string & strSource, ::user::primitive * puiMessageParentOptional)
      {

         return System.os().resolve_link(strTarget,strFolder, strParams, strSource,puiMessageParentOptional);

      }


      string system::nessie(const ::file::path & psz)
      {

         ::file::file_sp spfile(allocer());
         try
         {
            if (spfile->open(psz, ::file::type_binary | ::file::mode_read).failed())
               return "";
         }
         catch (::file::exception &)
         {
            return "";
         }
         return nessie(spfile);

      }


      string system::nessie(::file::file_sp  pfile)
      {

         memory mem(get_app());

         mem.allocate(1024 * 256);

         WHIRLPOOL_CTX ns;

         WHIRLPOOL_Init(&ns);

         memory_size_t iRead;

         while ((iRead = (memory_size_t) pfile->read(mem.get_data(), mem.get_size())) > 0)
         {

            WHIRLPOOL_Update(&ns, mem.get_data(), iRead);

         }

         unsigned char digest[WHIRLPOOL_DIGEST_LENGTH];

         WHIRLPOOL_Final(digest, &ns);

         return ::hex::lower_from(digest, WHIRLPOOL_DIGEST_LENGTH);

      }


      //bool system::get_last_write_time(FILETIME * pfiletime,const string & strFilename)
      //{

      //   throw interface_only_exception(papp);

      //}

      ::file::file_sp system::get_file(var varFile,UINT nOpenFlags,cres * pfesp, ::aura::application * papp)
      {

         ::file::file_sp spfile;

         string strPath = varFile.get_file_path();

         if (::str::begins(strPath, astr.strIfsProtocol) || ::str::begins(strPath, astr.strUifsProtocol))
         {

            if (&AppUser(papp) == NULL)
            {

               spfile = NULL;

            }
            else
            {

               spfile = AppUser(papp).m_pifs->get_file(strPath, nOpenFlags, pfesp);

            }

         }


         return spfile;
   
      }


   } // namespace axis


} // namespace file






