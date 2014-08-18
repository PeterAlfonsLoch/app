#pragma once


class string;


class CLASS_DECL_AXIS wtostring :
   public wstring
{
public:

   string * m_pstringUtf8;

   wtostring(string & str, int32_t iAllocCount);
   ~wtostring();

   inline operator const wchar_t * () { return m_pwsz; }
   inline operator wchar_t * () { return m_pwsz; }

};
