#pragma once


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



} // namespace lemon






