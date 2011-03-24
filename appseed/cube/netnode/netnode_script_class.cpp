#include "StdAfx.h"
#include "netnodeScriptClass.h"
#include "netnodeScriptInstance.h"
#include "netnodeScriptManager.h"


typedef struct tagLOADPARMS32 { 
  char * lpEnvAddress;  // address of environment strings 
  char * lpCmdLine;     // address of command line 
  char * lpCmdShow;     // how to show new program 
  DWORD dwReserved;    // must be zero 
} LOADPARMS32;

netnodeScript::netnodeScript(::ca::application * papp) : 
   ca(papp),
   m_memfileError(papp)
{
   m_hmodule               = NULL;
   m_lpfnCreateInstance    = NULL;
   m_bShouldBuild          = true;
   m_bCalcHasTempError     = false;
}

bool netnodeScript::DoesMatchVersion()
{
   CSingleLock sl(&m_mutex, TRUE);
   FILETIME ftCreation;
   FILETIME ftAccess;
   FILETIME ftModified;
   memset(&ftCreation, 0, sizeof(FILETIME));
   memset(&ftAccess, 0, sizeof(FILETIME));
   memset(&ftModified, 0, sizeof(FILETIME));
   HANDLE h = ::CreateFile(m_strSourcePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
   ::CloseHandle(h);
   return !memcmp(&ftCreation, &m_ftCreation, sizeof(FILETIME)) && 
      !memcmp(&m_ftModified, &ftModified, sizeof(FILETIME));
}

bool netnodeScript::ShouldBuild()
{
   CSingleLock sl(&m_mutex, TRUE);
   return  m_bShouldBuild || (HasTempError() && 
      HasTimedOutLastBuild()) 
       || !DoesMatchVersion();
      
}

void netnodeScript::on_start_build()
{
   CSingleLock sl(&m_mutex, TRUE);
   // Unload library in the context of manager thread
   //m_pmanager->m_pmessagewindow->SendMessage(WM_APP + 13, 13, (LPARAM) this);
   Unload(false);
   m_bCalcHasTempError = false;
   m_bShouldBuild = false;
   m_hmodule = NULL;
   m_memfileError.Truncate(0);
}

bool netnodeScript::HasTimedOutLastBuild()
{
   CSingleLock sl(&m_mutex, TRUE);
   return (::GetTickCount() - m_dwLastBuildTime) > 
      (m_pmanager->m_dwBuildTimeWindow + System.math().RandRange(0, m_pmanager->m_dwBuildTimeRandomWindow));
}

bool netnodeScript::HasCompileOrLinkError()
{
   CSingleLock sl(&m_mutex, TRUE);
   string str;
   m_memfileError.seek_to_begin();
   m_memfileError.to_string(str);
   if(str.find(" error(") >= 0)
      return true;
   if(str.find(" error ") >= 0)
      return true;
   if(str.find(" GetLastError ") >= 0)
      return true;
   return false;
}

bool netnodeScript::HasTempError(bool bLock)
{
   CSingleLock sl(&m_mutex, bLock ? TRUE : FALSE);
   if(!m_bCalcHasTempError)
   {
      m_bHasTempError = CalcHasTempError(false);
      m_bCalcHasTempError = true;
   }
   return m_bHasTempError;
}

bool netnodeScript::CalcHasTempError(bool bLock)
{
   CSingleLock sl(&m_mutex, bLock ? TRUE : FALSE);
   string str;
   m_memfileError.seek_to_begin();
   m_memfileError.to_string(str);
   {
      int iFind1 = str.find(".dll: does not exist.");
      if(iFind1 >= 0)
      {
         // if dll does not exist
         {
            int iFind1 = str.find(" error(");
            int iFind2 = str.find(" error ");
            int iFind3 = str.find("Linking...");
            // and have compile error
            if((iFind3 >= 0 && ((iFind1 < iFind3 && iFind1 >= 0) || 
               (iFind2 < iFind3 && iFind2 >= 0))))
            {
               return false;
            }
         }
         
      }
   }
   {
      int iFind1 = str.find("fatal error C1033:");
      if(iFind1 >= 0)
         return true;
   }
   {
      int iFind1 = str.find("warning LNK4099:");
      if(iFind1 >= 0)
         return true;
   }
   {
      int iFind1 = str.find("fatal error LNK1168:");
      if(iFind1 >= 0)
         return true;
   }
   {
      int iFind1 = str.find(" error(");
      int iFind2 = str.find(" error ");
      int iFind3 = str.find("Linking...");
      if(iFind3 >= 0 && (iFind1 > iFind3 || iFind2 > iFind3))
      {
         return true;
      }
   }
   if(str.find(" GetLastError ") >= 0)
      return true;
   return false;
}


void netnodeScript::Load(bool bLock)
{
   CSingleLock sl(&m_mutex, bLock ? TRUE : FALSE);
   m_strScriptPath.replace("/", "\\");
   if(!System.file().exists(m_strScriptPath))
   {
      if(HasTempError(false))
      {
         m_memfileError << m_strScriptPath << ": does not exist because of \"temp\" error.";
      }
      else
      {
         m_memfileError << m_strScriptPath << ": does not exist.";
      }
      m_lpfnCreateInstance = NULL;
      return;
   }
   if(m_hmodule == NULL)
   {
      //if(m_strScriptPath.find("transactions") >= 0)
      //{
        // AfxDebugBreak();
      //}
      m_hmodule = ::LoadLibraryW(
         gen::international::utf8_to_unicode("\\\\?\\" + m_strScriptPath));
      if(m_hmodule == NULL)
      {
         DWORD dwMessageId = GetLastError();
         if(dwMessageId == 0x139)
         {
            AfxDebugBreak();
         }
         LPTSTR lpBuffer;
         TRACE("Error Message Id: %d\n", dwMessageId);
         FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            dwMessageId,
            0,
            (LPTSTR) &lpBuffer,
            1,
            NULL);
         string str;
         str.Format("%d : ", ::GetLastError());
         m_memfileError << m_strScriptPath << " : LoadLibrary, GetLastError "  << str;
         
         if(lpBuffer != NULL)
         {
            m_memfileError << lpBuffer;
            LocalFree(lpBuffer);
         }
      }      
   }
   m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) ::GetProcAddress(m_hmodule, "create_netnode_script_instance");
}
void netnodeScript::Unload(bool bLock)
{
   CSingleLock sl(&m_mutex, bLock ? TRUE : FALSE);
   if(m_hmodule != NULL)
   {
      ::FreeLibrary(m_hmodule);
      HMODULE hmodule = ::GetModuleHandleW(gen::international::utf8_to_unicode("\\\\?\\" + m_strScriptPath));
      BOOL b = ::GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, gen::international::utf8_to_unicode("\\\\?\\" + m_strScriptPath), &hmodule);
      if(hmodule != NULL && !::FreeLibrary(hmodule))
      {
         DWORD dwError = ::GetLastError();
         TRACE("netnodeScript::GetModuleHandle return BOOL(%d) Unload Error close Handle %s %d\r\n", b, m_strScriptPath, dwError);
      }
      string strPdb;
      strPdb = m_strScriptPath;
      gen::str::ends_eat_ci(strPdb, ".dll");
      strPdb += ".pdb";
      hmodule = ::GetModuleHandleW(gen::international::utf8_to_unicode(strPdb));
      if(hmodule != NULL && !::FreeLibrary(hmodule))
      {
         DWORD dwError = ::GetLastError();
         TRACE("netnodeScript::Unload Error close Handle %s %d\r\n", strPdb, dwError);
      }

      m_hmodule = NULL;
      m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) NULL;
   }
}



netnodeScript::~netnodeScript(void)
{
}

void netnodeScript::run(netnodeScriptInstance * pinstance)
{
   pinstance->run();
}

netnodeScriptInstance * netnodeScript::create_instance()
{
   CSingleLock sl(&m_mutex, TRUE);
   netnodeScriptInstance * pinstance;
   if(m_lpfnCreateInstance == NULL)
   {
      pinstance = new netnodeScriptInstance(this);
   }
   else
   {
      pinstance = m_lpfnCreateInstance(this);
   }
   return pinstance;
}


::ca::application * netnodeScript::get_app() const
{
   return m_pmanager->get_app();
}