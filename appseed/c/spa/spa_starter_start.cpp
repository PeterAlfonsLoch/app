#include "StdAfx.h"

UINT g_nCa2StarterStartThreadID;
bool g_bCa2Installed = false;
bool g_bCa2Updated = false;
bool g_bInstallingCa2 = false;
bool g_bSpaInstalled = false;
bool g_bSpaUpdated = false;
bool g_bUpdated = false;
char * g_pszCa2Build = NULL;
extern HWND g_hwndMessage;


DWORD WINAPI  _ca2_starter_start(LPVOID pvoid);

const char * get_starter_version()
{
   return ca2_get_build();
}

const char * get_version()
{
   return file_get_contents_dup(dir::ca2("appdata", spa_get_platform(), "build.txt"));
}

const char * get_ca2_version()
{
   return file_get_contents_dup(dir::ca2("appdata", spa_get_platform(), "ca2_build.txt"));
}

void update_ca2_installed(bool bUnloadIfNotInstalled, bool bTakeLockInAccount)
{

   if(bTakeLockInAccount && is_installation_lock_file_locked())
   {
      
      g_bCa2Installed = false;
      return;

   }


   vsstring strStage(dir::ca2("stage", spa_get_platform()));

#ifdef WINDOWS
   ::SetDllDirectoryA(strStage);
#endif

   g_bCa2Installed = true;
   if(g_bCa2Installed)
   {
      ::ca::library libraryOs;
      g_bCa2Installed = libraryOs.open(dir::path(strStage, "os"));
      if(g_bCa2Installed)
      {
         ::ca::library libraryCa2;
         g_bCa2Installed = libraryCa2.open(dir::path(strStage, "ca2"));
         if(!bUnloadIfNotInstalled && g_bCa2Installed)
         {
            libraryCa2.m_bAutoClose    = false;
            libraryOs.m_bAutoClose     = false;
            return;
         }

      }
   }

}



bool is_ca2_installed()
{
   return g_bCa2Installed;
}


void update_ca2_updated()
{
   g_bCa2Updated = !strcmp_dup(get_starter_version(), get_ca2_version());
}

// ca2 files in store updated only in store but may not be yet transferred to the stage
bool is_ca2_updated()
{
   return g_bCa2Updated;
}

bool is_installing_ca2()
{
   return g_bInstallingCa2;
}

void set_installing_ca2(bool bSet)
{
   g_bInstallingCa2 = bSet;
}

// ca2 files in store updated and transferred to the stage
void update_updated()
{
   g_bUpdated = !strcmp_dup(get_starter_version(), get_version());
}


bool is_updated()
{
   return g_bUpdated;
}















#ifdef WINDOWS

void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}

#endif






void update_ca2_build()
{
   if(g_pszCa2Build != NULL)
      ca2_free(g_pszCa2Build);
   g_pszCa2Build = (char *) strdup_dup(ms_get_dup("http://spaignition.api.veriterse.net/ca2_get_build?authnone"));
}


const char * ca2_get_build()
{
   update_ca2_build();
   return g_pszCa2Build;
}



UINT spa_starter_start::start()
{
   static bool s_bStarting = false;

   if(s_bStarting)
      return -1;

   keep_true keepStarting(s_bStarting);

   spa_set_admin(false);
   while(true)
   {
      update_ca2_installed(true, false);
      if(is_ca2_installed() && is_installed(m_strId))
      {
         break;
         //update_ca2_updated();
         //if(is_ca2_updated())
           // break;
      }
      ca2_cube_install(m_strId);
      prepare_small_bell(true);
      Sleep((1984 + 1977) * 2);
   }

   //set_installing_ca2(false);

   //if(is_ca2_installed() && is_installed(m_strId) && is_ca2_updated())
   if(is_ca2_installed() && is_installed(m_strId))
   {
      defer_play_small_bell();
      m_pplugin->set_ca2_installation_ready();
   }

   vsstring strPlatform = spa_get_platform();

   vsstring strSentinelPath = dir::path(dir::beforeca2(), ("ca2\\stage\\" + strPlatform + "\\sentinel.exe"));

   call_sync(strSentinelPath, "");

   return 0;
}

DWORD WINAPI _ca2_starter_start(LPVOID pvoid)
{


   spa_starter_start * pstart = (spa_starter_start *) pvoid;


   UINT uiRet = pstart->start();


   if(uiRet != 0)
      return uiRet;


   _c_simple_message_loop();


   delete pstart;


   return uiRet;


}

void set_ca2_updated(const char * pszBuild)
{
   dir::mk(dir::ca2() + "\\appdata\\" + spa_get_platform());
   file_put_contents_dup(dir::ca2() + "\\appdata\\" + spa_get_platform() + "\\ca2_build.txt", pszBuild);
}


void set_updated(const char * pszBuild)
{
   dir::mk(dir::ca2() + "\\appdata\\" + spa_get_platform());
   file_put_contents_dup(dir::ca2() + "\\appdata\\" + spa_get_platform() + "\\build.txt", pszBuild);
}
