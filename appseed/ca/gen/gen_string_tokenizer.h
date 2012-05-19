#pragma once


class CLASS_DECL_ca string_tokenizer : public string 
{
protected:


   strsize      m_nCurrentIndex;


public:


   string_tokenizer(const string & strSrc);
   string_tokenizer(const char * lpch, int nLength );
   string_tokenizer();
   virtual ~string_tokenizer();


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
   bool GetNextToken(string &strToken, const char * lpSeparator, bool bWithSeparator = FALSE);
   bool GetNextSmallestToken(string &strToken, string_array & straSeparator, bool bWithSeparator = FALSE);
   // Any of separator character
   bool GetNextTokenEx(string &strToken, const char * lpSeparator, bool bWithSeparator = false, bool bSkipAdjacent = false);

};

