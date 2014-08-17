#pragma once


#include "base/primitive/collection/collection_iterator.h"


template < class TYPE, class ARG_TYPE >
inline bool LessCompareElements(ARG_TYPE element1, ARG_TYPE element2)
{
   return element1 < element2;
}


namespace comparison
{

   template < class TYPE, class ARG_TYPE >
   class less
   {
   public:

      inline static bool compare(ARG_TYPE element1, ARG_TYPE element2)
      {
         return ::LessCompareElements < TYPE, ARG_TYPE > (element1, element2);
      }


   };

   template < >
   class less < string, const string & >
   {
   public:

      inline static bool compare(const string & element1, const string & element2)
      {
         return element1 < element2;
      }

   };

   template < >
   class less < id, const id & >
   {
   public:

      inline static bool compare(const id & element1, const id & element2)
      {
         return element1.m_pstr < element2.m_pstr;
      }

   };





   class strid_less
   {
   public:

      inline static bool compare(const id & element1, const id & element2)
      {
         return element1.m_pstr < element2.m_pstr;
      }

   };


} // namespace comparison

template <bool b> struct StaticAssertionFailed;
template <> struct StaticAssertionFailed <true> {};

#define STATIC_ASSERT(x) \
    {StaticAssertionFailed <x> ();}


namespace lemon
{

   template <class RandomAccessIterator>
   void make_heap (RandomAccessIterator first, RandomAccessIterator last)
   {
      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t;
      raw_array < RandomAccessIterator > stackLowerBound;
      raw_array < RandomAccessIterator > stackUpperBound;
      RandomAccessIterator iLowerBound;
      RandomAccessIterator iUpperBound;
      RandomAccessIterator iLPos, iUPos, iMPos;
      //   uint32_t t;

      if(last - first >= 2)
      {
         stackLowerBound.push(first);
         stackUpperBound.push(last - 1);
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
                  if(!(*iMPos < *iUPos))
                     iUPos--;
                  else
                  {
                     t        = *iMPos;
                     *iMPos   = *iUPos;
                     *iUPos   = t;
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
                  if(!(*iLPos < *iMPos))
                     iLPos++;
                  else
                  {
                     t = *iMPos;
                     *iMPos = *iLPos;
                     *iLPos = t;
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

   template <class RandomAccessIterator, class Compare>
   void make_heap (RandomAccessIterator first, RandomAccessIterator last,
      Compare comp )
   {
      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t;
      raw_array < RandomAccessIterator > stackLowerBound;
      raw_array < RandomAccessIterator > stackUpperBound;
      RandomAccessIterator iLowerBound;
      RandomAccessIterator iUpperBound;
      RandomAccessIterator iLPos, iUPos, iMPos;
      //   uint32_t t;

      if(last - first >= 2)
      {
         stackLowerBound.push(first);
         stackUpperBound.push(last - 1);
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
                  if(!comp(*iMPos, *iUPos))
                     iUPos--;
                  else
                  {
                     t        = *iMPos;
                     *iMPos   = *iUPos;
                     *iUPos   = t;
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
                  if(!comp(*iLPos, *iMPos))
                     iLPos++;
                  else
                  {
                     t = *iMPos;
                     *iMPos = *iLPos;
                     *iLPos = t;
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


   template <class RandomAccessIterator, class Compare>
   void pop_heap (RandomAccessIterator first, RandomAccessIterator last)
   {

      make_heap(first, last);

      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t = *first;
      *first = *last;
      *last = t;

      make_heap(first, last - 1);

   }

   template <class RandomAccessIterator, class Compare>
   void pop_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {

      make_heap(first, last, comp);

      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t = *first;
      *first = *last;
      *last = t;

      make_heap(first, last - 1, comp);

   }

   template <class RandomAccessIterator, class Compare>
   void push_heap (RandomAccessIterator first, RandomAccessIterator last)
   {

      make_heap(first, last);

   }

   template <class RandomAccessIterator, class Compare>
   void push_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp)
   {

      make_heap(first, last, comp);

   }

   template <class RandomAccessIterator>
   void sort_heap (RandomAccessIterator first, RandomAccessIterator last)
   {
      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t;
      raw_array < RandomAccessIterator > stackLowerBound;
      raw_array < RandomAccessIterator > stackUpperBound;
      RandomAccessIterator iLowerBound;
      RandomAccessIterator iUpperBound;
      RandomAccessIterator iLPos, iUPos, iMPos;
      //   uint32_t t;

      if(last - first >= 2)
      {
         stackLowerBound.push(first);
         stackUpperBound.push(last - 1);
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
                  if(*iMPos < *iUPos)
                     iUPos--;
                  else
                  {
                     t        = *iMPos;
                     *iMPos   = *iUPos;
                     *iUPos   = t;
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
                  if(*iLPos < *iMPos)
                     iLPos++;
                  else
                  {
                     t = *iMPos;
                     *iMPos = *iLPos;
                     *iLPos = t;
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

   template <class RandomAccessIterator, class Compare>
   void sort_heap (RandomAccessIterator first, RandomAccessIterator last, Compare comp )
   {
      typename iterator_info < RandomAccessIterator >::VALUE_TYPE t;
      raw_array < RandomAccessIterator > stackLowerBound;
      raw_array < RandomAccessIterator > stackUpperBound;
      RandomAccessIterator iLowerBound;
      RandomAccessIterator iUpperBound;
      RandomAccessIterator iLPos, iUPos, iMPos;
      //   uint32_t t;

      if(last - first >= 2)
      {
         stackLowerBound.push(first);
         stackUpperBound.push(last - 1);
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
                  if(comp(*iMPos, *iUPos))
                     iUPos--;
                  else
                  {
                     t        = *iMPos;
                     *iMPos   = *iUPos;
                     *iUPos   = t;
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
                  if(comp(*iLPos, *iMPos))
                     iLPos++;
                  else
                  {
                     t = *iMPos;
                     *iMPos = *iLPos;
                     *iLPos = t;
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



}
