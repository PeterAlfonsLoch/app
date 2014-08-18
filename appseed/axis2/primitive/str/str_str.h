#pragma once


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


extern const char trailingBytesForUTF8[256];


namespace str
{

   enum e_pad
   {
      pad_left,
      pad_right
   };

   void CLASS_DECL_AXIS increment_digit_letter(string & str);
   int32_t  CLASS_DECL_AXIS compare(const char * psz1, const char * psz2);
   int32_t  CLASS_DECL_AXIS compare_ci(const char * psz1, const char * psz2);
   bool CLASS_DECL_AXIS equals(const char * psz1, const char * psz2);
   bool CLASS_DECL_AXIS equals_ci(const char * psz1, const char * psz2);
   string CLASS_DECL_AXIS equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);
   string CLASS_DECL_AXIS equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);



   bool CLASS_DECL_AXIS begins(const char * psz, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins(const string & str, const char * lpcszPrefix);
   inline bool CLASS_DECL_AXIS begins(const id & id, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_with(const char * psz, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_with(const string & str, const char * lpcszPrefix);


   void CLASS_DECL_AXIS begin(wstring & wstr, const wchar_t * lpcszPrefix);

   bool CLASS_DECL_AXIS begins(const wchar_t * psz, const wchar_t * lpcszPrefix);
   bool CLASS_DECL_AXIS begins(const wstring & str, const wchar_t * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_with(const wchar_t * psz, const wchar_t * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_with(const wstring & str, const wchar_t * lpcszPrefix);


   bool CLASS_DECL_AXIS begins_ci(const char * lpcsz, const char * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_AXIS begins_ci_iws(const char * psz, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_ci_iws(const string & str, const char * lpcszPrefix);


   bool CLASS_DECL_AXIS begins_ci(const wchar_t * lpcsz, const wchar_t * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_ci(const wstring & wstr, const wchar_t * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_AXIS begins_ci_iws(const wchar_t * psz, const wchar_t * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_ci_iws(const wstring & str, const wchar_t * lpcszPrefix);




   bool CLASS_DECL_AXIS begins_eat(string & str, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_eat_ci(string & str, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AXIS begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   bool CLASS_DECL_AXIS begins_eat(var & var, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_eat_ci(var & var, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AXIS begins_eat_ci(var & var, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   bool CLASS_DECL_AXIS begins_eat(property & property, const char * lpcszPrefix);
   bool CLASS_DECL_AXIS begins_eat_ci(property & property, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_AXIS begins_eat_ci(property & property, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   bool CLASS_DECL_AXIS while_begins_with_chars_eat(string & str, const char * lpcszChars);
   bool CLASS_DECL_AXIS while_begins_with_chars_eat_ci(string & str, const char * lpcszChars); // case insensitive
   bool CLASS_DECL_AXIS ends(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_AXIS ends_ci(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_AXIS ends_ci(const string & str, const char * lpcszSuffix);
   bool CLASS_DECL_AXIS ends_ci(const var & var, const char * lpcszSuffix);
   bool CLASS_DECL_AXIS ends_eat(string & str, const char * lpcszSuffix);
   bool CLASS_DECL_AXIS ends_eat_ci(string & str, const char * lpcszSuffix);
   void CLASS_DECL_AXIS copy(string & str, const char * lpcsz, int32_t iCount);
   string CLASS_DECL_AXIS replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);
   string CLASS_DECL_AXIS replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);

   string CLASS_DECL_AXIS random_replace(sp(::axis::application) papp, const string_array & straReplacement, const string_array & straSearch, const char * psz);

   strsize CLASS_DECL_AXIS find_first(const string_array & straSearch, index & iFound, const string & str, index iStart = 0);

   strsize CLASS_DECL_AXIS find_ci(const string & strFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_ci(const string & strFind   , const char   * psz, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_ci(const char   * pszFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_ci(const char   * pszFind   , const char   * psz, strsize iStart = 0);

   strsize CLASS_DECL_AXIS find_ww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_wwci(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_aww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_AXIS find_awwci(const char * pszFind, const char * psz, strsize iStart = 0);
   string CLASS_DECL_AXIS has_char(const char * pszIfHasChar, const char * pszBefore = NULL, const char * pszAfter = NULL);
   bool CLASS_DECL_AXIS has_upper(const char * psz);
   bool CLASS_DECL_AXIS has_lower(const char * psz);
   bool CLASS_DECL_AXIS has_digit(const char * psz);
   void CLASS_DECL_AXIS calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AXIS has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AXIS has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_AXIS has_all_v1(const char * psz);
   string CLASS_DECL_AXIS if_null(const char * psz, const char * pszIfNull = NULL);


   FORCEINLINE  const char * __utf8_inc(const char * psz) { return psz + 1 + trailingBytesForUTF8[(uchar) *psz]; }


   CLASS_DECL_AXIS  const char *   utf8_inc(const char * psz);
   CLASS_DECL_AXIS  const char *   utf8_inc_slide(strsize * pslide, const char * psz);
   CLASS_DECL_AXIS  const char *   utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc);


   CLASS_DECL_AXIS  const char *   utf8_dec(const char * pszBeg, const char * psz);
   CLASS_DECL_AXIS  string         get_utf8_char(const char *psz);
   CLASS_DECL_AXIS  string         get_utf8_char(const char *psz, const char * pszEnd);
   CLASS_DECL_AXIS  bool           get_utf8_char(string & strChar, const char * & psz, const char * pszEnd);
   CLASS_DECL_AXIS  string         get_utf8_char(const char * pszBeg, const char *psz, strsize i);
   CLASS_DECL_AXIS  string         utf8_next_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_AXIS  string         utf8_previous_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_AXIS  string         uni_to_utf8(int64_t ch);

   CLASS_DECL_AXIS  const char *   utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz);


   CLASS_DECL_AXIS  bool           to(const char * psz, int32_t & i);
   CLASS_DECL_AXIS  bool           to(const char * psz, int64_t & i);
   CLASS_DECL_AXIS  bool           to(const char * psz, int32_t & i, int32_t iAxis);
   CLASS_DECL_AXIS  bool           to(const char * psz, int64_t & i, int32_t iAxis);
   CLASS_DECL_AXIS  bool           to(const char * psz, uint32_t & i);
   CLASS_DECL_AXIS  bool           to(const char * psz, uint64_t & i);
   CLASS_DECL_AXIS  bool           to(const char * psz, uint32_t & i, int32_t iAxis);
   CLASS_DECL_AXIS  bool           to(const char * psz, uint64_t & i, int32_t iAxis);


   CLASS_DECL_AXIS  int_ptr        to_int_ptr(const char * psz);
   CLASS_DECL_AXIS  int32_t            to_int(const char * psz);
   CLASS_DECL_AXIS  uint32_t   to_uint(const char * psz);


   /** C++ Sockets Library \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/

   //CLASS_DECL_AXIS string l2string(long l); // please use itoa
   //CLASS_DECL_AXIS string bigint2string(uint64_t l); // please use itoa
   CLASS_DECL_AXIS int64_t         to_int64(const string & str) ;
   CLASS_DECL_AXIS int64_t         to_int64(const char * psz) ;
   CLASS_DECL_AXIS uint64_t        to_uint64(const string & str) ;
   CLASS_DECL_AXIS uint64_t        to_uint64(const char * psz) ;

   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/



   inline CLASS_DECL_AXIS int32_t      to_with_fallback(const char * psz, int32_t iDefault){ to(psz, iDefault); return iDefault; }
   inline CLASS_DECL_AXIS int64_t  to_with_fallback(const char * psz, int64_t & iDefault) { to(psz, iDefault); return iDefault; }
   inline CLASS_DECL_AXIS int32_t      to_with_fallback(const char * psz, int32_t iDefault, int32_t iAxis){ to(psz, iDefault, iAxis); return iDefault; }
   inline CLASS_DECL_AXIS int64_t  to_with_fallback(const char * psz, int64_t & iDefault, int32_t iAxis) { to(psz, iDefault, iAxis); return iDefault; }



   inline CLASS_DECL_AXIS string  from(int32_t i);
   inline CLASS_DECL_AXIS string  from(uint32_t ui);
   inline CLASS_DECL_AXIS string  from(int64_t i);
   inline CLASS_DECL_AXIS string  from(uint64_t ui);
   inline CLASS_DECL_AXIS string  from(const var & var);
   inline CLASS_DECL_AXIS string  from(const id & id);
   inline CLASS_DECL_AXIS string  from(double d);
   inline CLASS_DECL_AXIS string  from(float f);


   CLASS_DECL_AXIS  string &       from(string & str, int32_t i);
   CLASS_DECL_AXIS  string &       from(string & str, uint32_t ui);
   CLASS_DECL_AXIS  string &       from(string & str, int64_t i);
   CLASS_DECL_AXIS  string &       from(string & str, uint64_t ui);
   CLASS_DECL_AXIS  string &       from(string & str, float f);
   CLASS_DECL_AXIS  string &       from(string & str, double d);
   inline CLASS_DECL_AXIS string & from(string & str, const id & id);
   inline CLASS_DECL_AXIS string & from(string & str, const var & var);

   //inline CLASS_DECL_AXIS string   i64toa(int64_t i);


   CLASS_DECL_AXIS  int32_t        get_escaped_char(const char * str, strsize pos, strsize &retPos);
   CLASS_DECL_AXIS  bool           get_curly_content(const char * psz, string & str);
   CLASS_DECL_AXIS  bool           is_simple_natural(const char * psz);

   CLASS_DECL_AXIS string          to_lower(const char * psz);
   CLASS_DECL_AXIS string          to_upper(const char * psz);


   string CLASS_DECL_AXIS get_window_text(oswindow oswindow);

   string CLASS_DECL_AXIS get_word(
      const char * psz,
      const char * pszSeparator,
      bool bWithSeparator = false,
      // if end is separator, return entire string if separator is not found
      // otherwise, return is_empty
      bool bEndIsSeparator = true);

   CLASS_DECL_AXIS void consume(const char * & pszXml, const char * psz);
   CLASS_DECL_AXIS void consume(const char * & pszXml, const char * psz, const char * pszEnd);
   CLASS_DECL_AXIS void consume(const char * & pszXml, const char * psz, ::count iLen, const char * pszEnd);
   CLASS_DECL_AXIS void consume_spaces(const char * & pszXml, ::count iMinimumCount = 1);
   CLASS_DECL_AXIS uint64_t consume_natural(const char * & pszXml, uint64_t uiMax = ((uint64_t) -1), uint64_t uiMin = 0);
   CLASS_DECL_AXIS string consume_hex(const char * & pszXml);
   CLASS_DECL_AXIS void consume_spaces(const char * & pszXml, ::count iMinimumCount, const char * pszEnd);
   CLASS_DECL_AXIS string consume_nc_name(const char * & pszXml);
   CLASS_DECL_AXIS string consume_quoted_value(const char * & pszXml);
   CLASS_DECL_AXIS string consume_quoted_value(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_AXIS bool begins_consume(const char * & pszXml, const char * psz);

   CLASS_DECL_AXIS bool xml_is_comment(const char * pszXml);
   CLASS_DECL_AXIS string xml_consume_comment(const char * & pszXml);

   CLASS_DECL_AXIS string consume_c_quoted_value(const char * & pszXml);

   CLASS_DECL_AXIS string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad);

   inline ::count ilen(const char * psz) { return (count) strlen(psz); }
   inline int64_t len(const char * psz) { return (int64_t) strlen(psz); }


   template < class TYPE >
   inline TYPE from_string(const char * psz);

   void format(string_format * pformat, char const &  i);

   void format(string_format * pformat, uchar const &  i);

   void format(string_format * pformat, int16_t const &  i);

   void format(string_format * pformat, uint16_t const &  i);

   void format(string_format * pformat, int32_t const &  i);

   void format(string_format * pformat, uint32_t const &  i);

   void format(string_format * pformat, int64_t const & i);

   void format(string_format * pformat, uint64_t const & i);

   void format(string_format * pformat, double const &  i);

   void format(string_format * pformat, float const &  i);

   void format(string_format * pformat, void * const & p);

   void format(string_format * pformat, const void * const & p);

   void format(string_format * pformat, uchar * const & p);

   void format(string_format * pformat, const char * const & psz);

   void format(string_format * pformat, const string & str);

   void format(string_format * pformat, const calculator::value & val);

   void format(string_format * pformat, const lparam & lparam);



   bool CLASS_DECL_AXIS simple_escaped(const string & str, strsize pos);


   inline bool CLASS_DECL_AXIS begins(const id & id, const char * lpcszPrefix) { return begins((const string &) *id.m_pstr, lpcszPrefix); }


} // namespace str




template < typename T >
inline c_number < T > & c_number < T >::from(const string & str)
{
   ::str::to(str, m_number);
   return *this;
}



