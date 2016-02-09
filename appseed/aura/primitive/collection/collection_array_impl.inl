#pragma once

//
// see collection_array_decl.h for declaration
//
// raw_array is an array that does not call constructors or destructor in elements
// array is an array that call only copy constructor and destructor in elements
// array is an array that call default constructors, copy constructs and destructors in elements

template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::get_size() const
{
   return m_nSize;
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::get_size_in_bytes() const
{
   return m_nSize * sizeof(TYPE);
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::get_count() const
{
   return this->get_size();
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::get_byte_count() const
{
   return this->get_size_in_bytes();
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::size() const
{
   return this->get_size();
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::count() const
{
   return this->get_count();
}


template < class TYPE, class ALLOCATOR >
inline bool array_base < TYPE, ALLOCATOR > ::is_empty(::count countMinimum) const
{
   return m_nSize < countMinimum;
}


template < class TYPE, class ALLOCATOR >
inline bool array_base < TYPE, ALLOCATOR > ::empty(::count countMinimum) const
{
   return is_empty(countMinimum);
}


template < class TYPE, class ALLOCATOR >
inline bool array_base < TYPE, ALLOCATOR > ::has_elements(::count countMinimum) const
{
   return m_nSize >= countMinimum;
}


template < class TYPE, class ALLOCATOR >
inline index array_base < TYPE, ALLOCATOR > ::get_upper_bound(index index) const
{
   return m_nSize + index;
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::remove_all()
{
   return allocate(0, -1);
}


template < class TYPE, class ALLOCATOR >
inline ::count array_base < TYPE, ALLOCATOR > ::set_size(index nNewSize, ::count nGrowBy) // does not call default constructors on new items/elements
{
   return allocate(nNewSize, nGrowBy);
}


template < class TYPE, class ALLOCATOR >
inline void array_base < TYPE, ALLOCATOR > ::clear()
{
   remove_all();
}


template < class TYPE, class ALLOCATOR >
inline void array_base < TYPE, ALLOCATOR > ::remove_last()
{
   ASSERT(m_nSize > 0);
   remove_at(get_upper_bound());
}


template < class TYPE,class ALLOCATOR >
inline void array_base < TYPE,ALLOCATOR > ::zero(index iStart,::count c)
{
   if(c < 0)
   {
      c = get_size() - iStart;
   }
   ::zero(&m_pData[iStart],c * sizeof(TYPE));
}


























template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(index nIndex)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::get_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::set_at(index nIndex, ARG_TYPE newElement)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   get_data()[nIndex] = newElement;
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(index nIndex) const
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::element_at(index nIndex)
{
   ASSERT(nIndex >= 0 && nIndex < this->m_nSize);
   return get_data()[nIndex];
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::first(index nIndex) const
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::first(index nIndex)
{
   return this->element_at(nIndex);
}
template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::last(index index) const
{
   return element_at(this->get_upper_bound(index));
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::last(index index)
{
   return element_at(this->get_upper_bound(index));
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE* array < TYPE, ARG_TYPE, ALLOCATOR > ::get_data() const
{
   return (const TYPE*)this->m_pData;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE* array < TYPE, ARG_TYPE, ALLOCATOR > ::get_data()
{
   return (TYPE*)this->m_pData;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array < TYPE, ARG_TYPE, ALLOCATOR > ::add(ARG_TYPE newElement)
{
   index nIndex = this->m_nSize;
   this->allocate(nIndex + 1);
   last() = newElement;
   return nIndex;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array < TYPE, ARG_TYPE, ALLOCATOR > ::add(const array & src)
{
   return append(src);
}






template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline const TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](index nIndex) const
{
   return element_at(nIndex);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE& array < TYPE, ARG_TYPE, ALLOCATOR > ::operator[](index nIndex)
{
   return this->element_at(nIndex);
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::swap(index index1, index index2)
{
   TYPE t = get_data()[index1];
   get_data()[index1] = get_data()[index2];
   get_data()[index2] = t;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator = (const array & src)
{
   if(&src != this)
   {
      copy(src);
   }
   return *this;
}



// out-of-line functions

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(::aura::application * papp, ::count nGrowBy) :
object(papp),
array_base < TYPE, ALLOCATOR >(papp,sizeof(TYPE),false)
{
//   this->m_nGrowBy = MAX(0, nGrowBy);
//   this->m_pData = NULL;
//   this->m_nSize = this->m_nMaxSize = 0;
}


template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::array(const array & a) :
object(a.get_app()),
array_base < TYPE, ALLOCATOR > (a.get_app(),sizeof(TYPE),false)
{
//   m_nGrowBy = 32;
//   m_pData = NULL;
//   m_nSize = m_nMaxSize = 0;
   operator = (a);
}


template < class TYPE,class ARG_TYPE,class ALLOCATOR >
inline array < TYPE,ARG_TYPE,ALLOCATOR > ::array(::std::initializer_list < TYPE >  l) :
array_base < TYPE,ALLOCATOR >(NULL,sizeof(TYPE),false)
{
   forallref(l)
   {
      add((ARG_TYPE) item);
   }
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > :: array(::count n) :
array_base < TYPE, ALLOCATOR >(sizeof(TYPE),false)
{
//   m_nGrowBy = 32;
//   m_pData = NULL;
//   m_nSize = m_nMaxSize = 0;
   this->allocate(n);
}





template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR > ::~array()
{
   this->remove_all(); // on_destruct_element is virtual and won't be available for array_base
}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array < TYPE, ARG_TYPE, ALLOCATOR > ::append(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this == &src)
      throw invalid_argument_exception(this->get_app());

   ::count nOldSize = this->m_nSize;
   this->allocate(this->m_nSize + src.m_nSize);
   CopyElements<TYPE>(&this->m_pData[nOldSize], src.m_pData, src.m_nSize);
   return nOldSize;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::copy(const array& src)
{
   ASSERT_VALID(this);
   ASSERT(this != &src);   // cannot append to itself

   if(this != &src)
   {
      this->allocate(src.m_nSize);
      CopyElements<TYPE>(this->m_pData,src.m_pData,src.m_nSize);
   }
}







template < class TYPE, class ARG_TYPE, class ALLOCATOR >
void array < TYPE, ARG_TYPE, ALLOCATOR > ::dump(dump_context & dumpcontext) const
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
void array < TYPE, ARG_TYPE, ALLOCATOR > ::assert_valid() const
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
inline typename array < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator pos)
{
   if(pos.m_parray == this)
   {
      this->remove_at(pos.m_i);
      return iterator(pos.m_i, this);
   }
   else
   {
      return end();
   }
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline typename  array < TYPE, ARG_TYPE, ALLOCATOR > ::iterator array < TYPE, ARG_TYPE, ALLOCATOR > ::erase(iterator begin, iterator last)
{
   if(begin.m_parray == this && last.m_parray == this)
   {
      if(begin.m_i >= 0 && begin.m_i < this->get_size())
      {
         ::count nCount = last.m_i - begin.m_i;
         remove_at(begin.m_i, nCount);
         return iterator(begin.m_i, this);
      }
      else
      {
         return end();
      }
   }
   else
   {
      return end();
   }
}





template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  & array < TYPE, ARG_TYPE, ALLOCATOR > ::operator += (const array & a)
{

   if(&a == this)
   {
      array < TYPE, ARG_TYPE, ALLOCATOR >  aCopy(a);
      add(aCopy);
   }
   else
   {
      add(a);
   }
   return *this;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline array < TYPE, ARG_TYPE, ALLOCATOR >  array < TYPE, ARG_TYPE, ALLOCATOR > ::operator + (const array & a) const
{
   array < TYPE, ARG_TYPE, ALLOCATOR >  aNew(*this);
   aNew += a;
   return a;
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
index array < TYPE, ARG_TYPE, ALLOCATOR > ::insert_at(index nIndex, ARG_TYPE newElement, ::count nCount /*=1*/)
{

   return array_base < TYPE, ALLOCATOR > ::insert_at(nIndex,&newElement,nCount);

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new()
{
  this-> set_size(this->m_nSize + 1);
   return last();
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array < TYPE, ARG_TYPE, ALLOCATOR > ::add_new(::count count)
{
   this->set_size(this->m_nSize + count);
   return this->get_upper_bound();
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE array < TYPE, ARG_TYPE, ALLOCATOR >::pop(index n)
{

   index i = this->get_upper_bound(n);

   TYPE t = element_at(i);

   this->remove_at(i);

   return t;

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR >::pop_back(index n)
{

   remove_at(this->get_upper_bound(n));

}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline index array < TYPE, ARG_TYPE, ALLOCATOR >::push(ARG_TYPE newElement,index n)
{
   return insert_at(this->get_upper_bound(n),newElement);
}

template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR >::push_back(ARG_TYPE newElement,index n)
{
   insert_at(this->get_upper_bound(n),newElement);
}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline void array < TYPE, ARG_TYPE, ALLOCATOR > ::set_at_grow(index nIndex, ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
      this->set_size(nIndex+1, -1);

   get_data()[nIndex] = newElement;

}



template < class TYPE, class ARG_TYPE, class ALLOCATOR >
inline TYPE & array < TYPE, ARG_TYPE, ALLOCATOR > ::element_at_grow(index nIndex)
{

   ASSERT_VALID(this);

   ASSERT(nIndex >= 0);

   if (nIndex >= this->m_nSize)
      this->set_size(nIndex+1, -1);

   return get_data()[nIndex];

}




template < class TYPE, class ARG_TYPE, class ALLOCATOR >
array < TYPE, ARG_TYPE, ALLOCATOR >::array(array && a) :
object(a.get_app()),
array_base < TYPE, ALLOCATOR >(a.get_app(), sizeof(TYPE), false)
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
inline array < TYPE,ARG_TYPE,ALLOCATOR > & array < TYPE,ARG_TYPE,ALLOCATOR >::move(array && a)
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
inline array < TYPE, ARG_TYPE, ALLOCATOR > & array < TYPE, ARG_TYPE, ALLOCATOR >::operator = (array && a)
{

   move(::move(a));

	return *this;

}
















