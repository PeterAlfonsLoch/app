#include "StdAfx.h"
#include <shlwapi.h>




bool g_bAdmin = false;
e_version g_eversion = version_basis;


int bzuncompress_dup(LPCTSTR lpcszUncompressed, LPCTSTR lpcszGzFileCompressed);
bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
std::string get_temp_file_name_dup(const char * pszName, const char * pszExtension);
bool file_exists_dup(const char * path1);



HANDLE g_hmutexBoot = NULL;
std::string g_strId;
std::string g_strVersion;
DWORD g_dwPrepareSmallBell = 0;

void parse_spaboot(const char * psz);
bool parse_spaboot_start(const char * psz);
std::string read_resource_as_string(
   HINSTANCE hinst,
   UINT nID, 
   LPCTSTR lpcszType);

int gzuncompress(LPCTSTR lpcszUncompressed, LPCTSTR lpcszGzFileCompressed);
bool read_resource_as_file(
   const char * pszFile,
   HINSTANCE hinst,
   UINT nID, 
   LPCTSTR lpcszType);

std::string get_temp_file_name(const char * pszName, const char * pszExtension);

int start();

void prepare_small_bell();
void defer_play_small_bell();
void play_small_bell();

int APIENTRY ca2_cube_install(const char * pszId)
{
   g_hmutexBoot = NULL;
   SECURITY_ATTRIBUTES MutexAttributes;
   ZeroMemory( &MutexAttributes, sizeof(MutexAttributes) );
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
      {
         // Make the security attributes point
         // to the security descriptor
         MutexAttributes.lpSecurityDescriptor = &SD;
         g_hmutexBoot = ::CreateMutex(&MutexAttributes, FALSE, "Global\\ca2::fontopus::ccvotagus_ca2_spa_boot::7807e510-5579-11dd-ae16-0800200c7784");
         if(::GetLastError() == ERROR_ALREADY_EXISTS)
         {
            ::OutputDebugString("another instance of spa is already running");
            return -202;
         }
      }
      else
      {
         ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
         return -200;
      }
   }
   else
   {
      ::OutputDebugString("error when trying to analyze if another instance of spa is already running");
      return -201;
   }



   g_strVersion = "stage";
   g_eversion = version_stage;
   g_strId = pszId;

   std::string strSp = "C:\\ca2\\stage\\stage\\basis\\spaadmin.exe";


   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   SHELLEXECUTEINFO sei;
   memset(&sei, 0, sizeof(sei));
   sei.cbSize = sizeof(sei);
   sei.fMask = SEE_MASK_NOCLOSEPROCESS;
   sei.lpFile = strSp.c_str();
   sei.nShow = SW_SHOWNORMAL;
   std::string strParameters;

   strParameters = "starter_start=";
   strParameters += pszId;
   sei.lpParameters =  strParameters.c_str();

   if(!::ShellExecuteEx(&sei))
   {
      return 1;
   }

   if(g_eversion == version_stage)
      g_strVersion = "stage";
   else
      g_strVersion = "basis";

   DWORD dwExitCode;
   int i = 1;
   while(true)
   {
      if(!GetExitCodeProcess(sei.hProcess, &dwExitCode))
         break;
      if(dwExitCode != STILL_ACTIVE)
         break;
      Sleep(184);
      i++;
   }
   std::string strInstall;

   /*std::string strUrl;
   std::string strApp;
   strUrl = "http://spaignition.ca2api.net/query?node=install_application&id=";
   strUrl += g_strId;
   strUrl += "&key=application";
   int iRetry = 0;
   while(true)
   {
      strApp = ms_get(strUrl.c_str());
      if(strApp.length() > 0)
         break;
      iRetry++;
      if(iRetry > 30)
         break;
      Sleep(1984 + 1977);
   }
   if(iRetry > 30)
   {
      return 1;
   }*/

   return 0;
}




bool file_exists(const char * path1)
{
   DWORD dwFileAttributes = ::GetFileAttributes(path1);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;
}



void parse_spaboot(XNode & node)
{
   if(node.name == "spa" && node.childs.size() > 0)
   {
      LPXNode lpnode = &node;
      for(int i = 0; i < lpnode->childs.size(); i++)
      {
         if(lpnode->childs[i]->name == "index")
         {
            if(lpnode->childs[i]->GetAttr("start") != NULL)
            {
               if(std::string(lpnode->childs[i]->GetAttrValue("start")).length() > 0)
               {
                  g_strId= std::string(lpnode->childs[i]->GetAttrValue("start"));
               }
            }
         }
         if(lpnode->childs[i]->GetAttr("version") != NULL)
         {
            if(std::string(lpnode->childs[i]->GetAttrValue("version")).length() > 0)
            {
               if(std::string(lpnode->childs[i]->GetAttrValue("version")) == "stage")
               {
                  g_eversion = version_stage;
               }
               else
               {
                  g_eversion = version_basis;
               }
            }
         }
      }
   }
}

void parse_spaboot(const char * psz)
{
   XNode node;
   node.Load(file::get_contents(psz).c_str());
   parse_spaboot(node);
}

bool is_installed(const char * psz)
{
   XNode node;
   std::string str;
   if(g_eversion == version_stage)
   {
      if(!node.Load(file::get_contents("C:\\ca2\\stage\\appdata\\spa_install.xml").c_str()))
         return false;
   }
   else
   {
      if(!node.Load(file::get_contents("C:\\ca2\\basis\\appdata\\spa_install.xml").c_str()))
         return false;
   }
   XNode * pnodeInstalled = node.Find("installed");
   if(pnodeInstalled == NULL)
      return false;
   return pnodeInstalled->GetChildByAttr("application", "id", psz) != NULL;
}

bool parse_spaboot_start(XNode & node)
{
   int iOkCount = 0;
   std::string strInstalledBuild;
   std::string strRequestedBuild;
   if(node.name == "spa" && node.childs.size() > 0)
   {
      LPXNode lpnode = &node;
      for(int i = 0; i < lpnode->childs.size(); i++)
      {
         if(lpnode->childs[i]->name == "index")
         {
            if(lpnode->childs[i]->GetAttr("start") != NULL)
            {
               if(std::string(lpnode->childs[i]->GetAttrValue("start")).length() > 0)
               {
                  g_strId = std::string(lpnode->childs[i]->GetAttrValue("start"));
                  iOkCount++;
               }
               else
               {
                  return false;
               }
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
         if(lpnode->childs[i]->GetAttr("version") != NULL)
         {
            if(std::string(lpnode->childs[i]->GetAttrValue("version")).length() > 0)
            {
               if(std::string(lpnode->childs[i]->GetAttrValue("version")) == "stage")
               {
                  if(!file::exists("C:\\ca2\\stage\\app\\build.txt"))
                     return false;
                  iOkCount++;
                  g_eversion = version_stage;
               }
               else
               {
                  if(!file::exists("C:\\ca2\\basis\\app\\build.txt"))
                     return false;
                  iOkCount++;
                  g_eversion = version_basis;
               }
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
         if(lpnode->childs[i]->GetAttr("build") != NULL)
         {
            if(std::string(lpnode->childs[i]->GetAttrValue("build")).length() > 0)
            {
               if(g_eversion == version_stage)
               {
                  strInstalledBuild = file::get_contents("C:\\ca2\\stage\\app\\build.txt");
               }
               else
               {
                  strInstalledBuild = file::get_contents("C:\\ca2\\basis\\app\\build.txt");
                     return false;
               }
               if(strInstalledBuild.length() <= 0)
                  return false;
               strRequestedBuild = std::string(lpnode->childs[i]->GetAttrValue("build")).c_str();
               if(strRequestedBuild.length() <= 0)
                  return false;
               iOkCount++;
            }
            else
            {
               return false;
            }
         }
         else
         {
            return false;
         }
      }
   }
   if(iOkCount < 3)
      return false;
   if(strRequestedBuild != strInstalledBuild)
      return false;
   if(!is_installed(g_strId.c_str()))
      return false;
   if(g_eversion == version_stage)
      g_strVersion = "stage";
   else
      g_strVersion = "basis";
   return true;
}



bool parse_spaboot_start(const char * psz)
{
   XNode node;
   node.Load(file::get_contents(psz).c_str());
   return parse_spaboot_start(node);
}

void trace(const char * psz)
{
   printf("%s", psz);
}

int spaboot_start(const char * pszVersion, const char * pszId)
{
   STARTUPINFO si;
   PROCESS_INFORMATION pi;
   SHELLEXECUTEINFO sei;
   std::string strInstall;
   std::string strVersion = pszVersion;
   std::string strId = pszId;
   if(strId == "_set_windesk")
   {
      strInstall = "C:\\ca2\\" + strVersion + "\\stage\\basis\\";
      strInstall += "winservice_1app.exe";
      memset(&si, 0, sizeof(si));
      memset(&pi, 0, sizeof(pi));
      if(!::CreateProcess(NULL, (LPSTR)  strInstall.c_str(),
         NULL, NULL, FALSE, 0, NULL, NULL,
         &si, &pi))
      {
         return 1;
      }
   }
   else
   {
      strInstall = "C:\\ca2\\" + strVersion + "\\stage\\basis\\";
      strInstall += "bergedgeapp.exe";
      strInstall += " : ";
      strInstall += "app=";
      strInstall += strId;
      memset(&si, 0, sizeof(si));
      memset(&pi, 0, sizeof(pi));
      if(!::CreateProcess(NULL, (LPSTR)  strInstall.c_str(),
         NULL, NULL, FALSE, 0, NULL, NULL,
         &si, &pi))
      {
         return 1;
      }
   }
   
   return 0;
}



int bzuncompress_dup(LPCTSTR lpcszUncompressed, LPCTSTR lpcszGzFileCompressed)
{
   char * g_pchGzUncompressBuffer = NULL;
   int g_iGzUncompressLen = 1024 * 256;
   if(g_pchGzUncompressBuffer == NULL)
   {
       g_pchGzUncompressBuffer = new char[g_iGzUncompressLen];
   }
   BZFILE * file = BZ2_bzopen(lpcszGzFileCompressed, "rb");
   if (file == NULL)
   {
      fprintf(stderr, "bzopen error\n");
      return -2;
   }
   std::string strUn(lpcszUncompressed);
//   strUn += ".tmp";
   FILE * fileUn = fopen(strUn.c_str(), "wb+");
   if (fileUn == NULL)
   {
      BZ2_bzclose(file);
      int err;
      _get_errno(&err);
      fprintf(stderr, "fopen error\n %d", err);

      return -1;
   }
   int uncomprLen;
   while((uncomprLen = BZ2_bzread(file, g_pchGzUncompressBuffer, g_iGzUncompressLen)) > 0)
   {
      fwrite(g_pchGzUncompressBuffer, 1, uncomprLen, fileUn);
   }
   fclose(fileUn);
   BZ2_bzclose(file);
//   ::CopyFile(strUn.c_str(), lpcszUncompressed, FALSE);
//   ::DeleteFile(strUn.c_str());
   return 0;
}



bool read_resource_as_file_dup(
   const char * pszFile,
   HINSTANCE hinst,
   UINT nID, 
   LPCTSTR lpcszType)
{
	HRSRC hrsrc = ::FindResource(
		hinst,
		MAKEINTRESOURCE(nID), 
		lpcszType);
	if(hrsrc == NULL)
		return false;
    HGLOBAL hres = ::LoadResource(hinst, hrsrc);
	if(hres == NULL)
		return false;
    DWORD dwResSize = ::SizeofResource(hinst, hrsrc);

    if(hres != NULL)
    {
       bool bOk = false;
		UINT FAR* lpnRes = (UINT FAR*)::LockResource(hres);
      FILE * f  = fopen(pszFile, "wb");
      if(f != NULL)
      {
         fwrite(lpnRes, 1, dwResSize, f);
         fclose(f);
         bOk = true;
      }
		#ifndef WIN32 //Unlock Resource is obsolete in the Win32 API
			::UnlockResource(hres);
		#endif
            ::FreeResource(hres);
      return bOk;
	}
	return false;

}


std::string get_temp_file_name_dup(const char * pszName, const char * pszExtension)
{
   char lpPathBuffer[MAX_PATH * 16];
 // Get the temp path.
   DWORD dwRetVal = GetTempPath(sizeof(lpPathBuffer),     // length of the buffer
                        lpPathBuffer); // buffer for path 
   if (dwRetVal > sizeof(lpPathBuffer) || (dwRetVal == 0))
   {
      printf ("GetTempPath failed (%d)\n", GetLastError());
      return "";
   }
   std::string str;
   char buf[30];
   int iLen= strlen(lpPathBuffer);
   if(!(lpPathBuffer[iLen - 1] == '/'
      || lpPathBuffer[iLen - 1] == '\\'))
   {
      lpPathBuffer[iLen] = '\\';
      lpPathBuffer[iLen+1] = '\0';
   }
   for(int i = 0; i < 1000; i++)
   {
      sprintf(buf, "%d", i);
      str = lpPathBuffer;
      str += pszName;
      str += "-";
      str += buf;
      str += ".";
      str += pszExtension;
      if(!file_exists_dup(str.c_str()))
         return str;
   }
   return "";
}

bool file_exists_dup(const char * path1)
{
   DWORD dwFileAttributes = ::GetFileAttributes(path1);
   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
      (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
      return true;
   else
      return false;
}

bool is_spa_installed()
{
   return
      file_exists_dup("C:\\ca2\\stage\\stage\\basis\\spaadmin.exe")
   && file_exists_dup("C:\\ca2\\stage\\stage\\basis\\spalib.dll")
   && file_exists_dup("C:\\ca2\\stage\\stage\\basis\\spa_bspatch.dll")
   && file_exists_dup("C:\\ca2\\stage\\stage\\basis\\small_bell.mp3")
   && ::LoadLibraryA("C:\\ca2\\stage\\stage\\basis\\spa_bspatch.dll")
   && ::LoadLibraryA("C:\\ca2\\stage\\stage\\basis\\spalib.dll");
}

int install_spa()
{
   DWORD dw = GetFileAttributes("C:\\ca2");
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory("C:\\ca2", NULL);
   }
   dw = GetFileAttributes("C:\\ca2\\stage");
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory("C:\\ca2\\stage", NULL);
   }
   dw = GetFileAttributes("C:\\ca2\\stage\\stage");
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory("C:\\ca2\\stage\\stage", NULL);
   }
   dw = GetFileAttributes("C:\\ca2\\stage\\stage\\basis");
   if(dw == INVALID_FILE_ATTRIBUTES)
   {
      ::CreateDirectory("C:\\ca2\\stage\\stage\\basis", NULL);
   }

   if(!read_resource_as_file_dup("C:\\ca2\\stage\\stage\\basis\\spa_bspatch.dll", ::GetModuleHandleA("npca2.dll"), ID_CGCLBOOT, "CA2SP"))
      return 1;

   SetDllDirectory("C:\\ca2\\stage\\stage\\basis");

   std::string strGz = get_temp_file_name_dup("spalib_for_spasetup", "bz");
   if(!read_resource_as_file_dup(strGz.c_str(), ::GetModuleHandleA("npca2.dll"), ID_CST, "CA2SP"))
      return 1;

   std::string strSp = "C:\\ca2\\stage\\stage\\basis\\spalib.dll";
   if(bzuncompress_dup(strSp.c_str(), strGz.c_str()) != 0)
      return 1;


   strGz = get_temp_file_name_dup("spaadmin_for_spasetup", "bz");
   if(!read_resource_as_file_dup(strGz.c_str(), ::GetModuleHandleA("npca2.dll"), ID_CSTBOOT, "CA2SP"))
      return 1;

   strSp = "C:\\ca2\\stage\\stage\\basis\\spaadmin.exe";
   if(bzuncompress(strSp.c_str(), strGz.c_str()) != 0)
      return 1;

   return 0;
}


UINT ca2_starter_start::starter_start()
{

   if(!is_spa_installed())
   {
      install_spa();
   }

   prepare_small_bell();

   for(int i = 0; i < 8; i++)
   {
      update_ca2_installed();
      if(is_ca2_installed())
         break;
      ca2_cube_install(m_strId.c_str());
   }

   set_installing_ca2(false);

   ::PostMessageA(m_pplugin->m_hwnd, WM_USER + 1984 + 1977, 0, 0);

   if(is_ca2_installed())
      return spaboot_start("stage", m_strId.c_str());

   defer_play_small_bell();

   return 0;
}


UINT APIENTRY _ca2_starter_start(void * pvoid)
{
   ca2_starter_start * pstart = (ca2_starter_start *) pvoid;
   UINT uiRet = pstart->starter_start();
   delete pstart;
   return uiRet;
}
