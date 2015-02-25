//#include "framework.h"


cregexp_util::cregexp_util()
{

}

cregexp_util::~cregexp_util()
{

}




index cregexp_util::match(string_array & stra, const string & lpcsz, const string & lpcszExp, bool bCaseInsensitive, strsize iSize)
{

   sp(cregexp) pre = CompileExpression(lpcszExp, bCaseInsensitive);

   if(pre.is_null())
      return -1;

   index i = pre->match(stra, lpcsz, iSize);

   return i;

}



bool cregexp_util::find(string & strMatch, const string & str, const string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   sp(cregexp) pre = CompileExpression(strExp, false);

   if(pre.is_null())
      return false;


   bool bOk = pre->find(strMatch, str, iSubString, piStart, piEnd);

   delete pre;


   return bOk;

}

bool cregexp_util::find(const string & str, const string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   sp(cregexp) pre = CompileExpression(strExp, false);

   if(pre.is_null())
      return false;

   bool bOk = pre->find(str, iSubString, piStart, piEnd);

   return bOk;

}



cregexp * cregexp_util::CompileExpression(const string & lpszExp, bool bCaseInsensitive)
{

   UNREFERENCED_PARAMETER(bCaseInsensitive);

   return canew(cregexp(lpszExp));

}


bool cregexp_util::split(string_array & stra, index_array & iaStart, index_array & iaEnd,  const string & str, const string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   sp(cregexp) pre = CompileExpression(strExp, false);

   if(pre.is_null())
      return false;

   bool bFound = pre->split(stra, iaStart, iaEnd, str, iLimit, bAddEmpty, bWithSeparator);

   return bFound;


}

bool    cregexp_util::split(string_array & stra, const string & str, const string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   sp(cregexp) pre = CompileExpression(strExp, false);

   if(pre.is_null())
      return false;

   bool bFound = pre->split(stra, str, iLimit, bAddEmpty, bWithSeparator);

   return bFound;

}


///////////////////////////////////////////////////////////////////////////////
//
// Name: add_tokens
//
// Purpose:
// add non overlapping ocurrences of "expression" in "subject".
// Substring indicates the parenthesis order of the desired substring.
//
// Output:
// 'true' if successfull.
//
///////////////////////////////////////////////////////////////////////////////
bool cregexp_util::add_tokens(string_array & stra, const string & lpszSubject, const string & strExp, index iSubString /* =0 */)
{

   sp(cregexp) pre = CompileExpression(strExp, false);

   if(pre.is_null())
      return false;

   pre->setPositionMoves(true);

   string strSubject;


   strSubject = lpszSubject;

   string strToken;

   size_t start;
   size_t end = 0;

   if(iSubString < 0)
      iSubString = 0;

   strsize find = 0;
   while(end < strlen(lpszSubject))
   {
      SMatches matches;
      if(!pre->parse(&lpszSubject[find], &matches))
         break;
      start   = matches.s[iSubString] + find;
      end     = matches.e[iSubString] + find;

      strToken = strSubject.Mid(start, end - start);

      strToken = strToken;

      stra.add(strToken);
      find = end + 1;
   }

   delete pre;

   return true;
}

bool cregexp_util::match(const string & lpsz, const string & strExp)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return re->match(lpsz);

}



void cregexp_util::Format(string & str, string_array & wstraArg)
{

   string wstrExp;

   for(int32_t i = 0; i < wstraArg.get_size(); i++)
   {

      wstrExp.Format("/(%%%d)(\\d?!|$)/", i);

      sp(cregexp) pre = CompileExpression(wstrExp, false);

      pre->setPositionMoves(true);

      pre->replace(str, 1, wstraArg[i]);

   }

}

bool cregexp_util::replace(string & str, const string & strTopicParam, const string & strExp, index iSubString, const string & strReplace, strsize start, strsize end)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return re->replace(str, strTopicParam, iSubString, strReplace, start, end);

}

bool cregexp_util::replace(string & str, const string & strExp, index iSubString, const string & strReplace, strsize start, strsize end)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return re->replace(str, iSubString, strReplace, start, end);

}

