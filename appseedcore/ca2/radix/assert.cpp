#include "StdAfx.h"

BOOL AfxAssertFailedLine(const char * lpszFileName, int nLine)
{
   if(::ca::get_thread()->m_papp->m_psystem->assert_failed_line(lpszFileName, nLine))
      return TRUE;
   else
      return FALSE;
}
