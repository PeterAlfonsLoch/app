#include "framework.h"


lite_html_tag::lite_html_tag(lite_html_tag &rSource, bool bCopy)
   :m_pcollAttr(NULL)
{
   m_strTagName = rSource.m_strTagName;
   if (!bCopy)
   {
      m_pcollAttr = rSource.m_pcollAttr;
      rSource.m_pcollAttr = NULL;
   }
   else if (rSource.m_pcollAttr != NULL)
   {
      /** DEEP COPY BEGIN */
      try
      {
         m_pcollAttr = new LiteHTMLAttributes(*(rSource.m_pcollAttr), true);
      }
      catch(memory_exception * pe)
      {
         ::exception::rethrow(pe);
      }

      /** DEEP COPY END */
   }
}

lite_html_tag::~lite_html_tag()
{
   SAFE_DELETE_POINTER(m_pcollAttr);
}

/**
 * lite_html_tag::parseFromStr
 *
 * @param rStr - string to parse
 * @param bIsOpeningTag - receives true if the tag parsed
 *        is a opening tag, false otherwise.
 * @param bIsClosingTag - receives true if the tag parsed
 *        is a closing tag, false otherwise.
 * @param bParseAttrib - determines whether attribute/value
 *        pairs should be parsed. Default is true.
 *
 * @return number of characters successfully parsed
 * @since 1.0
 * @author Gurmeet S. Kochar
 */
UINT lite_html_tag::parseFromStr(::lite_html_reader * preader, const string & strString, strsize iPos,
                              bool &bIsOpeningTag,
                              bool &bIsClosingTag,
                              bool bParseAttrib /* = true */)
{


   bool            bClosingTag = false;
   bool            bOpeningTag = false;
   LiteHTMLAttributes   *pcollAttr = NULL;
   string            strTagName;
   UINT            nRetVal = 0U,
                  nTemp = 0U;
   const char *            lpszBegin = &strString[iPos];
   const char *            lpszEnd = NULL;

   // skip leading white-space characters
   while (::isspace(*lpszBegin))
      lpszBegin++;

   // HTML tags always begin with a less-than symbol
   if (*lpszBegin != '<')
      return (0U);

   // skip tag's opening delimeter '<'
   lpszBegin++;

   // optimization for is_empty opening tags
   if (*lpszBegin == '>')
   {
      ASSERT(strTagName.is_empty());
      ASSERT(pcollAttr == NULL);
      ASSERT(!bClosingTag);
      nRetVal = (UINT) (lpszBegin - &strString[iPos]);
      goto LUpdateAndExit;
   }

   // tag names always begin with an alphabet
   if (!::isalpha_dup(*lpszBegin))
   {
      bClosingTag = (*lpszBegin == '/');
      if (bClosingTag)
         lpszBegin++;
      else
         return (0U);
   }

   bOpeningTag = !bClosingTag;
   lpszEnd = lpszBegin;
   do
   {
      // tag name may contain letters (a-z, A-Z), digits (0-9),
      // underscores '_', hyphen '-', colons ':', and periods '.'
      if ((!(*lpszEnd >= 0 && ::isalnum(*lpszEnd))) &&
          (*lpszEnd != '-') && (*lpszEnd != ':') &&
          (*lpszEnd != '_') && (*lpszEnd != '.') )
      {

         if(lpszEnd == lpszBegin)
            return 0;

         // only white-space characters, a NULL-character, a
         // greater-than symbol, or a forward-slash can break
         // a tag name
         if (*lpszEnd == '\0' || ::isspace(*lpszEnd) ||
            *lpszEnd == '>' ||
            (*lpszEnd == '/' && (!bClosingTag)) )
         {
            break;
         }

         return (0U);   // any other character will fail parsing process
      }

      lpszEnd++;
   }
   while(true);

   // store tag name for later use
   strTagName = string(lpszBegin, lpszEnd - lpszBegin);

   // is this a closing tag?
   if (bClosingTag)
   {
      // in a closing tag, there can be only one symbol after
      // tag name, i.e., the tag end delimeter '>'. Anything
      // else will result in parsing failure
      if (*lpszEnd != '>')
         return (0U);

      // skip tag's ending delimeter
      lpszEnd++;

      ASSERT(strTagName.get_length());
      ASSERT(pcollAttr == NULL);
      nRetVal = (UINT) (lpszEnd - &strString[iPos]);
      goto LUpdateAndExit;
   }

   while (::isspace(*lpszEnd))
      lpszEnd++;

   // tag contains attribute/value pairs?
   if (*lpszEnd != '>')
   {
      lpszBegin = lpszEnd;
      lpszEnd = NULL;

      // skip white-space characters after tag name

      nTemp = 0U;
      if (bParseAttrib)   // parse attribute/value pairs?
      {
         ASSERT(pcollAttr == NULL);
         // instantiate collection ...
         if ((pcollAttr = new LiteHTMLAttributes) == NULL)
         {
//            TRACE0("(Error) lite_html_tag::parseFromStr: Out of primitive::memory.\n");
            throw memory_exception(get_thread_app());
            return (0U);
         }

         // ... and delegate parsing process
         nTemp = (UINT) pcollAttr->parseFromStr(preader, lpszBegin, strString.get_length() - (lpszBegin - (const char *) strString));
      }

      if (nTemp == 0)   // attribute/value pair parsing is disabled?
                  //   - OR -
                  // attribute/value pairs could not be parsed?
      {
         SAFE_DELETE_POINTER(pcollAttr);
         if ((lpszEnd = ::strstr(lpszBegin, "/>")) == NULL)
         {
            if ((lpszEnd = ::strchr(lpszBegin, '>')) == NULL)
               return (0U);
         }
      }
      else
      {
         lpszEnd = lpszBegin + nTemp;

         // skip white-space after attribute/value pairs
         while (::isspace((uchar) *lpszEnd))
            lpszEnd++;

         // tag's ending delimeter could not be found?
         if (*lpszEnd == '\0')
         {
            SAFE_DELETE_POINTER(pcollAttr);
            return (0U);
         }
      }

      // a tag like this one: <BR/>
      if (*lpszEnd == '/')
      {
         ASSERT(bOpeningTag);
         bClosingTag = true;
         lpszEnd++;
      }
   }

   // HTML tags always end with a greater-than '>' symbol
   if (*lpszEnd != '>')
   {
      SAFE_DELETE_POINTER(pcollAttr);
      return (0U);
   }
   else
      lpszEnd++;

   nRetVal = (UINT) (lpszEnd - &strString[iPos]);
   goto LUpdateAndExit;   // just to show the flow-of-control

LUpdateAndExit:
   m_strTagName = strTagName;
   if(strTagName.CompareNoCase("BR") == 0)
   {
      bIsClosingTag = true;
      bIsOpeningTag = true;
   }
   else
   {
      bIsClosingTag = bClosingTag;
      bIsOpeningTag = bOpeningTag;
   }
   m_strTagName.trim_left();   m_strTagName.trim_right();   // just-in-case!
   SAFE_DELETE_POINTER(m_pcollAttr);
   m_pcollAttr = pcollAttr;
   pcollAttr = NULL;

   return (nRetVal);
}

