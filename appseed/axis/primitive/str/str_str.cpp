#include "framework.h"


#ifdef LINUX
//#include <ctype.h>
#endif


namespace str
{




   const char trailingBytesForUTF8[256] = {
(const char)  -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
   };

   void          make_lower(char * psz)
   {

      while (*psz)
      {
         *psz = tolower(*psz);
         psz++;
      }

   }


   void          make_upper(char * psz)
   {

      while (*psz)
      {
         *psz = toupper(*psz);
         psz++;
      }

   }


   int32_t  compare(const char * psz1, const char * psz2)
   {
      return strcmp(psz1, psz2);
   }

   int32_t  compare_ci(const char * psz1, const char * psz2)
   {
      return stricmp_dup(psz1, psz2);
   }

   bool equals(const char * psz1, const char * psz2)
   {
      return compare(psz1, psz2) == 0;
   }

   bool equals_ci(const char * psz1, const char * psz2)
   {
      return compare_ci(psz1, psz2) == 0;
   }

   string  equals_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   string  equals_ci_get(const char * psz1, const char * psz2, const char * pszGetOnEqual, const char * pszGetOnDifferent)
   {
      return equals_ci(psz1, psz2) ? pszGetOnEqual : pszGetOnDifferent;
   }

   bool begins(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const char * lpcsz, const char * lpcszPrefix)
   {
      return begins(lpcsz, lpcszPrefix);
   }

   bool begins(const string & str, const char * lpcszPrefix)
   {
      if(str.is_empty())
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      const char * lpcsz = str;
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const string & str, const char * lpcszPrefix)
   {
      return begins(str, lpcszPrefix);
   }

   bool begins_ci(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(tolower(*lpcsz) == tolower(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const char * lpcsz, const char * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == '\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz && isspace(*lpcsz))
         lpcsz++;
      if(!*lpcsz)
         return false;
      while(tolower(*lpcsz) == tolower(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == '\0')
         {
            if(*lpcszPrefix == '\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == '\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci_iws(const string & str, const char * lpcszPrefix)
   {
      return begins_ci_iws(str.c_str(), lpcszPrefix);
   }


   bool begins_eat(string & str, const char * lpcszPrefix)
   {

      string strPrefix(lpcszPrefix);

      strsize iLen = strPrefix.get_length();

      if(str.Left(iLen) == lpcszPrefix)
      {
         str = str.Mid(iLen);
         return true;
      }

      return false;

   }

   bool begins_eat_ci(string & str, const char * lpcszPrefix)
   {

      if(lpcszPrefix == NULL)
         return true;

      string strPrefix(lpcszPrefix);

      strsize iLen = strPrefix.get_length();

      if(str.Left(iLen).CompareNoCase(lpcszPrefix) == 0)
      {
         str = str.Mid(iLen);
         return true;
      }

      return false;

   }

   bool begins_eat_ci(string & str, const char * lpcszPrefix, const char * pszSeparator)
   {
      if(str.CompareNoCase(lpcszPrefix) == 0)
      {
         str.Empty();
         return true;
      }
      else
      {
         return begins_eat_ci(str, string(lpcszPrefix) + pszSeparator);
      }
   }

   bool ends(const char * lpcsz, const char * lpcszSuffix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcszEnd = lpcsz;
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszEnd)
         lpcszEnd++;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(lpcszSuffixEnd[-1] == lpcszEnd[-1])
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;
      /*      string str(lpcsz);
      string strSuffix(lpcszSuffix);
      int32_t iLen = strSuffix.get_length();
      if(str.Right(iLen) == lpcszSuffix)
      {
      return true;
      }
      return false;*/
   }

   bool ends_ci(const char * lpcsz, const char * lpcszSuffix)
   {
      if(lpcsz == NULL || *lpcsz == '\0')
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcszEnd = lpcsz;
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszEnd)
         lpcszEnd++;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(tolower(lpcszSuffixEnd[-1]) == tolower(lpcszEnd[-1]))
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;

   }


   bool ends_ci(const string & str, const char * lpcszSuffix)
   {
      if(str.is_empty())
      {
         if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
            return true;
         else
            return false;
      }
      else if(lpcszSuffix == NULL || *lpcszSuffix == '\0')
      {
         return true;
      }
      const char * lpcsz = str;
      const char * lpcszEnd = lpcsz + str.get_length();
      const char * lpcszSuffixEnd = lpcszSuffix;
      while(*lpcszSuffixEnd)
         lpcszSuffixEnd++;
      if((lpcszSuffixEnd - lpcszSuffix) > (lpcszEnd - lpcsz))
         return false;
      while(tolower(lpcszSuffixEnd[-1]) == tolower(lpcszEnd[-1]))
      {
         lpcszSuffixEnd--;
         lpcszEnd--;
         if(lpcszSuffixEnd <= lpcszSuffix)
            return true;
      }

      return false;

   }

   bool ends_ci(const var & var, const char * lpcszSuffix)
   {
      return ends_ci(var.get_string(), lpcszSuffix);
   }


   bool ends_eat_ci(string & str, const char * lpcszSuffix)
   {

      string strSuffix(lpcszSuffix);

      strsize iLen = strSuffix.get_length();

      if(str.Right(iLen).CompareNoCase(lpcszSuffix) == 0)
      {

         str = str.Left(str.get_length() - iLen);
         return true;

      }

      return false;

   }

   void copy(string & str, const char * lpcsz, int32_t iCount)
   {
      string strCopy(lpcsz, iCount);
      str = strCopy;
   }

   string replace(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {
      string str(psz);
      str.replace(pszFind, pszReplace, iStart);
      return str;
   }


   index  find_first(const string_array & straSearch, index & iFound, const string & str, index iStart)
   {

      index iFind = -1;

      iFound = -1;

      for(index i = 0; i < straSearch.get_count(); i++)
      {

         if(straSearch[i].has_char())
         {

            index iSearch = str.find(straSearch[i], iStart);

            if(iSearch >= 0 && iSearch >= iStart && (iSearch < iFind || iFind < 0))
            {

               iFind = iSearch;
               iFound = i;

            }

         }

      }

      return iFind;

   }

   string  random_replace(sp(::axis::application) papp, const string_array & straReplacement, const string_array & straSearch, const char * psz)
   {

      string str(psz);

      index iFind;

      index iFound;

      index iStart = 0;

      while((iFind = find_first(straSearch, iFound, str, iStart)) >= 0)
      {

         if(iFind < iStart)
         {
            throw_parsing_exception("random replace error");
            return "";
         }

         index i = (index) (rand() % straReplacement.get_size());

         str = str.Left(iFind) + straReplacement[i] + str.Mid(iFind + straSearch[iFound].get_length());

         iFind += straReplacement[i].get_length();

         iStart = iFind;

      }

      return str;
   }

   string replace_ci(const char * pszFind, const char * pszReplace, const char * psz, strsize iStart)
   {

      index iPos = iStart;

      string str(psz);

      ::count iReplaceLen = -1;

      ::count iFindLen = -1;

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

   index find_ci(const string & strFind, const string & str, index iStart)
   {

      if(strFind.get_length() > (str.get_length() - iStart))
         return -1;

      string strFindLow(&((LPCSTR)strFind)[0], strFind.get_length()); // avoid optimized read only string copy

      strFindLow.make_lower();

      string strLow(&((LPCSTR)str)[iStart], str.get_length() - iStart); // avoid optimized read only string copy

      strLow.make_lower();

      index iFind = strLow.find(strFindLow);

      if(iFind < 0)
         return -1;

      return iStart + iFind;

   }


   index find_ci(const string & strFind, const char * psz, index iStart)
   {

      ::count iFindLen = strFind.get_length();

      ::count iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         memcpy(szFind, strFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            memcpy(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            const char * pszFind = strstr(sz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

            strLow.make_lower();

            psz = strLow;

            const char * pszFind = strstr(psz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - psz);

         }

      }
      else
      {

         string strFindLow(&((LPCSTR)strFind)[0], iFindLen); // avoid optimized read only string copy

         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy

         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }


   index find_ci(const char * pszFind, const string & str, index iStart)
   {

      ::count iFindLen = strlen(pszFind);

      index iLen = str.get_length() - iStart;

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         memcpy(szFind, pszFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            memcpy(sz, &((LPCSTR)str)[iStart], iLen + 1);

            make_lower(sz);

            pszFind = strstr(sz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - sz);

         }
         else
         {

            string strLow(&((LPCSTR)str)[iStart], iLen); // avoid optimized read only string copy

            strLow.make_lower();

            const char * psz = strLow;

            pszFind = strstr(psz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - psz);

         }

      }
      else
      {

         string strFindLow(pszFind, iFindLen); // avoid optimized read only string copy

         strFindLow.make_lower();

         string strLow(&((LPCSTR)str)[iStart], iLen); // avoid optimized read only string copy

         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }


   index find_ci(const char * pszFind, const char * psz, index iStart)
   {

      index iFindLen = strlen(pszFind);

      index iLen = strlen(&psz[iStart]);

      if(iFindLen > iLen)
         return -1;

      if(iFindLen < 256)
      {

         char szFind[256];

         memcpy(szFind, pszFind, iFindLen + 1);

         make_lower(szFind);

         if(iLen < 256)
         {

            char sz[256];

            memcpy(sz, &psz[iStart], iLen + 1);

            make_lower(sz);

            pszFind = strstr(sz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - sz);

         }
         else
         {

            string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
            strLow.make_lower();

            psz = strLow;

            pszFind = strstr(psz, szFind);

            if(pszFind == NULL)
               return -1;

            return iStart + (pszFind - psz);

         }

      }
      else
      {

         string strFindLow(pszFind, iFindLen); // avoid optimized read only string copy
         strFindLow.make_lower();

         string strLow(&psz[iStart], iLen); // avoid optimized read only string copy
         strLow.make_lower();

         index iFind = strLow.find(strFindLow);

         if(iFind < 0)
            return -1;

         return iStart + iFind;

      }

   }

   index find_wwci(const char * pszFind, const char * psz, index iStart)
   {

      string strFind(pszFind);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_ww(strFind, str, iStart);

   }

   index find_awwci(const char * pszFind, const char * psz, index iStart)
   {

      string strFind(pszFind);

      strFind.make_lower();

      string str(psz);

      str.make_lower();

      return find_aww(strFind, str, iStart);

   }

   index find_ww(const char * pszFind, const char * psz, index iStart)
   {

      if(psz == NULL)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == NULL)
         return -1;

      string strFind(pszFind);

      index i = 0;

      if(iStart == 0)
      {

         if(strFind == string(pszIter, strFind.get_length())
            && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter_or_digit(pszIter + strFind.get_length())))
         {
            return i;
         }

      }
      while(*pszIter != '\0')
      {

         string strChar = get_utf8_char(pszIter);

         if(!::str::ch::is_letter_or_digit(strChar))
         {

            do
            {
               i += strChar.get_length();
               pszIter = utf8_inc(pszIter);
               strChar = get_utf8_char(pszIter);
            }
            while(!::str::ch::is_letter_or_digit(strChar) && *pszIter != '\0');

            if(*pszIter == '\0')
               break;

            if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter_or_digit(pszIter + strFind.get_length())))
            {

               return iStart + i;

            }

         }

         i += strChar.get_length();

         pszIter = utf8_inc(pszIter);

      }

      return -1;

   }

   index find_aww(const char * pszFind, const char * psz, index iStart)
   {

      if(psz == NULL)
         return -1;

      const char * pszIter = &psz[iStart];

      if(pszIter == NULL)
         return -1;

      string strFind(pszFind);

      index i = 0;

      if(iStart == 0)
      {

         if(strFind == string(pszIter, strFind.get_length())
            && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter(pszIter + strFind.get_length())))
         {

            return i;

         }

      }

      while(*pszIter != '\0')
      {

         string strChar = get_utf8_char(pszIter);

         if(!::str::ch::is_letter(strChar))
         {

            do
            {

               i += strChar.get_length();

               pszIter = utf8_inc(pszIter);

               strChar = get_utf8_char(pszIter);

            }
            while(!::str::ch::is_letter(strChar) && *pszIter != '\0');

            if(*pszIter == '\0')
               break;

            if(strFind == string(pszIter, strFind.get_length())
               && (strlen(pszIter) == (size_t) strFind.get_length() || !::str::ch::is_letter(pszIter + strFind.get_length())))
            {

               return iStart + i;

            }
         }

         i += strChar.get_length();

         pszIter = utf8_inc(pszIter);

      }

      return -1;

   }

   string has_char(const char * pszIfHasChar, const char * pszBefore, const char * pszAfter)
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


   bool has_upper(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper;

   }

   bool has_lower(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasLower;

   }

   bool has_digit(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasDigit;

   }

   void calc_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      bHasUpper = false;
      bHasLower = false;
      bHasDigit = false;

      while(true)
      {
         string qc = get_utf8_char(psz);
         if(qc.is_empty())
         {
            break;
         }
         else if(::str::ch::is_digit(qc))
         {
            bHasDigit = true;
         }
         else if(::str::ch::is_lower_case(qc))
         {
            bHasLower = true;
         }
         else if(::str::ch::is_upper_case(qc))
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

   bool has_one_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper || bHasLower || bHasDigit;

   }

   bool has_all_v1(const char * psz, bool & bHasUpper, bool & bHasLower, bool & bHasDigit)
   {

      calc_v1(psz, bHasUpper, bHasLower, bHasDigit);

      return bHasUpper && bHasLower && bHasDigit;

   }

   bool has_all_v1(const char * psz)
   {

      bool bHasUpper;
      bool bHasLower;
      bool bHasDigit;

      return has_all_v1(psz, bHasUpper, bHasLower, bHasDigit);

   }


   string if_null(const char * psz, const char * pszIfNull)
   {

      if(psz == NULL)
         return pszIfNull;
      else
         return psz;

   }

   string get_window_text(oswindow oswindow)
   {

      string str;

      if (oswindow != NULL)
      {

#ifdef WINDOWSEX

         int32_t nLen = ::GetWindowTextLength(oswindow);

         ::GetWindowText(oswindow, str.GetBufferSetLength(nLen), nLen+1);

         str.ReleaseBuffer();

#else

         throw todo(get_thread_app());

#endif

      }

      return str;

   }

   string get_word(
      const char * psz,
      const char * pszSeparator,
      bool bWithSeparator,
      bool bEndIsSeparator)
   {

      if(psz == NULL)
         return string();

      if(pszSeparator == NULL)
      {

         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      const char * pszFind = strstr(psz, pszSeparator);
      if(pszFind == NULL)
      {
         if(bEndIsSeparator)
         {
            return psz;
         }
         else
         {
            return string();
         }
      }
      if(bWithSeparator)
      {
         return string(psz, pszFind - psz + 1);
      }
      else
      {
         return string(psz, pszFind - psz);
      }
   }

   bool to(const char * psz, int64_t & i)
   {

      char * pszEnd;

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool to(const char * psz, int32_t & i)
   {

      const char * pszEnd;

      int64_t iConversion = ::atoi_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int32_t > ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }


   bool to(const char * psz, int64_t & i, int32_t iAxis)
   {

      if(iAxis < 0 || iAxis == 1 || iAxis > 36)
         return false;

      char * pszEnd;

#ifdef WINDOWS

      int64_t iConversion = ::_strtoi64(psz, &pszEnd, iAxis);

#else

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd, iAxis);

#endif

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool to(const char * psz, int32_t & i, int32_t iAxis)
   {

      if(iAxis < 0 || iAxis == 1 || iAxis > 36)
         return false;

      char * pszEnd;

#ifdef WINDOWS

      int64_t iConversion = ::_strtoi64(psz, &pszEnd, iAxis);

#else

      int64_t iConversion = ::atoi64_dup(psz, &pszEnd, iAxis);

#endif

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info::get_maximum_value < int32_t > ())
         return false;

      i = (int32_t) iConversion;

      return true;

   }

   bool to(const char * psz, uint64_t & ui)
   {

      char * pszEnd;

      uint64_t uiConversion = ::atoi64_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      ui = uiConversion;

      return true;

   }

   bool to(const char * psz, uint32_t & ui)
   {

      const char * pszEnd;

      int64_t uiConversion = ::atoui_dup(psz, &pszEnd);

      if(pszEnd == psz)
         return false;

      if(uiConversion > numeric_info::get_maximum_value < uint32_t > ())
         return false;

      ui = (uint32_t) uiConversion;

      return true;

   }


   bool to(const char * psz, uint64_t & ui, int32_t iAxis)
   {

      if(iAxis < 0 || iAxis == 1 || iAxis > 36)
         return false;

      char * pszEnd;

      uint64_t uiConversion = ::atoui64_dup(psz, &pszEnd, iAxis);

      if(pszEnd == psz)
         return false;

      ui = uiConversion;

      return true;

   }

   bool to(const char * psz, uint32_t & ui, int32_t iAxis)
   {

      if(iAxis < 0 || iAxis == 1 || iAxis > 36)
         return false;

      const char * pszEnd;

      uint32_t uiConversion = ::atoui_dup(psz, &pszEnd, iAxis);

      if(pszEnd == psz)
         return false;

      if(uiConversion > numeric_info::get_maximum_value < uint32_t > ())
         return false;

      ui = uiConversion;

      return true;

   }

     int_ptr to_int_ptr(const char * psz)
   {

#if defined(_LP64) || defined(_AMD64_)

      return to_int64(psz);

#else
      return to_int(psz);

#endif

   }



   string & from(string & str, int32_t i)
   {

      str = i64toa_dup(i);

      return str;

   }


   string & from(string & str, uint32_t ui)
   {

      str = ui64toa_dup(ui);

      return str;

   }


   string & from(string & str, int64_t i)
   {

      str = i64toa_dup(i);

      return str;

   }

   string & from(string & str, uint64_t ui)
   {

//      str.Format("%I64u", ui);

      return str = ui64toa_dup(ui, 10);

   }

   string & from(string & str, float f)
   {
       char sz[256];
        sprintf(sz, "%f", f);
      str = sz;

      return str;

   }

   string & from(string & str, double d)
   {

       char sz[256];
        sprintf(sz, "%f", d);
      str = sz;

      return str;

   }


   string uni_to_utf8(int64_t w)
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


   const char * utf8_inc(const char * psz)
   {
      char len =  1 + ::str::trailingBytesForUTF8[(uchar) *psz];
      if(len == 0)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 1)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 2)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 3)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 4)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 5)      return psz;
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 6)      return psz;
      throw invalid_character(get_thread_app(), "invalid utf8 character");
   }


   const char * utf8_inc_slide(strsize * pslide, const char * psz)
   {
      char len =  1 + ::str::trailingBytesForUTF8[(uchar) *psz];
      if(len == 0)   { *pslide += 0; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 1)   { *pslide += 1; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 2)   { *pslide += 2; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 3)   { *pslide += 3; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 4)   { *pslide += 4; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 5)   { *pslide += 5; return psz; }
      if(*psz++ == 0)   throw invalid_character(get_thread_app(), "invalid utf8 character");
      if(len == 6)   { *pslide += 6; return psz; }
      throw invalid_character(get_thread_app(), "invalid utf8 character");
   }


   const char * utf8_inc_copy_slide_back(strsize * pslideback, char * pchDst, const char * pchSrc)
   {

      strsize count = 0;

      ::str::utf8_inc_slide(&count, pchSrc);

      memcpy(pchDst, pchSrc, count);

      pchSrc         += count;

      pchDst         += count;

      *pslideback    -= count;

      return pchSrc;

   }



   const char * utf8_dec(const char * pszBeg, const char * psz)
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

   const char * utf8_dec(::str::utf8_char * pchar, const char * pszBeg, const char * psz)
   {
      if(psz <= pszBeg)
      {
         pchar->m_chLen = -1;
         return NULL;
      }
      if((*(psz - 1) & 0x80) == 0x00)
      {
         if((psz - 1) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-1];
         pchar->m_sz[1] = '\0';
         pchar->m_chLen = 1;
         return psz - 1;
      }
      else if((*(psz - 2) & 0xE0) == 0xC0)
      {
         if((psz - 2) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-2];
         pchar->m_sz[1] = psz[-1];
         pchar->m_sz[2] = '\0';
         pchar->m_chLen = 2;
         return psz - 2;
      }
      else if((*(psz - 3) & 0xF0) == 0xE0)
      {
         if((psz - 3) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-3];
         pchar->m_sz[1] = psz[-2];
         pchar->m_sz[2] = psz[-1];
         pchar->m_sz[3] = '\0';
         pchar->m_chLen = 3;
         return psz - 3;
      }
      else if((*(psz - 4) & 0xF8) == 0xF0)
      {
         if((psz - 4) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-4];
         pchar->m_sz[1] = psz[-3];
         pchar->m_sz[2] = psz[-2];
         pchar->m_sz[3] = psz[-1];
         pchar->m_sz[4] = '\0';
         pchar->m_chLen = 4;
         return psz - 4;
      }
      else if((*(psz - 5) & 0xFC) == 0xF8)
      {
         if((psz - 5) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-5];
         pchar->m_sz[1] = psz[-4];
         pchar->m_sz[2] = psz[-3];
         pchar->m_sz[3] = psz[-2];
         pchar->m_sz[4] = psz[-1];
         pchar->m_sz[5] = '\0';
         pchar->m_chLen = 5;
         return psz - 5;
      }
      else if((*(psz - 6) & 0xFE) == 0xFC)
      {
         if((psz - 6) < pszBeg)
         {
            pchar->m_chLen = -1;
            return NULL;
         }
         pchar->m_sz[0] = psz[-6];
         pchar->m_sz[1] = psz[-5];
         pchar->m_sz[2] = psz[-4];
         pchar->m_sz[3] = psz[-3];
         pchar->m_sz[4] = psz[-2];
         pchar->m_sz[5] = psz[-1];
         pchar->m_sz[6] = '\0';
         pchar->m_chLen = 6;
         return psz - 6;
      }
      if((psz - 1) < pszBeg)
      {
         pchar->m_chLen = -1;
         return NULL;
      }
      pchar->m_sz[0] = psz[-1];
      pchar->m_sz[1] = '\0';
      pchar->m_chLen = 1;
      return psz - 1;
   }


   string get_utf8_char(const char * psz)
   {
      ::str::utf8_char ch;
      int32_t len = ch.parse(psz);
      if(len < 0)
         return "";
      return string(ch.m_sz);
   }

   string get_utf8_char(const char * psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
         return "";
      return string(psz, pszNext - psz);
   }

   bool get_utf8_char(string & str, const char * & psz, const char * pszEnd)
   {
      const char * pszNext = __utf8_inc(psz);
      if(pszNext > pszEnd)
      {
         return false;
      }
      str = string(psz, pszNext - psz);
      psz = pszNext;
      return true;
   }

   string get_utf8_char(const char * pszBeg, const char * psz, index i)
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
         return get_utf8_char(psz);
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
         return get_utf8_char(psz);
      }
   }

   string utf8_next_char(const char * pszBeg, const char * psz, index i)
   {
      return get_utf8_char(pszBeg, psz, i + 1);
   }

   string utf8_previous_char(const char * pszBeg, const char * psz, index i)
   {
      return utf8_next_char(pszBeg, psz, -i);
   }


   int32_t get_escaped_char(const char * lpcsz, strsize pos, strsize &retPos)
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
               int64_t hex = ::hex::to_int64(val);
               strsize val_len = val.get_length();
               if(hex < 0 || hex > 0xFFFF)
               {
                  return BAD_WCHAR;
               }
               retPos += val_len + 2;
               return (int32_t) hex;
            }
            else
            {
               int64_t hex = ::hex::to_int64(string(&lpcsz[pos+2], 2));
               if(int64_t(strlen(lpcsz)) <= pos + 2 || hex== -1)
               {
                  return BAD_WCHAR;
               }
               retPos += 2;
               return (int32_t) hex;
            }
         }
         return lpcsz[pos+1];
      }
      return lpcsz[pos];
   }

   bool get_curly_content(const char * psz, string & str)
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
         return NULL;*/
      };
      if (*pszChar == '\0')
         return false;
      str = string(&psz[1], pszChar - psz - 1);
      return true;
   }


   bool is_simple_natural(const char * pszCandidate)
   {
      string str(pszCandidate);
      str.trim();
      LPCSTR psz = str;
      if(*psz == '\0')
         return false;
      while(*psz != '\0')
      {
         if(!::str::ch::is_digit(psz))
            return false;
         psz = utf8_inc(psz);
      }
      return true;
   }

   void consume(const char * & pszXml, const char * psz)
   {

      index idx;

      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }

   void consume(const char * & pszXml, const char * psz, const char * pszEnd)
   {
      UNREFERENCED_PARAMETER(pszEnd);
      strsize idx;
      strsize len = strlen(psz);
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }

   void consume(const char * & pszXml, const char * psz, strsize len, const char * pszEnd)
   {
      UNREFERENCED_PARAMETER(pszEnd);
      int32_t idx;
      for(idx = 0; idx < len; idx++)
      {
         if(pszXml[idx] != psz[idx])
         {
            throw_parsing_exception("Name does not match expected");
            break;
         }
      }
      pszXml += len;
   }

   void consume_spaces(const char * & pszXml, ::count iMinimumCount)
   {
      const char * psz = pszXml;
      int32_t i = 0;
      while(::str::ch::is_whitespace(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(i < iMinimumCount)
      {
         throw_parsing_exception("Space is required");
      }
      pszXml = psz;
   }

   uint64_t consume_natural(const char * & pszXml, uint64_t uiMax, uint64_t uiMin)
   {
      if(uiMax < uiMin)
      {
         throw invalid_argument_exception(get_thread_app(), "max should be greater than min");
      }
      const char * psz = pszXml;
      int32_t i = 0;
      uint64_t ui;
      while(::str::ch::is_digit(psz))
      {
         psz = utf8_inc(psz);
         i++;
      }
      if(psz == pszXml)
      {
         throw_parsing_exception("empty natural found");
         goto end;
      }
      ui = ::str::to_uint(string(pszXml, psz - pszXml));
      if(ui < uiMin)
      {
         throw_parsing_exception("natural less than min");
      }
      else if(ui > uiMax)
      {
         throw_parsing_exception("natural greater than max");
      }
      end:
      pszXml = psz;

      return ui;

   }

   void consume_spaces(const char * & pszXml, ::count iMinimumCount, const char * pszEnd)
   {
      const char * psz = pszXml;
      int32_t i = 0;
      while(::str::ch::is_whitespace(psz, pszEnd))
      {
         psz = __utf8_inc(psz);
         if(psz > pszEnd)
         {
            throw_parsing_exception("premature end");
            break;
         }
         i++;
      }
      if(i < iMinimumCount)
      {
         throw_parsing_exception("Space is required");
      }
      pszXml = psz;
   }

   string consume_hex(const char * & pszXml)
   {
      const char * psz = pszXml;
//      int32_t i = 0;
      while(*psz != '\0')
      {
         int64_t i = ::str::ch::uni_index(pszXml);
         if(isdigit((int32_t) i) || (i >= 'a' && i <= 'f') || (i >= 'A' && i <= 'F'))
         {
            psz = __utf8_inc(psz);
         }
      }
      if(psz == pszXml)
      {
         throw_parsing_exception("no hex consumed");
         return "";
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return psz;
   }


   string consume_nc_name(const char * & pszXml)
   {
      const char * psz = pszXml;
      bool start = true;
      while(true)
      {
         const char * ca = psz;
         // first char
         if(start)
         {
            if(!::str::ch::is_letter(ca) || *ca == '\0')
            {
               throw_parsing_exception("NCName required here");
               return "";
            }
            start = false;
         }
         else
         {
            if(!::str::ch::is_letter_or_digit(ca) && *ca != '_' && *ca != '-')
            {
               break;
            }
            psz = ::str::utf8_inc(psz);
         }
      }
      string str(pszXml, psz - pszXml);
      pszXml = psz;
      return str;
   }

   string consume_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string qc = get_utf8_char(psz); // quote character
      if(qc != "\"" && qc != "\\")
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      string str;
      string qc2;
      while(true)
      {
         psz = utf8_inc(psz);
         qc2 = get_utf8_char(psz);
         //string str = ::str::international::utf8_to_unicode(qc2);
         if(qc2.is_empty())
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         if(qc2 == qc)
            break;
         str += qc2;
      }
      psz = utf8_inc(psz);
      pszXml = psz;
      return str;
   }

   string consume_quoted_value(const char * & pszXml, const char * pszEnd)
   {
      const char * psz = pszXml;
      string qc; // quote character
      if(!get_utf8_char(qc,psz,pszEnd))
      {
         throw_parsing_exception("Quote character is required here, premature end");
         return "";
      }
      if(qc != "\"" && qc != "\\")
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      const char * pszValueStart = psz;
      const char * pszValueEnd = psz;
      const char * pszNext = psz;
      const char * pszQc = qc;
      string qc2;
      char qclen = (char) qc.get_length();
       char i;
      while(true)
      {
         pszNext = __utf8_inc(psz);
         if(pszNext > pszEnd)
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
         }
         for(i = 0; i < qclen && psz < pszNext; i++)
         {
            if(*psz != pszQc[i])
               break;
            psz++;
         }
         if(i == qclen)
            break;
         psz = pszNext;
         pszValueEnd = psz;
      }
      pszXml = psz;
      return string(pszValueStart, pszValueEnd - pszValueStart);
   }

   string consume_c_quoted_value(const char * & pszXml)
   {
      const char * psz = pszXml;
      string strQuoteChar = get_utf8_char(psz);
      if(strQuoteChar != "\"" && strQuoteChar != "\\")
      {
         throw_parsing_exception("Quote character is required here");
         return "";
      }
      string strCurrentChar;
      string str;
      string strPreviousChar;
      while(true)
      {
         psz = utf8_inc(psz);
         strPreviousChar = strCurrentChar;
         strCurrentChar = get_utf8_char(psz);
         //string str = ::str::international::utf8_to_unicode(qc2);
         if(strCurrentChar.is_empty())
         {
            throw_parsing_exception("Quote character is required here, premature end");
            return "";
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

   bool begins_consume(const char * & pszXml, const char * psz)
   {
      strsize idx;
      strsize len = strlen(psz);
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

   bool xml_is_comment(const char * pszXml)
   {
      return pszXml[0] == '<' && pszXml[1] == '!' && pszXml[2] == '-';
   }

   string xml_consume_comment(const char * & pszXml)
   {
      string str;
      ::str::consume(pszXml, "<!--");
      while(pszXml[0] != '-' || pszXml[1] != '-' ||pszXml[2] != '>')
      {

         if(*pszXml == '\0')
         {
            break;
         }
         str += *pszXml;
         pszXml = ::str::utf8_inc(pszXml);
      }
      consume(pszXml, "-->");
      return str;
   }

   string pad(const char * psz, ::count iLen, const char * pszPattern, e_pad epad)
   {
      string str;
      str = psz;
      if(pszPattern == NULL || strlen(pszPattern) == 0)
         return str;
      int32_t i = 0;
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

   var ends_get(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
      if(str.Right(iLenSuffix) == pszSuffix)
      {
         return str.Mid(0, iLen - iLenSuffix);
      }
      return false;
   }

   var ends_get_ci(const char * pszSuffix, const char * psz)
   {
      if(pszSuffix == NULL)
         return psz;
      if(psz == NULL)
         return "";
      string str(psz);
      strsize iLen = strlen(psz);
      strsize iLenSuffix = strlen(pszSuffix);
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
/*   string l2string(long l)
   {
      string str;
      char tmp[100];
      sprintf(tmp,"%ld",l);
      str = tmp;
      return str;
   }


   string bigint2string(uint64_t l)
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
   }*/

   int32_t to_int(const char * psz)
   {
      return atoi_dup(psz);
   }

   uint32_t to_uint(const char * psz)
   {
      return (uint32_t) atoi64_dup(psz);
   }

   int64_t to_int64(const string & str)
   {

      int32_t i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      bool bNegative = str[i] == '-';

      if(bNegative)
         i++;

      uint64_t ui = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         ui = ui * 10 + str[i] - 48;
      }

      if(bNegative)
         return -(int64_t) ui;
      else
         return (int64_t) ui;
   }

   int64_t to_int64(const char * psz)
   {

      int32_t i = 0;

      for (; *psz != '\0' && i < 30 && isspace((uchar ) *psz); i++, psz++);

      bool bNegative = *psz == '-';

      if(bNegative)
         psz++;

      uint64_t ui = 0;

      for(; *psz != '\0' && i < 30 && isdigit((uchar ) *psz); psz++, i++)
      {
         ui = ui * 10 + *psz - 48;
      }

      if(bNegative)
         return -(int64_t) ui;
      else
         return (int64_t) ui;

   }

   uint64_t to_uint64(const string & str)
   {

      int32_t i = 0;

      for (; i < str.get_length() && isspace(str[i]); i++);

      uint64_t ui = 0;

      for(; i < str.get_length() && isdigit(str[i]); i++)
      {
         ui = ui * 10 + str[i] - 48;
      }

      return ui;

   }

   uint64_t to_uint64(const char * psz)
   {

      int32_t i = 0;

      for (; *psz != '\0' && i < 30 && isspace(*psz); i++, psz++);

      uint64_t ui = 0;

      for(; *psz != '\0' && i < 30 && isdigit(*psz); psz++, i++)
      {
         ui = ui * 10 + *psz - 48;
      }

      return ui;

   }



   void increment_digit_letter(string & str)
   {
      strsize i = str.get_length() - 1;
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


   bool  while_begins_with_chars_eat(string & str, const char * lpcszChars)
   {
      int32_t i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(lpcszChars, str[i]) == NULL)
            break;
      }
      str = str.Mid(i);
      return i > 0;
   }

   bool  while_begins_with_chars_eat_ci(string & str, const char * lpcszChars) // case insensitive
   {
      int32_t i = 0;
      for(i = 0; i < str.get_length(); i++)
      {
         if(strchr(lpcszChars, tolower(str[i])) == NULL)
            break;
      }
      str = str.Mid(i);
      return i > 0;
   }


   void begin(wstring & wstr, const wchar_t * lpcszPrefix)
   {

      strsize iPrefixLen = wcslen_dup(lpcszPrefix);
      if(natural(wstr.storage_size()) >= ((wstr.get_length() + iPrefixLen + 1) * sizeof(wchar_t)))
      {
         memmove(&wstr[iPrefixLen], (const wchar_t *) wstr, (wstr.get_length() + 1) * sizeof(wchar_t));
         memcpy_dup(wstr, lpcszPrefix, iPrefixLen);
      }
      else
      {
         wstring wstrNew;
         wstrNew.alloc((wstr.get_length() + iPrefixLen + 1) * sizeof(wchar_t));
         memcpy_dup(&wstrNew[iPrefixLen], (const wchar_t *) wstr, (wstr.get_length() + 1) * sizeof(wchar_t));
         memcpy_dup(wstrNew, lpcszPrefix, iPrefixLen * sizeof(wchar_t));
         wstr.attach(wstrNew.detach());
      }

   }


   bool begins(const wchar_t * lpcsz, const wchar_t * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const wchar_t * lpcsz, const wchar_t * lpcszPrefix)
   {
      return begins(lpcsz, lpcszPrefix);
   }

   bool begins(const wstring & str, const wchar_t * lpcszPrefix)
   {
      if(str.is_empty())
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      const wchar_t * lpcsz = str;
      while(*lpcsz == *lpcszPrefix)
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_with(const wstring & str, const wchar_t * lpcszPrefix)
   {
      return begins(str, lpcszPrefix);
   }



   // case insensitive, ignore white space - only in searched string
   bool begins_ci(const wchar_t * lpcsz, const wchar_t * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(::str::ch::to_lower_case(*lpcsz) == ::str::ch::to_lower_case(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci(const wstring & wstr, const wchar_t * lpcszPrefix)
   {
      return begins_ci_iws((const wchar_t *) wstr, lpcszPrefix);
   }

   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const wchar_t * lpcsz, const wchar_t * lpcszPrefix)
   {
      if(lpcsz == NULL || *lpcsz == L'\0')
      {
         if(lpcszPrefix == NULL || *lpcszPrefix == L'\0')
         {
            return true;
         }
         else
         {
            return false;
         }
      }
      while(*lpcsz && ::str::ch::is_space_char(*lpcsz))
         lpcsz++;
      if(!*lpcsz)
         return false;
      while(::str::ch::to_lower_case(*lpcsz) == ::str::ch::to_lower_case(*lpcszPrefix))
      {
         lpcsz++;
         lpcszPrefix++;
         if(*lpcsz == L'\0')
         {
            if(*lpcszPrefix == L'\0')
               return true;
            else
               return false;
         }
         else if(*lpcszPrefix == L'\0')
         {
            return true;
         }
      }
      return false;
   }

   bool begins_ci_iws(const wstring & wstr, const wchar_t * lpcszPrefix)
   {
      return begins_ci_iws((const wchar_t *) wstr, lpcszPrefix);
   }


    string          to_lower(const char * psz)
   {

      return string(psz).make_lower();

   }


   string          to_upper(const char * psz)
   {

      return string(psz).make_upper();

   }


   /** End \file Utility.cpp
   **   \date  2004-02-13
   **   \author grymse@alhem.net
   **/


   bool simple_escaped(const string & str, strsize pos)
   {

      if(pos == 0)
         return false;

      return str[pos - 1] == '\\' && !simple_escaped(str, pos - 1);

   }


} // namespace str


