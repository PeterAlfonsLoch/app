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


extern CLASS_DECL_ACE const char trailingBytesForUTF8[256];

#ifdef MACOS
#undef err_none
#endif

/// 
/// \author Camilo Sasuke Tsumanuma
///
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


   CLASS_DECL_ACE extern e_err g_eerr;


   void CLASS_DECL_ACE increment_digit_letter(string & str);
   int32_t  CLASS_DECL_ACE compare(const char * psz1, const char * psz2);
   int32_t  CLASS_DECL_ACE compare_ci(const char * psz1, const char * psz2);
   bool CLASS_DECL_ACE equals(const char * psz1, const char * psz2);
   bool CLASS_DECL_ACE equals_ci(const char * psz1, const char * psz2);
   string CLASS_DECL_ACE equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);
   string CLASS_DECL_ACE equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);

   inline bool begins(const char * psz,string & strFed, const string & strPrefix);
   inline bool begins(const string & str,string & strFed,const string & strPrefix);
   inline bool begins(const id & id,string & strFed,const string & strPrefix);

   inline bool begins(const char * psz, const string & strPrefix);
   inline bool begins(const string & str, const string & strPrefix);
   inline bool begins(const id & id, const string & strPrefix);
   inline bool begins_with(const char * psz, const string & strPrefix);
   inline bool begins_with(const string & str, const string & strPrefix);


   void CLASS_DECL_ACE begin(wstring & wstr, const unichar * lpcszPrefix);

   bool CLASS_DECL_ACE begins(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_ACE begins(const wstring & str, const unichar * lpcszPrefix);
   bool CLASS_DECL_ACE begins_with(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_ACE begins_with(const wstring & str, const unichar * lpcszPrefix);


   bool CLASS_DECL_ACE begins_ci(const char * lpcsz, const char * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACE begins_ci_iws(const char * psz, const char * lpcszPrefix);
   bool CLASS_DECL_ACE begins_ci_iws(const string & str, const char * lpcszPrefix);


   bool CLASS_DECL_ACE begins_ci(const unichar * lpcsz, const unichar * lpcszPrefix);
   bool CLASS_DECL_ACE begins_ci(const wstring & wstr, const unichar * lpcszPrefix);
   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_ACE begins_ci_iws(const unichar * psz, const unichar * lpcszPrefix);
   bool CLASS_DECL_ACE begins_ci_iws(const wstring & str, const unichar * lpcszPrefix);


   inline bool begins_eat(string & str, const string & strPrefix);
   bool CLASS_DECL_ACE begins_eat_ci(string & str, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_ACE begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   inline bool begins_eat(var & var,const string & strPrefix);
   bool CLASS_DECL_ACE begins_eat_ci(var & var, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_ACE begins_eat_ci(var & var, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   inline bool begins_eat(property & property, const string & strPrefix);
   bool CLASS_DECL_ACE begins_eat_ci(property & property, const char * lpcszPrefix); // case insensitive
   bool CLASS_DECL_ACE begins_eat_ci(property & property, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
   bool CLASS_DECL_ACE while_begins_with_chars_eat(string & str, const char * lpcszChars);
   bool CLASS_DECL_ACE while_begins_with_chars_eat_ci(string & str, const char * lpcszChars); // case insensitive
   bool CLASS_DECL_ACE ends(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_ACE ends_ci(const char * lpcsz, const char * lpcszSuffix);
   bool CLASS_DECL_ACE ends_ci(const string & str, const char * lpcszSuffix);
   bool CLASS_DECL_ACE ends_ci(const var & var, const char * lpcszSuffix);
   bool CLASS_DECL_ACE ends_eat(string & str, const char * lpcszSuffix);
   bool CLASS_DECL_ACE ends_eat_ci(string & str, const char * lpcszSuffix);
   void CLASS_DECL_ACE copy(string & str, const char * lpcsz, int32_t iCount);
   string CLASS_DECL_ACE replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);
   string CLASS_DECL_ACE replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);

   string CLASS_DECL_ACE random_replace(::ace::application * papp, const stringa & straReplacement, const stringa & straSearch, const char * psz);

   strsize CLASS_DECL_ACE find_first(const stringa & straSearch, index & iFound, const string & str, index iStart = 0);

   strsize CLASS_DECL_ACE find_ci(const string & strFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_ci(const string & strFind   , const char   * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_ci(const char   * pszFind   , const string & str, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_ci(const char   * pszFind   , const char   * psz, strsize iStart = 0);


   strsize CLASS_DECL_ACE find_ci(const char   * pszFind,const string & str,strsize iStart, strsize iLast);
   strsize CLASS_DECL_ACE find_file_extension(const char * pszExtension,const string & str,strsize iStart = 0, strsize iLast = -1);

   strsize CLASS_DECL_ACE find_ww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_wwci(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_aww(const char * pszFind, const char * psz, strsize iStart = 0);
   strsize CLASS_DECL_ACE find_awwci(const char * pszFind, const char * psz, strsize iStart = 0);
   string CLASS_DECL_ACE has_char(const char * pszIfHasChar, const char * pszBefore = NULL, const char * pszAfter = NULL, const char * pszDoesnt = NULL);
   bool CLASS_DECL_ACE has_upper(const char * psz);
   bool CLASS_DECL_ACE has_lower(const char * psz);
   bool CLASS_DECL_ACE has_digit(const char * psz);
   void CLASS_DECL_ACE calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACE has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACE has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
   bool CLASS_DECL_ACE has_all_v1(const char * psz);
   string CLASS_DECL_ACE if_null(const char * psz, const char * pszIfNull = NULL);


   FORCEINLINE  const char * __utf8_inc(const char * psz) { return psz + 1 + trailingBytesForUTF8[(byte) *psz]; }

   static_inline e_err           err() { return g_eerr; }
   static_inline void            set_err(e_err eerr){ g_eerr = eerr; }
   static_inline void            clear_err() { g_eerr = err_none; }

   CLASS_DECL_ACE  const char *   utf8_inc(const char * psz);
   CLASS_DECL_ACE  const char *   utf8_inc_slide(strsize * pslide, const char * psz);
   CLASS_DECL_ACE  const char *   utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc);


   CLASS_DECL_ACE  const char *   utf8_dec(const char * pszBeg, const char * psz);
   CLASS_DECL_ACE  string         get_utf8_char(const char *psz);
   CLASS_DECL_ACE  int            get_utf8_char_length(const char *psz);
   CLASS_DECL_ACE  string         get_utf8_char(const char *psz, const char * pszEnd);
   CLASS_DECL_ACE  bool           get_utf8_char(string & strChar, const char * & psz, const char * pszEnd);
   CLASS_DECL_ACE  string         get_utf8_char(const char * pszBeg, const char *psz, strsize i);
   CLASS_DECL_ACE  string         utf8_next_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACE  string         utf8_previous_char(const char * pszBeg, const char *psz, strsize i = 0);
   CLASS_DECL_ACE  string         uni_to_utf8(int64_t ch);

   CLASS_DECL_ACE  const char *   utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz);


   CLASS_DECL_ACE  bool           to(int32_t & i, const char * psz);
   CLASS_DECL_ACE  bool           to(int64_t & i, const char * psz);
   CLASS_DECL_ACE  bool           to(int32_t & i, int32_t iBase, const char * psz);
   CLASS_DECL_ACE  bool           to(int64_t & i, int32_t iBase, const char * psz);
   CLASS_DECL_ACE  bool           to(uint32_t & i, const char * psz);
   CLASS_DECL_ACE  bool           to(uint64_t & i, const char * psz);
   CLASS_DECL_ACE  bool           to(uint32_t & i, int32_t iBase, const char * psz);
   CLASS_DECL_ACE  bool           to(uint64_t & i, int32_t iBase, const char * psz);

   CLASS_DECL_ACE  bool           trim_any_quotes(string & str);
   CLASS_DECL_ACE  bool           paired_trim(string & str, char ch);
   CLASS_DECL_ACE  bool           trim(string & str);
   CLASS_DECL_ACE  bool           _008Trim(string & str);


   CLASS_DECL_ACE  int_ptr        to_int_ptr(const char * psz);
   CLASS_DECL_ACE  int32_t            to_int(const char * psz);
   CLASS_DECL_ACE  uint32_t   to_uint(const char * psz);


   /** C++ Sockets Library \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/

   //CLASS_DECL_ACE string l2string(long l); // please use itoa
   //CLASS_DECL_ACE string bigint2string(uint64_t l); // please use itoa
   CLASS_DECL_ACE int64_t         to_int64(const string & str) ;
   CLASS_DECL_ACE int64_t         to_int64(const char * psz) ;
   CLASS_DECL_ACE uint64_t        to_uint64(const string & str) ;
   CLASS_DECL_ACE uint64_t        to_uint64(const char * psz) ;

   /** \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/



   inline CLASS_DECL_ACE int32_t  to_with_fallback(const char * psz, int32_t iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACE int64_t  to_with_fallback(const char * psz, int64_t iDefault) { to(iDefault, psz); return iDefault; }
   inline CLASS_DECL_ACE int32_t  to_with_fallback(const char * psz, int32_t iDefault, int32_t iBase) { to(iDefault, iBase, psz); return iDefault; }
   inline CLASS_DECL_ACE int64_t  to_with_fallback(const char * psz, int64_t iDefault, int32_t iBase) { to(iDefault, iBase, psz); return iDefault; }



   inline CLASS_DECL_ACE string  from(int32_t i);
   inline CLASS_DECL_ACE string  from(uint32_t ui);
   inline CLASS_DECL_ACE string  from(int64_t i);
   inline CLASS_DECL_ACE string  from(uint64_t ui);
   inline CLASS_DECL_ACE string  from(const var & var);
   inline CLASS_DECL_ACE string  from(const id & id);
   inline CLASS_DECL_ACE string  from(double d);
   inline CLASS_DECL_ACE string  from(float f);


   CLASS_DECL_ACE  string &       from(string & str, int32_t i);
   CLASS_DECL_ACE  string &       from(string & str, uint32_t ui);
   CLASS_DECL_ACE  string &       from(string & str, int64_t i);
   CLASS_DECL_ACE  string &       from(string & str, uint64_t ui);
   CLASS_DECL_ACE  string &       from(string & str, float f);
   CLASS_DECL_ACE  string &       from(string & str, double d);
   inline CLASS_DECL_ACE string & from(string & str, const id & id);
   inline CLASS_DECL_ACE string & from(string & str, const var & var);


#ifdef ANDROID

   CLASS_DECL_ACE  string &       from(string & str, long int i);

#endif



   //inline CLASS_DECL_ACE string   i64toa(int64_t i);

   CLASS_DECL_ACE  string         zero_pad(const string & strSrc,int iPad);
   CLASS_DECL_ACE  int32_t        get_escaped_char(const char * str, strsize pos, strsize &retPos);
   CLASS_DECL_ACE  bool           get_curly_content(const char * psz, string & str);
   CLASS_DECL_ACE  bool           is_simple_natural(const char * psz, strsize iCount = -1);

   CLASS_DECL_ACE string          to_lower(const char * psz);
   CLASS_DECL_ACE string          to_upper(const char * psz);


   string CLASS_DECL_ACE GetWindowText(oswindow oswindow);

   string CLASS_DECL_ACE get_word(
      const char * psz,
      const char * pszSeparator,
      bool bWithSeparator = false,
      // if end is separator, return entire string if separator is not found
      // otherwise, return is_empty
      bool bEndIsSeparator = true);

   CLASS_DECL_ACE bool eats(const char * & pszXml, const char * psz);
   CLASS_DECL_ACE bool eats_ci(const char * & pszXml, const char * psz);
   CLASS_DECL_ACE void consume(const char * & pszXml, const char * psz);
   CLASS_DECL_ACE void consume(const char * & pszXml, const char * psz, const char * pszEnd);
   CLASS_DECL_ACE void consume(const char * & pszXml, const char * psz, ::count iLen, const char * pszEnd);
   CLASS_DECL_ACE void consume_spaces(const char * & pszXml, ::count iMinimumCount = 1);
   CLASS_DECL_ACE uint64_t consume_natural(const char * & pszXml, uint64_t uiMax = ((uint64_t) -1), uint64_t uiMin = 0);
   CLASS_DECL_ACE string consume_hex(const char * & pszXml);
   CLASS_DECL_ACE void consume_spaces(const char * & pszXml, ::count iMinimumCount, const char * pszEnd);
   CLASS_DECL_ACE string consume_nc_name(const char * & pszXml);
   CLASS_DECL_ACE string consume_quoted_value(const char * & pszXml);
   CLASS_DECL_ACE string consume_quoted_value(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_ACE string consume_quoted_value_ex(const char * & pszXml,const char * pszEnd);
   CLASS_DECL_ACE string consume_spaced_value(string & str);
   CLASS_DECL_ACE string consume_spaced_value(const char * & pszXml);
   CLASS_DECL_ACE string consume_spaced_value(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_ACE string consume_command_line_argument(string & str);
   CLASS_DECL_ACE string consume_command_line_argument(const char * & pszXml);
   CLASS_DECL_ACE string consume_command_line_argument(const char * & pszXml, const char * pszEnd);
   CLASS_DECL_ACE bool begins_consume(const char * & pszXml, const char * psz);

   CLASS_DECL_ACE bool xml_is_comment(const char * pszXml);
   CLASS_DECL_ACE string xml_consume_comment(const char * & pszXml);

   CLASS_DECL_ACE string consume_c_quoted_value(const char * & pszXml);

   CLASS_DECL_ACE string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad);

   inline ::count ilen(const char * psz) { return (count) strlen(psz); }
   inline int64_t len(const char * psz) { return (int64_t) strlen(psz); }


   template < class TYPE >
   inline TYPE from_string(const char * psz);

   CLASS_DECL_ACE void format(string_format * pformat,char const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,byte const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,int16_t const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,uint16_t const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,int32_t const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,uint32_t const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,int64_t const & i);

#ifdef ANDROID
   
   CLASS_DECL_ACE void format(string_format * pformat, long int const & i);

#endif

   CLASS_DECL_ACE void format(string_format * pformat,uint64_t const & i);

   CLASS_DECL_ACE void format(string_format * pformat,double const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,float const &  i);

   CLASS_DECL_ACE void format(string_format * pformat,void * const & p);

   CLASS_DECL_ACE void format(string_format * pformat,const void * const & p);

   CLASS_DECL_ACE void format(string_format * pformat,byte * const & p);

   CLASS_DECL_ACE void format(string_format * pformat,const char * const & psz);

   CLASS_DECL_ACE void format(string_format * pformat,const string & str);

   CLASS_DECL_ACE void format(string_format * pformat,const lparam & lparam);

#ifdef LINUX

   inline CLASS_DECL_ACE void format(string_format * pformat,const pthread & p)
   {

      ::str::format(pformat, p.m_thread);

   }

#endif

   template < class TYPE >
   void format_type(string_format * pformat,const TYPE & t)
   {
      ::str::format(pformat, t);
   }

   CLASS_DECL_ACE bool simple_escaped(const string & str,strsize pos);

#ifdef WINDOWS

   inline void format(string_format * pformat,const DWORD & dw) { return format(pformat,(const uint32_t &)dw);  }

#endif


   //inline bool begins(const id & id, const string & strPrefix) { return begins(id.m_psz, strPrefix); }

   inline int get_utf8_char_length(const char * psz)
   {

      int len = ch_uni_len(*psz);
      if (len == 0) return 0;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 1) return 1;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 2) return 2;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 3) return 3;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 4) return 4;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 5) return 5;
      if (*psz++ == 0)
      {
         return -1;
      }
      if (len == 6) return 6;

      {
         return -1;
      }
      return -1;
   }


} // namespace str




template < typename T >
inline c_number < T > & c_number < T >::from(const string & str)
{
   ::str::to(m_number, str);
   return *this;
}





