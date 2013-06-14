#pragma once

class CLASS_DECL_c wstringtovss :
   public wstring
{
public:

   vsstring * m_pstringUtf8;

   wstringtovss(vsstring & str, int32_t iAllocCount);
   ~wstringtovss();

   inline operator const wchar_t * () { return m_pwsz; }
   inline operator wchar_t * () { return m_pwsz; }

};


