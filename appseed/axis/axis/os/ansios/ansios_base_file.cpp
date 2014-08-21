#include "framework.h"
#include <sys/stat.h>
//Copy file using mmap()
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#define PACKAGE "mmap"

void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str);

int_bool ensure_file_size(int32_t fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return false;

   return true;

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



int_bool file_set_length(const char * pszName, size_t iSize)
{

   int32_t fd = ::open(pszName, O_RDONLY);

   int_bool bSet = ::ensure_file_size(fd, iSize) != -1;

   ::close(fd);

   return bSet;

}




int_bool file_exists_dup(const char * path1)
{

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   struct stat st;

   if(stat(path1, &st))
      return false;

   if((st.st_mode & S_IFDIR))
      return false;

   return true;

}



int_bool file_put_contents_dup(const char * path, const char * contents, ::count len)
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




string file_as_string_dup(const char * path)
{

   string str;


   FILE * f = fopen(path, "rb");

   if(f == NULL)
      return "";

   ::count iSize = fsize_dup(f);

   LPSTR lpsz = str.GetBufferSetLength(iSize);

   ::count iRead = fread(lpsz, iSize, 1, f);

   lpsz[iRead] = '\0';

   str.ReleaseBuffer(iRead);

   fclose(f);

   return str;

}


bool file_get_memory_dup(::primitive::memory_base & memory, const char * path)
{

   FILE * f = fopen(path, "rb");
   if(f == NULL)
      return false;
   memory.allocate(fsize_dup(f));
   fread(memory.get_data(), memory.get_size(), 1, f);
   fclose(f);
   return true;

}







uint64_t file_length_dup(const char * path)
{

   struct stat st;
   stat(path, &st);
   return st.st_size;

}



string file_module_path_dup()
{

   return "/core/stage";

}







int_bool file_ftd_dup(const char * pszDir, const char * pszFile)
{

   FILE * hfile1 = NULL;
   FILE * hfile2 = NULL;
   hfile1 = fopen(pszFile, "rb");
   if(hfile1 == NULL)
      return false;

   string strVersion;


   file_read_ex1_string_dup(hfile1, NULL, strVersion);
   int32_t n;
   string strRelative;
   string strMd5;
   string strMd5New;
   int32_t iBufSize = 1024 * 1024;
   uchar * buf = (uchar *)  memory_alloc(iBufSize);
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
         string strPath = dir::path(pszDir, strRelative);
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
         string strFormat;
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
   string str;
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

void file_read_ex1_string_dup(FILE * hfile, ::md5::md5 * pctx, string & str)
{
   int32_t iLen;
   file_read_n_number_dup(hfile, pctx, iLen);
   LPSTR lpsz = (LPSTR) memory_alloc(iLen + 1);
   ::count dwRead;
   dwRead = fread(lpsz, iLen, 1, (FILE *) hfile);
   if(pctx != NULL)
   {
      pctx->update(lpsz, iLen);
   }
   lpsz[iLen] = '\0';
   str = lpsz;
   memory_free_dbg(lpsz, 0);
}

























int_bool file_copy_dup(const char * pszNew, const char * pszSrc, int_bool bOverwrite)
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
   ftruncate(output, filesize);

   if((source = mmap(0, filesize, PROT_READ, MAP_PRIVATE, input, 0)) == (void *) -1)
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

   msync(target, filesize, MS_SYNC);

   munmap(source, filesize);
   munmap(target, filesize);

    fsync(output);

   close(input);
   close(output);

   return true;

}





int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
{
   if(stricmp_dup(psz1, psz2) == 0)
      return true;

   throw " // TODO: it should follow links ";

   return false;

}


CLASS_DECL_AXIS string file_get_mozilla_firefox_plugin_container_path()
{
   throw " todo ";

   return "";

}



int_bool file_delete_dup(const char * lpszFileName)
{


   if(!::unlink(lpszFileName))
      return FALSE;

   return TRUE;


}



/*

int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   const int32_t iBufSize = MAX_PATH * 8;
   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
   wchar_t * pwszFile1;
   wchar_t * pwszFile2;
   wchar_t * pwszPath1 = new wchar_t[iBufSize];
   wchar_t * pwszPath2 = new wchar_t[iBufSize];
   int32_t iCmp = -1;
   if(GetFullPathNameW(pwsz1,iBufSize,pwszPath1,&pwszFile1))
   {
      if(GetFullPathNameW(pwsz2,iBufSize,pwszPath2,&pwszFile2))
      {
         string p1 = ::str::international::unicode_to_utf8(pwszPath1);
         string p2 = ::str::international::unicode_to_utf8(pwszPath2);
         iCmp = stricmp_dup(p1,p2);
      }
   }
   delete pwszPath1;
   delete pwszPath2;
   return iCmp == 0;

}

*/
