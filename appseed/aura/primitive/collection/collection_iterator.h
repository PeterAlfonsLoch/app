#pragma once


template < class ITERATOR >
struct iterator_info
{	
   typedef typename ITERATOR::ITERATOR_CATEGORY    ITERATOR_CATEGORY;
   typedef typename ITERATOR::VALUE_TYPE           VALUE_TYPE;
   typedef typename ITERATOR::DIFFERENCE_TYPE      DIFFERENCE_TYPE;
   typedef DIFFERENCE_TYPE                         DISTANCE_TYPE;	// retained
   typedef typename ITERATOR::POINTER              POINTER;
   typedef typename ITERATOR::REFERENCE            REFERENCE;
};


template < class TYPE >
struct iterator_info < TYPE * >
{	
   typedef random_access_iterator                  ITERATOR_CATEGORY;
   typedef TYPE                                    VALUE_TYPE;
   typedef ptrdiff_t                               DIFFERENCE_TYPE;
   typedef ptrdiff_t                               DISTANCE_TYPE;	// retained
   typedef TYPE *                                  POINTER;
   typedef TYPE &                                  REFERENCE;
};


template < class TYPE >
struct iterator_info < const TYPE * >
{
   typedef random_access_iterator                  ITERATOR_CATEGORY;
   typedef TYPE                                    VALUE_TYPE;
   typedef ptrdiff_t                               DIFFERENCE_TYPE;
   typedef ptrdiff_t                               DISTANCE_TYPE;	// retained
   typedef const TYPE *                            POINTER;
   typedef const TYPE &                            REFERENCE;
};

/*

template < typename TYPE >
class base_iterator
{
public:

   typedef TYPE BASE_TYPE;


   bool operator != (const base_iterator & it)
   {

      return !operator==(it);

   }


   base_iterator operator ++(int)
   {

      base_iterator it = *this;
      operator ++();
      return it;

   }


   base_iterator operator --(int)
   {

      base_iterator it = *this;
      operator --();
      return it;

   }


   TYPE & operator * ()
   {

   return *(operator->());

   }

   TYPE & operator * () const
   {

   return *(operator->());

   }




};


template < typename TYPE >
class const_base_iterator :
   public base_iterator < TYPE >
{
public:


   typedef const TYPE BASE_TYPE;


   bool operator != (const base_iterator & it)
   {

   return !operator==(it);

   }


   base_iterator operator ++(int)
   {

   base_iterator it = *this;
   operator ++();
   return it;

   }


   base_iterator operator --(int)
   {

   base_iterator it = *this;
   operator --();
   return it;

   }


   const TYPE & operator * ()
   {

      return *(operator->());

   }

   const TYPE & operator * () const
   {

      return *(operator->());

   }



};

*/