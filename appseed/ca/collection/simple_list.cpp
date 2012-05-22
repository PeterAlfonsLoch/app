#include "framework.h"

/////////////////////////////////////////////////////////////////////////////
// simple_list

void base_simple_list::add_head(void * p)
{
   ASSERT(p != NULL);
   ASSERT(*GetNextPtr(p) == NULL);

   *GetNextPtr(p) = m_pHead;
   m_pHead = p;
}

<<<<<<< .mine
WINBOOL base_simple_list::remove(void * p)
=======
bool base_simple_list::remove(void * p)
>>>>>>> .r4408
{
   ASSERT(p != NULL);

   if (m_pHead == NULL)
      return false;

<<<<<<< .mine
   WINBOOL bResult = FALSE;
=======
   bool bResult = false;
>>>>>>> .r4408
   if (m_pHead == p)
   {
      m_pHead = *GetNextPtr(p);
      DEBUG_ONLY(*GetNextPtr(p) = NULL);
      bResult = true;
   }
   else
   {
      void * pTest = m_pHead;
      while (pTest != NULL && *GetNextPtr(pTest) != p)
         pTest = *GetNextPtr(pTest);
      if (pTest != NULL)
      {
         *GetNextPtr(pTest) = *GetNextPtr(p);
         DEBUG_ONLY(*GetNextPtr(p) = NULL);
         bResult = true;
      }
   }
   return bResult;
}

