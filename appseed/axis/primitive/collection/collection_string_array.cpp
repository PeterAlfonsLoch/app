#include "framework.h"

#undef new

static void _ConstructElements(string* pNewData, int_ptr nCount)
{
   ASSERT(nCount >= 0);

   while (nCount--)
   {
      ConstructElement(pNewData);
      pNewData++;
   }
}

static void _DestructElements(string* pOldData, int_ptr nCount)
{
   ASSERT(nCount >= 0);

   while (nCount--)
   {
      DestructElement(pOldData);
      pOldData++;
   }
}

string_array::string_array()
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
}


string_array::string_array(sp(::axis::application) papp) :
element(papp)
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

string_array::string_array(const string_array & a ) :
element(a.get_app())
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
   copy(a);
}

string_array::~string_array()
{
   ASSERT_VALID(this);


   _DestructElements(m_pData, m_nSize);
   delete[] (BYTE*)m_pData;
}

void string_array::set_size(::count nNewSize, ::count nGrowBy)
{
   ASSERT_VALID(this);
   ASSERT(nNewSize >= 0);

   if (nGrowBy != -1)
      m_nGrowBy = nGrowBy;  // set new size

   if (nNewSize == 0)
   {
      // shrink to nothing

      _DestructElements(m_pData, m_nSize);
      delete[] (BYTE*)m_pData;
      m_pData = NULL;
      m_nSize = m_nMaxSize = 0;
   }
   else if (m_pData == NULL)
   {
      // create one with exact size
#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX/sizeof(string))
         throw new memory_exception(get_app());
      ASSERT(nNewSize <= SIZE_T_MAX/sizeof(string));    // no overflow
#endif

      m_pData = (string*) new BYTE[nNewSize * sizeof(string)];

      _ConstructElements(m_pData, nNewSize);

      m_nSize = m_nMaxSize = nNewSize;
   }
   else if (nNewSize <= m_nMaxSize)
   {
      // it fits
      if (nNewSize > m_nSize)
      {
         // initialize the new elements

         _ConstructElements(&m_pData[m_nSize], nNewSize-m_nSize);

      }

      else if (m_nSize > nNewSize)  // destroy the old elements
         _DestructElements(&m_pData[nNewSize], m_nSize-nNewSize);

      m_nSize = nNewSize;
   }
   else
   {
      // otherwise, grow array
      nGrowBy = m_nGrowBy;
      if (nGrowBy == 0)
      {
         // heuristically determine growth when nGrowBy == 0
         //  (this avoids heap fragmentation in many situations)
         nGrowBy = min(1024, max(4, m_nSize / 8));
      }
      ::count nNewMax;
      if (nNewSize < m_nMaxSize + nGrowBy)
         nNewMax = m_nMaxSize + nGrowBy;  // granularity
      else
         nNewMax = nNewSize;  // no slush

      ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
#ifdef SIZE_T_MAX
      ASSERT(nNewMax <= SIZE_T_MAX/sizeof(string)); // no overflow
#endif
      string* pNewData = (string*) new BYTE[nNewMax * sizeof(string)];

      // copy new data from old
      memcpy(pNewData, m_pData, m_nSize * sizeof(string));

      // construct remaining elements
      ASSERT(nNewSize > m_nSize);

      _ConstructElements(&pNewData[m_nSize], nNewSize-m_nSize);


      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nSize = nNewSize;
      m_nMaxSize = nNewMax;
   }
}

::count string_array::add(const string_array& src)
{
   if(this == &src)
   {
      string_array thisCopy(src);
      return add(thisCopy);
   }
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   ::count nOldSize = m_nSize;
   set_size(m_nSize + src.m_nSize);

   CopyElements(m_pData + nOldSize, src.m_pData, src.m_nSize);

   return nOldSize;
}

void string_array::copy(const string_array& src)
{

   if(this == &src)
      return;

   ASSERT_VALID(this);

   set_size(src.m_nSize);

   CopyElements(m_pData, src.m_pData, src.m_nSize);

}

void string_array::copy(const raw_int64_array & src)
{

   ASSERT_VALID(this);

   set_size(src.m_nSize);

   for(int32_t i = 0; i < m_nSize; i++)
   {
      m_pData[i] = ::str::from(src[i]);
   }

}

void string_array::free_extra()
{
   ASSERT_VALID(this);

   if (m_nSize != m_nMaxSize)
   {
      // shrink to desired size
#ifdef SIZE_T_MAX
      ASSERT(m_nSize <= SIZE_T_MAX/sizeof(string)); // no overflow
#endif
      string* pNewData = NULL;
      if (m_nSize != 0)
      {
         pNewData = (string*) new BYTE[m_nSize * sizeof(string)];
         // copy new data from old
         memcpy(pNewData, m_pData, m_nSize * sizeof(string));
      }

      // get rid of old stuff (note: no destructors called)
      delete[] (BYTE*)m_pData;
      m_pData = pNewData;
      m_nMaxSize = m_nSize;
   }
}

/////////////////////////////////////////////////////////////////////////////

void string_array::set_at_grow(index nIndex, const char * newElement)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if (nIndex >= m_nSize)
      set_size(nIndex+1);
   m_pData[nIndex] = newElement;
}


void string_array::set_at_grow(index nIndex, const string & newElement)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if (nIndex >= m_nSize)
      set_size(nIndex+1);
   m_pData[nIndex] = newElement;
}



void string_array::InsertEmpty(index nIndex, ::count nCount)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need
   ASSERT(nCount > 0);     // zero or negative size not allowed

   if (nIndex >= m_nSize)
   {
      // adding after the end of the array
      set_size(nIndex + nCount);  // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = m_nSize;
      set_size(m_nSize + nCount);  // grow it to new size
      // shift old data up to fill gap
      memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
         (nOldSize-nIndex) * sizeof(string));

      // re-init slots we copied from

      _ConstructElements(&m_pData[nIndex], nCount);

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= m_nSize);
}


void string_array::insert_at(index nIndex, const char * newElement, ::count nCount)
{

   // make room for new elements
   InsertEmpty(nIndex, nCount);



   // copy elements into the is_empty space
   string temp = newElement;
   while (nCount--)
      m_pData[nIndex++] = temp;

}


void string_array::insert_at(index nIndex, const string & newElement, ::count nCount)
{
   // make room for new elements
   InsertEmpty(nIndex, nCount);

   // copy elements into the is_empty space
   while (nCount--)
      m_pData[nIndex++] = newElement;
}


void string_array::remove_at(index nIndex, ::count nCount)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);
   ASSERT(nCount >= 0);
   ASSERT(nIndex + nCount <= m_nSize);

   // just remov a range
   ::count nMoveCount = m_nSize - (nIndex + nCount);

   _DestructElements(&m_pData[nIndex], nCount);

   if (nMoveCount)
      memmove(&m_pData[nIndex], &m_pData[nIndex + nCount],
         nMoveCount * sizeof(string));
   m_nSize -= nCount;
}

void string_array::insert_at(index nStartIndex, const string_array & NewArray)
{
   ASSERT_VALID(this);
   ASSERT(&NewArray != NULL);
//   ASSERT_KINDOF(string_array, &NewArray);
   ASSERT_VALID(&NewArray);
   ASSERT(nStartIndex >= 0);

   if (NewArray.get_size() > 0)
   {
      insert_at(nStartIndex, NewArray.get_at(0), NewArray.get_size());
      for (int32_t i = 0; i < NewArray.get_size(); i++)
         set_at(nStartIndex + i, NewArray.get_at(i));
   }
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

/*void string_array::Serialize(CArchive& ar)
{
   ASSERT_VALID(this);

   object::Serialize(ar);

   if (ar.IsStoring())
   {
      ar.WriteCount(m_nSize);
      for (int32_t i = 0; i < m_nSize; i++)
         ar << m_pData[i];
   }
   else
   {
      uint32_t nOldSize = ar.ReadCount();
      set_size(nOldSize);
      for (int32_t i = 0; i < m_nSize; i++)
         ar >> m_pData[i];
   }
}
*/




void string_array::quick_sort(
      void swap(void * lpVoidSwapArg, const index, const index),
      void * lpvoidSwapArg,
      bool bNoCase)
{
   raw_index_array stackLowerBound;
   raw_index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   string t;

   if(this->get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(this->get_size() - 1);
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if((bNoCase && this->element_at(iMPos).CompareNoCase(this->element_at(iUPos)) <= 0) ||
                  (!bNoCase && this->element_at(iMPos).CompareNoCase(this->element_at(iUPos)) <= 0))
                  iUPos--;
               else
               {
                  t = get_at(iMPos);
                  set_at(iMPos, get_at(iUPos));
                  set_at(iUPos, t);
                  if(swap != NULL)
                  {
                     swap(lpvoidSwapArg, iUPos, iMPos);
                  }
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;

               if((bNoCase && this->element_at(iLPos).CompareNoCase(this->element_at(iMPos)) <= 0) ||
                  (!bNoCase && this->element_at(iLPos).CompareNoCase(this->element_at(iMPos)) <= 0))
                  iLPos++;
               else
               {
                  t = get_at(iLPos);
                  set_at(iLPos, get_at(iMPos));
                  set_at(iMPos, t);
                  if(swap != NULL)
                  {
                     swap(lpvoidSwapArg, iLPos, iMPos);
                  }
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}


string_array string_array::slice(index start, ::count count)
{
   string_array stra;
   if(start < 0)
   {
      start += this->get_count();
   }
   index last;
   if(count < 0)
   {
      last = this->get_count() - count;
   }
   else
   {
      last = start + count - 1;
   }
   for(index i = start; i <= last; i++)
   {
      stra.add(this->element_at(i));
   }
   return stra;
}


// IMPLEMENT_SERIAL(string_array, object, 0)


string_array & string_array::operator =(const string_array & tokena)
{
   copy(tokena);
   return *this;
}

index string_array::add_new(const char * psz, index i)
{
   if(i == -1)
   {
      return add(string(psz));
   }
   else
   {
      insert_at(i, string(psz));
      return i;
   }
}


string & string_array::new_element(index i)
{
   add_new(NULL, i);
   if(i == -1)
   {
      return last_element();
   }
   else
   {
      return this->element_at(i);
   }
}

index string_array::add(const char * psz)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, psz);
   return nIndex;
}

index string_array::add(const wchar_t * pwsz)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, ::str::international::unicode_to_utf8(pwsz));
   return nIndex;
}


index string_array::add(char ch)
{
   if(ch == '\0')
      return add("");
   else
   {
      char str[16];
      str[0] = ch;
      str[1] = '\0';
      return add(str);
   }
}

index string_array::add(wchar_t wch)
{
   if(wch == L'\0')
      return add("");
   else
   {
      wchar_t wstr[16];
      wstr[0] = wch;
      wstr[1] = L'\0';
      return add(wstr);
   }
}

index string_array::add(const string & newElement)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, newElement);
   return nIndex;
}

void string_array::push_back(const string & newElement)
{
   index nIndex = m_nSize;
   set_at_grow(nIndex, newElement);
}


void string_array::add(const id & id)
{
   if(id.is_null())
   {
   }
   else
   {
      add(id);
   }
}




// same as clear
void string_array::remove_all()
{
   set_size(0);
}

// same as remove all
void string_array::clear()
{
   set_size(0);
}

 string string_array::get_at(index nIndex) const
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      return m_pData[nIndex]; }
 void string_array::set_at(index nIndex, const char * newElement)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      m_pData[nIndex] = newElement; }

 void string_array::set_at(index nIndex, const string & newElement)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      m_pData[nIndex] = newElement; }

 string & string_array::element_at(index nIndex)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      return m_pData[nIndex]; }

 const string & string_array::element_at(index nIndex) const
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      return m_pData[nIndex]; }

 const string* string_array::get_data() const
   { return (const string*)m_pData; }
 string* string_array::get_data()
   { return (string*)m_pData; }


 string string_array::operator[](index nIndex) const
   { return get_at(nIndex); }
 string & string_array::operator[](index nIndex)
   { return this->element_at(nIndex); }




 void string_array::add_tokens(const char * lpcsz,const char * lpcszSeparator,bool bAddEmpty)
 {
    ::str::tokenizer strTokenizer(lpcsz);
    string strToken;
    if(bAddEmpty)
    {
       while(strTokenizer.GetNextToken(strToken,lpcszSeparator,FALSE))
       {
          string_array::add(strToken);
       }
    }
    else
    {
       while(strTokenizer.GetNextToken(strToken,lpcszSeparator,FALSE))
       {
          if(!strToken.is_empty())
             string_array::add(strToken);
       }
    }
 }

 int32_t g_add_smallest_tokens = 0;

 void string_array::add_smallest_tokens(const char * lpcsz,string_array & straSeparator,bool bAddEmpty,bool bWithSeparator)
 {
    ::str::tokenizer strTokenizer(lpcsz);
    string strToken;
    if(bAddEmpty)
    {
       while(strTokenizer.GetNextSmallestToken(strToken,straSeparator,bWithSeparator))
       {
          string_array::add(strToken);
       }
    }
    else
    {
       while(strTokenizer.GetNextSmallestToken(strToken,straSeparator,bWithSeparator))
       {
          if(!strToken.is_empty())
             string_array::add(strToken);
       }
    }
 }


 void string_array::add_lines(const string & str)
 {

    string_array straSeparator;

    straSeparator.add("\r");

    straSeparator.add("\n");

    straSeparator.add("\r\n");

    add_smallest_tokens(str,straSeparator,true,false);

 }


 void string_array::get_format_string(string & str,const char * lpcszSeparator) const
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




 index string_array::add_unique(const char * lpcsz)
 {
    index find = find_first(lpcsz);
    if(find >= 0)
       return -1;
    return string_array::add(lpcsz);
 }

 ::count string_array::add_unique(const string_array & stra)
 {
    ::count count = 0;
    for(int32_t i = 0; i < stra.get_size(); i++)
    {
       if(add_unique(stra[i]) >= 0)
          count++;
    }
    return count;
 }

 index string_array::add_unique_ci(const char * lpcsz)
 {
    index find = find_first_ci(lpcsz);
    if(find >= 0)
       return -1;
    return string_array::add(lpcsz);
 }

 ::count string_array::add_unique_ci(const string_array & stra)
 {
    ::count count = 0;
    for(int32_t i = 0; i < stra.get_size(); i++)
    {
       if(add_unique_ci(stra[i]) >= 0)
          count++;
    }
    return count;
 }

 index string_array::find_first_ci(const char * lpcsz,index find,index last) const
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

 index string_array::find_first(const char * lpcsz,index find,index last) const
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


 index string_array::reverse_find_ci(const char * lpcsz,index find,index last) const
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

 index string_array::reverse_find(const char * lpcsz,index find,index last) const
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

 index string_array::find_first_begins_ci(const char * lpcsz,index find,index last) const
 {
    if(find < 0)
       find += this->get_count();
    if(last < 0)
       last += this->get_count();
    for(; find < this->get_count(); find++)
    {
       if(::str::begins_ci(this->element_at(find),lpcsz))
          return find;
    }
    return -1;
 }

 index string_array::find_first_begins(const char * lpcsz,index find,index last) const
 {
    if(find < 0)
       find += this->get_count();
    if(last < 0)
       last += this->get_count();
    for(; find < this->get_count(); find++)
    {
       if(::str::begins(this->element_at(find),lpcsz))
          return find;
    }
    return -1;
 }

 index string_array::str_find_first_begins_ci(const char * lpcsz,index find,index last) const
 {
    if(find < 0)
       find += this->get_count();
    if(last < 0)
       last += this->get_count();
    for(; find < this->get_count(); find++)
    {
       if(::str::begins_ci(lpcsz,this->element_at(find)))
          return find;
    }
    return -1;
 }

 index string_array::str_find_first_begins(const char * lpcsz,index find,index last) const
 {
    if(find < 0)
       find += this->get_count();
    if(last < 0)
       last += this->get_count();
    for(; find < this->get_count(); find++)
    {
       if(::str::begins(lpcsz,this->element_at(find)))
          return find;
    }
    return -1;
 }


 bool string_array::contains_ci(const char * lpcsz,index find,index last,::count countMin,::count countMax) const
 {
    ::count count = 0;
    while((count < countMin || (countMax >= 0 && count <= countMax))
       && (find = find_first_ci(lpcsz,find,last)) >= 0)
       count++;
    return count >= countMin && conditional(countMax >= 0,count <= countMax);
 }

 bool string_array::contains(const char * lpcsz,index find,index last,::count countMin,::count countMax) const
 {
    ::count count = 0;
    while((count < countMin || (countMax >= 0 && count <= countMax))
       && (find = find_first(lpcsz,find,last)) >= 0)
       count++;
    return count >= countMin && conditional(countMax >= 0,count <= countMax);
 }


 index string_array::remove_first_ci(const char * lpcsz,index find,index last)
 {
    if((find = find_first_ci(lpcsz,find,last)) >= 0)
       remove_at(find);
    return find;
 }

 index string_array::remove_first(const char * lpcsz,index find,index last)
 {
    if((find = find_first(lpcsz,find,last)) >= 0)
       remove_at(find);
    return find;
 }

 ::count string_array::remove_ci(const char * lpcsz,index find,index last,::count countMin,::count countMax)
 {
    ::count count = 0;
    if(contains_ci(lpcsz,find,last,countMin,countMax))
    while(conditional(countMax >= 0,count < countMax)
       && (find = remove_first_ci(lpcsz,find,last)) >= 0)
       count++;
    return count;
 }

 ::count string_array::remove(const char * lpcsz,index find,index last,::count countMin,::count countMax)
 {
    ::count count = 0;
    if(contains(lpcsz,find,last,countMin,countMax))
    while(conditional(countMax >= 0,count < countMax)
       && (find = remove_first(lpcsz,find,last)) >= 0)
       count++;
    return count;
 }

 ::count string_array::remove_ci(const string_array & stra)
 {
    ::count count = 0;
    for(int32_t i = 0; i < stra.get_size(); i++)
    {
       count += remove_ci(stra[i]);
    }
    return count;
 }

 ::count string_array::remove(const string_array & stra)
 {
    ::count count = 0;
    for(int32_t i = 0; i < stra.get_size(); i++)
    {
       count += remove(stra[i]);
    }
    return count;
 }

 void string_array::trim_left(const char * pszChars)
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim_left(pszChars);
    }
 }

 void string_array::trim_right(const char * pszChars)
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim_right(pszChars);
    }
 }

 void string_array::trim(const char * pszChars)
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim(pszChars);
    }
 }


 void string_array::trim_left()
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim_left();
    }
 }

 void string_array::trim_right()
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim_right();
    }
 }

 void string_array::trim()
 {
    for(int32_t i = 0; i < m_nSize; i++)
    {
       operator[](i).trim();
    }
 }

 index string_array::add_normal(const char * lpcsz)
 {
    return string_array::add(lpcsz);
 }

 ::count string_array::remove_empty()
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

 primitive::memory string_array::GetFormatV004()
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

    char * lpsz = (char *)mem.get_data();

    memset(lpsz,0x00,iTotalLength * sizeof(char));

    char * lpszN = lpsz;

    strsize iLength;

    for(i = 0; i < m_nSize; i++)
    {

       string * pstr = &this->element_at(i);

       iLength = pstr->get_length();

#ifdef WINDOWS
       strcat_s(lpszN,iLength,*pstr);
#else
       strcat(lpszN,*pstr);
#endif

#ifdef WINDOWSEX
       iLength = _tcsnbcnt(lpszN,iLength);
#elif defined(METROWINDOW)
       iLength = wcsnbcnt(lpszN,iLength);
#else
       iLength = strlen(lpszN);
#endif

       lpszN = (char *)((LPBYTE)lpszN) + iLength + sizeof(char);

    }

    if(iTotalLength == 2)
    {
       memset(lpsz,0x00,iTotalLength * sizeof(char));
    }
    else
    {
       memset(lpszN,0x00,sizeof(char));
    }

    return mem;

 }




 string_array & string_array::operator =(const raw_int64_array & ia)
 {
    copy(ia);
    return *this;
 }
 void string_array::implode(string & str,const char * lpcszSeparator,index start,::count count) const
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

 string string_array::implode(const char * lpcszSeparator,index iStart,index iEnd) const
 {
    string str;
    implode(str,lpcszSeparator,iStart,iEnd);
    return str;
 }


 void string_array::reverse_implode(string & str,const char * lpcszSeparator,index start,::count count) const
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

 string string_array::reverse_implode(const char * lpcszSeparator,index iStart,index iEnd) const
 {
    string str;
    reverse_implode(str,lpcszSeparator,iStart,iEnd);
    return str;
 }

 string_array & string_array::explode(const string & strSeparator,const string & str)
 {

    remove_all();

    add_tokens(str,strSeparator,true);

    return * this;

 }


 string_array & string_array::csstidy_explode_ws(char sep,const char * psz)
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
          if(istring[i] == sep && !::str::simple_escaped(istring,i))
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

 void string_array::replace(const char * lpszSearch,const char * lpszReplace)
 {
    for(int32_t i = 0; i < this->get_size(); i++)
    {
       this->element_at(i).replace(lpszSearch,lpszReplace);
    }
 }


 void string_array::surround(const char * pszPrefix,const char * pszSuffix,index iStart,::count iCount)
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

 string string_array::surround_and_implode(const char * pszSeparator,const char * pszPrefix,const char * pszSuffix,index iStart,::count iCount)
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

 string_array & string_array::operator -=(const string_array & stra)
 {
    remove(stra);
    return *this;
 }

 string_array & string_array::operator +=(const string_array & stra)
 {
    add(stra);
    return *this;
 }

 string_array string_array::operator -(const string_array & straParam) const
 {
    string_array stra(*this);
    stra -= straParam;
    return stra;
 }

 string_array string_array::operator +(const string_array & straParam) const
 {
    string_array stra(*this);
    stra += straParam;
    return stra;
 }

 bool string_array::move_ci(const char * lpcsz,index iIndex)
 {
    index i = find_first_ci(lpcsz);
    if(i < 0)
       return false;
    remove_at(i);
    insert_at(iIndex,lpcsz);
    return true;
 }

 bool string_array::preferred(const char * lpcsz)
 {
    return move_ci(lpcsz,0);
 }

 ::count string_array::preferred(string_array & stra)
 {
    ::count count = 0;
    for(index i = stra.get_upper_bound(); i >= 0; i--)
    {
       if(preferred(stra[i]))
          count++;
    }
    return count;
 }


 string string_array::pop(index i)
 {
    i = get_upper_bound(i);
    string strRet = this->element_at(i);
    remove_at(i);
    return strRet;
 }

 void string_array::slice(string_array & stra,index iOffset,::count count)
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

 void string_array::remove(index iOffset,::count count)
 {
    for(index i = iOffset + count - 1; i >= iOffset; i--)
    {
       remove_at(i);
    }
 }


 void string_array::splice(const string_array & stra,index iOffset,::count count)
 {

    remove(iOffset,count);

    insert_at(iOffset,stra);

 }


 void string_array::splice(const string_array & stra,index iOffset,string_array & straRemoved,::count count)
 {

    slice(straRemoved,iOffset,count);

    remove(iOffset,count);

    insert_at(iOffset,stra);

 }


 bool string_array::is_empty(::count countMinimum)
 {
    return this->get_size() < countMinimum;
 }

 bool string_array::has_elements(::count countMinimum)
 {
    return this->get_count() >= countMinimum;
 }


 ::count string_array::get_begins_ci(string_array & stra,const char * lpcsz,index first,index last)
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
       iFind = find_first_begins_ci(lpcsz,i,last);
       if(iFind < 0)
          return count;
       stra.add(this->element_at(iFind));
       i = iFind + 1;
       count++;
    }
 }

 ::count string_array::filter_begins_ci(const char * lpcsz,index first,index last)
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
       iFind = find_first_begins_ci(lpcsz,i,last);
       if(iFind < 0)
       {
          remove_at(i,last - i + 1);
          return count;
       }
       remove_at(i,iFind - i);
       last -= iFind - i;
       i++;
       count++;

    }
 }

 index string_array::get_random_index() const
 {
    if(this->get_size() <= 0)
       return -1;
    return (index)(rand() % get_size());
 }

 string & string_array::random_element()
 {
    if(this->get_size() <= 0)
       throw "invalid call";
    return this->element_at(get_random_index());
 }

 const string & string_array::random_element() const
 {
    if(this->get_size() <= 0)
       throw "invalid call";
    return this->element_at(get_random_index());
 }

 string string_array::pop_random_element()
 {
    if(this->get_size() <= 0)
       throw "invalid call";
    index i = get_random_index();
    string str = this->element_at(i);
    remove_at(i);
    return str;
 }



 void string_array::make_lower()
 {
    for(index i = 0; i < this->get_count(); i++)
    {
       this->element_at(i).make_lower();
    }
 }

 void string_array::make_upper()
 {
    for(index i = 0; i < this->get_count(); i++)
    {
       this->element_at(i).make_upper();
    }
 }



 string string_array::encode_v16()
 {
    string strEncode;
    for(int32_t ui = 0; ui < this->get_count(); ui++)
    {
       string & str = this->element_at(ui);
       strEncode += hex::lower_from((const char*)str,str.get_length());
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



 void string_array::decode_v16(const char * psz)
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
       int32_t iConversion = ::atoi_dup(sz,&pszEnd,16);
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
             str = (char *)memory_alloc(iSize);
          }
          else if(iSize < (strlen_dup(str) + 1))
          {
             char * strOld = str;
             iSize += 1024;
             char * strNew = (char *)memory_alloc(iSize);
             strcpy_dup(strNew,strOld);
             str = strNew;
          }
          sz[0] = ch;
          sz[1] = '\0';
          strcat_dup(str,sz);
       }
       psz++;
    }

 }


 ::count string_array::get_count_except(const string & str)
 {

    ::count c = get_count();

    for(index i = 0; i < get_count(); i++)
    {

       if(element_at(i) == str)
          c--;

    }

    return c;

 }

 ::count string_array::get_count_except(const string_array & stra)
 {

    ::count c = get_count();

    for(index i = 0; i < get_count(); i++)
    {

       if(stra.contains(element_at(i)))
          c--;

    }

    return c;

 }


 ::count string_array::get_count_except_ci(const string & str)
 {

    ::count c = get_count();

    for(index i = 0; i < get_count(); i++)
    {

       if(element_at(i).CompareNoCase(str) == 0)
          c--;

    }

    return c;

 }

 ::count string_array::get_count_except_ci(const string_array & stra)
 {

    ::count c = get_count();

    for(index i = 0; i < get_count(); i++)
    {

       if(stra.contains_ci(element_at(i)))
          c--;

    }

    return c;

 }


 string string_array::get_json()
 {

    string str("[");

    for(index i = 1; i < get_count(); i++)
    {
       if(i > 0)
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