/**
*   PROJECT - HTML Reader Class Library
*
*   LiteHTMLAttributes.cpp
*
*   Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
*   Copyright (ca) 2004.
*
*   This code may be used in compiled form in any way you desire
*   (including commercial use). The code may be redistributed
*   unmodified by any means PROVIDING it is not sold for profit
*   without the authors written consent, and providing that this
*   notice and the authors name and all copyright notices remains
*   intact. However, this file and the accompanying source code may
*   not be hosted on a website or bulletin board without the authors
*   written permission.
*
*   This file is provided "AS IS" with no expressed or implied warranty.
*   The author accepts no liability for any damage/loss of business that
*   this product may cause.
*
*   Although it is not necessary, but if you use this code in any of
*   your application (commercial or non-commercial), please INFORM me
*   so that I may know how useful this library is. This will encourage
*   me to keep updating it.
*/
#include "framework.h"

/*#pragma warning(push, 4)

const COLORREF LiteHTMLElemAttr::_clrInvalid = (COLORREF)0xFFFFFFFF;
const uint16_t LiteHTMLElemAttr::_percentMax = USHRT_MAX;

// the reason behind setting the block size of our collection
// to 166 is that we have a total of 166 known named colors
//LiteHTMLElemAttr::CNamedColors LiteHTMLElemAttr::_namedColors(166 /* block size */

//#pragma warning(pop)


/**
* LiteHTMLElemAttr::parseFromStr
*
* @param lpszString - string to parse
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr LiteHTMLElemAttr::parseFromStr(::lite_html_reader * preader, const char * lpszString)
{
   ASSERT(__is_valid_string(lpszString));

   const char *   lpszBegin = lpszString;
   const char *   lpszEnd;
   //   char   ch = 0;

   // skip leading white-space characters
   while(::isspace((uchar) *lpszBegin))
      lpszBegin++;

   // name doesn't begin with an alphabet?
   if (!::isalpha((uchar) *lpszBegin))
      return (0U);

   lpszEnd = lpszBegin;
   do
   {
      // attribute name may contain letters (a-z, A-Z), digits (0-9),
      // underscores '_', hyphen '-', colons ':', and periods '.'
      if ( (!::isalnum((uchar) *lpszEnd)) &&
         (*lpszEnd != '-') && (*lpszEnd != ':') &&
         (*lpszEnd != '_') && (*lpszEnd != '.') )
      {
         ASSERT(lpszEnd != lpszBegin);

         // only white-space characters, a NULL-character, an
         // equal-sign, a greater-than symbol, or a forward-slash
         // can act as the separator between an attribute and its
         // value
         if (*lpszEnd =='\0' || ::isspace((uchar) *lpszEnd) ||
            *lpszEnd == '=' ||
            *lpszEnd == '>' || *lpszEnd == '/')
         {
            break;
         }

         return (0U);   // any other character will fail parsing process
      }

      lpszEnd++;
   }
   while (true);

   // extract attribute name
   string   strAttrName(lpszBegin, int32_t(lpszEnd - lpszBegin));

   // skip leading white-space characters
   while (::isspace((uchar)*lpszEnd))
      lpszEnd++;


   if (*lpszEnd != '=')
   {
      m_strName = strAttrName;
      m_strValue.Empty();
      return (lpszEnd - lpszString);
   }
   else
   {
      // skip white-space characters after equal-sign
      // and the equal-sign itself
      do {
         lpszEnd++;
      } while (::isspace((uchar) *lpszEnd));

      lpszBegin = lpszEnd;
      string strChar = string(*lpszEnd);

      if(strChar == "&")
      {
         if(string(lpszEnd, 6) == "&#039;")
         {
            strChar = "&#039;";
         }
      }

      // is attribute value wrapped in quotes?
      if(strChar == "\'" || strChar == "\"" || strChar == "&#039;")
      {
         lpszBegin += strChar.get_length();   // skip quote symbol
         do
         {
            lpszEnd++;
         }
         // Loop until we find the same quote character that
         // was used at the starting of the attribute value.
         // Anything within these quotes is considered valid!
         // NOTE that the entity references are resolved later.
         while (*lpszEnd != '\0' && !::str::begins_ci(lpszEnd, strChar));
      }

      // open attribute value i.e. not wrapped in quotes?
      else
      {
         strChar.Empty();
         do
         {
            lpszEnd++;
         }
         // loop until we find a tag ending delimeter or any
         // white-space character, or until we reach at the
         // end of the string buffer
         while (*lpszEnd != '\0' && !::isspace((uchar) *lpszEnd) &&
            *lpszEnd != '/' && *lpszEnd != '>');
      }

      m_strName = strAttrName;
      if (lpszEnd == lpszBegin)   // is_empty attribute value?
         m_strValue.Empty();
      else
         // use putValue() instead of direct assignment;
         // this will automatically normalize data before
         // assigning according to the specs and will
         // also resolve entity references!!!
         putValue(preader, string(lpszBegin,int32_t(lpszEnd - lpszBegin)));

      // calculate and return the ::count of characters successfully parsed
      return (lpszEnd - lpszString) + strChar.get_length();
   }

   return (0U);
}



/**
* LiteHTMLAttributes::parseFromStr
*
* @param lpszString - string to parse. It can contain pairs such as:
*
*          1. NAME
*          2. NAME=VALUE
*          3. NAME='VALUE'
*          4. NAME="VALUE"
*
*        NAME consist of letters, digits, underscores,
*        colons, hyphens, and periods
*
*        NOTE that white-spaces between NAME and equal-sign AND
*        equal-sign and VALUE is allowed.
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr LiteHTMLAttributes::parseFromStr(::lite_html_reader * preader, const char * lpszString, strsize iLen)
{

   CElemAttrArray      *pcoll = NULL;
   LiteHTMLElemAttr   oElemAttr;
   const uint_ptr         nStrLen = iLen;
   uint_ptr            nRetVal = 0U,
      nTemp = 0U;

   do
   {
      // try to parse an attribute/value
      // pair from the rest of the string
      if (!(nTemp = oElemAttr.parseFromStr(preader, &lpszString[nRetVal])))
      {
         if (!nRetVal)
            goto LError;
         break;
      }

      // collection has not been instantiated until now?
      if (pcoll == NULL)
      {
         // instantiate now
         if ((pcoll = new CElemAttrArray) == NULL)
            // out of primitive::memory?
         {
            //            TRACE0("(Error) LiteHTMLAttributes::parseFromStr: Out of primitive::memory.\n");
            goto LError;
         }
      }

      // add attribute/value pair to collection
      if (pcoll->add(new LiteHTMLElemAttr(oElemAttr)) < 0)
         goto LError;

      // advance seek pointer
      nRetVal += nTemp;
   }

   // do we still have something in the buffer to parse?
   while (nRetVal < nStrLen);

   // collection was never instantiated?
   if (pcoll == NULL)
      goto LError;
   // collection is is_empty?
   if (pcoll->get_upper_bound() == -1)
      goto LError;
   // current collection could not be emptied?
   if (!removeAll())
      goto LError;

   m_parrAttrib = pcoll;
   pcoll = NULL;
   goto LCleanExit;   // success!

LError:
   SAFE_DELETE_POINTER(pcoll);
   nRetVal = 0U;

LCleanExit:
   return (nRetVal);
}

LiteHTMLElemAttr* LiteHTMLAttributes::addAttribute(const char * lpszName, const char * lpszValue)
{

   ASSERT(__is_valid_string(lpszName));
   ASSERT(__is_valid_string(lpszValue));

   LiteHTMLElemAttr   *pItem = new LiteHTMLElemAttr(lpszName, lpszValue);
   if (pItem != NULL)
   {
      if (m_parrAttrib == NULL)
      {
         if ((m_parrAttrib = new CElemAttrArray) == NULL)
         {
            SAFE_DELETE_POINTER(pItem);
            //               TRACE0("(Error) LiteHTMLAttributes::addAttribute: Out of primitive::memory.\n");
            return (NULL);
         }
      }

      VERIFY(m_parrAttrib->add(pItem) >= 0);
   }
   return (pItem);
}


void LiteHTMLElemAttr::putValue(::lite_html_reader * preader, const char * lpszValue)
{

   ASSERT(__is_valid_string(lpszValue));

   m_strValue = lpszValue;

   // ignore leading white-spaces
   m_strValue.trim_left();

   // ignore trailing white-spaces
   m_strValue.trim_right();

   // ignore line feeds
   m_strValue.remove('\n');

   // replace tab and carriage-return with a single space
   m_strValue.replace('\r', ' ');

   m_strValue.replace('\t', ' ');

   /** resolve entity reference(s) */
   strsize iCurPos = -1, iParseLen = 0;

   string strChar;

   do
   {

      if ((iCurPos = m_strValue.find('&', ++iCurPos)) == -1)
         break;

      iParseLen = Sys(preader->m_pbaseapp).html()->resolve_entity(m_strValue.Mid(iCurPos), strChar);

      if (iParseLen)
      {

         m_strValue.replace(m_strValue.Mid(iCurPos, iParseLen), strChar);

      }

   }
   while (true);

}


bool LiteHTMLElemAttr::isNamedColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.get_length()) && (::isalpha(m_strValue[0])))
   {

      COLORREF crTemp = 0xffffffff;

      string      strKey(m_strValue);

      strKey.make_lower();

      if(Sys(preader->m_pbaseapp).html()->m_namedColors.Lookup(m_strValue, crTemp))
         return true;

   }

   return false;

}

bool LiteHTMLElemAttr::isSysColorValue(::lite_html_reader * preader) const
{

   if((m_strValue.get_length()) && (::isalpha(m_strValue[0])))
   {

      COLORREF   crTemp = 0xffffffff;

      string      strKey(m_strValue);

      strKey.make_lower();

      if(Sys(preader->m_pbaseapp).html()->m_namedColors.Lookup(strKey, crTemp))
         return (crTemp >= 0x80000000 && crTemp <= 0x80000018);

   }

   return false;

}

bool LiteHTMLElemAttr::isHexColorValue() const
{

   // zero-length attribute value?
   if (m_strValue.is_empty())
      return false;

   if (m_strValue[0] == '#')
   {

      if (m_strValue.get_length() > 1)
      {

         for (int32_t i = 1; i < m_strValue.get_length(); i++)
         {

            if (!::isdigit((uchar) m_strValue[i]))
               return false;

         }

         return true;

      }

   }

   return false;

}



COLORREF LiteHTMLElemAttr::getColorValue(::lite_html_reader * preader) const
{

   COLORREF crTemp = 0xffffffff;

   if(isNamedColorValue(preader))
   {

      string   strKey(m_strValue);

      strKey.make_lower();

      if(Sys(preader->m_pbaseapp).html()->m_namedColors.Lookup(strKey, crTemp))
      {

         // is this a system named color value?
         if (crTemp >= 0x80000000 && crTemp <= 0x80000018)
            crTemp = Sess(preader->m_pbaseapp).get_default_color(crTemp & 0x7FFFFFFF);
      }

   }
   else if (isHexColorValue())
   {

      crTemp = (uint32_t) ::strtoul(m_strValue.Mid(1), NULL, 16);

   }

   return crTemp;

}

string LiteHTMLElemAttr::getColorHexValue(::lite_html_reader * preader) const
{

   string   strColorHex;

   if(isHexColorValue())
   {

      strColorHex = m_strValue.Mid(1);

   }
   else
   {

      COLORREF crTemp = getColorValue(preader);

      if (crTemp != 0xffffffff)
         strColorHex.Format("#%06x", crTemp);

   }

   return strColorHex;

}

void LiteHTMLElemAttr::Init()
{
}



