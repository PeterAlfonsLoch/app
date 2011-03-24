#include "StdAfx.h"


int starter_start(const char * pszId);
int run_file(const char * pszFile, int nCmdShow);
int run_uninstall_run(const char * lpCmdLine, int nCmdShow);
int ca2_app_install_run(const char * psz, const char * pszParam1, const char * pszParam2, DWORD & dwStartError, bool bSynch);

void ensure_trace_file();

SPALIB_API int spalib_main(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   ::srand(::GetTickCount());

   ensure_trace_file();

   g_hmutexTrace =  ::CreateMutex(NULL, FALSE, NULL);

   g_hinstance = hInstance;

   if(!g_machineevent.initialize())
   {
      return 5;
   }

   g_iStyle = 0;

   g_bShowPercentage = false;

	UNREFERENCED_PARAMETER(hPrevInstance);
	//UNREFERENCED_PARAMETER(lpCmdLine);
   g_iStart = 0;
   //g_iStyle = 0;

   std::string str = lpCmdLine;

   std::string strExe = file::name(file::module_path().c_str());



   if(str.find(" background ") != std::string::npos
   || str_ends(str.c_str(), " background") || strExe.find(" in background ") != std::string::npos
   || str_ends(strExe.c_str(), " in background"))
   {
      g_bShow = false;
   }




   g_bLoginStartup = false;
   size_t i = str.find("install_filter=");
   if(i != std::string::npos)
   {
      int iStart = i + 15; // 15 = strlen("install_filter=")
      i = str.find(" ", i);
      if(i != std::string::npos)
      {
         g_strInstallFilter = str.substr(iStart, i - iStart);
      }
      else
      {
         g_strInstallFilter = str.substr(iStart);
      }
   }
   //MessageBox(NULL, "xxx", "yyy", MB_OK);
   i = str.find("install=");
   if(i != std::string::npos)
   {
      int iStart = i + 8; // 8 = strlen("install=")
      i = str.find(" ", i);
      if(i != std::string::npos)
      {
         g_strStart = str.substr(iStart, i - iStart);
      }
      else
      {
         g_strStart = str.substr(iStart);
      }
      g_iStart = 4;
      return run_install(lpCmdLine, nCmdShow);
   
   }
   if(str_begins_ci(strExe.c_str(), "Install "))
   {
      int iStart = strlen("Install ");
      i = strExe.find(" ", iStart);
      std::string strIdStart;
      if(i != std::string::npos)
      {
         strIdStart = strExe.substr(iStart, i - iStart);
      }
      else
      {
         strIdStart = strExe.substr(iStart);
      }
      g_iStart = 4;
      return starter_start(strIdStart.c_str());
   }
   std::string strFind("starter_start=");
   i = str.find(strFind);
   if(i != std::string::npos)
   {
      int iStart = i + strFind.length(); // 8 = strlen("install=")
      i = str.find(" ", iStart);
      std::string strIdStart;
      if(i != std::string::npos)
      {
         strIdStart = str.substr(iStart, i - iStart);
      }
      else
      {
         strIdStart = str.substr(iStart);
      }
      g_iStart = 4;
      return starter_start(strIdStart.c_str());
   
   }


   wchar_t * lpwstr = ::GetCommandLineW();
   int numargs;
   int numchars;
   wparse_cmdline(
      lpwstr, 
      NULL, 
      NULL,
      &numargs,
      &numchars);

   wchar_t * pszCmdLine = new WCHAR[numchars];
   wchar_t ** argv = new WCHAR*[numargs];

   wparse_cmdline(
      lpwstr, 
      argv, 
      pszCmdLine,
      &numargs,
      &numchars);

   if(numargs >= 2)
   {
      std::string str(utf16_to_8(argv[1]));
      return run_file(str.c_str(), nCmdShow);
   }


   int iFind;
   if((iFind = str.find("uninstall")) != std::string::npos)
   {
      return run_uninstall_run(&str[iFind + 10], nCmdShow);
   }
   else if(str.find("uninstall") != std::string::npos)
   {
      return run_uninstall(lpCmdLine, nCmdShow);
   }
   else
   {
      //g_strStart = "_set_windesk";  g_iStart = 4; return run_install(lpCmdLine, nCmdShow);
      return run_install(lpCmdLine, nCmdShow);
   }
}


