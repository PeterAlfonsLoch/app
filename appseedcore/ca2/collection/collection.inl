#pragma once



////////////////////////////////////////////////////////////////////////////
/*
inline INT_PTR CPtrArray::get_size() const
   { return m_nSize; }
inline INT_PTR CPtrArray::get_count() const
   { return m_nSize; }
inline BOOL CPtrArray::is_empty() const
   { return m_nSize == 0; }
inline INT_PTR CPtrArray::get_upper_bound() const
   { return m_nSize-1; }
inline void CPtrArray::remove_all()
   { set_size(0); }
inline void * CPtrArray::get_at(INT_PTR nIndex) const
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      return m_pData[nIndex]; }
inline void CPtrArray::set_at(INT_PTR nIndex, void * newElement)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      m_pData[nIndex] = newElement; }

inline void *& CPtrArray::element_at(index nIndex)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      return m_pData[nIndex]; }
inline const void ** CPtrArray::get_data() const
   { return (const void **)m_pData; }
inline void ** CPtrArray::get_data()
   { return (void **)m_pData; }
inline index CPtrArray::add(void * newElement)
   { index nIndex = m_nSize;
      set_at_grow(nIndex, newElement);
      return nIndex; }

inline void * CPtrArray::operator[](INT_PTR nIndex) const
   { return get_at(nIndex); }
inline void *& CPtrArray::operator[](INT_PTR nIndex)
   { return element_at(nIndex); }

*/
////////////////////////////////////////////////////////////////////////////
/*
inline INT_PTR CObArray::get_size() const
   { return m_nSize; }
inline INT_PTR CObArray::get_count() const
   { return m_nSize; }
inline BOOL CObArray::is_empty() const
   { return m_nSize == 0; }
inline INT_PTR CObArray::get_upper_bound() const
   { return m_nSize-1; }
inline void CObArray::remove_all()
   { set_size(0); }
inline ::radix::object* CObArray::get_at(INT_PTR nIndex) const
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      return m_pData[nIndex]; }
inline void CObArray::set_at(INT_PTR nIndex, ::radix::object* newElement)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      m_pData[nIndex] = newElement; }

inline ::radix::object*& CObArray::element_at(INT_PTR nIndex)
   { ASSERT(nIndex >= 0 && nIndex < m_nSize);
      if( nIndex < 0 || nIndex >= m_nSize )
         AfxThrowInvalidArgException();
      return m_pData[nIndex]; }
inline const ::radix::object** CObArray::get_data() const
   { return (const ::radix::object**)m_pData; }
inline ::radix::object** CObArray::get_data()
   { return (::radix::object**)m_pData; }
inline INT_PTR CObArray::add(::radix::object* newElement)
   { INT_PTR nIndex = m_nSize;
      set_at_grow(nIndex, newElement);
      return nIndex; }

inline ::radix::object* CObArray::operator[](INT_PTR nIndex) const
   { return get_at(nIndex); }
inline ::radix::object*& CObArray::operator[](INT_PTR nIndex)
   { return element_at(nIndex); }
*/


////////////////////////////////////////////////////////////////////////////

inline count pointer_list::get_count() const
   { return m_nCount; }
inline count pointer_list::get_size() const
   { return m_nCount; }
inline bool pointer_list::is_empty() const
   { return m_nCount == 0; }
inline void *& pointer_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline const void * pointer_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline void *& pointer_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline const void * pointer_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline POSITION pointer_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION pointer_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline void *& pointer_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline const void * pointer_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline void *& pointer_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline const void * pointer_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline void *& pointer_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline const void * pointer_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline void pointer_list::set_at(POSITION pos, void * newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline count base_object_list::get_count() const
   { return m_nCount; }
inline count base_object_list::get_size() const
   { return m_nCount; }
inline bool base_object_list::is_empty() const
   { return m_nCount == 0; }
inline ::radix::object*& base_object_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline const ::radix::object* base_object_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline ::radix::object*& base_object_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline const ::radix::object* base_object_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline POSITION base_object_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION base_object_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline ::radix::object*& base_object_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline const ::radix::object* base_object_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline ::radix::object*& base_object_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline const ::radix::object* base_object_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline ::radix::object*& base_object_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline const ::radix::object* base_object_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline void base_object_list::set_at(POSITION pos, ::radix::object* newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline INT_PTR string_list::get_count() const
   { return m_nCount; }
inline INT_PTR string_list::get_size() const
   { return m_nCount; }
inline bool string_list::is_empty() const
   { return m_nCount == 0; }
inline bool string_list::has_elements(count nMinimumCount) const
   { return m_nCount >= nMinimumCount; }
inline string & string_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline const string & string_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline string & string_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline const string & string_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline POSITION string_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION string_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline string & string_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline const string & string_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline string & string_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline const string & string_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline string & string_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline const string & string_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline void string_list::set_at(POSITION pos, const char * newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }

inline void string_list::set_at(POSITION pos, const string & newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }



////////////////////////////////////////////////////////////////////////////

inline INT_PTR CMapWordToPtr::get_count() const
   { return m_nCount; }
inline INT_PTR CMapWordToPtr::get_size() const
   { return m_nCount; }
inline BOOL CMapWordToPtr::is_empty() const
   { return m_nCount == 0; }
inline void CMapWordToPtr::set_at(WORD key, void * newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapWordToPtr::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapWordToPtr::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline INT_PTR CMapPtrToWord::get_count() const
   { return m_nCount; }
inline INT_PTR CMapPtrToWord::get_size() const
   { return m_nCount; }
inline BOOL CMapPtrToWord::is_empty() const
   { return m_nCount == 0; }
inline void CMapPtrToWord::set_at(void * key, WORD newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapPtrToWord::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapPtrToWord::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline INT_PTR CMapPtrToPtr::get_count() const
   { return m_nCount; }
inline INT_PTR CMapPtrToPtr::get_size() const
   { return m_nCount; }
inline BOOL CMapPtrToPtr::is_empty() const
   { return m_nCount == 0; }
inline void CMapPtrToPtr::set_at(void * key, void * newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapPtrToPtr::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapPtrToPtr::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////

inline INT_PTR CMapWordToOb::get_count() const
   { return m_nCount; }
inline INT_PTR CMapWordToOb::get_size() const
   { return m_nCount; }
inline BOOL CMapWordToOb::is_empty() const
   { return m_nCount == 0; }
inline void CMapWordToOb::set_at(WORD key, ::radix::object* newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapWordToOb::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapWordToOb::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline INT_PTR CMapStringToPtr::get_count() const
   { return m_nCount; }
inline INT_PTR CMapStringToPtr::get_size() const
   { return m_nCount; }
inline BOOL CMapStringToPtr::is_empty() const
   { return m_nCount == 0; }
inline void CMapStringToPtr::set_at(const char * key, void * newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapStringToPtr::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapStringToPtr::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline INT_PTR CMapStringToOb::get_count() const
   { return m_nCount; }
inline INT_PTR CMapStringToOb::get_size() const
   { return m_nCount; }
inline BOOL CMapStringToOb::is_empty() const
   { return m_nCount == 0; }
inline void CMapStringToOb::set_at(const char * key, ::radix::object* newValue)
   { (*this)[key] = newValue; }
inline POSITION CMapStringToOb::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT CMapStringToOb::GetHashTableSize() const
   { return m_nHashTableSize; }


////////////////////////////////////////////////////////////////////////////
inline INT_PTR string_to_string_map::get_count() const
   { return m_nCount; }
inline INT_PTR string_to_string_map::get_size() const
   { return m_nCount; }
inline bool string_to_string_map::is_empty(count countMinimum) const
   { return m_nCount < countMinimum; }
inline bool string_to_string_map::has_elements(count countMinimum) const
   { return m_nCount >= countMinimum; }
inline void string_to_string_map::set_at(const char * key, const char * newValue)
   { (*this)[key] = newValue; }
inline POSITION string_to_string_map::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT string_to_string_map::GetHashTableSize() const
   { return m_nHashTableSize; }

