#pragma once


namespace aura
{


   class str_context;


} // namespace aura


class CLASS_DECL_AURA cregexp_util
{
public:


   cregexp_util();
   virtual ~cregexp_util();


   static void    Format(string & str, string_array & wstraArg);


   static bool    add_tokens(string_array & stra, const string & lpsz, const string & lpszExp, index iSubString = 0);


   static bool    match(const string & lpcsz, const string & strExp);


   static index   match(string_array & stra, const string & lpcsz, const string & lpcszExp, bool bCaseInsensitive, strsize iSize);


   static bool    find(string & strMatch, const string & str, const string & strExp, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);

   static bool    find(const string & str, const string & strExp, index iSubString, strsize * piStart = NULL, strsize * piEnd = NULL);

   static bool    split(string_array & stra, index_array & iaStart, index_array & iaEnd, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);
   static bool    split(string_array & stra, const string & str, const string & strExp, int iLimit = -1, bool bAddEmpty = true, bool bWithSeparator = false);



   static bool    replace(string & str, const string & strTopic, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);
   static bool    replace(string & str, const string & strExp, index iSubString, const string & strReplace, strsize start = 0, strsize end = -1);



   static cregexp *  CompileExpression(const string & lpszExp, bool bCaseInsensitive);




};


