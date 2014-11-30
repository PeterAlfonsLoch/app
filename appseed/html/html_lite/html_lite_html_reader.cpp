/**
*   PROJECT - HTML Reader Class Library
*
*   lite_html_reader.cpp - lite_html_reader implementation
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
#if defined(LINUX) || defined(APPLEOS)
#include <sys/mman.h>
#include <unistd.h>
#endif

uint_ptr lite_html_reader::parseDocument()
{
   bool   bAbort = false;         // continue parsing or abort?
   bool   bIsClosingTag = false;   // tag parsed is a closing tag?
   bool   bIsOpeningTag = false;   // tag parsed is an opening tag?
   string   strCharacters;         // character data
   string   strComment;            // comment data
   string   strT;               // temporary storage
   uint_ptr   dwCharDataStart = 0L;   // starting position of character data
   uint_ptr   dwCharDataLen = 0L;      // length of character data
   LONG   lTemp = 0L;            // temporary storage
   char   ch = 0;               // character at current buffer position
   lite_html_tag   oTag;         // tag information

   if(m_strBuffer.is_empty())
      return 0U;

   // reset seek pointer to beginning
   ResetSeekPointer();

   // notify event handler about parsing startup
   if (getEventNotify(notifyStartStop))
   {
      bAbort = false;
      m_pEventHandler->BeginParse(m_dwAppData, bAbort);
      if (bAbort)   goto LEndParse;
   }

   // skip leading white-space characters
   while (isWhiteSpace(ReadChar()))
      ;

   ch = UngetChar();
   while ((ch = ReadChar()) != '\0')
   {
      switch (ch)
      {

         // tag starting delimeter?
      case '<':
         {
            UngetChar();

            strComment.Empty();
            if (!parseComment(strComment))
            {
               bIsOpeningTag = false;
               bIsClosingTag = false;
               if (!parseTag(oTag, bIsOpeningTag, bIsClosingTag))
               {
                  ++dwCharDataLen;

                  // manually advance buffer position
                  // because the last call to UngetChar()
                  // moved it back one character
                  ch = ReadChar();

                  break;
               }
            }

            // clear pending notifications
            if ( (dwCharDataLen) || (strCharacters.get_length()) )
            {
               strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen);
               NormalizeCharacters(strCharacters);

               if ( (strCharacters.get_length()) &&
                  (getEventNotify(notifyCharacters)) )
               {
                  bAbort = false;
                  m_pEventHandler->Characters(strCharacters, m_dwAppData, bAbort);
                  if (bAbort)   goto LEndParse;
               }

               strCharacters.Empty();
            }

            dwCharDataLen = 0L;
            dwCharDataStart = m_dwBufPos;

            if (strComment.get_length())
            {
               if (getEventNotify(notifyComment))
               {
                  bAbort = false;
                  m_pEventHandler->Comment(strComment, m_dwAppData, bAbort);
                  if (bAbort)   goto LEndParse;
               }
            }
            else
            {
               if ( (bIsOpeningTag) && (getEventNotify(notifyTagStart)) )
               {
                  bAbort = false;
                  m_pEventHandler->StartTag(&oTag, m_dwAppData, bAbort);
                  if (bAbort)   goto LEndParse;
               }

               if ( (bIsClosingTag) && (getEventNotify(notifyTagEnd)) )
               {
                  bAbort = false;
                  m_pEventHandler->EndTag(&oTag, m_dwAppData, bAbort);
                  if (bAbort)   goto LEndParse;
               }
            }

            break;
         }

         // entity reference beginning delimeter?
      case '&':
         {
            UngetChar();

            lTemp = 0;
            string strChar;
            if (m_bResolveEntities)
               lTemp = System.html()->resolve_entity(&m_strBuffer[m_dwBufPos], strChar);

            if (lTemp)
            {
               strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen) + strChar;
               m_dwBufPos += lTemp;
               dwCharDataStart = m_dwBufPos;
               dwCharDataLen = 0L;
            }
            else
            {
               ch = ReadChar();
               ++dwCharDataLen;
            }

            break;
         }

         // any other character
      default:
         {
            ++dwCharDataLen;
            break;
         }
      }
   }

   // clear pending notifications
   if ( (dwCharDataLen) || (strCharacters.get_length()) )
   {
      strCharacters += string(&m_strBuffer[dwCharDataStart], dwCharDataLen) + ch;
      NormalizeCharacters(strCharacters);
      strCharacters.trim_right();   // explicit trailing white-space removal

      if ( (strCharacters.get_length()) &&
         (getEventNotify(notifyCharacters)) )
      {
         bAbort = false;
         m_pEventHandler->Characters(strCharacters, m_dwAppData, bAbort);
         if (bAbort)   goto LEndParse;
      }
   }

LEndParse:
   // notify event handler about parsing completion
   if (getEventNotify(notifyStartStop))
      m_pEventHandler->EndParse(m_dwAppData, bAbort);

   m_strBuffer.Empty();
   return (m_dwBufPos);
}

/**
* lite_html_reader::read
* The read method parses an HTML document from an
* in-primitive::memory string buffer and raises events defined
* in ILiteHTMLReaderEvents to notify about variours
* elements.
*
* @param lpszString - string containing HTML text to parse
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr lite_html_reader::read(const string & str)
{

   m_strBuffer    = str;

   return parseDocument();

}

#ifdef WINDOWSEX
/**
* lite_html_reader::read
* This method is similar to the read(const char *) method,
* except that, it accepts a file HANDLE instead of
* an in-primitive::memory string buffer containing HTML text.
*
* @param hFile - file handle
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr lite_html_reader::ReadFile(HANDLE hFile)
{
   ASSERT(hFile != INVALID_HANDLE_VALUE);
   ASSERT(::GetFileType(hFile) == FILE_TYPE_DISK);

   HANDLE   hFileMap = NULL;
   const char *   lpsz = NULL;
   uint_ptr   nRetVal = -1;

   // determine file size
   strsize dwBufLen = ::GetFileSize(hFile, NULL);
   if (dwBufLen == INVALID_FILE_SIZE)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " GetFileSize() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

#ifdef WINDOWSEX
   // create a file-mapping object for the file
   hFileMap = ::CreateFileMapping(hFile, NULL, PAGE_READONLY, 0L, 0L, NULL);
#else
   hFileMap = ::CreateFileMappingFromApp(hFile, NULL, PAGE_READONLY, dwBufLen, NULL);
#endif
   if (hFileMap == NULL)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " CreateFileMapping() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

#ifdef WINDOWSEX
   // map the entire file into the address-space of the application
   lpsz = (const char *)::MapViewOfFile(hFileMap, FILE_MAP_READ, 0L, 0L, 0L);
#else
   lpsz = (const char *) ::MapViewOfFileFromApp(hFileMap, FILE_MAP_READ, 0, 0);
#endif
   if (lpsz == NULL)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " MapViewOfFile() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

   m_strBuffer = string(lpsz, dwBufLen);
   nRetVal = parseDocument();
   goto LCleanExit;

LError:
   nRetVal = 0U;

LCleanExit:
   if (lpsz != NULL)
      VERIFY(::UnmapViewOfFile(lpsz));
   if (hFileMap)
      VERIFY(::CloseHandle(hFileMap));
   return (nRetVal);
}


#elif defined(METROWIN)
/**
* lite_html_reader::read
* This method is similar to the read(const char *) method,
* except that, it accepts a file HANDLE instead of
* an in-primitive::memory string buffer containing HTML text.
*
* @param hFile - file handle
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr lite_html_reader::ReadFile(HANDLE hFile)
{
   ASSERT(hFile != INVALID_HANDLE_VALUE);
   //ASSERT(::GetFileType(hFile) == FILE_TYPE_DISK);

   HANDLE         hFileMap    = NULL;
   const char *   lpsz        = NULL;
   uint_ptr      nRetVal     = 0;

   // determine file size
   strsize dwBufLen = ::GetFileSize(hFile, NULL);
   if (dwBufLen == INVALID_FILE_SIZE)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " GetFileSize() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

   // create a file-mapping object for the file
#ifdef METROWIN
         hFileMap = CreateFileMappingFromApp(
            hFile,
            NULL,
            PAGE_READWRITE,
            dwBufLen,
            NULL);

#else
   hFileMap = ::CreateFileMapping(hFile, NULL, PAGE_READONLY, 0L, 0L, NULL);
#endif
   if (hFileMap == NULL)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " CreateFileMapping() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

#ifdef METROWIN
      lpsz = (const char *) MapViewOfFileFromApp(
         hFileMap,
         FILE_MAP_READ | FILE_MAP_WRITE,
         0,
         0);
#else
   // map the entire file into the address-space of the application
   lpsz = (const char *)::MapViewOfFile(hFileMap, FILE_MAP_READ, 0L, 0L, 0L);
#endif
   if (lpsz == NULL)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " MapViewOfFile() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto LError;
   }

   m_strBuffer = string(lpsz, dwBufLen);
   nRetVal = parseDocument();
   goto LCleanExit;

LError:
   nRetVal = 0U;

LCleanExit:
   if (lpsz != NULL)
      VERIFY(::UnmapViewOfFile(lpsz));
   if (hFileMap)
      VERIFY(::CloseHandle(hFileMap));
   return (nRetVal);
}


#else

/**
* lite_html_reader::read
* This method is similar to the read(const char *) method,
* except that, it accepts a file HANDLE instead of
* an in-primitive::memory string buffer containing HTML text.
*
* @param fd - file descriptor
*
* @return number of TCHARs successfully parsed
* @since 1.0
* @author Gurmeet S. Kochar
*/
uint_ptr lite_html_reader::ReadFile(int32_t fd)
{
//   ASSERT(hFile != INVALID_HANDLE_VALUE);
//   ASSERT(::GetFileType(hFile) == FILE_TYPE_DISK);

   char *   lpsz;
   uint_ptr   nRetVal;

   strsize dwBufLen;

   try
   {

      // determine file size
      dwBufLen = ::get_file_size(fd);
      if (dwBufLen == INVALID_FILE_SIZE)
      {
         TRACE1("(Error) lite_html_reader::read: GetFileSize() failed; GetLastError() returns 0x%08x.\n", ::GetLastError());
         return 0;
      }

   }
   catch(...)
   {
      return 0;
   }

   lpsz = (char *) mmap(NULL, dwBufLen, PROT_READ, MAP_PRIVATE, fd, 0);

   if(lpsz == MAP_FAILED)
   {
      TRACE1("(Error) lite_html_reader::read:"
         " CreateFileMapping() failed;"
         " GetLastError() returns 0x%08x.\n", ::GetLastError());
      goto map_error;
   }

   m_strBuffer = string(lpsz, dwBufLen);

   try
   {
      nRetVal = parseDocument();
   }
   catch(...)
   {
      nRetVal = 0;
   }

   munmap((void *) lpsz, dwBufLen);

   return nRetVal;

map_error:

   lpsz = m_strBuffer.GetBufferSetLength(dwBufLen);

   int64_t iRead;

   strsize iPos = 0;

   while(iPos < dwBufLen && (iRead = ::read(fd, &lpsz[iPos], dwBufLen - iPos)) > 0)
   {

      iPos += iRead;

   }

   if(iPos < dwBufLen)
      return 0;


   try
   {
      nRetVal = parseDocument();
   }
   catch(...)
   {
      nRetVal = 0;
   }

   return nRetVal;

}

#endif

char lite_html_reader::UngetChar()
{
   if(m_strBuffer.is_empty())
      return '\0';
   return m_strBuffer[--m_dwBufPos];
}


bool lite_html_reader::getEventNotify(uint32_t dwEvent) const
{
   ASSERT(dwEvent == notifyStartStop  ||
      dwEvent == notifyTagStart   ||
      dwEvent == notifyTagEnd     ||
      dwEvent == notifyCharacters ||
      dwEvent == notifyComment);
   if (m_pEventHandler == NULL)
      return (false);
   return ((m_eventMask & dwEvent) == dwEvent);
}

bool lite_html_reader::isWhiteSpace(char ch) const
{
   return ::isspace(static_cast < unsigned char > (ch)) ? true : false;
}


/**
* Parses an HTML tag starting from the current buffer position.
*
* @param rTag - this will receive tag information (along with its attributes)
* @param bIsOpeningTag - receives true if the tag parsed is a opening tag.
* @param bIsClosingTag - receives true if the tag parsed is a closing tag.
*
* @return true if successful, false otherwise
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::parseTag(lite_html_tag &rTag, bool &bIsOpeningTag, bool &bIsClosingTag)
{

   UINT nRetVal = rTag.parseFromStr(this, m_strBuffer, m_dwBufPos, bIsOpeningTag, bIsClosingTag);

   if(!nRetVal)
      return false;

   m_dwBufPos += nRetVal;

   return true;

}


/**
* Returns the current value for the specified option.
*
* @param option - option to inquire
* @param bCurVal - this will receive the current value for the option.
*
* @return true if value was retrieved successfully; otherwise false.
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const
{
   bool bSuccess = false;

   switch (option)
   {
   case resolveEntities:
      {
         bCurVal = m_bResolveEntities;
         bSuccess = true;
         break;
      }
   default:
      {
         bSuccess = false;
         break;
      }
   }
   return (bSuccess);
}

/**
* Changes the value of an option and returns
* true/false indicating if the specified option
* was set successfully.
*
* @param option - option to change
*                 (one of the ReaderOptionsEnum constants)
* @param bNewVal - value to set
*
* @return true if option was set successfully; otherwise false.
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::setBoolOption(ReaderOptionsEnum option, bool bNewVal)
{
   bool bSuccess = false;

   switch (option)
   {
   case resolveEntities:
      {
         m_bResolveEntities = bNewVal;
         bSuccess = true;
         break;
      }
   default:
      {
         bSuccess = false;
         break;
      }
   }
   return (bSuccess);
}

/**
* Parses an HTML comment starting from the current buffer position.
*
* @param rComment - this will receive the comment (without delimeters)
*
* @return true if successful, false otherwise
* @since 1.0
* @author Gurmeet S. Kochar
*/
bool lite_html_reader::parseComment(string &rComment)
{

   // HTML comments begin with '<!' delimeter and
   // are immediately followed by two hyphens '--'
   if (::strncmp(&m_strBuffer[m_dwBufPos], "<!--", 4))
      return (false);

   const char *   lpszBegin = &m_strBuffer[m_dwBufPos + 4];
   // HTML comments end with two hyphen symbols '--'
   const char *   lpszEnd = ::strstr(lpszBegin, "--");

   // comment ending delimeter could not be found?
   if (lpszEnd == NULL)
      // consider everything after current buffer position a comment
   {
      rComment = lpszBegin;
      m_dwBufPos += (4 + rComment.get_length());
      return (true);
   }

   string   strComment(lpszBegin, int32_t(lpszEnd - lpszBegin));

   // end of buffer?
   if (lpszEnd + (sizeof(char) * 2) >= &m_strBuffer[0] + m_strBuffer.size())
      return (false);

   // skip white-space characters after comment ending delimeter '--'
   lpszEnd += (sizeof(char) * 2);
   while (::isspace(*lpszEnd))
      lpszEnd++;

   // comment has not been terminated properly
   if (*lpszEnd != '>')
      return (false);

   lpszEnd++;
   m_dwBufPos += (lpszEnd - &m_strBuffer[m_dwBufPos]);
   rComment = strComment;
   return (true);
}

