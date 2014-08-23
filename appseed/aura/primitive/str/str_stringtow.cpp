#include "framework.h"

stringtow::stringtow(wstring & str, int32_t iAllocCount)
{
   m_pwstring = &str;
   GetBufferSetLength(iAllocCount);
}

stringtow::~stringtow()
{

   ReleaseBuffer();

   if(m_pwstring != NULL)
   {

      ::count iLen = utf16_len(c_str());

      m_pwstring->alloc(iLen + 1);

      utf8_to_utf16(*m_pwstring, c_str());

      m_pwstring->set_length(iLen);

   }

   /*if(m_psz != NULL)
   {

      //g_pfixedallocaWstring->free(m_psz, (wcslen(m_psz) + 1) * 2);
      memory_free_dbg(m_psz, 0);
      m_psz = NULL;

   }*/

}
