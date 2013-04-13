#include "framework.h"

bool __assert_failed_line(const char * lpszFileName, int32_t nLine)
{
   ::ca::thread * pthread = ::ca::get_thread();
   if(pthread == ::null())
      return FALSE;
   else if(pthread->m_papp->m_psystem->assert_failed_line(lpszFileName, nLine))
      return TRUE;
   else
      return FALSE;
}
