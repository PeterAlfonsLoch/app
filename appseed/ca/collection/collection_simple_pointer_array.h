#pragma once

class simple_pointer_array :
   virtual public base_object
{
public:

// Construction
	simple_pointer_array();

// Attributes
	int get_size() const;
	int get_upper_bound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void free_extra();
	void remove_all();

	// Accessing elements
	void* get_at(int nIndex) const;
	void set_at(int nIndex, void* newElement);

	void*& this->element_at(int nIndex);

	// Direct Access to the element data (may return NULL)
	const void** get_data() const;
	void** get_data();

	// Potentially growing the array
	void set_at_grow(int nIndex, void* newElement);

	int add(void* newElement);

	int add(const simple_pointer_array& src);
	void copy(const simple_pointer_array& src);

	// overloaded operator helpers
	void* operator[](index nIndex) const;
	void*& operator[](index nIndex);

	// Operations that move elements around
	void insert_at(index nIndex, void* newElement, int nCount = 1);

	void remove_at(index nIndex, int nCount = 1);
	void insert_at(index nStartIndex, simple_pointer_array* pNewArray);

// Implementation
protected:
	void** m_pData;   // the actual array of data
	::count m_nSize;     // # of elements (upperBound - 1)
	::count m_nMaxSize;  // max allocated
	::count m_nGrowBy;   // grow amount


public:
	~simple_pointer_array();
	void dump(dump_context&) const;
	void assert_valid() const;

protected:
	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};

