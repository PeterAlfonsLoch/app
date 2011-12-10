#pragma once

class CLASS_DECL_c vsstringtow :
   public vsstring
{
public:

   wstring * m_pwstring;

   vsstringtow(wstring & str, int iAllocCount);
   ~vsstringtow();

   inline operator const char * () { return m_psz; }
   inline operator char * () { return m_psz; }

};




