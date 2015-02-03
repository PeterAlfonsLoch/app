#include "framework.h"

//#ifndef METROWIN
//#include <openssl/ssl.h>
//#endif
//
//#include <openssl/md5.h>
//#include <openssl/whrlpool.h>
//
#ifndef WINDOWS
#include <sys/stat.h>
//#include <ctype.h>
#endif

//CLASS_DECL_AXIS void NESSIEinit(struct NESSIEstruct * const structpointer);
//CLASS_DECL_AXIS void NESSIEadd(const uchar * const source, uint_ptr sourceBits, struct NESSIEstruct * const structpointer);
//CLASS_DECL_AXIS void NESSIEfinalize(struct NESSIEstruct * const structpointer, uchar * const result);








namespace file
{


   bool system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
   {
      string stra(lpszFilPathA);
      string wstrb(lpszFilPathB);

      //   ::str::international::ACPToUnicode(stra, lpszFilPathA);
      //   ::str::international::ACPToUnicode(wstrb, lpszFilPathB);
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

      return ::dir::eat_end_level(str, iLevelCount, lpSeparator);

   }


   bool system::path::is_relative(const char * psz)
   {

      return file_path_is_relative_dup(psz) != FALSE;

   }


   void system::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
//      bool bUrl = System.url().is_url(lpcsz);
      bool bUrl = false;
#if defined(LINUX) || defined(APPLEOS)
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


   bool system::exists(const char * pszPath, ::aura::application * papp)
   {

      return exists(pszPath, NULL, papp);

   }


   bool system::exists(const char * pszPath, var * pvarQuery, ::aura::application * papp)
   {

      return exists(string(pszPath), pvarQuery, papp);

   }


   bool system::exists(const string & strPath, ::aura::application * papp)
   {

      return exists(strPath, NULL, papp);

   }


   bool system::exists(const string & strPath, var * pvarQuery, ::aura::application * papp)
   {






      if (!papp->m_paurasystem->dir().name_is(strPath, papp))
         return false;

#ifdef WINDOWS


      return file_exists_dup(strPath) != FALSE;

#else

      struct stat st;

      if (stat(strPath, &st) != 0)
         return false;

      return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

   }

   var system::length(const char * pszPath, ::aura::application * papp)
   {

      return length(pszPath, NULL, papp);

   }


   var system::length(const char * pszPath, var * pvarQuery, ::aura::application * papp)
   {

      return length(string(pszPath), pvarQuery, papp);

   }


   var system::length(const string & strPath, ::aura::application * papp)
   {

      return length(strPath, NULL, papp);

   }


   var system::length(const string & strPath, var * pvarQuery, ::aura::application * papp)
   {



      var varRet;

#ifdef WINDOWS

      WIN32_FILE_ATTRIBUTE_DATA data;

      if(!GetFileAttributesExW(::str::international::utf8_to_unicode(strPath), GetFileExInfoStandard, &data))
      {
         varRet.set_type(var::type_null);
      }
      else
      {
         varRet = (uint32_t) data.nFileSizeLow;
      }

#else

      struct stat stat;

      if(::stat(strPath, &stat)  == -1)
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


   string system::time_square(::aura::application * papp, const char * pszPrefix, const char * pszSuffix)
   {
      string str;
      System.dir().time_square(str);
      return time(papp, str, 25, pszPrefix, pszSuffix);
   }

   string system::time_log(::aura::application * papp, const char * pszId)
   {
      return time(papp, System.dir().time_log(pszId), 9);
   }

   string system::time(::aura::application * papp, const char * psz, int32_t iMaxLevel, const char * pszPrefix, const char * pszSuffix)
   {
      synch_lock lockMachineEvent(
         (&System.machine_event_central() != NULL) ?
         &System.machine_event_central().m_machineevent.m_mutex
         : ((mutex *) NULL));
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
         if(::str::begins_eat_ci(str, pszPrefix))
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
      ::file::binary_buffer_sp spfile(allocer());
      if(System.file().exists(lpcszCandidate, get_app()))
         return false;
      try
      {
         if(!spfile->open(lpcszCandidate, ::file::mode_create | ::file::type_binary))
            return false;
      }
      catch(...)
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
      primitive::memory storage;
      if(varFile.cast < ::file::stream_buffer > () != NULL)
      {
         ::file::byte_input_stream is(varFile.cast < ::file::stream_buffer >());
         storage.read(is);
      }
      else
      {
         string strFilePath(varFile);
         if(::str::begins_eat_ci(strFilePath, "file:///"))
         {
            if(!exists(strFilePath, papp))
               return "";
            as_memory(strFilePath, storage, papp);
         }
         else if(::str::begins_eat_ci(strFilePath, "file:\\\\\\"))
         {
            if(!exists(strFilePath, papp))
               return "";
            as_memory(strFilePath, storage, papp);
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
         ::str::international::unicode_to_utf8(strResult, (const wchar_t *) &storage.get_data()[2], (int32_t)(storage.get_size() - 2));
      }
      else if (storage.get_size() >= 3
         && storage.get_data()[0] == 255
         && storage.get_data()[1] == 254
         && storage.get_data()[2] == 0x73)
      {
         ::str::international::unicode_to_utf8(strResult, (const wchar_t *)&storage.get_data()[2], (int32_t)(storage.get_size() - 2));
      }
      else if (storage.get_size() >= 3
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

   void system::as_memory(var varFile, primitive::memory_base & mem, ::aura::application * papp)
   {

      mem.allocate(0);

      if(varFile.get_type() == var::type_string)
      {

         string strPath = varFile.get_string();

         if(strPath.is_empty())
         {

            TRACE("::file::binary_buffer::system::as_memory varFile is a empty file name!!");

            return;

         }

         strPath.trim("\"'");

         

      }

      ::file::buffer_sp spfile;

      try
      {

         spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_read | ::file::share_deny_none);

         if(spfile.is_null())
            return;

         ::file::byte_input_stream is(spfile);

         is >> mem;

      }
      catch(...)
      {
      }



   }

   void system::lines(stringa & stra, var varFile, ::aura::application * papp)
   {
      UNREFERENCED_PARAMETER(papp);
      ::file::text_buffer_sp spfile(allocer());

      try
      {
         if(!spfile->open(varFile, ::file::type_text | ::file::mode_read))
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

   bool system::put_contents(var varFile, const void * pvoidContents, ::count count, ::aura::application * papp)
   {

      ::file::binary_buffer_sp spfile;
      
      try
      {

         spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
         
      }
      catch(...)
      {
         
         return false;
         
      }

      if(spfile.is_null())
         return false;

      spfile->write(pvoidContents, count);

      return true;

   }

   bool system::put_contents(var varFile, const char * lpcszContents, ::aura::application * papp)
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

   bool system::put_contents(var varFile, ::file::reader & reader, ::aura::application * papp)
   {
      ::file::binary_buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      primitive::memory mem;
      mem.allocate(1024 * 1024 * 8);
      ::primitive::memory_size uiRead;
      while((uiRead = reader.read(mem.get_data(), mem.get_size())) > 0)
      {
         spfile->write(mem.get_data(), uiRead);
      }
      return true;
   }

   bool system::put_contents(var varFile, primitive::memory & mem, ::aura::application * papp)
   {
      return put_contents(varFile, mem.get_data(), (count) mem.get_size(), papp);
   }

   bool system::put_contents_utf8(var varFile, const char * lpcszContents, ::aura::application * papp)
   {
      ::file::binary_buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      spfile->write("\xef\xbb\xbf", 3);
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

   system::system(::aura::application * papp) :
      element(papp)
   {
      m_path.m_pfile = this;

   }

   system::~system()
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

      while(::str::ends_eat(str, "\\"));

      while(::str::ends_eat(str, "/"));

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

   void system::copy(const char * pszNew, const char * psz, bool bFailIfExists, e_extract eextract, ::aura::application * papp)
   {
      
      ::file_copy_dup(pszNew,psz,!bFailIfExists);

      return;

   }

   void system::move(const char * pszNew, const char * psz)
   {
#ifdef WINDOWSEX
      if(!::MoveFileW(
         ::str::international::utf8_to_unicode(psz),
         ::str::international::utf8_to_unicode(pszNew)))
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

   void system::del(const char * psz)
   {
#ifdef WINDOWSEX

      HANDLE h = ::CreateFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz),GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_DELETE_ON_CLOSE,NULL);

      if(h == INVALID_HANDLE_VALUE)
      {
         uint32_t dwError = ::GetLastError();
         if(dwError == 2) // the file does not exist, so delete "failed"
            return;
         string strError;
         strError.Format("Failed to delete file \"%s\" error=%d",psz,dwError);
         throw io_exception(get_app(),strError);
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
         throw io_exception(get_app(), strError);
      }*/
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


   string system::copy(const char * psz, ::aura::application * papp)
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



   string system::paste(const char * pszLocation, const char * path, ::aura::application * papp)
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

   void system::trash_that_is_not_trash(stringa & stra, ::aura::application * papp)
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

   void system::trash_that_is_not_trash(const char * psz, ::aura::application * papp)
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

   void system::replace(const char * pszContext, const char * pszFind, const char * pszReplace, ::aura::application * papp)
   {
      stringa straTitle;
      System.dir().ls(papp, pszContext, NULL, &straTitle);
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
            //                ::str::international::utf8_to_unicode(System.dir().path(pszContext, strOld)),
            //              ::str::international::utf8_to_unicode(System.dir().path(pszContext, strNew)));
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
         Application.simple_message_box(NULL, strFail, MB_ICONEXCLAMATION);
      }
   }

   bool system::is_read_only(const char * psz)
   {

#ifdef WINDOWSEX

      uint32_t dwAttrib = GetFileAttributesW(::str::international::utf8_to_unicode(psz));
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

   string system::sys_temp(const char * pszName, const char * pszExtension, ::aura::application * papp)
   {

      string strTempDir = get_sys_temp_path();

      if(!::str::ends(strTempDir, "\\") && !::str::ends(strTempDir, "/"))
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


   ::file::buffer_sp system::time_square_file(::aura::application * papp, const char * pszPrefix, const char * pszSuffix)
   {

      return get(time_square(papp, pszPrefix, pszSuffix), papp);

   }


   ::file::buffer_sp system::get(const char * name, ::aura::application * papp)
   {

      System.dir().mk(System.dir().name(name), papp);

      ::file::binary_buffer_sp fileOut = App(papp).file().get_file(name, ::file::mode_create | ::file::type_binary | ::file::mode_write);

      if(fileOut.is_null())
         throw ::file::exception(papp, -1, ::file::exception::none, name);

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
      strFile = strFile.Left(iEnd) + ::str::has_char(pszExtension, ".");
   }

   void system::normalize(string & str)
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

   int32_t system::cmp(const char * psz1, const char * psz2)
   {
      string str1(psz1);
      normalize(str1);
      string str2(psz2);
      normalize(str2);
      return str1.CompareNoCase(str2);
   }



   bool system::path::rename(const char *pszNew, const char *psz, ::aura::application * papp)
   {
      string strDir = System.dir().name(psz);
      string strDirNew = System.dir().name(pszNew);
      if(strDir == strDirNew)
      {
         string strOld = System.file().name_(psz);
      }
      ::exception::throw_not_implemented(get_app());
      //if(!System.file().as_string().move(psz, pszNew))
      {
         property_set propertyset;
         System.message_box("err\\::fontopus::user\\system\\could_not_rename_file.xml", propertyset);
         return false;
      }
      return true;
   }

   string system::md5(const char * psz)
   {
      throw interface_only_exception(get_app());

      return "";

   }



   void system::dtf(const char * pszFile, const char * pszDir, ::aura::application * papp)
   {
      stringa stra;
      stringa straRelative;
      System.dir().rls(papp, pszDir, &stra, NULL, &straRelative);
      dtf(pszFile, stra, straRelative, papp);
   }

   void system::dtf(const char * pszFile, stringa & stra, stringa & straRelative, ::aura::application * papp)
   {

      throw interface_only_exception(get_app());

   }

   void system::ftd(const char * pszDir,const char * pszFile,::aura::application * papp)
   {
   
      throw interface_only_exception(get_app());

   }


   bool system::resolve_link(string & strTarget,const char * pszSource,sp(::aura::interaction) puiMessageParentOptional)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool system::is_valid_fileset(const char * pszFile,::aura::application * papp)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   string system::nessie(const char * psz)
   {

      ::file::binary_buffer_sp spfile(allocer());
      try
      {
         if(!spfile->open(psz,::file::type_binary | ::file::mode_read))
            return "";
      }
      catch(::file::exception &)
      {
         return "";
      }
      return nessie(spfile);

   }


   string system::nessie(::file::buffer_sp  pfile)
   {

      throw interface_only_exception(get_app());

   }


   bool system::get_last_write_time(FILETIME * pfiletime,const string & strFilename)
   {

      throw interface_only_exception(get_app());

   }



} // namespace file






