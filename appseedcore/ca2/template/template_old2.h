#pragma once

#include "plex_.h"

#undef new


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
	&spgraphics; // not used
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
/*template<> CLASS_DECL_ca2api00000001 void SerializeElements<astring> (CArchive& ar, astring* pElements, count nCount);
template<> CLASS_DECL_ca2api00000001 void SerializeElements<wstring> (CArchive& ar, wstring* pElements, count nCount);
*/
template<> CLASS_DECL_ca2api00000001 UINT HashKey<LPCWSTR> (LPCWSTR key);
template<> CLASS_DECL_ca2api00000001 UINT HashKey<LPCSTR> (LPCSTR key);
template<> CLASS_DECL_ca2api00000001 UINT HashKey<wstring> (wstring key);
template<> CLASS_DECL_ca2api00000001 UINT HashKey<string> (string key);
#else // _MSC_VER >= 1100
//void SerializeElements(CArchive& ar, string* pElements, count nCount);
UINT HashKey(LPCWSTR key);
UINT HashKey(LPCSTR key);
#endif // _MSC_VER >= 1100

// special versions for CComBSTR
//template<> void SerializeElements<CComBSTR> (CArchive& ar, CComBSTR* pElements, count nCount);
template<> UINT HashKey<CComBSTR> (CComBSTR key);

// forward declarations
class COleVariant;
struct tagVARIANT;

// special versions for COleVariant
#if _MSC_VER >= 1100
template<> void CopyElements<COleVariant> (COleVariant* pDest, const COleVariant* pSrc, count nCount);
//template<> void SerializeElements<COleVariant> (CArchive& ar, COleVariant* pElements, count nCount);
#ifdef _DEBUG
template<> void DumpElements<COleVariant> (CDumpContext & dumpcontext, const COleVariant* pElements, count nCount);
#endif
template<> UINT HashKey<const struct tagVARIANT&> (const struct tagVARIANT& variable);
#else // _MSC_VER >= 1100
void CopyElements(COleVariant* pDest, const COleVariant* pSrc, count nCount);
//void SerializeElements(CArchive& ar, COleVariant* pElements, count nCount);
#ifdef _DEBUG
void DumpElements(CDumpContext & dumpcontext, const COleVariant* pElements, count nCount);
#endif
UINT HashKey(const struct tagVARIANT& variable);
#endif // _MSC_VER >= 1100



template<class TYPE, class ARG_TYPE = const TYPE&>
class base_array : 
   virtual public base_object
{
public:
// Construction
	base_array();

// Attributes
	count get_size() const;
	count get_count() const;
	bool is_empty() const;
	index get_upper_bound() const;
	void set_size(index nNewSize, count nGrowBy = -1);

// Operations
	// Clean up
	void free_extra();
	void remove_all();



	// Accessing elements
	const TYPE& get_at(index nIndex) const;
	TYPE& get_at(index nIndex);
	void set_at(index nIndex, ARG_TYPE newElement);
	const TYPE& element_at(index nIndex) const;
	TYPE& element_at(index nIndex);

	// Direct Access to the element data (may return NULL)
	const TYPE* get_data() const;
	TYPE* get_data();

	// Potentially growing the base_array
	void set_at_grow(index nIndex, ARG_TYPE newElement);
	virtual index add(ARG_TYPE newElement);
	index append(const base_array& src);
	void copy(const base_array& src);

	// overloaded operator helpers
	const TYPE& operator[](index nIndex) const;
	TYPE& operator[](index nIndex);

	// Operations that move elements around
	void insert_at(index nIndex, ARG_TYPE newElement, count nCount = 1);
	void remove_at(index nIndex, count nCount = 1);
	void insert_at(index nStartIndex, base_array* pNewArray);

// Implementation
protected:
	TYPE *   m_pData;   // the actual base_array of data
	count    m_nSize;     // # of elements (upperBound - 1)
	count    m_nMaxSize;  // max allocated
	count    m_nGrowBy;   // grow amount

public:
	virtual ~base_array();
//	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

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
inline void base_array<TYPE, ARG_TYPE>::remove_all()
	{ set_size(0, -1); }
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
	{ return (const TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
inline TYPE* base_array<TYPE, ARG_TYPE>::get_data()
	{ return (TYPE*)m_pData; }
template<class TYPE, class ARG_TYPE>
inline index base_array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
	{ index nIndex = m_nSize;
		set_at_grow(nIndex, newElement);
		return nIndex; }
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
void base_array<TYPE, ARG_TYPE>::set_size(count nNewSize, count nGrowBy)
{
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
}

template<class TYPE, class ARG_TYPE>
index base_array<TYPE, ARG_TYPE>::append(const base_array& src)
{
	ASSERT_VALID(this);
	ASSERT(this != &src);   // cannot append to itself
	
	if(this == &src)
		AfxThrowInvalidArgException();

	count nOldSize = m_nSize;
	set_size(m_nSize + src.m_nSize);
	CopyElements<TYPE>(m_pData + nOldSize, src.m_pData, src.m_nSize);
	return nOldSize;
}

template<class TYPE, class ARG_TYPE>
void base_array<TYPE, ARG_TYPE>::copy(const base_array& src)
{
	ASSERT_VALID(this);
	ASSERT(this != &src);   // cannot append to itself

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
void base_array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, base_array* pNewArray)
{
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
		DumpElements<TYPE>(spgraphics, m_pData, m_nSize);
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

/////////////////////////////////////////////////////////////////////////////
// list<TYPE, ARG_TYPE>

template<class TYPE, class ARG_TYPE = const TYPE&>
class list : public base_object
{
protected:
	struct node
	{
		node* pNext;
		node* pPrev;
		TYPE data;
	};
public:
// Construction
	/* explicit */ list(count nBlockSize = 10);

// Attributes (head and tail)
	// count of elements
	count get_count() const;
	count get_size() const;
	BOOL is_empty() const;

	// peek at head or tail
	TYPE& GetHead();
	const TYPE& GetHead() const;
	TYPE& GetTail();
	const TYPE& GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	TYPE RemoveHead();
	TYPE RemoveTail();

	// add before head or after tail
	POSITION AddHead(ARG_TYPE newElement);
	POSITION AddTail(ARG_TYPE newElement);

	// add another list of elements before head or after tail
	void AddHead(list* pNewList);
	void AddTail(list* pNewList);

	// remove all elements
	void remove_all();

	// iteration
	POSITION GetHeadPosition() const;
	POSITION GetTailPosition() const;
	TYPE& GetNext(POSITION& rPosition); // return *position++
	const TYPE& GetNext(POSITION& rPosition) const; // return *position++
	TYPE& GetPrev(POSITION& rPosition); // return *position--
	const TYPE& GetPrev(POSITION& rPosition) const; // return *position--

	// getting/modifying an element at a given position
	TYPE& get_at(POSITION position);
	const TYPE& get_at(POSITION position) const;
	void set_at(POSITION pos, ARG_TYPE newElement);
	void remove_at(POSITION position);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, ARG_TYPE newElement);
	POSITION InsertAfter(POSITION position, ARG_TYPE newElement);

	// helper functions (note: O(n) speed)
	POSITION Find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
		// defaults to starting at the HEAD, return NULL if not found
	POSITION FindIndex(index nIndex) const;
		// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	node* m_pNodeHead;
	node* m_pNodeTail;
	count m_nCount;
	node* m_pNodeFree;
	struct plex* m_pBlocks;
	count m_nBlockSize;

	node* NewNode(node*, node*);
	void FreeNode(node*);

public:
	~list();
	//void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// list<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline count list<TYPE, ARG_TYPE>::get_count() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
inline count list<TYPE, ARG_TYPE>::get_size() const
	{ return m_nCount; }
template<class TYPE, class ARG_TYPE>
inline BOOL list<TYPE, ARG_TYPE>::is_empty() const
	{ return m_nCount == 0; }
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::GetHead()
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::GetHead() const
	{ ASSERT(m_pNodeHead != NULL);
		return m_pNodeHead->data; }
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::GetTail()
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::GetTail() const
	{ ASSERT(m_pNodeTail != NULL);
		return m_pNodeTail->data; }
template<class TYPE, class ARG_TYPE>
inline POSITION list<TYPE, ARG_TYPE>::GetHeadPosition() const
	{ return (POSITION) m_pNodeHead; }
template<class TYPE, class ARG_TYPE>
inline POSITION list<TYPE, ARG_TYPE>::GetTailPosition() const
	{ return (POSITION) m_pNodeTail; }
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) // return *position++
	{ node* pNode = (node*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::GetNext(POSITION& rPosition) const // return *position++
	{ node* pNode = (node*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		rPosition = (POSITION) pNode->pNext;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) // return *position--
	{ node* pNode = (node*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::GetPrev(POSITION& rPosition) const // return *position--
	{ node* pNode = (node*) rPosition;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		rPosition = (POSITION) pNode->pPrev;
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position)
	{ node* pNode = (node*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position) const
	{ node* pNode = (node*) position;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		return pNode->data; }
template<class TYPE, class ARG_TYPE>
inline void list<TYPE, ARG_TYPE>::set_at(POSITION pos, ARG_TYPE newElement)
	{ node* pNode = (node*) pos;
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		pNode->data = newElement; }

template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(count nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_all()
{
	ASSERT_VALID(this);

	// destroy elements
	node* pNode;
	for (pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
		pNode->data.~TYPE();

	m_nCount = 0;
	m_pNodeHead = m_pNodeTail = m_pNodeFree = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::~list()
{
	remove_all();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Node helpers
//
// Implementation note: node's are stored in plex blocks and
//  chained together. Free blocks are maintained in a singly linked list
//  using the 'pNext' member of node with 'm_pNodeFree' as the head.
//  Used blocks are maintained in a doubly linked list using both 'pNext'
//  and 'pPrev' as links and 'm_pNodeHead' and 'm_pNodeTail'
//   as the head/tail.
//
// We never free a plex block unless the List is destroyed or remove_all()
//  is used - so the total number of plex blocks may grow large depending
//  on the maximum past size of the list.
//

template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::node*
list<TYPE, ARG_TYPE>::NewNode(node* pPrev, node* pNext)
{
	if (m_pNodeFree == NULL)
	{
		// add another block
		plex* pNewBlock = plex::Create(m_pBlocks, m_nBlockSize,
				 sizeof(node));

		// chain them into free list
		node* pNode = (node*) pNewBlock->data();
		// free in reverse order to make it easier to debug
		pNode += m_nBlockSize - 1;
		for (index i = m_nBlockSize-1; i >= 0; i--, pNode--)
		{
			pNode->pNext = m_pNodeFree;
			m_pNodeFree = pNode;
		}
	}
	ENSURE(m_pNodeFree != NULL);  // we must have something

	list::node* pNode = m_pNodeFree;
	m_pNodeFree = m_pNodeFree->pNext;
	pNode->pPrev = pPrev;
	pNode->pNext = pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);  // make sure we don't overflow

#pragma push_macro("new")
#undef new
	::new( (void *)( &pNode->data ) ) TYPE;
#pragma pop_macro("new")
	return pNode;
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::FreeNode(node* pNode)
{
	pNode->data.~TYPE();
	pNode->pNext = m_pNodeFree;
	m_pNodeFree = pNode;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		remove_all();
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::AddHead(ARG_TYPE newElement)
{
	ASSERT_VALID(this);

	node* pNewNode = NewNode(NULL, m_pNodeHead);
	pNewNode->data = newElement;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = pNewNode;
	else
		m_pNodeTail = pNewNode;
	m_pNodeHead = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::AddTail(ARG_TYPE newElement)
{
	ASSERT_VALID(this);

	node* pNewNode = NewNode(m_pNodeTail, NULL);
	pNewNode->data = newElement;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = pNewNode;
	else
		m_pNodeHead = pNewNode;
	m_pNodeTail = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::AddHead(list* pNewList)
{
	ASSERT_VALID(this);

	ENSURE(pNewList != NULL);
	ASSERT_VALID(pNewList);

	// add a list of same elements to head (maintain order)
	POSITION pos = pNewList->GetTailPosition();
	while (pos != NULL)
		AddHead(pNewList->GetPrev(pos));
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::AddTail(list* pNewList)
{
	ASSERT_VALID(this);
	ENSURE(pNewList != NULL);
	ASSERT_VALID(pNewList);

	// add a list of same elements
	POSITION pos = pNewList->GetHeadPosition();
	while (pos != NULL)
		AddTail(pNewList->GetNext(pos));
}

template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::RemoveHead()
{
	ASSERT_VALID(this);
	ASSERT(m_pNodeHead != NULL);  // don't call on empty list !!!
	ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(node)));

	node* pOldNode = m_pNodeHead;
	TYPE returnValue = pOldNode->data;

	m_pNodeHead = pOldNode->pNext;
	if (m_pNodeHead != NULL)
		m_pNodeHead->pPrev = NULL;
	else
		m_pNodeTail = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::RemoveTail()
{
	ASSERT_VALID(this);
	ASSERT(m_pNodeTail != NULL);  // don't call on empty list !!!
	ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(node)));

	node* pOldNode = m_pNodeTail;
	TYPE returnValue = pOldNode->data;

	m_pNodeTail = pOldNode->pPrev;
	if (m_pNodeTail != NULL)
		m_pNodeTail->pNext = NULL;
	else
		m_pNodeHead = NULL;
	FreeNode(pOldNode);
	return returnValue;
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::InsertBefore(POSITION position, ARG_TYPE newElement)
{
	ASSERT_VALID(this);

	if (position == NULL)
		return AddHead(newElement); // insert before nothing -> head of the list

	// Insert it before position
	node* pOldNode = (node*) position;
	node* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
	pNewNode->data = newElement;

	if (pOldNode->pPrev != NULL)
	{
		ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(node)));
		pOldNode->pPrev->pNext = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeHead);
		m_pNodeHead = pNewNode;
	}
	pOldNode->pPrev = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::InsertAfter(POSITION position, ARG_TYPE newElement)
{
	ASSERT_VALID(this);

	if (position == NULL)
		return AddTail(newElement); // insert after nothing -> tail of the list

	// Insert it before position
	node* pOldNode = (node*) position;
	ASSERT(AfxIsValidAddress(pOldNode, sizeof(node)));
	node* pNewNode = NewNode(pOldNode, pOldNode->pNext);
	pNewNode->data = newElement;

	if (pOldNode->pNext != NULL)
	{
		ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(node)));
		pOldNode->pNext->pPrev = pNewNode;
	}
	else
	{
		ASSERT(pOldNode == m_pNodeTail);
		m_pNodeTail = pNewNode;
	}
	pOldNode->pNext = pNewNode;
	return (POSITION) pNewNode;
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_at(POSITION position)
{
	ASSERT_VALID(this);

	node* pOldNode = (node*) position;
	ASSERT(AfxIsValidAddress(pOldNode, sizeof(node)));

	// remove pOldNode from list
	if (pOldNode == m_pNodeHead)
	{
		m_pNodeHead = pOldNode->pNext;
	}
	else
	{
		ASSERT(AfxIsValidAddress(pOldNode->pPrev, sizeof(node)));
		pOldNode->pPrev->pNext = pOldNode->pNext;
	}
	if (pOldNode == m_pNodeTail)
	{
		m_pNodeTail = pOldNode->pPrev;
	}
	else
	{
		ASSERT(AfxIsValidAddress(pOldNode->pNext, sizeof(node)));
		pOldNode->pNext->pPrev = pOldNode->pPrev;
	}
	FreeNode(pOldNode);
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::FindIndex(index nIndex) const
{
	ASSERT_VALID(this);

	if (nIndex >= m_nCount || nIndex < 0)
		return NULL;  // went too far

	node* pNode = m_pNodeHead;
	while (nIndex--)
	{
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		pNode = pNode->pNext;
	}
	return (POSITION) pNode;
}

template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::Find(ARG_TYPE searchValue, POSITION startAfter) const
{
	ASSERT_VALID(this);

	node* pNode = (node*) startAfter;
	if (pNode == NULL)
	{
		pNode = m_pNodeHead;  // start at head
	}
	else
	{
		ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
		pNode = pNode->pNext;  // start after the one specified
	}

	for (; pNode != NULL; pNode = pNode->pNext)
		if (CompareElements<TYPE>(&pNode->data, &searchValue))
			return (POSITION)pNode;
	return NULL;
}
/*

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	base_object::Serialize(ar);

	if (ar.IsStoring())
	{
		ar.WriteCount(m_nCount);
		for (node* pNode = m_pNodeHead; pNode != NULL; pNode = pNode->pNext)
		{
			ASSERT(AfxIsValidAddress(pNode, sizeof(node)));
			TYPE* pData;
			/* 
			 * in some cases the & operator might be overloaded, and we cannot use it to obtain
			 * the address of a given object.  We then use the following trick to get the address
			 */
	/*		pData = reinterpret_cast< TYPE* >( &reinterpret_cast< int& >( static_cast< TYPE& >( pNode->data ) ) );
			SerializeElements<TYPE>(ar, pData, 1);
		}
	}
	else
	{
		DWORD_PTR nNewCount = ar.ReadCount();
		while (nNewCount--)
		{
			TYPE newData[1];
			SerializeElements<TYPE>(ar, newData, 1);
			AddTail(newData[0]);
		}
	}
}*/

#ifdef _DEBUG
template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::Dump(CDumpContext & dumpcontext) const
{
	base_object::Dump(dumpcontext);

	dumpcontext << "with " << m_nCount << " elements";
	if (dumpcontext.GetDepth() > 0)
	{
		POSITION pos = GetHeadPosition();
		while (pos != NULL)
		{
			TYPE temp[1];
			temp[0] = ((list*)this)->GetNext(pos);
			dumpcontext << "\n";
			DumpElements<TYPE>(spgraphics, temp, 1);
		}
	}

	dumpcontext << "\n";
}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::AssertValid() const
{
	base_object::AssertValid();

	if (m_nCount == 0)
	{
		// empty list
		ASSERT(m_pNodeHead == NULL);
		ASSERT(m_pNodeTail == NULL);
	}
	else
	{
		// non-empty list
		ASSERT(AfxIsValidAddress(m_pNodeHead, sizeof(node)));
		ASSERT(AfxIsValidAddress(m_pNodeTail, sizeof(node)));
	}
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CTypedPtrArray<BASE_CLASS, TYPE>

template<class BASE_CLASS, class TYPE>
class CTypedPtrArray : public BASE_CLASS
{
public:
	// Accessing elements
	TYPE get_at(index nIndex) const
		{ return (TYPE)BASE_CLASS::get_at(nIndex); }
	TYPE& element_at(index nIndex)
		{ return (TYPE&)BASE_CLASS::element_at(nIndex); }
	void set_at(index nIndex, TYPE ptr)
		{ BASE_CLASS::set_at(nIndex, ptr); }

	// Potentially growing the base_array
	void set_at_grow(index nIndex, TYPE newElement)
	   { BASE_CLASS::set_at_grow(nIndex, newElement); }
	index add(TYPE newElement)
	   { return BASE_CLASS::add(newElement); }
	index append(const CTypedPtrArray<BASE_CLASS, TYPE>& src)
	   { return BASE_CLASS::append(src); }
	void copy(const CTypedPtrArray<BASE_CLASS, TYPE>& src)
		{ BASE_CLASS::copy(src); }

	// Operations that move elements around
	void insert_at(index nIndex, TYPE newElement, count nCount = 1)
		{ BASE_CLASS::insert_at(nIndex, newElement, nCount); }
	void insert_at(index nStartIndex, CTypedPtrArray<BASE_CLASS, TYPE>* pNewArray)
	   { BASE_CLASS::insert_at(nStartIndex, pNewArray); }

	// overloaded operator helpers
	TYPE operator[](index nIndex) const
		{ return (TYPE)BASE_CLASS::operator[](nIndex); }
	TYPE& operator[](index nIndex)
		{ return (TYPE&)BASE_CLASS::operator[](nIndex); }
};

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


#define new DEBUG_NEW


#include "comparable_array.h"
#include "array_ptr.h"
#include "array_ptr_copy.h"
#include "array_ptr_alloc.h"
#include "array_app_copy.h"
#include "numeric_array.h"
#include "sort_array.h"
#include "class_sort_array.h"
