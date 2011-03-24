#include "StdAfx.h"

const char * ms_get_dup(const char * host, const char * request);

UINT g_nCa2StarterStartThreadID;
bool g_bCa2Installed = false;
bool g_bCa2Updated = false;
bool g_bInstallingCa2 = false;
bool g_bSpaInstalled = false;
bool g_bSpaUpdated = false;
std::string g_strCa2Build;
extern char * g_pszCa2Build;

std::string get_ca2_folder_dup()
{
   char lpszModuleFolder[MAX_PATH * 8];
   get_ca2_folder_dup(lpszModuleFolder);
   return lpszModuleFolder;
}

void get_ca2_folder_dup(char * lpszModuleFolder)
{
   strcpy(lpszModuleFolder, "C:");
}


std::string spa_get_platform_dup()
{
#ifdef _X86_
   return "x86";
#else
   return "x64";
#endif
}

std::string get_starter_version()
{
   return g_strCa2Build;
}


std::string get_spa_version()
{
   return file_get_contents_dup((get_ca2_folder_dup() + "\\ca2\\appdata\\" + spa_get_platform_dup() + "\\spa_build.txt").c_str());
}


std::string get_ca2_version()
{
   return file_get_contents_dup((get_ca2_folder_dup() + "\\ca2\\appdata\\" + spa_get_platform_dup() + "\\build.txt").c_str());
}

void update_ca2_installed()
{
   try
   {
      SetDllDirectory((get_ca2_folder_dup() + "\\ca2\\stage\\" + spa_get_platform_dup()).c_str());
      g_bCa2Installed = true;
      if(g_bCa2Installed)
      {
         HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\" + spa_get_platform_dup() + "\\ca2.dll").c_str());
         g_bCa2Installed = hmodule != NULL;
         ::FreeLibrary(hmodule);
      }
      if(g_bCa2Installed)
      {
         HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\" + spa_get_platform_dup() + "\\cube.dll").c_str());
         g_bCa2Installed = hmodule != NULL;
         ::FreeLibrary(hmodule);
      }
      if(g_bCa2Installed)
      {
         HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\" + spa_get_platform_dup() + "\\win.dll").c_str());
         g_bCa2Installed = hmodule != NULL;
         ::FreeLibrary(hmodule);
      }
   }
   catch(...)
   {
      g_bCa2Installed = false;
   }
}



bool is_ca2_installed()
{
   return g_bCa2Installed;
}

// can be called only after spa is updated
void calc_ca2_build()
{
   g_strCa2Build = ms_get_dup("spaignition.api.veriterse.net", "/ca2_get_build?authnone");
}

void update_ca2_updated()
{
   try
   {
      calc_ca2_build();
      g_bCa2Updated = get_starter_version() == get_ca2_version();
   }
   catch(...)
   {
      g_bCa2Updated = false;
   }
}


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


void update_spa_installed()
{
#ifdef _X86_

  
   g_bSpaInstalled =
      file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spaboot.exe").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spaadmin.exe").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spalib.dll").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spa_bspatch.dll").c_str());
   if(g_bSpaInstalled)
   {
      HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spa_bspatch.dll").c_str());
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bSpaInstalled)
   {
      HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spalib.dll").c_str());
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
#else
   g_bSpaInstalled =
      file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spaboot.exe").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x86\\spaadmin.exe").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x64\\spalib.dll").c_str())
   && file_exists_dup((get_ca2_folder_dup() + "\\ca2\\stage\\x64\\spa_bspatch.dll").c_str());
   if(g_bSpaInstalled)
   {
      HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\x64\\spa_bspatch.dll").c_str());
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
   if(g_bSpaInstalled)
   {
      HMODULE hmodule = ::LoadLibraryA((get_ca2_folder_dup() + "\\ca2\\stage\\x64\\spalib.dll").c_str());
      g_bSpaInstalled = hmodule != NULL;
      ::FreeLibrary(hmodule);
   }
#endif
}



bool is_spa_installed()
{
   return g_bSpaInstalled;
}


void update_spa_updated()
{
   try
   {
      calc_ca2_build();
      g_bSpaUpdated = get_starter_version() == get_spa_version();
   }
   catch(...)
   {
      g_bSpaUpdated = false;
   }
}


bool is_spa_updated()
{
   return g_bSpaUpdated;
}


namespace npca2
{

   UINT starter_start::start()
   {

      defer_install_spa();

      update_spa_installed();
      if(!is_spa_installed())
         return 0;

      update_spa_updated();
      if(!is_spa_updated())
         return 0;

      spa_set_admin(false);
      prepare_small_bell();

      for(int i = 0; i < 8; i++)
      {
         if(i >= 1)
         {
            Sleep(1984 + 1977);
         }
         update_ca2_installed();
         if(is_ca2_installed() && is_installed(m_strId.c_str()))
         {
            update_ca2_updated();
            if(is_ca2_updated())
               break;
         }
         try
         {
            ca2_cube_install(m_strId.c_str());
         }
         catch(...)
         {
            // does not fail...
            // the loop would check again if is_ca2_installed and if is_installed(id)
         }
      }

      set_installing_ca2(false);

      m_pplugin->m_bCa2JustInstalled = true;

      if(is_ca2_installed() && is_installed(m_strId.c_str()) && is_ca2_updated())
      {
         defer_play_small_bell();
      }

      return 0;
   }



} // namespace npca2


UINT APIENTRY _ca2_starter_start(void * pvoid)
{
   npca2::starter_start * pstart = (npca2::starter_start *) pvoid;
   UINT uiRet = pstart->start();
   delete pstart;
   return uiRet;
}
