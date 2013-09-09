#pragma once


// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// lemon_array is an array that call default constructors, copy constructs and destructors in elements


template<class TYPE, class ARG_TYPE = const TYPE &>
class lemon_array :
   virtual public array < TYPE, ARG_TYPE >
{
public:

   typedef TYPE BASE_TYPE;
   typedef ARG_TYPE BASE_ARG_TYPE;
   typedef array < TYPE, ARG_TYPE > BASE_ARRAY;




   inline lemon_array(sp(base_application) papp = NULL, ::count nGrowBy = 32);
   inline lemon_array(const array <TYPE, ARG_TYPE> & a);
   inline lemon_array(::count n);
   inline lemon_array(ARG_TYPE t, ::count n = 1);
   inline lemon_array(TYPE * ptypea, ::count n);
   virtual ~lemon_array();


   ::count set_size(index nNewSize, ::count nGrowBy = -1); // does not call default constructors on new items/elements

   // Potentially growing the array
   inline void set_at_grow(index nIndex, ARG_TYPE newElement);
   inline TYPE & element_at_grow(index nIndex);
   inline TYPE get_at_grow(index nIndex);
   inline TYPE & add_new();
   inline ::index add_new(::count c);


   inline index push(ARG_TYPE newElement, index i = 0);
   inline void push_back(ARG_TYPE newElement, index = 0);



   // Operations that move elements around
   inline index insert_at(index nIndex, ARG_TYPE newElement, ::count nCount = 1);
   inline index insert_at(index nStartIndex, array < TYPE, ARG_TYPE > * pNewArray);

};








namespace lemon
{

   namespace array
   {

      template < class ARRAY >
      ::count set_size(ARRAY & a, ::count nNewSize, ::count nGrowBy = -1); // call default constructors and destructors

      template < class ARRAY >
      inline typename ARRAY::BASE_TYPE & add_new(ARRAY & a);

      template < class ARRAY >
      inline ::index add_new(ARRAY & a, ::count count);

      template < class ARRAY >
      void copy(ARRAY & a, const typename ARRAY::BASE_TYPE * ptype, ::count c);

      template<class ARRAY>
      index insert_at(ARRAY & a, index nIndex, typename ARRAY::BASE_ARG_TYPE newElement, ::count nCount = 1);

      template<class ARRAY>
      index push(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, index i = 0);

      template<class ARRAY>
      void push_back(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, index = 0);

      template<class ARRAY>
      index insert_at(ARRAY & a, index nStartIndex, typename ARRAY::BASE_ARRAY * pNewArray);

   }

} // namespace lemon
