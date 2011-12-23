#include "StdAfx.h"


#include "ca/x/x_charcategory_names.h"


namespace gen
{


   namespace ch
   {


      string ch::to_lower_case(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return "";
        unsigned long c1 = CHAR_PROP(c);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return string(wchar_t(c));
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return string(wchar_t(c+1));
        return string(wchar_t(c - (c1>>16)));
      }
      string ch::to_upper_case(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return "";
        unsigned long c1 = CHAR_PROP(c);
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return string(wchar_t(c));
        if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lt) return string(wchar_t(c-1));
        return string(wchar_t(c - (c1>>16)));
      }
      string ch::to_title_case(const char * pszUtf8Char)
      {
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return "";
        unsigned long c1 = CHAR_PROP(c);
        if (TITLE_CASE(c1)){ // titlecase exists
          if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Lu) return string(wchar_t(c+1));
          if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll) return string(wchar_t(c-1));
          return string(wchar_t(c));
        }else // has no titlecase form
          if (CHAR_CATEGORY(c1) == CHAR_CATEGORY_Ll)
            return string(wchar_t(c - (c1>>16)));
        return string(wchar_t(c));
      }


      bool ch::is_lower_case(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return CHAR_CATEGORY(CHAR_PROP(c)) == CHAR_CATEGORY_Ll;
      }
      bool ch::is_upper_case(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return CHAR_CATEGORY(CHAR_PROP(c)) == CHAR_CATEGORY_Lu;
      }
      bool ch::is_title_case(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return CHAR_CATEGORY(CHAR_PROP(c)) == CHAR_CATEGORY_Lt;
      }


      bool ch::is_letter(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        unsigned long c1 = CHAR_CATEGORY(CHAR_PROP(c));
        return ((( (1 << CHAR_CATEGORY_Lu) |
                   (1 << CHAR_CATEGORY_Ll) |
                   (1 << CHAR_CATEGORY_Lt) |
                   (1 << CHAR_CATEGORY_Lm) |
                   (1 << CHAR_CATEGORY_Lo)
                 ) >> c1) & 1) != 0;
      }
      bool ch::is_letter_or_digit(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        unsigned long c1 = CHAR_CATEGORY(CHAR_PROP(c));
        return ((( (1 << CHAR_CATEGORY_Lu) |
                   (1 << CHAR_CATEGORY_Ll) |
                   (1 << CHAR_CATEGORY_Lt) |
                   (1 << CHAR_CATEGORY_Lm) |
                   (1 << CHAR_CATEGORY_Lo) |
                   (1 << CHAR_CATEGORY_Nd)
                 ) >> c1) & 1) != 0;
      }

      bool ch::is_digit(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return CHAR_CATEGORY(CHAR_PROP(c)) == CHAR_CATEGORY_Nd;
      }

      bool ch::is_assigned(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return CHAR_CATEGORY(CHAR_PROP(c)) != CHAR_CATEGORY_Cn;
      }

      bool ch::is_space_char(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return  ((((1 << CHAR_CATEGORY_Zs) |
                   (1 << CHAR_CATEGORY_Zl)  |
                   (1 << CHAR_CATEGORY_Zp)
                  ) >> CHAR_CATEGORY(CHAR_PROP(c))) & 1) != 0;
      }
      bool ch::is_whitespace(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return  (c == 0x20)
                 ||
                ((c <= 0x0020) &&
                 (((((1 << 0x0009) |
                 (1 << 0x000A) |
                 (1 << 0x000C) |
                 (1 << 0x000D)) >> c) & 1) != 0))
                 ||
                (((((1 << CHAR_CATEGORY_Zs) |
                    (1 << CHAR_CATEGORY_Zl) |
                    (1 << CHAR_CATEGORY_Zp)
                   ) >> CHAR_CATEGORY(CHAR_PROP(c))) & 1) != 0);
      }
      bool ch::is_whitespace(const char * pszUtf8Char, const char * pszEnd){
         __int64 c = uni_index(pszUtf8Char, pszEnd);
         if(!is_legal_uni_index(c))
            return false;
        return  (c == 0x20)
                 ||
                ((c <= 0x0020) &&
                 (((((1 << 0x0009) |
                 (1 << 0x000A) |
                 (1 << 0x000C) |
                 (1 << 0x000D)) >> c) & 1) != 0))
                 ||
                (((((1 << CHAR_CATEGORY_Zs) |
                    (1 << CHAR_CATEGORY_Zl) |
                    (1 << CHAR_CATEGORY_Zp)
                   ) >> CHAR_CATEGORY(CHAR_PROP(c))) & 1) != 0);
      }

      bool ch::is_number(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return NUMBER(CHAR_PROP(c)) != 0;
      }

      bool ch::to_numeric_value(const char * pszUtf8Char, float *f){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        unsigned long c1 = CHAR_PROP(c);
        if (!NUMBER(c1)) return false;
        *f = CHAR_PROP2(c);
        return true;
      }

      ECharCategory ch::get_category(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return CHAR_CATEGORY_LAST;
        return ECharCategory(CHAR_CATEGORY(CHAR_PROP(c)));
      }

      string ch::get_category_name(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return "";
        return string(char_category_names[CHAR_CATEGORY(CHAR_PROP(c))]);
      }

      int ch::get_combining_class(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return COMBINING_CLASS(CHAR_PROP(c));
      }
      bool ch::is_mirrored(const char * pszUtf8Char){
         __int64 c = uni_index(pszUtf8Char);
         if(!is_legal_uni_index(c))
            return false;
        return MIRRORED(CHAR_PROP(c)) != 0;
      }

      int ch::size_of_tables(){
        return sizeof(arr_idxCharInfo)+sizeof(arr_CharInfo)+sizeof(arr_idxCharInfo2)+sizeof(arr_CharInfo2);
      }

      /* --------------------------------------------------------------------- */

      /*
       * Index into the table below with the first byte of a UTF-8 sequence to
       * get the number of trailing bytes that are supposed to follow it.
       * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
       * left as-is for anyone who may want to do such conversion, which was
       * allowed in earlier algorithms.
       */
      static const char trailingBytesForUTF8[256] = {
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
          2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
      };

      /*
       * Magic values subtracted from a buffer value during UTF8 conversion.
       * This table contains as many values as there might be trailing bytes
       * in a UTF-8 sequence.
       */
      static const unsigned int offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL, 
                 0x03C82080UL, 0xFA082080UL, 0x82082080UL };



      __int64 ch::uni_index(const char * pszUtf8)
      {
         unsigned char * source = (unsigned char *) pszUtf8;
         __int64 ch = 0;
         int extraBytesToRead = trailingBytesForUTF8[*source];
/*         if(natural(extraBytesToRead) >= strlen(pszUtf8))
         }*/
//         if(natural(extraBytesToRead) >= strlen(pszUtf8))
  //       {
    //        return -1; // source exhausted
      //   }
         if(*source == '\0') return -1;
         switch (extraBytesToRead)
         {
            case 5: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 4: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 3: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 2: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 1: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 0: ch += *source++;
         }
         ch -= offsetsFromUTF8[extraBytesToRead];
         return ch;
      }

      __int64 ch::uni_index(const char * pszUtf8, const char * pszEnd)
      {
         unsigned char * source = (unsigned char *) pszUtf8;
         __int64 ch = 0;
         int extraBytesToRead = trailingBytesForUTF8[*source];
         if(*source == '\0') return -1;
         if((source + extraBytesToRead + 1) > (unsigned char *) pszEnd)
            return -1;
         switch (extraBytesToRead)
         {
            case 5: ch += *source++; ch <<= 6; 
                if(*source == '\0') return -1;
            case 4: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 3: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 2: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 1: ch += *source++; ch <<= 6;
                if(*source == '\0') return -1;
            case 0: ch += *source++;
         }
         ch -= offsetsFromUTF8[extraBytesToRead];
         return ch;
      }


   } // namespace ch

} // namespace gen


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
