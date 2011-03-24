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
	CObject* GetAt(int nIndex) const;
	void SetAt(int nIndex, CObject* newElement);

	CObject*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const CObject** GetData() const;
	CObject** GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, CObject* newElement);

	int Add(CObject* newElement);

	int Append(const simple_object_array& src);
	void Copy(const simple_object_array& src);

	// overloaded operator helpers
	CObject* operator[](int nIndex) const;
	CObject*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CObject* newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, simple_object_array* pNewArray);

// Implementation
protected:
	CObject** m_pData;   // the actual array of data
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
	typedef CObject* BASE_TYPE;
	typedef CObject* BASE_ARG_TYPE;
};

