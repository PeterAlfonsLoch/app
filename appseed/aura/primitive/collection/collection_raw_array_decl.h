#pragma once


// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements


template<class TYPE, class ARG_TYPE = const TYPE &>
class raw_array :
   public array_base
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef raw_array < TYPE,ARG_TYPE > BASE_ARRAY;


   class iterator :
      public iterator_base
   {
   public:

      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef raw_array < TYPE,ARG_TYPE > BASE_ARRAY;


      iterator() {}
      iterator(index i,array_base * parray): iterator_base(i,parray) {}
      iterator(const iterator_base & it): iterator_base(it){}

      TYPE & operator * ()
      {
         return element_at(m_i);
      }

      const TYPE & operator * () const
      {
         return element_at(m_i);
      }

      TYPE & element_at(index i)
      {
         return ((TYPE*)m_parray->m_pData)[m_i];
      }

      const TYPE & element_at(index i) const
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }




   };


   class const_iterator
   {
   public:

      typedef TYPE BASE_TYPE;
      typedef ARG_TYPE BASE_ARG_TYPE;
      typedef raw_array < TYPE,ARG_TYPE > BASE_ARRAY;

      const_iterator() {}
      const_iterator(index i,const array_base * parray): const_iterator_base(i,parray) {}
      const_iterator(const iterator & it): const_iterator_base(it){}
      const_iterator(const const_iterator & it): const_iterator_base(it){}

      const TYPE & operator * ()
      {
         return element_at(m_i);
      }

      const TYPE & operator * () const
      {
         return element_at(m_i);
      }


      const TYPE & element_at(index i)
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }

      const TYPE & element_at(index i) const
      {
         return ((const TYPE*)m_parray->m_pData)[m_i];
      }

   };


   raw_array(::aura::application * papp = NULL, ::count nGrowBy = 32);
   raw_array(const raw_array <TYPE, ARG_TYPE> & a);
#ifdef MOVE_SEMANTICS
   raw_array(raw_array <TYPE,ARG_TYPE> && a);
#endif
   raw_array(::count n);
   raw_array(ARG_TYPE t, ::count n = 1);
   raw_array(TYPE * ptypea, ::count n);
   virtual ~raw_array();


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

   inline const TYPE & at(index nIndex) const { return element_at(nIndex); }
   inline TYPE & at(index nIndex) { return element_at(nIndex); }


   // Direct Access to the element data (may return NULL)
   inline const TYPE* get_data() const;
   inline TYPE* get_data();

   // Potentially growing the raw_array
   void set_at_grow(index nIndex, ARG_TYPE newElement);
   TYPE & element_at_grow(index nIndex);
   TYPE get_at_grow(index nIndex);
   index add(ARG_TYPE newElement);
   index add(const raw_array& src);
   virtual index add_new(::count count);
   virtual TYPE & add_new();
   //index append(const raw_array& src);
   //void copy(const raw_array& src);

   
   TYPE pop(index index = -1);
   index push(ARG_TYPE newElement, index i = 0);
   void pop_back(index index = -1);
   void push_back(ARG_TYPE newElement, index = 0);



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
   //index remove_at(index nIndex, ::count nCount = 1);
   //void _001RemoveIndexes(index_array & ia);
   //void remove_indexes(const index_array & ia); // remove indexes from index raw_array upper bound to index raw_array lower bound
   //void remove_descending_indexes(const index_array & ia); // remove indexes from index raw_array lower bound to index raw_array upper bound
   //index insert_at(index nStartIndex, raw_array* pNewArray);
   void swap(index index1, index index2);

   raw_array & operator = (const raw_array & src);

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

   //void quick_sort(index (* fCompare)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *));
   //void quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia);
   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const;

   //bool binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const;
   //index sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //::count sort_add(const raw_array < TYPE, ARG_TYPE > & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);
   //index sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia);



   raw_array & operator += (const raw_array & a);
   raw_array operator + (const raw_array & a) const;

   void dump(dump_context &) const;
   void assert_valid() const;


#ifdef MOVE_SEMANTICS
   inline raw_array & operator = (raw_array && a);
#endif


};



template<class TYPE,class ARG_TYPE = const TYPE &>
::file::output_stream & operator << (::file::output_stream & os,const raw_array < TYPE,ARG_TYPE> & a)
{
   ::file::array::write(os,a);
   return os;
}

template<class TYPE,class ARG_TYPE = const TYPE &>
::file::input_stream & operator >> (::file::input_stream & is,raw_array < TYPE,ARG_TYPE > & a)
{
   ::file::array::read(is,a);
   return is;
}