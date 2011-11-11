#pragma once

class CLASS_DECL_____ verisimple_string
{
public:

   char * m_psz;


   enum
   {
      npos = -1,
   };

   verisimple_string();
   verisimple_string(const char * psz);
   verisimple_string(char ch);
   verisimple_string(const char * psz, count count);
   verisimple_string(const verisimple_string & str);
   ~verisimple_string();

   void trim_left();
   void trim_right();
   void trim();


    char & operator [] (int iIndex);
    char operator [] (int iIndex) const;



   verisimple_string & operator = (const verisimple_string &str);
   verisimple_string & operator = (const char * psz);
   verisimple_string & operator = (char ch);

   bool operator == (const char * psz) const;
   bool operator == (const verisimple_string &str) const;

   bool operator != (const char * psz) const;
   bool operator != (const verisimple_string &str) const;

   int CompareCase(const char * psz) const;
   int CompareCase(const verisimple_string &str) const;

   int CompareNoCase(const char * psz) const;
   int CompareNoCase(const verisimple_string &str) const;

   void attach(const char * psz);

   inline operator const char * () const { return m_psz; }
   inline operator const char * () { return m_psz; }

   inline operator const void * () const { return m_psz; }
   inline operator const void * () { return m_psz; }

   inline operator void * () const { return m_psz; }
   inline operator void * () { return m_psz; }

   inline operator char * () const { return m_psz; }
   inline operator char * () { return m_psz; }

   verisimple_string & operator += (const char * psz);
   verisimple_string & operator += (const verisimple_string & str);

   bool is_empty() const;
   bool has_char() const;

   char * alloc(int iCount);
   count get_length() const;
   count length() const;
   count size() const;

   bool begins_eat_ci(const char * pszPrefix);
   bool begins_eat_ci(const verisimple_string & strPrefix);
   bool begins_ci(const char * pszPrefix) const;
   bool begins_ci(const verisimple_string & strPrefix) const;
   bool ends_ci(const char * pszSuffix) const;
   bool ends_ci(const verisimple_string & strSuffix) const;

   bool begins_eat(const char * pszPrefix);
   bool begins_eat(const verisimple_string & strPrefix);
   bool begins(const char * pszPrefix) const;
   bool begins(const verisimple_string & strPrefix) const;
   bool ends(const char * pszSuffix) const;
   bool ends(const verisimple_string & strSuffix) const;

   verisimple_string substr(int offset, count count = -1) const;

   int find(const char * pszFind, int iStart = 0) const;
   int find(const verisimple_string & strFind, int iStart = 0) const;
   void replace(const char * pszFind, const char * pszReplace);

   int find_ci(const char * pszFind, int iStart = 0) const;
   int find_ci(const verisimple_string & strFind, int iStart = 0) const;
   void replace_ci(const char * pszFind, const char * pszReplace);

   int rfind(char ch) const;
   int rfind(char ch, int iStart) const;




   void clear();


};

CLASS_DECL_____ verisimple_string operator + (const verisimple_string & str1, const verisimple_string & str2);
CLASS_DECL_____ verisimple_string operator + (const verisimple_string & str, const char * psz);
CLASS_DECL_____ verisimple_string operator + (const char * psz, const verisimple_string & str);
CLASS_DECL_____ verisimple_string operator + (const verisimple_string & str, char ch);
CLASS_DECL_____ verisimple_string operator + (char ch, const verisimple_string & str);

typedef verisimple_string vsstring;




CLASS_DECL_____ vsstring std_gen_international_unicode_to_utf8(const wchar_t * psz);

CLASS_DECL_____ vsstring url_encode_dup(const char * psz);

CLASS_DECL_____ vsstring str_replace_dup(const char * psz, const char * pszFind, const char * pszReplace);

CLASS_DECL_____ vsstring itoa_dup(int i);

CLASS_DECL_____ vsstring i64toa_dup(int64_t i);

#ifdef WINDOWS

CLASS_DECL_____ vsstring read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
#endif


#define _unitext(text) (std_gen_international_unicode_to_utf8(L##text))

