#include "StdAfx.h"

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
   int (*fCompare)(const char *, const char *) = m_pfnCompare;
   dword_array stackLowerBound;
   dword_array stackUpperBound;
   int iLowerBound;
   int iUpperBound;
   int iLPos, iUPos, iMPos;
   string str;
   
   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_size() - 1);
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
   int (*fCompare)(const char *, const char *) = m_pfnCompare;
   if(!m_bSorted)
      Sort();

   int iPos, iLoPos, iHiPos;
   int iCompare;
   iLoPos = 0;
   iHiPos = get_size() - 1;
   string strFind(lpcsz);
   while(iLoPos <= iHiPos)
   {
      iPos = (iHiPos + iLoPos) / 2;
      iCompare = fCompare(strFind, element_at(iPos));
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


/*int stringa::SortFindNoCase(const char * lpcsz)
{
    int iPos, iLoPos, iHiPos;
    int iCompare;
    iLoPos = 0;
    iHiPos = get_size() - 1;
    string strFind(lpcsz);
    while(iLoPos <= iHiPos)
    {
        iPos = (iHiPos + iLoPos) / 2;
        iCompare = _tcsicmp(strFind, element_at(iPos));
//      TRACE("strFind %s element_at(iPos) %s\n", strFind, element_at(iPos));
        // if(strFind == element_at(iPos))
        if(iCompare == 0)
        {
            return iPos;
        }
        // strFind > element_at(iPos)
        else if(iCompare > 0)
        {
            iLoPos = iPos + 1;
        }
        // strFind < element_at(iPos)
        else
        {
            iHiPos = iPos - 1;
        }


    }

    return -1;
}*/

void str_sort_array::SetCompareFunction(int (__cdecl *fCompare)(const char *,const char *))
{
   m_pfnCompare = fCompare;
}
