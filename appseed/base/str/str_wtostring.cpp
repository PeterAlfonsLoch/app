#include "framework.h"

wtostring::wtostring(string & str, int32_t iAllocCount)
{
   m_pstringUtf8 = &str;
   m_pwsz = NULL;
   alloc(iAllocCount);
}

wtostring::~wtostring()
{
   if(m_pstringUtf8 != NULL)
   {
      *m_pstringUtf8 = ::str::international::unicode_to_utf8(m_pwsz);
   }
   if(m_pwsz != NULL)
   {
      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      _ca_free(m_pwsz, 0);
      m_pwsz = NULL;
   }
}
