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
   void quick_sort(
      array < TYPE, ARG_TYPE > & a)
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
   void quick_sort(iterator  & a,iterator  & b)
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
                  if(COMPARE().(*iMPos,*iUPos))
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
                  if(COMPARE().(*iLPos,*iMPos))
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


   void CLASS_DECL_AXIS quick_sort(
      index iSize,
      array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
      array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
      array < void *, void * > & comparearga,
      array < void *, void * > & swaparga);



   template <class TYPE, class ARG_TYPE>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      int32_t (* fCompare)(const ARG_TYPE, const ARG_TYPE))
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

   template <class TYPE, class ARG_TYPE>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      index (* fCompare)(const TYPE &, const TYPE &))
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

   template <class TYPE, class ARG_TYPE>
   void quick_sort(
      array < TYPE, ARG_TYPE > & a,
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

   namespace array // hyper generic array template sort
      ////////////////////////////////////////////////////
   {
      template <class ARRAY_TYPE, class ARG_TYPE>
      void quick_sort(
         ARRAY_TYPE  & a,
         index (* lpfnCompare)(ARG_TYPE, ARG_TYPE))
      {
         index_array stackLowerBound;
         index_array stackUpperBound;
         index iLowerBound;
         index iUpperBound;
         index iLPos, iUPos, iMPos;
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
                     if(lpfnCompare((ARG_TYPE) a.element_at(iMPos), (ARG_TYPE) a.element_at(iUPos)) <= 0)
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
                     if(lpfnCompare((ARG_TYPE) a.element_at(iLPos), (ARG_TYPE) a.element_at(iMPos)) <= 0)
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
                  void * pCompare,
                  compare_interface::_FUNCTION_Compare fCompare)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      compare_interface * pinterface = (compare_interface *) pCompare;

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


   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortAsc(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list)
   {
      ::raw_array < POSITION > stackLowerBound;
      ::raw_array < POSITION > stackUpperBound;
      POSITION iLowerBound;
      POSITION iUpperBound;
      POSITION iLPos, iUPos, iMPos;

      if(list.get_size() >= 2)
      {
         stackLowerBound.push(list.get_head_position());
         stackUpperBound.push(list.get_tail_position());
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
                  if(list.get_at(iMPos) < list.get_at(iUPos))
                     list.get_previous(iUPos);
                  else
                  {
                     list.swap(iMPos, iUPos);
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
                  if(list.get_at(iLPos) < list.get_at(iMPos))
                     list.get_next(iLPos);
                  else
                  {
                     list.swap(iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(list.position_index(iLowerBound) < list.position_index(iMPos) - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(list.position_index(iMPos) + 1 < list.position_index(iUpperBound))
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
   void QuickSortDesc(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list)
   {
      ::raw_array < POSITION > stackLowerBound;
      ::raw_array < POSITION > stackUpperBound;
      POSITION iLowerBound;
      POSITION iUpperBound;
      POSITION iLPos, iUPos, iMPos;

      if(list.get_size() >= 2)
      {
         stackLowerBound.push(list.get_head_position());
         stackUpperBound.push(list.get_tail_position());
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
                  if(list.get_at(iUPos) < list.get_at(iMPos))
                     list.get_previous(iUPos);
                  else
                  {
                     list.swap(iMPos, iUPos);
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
                  if(list.get_at(iMPos) < list.get_at(iLPos))
                     list.get_next(iLPos);
                  else
                  {
                     list.swap(iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(list.position_index(iLowerBound) < list.position_index(iMPos) - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(list.position_index(iMPos) + 1 < list.position_index(iUpperBound))
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }
   }


} // namespace sort




//#include "collection_sort_array.h"
#include "collection_key_sort_array.h"


template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE >::quick_sort(bool bAsc)
{
   if(bAsc)
   {
      sort::QuickSortAsc(*this);
   }
   else
   {
      sort::QuickSortDesc(*this);
   }
}




template < class TYPE >
void numeric_array < TYPE >::
quick_sort(bool bAsc)
{
   if(bAsc)
   {
      sort::QuickSortAsc(*this);
   }
   else
   {
      sort::QuickSortDesc(*this);
   }
}



template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
quick_sort(bool bAsc)
{
   if(bAsc)
   {
      sort::QuickSortAsc(*this);
   }
   else
   {
      sort::QuickSortDesc(*this);
   }
}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
void key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
SetKeyProperty(KEY (TYPE::* lpfnKeyProperty)())
{
   m_lpfnKeyProperty= lpfnKeyProperty;
   sort::QuickSortByKey < KEY, TYPE, ARG_TYPE >(
      m_array,
      m_lpfnKeyProperty);
}

