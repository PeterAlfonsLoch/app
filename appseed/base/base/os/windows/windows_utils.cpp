#include "framework.h"
#include <Winsvc.h>

const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

// Function resolves the fosedevice name to drive name
bool GetDrive( LPCTSTR pszDosName, string& csDrive, bool bDriveLetterOnly )
{
	TCHAR tcDeviceName[50];
	TCHAR tcDrive[3] = _T("A:");

	// Iterating through the drive letters
	for ( TCHAR actDrive = _T('A'); actDrive <= _T('Z'); actDrive++ )
	{
		tcDrive[0] = actDrive;
		// Query the device for the drive letter
		if ( QueryDosDevice( tcDrive, tcDeviceName, 50 ) != 0 )
		{
            // Is this the drive letter we are looking for?
			if ( _tcsnicmp( tcDeviceName, pszDosName, _tcslen( tcDeviceName ) ) == 0 )
			{
                if( bDriveLetterOnly )
                {
                    csDrive = tcDrive;
                }
                else
                {
                    csDrive = pszDosName;
                    csDrive.replace( tcDeviceName, tcDrive );
                }
				return TRUE;
			}
		}
	}
	return FALSE;
}

//#ifdef _M_IX86
//#define DRVIER_ID IDR_XPDRIVER32
//#else
//#define DRVIER_ID IDR_XPDRIVER64
//#endif

//#ifdef _M_IX86
#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
//#else
#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")
//#endif

// This Function install the driver and starts it
HANDLE ExtractAndInstallDrv()
{
	SC_HANDLE hSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	SC_HANDLE hService = OpenService( hSCManager , DRV_NAME, SERVICE_ALL_ACCESS);
	string csPath;
	if( 0 == hService )
	{
		//Service not installed. So install the service.

		/*OSVERSIONINFO info = { 0 }; 
		info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&info); 
		int32_t nDriverId = IDR_VISTA_DRIVER;
		if( info.dwMajorVersion == 5 )
		{
			nDriverId = IDR_XPDRIVER;
		}*/


		/*// First extract the resource
		HINSTANCE hModule= __get_instance_handle();
		HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(DRVIER_ID),_T("BINARY"));
		HGLOBAL hDrvRsrc = LoadResource(hModule, hRsrc);
		uint32_t dwDriverSize = SizeofResource(hModule, hRsrc);
		LPVOID lpvDriver = LockResource(hDrvRsrc);
		CFile File;
        if( !File.Open( DRV_FILE_NAME, CFile::modeCreate|CFile::modeWrite ))
        {
            return 0;
        }
        File.Write( lpvDriver, dwDriverSize );
		csPath = File.GetFilePath();
		File.Close();*/
		

        HMODULE hModule = GetModuleHandle(_T("core.dll"));
        if( !hModule )
        {
            OutputDebugStringW( L"GetModuleHandle(_T(\"core.dll\")); failed" );
            return 0;
        }
        string csFilePath;
        LPTSTR lpPath = csFilePath.GetBuffer( MAX_PATH );
        GetModuleFileName( hModule,lpPath , MAX_PATH );
        PathRemoveFileSpec( lpPath );
        csFilePath.ReleaseBuffer();
        if(IsWow64())
        {
         csFilePath += DRIVER_FILE_NAME_64;
        }
        else
        {
           csFilePath += DRIVER_FILE_NAME_32;
        }
        
        if( !PathFileExists( csFilePath ))
        {
           simple_message_box(NULL,"Cannot find driver " + csFilePath,"Cannot find driver " + csFilePath,MB_OK);
            return 0;
        }



		hService = CreateService( hSCManager, DRV_NAME, DRV_NAME, SERVICE_ALL_ACCESS,
								  SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
								  csFilePath, NULL, NULL, NULL, NULL, NULL );
		
		if( 0 == hService )
		{
            OutputDebugStringW( L"CreateService failed");
			CloseServiceHandle(hSCManager);
			return 0;
		}
	}

	if( !StartService( hService, 0, NULL ))
	{
      uint32_t dwLastError = GetLastError();
		if(dwLastError  != ERROR_SERVICE_ALREADY_RUNNING )
		{
			DeleteService(hService);
			CloseServiceHandle(hService);
			CloseServiceHandle(hSCManager);			
			//DeleteFile( csPath );
            OutputDebugStringW( L"StartService failed");
			return 0;
		}
		
	}
	// Delete the temp file...
	//DeleteFile( csPath );
	HANDLE hFile = CreateFile( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE, 
								FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
								OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
	if( INVALID_HANDLE_VALUE == hFile )
	{
		hFile = 0;
		SERVICE_STATUS  stSrvStatus = {0};
		ControlService( hService, SERVICE_CONTROL_STOP, &stSrvStatus );
	}	
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);
	return hFile;
}

// Function stops the service and then deletes it.
int_bool StopAndUninstallDrv( HANDLE hDrvHandle )
{
	CloseHandle( hDrvHandle );
	SC_HANDLE hSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS );
	SC_HANDLE hService = OpenService( hSCManager , DRV_NAME, SERVICE_ALL_ACCESS );
	SERVICE_STATUS  stSrvStatus = {0};
	ControlService( hService, SERVICE_CONTROL_STOP, &stSrvStatus );
	int_bool bDeleted = DeleteService(hService);
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCManager);	
	return bDeleted;
}




#ifdef WINDOWSEX

int_bool IsWow64()
{

   int_bool bIsWow64 = FALSE;

   if (!IsWow64Process(GetCurrentProcess(),&bIsWow64))
   {
      return FALSE;
   }

   return bIsWow64 != FALSE;

}

#endif







int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege)
{
	// do it only once
	static int_bool bEnabled = FALSE;
	if( bEnabled )
	{
		return TRUE;
	}
	bEnabled = TRUE;

    HANDLE hToken        = 0;
    TOKEN_PRIVILEGES tkp = {0}; 

    // Get a token for this process.
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES |
                          TOKEN_QUERY, &hToken))
    {
        return FALSE;
    }

    // Get the LUID for the privilege. 
    if(LookupPrivilegeValue(NULL, pszPrivilege,
                            &tkp.Privileges[0].Luid)) 
    {
        tkp.PrivilegeCount = 1;  // one privilege to set    
        tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        // set the privilege for this process. 
        AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
                              (PTOKEN_PRIVILEGES)NULL, 0); 

        if (GetLastError() != ERROR_SUCCESS)
           return FALSE;
        
        return TRUE;
    }

    return FALSE;
}


