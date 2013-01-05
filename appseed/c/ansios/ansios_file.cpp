#include "framework.h"
#include <sys/stat.h>
#include <sys/types.h>
//Copy file using mmap()
#include <fcntl.h>
#include <sys/mman.h>
#define PACKAGE "mmap"

void ensure_file_size(int32_t fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      throw "fd_ensure_file_size exception";

}


size_t get_file_size(int32_t fd)
{

   struct stat st;

   if(fstat(fd, &st) == -1)
   {

      ::close(fd);

      return -1;

   }

   return st.st_size;

}






bool file_exists_dup(const char * path1)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if((st.st_mode & S_IFDIR))
      return false;

   return true;

}



bool file_put_contents_dup(const char * path, const char * contents, ::count len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);

   HANDLE hfile = ::create_file(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   if(hfile == INVALID_HANDLE_VALUE)
      return false;
   count dwWrite;
   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;
   uint32_t dwWritten = 0;
   bool bOk = ::WriteFile(hfile, contents, (uint32_t) dwWrite, &dwWritten, NULL) != FALSE;
   ::CloseHandle(hfile);
   return dwWrite == dwWritten && bOk != FALSE;


}




vsstring file_as_string_dup(const char * path)
{
   
   vsstring str;


   FILE * f = fopen(path, "rb");

   if(f == NULL)
      return "";

   ::count iSize = fsize_dup(f);

   str.alloc(iSize);

   ::count iRead = fread(str, iSize, 1, f);

   str.m_psz[iRead] = '\0';

   fclose(f);

   return str;

}


bool file_get_memory_dup(simple_memory & memory, const char * path)
{

   FILE * f = fopen(path, "rb");
   if(f == NULL)
      return NULL;
   ::count iSize = fsize_dup(f);
   char * psz = (char *) _ca_alloc(iSize + 1);
   ::count iRead = fread(psz, iSize, 1, f);
   psz[iRead] = '\0';
   fclose(f);
   return psz;

}


bool get_temp_file_name_template(char * szRet, ::count iBufferSize, const char * pszName, const char * pszExtension, const char * pszTemplate)
{


   char lpPathBuffer[256 * 4];
   strcpy_dup(lpPathBuffer, "/tmp/ca2");
   char bufTime[30];
   char bufItem[30];
   char buf[30];
   size_t iLen= strlen_dup(lpPathBuffer);
   if(!(lpPathBuffer[iLen - 1] == '/'
      || lpPathBuffer[iLen - 1] == '\\'))
   {
      lpPathBuffer[iLen] = '\\';
      lpPathBuffer[iLen+1] = '\0';
   }

   tm * ptm = gmtime(NULL);

   itoa_dup(bufItem, ptm->tm_year, 10);
   zero_pad(bufItem, 4);
   strcpy_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_mon, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_mday, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_hour, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, " ");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_min, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   itoa_dup(bufItem, ptm->tm_sec, 10);
   zero_pad(bufItem, 2);
   strcat_dup(bufTime, "-");
   strcat_dup(bufTime, bufItem);

   for(int32_t i = 0; i < (1024 * 1024); i++)
   {
      strcpy_dup(szRet, lpPathBuffer);
      strcat_dup(szRet, pszName);
      //if(i >= 0)
      {
         strcat_dup(szRet, "-");
         strcat_dup(szRet, bufTime);
      }
      //if(i > 0)
      {
         strcat_dup(szRet, "-");
         sprint_hex(buf, i + 1);
         strcat_dup(szRet, buf);
      }
      strcat_dup(szRet, ".");
      strcat_dup(szRet, pszExtension);
      if(pszTemplate != NULL)
      {
         if(is_file_ok(szRet, pszTemplate))
            return true;
      }
      if(file_exists_dup(szRet))
      {
         if(unlink(szRet))
            return true;
      }
      else
      {
         return true;
      }
   }
   return false;

}





uint64_t file_length_dup(const char * path)
{

   struct stat st;
   stat(path, &st);
   return st.st_size;

}



vsstring file_module_path_dup()
{

   return "/ca2/stage";

}







bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

   FILE * hfile1 = NULL;
   FILE * hfile2 = NULL;
   hfile1 = fopen(pszFile, "rb");
   if(hfile1 == NULL)
      return false;

   vsstring strVersion;


   file_read_ex1_string_dup(hfile1, NULL, strVersion);
   int32_t n;
   vsstring strRelative;
   vsstring strMd5;
   vsstring strMd5New;
   int32_t iBufSize = 1024 * 1024;
   uchar * buf = (uchar *)  _ca_alloc(iBufSize);
   int32_t iLen;
   ::md5::md5 ctx;
   ::count dwRead;
   ::count dwWritten;
   if(strVersion == "fileset v1")
   {
      while(true)
      {
         file_read_n_number_dup(hfile1, NULL, n);
         if(n == 2)
            break;
         file_read_ex1_string_dup(hfile1, NULL, strMd5);
         ctx.initialize();
         file_read_ex1_string_dup(hfile1, &ctx, strRelative);
         vsstring strPath = dir::path(pszDir, strRelative);
         dir::mk(dir::name(strPath));
         hfile2 = fopen(strPath, "wb");
         if(hfile2 == NULL)
            return false;
         file_read_n_number_dup(hfile1, &ctx, iLen);
         while(iLen > 0)
         {
            dwRead = ::fread(buf, min(iBufSize, iLen), 1, hfile1);
            break;
            if(dwRead == 0)
               break;
            dwWritten = ::fwrite(buf, dwRead,  1, hfile2);
            ctx.update(buf, dwRead);
            iLen -= dwRead;
         }
         fclose(hfile2);
         hfile2 = NULL;
         ctx.finalize();

         strMd5New.clear();
         vsstring strFormat;
         strMd5New = ctx.to_string();
         if(strMd5.CompareNoCase(strMd5New) != 0)
            return false;
      }
   }
   fclose(hfile1);
   if(hfile2 != NULL)
      fclose(hfile2);
   return true;
}


void file_read_n_number_dup(FILE * hfile, ::md5::md5 * pctx, int32_t & iNumber)
{
   vsstring str;
   char ch;
   ::count dwRead;
   while(((dwRead = fread(&ch, 1, 1, (FILE *) hfile))) && dwRead == 1)
   {
      if(ch >= '0' && ch <= '9')
         str += ch;
      else
         break;
      if(pctx != NULL)
      {
         pctx->update(&ch, 1);
      }
   }
   if(ch != 'n')
      return;
   if(pctx != NULL)
   {
      pctx->update(&ch, 1);
   }
   iNumber = atoi_dup(str);
}

void file_read_ex1_string_dup(HANDLE hfile, ::md5::md5 * pctx, vsstring & str)
{
   int32_t iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) _ca_alloc(iLen + 1);
   ::count dwRead;
   dwRead = fread(lpsz, iLen, 1, (FILE *) hfile);
   if(pctx != NULL)
   {
      pctx->update(lpsz, iLen);
   }
   lpsz[iLen] = '\0';
   str = lpsz;
   _ca_free(lpsz, 0);
}

























bool file_copy_dup(const char * pszNew, const char * pszSrc, bool bOverwrite)
{

   int32_t input, output;
   size_t filesize;
   void *source, *target;


   int32_t flags = O_RDWR|O_CREAT|O_TRUNC;
   if(!bOverwrite)
      flags |= O_EXCL;
   if((output = open(pszNew, flags, 0666)) == -1)
   {
      fprintf(stderr, "%s: Error: opening file: %s\n", PACKAGE, pszNew);
      return false;
   }


   if((input = open(pszSrc, O_RDONLY)) == -1)
   {
      fprintf(stderr, "%s: Error: opening file: %s\n", PACKAGE, pszSrc);
      return false;
   }


   filesize = lseek(input, 0, SEEK_END);
   lseek(output, filesize - 1, SEEK_SET);
   write(output, '\0', 1);

   if((source = mmap(0, filesize, PROT_READ, MAP_SHARED, input, 0)) == (void *) -1)
   {
      fprintf(stderr, "Error mapping input file: %s\n", pszSrc);
      return false;
   }


   if((target = mmap(0, filesize, PROT_WRITE, MAP_SHARED, output, 0)) == (void *) -1)
   {
      fprintf(stderr, "Error mapping ouput file: %s\n", pszNew);
      return false;
   }

   memcpy_dup(target, source, filesize);

   munmap(source, filesize);
   munmap(target, filesize);

   close(input);
   close(output);

   return true;

}





CLASS_DECL_c bool file_is_equal_path(const char * psz1, const char * psz2)
{
   if(stricmp_dup(psz1, psz2) == 0)
      return true;
   
   throw " // TODO: it should follow links ";
   
   return false;
   
}


CLASS_DECL_c vsstring file_get_mozilla_firefox_plugin_container_path()
{
   throw " todo ";
   
   return "";

}
