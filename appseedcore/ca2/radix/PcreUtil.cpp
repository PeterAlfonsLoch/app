#include "StdAfx.h"


PcreUtil::PcreUtil()
{

}

PcreUtil::~PcreUtil()
{

}

bool PcreUtil::match(::user::str_context * pcontext, string_array & stra, const char * psz,  const char * pszExp, const char * pszRoot)
{
   stringa straCandidate;
   pcontext->get(straCandidate, pszRoot);
   for(int i = 0; i < straCandidate.get_count(); i++)
   {
      string strCandidate = straCandidate[i];
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

int PcreUtil::match(string_array & stra, const char * lpcsz, CRegExp * re, int iSize)
{
   stra.remove_all();

   if(iSize <= 0)
      return 0;

   string str(lpcsz);

   SMatches matches;

   re->setPositionMoves(true);

   bool bMatch = re->parse(lpcsz, &matches);

   for(int i = 0; i < matches.cMatch; i++)
   {
      int iStart   = matches.s[i];
      int iEnd     = matches.e[i];
      stra.add(str.Mid(iStart, iEnd - iStart));
   }
   
   return bMatch;
}

int PcreUtil::match(string_array & stra, const char * lpcsz, const char * lpcszExp, bool bCaseInsensitive, int iSize)
{
   CRegExp * re = CompileExpression(lpcszExp, bCaseInsensitive);
   return match(stra, lpcsz, re, iSize);
}


bool PcreUtil::find(const char * lpsz, CRegExp * re, int iSubString, int & iStart, int & iEnd)
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

bool PcreUtil::find(const char * lpsz, const char * lpszExp, int iSubString, int & iStart, int & iEnd)
{
   CRegExp * re;

   string str;

   str = lpszExp;

   re = CompileExpression(lpszExp, false);

   ASSERT(re != NULL);
   if(re == NULL)
      return false;

   return find(lpsz, re, iSubString, iStart, iEnd);
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
bool PcreUtil::add_tokens(
   string_array & stra, 
   const char * lpszSubject, 
   const char * lpszExpression,
   int iSubString /* =0 */)
{
   CRegExp * re;

   string str;

   str = lpszExpression;

   re = CompileExpression(lpszExpression, false);

   ASSERT(re != NULL);
   if(re == NULL)
      return false;

   re->setPositionMoves(true);

   string strSubject;


   strSubject = lpszSubject;

   string strToken;

   size_t start;
   size_t end = 0;

   if(iSubString < 0)
      iSubString = 0;

   int find = 0;
   while(end < strlen(lpszSubject))
   {
      SMatches matches;
      if(!re->parse(&lpszSubject[find], &matches))
         break;
      start   = matches.s[iSubString] + find;
      end     = matches.e[iSubString] + find;
      
      strToken = strSubject.Mid(start, end - start);

      strToken = strToken;

      stra.add(strToken);      
      find = end + 1;
   }
//   strToken = strSubject.Mid(end, strSubject.get_length() - end);
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
      CRegExp * re = CompileExpression(wstrExp, false);
      re->setPositionMoves(true);
      ReplaceAll(str, re, 1, wstraArg[i]);
   }
}

bool PcreUtil::ReplaceAll(string & str, CRegExp * re, int iSubString, const char * lpsz)
{
   int start;
   int end = 0;
   int iSubstLen = lstrlen(lpsz);
   while(find(str, re, iSubString, start, end))
   {
      str = str.Left(start) + lpsz + str.Mid(end);
      end = start + iSubstLen;
   }
   return true;
}