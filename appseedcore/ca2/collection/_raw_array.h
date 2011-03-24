#pragma once

// raw array is a special array and should be used with care
// it uses operations like memmove and memcopy to move objects and does not
// call constructors and destructors for the elements
// it is faster than the more generic arrays and is proper for use
// with strict structs and primitive data types

template<class TYPE, class ARG_TYPE = const TYPE &>
class raw_array : 
   virtual public base_object
{
public:
	raw_array();

	count get_size() const;
	count get_count() const;
	bool is_empty() const;
	index get_upper_bound(index i = 0) const;
	void set_size(index nNewSize, count nGrowBy = -1);

	void free_extra();
	void remove_all();
   void remove_last();



	// Accessing elements
	const TYPE& get_at(index nIndex) const;
	TYPE& get_at(index nIndex);
	void set_at(index nIndex, ARG_TYPE newElement);

   const TYPE& element_at(index nIndex) const;
	TYPE& element_at(index nIndex);

   const TYPE& first_element(index index = 0) const;
	TYPE& first_element(index index = 0);

   const TYPE& last_element(index index = 0) const;
	TYPE& last_element(index index = 0);

	// Direct Access to the element data (may return NULL)
	const TYPE* get_data() const;
	TYPE* get_data();

	// Potentially growing the raw_array
	void set_at_grow(index nIndex, ARG_TYPE newElement);
	index add(ARG_TYPE newElement);
   index add(const raw_array& src);
	index append(const raw_array& src);
	void copy(const raw_array& src);
   index push(ARG_TYPE newElement);

   

	// overloaded operator helpers
	const TYPE& operator[](index nIndex) const;
	TYPE& operator[](index nIndex);

	// Operations that move elements around
	void insert_at(index nIndex, ARG_TYPE newElement, count nCount = 1);
	void remove_at(index nIndex, count nCount = 1);
	void insert_at(index nStartIndex, raw_array* pNewArray);
   TYPE pop(index index = 0);
   void swap(index index1, index index2);

   raw_array & operator = (const raw_array & src);

// Implementation
protected:
	TYPE *   m_pData;    // the actual raw_array of data
	count    m_nSize;    // # of elements (upperBound - 1)
	count    m_nMaxSize; // max allocated
	count    m_nGrowBy;  // grow amount

public:
	virtual ~raw_array();
#ifdef _DEBUG
	void dump(dump_context&) const;
	void assert_valid() const;
#endif

	typedef TYPE BASE_TYPE;
	typedef ARG_TYPE BASE_ARG_TYPE;

};

/////////////////////////////////////////////////////////////////////////////
// raw_array<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_size() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
inline count raw_array<TYPE, ARG_TYPE>::get_count() const
	{ return m_nSize; }
template<class TYPE, class ARG_TYPE>
inline bool raw_array<TYPE, ARG_TYPE>::is_empty() const
	{ return m_nSize == 0; }
template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::get_upper_bound(index index) const
	{ return m_nSize - 1 - index; }
template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::remove_all()
{
   set_size(0, -1);
}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::remove_last()
{
   remove_at(get_upper_bound());
}

template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::get_at(index nIndex)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::get_at(index nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::set_at(index nIndex, ARG_TYPE newElement)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		m_pData[nIndex] = newElement; 
	else
		AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::element_at(index nIndex) const
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::element_at(index nIndex)
{ 
	ASSERT(nIndex >= 0 && nIndex < m_nSize);
	if(nIndex >= 0 && nIndex < m_nSize)
		return m_pData[nIndex]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::first_element(index nIndex) const
{ 
	return element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::first_element(index nIndex)
{ 
	return element_at(nIndex);
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::last_element(index index) const
{ 
   index  = get_upper_bound(index);
   ASSERT(index >= 0 && index < m_nSize);
	if(index >= 0 && index < m_nSize)
		return m_pData[index]; 
	AfxThrowInvalidArgException();		
}
template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::last_element(index index)
{ 
   index  = get_upper_bound(index);
   ASSERT(index >= 0 && index < m_nSize);
	if(index >= 0 && index < m_nSize)
		return m_pData[index]; 
	AfxThrowInvalidArgException();		
}

template<class TYPE, class ARG_TYPE>
inline const TYPE* raw_array<TYPE, ARG_TYPE>::get_data() const
{
   return (const TYPE*)m_pData; 
}

template<class TYPE, class ARG_TYPE>
inline TYPE* raw_array<TYPE, ARG_TYPE>::get_data()
{
   return (TYPE*)m_pData; 
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
{ 
   index nIndex = m_nSize;
	set_at_grow(nIndex, newElement);
	return nIndex;
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::add(const raw_array & src)
{ 
	return append(src);
}

template<class TYPE, class ARG_TYPE>
inline index raw_array<TYPE, ARG_TYPE>::push(ARG_TYPE newElement)
{
   return add(newElement); 
}

template<class TYPE, class ARG_TYPE>
inline const TYPE& raw_array<TYPE, ARG_TYPE>::operator[](index nIndex) const
{
   return get_at(nIndex); 
}

template<class TYPE, class ARG_TYPE>
inline TYPE& raw_array<TYPE, ARG_TYPE>::operator[](index nIndex)
{
   return element_at(nIndex); 
}

template<class TYPE, class ARG_TYPE>
inline TYPE raw_array<TYPE, ARG_TYPE>::pop(index index)
{
	index = get_upper_bound(index);
   ASSERT(index >= 0 && index < m_nSize);
	if(index >= 0 && index < m_nSize)
   {
      TYPE t = m_pData[index]; 
      remove_at(index);
      return t;
   }
	AfxThrowInvalidArgException();		
}

template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::swap(index index1, index index2)
{
   TYPE t = m_pData[index2]; 
   m_pData[index2] = m_pData[index1];
   m_pData[index1] = t;
}

template<class TYPE, class ARG_TYPE>
inline raw_array<TYPE, ARG_TYPE> & raw_array<TYPE, ARG_TYPE>::operator = (const raw_array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}

// out-of-line functions

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::raw_array()
{
	m_pData = NULL;
	m_nSize = m_nMaxSize = m_nGrowBy = 0;
}

template<class TYPE, class ARG_TYPE>
raw_array<TYPE, ARG_TYPE>::~raw_array()
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
void raw_array<TYPE, ARG_TYPE>::set_size(count nNewSize, count nGrowBy)
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
		}
		m_nSize = nNewSize;
	}
	else
	{
		// otherwise, grow raw_array
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
		delete[] (BYTE*)m_pData;
		m_pData = pNewData;
		m_nSize = nNewSize;
		m_nMaxSize = nNewMax;
	}
}

template<class TYPE, class ARG_TYPE>
index raw_array<TYPE, ARG_TYPE>::append(const raw_array& src)
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
void raw_array<TYPE, ARG_TYPE>::copy(const raw_array& src)
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
void raw_array<TYPE, ARG_TYPE>::free_extra()
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
void raw_array<TYPE, ARG_TYPE>::set_at_grow(index nIndex, ARG_TYPE newElement)
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
void raw_array<TYPE, ARG_TYPE>::insert_at(index nIndex, ARG_TYPE newElement, count nCount /*=1*/)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0);    // will expand to meet need
	ASSERT(nCount > 0);     // zero or negative size not allowed

	if(nIndex < 0 || nCount <= 0)
		AfxThrowInvalidArgException();

	if (nIndex >= m_nSize)
	{
		// adding after the end of the raw_array
		set_size(nIndex + nCount, -1);   // grow so nIndex is valid
	}
	else
	{
		// inserting in the middle of the raw_array
		count nOldSize = m_nSize;
		set_size(m_nSize + nCount, -1);  // grow it to new size
		// destroy intial data before copying over it
		// shift old data up to fill gap
		::_template::checked::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
			m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
		for( int i = 0; i < nCount; i++ )
#undef new
			::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new DEBUG_NEW
	}

	// insert new value in the gap
	ASSERT(nIndex + nCount <= m_nSize);
	while (nCount--)
		m_pData[nIndex++] = newElement;
}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::remove_at(index nIndex, count nCount)
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
	if (nMoveCount)
	{
		::_template::checked::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
			m_pData + nUpperBound, (size_t)nMoveCount * sizeof(TYPE));
	}
	m_nSize -= nCount;
}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::insert_at(index nStartIndex, raw_array* pNewArray)
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
#ifdef _DEBUG
template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
{
	base_object::dump(dumpcontext);

	dumpcontext << "with " << m_nSize << " elements";
	if (dumpcontext.GetDepth() > 0)
	{
		dumpcontext << "\n";
		dump_elements<TYPE>(dumpcontext, m_pData, m_nSize);
	}

	dumpcontext << "\n";
}

template<class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::assert_valid() const
{
	base_object::assert_valid();

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
		ASSERT(fx_is_valid_address(m_pData, m_nMaxSize * sizeof(TYPE)));
	}
}
#endif //_DEBUG

