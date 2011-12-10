#pragma once

class CLASS_DECL_c verisimple_wstring
{
public:

   wchar_t * m_pwsz;

   verisimple_wstring();
   verisimple_wstring(const wchar_t * pwsz);
   verisimple_wstring(const wchar_t * pwsz, int iCount);
   verisimple_wstring(const verisimple_wstring & wstr);
   ~verisimple_wstring();


   verisimple_wstring & operator = (const verisimple_wstring & wstr);
   verisimple_wstring & operator = (const wchar_t * pwsz);


   inline operator const wchar_t * () const { return m_pwsz; }
   inline operator const wchar_t * () { return m_pwsz; }

   void attach(const wchar_t * psz);

   wchar_t * alloc(int iCount);
   count get_length();


   count get_length() const;
   count length() const;
   count size() const;

   int CompareNoCase(const wchar_t * psz) const;
   int CompareNoCase(const verisimple_wstring &str) const;


};


typedef verisimple_wstring wstring;


CLASS_DECL_c verisimple_wstring operator + (const verisimple_wstring & wstr1, const verisimple_wstring & wstr2);
CLASS_DECL_c verisimple_wstring operator + (const verisimple_wstring & str, const wchar_t * psz);

CLASS_DECL_c wstring gen_utf8_to_16(const char * psz);