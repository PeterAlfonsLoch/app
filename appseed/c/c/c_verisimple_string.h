#pragma once


class CLASS_DECL_c verisimple_string
{
public:

   char * m_psz;


   enum
   {
      npos = -1,
   };

   verisimple_string();
   verisimple_string(const wchar_t * psz);
   verisimple_string(const char * psz);
   verisimple_string(char ch);
   verisimple_string(const char * psz, int_ptr count);
   verisimple_string(const verisimple_string & str);
   ~verisimple_string();

   void trim_left();
   void trim_right();
   void trim();


    char & operator [] (int_ptr iIndex);
    char operator [] (int_ptr iIndex) const;



   verisimple_string & operator = (const verisimple_string &str);
   verisimple_string & operator = (const char * psz);
   verisimple_string & operator = (const wchar_t * pwsz);
   verisimple_string & operator = (char ch);

   bool operator == (const char * psz) const;
   bool operator == (const verisimple_string &str) const;

   bool operator != (const char * psz) const;
   bool operator != (const verisimple_string &str) const;

   int32_t CompareCase(const char * psz) const;
   int32_t CompareCase(const verisimple_string &str) const;

   int32_t CompareNoCase(const char * psz) const;
   int32_t CompareNoCase(const verisimple_string &str) const;

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

   char * alloc(int_ptr iCount);
   int_ptr get_length() const;
   int_ptr length() const;
   int_ptr size() const;

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

   verisimple_string substr(int_ptr offset, int_ptr count = -1) const;

   int_ptr find(const char * pszFind, int_ptr iStart = 0) const;
   int_ptr find(const verisimple_string & strFind, int_ptr iStart = 0) const;
   void replace(const char * pszFind, const char * pszReplace);

   int_ptr find_ci(const char * pszFind, int_ptr iStart = 0) const;
   int_ptr find_ci(const verisimple_string & strFind, int_ptr iStart = 0) const;
   void replace_ci(const char * pszFind, const char * pszReplace);

   int_ptr rfind(char ch) const;
   int_ptr rfind(char ch, int_ptr iStart) const;


#ifdef METROWIN
   inline operator Platform::String ^ ();
#endif


   void clear();

   verisimple_string & append(char ch)
   {
      return *this += ch;
   }

   verisimple_string & append(char ch, ::int_ptr c)
   {

      while(c > 0)
      {
         append(ch);
         c--;
      }

      return *this;

   }

};

CLASS_DECL_c verisimple_string operator + (const verisimple_string & str1, const verisimple_string & str2);
CLASS_DECL_c verisimple_string operator + (const verisimple_string & str, const char * psz);
CLASS_DECL_c verisimple_string operator + (const char * psz, const verisimple_string & str);
CLASS_DECL_c verisimple_string operator + (const verisimple_string & str, char ch);
CLASS_DECL_c verisimple_string operator + (char ch, const verisimple_string & str);

typedef verisimple_string vsstring;




#ifdef WINDOWS

CLASS_DECL_c vsstring read_resource_as_string_dup(HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);

#endif

CLASS_DECL_c vsstring std_gen_international_unicode_to_utf8(const wchar_t * psz);

CLASS_DECL_c vsstring url_encode_dup(const char * psz);

CLASS_DECL_c vsstring str_replace_dup(const char * psz, const char * pszFind, const char * pszReplace);

CLASS_DECL_c vsstring itoa_dup(int64_t i);

CLASS_DECL_c vsstring itohex_dup(int64_t i);

CLASS_DECL_c vsstring itohexpad_dup(int64_t i, int32_t iPad);

CLASS_DECL_c vsstring gen_utf16_to_8(const wchar_t * psz);

CLASS_DECL_c void zero_pad(vsstring & str, int_ptr iPad);

CLASS_DECL_c vsstring get_md5(const void * data, int_ptr c = -1);

CLASS_DECL_c vsstring file_as_string_dup(const char * path);

#define _unitext(text) (std_gen_international_unicode_to_utf8(L##text))

