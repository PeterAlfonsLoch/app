//
//  ansios_thread_impl.cpp
//  axis
//
//
//

#include "framework.h"
#include <fcntl.h>


namespace ansios
{


   thread_impl::thread_impl(sp(::axis::application) papp) :
   element(papp),
   ::thread_impl(papp)
   {


   }






   thread_impl::~thread_impl()
   {


   }





	unsigned long MillisecondCounter ()
	{
		timeval tv;
		gettimeofday(&tv, 0);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}


} // namespace mac










void __end_thread_impl(axis::application*, unsigned int, bool)

{

}


void __term_thread_impl(axis::application*, HINSTANCE__*)
{
}











void CLASS_DECL_AXIS __init_thread()
{

}






void CLASS_DECL_AXIS __term_thread()
{

}






