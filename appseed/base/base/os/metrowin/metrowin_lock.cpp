#include "framework.h"

int _c_lock_is_active(const char * pszName)
{

   HANDLE h;

   if(_c_lock(pszName, &h))
   {
      _c_unlock(&h);
      return false;
   }

   return true;

}


int _c_lock(const char * pszName, void ** pdata)
{
#ifdef METROWIN
   wstring wstrName(pszName);
   HANDLE hmutex = ::CreateMutexEx(NULL, wstrName, 0, SYNCHRONIZE);
#else
   HANDLE hmutex = ::CreateMutex(NULL, FALSE, pszName);
#endif
   if(::GetLastError() == ERROR_ALREADY_EXISTS)
   {
      ::CloseHandle(hmutex);
      return 0;
   }
   if(hmutex == INVALID_HANDLE_VALUE)
      return 0;

   HANDLE * phandle = new HANDLE;
   *phandle = hmutex;
   *pdata = phandle;

   return 1;

}


int _c_unlock(void ** pdata)
{

   HANDLE * phandle = (HANDLE *) *pdata;

   ::CloseHandle(*phandle);

   *phandle = NULL;

   delete phandle;

   *pdata = NULL;

   return 1;

}
