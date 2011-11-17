#include "StdAfx.h"


#ifdef _WINDOWS
#include <WinInet.h>
#include <Winternl.h>
#endif

#ifdef MACOS
#include <sys/param.h>
#include <mach-o/dyld.h>
#endif


extern TCHAR szTitle[1024];					// The title bar text
extern TCHAR szWindowClassSpaAdmin[1024];			// the main window class name

void ensure_trace_file();

bool g_bInstalling = false;

typedef PVOID * PPVOID;

#ifdef _WINDOWS

typedef int (* CA2MAIN)(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int nCmdShow);

typedef struct _PROCESS_BASIC_INFORMATION64 {
    uint64_t  Reserved1;
    uint64_t  PebBaseAddress;
    uint64_t  Reserved2[2];
    uint64_t  UniqueProcessId;
    uint64_t  Reserved3;
} PROCESS_BASIC_INFORMATION64;

typedef NTSTATUS (NTAPI *_NtQueryInformationProcess)(HANDLE ProcessHandle, DWORD ProcessInformationClass, PVOID ProcessInformation, DWORD ProcessInformationLength, PDWORD ReturnLength);


vsstring get_display_error(DWORD NTStatusMessage);

PPEB GetPebAddress(HANDLE handleProcess)
{
   _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
   PROCESS_BASIC_INFORMATION pbi;
   memset_dup(&pbi, 0, sizeof(pbi));
   DWORD dwInLen = sizeof(pbi);
   DWORD dwOutLen = 0xffffffff;
   DWORD dwStatus = NtQueryInformationProcess(handleProcess, ProcessBasicInformation, &pbi, dwInLen, &dwOutLen);
   vsstring strError = get_display_error(dwStatus);
   if((dwStatus & 3) == 3)
   {
      return NULL;
   }
   return pbi.PebBaseAddress;
}


vsstring get_display_error(DWORD NTStatusMessage)
{
   LPVOID lpMessageBuffer;
   HMODULE Hand = LoadLibrary("NTDLL.DLL");

   FormatMessage(
       FORMAT_MESSAGE_ALLOCATE_BUFFER |
       FORMAT_MESSAGE_FROM_SYSTEM |
       FORMAT_MESSAGE_FROM_HMODULE,
       Hand,
       NTStatusMessage,
       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
       (LPTSTR) &lpMessageBuffer,
       0,
       NULL );

   // Now display the string.

   vsstring str = (LPTSTR) lpMessageBuffer;

   // Free the buffer allocated by the system.
   LocalFree( lpMessageBuffer );
   FreeLibrary(Hand);
   return str;
}


vsstring get_command_line(HANDLE handleProcess)
{

   PPEB ppeb = GetPebAddress(handleProcess);

   PRTL_USER_PROCESS_PARAMETERS pparam1 = NULL;

   if(!ReadProcessMemory(handleProcess, (PCHAR)&ppeb->ProcessParameters, &pparam1, sizeof(PRTL_USER_PROCESS_PARAMETERS), NULL) || pparam1 == NULL)
   {
      ::OutputDebugStringA("Could not read the address of ProcessParameters!\n");
      return "";
   }


   _UNICODE_STRING ustrCommandLine;

   if(!ReadProcessMemory(handleProcess, (PCHAR)&pparam1->CommandLine, &ustrCommandLine, sizeof(ustrCommandLine), NULL))
   {
      ::OutputDebugStringA("Could not read CommandLine!\n");
      return "";
   }

   /* allocate memory to hold the command line */
   WCHAR * commandLineContents = (WCHAR *)ca2_alloc(ustrCommandLine.Length + sizeof(WCHAR));
   /* read the command line */
   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, NULL))
   {
      ::OutputDebugStringA("Could not read the command line string!\n");
      return "";
   }
   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
   vsstring str = utf16_to_8(commandLineContents);
   ca2_free(commandLineContents);
   return str;
}
#else // _WINDOWS

   typedef int (* CA2MAIN)(const char * lpCmdLine, int nCmdShow);

#endif // !_WINDOWS


int run_file(const char * pszFile, int nCmdShow);

HANDLE g_hmutexInstall = NULL;

stra_dup g_straTerminateProcesses;
stra_dup g_straRestartCommandLine;
stra_dup g_straRestartProcess;
vsstring g_strLastHost;
vsstring g_strCurrentHost;
bool g_bStarterStart = false;
#ifdef _WINDOWS
MSG g_msg;
#endif
vsstring g_strPlatform = "";


namespace spa
{



   installer::installer()
   {
      m_bMsDownload = false;
      m_dAnime = 0.0;
      g_bInstalling = false;
      m_pwindow = NULL;
      m_bStarterStart      = false;
      m_dProgressStart     = 0.0;
      m_dProgressEnd       = 0.0;
      m_bInstallSet = false;
      m_bOfflineInstall = false;
      m_bInternetInstall = true;
      m_dProgress = -1.0;
      m_dProgress1 = -1.0;
      m_dProgress2 = -1.0;
      m_bShow = true;
      m_hwnd = NULL;
      m_bForceUpdatedBuild = false;
   }


   installer::~installer()
   {
   }

   void installer::new_progress_end(double dMilestone)
   {
      m_dProgressStart = m_dProgressEnd;
      m_dProgressEnd = dMilestone;
      set_progress(0.0);
   }


   DWORD installer::run()
   {
      
      installation_lock_file_lock installationlockfilelock;


      new_progress_end(0.1);
         g_hmutexInstall = NULL;
         //SECURITY_ATTRIBUTES MutexAttributes;
         //ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
         //MutexAttributes.nLength = sizeof( MutexAttributes );
         //MutexAttributes.bInheritHandle = FALSE; // object uninheritable
         // declare and initialize a security descriptor
         //SECURITY_DESCRIPTOR SD;
   /*      BOOL bInitOk = InitializeSecurityDescriptor(
                           &SD,
                           SECURITY_DESCRIPTOR_REVISION );
         if ( bInitOk )
         {
            // give the security descriptor a Null Dacl
            // done using the  "TRUE, (PACL)NULL" here
            BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                                  TRUE,
                                                  (PACL)NULL,
                                                  FALSE );
            if ( bSetOk )
            {
               // Make the security attributes point
               // to the security descriptor
               MutexAttributes.lpSecurityDescriptor = &SD;*/
               //g_hmutexInstall = ::CreateMutex(&MutexAttributes, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
               /*g_hmutexInstall = ::CreateMutex(NULL, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
               if(::GetLastError() == ERROR_ALREADY_EXISTS)
               {
                  trace("another instance of spa is already running");
                  exit(-202);
                  return -202;
               }*/
           /* }
            else
            {
               trace("error when trying to analyze if another instance of spa is already running");
               exit(-200);
               return -200;
            }
         }
         else
         {
            trace("error when trying to analyze if another instance of spa is already running");
            exit(-201);
            return -201;
         }*/

         Sleep(584);
         if(g_bInstalling)
            return -1;

         //::MessageBox(g_hwnd, "Start", "Start", MB_OK);
         keep_true keeptrueInstalling(g_bInstalling);
         m_dwInstallStartTime = ::GetTickCount();

#if CA2_PLATFORM_VERSION == CA2_BASIS
         m_strSpaIgnitionBaseUrl = "http://basis.spaignition.api.veriterse.net";
#else
         m_strSpaIgnitionBaseUrl = "http://stage.spaignition.api.veriterse.net";
#endif


   install_begin:;
      {
         m_strSpa.remove_all();
         m_iTotalGzLen = 0;
         m_NeedRestartBecauseOfReservedFile = false;
         m_NeedRestartFatalError = false;
         int iFileError = 0;

         int iRet = application_name();
         if(iRet < 0)
            return iRet;

         set_progress(0.1);

         int iRetry = 0;
         iRet = ca2_build_version();
         if(iRet < 0)
            return iRet;

         set_progress(0.2);

         int iHostRetry = 0;
   RetryHost:
         vsstring strSpaHost;
         iRet= calc_host(strSpaHost, iHostRetry);
         if(iRet < 0)
            return iRet;
         g_strCurrentHost = strSpaHost;
         trace(("got server: " + strSpaHost));
         m_strInstall = "http://" + strSpaHost + "/stage/";
         m_strInstallGz = m_strInstall;
         trace(strSpaHost);

         set_progress(0.3);

#ifdef _WINDOWS
         vsstring path;
         path.alloc(1024 * 4);
         ::GetModuleFileNameA(NULL, (char *) (const char *) path, 1024 * 4);
#endif
         int iRetryDeleteSpa = 0;
         vsstring strFile;

         vsstring strUrl;

#ifdef _WINDOWS
         HKEY hkey;


         strUrl = m_strSpaIgnitionBaseUrl + "/install_filter_list";
         vsstring strInstallFilterList = ms_get_dup(strUrl);
         XNode nodeInstallFilter;
         nodeInstallFilter.Load(strInstallFilterList);
         strUrl = m_strSpaIgnitionBaseUrl + "query?node=install_application&id=";
         strUrl += m_strStart;
         strUrl += "&key=install_filter";
         vsstring strInstallFilter = ms_get_dup(strUrl);
         for(int ui = 0; ui < nodeInstallFilter.childs.get_count(); ui++)
         {
            LPXNode lpchild = nodeInstallFilter.childs[ui];
            vsstring strId;
            strId = lpchild->GetAttrValue("id");
            vsstring strFilter;
            strFilter = "|" + strId + "|"; // ex. "|multimedia|"
            if(strInstallFilter.find(strFilter) != vsstring::npos)
            {
               vsstring strKey;
               strKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\ca2_fontopus_votagus_" + strId;

               if(::RegCreateKey(HKEY_LOCAL_MACHINE,
                  strKey,
                  &hkey) == ERROR_SUCCESS)
               {
                  ::RegSetValueEx(
                     hkey,
                     "DisplayIcon",
                     0,
                     REG_SZ,
                     (const BYTE *) (const char *) strFile,
                     strFile.length());
                  vsstring strDisplayName;
                  strDisplayName = "ca2 fontopus votagus - ";
                  strKey = "install_filter_title_" + strId;
                  strDisplayName += load_string(strKey, strId);
                  ::RegSetValueEx(
                     hkey,
                     "DisplayName",
                     0,
                     REG_SZ,
                     (const BYTE *) (const char *) strDisplayName,
                     strDisplayName.length());
                  ::RegSetValueEx(
                     hkey,
                     "UninstallString",
                     0,
                     REG_SZ,
                     (const BYTE *) (const char *) strInstallFilter,
                     strInstallFilter.length());
                  ::RegSetValueEx(
                     hkey,
                     "ModifyString",
                     0,
                     REG_SZ,
                     (const BYTE *) (const char *) strInstallFilter,
                     strInstallFilter.length());
               }
            }
         }

#endif // _WINDOWS

         set_progress(0.4);

         stra_dup straFileList;
         simple_string_to_intptr mapLen;
         simple_string_to_string mapMd5;
         simple_string_to_intptr mapGzLen;



         XNode nodeInstall;

         nodeInstall.Load(file_get_contents_dup(dir::appdata("spa_install.xml")));

         LPXNode lpnodeInstalled = nodeInstall.GetChild("installed");



         trace("***Downloading file list.");

         vsstring strBuild;
         strBuild = str_replace_dup(m_strBuild, " ", "_");
         strBuild = str_replace_dup(strBuild, ":", "-");
         vsstring strIndexPath;
         if(!ca2_fy_url(strIndexPath, ("app/stage/metastage/index-"+strBuild+".spa.bz"), false, -1, NULL, -1, true))
         {
            trace("Failed to download file list!");
            trace("Going to retry host...");
            Sleep(584);
            goto RetryHost;
         }
         strUrl = "http://" + strSpaHost + "/stage/app/stage/metastage/index-"+strBuild+".md5";
         vsstring strCgclIndexMd5 = ms_get_dup(strUrl, false);
         if(strCgclIndexMd5.length() != 32
         || stricmp_dup(get_file_md5(strIndexPath), strCgclIndexMd5) != 0)
         {
            trace("Invalid file list!");
            trace("Going to retry host...");
            Sleep(584);
            goto RetryHost;
         }
         else
         {
            Sleep(584);
         }
         set_progress(0.5);
         ParseIndexFile(strIndexPath, mapLen, mapMd5, mapGzLen);

         set_progress(0.6);

         if(!GetFileList(straFileList, ("app/stage/metastage/" + m_strStart + ".spa"), mapLen, mapGzLen, mapMd5))
         {
               trace("Failed to download file list!");
               trace("Going to retry host...");
               Sleep(584);
               goto RetryHost;
         }

         set_progress(0.7);

        for(int i = 0; i < straFileList.get_count(); i++)
        {
           const char * psz = straFileList[i];
           ::OutputDebugStringA(psz);
           ::OutputDebugStringA("\r\n");
        }

         if(lpnodeInstalled != NULL)
         {
            for(int ui = 0; ui < lpnodeInstalled->childs.get_count(); ui++)
            {
               vsstring strId = lpnodeInstalled->childs[ui]->GetAttrValue("id");
               if(strcmp_dup(strId, m_strStart) != 0)
               {
                  GetFileList(straFileList, ("app/stage/metastage/" + strId + ".spa"), mapLen, mapGzLen, mapMd5);
               }
            }
         }
        vsstring strStart;
        XNode nodeSpaStart;
        nodeSpaStart.Load(file_get_contents_dup(dir::appdata("spa_start.xml")));
        for(int ui = 0; ui < nodeSpaStart.childs.get_count(); ui++)
        {
	        strStart = nodeSpaStart.childs[ui]->GetAttrValue("id");
	        bool bGet = true;
           if(lpnodeInstalled != NULL)
           {
              for(int ui = 0; ui < lpnodeInstalled->childs.get_count(); ui++)
              {
                 vsstring strId = lpnodeInstalled->childs[ui]->GetAttrValue("id");
                 if(strId == strStart)
                 {
                    bGet = false;
                 }
              }
           }

           if(bGet && m_strStart == strStart)
           {
               bGet = false;
           }
		      if(bGet)
		      {
			      vsstring strGet;
			      strGet = "app/stage/metastage/";
			      strGet += strStart;
			      strGet += ".spa";
			      GetFileList(straFileList, strGet, mapLen, mapGzLen, mapMd5);
		      }
            }

                 set_progress(0.9);


        for(int i = 0; i < straFileList.get_count(); i++)
        {
           ::OutputDebugStringA(straFileList[i]);
           ::OutputDebugStringA("\r\n");
        }

        new_progress_end(0.5);
         trace("***Downloading files.");
         if(m_bInternetInstall)
         {
            download_file_list(straFileList, mapLen, mapMd5, mapGzLen);
         }
         else
         {
            UncompressFileList(straFileList, mapMd5);
         }


         /*iRetry = 0;
         while(is_there_application_opened())
         {
            machine_signalize_close_application();
            if(iRetry == 0)
            {
               trace("***Suggesting ca2 applications to close...");
               trace("Installation will continue after ca2 applications have been closed.");
               trace("You may force closing them by yourself if they do not accept suggestion.");
               trace("Waiting for applications to close...");
               trace(".");
            }
            trace(".");
            iRetry++;
            Sleep(1984);
         }*/


         /*if(stra_dup.size() > 0)
         {
            vsstring strUrl;
            strUrl = stra_dup[0];
            vsstring strStage;

            strStage = dir::path(dir::stage(), "ca2\\stage\\ca2\\fontopus\\app\\main\\front\\Release\\bergedgeapp.exe");
            vsstring strParam;
            strParam = "start=" + file_name_dup(strUrl);
            int i = (int) ::ShellExecute(g_hwnd, "open", strStage, strParam, dir::name(strStage), SW_SHOWNORMAL);
            if(i >= 32)
            {
               ::PostMessage(g_hwnd, WM_CLOSE, 0, 0);
            }
         }*/

         set_ca2_updated(m_strBuild);


         simple_uint_array dwa;

   #ifdef _X86_
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x86\\c.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x86\\ca.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x86\\ca2.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x86\\npca2.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x86\\iexca2.dll"));
   #else
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x64\\c.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x64\\ca.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x64\\ca2.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x64\\npca2.dll"));
         dll_processes(dwa, g_straTerminateProcesses, dir::ca2("stage\\x64\\iexca2.dll"));
   #endif
         // TODO: simular virtualmente a cópia dos arquivos também, se tiver aquivo travado, também retornar


#ifdef _WINDOWS

         g_straRestartCommandLine.remove_all();
         g_straRestartProcess.remove_all();

         if(g_straTerminateProcesses.get_count() > 0)
         {
            if(!m_bStarterStart)
                  return 0;
            vsstring strCommand;
            bool bAsk;
            bool bRestart;
            for(int i = 0; i < g_straTerminateProcesses.get_count(); i++)
            {
               if(i >= 1)
               {
                  strCommand += ";";
               }
               bAsk = true;
               bRestart = true;
               vsstring strPath = g_straTerminateProcesses.element_at(i);
               if(str_ends_ci_dup(strPath, "\\installer.exe") && stristr_dup(strPath, "\\ca2\\") != NULL)
               {
                  bAsk = false;
                  bRestart = false;
               }
               else if(str_ends_ci_dup(strPath, ".exe")  && stristr_dup(strPath, "\\installer") != NULL)
               {
                  bAsk = false;
                  bRestart = false;
               }
               else if(file_is_equal_path(strPath, file_get_mozilla_firefox_plugin_container_path()))
               {
                  bAsk = false;
               }
               vsstring str;
               str = "Should ca2 Terminate and try to restart process \"";
               str += strPath;
               str += "\"?";
               strCommand += str;
               if(!bAsk || ::MessageBox(NULL, str, "need to terminate process to install", MB_ICONEXCLAMATION | MB_YESNO) == IDYES)
               {
                  HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE | PROCESS_VM_READ, FALSE, dwa[i]);
                  if(hProcess == NULL)
                  {
                     ::CloseHandle(hProcess);
                     str = "Failed to open process for termination - ";
                     str += g_straTerminateProcesses.element_at(i);
                     str += ".";
                     ::MessageBox(NULL, "Failed to open process for termination", str, MB_OK);

                     return -1;
                  }

                  if(bRestart)
                  {
                     g_straRestartCommandLine.add(get_command_line(hProcess));
                     g_straRestartProcess.add(g_straTerminateProcesses.element_at(i));
                  }

                  TerminateProcess(hProcess, -1);

                  int iRetry = 49;
                  DWORD dwExitCode = (DWORD) -1;
                  while(::GetExitCodeProcess(hProcess, &dwExitCode) && dwExitCode == STILL_ACTIVE && iRetry > 0)
                  {
                     Sleep(584);
                     iRetry--;
                  }
                  if(iRetry <= 0)
                  {
                     ::CloseHandle(hProcess);
                     str = "Timeout while waiting for process - ";
                     str += g_straTerminateProcesses.element_at(i);
                     str += " - to exit.";
                     ::MessageBox(NULL, "Failed to open process for termination", str, MB_OK);
                     return -1;
                  }
                  ::CloseHandle(hProcess);
               }
               else
               {
                  return -1;
               }

            }
            //file_put_contents_dup("C:\\ca2\\machine\\on_after_spaadmin.txt", strCommand);
         }

         if(g_straRestartCommandLine.get_count() > 0)
         {

            HWND hwndSpaBoot = ::FindWindow(NULL, "ca2::fontopus::ccvotagus::spaboot:callback_window");

            if(hwndSpaBoot != NULL)
            {
               vsstring str = g_straRestartCommandLine.encode_v16();
               COPYDATASTRUCT cds;
               memset_dup(&cds, 0, sizeof(cds));
               cds.dwData = 15111984;
               cds.cbData = str.length();
               cds.lpData = (PVOID) (const char *) str;
               ::SendMessageA(hwndSpaBoot, WM_COPYDATA, NULL, (LPARAM) &cds);
            }

         }


#else

      throw 0;

#endif


         new_progress_end(0.8);
         CopyFileList(straFileList);

         new_progress_end(1.0);
         iRetry = 0;
         while((!machine_unsignalize_close_application()
           || machine_check_close_application(true))&& iRetry < 840)
         {
            if(iRetry == 0)
            {
               trace("Enabling applications to run.");
            }
            iRetry++;
            Sleep(484);
            if((iRetry % 33) == 0)
            {
               trace(".");
            }
            else
            {
               trace_add(".");
            }
         }
         trace("***executing installer.");

         if(m_NeedRestartBecauseOfReservedFile
         || m_NeedRestartFatalError)
         {
	         add_spa_start(m_strStart);

            if(::MessageBox(NULL, "The computer need to be restarted!!\n\nDo you want to restart now?\n\nWe recommend you to close all other applications first and then agree with this question using the buttons below.", "spa - Restart Needed!!", MB_ICONEXCLAMATION | MB_YESNO)
               == IDYES)
            {
               m_reboot();
            }
         }
         else
         {
            if(!ignit_phase2())
            {
               trace("***Going to ebing!!");
               Sleep(1984);
               goto install_begin;
            }
         }
      }
      return 0;
   }


   DWORD WINAPI installer::thread_proc_run(LPVOID lpParam)
   {

      installer * pinstaller = (installer *) lpParam;

      DWORD dw = pinstaller->run();

      delete pinstaller;

      return dw;

   }

   void installer::set_progress(double dProgress)
   {
      dProgress = m_dProgressStart + (m_dProgressEnd - m_dProgressStart) * dProgress;
      trace_progress(dProgress);
   }



   int installer::download_file_list(stra_dup & stra_dup, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen)
   {
   restart_download:
      m_dwDownloadTick = ::GetTickCount();
      m_dwDownload = 0;
      m_iDownloadRate = 0;
      m_bShowPercentage = true;
      m_iGzLen = 0;

      int i;
      vsstring str;
      double d = 0.0;
      m_dProgress = 0.0;
      bool bDownload;

      for(i = 0; i < stra_dup.get_count(); i++)
      {
         if(m_iTotalGzLen > 0)
         {
            m_dProgress1 = (double) m_iGzLen / (double) m_iTotalGzLen;
            m_dProgress2 = (double) (m_iGzLen + mapGzLen[stra_dup[i]]) / (double) m_iTotalGzLen;
         }
         else
         {
            m_dProgress1 = d / ((double) stra_dup.get_count());
            d += 1.0;
            m_dProgress2 = d / ((double) stra_dup.get_count());
         }
         str = m_strInstall;
         str += stra_dup[i];
         vsstring str1 = stra_dup[i];
         vsstring str2 = dir::name(str);
         if(str2.substr(0, m_strInstall.length()) == m_strInstall)
         {
            str2 = str2.substr(21);
            str2 = str_replace_dup(str2, "\\", "/");
         }
         trace(str_replace_dup(file_title_dup((str2 + str)), "\\", "/"));
         str += ".bz";
         vsstring str3 = str;
         str += ".";
         str += mapMd5[stra_dup[i]];
         vsstring strStageGz = ca2bz_get_dir(str1) + ca2bz_get_file(str1, mapMd5[stra_dup[i]]);
         vsstring strStageUnbz = ca2unbz_get_dir(str1) + ca2unbz_get_file(str1);
         dir::mk(dir::name(strStageUnbz));
         // uncompress, may have downloaded .bz correctly in previous install
         // and Get will later check if decompressed file is already the correct one
         bzuncompress(strStageUnbz, strStageGz);
         bDownload = true;
         if(strStageUnbz.ends_ci(".expand_fileset") && file_exists_dup(strStageGz) && file_length_dup(strStageGz)>0)
         {
            vsstring strExpand = stra_dup[i];
            vsstring strCurrent = stra_dup[i];
            strExpand += ".spa";
            //strExpand = str_replace_dup(str_replace_dup(strExpand, "\\", "_"), "/", "_");
            strExpand = "app\\stage\\metastage\\" + strExpand;
               for(int j = 0;  j < stra_dup.get_count(); j++)
               {
                  ::OutputDebugStringA(stra_dup[j]);
                  ::OutputDebugStringA("\r\n");
               }
            if(GetFileList(stra_dup, strExpand , mapLen, mapGzLen, mapMd5) > 0)
            {
               stra_dup.remove(strCurrent);
               m_iTotalGzLen -= mapGzLen[strCurrent];
               for(int j = 0;  j < stra_dup.get_count(); j++)
               {
                  ::OutputDebugStringA(stra_dup[j]);
                  ::OutputDebugStringA("\r\n");
               }
               goto restart_download;
            }
         }
         if(bDownload && download_file(str3, true, mapLen[stra_dup[i]], mapMd5[stra_dup[i]], mapGzLen[stra_dup[i]]))
         {
            m_dProgress = m_dProgress2;
            if(strStageUnbz.ends_ci(".expand_fileset"))
            {
               str = stra_dup[i];
               vsstring strExpand = stra_dup[i];
               vsstring strCurrent = stra_dup[i];
               vsstring strRelative = dir::path(dir::name(str), file_name_dup(str));
               vsstring strStageUnbz1 = ca2unbz_get_dir(str) + ca2unbz_get_file(str);
               vsstring strStageUnbz2 = ca2unbz_get_dir(strRelative) + ca2unbz_get_file(strRelative);
               file_ftd_dup(strStageUnbz2, strStageUnbz);
               strExpand += ".spa";
               //strExpand = str_replace_dup(str_replace_dup(strExpand, "\\", "_"), "/", "_");
               strExpand = "app\\stage\\metastage\\" + strExpand;
               for(int j = 0;  j < stra_dup.get_count(); j++)
               {
                  ::OutputDebugStringA(stra_dup[j]);
                  ::OutputDebugStringA("\r\n");
               }
               if(GetFileList(stra_dup, strExpand , mapLen, mapGzLen, mapMd5) > 0)
               {
                  stra_dup.remove(strCurrent);
                  m_iTotalGzLen -= mapGzLen[strCurrent];
               for(int j = 0;  j < stra_dup.get_count(); j++)
               {
                  ::OutputDebugStringA(stra_dup[j]);
                  ::OutputDebugStringA("\r\n");
               }

                  goto restart_download;
               }
            }
         }
         else
         {
            if(bDownload)
            {
               /*vsstring strError;
               strError = "could not get file ";
               strError += str;
               trace(strError);*/
               //::MessageBox(g_hwnd, strError, "ca2 votagus spa",  MB_ICONINFORMATION);
            }
         }
         m_iGzLen += mapGzLen[stra_dup[i]];
         dlr(m_iGzLen);
         set_progress((double) m_iGzLen / (double) m_iTotalGzLen);
      }
      if(m_pwindow != NULL)
      {
         m_pwindow->redraw();
      }
      return stra_dup.get_count();
   }




   bool installer::get(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen)
   {
      if(m_bOfflineInstall)
         return true;
	   vsstring url = url_in;
	   vsstring file;
      vsstring file2;
      vsstring dir;
      vsstring dir2;
      dir = dir::beforeca2();
      if(dir.substr(dir.size() - 2, 1) != "\\")
      {
         dir += "\\";
      }
      dir2 = dir + "ca2\\";
      dir += "ca2\\time\\bz\\";
      int oldpos = -1;
	   {
         int pos = url_in.find(m_strInstall);
         if(pos == 0)
         {
            url = url_in.substr(m_strInstall.length());
         }
         int oldpos = -1;
         pos = url.find("/");
         vsstring lastfile;
		   while (pos >=0)
		   {
			   file = url.substr(oldpos + 1, pos - oldpos -1);
            if(lastfile.size() > 0)
               dir +=  lastfile + "\\";
            lastfile = file;
            oldpos = pos;
            pos = url.find("/", oldpos + 1);
		   }
		   file = url.substr(oldpos + 1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
	   }
      if(stricmp_dup(file.substr(file.length() - 3, 3), ".bz") == 0)
      {
         file2 = file.substr(0, file.length() - 3);
      }
      else
      {
         file2 = file;
      }
      dir::mk(dir);

      if(bExist)
      {
         if(file_exists_dup(dir2 + file2))
         {
            if(iLength != -1 && iLength == file_length_dup((dir2 + file2)))
            {
               if(pszMd5 != NULL && strlen_dup(pszMd5) > 0 && stricmp_dup(get_file_md5((dir2 + file2)), pszMd5) == 0)
               {
                  return true;
               }
            }
         }
      }
      dir::mk(dir::name((dir + file)));
      m_dwCurFileLen = iGzLen;
      m_dwDownloadLen = 0;
      keep_true keepDownloadTrue(m_bMsDownload);
      return ms_download_dup(url_in, (dir + file), true, false, NULL, &::ms_download_callback, (void *) this);
   }


   bool installer::download_file(const vsstring& url_in, bool bExist, int iLength, const char * pszMd5, int iGzLen)
   {
      if(m_bOfflineInstall)
         return true;
	   vsstring url = url_in;
	   vsstring file;
      vsstring file2;
      vsstring dir;
      vsstring dir2;
      vsstring dir3;
      dir = dir::beforeca2();
      if(dir.substr(dir.size() - 2, 1) != "\\")
      {
         dir += "\\";
      }
      dir3 = dir + "ca2\\time\\patchwork\\";
      dir2 = dir + "ca2\\time\\unbz\\";
      dir += "ca2\\time\\bz\\";
      int oldpos = -1;
	   {
         int pos = url_in.find(m_strInstall);
         if(pos == 0)
         {
            url = url_in.substr(m_strInstall.length());
         }
         int oldpos = -1;
         pos = url.find("/");
         vsstring lastfile;
		   while (pos >=0)
		   {
			   file = url.substr(oldpos + 1, pos - oldpos -1);
            if(lastfile.size() > 0)
               dir +=  lastfile + "\\";
            lastfile = file;
            oldpos = pos;
            pos = url.find("/", oldpos + 1);
		   }
		   file = url.substr(oldpos + 1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
	   }
      if(stricmp_dup(file.substr(file.length() - 3, 3), ".bz") == 0)
      {
         file2 = file.substr(0, file.length() - 3);
      }
      else
      {
         file2 = file;
      }
      dir::mk(dir);

      // first check if the exiting (old file) is already up-to-date (the current one)
      if(bExist)
      {
         if(file_exists_dup(dir2 + file2))
         {
            if(iLength != -1 && iLength == file_length_dup((dir2 + file2)))
            {
               if(pszMd5 != NULL && strlen_dup(pszMd5) > 0 && stricmp_dup(get_file_md5((dir2 + file2)), pszMd5) == 0)
               {
                  trace_add(_unitext(" up-to-date c"));
                  return true;
               }
            }
         }
      }
      bool bOk = false;
      int iRetry = 0;
      int iMaxRetry = 3;
      char sz[1024];
      int iStatus;
      if(file_exists_dup((dir2 + file2)))
      {
         // then first try to download and apply patch
         vsstring strOldMd5 = get_file_md5((dir2 + file2));
         vsstring strNewMd5 = pszMd5;
         dir::mk(dir::name((dir + file)));
         m_dwCurFileLen = iGzLen;
         m_dwDownloadLen = 0;
         keep_true keepDownloadTrue(m_bMsDownload);
         uint64_t iBsLen = 0;
         bool bPossible = false;
         while(true)
         {
            vsstring strUrl;
            strUrl = "http://spa.api.veriterse.net/bspatch?file=";
            strUrl += url_encode_dup(file2);
            strUrl += "&old_hash=";
            strUrl += strOldMd5;
            strUrl += "&new_hash=";
            strUrl += strNewMd5;
            vsstring strBsPatch = dir + file + "." + strOldMd5 + "." + strNewMd5 + ".bspatch";
            bOk = ms_download_dup(strUrl, strBsPatch, false, false, &iStatus, &::ms_download_callback, (void *) this);
            if(iStatus == 404)
               break;
            if(!bPossible)
            {
               bPossible = true;
               ///trace_add(" patching may be possible");
            }
            if(bOk)
            {
               int iResult = 0;
               if(iLength != -1)
               {
                  dir::mk(dir::name((dir3 + file2)));
                  iResult = bspatch((dir2 + file2), (dir3 + file2), strBsPatch);
                  if(iResult != 0)
                  {
                  //   trace("");
                    // trace("Patch failed : files may be corrupted):");
   /*                  trace("old   file : ");
                     trace_add((dir2 + file2));
                     trace("new   file :");
                     trace_add((dir3 + file2));
                     trace("patch file :");
                     trace_add(strBsPatch);*/
                     bOk = false;
                     break;
                  }
               }
            }
            if(bOk)
            {
               if(iLength == -1)
               {
                //  trace("Patch Length Check : There is no length information to check.");
               }
               else
               {
                  uint64_t iActualLength = file_length_dup((dir3 + file2));
                  bOk = iLength == iActualLength;
                  //trace("Patch Length Verification : ");
                  /*sprintf_dup(sz, "correct length : %d bytes", iLength);
                  trace(sz);
                  sprintf_dup(sz, "actual  length : %d bytes", iActualLength);
                  trace(sz);*/
                  if(bOk)
                  {
                  //   trace_add("Length match!");
                  }
                  else
                  {
                    // trace_add(_unitext("Length mismatch ¡X!"));
                  }
               }
            }
            if(bOk)
            {
               if(pszMd5 == NULL || strlen_dup(pszMd5) == 0)
               {
                  //trace("Patch MD5 Hash Verification : there is no MD5 Hash information to verify.");
               }
               else
               {
                  vsstring strMd5;
                  strMd5 = get_file_md5((dir3 + file2));
                  bOk = stricmp_dup(strMd5, pszMd5) == 0;
                  //trace("Patch MD5 Hash Verification");
                  /*sprintf_dup(sz, "correct MD5 Hash : %s", pszMd5);
                  trace(sz);
                  sprintf_dup(sz, "actual  MD5 Hash : %s", strMd5);
                  trace(sz);*/
                  if(bOk)
                  {
                    // trace_add("MD5 Hash match!");
                  }
                  else
                  {
                     //trace_add(_unitext("MD5 Hash mismatch ¡X!"));
                  }
               }
            }
            if(bOk)
            {
               if(!file_copy_dup(dir2 + file2, dir3 + file2))
               {
                  trace("Failed to copy patched file: Need Restart Because Of Reserved File");
                  m_NeedRestartBecauseOfReservedFile = true;
               }
               iBsLen = file_length_dup(strBsPatch);
               break;
            }
            iRetry++;
            //sprintf_dup(sz, "An error ocurred. Retrying... Attempt %d of %d.", iRetry, iMaxRetry);
            //trace(sz);
            //trace("Patch may fail due timeout if the patched file is large and it is the first");
            //trace("time the patch is requested for the older-newer-pair patch combination.");
            //trace("Other users later requesting the same older-newer-pair patch combination will");
            //trace("benefit from the cached patch.");
            Sleep((1984 + 1977) * 5);
            if(iRetry >= iMaxRetry)
               break;
         }
         if(bOk)
         {
            if(iRetry > 0)
            {
              // sprintf_dup(sz, _unitext("Patch succeeded with %d retries %0.2fkbytes compressed ✓"), (iBsLen / 1000.0), iRetry);
               trace_add(_unitext(" c"));
            }
            else
            {
               // this trace is added and signalized like that because it
               // should be one of the most common cases and one of the most
               // normal cases.
               //sprintf_dup(sz, _unitext(" patched %0.2fkbytes compressed ✓"), (iBsLen / 1000.0));
               //trace_add(sz);
               trace_add(_unitext(" c"));
            }
         }
         else
         {
            //trace(_unitext("Patch failed ¡X!"));
         }
      }
      // then finally try to download the entire file
      if(!bOk)
      {
         dir::mk(dir::name((dir + file)));
         m_dwCurFileLen = iGzLen;
         m_dwDownloadLen = 0;
         keep_true keepDownloadTrue(m_bMsDownload);
         if(iRetry > 0)
         {
            //trace(("Going to download " + file_title_dup(file2) + " entirely"));
         }
         trace(file2);
         iRetry = 0;
         while(true)
         {
            bOk = ms_download_dup((url_in + "." + pszMd5), (dir + file + "." + pszMd5), true, true, &iStatus, &::ms_download_callback, (void *) this);
            if(iStatus == 404)
               break;
            if(bOk)
            {
               if(iLength != -1)
               {
                  int iResult = bzuncompress((dir2 + file2), (dir + file + "." + pszMd5));
                  if(iResult == -1)
                  {
                     m_NeedRestartBecauseOfReservedFile = true;
                  }
                  else if(iResult == -2)
                  {
                     m_NeedRestartFatalError = true;
                  }
               }
               bOk = iLength == -1 || iLength == file_length_dup((dir2 + file2));
               if(bOk)
               {
                  bOk = pszMd5 == NULL || strlen_dup(pszMd5) == 0 || stricmp_dup(get_file_md5((dir2 + file2)), pszMd5) == 0;
                  if(bOk)
                  {
                     break;
                  }
               }
            }
            iRetry++;
            //sprintf_dup(sz, "An error ocurred. Retrying... Attempt %d of %d.", iRetry, iMaxRetry);
            //trace(sz);
            if(iRetry >= iMaxRetry)
               break;
         }
         if(bOk)
         {
            sprintf_dup(sz, _unitext("%0.2fkbytes compressed c"), (iGzLen / 1000.0));
            trace(sz);
         }
         else
         {
            //trace((_unitext("Failed to download file ") + file2 + _unitext("¡X!")));
         }
      }
      if(!bOk)
      {
         //sprintf_dup(sz, _unitext("General failure to retrieve file \"%s\" ¡X!"), file2);
         //trace(sz);
      }
      return bOk;
   }


   vsstring installer::ca2_get_dir(LPCTSTR lpcszUrl)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      dir = dir::beforeca2();
      if(dir.substr(dir.size() - 2, 1) != "\\")
      {
         dir += "\\";
      }
      dir += "ca2\\";
      vsstring strFind;
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
	   while (pos >=0)
	   {
		   file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
	   }
	   file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      return dir;
   }

   vsstring installer::ca2bz_get_dir(LPCTSTR lpcszUrl)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      if(m_bInternetInstall)
      {
         dir = dir::path(dir::afterca2(), "time\\bz\\");
      }
      else
      {
         dir = m_strInstallGz;
      }
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
	   while (pos >=0)
	   {
		   file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
	   }
	   file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      return dir;
   }
   vsstring installer::ca2unbz_get_dir(LPCTSTR lpcszUrl)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      if(m_bInternetInstall)
      {
         dir = dir::path(dir::afterca2(), "time\\unbz\\");
      }
      else
      {
         dir = m_strInstallGz;
      }
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
	   while (pos >=0)
	   {
		   file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
	   }
	   file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      return dir;
   }
   vsstring installer::ca2_get_file(LPCTSTR lpcszUrl)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      dir = dir::beforeca2();
      if(dir.substr(dir.size() - 2, 1) != "\\")
      {
         dir += "\\";
      }
      dir += "ca2\\";
      vsstring strFind;
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
	   while (pos >=0)
	   {
		   file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
	   }
	   file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      if(file.substr(file.size() - 3, 3) == ".bz")
         return file.substr(0, file.size() - 3);
      else
         return file;
   }
   vsstring installer::ca2bz_get_file(LPCTSTR lpcszUrl, const char * pszMd5)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      dir = dir::path(dir::afterca2(), "time\\bz\\");
      vsstring strFind;
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
      while (pos >=0)
      {
	      file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
      }
      file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      if(pszMd5 != NULL)
      {
         if(file.substr(file.size() - 3, 3) == ".bz")
            return file + "." + pszMd5;
         else
            return file + ".bz." + pszMd5;
      }
      else
      {
         if(file.substr(file.size() - 3, 3) == ".bz")
            return file;
         else
            return file + ".bz";
      }
   }

   vsstring installer::ca2unbz_get_file(LPCTSTR lpcszUrl)
   {
      vsstring url_in(lpcszUrl);
      vsstring dir;
      vsstring url;
      vsstring file;
      dir = dir::path(dir::afterca2(), "time\\unbz\\");
      vsstring strFind;
      int pos = url_in.find(m_strInstall);
      if(pos == 0)
      {
         url = url_in.substr(m_strInstall.length());
      }
      else
      {
         url = url_in;
      }
      int oldpos = -1;
      pos = url.find("/");
      vsstring lastfile;
      while (pos >=0)
      {
	      file = url.substr(oldpos + 1, pos - oldpos -1);
         if(lastfile.size() > 0)
            dir +=  lastfile + "\\";
         lastfile = file;
         oldpos = pos;
         pos = url.find("/", oldpos + 1);
      }
      file = url.substr(oldpos + 1);
      if(lastfile.size() > 0)
         dir +=  lastfile + "\\";
      if(file.substr(file.size() - 3, 3) == ".bz")
         return file.substr(0, file.size() - 3);
      else
         return file;
   }


   bool installer::ca2_fy_url(vsstring & str, LPCTSTR lpcszPath, bool bExist, int iLength, const char * pszMd5, int iGzLen, bool bIndex)
   {
      vsstring strStage;
      vsstring strStageGz;
      vsstring strUrl;
      strUrl = lpcszPath;
      if(bIndex)
      {
	      if (!get(m_strInstall + lpcszPath, bExist, iLength, pszMd5, iGzLen))
	      {
		      printf_dup("Failed: %s\n", (void *) strUrl);
            return false;
	      }
         if(m_bOfflineInstall)
         {
            strStageGz = strUrl;
            strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, NULL);
         }
         else
         {
            strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, NULL);
         }
      }
      else
      {
	      if (!get(m_strInstall + lpcszPath + "." + pszMd5, bExist, iLength, pszMd5, iGzLen))
	      {
		      printf_dup("Failed: %s\n", (void *) strUrl);
            return false;
	      }
         if(m_bOfflineInstall)
         {
            strStageGz = strUrl;
            strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, pszMd5);
         }
         else
         {
            strStageGz = ca2bz_get_dir(strUrl) + ca2bz_get_file(strUrl, pszMd5);
         }
      }
      strStage = ca2_get_dir(strUrl) + ca2_get_file(strUrl);
      dir::mk(dir::name(strStage));
      bzuncompress(strStage, strStageGz);
      str = strStage;
      return true;
   }






   int installer::GetFileList(stra_dup & stra_dup, LPCTSTR lpcszPath, simple_string_to_intptr & mapLen, simple_string_to_intptr & mapGzLen, simple_string_to_string & mapMd5)
   {
      vsstring strPath(lpcszPath);
      strPath = str_replace_dup(strPath, "/", "\\");
      strPath = strPath;
      vsstring strUrl(lpcszPath);
      if(strUrl.length() == 0)
         return -1;
      if(strUrl.ends_ci(".spa"))
      {
         if(!m_strSpa.spa_insert(strUrl))
         {
            return -1;
         }
      }
      else
      {
         return -1;
      }
      trace(str_replace_dup(strUrl, "\\", "/"));
      char buf[2048];
      int iCount = 0;
      int iCurrent;
      strUrl += ".bz";
      vsstring str;
      vsstring strMd5 = mapMd5[strPath];
      strUrl.replace_ci("\\", "/");
      if(!ca2_fy_url(str, strUrl, false, -1, strMd5, -1))
         return -2;
      _FILE * f = fopen_dup(str, "rb");
      vsstring strPlatform = spa_get_platform();
      while(fgets_dup(buf, sizeof(buf), f))
      {
         buf[sizeof(buf) - 1] = '\0';
         while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
         {
            buf[strlen_dup(buf) - 1] = '\0';
         }
         vsstring str2;
         vsstring strPathParam(buf);
         if(strPathParam.begins_ci("stage\\basis\\"))
         {
            strPathParam = "stage\\" + strPlatform + strPathParam.substr(11);
         }
         iCurrent = GetFileList(stra_dup, strPathParam, mapLen, mapGzLen, mapMd5);
         if(iCurrent == -2)
         {
            return -2;
         }
         else if(iCurrent == -1)
         {
            if(stra_dup.spa_insert(strPathParam))
            {
               m_iTotalGzLen += mapGzLen[strPathParam];
            }
         }
         else
         {
            iCount += iCurrent;
         }
      }
      fclose_dup(f);
      return 1;
   }

   int installer::GetLocalFileList(stra_dup & stra_dup, LPCTSTR lpcszUrl)
   {

      vsstring strUrl(lpcszUrl);
      trace(strUrl);
      //MainWindowRedraw();
      if(strUrl.substr(strUrl.size() - 4, 4) != ".spa")
      {
         return -1;
      }
      char buf[2048];
      int iCount = 0;
      int iCurrent;
      strUrl += ".bz";
      vsstring str;
      if(!ca2_fy_url(str, strUrl, false, -1, NULL, -1))
         return -2;
      _FILE * f = fopen_dup(str, "rb");
      char * pszFind1;
      char * pszFind2;
      while(fgets_dup(buf, sizeof(buf), f))
      {
         while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
         {
            buf[strlen_dup(buf) - 1] = '\0';
         }
         pszFind1 = strstr_dup(buf, ",");
         pszFind2 = NULL;
         if(pszFind1 != NULL)
         {
            pszFind2 = strstr_dup(pszFind2 + 1, ",");
         }
         if(pszFind1 != NULL)
         {
            *pszFind1 = '\0';
            pszFind1++;
         }
         if(pszFind2 != NULL)
         {
            *pszFind2 = '\0';
            pszFind2++;
         }
         vsstring strSpa;
         vsstring str2;
         iCurrent = GetLocalFileList(stra_dup, buf);
         if(iCurrent == -1)
         {
            stra_dup.spa_insert(buf);
         }
         else
         {
            iCount += iCurrent;
         }
      }
      fclose_dup(f);
      return iCount;
   }


   int installer::UncompressFileList(stra_dup & stra_dup, simple_string_to_string & strmapMd5)
   {
      vsstring strStage;
      vsstring strStageGz;
      vsstring str;
      double d = 0.0;
      m_dProgress = 0.0;
      for(int i = 0; i < stra_dup.get_count(); i++)
      {
         //m_dProgress1 = d / ((double) stra_dup.size());
         //d += 1.0;
         //m_dProgress2 = d / ((double) stra_dup.size());
         str = stra_dup[i];
         str += ".bz";
         trace(str);
         strStageGz = dir::path(m_strInstallGz, ca2bz_get_file(str, strmapMd5[stra_dup[i]]));
         strStage = ca2_get_dir(str) + ca2_get_file(str);
         dir::mk(dir::name(strStage));
         bzuncompress(strStage, strStageGz);
         d += 1.0;
         m_dProgress = d / ((double) stra_dup.get_count());
      }
      m_dProgress = 1.0;
      if(m_pwindow != NULL)
      {
         m_pwindow->redraw();
      }
      return stra_dup.get_count();
   }

   int installer::CopyFileList(stra_dup & stra_dup)
   {
      vsstring strStage;
      vsstring strStageUnbz;
      vsstring str;
      double d = 0.0;
      m_dProgress = 0.0;
      for(int i = 0; i < stra_dup.get_count(); i++)
      {
         //m_dProgress1 = d / ((double) stra_dup.size());
         //d += 1.0;
         //m_dProgress2 = d / ((double) stra_dup.size());
         str = stra_dup[i];
         str += ".bz";
         trace(str);
         strStageUnbz = ca2unbz_get_dir(str) + ca2unbz_get_file(str);
         strStage = ca2_get_dir(str) + ca2_get_file(str);
         if(strStage.length() > strlen_dup(".expand_fileset") && stricmp_dup(strStage.substr(strStage.length() - strlen_dup(".expand_fileset"), strlen_dup(".expand_fileset")), ".expand_fileset") == 0)
         {
   //         file_ftd_dup(strStage.substr(0, strStage.length() - strlen_dup(".expand_fileset")), strStageUnbz);
         }
         else
         {
            dir::mk(dir::name(strStage));
            file_copy_dup(strStage, strStageUnbz);
         }
         d += 1.0;
         m_dProgress = d / ((double) stra_dup.get_count());
         set_progress((double) i / (double) stra_dup.get_count());
      }
      m_dProgress = 1.0;
      if(m_pwindow != NULL)
      {
         m_pwindow->redraw();
      }
      return stra_dup.get_count();
   }




   void installer::ParseSpaIndex(XNode & node)
   {
      if(node.name == "spa" && node.childs.get_count() > 0)
      {
         LPXNode lpnode = &node;
         for(int ui = 0; ui < lpnode->childs.get_count(); ui++)
         {
            if(lpnode->childs[ui]->name == "index")
            {
               if(lpnode->childs[ui]->GetAttr("start") != NULL)
               {
                  if(vsstring(lpnode->childs[ui]->GetAttrValue("start")).length() > 0)
                  {
                     m_iStart = 4;
                     m_strStart = vsstring(lpnode->childs[ui]->GetAttrValue("start"));
                  }
               }
               if(lpnode->childs[ui]->GetAttr("build") != NULL)
               {
                  if(vsstring(lpnode->childs[ui]->GetAttrValue("build")).length() > 0)
                  {
                     m_iStart = 4;
                     m_strBuildResource = vsstring(lpnode->childs[ui]->GetAttrValue("build"));
                  }
               }
               if(lpnode->childs[ui]->GetAttr("type") != NULL)
               {
                  #ifdef _WINDOWS
                  if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "parse_file_name")
                  {
                     m_iStart = 4;
                     char buf[2048];
                     ::GetModuleFileName(NULL, buf, sizeof(buf));
                     char * psz = strrchr_dup(buf, '\\');
                     vsstring str;
                     if(psz == NULL)
                     {
                        str = buf;
                     }
                     else
                     {
                        str = psz;
                     }
                     if(!stricmp_dup(str.substr(str.length()  - 4, 4), ".exe"))
                     {
                        str = str.substr(str.length() - 4);
                        if(str.length() > 19)
                        {
                           m_strStart = str.substr(0, str.length() - 19);
                           m_strBuildResource = str.substr(str.length() - 19);
                        }
                     }
                  }
                  else
                  #endif
                  if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "online_default")
                  {
                     m_bOfflineInstall = false;
                     m_strInstallGz = "http://ccvotagus.net/stage/";
                     m_strInstall = "http://ccvotagus.net/stage/";
                  }
                  else if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "offline")
                  {
                     m_bOfflineInstall = true;
                     m_strInstallGz = dir::path(lpnode->childs[ui]->GetAttrValue("src"), "stage.bz\\");
                     m_strInstall = dir::path(lpnode->childs[ui]->GetAttrValue("src"), "stage\\");
                  }
                  else if(vsstring(lpnode->childs[ui]->GetAttrValue("type")) == "online")
                  {
                     m_bOfflineInstall = false;
                     m_bInstallSet = true;
                     m_strInstallGz = lpnode->childs[ui]->GetAttrValue("src");
                     m_strInstall = lpnode->childs[ui]->GetAttrValue("src");
                  }
               }
            }
         }
      }
   }

   vsstring installer::load_string(const char * pszId, const char * pszDefault)
   {
      LPXNode lpnode = &m_nodeStringTable;
      for(int ui = 0; ui < lpnode->childs.get_count(); ui++)
      {
         if(vsstring(lpnode->childs[ui]->GetAttrValue("id")) == pszId)
         {
            return lpnode->childs[ui]->value;
         }
      }
      return pszDefault;
   }

   void installer::ParseIndexFile(const char * psz, simple_string_to_intptr & mapLen, simple_string_to_string & mapMd5, simple_string_to_intptr & mapGzLen)
   {
      _FILE * f = fopen_dup(psz, "rb");
      char * pszFind1;
      char * pszFind2;
      char * pszFind3;
      int iBufSize = 16 * 1024;
      char * buf = (char *) ca2_alloc(iBufSize);
      while(fgets_dup(buf, iBufSize, f))
      {
         while(buf[strlen_dup(buf) - 1] == '\r' || buf[strlen_dup(buf) - 1] == '\n')
         {
            buf[strlen_dup(buf) - 1] = '\0';
         }
         pszFind1 = strstr_dup(buf, ",");
         pszFind2 = NULL;
         pszFind3 = NULL;
         if(pszFind1 != NULL)
         {
            pszFind2 = strstr_dup(pszFind1 + 1, ",");
            if(pszFind2 != NULL)
            {
               pszFind3 = strstr_dup(pszFind2 + 1, ",");
            }
         }
         if(pszFind1 != NULL)
         {
            *pszFind1 = '\0';
            pszFind1++;
         }
         if(pszFind2 != NULL)
         {
            *pszFind2 = '\0';
            pszFind2++;
         }
         if(pszFind3 != NULL)
         {
            *pszFind3 = '\0';
            pszFind3++;
         }
         vsstring strSpa;
         vsstring str2;
         strSpa = m_strInstall;
         strSpa += buf;
         if(pszFind1 != NULL)
         {
            m_iProgressMode = 0;
            mapLen[(vsstring)(const char *) buf] = atoi_dup(pszFind1);
         }
         else
            mapLen[(vsstring)(const char *) buf] = -1;
         if(pszFind2 != NULL)
         {
            mapMd5[(vsstring)(const char *) buf] = pszFind2;
         }
         else
            mapMd5[(vsstring)(const char *) buf] = "";
         if(pszFind3 != NULL)
         {
            mapGzLen[(vsstring)(const char *) buf] = atoi_dup(pszFind3);
         }
         else
            mapGzLen[(vsstring)(const char *) buf] = -1;
      }
      fclose_dup(f);
      ca2_free(buf);
   }

   bool installer::spa_exec(const char * psz)
   {
      vsstring strExec(psz);
      if(strExec.substr(0, 15) == "install_service")
      {
         vsstring strStage;
         strStage = dir::path(dir::beforeca2(),strExec.substr(16));
         #ifdef _WINDOWS
         ::ShellExecute(m_pwindow == NULL ? NULL : m_pwindow->m_hwnd, "open", strStage, " : remove usehostlogin", dir::name(strStage), SW_SHOWNORMAL);
         ::ShellExecute(m_pwindow == NULL ? NULL : m_pwindow->m_hwnd, "open", strStage, " : install usehostlogin", dir::name(strStage), SW_SHOWNORMAL);
         #else
         throw "TODO";
         #endif
      }
      else if(strExec.substr(0, 10) == "install_ex")
      {
         vsstring strStage;
         vsstring str2 = strExec.substr(11);
         int iPos = str2.find(" ");
         vsstring str3 = str2.substr(iPos + 1);
         strStage = dir::path(dir::beforeca2(), "ca2");
         strStage = dir::path(strStage, str3);
         #ifdef _WINDOWS
         ::ShellExecute(m_pwindow == NULL ? NULL : m_pwindow->m_hwnd, "open", strStage, (" : " + str2.substr(0, iPos) + " usehostlogin"), dir::name(strStage), SW_SHOWNORMAL);
         #else
         throw "TODO";
         #endif
      }
      return true;
   }


   bool installer::ignit_phase2()
   {



      char szFormat[256];
      vsstring strUrl;
      strUrl = m_strSpaIgnitionBaseUrl + "/query?node=install_application&id=";
      strUrl += m_strStart;
      strUrl += "&key=post_install_count";
      vsstring strCount = ms_get_dup(strUrl);
      int iCount = atoi_dup(strCount);
      set_progress(0.2);
      for(int i = 0; i < iCount; i++)
      {
         strUrl = m_strSpaIgnitionBaseUrl + "/query?node=install_application&id=";
         strUrl += m_strStart;
         strUrl += "&key=post_install";
         sprintf_dup(szFormat, "[%d]", i);
         strUrl += szFormat;
         vsstring strExec = ms_get_dup(strUrl);
         if(!spa_exec(strExec))
         {
            ::MessageBox(m_pwindow == NULL ? NULL :m_pwindow->m_hwnd, "Error", "Error", MB_OK);
         }
         set_progress(((double) i * (0.5 - 0.2) / (double) iCount) + 0.2);
      }
      set_progress(0.5);
//      DWORD dwStartError;
      trace("starting installer...");
      int i = run_ca2_application_installer(m_strStart);
      if(m_strStart != "_set_windesk" && is_installed("_set_windesk"))
      {
         //DWORD dwStartError2;
         trace("starting windeskPackage...");
         int i2 = run_ca2_application_installer("_set_windesk");
         trace("started windeskPackage");
      }
      trace(".");
      set_progress(0.9);
      vsstring strPlatform = spa_get_platform();
      if(i == 0)
      {
         set_updated(m_strBuild);
         // keeps g_bInstalling for a while
         Sleep((1984 + 1977) * 5);
         //::PostMessage(g_hwnd, WM_CLOSE, 0, 0);

         if(g_straRestartProcess.get_count() > 0)
         {

            vsstring str;

            str = "Now :\n\n";

            for(int i = 0; i < g_straRestartProcess.get_count(); i++)
            {
               if(file_is_equal_path(file_get_mozilla_firefox_plugin_container_path(), g_straRestartProcess[i]))
               {
                  g_straRestartProcess.remove_at(i);
                  str += "You may reload the Firefox plugin or plugins that has/have been shutdown.\n\n";
               }
            }

            if(g_straRestartProcess.get_count() > 0)
            {
               str += "You may restart the applications listed below if they are not restarted automatically:\n\n";
               for(int i = 0; i < g_straRestartProcess.get_count(); i++)
               {
                  str += "\t";
                  str += g_straRestartProcess[i];
                  if(i == g_straRestartProcess.get_count() - 1)
                  {
                     str += ".";
                  }
                  else if(i == g_straRestartProcess.get_count() - 2)
                  {
                     str += ", and;\n";
                  }
                  else
                  {
                     str += ";\n";
                  }

               }
            }

            ::MessageBox(NULL, str, "You may restart the applications ...", MB_ICONINFORMATION | MB_OK);
         }
         return true;
      }
      else
      {
         //DWORD dwError = dwStartError;
         trace("");
         trace("");
         trace("");
         trace("");
         trace("");
         trace("Failed to install");
         trace("Manually contact mailto:support.veriwell@ca2mail.com");
         trace("or Manually go to http://votagus.com/");
         trace("");
         trace("In votagus.com you can try to");
         trace("download the most recent release version for installation");
         trace("(Automatic links not availabe by now)");
         trace("");
         trace("");
         trace("");
         trace("");
         trace("");
         return false;
      }
   }


   int installer::run_file(const char * pszFile, int nCmdShow)
   {

      m_strFile = pszFile;

   //	MSG msg;
   //	HACCEL hAccelTable;



      XNode node;

      //MessageBox(NULL, "BegInstall", "Caption", MB_OK);
      if(m_iStart != 4)
      {
         vsstring strCa2sp = file_get_contents_dup(m_strFile);
         if(strCa2sp.length() == 0)
         {
            #ifdef _WINDOWS
            strCa2sp = read_resource_as_string_dup(NULL, 1984, "CA2SP");
            #else
            throw "TODO";
            #endif
         }
         if(strCa2sp.length() > 0)
         {
            node.Load(strCa2sp);
            ParseSpaIndex(node);
         }
         else
         {
            m_strStart = "bergedge";
         }
      }



   /*
      char * pszStart = strstr_dup(lpCmdLine, "start=");
      char * pszEnd = NULL;
      if(pszStart != NULL)
      {
         pszStart += strlen_dup("start=");
         pszEnd = pszStart;
         while(isdigit(*pszEnd) || isalpha_dup(*pszEnd))
         {
            pszEnd++;
         }
         m_strStart = vsstring(pszStart, pszEnd - pszStart);
      }
      else
      {
         m_strStart = "bergedge";
      }*/

   //   char * pszStart;
      char * pszEnd = NULL;
      char * lpCmdLine = ::GetCommandLine();
      char * pszLocale = strstr_dup((char *) lpCmdLine, "locale=");
      if(pszLocale != NULL)
      {
         pszLocale += strlen_dup("locale=");
         pszEnd = pszLocale;
         while(isdigit_dup(*pszEnd) || isalpha_dup(*pszEnd))
         {
            pszEnd++;
         }
         m_strLocale = vsstring(pszLocale, pszEnd - pszLocale);
      }
      else
      {
         m_strLocale = "";
      }

      return run_starter_start(nCmdShow);
   }


   int installer::starter_start(const char * pszId)
   {

      m_strStart  = pszId;

      m_bOfflineInstall = false;

      m_strInstallGz = "http://ccvotagus.net/stage/";

      m_strInstall = "http://ccvotagus.net/stage/";

      m_bForceUpdatedBuild = true;

      m_bStarterStart = true;

      return run_starter_start(m_bShow ? SW_SHOWNORMAL : SW_HIDE);

   }


   int installer::application_name()
   {
      vsstring strUrl;
      trace(("get application name from server http://spaignition.api.veriterse.net/ using id \"" + m_strStart + "\" "));
      strUrl = m_strSpaIgnitionBaseUrl + "/query?node=install_application&id=";
      strUrl += m_strStart;
      strUrl += "&key=name";

      vsstring strName;
      int iRetry = 0;
      while(true)
      {
         strName = ms_get_dup(strUrl);
         if(strName.length() > 0)
            break;
         else if(iRetry < 84)
            iRetry++;
         else
         {
            trace("main server seems to be unavailable. could not get application name");
            exit(-1);
            return -1;
         }
         trace_add(".");
         Sleep(484);
      }

      strName = "Installing " + strName;

      m_strTitle = strName;

      trace(("***" + strName));
      return 0;
   }

   int installer::ca2_build_version()
   {
      int iRetry = 0;
      RetryBuildNumber:
         if(m_strBuildResource.length() == 19) // heuristically valid
         {
            trace("***Internal build number");
            m_strBuild = m_strBuildResource;
         }
         else
         {
            trace("***Getting build number");
            if(iRetry > 10)
            {
               trace("could not get build number. exiting");
               exit(-1);
               return -1;
            }
            iRetry++;
            m_strBuild = ms_get_dup(m_strSpaIgnitionBaseUrl + "/query?node=build", false, &::ms_get_callback, (void *) this);
            m_strBuild.trim();
            if(m_strBuild.length() != 19)
            {
               Sleep(1984);
               goto RetryBuildNumber;
            }
         }
         trace(m_strBuild);
         return 0;
   }

   int installer::calc_host(vsstring & strSpaHost, int &iHostRetry)
   {
      RetryHost:
      if(iHostRetry > 84)
      {
         exit(-1);
         return -1;
      }
      else if(iHostRetry > 0)
      {
         trace("Retrying to guess host...");
      }
      iHostRetry = 1;
      if(g_strLastHost.is_empty())
      {
         g_strLastHost = g_strCurrentHost;
      }
      else
      {
         g_strLastHost = g_strCurrentHost + ";" + g_strLastHost;
      }
      vsstring strUrl;

#if CA2_PLATFORM_VERSION == CA2_BASIS
      strUrl = m_strSpaIgnitionBaseUrl + "/query?node=spa_host&version=basis";
#else
      strUrl = m_strSpaIgnitionBaseUrl + "/query?node=spa_host&version=stage";
#endif

      if(!g_strLastHost.is_empty())
      {
         strUrl += "&last_host=" + g_strLastHost;
      }
      trace("***Guessing fastest mirror");
      int iGuessRetry = 0;
      trace(".");
      while(iGuessRetry < 30)
      {
         strSpaHost = ms_get_dup(strUrl, false, &::ms_get_callback, (void *) this);
         if(strSpaHost.is_empty())
         {
            if(g_strLastHost.is_empty())
            {
               trace_add(".");
               Sleep(484);
               iGuessRetry++;
            }
            else
            {
#if CA2_PLATFORM_VERSION == CA2_BASIS
               strUrl = m_strSpaIgnitionBaseUrl + "/query?node=spa_host&version=basis";
#else
               strUrl = m_strSpaIgnitionBaseUrl + "/query?node=spa_host&version=stage";
#endif
            }
         }
         else
         {
            break;
         }
      }
      if(g_strCurrentHost == strSpaHost)
      {
         g_strLastHost.clear();
         g_strCurrentHost.clear();
         goto RetryHost;
      }
      return 0;
   }

   /*vsstring installer::install(const char * psz)
   {
      return m_strInstall + psz;
   }*/



   int installer::run_uninstall(const char * lpCmdLine, int nCmdShow)
   {
      return run_install(lpCmdLine, nCmdShow);
   }

   int installer::run_uninstall_run(const char * lpCmdLine, int nCmdShow)
   {
      DWORD dwStartError = 0;
      return ca2_app_install_run(lpCmdLine, "", "uninstall", dwStartError, true);
   }

   int installer::run_install(const char * lpCmdLine, int nCmdShow)
   {
      vsstring str = lpCmdLine;
      vsstring strFile = lpCmdLine;

      int i1 = str.find("\"");
      if(i1 >= 0)
      {
         int i2 =str.find("\"", i1 +1);
         strFile = str.substr(i1 + 1, i2 - i1 - 1);
      }
      else
      {
         strFile = str;
      }

      if(strFile.is_empty())
      {
         strFile = dir::path(dir::module_folder(), "spa.xml");
      }

	   return run_file(strFile, nCmdShow);
   }



   int installer::run_starter_start(int nCmdShow)
   {

      vsstring strName = "spa ignition";

	   strcpy_dup(szTitle, strName);
	   strcpy_dup(szWindowClassSpaAdmin, strName);

      if(nCmdShow != SW_HIDE)
      {
         //m_pwindow = new spa::window;
      }

#if defined(WINDOWS)
      if(m_pwindow != NULL)
      {
         m_pwindow->register_class(m_hinstance);
      }
#endif

	   if(!init_instance(m_hinstance, nCmdShow))
	   {
		   return FALSE;
	   }


	   return 0;

   }

   bool installer::init_instance(HINSTANCE hinstance, int nCmdShow)
   {

      m_hinstance = hinstance; // Store instance handle in our global variable

      m_strInstallGz = dir::module_folder("ca2\\bz\\stage\\");
      m_strInstall = dir::module_folder("ca2\\stage\\");

      m_strIndexGz = dir::path(m_strInstallGz, ("app\\stage\\metastage\\" + m_strStart + ".spa.bz"));
      m_strIndex = dir::path(m_strInstallGz, ("app\\stage\\metastage\\" + m_strStart + ".spa"));

      bool bOfflineInstall1 = dir::exists(dir::module_folder("ca2\\bz"));
      //bool bOfflineInstall2 = file_exists_dup(g_strIndexGz);
      //m_bOfflineInstall = bOfflineInstall1 && bOfflineInstall2;
      m_bOfflineInstall = bOfflineInstall1;

      // Default stage.bz folder not present, would default to internet install
      // since the spa.xml is not present and contains turning information.
      if(!m_bOfflineInstall && (m_strStart.length() == 0 || (!m_bForceUpdatedBuild && m_strBuildResource.length() == 0)))
      {
         vsstring str = file_get_contents_dup(dir::module_folder("spa.xml"));
         XNode node;
         node.Load(str);
         ParseSpaIndex(node);
      }

#ifdef _WINDOWS
      // Default stage.bz folder not present, would default to internet install
      // since the spa.xml is not present and contains turning information.
      if(!m_bOfflineInstall && !m_bInstallSet && (m_strStart.length() == 0 || (!m_bForceUpdatedBuild && m_strBuildResource.length() == 0)))
      {
         vsstring str = read_resource_as_string_dup(NULL, 1984, "CA2SP");
         XNode node;
         node.Load(str);
         ParseSpaIndex(node);
      }
#else
      throw "NEEDED?TODO?";
#endif


      if(m_strStart == "***parse_file_name")
      {

      }



      m_strIndexGz = dir::path(m_strInstallGz, ("app\\stage\\metastage\\" + m_strStart + ".spa.bz"));
      m_strIndex = dir::path(m_strInstallGz, ("app\\stage\\metastage\\" + m_strStart + ".spa"));

      m_bInternetInstall = !m_bOfflineInstall;

      m_iStyle = 0;

      starter_start();

      return TRUE;
   }

   int installer::spaadmin_main(const char * pszCommandLine)
   {
      ::srand_dup(::GetTickCount());

      ensure_trace_file();

      if(!m_machineevent.initialize())
      {
         return 5;
      }

      m_iStyle = 0;

      m_bShowPercentage = false;

	   //UNREFERENCED_PARAMETER(lpCmdLine);
      m_iStart = 0;
      //m_iStyle = 0;

      vsstring str = pszCommandLine;

      vsstring strExe = file_name_dup(file_module_path_dup());

      bool bSpa = false;

      if(str.find(" background ") != vsstring::npos
      || str.ends(" background") || strExe.find(" in background ") != vsstring::npos
      || strExe.ends(" in background"))
      {
         m_bShow = false;
      }

      if(str.find(" spa ") != vsstring::npos
      || str.ends(" spa") || strExe.find(" in spa ") != vsstring::npos
      || strExe.ends(" in spa"))
      {
         spa::installer::spa();
         return 0;
      }

      m_bLoginStartup = false;
      size_t i = str.find("install_filter=");
      if(i != vsstring::npos)
      {
         int iStart = i + 15; // 15 = strlen_dup("install_filter=")
         i = str.find(" ", i);
         if(i != vsstring::npos)
         {
            m_strInstallFilter = str.substr(iStart, i - iStart);
         }
         else
         {
            m_strInstallFilter = str.substr(iStart);
         }
      }
      //MessageBox(NULL, "xxx", "yyy", MB_OK);
      i = str.find("install=");
      if(i != vsstring::npos)
      {
         int iStart = i + 8; // 8 = strlen_dup("install=")
         i = str.find(" ", i);
         if(i != vsstring::npos)
         {
            m_strStart = str.substr(iStart, i - iStart);
         }
         else
         {
            m_strStart = str.substr(iStart);
         }
         m_iStart = 4;
         return run_install(pszCommandLine, m_nCmdShow);

      }
      if(strExe.begins_ci("Install "))
      {
         int iStart = strlen_dup("Install ");
         i = strExe.find(" ", iStart);
         vsstring strIdStart;
         if(i != vsstring::npos)
         {
            strIdStart = strExe.substr(iStart, i - iStart);
         }
         else
         {
            strIdStart = strExe.substr(iStart);
         }
         m_iStart = 4;
         return starter_start(strIdStart);
      }
      vsstring strFind("starter_start=");
      i = str.find(strFind);
      if(i != vsstring::npos)
      {
         int iStart = i + strFind.length(); // 8 = strlen_dup("install=")
         i = str.find(" ", iStart);
         vsstring strIdStart;
         if(i != vsstring::npos)
         {
            strIdStart = str.substr(iStart, i - iStart);
         }
         else
         {
            strIdStart = str.substr(iStart);
         }
         m_iStart = 4;
         return starter_start(strIdStart);
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
         vsstring str(utf16_to_8(argv[1]));
         return run_file(str, m_nCmdShow);
      }


      int iFind;
      if((iFind = str.find("uninstall")) != vsstring::npos)
      {
         return run_uninstall_run(&str[iFind + 10], m_nCmdShow);
      }
      else if(str.find("uninstall") != vsstring::npos)
      {
         return run_uninstall(pszCommandLine, m_nCmdShow);
      }
      else
      {
         //m_strStart = "_set_windesk";  m_iStart = 4; return run_install(lpCmdLine, nCmdShow);
         return run_install(pszCommandLine, m_nCmdShow);
      }
   }


   bool installer::is_application_opened(const char * psz)
   {

   /*   SECURITY_ATTRIBUTES MutexAttributes;
      memset_dup( &MutexAttributes, 0, sizeof(MutexAttributes) );
      MutexAttributes.nLength = sizeof( MutexAttributes );
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      BOOL bInitOk = InitializeSecurityDescriptor(
                        &SD,
                        SECURITY_DESCRIPTOR_REVISION );
      if ( bInitOk )
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         BOOL bSetOk = SetSecurityDescriptorDacl( &SD,
                                               TRUE,
                                               (PACL)NULL,
                                               FALSE );
         if ( bSetOk )
         {*/
            // Make the security attributes point
            // to the security descriptor
            //MutexAttributes.lpSecurityDescriptor = &SD;
            vsstring strMutex;
            strMutex = "Global\\ca2_fontopus_votagus_application_global_mutex:";
            strMutex += psz;
            //HANDLE hmutex = ::CreateMutex(&MutexAttributes, FALSE, strMutex);
            simple_mutex mutex(strMutex, false);
            bool bOpened = ::GetLastError() == ERROR_ALREADY_EXISTS;
            if(bOpened)
            {
               vsstring strMessage;
               strMessage = psz;
               strMessage += "app.exe is still opened!";
               trace(strMessage);
               trace("You may finalize the process by:");
               trace("   1. Pressing CTRL+ALT+DEL;");
               trace("   2. Opening Task Manager, and;");
        strMessage = "   4. Closing the process ";
               strMessage += psz;
               strMessage += "app.exe.";
               trace(strMessage);
               trace(".");
            }
            return bOpened;
   /*      }
         else
         {
            return false;
         }
      }
      else
      {
         return false;
      }
      */
   }

   bool installer::is_there_application_opened()
   {
      return
         is_application_opened("winactionarea")
      || is_application_opened("winservice_1")
      || is_application_opened("winutil")
      || is_application_opened("winshelllink")
      || is_application_opened("command")
      || is_application_opened("winservice_filesystemsize")
      || is_application_opened("filemanager");
   }

   void installer::machine_signalize_close_application()
   {
      mutex_lock lockMachineEvent(&m_machineevent.m_mutex, true);
      machine_event_data data;
      m_machineevent.read(&data);
      data.m_fixed.m_bRequestCloseApplication = true;
      m_machineevent.write(&data);
   }

   bool installer::machine_unsignalize_close_application()
   {
      mutex_lock lockMachineEvent(&m_machineevent.m_mutex, true);
      machine_event_data data;
      m_machineevent.read(&data);
      data.m_fixed.m_bRequestCloseApplication = false;
      bool bOk = m_machineevent.write(&data);
      return bOk;
   }

   bool installer::machine_check_close_application(bool bDefault)
   {
      mutex_lock lockMachineEvent(&m_machineevent.m_mutex, true);
      machine_event_data data;
      if(!m_machineevent.read(&data))
         return false;
      return data.m_fixed.m_bRequestCloseApplication;
   }

   void installer::spa()
   {

      installer * pinstaller = new installer;

      pinstaller->m_bStarterStart = false;

      ::CreateThread(NULL, 0, spa::installer::thread_proc_run, (LPVOID) pinstaller, 0, 0);

   }


   void installer::starter_start()
   {

      m_bStarterStart = true;

      ::CreateThread(NULL, 0, spa::installer::thread_proc_run, (LPVOID) this, 0, 0);

   }



   void installer::add_spa_start(const char * pszId)
   {
	   vsstring strPath = dir::appdata("spa_start.xml");
	   vsstring strContents = file_get_contents_dup(strPath);
      XNode node;
      node.Load(strContents);
      node.name = "spa";
      LPXNode lpnode = node.GetChildByAttr("start", "id", pszId);
      if(lpnode == NULL)
      {
	      lpnode = node.AppendChild("start");
	      lpnode->AppendAttr("id", pszId);
	      file_put_contents_dup(strPath, node.GetXML());
      }
   }

   void installer::remove_spa_start(const char * pszId)
   {
	   vsstring strPath = dir::appdata("spa_start.xml");
	   vsstring strContents = file_get_contents_dup(strPath);
      XNode node;
      node.Load(strContents);
      node.name = "spa";
      LPXNode lpnode = node.GetChildByAttr("start", "id", pszId);
      if(lpnode != NULL)
      {
	      node.RemoveChild(lpnode);
	      file_put_contents_dup(strPath, node.GetXML());
      }
   }



   bool installer::m_reboot()
   {
#ifdef _WINDOWS
	   HANDLE hToken;
	   TOKEN_PRIVILEGES tkp;
	   if (!OpenProcessToken(GetCurrentProcess(),
		   TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		   return false;
	   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
	   tkp.PrivilegeCount = 1;
	   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
	   if (ExitWindowsEx(EWX_REBOOT, 0) == 0)
		   return false;
	   //reset the previlages
	   tkp.Privileges[0].Attributes = 0;
	   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
#else
      throw "TODO?";
#endif
      return true;
   }


   void installer::dlr(DWORD dwDownload)
   {
      if(!m_bShowPercentage)
         return;
      DWORD dw = ::GetTickCount();
      DWORD dwDeltaTime = dw - m_dwDownloadTick;
      if(dwDeltaTime < 184)
         return;
      m_dwDownloadTick = dw;
      DWORD dwLen = dwDownload - m_dwDownload;
      m_dwDownload = dwDownload;
      if(m_daDownloadRate.get_count() < 100)
      {
         m_daDownloadRate.add(((double)dwLen / 1024.0) / ((double)(dwDeltaTime) / 1000.0));
      }
      else
      {
         if(m_iDownloadRate >= 100 || m_iDownloadRate < 0)
            m_iDownloadRate = 0;
         m_daDownloadRate[m_iDownloadRate] = ((double)dwLen / 1024.0) / ((double)(dwDeltaTime) / 1000.0);
         m_iDownloadRate++;
      }
      if(m_daDownloadRate.average() == 0.0)
      {
         if(m_dDownloadRate != 0.0)
         {
            m_dDownloadRate = 0.0;
            m_dwDownloadZeroRateTick = ::GetTickCount();
            m_dwDownloadZeroRateRemain = m_dwDownloadRemain;
         }
         m_dwDownloadRemain = m_dwDownloadZeroRateRemain + ::GetTickCount() - m_dwDownloadZeroRateTick;
      }
      else
      {
         m_dDownloadRate = m_daDownloadRate.average();
         m_dwDownloadRemain = (DWORD)(((m_iTotalGzLen - m_iGzLen) / 1024.0) / m_daDownloadRate.average());
      }
   }


   bool installer::launcher::ensure_executable()
   {

      int iSpabootInstallStrSize = MAX_PATH * 16;
      m_strPath.alloc(iSpabootInstallStrSize);

   #ifdef _WINDOWS

      HINSTANCE hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("npca2.dll");
      if(hinstancePlugin == NULL)
         hinstancePlugin = (HINSTANCE) ::GetModuleHandleA("iexca2.dll");
      if(hinstancePlugin != NULL)
      {
         char szModulePath[MAX_PATH * 3];
         ::GetModuleFileNameA((HINSTANCE) hinstancePlugin , szModulePath, sizeof(szModulePath));

         char * file = NULL;
         ::GetFullPathNameA(szModulePath, iSpabootInstallStrSize, m_strPath.m_psz, &file);
         file[0] = '\0';

         strcat_dup(m_strPath.m_psz, "installer.exe");
      }
   #else
      throw "TODO";
   #endif

      if(!file_exists_dup(m_strPath))
      {
         int iRetry = 0;
         while(iRetry < 8)
         {

            if(!get_temp_file_name_dup(m_strPath.m_psz, iSpabootInstallStrSize, "installer", "exe"))
               return false;

            if(is_file_ok(m_strPath, "installer.exe"))
               break;
            if(ms_download_dup("http://veriterse.net/spa?download=installer.exe&authnone", m_strPath, false))
            {
               if(is_file_ok(m_strPath, "installer.exe"))
               {
                  break;
               }
            }
            iRetry++;
         }
      }
      if(!is_file_ok(m_strPath, "installer.exe"))
      {
         return false;
      }
      return true;
   }

   vsstring installer::launcher::get_executable_path()
   {
      ensure_executable();
      return m_strPath;
   }


   int installer::run_ca2_application_installer(const char * id)
   {
      vsstring param;
      param = "-install=";
      param += id;
#if defined(WINDOWS)
      wchar_t * pwsz = new wchar_t[2048];
      ::GetModuleFileNameW(NULL, pwsz, 2048);
      wchar_t * pwszFullPath = new wchar_t[2048];
      wchar_t * pwszFile = NULL;
      ::GetFullPathNameW(pwsz, 2048, pwszFullPath, &pwszFile);
      char * psz = utf16_to_8(pwszFullPath);
      delete pwsz;
      delete pwszFullPath;
#elif defined(MACOS)
       char path[MAXPATHLEN];
       uint32_t path_len = MAXPATHLEN;
       _NSGetExecutablePath(path, &path_len);
       char * psz = path;
#else
      char * psz = br_find_exe("installer");
#endif
      call_sync(psz, param);
#if defined(WINDOWS)
      ca2_free(psz);
#else
      free(psz);
#endif

      return 0;
   }


   int ca2_app_install_run(const char * psz, const char * pszParam1, const char * pszParam2, DWORD & dwStartError, bool bSynch)
   {
      vsstring strStage;
      vsstring strApp;
      vsstring strUrl;

      vsstring strParam1;
      vsstring strParam2;

      if(pszParam1 != NULL)
      {
         strParam1 = pszParam1;
         strParam1.trim();
      }

      if(pszParam2 != NULL)
      {
         strParam2 = pszParam2;
         strParam2.trim();
      }

      vsstring strPlatform = spa_get_platform();

#ifdef _WINDOWS
      ::SetDllDirectory(dir::path(dir::beforeca2(), "ca2\\stage\\" + strPlatform));
#endif

      ::ca::library libraryOs;

      libraryOs.open(dir::path(dir::beforeca2(), "ca2\\stage\\" + strPlatform + "\\os"));

      CA2MAIN pfn_ca2_main = (CA2MAIN) libraryOs.raw_get("ca2_main");

      strStage = dir::path(dir::beforeca2(), ("ca2\\stage\\" + strPlatform + "\\ca2app.exe"));

      if(strParam1.length() > 0)
      {
         strStage += " " + strParam1;
      }
      strStage += " : app=bergedge bergedge_start=";
      strStage += psz;
      if(strParam2.length() > 0)
      {
         strStage += " " + strParam2;
      }

#ifdef WINDOWS
      pfn_ca2_main(::GetModuleHandleA(NULL), NULL, strStage, SW_HIDE);
#else
      pfn_ca2_main(strStage, SW_HIDE);
#endif

      return 0;
   }

} // namespace spa







