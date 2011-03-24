#include "mutex_lock.h"
#define WINVER 0x0502
#define _WIN32_WINNT   0x0502
#include <windows.h>

mutex_lock::mutex_lock(HANDLE hmutex)
{
   m_hmutex = hmutex;
   ::WaitForSingleObject(m_hmutex, INFINITE);
}

mutex_lock::~mutex_lock()
{
   ::ReleaseMutex(m_hmutex);
}
