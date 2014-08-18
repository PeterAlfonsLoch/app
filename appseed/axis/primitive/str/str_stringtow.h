#pragma once


class CLASS_DECL_AXIS stringtow :
   public string
{
public:

   wstring * m_pwstring;

   stringtow(wstring & str, int32_t iAllocCount = 0);
   ~stringtow();


   using string::operator = ;

   inline operator const char * () { return c_str(); }
   inline operator char * () { return (char *) c_str(); }

};
