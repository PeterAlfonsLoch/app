#include "StdAfx.h"
#include <lm.h>
#include <WtsApi32.h>
#include <Ntsecapi.h>

#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Secur32.lib") 

namespace whiteboard
{

   util::util()
   {
   }

   bool util::get_current_user_logon_time(whiteboard::time & time)
   {
      ULONG ulLogonSessionCount = 0;
      PLUID pluid = NULL;
      NTSTATUS st = LsaEnumerateLogonSessions(
         &ulLogonSessionCount,
         &pluid);

      bool bSuccess = false;
      if(st == ERROR_SUCCESS
         && ulLogonSessionCount > 0)
      {
         PSECURITY_LOGON_SESSION_DATA pdata;
         if(LsaGetLogonSessionData(pluid,  &pdata)
            == 0)
         {
            bSuccess = true;
         }
         time.SetTime((__time64_t) pdata->LogonTime.QuadPart);
         LsaFreeReturnBuffer(pdata);
      }
      if(pluid != NULL)
         LsaFreeReturnBuffer(pluid);
      return bSuccess;
/*      USER_INFO_11 * lpui11;
      string wstrUserName;
      wchar_t * lpwszComputerName;
      get_current_session_current_user_name(wstrUserName);
//      NetGetDCName( NULL, L"WW101", (LPBYTE*) &lpwszComputerName );
      wstrUserName = L"WW101\\" + wstrUserName;
      NET_API_STATUS status =
         NetUserGetInfo(L"\\\\CUR3W105\\", wstrUserName, 11, (LPBYTE *) &lpui11);
      if(status != NERR_Success)
         return false;
      time.SetTime((__time64_t) lpui11->usri11_last_logon);
      NetApiBufferFree(lpui11);
      return true;*/
   }

   bool util::get_current_session_current_user_name(string & wstrUserName)
   {
      wchar_t * lpszUserName;
      DWORD dw;
      if(!WTSQuerySessionInformationW(
         WTS_CURRENT_SERVER_HANDLE,
         WTS_CURRENT_SESSION,
         WTSUserName,
         &lpszUserName,
         &dw))
         return false;
      string str;
      wstrUserName = lpszUserName;
      WTSFreeMemory(lpszUserName);
      return true;
   }

   void util::get_month_text(string & str, int iMonth)
   {
      if(iMonth < 0 || iMonth >= 12)
      {
//         ASSERT(FALSE);
         str.Empty();
         return;
      }
      char * lpszaMonth[] =
      {
         "Janeiro",
         "Fevereiro",
         "Março",
         "Abril",
         "Maio",
         "Junho",
         "Julho",
         "Agosto",
         "Setembro",
         "Outubro",
         "Novembro",
         "Dezembro",
      };
      str = lpszaMonth[iMonth];
   }

   void util::get_month_abbr_text(string & str, int iMonth)
   {
      if(iMonth < 0 || iMonth >= 12)
      {
         ASSERT(FALSE);
         str.Empty();
         return;
      }
      char * lpszaMonth[] =
      {
         "Jan",
         "Fev",
         "Mar",
         "Abr",
         "Mai",
         "Jun",
         "Jul",
         "Ago",
         "Set",
         "Out",
         "Nov",
         "Dez",
      };
      str = lpszaMonth[iMonth];
   }


   void util::strip_file_extension(string & str)
   {
      int iDot = str.reverse_find('.');
      int iSlash = str.reverse_find('/');
      int iBackSlash = str.reverse_find('\\');
      int iDotMax = -1;
      if((iSlash >= 0 && iDot > iSlash && iBackSlash < iSlash)
      || (iBackSlash >= 0 && iDot > iBackSlash && iSlash < iBackSlash))
      {
         str = str.Left(iDot);
      }
   }

} // namespace whiteboard