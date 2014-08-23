#pragma once

template<class AXIS_CLASS, class TYPE>
class simple_typed_pointer_array : public AXIS_CLASS
{
public:
	// Accessing elements
	TYPE get_at(index nIndex) const
		{ return (TYPE)AXIS_CLASS::GetAt(nIndex); }
	TYPE & element_at(index nIndex)
		{ return (TYPE&)AXIS_CLASS::ElementAt(nIndex); }
	void set_at(index nIndex, TYPE ptr)
		{ AXIS_CLASS::SetAt(nIndex, ptr); }

	// Potentially growing the array
	void set_at_grow(index nIndex, TYPE newElement)
	   { AXIS_CLASS::SetAtGrow(nIndex, newElement); }
	int32_t add(TYPE newElement)
	   { return AXIS_CLASS::add(newElement); }
	int32_t add(const simple_typed_pointer_array<AXIS_CLASS, TYPE>& src)
	   { return AXIS_CLASS::Append(src); }
	void copy(const simple_typed_pointer_array<AXIS_CLASS, TYPE>& src)
		{ AXIS_CLASS::Copy(src); }

	// Operations that move elements around
	void insert_at(index nIndex, TYPE newElement, int32_t nCount = 1)
		{ AXIS_CLASS::InsertAt(nIndex, newElement, nCount); }
	void insert_at(index nStartIndex, simple_typed_pointer_array<AXIS_CLASS, TYPE>* pNewArray)
	   { AXIS_CLASS::InsertAt(nStartIndex, pNewArray); }

	// overloaded operator helpers
	TYPE operator[](index nIndex) const
		{ return (TYPE)AXIS_CLASS::operator[](nIndex); }
	TYPE& operator[](index nIndex)
		{ return (TYPE&)AXIS_CLASS::operator[](nIndex); }
};
