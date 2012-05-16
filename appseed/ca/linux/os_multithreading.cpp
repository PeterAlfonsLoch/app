#include "StdAfx.h"


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable * pwaitableptra, BOOL bWaitForAll, DWORD dwTimeout, BOOL UNUSED(bAlertable))
{

   DWORD start;

   if(dwTimeout != (DWORD) INFINITE)
   {
      start = ::GetTickCount();
   }

   if(bWaitForAll)
   {

      timespec delay;

      delay.tv_sec = 0;
      delay.tv_nsec = 1000000;

      int i;
      int j;
      i = 0;
      for(; i < dwSize;)
      {
         if(dwTimeout != (DWORD) INFINITE && ::GetTickCount() - start >= dwTimeout)
         {
            return WAIT_TIMEOUT;
         }
         if(pwaitableptra[i].is_locked())
         {
            for(j = 0; j < i; j++)
            {
               pwaitableptra[j].unlock();
            }
            nanosleep(&delay, NULL)
            i = 0;
         }
         else
         {
            pwaitableptra[i].lock();
            i++;
         }
      }
      for(j = 0; j < dwSize; j++)
      {
         pwaitableptra[j]->unlock();
      }

   }

}



DWORD WaitForMultipleObjects(DWORD dwSize, waitable * pwaitableptra, BOOL bWaitForAll, DWORD dwTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, FALSE);

}


DWORD WaitForMultipleObjects(DWORD dwSize, waitable * pwaitableptra, BOOL bWaitForAll, DWORD dwWakeMask)
{

   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, FALSE);

}
