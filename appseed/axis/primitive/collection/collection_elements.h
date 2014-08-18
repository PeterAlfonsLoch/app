// This is core API library.
// 
// 
//
// 
// 
// 
// 
// 

// Collection implementation helpers

/*
* The int16_t story:
*   this file contains inline functions that make up the building blocks
*   for implementing the string versions of standard parameterized
*   collection shapes
*
* The long story:
*   Because the implementation of collection classes moves objects around
*   in various ways, it is very inefficient to use only generic C++ constructs.
*   For example, in order to grow an array of FOO objects by one element,
*   you would be forced to allocate a new array of appropriate size, calling
*   the FOO constructor on every element.  Then copy the original array, element
*   by element using a possibly overloaded assignment operator.  Finally destroy
*   the original array element by element.
*   For built-in data types (WORD, uint32_t, pointer types), this is complete
*   overkill.  For non-trivial classes (eg: string in particular) this is
*   a terrible implementation.
*
*   The bottom line: we have two special routines for doing construction
*   and destruction of arrays of special elements - in particular Strings.
*   The standard templates are parameterized on 'HAS_CREATE' which is
*   non-zero if the collection implementation requires a special
*   construct and destruct function.
*
*   Please note that these are inline overloaded operators, and do not have
*   any form of runtime polymorphism (i.e. nothing is 'virtual').
*/

/////////////////////////////////////////////////////////////////////////////
// Special implementations for Strings
// it is faster to bit-wise copy a string than to call an official
//   constructor - since an is_empty string can be bit-wise copied

/*static inline void ConstructElement(string* pNewData)
{
   ENSURE_ARG(pNewData!=NULL);
   new( pNewData ) string;
}

static inline void DestructElement(string* pOldData)
{
   ENSURE_ARG(pOldData!=NULL);
   pOldData->~string();
}
*/
static inline void CopyElement(string* pSrc, string* pDest)
{
   ENSURE_ARG(pSrc!=NULL && pDest!=NULL);
   *pSrc = *pDest;
}

/////////////////////////////////////////////////////////////////////////////
