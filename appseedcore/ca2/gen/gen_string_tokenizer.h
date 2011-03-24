#pragma once

class CLASS_DECL_ca string_tokenizer : public string 
{
private:
   int      m_nCurrentIndex;
public:
   bool ReadLine(string & str,
      bool bWithSeparator = false);
   // _01Read read a token if find one of \n\r\t or space
   bool _01Read(int & i);
   bool _01Read(UINT & user);
   bool _01ReadHex(int & i);
   bool _01ReadHex(UINT & user);
   //bool _01Read(LPTSTR lpsz);
   bool _01Read(string & str);
   bool ExtractFolderPath(const char * lpcszFilePath);
   void Restart();
   void Restart(string &strNew);
   string_tokenizer(const string & strSrc);
   string_tokenizer(const char * lpch, int nLength );
   string_tokenizer();
   virtual ~string_tokenizer();
   BOOL GetNextToken(
      string &strToken,
      const char * lpSeparator,
      BOOL bWithSeparator = FALSE);

   BOOL GetNextSmallestToken(
      string &strToken,
      string_array & straSeparator,
      BOOL bWithSeparator = FALSE);

   // Any of separator character
   bool GetNextTokenEx(
      string &strToken,
      const char * lpSeparator,
      bool bWithSeparator = false,
      bool bSkipAdjacent = false);

};
