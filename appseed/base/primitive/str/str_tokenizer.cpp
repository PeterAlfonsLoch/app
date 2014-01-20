#include "framework.h"


namespace str
{


   tokenizer::tokenizer()
   {
      Restart();
   }

   tokenizer::~tokenizer()
   {

   }

   tokenizer::tokenizer(const char * lpch, int32_t nLength) :
      string(lpch, nLength)
   {
      Restart();
   }

   tokenizer::tokenizer(const string & strSrc) :
      string(strSrc)
   {
      Restart();
   }



   bool tokenizer::GetNextToken(string &strToken, const char * lpSeparator, bool bWithSeparator)
   {

      strsize i;

      if((i = find(lpSeparator, m_nCurrentIndex)) >= 0)
      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex + strlen(lpSeparator));
         else
            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex);
         m_nCurrentIndex = i + strlen(lpSeparator);
         return TRUE;
      }
      else
      {
         if(m_nCurrentIndex <= get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length() + 1;
            return TRUE;
         }
         else
            return FALSE;
      }

   }

   bool tokenizer::GetNextSmallestToken(string & strToken, string_array & straSeparator, bool bWithSeparator)
   {
      if(m_nCurrentIndex >= get_length())
      {
         return FALSE;
      }
      strsize iMinPos = get_length();
      strsize iMaxSepLen = 0;
      strsize iPos;
      for(int32_t j = 0; j < straSeparator.get_size(); j++)
      {
         iPos = find(straSeparator[j], m_nCurrentIndex);
         if(iPos >= 0 && iPos <= iMinPos)
         {
            if(iMinPos == iPos)
            {
               if(straSeparator[j].get_length() > iMaxSepLen)
               {
                  iMaxSepLen = straSeparator[j].get_length();
               }
            }
            else
            {
               iMinPos = iPos;
               iMaxSepLen = straSeparator[j].get_length();
            }
         }
      }
      if(bWithSeparator)
         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex + iMaxSepLen);
      else
         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex);
      m_nCurrentIndex = iMinPos + iMaxSepLen;
      return TRUE;
   }

   bool tokenizer::GetNextTokenEx(string &strToken, const char * lpSeparator, bool bWithSeparator, bool bSkipAdjacent)
   {
      strsize i;
      string strMid = Mid(m_nCurrentIndex);
      if((i = strMid.FindOneOf(lpSeparator)) >= 0)
      {
         if(bWithSeparator)
            strToken = strMid.Left(i + 1);
         else
            strToken = strMid.Left(i);
         m_nCurrentIndex += i + 1;
         if(bSkipAdjacent)
         {
            strMid = strMid.Mid(i + 1);
            while(strMid.get_length() > 1)
            {
               if(strMid.FindOneOf(lpSeparator) == 0)
               {
                  m_nCurrentIndex++;
               }
               else
               {
                  break;
               }
               strMid = strMid.Mid(1);
            }
         }
         return true;
      }
      else
      {
         if(m_nCurrentIndex < get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length();
            return TRUE;
         }
         else
            return FALSE;
      }

   }

   void tokenizer::Restart()
   {
      m_nCurrentIndex = 0;
   }

   void tokenizer::Restart(string &strNew)
   {
      operator =(strNew);
      m_nCurrentIndex = 0;
   }

   bool tokenizer::ExtractFolderPath(const char * lpcszFilePath)
   {
      string strFilePath(lpcszFilePath);
      strsize i = strFilePath.get_length();
      bool b = false;
      while(i > 0)
      {
         i--;
         if(strFilePath[i] == '/' ||
            strFilePath[i] == '\\')
         {
            b = true;
            break;
         }
      }
      operator=(strFilePath.Left(i));
      return b;
   }

   bool tokenizer::_01Read(string &str)
   {
      if(!GetNextTokenEx(str, "\n\r\t ", false, true))
         return false;
      if(str.is_empty())
         if(!GetNextTokenEx(str, "\n\r\t ", false, true))
            return false;
      return true;
   }

   bool tokenizer::_01Read(UINT & user)
   {
      int32_t i;
      if(!_01Read(i))
         return false;
      user = (UINT) i;
      return true;
   }

   bool tokenizer::_01Read(int32_t &i)
   {
      string str;
      if(!_01Read(str))
         return false;
      i = atoi(str);
      return true;
   }

   bool tokenizer::_01ReadHex(UINT & user)
   {
      int32_t i;
      if(!_01ReadHex(i))
         return false;
      user = (UINT) i;
      return true;
   }

   bool tokenizer::_01ReadHex(int32_t &i)
   {
      string str;
      if(!_01Read(str))
         return false;
#ifdef WINDOWS
      sscanf_s(str, "%x", &i);
#else
      sscanf(str, "%x", &i);
#endif
      return true;
   }

   /*bool  tokenizer::_01Read(LPTSTR lpsz)
   {
   string str;
   if(!_01Read(str))
   return false;
   _tcscpy(lpsz, str);
   return true;
   }*/

   bool tokenizer::ReadLine(string &strToken,
      bool bWithSeparator)
   {
      strsize i1 = find("\r\n", m_nCurrentIndex);
      strsize i2 = find("\n", m_nCurrentIndex);
      if(i1 >= 0 && (i1 < i2 || i2 < 0))
      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex + 2);
         else
            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex);
         m_nCurrentIndex = i1 + 2;
         return TRUE;
      }
      else if(i2 >= 0)
      {
         if(bWithSeparator)
            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex + 2);
         else
            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex);
         m_nCurrentIndex = i2 + 2;
         return TRUE;
      }
      else
      {
         if(m_nCurrentIndex < get_length())
         {
            strToken = Mid(m_nCurrentIndex);
            m_nCurrentIndex = get_length();
            return TRUE;
         }
         else
            return FALSE;
      }
   }



} // namespace str




