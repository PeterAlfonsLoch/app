﻿#include "c/c.h"


#include <psapi.h>


#include <tlhelp32.h>


class simple_app
{
public:


   HINSTANCE                  m_hinstance;
   int                        __argc;
   TCHAR **                   __targv;

   MSG                        m_msg;
   int                        m_iReturn;


   simple_app();
   virtual ~simple_app();

   virtual void main();

   virtual bool initialize();
   virtual int run();
   virtual bool finalize();

};


class installer :
   public simple_app,
   public small_ipc_rx_channel::receiver
{
public:

   
   enum e_message
   {
      message_none,
      message_ok,
      message_failed,
      message_unknown,
   };


   e_message                  m_emessage;
   HANDLE                     m_hmutexSpabootInstall;
   small_ipc_rx_channel       m_rxchannel;
   
   char *                     m_modpath;
   char *                     m_pszDllEnds;
   DWORD *                    m_dwaProcess;
   int                        m_iSizeProcess;
   HMODULE *                  m_hmodulea;
   int                        m_iSizeModule;
   bool                       m_bInstallerInstalling;

   installer();
   virtual ~installer();
   
   void install_defer_file_transfer();

   bool is_user_using(const char * pszDll);

   ATOM spaboot_message_register_class(HINSTANCE hInstance);

   int cube_run(const char * id);

   void execute_sync(SHELLEXECUTEINFOA * pinfoa);

   void call_self_privileged_sync(const char * param);

   int spaboot_registry_register(const char * lpszFile);

   void call_sync(const char * path, const char * param);

   void installer_call_sync(const char * path, const char * param);

   bool are_there_user_files_in_use();

   bool is_user_using(DWORD processid, const char * pszDll);

   virtual void on_receive(const char * pszMessage);

   virtual bool initialize();

   virtual bool finalize();

};




extern "C" void WinMainCRTStartup()
{

   class installer installer;

   installer.main();

}


extern bool g_bInstalling;

installer::installer()
{
   m_hinstance             = ::GetModuleHandleA(NULL);
   m_hmutexSpabootInstall  = NULL;
   e_message m_emessage    = message_none;
   m_modpath               = NULL;
   m_pszDllEnds            = NULL;
   m_dwaProcess            = NULL;
   m_iSizeProcess          = 0;
   m_hmodulea              = NULL;
   m_iSizeModule           = 0;
   m_bInstallerInstalling  = false;
}

installer::~installer()
{
}

bool installer::initialize()
{

   m_hmutexSpabootInstall = ::CreateMutex(NULL, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spaboot_install::7807e510-5579-11dd-ae16-0800200c7784");
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      m_iReturn = 202;
      return false;
   }

   installation_file_lock(false);

   //Sleep(15 * 1000);

   m_modpath      = (char *) ca2_alloc(MAX_PATH * 8);
   m_pszDllEnds   = (char *) ca2_alloc(MAX_PATH * 8);
   m_iSizeProcess = 1024;
   m_dwaProcess   = (DWORD *) ca2_alloc(m_iSizeProcess);
   m_iSizeModule  = 1024;
   m_hmodulea     = (HMODULE *) ca2_alloc(m_iSizeModule);

   m_rxchannel.m_preceiver = this;

   prepare_small_bell();

   if(!m_rxchannel.create("ca2/fontopus/ccvotagus/spaboot_install", "installer.exe"))
   {
      m_iReturn = -1;
      return false;
   }

   return true;

}

void installer::install_defer_file_transfer()
{
   if(!g_bInstalling)
   {
      update_updated();
      if(!is_updated() && !are_there_user_files_in_use())
      {
         synch_spaadmin("starter_start=bergedge in background in spa");
      }
   }
}


typedef int (__cdecl * PFN_SPAADMIN_MAIN)(const char * pszCommandLine);


// non-thread safe
bool installer::is_user_using(DWORD processid, const char * pszDll)
{

   HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
   MODULEENTRY32 me32;
   bool bFound = false;

   hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, processid );
   if( hModuleSnap == INVALID_HANDLE_VALUE )
   {
      return false;
   }

   me32.dwSize = sizeof(MODULEENTRY32);

   if(!Module32First(hModuleSnap, &me32))
   {
      ::CloseHandle(hModuleSnap);
      return false;
   }

   strcpy_dup(m_pszDllEnds, "\\");
   strcat_dup(m_pszDllEnds, pszDll);

   do
   {
      if(str_ends_ci_dup(me32.szModule, m_pszDllEnds) || stricmp_dup(me32.szModule, pszDll) == 0)
      {
         bFound = true;
         break;
      }

   }
   while(Module32Next(hModuleSnap, &me32));

   ::CloseHandle( hModuleSnap );
   return bFound;

}

// non-thread safe
bool installer::is_user_using(const char * pszDll)
{
   HANDLE hProcessSnap;
   PROCESSENTRY32 pe32;

   hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
   if(hProcessSnap == INVALID_HANDLE_VALUE)
   {
      return false;
   }
   
   pe32.dwSize = sizeof(PROCESSENTRY32);

   if(!Process32First(hProcessSnap, &pe32))
   {
      ::CloseHandle(hProcessSnap);
      return false;
   }

   bool bUsing = false;
   do
   {
      if(is_user_using(pe32.th32ProcessID, pszDll))
      {
         bUsing = true;
         break;
      }
   }
   while(Process32Next(hProcessSnap, &pe32));

  ::CloseHandle(hProcessSnap);

  return bUsing;

}

void installer::on_receive(const char * pszMessage)
{
   vsstring strMessage(pszMessage);
   int iRet = 0;
   const char * pszSuffix;
   if((pszSuffix = str_begins_inc_dup(strMessage, "synch_spaadmin:")) != NULL)
   {
      if(g_bInstalling)
      {
         iRet = 1;
         return;
      }
      if(m_bInstallerInstalling)
      {
         iRet = 1;
         return;
      }
      m_bInstallerInstalling = true;
      synch_spaadmin(pszSuffix);
      m_bInstallerInstalling = false;
   }
   else if((pszSuffix = str_begins_inc_dup(strMessage, "spaadmin:")) != NULL)
   {
      if(g_bInstalling)
      {
         iRet = 1;
         return;
      }
      //if(m_bInstallerInstalling)
      //{
        // iRet = 1;
         //return;
      //}
      //m_bInstallerInstalling = true;
      start_spaadmin(pszSuffix);
   }
   else if(stricmp_dup(strMessage, "ok") == 0)
   {
      m_emessage = message_ok;
   }
   else if(stricmp_dup(strMessage, "failed") == 0)
   {
      m_emessage = message_failed;
   }
   else if(stricmp_dup(strMessage, "exit") == 0)
   {
      PostQuitMessage(0);
   }
   else if(stricmp_dup(strMessage, "quit") == 0)
   {
      PostQuitMessage(0);
   }
   else
   {
      m_emessage = message_unknown;
   }
}



bool installer::are_there_user_files_in_use()
{
#ifdef _X86_
   if(is_user_using(dir::ca2("stage\\x86\\msvcp100d.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x86\\msvcr100d.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x86\\c.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x86\\ca.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x86\\ca2.dll")))
      return true;
#else
   if(is_user_using(dir::ca2("stage\\x64\\msvcp100d.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x64\\msvcr100d.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x64\\c.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x64\\ca.dll")))
      return true;
   if(is_user_using(dir::ca2("stage\\x64\\ca2.dll")))
      return true;
#endif
   return false;
}


bool installer::finalize()
{

   simple_app::finalize();

   ca2_free(m_hmodulea);
   ca2_free(m_dwaProcess);
   ca2_free(m_pszDllEnds);
   ca2_free(m_modpath);

   return true;

}








simple_app::simple_app()
{
   //Sleep(15 * 1000);

   
   __argc = _init_args();
	__targv = _argv;
	_init_file();

	TCHAR *cmd = GetCommandLine();

	// Skip program name
	if (*cmd == _T('"'))
	{
	    while (*cmd && *cmd != _T('"'))
	        cmd++;
	    if (*cmd == _T('"'))
	        cmd++;
	}
	else
	{
	    while (*cmd > _T(' '))
	        cmd++;
	}

	// Skip any white space
	while (*cmd && *cmd <= _T(' '))
	    cmd++;

	STARTUPINFO si;
	si.dwFlags = 0;
	GetStartupInfo(&si);

   initialize_primitive_heap();


	_init_atexit();
	_initterm(__xc_a, __xc_z);			// call C++ constructors

}

simple_app::~simple_app()
{
   
   finalize_primitive_heap();

	_doexit();
	_term_args();
	ExitProcess(m_iReturn);

}


void simple_app::main()
{
   if(__argc >= 2)
   {
     if(!strncmp_dup(__argv[1], "-install=", strlen_dup("-install=")))
     {
        Sleep(15 * 1000);
         vsstring id = &__argv[1][strlen_dup("-install=")];
         DWORD dwStartError;
         spa::ca2_app_install_run(id, "", "install", dwStartError, true);
         finalize();
         return;
     }
   }

   if(!initialize())
      return;
   m_iReturn = run();
   finalize();
}

bool simple_app::initialize()
{
   return true;
}

int simple_app::run()
{

	while(true)
	{
      GetMessage(&m_msg, NULL, 0, 0xffffffffu);
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}

   return 0;
}

bool simple_app::finalize()
{
   return true;
}
