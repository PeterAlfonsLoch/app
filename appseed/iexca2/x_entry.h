#pragma once

STDAPI _DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppv);
STDAPI _DllCanUnloadNow();
STDAPI _DllUnregisterServer();
STDAPI _DllRegisterServer(HANDLE hinstanceParent);
STDAPI_(BOOL) _DllMain(HANDLE hinstance, DWORD dwReason, LPVOID lpReserved);


