#pragma once


class CLASS_DECL_ca ptr_array :
   virtual public comparable_raw_array < void * >
{
public:

};




/////////////////////////////////////////////////////////////////////////////
// CTypedPtrArray<BASE_CLASS, POINTER>

template < class POINTER, class BASE_CLASS = ptr_array>
class typed_ptr_array : 
   public BASE_CLASS
{
public:
	// Accessing elements
	POINTER GetAt(INT_PTR nIndex) const
		{ return (POINTER)BASE_CLASS::GetAt(nIndex); }
	POINTER& ElementAt(INT_PTR nIndex)
		{ return (POINTER&)BASE_CLASS::ElementAt(nIndex); }
	void SetAt(INT_PTR nIndex, POINTER ptr)
		{ BASE_CLASS::SetAt(nIndex, ptr); }

	// Potentially growing the array
	void SetAtGrow(INT_PTR nIndex, POINTER newElement)
		{ BASE_CLASS::SetAtGrow(nIndex, newElement); }
	INT_PTR Add(POINTER newElement)
		{ return BASE_CLASS::Add(newElement); }
	INT_PTR Append(const typed_ptr_array<POINTER, BASE_CLASS>& src)
		{ return BASE_CLASS::Append(src); }
	void Copy(const typed_ptr_array<POINTER, BASE_CLASS>& src)
		{ BASE_CLASS::Copy(src); }

	// Operations that move elements around
	void InsertAt(INT_PTR nIndex, POINTER newElement, INT_PTR nCount = 1)
		{ BASE_CLASS::InsertAt(nIndex, newElement, nCount); }
	void InsertAt(INT_PTR nStartIndex, typed_ptr_array<BASE_CLASS, POINTER>* pNewArray)
		{ BASE_CLASS::InsertAt(nStartIndex, pNewArray); }

	// overloaded operator helpers
	POINTER operator[](INT_PTR nIndex) const
		{ return (POINTER)BASE_CLASS::operator[](nIndex); }
	POINTER& operator[](INT_PTR nIndex)
		{ return (POINTER&)BASE_CLASS::operator[](nIndex); }
};



