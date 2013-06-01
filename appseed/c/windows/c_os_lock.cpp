#include "framework.h"

int32_t _c_lock_is_active(const char * pszName)
{

   HANDLE h;

   if(_c_lock(pszName, &h))
   {
      _c_unlock(&h);
      return false;
   }

   return true;

}


int32_t _c_lock(const char * pszName, void ** pdata)
{

   HANDLE hmutex = ::CreateMutex(NULL, FALSE, "Global\\::ca::fontopus::ca2_spa::7807e510-5579-11dd-ae16-0800200c7784");
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


int32_t _c_unlock(void ** pdata)
{

   HANDLE * phandle = (HANDLE *) *pdata;

   ::CloseHandle(*phandle);

   *phandle = NULL;

   delete phandle;

   *pdata = NULL;

   return 1;

}
