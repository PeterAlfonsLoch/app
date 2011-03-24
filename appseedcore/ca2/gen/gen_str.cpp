#include "StdAfx.h"

namespace gen
{

   int  str::compare(const char * psz1, const char * psz2)
   {
      return strcmp(psz1, psz2);
   }

   int  str::compare_ci(const char * psz1, const char * psz2)
   {
      return _stricmp(psz1, psz2);
   }

   bool str::equals(const char * psz1, const char * psz2)
   {
      return compare(psz1, psz2) == 0;
   }

   bool str::equals_ci(const char * psz1, const char * psz2)
   {
      return compare_ci(psz1, psz2) == 0;
   }

   string CLASS_DECL_ca str::equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   string CLASS_DECL_ca str::equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals_ci(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   bool str::begins(const char * lpcsz, const char * lpcszPrefix)
   {
      while(*lpcszPrefix != '\0')
      {
         if(*lpcsz == '\0')
            return false;
         else if(*lpcszPrefix != *lpcsz)
            return false;
         lpcsz++;
         lpcszPrefix++;
      }
      return true;
   }

   bool str::begins_ci(const char * lpcsz, const char * lpcszPrefix)
   {
      string str(lpcsz);
      string strPrefix(lpcszPrefix);
      int iLen = strPrefix.get_length();
      if(str.Left(iLen).CompareNoCase(lpcszPrefix) == 0)
      {
         return true;
      }
      return false;
   }

   bool str::begins_eat(string & str, const char * lpcszPrefix)
   {
      string strPrefix(lpcszPrefix);
      int iLen = strPrefix.get_length();
      if(str.Left(iLen) == lpcszPrefix)
      {
         str = str.Mid(iLen);
         return true;
      }
      return false;
   }

   bool str::begins_eat_ci(string & str, const char * lpcszPrefix)
   {
      if(lpcszPrefix == NULL)
         return true;
      string strPrefix(lpcszPrefix);
      int iLen = strPrefix.get_length();
      if(str.Left(iLen).CompareNoCase(lpcszPrefix) == 0)
      {
         str = str.Mid(iLen);
         return true;
      }
      return false;
   }

   bool str::ends(const char * lpcsz, const char * lpcszSuffix)
   {
      string str(lpcsz);
      string strSuffix(lpcszSuffix);
      int iLen = strSuffix.get_length();
      if(str.Right(iLen) == lpcszSuffix)
      {
         return true;
      }
      return false;
   }

   bool str::ends_ci(const char * lpcsz, const char * lpcszSuffix)
   {
      string str(lpcsz);
      string strSuffix(lpcszSuffix);
      int iLen = strSuffix.get_length();
      if(str.Right(iLen).CompareNoCase(lpcszSuffix) == 0)
      {
         return true;
      }
      return false;
   }

   bool str::ends_eat(string & str, const char * lpcszSuffix)
   {
      string strSuffix(lpcszSuffix);
      int iLen = strSuffix.get_length();
      if(str.Right(iLen) == lpcszSuffix)
      {
         str = str.Left(str.get_length() - iLen);
         return true;
      }
      return false;
   }

   bool str::ends_eat_ci(string & str, const char * lpcszSuffix)
   {
      string strSuffix(lpcszSuffix);
      int iLen = strSuffix.get_length();
      if(str.Right(iLen).CompareNoCase(lpcszSuffix) == 0)
      {
         str = str.Left(str.get_length() - iLen);
         return true;
      }
      return false;
   }

   void str::copy(string & str, const char * lpcsz, int iCount)
   {
      string strCopy(lpcsz, iCount);
      str = strCopy;
   }

   string str::replace(const char * pszFind, const char * pszReplace, const char * psz)
   {
      string str(psz);
      str.replace(pszFind, pszReplace);
      return str;
   }

   string str::replace_ci(const char * pszFind, const char * pszReplace, const char * psz)
   {
      int iPos = 0;
      string str(psz);
      int iReplaceLen = -1;
      int iFindLen = -1;
      while(true)
      {
         iPos = find_ci(pszFind, str, iPos);
         if(iPos < 0)
            break;
         if(iReplaceLen < 0)
            iReplaceLen = strlen(pszReplace);
         if(iFindLen < 0)
            iFindLen = strlen(pszFind);
         str = str.Left(iPos) + pszReplace + str.Mid(iPos + iFindLen);
         iPos += iReplaceLen;
      }
      return str;
   }

   int str::find_ci(const char * pszFind, const char * psz, int iStart)
   {
      string strFind(pszFind);
      strFind.make_lower();
      string str(psz);
      str.make_lower();
      return str.find(strFind, iStart);
   }

   int str::find_wwci(const char * pszFind, const char * psz, int iStart)
   {
      string strFind(pszFind);
      strFind.make_lower();
      string str(psz);
      str.make_lower();
      return find_ww(strFind, str, iStart);
   }

   int str::find_ww(const char * pszFind, const char * psz, int iStart)
   {
      if(psz == NULL)
         return -1;
      const char * pszIter = &psz[iStart];
      if(pszIter == NULL)
         return -1;
      string strFind(pszFind);
      int i = 0;
      if(iStart == 0)
      {
         if(strFind == string(pszIter, strFind.get_length())
         && (strlen(pszIter) == strFind.get_length() || !gen::ch::is_letter_or_digit(pszIter + strFind.get_length())))
         {
            return i;
         }
      }
      while(*pszIter != '\0')
      {
         string strChar = utf8_char(pszIter);
         if(!gen::ch::is_letter_or_digit(strChar))
         {
            do
            {
               i += strChar.get_length();
               pszIter = utf8_inc(pszIter);
               strChar = utf8_char(pszIter);
            } 
            while(!gen::ch::is_letter_or_digit(strChar) && *pszIter != '\0');

            if(*pszIter == '\0')
               break;
            if(strFind == string(pszIter, strFind.get_length())
            && (strlen(pszIter) == strFind.get_length() || !gen::ch::is_letter_or_digit(pszIter + strFind.get_length())))
            {
               return iStart + i;
            }
         }
         i += strChar.get_length();
         pszIter = utf8_inc(pszIter);
      }
      return -1;
   }

   string str::has_char(const char * pszIfHasChar, const char * pszBefore, const char * pszAfter)
   {
      string str;
      if(pszIfHasChar == NULL)
         return str;
      if(strlen(pszIfHasChar) == 0)
         return str;
      if(pszBefore != NULL)
      {
         str = pszBefore;
      }
      str += pszIfHasChar;
      if(pszAfter != NULL)
      {
         str += pszAfter;
      }
      return str;
   }
   bool str::has_upper(const char * psz)
   {
      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;
      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);
      return bHasUpper;
   }
   bool str::has_lower(const char * psz)
   {
      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;
      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);
      return bHasLower;
   }
   bool str::has_digit(const char * psz)
   {
      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;
      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);
      return bHasDigit;
   }
   void str::calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {
      bHasUpper = false;
      bHasLower = false;
      bHasDigit = false;
      while(true)
      {
         string qc = utf8_char(psz);
         if(qc.is_empty())
         {
            break;
         }
         else if(gen::ch::is_digit(qc))
         {
            bHasDigit = true;
         }
         else if(gen::ch::is_lower_case(qc))
         {
            bHasLower = true;
         }
         else if(gen::ch::is_upper_case(qc))
         {
            bHasUpper = true;
         }
         if(bHasUpper && bHasDigit && bHasLower)
         {
            // it is not necessary to evaluate more chars anymore
            break;
         }
         psz = utf8_inc(psz);
      }
   }
   bool str::has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {
      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);
      return bHasUpper || bHasLower || bHasDigit;
   }
   bool str::has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {
      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);
      return bHasUpper && bHasLower && bHasDigit;
   }
   bool str::has_all_v1(const char * psz)
   {
      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;
      return has_all_v1(psz, bHasUpper, bHasLower, bHasDigit);
   }

   string str::if_null(const char * psz, const char * pszIfNull)
   {
      if(psz == NULL)
         return pszIfNull;
      else
         return psz;
   }

   string str::get_window_text(HWND hwnd)
   {
      string str;
      if (hwnd != NULL)
      {
         int nLen = ::GetWindowTextLength(hwnd);
         ::GetWindowText(hwnd, str.GetBufferSetLength(nLen), nLen+1);
         str.ReleaseBuffer();
      }
      return str;
   }

   string str::get_word(
                     const char * psz, 
                     const char * pszSeparator, 
                     bool bWithSeparator, 
                     bool bEndIsSeparator)
   {
      if(psz == NULL)
         return "";
      if(pszSeparator == NULL)
      {
         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return "";
         }
      }
      string str(psz);
      int iFind = str.find(pszSeparator);
      if(iFind < 0)
      {
         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return "";
         }
      }
      if(bWithSeparator)
      {
         return str.Left(iFind + 1);
      }
      else
      {
         return str.Left(iFind);
      }
   }

   bool str::atoi(const char * psz, int & i, int iBase)
   {
      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;
      char * pszEnd;
      int iConversion = ::strtol(psz, &pszEnd, iBase);
      if(pszEnd == psz)
         return false;
      i = iConversion;
      return true;
   }

   string str::itoa(int i)
   {
      string str;
      str.Format("%d", i);
      return str;
   }

   __int64 str::get_hex(const char * pszUtf8Char)
   {
      string low = gen::ch::to_lower_case(pszUtf8Char);
      __int64 ch = gen::ch::uni_index(low);
      ch -= '0';
      if(ch >= 'a'-'0' && ch <= 'f'-'0')
      {
         return ch - 0x27;
      }
      else if (ch <= 9)
      {
         return ch;
      }
      else
      {
         return -1;
      }
   }

   string str::uni_to_utf8(__int64 w)
   {
      string str;
      if(w < 0x0080 )
      {
         str += (char) w;
      }
      else if(w < 0x0800) 
      {
         str = (char)(0xc0 | ((w) >> 6));
         str += (char)(0x80 | ((w) & 0x3f));
      }
      else 
      {
         str = (char)(0xe0 | ((w) >> 12));
         str += (char)(0x80 | (((w) >> 6) & 0x3f));
         str += (char)(0x80 | ((w) & 0x3f));
      } 
      return str;
   }


   const char * str::utf8_inc(const char * psz)
   {
      if(*psz == '\0')
      {
         return psz;
      }
      else if((*psz & 0x80) == 0)
      {
         return psz + 1;
      }
      else if((*psz & 0xE0) == 0xC0)
      {
         return psz + 2;
      }
      else if((*psz & 0xF0) == 0xE0)
      {
         return psz + 3;
      }
      else if((*psz & 0xF8) == 0xF0)
      {
         return psz + 4;
      }
      else if((*psz & 0xFC) == 0xF8)
      {
         return psz + 5;
      }
      else if((*psz & 0xFE) == 0xFC)
      {
         return psz + 6;
      }
      return psz + 1;
   }

   const char * str::utf8_dec(const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         return NULL;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            return NULL;
         }
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            return NULL;
         }
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            return NULL;
         }
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            return NULL;
         }
         return psz - 4;
      } 
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            return NULL;
         }
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            return NULL;
         }
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         return NULL;
      }
      return psz - 1;
   }

   string str::utf8_char(const char * psz)
   {
      const char * pszNext = utf8_inc(psz);
      if(pszNext == NULL)
         return "";
      return string(psz, pszNext  - psz);
   }

   string str::utf8_char(const char * pszBeg, const char * psz, int i)
   {
      if(i > 0)
      {
         while(i != 0)
         {
            psz = utf8_inc(psz);
            if(*psz == '\0')
            {
               return "";
            }
            i--;
         }
         return utf8_char(psz);
      }
      else
      {
         while(i != 0)
         {
            psz = utf8_dec(pszBeg, psz);
            if(psz == NULL)
            {
               return "";
            }
            else if(*psz == '\0')
            {
               return "";
            }
            i++;
         }
         return utf8_char(psz);
      }
   }

   string str::utf8_next_char(const char * pszBeg, const char * psz, int i)
   {
      return utf8_char(pszBeg, psz, i + 1);
   }

   string str::utf8_previous_char(const char * pszBeg, const char * psz, int i)
   {
      return utf8_next_char(pszBeg, psz, -i);
   }


   __int64 str::get_escaped_char(const char * lpcsz, int pos, int &retPos)
   {
      retPos = pos;
      if(lpcsz[pos] == '\\')
      {
         retPos++;
         if(lpcsz[pos+1] == 'x')
         {
            if(lpcsz[pos+2] == '{')
            {
               string val;
               if(!get_curly_content(&lpcsz[pos+2], val))
               {
                  return BAD_WCHAR;
               }
               __int64 hex = get_hex_number(val);
               int val_len = val.get_length();
               if(hex < 0 || hex > 0xFFFF) 
               {
                  return BAD_WCHAR;
               }
               retPos += val_len + 2;
               return hex;
            }
            else
            {
               __int64 hex = get_hex_number(string(&lpcsz[pos+2], 2));
               if(__int64(strlen(lpcsz)) <= pos + 2 || hex== -1) 
               {  
                  return BAD_WCHAR;
               }
               retPos += 2;
               return hex;
            }
         }
         return lpcsz[pos+1];
      }
      return lpcsz[pos];
   }

   __int64 str::get_hex_number(const char * lpcsz)
   {
      __int64 r = 0, num = 0;
      if(lpcsz == NULL) 
         return -1;
      for(__int64 i = strlen(lpcsz)-1; i >= 0; i--)
      {
         __int64 d = get_hex(&(lpcsz)[i]);
         if(d == -1) 
            return -1;
         num += d << r;
         r += 4;
      }
      return num;
   }


   bool str::get_curly_content(const char * psz, string & str)
   {
     if (psz[0] != '{') return false;
     const char * pszChar;
     for(pszChar = utf8_inc(psz); pszChar != NULL; pszChar = utf8_inc(pszChar))
     {
       if (*pszChar == '}')
         break;
     /*  ECharCategory cc = Character::getCategory(str[lpos]);
       // check for what??
       if (Character::isWhitespace(str[lpos]) ||
           cc == CHAR_CATEGORY_Cn || cc == CHAR_CATEGORY_Cc ||
           cc == CHAR_CATEGORY_Cf || cc == CHAR_CATEGORY_Cs)
         return null;*/
     };
     if (*pszChar == '\0')
        return false;
     str = string(&psz[1], pszChar - psz - 1);
     return true;
   }


   bool str::is_simple_natural(const char * pszCandidate)
   {
      string str(pszCandidate);
      str.trim();
      LPCTSTR psz = str;
      if(*psz == '\0')
         return false;
      while(*psz != '\0')
      {
         if(!gen::ch::is_digit(psz))
            return false;
         psz = utf8_inc(psz);
      }
      return true;
   }

   void str::consume(const char * & pszXml, const char * psz)
   {
     int idx;
     int len = strlen(psz);
     for(idx = 0; idx < len; idx++)
     {
        if(pszXml[idx] != psz[idx])
        {
           throw "Name does not match expected";
        }
     }
     pszXml += len;
   }


   void str::consume_spaces(const char * & pszXml, int iMinimumCount)
   {
      const char * psz = pszXml;
      int i = 0;
      while(gen::ch::is_whitespace(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(i < iMinimumCount)
      {
         throw "Space is required";
      }
      pszXml = psz;
   }


   string str::consume_nc_name(const char * & pszXml)
   {
      const char * psz = pszXml;
      bool start = true;
      while(true)
      {
         const char * c = psz;
         // first char
         if(start)
         {
            if(!gen::ch::is_letter(c) || *c == '\0')
            {
               throw "NCName required here";
            }
            start = false;
         }
         else
         {
            if(!gen::ch::is_letter_or_digit(c) && *c != '_' && *c != '-')
            {
               break;
            }
            psz = gen::str::utf8_inc(psz);
         }
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return str;
   }

   string str::consume_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string qc = utf8_char(psz);
      if(qc != "\"" && qc != "\\")
      {
         throw "Quote character is required here";
      }
      string str;
      while(true)
      {
         psz = utf8_inc(psz);
         string qc2 = utf8_char(psz);
         //string str = gen::international::utf8_to_unicode(qc2);
         if(qc2.is_empty())
         {
            throw "Quote character is required here, premature end";
         }
         if(qc2 == qc) 
            break;
         str += qc2;
      }
      psz = utf8_inc(psz);
      pszXml = psz;
      return str;
   }

   string str::consume_c_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string strQuoteChar = utf8_char(psz);
      if(strQuoteChar != "\"" && strQuoteChar != "\\")
      {
         throw "Quote character is required here";
      }
      string strCurrentChar;
      string str;
      string strPreviousChar;
      while(true)
      {
         psz = utf8_inc(psz);
         strPreviousChar = strCurrentChar;
         strCurrentChar = utf8_char(psz);
         //string str = gen::international::utf8_to_unicode(qc2);
         if(strCurrentChar.is_empty())
         {
            throw "Quote character is required here, premature end";
         }
         if(strPreviousChar == "\\")
         {
            str += strCurrentChar;
            strCurrentChar.Empty();
         }
         else if(strCurrentChar == "\\")
         {
         }
         else
         {
            if(strCurrentChar == strQuoteChar) 
               break;
            str += strCurrentChar;
         }
      }
      psz = utf8_inc(psz);
      pszXml = psz;
      return str;
   }

   bool str::begins_consume(const char * & pszXml, const char * psz)
   {
     int idx;
     int len = strlen(psz);
     for(idx = 0; idx < len; idx++)
     {
        if(pszXml[idx] != psz[idx])
        {
           return false;
        }
     }
     pszXml += len;
     return true;
   }

   bool str::xml_is_comment(const char * pszXml)
   {
     return pszXml[0] == '<' && pszXml[1] == '!' && pszXml[2] == '-';
   }

   string str::xml_consume_comment(const char * & pszXml)
   {
      string str;
      gen::str::consume(pszXml, "<!--");
      while(pszXml[0] != '-' || pszXml[1] != '-' ||pszXml[2] != '>')
      {
         
         if(*pszXml == '\0')
         {
            break;
         }
         str += *pszXml;
         pszXml = gen::str::utf8_inc(pszXml);
      }
      consume(pszXml, "-->");
     return str;
   }

   string str::pad(const char * psz, int iLen, const char * pszPattern, str::e_pad epad)
   {
      string str;
      str = psz;
      if(pszPattern == NULL || strlen(pszPattern) == 0)
         return str;
      int i = 0;
      if(epad == pad_left)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = pszPattern[i] + str;
            i++;
         }
      }
      else if(epad == pad_right)
      {
         while(str.get_length() < iLen)
         {
            if(pszPattern[i] == '\0')
               i = 0;
            str = str + pszPattern[i];
            i++;
         }
      }
      return str;
   }
   
   var str::ends_get(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      int iLen = strlen(psz);
      int iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix) == pszSuffix)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }

   var str::ends_get_ci(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      int iLen = strlen(psz);
      int iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix).CompareNoCase(pszSuffix) == 0)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }
/** \file Utility.cpp
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/
/*
Copyright (C) 2004-2007  Anders Hedstrom

This library is made available under the terms of the GNU GPL.

If you would like to use this library in a closed-source application,
a separate license agreement is available. For information about 
the closed-source license agreement for the C++ sockets library,
please visit http://www.alhem.net/Sockets/license.html and/or
email license@alhem.net.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
   string str::l2string(long l)
   {
      string str;
      char tmp[100];
      sprintf(tmp,"%ld",l);
      str = tmp;
      return str;
   }


   string str::bigint2string(uint64_t l)
   {
      string str;
      uint64_t tmp = l;
      while (tmp)
      {
         uint64_t a = tmp % 10;
         str = (char)(a + 48) + str;
         tmp /= 10;
      }
      if (!str.get_length())
      {
         str = "0";
      }
      return str;
   }


   uint64_t str::atoi64(const string & str) 
   {
      uint64_t l = 0;
      for (int i = 0; i < str.get_length(); i++)
      {
         l = l * 10 + str[i] - 48;
      }
      return l;
   }


   unsigned int str::hex2unsigned(const string & str)
   {
      unsigned int r = 0;
      for (int i = 0; i < str.get_length(); i++)
      {
         r = r * 16 + str[i] - 48 - ((str[i] >= 'A') ? 7 : 0) - ((str[i] >= 'a') ? 32 : 0);
      }
      return r;
   }

   string str::to_string(double d)
   {
      char tmp[100];
      sprintf(tmp, "%f", d);
      return tmp;
   }


   void str::increment_digit_letter(string & str)
   {
      int i = str.get_length() - 1;
      while(i >= 0)
      {
         if(str[i] >= '0' && str[i] <= '8')
         {
            str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == '9')
         {
            str = str.Left(i) + string((char)('a')) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] >= 'a' && str[i] <= 'y')
         {
            str = str.Left(i) + string((char)(str[i] + 1)) + str.Right(str.get_length() - i - 1);
            break;
         }
         else if(str[i] == 'z')
         {
            str = str.Left(i) + string((char)('0')) + str.Right(str.get_length() - i - 1);
            i--;
         }
      }
   }

/** End \file Utility.cpp
 **   \date  2004-02-13
 **   \author grymse@alhem.net
**/

} // namespace gen