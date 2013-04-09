#include "framework.h"

wstringtovss::wstringtovss(vsstring & str, int32_t iAllocCount)
{
   m_pstringUtf8 = &str;
   m_pwsz = ::null();
   alloc(iAllocCount);
}

wstringtovss::~wstringtovss()
{
   if(m_pstringUtf8 != ::null())
   {
      m_pstringUtf8->attach(utf16_to_8(m_pwsz));
   }
   if(m_pwsz != ::null())
   {
      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      _ca_free(m_pwsz, 0);
      m_pwsz = ::null();
   }
}
