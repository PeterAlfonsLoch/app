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



