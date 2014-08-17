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
      wstring_data::free(m_pwsz);
      m_pwsz = NULL;
   }
}
