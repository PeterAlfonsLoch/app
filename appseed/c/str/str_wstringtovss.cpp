#include "framework.h"

wstringtovss::wstringtovss(vsstring & str, int32_t iAllocCount)
{
   m_pstringUtf8 = &str;
   m_pwsz = NULL;
   alloc(iAllocCount);
}

wstringtovss::~wstringtovss()
{
   if(m_pstringUtf8 != NULL)
   {
      m_pstringUtf8->attach(utf16_to_8_dup(m_pwsz));
   }
   if(m_pwsz != NULL)
   {
      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      _ca_free(m_pwsz, 0);
      m_pwsz = NULL;
   }
}
