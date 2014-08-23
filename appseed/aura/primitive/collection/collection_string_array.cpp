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
         nGrowBy = MIN(1024, MAX(4, m_nSize / 8));
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

void string_array::copy(const int64_array & src)
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



void string_array::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << m_nSize << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      for (int32_t i = 0; i < m_nSize; i++)
         dumpcontext << "\n\t[" << i << "] = " << m_pData[i];
   }

   dumpcontext << "\n";
}

void string_array::assert_valid() const
{
   object::assert_valid();

   if (m_pData == NULL)
   {
      ASSERT(m_nSize == 0);
      ASSERT(m_nMaxSize == 0);
   }
   else
   {
      ASSERT(m_nSize >= 0);
      ASSERT(m_nMaxSize >= 0);
      ASSERT(m_nSize <= m_nMaxSize);
      ASSERT(__is_valid_address(m_pData, m_nMaxSize * sizeof(string)));
   }
}


void string_array::quick_sort(
      void swap(void * lpVoidSwapArg, const index, const index),
      void * lpvoidSwapArg,
      bool bNoCase)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
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

void string_array::get_quick_sort_ci(index_array & ia)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   string t;
   ia.remove_all();
   ia.append_sequence(0, get_upper_bound());
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
               if(this->element_at(ia[iMPos]).CompareNoCase(this->element_at(ia[iUPos])) <= 0)
                  iUPos--;
               else
               {
                  index i = ia[iMPos];
                  ia[iMPos] = ia[iUPos];
                  ia[iUPos] = i;
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

               if(this->element_at(ia[iLPos]).CompareNoCase(this->element_at(ia[iMPos])) <= 0)
                  iLPos++;
               else
               {
                  index i = ia[iLPos];
                  ia[iLPos] = ia[iMPos];
                  ia[iMPos] = i;
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

void string_array::add(const var & var)
{
   if(var.is_empty())
   {
   }
   else if(var.get_type() == var::type_stra)
   {
      add(var.stra());
   }
   else if(var.cast < string_array >() != NULL)
   {
      add(*var.cast < string_array >());
   }
   else if(var.get_type() == var::type_vara)
   {
      for(int32_t i = 0; i < var.vara().get_count(); i++)
      {
         add(var.vara()[i].get_string());
      }
   }
   else if(var.get_type() == var::type_inta)
   {
      for(int32_t i = 0; i < var.inta().get_count(); i++)
      {
         add(::str::from(var.inta()[i]));
      }
   }
   else if(var.get_type() == var::type_propset)
   {
      for(int32_t i = 0; i < var.propset().m_propertya.get_count(); i++)
      {
         add(var.propset().m_propertya[i].get_value().get_string());
      }
   }
   else
   {
      add(var.get_string());
   }
}

void string_array::add(const property & prop)
{
   add(prop.get_value());
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


