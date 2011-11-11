#pragma once


namespace _template
{
   class CComBSTR;
}
using _template::CComBSTR;


namespace _template
{
   class CComBSTR;
}
using _template::CComBSTR;

// the two functions below are deprecated.  Use a constructor/destructor instead.
//#pragma deprecated( DestructElements )
//#pragma deprecated( ConstructElements )

template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, count nCount)
{
   ENSURE(nCount == 0 || pDest != 0 && pSrc != 0);
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));

   // default is element-copy using assignment
   while (nCount--)
      *pDest++ = *pSrc++;
}
/*
template<class TYPE>
void SerializeElements(CArchive& ar, TYPE* pElements, count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pElements, (size_t)nCount * sizeof(TYPE)));

   // default is bit-wise read/write
   if (ar.IsStoring())
   {
     TYPE* pData;
     UINT_PTR nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToWrite;

       nElementsToWrite = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.write(pData, nElementsToWrite*sizeof(TYPE));
       nElementsLeft -= nElementsToWrite;
       pData += nElementsToWrite;
     }
   }
   else
   {
     TYPE* pData;
     UINT_PTR nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToRead;

       nElementsToRead = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.EnsureRead(pData, nElementsToRead*sizeof(TYPE));
       nElementsLeft -= nElementsToRead;
       pData += nElementsToRead;
     }
   }
}

template<class TYPE>
void SerializeElementsInsertExtract(CArchive& ar, TYPE* pElements, 
   count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT((nCount == 0) || 
      (fx_is_valid_address(pElements, nCount*sizeof(TYPE))));

   if (nCount == 0 || pElements == NULL)
   {
      return;
   }

   if (ar.IsStoring())
   {
      for (; nCount--; ++pElements)
         ar << *pElements;
   }
   else
   {
      for (; nCount--; ++pElements)
         ar >> *pElements;
   }
}
*/

#ifdef _DEBUG
template<class TYPE>
void dump_elements(dump_context & dumpcontext, const TYPE* pElements, count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), FALSE));
   &dumpcontext; // not used
   pElements;  // not used
   nCount; // not used

   // default does nothing
}
#endif


// the two functions below are deprecated.  Use a constructor/destructor instead.
//#pragma deprecated( DestructElements )
//#pragma deprecated( ConstructElements )

/*
template<class TYPE>
void SerializeElements(CArchive& ar, TYPE* pElements, count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      fx_is_valid_address(pElements, (size_t)nCount * sizeof(TYPE)));

   // default is bit-wise read/write
   if (ar.IsStoring())
   {
     TYPE* pData;
     UINT_PTR nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToWrite;

       nElementsToWrite = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.write(pData, nElementsToWrite*sizeof(TYPE));
       nElementsLeft -= nElementsToWrite;
       pData += nElementsToWrite;
     }
   }
   else
   {
     TYPE* pData;
     UINT_PTR nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToRead;

       nElementsToRead = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.EnsureRead(pData, nElementsToRead*sizeof(TYPE));
       nElementsLeft -= nElementsToRead;
       pData += nElementsToRead;
     }
   }
}

template<class TYPE>
void SerializeElementsInsertExtract(CArchive& ar, TYPE* pElements, 
   count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT((nCount == 0) || 
      (fx_is_valid_address(pElements, nCount*sizeof(TYPE))));

   if (nCount == 0 || pElements == NULL)
   {
      return;
   }

   if (ar.IsStoring())
   {
      for (; nCount--; ++pElements)
         ar << *pElements;
   }
   else
   {
      for (; nCount--; ++pElements)
         ar >> *pElements;
   }
}
*/



template<class TYPE, class ARG_TYPE>
BOOL CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
{
	ENSURE(pElement1 != NULL && pElement2 != NULL);
	ASSERT(fx_is_valid_address(pElement1, sizeof(TYPE), FALSE));
	ASSERT(fx_is_valid_address(pElement2, sizeof(ARG_TYPE), FALSE));

	return *pElement1 == *pElement2;
}

#include "template_hash.h"

