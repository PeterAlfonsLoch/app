#include "framework.h"
#include <sys/time.h>

// http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
// http://stackoverflow.com/users/346736/jbenet

//
//inline DWORD GetTickCount()
//{
//   timeval ts;
//   gettimeofday(&ts,0);
//   return (ts.tv_sec * 1000 + (ts.tv_usec / 1000)) % 0xffffffffu;
//
//}
//
//
//
//DWORD get_tick_count()
//{
//
//   return (DWORD) GetTickCount();
//
//}
//
//
//
//
//
//
//
#include <mach/clock.h>
#include <mach/mach.h>
//
//

uint64_t get_nanos()
{
    
    mach_timespec ts;
    
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts.tv_sec = mts.tv_sec;
    ts.tv_nsec = mts.tv_nsec;
    
    return (uint64_t) ts.tv_sec * 1000 * 1000 * 1000 + (uint64_t) ts.tv_nsec;
    
}



