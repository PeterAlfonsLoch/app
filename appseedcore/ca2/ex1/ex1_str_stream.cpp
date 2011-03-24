#include "StdAfx.h"

namespace ex1
{

   DWORD_PTR str_reader::read(void *lpBuf, DWORD_PTR nCount)
   {
      UINT uiRead = min(nCount, m_pstr->get_length() - m_dwPos);
      memcpy(lpBuf, &((const char *) *m_pstr)[m_dwPos], uiRead);
      m_dwPos += uiRead;
      return uiRead;
   };

   void str_writer::write(const void *lpBuf, DWORD_PTR nCount)
   {
      string str((const char *) lpBuf, nCount);
      *m_pstr += str;
   }

} // namespace ex1

