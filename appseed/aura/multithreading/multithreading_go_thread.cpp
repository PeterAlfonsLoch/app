#include "framework.h"


#if defined(LINUX) || defined(ANDROID)
#include <unistd.h>
#endif


go_thread::go_thread(::aura::application * papp) :
   object(papp),
   thread(papp),
   simple_thread(papp)
{

}


go_thread::~go_thread()
{

}

void go_thread::start()
{
   
   begin();

}


int32_t go_thread::run()
{
   
   go();

   return 0;

}

