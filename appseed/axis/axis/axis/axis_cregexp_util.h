#pragma once


namespace user
{


   class str_context;


} // namespace user


class CLASS_DECL_AXIS cregexp_util  
{
public:


   cregexp_util();
   virtual ~cregexp_util();


   static void    Format(string & str, string_array & wstraArg);


   static bool    add_tokens(string_array & stra, const char * lpsz, const char * lpszExp, index iSubString = 0);
   

   static bool    match(const char * lpcsz, const string & strExp);
   static bool    match(const char * lpcsz, cregexp * re);
   static bool    match(::user::str_context * pcontext, string_array & stra, const char * psz, id pszExp, id pszRoot);
   

   static index   match(string_array & stra, const char * lpcsz, cregexp * re, strsize iSize);
   static index   match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, strsize iSize);
   

   static bool    find(string & strMatch, const string & str, const string & strExp, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);
   static bool    find(string & strMatch, const string & str, cregexp * re, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);

   static bool    find(const string & str, const string & strExp, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);
   static bool    find(const string & str, cregexp * re, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);

   static bool    split(string_array & stra, raw_index_array & iaStart, raw_index_array & iaEnd, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
   static bool    split(string_array & stra, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);


   static bool    split(string_array & stra, raw_index_array & iaStart, raw_index_array & iaEnd, const string & str, cregexp * re, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
   static bool    split(string_array & stra, const string & str, cregexp * re, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);

   static bool    replace(string & str, const string & strTopic, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
   static bool    replace(string & str, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);

   static bool    replace(string & str, const string & strTopic, cregexp * re, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
   static bool    replace(string & str, cregexp * re, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
   

   static cregexp *  CompileExpression(const char * lpszExp, bool bCaseInsensitive);

   


};


