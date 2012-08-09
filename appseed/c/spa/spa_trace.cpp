#include "framework.h"

//extern HWND g_hwnd;


simple_mutex g_mutexTrace;
stra_dup * g_pstraTrace = NULL;
HANDLE g_ftrace = INVALID_HANDLE_VALUE;
vsstring g_strLastStatus;
vsstring g_strLastGlsStatus;
int g_iLastStatus = 0;
int g_iLastGlsStatus = 0;


void on_trace(vsstring & str, vsstring & str2);




void ensure_trace_file()
{
   dir::mk(dir::ca2());
   if(g_ftrace != INVALID_HANDLE_VALUE)
   {
      // best really determination that g_ftrace is valid, if it is valid, it is not necessary to create or open it
      vsstring str2 = "ensure_trace_file";
      DWORD dwWritten;
      if(WriteFile(g_ftrace, str2, (DWORD) str2.length(), &dwWritten, NULL))
      {
         ::FlushFileBuffers(g_ftrace);
         return;
      }
   }
   g_ftrace = ::CreateFile(dir::ca2("install.log"), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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
   else if(str_begins_ci_dup(psz, ":::::"))
   {
      g_iLastGlsStatus = 0;
      if(g_strLastGlsStatus != psz)
      {
         g_strLastGlsStatus = psz;
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
		if(g_strLastGlsStatus.begins_ci(":::::"))
      {
         g_iLastGlsStatus++;
         if(g_iLastGlsStatus >= 23)
         {
            trace(g_strLastGlsStatus);
         }
      }
   }
   vsstring str;
   {
      mutex_lock lockTrace(&g_mutexTrace, true);
      g_pstraTrace->add(psz);
      str = g_pstraTrace->element_at(g_pstraTrace->get_count() - 1);
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
      if(g_pstraTrace->get_count() == 0)
         g_pstraTrace->add(psz);
      else
         g_pstraTrace->element_at(g_pstraTrace->get_count() - 1) += psz;
      str = g_pstraTrace->element_at(g_pstraTrace->get_count() - 1);
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
      ::SetFilePointer(g_ftrace, 0, NULL, SEEK_END);
      WriteFile(g_ftrace, str2, (DWORD) str2.length(), &dwWritten, NULL);
      ::FlushFileBuffers(g_ftrace);
   }

}



CLASS_DECL_c void trace_progress(double dRate)
{
   if(dRate < 0.0)
      dRate = 1.0;
   if(dRate > 1.0)
      dRate = 1.0;
   dRate = dRate * 1000.0 * 1000.0 * 1000.0;
   //int i = ftol(dRate);
   int i = (int) dRate;
   vsstring str;
   str = "|||";
   str += itoa_dup(i);
   trace(str);
}




CLASS_DECL_c bool initialize_primitive_trace()
{
   
   g_pstraTrace = new stra_dup();

   if(g_pstraTrace == NULL)
      return false;

   return true;

}


CLASS_DECL_c void finalize_primitive_trace()
{

   if(g_pstraTrace != NULL)
   {

      delete g_pstraTrace;

   }

}
