#include "StdAfx.h"

namespace ca2
{

   bool system_file::path::is_equal(const char * lpszFilPathA, const char * lpszFilPathB)
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
   bool system_file::path::eat_end_level(string & str, int iLevelCount, const char * lpSeparator)
   {
      stringa stra;
      stringa straSeparator;
      straSeparator.add("/");
      straSeparator.add("\\");
      stra.add_smallest_tokens(str, straSeparator, FALSE);

      str.Empty();
      for(int i = 0; i < (stra.get_size() - iLevelCount); i++)
      {
         str += stra[i];
         str += lpSeparator;
      }
      return true;
   }

   bool system_file::path::is_relative(const char * psz)
   {
      string strPath(psz);
      if(strPath.find(':') != -1 && strPath.find(':') < 10) 
         return false;
      if(strPath.find('/') == 0 || strPath.find('\\') == 0) 
         return false;
      return true;
   }

   void system_file::get_ascendants_path(const char * lpcsz, stringa & straParam)
   {
      stringa stra;
      get_ascendants_name(lpcsz, stra);
      string str;
      for(int i = 0; i < stra.get_size(); i++)
      {
         str += stra[i];
         str += "\\";
         straParam.add(str);
      }
   }

   void system_file::get_ascendants_name(const char * lpcsz, stringa & straParam)
   {
      stringa straSeparator;
      straSeparator.add("/");
      straSeparator.add("\\");
      straParam.add_smallest_tokens(lpcsz, straSeparator, FALSE);
   }

   var system_file::length(const char * pszPath)
   {
      var varRet;
      WIN32_FILE_ATTRIBUTE_DATA data;
      if(!GetFileAttributesExW(gen::international::utf8_to_unicode(pszPath),
         GetFileExInfoStandard, &data))
      {
         varRet.set_type(var::type_null);
         return varRet;
      }
      varRet = data.nFileSizeLow;
      return varRet;
   }


   string system_file::time_square(const char * pszPrefix, const char * pszSuffix)
   {
      string str;
      System.dir().time_square(str);
      return time(str, 25, pszPrefix, pszSuffix);
   }

   string system_file::time_log(const char * pszId)
   {
      return time(System.dir().time_log(pszId), 9);
   }

   string system_file::time(const char * psz, int iMaxLevel, const char * pszPrefix, const char * pszSuffix)
   {
      mutex_lock lockMachineEvent(
         &System.machine_event_central() != NULL ?
            System.machine_event_central().m_machineevent.m_hmutex 
            : NULL);
      int iIncLevel = -1;
      string str;
   restart:
      str.Empty();
      str = psz;
      System.dir().mk(str);
      stringa straTitle;
      string strFormat;
      for(int i = 1; i <= iMaxLevel;)
      {
        if(!System.dir().is(str))
           throw "time square dir does not exist";
        straTitle.remove_all();
         System.dir().ls(str, NULL, &straTitle);
         if(i < iMaxLevel)
         {
            int iMax = filterex_time_square(straTitle);
            if(iMax == -1)
            {
               str = System.dir().path(str, "00");
               System.dir().mk(str);
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
                  System.dir().mk(str);
               }
            }
            i++;
         }
         else // if i == iMaxLevel
         {
            System.dir().ls(str, NULL, &straTitle);
            int iMax = filterex_time_square(straTitle);
            if(iMax == -1)
            {
               str = System.dir().path(str, "00");
               if(system_file::mk_time(str))
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
               strFormat += gen::str::if_null(pszPrefix);
               strFormat += gen::str::has_char(pszSuffix, ".");
               str = System.dir().path(str, strFormat);
               if(system_file::mk_time(str))
                  break;
            }
         }
      }
      return str;
   }

   int system_file::filterex_time_square(stringa & stra)
   {
      int iMax = -1;
      int iIndex;
      for(int i = 0; i < stra.get_size(); i++)
      {
         if(stra[i].get_length() < 2)
         {
            stra.remove_at(i);
            i--;
            continue;
         }
         if(!isdigit(stra[i][0]) || !isdigit(stra[i][1]))
         {
            stra.remove_at(i);
            i--;
            continue;
         }
         iIndex = atoi(stra[i].Mid(0, 2));
         if(iIndex > iMax)
            iMax = iIndex;
      }
      return iMax;
   }

   // fail if exists, create if not exists
   bool system_file::mk_time(const char * lpcszCandidate)
   {
      ex1::filesp spfile(get_app());
      if(::GetFileAttributesW(gen::international::utf8_to_unicode(lpcszCandidate))
         != INVALID_FILE_ATTRIBUTES)
         return false;
      if(!spfile->open(lpcszCandidate, ::ex1::file::mode_create | ::ex1::file::type_binary))
         return false;
      return true;
   }

   string system_file::as_string(var varFile, ::ca::application * papp)
   {
      primitive::memory storage;
      if(varFile.ca2 < ::ex1::file > () != NULL)
      {
         storage.FullLoad(*varFile.ca2 < ::ex1::file >());
      }
      else
      {
         string strFilePath(varFile);
         if(gen::str::find_ci(".zip:", strFilePath) >= 0)
         {
            gen::memory_file memfile(get_app(), storage);
            zip::InFile infile(get_app());
            if(!infile.open(strFilePath, 0, NULL))
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
            System.http().get(strFilePath, storage, &AppUser(papp));
         }
         else
         {
            as_memory(strFilePath, storage, papp);
         }
      }
      string strResult;
      if(storage.GetStorageSize() >= 2
      && storage.GetAllocation()[0] == 255
      && storage.GetAllocation()[1] == 60)
      {
         gen::international::unicode_to_utf8(strResult, (const wchar_t *) &storage.GetAllocation()[2], storage.GetStorageSize() - 2);
      }
      else if(storage.GetStorageSize() >= 3
      && storage.GetAllocation()[0] == 0xef
      && storage.GetAllocation()[1] == 0xbb
      && storage.GetAllocation()[2] == 0xbf)
      {
         strResult = string((const char *) (const wchar_t *) &storage.GetAllocation()[3], storage.GetStorageSize() - 3);
      }
      else 
      {
         strResult = string((const char *) storage.GetAllocation(), storage.GetStorageSize());
      }
      
      return strResult;
   }

   void system_file::as_memory(var varFile, primitive::memory & mem, ::ca::application * papp)
   {
      ex1::filesp spfile(get_app());

      if(varFile.get_type() == var::type_string
      && (gen::str::begins(varFile, "http://")
         || gen::str::begins(varFile, "https://")))
      {
         System.http().get(varFile, mem, &AppUser(papp));
      }
      else if(varFile.get_type() == var::type_propset
      && varFile.propset()["file"].ca2 < ::ex1::file >() != NULL)
      {
         mem.read(*varFile.propset()["file"].ca2 < ::ex1::file >());
      }
      else if(varFile.get_type() == var::type_ca2
      && varFile.ca2 < ::ex1::file >() != NULL)
      {
         mem.read(*varFile.ca2 < ::ex1::file >());
      }
      else if(varFile.get_type() == var::type_string)
      {
         string str(varFile);
         if(gen::str::begins_eat_ci(str, "matter://"))
         {
            str = System.dir().matter(str);
         }
         try
         {
            spfile->open(str, ::ex1::file::type_binary | ::ex1::file::mode_read | ::ex1::file::shareDenyNone);
         }
         catch(ex1::exception * pe)
         {
            gen::del(pe);
            return;
         }
         mem.FullLoad(spfile);
      }
   }

   void system_file::lines(stringa & stra, var varFile, ::ca::application * papp)
   {
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

   bool system_file::put_contents(const char * lpcsz, const char * lpcszContents)
   {
      ex1::filesp spfile(get_app());
      if(!spfile->open(
         lpcsz, 
         ::ex1::file::type_binary 
         | ::ex1::file::mode_write 
         | ::ex1::file::mode_create 
         | ::ex1::file::shareDenyNone
         | ::ex1::file::defer_create_directory))
         return false;
      else
      {
         spfile->write(lpcszContents, strlen(lpcszContents));
         spfile->Flush();
         spfile->close();
         return true;
      }
   }
   bool system_file::put_contents_utf8(const char * lpcsz, const char * lpcszContents)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(lpcsz, ::ex1::file::type_binary | ::ex1::file::mode_write | ::ex1::file::mode_create | ::ex1::file::shareDenyNone | ::ex1::file::defer_create_directory))
            return false;
      }
      catch(...)
      {
         return false;
      }
      char sig[] = {'\xef', '\xbb', '\xbf'};
      spfile->write(&sig, sizeof(sig));
      spfile->write(lpcszContents, strlen(lpcszContents));
      spfile->Flush();
      spfile->close();
      return true;
   }
   bool system_file::put_contents(const char * lpcsz, ex1::file & file)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(
            lpcsz, 
            ::ex1::file::type_binary 
            | ::ex1::file::mode_write 
            | ::ex1::file::mode_create 
            | ::ex1::file::shareDenyNone
            | ::ex1::file::defer_create_directory))
            return false;
      }
      catch(...)
      {
         return false;
      }
      primitive::memory mem;
      mem.allocate(1024 * 1024 * 8);
      UINT uiRead;
      while((uiRead = file.read(mem.GetAllocation(), mem.GetStorageSize())) > 0)
      {
         spfile->write(mem.GetAllocation(), uiRead);
      }
      spfile->Flush();
      spfile->close();
      return true;
   }
   bool system_file::put_contents(const char * lpcsz, primitive::memory & mem)
   {
      ex1::filesp spfile(get_app());
      try
      {
         if(!spfile->open(
            lpcsz, 
            ::ex1::file::type_binary 
            | ::ex1::file::mode_write 
            | ::ex1::file::mode_create 
            | ::ex1::file::shareDenyNone
            | ::ex1::file::defer_create_directory))
            return false;
      }
      catch(...)
      {
         return false;
      }
      spfile->write(mem.GetAllocation(), mem.GetStorageSize());
      spfile->Flush();
      spfile->close();
      return true;
   }
   void system_file::path::split(stringa & stra, const char * lpcszPath)
   {
      stringa straSeparator;
      straSeparator.add("\\");
      straSeparator.add("/");
      stra.add_smallest_tokens(lpcszPath, straSeparator, FALSE);
   }

   class system_file::path & system_file::path()
   {
      return m_path;
   }

   system_file::system_file()
   {
   }

   string system_file::title_(const char * path)
   {
      string str = name_(path);
      int iPos = str.reverse_find('.');
      if(iPos != -1)
      {
         return str.Mid(0, iPos);
      }
      else
      {
         return str;
      }
   }

   string system_file::name_(const char * path)
   {
      string str(path);
      int iPos;
      int iPos1 = str.reverse_find('\\');
      int iPos2 = str.reverse_find('/');
      if(iPos1 != -1 && iPos2 != -1)
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
      else if(iPos1 != -1)
      {
         iPos = iPos1 + 1;
      }
      else if(iPos2 != -1)
      {
         iPos = iPos2 + 1;
      }
      else
      {
         iPos = 0;
      }
      return str.Mid(iPos);
   }

   string system_file::extension(const char * path)
   {
      string str = name_(path);
      int iPos = str.reverse_find('.');
      if(iPos != -1)
      {
         return str.Mid(iPos + 1);
      }
      else
      {
         return "";
      }
   }

   void system_file::copy(const char * pszNew, const char * psz, bool bFailIfExists)
   {
      if(bFailIfExists)
      {
         if(exists(pszNew))
            throw "Failed to copy file";
      }
      if(System.dir().is(psz) && !gen::str::ends_ci(psz, ".zip"))
      {
         stringa straPath;
         System.dir().rls(psz, &straPath);
         string strNew;
         string strOld;
         for(int i = 0; i < straPath.get_size(); i++)
         {
            strOld = straPath[i];
            strNew = strOld;
            strNew.replace(psz, pszNew);
            if(System.dir().is(strOld))
            {
               System.dir().mk(strNew);
            }
            else
            {
               if(!System.dir().is(System.dir().name(strNew)))
               {
                  System.dir().mk(System.dir().name(strNew));
               }
               if(!::CopyFileW(
                  gen::international::utf8_to_unicode(strOld), 
                  gen::international::utf8_to_unicode(strNew), bFailIfExists))
                  throw "Failed to copy file";
            }
         }
      }
      else
      {
         System.dir().mk(System.dir().name(pszNew));
         if(!::CopyFileW(
            gen::international::utf8_to_unicode(psz), 
            gen::international::utf8_to_unicode(pszNew), bFailIfExists))
         {
            DWORD dwError = ::GetLastError();
            string strError;
            strError.Format("Failed to copy file \"%s\" to \"%s\" bFailIfExists=%d error=%d", psz, pszNew, bFailIfExists, dwError);
            throw strError;
         }
      }
   }

   void system_file::move(const char * pszNew, const char * psz)
   {
      if(!::MoveFileW(
         gen::international::utf8_to_unicode(psz), 
         gen::international::utf8_to_unicode(pszNew)))
      {
         DWORD dwError = ::GetLastError();
         string strError;
         strError.Format("Failed to move file \"%s\" to \"%s\" error=%d", psz, pszNew, dwError);
         throw strError;
      }
   }

   void system_file::del(const char * psz)
   {
      if(!::DeleteFileW(
         gen::international::utf8_to_unicode(psz)))
      {
         DWORD dwError = ::GetLastError();
         if(dwError == 2) // the file does not exist, so delete "failed"
            return;
         string strError;
         strError.Format("Failed to delete file \"%s\" error=%d", psz, dwError);
         throw strError;
      }
   }


   string system_file::copy(const char * psz)
   {
      string strCopy("copy");
      string strNew;
      if(System.dir().is(psz))
      {
         int i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d", psz, strCopy, i);
            if(!exists(strNew))
            {
               copy(strNew, psz);
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
         int i = 1;
         while( i <= 100)
         {
            strNew.Format("%s-%s-%d%s", psz, strCopy, i, strExt);
            if(!exists(strNew))
            {
               copy(strNew, psz);
               return strNew;
            }
            i++;
         }
      }
      return "";
   }


   bool system_file::exists(const char * pszPath)
   {
      int iFind = gen::str::find_ci(".zip:", pszPath);
      zip::Util ziputil(get_app());
      if(iFind >= 0)
         return ziputil.exists(pszPath);
      return ::GetFileAttributesW(gen::international::utf8_to_unicode(pszPath)) != INVALID_FILE_ATTRIBUTES;
   }

   string system_file::paste(const char * pszLocation, const char * path)
   {
      string strDir = System.dir().name(path);
      string strDest = System.dir().path(pszLocation, "");
      string strSrc = System.dir().path(strDir, "");
      if(strDest == strSrc)
      {
         return copy(path);
      }
      else
      {
         string strNew = System.dir().path(strDest, name_(path));
         copy(strNew, path);
         return strNew;
      }
   }

   void system_file::trash_that_is_not_trash(stringa & stra)
   {
      for(int i = 0; i < stra.get_size(); i++)
      {
         trash_that_is_not_trash(stra[i]);
      }
   }

   void system_file::trash_that_is_not_trash(const char * psz)
   {
      string strDir = System.dir().trash_that_is_not_trash(psz);
      System.dir().mk(strDir);
      ::MoveFile(psz, System.dir().path(strDir, name_(psz)));
   }

   void system_file::replace(const char * pszContext, const char * pszFind, const char * pszReplace)
   {
      stringa straTitle;
      System.dir().ls(pszContext, NULL, &straTitle);
      string strOld;
      string strNew;
      for(int i = 0; i < straTitle.get_size(); i++)
      {
         strOld = straTitle[i];
         strNew = strOld;
         strNew.replace(pszFind, pszReplace);
         if(strNew != strOld)
         {
            ::MoveFileW(
               gen::international::utf8_to_unicode(System.dir().path(pszContext, strOld)), 
               gen::international::utf8_to_unicode(System.dir().path(pszContext, strNew)));
         }
      }
   }

   bool system_file::is_read_only(const char * psz)
   {
      DWORD dwAttrib = GetFileAttributesW(gen::international::utf8_to_unicode(psz));
      if(dwAttrib & FILE_ATTRIBUTE_READONLY)
         return true;
      return false;
   }

   string system_file::sys_temp(const char * pszName, const char * pszExtension)
   {
      char lpPathBuffer[MAX_PATH * 16];
    // get the temp path.
      DWORD dwRetVal = GetTempPath(sizeof(lpPathBuffer),     // length of the buffer
                           lpPathBuffer); // buffer for path 
      if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
      {
         printf ("GetTempPath failed (%d)\n", GetLastError());
         return "";
      }
      string str;
      char buf[30];
      int iLen= strlen(lpPathBuffer);
      if(!(lpPathBuffer[iLen - 1] == '/'
         || lpPathBuffer[iLen - 1] == '\\'))
      {
         lpPathBuffer[iLen] = '\\';
         lpPathBuffer[iLen+1] = '\0';
      }
      for(int i = 0; i < 1000; i++)
      {
         sprintf(buf, "%d", i);
         str = lpPathBuffer;
         str += pszName;
         str += "-";
         str += buf;
         str += ".";
         str += pszExtension;
         if(!exists(str))
            return str;
      }
      return "";
   }

   string system_file::sys_temp_unique(const char * pszName)
   {
      char lpPathBuffer[MAX_PATH * 16];
    // get the temp path.
      DWORD dwRetVal = GetTempPath(sizeof(lpPathBuffer),     // length of the buffer
                           lpPathBuffer); // buffer for path 
      if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
      {
         printf ("GetTempPath failed (%d)\n", GetLastError());
         return "";
      }
      string str;
      int iLen= strlen(lpPathBuffer);
      if(!(lpPathBuffer[iLen - 1] == '/'
         || lpPathBuffer[iLen - 1] == '\\'))
      {
         lpPathBuffer[iLen] = '\\';
         lpPathBuffer[iLen+1] = '\0';
      }
      str = lpPathBuffer;
      str += pszName;
      return str;
   }

   ex1::filesp system_file::time_square_file(const char * pszPrefix, const char * pszSuffix)
   {
      return get(time_square(pszPrefix, pszSuffix));
   }

   ex1::filesp system_file::get(const char * name)
   {
      System.dir().mk(System.dir().name(name));
      ex1::filesp fileOut(get_app());
      ::ex1::file_exception_sp e(get_app());
      if(!fileOut->open(name, ::ex1::file::mode_create | ::ex1::file::type_binary | ::ex1::file::mode_write, &e))
         throw e;
      return fileOut;
   }


} // namespace ca2
