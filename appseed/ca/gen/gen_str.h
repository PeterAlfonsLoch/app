#pragma once


class var;
class stringa;
class id;


namespace gen
{


   namespace str
   {

      extern const char trailingBytesForUTF8[256];

      enum e_pad
      {
         pad_left,
         pad_right
      };

      void CLASS_DECL_ca increment_digit_letter(string & str);
      int  CLASS_DECL_ca compare(const char * psz1, const char * psz2);
      int  CLASS_DECL_ca compare_ci(const char * psz1, const char * psz2);
      bool CLASS_DECL_ca equals(const char * psz1, const char * psz2);
      bool CLASS_DECL_ca equals_ci(const char * psz1, const char * psz2);
      string CLASS_DECL_ca equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);
      string CLASS_DECL_ca equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent = NULL);

      
      
      bool CLASS_DECL_ca begins(const char * psz, const char * lpcszPrefix);
      bool CLASS_DECL_ca begins(const string & str, const char * lpcszPrefix);
      inline bool CLASS_DECL_ca begins(const id & id, const char * lpcszPrefix) { return begins((const string &) id, lpcszPrefix); }
      bool CLASS_DECL_ca begins_with(const char * psz, const char * lpcszPrefix);
      bool CLASS_DECL_ca begins_with(const string & str, const char * lpcszPrefix);


      void CLASS_DECL_ca begin(wstring & wstr, const wchar_t * lpcszPrefix);

      bool CLASS_DECL_ca begins(const wchar_t * psz, const wchar_t * lpcszPrefix);
      bool CLASS_DECL_ca begins(const wstring & str, const wchar_t * lpcszPrefix);
      bool CLASS_DECL_ca begins_with(const wchar_t * psz, const wchar_t * lpcszPrefix);
      bool CLASS_DECL_ca begins_with(const wstring & str, const wchar_t * lpcszPrefix);


      bool CLASS_DECL_ca begins_ci(const char * lpcsz, const char * lpcszPrefix);
      // case insensitive, ignore white space - only in searched string
      bool CLASS_DECL_ca begins_ci_iws(const char * psz, const char * lpcszPrefix);
      bool CLASS_DECL_ca begins_ci_iws(const string & str, const char * lpcszPrefix);


      bool CLASS_DECL_ca begins_ci(const wchar_t * lpcsz, const wchar_t * lpcszPrefix);
      bool CLASS_DECL_ca begins_ci(const wstring & wstr, const wchar_t * lpcszPrefix);
      // case insensitive, ignore white space - only in searched string
      bool CLASS_DECL_ca begins_ci_iws(const wchar_t * psz, const wchar_t * lpcszPrefix);
      bool CLASS_DECL_ca begins_ci_iws(const wstring & str, const wchar_t * lpcszPrefix);




      bool CLASS_DECL_ca begins_eat(string & str, const char * lpcszPrefix);
      bool CLASS_DECL_ca begins_eat_ci(string & str, const char * lpcszPrefix); // case insensitive
      bool CLASS_DECL_ca begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator); // case insensitive
      bool CLASS_DECL_ca while_begins_with_chars_eat(string & str, const char * lpcszChars);
      bool CLASS_DECL_ca while_begins_with_chars_eat_ci(string & str, const char * lpcszChars); // case insensitive
      bool CLASS_DECL_ca ends(const char * lpcsz, const char * lpcszSuffix);
      bool CLASS_DECL_ca ends_ci(const char * lpcsz, const char * lpcszSuffix);
      bool CLASS_DECL_ca ends_ci(const string & str, const char * lpcszSuffix);
      bool CLASS_DECL_ca ends_ci(const var & var, const char * lpcszSuffix);
      bool CLASS_DECL_ca ends_eat(string & str, const char * lpcszSuffix);
      bool CLASS_DECL_ca ends_eat_ci(string & str, const char * lpcszSuffix);
      void CLASS_DECL_ca copy(string & str, const char * lpcsz, int iCount);
      string CLASS_DECL_ca replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);
      string CLASS_DECL_ca replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart = 0);

      string CLASS_DECL_ca random_replace(::ca::application * papp, const stringa & straReplacement, const stringa & straSearch, const char * psz);
      
      index CLASS_DECL_ca find_first(const stringa & straSearch, index & iFound, const string & str, index iStart = 0);

      index CLASS_DECL_ca find_ci(const string & strFind   , const string & str, index iStart = 0);
      index CLASS_DECL_ca find_ci(const string & strFind   , const char   * psz, index iStart = 0);
      index CLASS_DECL_ca find_ci(const char   * pszFind   , const string & str, index iStart = 0);
      index CLASS_DECL_ca find_ci(const char   * pszFind   , const char   * psz, index iStart = 0);

      index CLASS_DECL_ca find_ww(const char * pszFind, const char * psz, index iStart = 0);
      index CLASS_DECL_ca find_wwci(const char * pszFind, const char * psz, index iStart = 0);
      index CLASS_DECL_ca find_aww(const char * pszFind, const char * psz, index iStart = 0);
      index CLASS_DECL_ca find_awwci(const char * pszFind, const char * psz, index iStart = 0);
      string CLASS_DECL_ca has_char(const char * pszIfHasChar, const char * pszBefore = NULL, const char * pszAfter = NULL);
      bool CLASS_DECL_ca has_upper(const char * psz);
      bool CLASS_DECL_ca has_lower(const char * psz);
      bool CLASS_DECL_ca has_digit(const char * psz);
      void CLASS_DECL_ca calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
      bool CLASS_DECL_ca has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
      bool CLASS_DECL_ca has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit);
      bool CLASS_DECL_ca has_all_v1(const char * psz);
      string CLASS_DECL_ca if_null(const char * psz, const char * pszIfNull = NULL);


      FORCEINLINE  const char * __utf8_inc(const char * psz)
      {
         return psz + 1 + trailingBytesForUTF8[(unsigned char) *psz];
      }

      CLASS_DECL_ca  const char *   utf8_inc(const char * psz);

      CLASS_DECL_ca  const char *   utf8_dec(const char * pszBeg, const char * psz);
      CLASS_DECL_ca  string         utf8_char(const char *psz);
      CLASS_DECL_ca  string         utf8_char(const char *psz, const char * pszEnd);
      CLASS_DECL_ca  bool           utf8_char(string & strChar, const char * & psz, const char * pszEnd);
      CLASS_DECL_ca  string         utf8_char(const char * pszBeg, const char *psz, strsize i);
      CLASS_DECL_ca  string         utf8_next_char(const char * pszBeg, const char *psz, strsize i = 0);
      CLASS_DECL_ca  string         utf8_previous_char(const char * pszBeg, const char *psz, strsize i = 0);
      CLASS_DECL_ca  string         uni_to_utf8(__int64 ch);

      CLASS_DECL_ca  const char *   utf8_dec(::gen::utf8_char * pchar, const char * pszBeg, const char * psz);
      CLASS_DECL_ca  int            utf8_char(::gen::utf8_char * pchar, const char *psz);

      CLASS_DECL_ca  bool           atoi(const char * psz, int & i);
      CLASS_DECL_ca  bool           atoi(const char * psz, int64_t & i);
      CLASS_DECL_ca  bool           atoi(const char * psz, int & i, int iBase);
      CLASS_DECL_ca  bool           atoi(const char * psz, int64_t & i, int iBase);

      inline CLASS_DECL_ca int      xatoi(const char * psz, int iDefault){ atoi(psz, iDefault); return iDefault; }
      inline CLASS_DECL_ca int64_t  xatoi64(const char * psz, int64_t & iDefault) { atoi(psz, iDefault); return iDefault; }
      inline CLASS_DECL_ca int      xatoi(const char * psz, int iDefault, int iBase){ atoi(psz, iDefault, iBase); return iDefault; }
      inline CLASS_DECL_ca int64_t  xatoi64(const char * psz, int64_t & iDefault, int iBase) { atoi(psz, iDefault, iBase); return iDefault; }

      inline CLASS_DECL_ca  string  itoa(int i);
      inline CLASS_DECL_ca  string  itoa(int64_t i);
      inline CLASS_DECL_ca  string  itoa(unsigned int ui);
      inline CLASS_DECL_ca  string  itoa(unsigned long ui);
      inline CLASS_DECL_ca  string  itoa(uint64_t ui);
      inline CLASS_DECL_ca  string  itoa(const var & var);
      inline CLASS_DECL_ca  string  itoa(const id & id);
      
      
      CLASS_DECL_ca  string &       itoa(string & str, int i);
      CLASS_DECL_ca  string &       itoa(string & str, int64_t i);
      CLASS_DECL_ca  string &       itoa(string & str, unsigned int ui);
      CLASS_DECL_ca  string &       itoa(string & str, unsigned long ui);
      CLASS_DECL_ca  string &       itoa(string & str, uint64_t ui);
      inline CLASS_DECL_ca string & itoa(string & str, const var & var);
      inline CLASS_DECL_ca string & itoa(string & str, const id & id);


      inline CLASS_DECL_ca string   i64toa(int64_t i);
      CLASS_DECL_ca string &        i64toa(string & str, int64_t i);

      CLASS_DECL_ca  __int64        get_hex(const char * pszUtf8);
      CLASS_DECL_ca  __int64        get_hex_number(const char * pstr);
      CLASS_DECL_ca  int            get_escaped_char(const char * str, strsize pos, strsize &retPos);
      CLASS_DECL_ca  bool           get_curly_content(const char * psz, string & str);
      CLASS_DECL_ca  bool           is_simple_natural(const char * psz);




      string CLASS_DECL_ca get_window_text(HWND hwnd);

      string CLASS_DECL_ca get_word(
                        const char * psz,
                        const char * pszSeparator,
                        bool bWithSeparator = false,
                        // if end is separator, return entire string if separator is not found
                        // otherwise, return is_empty
                        bool bEndIsSeparator = true);

      CLASS_DECL_ca void consume(const char * & pszXml, const char * psz);
      CLASS_DECL_ca void consume(const char * & pszXml, const char * psz, const char * pszEnd);
      CLASS_DECL_ca void consume(const char * & pszXml, const char * psz, count iLen, const char * pszEnd);
      CLASS_DECL_ca void consume_spaces(const char * & pszXml, count iMinimumCount = 1);
      CLASS_DECL_ca void consume_spaces(const char * & pszXml, count iMinimumCount, const char * pszEnd);
      CLASS_DECL_ca string consume_nc_name(const char * & pszXml);
      CLASS_DECL_ca string consume_quoted_value(const char * & pszXml);
      CLASS_DECL_ca string consume_quoted_value(const char * & pszXml, const char * pszEnd);
      CLASS_DECL_ca bool begins_consume(const char * & pszXml, const char * psz);

      CLASS_DECL_ca bool xml_is_comment(const char * pszXml);
      CLASS_DECL_ca string xml_consume_comment(const char * & pszXml);

      CLASS_DECL_ca string consume_c_quoted_value(const char * & pszXml);

      CLASS_DECL_ca string pad(const char * psz, count iLen, const char * pszPattern, e_pad epad);

      __inline count ilen(const char * psz) { return (count) strlen(psz); }
      __inline __int64 len(const char * psz) { return (__int64) strlen(psz); }

/** C++ Sockets Library \file Utility.cpp
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/

      //CLASS_DECL_ca string l2string(long l); // please use itoa
      //CLASS_DECL_ca string bigint2string(uint64_t l); // please use itoa
      CLASS_DECL_ca int64_t atoi64(const string & str) ;
      CLASS_DECL_ca int64_t atoi64(const char * psz) ;
      CLASS_DECL_ca uint64_t atoui64(const string & str) ;
      CLASS_DECL_ca uint64_t atoui64(const char * psz) ;
      CLASS_DECL_ca unsigned int hex2unsigned(const string & str);
      CLASS_DECL_ca string to_string(double d);
/** \file Utility.cpp
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/

      template < class TYPE >
      inline TYPE from_string(const char * psz);


      inline CLASS_DECL_ca  string         itoa(int64_t i);

   } // namespace str


} // namespace gen



