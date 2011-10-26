#include "StdAfx.h"

//extern HWND g_hwnd;


simple_mutex g_mutexTrace;
stra_dup g_straTrace;
HANDLE g_ftrace = NULL;
vsstring g_strLastStatus;
int g_iLastStatus = 0;


void on_trace(vsstring & str, vsstring & str2);




void ensure_trace_file()
{
   dir::mk(dir::ca2());
   g_ftrace = ::CreateFile(dir::ca2("install.log"), GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
   ::SetFilePointer(g_ftrace, 0, NULL, FILE_END);
}


void trace(const char * psz)
{
   if(str_begins_ci_dup(psz, "***"))
   {
      g_iLastStatus = 0;
      if(g_strLastStatus != psz)
      {
         g_strLastStatus = psz;
      }
   }
   else
   {
		if(g_strLastStatus.begins_ci("***"))
      {
         g_iLastStatus++;
         if(g_iLastStatus >= 23)
         {
            trace(g_strLastStatus);
         }
      }
   }
   vsstring str;
   {
      mutex_lock lockTrace(&g_mutexTrace, true);
      g_straTrace.add(psz);
      str = g_straTrace[g_straTrace.get_count() - 1];
   }
   vsstring str2(str);
   str2 = "\r\n" + str2;
   on_trace(str, str2);
}

void trace_add(const char * psz)
{
   vsstring str;
   {
      mutex_lock lockTrace(&g_mutexTrace, true);
      if(g_straTrace.get_count() == 0)
         g_straTrace.add(psz);
      else
         g_straTrace[g_straTrace.get_count() - 1] += psz;
      str = g_straTrace[g_straTrace.get_count() - 1];
   }
   vsstring str2(psz);
   on_trace(str, str2);
}

bool isspace_dup(char ch)
{
   if(ch=='\t')
      return true;
   if(ch==' ')
      return true;
   if(ch=='\r')
      return true;
   if(ch=='\n')
      return true;
   return false;
}

void on_trace(vsstring & str, vsstring & str2)
{
/*   if(::IsWindowVisible(g_hwnd))
   {
      if(str.length() > 3 && str.substr(0, 3) == "***")
      {
         SetWindowText(g_hwnd, str.substr(3));
      }
      else if(str.length() > 0 && str.substr(0, 1) != ".")
      {
         SetWindowText(g_hwnd, str);
      }
   }*/
   if(g_ftrace != NULL && str2.length() > 0)
   {
      DWORD dwWritten;
      WriteFile(g_ftrace, str2, str2.length(), &dwWritten, NULL);
      ::FlushFileBuffers(g_ftrace);
   }

}



CLASS_DECL_____ void trace_progress(double dRate)
{
   if(dRate < 0.0)
      dRate = 1.0;
   if(dRate > 1.0)
      dRate = 1.0;
   dRate = dRate * 1000.0 * 1000.0 * 1000.0;
   int i = ftol(dRate);
   vsstring str;
   str = "|||";
   str += itoa_dup(i);
   trace(str);
}
