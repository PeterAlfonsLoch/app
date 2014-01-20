#include "framework.h"

str_sort_array::str_sort_array()
{
   // Array is is_empty. Be optimistic. Assume that is sorted.
   m_bSorted = true;
   m_pfnCompare = Compare;
}

str_sort_array::~str_sort_array()
{

}


void str_sort_array::Sort()
{
   int32_t (*fCompare)(const char *, const char *) = m_pfnCompare;
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   string str;

   if(this->get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(this->get_size() - 1);
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
               if(fCompare(m_stra.element_at(iMPos), m_stra.element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  _Swap(iMPos, iUPos);
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
               if(fCompare(m_stra.element_at(iLPos), m_stra.element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  _Swap(iMPos, iLPos);
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
   m_bSorted = true;
}


index str_sort_array::SortFind(const char * lpcsz)
{
   int32_t (*fCompare)(const char *, const char *) = m_pfnCompare;
   if(!m_bSorted)
      Sort();

   index iPos, iLoPos, iHiPos;
   int32_t iCompare;
   iLoPos = 0;
   iHiPos = this->get_size() - 1;
   string strFind(lpcsz);
   while(iLoPos <= iHiPos)
   {
      iPos = (iHiPos + iLoPos) / 2;
      iCompare = fCompare(strFind, this->element_at(iPos));
      if(iCompare == 0)
      {
         return iPos;
      }
      else if(iCompare > 0)
      {
         iLoPos = iPos + 1;
      }
      else
      {
         iHiPos = iPos - 1;
      }
   }
   return -1;
}


/*int32_t stringa::SortFindNoCase(const char * lpcsz)
{
    int32_t iPos, iLoPos, iHiPos;
    int32_t iCompare;
    iLoPos = 0;
    iHiPos = this->get_size() - 1;
    string strFind(lpcsz);
    while(iLoPos <= iHiPos)
    {
        iPos = (iHiPos + iLoPos) / 2;
        iCompare = _tcsicmp(strFind, this->element_at(iPos));
//      TRACE("strFind %s this->element_at(iPos) %s\n", strFind, this->element_at(iPos));
        // if(strFind == this->element_at(iPos))
        if(iCompare == 0)
        {
            return iPos;
        }
        // strFind > this->element_at(iPos)
        else if(iCompare > 0)
        {
            iLoPos = iPos + 1;
        }
        // strFind < this->element_at(iPos)
        else
        {
            iHiPos = iPos - 1;
        }


    }

    return -1;
}*/

void str_sort_array::SetCompareFunction(int32_t (__cdecl *fCompare)(const char *,const char *))
{
   m_pfnCompare = fCompare;
}
