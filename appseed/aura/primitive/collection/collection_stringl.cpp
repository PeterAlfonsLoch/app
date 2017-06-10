//#include "framework.h"


stringl::stringl()
{
}

stringl::~stringl()
{
}

void stringl::implode(string & str, const char * lpcszSeparator, index start, ::count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   
   index i = start;

   auto pos = index_iterator(i);

   for(; i <= last; i++)
   {
      
      if(i > start)
      {
         str += strSeparator;
      }
      
      str += *pos;

      pos++;

   }

}

string stringl::implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}


void stringl::reverse_implode(string & str, const char * lpcszSeparator, index start, ::count count) const
{
   str.Empty();
   string strSeparator(lpcszSeparator);
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }

   index i = last;

   auto pos = reverse_index_iterator(i);

   for(index i = last; i >= start; i--)
   {

      if(i < last)
      {
         str += strSeparator;
      }

      str += *pos;

      pos--;

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


void stringl::add_tail_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty)
{
   ::str::tokenizer strTokenizer(lpcsz);
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


void stringl::write(::file::ostream & ostream) const
{
   ostream << m_count;
   POSITION pos = get_head_position();
   for(int32_t i = 0; i < m_count; i++)
   {
      ostream << get_next(pos);
   }
}

void stringl::read(::file::istream & istream)
{
   int32_t iSize;
   istream >> iSize;
   string str;
   for(int32_t i = 0; i < iSize; i++)
   {
      istream >> str;
      add_tail(str);
   }
}


