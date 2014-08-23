#pragma once

class CLASS_DECL_AXIS str_sort_array
{
public:
   str_sort_array();
   virtual ~str_sort_array();

protected:
   bool        m_bSorted;
   stringa   m_stra;
   int32_t       (*m_pfnCompare)(const char *, const char *);

   inline void _Swap(index iA, index iB);


public:

   ::count get_size();

   void SetCompareFunction(int32_t fCompare(const char *, const char *));
   void Sort();
   index SortFind(const char * lpcsz);
   index SortFindNoCase(const char * lpcsz);

   inline void swap(index iA, index iB);

   // stringa overrides
   void set_at(index nIndex, const char * newElement);
   void set_at(index nIndex, const string & newElement);
   string element_at(index nIndex);
   string * get_data();
   void set_at_grow(index nIndex, const char * newElement);
   void set_at_grow(index nIndex, const string & newElement);
   index add(const char * newElement);
   index add(const string & newElement);
   void push(const string & newElement);
   ::count add(const string_array& src);

   void copy(const string_array& src);
   string & operator[](index nIndex);
   void insert_at(index nIndex, const char * newElement, ::count nCount = 1);
   void insert_at(index nIndex, const string & newElement, ::count nCount = 1);
   void insert_at(index nStartIndex, const string_array & NewArray);

   // stringa overrides
   void add_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty);
   void add_unique(const char * lpcsz);
   void add_normal(const char * lpcsz);

   static int32_t Compare(const char * lpcszA, const char * lpcszB);
   static int32_t CompareNoCase(const char * lpcszA, const char * lpcszB);

};

inline ::count str_sort_array::get_size()
{
   return m_stra.get_size();
}

inline void str_sort_array::set_at(index nIndex, const char * newElement)
{
   m_bSorted = false;
   m_stra.set_at(nIndex, newElement);
}

inline void str_sort_array::set_at(index nIndex, const string & newElement)
{
   m_bSorted = false;
   m_stra.set_at(nIndex, newElement);
}

inline string str_sort_array::element_at(index nIndex)
{
   m_bSorted = false;
   return m_stra.element_at(nIndex);
}

inline string * str_sort_array::get_data()
{
   m_bSorted = false;
   return m_stra.get_data();
}

inline void str_sort_array::set_at_grow(index nIndex, const char * newElement)
{
   m_bSorted = false;
   m_stra.set_at_grow(nIndex, newElement);
}

inline void str_sort_array::set_at_grow(index nIndex, const string & newElement)
{
   m_bSorted = false;
   m_stra.set_at_grow(nIndex, newElement);
}

inline index str_sort_array::add(const char * newElement)
{
   m_bSorted = false;
   return m_stra.add(newElement);
}

inline index str_sort_array::add(const string & newElement)
{
   m_bSorted = false;
   return m_stra.add(newElement);
}

inline void str_sort_array::push(const string & newElement)
{
   m_bSorted = false;
   return m_stra.push_back(newElement);
}

inline ::count str_sort_array::add(const string_array& src)
{
   m_bSorted = false;
   return m_stra.add(src);
}

inline void str_sort_array::copy(const string_array& src)
{
   m_bSorted = false;
   m_stra.copy(src);
}

inline string & str_sort_array::operator[](index nIndex)
{
   m_bSorted = false;
   return m_stra.operator[](nIndex);
}

inline void str_sort_array::insert_at(index nIndex, const char * newElement, ::count nCount)
{
   m_bSorted = false;
   m_stra.insert_at(nIndex, newElement, nCount);
}

inline void str_sort_array::insert_at(index nIndex, const string & newElement, ::count nCount)
{
   m_bSorted = false;
   m_stra.insert_at(nIndex, newElement, nCount);
}

inline void str_sort_array::insert_at(index nStartIndex, const string_array & NewArray)
{
   m_bSorted = false;
   m_stra.insert_at(nStartIndex, NewArray);
}

inline void str_sort_array::_Swap(index iA, index iB)
{
   string str(m_stra.element_at(iA));
   m_stra.element_at(iA) = m_stra.element_at(iB);
   m_stra.element_at(iB) = str;
}

inline void str_sort_array::swap(index iA, index iB)
{
   m_bSorted = false;
   _Swap(iA, iB);
}

// stringa overrides
inline void str_sort_array::add_tokens(const char * lpcsz, const char * lpcszSeparator, bool bAddEmpty)
{
   m_bSorted = false;
   m_stra.add_tokens(lpcsz, lpcszSeparator, bAddEmpty);
}

inline void str_sort_array::add_unique(const char * lpcsz)
{
   m_bSorted = false;
   m_stra.add_unique(lpcsz);
}

inline void str_sort_array::add_normal(const char * lpcsz)
{
   m_bSorted = false;
   m_stra.add_normal(lpcsz);
}

// strA - strB
inline int32_t str_sort_array::Compare(const char * lpcszA, const char * lpcszB)
{
   return strcmp(lpcszA, lpcszB);
}

// strA - strB
inline int32_t str_sort_array::CompareNoCase(const char * lpcszA, const char * lpcszB)
{
   return stricmp_dup(lpcszA, lpcszB);
}
