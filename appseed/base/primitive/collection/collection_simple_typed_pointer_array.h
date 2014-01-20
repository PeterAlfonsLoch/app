#pragma once

template<class BASE_CLASS, class TYPE>
class simple_typed_pointer_array : public BASE_CLASS
{
public:
	// Accessing elements
	TYPE get_at(index nIndex) const
		{ return (TYPE)BASE_CLASS::GetAt(nIndex); }
	TYPE & element_at(index nIndex)
		{ return (TYPE&)BASE_CLASS::ElementAt(nIndex); }
	void set_at(index nIndex, TYPE ptr)
		{ BASE_CLASS::SetAt(nIndex, ptr); }

	// Potentially growing the array
	void set_at_grow(index nIndex, TYPE newElement)
	   { BASE_CLASS::SetAtGrow(nIndex, newElement); }
	int32_t add(TYPE newElement)
	   { return BASE_CLASS::add(newElement); }
	int32_t add(const simple_typed_pointer_array<BASE_CLASS, TYPE>& src)
	   { return BASE_CLASS::Append(src); }
	void copy(const simple_typed_pointer_array<BASE_CLASS, TYPE>& src)
		{ BASE_CLASS::Copy(src); }

	// Operations that move elements around
	void insert_at(index nIndex, TYPE newElement, int32_t nCount = 1)
		{ BASE_CLASS::InsertAt(nIndex, newElement, nCount); }
	void insert_at(index nStartIndex, simple_typed_pointer_array<BASE_CLASS, TYPE>* pNewArray)
	   { BASE_CLASS::InsertAt(nStartIndex, pNewArray); }

	// overloaded operator helpers
	TYPE operator[](index nIndex) const
		{ return (TYPE)BASE_CLASS::operator[](nIndex); }
	TYPE& operator[](index nIndex)
		{ return (TYPE&)BASE_CLASS::operator[](nIndex); }
};
