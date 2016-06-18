#include "framework.h"


inline DWORD GetTickCount()
{
   timeval ts;
   gettimeofday(&ts,0);
   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;

}



//DWORD get_tick_count()
//{
//
//   return (DWORD) GetTickCount();
//
//}
//
//
//





#include "framework.h"
#include <sys/time.h>

// http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
// http://stackoverflow.com/users/346736/jbenet

#include <mach/clock.h>
#include <mach/mach.h>

uint64_t get_nanos()
{
   
   clock_serv_t cclock;
   mach_timespec_t mts;
   host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
   clock_get_time(cclock, &mts);
   mach_port_deallocate(mach_task_self(), cclock);
   
   return ((uint64_t) mts.tv_sec * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 )+ ((uint64_t) mts.tv_nsec);
   
}



