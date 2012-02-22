#include "StdAfx.h"


PcreUtil::PcreUtil()
{

}

PcreUtil::~PcreUtil()
{

}

bool PcreUtil::match(::user::str_context * pcontext, string_array & stra, const char * psz,  id pszExp, id pszRoot, id pszExtra)
{
   stringa straCandidate;
   pcontext->get(straCandidate, pszRoot, pszExtra);
   for(int i = 0; i < straCandidate.get_count(); i++)
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

index PcreUtil::match(string_array & stra, const char * lpcsz, CRegExp * re, strsize iSize)
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

index PcreUtil::match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, strsize iSize)
{
   CRegExp * pre = CompileExpression(lpcszExp, bCaseInsensitive);
   index i = match(stra, lpcsz, pre, iSize);
   delete pre;
   return i;
}


bool PcreUtil::find(const char * lpsz, CRegExp * re, index iSubString, strsize & iStart, strsize & iEnd)
{
   string strSubject;


   strSubject = lpsz;

   string str;
   string strToken;

   if(iSubString < 0)
      iSubString = 0;


   str = lpsz;
   str =  str.Left(iEnd);
   iEnd = str.get_length();

   SMatches matches;

   matches.cMatch = 0;

   if(!re->parse(lpsz, &matches))
      return false;

   if(matches.cMatch == 0)
      return false;

   iStart   = matches.s[iSubString];
   str      = strSubject.Left(iStart);
   iStart   = str.get_length();
   iEnd     = matches.e[iSubString];
   str      = strSubject.Left(iEnd);
   iEnd     = str.get_length();

   return true;
}

CRegExp * PcreUtil::CompileExpression(const char * lpszExp, bool bCaseInsensitive)
{
   UNREFERENCED_PARAMETER(bCaseInsensitive);
   return new CRegExp(lpszExp);
}

bool PcreUtil::find(const char * lpsz, const char * lpszExp, index iSubString, strsize & iStart, strsize & iEnd)
{
   CRegExp * pre;

   string str;

   str = lpszExp;

   pre = CompileExpression(lpszExp, false);

   if(pre == NULL)
      return false;

   bool bOk = find(lpsz, pre, iSubString, iStart, iEnd);

   delete pre;

   return bOk;
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
bool PcreUtil::add_tokens(string_array & stra, const char * lpszSubject, const char * lpszExpression, index iSubString /* =0 */)
{
   CRegExp * pre;

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

bool PcreUtil::match(const char * lpsz, CRegExp * re)
{
   string strSubject;


   strSubject = lpsz;

   string str;
   string strToken;

   SMatches matches;

   return re->parse(strSubject, &matches);
}

void PcreUtil::Format(string & str, string_array & wstraArg)
{
   string wstrExp;
   for(int i = 0; i < wstraArg.get_size(); i++)
   {
      wstrExp.Format("/(%%%d)(\\d?!|$)/", i);
      CRegExp * pre = CompileExpression(wstrExp, false);
      pre->setPositionMoves(true);
      ReplaceAll(str, pre, 1, wstraArg[i]);
      delete pre;
   }
}

bool PcreUtil::ReplaceAll(string & str, CRegExp * re, index iSubString, const char * lpsz)
{
   strsize start;
   strsize end = 0;
   strsize iSubstLen = lstrlen(lpsz);
   while(find(str, re, iSubString, start, end))
   {
      str = str.Left(start) + lpsz + str.Mid(end);
      end = start + iSubstLen;
   }
   return true;
}
