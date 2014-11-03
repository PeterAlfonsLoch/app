#include "framework.h"
#include "windows.h"
#include "aura/graphics/draw2d/draw2d.h"



#include <Wtsapi32.h>
#include <Psapi.h>
#include <WinCred.h>

CLASS_DECL_AURA HBITMAP get_icon_hbitmap(HICON hICON);

namespace windows
{


   os::os(sp(::aura::application) papp) :
      element(papp),
      ::aura::os(papp)
   {
   }


   os::~os()
   {
   }


   bool os::shutdown(bool bIfPowerOff)
   {
      bool retval = true;
      HANDLE hToken;
      TOKEN_PRIVILEGES tkp;
      if (!OpenProcessToken(GetCurrentProcess(),
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      if (bIfPowerOff)
         retval = ExitWindowsEx(EWX_POWEROFF, 0) != FALSE;
      else
         retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != FALSE;

      //reset the previlages
      tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      return retval;
   }

   bool os::reboot()
   {
      HANDLE hToken;
      TOKEN_PRIVILEGES tkp;
      if (!OpenProcessToken(GetCurrentProcess(),
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      if(!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }
      if(!LookupPrivilegeValue(NULL, SE_REMOTE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }


      if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE, WTS_WSD_REBOOT))
      {
         TRACELASTERROR();
         return false;
      }
      /*if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 
      SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      {
      DWORD dwLastError = ::GetLastError();
      return false;
      }*/
      //reset the previlages
      tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      return true;
   }

   void os::terminate_processes_by_title(const char * pszName)
   {
      DWORD dwPid;
      while(get_pid_by_title(pszName, dwPid))
      {
         HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ,
            FALSE, dwPid );
         TerminateProcess(hProcess, (UINT) -1);
         CloseHandle(hProcess);
         /*::EnumWindows((WNDENUMPROC)
         CKillProcessHelper::TerminateAppEnum, 
         (LPARAM) dwId);
         // Wait on the handle. If it signals, great. 

         //If it times out, then you kill it.

         if(WaitForSingleObject(hProcess, 5000)
         !=WAIT_OBJECT_0)
         bResult = TerminateProcess(hProcess,0);
         else
         bResult = TRUE; 
         CloseHandle(hProcess);
         return bResult == TRUE;*/

      }
   }

   bool os::get_pid_by_path(const char * pszName, DWORD & dwPid)
   {
      uint_array dwa;
      get_all_processes(dwa);
      for(int32_t i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).CompareNoCase(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   bool os::get_pid_by_title(const char * pszName, DWORD & dwPid)
   {
      uint_array dwa;
      get_all_processes(dwa);
      for(int32_t i = 0; i < dwa.get_count(); i++)
      {
         if(Application.file_title(get_process_path(dwa[i]))
            .CompareNoCase(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   string os::get_process_path(DWORD dwPid)
   {
      string strName = ":<unknown>";
      // get a handle to the process.
      HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
         PROCESS_VM_READ,
         FALSE, dwPid );

      // get the process name.

      if (NULL != hProcess )
      {
         HMODULE hMod;
         DWORD cbNeeded;

         if(EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
            &cbNeeded) )
         {
            strName = get_module_path(hMod);
         }
      }

      CloseHandle( hProcess );
      return strName;
   }

   void os::get_all_processes(uint_array & dwa )
   {
      dwa.allocate(0);
      DWORD cbNeeded = 0;
      while(cbNeeded == natural(dwa.get_count()))
      {
         dwa.allocate(dwa.get_count() + 1024);
         if(!EnumProcesses(
            (DWORD *) dwa.get_data(), 
            (DWORD) (dwa.get_count() * sizeof(DWORD)),
            &cbNeeded))
         {
            return;
         }
         dwa.allocate(cbNeeded / sizeof(DWORD));
      }
   }

   string os::get_module_path(HMODULE hmodule)
   {
      wstring wstrPath;
      DWORD dwSize = 1;
      while(natural(wstrPath.get_length() + 1) == dwSize)
      {
         dwSize = ::GetModuleFileNameW(
            hmodule,
            wstrPath.alloc(dwSize + 1024),
            (dwSize + 1024));
         wstrPath.release_buffer();
      }
      return ::str::international::unicode_to_utf8(wstrPath);
   }


   bool os::connection_settings_get_auto_detect()
   {

      registry::Key key1;

      key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

      primitive::memory mem;

      key1.QueryValue("DefaultConnectionSettings", mem);

      bool bAutoDetect = (((LPBYTE) mem.get_data())[8] & 0x08) != 0;

      return bAutoDetect;

   }


   string os::connection_settings_get_auto_config_url()
   {

      registry::Key key;

      key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

      string strUrl;

      key.QueryValue("AutoConfigURL", strUrl);

      return strUrl;

   }

   bool os::local_machine_set_run(const char * pszKey, const char * pszCommand)
   {


      registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


      keyKar.SetValue(pszKey, pszCommand);


      return true;

   }


   bool os::local_machine_set_run_once(const char * pszKey, const char * pszCommand)
   {


      registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


      keyKar.SetValue(pszKey, pszCommand);


      return false;

   }

   bool os::current_user_set_run(const char * pszKey, const char * pszCommand)
   {


      registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


      keyKar.SetValue(pszKey, pszCommand);


      return false;

   }

   bool os::current_user_set_run_once(const char * pszKey, const char * pszCommand)
   {


      registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


      keyKar.SetValue(pszKey, pszCommand);


      return false;

   }


   bool os::defer_register_ca2_plugin_for_mozilla()
   {

      registry::Key keyPlugins;

      if(keyPlugins.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
      {

         registry::Key keyPlugin;

         if(keyPlugin.OpenKey(keyPlugins, "@ca2.cc/npca2", true))
         {

            keyPlugin.SetValue("Description", "core plugin for NPAPI");
            keyPlugin.SetValue("Path", System.dir_ca2module("npca2.dll"));
            keyPlugin.SetValue("ProductName", "core plugin for NPAPI");
            keyPlugin.SetValue("Vendor", "core Desenvolvimento de Software Ltda.");
            keyPlugin.SetValue("Version", Application.file_as_string(System.dir_element("appdata/x86/ca2_build.txt")));

            registry::Key keyApplicationCa2;

            if(keyApplicationCa2.OpenKey(keyPlugin, "application/core", true))
            {

               keyApplicationCa2.SetValue("Description", "core Document");

            }

         }

      }

      return true;

   }

   bool os::file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension)
   {

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      string strOpenWithKey;
      strOpenWithKey = strExt + "\\OpenWithList";

      registry::Key key;

      key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);

      key.EnumKey(straKey);

      return true;

   }


   bool os::file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension)
   {

      stringa straKey;

      if(!file_extension_get_open_with_list_keys(straKey, pszExtension))
         return false;


      return true;

   }

   bool os::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {


      string strExtensionNamingClass(pszExtensionNamingClass);

      registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
      keyLink3.SetValue("DefaultIcon", pszIconPath);


      return false;

   }


   bool os::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      string strExtensionNamingClass(pszExtensionNamingClass);

      registry::Key key(HKEY_CLASSES_ROOT, strExt, true);
      key.SetValue(NULL, strExtensionNamingClass);

      registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);
      keyLink3.SetValue(NULL, "open");

      registry::Key keyLink2(keyLink3, "open", true);
      keyLink2.SetValue(NULL, "&Abrir");

      registry::Key keyLink1(keyLink2, "command", true);

      string strFormat;
      strFormat.Format("\"%s\" \"%%L\" %s", pszCommand, pszParam);
      keyLink1.SetValue(NULL, strFormat);

      return true;

   }

   bool os::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      registry::Key key(HKEY_CLASSES_ROOT, strExt, false);
      if(!key.QueryValue(NULL, strExtensionNamingClass))
         return false;

      registry::Key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

      string strFormat;
      if(keyLink.QueryValue(NULL, strFormat))
      {

         const char * psz = strFormat;

         try
         {

            strCommand = ::str::consume_quoted_value(psz);
            ::str::consume_spaces(psz);
            ::str::consume(psz, "\"%L\"");
            strParam = psz;

         }
         catch(...)
         {
         }


      }

      return true;

   }

   bool os::open_in_ie(const char * lpcsz)
   {

      registry reg;
      string str;
      string str2;
      string strCommand;
      registry::Key key;
      if(key.OpenKey(HKEY_CLASSES_ROOT, ".html", false))
      {
         if(reg.RegQueryValue(key.m_hkey, "", str))
         {
            if(key.OpenKey(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
            {
               string str;
               if(reg.RegQueryValue(HKEY_CLASSES_ROOT, str, str2))
               {
                  string strCommand(str2);
                  strCommand.replace("%1", lpcsz);
                  WinExec(strCommand,SW_SHOW);
               }
            }
            else
            {
               if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
               {
                  str += "\\shell\\opennew\\command";
                  if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
                  {
                     if(reg.RegQueryValue(key.m_hkey, "", str2))
                     {
                        string strCommand(str2);
                        strCommand.replace("%1", lpcsz);
                        WinExec(strCommand,SW_SHOW);
                     }
                  }
               }
            }
         }
      }

      return true;

   }


   //------------------------------------------------------------------------
   // The following function retrieves the identity of the current user.
   // This is a helper function and is not part of the Windows Biometric
   // Framework API.
   //
   struct TOKEN_INFO{
      TOKEN_USER tokenUser;
      BYTE buffer[SECURITY_MAX_SID_SIZE];
   };
   HRESULT GetCurrentUserIdentity(TOKEN_INFO & tokenInfo)
   {
      // Declare variables.
      bool bOk = true;
      HANDLE tokenHandle = NULL;
      DWORD bytesReturned = 0;


      // Open the access token associated with the
      // current process
      if(!OpenProcessToken(
         GetCurrentProcess(),            // Process handle
         TOKEN_READ,                     // Read access only
         &tokenHandle))                  // Access token handle
      {
         DWORD win32Status = GetLastError();
         printf("Cannot open token handle: %d\n",win32Status);
         bOk = false;
      }

      // Zero the tokenInfoBuffer structure.
      ZeroMemory(&tokenInfo,sizeof(tokenInfo));

      // Retrieve information about the access token. In this case,
      // retrieve a SID.
      if(!GetTokenInformation(
         tokenHandle,                    // Access token handle
         TokenUser,                      // User for the token
         &tokenInfo.tokenUser,     // Buffer to fill
         sizeof(tokenInfo),        // Size of the buffer
         &bytesReturned))                // Size needed
      {
         DWORD win32Status = GetLastError();
         printf("Cannot query token information: %d\n",win32Status);
         bOk = false;
      }

      if(tokenHandle != NULL)
      {
         CloseHandle(tokenHandle);
      }

      return bOk;
   }
   BOOL
      GetAccountSid(
      LPTSTR SystemName,
      LPTSTR AccountName,
      PSID *Sid
      )
   {
      LPTSTR ReferencedDomain=NULL;
      DWORD cbSid=128;    // initial allocation attempt
      DWORD cchReferencedDomain=16; // initial allocation size
      SID_NAME_USE peUse;
      BOOL bSuccess=FALSE; // assume this function will fail

      __try {

         // 
         // initial memory allocations
         // 
         if((*Sid=HeapAlloc(
            GetProcessHeap(),
            0,
            cbSid
            )) == NULL) __leave;

         if((ReferencedDomain=(LPTSTR)HeapAlloc(
            GetProcessHeap(),
            0,
            cchReferencedDomain * sizeof(TCHAR)
            )) == NULL) __leave;

         // 
         // Obtain the SID of the specified account on the specified system.
         // 
         while(!LookupAccountName(
            SystemName,         // machine to lookup account on
            AccountName,        // account to lookup
            *Sid,               // SID of interest
            &cbSid,             // size of SID
            ReferencedDomain,   // domain account was found on
            &cchReferencedDomain,
            &peUse
            )) {
            if(GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
               // 
               // reallocate memory
               // 
               if((*Sid=HeapReAlloc(
                  GetProcessHeap(),
                  0,
                  *Sid,
                  cbSid
                  )) == NULL) __leave;

               if((ReferencedDomain=(LPTSTR)HeapReAlloc(
                  GetProcessHeap(),
                  0,
                  ReferencedDomain,
                  cchReferencedDomain * sizeof(TCHAR)
                  )) == NULL) __leave;
            }
            else __leave;
         }

         // 
         // Indicate success.
         // 
         bSuccess=TRUE;

      } // finally
      __finally {

         // 
         // Cleanup and indicate failure, if appropriate.
         // 

         HeapFree(GetProcessHeap(),0,ReferencedDomain);

         if(!bSuccess) {
            if(*Sid != NULL) {
               HeapFree(GetProcessHeap(),0,*Sid);
               *Sid = NULL;
            }
         }

      } // finally

      return bSuccess;
   }























   bool getCredentialsForService(sp(::aura::application) papp, const string & strService,WCHAR * szUsername,WCHAR *szPassword)
   {


      HRESULT hr = S_OK;
      DWORD   dwResult;
      PVOID   pvInAuthBlob = NULL;
      ULONG   cbInAuthBlob = 0;
      PVOID   pvAuthBlob = NULL;
      ULONG   cbAuthBlob = 0;
      CREDUI_INFOW ui;
      ULONG   ulAuthPackage = 0;
      BOOL    fSave = FALSE;
      WCHAR szDomainAndUser[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR szDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      TOKEN_INFO ti;

      DWORD maxLenName = CREDUI_MAX_USERNAME_LENGTH + 1;
      DWORD maxLenPass = CREDUI_MAX_PASSWORD_LENGTH + 1;
      DWORD maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      HICON hicon = NULL;


      // Display a dialog box to request credentials.
      ZERO(ui);
      ui.cbSize = sizeof(ui);
      ui.hwndParent = NULL;



      // Retrieve the user name and domain name.
      SID_NAME_USE    SidUse;
      DWORD           cchTmpUsername = CREDUI_MAX_USERNAME_LENGTH +1;
      DWORD           cchTmpDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;
      DWORD           cchDomainAndUser = CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      wstring wstrCaption("\"ca2 : " + strService + "\" Authentication");
      wstring wstrMessage("The Service \"ca2 : " + strService + "\" requires current user password for installing Windows Service.");

      DWORD lenUserName = CREDUI_MAX_USERNAME_LENGTH + 1;

         //::GetUserNameW(szUsername,&lenUserName);


      DWORD dwLastError = 0;



      bool bOk;


      //if(!GetCurrentUserIdentity(ti))
      //   return false;
      ////szDomain[0] ='.';
      ////         szDomain[1] ='\0';
      //if(!LookupAccountSidW(
      //   NULL,             // Local computer
      //   ti.tokenUser.User.Sid,             // Security identifier for user
      //   szUsername,       // User name
      //   &cchTmpUsername,  // Size of user name
      //   szDomain,         // Domain name
      //   &cchTmpDomain,    // Size of domain name
      //   &SidUse))         // Account type
      //{
      //   dwResult = GetLastError();
      //   printf("\n getCredentialsForService LookupAccountSidLocalW failed: win32 error = 0x%x\n",dwResult);
      //   return false;
      //}

      ULONG l = sizeof(szDomainAndUser) / sizeof(WCHAR);

      ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

      // Combine the domain and user names.
      /*swprintf_s(
         szDomainAndUser,
         cchDomainAndUser,
         L"%s\\%s",
         szDomain,
         szUsername);*/
      zero(szPassword,CREDUI_MAX_PASSWORD_LENGTH);

      // Call CredPackAuthenticationBufferW once to determine the size,
      // in bytes, of the authentication buffer.
      if(!CredPackAuthenticationBufferW(
         0,                // Reserved
         szDomainAndUser,  // Domain\User name
         szPassword,       // User Password
         NULL,             // Packed credentials
         &cbInAuthBlob)    // Size, in bytes, of credentials
         && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
      {
         dwResult = GetLastError();
         printf("\n getCredentialsForService CredPackAuthenticationBufferW (1) failed: win32 error = 0x%x\n",dwResult);
         return false;
      }

      // Allocate memory for the input buffer.
      pvInAuthBlob = CoTaskMemAlloc(cbInAuthBlob);
      if(!pvInAuthBlob)
      {
         cbInAuthBlob = 0;
         printf("\n getCredentialsForService CoTaskMemAlloc() Out of memory.\n");
         return false;
      }

      // Call CredPackAuthenticationBufferW again to retrieve the
      // authentication buffer.
      if(!CredPackAuthenticationBufferW(
         0,
         szDomainAndUser,
         szPassword,
         (PBYTE)pvInAuthBlob,
         &cbInAuthBlob))
      {
         dwResult = GetLastError();
         printf("\n CredPackAuthenticationBufferW (2) failed: win32 error = 0x%x\n",dwResult);
      }


      ui.pszCaptionText = wstrCaption;
      ui.pszMessageText = wstrMessage;
      hicon = (HICON) ::LoadImageW(::GetModuleHandle(NULL),MAKEINTRESOURCEW(1),IMAGE_ICON,48,48,LR_DEFAULTCOLOR);


      if(hicon != NULL)
      {

         ui.hbmBanner = get_icon_hbitmap(hicon);

         ::DeleteObject(hicon);

      }

   retry:

      dwResult = CredUIPromptForWindowsCredentialsW(
         &ui,             // Customizing information
         dwLastError,               // Error code to display
         &ulAuthPackage,  // Authorization package
         pvInAuthBlob,    // Credential byte array
         cbInAuthBlob,    // Size of credential input buffer
         &pvAuthBlob,     // Output credential byte array
         &cbAuthBlob,     // Size of credential byte array
         &fSave,          // Select the save check box.
         //CREDUIWIN_SECURE_PROMPT |
         CREDUIWIN_IN_CRED_ONLY |
         CREDUIWIN_ENUMERATE_CURRENT_USER
         );

      
      if(dwResult == NO_ERROR)
      {

         DWORD lenName = maxLenName;
         DWORD lenDomain = maxLenDomain;
         DWORD lenPass = maxLenPass;

         bOk = CredUnPackAuthenticationBufferW(CRED_PACK_PROTECTED_CREDENTIALS,
            pvAuthBlob,
            cbAuthBlob,
            szUsername,
            &lenName,
            szDomain,
            &lenDomain,
            szPassword,
            &lenPass) != FALSE;
      
         SecureZeroMemory(pvAuthBlob,cbAuthBlob);
         CoTaskMemFree(pvAuthBlob);
         pvAuthBlob = NULL;
         cbAuthBlob = 0;

         if(!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         //wcscpy(szDomainAndUser,szUsername);

         ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

         bOk = CredUIParseUserNameW(
            szDomainAndUser,
            szUsername,
            CREDUI_MAX_USERNAME_LENGTH,
            szDomain,
            CREDUI_MAX_DOMAIN_TARGET_LENGTH
            ) == NO_ERROR ;

         if(!bOk)
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         HANDLE h;



         if(::LogonUserW(
            szUsername,
            szDomain,
            szPassword,
            LOGON32_LOGON_SERVICE,
            LOGON32_PROVIDER_DEFAULT,
            &h))
         {
            ::CloseHandle(h);
         }
         else
         {
            dwLastError = ::GetLastError();
            goto retry;
         }

         wcscpy(szUsername,szDomainAndUser);
           

      }
      else
      {

         if(dwResult != ERROR_CANCELLED)
            goto retry;

         hr = HRESULT_FROM_WIN32(dwResult);
         bOk = false;
      }

      if(pvInAuthBlob)
      {
         SecureZeroMemory(pvInAuthBlob,cbInAuthBlob);
         CoTaskMemFree(pvInAuthBlob);
         pvInAuthBlob = NULL;
      }

      if(ui.hbmBanner != NULL)
      {

         ::DeleteObject(ui.hbmBanner);

      }

      return bOk;

   }








































   bool os::create_service(sp(::aura::application) papp)
   {

      if(papp->m_strAppName.is_empty()
         || papp->m_strAppName.CompareNoCase("bergedge") == 0
         || !papp->is_serviceable())
         return false;


      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_CREATE_SERVICE);

      if(hdlSCM == 0)
      {
         //::GetLastError()
         return false;
      }

      string strServiceName = "ca2-" + papp->m_strAppId;

      strServiceName.replace("/", "-");
      strServiceName.replace("\\", "-");
      //strServiceName.replace("-", "_");

      string strDisplay(strServiceName);

      strDisplay.replace("-"," ");

      string strExe(strServiceName);

      strExe.replace("-","_");

      strExe += ".exe";

      string strCalling = System.dir_path(Sys(papp).m_strModuleFolder, strExe) + " : service";

      WCHAR * pname = NULL;
      WCHAR * ppass = NULL;

      WCHAR pszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      //if(App(papp).is_user_service())
      {

         if(getCredentialsForService(papp, papp->m_strAppId,pszName,pszPass))
         {

            pname = pszName;
            ppass = pszPass;

         }
         else
         {

            return false;

         }

      }

      SC_HANDLE hdlServ = ::CreateServiceW(
         hdlSCM,                    // SCManager database 
         wstring(strServiceName),
         wstring(strDisplay),        // service name to display 
         STANDARD_RIGHTS_REQUIRED,  // desired access 
         SERVICE_WIN32_OWN_PROCESS, // service type 
         SERVICE_AUTO_START,      // start type 
         SERVICE_ERROR_NORMAL,      // error control type 
         wstring(strCalling),                   // service's binary Path name
         0,                      // no load ordering group 
         0,                      // no tag identifier 
         0,                      // no dependencies 
         pname,                      // LocalSystem account 
         ppass);                     // no password 


      if(!hdlServ)
      {
         DWORD Ret = ::GetLastError();
         TRACELASTERROR();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SecureZeroMemory(pszName,sizeof(pszName));
      SecureZeroMemory(pszPass,sizeof(pszPass));


      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return true;

   }


   bool os::remove_service(sp(::aura::application) papp)
   {

      if(papp->m_strAppName.is_empty()
         || papp->m_strAppName.CompareNoCase("bergedge") == 0
         || !papp->is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }
      string strServiceName = "ca2-" + papp->m_strAppId;

      strServiceName.replace("/","-");
      strServiceName.replace("\\","-");
      //WCHAR * pname = NULL;
      //WCHAR * ppass = NULL;

      //WCHAR pszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      //WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      //if(App(papp).is_user_service())
      //{

      //   if(getCredentialsForService(papp,papp->m_strAppId,pszName,pszPass))
      //   {

      //      pname = pszName;
      //      ppass = pszPass;

      //   }
      //   else
      //   {

      //      return false;

      //   }

      //}


      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database 
         wstring(strServiceName),
         DELETE);

      if(!hdlServ)
      {
         DWORD Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         if(Ret == 1060) // O serviço já não existe. Service already doesn't exist.
            return true; // do self-healing
         return false;
      }

      if(!::DeleteService(hdlServ))
      {
         DWORD Ret = ::GetLastError();
         CloseServiceHandle(hdlServ);
         CloseServiceHandle(hdlSCM);
         return false;
      }

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return true;

   }

   bool os::start_service(sp(::aura::application) papp)
   {

      if(papp->m_strAppName.is_empty()
         || papp->m_strAppName.CompareNoCase("bergedge") == 0
         || !papp->is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }

      string strServiceName = "ca2-" + papp->m_strAppId;

      strServiceName.replace("/", "-");
      strServiceName.replace("\\", "-");

      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database 
         wstring(strServiceName),
         SERVICE_START);                     // no password 


      if (!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::GetLastError();
         return FALSE;
      }

      bool bOk = StartService(hdlServ, 0, NULL) != FALSE;

      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }

   bool os::stop_service(sp(::aura::application) papp)
   {

      if(papp->m_strAppName.is_empty()
         || papp->m_strAppName.CompareNoCase("bergedge") == 0
         || !papp->is_serviceable())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::GetLastError();
         return false;
      }

      string strServiceName = "ca2-" + papp->m_strAppId;

      strServiceName.replace("/", "-");
      strServiceName.replace("\\", "-");

      SC_HANDLE hdlServ = ::OpenServiceW(
         hdlSCM,                    // SCManager database 
         wstring(strServiceName),
         SERVICE_STOP);                     // no password 

      if (!hdlServ)
      {
         // Ret = ::GetLastError();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SERVICE_STATUS ss;

      memset(&ss, 0, sizeof(ss));

      bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != FALSE;

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }


   DECLSPEC_NO_RETURN void os::raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags)
   {
      RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
   }

   bool os::is_remote_session()
   {

      return GetSystemMetrics(SM_REMOTESESSION) != FALSE;

   }




   void os::set_file_status(const char * lpszFileName, const ::file::file_status& status)
   {

      DWORD wAttr;
      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME lpCreationTime = NULL;
      LPFILETIME lpLastAccessTime = NULL;
      LPFILETIME lpLastWriteTime = NULL;

      wstring wstr(lpszFileName);

      if((wAttr = GetFileAttributesW(wstr)) == (DWORD)-1L)
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());

      }

      if ((DWORD)status.m_attribute != wAttr && (wAttr & ::windows::file::readOnly))
      {

         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         if (!SetFileAttributesW(wstr, (DWORD)status.m_attribute))
         {

            ::windows::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());

         }

      }

      // last modification time
      if (status.m_mtime.get_time() != 0)
      {

         ::windows::TimeToFileTime(get_app(), status.m_mtime, &lastWriteTime);

         lpLastWriteTime = &lastWriteTime;

      }

      // last access time
      if (status.m_atime.get_time() != 0)
      {

         ::windows::TimeToFileTime(get_app(),status.m_atime, &lastAccessTime);

         lpLastAccessTime = &lastAccessTime;

      }

      // create time
      if (status.m_ctime.get_time() != 0)
      {

         ::windows::TimeToFileTime(get_app(),status.m_ctime, &creationTime);

         lpCreationTime = &creationTime;

      }

      HANDLE hFile = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      if(hFile == INVALID_HANDLE_VALUE)
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());

      }

      if(!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());

      }

      if(!::CloseHandle(hFile))
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::GetLastError());

      }

      if ((DWORD)status.m_attribute != wAttr && !(wAttr & ::windows::file::readOnly))
      {

         if (!::SetFileAttributesW(wstr, (DWORD)status.m_attribute))
         {

            ::windows::file_exception::ThrowOsError(get_app(), (LONG)GetLastError());

         }

      }

   }


} // namespace windows



