#include "framework.h"


bool __assert_failed_line(const char * lpszFileName, int32_t nLine)
{
   base_thread * pthread = ::ca2::get_thread();
   if(pthread == NULL)
      return FALSE;
   else if(pthread->m_papp->m_pcasystem->assert_failed_line(lpszFileName, nLine))
      return TRUE;
   else
      return FALSE;
}



