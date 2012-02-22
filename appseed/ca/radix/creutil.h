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


   static void    Format(string & str, string_array & wstraArg);


   static bool    add_tokens(string_array & stra, const char * lpsz, const char * lpszExp, index iSubString = 0);
   

   static bool    match(const char * lpcsz, CRegExp * re);
   static bool    match(::user::str_context * pcontext, string_array & stra, const char * psz, id pszExp, id pszRoot, id pszExtra);


   static index   match(string_array & stra, const char * lpcsz, CRegExp * re, strsize iSize);
   static index   match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, strsize iSize);
   

   static bool    find(const char * lpsz, const char * lpszExp, index iSubString, strsize & iStart, strsize & iEnd);
   static bool    find(const char * lpsz, CRegExp * re, index iSubString, strsize & iStart, strsize & iEnd);


   static bool    ReplaceAll(string & str, CRegExp * re, index iSubString, const char * lpsz);
   

   static CRegExp *  CompileExpression(const char * lpszExp, bool bCaseInsensitive);

   


};


