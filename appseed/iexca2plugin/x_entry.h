#pragma once

STDAPI _DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv);
STDAPI _DllCanUnloadNow();
STDAPI _DllUnregisterServer();
STDAPI _DllRegisterServer(HANDLE hinstanceParent);
STDAPI_(BOOL) _DllMain(HANDLE hinstance, DWORD dwReason, LPVOID lpReserved);


extern "C"  typedef  HRESULT     (STDAPICALLTYPE *    LPFN_DllGetClassObject     )(REFCLSID rclsid, REFIID riid, LPVOID *ppv);
extern "C"  typedef  HRESULT     (STDAPICALLTYPE *    LPFN_DllCanUnloadNow       )();
extern "C"  typedef  HRESULT     (STDAPICALLTYPE *    LPFN_DllUnregisterServer   )();
extern "C"  typedef  HRESULT     (STDAPICALLTYPE *    LPFN_DllRegisterServer     )(HANDLE hinstanceParent);
extern "C"  typedef  BOOL        (STDAPICALLTYPE *    LPFN_DllMain               )(HANDLE hinstance, DWORD dwReason, LPVOID lpReserved);
