#pragma once


namespace str
{


   class CLASS_DECL_AURA tokenizer : public string 
   {
   public:


      strsize      m_nCurrentIndex;

      tokenizer(const string & strSrc);
      tokenizer(const char * lpch, int32_t nLength );
      tokenizer();
      ~tokenizer();


      bool read_line(string & str, bool bWithSeparator = false);
      bool read(int32_t & i);
      bool read(UINT & user);
      bool read_hex(int32_t & i);
      bool read_hex(UINT & user);
      bool read(string & str);
      bool extract_folder_path(const char * lpcszFilePath);
      void reset();
      void initialize(string &strNew);
      
      bool next_token(string &strToken, const char * lpSeparator, bool bWithSeparator = FALSE);

      template < typename ITERABLE >
      bool next_shortest_token(string &strToken, const ITERABLE & iterableSeparator, bool bWithSeparator = FALSE);
      
      bool next_token_ex(string &strToken, const char * lpSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

   };


   template < typename ITERABLE >
   inline bool tokenizer::next_shortest_token(string & strToken, const ITERABLE & straSeparator, bool bWithSeparator)
   {

      if (m_nCurrentIndex >= get_length())
      {

         return false;

      }

      strsize iMinPos = get_length();

      strsize iMaxSepLen = 0;

      strsize iPos;

      for (int32_t j = 0; j < straSeparator.get_size(); j++)
      {

         iPos = find(straSeparator[j], m_nCurrentIndex);

         if (iPos >= 0 && iPos <= iMinPos)
         {

            if (iMinPos == iPos)
            {

               if (straSeparator[j].get_length() > iMaxSepLen)
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

      if (bWithSeparator)
      {

         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex + iMaxSepLen);

      }
      else
      {

         strToken = Mid(m_nCurrentIndex, iMinPos - m_nCurrentIndex);

      }

      m_nCurrentIndex = iMinPos + iMaxSepLen;

      return true;

   }


} // namespace str




