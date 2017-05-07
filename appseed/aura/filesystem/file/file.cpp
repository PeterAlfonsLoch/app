//#include "framework.h"
#include <stdio.h>


string file_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.find('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}

string file_final_extension_dup(const char * path)
{

   string str = file_name_dup(path);

   strsize iPos = str.rfind('.');

   if(iPos >= 0)
   {

      return str.Mid(iPos + 1);

   }
   else
   {

      return "";

   }

}





string url_dir_name_for_relative(const char * pszPath)
{
   string strDir(pszPath);

   if(str::ends(strDir,"/"))
      return strDir;

   str::ends_eat(strDir,"/");

   strsize iFind = strDir.reverse_find("/");

   if(iFind < 0)
      return "/";

   return strDir.substr(0,iFind + 1);

}

CLASS_DECL_AURA string solve_relative_compressions(const string & strParam)
{

   bool bDup = false;

   char * psz = (char *) strParam.c_str();

   strsize iLen = strParam.get_length();
   
   //string strAbsolute(strParam);

   strsize iNewPos;

   strsize iaSlash[512];
   int iSlashCount = 0;

   iaSlash[0] = 0;

   strsize iPos = 0;

   if (iLen >= 2)
   {

      if (psz[0] == '\\' && psz[1] == '\\')
      {
         
         iaSlash[0] = 1;

         iPos = 2;

         iSlashCount = 1;

      }

   }

   while (psz[iPos])
   {

      if (psz[iPos] == '/' || psz[iPos] == '\\')
      {
         
         iaSlash[iSlashCount] = iPos;

         iSlashCount++;

         iPos++;

         if (iPos >= iLen)
         {

            // the end of string has been reached

            if (iPos > 2)
            {

               iPos--; // remove trailing slash

            }

            goto ret;

         }

         if (psz[iPos] == '.')
         {

            iPos++;

            if (iPos >= iLen)
            {

               // the end of string has been reached

               if (iSlashCount >= 2)
               {

                  iPos -= 2; // remove the dot and and trailing slash

               }
               else
               {

                  iPos--;// remove the dot 

               }

               goto ret;

            }
            else if (psz[iPos] == '.')
            {

               iPos++;

               if (iPos >= iLen)
               {

                  // the end of string has been reached

                  iPos = iaSlash[MAX(0, iSlashCount - 2)]; // go back to position of previous slash

                  if (iPos > 2)
                  {

                     iPos--; 

                  }

                  goto ret;

               }
               else if (psz[iPos] == '/' || psz[iPos] == '\\')
               {

                  psz = strdup(strParam);

                  bDup = true;

                  iSlashCount-=2;

                  if (iSlashCount <= 0)
                  {

                     iNewPos = iaSlash[0];

                     iSlashCount = 1;

                  }
                  else
                  {

                     iNewPos = iaSlash[iSlashCount];

                  }

                  strcpy(&psz[iNewPos], &psz[iPos]);

                  iLen -= iPos - iNewPos;

                  iPos = iNewPos;

               }
               else
               {

                  iPos += ::str::get_utf8_char_length(psz);

                  if (iPos >= iLen)
                  {

                     iPos = iLen - 1;

                     goto ret;

                  }

               }

            }
            else if (psz[iPos] == '/' || psz[iPos] == '\\')
            {

               psz = strdup(strParam);

               bDup = true;

               iSlashCount--;

               if (iSlashCount <= 0)
               {

                  iNewPos = iaSlash[0];

                  iSlashCount = 1;

               }
               else
               {

                  iNewPos = iaSlash[iSlashCount];

               }

               strcpy(&psz[iNewPos], &psz[iPos]);

               iLen -= iPos - iNewPos;

               iPos = iNewPos;

            }
            else
            {

               iPos += ::str::get_utf8_char_length(psz);

               if (iPos >= iLen)
               {

                  goto ret;

               }

            }

         }
         else if (psz[iPos] == '/' || psz[iPos] == '\\')
         {

            iaSlash[iSlashCount] = iPos;

            iSlashCount++;

            iPos++;

            if (iPos >= iLen)
            {

               // the end of string has been reached

               goto ret;

            }

         }
         else
         {

            iPos += ::str::get_utf8_char_length(psz);

            if (iPos >= iLen)
            {

               goto ret;

            }

         }

      }
      else
      {

         iPos += ::str::get_utf8_char_length(psz);

         if (iPos >= iLen)
         {

            goto ret;

         }

      }

   }

ret:

   if (bDup)
   {

      string str(psz, iPos + 1);

      free(psz);

      return str;

   }
   else if (iPos < iLen)
   {

      string str(psz, iPos);

      return str;

   }
   else
   {

      return strParam;

   }

   //retu

   //strAbsolute.replace("/./","/");

   //strsize iFind;
   //strsize iFind2;

   //while((iFind = strAbsolute.find("/../")) >= 0)
   //{
   //   if (iFind == 0)
   //   {
   //      strAbsolute = strAbsolute.substr(iFind + 3);
   //   }
   //   else
   //   {
   //      iFind2 = strAbsolute.reverse_find("/", iFind - 1);
   //      if (iFind2 <= 0)
   //      {
   //         strAbsolute = strAbsolute.substr(iFind + 3);
   //      }
   //      else
   //      {
   //         strAbsolute = strAbsolute.substr(0, iFind2) + strAbsolute.substr(iFind + 3);
   //      }
   //   }
   //}

   //strAbsolute.replace("\\.\\","\\");

   //while((iFind = strAbsolute.find("\\..\\")) >= 0)
   //{
   //   if (iFind == 0)
   //   {
   //      strAbsolute = strAbsolute.substr(iFind + 3);
   //   }
   //   else
   //   {
   //      iFind2 = strAbsolute.reverse_find("\\", iFind - 1);
   //      if (iFind2 <= 0)
   //      {
   //         strAbsolute = strAbsolute.substr(iFind + 3);
   //      }
   //      else
   //      {
   //         strAbsolute = strAbsolute.substr(0, iFind2) + strAbsolute.substr(iFind + 3);
   //      }
   //   }
   //}

   //if(::str::ends_eat(strAbsolute, "\\.."))
   //{
   //   iFind2 = strAbsolute.reverse_find("\\");
   //   if(iFind2>= 0)
   //   {
   //      strAbsolute = strAbsolute.substr(0,iFind2);
   //   }
   //}

   //::str::ends_eat(strAbsolute,"\\.");


   //return strAbsolute;
}

CLASS_DECL_AURA string defer_solve_relative_name(const char * pszRelative,const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if(strRelative.is_empty())
      return "";
   if(strAbsolute.is_empty())
      return solve_relative_compressions(strRelative);
   if(str::begins_ci(strRelative,"http://"))
      return solve_relative_compressions(strRelative);
   if(str::begins_ci(strRelative,"https://"))
      return solve_relative_compressions(strRelative);
   if(str::begins_ci(strRelative,"ftp://"))
      return solve_relative_compressions(strRelative);
   if(str::begins_ci(strRelative,"ext://"))
      return solve_relative_compressions(strRelative);
   if(str::begins(strRelative,"/"))
      return solve_relative_compressions(strRelative);
   if(str::begins(strRelative,"\\\\"))
      return solve_relative_compressions(strRelative);

   index iFind = strRelative.find(":\\");

   if(iFind >= 0)
   {
      index i = 0;
      for(; i < iFind; i++)
      {
         if(!isalpha_dup(strRelative[i]) && !isdigit_dup(strRelative[i]))
            break;
      }

      if(i == iFind)
         return solve_relative_compressions(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if(!str::ends(strAbsolute,"/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return solve_relative_compressions(strRelative);

}




#ifdef WINDOWSEX

//CLASS_DECL_AURA bool read_resource_as_file_dup(const char * pszFile,HINSTANCE hinst,UINT nID,LPCTSTR lpcszType);



string get_temp_file_name_dup(const char * pszName,const char * pszExtension)
{
   char lpPathBuffer[MAX_PATH * 16];
   // Get the temp path.
   DWORD dwRetVal = GetTempPath(sizeof(lpPathBuffer),     // length of the buffer
      lpPathBuffer); // buffer for path
   if(dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {
      debug_print("GetTempPath failed (%d)\n",GetLastError());
      return "";
   }
   string str;
   char buf[30];
   size_t iLen= strlen(lpPathBuffer);
   if(!(lpPathBuffer[iLen - 1] == '/'
      || lpPathBuffer[iLen - 1] == '\\'))
   {
      lpPathBuffer[iLen] = '\\';
      lpPathBuffer[iLen + 1] = '\0';
   }
   for(int i = 0; i < 1000; i++)
   {
      sprintf(buf,"%d",i);
      str = lpPathBuffer;
      str += pszName;
      str += "\\";
      str += buf;
      str += "\\";
      str += pszName;
      str += ".";
      str += pszExtension;
      if(file_exists_dup(str.c_str()))
      {
         if(::DeleteFileA(str.c_str()))
            return str;
      }
      else
      {
         return str;
      }
   }
   return "";
}


bool write_memory_to_file(HANDLE hFile,const void * lpBuf,memory_size_t nCount,memory_size_t * puiWritten)
{

#if OSBIT > 32

   memory_position_t pos = 0;

   DWORD dw= 0;

   DWORD dwWrite;

   memory_size_t uiWrittenTotal = 0;

   while(pos < nCount)
   {

      dwWrite = (DWORD)MIN(nCount - uiWrittenTotal,0xffffffffu);

      if(!::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),&((byte *)lpBuf)[pos],dwWrite,&dw,NULL))
      {

         uiWrittenTotal += dw;

         if(puiWritten != NULL)
         {

            *puiWritten = uiWrittenTotal;

         }

         return false;

      }

      uiWrittenTotal += dw;

      if(dw != dwWrite)
         break;

      pos += dw;

   }

   if(puiWritten != NULL)
   {

      *puiWritten = uiWrittenTotal;

   }

   return uiWrittenTotal == nCount;

#else

   DWORD dw= 0;

   BOOL bOk = ::WriteFile(GetStdHandle(STD_OUTPUT_HANDLE),lpBuf,nCount,&dw,NULL);

   if(puiWritten != NULL)
   {

      *puiWritten = dw;

   }

   return bOk && dw == nCount;

#endif

}

#endif


CLASS_DECL_AURA bool file_append_wait_dup(const string & strFile, const char * psz, strsize s, DWORD dwTimeout)
{

   ::dir::mk(::dir::name(strFile));

   if (!::dir::is(::dir::name(strFile)))
   {

      return false;

   }

   wstring wstr(strFile);

   FILE * pfile = NULL;

   DWORD dwStart = get_tick_count();



   while (true)
   {

#if defined(__APPLE__) || defined(LINUX) || defined(VSNORD)
      pfile = fopen(strFile, "ab");
#else
      pfile = _wfopen(wstr, L"ab");
#endif

      if (pfile != NULL)
      {

         break;

      }

      if (get_tick_count() - dwStart > dwTimeout)
      {

         return false;

      }

      Sleep(5);

   }

   fwrite(psz, s, 1, pfile);

   fclose(pfile);

   return true;

}



bool file_append_wait_dup(const string & strFile, const string & str, DWORD dwTimeout)
{

   return file_append_wait_dup(strFile, str, str.get_length(), dwTimeout);

}

CLASS_DECL_AURA bool file_append_dup(const string & strFile, const char * psz, strsize s)
{

   return file_append_wait_dup(strFile, psz, s, 0);

}

bool file_append_dup(const string & strFile, const string & str)
{

   return file_append_dup(strFile, str, str.get_length());

}
