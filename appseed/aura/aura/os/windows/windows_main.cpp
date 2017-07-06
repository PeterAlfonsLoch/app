//#include "framework.h"
//#include "aura/node/windows/windows.h"
//#include "windows.h"

#include <time.h>
#ifdef __MCRTDBG
#include <crtdbg.h>
#endif


CLASS_DECL_AURA int32_t ca2_main();


void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

   throw simple_exception(get_thread_app());

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}




CLASS_DECL_AURA int32_t __win_main(sp(::aura::system) psystem, ::windows::main_init_data * pmaininitdata)
{

   psystem->construct(NULL);

   if (pmaininitdata == NULL)
   {
      psystem->m_hinstance;
   }

   psystem->init_main_data(pmaininitdata);

   xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   set_main_thread(GetCurrentThread());

   set_main_thread_id(GetCurrentThreadId());

   if (!psystem->pre_run())
   {

      return psystem->m_iReturnCode;

   }

   int32_t nReturnCode = psystem->main();

   return nReturnCode;

}


int app_core::start()
{

   if (!defer_aura_init())
   {

      ::OutputDebugString("Failed to defer_core_init");

      return -4;

   }

   m_dwStartTime = ::get_first_tick();
   
   m_dwAfterApplicationFirstRequest = m_dwStartTime;

   if (file_exists_dup("C:\\ca2\\config\\system\\wait_on_beg.txt"))
   {

      Sleep(10000);

   }

   if (file_exists_dup("C:\\ca2\\config\\system\\beg_debug_box.txt"))
   {

      debug_box("zzzAPPzzz app", "zzzAPPzzz app", MB_ICONINFORMATION);

   }

   return 0;

}


int app_core::end()
{

   int iRet = 0;

   if (!defer_aura_term())
   {

      ::OutputDebugString("Failed to defer_core_term");

      iRet -= 10000;

   }

   DWORD dwEnd = ::get_tick_count();

   char szTimeMessage[2048];

   ::time_t timet = ::time(NULL);

   tm t;

   errno_t err = _localtime64_s(&t, &timet);

   char szTime[2048];

   sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

   sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First Application Request Completion %d", (uint32_t)m_dwAfterApplicationFirstRequest - m_dwStartTime);
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   int iMillisecondsTotal = dwEnd - m_dwStartTime;

   sprintf(szTimeMessage, "\n|  Total Elapsed Time %d ms", (uint32_t)iMillisecondsTotal);
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   int iMilliseconds = iMillisecondsTotal % 1000;
   int iSecondsTotal = iMillisecondsTotal / 1000;
   int iSeconds = iSecondsTotal % 60;
   int iMinutesTotal = iSecondsTotal / 60;
   int iMinutes = iMinutesTotal % 60;
   int iHoursTotal = iMinutesTotal / 60;
   int iHours = iHoursTotal % 24;
   int iDays = iHoursTotal / 24;

   if (iDays > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %d days %02d:%02d:%02d %03d ms", iDays, iHours, iMinutes, iSeconds, iMilliseconds);

   }
   else if (iHours > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d:%02d %03d ms", iHours, iMinutes, iSeconds, iMilliseconds);

   }
   else if (iMinutes > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d %03d ms", iMinutes, iSeconds, iMilliseconds);

   }
   else
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02ds %03d ms", iSeconds, iMilliseconds);

   }

   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|  %s", szTime);
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::OutputDebugStringA(szTimeMessage);
   printf(szTimeMessage);


   if (file_exists_raw("C:\\ca2\\config\\system\\show_elapsed.txt"))
   {
      char szUTCTime[2048];
      //      char szLocalTime[2048];
      time_t rawtime;
      struct tm * l;
      struct tm * g;
      time(&rawtime);
      l = localtime(&rawtime);
      g = gmtime(&rawtime);
      sprintf(szUTCTime, "%04d-%02d-%02d %02d:%02d:%02d UTC", g->tm_year + 1900, g->tm_mon, g->tm_mday, g->tm_hour, g->tm_min, g->tm_sec);
      //   sprintf(szLocalTime,"%04d-%02d-%02d %02d:%02d:%02d local : ",l->tm_year + 1900,l->tm_mon,l->tm_mday,l->tm_hour,l->tm_min,l->tm_sec);
      char szTimeMessage1[2048];
      sprintf(szTimeMessage1, " Just After First Application Request Completion %d", (uint32_t)m_dwAfterApplicationFirstRequest - m_dwStartTime);
      if (file_length_raw("C:\\ca2\\config\\system\\show_elapsed.txt") > 0)
      {
         file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", "\n");
      }
      file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", szUTCTime);
      file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", szTimeMessage1);
      //file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt",szLocalTime);
      file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", "\n");
      char szTimeMessage2[2048];
      sprintf(szTimeMessage2, " Total Elapsed Time %d", (uint32_t)dwEnd - m_dwStartTime);
      file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", szUTCTime);
      file_add_contents_raw("C:\\ca2\\config\\system\\show_elapsed.txt", szTimeMessage2);

   }
#ifdef __MCRTDBG
   _CrtDumpMemoryLeaks();
#endif

   return iRet;

}


CLASS_DECL_AURA int node_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   app_core appcore;

   int iError = appcore.start();

   if (iError != 0)
   {

      return iError;

   }

   iError = app_common_main(hinstance, hPrevInstance, (char *)(const char *)  ::str::international::unicode_to_utf8(::GetCommandLineW()), nCmdShow, appcore);

   return appcore.end();

}


CLASS_DECL_AURA int node_main(int argc, char * argv[])
{

   app_core appcore;

   int iError = 0;

   iError = appcore.start();

   if (iError != NOERROR)
   {

      return iError;

   }

   iError = app_common_main(argc, argv, appcore);

   return appcore.end();

}

