#pragma once


#pragma warning( push )
#if _SECURE_ATL
#pragma warning( disable: 4505 4127 )
#endif

/////////////////////////////////////////////////////////////////////////////
// global helpers (can be overridden)


namespace _template
{
	class CComBSTR;
}
using _template::CComBSTR;

// the two functions below are deprecated.  Use a constructor/destructor instead.
#pragma deprecated( DestructElements )
#pragma deprecated( ConstructElements )

template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, count nCount)
{
	ENSURE(nCount == 0 || pDest != 0 && pSrc != 0);
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pDest, (size_t)nCount * sizeof(TYPE)));
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pSrc, (size_t)nCount * sizeof(TYPE)));

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
		AfxIsValidAddress(pElements, (size_t)nCount * sizeof(TYPE)));

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
		(AfxIsValidAddress(pElements, nCount*sizeof(TYPE))));

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
void DumpElements(CDumpContext & dumpcontext, const TYPE* pElements, count nCount)
{
	ENSURE(nCount == 0 || pElements != NULL);
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, (size_t)nCount * sizeof(TYPE), FALSE));
	&dumpcontext; // not used
	pElements;  // not used
	nCount; // not used

	// default does nothing
}
#endif

template<class TYPE, class ARG_TYPE>
BOOL CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
{
	ENSURE(pElement1 != NULL && pElement2 != NULL);
	ASSERT(AfxIsValidAddress(pElement1, sizeof(TYPE), FALSE));
	ASSERT(AfxIsValidAddress(pElement2, sizeof(ARG_TYPE), FALSE));

	return *pElement1 == *pElement2;
}


template<class ARG_KEY>
inline UINT HashKey(ARG_KEY key)
{
	// default identity hash - works for most primitive values
	return (DWORD)(((DWORD_PTR)key)>>4);
}

// special versions for string
#if _MSC_VER >= 1100
/*template<> CLASS_DECL_ca void SerializeElements<astring> (CArchive& ar, astring* pElements, count nCount);
template<> CLASS_DECL_ca void SerializeElements<wstring> (CArchive& ar, wstring* pElements, count nCount);
*/
template<> CLASS_DECL_ca UINT HashKey<const wchar_t *> (const wchar_t * key);
template<> CLASS_DECL_ca UINT HashKey<const char *> (const char * key);
template<> CLASS_DECL_ca UINT HashKey<wstring> (wstring key);
template<> CLASS_DECL_ca UINT HashKey<string> (string key);
#else // _MSC_VER >= 1100
//void SerializeElements(CArchive& ar, string* pElements, count nCount);
UINT HashKey(const wchar_t * key);
UINT HashKey(const char * key);
#endif // _MSC_VER >= 1100

// special versions for CComBSTR
//template<> void SerializeElements<CComBSTR> (CArchive& ar, CComBSTR* pElements, count nCount);
template<> UINT HashKey<CComBSTR> (CComBSTR key);

namespace gen
{
   namespace win
   {
      template < class TYPE, class ARG_TYPE >
      bool CreateSafeArray(base_array < TYPE, ARG_TYPE > & ar, VARIANT * pvar, VARTYPE vt)
      {
          pvar->vt = VT_ARRAY | vt;
          SAFEARRAYBOUND rgsabound[1];
          rgsabound[0].lLbound = 0;
          rgsabound[0].cElements = get_size();
          pvar->parray = SafeArrayCreate(vt, 1, rgsabound);
          if(pvar->parray == NULL)
              return false;
          for(int i = 0; i < get_size(); i++)
          {
              SafeArrayPutElement(pvar->parray, (long *) &i, &ar.element_at(i));
          }
      }

      template < class TYPE, class ARG_TYPE >
	   bool CopySafeArray(base_array < TYPE, ARG_TYPE > & ar, VARIANT * var)
      {
      //    AFX_MANAGE_STATE(AfxGetStaticModuleState())
          ASSERT(pvar->vt == (VT_ARRAY | VT_I4)); 
          ar.remove_all();
          UINT uiDim;
          
          if(1 != (uiDim = SafeArrayGetDim(pvar->parray)))
          {
              ASSERT(FALSE);
              return false;
          }

          HRESULT hr;
          long lLBound;
          long lUBound;
          
          if(FAILED(hr = SafeArrayGetLBound(pvar->parray, uiDim, &lLBound)))
          {
              return false;
          }

          if(FAILED(hr = SafeArrayGetUBound(pvar->parray, uiDim, &lUBound)))
          {
              return false;
          }

          DWORD dw;
          for(int i = lLBound; i <= lUBound; i++)
          {
              SafeArrayGetElement(pvar->parray, (long *) &i, &dw);
              ar.add(dw);
          }
          return true;

      }
   }
}


/////////////////////////////////////////////////////////////////////////////
// base_array<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline count base_array<TYPE, ARG_TYPE>::get_size() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
inline count base_array<TYPE, ARG_TYPE>::get_count() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
inline bool base_array<TYPE, ARG_TYPE>::is_empty() const
	{ return m_nSize == 0; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::get_upper_bound() const
	{ return m_nSize-1; }
template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::get_at(index nIndex)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline void base_array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		m_pData[nIndex] = newElement; 
	else
		AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::element_at(index nIndex)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}

template<class TYPE, class ARG_TYPE>
inline const TYPE* base_array<TYPE, ARG_TYPE>::get_data() const
{
   return (const TYPE*)m_pData;
}

template<class TYPE, class ARG_TYPE>
inline void base_array<TYPE, ARG_TYPE>::remove_last()
{
   return remove_at(get_upper_bound());
}

template<class TYPE, class ARG_TYPE>
inline TYPE* base_array<TYPE, ARG_TYPE>::get_data()
	{ return (TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
	{ index nIndex = m_nSize;
		set_at_grow(nIndex, newElement);
		return nIndex; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::add_new(count count)
	{ set_size(m_nSize + count);
		return get_upper_bound(); }
template<class TYPE, class ARG_TYPE>
inline const TYPE& base_array<TYPE, ARG_TYPE>::operator[](index nIndex) const
	{ return get_at(nIndex); }
template<class TYPE, class ARG_TYPE>
inline TYPE& base_array<TYPE, ARG_TYPE>::operator[](index nIndex)
	{ return element_at(nIndex); }

/////////////////////////////////////////////////////////////////////////////
// base_array<TYPE, ARG_TYPE> out-of-line functions

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::base_array()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
base_array<TYPE, ARG_TYPE>::~base_array()
{
	ASSERT_VALID(this);

	if (m_pData != NULL)
	{
		for( int i = 0; i < m_nSize; i++ )
			(m_pData + i)->~TYPE();
		delete[] (BYTE*)m_pData;
	}
}

template<class TYPE, class ARG_TYPE>
count base_array<TYPE, ARG_TYPE>::set_size(count nNewSize, count nGrowBy)
{
   count countOld = get_count();
	ASSERT_VALID(this);
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		AfxThrowInvalidArgException();

	if (nGrowBy >= 0)
		m_nGrowBy = nGrowBy;  // set new size

	if (nNewSize == 0)
	{
		// shrink to nothing
		if (m_pData != NULL)
		{
			for( int i = 0; i < m_nSize; i++ )
				(m_pData + i)->~TYPE();
			delete[] (BYTE*)m_pData;
			m_pData = NULL;
		}
		m_nSize = m_nMaxSize = 0;
	}
	else if (m_pData == NULL)
	{
		// create buffer big enough to hold number of requested elements or
		// m_nGrowBy elements, whichever is larger.
#ifdef SIZE_T_MAX
      if(nNewSize > SIZE_T_MAX/sizeof(TYPE))
         throw new memory_exception;
		ASSERT(nNewSize <= SIZE_T_MAX/sizeof(TYPE));    // no overflow
#endif
		count nAllocSize = __max(nNewSize, m_nGrowBy);
		m_pData = (TYPE*) new BYTE[(size_t)nAllocSize * sizeof(TYPE)];
		memset((void *)m_pData, 0, (size_t)nAllocSize * sizeof(TYPE));
		for( int i = 0; i < nNewSize; i++ )
#pragma push_macro("new")
#undef new
			::new( (void *)( m_pData + i ) ) TYPE;
#pragma pop_macro("new")
		m_nSize = nNewSize;
		m_nMaxSize = nAllocSize;
	}
	else if (nNewSize <= m_nMaxSize)
	{
		// it fits
		if (nNewSize > m_nSize)
		{
			// initialize the new elements
			memset((void *)(m_pData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
			for( int i = 0; i < nNewSize-m_nSize; i++ )
#pragma push_macro("new")
#undef new
				::new( (void *)( m_pData + m_nSize + i ) ) TYPE;
#pragma pop_macro("new")
		}
		else if (m_nSize > nNewSize)
		{
			// destroy the old elements
			for( int i = 0; i < m_nSize-nNewSize; i++ )
				(m_pData + nNewSize + i)->~TYPE();
		}
		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow base_array
		nGrowBy = m_nGrowBy;
		if (nGrowBy == 0)
		{
			// heuristically determine growth when nGrowBy == 0
			//  (this avoids heap fragmentation in many situations)
			nGrowBy = m_nSize / 8;
			nGrowBy = (nGrowBy < 4) ? 4 : ((nGrowBy > 1024) ? 1024 : nGrowBy);
		}
		count nNewMax;
		if (nNewSize < m_nMaxSize + nGrowBy)
			nNewMax = m_nMaxSize + nGrowBy;  // granularity
		else
			nNewMax = nNewSize;  // no slush

		ASSERT(nNewMax >= m_nMaxSize);  // no wrap around
		
		if(nNewMax  < m_nMaxSize)
			AfxThrowInvalidArgException();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
		TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];

		// copy new data from old
		::_template::checked::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
			m_pData, (size_t)m_nSize * sizeof(TYPE));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);
		memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
		for( int i = 0; i < nNewSize-m_nSize; i++ )
#pragma push_macro("new")
#undef new
			::new( (void *)( pNewData + m_nSize + i ) ) TYPE;
#pragma pop_macro("new")

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
   return countOld;
}

template<class TYPE, class ARG_TYPE>
count base_array<TYPE, ARG_TYPE>::
add(const base_array& src)
{
   return add_array(src);
}

template<class TYPE, class ARG_TYPE>
count base_array<TYPE, ARG_TYPE>::
add_array(const base_array& src)
{
   if(this == &src)
   {
      base_array<TYPE, ARG_TYPE> arrayCopy(*this);
      return add_array(arrayCopy);
   }
	ASSERT_VALID(this);

	count nOldSize = m_nSize;
	set_size(m_nSize + src.m_nSize);
	CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
	return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::copy(const base_array& src)
{
	ASSERT_VALID(this);
	if(this != &src)
	{
		set_size(src.m_nSize);
		CopyElements<TYPE>(m_pData, src.m_pData, src.m_nSize);
	}
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::free_extra()
{
	ASSERT_VALID(this);

	if (m_nSize != m_nMaxSize)
	{
		// shrink to desired size
#ifdef SIZE_T_MAX
		ASSERT(m_nSize <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
		TYPE* pNewData = NULL;
		if (m_nSize != 0)
		{
			pNewData = (TYPE*) new BYTE[m_nSize * sizeof(TYPE)];
			// copy new data from old
			::_template::checked::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
				m_pData, m_nSize * sizeof(TYPE));
		}

		// get rid of old stuff (note: no destructors called)
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nMaxSize = m_nSize;
	}
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);
	
	if(nIndex < 0)
		AfxThrowInvalidArgException();

	if (nIndex >= m_nSize)
		set_size(nIndex+1, -1);
	m_pData[nIndex] = newElement;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, count nCount /*=1*/)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		AfxThrowInvalidArgException();

	if (nIndex >= m_nSize)
	{
		// adding after the end of the base_array
		set_size(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the base_array
		count nOldSize = m_nSize;
		set_size(m_nSize + nCount, -1);  // grow it to new size
		// destroy intial data before copying over it
		for( int i = 0; i < nCount; i++ )
			(m_pData + nOldSize + i)->~TYPE();
		// shift old data up to fill gap
		::_template::checked::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
			m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
		for( int i = 0; i < nCount; i++ )
#pragma push_macro("new")
#undef new
			::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#pragma pop_macro("new")
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
	while (nCount--)
		m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::remove_at(index nIndex, count nCount)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);
	ASSERT(nCount >= 0);
	index nUpperBound = nIndex + nCount;
	ASSERT(nUpperBound <= m_nSize && nUpperBound >= nIndex && nUpperBound >= nCount);

	if(nIndex < 0 || nCount < 0 || (nUpperBound > m_nSize) || (nUpperBound < nIndex) || (nUpperBound < nCount))
		AfxThrowInvalidArgException();

	// just remove a range
	count nMoveCount = m_nSize - (nUpperBound);
	for( int i = 0; i < nCount; i++ )
		(m_pData + nIndex + i)->~TYPE();
	if (nMoveCount)
	{
		::_template::checked::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
			m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
	}
	m_nSize -= nCount;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
insert_at(index nStartIndex, base_array* pNewArray)
{
   insert_array_at(nStartIndex, pNewArray);
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::
insert_array_at(index nStartIndex, base_array* pNewArray)
{
   if(this == pNewArray)
   {
      base_array<TYPE, ARG_TYPE> arrayCopy(*this);
      return insert_array_at(nStartIndex, &arrayCopy);
   }
	ASSERT_VALID(this);
	ASSERT(pNewArray != NULL);
	ASSERT_VALID(pNewArray);
	ASSERT(nStartIndex >= 0);

	if(pNewArray == NULL || nStartIndex < 0)
		AfxThrowInvalidArgException();

	if (pNewArray->get_size() > 0)
	{
		insert_at(nStartIndex, pNewArray->get_at(0), pNewArray->get_size());
		for (index i = 0; i < pNewArray->get_size(); i++)
			set_at(nStartIndex + i, pNewArray->get_at(i));
	}
}
/*
template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	base_object::Serialize(ar);
	if (ar.IsStoring())
	{
		ar.WriteCount(m_nSize);
	}
	else
	{
		DWORD_PTR nOldSize = ar.ReadCount();
		set_size(nOldSize, -1);
	}
	SerializeElements<TYPE>(ar, m_pData, m_nSize);
}
*/
#ifdef _DEBUG
template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::Dump(CDumpContext & dumpcontext) const
{
	base_object::Dump(dumpcontext);

	dumpcontext << "with " << m_nSize << " elements";
	if (dumpcontext.GetDepth() > 0)
	{
		dumpcontext << "\n";
		DumpElements<TYPE>(dumpcontext, m_pData, m_nSize);
	}

	dumpcontext << "\n";
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::AssertValid() const
{
	base_object::AssertValid();

	if (m_pData == NULL)
	{
		ASSERT(m_nSize == 0);
		ASSERT(m_nMaxSize == 0);
	}
	else
	{
		ASSERT(m_nSize >= 0);
		ASSERT(m_nMaxSize >= 0);
		ASSERT(m_nSize <= m_nMaxSize);
		ASSERT(AfxIsValidAddress(m_pData, m_nMaxSize * sizeof(TYPE)));
	}
}
#endif //_DEBUG

#include "collection/list.h"
#include "collection/comparable_eq_list.h"
#include "collection/comparable_list.h"

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
class map : public base_object
{
public:
	class pair
	{
   public:
		const KEY key;
		VALUE value;
	protected:
		pair( ARG_KEY keyval ) : key( keyval )	{}
	};

protected:
	// Association
	class assoc : public pair
	{
		friend class map<KEY,ARG_KEY,VALUE,ARG_VALUE>;
		assoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
	public:
		assoc( ARG_KEY key ) : pair( key ) {}
	};

public:
   void construct(count nBlockSize = 10);
	map(count nBlockSize = 10);
   //template < pair pairs[]>
   map(pair pairs[]);

	count get_count() const;
	count get_size() const;
	BOOL is_empty() const;

	// Lookup
	BOOL Lookup(ARG_KEY key, VALUE& rValue) const;
	const pair *PLookup(ARG_KEY key) const;
	pair *PLookup(ARG_KEY key);

// Operations
	// Lookup and add if not there
	VALUE& operator[](ARG_KEY key);

	// add a new (key, value) pair
	void set_at(ARG_KEY key, ARG_VALUE newValue);
   void set_at(ARG_KEY key, VALUE * pnewValue);

	// removing existing (key, ?) pair
	BOOL remove_key(ARG_KEY key);
	void remove_all();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;

	const pair *PGetFirstAssoc() const;
	pair *PGetFirstAssoc();

	void GetNextAssoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

	const pair *PGetNextAssoc(const pair *pAssocRet) const;
	pair *PGetNextAssoc(const pair *pAssocRet);

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);


   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);
   VALUE * pget(ARG_KEY argkey);

   map & operator = (const map & m);

// Implementation
protected:
	assoc** m_pHashTable;
	UINT m_nHashTableSize;
	count m_nCount;
	assoc* m_pFreeList;
	struct plex* m_pBlocks;
	count m_nBlockSize;

	assoc* NewAssoc(ARG_KEY key);
	void FreeAssoc(assoc*);
	assoc* GetAssocAt(ARG_KEY, UINT&, UINT&) const;

public:
	virtual ~map();
//	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// map<KEY, ARG_KEY, VALUE, ARG_VALUE> inline functions



template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline count map<KEY, ARG_KEY, VALUE, ARG_VALUE>::get_count() const
	{ return m_nCount; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline count map<KEY, ARG_KEY, VALUE, ARG_VALUE>::get_size() const
	{ return m_nCount; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline BOOL map<KEY, ARG_KEY, VALUE, ARG_VALUE>::is_empty() const
	{ return m_nCount == 0; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::set_at(ARG_KEY key, ARG_VALUE newValue)
	{ (*this)[key] = newValue; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::set_at(ARG_KEY key, VALUE * pnewValue)
	{ (*this)[key] = *pnewValue; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline POSITION map<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetStartPosition() const
	{ return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PGetFirstAssoc() const
{ 
	ASSERT_VALID(this);
	if(m_nCount == 0) return NULL;

	ASSERT(m_pHashTable != NULL);  // never call on empty map

	assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

	// find the first association
	for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
		if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
			break;
	ASSERT(pAssocRet != NULL);  // must find something

	return pAssocRet;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PGetFirstAssoc()
{ 
	ASSERT_VALID(this);
	if(m_nCount == 0) return NULL;

	ASSERT(m_pHashTable != NULL);  // never call on empty map

	assoc* pAssocRet = (assoc*)BEFORE_START_POSITION;

	// find the first association
	for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
		if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
			break;
	ASSERT(pAssocRet != NULL);  // must find something

	return pAssocRet;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
inline UINT map<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetHashTableSize() const
	{ return m_nHashTableSize; }

/////////////////////////////////////////////////////////////////////////////
// map<KEY, ARG_KEY, VALUE, ARG_VALUE> out-of-line functions
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::construct(count nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_pHashTable = NULL;
	m_nHashTableSize = 17;  // default size
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::map(count nBlockSize)
{
   construct(nBlockSize);
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::map(pair pairs[])
{
	construct();
   int iCount = sizeof(pairs) / sizeof(pair);
   for(int i = 0; i < iCount; i++)
   {
      set_at(pairs[i].key, pairs[i].value);
   }
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::InitHashTable(
	UINT nHashSize, BOOL bAllocNow)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{
	ASSERT_VALID(this);
	ASSERT(m_nCount == 0);
	ASSERT(nHashSize > 0);

	if (m_pHashTable != NULL)
	{
		// free hash table
		delete[] m_pHashTable;
		m_pHashTable = NULL;
	}

	if (bAllocNow)
	{
		m_pHashTable = new assoc* [nHashSize];
		ENSURE(m_pHashTable != NULL);
		memset(m_pHashTable, 0, sizeof(assoc*) * nHashSize);
	}
	m_nHashTableSize = nHashSize;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::remove_all()
{
	ASSERT_VALID(this);

	if (m_pHashTable != NULL)
	{
		// destroy elements (values and keys)
		for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
		{
			assoc* pAssoc;
			for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
			  pAssoc = pAssoc->pNext)
			{
				pAssoc->assoc::~assoc();
				//DestructElements<VALUE>(&pAssoc->value, 1);
				//DestructElements<KEY>((KEY*)&pAssoc->key, 1);
			}
		}
	}

	// free hash table
	delete[] m_pHashTable;
	m_pHashTable = NULL;

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::~map()
{
	remove_all();
	ASSERT(m_nCount == 0);
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::assoc*
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::NewAssoc(ARG_KEY key)
{
	if (m_pFreeList == NULL)
	{
		// add another block
		plex* newBlock = plex::create(m_pBlocks, m_nBlockSize, sizeof(map::assoc));
		// chain them into free list
		map::assoc* pAssoc = (map::assoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (index i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	ENSURE(m_pFreeList != NULL);  // we must have something

	map::assoc* pAssoc = m_pFreeList;

	// zero the memory
	map::assoc* pTemp = pAssoc->pNext;
	memset( pAssoc, 0, sizeof(map::assoc) );
	pAssoc->pNext = pTemp;

	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);  // make sure we don't overflow
#pragma push_macro("new")
#undef new
	::new(pAssoc) map::assoc(key);
#pragma pop_macro("new")
//	ConstructElements<KEY>(&pAssoc->key, 1);
//	ConstructElements<VALUE>(&pAssoc->value, 1);   // special construct values
	return pAssoc;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::FreeAssoc(assoc* pAssoc)
{
	pAssoc->assoc::~assoc();
//	DestructElements<VALUE>(&pAssoc->value, 1);
//	DestructElements<KEY>(&pAssoc->key, 1);
	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		remove_all();
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::assoc*
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetAssocAt(ARG_KEY key, UINT& nHashBucket, UINT& nHashValue) const
// find association (or return NULL)
{
	nHashValue = HashKey<ARG_KEY>(key);
	nHashBucket = nHashValue % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	assoc* pAssoc;
	for (pAssoc = m_pHashTable[nHashBucket]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->nHashValue == nHashValue && CompareElements(&pAssoc->key, &key))
			return pAssoc;
	}
	return NULL;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL map<KEY, ARG_KEY, VALUE, ARG_VALUE>::Lookup(ARG_KEY key, VALUE& rValue) const
{
	ASSERT_VALID(this);

	UINT nHashBucket, nHashValue;
	assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
	if (pAssoc == NULL)
		return FALSE;  // not in map

	rValue = pAssoc->value;
	return TRUE;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PLookup(ARG_KEY key) const
{
	ASSERT_VALID(this);

	UINT nHashBucket, nHashValue;
	assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
	return pAssoc;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PLookup(ARG_KEY key)
{
	ASSERT_VALID(this);

	UINT nHashBucket, nHashValue;
	assoc* pAssoc = GetAssocAt(key, nHashBucket, nHashValue);
	return pAssoc;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
VALUE& map<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator[](ARG_KEY key)
{
	ASSERT_VALID(this);

	UINT nHashBucket, nHashValue;
	assoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHashBucket, nHashValue)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		ENSURE(m_pHashTable);
		// it doesn't exist, add a new Association
		pAssoc = NewAssoc(key);
		pAssoc->nHashValue = nHashValue;
		//'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHashBucket];
		m_pHashTable[nHashBucket] = pAssoc;
	}
	return pAssoc->value;  // return new reference
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
BOOL map<KEY, ARG_KEY, VALUE, ARG_VALUE>::remove_key(ARG_KEY key)
// remove key - return TRUE if removed
{
	ASSERT_VALID(this);

	if (m_pHashTable == NULL)
		return FALSE;  // nothing in the table

	UINT nHashValue;
	assoc** ppAssocPrev;
	nHashValue = HashKey<ARG_KEY>(key);
	ppAssocPrev = &m_pHashTable[nHashValue%m_nHashTableSize];

	assoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if ((pAssoc->nHashValue == nHashValue) && CompareElements(&pAssoc->key, &key))
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;  // not found
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::GetNextAssoc(POSITION& rNextPosition,
	KEY& rKey, VALUE& rValue) const
{
	ASSERT_VALID(this);
	ENSURE(m_pHashTable != NULL);  // never call on empty map

	assoc* pAssocRet = (assoc*)rNextPosition;
	ENSURE(pAssocRet != NULL);

	if (pAssocRet == (assoc*) BEFORE_START_POSITION)
	{
		// find the first association
		for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
		{
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
			{
				break;
			}
		}
		ENSURE(pAssocRet != NULL);  // must find something
	}

	// find next association
	ASSERT(AfxIsValidAddress(pAssocRet, sizeof(assoc)));
	assoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (POSITION) pAssocNext;

	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
const typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair*
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PGetNextAssoc(const typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* pPairRet) const
{
	ASSERT_VALID(this);

	assoc* pAssocRet = (assoc*)pPairRet;

	ASSERT(m_pHashTable != NULL);  // never call on empty map
	ASSERT(pAssocRet != NULL);
	
	if(m_pHashTable == NULL || pAssocRet == NULL)
		return NULL;
		
	ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION);

	// find next association
	ASSERT(AfxIsValidAddress(pAssocRet, sizeof(assoc)));
	assoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	return pAssocNext;
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair*
map<KEY, ARG_KEY, VALUE, ARG_VALUE>::PGetNextAssoc(const typename map<KEY, ARG_KEY, VALUE, ARG_VALUE>::pair* pPairRet)
{
	ASSERT_VALID(this);

	assoc* pAssocRet = (assoc*)pPairRet;

	ASSERT(m_pHashTable != NULL);  // never call on empty map
	ASSERT(pAssocRet != NULL);
	
	if(m_pHashTable == NULL || pAssocRet == NULL)
		return NULL;
		
	ASSERT(pAssocRet != (assoc*)BEFORE_START_POSITION);

	// find next association
	ASSERT(AfxIsValidAddress(pAssocRet, sizeof(assoc)));
	assoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = (pAssocRet->nHashValue % m_nHashTableSize) + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	return pAssocNext;
}

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE >
   VALUE map <KEY, ARG_KEY, VALUE, ARG_VALUE> ::
      get(ARG_KEY argkey, ARG_VALUE valueDefault)
   {
      pair * ppair = PLookup(argkey);
      if(ppair == NULL)
         return valueDefault;
      else
         return ppair->value;
   }

   template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE >
   VALUE * map <KEY, ARG_KEY, VALUE, ARG_VALUE> ::
      pget(ARG_KEY argkey)
   {
      pair * ppair = PLookup(argkey);
      if(ppair == NULL)
         return NULL;
      else
         return &ppair->value;
   }

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
map<KEY, ARG_KEY, VALUE, ARG_VALUE> & map<KEY, ARG_KEY, VALUE, ARG_VALUE>::operator = (const map<KEY, ARG_KEY, VALUE, ARG_VALUE> & m)
{
   if(&m != this)
   {
      remove_all();
      map & mapSrc = const_cast < map &> (m);
  	   pair * p = mapSrc.PGetFirstAssoc();
      while(p != NULL)
      {
         set_at(p->key, p->value);
         p = mapSrc.PGetNextAssoc(p);
      }
   }
   return *this;
}

/*
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	base_object::Serialize(ar);

	if (ar.IsStoring())
	{
		ar.WriteCount(m_nCount);
		if (m_nCount == 0)
			return;  // nothing more to do

		ASSERT(m_pHashTable != NULL);
		for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
		{
			assoc* pAssoc;
			for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
			  pAssoc = pAssoc->pNext)
			{
				KEY* pKey;
				VALUE* pValue;
				/* 
				 * in some cases the & operator might be overloaded, and we cannot use it to 
				 * obtain the address of a given object.  We then use the following trick to 
				 * get the address
				 */
				/*pKey = reinterpret_cast< KEY* >( &reinterpret_cast< int& >( const_cast< KEY& > ( static_cast< const KEY& >( pAssoc->key ) ) ) );
				pValue = reinterpret_cast< VALUE* >( &reinterpret_cast< int& >( static_cast< VALUE& >( pAssoc->value ) ) );
				SerializeElements<KEY>(ar, pKey, 1);
				SerializeElements<VALUE>(ar, pValue, 1);
			}
		}
	}
	else
	{
		DWORD_PTR nNewCount = ar.ReadCount();
		while (nNewCount--)
		{
			KEY newKey[1];
			VALUE newValue[1];
			SerializeElements<KEY>(ar, newKey, 1);
			SerializeElements<VALUE>(ar, newValue, 1);
			set_at(newKey[0], newValue[0]);
		}
	}
}
*/

#ifdef _DEBUG
template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::Dump(CDumpContext & dumpcontext) const
{
	base_object::Dump(dumpcontext);

	dumpcontext << "with " << m_nCount << " elements";
	if (dumpcontext.GetDepth() > 0)
	{
		// Dump in format "[key] -> value"

		const pair * ppair = PGetFirstAssoc();
		while (ppair != NULL)
		{
			ppair = PGetNextAssoc(ppair);
			dumpcontext << "\n\t[";
			DumpElements<KEY>(dumpcontext, &ppair->key, 1);
			dumpcontext << "] = ";
			DumpElements<VALUE>(dumpcontext, &ppair->value, 1);
		}
	}

	dumpcontext << "\n";
}

template<class KEY, class ARG_KEY, class VALUE, class ARG_VALUE>
void map<KEY, ARG_KEY, VALUE, ARG_VALUE>::AssertValid() const
{
	base_object::AssertValid();

	ASSERT(m_nHashTableSize > 0);
	ASSERT(m_nCount == 0 || m_pHashTable != NULL);
		// non-empty map should have hash table
}


template < class VALUE, class ARG_VALUE = const VALUE & >
class string_map :
   virtual public map < string, string, VALUE, ARG_VALUE >
{
public:
   string_map(count nBlockSize = 10) : map (nBlockSize) {};
};

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CTypedPtrList<BASE_CLASS, TYPE>

template<class BASE_CLASS, class TYPE>
class _CTypedPtrList : public BASE_CLASS
{
public:
// Construction
	_CTypedPtrList(count nBlockSize = 10)
		: BASE_CLASS(nBlockSize) { }

	// peek at head or tail
	TYPE& GetHead()
		{ return (TYPE&)BASE_CLASS::GetHead(); }
	TYPE GetHead() const
		{ return (TYPE)BASE_CLASS::GetHead(); }
	TYPE& GetTail()
		{ return (TYPE&)BASE_CLASS::GetTail(); }
	TYPE GetTail() const
		{ return (TYPE)BASE_CLASS::GetTail(); }

	// get head or tail (and remove it) - don't call on empty list!
	TYPE RemoveHead()
		{ return (TYPE)BASE_CLASS::RemoveHead(); }
	TYPE RemoveTail()
		{ return (TYPE)BASE_CLASS::RemoveTail(); }

	// iteration
	TYPE& GetNext(POSITION& rPosition)
		{ return (TYPE&)BASE_CLASS::GetNext(rPosition); }
	TYPE GetNext(POSITION& rPosition) const
		{ return (TYPE)BASE_CLASS::GetNext(rPosition); }
	TYPE& GetPrev(POSITION& rPosition)
		{ return (TYPE&)BASE_CLASS::GetPrev(rPosition); }
	TYPE GetPrev(POSITION& rPosition) const
		{ return (TYPE)BASE_CLASS::GetPrev(rPosition); }

	// getting/modifying an element at a given position
	TYPE& get_at(POSITION position)
		{ return (TYPE&)BASE_CLASS::get_at(position); }
	TYPE get_at(POSITION position) const
		{ return (TYPE)BASE_CLASS::get_at(position); }
	void set_at(POSITION pos, TYPE newElement)
		{ BASE_CLASS::set_at(pos, newElement); }

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, TYPE newElement)
		{ return BASE_CLASS::InsertBefore(position, newElement); }
	POSITION InsertAfter(POSITION position, TYPE newElement)
		{ return BASE_CLASS::InsertAfter(position, newElement); }

	// transfer before or after a given position
	// Transfer semantics ensure no leakage by deleting the element in the case of an exception
	POSITION TransferInsertBefore(POSITION position, TYPE newElement)
	{
		try
		{
			return BASE_CLASS::InsertBefore(position, newElement); 
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}

	POSITION TransferInsertAfter(POSITION position, TYPE newElement)
	{
		try
		{
			return BASE_CLASS::InsertAfter(position, newElement); 
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}
};

template<class BASE_CLASS, class TYPE>
class CTypedPtrList : public _CTypedPtrList<BASE_CLASS, TYPE>
{
public:
// Construction
	CTypedPtrList(count nBlockSize = 10)
		: _CTypedPtrList<BASE_CLASS, TYPE>(nBlockSize) { }

	// add before head or after tail
	POSITION AddHead(TYPE newElement)
		{ return BASE_CLASS::AddHead(newElement); }
	POSITION AddTail(TYPE newElement)
		{ return BASE_CLASS::AddTail(newElement); }

	// transfer add before head or tail
	POSITION TransferAddHead(TYPE newElement)
	{ 
		try
		{
			return BASE_CLASS::AddHead(newElement); 
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}
	POSITION TransferAddTail(TYPE newElement)
	{ 
		try
		{
			return BASE_CLASS::AddTail(newElement); 
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}

	// add another list of elements before head or after tail
	void AddHead(CTypedPtrList<BASE_CLASS, TYPE>* pNewList)
		{ BASE_CLASS::AddHead(pNewList); }
	void AddTail(CTypedPtrList<BASE_CLASS, TYPE>* pNewList)
		{ BASE_CLASS::AddTail(pNewList); }
};

// need specialized version for CObList because of AddHead/Tail ambiguity
template<> class CTypedPtrList<CObList, CObList*>
	: public _CTypedPtrList<CObList, CObList*>
{
public:
// Construction
	CTypedPtrList(count nBlockSize = 10)
		: _CTypedPtrList<CObList, CObList*>(nBlockSize) { }

	// add before head or after tail
	POSITION AddHead(CObList* newElement)
		{ return _CTypedPtrList<CObList, CObList*>::AddHead((base_object*)newElement); }
	POSITION AddTail(CObList* newElement)
		{ return _CTypedPtrList<CObList, CObList*>::AddTail((base_object*)newElement); }

	// add another list of elements before head or after tail
	void AddHead(CTypedPtrList<CObList, CObList*>* pNewList)
		{ _CTypedPtrList<CObList, CObList*>::AddHead(pNewList); }
	void AddTail(CTypedPtrList<CObList, CObList*>* pNewList)
		{ _CTypedPtrList<CObList, CObList*>::AddTail(pNewList); }
};

// need specialized version for CPtrList because of AddHead/Tail ambiguity
template<> class CTypedPtrList<CPtrList, CPtrList*>
	: public _CTypedPtrList<CPtrList, CPtrList*>
{
public:
// Construction
	CTypedPtrList(count nBlockSize = 10)
		: _CTypedPtrList<CPtrList, CPtrList*>(nBlockSize) { }

	// add before head or after tail
	POSITION AddHead(CPtrList* newElement)
		{ return _CTypedPtrList<CPtrList, CPtrList*>::AddHead((void *)newElement); }
	POSITION AddTail(CPtrList* newElement)
		{ return _CTypedPtrList<CPtrList, CPtrList*>::AddTail((void *)newElement); }

	// add another list of elements before head or after tail
	void AddHead(CTypedPtrList<CPtrList, CPtrList*>* pNewList)
		{ _CTypedPtrList<CPtrList, CPtrList*>::AddHead(pNewList); }
	void AddTail(CTypedPtrList<CPtrList, CPtrList*>* pNewList)
		{ _CTypedPtrList<CPtrList, CPtrList*>::AddTail(pNewList); }
};

/////////////////////////////////////////////////////////////////////////////
// CTypedPtrMap<BASE_CLASS, KEY, VALUE>

template<class BASE_CLASS, class KEY, class VALUE>
class CTypedPtrMap : public BASE_CLASS
{
public:

// Construction
	CTypedPtrMap(count nBlockSize = 10)
		: BASE_CLASS(nBlockSize) { }

	// Lookup
	BOOL Lookup(typename BASE_CLASS::BASE_ARG_KEY key, VALUE& rValue) const
		{ return BASE_CLASS::Lookup(key, (BASE_CLASS::BASE_VALUE&)rValue); }

	// Lookup and add if not there
	VALUE& operator[](typename BASE_CLASS::BASE_ARG_KEY key)
		{ return (VALUE&)BASE_CLASS::operator[](key); }

	// add a new key (key, value) pair
	void set_at(KEY key, VALUE newValue)
		{ BASE_CLASS::set_at(key, newValue); }

	// removing existing (key, ?) pair
	BOOL RemoveKey(KEY key)
		{ return BASE_CLASS::RemoveKey(key); }

	// iteration
	void GetNextAssoc(POSITION& rPosition, KEY& rKey, VALUE& rValue) const
		{ BASE_CLASS::GetNextAssoc(rPosition, (BASE_CLASS::BASE_KEY&)rKey,
			(BASE_CLASS::BASE_VALUE&)rValue); }
};

/////////////////////////////////////////////////////////////////////////////

#undef THIS_FILE
#define THIS_FILE __FILE__

#pragma pop_macro("new")


#pragma warning( pop )

class CLASS_DECL_ca int_to_int_map :
   virtual public map < int, int, int, int >
{
public:
};

class CLASS_DECL_ca int_to_string_map :
   virtual public map < int, int, string, string >
{
public:
};


#include "comparable_array.h"
#include "array_smart_ptr.h"
#include "array_ptr.h"
#include "array_ptr_copy.h"
#include "array_ptr_alloc.h"
#include "array_app_alloc.h"
#include "array_parent_alloc.h"
#include "numeric_array.h"
#include "sort_array.h"
#include "class_sort_array.h"
