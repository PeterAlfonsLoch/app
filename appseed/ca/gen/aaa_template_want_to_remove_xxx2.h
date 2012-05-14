#pragma once


namespace gen
{
	class CComBSTR;
}
using gen::CComBSTR;


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
          rgsabound[0].cElements = this->get_size();
          pvar->parray = SafeArrayCreate(vt, 1, rgsabound);
          if(pvar->parray == NULL)
              return false;
          for(int i = 0; i < this->get_size(); i++)
          {
              SafeArrayPutElement(pvar->parray, (long *) &i, &ar.element_at(i));
          }
      }

      template < class TYPE, class ARG_TYPE >
	   bool CopySafeArray(base_array < TYPE, ARG_TYPE > & ar, VARIANT * var)
      {
      //    __MANAGE_STATE(__get_static_module_state())
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
   count countOld = this->get_count();
	ASSERT_VALID(this);
	ASSERT(nNewSize >= 0);

	if(nNewSize < 0 )
		throw invalid_argument_exception();

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
#undef new
			::new( (void *)( m_pData + i ) ) TYPE;
#define new DEBUG_NEW
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
#undef new
				::new( (void *)( m_pData + m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
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
			throw invalid_argument_exception();

#ifdef SIZE_T_MAX
		ASSERT(nNewMax <= SIZE_T_MAX/sizeof(TYPE)); // no overflow
#endif
//#undef new
		TYPE* pNewData = (TYPE*) new BYTE[(size_t)nNewMax * sizeof(TYPE)];
//#define new DEBUG_NEW

		// copy new data from old
		::gen::memcpy_s(pNewData, (size_t)nNewMax * sizeof(TYPE),
			m_pData, (size_t)m_nSize * sizeof(TYPE));

		// construct remaining elements
		ASSERT(nNewSize > m_nSize);
		memset((void *)(pNewData + m_nSize), 0, (size_t)(nNewSize-m_nSize) * sizeof(TYPE));
		for( int i = 0; i < nNewSize-m_nSize; i++ )
#undef new
			::new( (void *)( pNewData + m_nSize + i ) ) TYPE;
#define new DEBUG_NEW
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
			::gen::memcpy_s(pNewData, m_nSize * sizeof(TYPE),
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
		throw invalid_argument_exception();

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
		throw invalid_argument_exception();

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
      int i;
		for(i = 0; i < nCount; i++ )
			(m_pData + nOldSize + i)->~TYPE();
		// shift old data up to fill gap
		::gen::memmove_s(m_pData + nIndex + nCount, (nOldSize-nIndex) * sizeof(TYPE),
			m_pData + nIndex, (nOldSize-nIndex) * sizeof(TYPE));

		// re-init slots we copied from
		memset((void *)(m_pData + nIndex), 0, (size_t)nCount * sizeof(TYPE));
		for(i = 0; i < nCount; i++ )
      {
#undef new
			::new( (void *)( m_pData + nIndex + i ) ) TYPE;
#define new DEBUG_NEW
      }
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
		throw invalid_argument_exception();

	// just remove a range
	count nMoveCount = m_nSize - (nUpperBound);
	for( int i = 0; i < nCount; i++ )
		(m_pData + nIndex + i)->~TYPE();
	if (nMoveCount)
	{
		::gen::memmove_s(m_pData + nIndex, (size_t)nMoveCount * sizeof(TYPE),
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
		throw invalid_argument_exception();

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
void base_array<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
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
void base_array<TYPE, ARG_TYPE>::assert_valid() const
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
		ASSERT(__is_valid_address(m_pData, m_nMaxSize * sizeof(TYPE)));
	}
}
#endif //_DEBUG





/////////////////////////////////////////////////////////////////////////////
// typed_pointer_list<BASE_CLASS, TYPE>

template<class BASE_CLASS, class TYPE>
class _typed_pointer_list :
   virtual public BASE_CLASS
{
public:

/*   _typed_pointer_list(count nBlockSize = 10) :
      BASE_CLASS(nBlockSize)
   {
   }*/

	// peek at head or tail
	TYPE& get_head()
		{ return (TYPE&)BASE_CLASS::get_head(); }
	TYPE get_head() const
		{ return (TYPE)BASE_CLASS::get_head(); }
	TYPE& get_tail()
		{ return (TYPE&)BASE_CLASS::get_tail(); }
	TYPE get_tail() const
		{ return (TYPE)BASE_CLASS::get_tail(); }

	// get head or tail (and remove it) - don't call on is_empty list!
	TYPE remove_head()
		{ return (TYPE)BASE_CLASS::remove_head(); }
	TYPE remove_tail()
		{ return (TYPE)BASE_CLASS::remove_tail(); }

	// iteration
	TYPE& get_next(POSITION& rPosition)
		{ return (TYPE&)BASE_CLASS::get_next(rPosition); }
	TYPE get_next(POSITION& rPosition) const
		{ return (TYPE)BASE_CLASS::get_next(rPosition); }
	TYPE& get_previous(POSITION& rPosition)
		{ return (TYPE&)BASE_CLASS::get_previous(rPosition); }
	TYPE get_previous(POSITION& rPosition) const
		{ return (TYPE)BASE_CLASS::get_previous(rPosition); }

	// getting/modifying an element at a given position
	TYPE& get_at(POSITION position)
		{ return (TYPE&)BASE_CLASS::get_at(position); }
	TYPE get_at(POSITION position) const
		{ return (TYPE)BASE_CLASS::get_at(position); }
	void set_at(POSITION pos, TYPE newElement)
		{ BASE_CLASS::set_at(pos, newElement); }

	// inserting before or after a given position
	POSITION insert_before(POSITION position, TYPE newElement)
		{ return BASE_CLASS::insert_before(position, newElement); }
	POSITION insert_after(POSITION position, TYPE newElement)
		{ return BASE_CLASS::insert_after(position, newElement); }

	// transfer before or after a given position
	// Transfer semantics ensure no leakage by deleting the element in the case of an exception
	POSITION TransferInsertBefore(POSITION position, TYPE newElement)
	{
		try
		{
			return BASE_CLASS::insert_before(position, newElement);
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
			return BASE_CLASS::insert_after(position, newElement);
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}
};

template<class BASE_CLASS, class TYPE>
class typed_pointer_list :
   virtual public _typed_pointer_list<BASE_CLASS, TYPE>
{
public:

   typed_pointer_list(count nBlockSize = 10) :
      BASE_CLASS(nBlockSize)
   {
   }

	// add before head or after tail
	POSITION add_head(TYPE newElement)
		{ return BASE_CLASS::add_head(newElement); }
	POSITION add_tail(TYPE newElement)
		{ return BASE_CLASS::add_tail(newElement); }

	// transfer add before head or tail
	POSITION TransferAddHead(TYPE newElement)
	{
		try
		{
			return BASE_CLASS::add_head(newElement);
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
			return BASE_CLASS::add_tail(newElement);
		}
		catch(...)
		{
			delete newElement;
			throw;
		}
	}

	// add another list of elements before head or after tail
	void add_head(typed_pointer_list<BASE_CLASS, TYPE>* pNewList)
		{ BASE_CLASS::add_head(pNewList); }
	void add_tail(typed_pointer_list<BASE_CLASS, TYPE>* pNewList)
		{ BASE_CLASS::add_tail(pNewList); }
};

// need specialized version for base_object_list because of add_head/Tail ambiguity
template<> class typed_pointer_list<base_object_list, base_object_list*> :
   virtual public _typed_pointer_list<base_object_list, base_object_list*>
{
public:
// Construction
	typed_pointer_list(count nBlockSize = 10) :
      base_object_list(nBlockSize)
   {
   }

	// add before head or after tail
	POSITION add_head(base_object_list* newElement)
		{ return _typed_pointer_list<base_object_list, base_object_list*>::add_head((base_object*)newElement); }
	POSITION add_tail(base_object_list* newElement)
		{ return _typed_pointer_list<base_object_list, base_object_list*>::add_tail((base_object*)newElement); }

	// add another list of elements before head or after tail
	void add_head(typed_pointer_list<base_object_list, base_object_list*>* pNewList)
		{ _typed_pointer_list<base_object_list, base_object_list*>::add_head(pNewList); }
	void add_tail(typed_pointer_list<base_object_list, base_object_list*>* pNewList)
		{ _typed_pointer_list<base_object_list, base_object_list*>::add_tail(pNewList); }
};

// need specialized version for pointer_list because of add_head/Tail ambiguity
template<> class typed_pointer_list<pointer_list, pointer_list*> :
   public _typed_pointer_list<pointer_list, pointer_list*>
{
public:
	typed_pointer_list(count nBlockSize = 10) :
      pointer_list(nBlockSize)
   {
   }

	// add before head or after tail
	POSITION add_head(pointer_list* newElement)
		{ return _typed_pointer_list<pointer_list, pointer_list*>::add_head((void *)newElement); }
	POSITION add_tail(pointer_list* newElement)
		{ return _typed_pointer_list<pointer_list, pointer_list*>::add_tail((void *)newElement); }

	// add another list of elements before head or after tail
	void add_head(typed_pointer_list<pointer_list, pointer_list*>* pNewList)
		{ _typed_pointer_list<pointer_list, pointer_list*>::add_head(pNewList); }
	void add_tail(typed_pointer_list<pointer_list, pointer_list*>* pNewList)
		{ _typed_pointer_list<pointer_list, pointer_list*>::add_tail(pNewList); }
};


template<class BASE_CLASS, class KEY, class VALUE>
class typed_pointer_map : public BASE_CLASS
{
public:

	typed_pointer_map(count nBlockSize = 10) :
      BASE_CLASS(nBlockSize)
   {
   }

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






#undef new
#define new DEBUG_NEW
