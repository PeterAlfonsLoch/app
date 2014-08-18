#pragma once


class CLASS_DECL_AXIS string_array :
   virtual public ::object
{
public:
   
   typedef string AXIS_TYPE;
   typedef const char * AXIS_ARG_TYPE;

   string * m_pData;   // the actual array of data
   ::count m_nSize;     // # of elements (upperBound - 1)
   ::count m_nMaxSize;  // max allocated
   ::count m_nGrowBy;   // grow amount

   string_array();
   string_array(sp(::axis::application) app);
   string_array(const string_array & a);
   ~string_array();


   ::count get_size() const;
   ::count get_count() const;
   index get_lower_bound(index i = 0) const;
   index get_upper_bound(index i = -1) const;
   void set_size(::count nNewSize, ::count nGrowBy = -1);

   ::count size() const;

   void free_extra();
   void remove_all();
   void clear();

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

   void add(const id & id);

   index add(const string & newElement);

   void push_back(const string & newElement);

   ::count add(const string_array & src);

   void copy(const string_array & src);

   void copy(const raw_int64_array & src);

   // overloaded operator helpers
   string operator[](index nIndex) const;
   string & operator[](index nIndex);

   // Operations that move elements around
   void insert_at(index nIndex, const char * newElement, ::count nCount = 1);

   void insert_at(index nIndex, const string & newElement, ::count nCount = 1);

   void remove_at(index nIndex, ::count nCount = 1);

   void insert_at(index nStartIndex, const string_array & NewArray);

   void quick_sort(
      void swap(void * lpVoidSwapArg, const index, const index) = NULL,
      void * lpvoidSwapArg = NULL,
      bool bNoCase = false);

   void get_quick_sort_ci(raw_index_array & ia);

   string_array slice(index iStart, ::count iCount = -1);

   string_array & operator =(const string_array & stra);

   void add_tokens(const char * lpcsz,const char * lpcszSeparator,bool bAddEmpty = true);
   void add_smallest_tokens(const char * lpcsz,string_array & straSeparator,bool bAddEmpty = true,bool bWithSeparator = FALSE);
   void add_lines(const string & str);


   bool is_empty(::count countMinimum = 1);
   bool has_elements(::count countMinimum = 1);


   void InsertEmpty(index nIndex, ::count nCount);


   void get_format_string(string & str,const char * lpcszSeparator) const;

   string encode_v16();


   void decode_v16(const char * psz);

   ::count get_count_except(const char * psz);
   ::count get_count_except(const string & str);
   ::count get_count_except(const string_array & stra);

   ::count get_count_except_ci(const char * psz);
   ::count get_count_except_ci(const string & str);
   ::count get_count_except_ci(const string_array & stra);

   string get_json();

   //   void XFV001Expand();

   string_array & operator =(const raw_int64_array & ia);
   string_array & operator -=(const string_array & stra);
   string_array & operator +=(const string_array & stra);

   string_array operator -(const string_array & stra) const;
   string_array operator +(const string_array & stra) const;





   void replace(const char * lpszSearch,const char * lpszReplace);


   primitive::memory GetFormatV004();
   ::count remove_empty();
   index add_normal(const char * lpcsz);
   void trim_right(const char * pszChars);
   void trim_left(const char * pszChars);
   void trim(const char * pszChars);
   void trim_right();
   void trim_left();
   void trim();
   index add_unique(const char * lpcsz);
   ::count add_unique(const string_array & stra);
   index add_unique_ci(const char * lpcsz);
   ::count add_unique_ci(const string_array & stra);

   void make_lower();
   void make_upper();


   index get_random_index() const;

   string & random_element();
   const string & random_element() const;

   string pop_random_element();

   string pop(index i = -1);
   void slice(string_array & stra,index index,::count ca = -1);
   void remove(index index,::count count);
   void splice(const string_array & stra,index index,::count ca = -1);
   void splice(const string_array & stra,index index,string_array & straRemoved,::count ca = -1);


   // if string is found, move it to specified position
   bool move_ci(const char * lpcsz,index iIndex);

   // move preferred in order
   bool preferred(const char * lpcsz);
   ::count preferred(string_array & stra);

   index find_first_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index find_first(const char * lpcsz,index find = 0,index last = -1) const;

   index reverse_find_ci(const char * lpcsz,index find = -1,index last = 0) const;
   index reverse_find(const char * lpcsz,index find = -1,index last = 0) const;


   index find_first_begins_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index find_first_begins(const char * lpcsz,index find = 0,index last = -1) const;

   index str_find_first_begins_ci(const char * lpcsz,index find = 0,index last = -1) const;
   index str_find_first_begins(const char * lpcsz,index find = 0,index last = -1) const;

   bool contains_ci(const char * lpcsz,index find = 0,index last = -1,::count countMin = 1,::count countMax = -1) const;
   bool contains(const char * lpcsz,index find = 0,index last = -1,::count countMin = 1,::count countMax = -1) const;

   ::count get_begins_ci(string_array & stra,const char * lpcsz,index first = 0,index last = -1);

   ::count filter_begins_ci(const char * lpcsz,index first = 0,index last = -1);

   ::count remove_first_ci(const char * lpcsz,index find = 0,index last = -1);
   ::count remove_first(const char * lpcsz,index find = 0,index last = -1);

   ::count remove_ci(const char * lpcsz,index find = 0,index last = -1,::count countMin = 0,::count countMax = -1);
   ::count remove(const char * lpcsz,index find = 0,index last = -1,::count countMin = 0,::count countMax = -1);

   ::count remove_ci(const string_array & stra);
   ::count remove(const string_array & stra);

   string_array & explode(const string & strSeparator,const string & str);

   // csstidy: Same as explode, but not within a string
   string_array & csstidy_explode_ws(char sep,const char * psz);

   void implode(string & rwstr,const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   void reverse_implode(string & rwstr,const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;
   string reverse_implode(const char * lpcszSeparator = NULL,index iStart = 0,::count iCount = -1) const;

   void surround(const char * pszPrefix = NULL,const char * pszSuffix = NULL,index iStart = 0,::count iCount = -1);
   string surround_and_implode(const char * lpcszSeparator = NULL,const char * pszPrefix = NULL,const char * pszSuffix = NULL,index iStart = 0,::count iCount = -1);


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

inline ::count string_array::size() const
   { return m_nSize; }
