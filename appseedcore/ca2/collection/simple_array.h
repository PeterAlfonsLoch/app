#pragma once

template<class TYPE, class ARG_TYPE = const TYPE&>
class simple_array : 
   virtual public base_object
{
public:
	simple_array();
   simple_array(const simple_array <TYPE, ARG_TYPE> & a);
   virtual ~simple_array();

// Attributes
	count get_size() const;
	count get_count() const;
	bool is_empty() const;
	index get_upper_bound() const;
	count set_size(count nNewSize, count nGrowBy = -1);

	void free_extra();

	// Accessing elements
	const TYPE& get_at(index nIndex) const;
	TYPE& get_at(index nIndex);
	void set_at(index nIndex, ARG_TYPE newElement);
	const TYPE& element_at(index nIndex) const;
	TYPE& element_at(index nIndex);

	// Direct Access to the element data (may return NULL)
	const TYPE* get_data() const;
	TYPE* get_data();

	// Potentially growing the simple_array
	void set_at_grow(index nIndex, ARG_TYPE newElement);
   virtual index add_new(count count = 1);
	virtual index add(ARG_TYPE newElement);
   virtual count add(const simple_array& src); // for disambiguation
   virtual count add_array(const simple_array& src);
	void copy(const simple_array& src);

	// overloaded operator helpers
	const TYPE& operator[](index nIndex) const;
	TYPE& operator[](index nIndex);

	// Operations that move elements around
	void insert_at(index nIndex, ARG_TYPE newElement, count nCount = 1);
	void remove_at(index nIndex, count nCount = 1);
   void insert_at(index nStartIndex, simple_array* pNewArray);
	void insert_array_at(index nStartIndex, simple_array* pNewArray); // for disambiguation
   void remove_last();

   void increment_size(count add_up = 1);
   
   count remove_all(bool bResize = false);

   void swap(index i1, index i2);

	simple_array <TYPE, ARG_TYPE> & operator = (const simple_array <TYPE, ARG_TYPE> & a);

// Implementation
protected:
	TYPE *   m_pData;   // the actual simple_array of data
	count    m_nSize;     // # of elements (upperBound - 1)
	count    m_nMaxSize;  // max allocated
	count    m_nGrowBy;   // grow amount

public:
//	void Serialize(CArchive&);
#ifdef _DEBUG
	void dump(dump_context&) const;
	void assert_valid() const;
#endif
};

template<class TYPE, class ARG_TYPE>
simple_array<TYPE, ARG_TYPE>::simple_array(const simple_array<TYPE, ARG_TYPE> & a)
{
   m_pData = NULL;
   m_nSize = m_nMaxSize = m_nGrowBy = 0;
   operator =(a);
}

template<class TYPE, class ARG_TYPE>
void simple_array<TYPE, ARG_TYPE>::
increment_size(count iAddUp)
{
    set_size(get_size() + iAddUp);
}

template <class TYPE, class ARG_TYPE>
count simple_array<TYPE, ARG_TYPE>::
remove_all(bool bResize)
{
   count countOld = get_count();
   if(bResize)
   {
      set_size(0, -1);
   }
   else
   {
      remove_at(0, m_nSize);
   }
   return countOld;
}

template <class TYPE, class ARG_TYPE>
void simple_array<TYPE, ARG_TYPE>::swap(index i1, index i2)
{
    TYPE t;
    t = element_at(i1);
    element_at(i1) = element_at(i2);
    element_at(i2) = t;
}


template <class TYPE, class ARG_TYPE>
simple_array <TYPE, ARG_TYPE> & 
simple_array<TYPE, ARG_TYPE>::
operator = (const simple_array <TYPE, ARG_TYPE> & a)
{
   if(&a == this)
      return *this;
	copy(a);
	return * this;
}

typedef CLASS_DECL_ca simple_array < int, int > simple_int_array;