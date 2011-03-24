#pragma once

namespace user
{
   class str_context;
} // namespace user

class CLASS_DECL_ca PcreUtil  
{
public:
   PcreUtil();
   virtual ~PcreUtil();

   static void Format(string & str, string_array & wstraArg);
   static bool add_tokens(string_array & stra, const char * lpsz, const char * lpszExp, int iSubString = 0);
   static bool match(const char * lpcsz, CRegExp * re);
   static int match(string_array & stra, const char * lpcsz, CRegExp * re, int iSize);
   static int match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, int iSize);
   static bool find(const char * lpsz, const char * lpszExp, int iSubString, int & iStart, int & iEnd);
   static bool find(const char * lpsz, CRegExp * re, int iSubString, int & iStart, int & iEnd);
   static bool ReplaceAll(string & str, CRegExp * re, int iSubString, const char * lpsz);
   static CRegExp * CompileExpression(const char * lpszExp, bool bCaseInsensitive);
   static bool match(::user::str_context * pcontext, string_array & stra, const char * psz,  const char * pszExp, const char * pszRoot);
};

