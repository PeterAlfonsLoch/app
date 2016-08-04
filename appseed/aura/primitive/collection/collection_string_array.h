#pragma once


template < typename Type, typename RawType >
class string_array :
   virtual public array < Type >,
   virtual public ::file::serializable
{
public:


   typedef Type                           String;
   typedef RawType                        RawString;
   typedef string_array < RawType >       RawStringArray;


   string_array() {}
   string_array(::aura::application * papp);
   string_array(::std::initializer_list < Type > l) {   for(auto & e : l) {    add(e);    }  }
   string_array(const string_array & array);
   virtual ~string_array();



   ::count get_size() const;
   ::count get_count() const;
   index get_lower_bound(index i = 0) const;
   index get_upper_bound(index i = -1) const;
   //void set_size(::count nNewSize, ::count nGrowBy = -1);

   //::count size() const;

   //void free_extra();
   //void remove_all();
   //void clear();

   Type get_at(index nIndex) const;
   void set_at(index nIndex, const char * newElement);

   void set_at(index nIndex, const Type & newElement);

   Type & element_at(index nIndex);
   const Type & element_at(index nIndex) const;

   Type & add_new(const char * psz = NULL, index i = -1);
   Type & new_element(index i = -1);

   Type & first(index count = 0);
   Type first(index count = 0) const;

   Type & last(index count = -1);
   Type last(index count = -1) const;

   const Type* get_data() const;
   Type* get_data();

   // Potentially growing the array
   Type & set_at_grow(index nIndex, const char * newElement);

   Type & set_at_grow(index nIndex,const Type & newElement);

   index add(const char * psz);

   index add(const unichar * pwsz);

   index add(char ch);

   index add(unichar wch);

   void add(const var & var);

   void add(const property & prop);

   void add(const id & id);

   Type & add(const Type & newElement);

   void push_back(const Type & newElement);

   ::count add(const string_array & src);

   void copy(const string_array & src);
   void copy(const int64_array & src);



   // overloaded operator helpers
   Type operator[](index nIndex) const;
   Type & operator[](index nIndex);

   // Operations that move elements around
   Type & insert_at(index nIndex,const Type & newElement);
   void insert_at(index nIndex,const char * newElement,::count nCount);
   void insert_at(index nIndex,const Type & newElement,::count nCount);
   void insert_at(index nStartIndex, const string_array & NewArray);

   void quick_sort(
      void swap(void * lpVoidSwapArg, const index, const index) = NULL,
      void * lpvoidSwapArg = NULL,
      bool bNoCase = false);

   void get_quick_sort_ci(index_array & ia);

   string_array slice(index iStart, ::count iCount = -1) const;

   string_array & operator =(const string_array & stra);


   Type & insert_empty(index nIndex);

   void insert_empty(index nIndex, ::count c);


   class ::memory GetFormatV004();
   ::count remove_empty();
   index add_normal(const char * lpcsz);
   void trim_right(const char * pszChars);
   void trim_left(const char * pszChars);
   void trim(const char * pszChars);
   void trim_right();
   void trim_left();
   void trim();
   index add_unique(const string & lpcsz);
   ::count add_unique(const string_array & stra);
   index add_unique_ci(const string & lpcsz);
   ::count add_unique_ci(const string_array & stra);

   void make_lower();
   void make_upper();

   operator ::count() const {
      return get_count();
   }


   index get_random_index() const;

   Type & random_element();
   const Type & random_element() const;

   Type pop_random_element();

   Type pop(index i = -1);
   void slice(string_array & stra,index index,::count ca = -1);
   void remove(index index,::count count);
   void splice(const string_array & stra,index index,::count ca = -1);
   void splice(const string_array & stra,index index,string_array & straRemoved,::count ca = -1);


   // if Type is found, move it to specified position
   bool move_ci(const char * lpcsz,index iIndex);

   // move preferred in order
   bool preferred(const char * lpcsz);
   ::count preferred(string_array & stra);

   index find_first_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index find_first(const char * lpcsz,index find = 0,index last = -1) const;

   index reverse_find_ci(const char * lpcsz,index find = -1,index last = 0) const;
   index reverse_find(const char * lpcsz,index find = -1,index last = 0) const;

   bool begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   bool begins(const char * lpcsz, index find = 0, index last = -1) const;

   index find_first_begins_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index find_first_begins(const Type & strPrefix,index find = 0,index last = -1) const;

   bool str_begins_ci(const char * lpcsz, index find = 0, index last = -1) const;
   bool str_begins(const char * lpcsz, index find = 0, index last = -1) const;

   index str_find_first_begins_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index str_find_first_begins(const char * lpcsz,index find = 0,index last = -1) const;

   index find_first_begins_eat_ci(string & str,const char * lpcsz, index find = 0,index last = -1) const;

   bool contains_ci(const char * lpcsz,index find = 0,index last = -1,::count countMin = 1,::count countMax = -1) const;
   bool contains(const char * lpcsz,index find = 0,index last = -1,::count countMin = 1,::count countMax = -1) const;

   ::count get_begins_ci(string_array & stra,const char * lpcsz,index first = 0,index last = -1);

   ::count filter_begins_ci(const char * lpcsz,index first = 0,index last = -1);

   template < typename Pred >
   ::count filter(Pred pred,index first = 0,index last = -1);

   template < typename Pred >
   ::count filter_out(Pred pred,index first = 0,index last = -1);

   template < typename Pred, typename ArrayOut >
   ::count filter_out(Pred pred, ArrayOut & a, index first = 0,index last = -1);

   ::count remove_first_ci(const string & lpcsz,index find = 0,index last = -1);
   ::count remove_first(const string & lpcsz,index find = 0,index last = -1);

   ::count remove_ci(const string & lpcsz,index find = 0,index last = -1,::count countMin = 0,::count countMax = -1);
   ::count remove(const string & lpcsz,index find = 0,index last = -1,::count countMin = 0,::count countMax = -1);

   ::count remove_ci(const string_array & stra);
   ::count remove(const string_array & stra);

   string_array & explode(const Type & strSeparator,const Type & str);

   // csstidy: Same as explode, but not within a Type
   string_array & csstidy_explode_ws(char sep,const char * psz);

   void implode(Type & rwstr,const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   Type implode(const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   void reverse_implode(Type & rwstr,const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   Type reverse_implode(const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;

   void _008Implode(Type & rwstr, const char * lpcszSeparator = NULL, const char * lpcszLastSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   Type _008Implode(const char * lpcszSeparator = NULL, const char * lpcszLastSeparator = NULL, index iStart = 0, ::count iCount = -1) const;

   void _008IfImplode(Type & rwstr, const char * lpcszIfHasElementPrefix = NULL, const char * lpcszSeparator = NULL, const char * lpcszLastSeparator = NULL, bool bUseLast = true, index iStart = 0, ::count iCount = -1) const;
   Type _008IfImplode(const char * lpcszIfHasElementPrefix = NULL, const char * lpcszSeparator = NULL, const char * lpcszLastSeparator = NULL, bool bUseLast = true, index iStart = 0, ::count iCount = -1) const;

   void surround(const char * pszPrefix = NULL,const char * pszSuffix = NULL,index iStart = 0,::count iCount = -1);
   Type surround_and_implode(const char * lpcszSeparator = NULL,const char * pszPrefix = NULL,const char * pszSuffix = NULL,index iStart = 0,::count iCount = -1);

   comparable_array < id > get_comparable_ida() const;

   ::count explode_command_line(const Type & str,ref_array < char > * argv = NULL);



   //   void XFV001Expand();

   string_array & operator =(const var var);
//   string_array & operator =(const string_array & stra);
   string_array & operator =(const int64_array & ia);
//   string_array & operator =(const string_array & stra);
   string_array & operator -=(const string_array & stra);
   string_array & operator +=(const string_array & stra);

   string_array operator -(const string_array & stra) const;
   string_array operator +(const string_array & stra) const;
//   string_array operator -(const string_array & stra) const;
//   string_array operator +(const string_array & stra) const;


   bool operator == (const RawStringArray & a) const;
   bool operator != (const RawStringArray & a) const;


   void replace(const char * lpszSearch,const char * lpszReplace);

   void write(::file::ostream & ostream) const;
   void read(::file::istream & istream);


   void get_format_string(Type & str,const char * lpcszSeparator) const;
   void add_tokens(const char * lpcsz,const char * lpcszSeparator,bool bAddEmpty = true);
   void add_smallest_tokens(const char * lpcsz, RawStringArray & straSeparator,bool bAddEmpty = true,bool bWithSeparator = FALSE);
   void add_lines(const Type & str,bool bAddEmpty = true);


   bool is_empty(::count countMinimum = 1);
   bool has_elements(::count countMinimum = 1);

   Type encode_v16();


   void decode_v16(const char * psz);

   ::count get_count_except(const char * psz);
   ::count get_count_except(const Type & str);
   ::count get_count_except(const string_array & stra);

   ::count get_count_except_ci(const char * psz);
   ::count get_count_except_ci(const Type & str);
   ::count get_count_except_ci(const string_array & stra);

   Type & get_json(Type & str, bool bNewLine = true) const;

   void dump(dump_context &) const;

   void assert_valid() const;

   typedef Type BASE_TYPE;

   typedef const char * BASE_ARG_TYPE;

};



static inline void ConstructElement(string * pNewData)
{
   ((string *)pNewData)->construct();
}

static inline void DestructElement(string * pOldData)
{
   pOldData->~string();
}


template < class Type, class RawType >
inline Type & string_array < Type, RawType >::last(index i)
{
   return this->element_at(get_upper_bound(i));
}

template < class Type, class RawType >
inline Type string_array < Type, RawType >::last(index count) const
{
   return this->element_at(get_upper_bound(count));
}

template < class Type, class RawType >
inline Type & string_array < Type, RawType >::first(index i)
{
   return this->element_at(get_lower_bound(i));
}

template < class Type, class RawType >
inline Type string_array < Type, RawType >::first(index count) const
{
   return this->element_at(get_lower_bound(count));
}

template < class Type, class RawType >
inline ::count string_array < Type, RawType >::get_size() const
   { return this->m_nSize; }

template < class Type, class RawType >
inline ::count string_array < Type, RawType >::get_count() const
   { return this->m_nSize; }

template < class Type, class RawType >
inline index string_array < Type, RawType >::get_lower_bound(index i) const
   { return i; }

template < class Type, class RawType >
inline index string_array < Type, RawType >::get_upper_bound(index count) const
   { return this->m_nSize + count; }








template < class Type, class RawType >
string_array < Type, RawType >::~string_array()
{
   ASSERT_VALID(this);


   //_DestructElements(this->m_pData, this->m_nSize);
   //delete[] (BYTE*)this->m_pData;
}

/*void string_array < Type, RawType >::set_size(::count nNewSize, ::count nGrowBy)
{
ASSERT_VALID(this);
ASSERT(nNewSize >= 0);

if (nGrowBy != -1)
m_nGrowBy = nGrowBy;  // set new size

if (nNewSize == 0)
{
// shrink to nothing

_DestructElements(this->m_pData, this->m_nSize);
delete[] (BYTE*)this->m_pData;
this->m_pData = NULL;
this->m_nSize = m_nMaxSize = 0;
}
else if (this->m_pData == NULL)
{
// create one with exact size
#ifdef SIZE_T_MAX
if(nNewSize > SIZE_T_MAX/sizeof(Type))
throw new memory_exception(get_app());
ASSERT(nNewSize <= SIZE_T_MAX/sizeof(Type));    // no overflow
#endif

this->m_pData = (Type*) new BYTE[nNewSize * sizeof(Type)];

_ConstructElements(this->m_pData, nNewSize);

this->m_nSize = m_nMaxSize = nNewSize;
}
else if (nNewSize <= m_nMaxSize)
{
// it fits
if (nNewSize > this->m_nSize)
{
// initialize the new elements

_ConstructElements(&this->m_pData[this->m_nSize], nNewSize-this->m_nSize);

}

else if (this->m_nSize > nNewSize)  // destroy the old elements
_DestructElements(&this->m_pData[nNewSize], this->m_nSize-nNewSize);

this->m_nSize = nNewSize;
}
else
{
// otherwise, grow array
nGrowBy = m_nGrowBy;
if (nGrowBy == 0)
{
// heuristically determine growth when nGrowBy == 0
//  (this avoids heap fragmentation in many situations)
nGrowBy = MIN(1024, MAX(4, this->m_nSize / 8));
}
::count nNewMax;
if (nNewSize < m_nMaxSize + nGrowBy)
nNewMax = m_nMaxSize + nGrowBy;  // granularity
else
nNewMax = nNewSize;  // no slush

ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
#ifdef SIZE_T_MAX
ASSERT(nNewMax <= SIZE_T_MAX/sizeof(Type)); // no overflow
#endif
Type* pNewData = (Type*) new BYTE[nNewMax * sizeof(Type)];

// copy new data from old
memcpy(pNewData, this->m_pData, this->m_nSize * sizeof(Type));

// construct remaining elements
ASSERT(nNewSize > this->m_nSize);

_ConstructElements(&pNewData[this->m_nSize], nNewSize-this->m_nSize);


// get rid of old stuff (note: no destructors called)
delete[] (BYTE*)this->m_pData;
this->m_pData = pNewData;
this->m_nSize = nNewSize;
m_nMaxSize = nNewMax;
}
}*/


template < class Type, class RawType >
::count string_array < Type, RawType >::add(const string_array < Type, RawType >& src)
{
   if(this == &src)
   {
      string_array < Type, RawType > thisCopy(src);
      return add(thisCopy);
   }
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   ::count nOldSize = this->m_nSize;
   this->set_size(this->m_nSize + src.m_nSize);

   CopyElements(&this->m_pData[nOldSize],src.m_pData,src.m_nSize);

   return nOldSize;
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::copy(const string_array < Type, RawType >& src)
{

   if(this == &src)
      return;

   ASSERT_VALID(this);

   this->set_size(src.m_nSize);

   CopyElements(this->m_pData,src.m_pData,src.m_nSize);

}


template < typename Type, typename RawType >
void string_array < Type, RawType >::copy(const int64_array & src)
{

   ASSERT_VALID(this);

   this->set_size(src.m_nSize);

   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      get_data()[i] = ::str::from(src[i]);
   }

}

/*void string_array < Type, RawType >::free_extra()
{
ASSERT_VALID(this);

if (this->m_nSize != m_nMaxSize)
{
// shrink to desired size
#ifdef SIZE_T_MAX
ASSERT(this->m_nSize <= SIZE_T_MAX/sizeof(Type)); // no overflow
#endif
Type* pNewData = NULL;
if (this->m_nSize != 0)
{
pNewData = (Type*) new BYTE[this->m_nSize * sizeof(Type)];
// copy new data from old
memcpy(pNewData, this->m_pData, this->m_nSize * sizeof(Type));
}

// get rid of old stuff (note: no destructors called)
delete[] (BYTE*)this->m_pData;
this->m_pData = pNewData;
m_nMaxSize = this->m_nSize;
}
}*/

/////////////////////////////////////////////////////////////////////////////


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::set_at_grow(index nIndex,const char * newElement)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if(nIndex >= this->m_nSize)
      this->set_size(nIndex + 1);

   return get_data()[nIndex] = newElement;

}



template < typename Type, typename RawType >
Type & string_array < Type, RawType >::set_at_grow(index nIndex,const Type & newElement)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);

   if(nIndex >= this->m_nSize)
      this->set_size(nIndex + 1);

   return get_data()[nIndex] = newElement;

}




template < typename Type, typename RawType >
void string_array < Type, RawType >::insert_empty(index nIndex,::count nCount)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need
   ASSERT(nCount > 0);     // zero or negative size not allowed

   if(nIndex >= this->m_nSize)
   {
      // adding after the end of the array
      this->set_size(nIndex + nCount);  // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = this->m_nSize;
      this->set_size(this->m_nSize + nCount);  // grow it to new size
      // shift old data up to fill gap
      memmove(&get_data()[nIndex + nCount],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(Type));

      // re-init slots we copied from
      for(index i = nIndex; i < nIndex + nCount; i++)
      {
         get_data()[i].construct();
      }

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= this->m_nSize);
}

template < typename Type,typename RawType >
Type & string_array < Type,RawType >::insert_empty(index nIndex)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1);

   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = this->m_nSize;
      this->set_size(this->m_nSize + 1);  // grow it to new size
      // shift old data up to fill gap
      memmove(&get_data()[nIndex + 1],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(Type));

      // re-init slots we copied from
      for(index i = nIndex; i < nIndex + 1; i++)
      {
         get_data()[i].construct();
      }

   }

   // insert new value in the gap
   ASSERT(nIndex + 1 <= this->m_nSize);
   return get_data()[nIndex];
}



template < typename Type,typename RawType >
Type & string_array < Type,RawType >::insert_at(index nIndex,const Type & newElement)
{

   return insert_empty(nIndex) = newElement;

}


template < typename Type, typename RawType >
void string_array < Type, RawType >::insert_at(index nIndex,const char * newElement,::count nCount)
{

   // make room for new elements
   insert_empty(nIndex,nCount);



   // copy elements into the is_empty space
   Type temp = newElement;
   while(nCount--)
      get_data()[nIndex++] = temp;

}



template < typename Type, typename RawType >
void string_array < Type, RawType >::insert_at(index nIndex,const Type & newElement,::count nCount)
{
   // make room for new elements
   insert_empty(nIndex,nCount);

   // copy elements into the is_empty space
   while(nCount--)
      get_data()[nIndex++] = newElement;
}


//void string_array < Type, RawType >::remove_at(index nIndex, ::count nCount)
//{
//   ASSERT_VALID(this);
//   ASSERT(nIndex >= 0);
//   ASSERT(nCount >= 0);
//   ASSERT(nIndex + nCount <= this->m_nSize);
//
//   // just remov a range
//   ::count nMoveCount = this->m_nSize - (nIndex + nCount);
//
//   _DestructElements(&this->m_pData[nIndex], nCount);
//
//   if (nMoveCount)
//      memmove(&this->m_pData[nIndex], &this->m_pData[nIndex + nCount],
//         nMoveCount * sizeof(Type));
//   this->m_nSize -= nCount;
//}
//

template < typename Type, typename RawType >
void string_array < Type, RawType >::insert_at(index nStartIndex,const string_array < Type, RawType > & NewArray)
{
   ASSERT_VALID(this);
   ASSERT(&NewArray != NULL);
   //   ASSERT_KINDOF(string_array < Type, RawType >, &NewArray);
   ASSERT_VALID(&NewArray);
   ASSERT(nStartIndex >= 0);

   if(NewArray.get_size() > 0)
   {
      insert_at(nStartIndex,NewArray.get_at(0),NewArray.get_size());
      for(int32_t i = 0; i < NewArray.get_size(); i++)
         set_at(nStartIndex + i,NewArray.get_at(i));
   }
}


/////////////////////////////////////////////////////////////////////////////
// Serialization

/*void string_array < Type, RawType >::Serialize(CArchive& ar)
{
ASSERT_VALID(this);

object::Serialize(ar);

if (ar.IsStoring())
{
ar.WriteCount(this->m_nSize);
for (int32_t i = 0; i < this->m_nSize; i++)
ar << this->m_pData[i];
}
else
{
uint32_t nOldSize = ar.ReadCount();
set_size(nOldSize);
for (int32_t i = 0; i < this->m_nSize; i++)
ar >> this->m_pData[i];
}
}
*/




template < typename Type, typename RawType >
void string_array < Type, RawType >::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << this->m_nSize << " elements";
   if(dumpcontext.GetDepth() > 0)
   {
      for(int32_t i = 0; i < this->m_nSize; i++)
         dumpcontext << "\n\t[" << i << "] = " << get_data()[i];
   }

   dumpcontext << "\n";
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::assert_valid() const
{
   object::assert_valid();

   if(this->m_pData == NULL)
   {
      ASSERT(this->m_nSize == 0);
      ASSERT(this->m_nMaxSize == 0);
   }
   else
   {
      ASSERT(this->m_nSize >= 0);
      ASSERT(this->m_nMaxSize >= 0);
      ASSERT(this->m_nSize <= this->m_nMaxSize);
      ASSERT(__is_valid_address(this->m_pData,this->m_nMaxSize * sizeof(Type)));
   }
}



template < typename Type, typename RawType >
void string_array < Type, RawType >::quick_sort(
   void swap(void * lpVoidSwapArg,const index,const index),
   void * lpvoidSwapArg,
   bool bNoCase)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos,iUPos,iMPos;
   Type t;

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
                  set_at(iMPos,get_at(iUPos));
                  set_at(iUPos,t);
                  if(swap != NULL)
                  {
                     swap(lpvoidSwapArg,iUPos,iMPos);
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
                  set_at(iLPos,get_at(iMPos));
                  set_at(iMPos,t);
                  if(swap != NULL)
                  {
                     swap(lpvoidSwapArg,iLPos,iMPos);
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


template < typename Type, typename RawType >
void string_array < Type, RawType >::get_quick_sort_ci(index_array & ia)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos,iUPos,iMPos;
   Type t;
   ia.remove_all();
   ::lemon::array::append_sequence(ia,(index)0,(index)get_upper_bound());
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


template < typename Type, typename RawType >
string_array < Type, RawType > string_array < Type, RawType >::slice(index start,::count count) const
{
   string_array < Type, RawType > stra;
   if(start < 0)
   {
      start += this->get_count();
   }
   index last;
   if(count < 0)
   {
      last = this->get_count() + count;
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


// IMPLEMENT_SERIAL(string_array < Type, RawType >, object, 0)



template < typename Type, typename RawType >
string_array < Type, RawType > & string_array < Type, RawType >::operator =(const string_array < Type, RawType > & tokena)
{
   copy(tokena);
   return *this;
}


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::add_new(const char * psz,index i)
{
   if(i == -1)
   {
      return add(Type(psz));
   }
   else
   {
      return insert_at(i,Type(psz));

   }
}



template < typename Type, typename RawType >
Type & string_array < Type, RawType >::new_element(index i)
{
   add_new(NULL,i);
   if(i == -1)
   {
      return last();
   }
   else
   {
      return this->element_at(i);
   }
}


template < typename Type, typename RawType >
index string_array < Type, RawType >::add(const char * psz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex,psz);
   return nIndex;
}


template < typename Type, typename RawType >
index string_array < Type, RawType >::add(const unichar * pwsz)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex,(Type)::str::international::unicode_to_utf8(pwsz));
   return nIndex;
}



template < typename Type, typename RawType >
index string_array < Type, RawType >::add(char ch)
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


template < typename Type, typename RawType >
index string_array < Type, RawType >::add(unichar wch)
{
   if(wch == L'\0')
      return add("");
   else
   {
      unichar wstr[16];
      wstr[0] = wch;
      wstr[1] = L'\0';
      return add(wstr);
   }
}


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::add(const Type & newElement)
{

   index nIndex = this->m_nSize;

   return set_at_grow(nIndex,newElement);

}


template < typename Type, typename RawType >
void string_array < Type, RawType >::push_back(const Type & newElement)
{
   index nIndex = this->m_nSize;
   set_at_grow(nIndex,newElement);
}




template < typename Type, typename RawType >
void string_array < Type, RawType >::add(const id & id)
{
   if(id.is_null())
   {
   }
   else
   {
      add(id);
   }
}




//// same as clear
//void string_array < Type, RawType >::remove_all()
//{
//   set_size(0);
//}
//
//// same as remove all
//void string_array < Type, RawType >::clear()
//{
//   set_size(0);
//}


template < typename Type, typename RawType >
Type string_array < Type, RawType >::get_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}

template < typename Type, typename RawType >
void string_array < Type, RawType >::set_at(index nIndex,const char * newElement)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType >
void string_array < Type, RawType >::set_at(index nIndex,const Type & newElement)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   get_data()[nIndex] = newElement;
}


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::element_at(index nIndex)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}


template < typename Type, typename RawType >
const Type & string_array < Type, RawType >::element_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}


template < typename Type, typename RawType >
const Type* string_array < Type, RawType >::get_data() const
{
   return (const Type*)this->m_pData;
}


template < typename Type, typename RawType >
Type* string_array < Type, RawType >::get_data()
{
   return (Type*)this->m_pData;
}



template < typename Type, typename RawType >
Type string_array < Type, RawType >::operator[](index nIndex) const
{
   return get_at(nIndex);
}


template < typename Type, typename RawType >
Type & string_array < Type, RawType >::operator[](index nIndex)
{
   return this->element_at(nIndex);
}










template <class ARRAYCOMPARE,class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
   int32_t fCompare(const char *,const char *),
   ARRAYRELATION * parelation)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos,iUPos,iMPos;
   string str;

   if(pacompare->get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(pacompare->get_size() - 1);
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
               if(fCompare(pacompare->element_at(iMPos),pacompare->element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  pacompare->swap(iMPos,iUPos);
                  parelation->swap(iMPos,iUPos);
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
               if(fCompare(pacompare->element_at(iLPos),pacompare->element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  pacompare->swap(iMPos,iLPos);
                  parelation->swap(iMPos,iLPos);
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
   //for(int32_t i = 0; i < pacompare->get_size(); i++)
   //{
   //      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}

template <class ARRAYCOMPARE,class ARRAYRELATION>
void SortEx(ARRAYCOMPARE * pacompare,
   int32_t fCompare(const unichar *,const unichar *),
   ARRAYRELATION * parelation)
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos,iUPos,iMPos;
   string str;

   if(pacompare->get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(pacompare->get_size() - 1);
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
               if(fCompare(pacompare->element_at(iMPos),pacompare->element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  pacompare->swap(iMPos,iUPos);
                  parelation->swap(iMPos,iUPos);
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
               if(fCompare(pacompare->element_at(iLPos),pacompare->element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  pacompare->swap(iMPos,iLPos);
                  parelation->swap(iMPos,iLPos);
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
   //for(int32_t i = 0; i < pacompare->get_size(); i++)
   //{
   //      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
   //}
}


typedef CLASS_DECL_AURA string_array < string > stringa;


class string2a:
   public array < stringa >
{
public:


};


template < class Type, class RawType >
inline ::count string_array < Type, RawType >::get_count_except(const char * psz)
{

   return get_count_except(Type(psz));

}

template < class Type, class RawType >
inline ::count string_array < Type, RawType > ::get_count_except_ci(const char * psz)
{

   return get_count_except_ci(Type(psz));

}









// return Type length or -1 if UNICODE Type is found in the archive
__STATIC UINT __read_string_length(::file::istream & ar);

template < class Type, class RawType >
string_array < Type, RawType > ::string_array(::aura::application * papp):
object(papp)
{
}

//template < class Type, class RawType >
//string_array < Type, RawType > ::string_array(const char * psz)
//{
//
//   add(psz);
//
//}
//
//
//template < class Type, class RawType >
//string_array < Type, RawType > ::string_array(const Type & str)
//{
//
//   add(str);
//
//}


//template < class Type, class RawType >
//string_array < Type, RawType > ::string_array(const var & var)
//{
//
//   add(var);
//
//}
//

template < class Type, class RawType >
string_array < Type, RawType > ::string_array(const string_array < Type, RawType >  &array)
{
   operator =(array);
}




template < class Type, class RawType >
void string_array < Type, RawType > ::add_tokens(const char * lpcsz,const char * lpcszSeparator,bool bAddEmpty)
{
   ::str::tokenizer strTokenizer(lpcsz);
   Type strToken;
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

extern int32_t g_add_smallest_tokens;


template < class Type, class RawType >
void string_array < Type, RawType > ::add_smallest_tokens(const char * lpcsz,string_array < RawString >  & straSeparator,bool bAddEmpty,bool bWithSeparator)
{
   ::str::tokenizer strTokenizer(lpcsz);
   Type strToken;
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



template < class Type, class RawType >
void string_array < Type, RawType > ::add_lines(const Type & str,bool bAddEmpty)
{

   strsize iPos = 0;

   strsize iFindA;

   strsize iFindB;

   strsize iFind1;

   strsize iFind2;

   do
   {

      iFindA = str.find('\n',iPos);

      if(iFindA < 0)
         goto r_only;

      iFindB = str.find('\r',iPos);

      if(iFindB < 0)
         goto n_only;

      iFind1 = MIN(iFindA,iFindB);

      iFind2 = MAX(iFindA,iFindB);

      if(iFind1 > iPos)
      {

         add((Type)RawType(&str[iPos],iFind1 - iPos));

      }
      else if(bAddEmpty)
      {

         add(Type());

      }

      if(iFind2 - iFind1 == 1)
      {

         iPos = iFind2 + 1;

      }
      else
      {

         iPos = iFind1 + 1;

      }

   } while(true);

   goto end;

n_only:

   do
   {

      iFindA = str.find('\n',iPos);

      if(iFindA < 0)
         goto end;

      if(iFindA > iPos)
      {

         add((Type)RawType(&str[iPos],iFindA - iPos));

      }
      else if(bAddEmpty)
      {

         add(Type());

      }

      iPos = iFindA + 1;


   } while(true);
   goto end;
r_only:
   do
   {

      iFindB = str.find('\r',iPos);

      if(iFindB < 0)
         goto end;

      if(iFindB > iPos)
      {

         add((Type)RawType(&str[iPos],iFindA - iPos));

      }
      else if(bAddEmpty)
      {

         add(Type());

      }

      iPos = iFindB + 1;


   } while(true);

end:

   if(str.get_length() > iPos)
   {

      add((Type)RawType(&str[iPos],str.get_length() - iPos));

   }
   else if(bAddEmpty)
   {

      add(Type());

   }



}





template < class Type, class RawType >
void string_array < Type, RawType > ::get_format_string(Type & str,const char * lpcszSeparator) const
{
   str.Empty();
   if(this->m_nSize > 0)
   {
      str = get_at(0);
   }
   for(int32_t i = 1; i < this->m_nSize; i++)
   {
      str += lpcszSeparator + get_at(i);
   }
}






/*void string_array < Type, RawType > ::XFV001Expand()
{
string_array < Type, RawType >  strArray;
uint_array dwa;
for(int32_t i = 0; i < this->m_nSize; i++)
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
Sort(string_array < Type, RawType > ::Compare);

}*/


template < class Type, class RawType >
index string_array < Type, RawType > ::add_unique(const string & lpcsz)
{

   index find = find_first(lpcsz);

   if(find >= 0)
      return -1;

   string_array::add((const Type &) lpcsz);

   return get_upper_bound();

}


template < class Type, class RawType >
::count string_array < Type, RawType > ::add_unique(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      if(add_unique(stra[i]) >= 0)
         count++;
   }
   return count;
}


template < class Type, class RawType >
index string_array < Type, RawType > ::add_unique_ci(const string & lpcsz)
{

   index find = find_first_ci(lpcsz);

   if(find >= 0)
      return -1;

   string_array::add((Type)lpcsz);

   return get_upper_bound();

}


template < class Type, class RawType >
::count string_array < Type, RawType > ::add_unique_ci(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      if(add_unique_ci(stra[i]) >= 0)
         count++;
   }
   return count;
}


template < class Type, class RawType >
index string_array < Type, RawType > ::find_first_ci(const char * lpcsz,index find,index last) const
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


template < class Type, class RawType >
index string_array < Type, RawType > ::find_first(const char * lpcsz,index find,index last) const
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



template < class Type, class RawType >
index string_array < Type, RawType > ::reverse_find_ci(const char * lpcsz,index find,index last) const
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


template < class Type, class RawType >
index string_array < Type, RawType > ::reverse_find(const char * lpcsz,index find,index last) const
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


template < class Type, class RawType >
bool string_array < Type, RawType > ::str_begins_ci(const char * lpcsz, index find, index last) const
{
   return str_find_first_begins_ci(lpcsz, find, last) >= 0;
}

template < class Type, class RawType >
bool string_array < Type, RawType > ::str_begins(const char * lpcsz, index find, index last) const
{
   return str_find_first_begins(lpcsz, find, last) >= 0;
}

template < class Type, class RawType >
bool string_array < Type, RawType > ::begins_ci(const char * lpcsz, index find, index last) const
{
   return find_first_begins_ci(lpcsz, find, last) >= 0;
}

template < class Type, class RawType >
bool string_array < Type, RawType > ::begins(const char * lpcsz, index find, index last) const
{
   return find_first_begins(lpcsz, find, last) >= 0;
}

template < class Type, class RawType >
index string_array < Type, RawType > ::find_first_begins_ci(const char * lpcsz,index find,index last) const
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


template < class Type,class RawType >
index string_array < Type,RawType > ::find_first_begins_eat_ci(string & str,const char * lpcsz, index find,index last) const
{
   
   find  = find_first_begins_ci(lpcsz,find,last);

   if(find < 0)
      return find;

   str = element_at(find).Mid(strlen(lpcsz));

   return find;

}


template < class Type, class RawType >
index string_array < Type, RawType > ::find_first_begins(const Type & strPrefix,index find,index last) const
{
   if(find < 0)
      find += this->get_count();
   if(last < 0)
      last += this->get_count();
   for(; find < this->get_count(); find++)
   {
      if(::str::begins(this->element_at(find),strPrefix))
         return find;
   }
   return -1;
}


template < class Type, class RawType >
index string_array < Type, RawType > ::str_find_first_begins_ci(const char * lpcsz,index find,index last) const
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


template < class Type, class RawType >
index string_array < Type, RawType > ::str_find_first_begins(const char * lpcsz,index find,index last) const
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



template < class Type, class RawType >
bool string_array < Type, RawType > ::contains_ci(const char * lpcsz,index find,index last,::count countMin,::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first_ci(lpcsz,find,last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0,count <= countMax);
}


template < class Type, class RawType >
bool string_array < Type, RawType > ::contains(const char * lpcsz,index find,index last,::count countMin,::count countMax) const
{
   ::count count = 0;
   while((count < countMin || (countMax >= 0 && count <= countMax))
      && (find = find_first(lpcsz,find,last)) >= 0)
      count++;
   return count >= countMin && conditional(countMax >= 0,count <= countMax);
}



template < class Type, class RawType >
index string_array < Type, RawType > ::remove_first_ci(const string & lpcsz,index find,index last)
{
   if((find = find_first_ci(lpcsz,find,last)) >= 0)
      this->remove_at(find);
   return find;
}


template < class Type, class RawType >
index string_array < Type, RawType > ::remove_first(const string & lpcsz,index find,index last)
{
   if((find = find_first(lpcsz,find,last)) >= 0)
      this->remove_at(find);
   return find;
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::remove_ci(const string & lpcsz,index find,index last,::count countMin,::count countMax)
{
   ::count count = 0;
   if(contains_ci(lpcsz,find,last,countMin,countMax))
      while(conditional(countMax >= 0,count < countMax)
         && (find = remove_first_ci(lpcsz,find,last)) >= 0)
         count++;
   return count;
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::remove(const string & lpcsz,index find,index last,::count countMin,::count countMax)
{
   ::count count = 0;
   if(contains(lpcsz,find,last,countMin,countMax))
      while(conditional(countMax >= 0,count < countMax)
         && (find = remove_first(lpcsz,find,last)) >= 0)
         count++;
   return count;
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::remove_ci(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      count += remove_ci(stra[i]);
   }
   return count;
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::remove(const string_array & stra)
{
   ::count count = 0;
   for(int32_t i = 0; i < stra.get_size(); i++)
   {
      count += remove(stra[i]);
   }
   return count;
}


template < class Type, class RawType >
void string_array < Type, RawType > ::trim_left(const char * pszChars)
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim_left(pszChars);
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::trim_right(const char * pszChars)
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim_right(pszChars);
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::trim(const char * pszChars)
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim(pszChars);
   }
}



template < class Type, class RawType >
void string_array < Type, RawType > ::trim_left()
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim_left();
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::trim_right()
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim_right();
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::trim()
{
   for(int32_t i = 0; i < this->m_nSize; i++)
   {
      operator[](i).trim();
   }
}


template < class Type, class RawType >
index string_array < Type, RawType > ::add_normal(const char * lpcsz)
{
   return string_array::add(lpcsz);
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::remove_empty()
{
   ::count count = 0;
   for(index i = 0; i < this->get_size();)
   {
      if(this->element_at(i).is_empty())
      {
         this->remove_at(i);
         count++;
      }
      else
      {
         i++;
      }
   }
   return count;
}






template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::operator =(const int64_array & ia)
{
   copy(ia);
   return *this;
}


/*int32_t string_array < Type, RawType > ::CountPrefixNoCase(const char * lpcszPrefix)
{
Type str;
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
Type & strLeft = this->element_at(i).Left(iLen);
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

/*void string_array < Type, RawType > ::ExtractPrefixNoSortNoCase(
string_array < Type, RawType >  &stra,
const char * lpcsz,
int32_t iLength,
int32_t iMinLength)
{
ASSERT(iLength >= iMinLength);
remove_all();
Type str;
if(lpcsz != NULL)
str = lpcsz;
if(str.is_empty())
{
for(int32_t i = 0; i < stra.get_size(); i++)
{
Type & strMid = stra[i].Left(iLength);
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
int32_t iLen = MAX(str.get_length(), iMinLength);
for(int32_t i = 0; i < stra.get_size(); i++)
{
Type & strMid = stra[i].Left(iLength);
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

int32_t string_array < Type, RawType > ::FindFirstNoSortNoCase(const char * lpcsz)
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



template < class Type, class RawType >
void string_array < Type, RawType > ::write(::file::ostream & ostream) const
{
   ostream.write_arbitrary(this->m_nSize);
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      ostream << this->element_at(i);
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::read(::file::istream & istream)
{

   if(istream.fail())
   {

      return;

   }

   ::count iSize;

   istream.read_arbitrary(iSize);

   if(istream.fail())
   {

      return;

   }

   this->remove_all();

   for(int32_t i = 0; i < iSize; i++)
   {

      if(i >= this->get_size())
         this->set_size(MIN(i + 1024,iSize));

      istream >> this->element_at(i);

      if(istream.fail())
      {

         return;

      }

   }

   if(this->get_size() != iSize)
   {

      istream.setstate(::file::failbit);

   }

}






template < class Type, class RawType >
void string_array < Type, RawType > ::implode(Type & str,const char * lpcszSeparator,index start,::count count) const
{
   str.Empty();
   Type strSeparator(lpcszSeparator);
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


template < class Type, class RawType >
Type string_array < Type, RawType > ::implode(const char * lpcszSeparator,index iStart,index iEnd) const
{
   Type str;
   implode(str,lpcszSeparator,iStart,iEnd);
   return str;
}



template < class Type, class RawType >
void string_array < Type, RawType > ::reverse_implode(Type & str,const char * lpcszSeparator,index start,::count count) const
{
   str.Empty();
   Type strSeparator(lpcszSeparator);
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


template < class Type, class RawType >
Type string_array < Type, RawType > ::reverse_implode(const char * lpcszSeparator,index iStart,index iEnd) const
{
   Type str;
   reverse_implode(str,lpcszSeparator,iStart,iEnd);
   return str;
}


template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::explode(const Type & strSeparator,const Type & str)
{

   this->remove_all();

   add_tokens(str,strSeparator,true);

   return * this;

}



template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::csstidy_explode_ws(char sep,const char * psz)
{

   Type istring(psz);

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
            element_at(num) += (Type)RawType(istring[i]);
         }
         else
         {
            element_at(num) += (Type)RawType(istring[i]);
         }
         break;

      case 2:
         if(istring[i] == to && !::str::simple_escaped(istring,i))
         {
            status = 1;
         }
         element_at(num) += (Type)RawType(istring[i]);
         break;
      }

   }

   return *this;

}


template < class Type, class RawType >
bool string_array < Type, RawType > ::operator == (const typename string_array < Type, RawType >::RawStringArray & a) const
{

   if (a.get_size() != get_size())
   {

      return false;

   }

   for (index i = 0; i < get_size(); i++)
   {

      if (a[i] != element_at(i))
      {

         return false;

      }

   }

   return true;

}


template < class Type, class RawType >
bool string_array < Type, RawType > ::operator != (const typename string_array < Type, RawType >::RawStringArray & a) const
{

   return !operator == (a);

}


template < class Type, class RawType >
void string_array < Type, RawType > ::replace(const char * lpszSearch,const char * lpszReplace)
{
   for(int32_t i = 0; i < this->get_size(); i++)
   {
      this->element_at(i).replace(lpszSearch,lpszReplace);
   }
}



template < class Type, class RawType >
::count string_array < Type, RawType > ::explode_command_line(const Type & str,ref_array < char > * argv)
{

   Type strParse(str);

   while(strParse.has_char())
   {

      add((Type)::str::consume_command_line_argument(strParse));

   }

   if(argv != NULL)
   {

      for(index i = 0; i < get_count(); i++)
      {

         char * pch = (char *)(const char *)element_at(i);

         argv->add(pch);

      }

      argv->add(NULL);

   }

   return get_count();


}



template < class Type, class RawType >
void string_array < Type, RawType > ::surround(const char * pszPrefix,const char * pszSuffix,index iStart,::count iCount)
{

   Type strPrefix(pszPrefix);

   Type strSuffix(pszSuffix);

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


template < class Type, class RawType >
Type string_array < Type, RawType > ::surround_and_implode(const char * pszSeparator,const char * pszPrefix,const char * pszSuffix,index iStart,::count iCount)
{
   Type str;
   Type strSeparator(pszSeparator);
   Type strPrefix(pszPrefix);
   Type strSuffix(pszSuffix);

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


template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::operator -=(const string_array & stra)
{
   remove(stra);
   return *this;
}


template < class Type, class RawType >
string_array < Type, RawType >  & string_array < Type, RawType > ::operator +=(const string_array & stra)
{
   add(stra);
   return *this;
}


template < class Type, class RawType >
string_array < Type, RawType >  string_array < Type, RawType > ::operator -(const string_array & straParam) const
{
   string_array < Type, RawType >  stra(*this);
   stra -= straParam;
   return stra;
}


template < class Type, class RawType >
string_array < Type, RawType >  string_array < Type, RawType > ::operator +(const string_array & straParam) const
{
   string_array < Type, RawType >  stra(*this);
   stra += straParam;
   return stra;
}






template < class Type, class RawType >
bool string_array < Type, RawType > ::move_ci(const char * lpcsz,index iIndex)
{
   index i = find_first_ci(lpcsz);
   if(i < 0)
      return false;
   this->remove_at(i);
   insert_at(iIndex,lpcsz);
   return true;
}


template < class Type, class RawType >
bool string_array < Type, RawType > ::preferred(const char * lpcsz)
{
   return move_ci(lpcsz,0);
}


template < class Type, class RawType >
::count string_array < Type, RawType > ::preferred(string_array < Type, RawType >  & stra)
{
   ::count count = 0;
   for(index i = stra.get_upper_bound(); i >= 0; i--)
   {
      if(preferred(stra[i]))
         count++;
   }
   return count;
}



template < class Type, class RawType >
Type string_array < Type, RawType > ::pop(index i)
{
   i = get_upper_bound(i);
   Type strRet = this->element_at(i);
   this->remove_at(i);
   return strRet;
}


template < class Type, class RawType >
void string_array < Type, RawType > ::slice(string_array < Type, RawType >  & stra,index iOffset,::count count)
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


template < class Type, class RawType >
void string_array < Type, RawType > ::remove(index iOffset,::count count)
{
   for(index i = iOffset + count - 1; i >= iOffset; i--)
   {
      this->remove_at(i);
   }
}



template < class Type, class RawType >
void string_array < Type, RawType > ::splice(const string_array < Type, RawType >  & stra,index iOffset,::count count)
{

   remove(iOffset,count);

   insert_at(iOffset,stra);

}



template < class Type, class RawType >
void string_array < Type, RawType > ::splice(const string_array < Type, RawType >  & stra,index iOffset,string_array < Type, RawType >  & straRemoved,::count count)
{

   slice(straRemoved,iOffset,count);

   remove(iOffset,count);

   insert_at(iOffset,stra);

}



template < class Type, class RawType >
bool string_array < Type, RawType > ::is_empty(::count countMinimum)
{
   return this->get_size() < countMinimum;
}


template < class Type, class RawType >
bool string_array < Type, RawType > ::has_elements(::count countMinimum)
{
   return this->get_count() >= countMinimum;
}



template < class Type, class RawType >
::count string_array < Type, RawType > ::get_begins_ci(string_array < Type, RawType >  & stra,const char * lpcsz,index first,index last)
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


template < class Type, class RawType >
::count string_array < Type, RawType > ::filter_begins_ci(const char * lpcsz,index first,index last)
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
         this->remove_at(i,last - i + 1);
         return count;
      }
      this->remove_at(i,iFind - i);
      last -= iFind - i;
      i++;
      count++;

   }
}

template < class Type,class RawType >
template < typename Pred >
::count string_array < Type,RawType > ::filter(Pred pred,index first,index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
//   index i = first;
   ::count count = 0;
   for(index i = first; i <= last;)
   {
      if(pred(element_at(i)))
      {
         i++;
      }
      else
      {
         this->remove_at(i);
         count++;
         last--;
      }

   }
   return count;
}


template < class Type,class RawType >
template < typename Pred >
::count string_array < Type,RawType > ::filter_out(Pred pred,index first,index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
//   index i = first;
   ::count count = 0;
   for(index i = first; i <= last;)
   {
      if(!pred(element_at(i)))
      {
         i++;
      }
      else
      {
         this->remove_at(i);
         count++;
         last--;
      }

   }
   return count;
}

template < class Type,class RawType >
template < typename Pred, typename ArrayOut >
::count string_array < Type,RawType > ::filter_out(Pred pred, ArrayOut & a, index first,index last)
{
   if(last < 0)
      last = this->get_size() + last;
   if(last >= this->get_size())
      last = get_upper_bound();
   if(first < 0)
      first = 0;
//   index i = first;
   ::count count = 0;
   for(index i = first; i <= last;)
   {
      if(!pred(element_at(i)))
      {
         i++;
      }
      else
      {
         a.add(this->element_at(i));
         this->remove_at(i);
         count++;
         last--;
      }

   }
   return count;
}

template < class Type, class RawType >
index string_array < Type, RawType > ::get_random_index() const
{
   if(this->get_size() <= 0)
      return -1;
   return (index)(rand() % get_size());
}


template < class Type, class RawType >
Type & string_array < Type, RawType > ::random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}


template < class Type, class RawType >
const Type & string_array < Type, RawType > ::random_element() const
{
   if(this->get_size() <= 0)
      throw "invalid call";
   return this->element_at(get_random_index());
}


template < class Type, class RawType >
Type string_array < Type, RawType > ::pop_random_element()
{
   if(this->get_size() <= 0)
      throw "invalid call";
   index i = get_random_index();
   Type str = this->element_at(i);
   this->remove_at(i);
   return str;
}




template < class Type, class RawType >
void string_array < Type, RawType > ::make_lower()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_lower();
   }
}


template < class Type, class RawType >
void string_array < Type, RawType > ::make_upper()
{
   for(index i = 0; i < this->get_count(); i++)
   {
      this->element_at(i).make_upper();
   }
}



template < class Type, class RawType >
comparable_array < id > string_array < Type, RawType > ::get_comparable_ida() const
{

   comparable_array < id > ida;

   for(int32_t i = 0; i < get_count(); i++)
   {
      ida.add(element_at(i));
   }

   return ida;

}




template < class Type, class RawType >
Type string_array < Type, RawType > ::encode_v16()
{
   Type strEncode;
   for(int32_t ui = 0; ui < this->get_count(); ui++)
   {
      Type & str = this->element_at(ui);
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




template < class Type, class RawType >
void string_array < Type, RawType > ::decode_v16(const char * psz)
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
      char ch = static_cast <char> (iConversion);
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



template < class Type, class RawType >
::count string_array < Type, RawType > ::get_count_except(const Type & str)
{

   ::count c = get_count();

   for(index i = 0; i < get_count(); i++)
   {

      if(element_at(i) == str)
         c--;

   }

   return c;

}


template < class Type, class RawType >
::count string_array < Type, RawType > ::get_count_except(const string_array < Type, RawType >  & stra)
{

   ::count c = get_count();

   for(index i = 0; i < get_count(); i++)
   {

      if(stra.contains(element_at(i)))
         c--;

   }

   return c;

}



template < class Type, class RawType >
::count string_array < Type, RawType > ::get_count_except_ci(const Type & str)
{

   ::count c = get_count();

   for(index i = 0; i < get_count(); i++)
   {

      if(element_at(i).CompareNoCase(str) == 0)
         c--;

   }

   return c;

}


template < class Type, class RawType >
::count string_array < Type, RawType > ::get_count_except_ci(const string_array < Type, RawType >  & stra)
{

   ::count c = get_count();

   for(index i = 0; i < get_count(); i++)
   {

      if(stra.contains_ci(element_at(i)))
         c--;

   }

   return c;

}



template < class Type, class RawType >
Type & string_array < Type, RawType > ::get_json(Type & str, bool bNewLine) const
{

   str += "[";

   if(get_count() > 0)
   {

      str += "\"";

      str += element_at(0);

      str += "\"";

   }

   for(index i = 1; i < get_count(); i++)
   {

      if (bNewLine)
      {

         str += ", \r\n";

      }
      else
      {

         str += ", ";

      }

      str += "\"";

      str += element_at(i);

      str += "\"";

   }

   if (bNewLine)
   {

      str += "\r\n";

   }

   str += "]";

   return str;

}





template < class Type, class RawType >
void string_array < Type, RawType > ::_008Implode(Type & str, const char * lpcszSeparator, const char * lpcszLastSeparator, index start, ::count count) const
{
   str.Empty();
   Type strSeparator(lpcszSeparator);
   if (start < 0)
   {
      start += this->get_size();
   }
   index last;
   if (count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   for (index i = start; i <= last; i++)
   {
      if (i > start)
      {
         if (i == last)
         {
            str += lpcszLastSeparator;
         }
         else
         {
            str += strSeparator;
         }
      }
      str += this->element_at(i);
   }
}


template < class Type, class RawType >
Type string_array < Type, RawType > ::_008Implode(const char * lpcszSeparator, const char * lpcszLastSeparator, index iStart, index iEnd) const
{
   Type str;
   _008Implode(str, lpcszSeparator, lpcszLastSeparator, iStart, iEnd);
   return str;
}


template < class Type, class RawType >
void string_array < Type, RawType > ::_008IfImplode(Type & str, const char * lpcszIfHasElementPrefix, const char * lpcszSeparator, const char * lpcszLastSeparator, bool bUseLast, index start, ::count count) const
{
   str.Empty();
   Type strSeparator(lpcszSeparator);
   if (start < 0)
   {
      start += this->get_size();
   }
   index last;
   if (count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   if (last >= start)
   {
      str += lpcszIfHasElementPrefix;
   }
   for (index i = start; i <= last; i++)
   {
      if (i > start)
      {
         if (i == last && bUseLast)
         {
            str += lpcszLastSeparator;
         }
         else
         {
            str += strSeparator;
         }
      }
      str += this->element_at(i);
   }
}


template < class Type, class RawType >
Type string_array < Type, RawType > ::_008IfImplode(const char * lpcszIfHasElementPrefix, const char * lpcszSeparator, const char * lpcszLastSeparator, bool bUseLast, index iStart, index iEnd) const
{
   Type str;
   _008IfImplode(str, lpcszIfHasElementPrefix, lpcszSeparator, lpcszLastSeparator, bUseLast, iStart, iEnd);
   return str;
}
