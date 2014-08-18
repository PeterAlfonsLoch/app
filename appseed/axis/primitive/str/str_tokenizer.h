#pragma once


namespace str
{

   class CLASS_DECL_AXIS tokenizer : public string 
   {
   protected:


      strsize      m_nCurrentIndex;


   public:


      tokenizer(const string & strSrc);
      tokenizer(const char * lpch, int32_t nLength );
      tokenizer();
      virtual ~tokenizer();


      bool ReadLine(string & str,
         bool bWithSeparator = false);
      // _01Read read a token if find one of \n\r\t or space
      bool _01Read(int32_t & i);
      bool _01Read(UINT & user);
      bool _01ReadHex(int32_t & i);
      bool _01ReadHex(UINT & user);
      //bool _01Read(LPTSTR lpsz);
      bool _01Read(string & str);
      bool ExtractFolderPath(const char * lpcszFilePath);
      void Restart();
      void Restart(string &strNew);
      bool GetNextToken(string &strToken, const char * lpSeparator, bool bWithSeparator = FALSE);
      bool GetNextSmallestToken(string &strToken, string_array & straSeparator, bool bWithSeparator = FALSE);
      // Any of separator character
      bool GetNextTokenEx(string &strToken, const char * lpSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

   };



} // namespace string



