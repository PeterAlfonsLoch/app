#include "framework.h"


void base_simple_list::add_head(void * p)
{
//   ASSERT(p != ::null());
//   ASSERT(*GetNextPtr(p) == ::null());

   *GetNextPtr(p) = m_pHead;
   m_pHead = p;
}

bool base_simple_list::remove(void * p)
{
//   ASSERT(p != ::null());

   if (m_pHead == ::null())
      return FALSE;

   bool bResult = FALSE;
   if (m_pHead == p)
   {
      m_pHead = *GetNextPtr(p);
//      DEBUG_ONLY(*GetNextPtr(p) = ::null());
      bResult = TRUE;
   }
   else
   {
      void * pTest = m_pHead;
      while (pTest != ::null() && *GetNextPtr(pTest) != p)
         pTest = *GetNextPtr(pTest);
      if (pTest != ::null())
      {
         *GetNextPtr(pTest) = *GetNextPtr(p);
  //       DEBUG_ONLY(*GetNextPtr(p) = ::null());
         bResult = TRUE;
      }
   }
   return bResult;
}

