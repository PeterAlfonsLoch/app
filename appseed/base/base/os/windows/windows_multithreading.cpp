#include "framework.h"


_declspec(thread) void * thread_data_base::t_p = NULL;


void * thread_data::get()
{
   
   return t_p;

}
   

void thread_data::set(void * p)
{

   t_p = p;

}
