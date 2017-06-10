//#include "framework.h"


namespace str
{


   tokenizer::tokenizer()
   {
      
      reset();

   }

   tokenizer::~tokenizer()
   {

   }

   tokenizer::tokenizer(const char * lpch, int32_t nLength) :
      string(lpch, nLength)
   {
      
      reset();

   }

   tokenizer::tokenizer(const char * pszSrc) :
      string(pszSrc)
   {

      reset();

   }
   tokenizer::tokenizer(const string & strSrc) :
      string(strSrc)
   {
      
      reset();

   }
   tokenizer::tokenizer(const var & var) :
      string(var)
   {

      reset();

   }   
   
   tokenizer::tokenizer(const property & property) :
      string(property)
   {

      reset();

   }


   bool tokenizer::next_token(string &strToken, const char * lpSeparator, bool bWithSeparator)
   {

      strsize i;

      if((i = find(lpSeparator, m_nCurrentIndex)) >= 0)
      {
         
         if (bWithSeparator)
         {

            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex + strlen(lpSeparator));

         }
         else
         {

            strToken = Mid(m_nCurrentIndex, i - m_nCurrentIndex);
         
         }

         m_nCurrentIndex = i + strlen(lpSeparator);

         return true;

      }
      else
      {

         if(m_nCurrentIndex <= get_length())
         {
            
            strToken = Mid(m_nCurrentIndex);
            
            m_nCurrentIndex = get_length() + 1;
            
            return true;

         }
         else
         {

            return false;

         }

      }

   }


   bool tokenizer::next_token_ex(string &strToken, const char * lpSeparator, bool bWithSeparator, bool bSkipAdjacent)
   {
      
      strsize i;

      string strMid = Mid(m_nCurrentIndex);

      if((i = strMid.FindOneOf(lpSeparator)) >= 0)
      {
      
         if (bWithSeparator)
         {

            strToken = strMid.Left(i + 1);

         }
         else
         {

            strToken = strMid.Left(i);

         }

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

            return true;

         }
         else
         {

            return false;

         }

      }

   }

  
   void tokenizer::reset()
   {

      m_nCurrentIndex = 0;

   }


   void tokenizer::initialize(string &strNew)
   {
      
      operator =(strNew);

      m_nCurrentIndex = 0;

   }

   bool tokenizer::extract_folder_path(const char * lpcszFilePath)
   {

      string strFilePath(lpcszFilePath);

      strsize i = strFilePath.get_length();

      bool b = false;

      while(i > 0)
      {

         i--;

         if(strFilePath[i] == '/' || strFilePath[i] == '\\')
         {

            b = true;

            break;

         }

      }

      operator=(strFilePath.Left(i));

      return b;

   }


   bool tokenizer::read(string &str)
   {
      
      if (!next_token_ex(str, "\n\r\t ", false, true))
      {

         return false;

      }

      if (str.is_empty())
      {

         if (!next_token_ex(str, "\n\r\t ", false, true))
         {

            return false;

         }

      }

      return true;

   }


   bool tokenizer::read(UINT & user)
   {

      int32_t i;

      if (!read(i))
      {

         return false;

      }

      user = (UINT) i;

      return true;

   }


   bool tokenizer::read(int32_t &i)
   {
      
      string str;

      if (!read(str))
      {

         return false;

      }

      i = atoi(str);

      return true;

   }


   bool tokenizer::read_hex(UINT & user)
   {

      int32_t i;

      if (!read_hex(i))
      {

         return false;

      }

      user = (UINT) i;

      return true;

   }

   bool tokenizer::read_hex(int32_t &i)
   {

      string str;

      if (!read(str))
      {

         return false;

      }

      i = hex::to_int64(str);

      return true;

   }


   bool tokenizer::read_line(string &strToken, bool bWithSeparator)
   {

      strsize i1 = find("\r\n", m_nCurrentIndex);

      strsize i2 = find("\n", m_nCurrentIndex);

      if(i1 >= 0 && (i1 < i2 || i2 < 0))
      {

         if (bWithSeparator)
         {

            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex + 2);

         }
         else
         {

            strToken = Mid(m_nCurrentIndex, i1 - m_nCurrentIndex);

         }

         m_nCurrentIndex = i1 + 2;

         return true;

      }
      else if(i2 >= 0)
      {

         if (bWithSeparator)
         {

            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex + 2);

         }
         else
         {

            strToken = Mid(m_nCurrentIndex, i2 - m_nCurrentIndex);

         }

         m_nCurrentIndex = i2 + 2;

         return TRUE;

      }
      else
      {

         if(m_nCurrentIndex < get_length())
         {

            strToken = Mid(m_nCurrentIndex);

            m_nCurrentIndex = get_length();

            return true;

         }
         else
         {

            return FALSE;

         }

      }

   }


} // namespace str




