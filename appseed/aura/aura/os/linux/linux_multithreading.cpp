#include "framework.h"
#include <sched.h>


#ifdef LINUX
# define SCHED_BATCH		3
# define SCHED_IDLE		5

# define SCHED_RESET_ON_FORK	0x40000000
#endif



void get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   int iOsPolicy;

   int iCa2Min;

   int iCa2Max;

   if(nCa2Priority == ::multithreading::priority_normal)
   {

      iOsPolicy = SCHED_OTHER;

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = (int) ::multithreading::priority_normal;

   }
   else if(nCa2Priority > ::multithreading::priority_normal)
   {

      iOsPolicy = SCHED_RR;

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = 99;

   }
   else
   {

      iOsPolicy = SCHED_IDLE;

      iCa2Min = 0;

      iCa2Max = (int) ::multithreading::priority_normal;

   }

   int iOsMax = sched_get_priority_max(iOsPolicy);

   int iOsMin = sched_get_priority_min(iOsPolicy);

   int iOsPriority;

   if(iCa2Min == iCa2Max)
   {
      iOsPriority = 0;
   }
   else
   {
      iOsPriority = (((nCa2Priority - iCa2Min)  * (iOsMax - iOsMin)) / (iCa2Max - iCa2Min)) + iOsMin;
   }

   iOsPriority = MAX(iOsMin, MIN(iOsMax, iOsPriority));

   *piPolicy = iOsPolicy;

   pparam->sched_priority = iOsPriority;

}

int32_t get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   int iCa2Min;

   int iCa2Max;


   if(iOsPolicy == SCHED_RR)
   {

      iCa2Min = (int) ::multithreading::priority_normal;

      iCa2Max = 99;

   }
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

   iCa2Priority = MAX(iCa2Min, MIN(iCa2Max, iCa2Priority));

   return iCa2Priority;

}


void thread_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t thread_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}


void process_get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority)
{

   get_os_priority(piPolicy, pparam, nCa2Priority);

}


int32_t process_get_scheduling_priority(int32_t iOsPolicy, const sched_param * pparam)
{

   return get_scheduling_priority(iOsPolicy, pparam);

}






namespace process
{

   CLASS_DECL_AURA bool set_priority(int32_t priority)
	{

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, priority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

	}




} // namespace core

































void __node_init_thread()
{

}

void __node_term_thread()
{

}














//thread_int_ptr < HRESULT > t_hresultCoInitialize;


bool __os_init_thread()
{

//   t_hresultCoInitialize = ::CoInitializeEx(NULL,COINIT_MULTITHREADED);
//
//   if(FAILED(t_hresultCoInitialize))
//   {
//
//      if(t_hresultCoInitialize.operator HRESULT() == RPC_E_CHANGED_MODE)
//      {
//
//         t_hresultCoInitialize = ::CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);
//
//         if(FAILED(t_hresultCoInitialize))
//         {
//
//            ::simple_message_box(NULL,"Failed to ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);
//
//            return false;
//
//         }
//
//      }
//      else
//      {
//
//         ::simple_message_box(NULL,"Failed to ::CoInitializeEx(NULL, COINIT_MULTITHREADED) at __node_pre_init","__node_pre_init failure",MB_ICONEXCLAMATION);
//
//         return false;
//
//      }
//
//   }

   return true;

}



bool __os_term_thread()
{

//   if(SUCCEEDED(t_hresultCoInitialize))
//   {
//
//      CoUninitialize();
//
//   }

   return true;

}
