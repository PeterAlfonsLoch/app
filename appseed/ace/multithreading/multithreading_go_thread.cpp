#include "framework.h"


#if defined(LINUX) || defined(ANDROID)
#include <unistd.h>
#endif


go_thread::go_thread(::ace::application * papp, bool bRelease) :
   object(papp),
   thread(papp),
   simple_thread(papp),
   m_bRelease(false),
   m_bStartRelease(bRelease)
{
}

go_thread::~go_thread()
{
}

void go_thread::start()
{
   m_bRelease = false;
   begin();
   m_bRelease = m_bStartRelease;
}

int32_t go_thread::run()
{
   while(get_run() && !m_bRelease)
   {
      sleep(seconds(1));
   }
   if(get_run())
   {
      go();
   }
   return 0;
}

