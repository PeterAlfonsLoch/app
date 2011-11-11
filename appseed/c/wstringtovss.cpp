#include "StdAfx.h"

wstringtovss::wstringtovss(vsstring & str, int iAllocCount)
{
   m_pstringUtf8 = &str;
   m_pwsz = NULL;
   alloc(iAllocCount);
}

wstringtovss::~wstringtovss()
{
   if(m_pstringUtf8 != NULL)
   {
      *m_pstringUtf8 = utf16_to_8(m_pwsz);
   }
   if(m_pwsz != NULL)
   {
      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      ca2_free(m_pwsz);
      m_pwsz = NULL;
   }
}
