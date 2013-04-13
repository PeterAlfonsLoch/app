#pragma once


namespace user
{


   class str_context;


} // namespace user


class CLASS_DECL_ca2 cregexp_util  
{
public:


   cregexp_util();
   virtual ~cregexp_util();


   static void    Format(string & str, string_array & wstraArg);


   static bool    add_tokens(string_array & stra, const char * lpsz, const char * lpszExp, index iSubString = 0);
   

   static bool    match(const char * lpcsz, cregexp * re);
   static bool    match(::user::str_context * pcontext, string_array & stra, const char * psz, id pszExp, id pszRoot);


   static index   match(string_array & stra, const char * lpcsz, cregexp * re, strsize iSize);
   static index   match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, strsize iSize);
   

   static bool    find(const char * lpsz, const char * lpszExp, index iSubString, strsize & iStart, strsize & iEnd);
   static bool    find(const char * lpsz, cregexp * re, index iSubString, strsize & iStart, strsize & iEnd);


   static bool    ReplaceAll(string & str, cregexp * re, index iSubString, const char * lpsz);
   

   static cregexp *  CompileExpression(const char * lpszExp, bool bCaseInsensitive);

   


};


