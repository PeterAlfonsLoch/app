#pragma once


template < typename T > class numeric_array;
typedef CLASS_DECL_AURA numeric_array < index > index_array;


namespace constructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void construct(void * pvoid)
      {
         ::new(pvoid) TYPE;
      }
      inline static void construct(void * pvoid, ::count c)
      {
         TYPE * p = (TYPE *) pvoid;
         while(c > 0)
         {
            ::new((void *) p) TYPE;
            p++;
            c--;
         }
      }



   };


   template < class TYPE >
   class zero
   {
   public:

      inline static void construct(void * pvoid)
      {

         ::zero(pvoid, sizeof(TYPE));

      }

      inline static void construct(void * pvoid, ::count c)
      {

         TYPE * p = (TYPE *)pvoid;

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            p++;

            c--;

         }

      }



   };

   class nodef
   {
   public:

      inline static void construct(void * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void construct(void * p, :: count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor


// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template < class TYPE, class ARG_TYPE = const TYPE &, class DEFCONSTRUCTOR = ::constructor::def < TYPE > >
class array :
   virtual public ::object
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef array < TYPE, ARG_TYPE > BASE_ARRAY;

   /*

   class iterator
   {
   public:


   index            m_i;
   array *     m_parray;

   iterator()
   {
   m_i = 0;
   m_parray = NULL;
   }

   iterator(index i, array * parray)
   {
   m_i         = i;
   m_parray    = parray;
   }

   iterator(const iterator & it)
   {
   }

   TYPE & operator * ()
   {
   m_parray->element_at[m_i];
   }

   const TYPE & operator * () const
   {
   m_parray->element_at[m_i];
   }

   iterator & operator = (const iterator & it)
   {
   if(this != &it)
   {
   m_i         = it.m_i;
   m_parray    = it.m_parray;
   }
   return *this;
   }

   bool operator == (const iterator & it)
   {
   if(this == &it)
   return true;
   if(m_parray != it.m_parray)
   return false;
   if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
   return true;
   if(m_i <= 0 && it.m_i <= 0)
   return true;
   return m_i == it.m_i;
   }

   iterator & operator ++()
   {
   m_i++;
   if(m_i >= m_parray->get_size())
   m_i = m_parray->get_size();
   return *this;
   }

   iterator & operator +(int32_t i)
   {
   m_i += i;
   if(m_i >= m_parray->get_size())
   m_i = m_parray->get_size();
   return *this;
   }

   iterator & operator --()
   {
   m_i--;
   if(m_i < 0)
   m_i = 0;
   return *this;
   }

   };
   */

   class iterator :
      public random_access_iterator
   {
   public:

      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef array < TYPE,ARG_TYPE > BASE_ARRAY;

      index            m_i;
      array *     m_parray;

      iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      iterator(index i, array * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      iterator(const iterator & it)
      {
         operator = (it);
      }

      TYPE & operator * ()
      {
         return m_parray->element_at(m_i);
      }

      const TYPE & operator * () const
      {
         return m_parray->element_at(m_i);
      }

      iterator & operator = (const iterator & it)
      {
         if(this != &it)
         {
            m_i         = it.m_i;
            m_parray    = it.m_parray;
         }
         return *this;
      }

      bool operator == (const iterator & it)
      {
         if(this == &it)
            return true;
         if(m_parray != it.m_parray)
            return false;
         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if(m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const iterator & it)
      {
         return !operator==(it);
      }

      iterator & operator ++()
      {
         m_i++;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      iterator & operator +(index i)
      {
         m_i += i;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      iterator & operator --()
      {
         m_i--;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      iterator mid(const iterator & i) const
      {
         return iterator((m_i + i.m_i + 1) / 2,m_parray);
      }

      iterator & operator -(::count c)
      {
         m_i-=c;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }

   };


   class const_iterator :
      public random_access_iterator
   {
   public:


      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef array < TYPE,ARG_TYPE > BASE_ARRAY;

      index            m_i;
      const array *     m_parray;

      const_iterator()
      {
         m_i = 0;
         m_parray = NULL;
      }

      const_iterator(index i, const array * parray)
      {
         m_i = i;
         m_parray = parray;
      }

      const_iterator(const iterator & it)
      {
         operator = (it);
      }

      const_iterator(const const_iterator & it)
      {
         operator = (it);
      }

      const TYPE & operator * ()
      {
         return m_parray->element_at(m_i);
      }

      const_iterator & operator = (const iterator & it)
      {

         m_i         = it.m_i;
         m_parray    = it.m_parray;

         return *this;

      }

      const_iterator & operator = (const const_iterator & it)
      {
         if(this != &it)
         {
            m_i         = it.m_i;
            m_parray    = it.m_parray;
         }
         return *this;
      }

      bool operator == (const const_iterator & it)
      {
         if(this == &it)
            return true;
         if(m_parray != it.m_parray)
            return false;
         if(m_i >= m_parray->get_size() && it.m_i >= m_parray->get_size())
            return true;
         if(m_i <= 0 && it.m_i <= 0)
            return true;
         return m_i == it.m_i;
      }

      bool operator != (const const_iterator & it)
      {
         return !operator==(it);
      }

      const_iterator & operator ++()
      {
         m_i++;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      const_iterator & operator +(index i)
      {
         m_i += i;
         if(m_i >= m_parray->get_size())
            m_i = m_parray->get_size();
         return *this;
      }

      const_iterator & operator --()
      {
         m_i--;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      const_iterator mid(const const_iterator & i) const
      {
         return const_iterator((m_i + i.m_i + 1) / 2,m_parray);
      }

      const_iterator & operator -(::count c)
      {
         m_i-=c;
         if(m_i < 0)
            m_i = 0;
         return *this;
      }

      bool operator < (const const_iterator & i) const
      {

         return m_i < i.m_i;

      }

      ::count get_count() const
      {
         return m_parray->get_count();
      }

   };

   TYPE *      m_pData;    // the actual array of data
   ::count     m_nSize;    // # of elements (upperBound - 1)
   ::count     m_nMaxSize; // MAX allocated
   ::count     m_nGrowBy;  // grow amount



   array(sp(::aura::application) papp = NULL, ::count nGrowBy = 32);
   array(const array <TYPE, ARG_TYPE> & a);
   array(::count n);
 //  array(ARG_TYPE t, ::count n = 1);
   //array(TYPE * ptypea, ::count n);
   virtual ~array();

   virtual void destroy();

   inline ::count get_size() const;
   inline ::count get_size_in_bytes() const;
   inline ::count get_count() const;
   inline ::count get_byte_count() const;
   inline ::count size() const;
   inline ::count count() const;

   inline bool is_empty(::count countMinimum = 1) const;
   inline bool empty(::count countMinimum = 1) const;
   inline bool has_elements(::count countMinimum = 1) const;
   inline index get_upper_bound(index i = -1) const;
   ::count set_size(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count allocate_in_bytes(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements
   ::count set_raw_size(index nNewSize, ::count nGrowBy = -1); // does not call constructors and destructors on items/elements
   ::count resize(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements


   void free_extra();

   void remove_last();

   ::count remove_all();
   void clear();




   // Accessing elements
   inline const TYPE& get_at(index nIndex) const;
   inline TYPE& get_at(index nIndex);
   inline void set_at(index nIndex, ARG_TYPE newElement);

   inline const TYPE & element_at(index nIndex) const;
   inline TYPE & element_at(index nIndex);

   inline const TYPE& first_element(index index = 0) const;
   inline TYPE& first_element(index index = 0);

   inline const TYPE& last_element(index index = -1) const;
   inline TYPE& last_element(index index = -1);

   inline TYPE & front(index n = 0);
   inline const TYPE & front(index n = 0) const;

   inline TYPE & back(index n = -1);
   inline const TYPE & back(index n = -1) const;


   inline const TYPE & at(index nIndex) const { return element_at(nIndex);  }
   inline TYPE & at(index nIndex) { return element_at(nIndex); }

   // Direct Access to the element data (may return NULL)
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing the array
   index add(ARG_TYPE newElement);
   index add(const array& src);
   index append(const array& src);
   void copy(const array& src);

   index push_back(ARG_TYPE newElement);

   inline TYPE & add_new();
   inline index add_new( ::count count);


   void push_last();


   TYPE pop(index index = -1);
   void pop_back(index index = -1);

   TYPE pop_to();


   iterator erase(iterator pos);
   iterator erase(iterator first, iterator last);
   iterator begin()
   {
      return iterator(0, this);
   }

   iterator end()
   {
      return iterator(this->get_size(), this);
   }


   // overloaded operator helpers
   inline const TYPE& operator[](index nIndex) const;
   inline TYPE& operator[](index nIndex);

   // Operations that move elements around
   index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   index remove_at(index nIndex, ::count nCount = 1);
   void _001RemoveIndexes(index_array & ia);
   void remove_indexes(const index_array & ia); // remove indexes from index array upper bound to index array lower bound
   void remove_descending_indexes(const index_array & ia); // remove indexes from index array lower bound to index array upper bound
   index insert_at(index nStartIndex, array* pNewArray);
   void swap(index index1, index index2);

   array & operator = (const array & src);

   index find_first(ARG_TYPE t, index (* lpfnCompare)(ARG_TYPE, ARG_TYPE), index start = 0, index last = -1) const;
   index raw_find_first(TYPE * pt, index first = 0, index last = -1) const;

   template < class DERIVED >
   index find_first(DERIVED * pt, index first = 0, index last = -1)
   {
      return raw_find_first(dynamic_cast < TYPE * > (pt), first, last);
   }

   template < class ARRAY >
   ::count get_array(ARRAY & a, index iStart = 0, ::count nCount = -1)
   {

      ::count ca = 0;

      index iEnd;

      if(nCount < 0)
         iEnd = get_upper_bound(nCount);
      else
         iEnd = iStart + nCount - 1;

      for(index i = iStart; i <= iEnd; i++)
      {

         a.add(element_at(i));
         ca++;

      }

      return ca;

   }

   void quick_sort(index (* fCompare)(TYPE *, TYPE *));
   void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
   void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
   bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

   bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
   index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   ::count sort_add(const array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);



   array & operator += (const array & a);
   array operator + (const array & a) const;

   void dump(dump_context &) const;
   void assert_valid() const;

#ifdef MOVE_SEMANTICS
   array(array && a) :
   element(a.get_app())
   {

      m_nGrowBy      = a.m_nGrowBy;
      m_pData        = a.m_pData;
      m_nSize        = a.m_nSize;
      m_nMaxSize     = a.m_nMaxSize;

      a.m_pData      = NULL;
      a.m_nSize      = 0;
      a.m_nMaxSize   = 0;

   }


   inline array & operator = (array && a)
   {

      if(&a != this)
      {
         destroy();

         m_nGrowBy      = a.m_nGrowBy;
         m_pData        = a.m_pData;
         m_nSize        = a.m_nSize;
         m_nMaxSize     = a.m_nMaxSize;

         a.m_pData      = NULL;
         a.m_nSize      = 0;
         a.m_nMaxSize   = 0;

      }

      return *this;
   }

#endif

   inline void set_at_grow(index nIndex, ARG_TYPE newElement);

   inline TYPE & element_at_grow(index nIndex);

};




template < class TYPE, class ARG_TYPE = const TYPE & >
class nodefctr_array :
   public array < TYPE, ARG_TYPE, ::constructor::nodef >
{
public:


   nodefctr_array(sp(::aura::application) papp = NULL, ::count nGrowBy = 32) : array < TYPE, ARG_TYPE, ::constructor::nodef > (papp, nGrowBy) {}
   nodefctr_array(const array <TYPE, ARG_TYPE> & a) : array < TYPE, ARG_TYPE, ::constructor::nodef > (a) {}
   nodefctr_array(::count n) : array < TYPE, ARG_TYPE, ::constructor::nodef > (n){}
   virtual ~nodefctr_array() {}

};
