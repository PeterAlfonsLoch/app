#pragma once

#include "aura/primitive/str/x/x_charcategory.h"
#include "aura/primitive/str/x/x_defines.h"
#include "aura/primitive/str/x/x_tables.h"


/** Character information class.
    \par Basic features:
    - All Unicode information is generated into tables by scripts
      xcharsets.pl  and  xtables_gen.pl
      They are using UnicodeData.txt file and some codepage files, available
      from <a href="http://www.unicode.org/">http://www.unicode.org/</a>
    - Character class supports most Unicode character properties, except for
      Bidirectional char class, and Decomposition information.
      Most of these methods works like Java Character class methods.

    \par Todo:
    - retrieving of bidirectional class information,
    - retrieving of character decomposition mappings (and normalization
      process information),
    - character 'Digit', 'Decimal Digit' properties. You can retrieve
      only 'Number' value property from digit characters.
    - No explicit surrogate characters support. Surrogate pairs are treated as distinct characters.

    @ingroup unicode
*/

extern CLASS_DECL_AURA const char trailingBytesForUTF8[256];

#define ch_uni_len(c) (trailingBytesForUTF8[(uchar)c] + 1)
#define str_uni_len(pszUtf8) (ch_uni_len(*(pszUtf8)))



namespace str
{


   class CLASS_DECL_AURA utf8_char
   {
   public:


      char     m_sz[32];
      char     m_chLen;


      int32_t parse(const char * psz);


   };


   namespace ch
   {

      // return UTF8 offset
      inline int64_t utf8_o(char cExtraBytes)
      {
         switch(cExtraBytes)
         {
         case 0:
            return 0x00000000UL;
         case 1:
            return 0x00003080UL;
         case 2:
            return 0x000E2080UL;
         case 3:
            return 0x03C82080UL;
         case 4:
            return 0xFA082080UL;
         case 5:
            return 0x82082080UL;
         default:
            return -1;
         };
      }
      //    /*
      // * Index into the table below with the first byte of a UTF-8 sequence to
      // * get the number of trailing bytes that are supposed to follow it.
      // * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
      // * left as-is for anyone who may want to do such conversion, which was
      // * allowed in earlier algorithms.
      // */
      //static const char trailingBytesForUTF8[256] = {
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
      //    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
      //    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
      //};
      // return UTF8 Extra Bytes based on supplied First Char
      inline char utf8_e(uchar c)
      {
         if(c < 192)
            return 0;
         else if(c < 192 + 32)
            return 1;
         else if(c < 192 + 32 + 16)
            return 2;
         else if(c < 192 + 32 + 16 + 8)
            return 3;
         else if(c < 192 + 32 + 16 + 8 + 4)
            return 4;
         else
            return 5;
      }


      inline int64_t uni_index(const char * pszUtf8);
      inline int64_t _uni_index(const char * pszUtf8);
      inline int64_t _uni_index_len(const char * pszUtf8,strsize & len);
      inline int64_t uni_index_len(const char * pszUtf8, strsize & len);

      // ATTENTION: it does not check validity of entire UTF8 char, you should check if the (last position + uni_len) is greater than the working string length
      //inline  char uni_len(const char * pszUtf8);
      //char uni_len(const char * pszUtf8);

      CLASS_DECL_AURA  int64_t uni_index(const char * pszUtf8,const char * pszEnd);

      inline int64_t uni_index_len(const char * pszUtf8,strsize & len)
      {
         if(((uchar) *pszUtf8) < 192)
         {
            len = 1;
            return *pszUtf8;
         }
         else
         {
            return _uni_index_len(pszUtf8, len);
         }
      }

      inline int64_t uni_index(const char * pszUtf8)
      {
         if(((uchar) *pszUtf8) < 192)
         {
            return *pszUtf8;
         }
         else
         {
            return _uni_index(pszUtf8);
         }
      }


      inline  int64_t _uni_index(const char * pszUtf8)
      {
         uchar * source = (uchar *) pszUtf8;
         int64_t ch = 0;
         uchar c;
         int len = 0;
         char extraBytesToRead = utf8_e(*source);
         if(*source == '\0') return -1;
         switch(extraBytesToRead)
         {
         case 5:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 4:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 3:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 2:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 1:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 0:
            ch += c = source[len++];
            if(c == '\0' && extraBytesToRead) return -1;
         }
         ch -= utf8_e(extraBytesToRead);
         return ch;
      }

      int64_t _uni_index_len(const char * pszUtf8,strsize & len)
      {
         uchar * source = (uchar *)pszUtf8;
         int64_t ch = 0;
         uchar c;
         char extraBytesToRead = utf8_e(*source);
         len = 0;
         if(*source == '\0') return 0;
         switch(extraBytesToRead)
         {
         case 5:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 4:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 3:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 2:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 1:
            ch += c = source[len++]; ch <<= 6;
            if(c == '\0') return -1;
         case 0:
            ch += c = source[len++];
            if(c == '\0' && extraBytesToRead) return -1;
         }
         ch -= utf8_o(extraBytesToRead);
         return ch;
      }


      inline bool is_legal_uni_index(int64_t iUnicodeIndex)
      {
         
         return iUnicodeIndex < 65536 ? true : false;

         //return ca >= ((uint64_t) 0xffffffffu) ? false : true;

      }


      inline bool is_space_char(unichar wch)
      {
         return ((((1 << CHAR_CATEGORY_Zs) |
                   (1 << CHAR_CATEGORY_Zl)  |
                   (1 << CHAR_CATEGORY_Zp)
                  ) >> CHAR_CATEGORY(CHAR_PROP(wch))) & 1) != 0;
      }

      inline bool is_space_char(int64_t ca)
      {
         if(!is_legal_uni_index(ca)) return false;
         return is_space_char((unichar) ca);
      }

      inline unichar to_lower_case(unichar wch)
      {
        uint32_t c1 = CHAR_PROP(wch);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return unichar(wch);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return unichar(wch+1);
        return unichar(wch - (c1>>16));
      }

      inline int64_t to_lower_case(int64_t ca)
      {
         if(!is_legal_uni_index(ca)) return false;
         return (int64_t) to_lower_case((unichar) ca);
      }

      inline unichar to_upper_case(unichar wch)
      {
        uint32_t c1 = CHAR_PROP(wch);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return unichar(wch);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return unichar(wch-1);
        return unichar(wch - (c1>>16));
      }

      inline int64_t to_upper_case(int64_t ca)
      {
         if(!is_legal_uni_index(ca)) return false;
         return (int64_t) to_upper_case((unichar) ca);
      }

      inline bool to_numeric_value(const char * pszUtf8Char, float *f)
      {
         int64_t ca = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(ca))
            return false;
        uint32_t c1 = CHAR_PROP(ca);
        if (!NUMBER(c1)) return false;
        *f = CHAR_PROP2(ca);
        return true;
      }


      CLASS_DECL_AURA string to_lower_case(const char * pszUtf8Char);
      CLASS_DECL_AURA string to_upper_case(const char * pszUtf8Char);
      CLASS_DECL_AURA string to_title_case(const char * pszUtf8Char);

      CLASS_DECL_AURA bool is_lower_case(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_upper_case(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_title_case(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_letter(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_letter_or_digit(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_digit(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_digit(int64_t iUniIndex);
      CLASS_DECL_AURA bool is_assigned(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_space_char(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_whitespace(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_whitespace(const char * pszUtf8Char, const char * pszEnd);

      CLASS_DECL_AURA bool is_number(const char * pszUtf8Char);
//      CLASS_DECL_AURA bool to_numeric_value(const char * pszUtf8Char, float *f);

      CLASS_DECL_AURA string get_category_name(const char * pszUtf8Char);
      ECharCategory get_category(const char * pszUtf8Char);

      CLASS_DECL_AURA int32_t get_combining_class(const char * pszUtf8Char);
      CLASS_DECL_AURA bool is_mirrored(const char * pszUtf8Char);

      /** @deprecated For debug purposes only. */
      CLASS_DECL_AURA int32_t size_of_tables();




   }

} // namespace str

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
