#pragma once


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
class key_sort_array
{
public:
   key_sort_array();
   virtual ~key_sort_array();

   void SetKeyProperty(KEY (TYPE::* lpfnKeyProperty)());
   bool FindFirst(KEY k, int32_t & iIndex);
   bool FindFirst(KEY k, int32_t & iIndex, int32_t iStart, int32_t iEnd);

   int32_t add(ARG_TYPE type);

   int32_t GetSize();

   TYPE & ElementAt(int32_t iIndex);

protected:


   KEY (TYPE::* m_lpfnKeyProperty)();
   // ARRAY must implement:
   // InsertAt(int32_t iIndex, ARG_TYPE)
   // TYPE & ElementAt(int32_t iIndex)
   // int32_t GetSize()
   ARRAY m_array;

};
template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
key_sort_array()
{
}
template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
~key_sort_array()
{
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
TYPE & key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
ElementAt(int32_t iIndex)
{
   return m_array.ElementAt(iIndex);
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
bool key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
FindFirst(KEY k, int32_t & iIndex)
{
   return FindFirst(k, iIndex, 0, GetSize() - 1);
}


template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
bool key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
FindFirst(KEY k, int32_t & iIndex, int32_t iStart, int32_t iEnd)
{
   if(GetSize() == 0)
   {
      return false;
   }
   int32_t iLowerBound = iStart;
   int32_t iMaxBound = iEnd;
   int32_t iUpperBound = iMaxBound;

   while(true)
   {
      iIndex = (iUpperBound + iLowerBound) / 2;
      if((ElementAt(iIndex).*m_lpfnKeyProperty)() == k)
      {
         while(iIndex > 0)
         {
            if((ElementAt(iIndex - 1).*m_lpfnKeyProperty)() == k)
            {
               iIndex--;
            }
            else
            {
               break;
            }
         }
         return true;
      }
      else if((ElementAt(iIndex).*m_lpfnKeyProperty)() > k)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
         if(iUpperBound < iLowerBound)
         {
            iIndex = iLowerBound;
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
         if(iUpperBound < iLowerBound)
         {
            iIndex = iLowerBound;
            break;
         }
      }

   }
   return false;

}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
int32_t key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
add(ARG_TYPE t)
{
   int32_t iIndex = 0;
   FindFirst((t.*m_lpfnKeyProperty)(), iIndex);
   m_array.InsertAt(iIndex, t);
   return iIndex;
}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
int32_t key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
GetSize()
{
   return m_array.GetSize();
}

