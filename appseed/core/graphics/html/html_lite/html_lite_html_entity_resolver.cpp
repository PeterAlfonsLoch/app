/**
 *   PROJECT - HTML Reader Class Library
 *
 *   LiteHTMLEntityResolver.cpp
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

LiteHTMLEntityResolver::CharEntityRefs::CharEntityRefs(sp(::axis::application) papp) :
   string_map < char, char >(papp, 55)
{
   /** C0 Controls and Basic Latin */
   (*this)["quot"]      = '\x22';
   (*this)["amp"]      = '\x26';
   (*this)["apos"]      = '\x27';
   (*this)["lt"]      = '\x3C';
   (*this)["gt"]      = '\x3E';
   /** ISO 8859-1 (Latin-1) characters */
   (*this)["nbsp"]      = '\xA0';
   (*this)["iexcl"]   = '\xA1';
   (*this)["cent"]      = '\xA2';
   (*this)["pound"]   = '\xA3';
   (*this)["current"]   = '\xA4';
   (*this)["yen"]      = '\xA5';
   (*this)["brvbar"]   = '\xA6';
   (*this)["sect"]      = '\xA7';
   (*this)["uml"]      = '\xA8';
   (*this)["copy"]      = '\xA9';
   (*this)["ordf"]      = '\xAA';
   (*this)["laquo"]   = '\xAB';
   (*this)["not"]      = '\xAC';
   (*this)["shy"]      = '\xAD';
   (*this)["reg"]      = '\xAE';
   (*this)["macr"]      = '\xAF';
   (*this)["deg"]      = '\xB0';
   (*this)["plusmn"]   = '\xB1';
   (*this)["sup2"]      = '\xB2';
   (*this)["sup3"]      = '\xB3';
   (*this)["acute"]   = '\xB4';
   (*this)["micro"]   = '\xB5';
   (*this)["para"]      = '\xB6';
   (*this)["middot"]   = '\xB7';
   (*this)["cedil"]   = '\xB8';
   (*this)["sup1"]      = '\xB9';
   (*this)["ordm"]      = '\xBA';
   (*this)["raquo"]   = '\xBB';
   (*this)["frac14"]   = '\xBC';
   (*this)["frac12"]   = '\xBD';
   (*this)["frac34"]   = '\xBE';
   (*this)["iquest"]   = '\xBF';
   (*this)["Agrave"]   = '\xC0';
   (*this)["Aacute"]   = '\xC1';
   (*this)["Acirc"]   = '\xC2';
   (*this)["Atilde"]   = '\xC3';
   (*this)["Auml"]      = '\xC4';
   (*this)["Aring"]   = '\xC5';
   (*this)["AElig"]   = '\xC6';
   (*this)["Ccedil"]   = '\xC7';
   (*this)["Egrave"]   = '\xC8';
   (*this)["Eacute"]   = '\xC9';
   (*this)["Ecirc"]   = '\xCA';
   (*this)["Euml"]      = '\xCB';
   (*this)["Igrave"]   = '\xCC';
   (*this)["Iacute"]   = '\xCD';
   (*this)["Icirc"]   = '\xCE';
   (*this)["Iuml"]      = '\xCF';
   (*this)["ETH"]      = '\xD0';
   (*this)["Ntilde"]   = '\xD1';
   (*this)["Ograve"]   = '\xD2';
   (*this)["Oacute"]   = '\xD3';
   (*this)["Ocirc"]   = '\xD4';
   (*this)["Otilde"]   = '\xD5';
   (*this)["Ouml"]      = '\xD6';
   (*this)["times"]   = '\xD7';
   (*this)["Oslash"]   = '\xD8';
   (*this)["Ugrave"]   = '\xD9';
   (*this)["Uacute"]   = '\xDA';
   (*this)["Ucirc"]   = '\xDB';
   (*this)["Uuml"]      = '\xDC';
   (*this)["Yacute"]   = '\xDD';
   (*this)["THORN"]   = '\xDE';
   (*this)["szlig"]   = '\xDF';
   (*this)["agrave"]   = '\xE0';
   (*this)["aacute"]   = '\xE1';
   (*this)["acirc"]   = '\xE2';
   (*this)["atilde"]   = '\xE3';
   (*this)["auml"]      = '\xE4';
   (*this)["aring"]   = '\xE5';
   (*this)["aelig"]   = '\xE6';
   (*this)["ccedil"]   = '\xE7';
   (*this)["egrave"]   = '\xE8';
   (*this)["eacute"]   = '\xE9';
   (*this)["ecirc"]   = '\xEA';
   (*this)["euml"]      = '\xEB';
   (*this)["igrave"]   = '\xEC';
   (*this)["iacute"]   = '\xED';
   (*this)["icirc"]   = '\xEE';
   (*this)["iuml"]      = '\xEF';
   (*this)["eth"]      = '\xF0';
   (*this)["ntilde"]   = '\xF1';
   (*this)["ograve"]   = '\xF2';
   (*this)["oacute"]   = '\xF3';
   (*this)["ocirc"]   = '\xF4';
   (*this)["otilde"]   = '\xF5';
   (*this)["ouml"]      = '\xF6';
   (*this)["divide"]   = '\xF7';
   (*this)["oslash"]   = '\xF8';
   (*this)["ugrave"]   = '\xF9';
   (*this)["uacute"]   = '\xFA';
   (*this)["ucirc"]   = '\xFB';
   (*this)["uuml"]      = '\xFC';
   (*this)["yacute"]   = '\xFD';
   (*this)["thorn"]   = '\xFE';
   (*this)["yuml"]      = '\xFF';
}


int32_t LiteHTMLEntityResolver::resolveEntity(const char * lpszEntity, string & strChar)
{
   if (m_CharEntityRefs.get_count() <= 0)
      return 0;

   ASSERT(m_CharEntityRefs.get_count());
   ASSERT(__is_valid_string(lpszEntity));

   const char * lpszBegin = lpszEntity;
   const char * lpszEnd = ::strchr(lpszEntity, ';');
   char   chTemp = 0;

   // entity references always end with a semi-colon ';'
   if (lpszEnd == NULL)
      return (0);

   // skip leading white-space characters
   while (::isspace(*lpszBegin))
      lpszBegin++;

   // remaining string (including semi-colon)
   // must be at least 4 characters in length
   if (lpszEnd - lpszBegin < 3)
      return (0U);

   // entity references always begin with an ampersand '&' symbol
   if (*lpszBegin != '&')
      return (0U);
   lpszBegin++;

   // numeric (decimal or hexadecimal) entity reference?
   if (*lpszBegin == '#')
   {
      lpszBegin++;
      chTemp = *lpszBegin;
      int32_t   core = (::isdigit(chTemp) ? 10 :
               (chTemp == 'x' ||
                  chTemp == 'X' ? 16 : 0));
      if (core)
      {
         if (core == 16)
            lpszBegin++;

         uint32_t  ulNum = (uint32_t) ::strtoul(lpszBegin, NULL, core);
         strChar = ::str::uni_to_utf8(ulNum);
         return (int32_t) (lpszEnd - lpszEntity + 1);
      }
   }

   // character entity reference?
   else
   {
      string   strKey(lpszBegin, (int32_t)(lpszEnd - lpszBegin));

      // because some character entity references are
      // case-sensitive, we must fix them manually
      if (!strKey.CompareNoCase("eth") ||
         !strKey.CompareNoCase("thorn"))
      {
         if (::isupper(strKey[0]))
            strKey.make_upper();
         else
            strKey.make_lower();
      }
      else if (!strKey.CompareNoCase("Oslash"))
      {
         strKey.make_lower();
         strKey.set_at(0, 'O');
      }
      else if (!strKey.CompareNoCase("AElig"))
      {
         strKey.make_lower();
         strKey.set_at(0, 'A');
         strKey.set_at(1, 'E');
      }
      else
      {
         string   strT = strKey.Mid(1);
         strKey.make_lower();
         if (strT.CompareNoCase("grave") == 0 ||
            strT.CompareNoCase("acute") == 0 ||
            strT.CompareNoCase("circ")  == 0 ||
            strT.CompareNoCase("uml")   == 0 ||
            strT.CompareNoCase("tilde") == 0 ||
            strT.CompareNoCase("cedil") == 0 ||
            strT.CompareNoCase("ring")  == 0)
         {
            strKey.set_at(0, strT[0]);
         }
      }

      // is this a known entity reference?
      if (m_CharEntityRefs.Lookup(strKey, chTemp))
      {
         strChar = chTemp;
         return (int32_t) (lpszEnd - lpszEntity + 1);
      }
   }

   return (0U);
}
