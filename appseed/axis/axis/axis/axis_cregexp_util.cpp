#include "framework.h"


cregexp_util::cregexp_util()
{

}

cregexp_util::~cregexp_util()
{

}

bool cregexp_util::match(::user::str_context * pcontext, string_array & stra, const char * psz,  id pszExp, id pszRoot)
{
   stringa straCandidate;
   pcontext->get(straCandidate, pszRoot);
   for(int32_t i = 0; i < straCandidate.get_count(); i++)
   {
      string strCandidate = straCandidate[i];
      strCandidate.replace("-", "\\-");
      string strExp(pszExp);
      strExp.replace("%1", strCandidate);
      stringa straResult;
      if(match(straResult, psz, strExp, true, 2) > 0)
      {
         stra = straResult;
         return true;
      }
   }
   return false;
}


index cregexp_util::match(string_array & stra, const char * lpcsz, cregexp * re, strsize iSize)
{
   stra.remove_all();

   if(iSize <= 0)
      return 0;

   string str(lpcsz);

   SMatches matches;

   re->setPositionMoves(true);

   bool bMatch = re->parse(lpcsz, &matches);

   for(index i = 0; i < matches.cMatch; i++)
   {
      strsize iStart   = matches.s[i];
      strsize iEnd     = matches.e[i];
      stra.add(str.Mid(iStart, iEnd - iStart));
   }

   return bMatch;
}

index cregexp_util::match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, strsize iSize)
{
   cregexp * pre = CompileExpression(lpcszExp, bCaseInsensitive);
   index i = match(stra, lpcsz, pre, iSize);
   delete pre;
   return i;
}

bool cregexp_util::find(string & strMatch, const string & str, cregexp * pre, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   if(pre == NULL)
      return false;

   strsize iStart = piStart == NULL ? 0 : *piStart;

   strsize iEnd = piEnd == NULL ? str.get_length() - 1 : *piEnd;

   bool bOk = find(str, pre, iSubString, &iStart, &iEnd);

   if(bOk)
   {
      strMatch = str.substr(iStart, iEnd);
   }

   if(piStart != NULL)
   {
      *piStart = iStart;
   }

   if(piEnd != NULL)
   {
      *piEnd = iEnd;
   }

   return bOk;

}


bool cregexp_util::find(string & strMatch, const string & str, const string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   cregexp * pre;

   pre = CompileExpression(strExp, false);

   if(pre == NULL)
      return false;


   bool bOk = find(strMatch, str, pre, iSubString, piStart, piEnd);

   delete pre;


   return bOk;

}

bool cregexp_util::find(const string & str, const string & strExp, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   cregexp * pre;

   pre = CompileExpression(strExp, false);

   if(pre == NULL)
      return false;


   bool bOk = find(str, pre, iSubString, piStart, piEnd);

   delete pre;


   return bOk;
}

bool cregexp_util::find(const string & str, cregexp * re, index iSubString, strsize  * piStart, strsize  * piEnd)
{

   string strSubject;

   strsize iStart;

   strsize iEnd;

   if(piStart != NULL)
      iStart = *piStart;
   else
      iStart = 0;

   if(piEnd != NULL)
      iEnd = *piEnd;
   else
      iEnd = str.get_length() - 1;


   if(iSubString < 0)
      iSubString = 0;

   iStart = MIN(str.get_length(), MAX(0, iStart));

   iEnd = MIN(str.get_length(), MAX(0, iEnd));

   SMatches matches;

   matches.cMatch = 0;

   const char * lpsz = str;

   lpsz += iStart;

   if(!re->parse(lpsz, &matches))
      return false;

   if(matches.cMatch == 0)
      return false;

   iEnd     = iStart + matches.e[iSubString];

   iStart   = iStart + matches.s[iSubString];

   if(piStart != NULL)
   {
      *piStart = iStart;
   }

   if(piEnd != NULL)
   {
      *piEnd = iEnd;
   }

   return true;

}

cregexp * cregexp_util::CompileExpression(const char * lpszExp, bool bCaseInsensitive)
{
   UNREFERENCED_PARAMETER(bCaseInsensitive);
   return new cregexp(lpszExp);
}

bool cregexp_util::split(string_array & stra, index_array & iaStart, index_array & iaEnd,  const string & str, const string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   cregexp * pre;

   pre = CompileExpression(strExp, false);

   if(pre == NULL)
      return false;

   bool bFound = split(stra, iaStart, iaEnd, str, pre, iLimit, bAddEmpty, bWithSeparator);

   delete pre;

   return bFound;


}

bool    cregexp_util::split(string_array & stra, const string & str, const string & strExp, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   cregexp * pre;

   pre = CompileExpression(strExp, false);

   if(pre == NULL)
      return false;

   bool bFound = split(stra, str, pre, iLimit, bAddEmpty, bWithSeparator);

   delete pre;

   return bFound;

}

bool cregexp_util::split(string_array & stra, index_array & iaStart, index_array & iaEnd,  const string & str, cregexp * pre, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   if(pre == NULL)
      return false;

   strsize iStart = 0;
   string strMatch;
   strsize iPreviousStart;

   ::count cInitial = stra.get_count();

   while(true)
   {

      strsize iEnd = str.get_length() - 1;

      iPreviousStart = iStart;

      if(!find(strMatch, str, pre, 0, &iStart, &iEnd))
         break;

      if(bAddEmpty || iStart > iPreviousStart)
      {

         if(bWithSeparator)
         {
            stra.add(str.substr(iPreviousStart, iEnd - iPreviousStart + 1));
         }
         else
         {
            stra.add(str.substr(iPreviousStart, iEnd - iStart));
         }

         iaStart.add(iStart);
         iaEnd.add(iEnd);

      }

      iStart = iEnd + 1;

      if(iStart >= str.length())
         break;

   }

   delete pre;

   return stra.get_count() > cInitial;

}


bool cregexp_util::split(string_array & stra, const string & str, cregexp * pre, int iLimit, bool bAddEmpty, bool bWithSeparator)
{

   if(pre == NULL)
      return false;

   strsize iStart = 0;
   string strMatch;
   strsize iPreviousStart;

   ::count cInitial = stra.get_count();

   while(true)
   {

      strsize iEnd = str.get_length() - 1;

      iPreviousStart = iStart;

      if(!find(strMatch, str, pre, 0, &iStart, &iEnd))
         break;

      if(bAddEmpty || iStart > iPreviousStart)
      {

         if(bWithSeparator)
         {
            stra.add(str.substr(iPreviousStart, iEnd - iPreviousStart + 1));
         }
         else
         {
            stra.add(str.substr(iPreviousStart, iEnd - iStart));
         }

      }

      iStart = iEnd + 1;

      if(iStart >= str.length())
         break;

   }

   return stra.get_count() > cInitial;

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
bool cregexp_util::add_tokens(string_array & stra, const char * lpszSubject, const char * lpszExpression, index iSubString /* =0 */)
{
   cregexp * pre;

   string str;

   str = lpszExpression;

   pre = CompileExpression(lpszExpression, false);

   ASSERT(pre != NULL);
   if(pre == NULL)
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

bool cregexp_util::match(const char * lpsz, const string & strExp)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return match(lpsz, re);

}

bool cregexp_util::match(const char * lpsz, cregexp * re)
{
   string strSubject;


   strSubject = lpsz;

   string str;
   string strToken;

   SMatches matches;

   return re->parse(strSubject, &matches);
}

void cregexp_util::Format(string & str, string_array & wstraArg)
{

   string wstrExp;

   for(int32_t i = 0; i < wstraArg.get_size(); i++)
   {

      wstrExp.Format("/(%%%d)(\\d?!|$)/", i);

      cregexp * pre = CompileExpression(wstrExp, false);

      pre->setPositionMoves(true);

      replace(str, pre, 1, wstraArg[i]);

      delete pre;

   }

}

bool cregexp_util::replace(string & str, const string & strTopicParam, const string & strExp, index iSubString, const string & strReplace, strsize start, strsize end)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return replace(str, strTopicParam, re, iSubString, strReplace, start, end);

}

bool cregexp_util::replace(string & str, const string & strExp, index iSubString, const string & strReplace, strsize start, strsize end)
{

   sp(cregexp) re;

   re = CompileExpression(strExp, true);

   return replace(str, re, iSubString, strReplace, start, end);

}

bool cregexp_util::replace(string & str, const string & strTopicParam, cregexp * re, index iSubString, const string & strReplace, strsize start, strsize end)
{

   str = strTopicParam;

   return replace(str, re, iSubString, strReplace, start, end);

}

bool cregexp_util::replace(string & str, cregexp * re, index iSubString, const string & strReplace, strsize start, strsize end)
{
   string strTopic(str.Left(end));
   strsize iSubstLen = strReplace.length();
   string strMatch;
   while(true)
   {
      end = str.length();
      if(!find(strMatch, str, re, iSubString, &start, &end))
         break;
      str = str.Left(start) + strReplace + str.Mid(end);
      end = start + iSubstLen;
   }
   return true;
}
