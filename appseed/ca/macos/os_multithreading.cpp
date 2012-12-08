#include "framework.h"


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout, WINBOOL UNUSED(bAlertable))
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
         if(pwaitableptra[i]->is_locked())
         {
            for(j = 0; j < i; j++)
            {
               pwaitableptra[j]->unlock();
            }
            nanosleep(&delay, NULL);
            i = 0;
         }
         else
         {
            pwaitableptra[i]->lock();
            i++;
         }
      }
      for(j = 0; j < dwSize; j++)
      {
         pwaitableptra[j]->unlock();
      }

   }

}



DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, WINBOOL bWaitForAll, DWORD dwTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, FALSE);

}


DWORD WaitForSingleObjectEx(waitable * pwaitable, DWORD dwTimeout, bool bAlertable)
{
   
   return WaitForMultipleObjectsEx(1, &pwaitable, TRUE, dwTimeout, bAlertable);
   
}


DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwTimeout)
{

   return WaitForSingleObjectEx(pwaitable, dwTimeout, FALSE);

}


