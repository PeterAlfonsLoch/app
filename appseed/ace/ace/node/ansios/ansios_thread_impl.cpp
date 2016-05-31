//#include "framework.h"
//#include "ansios.h"
//#include <fcntl.h>
//#include <sys/time.h>

void __clear_mq();

namespace ansios
{


//   thread_impl::thread_impl(::ace::application * papp) :
//   object(papp),
//   ::thread_impl(papp)
//   {
//
//
//   }
//
//
//
//
//
//
//   thread_impl::~thread_impl()
//   {
//
//      __clear_mq();
//
//   }
//




	unsigned long MillisecondCounter ()
	{
		timeval tv;
		gettimeofday(&tv, 0);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}


} // namespace macos










void __end_thread_impl(ace::application*, unsigned int, bool)

{

}


void __term_thread_impl(ace::application*, HINSTANCE__*)
{
}











void CLASS_DECL_ACE __init_thread()
{

}






void CLASS_DECL_ACE __term_thread()
{

}






