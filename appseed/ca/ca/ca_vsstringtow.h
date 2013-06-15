#pragma once


class CLASS_DECL_ca vsstringtow :
   public vsstring
{
public:

   wstring * m_pwstring;

   vsstringtow(wstring & str, int32_t iAllocCount = 0);
   ~vsstringtow();


   using vsstring::operator = ;

   inline operator const char * () { return m_psz; }
   inline operator char * () { return m_psz; }

};
