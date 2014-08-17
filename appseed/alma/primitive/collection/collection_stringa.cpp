#include "framework.h"


// return string length or -1 if UNICODE string is found in the archive
__STATIC UINT __read_string_length(::file::input_stream & ar);


stringa::stringa(sp(::base::application) papp) :
element(papp)
{
}

stringa::stringa(const char * psz)
{

   add(psz);

}


stringa::stringa(const string & str)
{

   add(str);

}

stringa::stringa(const var & var)
{

   add(var);

}

stringa::stringa(const stringa &array)
{
   operator =(array);
}

stringa::~stringa()
{
}

void stringa::add_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty)
{
   ::str::tokenizer strTokenizer(lpcsz);
   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         string_array::add(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextToken(strToken, lpcszSeparator, FALSE))
      {
         if(!strToken.is_empty())
            string_array::add(strToken);
      }
   }
}

int32_t g_add_smallest_tokens = 0;

void stringa::add_smallest_tokens(const char * lpcsz, stringa & straSeparator, bool bAddEmpty, bool bWithSeparator)
{
   ::str::tokenizer strTokenizer(lpcsz);
   string strToken;
   if(bAddEmpty)
   {
      while(strTokenizer.GetNextSmallestToken(strToken, straSeparator, bWithSeparator))
      {
         string_array::add(strToken);
      }
   }
   else
   {
      while(strTokenizer.GetNextSmallestToken(strToken, straSeparator, bWithSeparator))
      {
         if(!strToken.is_empty())
            string_array::add(strToken);
      }
   }
}


void stringa::add_lines(const string & str)
{

   stringa straSeparator;

   straSeparator.add("\r");

   straSeparator.add("\n");

   straSeparator.add("\r\n");

   add_smallest_tokens(str, straSeparator, true, false);

}


void stringa::get_format_string(string & str, const char * lpcszSeparator) const
{
   str.Empty();
   if(m_nSize > 0)
   {
      str = get_at(0);
   }
   for(int32_t i = 1; i < m_nSize; i++)
   {
      str += lpcszSeparator + get_at(i);
   }
}






/*void stringa::XFV001Expand()
{
stringa strArray;
uint_array dwa;
for(int32_t i = 0; i < m_nSize; i++)
{
strArray.add_tokens(get_at(i), "/", FALSE);
if(strArray.get_size() > 1)
{
for(int32_t j = 0; j < strArray.get_size(); j++)
{
add_unique(strArray.get_at(j));
}
if(strArray.get_size() > 1)
{
dwa.add(i);
}
}
strArray.remove_all();
}
for(i = dwa.get_size(); --i >= 0 ;)
{
remove_at(dwa.get_at(i));
}
Sort(stringa::Compare);

}*/

index stringa::add_unique(const char * lpcsz)
{
   index find = find_first(lpcsz);
   if(find >= 0)
      return -1;
   return string_array::add(lpcsz);
}

::count stringa::add_unique(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      if(add_unique(stra[i]) >= 0)
         count++;
   }
   return count;
}

index stringa::add_unique_ci(const char * lpcsz)
{
   index find = find_first_ci(lpcsz);
   if(find >= 0)
      return -1;
   return string_array::add(lpcsz);
}

::count stringa::add_unique_ci(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      if(add_unique_ci(stra[i]) >= 0)
         count++;
   }
   return count;
}

index stringa::find_first_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(this->element_at(find).CompareNoCase(lpcsz) == 0)
         return find;
   }
   return -1;
}

index stringa::find_first(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find <= last; find++)
   {
      if(this->element_at(find).Compare(lpcsz) == 0)
         return find;
   }
   return -1;
}


index stringa::reverse_find_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find >= last; find--)
   {
      if(this->element_at(find).CompareNoCase(lpcsz) == 0)
         return find;
   }
   return -1;
}

index stringa::reverse_find(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find >= last; find--)
   {
      if(this->element_at(find).Compare(lpcsz) == 0)
         return find;
   }
   return -1;
}

index stringa::find_first_begins_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(::str::begins_ci(this->element_at(find), lpcsz))
         return find;
   }
   return -1;
}

index stringa::find_first_begins(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(::str::begins(this->element_at(find), lpcsz))
         return find;
   }
   return -1;
}

index stringa::str_find_first_begins_ci(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(::str::begins_ci(lpcsz, this->element_at(find)))
         return find;
   }
   return -1;
}

index stringa::str_find_first_begins(const char * lpcsz, index find, index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(::str::begins(lpcsz, this->element_at(find)))
         return find;
   }
   return -1;
}


bool stringa::contains_ci(const char * lpcsz, index find, index last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first_ci(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}

bool stringa::contains(const char * lpcsz, index find, index last, ::count countMin, ::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(lpcsz, find, last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0, count <= countMax);
}


index stringa::remove_first_ci(const char * lpcsz, index find, index last)
{
   if((find = find_first_ci(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

index stringa::remove_first(const char * lpcsz, index find, index last)
{
   if((find = find_first(lpcsz, find, last)) >= 0)
      remove_at(find);
   return find;
}

::count stringa::remove_ci(const char * lpcsz, index find, index last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains_ci(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first_ci(lpcsz, find, last)) >= 0)
         count++;
   return count;
}

::count stringa::remove(const char * lpcsz, index find, index last, ::count countMin, ::count countMax)
{
   ::count count = 0;
   if(contains(lpcsz, find, last, countMin, countMax))
      while(conditional(countMax >= 0, count < countMax)
         && (find = remove_first(lpcsz, find, last)) >= 0)
         count++;
   return count;
}

::count stringa::remove_ci(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      count += remove_ci(stra[i]);
   }
   return count;
}

::count stringa::remove(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      count += remove(stra[i]);
   }
   return count;
}

void stringa::trim_left(const char * pszChars)
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_left(pszChars);
   }
}

void stringa::trim_right(const char * pszChars)
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_right(pszChars);
   }
}

void stringa::trim(const char * pszChars)
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim(pszChars);
   }
}


void stringa::trim_left()
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_left();
   }
}

void stringa::trim_right()
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim_right();
   }
}

void stringa::trim()
{
   for(int32_t i = 0; i < m_nSize; i++)
   {
      operator[](i).trim();
   }
}

index stringa::add_normal(const char * lpcsz)
{
   return string_array::add(lpcsz);
}

::count stringa::remove_empty()
{
   ::count count = 0;
   for(index i = 0; i < this->get_size();)
   {
      if(this->element_at(i).is_empty())
      {
         remove_at(i);
         count++;
      }
      else
      {
         i++;
      }
   }
   return count;
}

primitive::memory stringa::GetFormatV004()
{

   strsize iTotalLength = 0;

   strsize i;

   for(i = 0; i < m_nSize; i++)
   {
      iTotalLength += this->element_at(i).get_length();
      iTotalLength++;
   }

   if(iTotalLength == 0)
   {
      iTotalLength = 2;
   }
   else
   {
      iTotalLength++;
   }

   primitive::memory mem;

   mem.allocate(iTotalLength * sizeof(char));

   char * lpsz = (char *) mem.get_data();

   memset(lpsz, 0x00, iTotalLength * sizeof(char));

   char * lpszN = lpsz;

   strsize iLength;

   for(i = 0; i < m_nSize; i++)
   {

      string * pstr = &this->element_at(i);

      iLength = pstr->get_length();

#ifdef WINDOWS
      strcat_s(lpszN, iLength, *pstr);
#else
      strcat(lpszN, *pstr);
#endif

#ifdef WINDOWSEX
      iLength = _tcsnbcnt(lpszN, iLength);
#elif defined(METROWINDOW)
      iLength = wcsnbcnt(lpszN, iLength);
#else
      iLength = strlen(lpszN);
#endif

      lpszN = (char *) ((LPBYTE)lpszN) + iLength + sizeof(char);

   }

   if(iTotalLength == 2)
   {
      memset(lpsz, 0x00, iTotalLength * sizeof(char));
   }
   else
   {
      memset(lpszN, 0x00, sizeof(char));
   }

   return mem;

}


stringa & stringa::operator =(const stringa & tokena)
{
   copy((string_array &) tokena);
   return *this;
}

stringa & stringa::operator =(const string_array & tokena)
{
   copy(tokena);
   return *this;
}

stringa & stringa::operator =(const int64_array & ia)
{
   copy(ia);
   return *this;
}


/*int32_t stringa::CountPrefixNoCase(const char * lpcszPrefix)
{
string str;
if(lpcszPrefix != NULL)
str = lpcszPrefix;
if(str.is_empty())
{
return this->get_size();
}
else
{
int32_t iCount = 0;
int32_t iLen = str.get_length();
for(int32_t i = 0; i < this->get_size(); i++)
{
string & strLeft = this->element_at(i).Left(iLen);
if(strLeft.get_length() == iLen)
{
if(CompareNoCase(strLeft, str) == 0)
{
iCount++;
}
}
}
return iCount;
}
}*/

/*void stringa::ExtractPrefixNoSortNoCase(
stringa &stra,
const char * lpcsz,
int32_t iLength,
int32_t iMinLength)
{
ASSERT(iLength >= iMinLength);
remove_all();
string str;
if(lpcsz != NULL)
str = lpcsz;
if(str.is_empty())
{
for(int32_t i = 0; i < stra.get_size(); i++)
{
string & strMid = stra[i].Left(iLength);
if(strMid.get_length() >= iMinLength)
{
if(FindFirstNoSortNoCase(strMid) < 0)
{
add(strMid);
}
}
}
}
else
{
int32_t iLen = max(str.get_length(), iMinLength);
for(int32_t i = 0; i < stra.get_size(); i++)
{
string & strMid = stra[i].Left(iLength);
if(strMid.get_length() >= iLen)
{
if(CompareNoCase(strMid.Left(iLen), str) == 0)
{
if(FindFirstNoSortNoCase(strMid) < 0)
{
add(strMid);
}
}
}
}
}

}

int32_t stringa::FindFirstNoSortNoCase(const char * lpcsz)
{
for(int32_t i = 0; i < this->get_size(); i++)
{
if(CompareNoCase(lpcsz, this->element_at(i)) == 0)
{
return i;
}
}
return -1;
}
*/


void stringa::write(::file::output_stream & ostream)
{
   ostream.write_arbitrary(m_nSize);
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      ostream << this->element_at(i);
   }
}

void stringa::read(::file::input_stream & istream)
{

   ::count iSize;

   istream.read_arbitrary(iSize);

   remove_all();

   for(int32_t i = 0; i < iSize; i++)
   {

      if(i >= this->get_size())
         set_size(min(i + 1024, iSize));

      istream >> this->element_at(i);

   }

   if(this->get_size() != iSize)
      throw io_exception(get_app(), "stringa::read");

}





void stringa::implode(string & str, const char * lpcszSeparator, index start, ::count count) const
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
   for(index i = start; i <= last; i++)
   {
      if(i > start)
      {
         str += strSeparator;
      }
      str += this->element_at(i);
   }
}

string stringa::implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}


void stringa::reverse_implode(string & str, const char * lpcszSeparator, index start, ::count count) const
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
   for(index i = last; i >= start; i--)
   {
      if(i < last)
      {
         str += strSeparator;
      }
      str += this->element_at(i);
   }
}

string stringa::reverse_implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   reverse_implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}

stringa & stringa::explode(const string & strSeparator, const string & str)
{

   remove_all();

   add_tokens(str, strSeparator, true);

   return * this;

}


stringa & stringa::csstidy_explode_ws(char sep, const char * psz)
{

   string istring(psz);

   // 1 = st // 2 = str
   int32_t status = 1;
   char to = '\0';

   add("");
   strsize num = 0;
   strsize len = istring.length();
   for(strsize i = 0; i < len; i++)
   {

      switch(status)
      {
      case 1:
         if(istring[i] == sep && !::str::simple_escaped(istring, i))
         {
            ++num;
            add("");
         }
         else if((istring[i] == '"' || istring[i] == '\'' || istring[i] == '(') && !::str::simple_escaped(istring,i))
         {
            status = 2;
            to = (istring[i] == '(') ? ')' : istring[i];
            element_at(num) += istring[i];
         }
         else
         {
            element_at(num) += istring[i];
         }
         break;

      case 2:
         if(istring[i] == to && !::str::simple_escaped(istring,i))
         {
            status = 1;
         }
         element_at(num) += istring[i];
         break;
      }

   }

   return *this;

}

void stringa::replace(const char * lpszSearch, const char * lpszReplace)
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).replace(lpszSearch, lpszReplace);
   }
}


void stringa::surround(const char * pszPrefix, const char * pszSuffix, index iStart, ::count iCount)
{

   string strPrefix(pszPrefix);

   string strSuffix(pszSuffix);

   strsize iEnd;

   if(iStart < 0)
      iStart = this->get_size() + iStart;

   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;

   for(index i = iStart; i <= iEnd; i++)
   {

      this->element_at(i) = strPrefix + this->element_at(i) + strSuffix;

   }

}

string stringa::surround_and_implode(const char * pszSeparator, const char * pszPrefix, const char * pszSuffix, index iStart, ::count iCount)
{
   string str;
   string strSeparator(pszSeparator);
   string strPrefix(pszPrefix);
   string strSuffix(pszSuffix);

   index iEnd;

   if(iStart < 0)
      iStart = this->get_size() + iStart;

   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;

   if(iStart <= iEnd)
   {

      str = strPrefix + this->element_at(iStart) + strSuffix;

      iStart++;

      for(index i = iStart; i <= iEnd; i++)
      {

         str += strSeparator + strPrefix + this->element_at(i) + strSuffix;

      }

   }

   return str;

}

stringa & stringa::operator -=(const string_array & stra)
{
   remove(stra);
   return *this;
}

stringa & stringa::operator +=(const string_array & stra)
{
   add(stra);
   return *this;
}

stringa stringa::operator -(const string_array & straParam) const
{
   stringa stra(*this);
   stra -= straParam;
   return stra;
}

stringa stringa::operator +(const string_array & straParam) const
{
   stringa stra(*this);
   stra += straParam;
   return stra;
}

stringa & stringa::operator = (var var)
{
   if(var.get_type() == var::type_stra)
   {
      *this = var.stra();
   }
   else
   {
      remove_all();
      if(var.get_count() == 1)
      {
         add(var.get_string());
      }
      else if(var.get_count() > 1)
      {
         *this = var.stra();
      }
   }
   return *this;
}

bool stringa::move_ci(const char * lpcsz, index iIndex)
{
   index i = find_first_ci(lpcsz);
   if(i < 0)
      return false;
   remove_at(i);
   insert_at(iIndex, lpcsz);
   return true;
}

bool stringa::preferred(const char * lpcsz)
{
   return move_ci(lpcsz, 0);
}

::count stringa::preferred(stringa & stra)
{
   ::count count = 0;
   for(index i = stra.get_upper_bound(); i >= 0; i--)
   {
      if(preferred(stra[i]))
         count++;
   }
   return count;
}


string stringa::pop(index i)
{
   i = get_upper_bound(i);
   string strRet = this->element_at(i);
   remove_at(i);
   return strRet;
}

void stringa::slice(stringa & stra, index iOffset, ::count count)
{

   index iEnd;

   if(count < 0)
      iEnd = get_upper_bound(count);
   else
      iEnd = iOffset + count - 1;

   for(index i = iOffset; i <= iEnd; i++)
   {
      stra.add(this->element_at(i));
   }

}

void stringa::remove(index iOffset, ::count count)
{
   for(index i = iOffset + count - 1; i >= iOffset; i--)
   {
      remove_at(i);
   }
}


void stringa::splice(const stringa & stra, index iOffset, ::count count)
{

   remove(iOffset, count);

   insert_at(iOffset, stra);

}


void stringa::splice(const stringa & stra, index iOffset, stringa & straRemoved, ::count count)
{

   slice(straRemoved, iOffset, count);

   remove(iOffset, count);

   insert_at(iOffset, stra);

}


bool stringa::is_empty(::count countMinimum)
{
   return this->get_size() < countMinimum;
}

bool stringa::has_elements(::count countMinimum)
{
   return this->get_count() >= countMinimum;
}


::count stringa::get_begins_ci(stringa & stra, const char * lpcsz, index first, index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
   index i = first;
   index iFind;
   ::count count = 0;
   while(true)
   {
      iFind = find_first_begins_ci(lpcsz, i, last);
      if(iFind < 0)
         return count;
      stra.add(this->element_at(iFind));
      i = iFind + 1;
      count++;
   }
}

::count stringa::filter_begins_ci(const char * lpcsz, index first, index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
   index i = first;
   index iFind;
   ::count count = 0;
   while(true)
   {
      iFind = find_first_begins_ci(lpcsz, i, last);
      if(iFind < 0)
      {
         remove_at(i, last - i + 1);
         return count;
      }
      remove_at(i, iFind - i);
      last -= iFind - i;
      i++;
      count++;

   }
}

index stringa::get_random_index() const
{
   if(this->get_size() <= 0)
      return -1;
   return (index) (rand() % get_size());
}

string & stringa::random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}

const string & stringa::random_element() const
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}

string stringa::pop_random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   index i = get_random_index();
   string str = this->element_at(i);
   remove_at(i);
   return str;
}



void stringa::make_lower()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_lower();
   }
}

void stringa::make_upper()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_upper();
   }
}


comparable_array < id > stringa::get_comparable_ida() const
{

   comparable_array < id > ida;

   for(int32_t i = 0; i < get_count(); i++)
   {
      ida.add(element_at(i));
   }

   return ida;

}



string stringa::encode_v16()
{
   string strEncode;
   for(int32_t ui = 0; ui < this->get_count(); ui++)
   {
      string & str = this->element_at(ui);
      strEncode += hex::lower_from((const char*) str, str.get_length());
      strEncode += "00";
/*      for(int32_t uj = 0; uj < str.length(); uj++)
      {
         char sz[32];
         itoa_dup(sz, str[uj], 16);
         if(strlen_dup(sz) == 0)
         {
            strEncode += "00";
         }
         else if(strlen_dup(sz) == 1)
         {
            strEncode += "0";
            strEncode += sz;
         }
         else if(strlen_dup(sz) == 2)
         {
            strEncode += sz;
         }
      }*/

   }
   return strEncode;
}



void stringa::decode_v16(const char * psz)
{
   int32_t iSize = 1024;
   char * str = NULL;
   if(psz == NULL)
      return;
   while(*psz != '\0')
   {
      psz++;
      if(*psz == '\0')
         break;
      char sz[3];
      sz[0] = psz[-1];
      sz[1] = psz[0];
      sz[2] = '\0';
      const char * pszEnd;
      int32_t iConversion = ::atoi_dup(sz, &pszEnd, 16);
      char ch = static_cast < char > (iConversion);
      if(ch == '\0')
      {
         add(str);
         str = NULL;
         iSize = 1024;
      }
      else
      {
         if(str == NULL)
         {
            str = (char *) memory_alloc(iSize);
         }
         else if(iSize < (strlen_dup(str) + 1))
         {
            char * strOld = str;
            iSize += 1024;
            char * strNew = (char *) memory_alloc(iSize);
            strcpy_dup(strNew, strOld);
            str = strNew;
         }
         sz[0] = ch;
         sz[1] = '\0';
         strcat_dup(str, sz);
      }
      psz++;
   }

}


::count stringa::get_count_except(const string & str)
{

   ::count c = get_count();

   for (index i = 0; i < get_count(); i++)
   {
      
      if (element_at(i) == str)
         c--;

   }

   return c;

}

::count stringa::get_count_except(const stringa & stra)
{

   ::count c = get_count();

   for (index i = 0; i < get_count(); i++)
   {

      if (stra.contains(element_at(i)))
         c--;

   }

   return c;

}


::count stringa::get_count_except_ci(const string & str)
{

   ::count c = get_count();

   for (index i = 0; i < get_count(); i++)
   {

      if (element_at(i).CompareNoCase(str) == 0)
         c--;

   }

   return c;

}

::count stringa::get_count_except_ci(const stringa & stra)
{

   ::count c = get_count();

   for (index i = 0; i < get_count(); i++)
   {

      if (stra.contains_ci(element_at(i)))
         c--;

   }

   return c;

}


string stringa::get_json()
{
   
   string str("[");

   for (index i = 1; i < get_count(); i++)
   {
      if (i > 0)
      {
         str += ", \r\n";
      }

      str += "\"";

      str += element_at(i);

      str += "\"";

   }


   str += "\r\n]";

   return str;
}