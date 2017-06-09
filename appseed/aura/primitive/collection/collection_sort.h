#pragma once


namespace sort
{


   template < typename ITERABLE >
   void quick_sort(ITERABLE & iterable, bool bAsc);

   template < typename ITERABLE >
   void quick_sort(ITERABLE & iterable);

   template < typename ITERABLE >
   void quick_sort_desc(ITERABLE & iterable);

   template < typename ITERABLE >
   void quick_sort_ci(ITERABLE & iterable, bool bAsc);

   template < typename ITERABLE >
   void quick_sort_ci(ITERABLE & iterable);

   template < typename ITERABLE >
   void quick_sort_ci_desc(ITERABLE & iterable);






   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort(ITERABLE & iterable, SWAP swap, bool bAsc);

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort(ITERABLE & iterable, SWAP swap);

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_desc(ITERABLE & iterable, SWAP swap);

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci(ITERABLE & iterable, SWAP swap, bool bAsc);

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci(ITERABLE & iterable, SWAP swap);

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci_desc(ITERABLE & iterable, SWAP swap);







   template < typename ITERABLE, typename PRED >
   void pred_quick_sort(ITERABLE & iterable, PRED pred, bool bAsc);

   template < typename ITERABLE, typename PRED >
   void pred_quick_sort(ITERABLE & iterable, PRED pred);

   template < typename ITERABLE, typename PRED >
   void pred_quick_sort_desc(ITERABLE & iterable, PRED pred);





   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_swap_quick_sort(ITERABLE & iterable, PRED pred, SWAP swap, bool bAsc);

   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_swap_quick_sort(ITERABLE & iterable, PRED pred, SWAP swap);

   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_swap_quick_sort_desc(ITERABLE & iterable, PRED pred, SWAP swap);






   template < typename ITERABLE, typename INDEX_ARRAY >
   void get_quick_sort(const ITERABLE & iterable, INDEX_ARRAY & ia);

   template < typename ITERABLE, typename INDEX_ARRAY  >
   void get_quick_sort_ci(const ITERABLE & iterable, INDEX_ARRAY & ia);

   template <class T>
   void sort(T & t1, T & t2);

   template <class T>
   void sort_non_negative(T & t1, T & t2);

   template <class T>
   void sort(T & t1, T & t2);

   template < typename TYPE, typename TYPE2 >
   void swap(TYPE & a, TYPE2 & b);

   template < typename TYPE, typename TYPE2 >
   void sort_non_negative(TYPE & t1, TYPE2 & t2);

   template < typename TYPE, typename TYPE2>
   index numeric_compare(const TYPE & a, const TYPE2 & b);

   template < typename TYPE, typename TYPE2>
   index less_than_compare(const TYPE & a, const TYPE2 & b);




   template < typename TYPE, typename TYPE2 >
   index less_than_compare(const TYPE & a, const TYPE2 & b) // uses only the less than implementation
   {
      
      if(a < b)
         return -1;
      else if(b < a)
         return 1;
      else
         return 0;

   }

   template < typename TYPE, typename TYPE2 >
   void sort_non_negative(TYPE & t1, TYPE2 & t2)
   {
      if (t1 < ::numeric_info<T>::null())
      {
         return;
      }
      if (t2 < ::numeric_info<T>::null())
      {
         return;
      }
      if (t1 > t2)
      {
         T t = t2;
         t2 = t1;
         t1 = t;
      }
   }


   template < typename TYPE, typename TYPE2>
   void swap(TYPE & a, TYPE2 & b)
   {
      
      auto acopy = a;
      
      a = b;
      
      b= acopy;

   }

   template < typename TYPE, typename TYPE2>
   index numeric_compare(const TYPE & a, const TYPE2 & b)
   {
      
      return a - b;

   }



   template < typename ITERABLE >
   void quick_sort(ITERABLE & iterable, bool bAsc)
   {

      if (bAsc)
      {

         quick_sort(iterable);

      }
      else
      {

         quick_sort_desc(iterable);

      }

   }

   template < typename ITERABLE >
   void quick_sort(ITERABLE & iterable)
   {

      pred_quick_sort(iterable, [](auto & a, auto & b) { return a < b;  });

   }

   template < typename ITERABLE >
   void quick_sort_desc(ITERABLE & iterable)
   {

      pred_quick_sort_desc(iterable, [](auto & a, auto & b) { return a < b;  });

   }

   template < typename ITERABLE >
   void quick_sort_ci(ITERABLE & iterable, bool bAsc)
   {

      if (bAsc)
      {

         quick_sort_ci(iterable);

      }
      else
      {

         quick_sort_ci_desc(iterable);

      }

   }

   template < typename ITERABLE >
   void quick_sort_ci(ITERABLE & iterable)
   {

      pred_quick_sort(iterable, [](auto & a, auto & b) { return stricmp(a, b) < 0;  });

   }

   template < typename ITERABLE >
   void quick_sort_ci_desc(ITERABLE & iterable)
   {

      pred_quick_sort_desc(iterable, [](auto & a, auto & b) { return stricmp(a, b) < 0;  });

   }






   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort(ITERABLE & iterable, SWAP swap, bool bAsc)
   {

      if (bAsc)
      {

         swap_quick_sort(iterable, swap);

      }
      else
      {

         swap_quick_sort_desc(iterable, swap);

      }

   }

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort(ITERABLE & iterable, SWAP swap)
   {

      pred_swap_quick_sort(iterable, [](auto & a, auto &b) {return a < b; }, swap);

   }

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_desc(ITERABLE & iterable, SWAP swap)
   {

      pred_swap_quick_sort(iterable, [](auto & a, auto &b) {return b < a; }, swap);

   }

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci(ITERABLE & iterable, SWAP swap, bool bAsc)
   {

      if (bAsc)
      {

         swap_quick_sort_ci(iterable, swap);

      }
      else
      {

         swap_quick_sort_ci_desc(iterable, swap);

      }

   }


   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci(ITERABLE & iterable, SWAP swap)
   {

      pred_swap_quick_sort(iterable, [](auto & a, auto &b) {return stricmp(a, b) < 0; }, swap);

   }

   template < typename ITERABLE, typename SWAP >
   void swap_quick_sort_ci_desc(ITERABLE & iterable, SWAP swap)
   {

      pred_swap_quick_sort(iterable, [](auto & a, auto &b) {return stricmp(b, a) < 0; }, swap);

   }







   template < typename ITERABLE, typename PRED >
   void pred_quick_sort(ITERABLE & iterable, PRED pred, bool bAsc)
   {

      if (bAsc)
      {

         pred_quick_sort(iterable, pred);

      }
      else
      {

         pred_quick_sort_desc(iterable, pred);

      }

   }

   template < typename ITERABLE, typename PRED >
   void pred_quick_sort(ITERABLE & iterable, PRED pred)
   {

      pred_swap_quick_sort(iterable, pred, [](auto & it1, auto & it2) {});

   }

   template < typename ITERABLE, typename PRED >
   void pred_quick_sort_desc(ITERABLE & iterable, PRED pred)
   {

      pred_swap_quick_sort_desc(iterable, pred, [](auto & it1, auto & it2) {});

   }





   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_swap_quick_sort(ITERABLE & iterable, PRED pred, SWAP swap, bool bAsc)
   {


      if (bAsc)
      {

         pred_swap_quick_sort(iterable, pred, swap);

      }
      else
      {

         pred_swap_quick_sort_desc(iterable, pred, swap);

      }

   }

   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_quick_sort_desc(ITERABLE & iterable, PRED pred, SWAP swap)
   {

      pred_swap_quick_sort_desc(iterable, [](auto & a, auto & b) { return pred(b, a); }, swap);

   }


   template < typename ITERABLE, typename PRED, typename SWAP >
   void pred_swap_quick_sort(ITERABLE & iterable, PRED pred, SWAP swap)
   {

      ::array < typename ITERABLE::iterator > stackLowerBound;
      ::array < typename ITERABLE::iterator > stackUpperBound;
      typename ITERABLE::iterator iLowerBound;
      typename ITERABLE::iterator iUpperBound;
      typename ITERABLE::iterator iLPos, iUPos, iMPos;

      if (iterable.get_size() >= 2)
      {
         stackLowerBound.push(iterable.begin());
         stackUpperBound.push(iterable.upper_bound());
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     goto mid_loop_break;
                  if (pred(*iUPos, *iMPos))
                  {
                     iterable.swap(iMPos, iUPos);
                     swap(iMPos, iUPos);
                     break;
                  }
                  iUPos--;
               }
               iMPos = iUPos;
               while (true)
               {
                  if (iMPos == iLPos)
                     goto mid_loop_break;
                  if (pred(*iMPos, *iLPos))
                  {
                     iterable.swap(iLPos, iMPos);
                     swap(iMPos, iUPos);
                     break;
                  }
                  iLPos++;
               }
               iMPos = iLPos;
            }
         mid_loop_break:
            if (iterable.valid_iter(iLowerBound, iMPos - 1))
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iterable.valid_iter(iMPos + 1, iUpperBound))
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }
   }


   template < typename ITERABLE, typename INDEX_ARRAY >
   void get_quick_sort(const ITERABLE & iterable, INDEX_ARRAY & ia)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      typename ITERABLE::iterator iLowerBound;
      typename ITERABLE::iterator iUpperBound;
      typename ITERABLE::iterator iLPos, iUPos, iMPos;
      TYPE t;
      ia.remove_all();
      ::lemon::array::append_sequence(ia, (typename ITERABLE::iterator)0, (typename ITERABLE::iterator)get_upper_bound());
      if (iterable.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(iterable.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     goto mid_loop_break;
                  if (iterable.element_at(ia[iUPos]) <  iterable.element_at(ia[iMPos]))
                  {
                     typename ITERABLE::iterator i = ia[iMPos];
                     ia[iMPos] = ia[iUPos];
                     ia[iUPos] = i;
                     break;
                  }
                  iUPos--;
               }
               iMPos = iUPos;
               while (true)
               {
                  if (iMPos == iLPos)
                     goto mid_loop_break;

                  if (iterable.element_at(ia[iMPos]) <  iterable.element_at(ia[iLPos]))
                  {
                     typename ITERABLE::iterator i = ia[iLPos];
                     ia[iLPos] = ia[iMPos];
                     ia[iMPos] = i;
                     break;
                  }
                  iLPos++;
               }
               iMPos = iLPos;
            }
            mid_loop_break:
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }

   }


   template < typename ITERABLE, typename INDEX_ARRAY >
   void get_quick_sort_ci(const ITERABLE & iterable, INDEX_ARRAY & ia)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      typename ITERABLE::iterator iLowerBound;
      typename ITERABLE::iterator iUpperBound;
      typename ITERABLE::iterator iLPos, iUPos, iMPos;
      TYPE t;
      ia.remove_all();
      ::lemon::array::append_sequence(ia, (typename ITERABLE::iterator)0, (typename ITERABLE::iterator)get_upper_bound());
      if (iterable.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(iterable.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     goto mid_loop_break;
                  if (iterable.element_at(ia[iUPos]).CompareNoCase(iterable.element_at(ia[iMPos])) < 0)
                  {
                     typename ITERABLE::iterator i = ia[iMPos];
                     ia[iMPos] = ia[iUPos];
                     ia[iUPos] = i;
                     break;
                  }
                  iUPos--;
               }
               iMPos = iUPos;
               while (true)
               {
                  if (iMPos == iLPos)
                     goto mid_loop_break;

                  if (iterable.element_at(ia[iMPos]).CompareNoCase(iterable.element_at(ia[iLPos])) < 0)
                  {
                     typename ITERABLE::iterator i = ia[iLPos];
                     ia[iLPos] = ia[iMPos];
                     ia[iMPos] = i;
                     break;
                  }
                  iLPos++;
               }
               iMPos = iLPos;
            }
        mid_loop_break:
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }

   }


   template < typename iterator, typename PRED >
   void quick_sort(const iterator & a, const iterator & b, PRED pred)
   {
      typename iterator::BASE_TYPE t;
      raw_array < iterator > stackLowerBound;
      raw_array < iterator > stackUpperBound;
      iterator iLowerBound;
      iterator iUpperBound;
      iterator iLPos,iUPos,iMPos;
      //   uint32_t t;

      if(a.get_count() >= 2)
      {
         stackLowerBound.push(a);
         stackUpperBound.push(b);
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
                  if(pred(*iMPos,*iUPos))
                     --iUPos;
                  else
                  {
                     t = *iMPos;
                     *iMPos = *iUPos;
                     *iUPos = t;
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
                  if(pred(*iLPos,*iMPos))
                     ++iLPos;
                  else
                  {
                     t =*iMPos;
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

   };





   template < typename ITERABLE >
   bool sort_find_index(ITERABLE & a, typename ITERABLE::BASE_ARG_TYPE t, index & iIndex, index iStart, index iEnd)
   {
      if(a.get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      index iCompare;

      while(true)
      {
         iIndex = (iUpperBound + iLowerBound) / 2;
         iCompare = SortCompare((ARG_TYPE) a.element_at(iIndex), (ARG_TYPE) t);
         if(iCompare == 0)
         {
            return true;
         }
         else if(iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
               break;
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iLowerBound;
               break;
            }
         }
         if(iUpperBound < iLowerBound)
            break;

      }
      return false;

   }

   template < typename ITERABLE >
   bool sort_find_index(ITERABLE & a, typename ITERABLE::BASE_ARG_TYPE t, index & iIndex)
   {
      return sort_find_index(a, t, iIndex, 0, a.get_count() - 1);
   }


   //template < class ITERABLE >
   //inline bool sort_find(ITERABLE & a, typename ARRAY::BASE_ARG_TYPE arg,index & iIndex,index iStart,index iEnd)
   //{
   //   if(a.get_size() == 0)
   //   {
   //      return false;
   //   }
   //   index iLowerBound = iStart;
   //   index iMaxBound = iEnd;
   //   index iUpperBound = iMaxBound;
   //   memory_offset_t iCompare;
   //   // do binary search
   //   iIndex = (iUpperBound + iLowerBound) / 2;
   //   while(iUpperBound - iLowerBound >= 8)
   //   {
   //      iCompare = CompareElements(a.element_at(iIndex),arg);
   //      if(iCompare == 0)
   //      {
   //         return true;
   //      }
   //      else if(iCompare > 0)
   //      {
   //         iUpperBound = iIndex - 1;
   //         if(iUpperBound < 0)
   //         {
   //            iIndex = 0;
   //            break;
   //         }
   //      }
   //      else
   //      {
   //         iLowerBound = iIndex + 1;
   //         if(iLowerBound > iMaxBound)
   //         {
   //            iIndex = iMaxBound + 1;
   //            break;
   //         }
   //      }
   //      iIndex = (iUpperBound + iLowerBound) / 2;
   //   }
   //   // do sequential search
   //   while(iIndex < a.get_count())
   //   {
   //      iCompare = CompareElements(a.element_at(iIndex),arg);
   //      if(iCompare == 0)
   //         return true;
   //      else if(iCompare < 0)
   //         iIndex++;
   //      else
   //         break;
   //   }
   //   if(iIndex >= a.get_count())
   //      return false;
   //   while(iIndex >= 0)
   //   {
   //      iCompare = CompareElements(a.element_at(iIndex),arg);
   //      if(iCompare == 0)
   //         return true;
   //      else if(iCompare > 0)
   //         iIndex--;
   //      else
   //         break;
   //   }
   //   iIndex++;
   //   return false;

   //}



} // namespace sort


