#include "StdAfx.h"
#include "netnodeLibraryClass.h"
#include "netnodeScriptInstance.h"
#include "netnodeScriptManager.h"

typedef struct tagLOADPARMS32 { 
  char * lpEnvAddress;  // address of environment strings 
  char * lpCmdLine;     // address of command line 
  char * lpCmdShow;     // how to show new program 
  DWORD dwReserved;    // must be zero 
} LOADPARMS32;

netnodeLibraryClass::netnodeLibraryClass(::ca::application * papp)
: m_memfileError(papp), ca(papp)
{
}

bool netnodeLibraryClass::DoesMatchVersion()
{
   for(int i = 0; i < m_straSourcePath.get_size(); i++)
   {
      FILETIME ftCreation;
      FILETIME ftAccess;
      FILETIME ftModified;
      memset(&ftCreation, 0, sizeof(FILETIME));
      memset(&ftAccess, 0, sizeof(FILETIME));
      memset(&ftModified, 0, sizeof(FILETIME));
      HANDLE h = ::CreateFile(m_straSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      GetFileTime(h, &ftCreation, &ftAccess, &ftModified);
      ::CloseHandle(h);
      if(memcmp(&ftCreation, &m_ftaCreation[i], sizeof(FILETIME)) != 0
      || memcmp(&m_ftaModified[i], &ftModified, sizeof(FILETIME)) != 0)
      {
         return false;
      }
   }
   return true;
}
void netnodeLibraryClass::Load()
{
   m_hmodule = ::LoadLibraryW(
      gen::international::utf8_to_unicode("\\\\?\\" + m_strLibraryPath));
   m_ftaCreation.set_size(m_straSourcePath.get_size());
   m_ftaAccess.set_size(m_straSourcePath.get_size());
   m_ftaModified.set_size(m_straSourcePath.get_size());
   for(int i = 0; i < m_straSourcePath.get_size(); i++)
   {
      HANDLE h = ::CreateFile(m_straSourcePath[i], GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      memset(&m_ftaCreation[i], 0, sizeof(FILETIME));
      memset(&m_ftaAccess[i], 0, sizeof(FILETIME));
      memset(&m_ftaModified[i], 0, sizeof(FILETIME));
      GetFileTime(h , &m_ftaCreation[i], &m_ftaAccess[i], &m_ftaModified[i]);
      ::CloseHandle(h);
   }
}
void netnodeLibraryClass::Unload()
{
   ::FreeLibrary(m_hmodule);
}



netnodeLibraryClass::~netnodeLibraryClass(void)
{
}

::ca::application * netnodeLibraryClass::get_app() const
{
   return m_pmanager->get_app();
}