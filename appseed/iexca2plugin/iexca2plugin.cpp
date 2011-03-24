/*****************************************************************************
* main.cpp: Free ActiveX based on ActiveX control for VLC
*****************************************************************************
* Copyright (C) 2005 the VideoLAN team
* Copyright (C) 2008 http://unick-soft.xost.ru
*
* Authors: Damien Fouilleul <Damien.Fouilleul@laposte.net>
* Modification: Oleg <soft_support@list.ru>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
*****************************************************************************/

#include "StdAfx.h"
#include "x_entry.h"

#include <string.h>

#pragma comment(lib, "win.lib")

#undef new


bool g_bApp = false;

unsigned long g_last_redraw = 0;

HANDLE g_hEventReady = NULL;

//It is test exmple for create ActiveX without ALT an MFC
#define COMPANY_STR "ccvotagus.ca2.fontopus"
#define PROGRAM_STR "iexca2"
#define DESCRIPTION "ca2 starter ActiveX Control"

#define PROGID_STR  "ccvotagus.ca2.fontopus.iexca2"

#define THREADING_MODEL "Apartment"
#define MISC_STATUS     "131345"



#define GUID_STRLEN 39

DEFINE_GUID(_CATID_SafeForInitializing, 0x7DD95802, 0x9882, 0x11CF, 0x9F, 0xA9, 0x00,0xAA,0x00,0x6C,0x42,0xC4);
DEFINE_GUID(_CATID_SafeForScripting,    0x7DD95801, 0x9882, 0x11CF, 0x9F, 0xA9, 0x00,0xAA,0x00,0x6C,0x42,0xC4);

LONG i_class_ref= 0;
HINSTANCE g_hinstance= 0;

HMODULE DllGetModule()
{
   return g_hinstance;
};

STDAPI _DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
   HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;

   *ppv = NULL;

   if( (CLSID_iexca2_plugin == rclsid ) )
   {
      iexca2::class_factory * plugin = new iexca2::class_factory(&i_class_ref, g_hinstance, rclsid);
      hr = plugin->QueryInterface(riid, ppv);
      plugin->Release();
   }
   return hr;
};

STDAPI _DllCanUnloadNow(VOID)
{
   return (0 == i_class_ref) ? S_OK: S_FALSE;
};

static inline HKEY keyCreate(HKEY parentKey, LPCWSTR keyName)
{
   HKEY childKey;
   if( ERROR_SUCCESS == RegCreateKeyExW(parentKey, keyName, 0, NULL,
      REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &childKey, NULL) )
   {
      return childKey;
   }
   return NULL;
};

static inline HKEY keySet(HKEY hKey, LPCWSTR valueName, const void *s, size_t len, DWORD dwType = REG_SZ)
{
   if( NULL != hKey )
   {
      RegSetValueExW(hKey, valueName, 0, dwType,
         (const BYTE*)s, len);
   }
   return hKey;
};

static inline HKEY keySetDef(HKEY hKey, const void *s, size_t len, DWORD dwType = REG_SZ)
{
   return keySet(hKey, NULL, s, len, dwType);
};

static inline HKEY keySetDef(HKEY hKey, LPCWSTR s)
{
   return keySetDef(hKey, s, sizeof(WCHAR)*(wcslen(s)+1), REG_SZ);
};

static inline HKEY keyClose(HKEY hKey)
{
   if( NULL != hKey )
   {
      RegCloseKey(hKey);
   }
   return NULL;
};

static void UnregisterProgID(REFCLSID rclsid, unsigned int version)
{
   OLECHAR szCLSID[GUID_STRLEN];

   StringFromGUID2(rclsid, szCLSID, GUID_STRLEN);

   WCHAR progId[sizeof(PROGID_STR)+16];
   swprintf(progId, W("%s.%u"), W(PROGID_STR), version);

   SHDeleteKeyW(HKEY_CLASSES_ROOT, progId);

   HKEY hClsIDKey;
   if( ERROR_SUCCESS == RegOpenKeyExW(HKEY_CLASSES_ROOT, W("CLSID"), 0, KEY_WRITE, &hClsIDKey) )
   {
      SHDeleteKeyW(hClsIDKey, szCLSID);
      RegCloseKey(hClsIDKey);
   }
};

STDAPI _DllUnregisterServer(VOID)
{
   // unregister type lib from the registry
   UnRegisterTypeLib(LIBID_iexca2, 1, 0, LOCALE_NEUTRAL, SYS_WIN32);

   // remove component categories we supports
   ICatRegister *pcr;
   if(SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,
      NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr)) ) 
   {
      CATID implCategories[] = 
      {
         CATID_Control,
         CATID_PersistsToPropertyBag,
         CATID_InternetAware,
         _CATID_SafeForInitializing,
         _CATID_SafeForScripting,
      };

      pcr->UnRegisterClassImplCategories(CLSID_iexca2_plugin, sizeof(implCategories)/sizeof(CATID), implCategories);
      pcr->Release();
   }

   SHDeleteKeyW(HKEY_CLASSES_ROOT, W(PROGID_STR));

   UnregisterProgID(CLSID_iexca2_plugin, 2);

   return S_OK;
};

static HRESULT RegisterClassID(HKEY hParent, REFCLSID rclsid, unsigned int version, BOOL isDefault, LPCWSTR path,const size_t pathLen)
{
   WCHAR progId[sizeof(PROGID_STR)+16];
   _swprintf(progId, W("%s.%u"), W(PROGID_STR), version);

   WCHAR description[sizeof(DESCRIPTION)+16];
   _swprintf(description, W("%s v%u"), W(DESCRIPTION), version);

   HKEY hClassKey;
   {
      OLECHAR szCLSID[GUID_STRLEN];

      StringFromGUID2(rclsid, szCLSID, GUID_STRLEN);


      HKEY hProgKey = keyCreate(HKEY_CLASSES_ROOT, progId);
      if( NULL != hProgKey )
      {
         // default key value
         keySetDef(hProgKey, description);

         keyClose(keySetDef(keyCreate(hProgKey, W("CLSID")), szCLSID, sizeof(szCLSID)));

         RegCloseKey(hProgKey);
      }
      if( isDefault )
      {
         hProgKey = keyCreate(HKEY_CLASSES_ROOT, W(PROGID_STR));
         if( NULL != hProgKey )
         {
            // default key value
            keySetDef(hProgKey, description);

            keyClose(keySetDef(keyCreate(hProgKey, W("CLSID")), szCLSID, sizeof(szCLSID)));

            keyClose(keySetDef(keyCreate(hProgKey, W("CurVer")), progId));
         }
      }
      hClassKey = keyCreate(hParent, (const WCHAR *) szCLSID);
   }
   if( NULL != hClassKey )
   {
      // default key value
      keySetDef(hClassKey, description);

      // Control key value
      keyClose(keyCreate(hClassKey, W("Control")));

      // ToolboxBitmap32 key value
      {
         WCHAR* iconPath = new WCHAR[pathLen + 3];
         memcpy(iconPath, path, sizeof(WCHAR)*pathLen);
         wcscpy(iconPath+pathLen, W(",1"));
         keyClose(keySetDef(keyCreate(hClassKey, W("ToolboxBitmap32")), iconPath, sizeof(WCHAR) * (pathLen + 3)));
         delete[] iconPath;
         iconPath = NULL;
      }

      // InprocServer32 key value
      {
         HKEY hSubKey = keySetDef(keyCreate(hClassKey, W("InprocServer32")), path, sizeof(WCHAR)*(pathLen+1));
         
         keySet(hSubKey, W("ThreadingModel"), W(THREADING_MODEL), sizeof(W(THREADING_MODEL)));

         keyClose(hSubKey);
      }

      // MiscStatus key value
      keyClose(keySetDef(keyCreate(hClassKey, W("MiscStatus\\1")), W(MISC_STATUS), sizeof(W(MISC_STATUS))));

      // Programmable key value
      keyClose(keyCreate(hClassKey, W("Programmable")));

      // ProgID key value
      keyClose(keySetDef(keyCreate(hClassKey, W("ProgID")), progId));

      // VersionIndependentProgID key value
      keyClose(keySetDef(keyCreate(hClassKey, W("VersionIndependentProgID")), W(PROGID_STR), sizeof(W(PROGID_STR))));

      // Version key value
      keyClose(keySetDef(keyCreate(hClassKey, W("Version")), W("1.0")));

      // TypeLib key value
      OLECHAR szLIBID[GUID_STRLEN];

      StringFromGUID2(LIBID_iexca2, szLIBID, GUID_STRLEN);

      keyClose(keySetDef(keyCreate(hClassKey, W("TypeLib")), szLIBID, sizeof(szLIBID)));

      RegCloseKey(hClassKey);
   }
   return S_OK;
}

STDAPI _DllRegisterServer(HANDLE hinstanceParent)
{

   _DllUnregisterServer();

   WCHAR DllPath[MAX_PATH * 8];
   //UINT DllPathLen = ::GetModuleFileNameW((HMODULE) hinstanceParent, DllPath, sizeof(DllPath) / sizeof(WCHAR));

#ifdef _X86_
   wcscpy(DllPath, L"C:\\ca2\\stage\\x86\\iexca2plugin.dll");
#else
   wcscpy(DllPath, L"C:\\ca2\\stage\\x64\\iexca2plugin.dll");
#endif

   UINT DllPathLen = wcslen(DllPath);

   HKEY hBaseKey;

   if( ERROR_SUCCESS != RegOpenKeyExW(HKEY_CLASSES_ROOT, W("CLSID"), 0, KEY_CREATE_SUB_KEY, &hBaseKey) )
      return SELFREG_E_CLASS;

   RegisterClassID(hBaseKey, CLSID_iexca2_plugin, 2, TRUE, DllPath, DllPathLen);

   RegCloseKey(hBaseKey);

   // indicate which component categories we support
   ICatRegister *pcr;
   if( SUCCEEDED(CoCreateInstance(CLSID_StdComponentCategoriesMgr,
      NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr)) ) {
         CATID implCategories[] = {
            CATID_Control,
            CATID_PersistsToPropertyBag,
            CATID_InternetAware,
            _CATID_SafeForInitializing,
            _CATID_SafeForScripting,
         };

         pcr->RegisterClassImplCategories(CLSID_iexca2_plugin,
            sizeof(implCategories)/sizeof(CATID), implCategories);
         pcr->Release();
   }

   // register type lib into the registry
   ITypeLib *typeLib;

   HRESULT result = LoadTypeLibEx((const WCHAR *) DllPath, REGKIND_REGISTER, &typeLib);
   if( SUCCEEDED(result) )
      typeLib->Release();

   return result;
};


STDAPI_(BOOL) _DllMain(HANDLE hinstance, DWORD dwReason, LPVOID lpReserved )
{
   if (dwReason == DLL_PROCESS_ATTACH)
   {

      g_hinstance = (HINSTANCE) hinstance;

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
   }

   return TRUE;
};


const char * ca2_browser_plugin_get_module_name()
{
   return "iexca2plugin.dll";
}

/*void get_ca2_folder(char * lpszModuleFolder)
{
   strcpy(lpszModuleFolder, "C:");
}*/

extern "C" int APIENTRY
DllMain(HINSTANCE hinstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
      g_hinstance = hinstance;
      char lpszDir[MAX_PATH * 8];
      get_ca2_folder(lpszDir);
#ifdef _X86_
      strcat(lpszDir, "\\ca2\\stage\\x86\\");
#else
      strcat(lpszDir, "\\ca2\\stage\\x64\\");
#endif
      ::SetDllDirectory(lpszDir);
      defer_install_spa();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
      //on_npca2_detach();

	}
	return 1;   // ok
}




STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv)
{
   return _DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllCanUnloadNow(VOID)
{
   return _DllCanUnloadNow();
}


STDAPI DllUnregisterServer(VOID)
{
   return _DllUnregisterServer();
}

STDAPI DllRegisterServer(VOID)
{
   return _DllRegisterServer(NULL);
}



