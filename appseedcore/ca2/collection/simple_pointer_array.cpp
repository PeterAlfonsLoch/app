#include "StdAfx.h"

int simple_pointer_array::GetSize() const
	{ return m_nSize; }
int simple_pointer_array::GetUpperBound() const
	{ return m_nSize-1; }
void simple_pointer_array::RemoveAll()
	{ SetSize(0); }
void* simple_pointer_array::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
void simple_pointer_array::SetAt(int nIndex, void* newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }

void*& simple_pointer_array::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
const void** simple_pointer_array::GetData() const
	{ return (const void**)m_pData; }
void** simple_pointer_array::GetData()
	{ return (void**)m_pData; }
int simple_pointer_array::Add(void* newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

void* simple_pointer_array::operator[](int nIndex) const
	{ return GetAt(nIndex); }
void*& simple_pointer_array::operator[](int nIndex)
	{ return ElementAt(nIndex); }

