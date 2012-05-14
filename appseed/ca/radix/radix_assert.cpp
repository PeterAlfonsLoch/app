#include "framework.h"

BOOL __assert_failed_line(const char * lpszFileName, int nLine)
{
   ::ca::thread * pthread = ::ca::get_thread();
   if(pthread == NULL)
      return FALSE;
   else if(pthread->m_papp->m_psystem->assert_failed_line(lpszFileName, nLine))
      return TRUE;
   else
      return FALSE;
}
