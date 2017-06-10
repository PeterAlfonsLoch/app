#pragma once


#include "collection_string_iterable.h"


template < typename TYPE >
class string_array :
   public string_iterable < array < TYPE > >
{
public:


   typedef TYPE                           String;
   typedef array < TYPE >                 Iterable;


   string_array() {}
   string_array(::aura::application * papp);
   string_array(const TYPE & t) { add(t); }
   string_array(::std::initializer_list < TYPE > l) {   for(auto & e : l) {    add(e);    }  }
   string_array(const Iterable & array);
   template < typename ITERABLE2 >
   string_array(const ITERABLE2 & iterable2);
   virtual ~string_array();



   //::count get_size() const;
   //::count get_count() const;
   //index get_lower_bound(index i = 0) const;
   //index get_upper_bound(index i = -1) const;

   TYPE safe_at(index nIndex, TYPE tDefault = "") const;
   TYPE safe_at(index nIndex, TYPE tDefault = "");

   //TYPE get_at(index nIndex) const;
   //void set_at(index nIndex, const char * newElement);

   //void set_at(index nIndex, const TYPE & newElement);

   //TYPE & element_at(index nIndex);
   //const TYPE & element_at(index nIndex) const;

   TYPE & add_new(const char * psz = NULL, index i = -1);
   TYPE & new_element(index i = -1);

   //TYPE & first(index count = 0);
   //TYPE first(index count = 0) const;

   //TYPE & last(index count = -1);
   //TYPE last(index count = -1) const;

   //const TYPE* get_data() const;
   //TYPE* get_data();

   //TYPE & set_at_grow(index nIndex, const char * newElement);
   //TYPE & set_at_grow(index nIndex,const TYPE & newElement);


   //using array < TYPE >::add;

   //iterator add(const char * psz);

   //iterator add(const unichar * pwsz);

   //iterator add(char ch);

   //iterator add(unichar wch);

   //iterator add(const var & var);

   //iterator add(const property & prop);

   //iterator add(const id & id);

   //iterator add(const TYPE & newElement);

   //void push_back(const TYPE & newElement);

   //iterator add_iter(const Iterable & src);

   //void copy_iter(const Iterable & src);

   template < typename T1, typename T2 >
   void provision(T1 first, T2 last);


   //TYPE operator[](index nIndex) const;
   //TYPE & operator[](index nIndex);

   TYPE & insert_at(index nIndex,const TYPE & newElement);
   void insert_at(index nIndex,const char * newElement,::count nCount);
   void insert_at(index nIndex,const TYPE & newElement,::count nCount);
   void insert_at(index nStartIndex, const Iterable & iterable);


   TYPE & insert_empty(index nIndex);

   void insert_empty(index nIndex, ::count c);



   void dump(dump_context &) const;

   void assert_valid() const;

   //string_array & operator = (const string_array & a);


};

//template < typename TYPE >
//string_array < TYPE > & string_array < TYPE >::operator = (const string_array & a)
//{
//
//   if (this != &a)
//   {
//
//      ::iter::copy(*this, a);
//
//   }
//
//   return *this;
//
//}


//template < typename TYPE >
//inline TYPE & string_array < TYPE >::last(index i)
//{
//   
//   return this->element_at(get_upper_bound(i));
//
//}
//
//
//template < typename TYPE >
//inline TYPE string_array < TYPE >::last(index count) const
//{
//   
//   return this->element_at(get_upper_bound(count));
//
//}
//
//
//template < typename TYPE >
//inline TYPE & string_array < TYPE >::first(index i)
//{
//
//   return this->element_at(get_lower_bound(i));
//
//}
//
//
//template < typename TYPE >
//inline TYPE string_array < TYPE >::first(index count) const
//{
//   
//   return this->element_at(get_lower_bound(count));
//
//}


//template < typename TYPE >
//inline ::count string_array < TYPE >::get_size() const
//{
//   
//   return this->m_nSize; 
//
//}
//
//
//template < typename TYPE >
//inline ::count string_array < TYPE >::get_count() const
//{
//   
//   return this->m_nSize; 
//
//}
//
//
//template < typename TYPE >
//inline index string_array < TYPE >::get_lower_bound(index i) const
//{
//   
//   return i; 
//
//}
//
//
//template < typename TYPE >
//inline index string_array < TYPE >::get_upper_bound(index count) const
//{
//
//   return this->m_nSize + count; 
//
//}
template < typename TYPE >
string_array< TYPE>::string_array(const Iterable & array)
{
   ::iter::copy_iter(*this, array);

}
template < typename TYPE >
string_array < TYPE >::~string_array()
{

}


//template < typename TYPE >
//typename string_array < TYPE >::iterator string_array < TYPE >::add_iter(const Iterable & src)
//{
//   
//   if(this == &src)
//   {
//      
//      Iterable iterableDuplicate(src);
//   
//      return add_iter(iterableDuplicate);
//
//   }
//
//   ASSERT_VALID(this);
//   ASSERT(this != &src);   // cannot append to itself
//
//   ::count nOldSize = this->m_nSize;
//   this->set_size(this->m_nSize + src.m_nSize);
//
//   CopyElements(&this->m_pData[nOldSize],src.m_pData,src.m_nSize);
//
//   return &this->m_pData[m_nSize-1];
//}


//template < typename TYPE >
//void string_array < TYPE >::copy_iter(const Iterable & src)
//{
//
//   if(this == &src)
//      return;
//
//   ASSERT_VALID(this);
//
//   this->set_size(src.m_nSize);
//
//   CopyElements(this->m_pData,src.m_pData,src.m_nSize);
//
//}
//


//template < typename TYPE >
//TYPE & string_array < TYPE >::set_at_grow(index nIndex,const char * newElement)
//{
//
//   ASSERT_VALID(this);
//   ASSERT(nIndex >= 0);
//
//   if(nIndex >= this->m_nSize)
//      this->set_size(nIndex + 1);
//
//   return get_data()[nIndex] = newElement;
//
//}
//
//
//template < typename TYPE >
//TYPE & string_array < TYPE >::set_at_grow(index nIndex,const TYPE & newElement)
//{
//   ASSERT_VALID(this);
//   ASSERT(nIndex >= 0);
//
//   if(nIndex >= this->m_nSize)
//      this->set_size(nIndex + 1);
//
//   return get_data()[nIndex] = newElement;
//
//}


template < typename TYPE >
void string_array < TYPE >::insert_empty(index nIndex,::count nCount)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need
   ASSERT(nCount > 0);     // zero or negative size not allowed

   if(nIndex >= this->m_nSize)
   {
      // adding after the end of the array
      this->set_size(nIndex + nCount);  // grow so nIndex is valid
   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = this->m_nSize;
      this->set_size(this->m_nSize + nCount);  // grow it to new size
      // shift old data up to fill gap
      memmove(&get_data()[nIndex + nCount],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      for(index i = nIndex; i < nIndex + nCount; i++)
      {
         get_data()[i].construct();
      }

   }

   // insert new value in the gap
   ASSERT(nIndex + nCount <= this->m_nSize);
}

template < typename TYPE >
typename TYPE & string_array < TYPE >::insert_empty(index nIndex)
{
   ASSERT_VALID(this);
   ASSERT(nIndex >= 0);    // will expand to meet need

   if(nIndex >= this->m_nSize)
   {

      this->set_size(nIndex + 1);

   }
   else
   {
      // inserting in the middle of the array
      ::count nOldSize = this->m_nSize;
      this->set_size(this->m_nSize + 1);  // grow it to new size
      // shift old data up to fill gap
      memmove(&get_data()[nIndex + 1],&get_data()[nIndex],(nOldSize - nIndex) * sizeof(TYPE));

      // re-init slots we copied from
      for(index i = nIndex; i < nIndex + 1; i++)
      {
         get_data()[i].construct();
      }

   }

   // insert new value in the gap
   ASSERT(nIndex + 1 <= this->m_nSize);
   return get_data()[nIndex];
}



template < typename TYPE >
typename TYPE & string_array < TYPE >::insert_at(index nIndex,const TYPE & newElement)
{

   return insert_empty(nIndex) = newElement;

}


template < typename TYPE >
void string_array < TYPE >::insert_at(index nIndex,const char * newElement,::count nCount)
{

   // make room for new elements
   insert_empty(nIndex,nCount);



   // copy elements into the is_empty space
   TYPE temp = newElement;
   while(nCount--)
      get_data()[nIndex++] = temp;

}



template < typename TYPE >
void string_array < TYPE >::insert_at(index nIndex,const TYPE & newElement,::count nCount)
{
   // make room for new elements
   insert_empty(nIndex,nCount);

   // copy elements into the is_empty space
   while(nCount--)
      get_data()[nIndex++] = newElement;
}



template < typename TYPE >
void string_array < TYPE >::insert_at(index nStartIndex,const Iterable & iterable)
{
   
   ASSERT_VALID(this);
   ASSERT(&iterable != NULL);
   ASSERT_VALID(&iterable);
   ASSERT(nStartIndex >= 0);

   if(iterable.get_size() > 0)
   {
      
      insert_at(nStartIndex, iterable.get_at(0), iterable.get_size());

      for (int32_t i = 0; i < iterable.get_size(); i++)
      {

         set_at(nStartIndex + i, iterable.get_at(i));

      }

   }

}






template < typename TYPE >
void string_array < TYPE >::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << this->m_nSize << " elements";
   if(dumpcontext.GetDepth() > 0)
   {
      for(int32_t i = 0; i < this->m_nSize; i++)
         dumpcontext << "\n\t[" << i << "] = " << get_data()[i];
   }

   dumpcontext << "\n";
}


template < typename TYPE >
void string_array < TYPE >::assert_valid() const
{
   object::assert_valid();

   if(this->m_pData == NULL)
   {
      ASSERT(this->m_nSize == 0);
      ASSERT(this->m_nMaxSize == 0);
   }
   else
   {
      ASSERT(this->m_nSize >= 0);
      ASSERT(this->m_nMaxSize >= 0);
      ASSERT(this->m_nSize <= this->m_nMaxSize);
      ASSERT(__is_valid_address(this->m_pData,this->m_nMaxSize * sizeof(TYPE)));
   }
}



template < typename TYPE >
TYPE & string_array < TYPE >::add_new(const char * psz,index i)
{
   if(i == -1)
   {
      return *add(TYPE(psz));
   }
   else
   {
      return insert_at(i,TYPE(psz));

   }
}



template < typename TYPE >
TYPE & string_array < TYPE >::new_element(index i)
{
   add_new(NULL,i);
   if(i == -1)
   {
      return last();
   }
   else
   {
      return this->element_at(i);
   }
}






//template < typename TYPE >
//const TYPE* string_array < TYPE >::get_data() const
//{
//   return (const TYPE*)this->m_pData;
//}
//
//
//template < typename TYPE >
//TYPE* string_array < TYPE >::get_data()
//{
//   return (TYPE*)this->m_pData;
//}



//template < typename TYPE >
//inline TYPE string_array < TYPE >::operator[](index nIndex) const
//{
//   return get_data()[nIndex];
//}
//
//
//template < typename TYPE >
//inline TYPE & string_array < TYPE >::operator[](index nIndex)
//{
//   return get_data()[nIndex];
//}










//template <class ARRAYCOMPARE,class ARRAYRELATION>
//void SortEx(ARRAYCOMPARE * pacompare,
//   int32_t fCompare(const char *,const char *),
//   ARRAYRELATION * parelation)
//{
//   index_array stackLowerBound;
//   index_array stackUpperBound;
//   index iLowerBound;
//   index iUpperBound;
//   index iLPos,iUPos,iMPos;
//   string str;
//
//   if(pacompare->get_size() >= 2)
//   {
//      stackLowerBound.push(0);
//      stackUpperBound.push(pacompare->get_size() - 1);
//      while(true)
//      {
//         iLowerBound = stackLowerBound.pop();
//         iUpperBound = stackUpperBound.pop();
//         iLPos = iLowerBound;
//         iMPos = iLowerBound;
//         iUPos = iUpperBound;
//         while(true)
//         {
//            while(true)
//            {
//               if(iMPos == iUPos)
//                  break;
//               if(fCompare(pacompare->element_at(iMPos),pacompare->element_at(iUPos)) <= 0)
//                  iUPos--;
//               else
//               {
//                  pacompare->swap(iMPos,iUPos);
//                  parelation->swap(iMPos,iUPos);
//                  break;
//               }
//            }
//            if(iMPos == iUPos)
//               break;
//            iMPos = iUPos;
//            while(true)
//            {
//               if(iMPos == iLPos)
//                  break;
//               if(fCompare(pacompare->element_at(iLPos),pacompare->element_at(iMPos)) <= 0)
//                  iLPos++;
//               else
//               {
//                  pacompare->swap(iMPos,iLPos);
//                  parelation->swap(iMPos,iLPos);
//                  break;
//               }
//            }
//            if(iMPos == iLPos)
//               break;
//            iMPos = iLPos;
//         }
//         if(iLowerBound < iMPos - 1)
//         {
//            stackLowerBound.push(iLowerBound);
//            stackUpperBound.push(iMPos - 1);
//         }
//         if(iMPos + 1 < iUpperBound)
//         {
//            stackLowerBound.push(iMPos + 1);
//            stackUpperBound.push(iUpperBound);
//         }
//         if(stackLowerBound.get_size() == 0)
//            break;
//      }
//   }
//   //for(int32_t i = 0; i < pacompare->get_size(); i++)
//   //{
//   //      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
//   //}
//}
//
//template <class ARRAYCOMPARE,class ARRAYRELATION>
//void SortEx(ARRAYCOMPARE * pacompare,
//   int32_t fCompare(const unichar *,const unichar *),
//   ARRAYRELATION * parelation)
//{
//   index_array stackLowerBound;
//   index_array stackUpperBound;
//   index iLowerBound;
//   index iUpperBound;
//   index iLPos,iUPos,iMPos;
//   string str;
//
//   if(pacompare->get_size() >= 2)
//   {
//      stackLowerBound.push(0);
//      stackUpperBound.push(pacompare->get_size() - 1);
//      while(true)
//      {
//         iLowerBound = stackLowerBound.pop();
//         iUpperBound = stackUpperBound.pop();
//         iLPos = iLowerBound;
//         iMPos = iLowerBound;
//         iUPos = iUpperBound;
//         while(true)
//         {
//            while(true)
//            {
//               if(iMPos == iUPos)
//                  break;
//               if(fCompare(pacompare->element_at(iMPos),pacompare->element_at(iUPos)) <= 0)
//                  iUPos--;
//               else
//               {
//                  pacompare->swap(iMPos,iUPos);
//                  parelation->swap(iMPos,iUPos);
//                  break;
//               }
//            }
//            if(iMPos == iUPos)
//               break;
//            iMPos = iUPos;
//            while(true)
//            {
//               if(iMPos == iLPos)
//                  break;
//               if(fCompare(pacompare->element_at(iLPos),pacompare->element_at(iMPos)) <= 0)
//                  iLPos++;
//               else
//               {
//                  pacompare->swap(iMPos,iLPos);
//                  parelation->swap(iMPos,iLPos);
//                  break;
//               }
//            }
//            if(iMPos == iLPos)
//               break;
//            iMPos = iLPos;
//         }
//         if(iLowerBound < iMPos - 1)
//         {
//            stackLowerBound.push(iLowerBound);
//            stackUpperBound.push(iMPos - 1);
//         }
//         if(iMPos + 1 < iUpperBound)
//         {
//            stackLowerBound.push(iMPos + 1);
//            stackUpperBound.push(iUpperBound);
//         }
//         if(stackLowerBound.get_size() == 0)
//            break;
//      }
//   }
//   //for(int32_t i = 0; i < pacompare->get_size(); i++)
//   //{
//   //      TRACE("%d this->element_at(iPos) %s\n", i, this->element_at(i));
//   //}
//}


class string2a:
   public array < stringa >
{
public:


};


// return TYPE length or -1 if UNICODE TYPE is found in the archive
__STATIC UINT __read_string_length(::file::istream & ar);

template < typename TYPE >
string_array < TYPE > ::string_array(::aura::application * papp):
object(papp)
{
}


template < typename TYPE >
template < typename ITERABLE2 >
string_array < TYPE > ::string_array(const ITERABLE2 & iterable2) :
   ::object((const ::object &) iterable2)
{
   ::iter::copy_iter(*this, iterable2);
}

//template < typename TYPE >
//::file::ostream & operator << (::file::ostream & ostream, const string_array < TYPE > & a)
//{
//
//   ostream.write_arbitrary(a.m_nSize);
//
//   for(int32_t i = 0; i < a.get_size(); i++)
//   {
//
//      ostream << a.element_at(i);
//
//   }
//
//   return ostream;
//
//}
//
//
//template < typename TYPE >
//::file::istream & operator >> (::file::istream & istream, string_array < TYPE > & a)
//{
//
//   if(istream.fail())
//   {
//
//      return istream;
//
//   }
//
//   ::count iSize;
//
//   istream.read_arbitrary(iSize);
//
//   if(istream.fail())
//   {
//
//      return istream;
//
//   }
//
//   ::count cOldSize = a.get_size();
//
//   a.set_size(cOldSize + iSize);
//
//   ::count cNewSize = a.get_size();
//
//   for(int32_t i = cOldSize; i < cNewSize; i++)
//   {
//
//      istream >> a.element_at(i);
//
//      if(istream.fail())
//      {
//
//         return istream;
//
//      }
//
//   }
//
//   return istream;
//
//}
//



























template < typename TYPE >
template < typename T1, typename T2 >
void string_array < TYPE > ::provision(T1 first, T2 last)
{
   
   set_size(0, last - first);

}



