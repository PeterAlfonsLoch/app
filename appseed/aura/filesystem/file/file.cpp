//#include "framework.h"


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

string defer_solve_relative_compresions(const char * pszAbsolute)
{
   string strAbsolute(pszAbsolute);

   strAbsolute.replace("/./","/");

   strsize iFind;
   strsize iFind2;

   while((iFind = strAbsolute.find("/../")) >= 0)
   {
      iFind2 = strAbsolute.reverse_find("/",iFind - 1);
      if(iFind2 <= 0)
      {
         strAbsolute = strAbsolute.substr(iFind + 3);
      }
      else
      {
         strAbsolute = strAbsolute.substr(0,iFind2) + strAbsolute.substr(iFind + 3);
      }
   }

   strAbsolute.replace("\\.\\","\\");

   while((iFind = strAbsolute.find("\\..\\")) >= 0)
   {
      iFind2 = strAbsolute.reverse_find("\\",iFind - 1);
      if(iFind2 <= 0)
      {
         strAbsolute = strAbsolute.substr(iFind + 3);
      }
      else
      {
         strAbsolute = strAbsolute.substr(0,iFind2) + strAbsolute.substr(iFind + 3);
      }
   }

   return strAbsolute;
}

string defer_solve_relative_name(const char * pszRelative,const char * pszAbsolute)
{
   string strRelative(pszRelative);
   string strAbsolute(pszAbsolute);
   if(strRelative.is_empty())
      return "";
   if(strAbsolute.is_empty())
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"http://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"https://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"ftp://"))
      return defer_solve_relative_compresions(strRelative);
   if(str::begins_ci(strRelative,"ext://"))
      return defer_solve_relative_compresions(strRelative);

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
         return defer_solve_relative_compresions(strRelative);

   }

   strAbsolute = ::url_dir_name_for_relative(strAbsolute);

   if(!str::ends(strAbsolute,"/"))
      strAbsolute += "/";
   strRelative = strAbsolute + strRelative;


   return defer_solve_relative_compresions(strRelative);

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
      str += "-";
      str += buf;
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





