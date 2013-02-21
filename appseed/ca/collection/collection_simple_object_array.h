#pragma once

class simple_object_array :
   virtual public gen::serializable
{
public:

// Construction
	simple_object_array();

// Attributes
	int32_t get_size() const;
	int32_t get_upper_bound() const;
	void SetSize(int32_t nNewSize, int32_t nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void remove_all();

	// Accessing elements
	::gen::object* GetAt(int32_t nIndex) const;
	void SetAt(int32_t nIndex, ::gen::object* newElement);

	::gen::object*& ElementAt(int32_t nIndex);

	// Direct Access to the element data (may return NULL)
	const ::gen::object** GetData() const;
	::gen::object** GetData();

	// Potentially growing the array
	void SetAtGrow(int32_t nIndex, ::gen::object* newElement);

	int32_t add(::gen::object* newElement);

	int32_t Append(const simple_object_array& src);
	void Copy(const simple_object_array& src);

	// overloaded operator helpers
	::gen::object* operator[](int32_t nIndex) const;
	::gen::object*& operator[](int32_t nIndex);

	// Operations that move elements around
	void InsertAt(int32_t nIndex, ::gen::object* newElement, int32_t nCount = 1);

	void RemoveAt(int32_t nIndex, int32_t nCount = 1);
	void InsertAt(int32_t nStartIndex, simple_object_array* pNewArray);

// Implementation
protected:
	::gen::object** m_pData;   // the actual array of data
	int32_t m_nSize;     // # of elements (upperBound - 1)
	int32_t m_nMaxSize;  // max allocated
	int32_t m_nGrowBy;   // grow amount


public:
	~simple_object_array();

	void Serialize(CArchive&);
#ifdef DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for class templates
	typedef ::gen::object* BASE_TYPE;
	typedef ::gen::object* BASE_ARG_TYPE;
};

