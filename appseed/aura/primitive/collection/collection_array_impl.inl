#pragma once

//
// see collection_array_decl.h for declaration
//
// raw_array is an array_data that does not call constructors or destructor in elements
// array_data is an array_data that call only copy constructor and destructor in elements
// array_data is an array_data that call default constructors, copy constructs and destructors in elements

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_size() const
{
   return m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_count() const
{
   return this->get_size();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_byte_count() const
{
   return this->get_size_in_bytes();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::size() const
{
   return this->get_size();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::count() const
{
   return this->get_count();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_data < TYPE, ARG_TYPE, ALLOCATOR > ::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_data < TYPE, ARG_TYPE, ALLOCATOR > ::empty(::count countMinimum) const
{
   return is_empty(countMinimum);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_data < TYPE, ARG_TYPE, ALLOCATOR > ::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_upper_bound(index index) const
{
   return m_nSize + index;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_lower_bound(index index) const
{
   return index;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline bool array_data < TYPE, ARG_TYPE, ALLOCATOR > ::bounds(index index) const
{
   return index >= 0 && index < m_nSize;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::remove_all()
{
   return allocate(0, -1);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline ::count array_data < TYPE, ARG_TYPE, ALLOCATOR > ::set_size(index nNewSize, ::count nGrowBy) // does not call default constructors on new items/elements
{
   return allocate(nNewSize, nGrowBy);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::clear()
{
   remove_all();
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::remove_last()
{
   ASSERT(m_nSize > 0);
   remove_at(get_upper_bound());
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::zero(index iStart,::count c)
{
   if(c < 0)
   {
      c = get_size() - iStart;
   }
   ::zero(&m_pData[iStart],c * sizeof(TYPE));
}


























template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(index nIndex)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::set_at(index nIndex, ARG_TYPE newElement)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   get_data()[nIndex] = newElement;
}


//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline const TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
//
//
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(index nIndex)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::first(index nIndex) const
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::first(index nIndex)
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::last(index index) const
{
   return element_at(this->get_upper_bound(index));
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::last(index index)
{
   return element_at(this->get_upper_bound(index));
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE* array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_data() const
{
   return (const TYPE*)this->m_pData;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE* array_data < TYPE, ARG_TYPE, ALLOCATOR > ::get_data()
{
   return (TYPE*)this->m_pData;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename array_data < TYPE, ARG_TYPE, ALLOCATOR >::iterator array_data < TYPE, ARG_TYPE, ALLOCATOR > ::add(ARG_TYPE newElement)
{
   
   index nIndex = this->m_nSize;
   
   this->allocate(nIndex + 1);
   
   last() = newElement;
   
   return &(last() = newElement);

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename array_data < TYPE, ARG_TYPE, ALLOCATOR >::iterator array_data < TYPE, ARG_TYPE, ALLOCATOR > ::add(const array_data & src)
{

   return append(src);

}






template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](index nIndex) const
{

   return get_data()[nIndex];

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array_data < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](index nIndex)
{

   return get_data()[nIndex];

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::iswap(index index1, index index2)
{
   TYPE t = get_data()[index1];
   get_data()[index1] = get_data()[index2];
   get_data()[index2] = t;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::swap(iterator it1, iterator it2)
{
   TYPE t = *it1;
   *it1 = *it2;
   *it2 = t;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array_data < TYPE, ARG_TYPE, ALLOCATOR >  & array_data < TYPE, ARG_TYPE, ALLOCATOR > ::operator = (const array_data & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}





template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_data < TYPE, ARG_TYPE, ALLOCATOR > ::array_data(const array_data & a)
{

   set_app(a.get_app());
   
   operator = (a);

}


template < class TYPE,class ARG_TYPE,class ALLOCATOR >
inline array_data < TYPE,ARG_TYPE,ALLOCATOR > ::array_data(::std::initializer_list < TYPE >  l)
{
   forallref(l)
   {
      add((ARG_TYPE) item);
   }
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_data < TYPE, ARG_TYPE, ALLOCATOR > ::array_data(::count n, ARG_TYPE t) 
{

   ::iter::add_item(*this, t, n);

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_data < TYPE, ARG_TYPE, ALLOCATOR > ::~array_data()
{
   this->remove_all(); // on_destruct_element is virtual and won't be available for array_data
   destroy();


}




//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline typename array_data < TYPE, ARG_TYPE, ALLOCATOR >::iterator array_data < TYPE, ARG_TYPE, ALLOCATOR > ::append(const array_data& src)
//{
//   ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   if(this == &src)
//      throw invalid_argument_exception(this->get_app());
//
//   ::count nOldSize = this->m_nSize;
//   this->allocate(this->m_nSize + src.m_nSize);
//   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, src.m_nSize);
//   
//   return &this->m_pData[m_nSize-1];
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::copy(const array_data& src)
//{
//   ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   if(this != &src)
//   {
//      this->allocate(src.m_nSize);
//      CopyElements<TYPE>(this->m_pData,src.m_pData,src.m_nSize);
//   }
//}
//






template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << this->m_nSize << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      dumpcontext << "\n";
      dump_elements<TYPE>(dumpcontext, this->get_data(), this->m_nSize);
   }

   dumpcontext << "\n";
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::assert_valid() const
{
   object::assert_valid();

   if (this->m_pData == NULL)
   {
      ASSERT(this->m_nSize == 0);
      ASSERT(this->m_nMaxSize == 0);
   }
   else
   {
      ASSERT(this->m_nSize >= 0);
      ASSERT(this->m_nMaxSize >= 0);
      ASSERT(this->m_nSize <= this->m_nMaxSize);
      ASSERT(__is_valid_address(this->m_pData, this->m_nMaxSize * sizeof(TYPE)));
   }
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename array_data < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array_data < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator pos)
{

   this->remove_at(pos.m_p - m_pData);
   
   return pos.m_p;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename array_data < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array_data < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator first, iterator last)
{
   
   remove_at(first.m_p - m_pData, last.m_p - first.m_p);

   return first.m_p;

}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >

inline array_data < TYPE, ARG_TYPE, ALLOCATOR >  & array_data < TYPE, ARG_TYPE, ALLOCATOR > ::operator += (const array_data & a)
{

   if(&a == this)
   {
      array_data < TYPE, ARG_TYPE, ALLOCATOR >  aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array_data < TYPE, ARG_TYPE, ALLOCATOR >  array_data < TYPE, ARG_TYPE, ALLOCATOR > ::operator + (const array_data & a) const
{
   array_data < TYPE, ARG_TYPE, ALLOCATOR >  aNew(*this);
   aNew += a;
   return a;
}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//index array_data < TYPE, ARG_TYPE, ALLOCATOR > ::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
//{
//
//   return array_data < TYPE, ARG_TYPE, ALLOCATOR > ::insert_at(nIndex, newElement,nCount);
//
//}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_data < TYPE, ARG_TYPE, ALLOCATOR > ::add_new()
{
  this-> set_size(this->m_nSize + 1);
   return last();
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array_data < TYPE, ARG_TYPE, ALLOCATOR > ::add_new(::count count)
{
   this->set_size(this->m_nSize + count);
   return this->get_upper_bound();
}

//template < class TYPE, class ARG_TYPE, class ALLOCATOR >
//inline TYPE array_data < TYPE, ARG_TYPE, ALLOCATOR >::pop(index n)
//{
//
//   index i = this->get_upper_bound(n);
//
//   TYPE t = element_at(i);
//
//   this->remove_at(i);
//
//   return t;
//
//}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR >::pop_back(index n)
{

   remove_at(this->get_upper_bound(n));

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array_data < TYPE, ARG_TYPE, ALLOCATOR >::push(ARG_TYPE newElement,index n)
{
   return insert_at(this->get_upper_bound(n),newElement);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR >::push_back(ARG_TYPE newElement,index n)
{
   insert_at(this->get_upper_bound(n),newElement);
}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array_data < TYPE, ARG_TYPE, ALLOCATOR > ::set_at_grow(index nIndex, ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
      this->set_size(nIndex+1, -1);

   get_data()[nIndex] = newElement;

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array_data < TYPE, ARG_TYPE, ALLOCATOR > ::element_at_grow(index nIndex)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
      this->set_size(nIndex+1, -1);

   return get_data()[nIndex];

}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array_data < TYPE, ARG_TYPE, ALLOCATOR >::array_data(array_data && a) :
object(a.get_app())
{

	this->m_nGrowBy = a.m_nGrowBy;
	this->m_pData = a.m_pData;
	this->m_nSize = a.m_nSize;
	this->m_nMaxSize = a.m_nMaxSize;

	a.m_pData = NULL;
	a.m_nSize = 0;
	a.m_nMaxSize = 0;

}


template < class TYPE,class ARG_TYPE,class ALLOCATOR >
inline array_data < TYPE,ARG_TYPE,ALLOCATOR > & array_data < TYPE,ARG_TYPE,ALLOCATOR >::move(array_data && a)
{

   if(&a != this)
   {

      this->destroy();

      this->m_nGrowBy = a.m_nGrowBy;
      this->m_pData = a.m_pData;
      this->m_nSize = a.m_nSize;
      this->m_nMaxSize = a.m_nMaxSize;

      a.m_pData = NULL;
      a.m_nSize = 0;
      a.m_nMaxSize = 0;

   }

   return *this;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array_data < TYPE, ARG_TYPE, ALLOCATOR > & array_data < TYPE, ARG_TYPE, ALLOCATOR >::operator = (array_data && a)
{

   move(::move(a));

	return *this;

}


































//template < typename Type, typename RawType >
//Type string_array < Type, RawType >::get_at(index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
//
//template < typename Type, typename RawType >
//void string_array < Type, RawType >::set_at(index nIndex,const char * newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   get_data()[nIndex] = newElement;
//}
//
//
//template < typename Type, typename RawType >
//void string_array < Type, RawType >::set_at(index nIndex,const Type & newElement)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   get_data()[nIndex] = newElement;
//}
//
//
//template < typename Type, typename RawType >
//Type & string_array < Type, RawType >::element_at(index nIndex)
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//      throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}


//template < typename Type, typename RawType >
//const Type & string_array < Type, RawType >::element_at(index nIndex) const
//{
//   if (nIndex < 0 || nIndex >= this->m_nSize)
//     throw index_out_of_bounds(this->get_app());
//   return get_data()[nIndex];
//}
