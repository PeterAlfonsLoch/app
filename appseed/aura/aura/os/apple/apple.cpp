//
//  apple.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//

#include "framework.h"

// ThomasBS-LiveEdu.TV(LiveCoding.TV)

void * CreateDispatchQueue()
{
   
   return dispatch_queue_create (NULL, NULL);
   
}

void CancelDispatchSource(void * p)
{
   
   dispatch_source_cancel((dispatch_source_t) p);
   
}

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void (*pfnTimer)(void * p), void * p)
{
   
   dispatch_source_t timer = dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, (dispatch_queue_t) queue);
   
   if (timer)
   {
      
      dispatch_source_set_timer(timer, dispatch_walltime(NULL, 0), interval * NSEC_PER_MSEC, leeway * NSEC_PER_MSEC);
      
      dispatch_source_set_event_handler(timer, ^(){ pfnTimer(p); });
      
      dispatch_resume(timer);
      
   }
   
   return timer;
   
}


void ReleaseDispatch(void * p)
{
   
   dispatch_release((dispatch_object_t) p);
   
}


