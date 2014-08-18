#include "framework.h"


#ifdef LINUX
#include <unistd.h>
#endif


go_thread::go_thread(sp(::axis::application) papp, bool bRelease) :
   element(papp),
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
#ifdef _WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
   }
   if(get_run())
   {
      go();
   }
   return 0;
}

