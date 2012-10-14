#pragma once


class CLASS_DECL_c vsstringtow :
   public vsstring
{
public:

   wstring * m_pwstring;

   vsstringtow(wstring & str, int iAllocCount = 0);
   ~vsstringtow();


   using vsstring::operator = ;

   inline operator const char * () { return m_psz; }
   inline operator char * () { return m_psz; }

};
