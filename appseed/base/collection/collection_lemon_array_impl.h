#pragma once

//
// see collection_lemon_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// lemon_array is an array that call default constructors, copy constructs and destructors in elements


template < class TYPE, class ARG_TYPE >
inline lemon_array < TYPE, ARG_TYPE > :: lemon_array(sp(base_application) papp, ::count nGrowBy) :
   array < TYPE, ARG_TYPE > (papp, nGrowBy)
{
}


template < class TYPE, class ARG_TYPE >
inline lemon_array < TYPE, ARG_TYPE > :: lemon_array(const array <TYPE, ARG_TYPE> & a) :
   array < TYPE, ARG_TYPE > (a)
{
}


template < class TYPE, class ARG_TYPE >
inline lemon_array < TYPE, ARG_TYPE > :: lemon_array(::count n) :
   array < TYPE, ARG_TYPE > (n)
{
}


template < class TYPE, class ARG_TYPE >
inline lemon_array < TYPE, ARG_TYPE > :: lemon_array(ARG_TYPE t, ::count n)
{
   
   ::lemon::array::insert_at(*this, 0, t, n);

}


template < class TYPE, class ARG_TYPE >
inline lemon_array < TYPE, ARG_TYPE > :: lemon_array(TYPE * ptypea, ::count n)
{

   ::lemon::array::copy(*this, ptypea, n);

}


template < class TYPE, class ARG_TYPE >
lemon_array < TYPE, ARG_TYPE > :: ~lemon_array()
{
}

template < class TYPE, class ARG_TYPE >
::count lemon_array < TYPE, ARG_TYPE > :: set_size(index nNewSize, ::count nGrowBy) // does not call default constructors on new items/elements
{

   return ::lemon::array::set_size(*this, nNewSize, nGrowBy);

}

// Potentially growing the array
template < class TYPE, class ARG_TYPE >
inline void lemon_array < TYPE, ARG_TYPE > :: set_at_grow(index nIndex, ARG_TYPE newElement)
{

   ::lemon::array::set_at_grow(*this, nIndex, newElement);

}

template < class TYPE, class ARG_TYPE >
inline TYPE & lemon_array < TYPE, ARG_TYPE > :: element_at_grow(index nIndex)
{

   return ::lemon::array::element_at_grow(*this, nIndex);

}

template < class TYPE, class ARG_TYPE >
inline TYPE lemon_array < TYPE, ARG_TYPE > :: get_at_grow(index nIndex)
{

   return ::lemon::array::get_at_grow(*this, nIndex);

}



template < class TYPE, class ARG_TYPE >
inline index lemon_array < TYPE, ARG_TYPE > :: push(ARG_TYPE newElement, index i)
{

   return ::lemon::array::push(*this, newElement, i);

}


template < class TYPE, class ARG_TYPE >
inline void lemon_array < TYPE, ARG_TYPE > :: push_back(ARG_TYPE newElement, index i)
{

   ::lemon::array::push_back(*this, newElement, i);

}


// Operations that move elements around
template < class TYPE, class ARG_TYPE >
inline index lemon_array < TYPE, ARG_TYPE > :: insert_at(index nIndex, ARG_TYPE newElement, ::count nCount)
{

   return ::lemon::array::insert_at(*this, nIndex, newElement, nCount);

}


template < class TYPE, class ARG_TYPE >
inline index lemon_array < TYPE, ARG_TYPE > :: insert_at(index nStartIndex, array < TYPE, ARG_TYPE > * pNewArray)
{
   
   return ::lemon::array::insert_at(*this, nStartIndex, pNewArray);

}






namespace lemon
{

   namespace array
   {

      template < class ARRAY >
      ::count set_size(ARRAY & a, ::count nNewSize, ::count nGrowBy) // call default constructors and destructors
      {
         
         typedef typename ARRAY::BASE_TYPE TYPE;

         ::count countOld = a.get_count();
         ASSERT_VALID(&a);
         ASSERT(nNewSize >= 0);

         if(nNewSize < 0 )
            throw invalid_argument_exception(a.get_app());

         if (nGrowBy >= 0)
            a.m_nGrowBy = nGrowBy;  // set new size

         if (nNewSize == 0)
         {
            // shrink to nothing
            if (a.m_pData != NULL)
            {
               for( int32_t i = 0; i < a.m_nSize; i++ )
                  (a.m_pData + i)->~TYPE();
               delete[] (BYTE*)a.m_pData;
               a.m_pData = NULL;
            }
            a.m_nSize = a.m_nMaxSize = 0;
         }
         else if (a.m_pData == NULL)
         {
            // create buffer big enough to hold number of requested elements or
            // m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
            if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
               throw memory_exception(a.get_app());
            ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
            ::count nAllocSize = __max(nNewSize, a.m_nGrowBy);
            a.m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
            //memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
#undef new
            for( int32_t i = 0; i < nNewSize; i++ )
               ::new( (void *)( a.m_pData + i ) ) TYPE;
#define new DEBUG_NEW
            a.m_nSize = nNewSize;
            a.m_nMaxSize = nAllocSize;
         }
         else if (nNewSize <= a.m_nMaxSize)
         {
            // it fits
            if (nNewSize > a.m_nSize)
            {
               // initialize the new elements
               memset((void *)(a.m_pData + a.m_nSize), 0, (size_t)(nNewSize-a.m_nSize) * sizeof(TYPE));
               for( int32_t i = 0; i < nNewSize-a.m_nSize; i++ )
#undef new
                  ::new( (void *)( a.m_pData + a.m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
            }
            else if (a.m_nSize > nNewSize)
            {
               // destroy the old elements
               for( int32_t i = 0; i < a.m_nSize-nNewSize; i++ )
                  (a.m_pData + nNewSize + i)->~TYPE();
            }
            a.m_nSize = nNewSize;
         }
         else
         {
            // otherwise, grow aaa_base_array
            nGrowBy = a.m_nGrowBy;
            if (nGrowBy == 0)
            {
               // heuristically determine growth when nGrowBy == 0
               //  (this avoids heap fragmentation in many situations)
               nGrowBy = a.m_nSize / 8;
               nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
            }
            ::count nNewMax;
            if (nNewSize < a.m_nMaxSize + nGrowBy)
               nNewMax = a.m_nMaxSize + nGrowBy;  // granularity
            else
               nNewMax = nNewSize;  // no slush

            ASSERT(nNewMax >= a.m_nMaxSize);  // no wrap around

            if(nNewMax  < a.m_nMaxSize)
               throw invalid_argument_exception(a.get_app());

#ifdef SIZE_T_MAX
            ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
            TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

            // copy new data from old
            ::core::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE), a.m_pData, (size_t)a.m_nSize * sizeof(TYPE));

            // construct remaining elements
            ASSERT(nNewSize > a.m_nSize);
            memset((void *)(pNewData + a.m_nSize), 0, (size_t)(nNewSize-a.m_nSize) * sizeof(TYPE));
            for( int32_t i = 0; i < nNewSize-a.m_nSize; i++ )
#undef new
               ::new( (void *)( pNewData + a.m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
            // get rid of old stuff (note: no destructors called)
            delete[] (BYTE*)a.m_pData;
            a.m_pData = pNewData;
            a.m_nSize = nNewSize;
            a.m_nMaxSize = nNewMax;
         }
         return countOld;
      }

      template <class ARRY, class TYPE>
      inline index add_new(::count count)
      {
         allocate(m_nSize + count);
         return get_upper_bound();
      }

      template <class ARRAY >
      inline typename ARRAY::BASE_TYPE & add_new(ARRAY & a)
      {
         ::lemon::array::set_size(a, a.m_nSize + 1);
         return a.last_element();
      }

      template <class ARRAY>
      void copy(ARRAY & a, const typename ARRAY::BASE_TYPE * ptypea, ::count n)
      {

         ::lemon::array::set_size(a, n);

         for(int i = 0; i < n; i++)
         {
            a.element_at(i) = ptypea[i];
         }

      }

      template < class ARRAY >
      void set_at_grow(ARRAY & a, index nIndex, typename ARRAY::BASE_ARG_TYPE newElement)
      {
         
         ASSERT_VALID(&a);
         
         ASSERT(nIndex >= 0);

         if(nIndex < 0)
            throw invalid_argument_exception(a.get_app());

         if (nIndex >= a.m_nSize)
            ::lemon::array::set_size(a, nIndex+1, -1);

         a.m_pData[nIndex] = newElement;

      }

      template < class ARRAY>
      typename ARRAY::BASE_TYPE get_at_grow(ARRAY & a, index nIndex)
      {
         return element_at_grow(a, nIndex);
      }


      template < class ARRAY >
      typename ARRAY::BASE_TYPE & element_at_grow(ARRAY & a, index nIndex)
      {
         
         ASSERT_VALID(&a);

         ASSERT(nIndex >= 0);

         if(nIndex < 0)
            throw invalid_argument_exception(a.get_app());

         if (nIndex >= a.m_nSize)
            ::lemon::array::set_size(a, nIndex+1, -1);

         return a.m_pData[nIndex];

      }

      template<class ARRAY>
      index insert_at(ARRAY & a, index nIndex, typename ARRAY::BASE_ARG_TYPE newElement, ::count nCount /*=1*/)
      {
         
         ASSERT_VALID(&a);
         
         ASSERT(nIndex >= 0);    // will expand to meet need

         if(nCount <= 0)
            return -1;

         if(nIndex < 0)
            throw invalid_argument_exception(a.get_app());

         if (nIndex >= a.m_nSize)
         {
            // adding after the end of the array
            ::lemon::array::set_size(a, nIndex + nCount, -1);   // grow so nIndex is valid
         }
         else
         {
            // inserting in the middle of the array
            ::count nOldSize = a.m_nSize;
            ::lemon::array::set_size(a, a.m_nSize + nCount, -1);  // grow it to new size
            // destroy intial data before copying over it
            // shift old data up to fill gap
            ::core::memmove_s(a.m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(ARRAY::BASE_TYPE),
               a.m_pData + nIndex, (nOldSize-nIndex) * sizeof(ARRAY::BASE_TYPE));

            // re-init slots we copied from
            memset((void *)(a.m_pData + nIndex), 0, (size_t)nCount * sizeof(ARRAY::BASE_TYPE));
#undef new
            for( int32_t i = 0; i < nCount; i++ )
               ::new( (void *)(a.m_pData + nIndex + i ) ) ARRAY::BASE_TYPE;
#define new DEBUG_NEW
         }

         // insert new value in the gap
         ASSERT(nIndex + nCount <= a.m_nSize);

         index nIndexParam = nIndex;

         while (nCount--)
            a.m_pData[nIndex++] = newElement;

         return nIndexParam;

      }

      template<class ARRAY>
      inline index push(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, index n)
      {
         return insert_at(a, a.get_upper_bound(n), newElement);
      }

      template<class ARRAY>
      inline void push_back(ARRAY & a, typename ARRAY::BASE_ARG_TYPE newElement, index n)
      {
         insert_at(a, a.get_upper_bound(n), newElement);
      }

      template<class ARRAY>
      index insert_at(ARRAY & a, index nStartIndex, typename ARRAY::BASE_ARRAY * pNewArray)
      {
         ASSERT_VALID(&a);
         ASSERT(pNewArray != NULL);
         ASSERT_VALID(pNewArray);
         ASSERT(nStartIndex >= 0);

         if(pNewArray == NULL || nStartIndex < 0)
            throw invalid_argument_exception(a.get_app());

         if (pNewArray->get_size() > 0)
         {
            insert_at(a, nStartIndex, pNewArray->element_at(0), pNewArray->get_size());
            for (index i = 1; i < pNewArray->get_size(); i++)
               insert_at(a, nStartIndex + i, pNewArray->element_at(i));
         }

         return nStartIndex;

      }

   } // namespace array


} // namespace lemon





#define new DEBUG_NEW







