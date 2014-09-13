#include "framework.h"


DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, DWORD dwTimeout, DWORD UNUSED(dwWakeMask), DWORD dwFlags)
{

   DWORD start;

   if(dwTimeout != (DWORD) INFINITE)
   {
      start = ::get_tick_count();
   }


   BOOL bWaitForAll        = dwFlags & MWMO_WAITALL;
   BOOL bAlertable         = dwFlags & MWMO_ALERTABLE;
   BOOL bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;

   if(bWaitForAll)
   {

      int32_t i;
      int32_t j;
      i = 0;
      for(; i < dwSize;)
      {
         if(dwTimeout != (DWORD) INFINITE && ::get_tick_count() - start >= dwTimeout)
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
//      for(j = 0; j < dwSize; j++)
  //    {
    //     pwaitableptra[j]->unlock();
      //}

      return WAIT_OBJECT_0;

   }
   else
   {

      int32_t i;
      int32_t j;
      while(true)
      {

         for(i = 0; i < dwSize;)
         {
            if(dwTimeout != (DWORD) INFINITE && ::get_tick_count() - start >= dwTimeout)
            {
               return WAIT_TIMEOUT;
            }
            if(pwaitableptra[i]->lock(millis(0)))
            {
               return WAIT_OBJECT_0 + i;
            }
         }

         nanosleep(&delay, NULL);

      }

   }

}

DWORD MsgWaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));

}


DWORD WaitForMultipleObjectsEx(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout, int_bool bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pwaitableptra, dwTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));

}


DWORD WaitForMultipleObjects(DWORD dwSize, waitable ** pwaitableptra, int_bool bWaitForAll, DWORD dwTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pwaitableptra, bWaitForAll, dwTimeout, FALSE);

}


DWORD WaitForSingleObjectEx(waitable * pwaitable, DWORD dwTimeout, int_bool bAlertable)
{

   return WaitForMultipleObjectsEx(1, &pwaitable, TRUE, dwTimeout, bAlertable);

}


DWORD WaitForSingleObject(waitable * pwaitable, DWORD dwTimeout)
{

   return WaitForSingleObjectEx(pwaitable, dwTimeout, FALSE);

}

