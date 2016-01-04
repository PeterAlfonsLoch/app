#pragma once


class var;
class id;
class string_format;


namespace calculator
{


   class value;


} // namespace calculator


namespace core
{


   class property;

}


extern CLASS_DECL_AURA const char trailingBytesForUTF8[256];

#ifdef MACOS
#undef err_none
#endif

namespace str
{



   enum e_pad
   {
      pad_left,
      pad_right
   };

   enum e_err
   {
      err_none,
      err_invalid_utf8_character
   };


   CLASS_DECL_AURA extern e_err g_eerr;


   void CLASS_DECL_AURA increment_digit_letter(string & str);
   int32_t  CLASS_DECL_AURA compare(const char * psz1, const char * psz2);
   int32_t  CLASS_DECL_AURA compare_ci(const char * psz1, const char * psz2);
   bool CLASS_DECL_AURA equals(const char * psz1, const char * psz2);
   bool CLASS_DECL_AURA equals_ci(const char * psz1, const char * psz2);
   string CLASS_DECL_AURA equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);
   string CLASS_DECL_AURA equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);


   inline bool begins(const char * psz,string & strFed, const string & strPrefix);
   inline bool begins(const string & str,string & strFed,const string & strPrefix);
   inline bool begins(const id & id,string & strFed,const string & strPrefix);


   inline bool begins(const char * psz, const string & strPrefix);
   inline bool begins(const string & str, const string & strPrefix);
   inline bool begins(const id & id, const string & strPrefix);
   inline bool begins_with(const char * psz, const string & strPrefix);
   inline bool begins_with(const string & str, const string & strPrefix);


   void CLASS_DECL_AURA begin(wstring & wstr, const unichar * lpcszPrefix);

   bool CLASS_DECL_AURA begins(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_AURA begins(const wstring & str, const unichar * lpcszPrefix);
   bool CLASS_DECL_AURA begins_with(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_AURA begins_with(const wstring & str, const unichar * lpcszPrefix);


   bool CLASS_DECL_AURA begins_ci(const char * lpcsz, const char * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_AURA begins_ci_iws(const char * psz, const char * lpcszPrefix);
   bool CLASS_DECL_AURA begins_ci_iws(const string & str, const char * lpcszPrefix);


   bool CLASS_DECL_AURA begins_ci(const unichar * lpcsz, const unichar * lpcszPrefix);
   bool CLASS_DECL_AURA begins_ci(const wstring & wstr, const unichar * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_AURA begins_ci_iws(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_AURA begins_ci_iws(const wstring & str, const unichar * lpcszPrefix);



   inline bool begins_eat(string & str, const string & strPrefix);
   bool CLASS_DECL_AURA begins_eat_ci(string & str, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AURA begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   inline bool begins_eat(var & var,const string & strPrefix);
   bool CLASS_DECL_AURA begins_eat_ci(var & var, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AURA begins_eat_ci(var & var, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   inline bool begins_eat(property & property, const string & strPrefix);
   bool CLASS_DECL_AURA begins_eat_ci(property & property, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AURA begins_eat_ci(property & property, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   bool CLASS_DECL_AURA while_begins_with_chars_eat(string & str, const char * lpcszChars);
   bool CLASS_DECL_AURA while_begins_with_chars_eat_ci(string & str, const char * lpcszChars); // case insensitive
   bool CLASS_DECL_AURA ends(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_AURA ends_ci(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_AURA ends_ci(const string & str, const char * lpcszSuffix);
   bool CLASS_DECL_AURA ends_ci(const var & var, const char * lpcszSuffix);
   bool CLASS_DECL_AURA ends_eat(string & str, const char * lpcszSuffix);
   bool CLASS_DECL_AURA ends_eat_ci(string & str, const char * lpcszSuffix);
   void CLASS_DECL_AURA copy(string & str, const char * lpcsz, int32_t iCount);
   string CLASS_DECL_AURA replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);
   string CLASS_DECL_AURA replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);

   string CLASS_DECL_AURA random_replace(::aura::application * papp, const stringa & straReplacement, const stringa & straSearch, const char * psz);

   strsize CLASS_DECL_AURA find_first(const stringa & straSearch, index & iFound, const string & str, index iStart = 0);

   strsize CLASS_DECL_AURA find_ci(const string & strFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_ci(const string & strFind   , const char   * psz, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_ci(const char   * pszFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_ci(const char   * pszFind   , const char   * psz, strsize iStart = 0);


   strsize CLASS_DECL_AURA find_ci(const char   * pszFind,const string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_AURA find_file_extension(const char * pszExtension,const string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_AURA find_ww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_wwci(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_aww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AURA find_awwci(const char * pszFind, const char * psz, strsize iStart = 0);
   string CLASS_DECL_AURA has_char(const char * pszIfHasChar, const char * pszBefore = NULL, const char * pszAfter = NULL);
   bool CLASS_DECL_AURA has_upper(const char * psz);
   bool CLASS_DECL_AURA has_lower(const char * psz);
   bool CLASS_DECL_AURA has_digit(const char * psz);
   void CLASS_DECL_AURA calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AURA has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AURA has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AURA has_all_v1(const char * psz);
   string CLASS_DECL_AURA if_null(const char * psz, const char * pszIfNull = NULL);


   FORCEINLINE  const char * __utf8_inc(const char * psz) { return psz + 1 + trailingBytesForUTF8[(byte) *psz]; }

   static_inline e_err           err() { return g_eerr; }
   static_inline void            set_err(e_err eerr){ g_eerr = eerr; }
   static_inline void            clear_err() { g_eerr = err_none; }

   CLASS_DECL_AURA  const char *   utf8_inc(const char * psz);
   CLASS_DECL_AURA  const char *   utf8_inc_slide(strsize * pslide, const char * psz);
   CLASS_DECL_AURA  const char *   utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc);


   CLASS_DECL_AURA  const char *   utf8_dec(const char * pszBeg, const char * psz);
   CLASS_DECL_AURA  string         get_utf8_char(const char *psz);
   CLASS_DECL_AURA  string         get_utf8_char(const char *psz, const char * pszEnd);
   CLASS_DECL_AURA  bool           get_utf8_char(string & strChar, const char * & psz, const char * pszEnd);
   CLASS_DECL_AURA  string         get_utf8_char(const char * pszBeg, const char *psz, strsize i);
   CLASS_DECL_AURA  string         utf8_next_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_AURA  string         utf8_previous_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_AURA  string         uni_to_utf8(int64_t ch);

   CLASS_DECL_AURA  const char *   utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz);


   CLASS_DECL_AURA  bool           to(const char * psz, int32_t & i);
   CLASS_DECL_AURA  bool           to(const char * psz, int64_t & i);
   CLASS_DECL_AURA  bool           to(const char * psz, int32_t & i, int32_t iBase);
   CLASS_DECL_AURA  bool           to(const char * psz, int64_t & i, int32_t iBase);
   CLASS_DECL_AURA  bool           to(const char * psz, uint32_t & i);
   CLASS_DECL_AURA  bool           to(const char * psz, uint64_t & i);
   CLASS_DECL_AURA  bool           to(const char * psz, uint32_t & i, int32_t iBase);
   CLASS_DECL_AURA  bool           to(const char * psz, uint64_t & i, int32_t iBase);

   CLASS_DECL_AURA  bool           trim_any_quotes(string & str);
   CLASS_DECL_AURA  bool           paired_trim(string & str, char ch);
   CLASS_DECL_AURA  bool           trim(string & str);
   CLASS_DECL_AURA  bool           _008Trim(string & str);


   CLASS_DECL_AURA  int_ptr        to_int_ptr(const char * psz);
   CLASS_DECL_AURA  int32_t            to_int(const char * psz);
   CLASS_DECL_AURA  uint32_t   to_uint(const char * psz);


   /** C++ Sockets Library \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/

   //CLASS_DECL_AURA string l2string(long l); // please use itoa
   //CLASS_DECL_AURA string bigint2string(uint64_t l); // please use itoa
   CLASS_DECL_AURA int64_t         to_int64(const string & str) ;
   CLASS_DECL_AURA int64_t         to_int64(const char * psz) ;
   CLASS_DECL_AURA uint64_t        to_uint64(const string & str) ;
   CLASS_DECL_AURA uint64_t        to_uint64(const char * psz) ;

   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/



   inline CLASS_DECL_AURA int32_t      to_with_fallback(const char * psz, int32_t iDefault){ to(psz, iDefault); return iDefault; }
   inline CLASS_DECL_AURA int64_t  to_with_fallback(const char * psz, int64_t & iDefault) { to(psz, iDefault); return iDefault; }
   inline CLASS_DECL_AURA int32_t      to_with_fallback(const char * psz, int32_t iDefault, int32_t iBase){ to(psz, iDefault, iBase); return iDefault; }
   inline CLASS_DECL_AURA int64_t  to_with_fallback(const char * psz, int64_t & iDefault, int32_t iBase) { to(psz, iDefault, iBase); return iDefault; }



   inline CLASS_DECL_AURA string  from(int32_t i);
   inline CLASS_DECL_AURA string  from(uint32_t ui);
   inline CLASS_DECL_AURA string  from(int64_t i);
   inline CLASS_DECL_AURA string  from(uint64_t ui);
   inline CLASS_DECL_AURA string  from(const var & var);
   inline CLASS_DECL_AURA string  from(const id & id);
   inline CLASS_DECL_AURA string  from(double d);
   inline CLASS_DECL_AURA string  from(float f);


   CLASS_DECL_AURA  string &       from(string & str, int32_t i);
   CLASS_DECL_AURA  string &       from(string & str, uint32_t ui);
   CLASS_DECL_AURA  string &       from(string & str, int64_t i);
   CLASS_DECL_AURA  string &       from(string & str, uint64_t ui);
   CLASS_DECL_AURA  string &       from(string & str, float f);
   CLASS_DECL_AURA  string &       from(string & str, double d);
   inline CLASS_DECL_AURA string & from(string & str, const id & id);
   inline CLASS_DECL_AURA string & from(string & str, const var & var);

   //inline CLASS_DECL_AURA string   i64toa(int64_t i);

   CLASS_DECL_AURA  string         zero_pad(const string & strSrc,int iPad);
   CLASS_DECL_AURA  int32_t        get_escaped_char(const char * str, strsize pos, strsize &retPos);
   CLASS_DECL_AURA  bool           get_curly_content(const char * psz, string & str);
   CLASS_DECL_AURA  bool           is_simple_natural(const char * psz, strsize iCount = -1);

   CLASS_DECL_AURA string          to_lower(const char * psz);
   CLASS_DECL_AURA string          to_upper(const char * psz);


   string CLASS_DECL_AURA GetWindowText(oswindow oswindow);

   string CLASS_DECL_AURA get_word(
      const char * psz,
      const char * pszSeparator,
      bool bWithSeparator = false,
      // if end is separator, return entire string if separator is not found
      // otherwise, return is_empty
      bool bEndIsSeparator = true);

   CLASS_DECL_AURA void consume(const char * & pszXml, const char * psz);
   CLASS_DECL_AURA void consume(const char * & pszXml, const char * psz, const char * pszEnd);
   CLASS_DECL_AURA void consume(const char * & pszXml, const char * psz, ::count iLen, const char * pszEnd);
   CLASS_DECL_AURA void consume_spaces(const char * & pszXml, ::count iMinimumCount = 1);
   CLASS_DECL_AURA uint64_t consume_natural(const char * & pszXml, uint64_t uiMax = ((uint64_t) -1), uint64_t uiMin = 0);
   CLASS_DECL_AURA string consume_hex(const char * & pszXml);
   CLASS_DECL_AURA void consume_spaces(const char * & pszXml, ::count iMinimumCount, const char * pszEnd);
   CLASS_DECL_AURA string consume_nc_name(const char * & pszXml);
   CLASS_DECL_AURA string consume_quoted_value(const char * & pszXml);
   CLASS_DECL_AURA string consume_quoted_value(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_AURA string consume_quoted_value_ex(const char * & pszXml,const char * pszEnd);
   CLASS_DECL_AURA string consume_spaced_value(string & str);
   CLASS_DECL_AURA string consume_spaced_value(const char * & pszXml);
   CLASS_DECL_AURA string consume_spaced_value(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_AURA string consume_command_line_argument(string & str);
   CLASS_DECL_AURA string consume_command_line_argument(const char * & pszXml);
   CLASS_DECL_AURA string consume_command_line_argument(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_AURA bool begins_consume(const char * & pszXml, const char * psz);

   CLASS_DECL_AURA bool xml_is_comment(const char * pszXml);
   CLASS_DECL_AURA string xml_consume_comment(const char * & pszXml);

   CLASS_DECL_AURA string consume_c_quoted_value(const char * & pszXml);

   CLASS_DECL_AURA string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad);

   inline ::count ilen(const char * psz) { return (count) strlen(psz); }
   inline int64_t len(const char * psz) { return (int64_t) strlen(psz); }


   template < class TYPE >
   inline TYPE from_string(const char * psz);

   CLASS_DECL_AURA void format(string_format * pformat,char const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,byte const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,int16_t const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,uint16_t const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,int32_t const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,uint32_t const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,int64_t const & i);

   CLASS_DECL_AURA void format(string_format * pformat,uint64_t const & i);

   CLASS_DECL_AURA void format(string_format * pformat,double const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,float const &  i);

   CLASS_DECL_AURA void format(string_format * pformat,void * const & p);

   CLASS_DECL_AURA void format(string_format * pformat,const void * const & p);

   CLASS_DECL_AURA void format(string_format * pformat,byte * const & p);

   CLASS_DECL_AURA void format(string_format * pformat,const char * const & psz);

   CLASS_DECL_AURA void format(string_format * pformat,const string & str);

   CLASS_DECL_AURA void format(string_format * pformat,const lparam & lparam);

#ifdef LINUX

   inline CLASS_DECL_AURA void format(string_format * pformat,const pthread & p)
   {

      ::str::format(pformat, p.m_thread);

   }

#endif

   template < class TYPE >
   void format_type(string_format * pformat,const TYPE & t)
   {
      ::str::format(pformat, t);
   }

   CLASS_DECL_AURA bool simple_escaped(const string & str,strsize pos);

#ifdef WINDOWS

   inline void format(string_format * pformat,const DWORD & dw) { return format(pformat,(const uint32_t &)dw);  }

#endif


   //inline bool begins(const id & id, const string & strPrefix) { return begins(id.m_psz, strPrefix); }


} // namespace str




template < typename T >
inline c_number < T > & c_number < T >::from(const string & str)
{
   ::str::to(str, m_number);
   return *this;
}





