#pragma once


class string;


class CLASS_DECL_AURA wtostring :
   public wstring
{
public:

   string * m_pstringUtf8;

   wtostring(string & str, int32_t iAllocCount);
   ~wtostring();

   inline operator const unichar * () { return m_pwsz; }
   inline operator unichar * () { return m_pwsz; }

};
