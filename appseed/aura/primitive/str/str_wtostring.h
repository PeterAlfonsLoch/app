#pragma once


class string;


class CLASS_DECL_AURA wtostring :
   public wstring
{
public:

   string * m_pstringUtf8;

   wtostring(string & str, int32_t iAllocCount);
   ~wtostring();

   inline operator const char16_t * () { return m_pwsz; }
   inline operator char16_t * () { return m_pwsz; }

};
