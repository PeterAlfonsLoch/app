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

      int iLen = utf16_len(m_psz);
      m_pwstring->alloc(iLen + 1);
      utf8_to_16(*m_pwstring, m_psz);
      m_pwstring->set_length(iLen);

   }

   if(m_psz != NULL)
   {

      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      ca2_free(m_psz);
      m_psz = NULL;

   }

}
