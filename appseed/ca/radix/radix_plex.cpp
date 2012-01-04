#include "StdAfx.h"
#include "plex_heap.h"

#undef new

CLASS_DECL_ca plex_heap_alloc_array g_heap;

plex* PASCAL plex::create(plex*& pHead, UINT_PTR nMax, UINT_PTR cbElement)
{

   ::primitive::memory_size size = sizeof(plex) + nMax * cbElement + CA2_PALACE_SAFE_ZONE_BORDER_SIZE * 2;
   plex* p = (plex*) g_heap.alloc(size);
   p->size = size;
         // may throw exception
   p->pNext = pHead;
   pHead = p;  // change head (adds in reverse order for simplicity)
   return p;
}

void plex::FreeDataChain()     // free this one and links
{
   try
   {
      plex* pPrevious = NULL;
      plex* p = this;
      while (p != NULL)
      {
         BYTE* bytes = (BYTE*) p;
         plex* pNext = p->pNext;
         g_heap.free(bytes, p->size);
         pPrevious = p;
         p = pNext;
      }
   }
   catch(...)
   {
   }
}
