#pragma once


namespace sort
{

   template <class T> void sort( T & t1, T & t2)
   {
      if(t1 > t2)
      {
         T t = t2;
         t2 = t1;
         t1 = t;
      }
   }

   template <class T> void sort_non_negative(T & t1, T & t2)
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

   template <class TYPE>
   static index NumericCompare(const TYPE * ptA, const TYPE * ptB);

//    static index DWordCompare(const index dwA, const index dwB);

//   static void BubbleSort(LPINT lpInt, index size);

//   static void quick_sort(
  //    array<uint32_t, uint32_t> & a,
    //  index (*fCompare)(const index, const index),
      //void (*swap)(void * lpVoidSwapArg, index iA, index iB),
      //void * lpVoidSwapArg);

   template <class A> static index  CompareTkPosition(const A a1, const A a2);

   template <class TYPE>
   index NumericCompare(const TYPE * pta, const TYPE * ptb)
   {
      if(*pta > *ptb)
         return 1;
      else if(*pta < *ptb)
         return -1;
      else
         return 0;
   }


   template <class A> static index  CompareTkPosition(const A a1, const A a2)
   {
      if(a1.m_tkPosition > a2.m_tkPosition)
         return 1;
      else if(a1.m_tkPosition > a2.m_tkPosition)
         return -1;
      else
         return 0;
   }

   template <class TYPE, class ARG_TYPE>
   void SwapArray(
      array<TYPE, ARG_TYPE> & a,
      index   iA,
      index iB)
   {
      TYPE t;
      t = a.get_at(iA);
      a.set_at(iA, a.get_at(iB));
      a.set_at(iB, t);
   };
   /*template <class TYPE, class ARG_TYPE>
   void quick_sort(
   array<TYPE, ARG_TYPE> & array,
   index (* fCompare)(const TYPE *, const TYPE *),
   void (* fSwap)(TYPE *, TYPE *));*/

   /*template <class TYPE, class ARG_TYPE>
   void swap(
   CarrayInterface<TYPE, ARG_TYPE> * parray,
   index   iA,
   index iB)
   {
   TYPE t;
   t = parray->element_at(iA);
   parray->set_at(iA, parray->element_at(iB));
   parray->set_at(iB, t);
   };*/

   template <class TYPE>
   void  swap(
      TYPE * pA,
      TYPE * pB)
   {
      TYPE ACopy = *pA;
      *pA = *pB;
      *pB= ACopy;
   };

   template <class TYPE>
   index CompareAscending(
      TYPE * pA,
      TYPE * pB)
   {
      return *pA - *pB;
   };

   template < class TYPE, class ARG_TYPE, class FIRST>
   void quick_sort(array < TYPE, ARG_TYPE > & a)
   {
      TYPE t;
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;
      //   uint32_t t;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
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
                  if(FIRST::Compare(&a.element_at(iMPos), &a.element_at(iUPos)))
                     iUPos--;
                  else
                  {
                     t = a.element_at(iMPos);
                     a.element_at(iMPos) = a.element_at(iUPos);
                     a.element_at(iUPos) = t;
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
                  if(FIRST::Compare(&a.element_at(iLPos), &a.element_at(iMPos)))
                     iLPos++;
                  else
                  {
                     t = a.element_at(iMPos);
                     a.element_at(iMPos) = a.element_at(iLPos);
                     a.element_at(iLPos) = t;
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


   template <class TYPE, class ARG_TYPE, typename SWAP>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      SWAP swap)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
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
                     break;
                  if (a.get_at(iMPos) <= a.get_at(iUPos))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
                     swap(iUPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while (true)
               {
                  if (iMPos == iLPos)
                     break;
                  if (a.get_at(iLPos) <= a.get_at(iMPos))
                     iLPos++;
                  else
                  {
                     a.swap(iMPos, iLPos);
                     swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
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



   template <class TYPE, class ARG_TYPE>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      index fCompare(const ARG_TYPE, const ARG_TYPE),
      void swap(void * lpVoidSwapArg, index iA, index iB),
      void * lpVoidSwapArg)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
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
                  if(fCompare(a.get_at(iMPos), a.get_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
                     swap(lpVoidSwapArg, iUPos, iMPos);
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
                  if(fCompare(a.get_at(iLPos), a.get_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     a.swap(iMPos, iLPos);
                     swap(lpVoidSwapArg, iLPos, iMPos);
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


   template < class iterator,class COMPARE = ::comparison::less < typename iterator::BASE_TYPE, typename iterator::BASE_ARG_TYPE > >
   void quick_sort(const iterator & a, const iterator & b)
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
                  if(COMPARE().operator()(*iMPos,*iUPos))
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
                  if(COMPARE().operator()(*iLPos,*iMPos))
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


   typedef void (*ARG_SWAP_FUNCTION)(void * lpVoidSwapArg, index,  index);
   typedef int32_t (*ARG_COMPARE_FUNCTION)(void * lpVoidCompareArg,  index,  index);


   void CLASS_DECL_AURA quick_sort(
      index iSize,
      array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
      array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
      void_ptra & comparearga,
      void_ptra & swaparga);



   //template <class TYPE, class ARG_TYPE>
   //void quick_sort(
   //   array<TYPE, ARG_TYPE> & a,
   //   int32_t (* fCompare)(const ARG_TYPE, const ARG_TYPE))
   //{
   //   index_array stackLowerBound;
   //   index_array stackUpperBound;
   //   index iLowerBound;
   //   index iUpperBound;
   //   index iLPos, iUPos, iMPos;
   //   TYPE t;

   //   if(a.get_size() >= 2)
   //   {
   //      stackLowerBound.push(0);
   //      stackUpperBound.push(a.get_size() - 1);
   //      while(true)
   //      {
   //         iLowerBound = stackLowerBound.pop();
   //         iUpperBound = stackUpperBound.pop();
   //         iLPos = iLowerBound;
   //         iMPos = iLowerBound;
   //         iUPos = iUpperBound;
   //         while(true)
   //         {
   //            while(true)
   //            {
   //               if(iMPos == iUPos)
   //                  break;
   //               if(fCompare(a.element_at(iMPos), a.element_at(iUPos)) <= 0)
   //                  iUPos--;
   //               else
   //               {
   //                  //    t = a.get_at(iMPos);
   //                  //  a.set_at(iMPos, a.get_at(iUPos));
   //                  //a.set_at(iUPos, t);
   //                  a.swap(iMPos, iUPos);
   //                  break;
   //               }
   //            }
   //            if(iMPos == iUPos)
   //               break;
   //            iMPos = iUPos;
   //            while(true)
   //            {
   //               if(iMPos == iLPos)
   //                  break;
   //               if(fCompare(a.element_at(iLPos), a.element_at(iMPos)) <= 0)
   //                  iLPos++;
   //               else
   //               {
   //                  //                        t = a.get_at(iMPos);
   //                  //                      a.set_at(iMPos, a.get_at(iLPos));
   //                  //                    a.set_at(iLPos, t);
   //                  a.swap(iLPos, iMPos);
   //                  break;
   //               }
   //            }
   //            if(iMPos == iLPos)
   //               break;
   //            iMPos = iLPos;
   //         }
   //         if(iLowerBound < iMPos - 1)
   //         {
   //            stackLowerBound.push(iLowerBound);
   //            stackUpperBound.push(iMPos - 1);
   //         }
   //         if(iMPos + 1 < iUpperBound)
   //         {
   //            stackLowerBound.push(iMPos + 1);
   //            stackUpperBound.push(iUpperBound);
   //         }
   //         if(stackLowerBound.get_size() == 0)
   //            break;
   //      }
   //   }
   //}

   template <class TYPE, class ARG_TYPE = const TYPE &>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      index (* fCompare)(ARG_TYPE, ARG_TYPE))
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
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
                  if(fCompare(a.element_at(iMPos), a.element_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     //    t = a.get_at(iMPos);
                     //  a.set_at(iMPos, a.get_at(iUPos));
                     //a.set_at(iUPos, t);
                     a.swap(iMPos, iUPos);
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
                  if(fCompare(a.element_at(iLPos), a.element_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     //                        t = a.get_at(iMPos);
                     //                      a.set_at(iMPos, a.get_at(iLPos));
                     //                    a.set_at(iLPos, t);
                     a.swap(iLPos, iMPos);
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

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortAsc(comparable_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
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
                  if(a.element_at(iMPos) <= a.element_at(iUPos))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
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
                  if(a.element_at(iLPos) <= a.element_at(iMPos))
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
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

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortDesc(comparable_array < TYPE, ARG_TYPE, ARRAY_TYPE > & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
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
                  if(a.element_at(iUPos) <= a.element_at(iMPos))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
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
                  if(a.element_at(iMPos) <= a.element_at(iLPos))
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
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


   template <class TYPE >
   void QuickSortAsc(numeric_array < TYPE > & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
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
                  if(a.element_at(iMPos) <= a.element_at(iUPos))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
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
                  if(a.element_at(iLPos) <= a.element_at(iMPos))
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
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

   template <class TYPE >
   void QuickSortDesc(numeric_array < TYPE > & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
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
                  if(a.element_at(iUPos) < a.element_at(iMPos))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
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
                  if(a.element_at(iMPos) < a.element_at(iLPos))
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
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

   template <class KEY, class TYPE, class ARG_TYPE>
   void QuickSortByKey(
      array<TYPE, ARG_TYPE> & a,
      KEY (TYPE::* fKey)())
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;
      TYPE t;

      if(a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
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
                  if((a.element_at(iMPos).*fKey)() < (a.element_at(iUPos).*fKey)())
                     iUPos--;
                  else
                  {
                     //    t = a.get_at(iMPos);
                     //  a.set_at(iMPos, a.get_at(iUPos));
                     //a.set_at(iUPos, t);
                     a.swap(iMPos, iUPos);
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
                  if((a.element_at(iLPos).*fKey)() < (a.element_at(iMPos).*fKey)())
                     iLPos++;
                  else
                  {
                     //                        t = a.get_at(iMPos);
                     //                      a.set_at(iMPos, a.get_at(iLPos));
                     //                    a.set_at(iLPos, t);
                     a.swap(iLPos, iMPos);
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

   template<class ARG_TYPE>
   inline index SortCompare(ARG_TYPE t1, ARG_TYPE t2)
   {
      return t1 - t2;
   }


   template <class TYPE, class ARG_TYPE>
   bool SortFind(array < TYPE, ARG_TYPE > & a, ARG_TYPE t, index & iIndex, index iStart, index iEnd)
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

   template < class TYPE, class ARG_TYPE >
   bool SortFind(array < TYPE, ARG_TYPE > & a, ARG_TYPE t, index & iIndex)
   {
      return SortFind(a, t, iIndex, 0, a.get_size() - 1);
   }

   template < class TYPE, class ARG_TYPE >
   void BubbleSortByLPGetSize(array < TYPE, ARG_TYPE > & a, bool bAsc = true);

   template < class TYPE, class ARG_TYPE >
   void BubbleSortByGetSize(array < TYPE, ARG_TYPE > & a, bool bAsc = true);

   template < class TYPE >
   void BubbleSortByPtrAtGetSize(
      spa(TYPE) & a,
      bool bAsc = true);

   template < class TYPE,class ARG_TYPE = const TYPE &,class DEFCONSTRUCTOR >
   void quick_sort(
      array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > & a,
      index (* lpfnCompare)(ARG_TYPE, ARG_TYPE));



   template < class TYPE, class ARG_TYPE >
   void BubbleSortByLPGetSize(
      array < TYPE, ARG_TYPE > & a,
      bool bAsc)
   {
      TYPE * t;
      if(bAsc)
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i)->get_size() > a.element_at(j)->get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }
      else
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i)->get_size() < a.element_at(j)->get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }

      return;
   }

   template < class TYPE, class ARG_TYPE >
   void BubbleSortByGetSize(
      array < TYPE, ARG_TYPE > & a,
      bool bAsc)
   {
      TYPE t;
      if(bAsc)
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i).get_size() > a.element_at(j).get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }
      else
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i).get_size() < a.element_at(j).get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }

      return;
   }

   template < class ARRAY >
   void BubbleSortByGetSize(
      ARRAY & a,
      bool bAsc)
   {
      typename ARRAY::BASE_TYPE t;
      if(bAsc)
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
            if(a.element_at(i).get_size() > a.element_at(j).get_size())
            {
               a.swap(i,j);
            }
            }
      }
      else
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
            if(a.element_at(i).get_size() < a.element_at(j).get_size())
            {
               a.swap(i,j);
            }

            }
      }

      return;
   }


   template < class TYPE >
   void BubbleSortByPtrAtGetSize(
      spa(TYPE) & a,
      bool bAsc)
   {
      TYPE t;
      if(bAsc)
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i)->get_size() > a.element_at(j)->get_size())
               {
                  a.swap(i, j);
               }
            }
      }
      else
      {
         for(index i = 0; i < a.get_size(); i++)
            for(index j = i + 1; j < a.get_size(); j++)
            {
               if(a.element_at(i)->get_size() < a.element_at(j)->get_size())
               {
                  a.swap(i, j);
               }

            }
      }

      return;
   }


   namespace array
   {

      template < typename ARRAY_TYPE >
      void quick_sort(
         ARRAY_TYPE  & a,
         index(* lpfnCompare)(typename ARRAY_TYPE::BASE_ARG_TYPE,typename ARRAY_TYPE::BASE_ARG_TYPE))
      {
         index_array stackLowerBound;
         index_array stackUpperBound;
         index iLowerBound;
         index iUpperBound;
         index iLPos,iUPos,iMPos;
         //   TYPE t;

         if(a.get_size() >= 2)
         {
            stackLowerBound.push(0);
            stackUpperBound.push(a.get_size() - 1);
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
                     if(lpfnCompare((typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iMPos),(typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iUPos)) <= 0)
                        iUPos--;
                     else
                     {
                        a.swap(iMPos,iUPos);
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
                     if(lpfnCompare((typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iLPos),(typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iMPos)) <= 0)
                        iLPos++;
                     else
                     {
                        a.swap(iLPos,iMPos);
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

      template < typename ARRAY_TYPE >
      void quick_sort(ARRAY_TYPE  & a,index(* lpfnCompare)(typename ARRAY_TYPE::BASE_ARG_TYPE,typename ARRAY_TYPE::BASE_ARG_TYPE),index_array & ia)
      {

         // minimum check
         if(ia.get_size() != a.get_size())
            throw invalid_argument_exception(::get_thread_app());

         index_array stackLowerBound;
         index_array stackUpperBound;
         index iLowerBound;
         index iUpperBound;
         index iLPos, iUPos, iMPos;
         //   uint32_t t;

         if(a.get_size() >= 2)
         {
            stackLowerBound.push(0);
            stackUpperBound.push(a.get_size() - 1);
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
                     if(lpfnCompare(a.element_at(ia[iMPos]),a.element_at(ia[iUPos])) <= 0)
                        iUPos--;
                     else
                     {
                        ia.swap(iMPos, iUPos);
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
                     if(lpfnCompare(a.element_at(ia[iLPos]),a.element_at(ia[iMPos])) <= 0)
                        iLPos++;
                     else
                     {
                        ia.swap(iLPos, iMPos);
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


      template < typename ARRAY_TYPE, typename PRED >
      void pred_sort(ARRAY_TYPE  & a, PRED pred)
      {

         index_array stackLowerBound;
         
         index_array stackUpperBound;
         
         index iLowerBound;

         index iUpperBound;

         index iLPos, iUPos, iMPos;

         if (a.get_size() >= 2)
         {
            
            stackLowerBound.push(0);
            
            stackUpperBound.push(a.get_size() - 1);

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
                     {

                        goto break_mid_loop;

                     }

                     if (pred(a[iUPos], a[iMPos]))
                     {
                        
                        a.swap(iMPos, iUPos);
                        
                        break;

                     }

                     iUPos--;

                  }
                  
                  iMPos = iUPos;

                  while (true)
                  {

                     if (iMPos == iLPos)
                     {

                        goto break_mid_loop;

                     }

                     if (pred(a[iMPos], a[iLPos]))
                     {
                        
                        a.swap(iLPos, iMPos);

                        break;

                     }

                     iLPos++;

                  }

                  iMPos = iLPos;

               }

            break_mid_loop:

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
               {

                  break;

               }

            }

         }

      }


   } // namespace array





























































   class compare_interface
   {
   public:
      typedef index (compare_interface::*_FUNCTION_Compare)(index, index);
   };

   // Sort "array" according to "fCompare" function
   // of "pCompare" interface


   template < class NUMERIC_ARRAY >
   void quick_sort(
                  NUMERIC_ARRAY & ar,
                  compare_interface * pinterface,
                  compare_interface::_FUNCTION_Compare fCompare)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      ///compare_interface * pinterface = (compare_interface *) pCompare;

      if(ar.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(ar.get_size() - 1);
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
                  if((pinterface->*fCompare)(ar[iMPos], ar[iUPos]) < 0)
                     iUPos--;
                  else
                  {
                     ar.swap(iMPos, iUPos);
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
                  if((pinterface->*fCompare)(ar[iLPos], ar[iMPos]) < 0)
                     iLPos++;
                  else
                  {
                     ar.swap(iLPos, iMPos);
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


   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE, typename PRED>
   void pred_quick_sort(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list, PRED pred)
   {

      if (list.get_size() < 2)
      {

         return;

      }

      typedef comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE >::node node;

      ::raw_array < node * > stackLowerBound;
      ::raw_array < node * > stackUpperBound;

      node * iLowerBound;
      node * iUpperBound;
      node * iLPos, * iUPos, * iMPos;

      stackLowerBound.push(list.m_phead);
      stackUpperBound.push(list.m_ptail);
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
                  goto break_mid_loop;
               if(pred(iUPos->m_value, iMPos->m_value))
               {
                  list.swap((POSITION) iMPos, (POSITION)iUPos);
                  break;
               }
               iUPos = iUPos->m_pprev;
            }
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  goto break_mid_loop;
               if (pred(iMPos->m_value, iLPos->m_value))
               {
                  list.swap((POSITION)iLPos, (POSITION)iMPos);
                  break;
               }
               iLPos = iLPos->m_pnext;
            }
            iMPos = iLPos;
         }
         break_mid_loop:
         if(iLowerBound != iMPos->m_pprev)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos->m_pprev);
         }
         if(iMPos->m_pnext != iUpperBound)
         {
            stackLowerBound.push(iMPos->m_pnext);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }

   }

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE, typename PRED>
   void pred_quick_sort_descending(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list, PRED pred)
   {

      pred_quick_sort(list, [](auto & a, autor & b) { return pred(b, a); })

   }

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE >
   void quick_sort(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list, bool bAscendent = true)
   {

      if (bAscendent)
      {
         
         pred_quick_sort(list, [](auto & a, auto & b) { return a < b; });

      }
      else
      {

         pred_quick_sort(list, [](auto & a, auto & b) { return b < a; });

      }



   }



   template < class ARRAY >
   inline bool sort_find(ARRAY & a, typename ARRAY::BASE_ARG_TYPE arg,index & iIndex,index iStart,index iEnd)
   {
      if(a.get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      memory_offset_t iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while(iUpperBound - iLowerBound >= 8)
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
         {
            return true;
         }
         else if(iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while(iIndex < a.get_count())
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare < 0)
            iIndex++;
         else
            break;
      }
      if(iIndex >= a.get_count())
         return false;
      while(iIndex >= 0)
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare > 0)
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }

   template < class ARRAY >
   void quick_sort(ARRAY & a, bool bAsc)
   {
      if(bAsc)
      {
         sort::QuickSortAsc(a);
      }
      else
      {
         sort::QuickSortDesc(a);
      }
   }


   template < typename ITERATOR>
   void quick_sort_iter(ITERATOR first, ITERATOR last)
   {

      auto & iterable = first.iterable();

      ASSERT(&iterable == &last.iterable());

      if (&iterable != &last.iterable())
      {

         return;

      }

      if (iterable.get_size() < 2)
      {

         return;

      }

      ::array < ITERATOR > stackLowerBound;
      ::array < ITERATOR > stackUpperBound;
      ITERATOR iLowerBound;
      ITERATOR iUpperBound;
      ITERATOR iLPos, iUPos, iMPos;

      stackLowerBound.push(first);
      stackUpperBound.push(last);

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
                  goto break_mid_loop;
               if (*iMPos < *iUPos)
               {
                  iterable.swap(iMPos, iUPos);
                  break;
               }
               iUPos--;

            }
            if (iMPos == iUPos)
               break;
            iMPos = iUPos;
            while (true)
            {
               if (iMPos == iLPos)
                  goto break_mid_loop;
               if (*iLPos < *iMPos)
               {
                  iterable.swap(iMPos, iLPos);
                  break;
               }
               iLPos++;
            }
            if (iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
      break_mid_loop:
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


} // namespace sort




//#include "collection_sort_array.h"
// #include "collection_key_sort_array.h"


//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//void comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE >::quick_sort(bool bAsc)
//{
//   if(bAsc)
//   {
//      sort::QuickSortAsc(*this);
//   }
//   else
//   {
//      sort::QuickSortDesc(*this);
//   }
//}







template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
quick_sort(bool bAscendent)
{

   sort::quick_sort(*this, bAscendent);

}

//template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
//void key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
//SetKeyProperty(KEY (TYPE::* lpfnKeyProperty)())
//{
//   m_lpfnKeyProperty= lpfnKeyProperty;
//   sort::QuickSortByKey < KEY, TYPE, ARG_TYPE >(
//      m_array,
//      m_lpfnKeyProperty);
//}
//
//
