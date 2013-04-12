#pragma once



class CLASS_DECL_ca wstringtou :
   public wstring
{
public:

   string * m_pstringUtf8;

   wstringtou(string & str, int32_t iAllocCount);
   ~wstringtou();

   inline operator const wchar_t * () { return m_pwsz; }
   inline operator wchar_t * () { return m_pwsz; }

};
