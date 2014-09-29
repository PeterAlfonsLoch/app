#pragma once


class CLASS_DECL_AURA string_array :
   virtual public array < string >
{
public:
   string_array();

   ::count get_size() const;
   ::count get_count() const;
   index get_lower_bound(index i = 0) const;
   index get_upper_bound(index i = -1) const;
   //void set_size(::count nNewSize, ::count nGrowBy = -1);

   //::count size() const;

   //void free_extra();
   //void remove_all();
   //void clear();

   string get_at(index nIndex) const;
   void set_at(index nIndex, const char * newElement);

   void set_at(index nIndex, const string & newElement);

   string & element_at(index nIndex);
   const string & element_at(index nIndex) const;

   index add_new(const char * psz = NULL, index i = -1);
   string & new_element(index i = -1);

   string & first_element(index count = 0);
   string first_element(index count = 0) const;

   string & last_element(index count = -1);
   string last_element(index count = -1) const;

   const string* get_data() const;
   string* get_data();

   // Potentially growing the array
   void set_at_grow(index nIndex, const char * newElement);

   void set_at_grow(index nIndex, const string & newElement);

   index add(const char * psz);

   index add(const wchar_t * pwsz);

   index add(char ch);

   index add(wchar_t wch);

   void add(const var & var);

   void add(const property & prop);

   void add(const id & id);

   index add(const string & newElement);

   void push_back(const string & newElement);

   ::count add(const string_array & src);

   void copy(const string_array & src);
   void copy(const int64_array & src);



   // overloaded operator helpers
   string operator[](index nIndex) const;
   string & operator[](index nIndex);

   // Operations that move elements around
   void insert_at(index nIndex, const char * newElement, ::count nCount = 1);

   void insert_at(index nIndex, const string & newElement, ::count nCount = 1);

   //void remove_at(index nIndex, ::count nCount = 1);

   void insert_at(index nStartIndex, const string_array & NewArray);

   void quick_sort(
      void swap(void * lpVoidSwapArg, const index, const index) = NULL,
      void * lpvoidSwapArg = NULL,
      bool bNoCase = false);

   void get_quick_sort_ci(index_array & ia);

   string_array slice(index iStart, ::count iCount = -1);

   string_array & operator =(const string_array & stra);


protected:
//   string * m_pData;   // the actual array of data
  // ::count m_nSize;     // # of elements (upperBound - 1)
   //::count m_nMaxSize;  // MAX allocated
   //::count m_nGrowBy;   // grow amount

   void InsertEmpty(index nIndex, ::count nCount);



public:
   ~string_array();

///   void Serialize(CArchive&);
   void dump(dump_context &) const;
   void assert_valid() const;

protected:
   // local typedefs for class templates
   typedef string BASE_TYPE;
   typedef const char * BASE_ARG_TYPE;
};



static inline void ConstructElement(string* pNewData)
{
   ((string *)pNewData)->construct();
}

static inline void DestructElement(string* pOldData)
{
   pOldData->~string();
}


inline string & string_array::last_element(index i)
{
   return this->element_at(get_upper_bound(i));
}


inline string string_array::last_element(index count) const
{
   return this->element_at(get_upper_bound(count));
}

inline string & string_array::first_element(index i)
{
   return this->element_at(get_lower_bound(i));
}


inline string string_array::first_element(index count) const
{
   return this->element_at(get_lower_bound(count));
}


inline ::count string_array::get_size() const
   { return m_nSize; }
inline ::count string_array::get_count() const
   { return m_nSize; }
inline index string_array::get_lower_bound(index i) const
   { return i; }
inline index string_array::get_upper_bound(index count) const
   { return m_nSize + count; }

//inline ::count string_array::size() const
  // { return m_nSize; }
