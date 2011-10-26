#include "StdAfx.h"

vsstringtow::vsstringtow(wstring & str, int iAllocCount)
{
   m_pwstring = &str;
   m_psz = NULL;
   alloc(iAllocCount);
}

vsstringtow::~vsstringtow()
{
   if(m_pwstring != NULL)
   {
      *m_pwstring = utf8_to_16(m_psz);
   }
   if(m_psz != NULL)
   {
      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      ca2_free(m_psz);
      m_psz = NULL;
   }
}
