#pragma once

class simple_object_array :
   virtual public ex1::serializable
{
public:

// Construction
	simple_object_array();

// Attributes
	int get_size() const;
	int get_upper_bound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	::radix::object* GetAt(int nIndex) const;
	void SetAt(int nIndex, ::radix::object* newElement);

	::radix::object*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const ::radix::object** GetData() const;
	::radix::object** GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, ::radix::object* newElement);

	int Add(::radix::object* newElement);

	int Append(const simple_object_array& src);
	void Copy(const simple_object_array& src);

	// overloaded operator helpers
	::radix::object* operator[](int nIndex) const;
	::radix::object*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, ::radix::object* newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, simple_object_array* pNewArray);

// Implementation
protected:
	::radix::object** m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~simple_object_array();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for class templates
	typedef ::radix::object* BASE_TYPE;
	typedef ::radix::object* BASE_ARG_TYPE;
};

