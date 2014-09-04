#include "framework.h"
#include <sys/resource.h>


void thread_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   int iOsMax = sched_get_priority_max(SCHED_RR);

   int iOsMin = sched_get_priority_min(SCHED_RR);

   if(nCa2Priority == ::multithreading::priority_normal)
   {

      iOsPolicy = SCHED_RR; // iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = (int) ::multithreading::priority_normal;

      iOsMin = (iOsMin + iOsMax) / 2;

      iOsMax = iOsMin;

   }
   else if(nCa2Priority > ::multithreading::priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = 99;

      iOsMin = (iOsMin + iOsMax) / 2;

   }
   else
   {

      iOsPolicy = SCHED_RR; // iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::multithreading::priority_normal;

      iOsMax = (iOsMin + iOsMax) / 2;

   }


   int iOsPriority;

   if(iCa2Min == iCa2Max)
   {
      iOsPriority = 0;
   }
   else
   {
      iOsPriority = (((nCa2Priority - iCa2Min)  * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
   }

   iOsPriority = max(iOsMin, min(iOsMax, iOsPriority));

   *piPolicy = iOsPolicy;

   pparam->sched_priority = iOsPriority;

}

int32_t thread_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


//   if(iOsPolicy == SCHED_RR)
   {

      iCa2Min = ::multithreading::priority_idle;

      iCa2Max = 99;

   }
/*
   else if(iOsPolicy == SCHED_IDLE)
   {

      iCa2Min = 0;

      iCa2Max = (int) ::multithreading::priority_normal;

   }
   else
   {

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = (int) ::multithreading::priority_normal;

   }
*/

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iCa2Priority;

   if(iOsMax == iOsMin)
   {
      iCa2Priority = (int32_t) ::multithreading::priority_normal;
   }
   else
   {
      iCa2Priority = (((pparam->sched_priority - iOsMin)  * (iCa2Max - iCa2Min)) / (iOsMax - iOsMin)) + iCa2Min;
   }

   iCa2Priority = max(iCa2Min, min(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void process_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   throw "not applicable in Mac OS";

}

int32_t process_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   throw "not applicable in Mac OS";

}


int32_t process_get_os_priority(int32_t nCa2Priority)
{

   if(nCa2Priority <= (int) ::multithreading::priority_none)
      return 0;

   if(nCa2Priority <= (int) ::multithreading::priority_normal)
      return max(-20, min(0, -20 * ((int) ::multithreading::priority_normal - nCa2Priority) / ((int) ::multithreading::priority_normal - (int) ::multithreading::priority_idle)));

   return max(0, min(20, 20 * (nCa2Priority - (int) ::multithreading::priority_normal) / ((int) ::multithreading::priority_time_critical - (int) ::multithreading::priority_normal)));

}


int32_t process_get_scheduling_priority(int32_t iOsPriority)
{

   if(iOsPriority < -15)
      return ::multithreading::priority_idle;

   if(iOsPriority < -10)
      return ::multithreading::priority_lowest;

   if(iOsPriority < 0)
      return ::multithreading::priority_below_normal;

   if(iOsPriority == 0)
      return ::multithreading::priority_normal;

   if(iOsPriority < 10)
      return ::multithreading::priority_above_normal;

   if(iOsPriority < 15)
      return ::multithreading::priority_highest;

   return ::multithreading::priority_time_critical;


}


namespace ca2
{



   bool set_priority_class(int32_t iCa2Priority)
   {

      int iOsPriority = process_get_os_priority(iCa2Priority);

      setpriority(PRIO_PROCESS, 0, iOsPriority);

      return true;

   }



} // namespace ca2





void __node_init_thread()
{

}


void __node_term_thread()
{

}


bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   return true;

}



