#pragma once


class CLASS_DECL_____ wstringtovss :
   public wstring
{
public:

   vsstring * m_pstringUtf8;

   wstringtovss(vsstring & str, int iAllocCount);
   ~wstringtovss();

   inline operator const wchar_t * () { return m_pwsz; }
   inline operator wchar_t * () { return m_pwsz; }

};
