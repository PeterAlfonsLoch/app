#include "StdAfx.h"

int simple_object_array::GetSize() const
{
      return m_nSize; 
}

int simple_object_array::GetUpperBound() const
{
   return m_nSize-1;
}

 void simple_object_array::RemoveAll()
	{ SetSize(0); }
 CObject* simple_object_array::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
 void simple_object_array::SetAt(int nIndex, CObject* newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }

 CObject*& simple_object_array::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
 const CObject** simple_object_array::GetData() const
	{ return (const CObject**)m_pData; }
 CObject** simple_object_array::GetData()
	{ return (CObject**)m_pData; }
 int simple_object_array::Add(CObject* newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

 CObject* simple_object_array::operator[](int nIndex) const
	{ return GetAt(nIndex); }
 CObject*& simple_object_array::operator[](int nIndex)
	{ return ElementAt(nIndex); }
