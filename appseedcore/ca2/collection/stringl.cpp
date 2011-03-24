#include "StdAfx.h"


stringl::stringl(INT_PTR nBlockSize) :
   string_list(nBlockSize)
{
}

stringl::~stringl()
{
}

void stringl::implode(string & str, const char * lpcszSeparator, index start, count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += get_size();
   }
   index last;
   if(count < 0)
   {
      last = get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   int i = start;
   POSITION pos = find_index(i);
   for(;i <= last; i++)
   {
      if(i > start)
      {
         str += strSeparator;
      }
      str += get_at(pos);
      get_next(pos);
   }
}

string stringl::implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}


void stringl::reverse_implode(string & str, const char * lpcszSeparator, index start, count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += get_size();
   }
   index last;
   if(count < 0)
   {
      last = get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   int i = last;
   POSITION pos = reverse_find_index(i);
   for(index i = last; i >= start; i--)
   {
      if(i < last)
      {
         str += strSeparator;
      }
      str += get_at(pos);
      get_previous(pos);
   }
}

string stringl::reverse_implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   reverse_implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}

void stringl::explode(const char * lpcszSeparator, const char * psz)
{
   remove_all();
   add_tail_tokens(psz, lpcszSeparator, true);
}


void stringl::add_tail_tokens(const char * lpcsz, const char * lpcszSeparator, BOOL bAddEmpty)
{
   string_tokenizer strTokenizer(lpcsz);
   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         add_tail(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         if(strToken.has_char())
            add_tail(strToken);
      }
   }
}


void stringl::write(ex1::output_stream & ostream)
{
   ostream << m_nCount;
   POSITION pos = get_head_position();
   for(int i = 0; i < m_nCount; i++)
   {
      ostream << get_next(pos);
   }
}

void stringl::read(ex1::input_stream & istream)
{
   int iSize;
   istream >> iSize;
   string str;
   for(int i = 0; i < iSize; i++)
   {
      istream >> str;
      add_tail(str);
   }
}


