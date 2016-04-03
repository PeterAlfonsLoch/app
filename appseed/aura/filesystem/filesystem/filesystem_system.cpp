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

//CLASS_DECL_AURA void NESSIEinit(struct NESSIEstruct * const structpointer);
//CLASS_DECL_AURA void NESSIEadd(const uchar * const source, uint_ptr sourceBits, struct NESSIEstruct * const structpointer);
//CLASS_DECL_AURA void NESSIEfinalize(struct NESSIEstruct * const structpointer, uchar * const result);








namespace file
{


   //bool system::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
   //{
   //   string stra(lpszFilPathA);
   //   string wstrb(lpszFilPathB);

   //   //   ::str::international::ACPToUnicode(stra, lpszFilPathA);
   //   //   ::str::international::ACPToUnicode(wstrb, lpszFilPathB);
   //   if(stra == wstrb)
   //      return true;

   //   /*if(_GetShortPathName(stra, lpszFilPathA) == 0)
   //   return false;
   //   if(_GetShortPathName(wstrb, lpszFilPathB) == 0)
   //   return false;*/
   //   return stra == wstrb;

   //}


   //bool system::path::eat_end_level(string & str, int32_t iLevelCount, const char * lpSeparator)
   //{

   //   return ::dir::eat_end_level(str, iLevelCount, lpSeparator);

   //}


   //bool system::path::is_relative(const char * psz)
   //{

   //   return file_path_is_relative_dup(psz) != FALSE;

   //}


//   void system::get_ascendants_path(const ::file::path & lpcsz,::file::patha & straParam)
//   {
//      ::file::patha stra;
//      get_ascendants_name(lpcsz, stra);
//      ::file::path str;
////      bool bUrl = System.url().is_url(lpcsz);
//      bool bUrl = false;
//#if defined(LINUX) || defined(APPLEOS)
//      bool bLinux = true;
//      str += "/";
//#else
//      bool bLinux = false;
//#endif
//
//      for(int32_t i = 0; i < stra.get_size(); i++)
//      {
//         str /= stra[i];
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
//         straParam.add(str);
//      }
//   }
//
//   void system::get_ascendants_name(const ::file::path & lpcsz,::file::patha & straParam)
//   {
//
//      stringa straSeparator;
//
//      straSeparator.add("/");
//      straSeparator.add("\\");
//
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


   bool system::exists(const ::file::path & pszPath, ::aura::application * papp)
   {

      return exists(pszPath, NULL, papp);

   }


   //bool system::exists(const char * pszPath, var * pvarQuery, ::aura::application * papp)
   //{

   //   return exists(string(pszPath), pvarQuery, papp);

   //}


   //bool system::exists(const ::file::path & strPath,::aura::application * papp)
   //{

   //   return exists(strPath, NULL, papp);

   //}


   bool system::exists(const ::file::path & strPath,var * pvarQuery,::aura::application * papp)
   {






      //if (!papp->m_paurasystem->dir().name_is(strPath, papp))
      //   return false;

#ifdef WINDOWS


      return file_exists_dup(strPath) != FALSE;

#else

      struct stat st;

      if (stat(strPath, &st) != 0)
         return false;

      return S_ISREG(st.st_mode) || S_ISDIR(st.st_mode);

#endif

   }

   var system::length(const ::file::path & pszPath,::aura::application * papp)
   {

      return length(pszPath, NULL, papp);

   }


   //var system::length(const ::file::path & pszPath,var * pvarQuery,::aura::application * papp)
   //{

   //   return length(string(pszPath), pvarQuery, papp);

   //}


   //var system::length(const string & strPath, ::aura::application * papp)
   //{

   //   return length(strPath, NULL, papp);

   //}


   var system::length(const ::file::path & strPath,var * pvarQuery,::aura::application * papp)
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


   ::file::path system::module()
   {

      return m_pathModule;

   }


   ::file::path system::ca2module()
   {

      return m_pathCa2Module;

   }


   ::file::path system::time_square(::aura::application * papp,const string & pszPrefix,const string & pszSuffix)
   {

      return time(papp,System.dir().time_square(papp,pszPrefix,pszSuffix),25,pszPrefix,pszSuffix);

   }


   ::file::path system::time_log(::aura::application * papp,const string & pszId)
   {
      return time(papp, System.dir().time_log(pszId), 9);
   }


   ::file::path system::time(::aura::application * papp,const ::file::path & psz,int32_t iMaxLevel,const string & pszPrefix,const string & pszSuffix)
   {

      synch_lock lockMachineEvent((&System.machine_event_central() != NULL) ? &System.machine_event_central().m_machineevent.m_mutex : ((mutex *) NULL));

      int32_t iIncLevel = -1;

      ::file::path str;

      string strPrefix(pszPrefix);

      string strSuffix(pszSuffix);

restart:

      str.Empty();

      str = psz;

      System.dir().mk(str, papp);

      listing ls(papp);

      string strFormat;

      for(int32_t i = 1; i <= iMaxLevel;)
      {

         System.dir().mk(str, papp);

         if(!System.dir().is(str, papp))
            throw "time square dir does not exist";

         ls.ls(str);

         if(i < iMaxLevel)
         {

            int32_t iMax = filterex_time_square("", ls);

            if(iMax == -1)
            {
               str /= "00";
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
               str /= strFormat;
               if(i == iIncLevel)
               {
                  System.dir().mk(str, papp);
               }
            }
            i++;
         }
         else // if i == iMaxLevel
         {

            ls.ls(str);

            int32_t iMax = filterex_time_square(pszPrefix, ls);

            if(iMax == -1)
            {
               str = str / (strPrefix+"00"+strSuffix);
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
               str = str / (strPrefix+strFormat+strSuffix);
               if(system::mk_time(str))
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
      for(int32_t i = 0; i < stra.get_size(); i++)
      {
         string str = stra[i].name();
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
      ::file::buffer_sp spfile(allocer());
      if(System.file().exists(lpcszCandidate, get_app()))
         return false;
      try
      {
         if(spfile->open(lpcszCandidate, ::file::mode_create | ::file::type_binary).failed())
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
      memory storage;
      if(varFile.cast < ::file::stream_buffer > () != NULL)
      {
         ::file::byte_istream is(varFile.cast < ::file::stream_buffer >());
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
         ::str::international::unicode_to_utf8(strResult, (const unichar *) &storage.get_data()[2], (int32_t)(storage.get_size() - 2));
      }
      else if (storage.get_size() >= 3
         && storage.get_data()[0] == 255
         && storage.get_data()[1] == 254
         && storage.get_data()[2] == 0x73)
      {
         ::str::international::unicode_to_utf8(strResult, (const unichar *)&storage.get_data()[2], (int32_t)(storage.get_size() - 2));
      }
      else if (storage.get_size() >= 3
         && storage.get_data()[0] == 0xef
         && storage.get_data()[1] == 0xbb
         && storage.get_data()[2] == 0xbf)
      {
         strResult = string((const char *) (const unichar *) &storage.get_data()[3], (int32_t) (storage.get_size() - 3));
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

         ::file::byte_istream is(spfile);

         is >> mem;

      }
      catch(...)
      {
      }



   }


   void system::lines(stringa & stra, var varFile, ::aura::application * papp)
   {

      UNREFERENCED_PARAMETER(papp);


      ::file::buffer_sp spfile;

      try
      {

         spfile = App(papp).file().get_file(varFile,::file::type_text | ::file::mode_read);

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

      ::file::buffer_sp spfile;

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

   bool system::add_contents(var varFile,const void * pvoidContents,::count count,::aura::application * papp)
   {

      ::file::buffer_sp spfile;

      try
      {

         spfile = App(papp).file().get_file(varFile,::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::mode_no_truncate | ::file::share_deny_none | ::file::defer_create_directory);

      }
      catch(...)
      {

         return false;

      }

      if(spfile.is_null())
         return false;


      spfile->seek_to_end();

      spfile->write(pvoidContents,count);

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


   bool system::add_contents(var varFile,const char * lpcszContents,::aura::application * papp)
   {

      if(lpcszContents != NULL)
      {

         return add_contents(varFile,lpcszContents,strlen(lpcszContents),papp);

      }

      return false;

   }


   bool system::put_contents(var varFile, ::file::reader & reader, ::aura::application * papp)
   {
      ::file::buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      memory mem;
      mem.allocate(1024 * 1024 * 8);
      memory_size_t uiRead;
      while((uiRead = reader.read(mem.get_data(), mem.get_size())) > 0)
      {
         spfile->write(mem.get_data(), uiRead);
      }
      return true;
   }

   bool system::put_contents(var varFile, memory & mem, ::aura::application * papp)
   {
      return put_contents(varFile, mem.get_data(), (count) mem.get_size(), papp);
   }

   bool system::put_contents_utf8(var varFile, const char * lpcszContents, ::aura::application * papp)
   {
      ::file::buffer_sp spfile;
      spfile = App(papp).file().get_file(varFile, ::file::type_binary | ::file::mode_write | ::file::mode_create | ::file::share_deny_none | ::file::defer_create_directory);
      if(spfile.is_null())
         return false;
      spfile->write("\xef\xbb\xbf", 3);
      spfile->write(lpcszContents, strlen(lpcszContents));
      return true;
   }

   //void system::path::split(::file::patha & stra, const char * lpcszPath)
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

   system::system(::aura::application * papp) :
      object(papp)
   {
      //m_path.m_pfile = this;

   }

   system::~system()
   {

   }

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

   ::cres system::copy(const ::file::path & pszNew,const ::file::path & psz,bool bFailIfExists,e_extract eextract,::aura::application * papp)
   {

      if(!papp->m_spdir->is(pszNew.folder()))
      {

         papp->m_spdir->mk(pszNew.folder());

      }

      if(!::file_copy_dup(pszNew,psz,!bFailIfExists))
      {

         return ::failure;

      }

      return ::no_exception;

   }


   bool system::get_status(const ::file::path & path,::file::file_status & status,::aura::application * papp)
   {

      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(status);
      throw interface_only_exception(papp);

   }


   cres system::set_status(const ::file::path & path,const ::file::file_status & status,::aura::application * papp)
   {

      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(status);
      throw interface_only_exception(papp);

   }


   ::cres system::move(const ::file::path & pszNew,const ::file::path & psz,::aura::application * papp)
   {
#ifdef WINDOWSEX

      if(!::MoveFileW(::str::international::utf8_to_unicode(psz), ::str::international::utf8_to_unicode(pszNew)))
      {

         return ::failure;

      }
#elif defined(METROWIN)

      ::Windows::Storage::StorageFile ^ file = get_os_file(psz,  0, 0, NULL, OPEN_EXISTING, 0, NULL);

      if(file == nullptr)
         throw "file::system::move Could not move file, could not open source file";

      string strDirOld     = psz.folder();
      string strDirNew     = pszNew.folder();
      string strNameOld    = psz.name();
      string strNameNew    = pszNew.name();

      if(strDirOld == strDirNew)
      {
         if(strNameOld == strNameNew)
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
      if(::rename(psz, pszNew) != 0)
      {
         int32_t err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         throw strError;
      }
#endif

      return ::no_exception;

   }


   ::cres system::del(const ::file::path & psz,::aura::application * papp)
   {

      if(!exists(psz,papp))
         return no_exception;

#ifdef WINDOWSEX

      if(!::DeleteFileW(::str::international::utf8_to_unicode(string("\\\\?\\") + psz)))
      {
         uint32_t dwError = ::GetLastError();
         if(dwError == 2) // the file does not exist, so delete "failed"
            return failure;
         string strError;
         strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
         TRACE(strError);
         return failure;
      }

      return no_exception;

#else
      if(remove(psz) != 0)
      {
         int32_t err = errno;
         string strError;
         strError.Format("Failed to delete file error=%d", err);
         throw strError;
      }
#endif

      return no_exception;

   }


   ::file::path system::copy(const ::file::path & psz,::aura::application * papp)
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
         string strExt = psz.ext();
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



   ::file::path system::paste(const ::file::path & pszLocation,const ::file::path & path,::aura::application * papp)
   {
      //::file::path strDir = System.dir().name(path);
      ::file::path strDir = path.name();
      ::file::path strDest = pszLocation;
      ::file::path strSrc = strDir;
      if(strDest == strSrc)
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

   void system::trash_that_is_not_trash(::file::patha & stra, ::aura::application * papp)
   {

      if(stra.get_size() <= 0)
         return;

      ::file::path strDir = System.dir().trash_that_is_not_trash(stra[0]);

      System.dir().mk(strDir, papp);

      for(int32_t i = 0; i < stra.get_size(); i++)
      {
#ifdef WINDOWS
         move(strDir / stra[i].name(), stra[i], papp);
#else
         ::rename(stra[i], strDir / stra[i].name());
#endif
      }

   }

   void system::trash_that_is_not_trash(const ::file::path & psz,::aura::application * papp)
   {

      ::file::path strDir = System.dir().trash_that_is_not_trash(psz);

      System.dir().mk(strDir, papp);

#ifdef WINDOWS
      //         ::MoveFile(psz, strDir / name_(psz)));
      move(strDir / psz.name(), psz, papp);
#else
      ::rename(psz, strDir / psz.name());
#endif

   }

   ::cres system::replace(const ::file::path & pszContext,const string & pszFind,const string & pszReplace,::aura::application * papp)
   {

      listing ls(papp);

      ls.ls(pszContext);

      string strOld;
      string strNew;
      string strFail;
      for(int32_t i = 0; i < ls.get_size(); i++)
      {
         strOld = ls[i].name();
         strNew = strOld;
         strNew.replace(pszFind, pszReplace);
         if(strNew != strOld)
         {
#ifdef WINDOWS
            //               ::MoveFileW(
            //                ::str::international::utf8_to_unicode(pszContext, strOld)),
            //              ::str::international::utf8_to_unicode(pszContext, strNew)));
            try
            {
               move(::file::path(pszContext)/ strNew, ::file::path(pszContext) / strOld, papp);
            }
            catch(...)
            {
               strFail += "failed to move " + ::file::path(pszContext)/ strOld + " to " + ::file::path(pszContext) / strNew;
            }
#else
            ::rename(::file::path(pszContext) / strOld, ::file::path(pszContext) / strNew);
#endif
         }
      }

      if(strFail.has_char())
      {

         return fesp(papp,::file::exception::none,-1,strFail);

      }

      return no_exception;

   }


   bool system::is_read_only(const ::file::path & psz)
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


   ::file::path system::sys_temp(const ::file::path & pszName, const char * pszExtension, ::aura::application * papp)
   {

      ::file::path strTempDir = ::dir::sys_temp();

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


   ::file::path system::sys_temp_unique(const ::file::path & pszName)
   {

      return ::dir::sys_temp() / pszName;

   }


   ::file::buffer_sp system::time_square_file(::aura::application * papp, const string & pszPrefix, const string & pszSuffix)
   {

      return get(time_square(papp, pszPrefix, pszSuffix), papp);

   }


   ::file::buffer_sp system::get(const ::file::path & name,::aura::application * papp)
   {

      System.dir().mk(name.name(), papp);

      ::file::buffer_sp fileOut = App(papp).file().get_file(name, ::file::mode_create | ::file::type_binary | ::file::mode_write);

      if(fileOut.is_null())
         throw ::file::exception(papp, ::file::exception::none,-1L, name);

      return fileOut;

   }


   ::file::path system::replace_extension(const ::file::path & pszFile, const char * pszExtension)
   {

      ::file::path strFile(pszFile);

      set_extension(strFile, pszExtension);

      return strFile;

   }


   void system::set_extension(::file::path & strFile, const char * pszExtension)
   {

      strsize iEnd = strFile.reverse_find('.');

      if(iEnd < 0)
      {

         iEnd = strFile.get_length();

      }

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

   int32_t system::cmp(const ::file::path & psz1, const ::file::path & psz2)
   {
      string str1(psz1);
      normalize(str1);
      string str2(psz2);
      normalize(str2);
      return str1.CompareNoCase(str2);
   }



   cres system::rename(const ::file::path & pszNew,const ::file::path & psz,::aura::application * papp)
   {

      ::file::path strDir = psz.folder();

      ::file::path strDirNew = pszNew.folder();

      if(strDir != strDirNew)
      {

         // rename should work only on files in the same directory/folder

         return failure;

      }

      if(!move(pszNew, psz, papp))
      {

         return failure;

      }

      return no_exception;

   }


   string system::md5(const ::file::path & psz)
   {
      throw interface_only_exception(get_app());

      return "";

   }



   void system::dtf(const ::file::path  & pszFile,const ::file::path & pszDir,::aura::application * papp)
   {
      listing ls(papp);
      ls.rls( pszDir);
      dtf(pszFile, ls, papp);
   }

   void system::dtf(const ::file::path & pszFile,::file::patha & stra,::aura::application * papp)
   {

      throw interface_only_exception(get_app());

   }

   void system::ftd(const ::file::path & pszDir,const ::file::path & pszFile,::aura::application * papp)
   {

      throw interface_only_exception(get_app());

   }


   bool system::resolve_link(string & strTarget, string & strFolder, string & strParams, const string & pszSource, ::user::primitive * puiMessageParentOptional)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   bool system::is_valid_fileset(const ::file::path & pszFile,::aura::application * papp)
   {

      throw interface_only_exception(get_app());

      return false;

   }


   string system::nessie(const ::file::path & psz)
   {

      ::file::buffer_sp spfile(allocer());
      try
      {
         if(spfile->open(psz,::file::type_binary | ::file::mode_read).failed())
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


   bool system::update_module_path()
   {

      m_pathModule = "";
      m_pathCa2Module = "";


      return true;

   }


   bool system::initialize()
   {
      
      return true;
      
   }

   ::file::buffer_sp system::get_file(var varFile,UINT nOpenFlags,cres * pfesp,::aura::application * papp)
   {

      if(pfesp != NULL)
      {
         ::release(pfesp->m_p);
      }

      ::cres cres;

      ::file::buffer_sp spfile;

      ::file::path strPath;

      if(varFile.get_type() == var::type_element)
      {

         spfile = varFile.cast < ::file::stream_buffer >();

         if(spfile.is_set())
            return spfile;

      }
      else if(varFile.get_type() == var::type_string)
      {

         strPath = varFile;

         //strPath.trim("\"'");

      }
      else if(varFile.get_type() == var::type_stra)
      {

         if(varFile.stra().get_count() > 0)
         {

            strPath = varFile.stra()[0];

         }

         //strPath.trim("\"'");

      }
      else if(varFile.get_type() == var::type_propset)
      {

         if(varFile.has_property("url"))
         {

            strPath = varFile["url"];

            //strPath.trim("\"'");

         }

      }

      if(varFile.get_type() == var::type_propset && varFile.propset()["file"].cast < ::file::binary_buffer >() != NULL)
      {

         spfile = varFile.propset()["file"].cast < ::file::stream_buffer >();

      }
      else
      {

         if(strPath.is_empty())
         {
            TRACE("::application::get_file file with empty name!!");
            return spfile;
         }

         /*            if((nOpenFlags & ::file::mode_create) == 0 && !exists(strPath))
         {
         TRACE("::application::file does not exist!! : \"%s\"",strPath);
         return spfile;
         }
         */

         spfile = App(papp).alloc(System.type_info < ::file::stream_buffer >());

         cres = spfile->open(strPath,nOpenFlags);


      }

      if(cres.failed())
      {

         spfile.release();

         if(pfesp != NULL)
         {

            *pfesp = cres;

         }

      }

      return spfile;


   }


} // namespace file






