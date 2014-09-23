#include "framework.h"


void throw_memory_exception()
{

   throw memory_exception(get_thread_app());

}


void throw_error_exception(const char * psz)
{

   throw error_exception(get_thread_app(),psz);

}

