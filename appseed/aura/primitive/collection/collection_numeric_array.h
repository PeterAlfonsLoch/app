#pragma once


template < typename T >
index numeric_compare(T * p1, T * p2)
{
   T t = *p1 - *p2;
   if(t > ::numeric_info< T >::null())
      return 1;
   else if(t < ::numeric_info < T >::null())
      return -1;
   else
      return 0;
}

namespace str
{


   template < >
   inline int64_t from_string(const char * psz)
   {
      return to_int64(string(psz));
   }

} // namespace ::core::str


template < typename TYPE >
class numeric_array :
   virtual public ::file::serializable_array < typename comparable_primitive_array < TYPE >::type::type >
{
public:

   numeric_array();
   numeric_array(::count cSize);
   numeric_array(sp(::aura::application) papp);
   numeric_array(const numeric_array & array);
#ifdef MOVE_SEMANTICS
   numeric_array(numeric_array && array);
#endif

   index find_first_maximum_value();
   TYPE & get_maximum_value();

   ::count append_sequence(TYPE start, TYPE end, TYPE increment = 1);
   ::count set_sequence(TYPE start, TYPE end, TYPE increment = 1);
   ::count ensure_sequence(TYPE start, TYPE end, TYPE increment = 1);

   ::count remove_greater_than(TYPE hi);
   ::count remove_greater_than_or_equal(TYPE hi);
   ::count remove_lesser_than(TYPE lo);
   ::count remove_lesser_than_or_equal(TYPE lo);

   ::count remove_lesser_than_or_greater_than(TYPE lo, TYPE hi);
   ::count remove_lesser_than_or_greater_than_or_equal(TYPE lo, TYPE hi);
   ::count remove_lesser_than_or_equal_or_greater_than(TYPE lo, TYPE hi);
   ::count remove_lesser_than_or_equal_or_greater_than_or_equal(TYPE lo, TYPE hi);


   void push_last();


   TYPE pop_max();
   TYPE pop_max_last_add_up(TYPE tLastAddUp);


   TYPE pop_to();


   void CopySorted(const numeric_array < TYPE > & array, TYPE & tOffset, TYPE & tMin);

   void Diff(
      const numeric_array  < TYPE > & array1,
      const numeric_array  < TYPE > & array2);

   void divide(TYPE i);

   void ElementDiff(
      const numeric_array  < TYPE > & array1,
      TYPE & tMax);

   TYPE GetMean();

   void set(const TYPE & t, index iStart = 0, index iEnd = -1);

   index Cmp(const numeric_array  < TYPE > & array1);


   numeric_array unique() const;
   void unique();


   void quick_sort(bool bAsc = true);

   bool sort_type(TYPE t, index & iIndex, index iStart, index iEnd) const
   {
      if(this->get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      typename ::numeric_info < TYPE >::OFFSET_TYPE iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while(iUpperBound - iLowerBound >= 8)
      {
         iCompare = this->element_at(iIndex) - t;
         if(iCompare == ::numeric_info < TYPE > ::get_null_value())
         {
            return true;
         }
         else if(iCompare > (typename ::numeric_info < TYPE >::OFFSET_TYPE) ::numeric_info < TYPE > ::get_null_value())
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while(iIndex < this->get_count())
      {
         iCompare = this->element_at(iIndex) - t;
         if(iCompare == ::numeric_info::get_null_value < TYPE > ())
            return true;
         else if(iCompare < (typename ::numeric_info < TYPE >::OFFSET_TYPE) ::numeric_info < TYPE >::get_null_value ())
            iIndex++;
         else
            break;
      }
      if(iIndex >= this->get_count())
         return false;
      while(iIndex >= 0)
      {
         iCompare = this->element_at(iIndex) - t;
         if(iCompare == ::numeric_info::get_null_value < TYPE > ())
            return true;
         else if(iCompare > (typename ::numeric_info::offset < TYPE >::TYPE) ::numeric_info::get_null_value < TYPE > ())
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }


#if defined(MOVE_SEMANTICS)
      inline numeric_array & operator = (numeric_array && a);
#endif

   void implode(string & rwstr, const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;
   string implode(const char * lpcszSeparator = NULL, index iStart = 0, ::count iCount = -1) const;


   string surround_and_implode(const char * lpcszSeparator = NULL, const char * pszPrefix = NULL, const char * pszSuffix = NULL, index iStart = 0, ::count iCount = -1);


   numeric_array operator - (const numeric_array & a) const;
   numeric_array operator + (const numeric_array & a) const;

   numeric_array & operator = (const numeric_array & a);
   numeric_array & operator -= (const numeric_array & a);
   numeric_array & operator += (const numeric_array & a);


   string get_json();


};

template < class TYPE >
class unique_number_sort_array :
   public numeric_array < TYPE >
{
public:
   unique_number_sort_array(sp(::aura::application) papp = NULL);
   unique_number_sort_array(const unique_number_sort_array & array);

   index add(const TYPE & newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         this->insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, index & find) const
   {
      index iL = find;
      index iU = this->get_upper_bound();
      while(iU - iL > 5)
      {
         find = (iL + iU) / 2;
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == numeric_info::get_null_value  < TYPE >())
         {
            return true;
         }
         else if(tCmp > numeric_info::get_null_value  < TYPE >())
         {
            iL = find + 1;
         }
         else
         {
            iU = find - 1;
         }
      }
      for(; find < this->get_size(); find++)
      {
         TYPE tCmp = t - this->element_at(find);
         if(tCmp == numeric_info::get_null_value  < TYPE >())
         {
            return true;
         }
         else if(tCmp < numeric_info::get_null_value  < TYPE >())
         {
            return false;
         }
      }
      return false;
   }

   /*index find_first_maximum_value();
   TYPE & get_maximum_value();

   void CopySorted(
   const numeric_array  < TYPE > & array, // this array is sorted
   TYPE & tOffset,
   TYPE & tMin);

   void Diff(
   const numeric_array  < TYPE > & array1,
   const numeric_array  < TYPE > & array2);*/

   //void divide(int32_t i);

   //void ElementDiff(
   // const numeric_array  < TYPE > & array1,
   //TYPE & tMax);

   //TYPE GetMean();

   //void set(const TYPE & t, int32_t iStart = 0, int32_t iEnd = -1);

   //int32_t Cmp(const numeric_array  < TYPE > & array1);


   /*virtual void quick_sort(bool bAsc = true)
   {
   if(bAsc)
   {
   sort::QuickSortAsc(*this);
   }
   else
   {
   sort::QuickSortDesc(*this);
   }
   }*/


};

template < class TYPE >
numeric_array < TYPE >::
   numeric_array()
{
}

template < class TYPE >
numeric_array < TYPE >::
numeric_array(::count cSize)
{
   this->set_size(cSize);
}

template < class TYPE >
numeric_array < TYPE >::
   numeric_array(sp(::aura::application) papp) :
   element(papp)
{
}

template < class TYPE >
numeric_array < TYPE >::
   numeric_array(const numeric_array < TYPE > & a)
{
   this->operator = (a);
}

#ifdef MOVE_SEMANTICS
template < class TYPE >
numeric_array < TYPE >::
numeric_array(numeric_array < TYPE > && a)
: raw_array < TYPE,const TYPE & >((raw_array < TYPE,const TYPE & > &&) a)
{

}
#endif

template < typename T >
string to_json(const T & t);


template < class TYPE >
string numeric_array < TYPE >::get_json()
{


   string str("[");

   for (index i = 1; i < this->get_count(); i++)
   {
      if (i > 0)
      {
         str += ", \r\n";
      }

      str += to_json(this->element_at(i));

   }


   str += "\r\n]";

   return str;

}


template < class TYPE >
void numeric_array < TYPE >::implode(string & str, const char * lpcszSeparator, index start, ::count count) const
{
   if(start < 0)
   {
      start += this->get_size();
   }
   index last;
   if(count < 0)
   {
      last = this->get_size() + count;
   }
   else
   {
      last = start + count - 1;
   }
   if(start <= last)
   {
      string strSeparator(lpcszSeparator);
      index i = start;
      str = ::str::from(this->element_at(i));
      i++;
      for(; i <= last; i++)
      {
         str += strSeparator + ::str::from(this->element_at(i));
      }
   }
   else
   {
      str.Empty();
   }
}

template < class TYPE >
string numeric_array < TYPE >::implode(const char * lpcszSeparator, index iStart, index iEnd) const
{
   string str;
   implode(str, lpcszSeparator, iStart, iEnd);
   return str;
}


template < class TYPE >
string numeric_array < TYPE >::surround_and_implode(const char * pszSeparator, const char * pszPrefix, const char * pszSuffix, index iStart, ::count iCount)
{
   string str;
   string strSeparator(pszSeparator);
   string strPrefix(pszPrefix);
   string strSuffix(pszSuffix);
   index iEnd;
   if(iStart < 0)
      iStart = this->get_size() + iStart;
   if(iCount < 0)
      iEnd = this->get_size() + iCount;
   else
      iEnd = iStart + iCount - 1;
   if(iStart <= iEnd)
   {
      index i = iStart;
      str = strPrefix + ::str::from(this->element_at(i)) + strSuffix;
      i++;
      for(; i <= iEnd; i++)
      {
         str += strSeparator + strPrefix + ::str::from(this->element_at(i)) + strSuffix;
      }
   }
   return str;
}


template < class TYPE >
numeric_array < TYPE > numeric_array < TYPE >::unique() const
{

   numeric_array < TYPE > a;

   for(int32_t i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   return a;

}

template < class TYPE >
void numeric_array < TYPE >::unique()
{

   numeric_array < TYPE > a;

   for(int32_t i = 0; i < this->get_count(); i++)
   {
      a.add_unique(this->element_at(i));
   }

   *this = a;

}


template < class TYPE >
::count numeric_array < TYPE >::append_sequence(TYPE iterator, TYPE end, TYPE increment)
{
   if(increment == 0)
   {
      this->add(iterator);
      this->add(end);
      return 2;
   }
   else if(increment > 0)
   {
      ::count ca = 0;
      for(; iterator <= end; iterator +=increment)
      {
         this->add(iterator);
         ca++;
      }
      return ca;
   }
   else
   {
      ::count ca = 0;
      for(; iterator >= end; iterator +=increment)
      {
         this->add(iterator);
         ca++;
      }
      return ca;
   }
}

template < class TYPE >
::count numeric_array < TYPE >::
   set_sequence(TYPE start, TYPE end, TYPE increment)
{
   this->remove_all();
   return this->append_sequence(start, end, increment);
}


template < class TYPE >
index numeric_array < TYPE >::
   Cmp(const numeric_array  < TYPE > & array1)
{
   ::count iMinSize = MIN(array1.get_size(), this->get_size());
   index i = 0;
   while(true)
   {
      if(i >= iMinSize)
      {
         return this->get_size() - array1.get_size();
      }
      if(this->element_at(i) > array1.element_at(i))
         return 1;
      else if(this->element_at(i) < array1.element_at(i))
         return -1;
      i++;
   }
}

template < class TYPE >
void numeric_array < TYPE >::CopySorted(
   const numeric_array  < TYPE > & a,
   TYPE & tOffset,
   TYPE & tMin)
{
   index i;
   TYPE tStart = tMin - tOffset;
   this->allocate(a.get_size());
   TYPE t;
   for(i = 0; i < a.get_size()
      && a.get_at(i) <= tStart; i++)
   {
      this->set_at(i, tMin);
   }
   for(; i < a.get_size(); i++)
   {
      t = a.get_at(i) + tOffset;
      this->set_at(i, t);
   }
}
template < class TYPE >
void numeric_array < TYPE >::Diff(
   const numeric_array  < TYPE > & array1,
   const numeric_array  < TYPE > & array2)
{
   ASSERT(array1.get_size() == array2.get_size());
   index i;
   this->allocate(array1.get_size());
   TYPE t;
   for(i = 0; i < array1.get_size(); i++)
   {
      t = array1.get_at(i) - array2.get_at(i);
      this->set_at(i, t);
   }
}

template < class TYPE >
void numeric_array < TYPE >::ElementDiff(
   const numeric_array  < TYPE > & a,
   TYPE & tMax)
{
   index i;
   TYPE t;
   TYPE it;
   this->allocate(a.get_size());
   if(a.get_size() > 0)
   {
      TYPE tLast = a[0];
      for(i = 1; i < a.get_size(); i++)
      {
         t = a[i];
         it =  t - tLast;
         this->set_at(i - 1, it);
         tLast = t;
      }
      it =  tMax - tLast;
      this->set_at(i - 1, it);
   }
}

template < class TYPE >
index numeric_array < TYPE >::find_first_maximum_value()
{
   TYPE tMax = this->element_at(0);
   for(index i = 1; i < this->get_size(); i++)
   {
      if(this->element_at(i) > tMax)
         return i;
   }
   return -1;
}
template < class TYPE >
TYPE & numeric_array < TYPE >::
   get_maximum_value()
{
   ASSERT(this->get_size() > 0);
   return this->element_at(find_first_maximum_value());
}

template < class TYPE >
TYPE numeric_array < TYPE >::GetMean()
{
   double dSum = 0.0;
   for(index i = 0; i < this->get_size(); i++)
   {
      dSum += this->element_at(i);
   }
   return (typename ::numeric_info < TYPE >::TYPE) (dSum / (double) this->get_size());
}

template < class TYPE >
void numeric_array < TYPE >::set(const TYPE & t, index iStart, index iEnd)
{
   if(iEnd == -1)
      iEnd = this->get_upper_bound();
   for(index i = iStart; i <= iEnd; i++)
   {
      this->set_at(i, t);
   }
}


template < class TYPE >
void numeric_array < TYPE >::divide(TYPE div)
{
   index i;
   for(i = 0; i < this->get_size(); i++)
   {
      this->element_at(i) = this->element_at(i) / div;
   }
}

template < class TYPE >
numeric_array < TYPE >  numeric_array < TYPE >::operator - (const numeric_array < TYPE > & a) const
{

   numeric_array < TYPE > aRet(*this);

   aRet.remove(a);

   return *this;

}

template < class TYPE >
numeric_array < TYPE >  numeric_array < TYPE >::operator + (const numeric_array < TYPE >  & a) const
{

   numeric_array < TYPE > aRet(*this);

   aRet.add(a);

   return aRet;

}

template < class TYPE >
numeric_array < TYPE >  & numeric_array < TYPE >::operator = (const numeric_array < TYPE >  & a)
{

   raw_array < TYPE, const TYPE & >::copy(a);

   return *this;

}


template < class TYPE >
numeric_array < TYPE >  & numeric_array < TYPE >::operator -= (const numeric_array < TYPE >  & a)
{

   remove(a);

   return *this;

}

template < class TYPE >
numeric_array < TYPE >  & numeric_array < TYPE >::operator += (const numeric_array < TYPE >  & a)
{

   add(a);

   return *this;

}



template < class TYPE >
inline void numeric_array < TYPE > ::push_last()
{

   this->add(this->last_element());

}


template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_max()
{

   TYPE lastelement = this->last_element();

   TYPE nowpop = this->pop();

   this->last_element() = MAX(nowpop, lastelement);

   return this->last_element();

}



template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_max_last_add_up(TYPE tLastAddUp)
{

   TYPE lastelement = this->last_element();

   TYPE nowpop = this->pop();

   this->last_element() = MAX(nowpop, lastelement + tLastAddUp);

   return this->last_element();

}



template < class TYPE >
inline TYPE numeric_array < TYPE > ::pop_to()
{

   TYPE lastelement = this->pop();

   this->last_element() = lastelement;

   return this->last_element();

}



template < class TYPE >
unique_number_sort_array < TYPE >::
   unique_number_sort_array(sp(::aura::application) papp) :
   element(papp)
{
}

template < class TYPE >
unique_number_sort_array < TYPE >::
   unique_number_sort_array(const unique_number_sort_array < TYPE > & a) :
   element(a.get_app())
{
   numeric_array < TYPE > ::operator = (a);
}






































typedef CLASS_DECL_AURA numeric_array < index > index_array;
typedef CLASS_DECL_AURA numeric_array < count > count_array;
typedef CLASS_DECL_AURA numeric_array < int32_t > int_array;
typedef CLASS_DECL_AURA numeric_array < int64_t > int64_array;
typedef CLASS_DECL_AURA numeric_array < uint64_t > uint64_array;
typedef CLASS_DECL_AURA numeric_array < float > float_array;
typedef CLASS_DECL_AURA numeric_array < double > double_array;
typedef CLASS_DECL_AURA numeric_array < byte > byte_array;
typedef CLASS_DECL_AURA numeric_array < uint16_t > uint16_array;
typedef CLASS_DECL_AURA numeric_array < uint32_t > uint_array;
typedef CLASS_DECL_AURA numeric_array < uint_ptr > uint_ptr_array;




typedef CLASS_DECL_AURA unique_number_sort_array < int32_t > unique_int_sort_array;
typedef CLASS_DECL_AURA unique_number_sort_array < index > unique_index_sort_array;














































// take in ac::count that _001RemoveIndexes change
// the index array by sorting it and returning
// only the indexes that could be removed
// without indexes duplicates
template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::_001RemoveIndexes( /* [in, out] */ index_array & ia /* [in, out] */ )
{

   // sort
   ia.quick_sort(true);

   index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while(i >= 0 && ia[i] >= get_size())
   {

      ia.remove_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while(ia.get_size() > 0 && ia[0] < 0)
   {

      ia.remove_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while(i > 0 && ia[i] >= get_size())
   {

      if(ia[i] == ia[i - 1])
         ia.remove_at(i);

      i--;

   }

   remove_indexes(ia);

}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::remove_indexes(const index_array & ia)
{


   // remove indexes
   for(index i = ia.get_upper_bound(); i >= 0; i--)
   {

      remove_at(ia[i]);

   }

}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
inline void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::remove_descending_indexes(const index_array & ia)
{

   for(index i = 0; i < ia.get_count(); i++)
   {

      remove_at(ia[i]);

   }

}


// take in ac::count that _001RemoveIndexes change
// the index raw_array by sorting it and returning
// only the indexes that could be removed
// without indexes duplicates
template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::_001RemoveIndexes( /* [in, out] */ index_array & ia /* [in, out] */ )
{

   // sort
   ia.quick_sort(true);

   index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while(i >= 0 && ia[i] >= get_size())
   {

      ia.remove_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while(ia.get_size() > 0 && ia[0] < 0)
   {

      ia.remove_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while(i > 0 && ia[i] >= get_size())
   {

      if(ia[i] == ia[i - 1])
         ia.remove_at(i);

      i--;

   }

   remove_indexes(ia);

}



template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::remove_indexes(const index_array & ia)
{


   // remove indexes
   for(index i = ia.get_upper_bound(); i >= 0; i--)
   {

      remove_at(ia[i]);

   }

}


template<class TYPE, class ARG_TYPE>
inline void raw_array<TYPE, ARG_TYPE>::remove_descending_indexes(const index_array & ia)
{

   for(index i = 0; i < ia.get_count(); i++)
   {

      remove_at(ia[i]);

   }

}




template < class TYPE >
::count numeric_array < TYPE >::remove_greater_than(TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) > hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_greater_than_or_equal(TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) >= hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than(TYPE lo)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) < lo)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than_or_equal(TYPE lo)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) <= lo)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than_or_greater_than(TYPE lo, TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) < lo)
      {
         this->remove_at(i);
         ca++;
      }
      else if(this->element_at(i) > hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than_or_greater_than_or_equal(TYPE lo, TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) < lo)
      {
         this->remove_at(i);
         ca++;
      }
      else if(this->element_at(i) >= hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than_or_equal_or_greater_than(TYPE lo, TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) <= lo)
      {
         this->remove_at(i);
         ca++;
      }
      else if(this->element_at(i) > hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}


template < class TYPE >
::count numeric_array < TYPE >::remove_lesser_than_or_equal_or_greater_than_or_equal(TYPE lo, TYPE hi)
{

   ::count ca = 0;

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      if(this->element_at(i) <= lo)
      {
         this->remove_at(i);
         ca++;
      }
      else if(this->element_at(i) >= hi)
      {
         this->remove_at(i);
         ca++;
      }
   }

   return ca;

}

template < class TYPE >
::count numeric_array < TYPE >::ensure_sequence(TYPE start, TYPE end, TYPE increment)
{

   ::count ca = 0;

   numeric_array < TYPE > a;

   a.set_sequence(start, end, increment);

   ca += this->remove_lesser_than_or_greater_than(start, end);

   for(index i = this->get_upper_bound(); i >= 0; i--)
   {
      index iFind = 0;
      if(a.binary_search(this->element_at(i), iFind, &::numeric_compare < TYPE >))
      {
         a.remove_at(iFind);
         ca++;
      }
      else
      {
         this->remove_at(i);
         ca++;
      }
   }

   ca += this->add(a);

   return ca;

}


template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  fSwap(&element_at(iMPos), &element_at(iUPos));
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&this->element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  fSwap(&element_at(iLPos), &element_at(iMPos));
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::quick_sort(index (* fCompare)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
void array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia)
{

   // minimum check
   if(ia.get_size() != get_size())
      throw invalid_argument_exception(get_app());

   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(ia[iMPos]), &element_at(ia[iUPos])) <= 0)
                  iUPos--;
               else
               {
                  ia.swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(ia[iLPos]), &element_at(ia[iMPos])) <= 0)
                  iLPos++;
               else
               {
                  ia.swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}



template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
bool array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const
{
   if(this->get_size() == 0)
   {
      return false;
   }

   index iLowerBound = 0;
   index iMaxBound   = get_upper_bound();
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < this->get_count())
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= this->get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *)  &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
index array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::
sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{

   return ::lemon::array::sort_add(*this, t, fCompare, ia);

}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::
sort_add(const array  < TYPE, ARG_TYPE> & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   for(index i = 0; i < a.get_size(); i++)
   {
      sort_add((ARG_TYPE) a[i], fCompare, ia);
   }
   return a.get_size();
}

template < class TYPE, class ARG_TYPE, class DEFCONSTRUCTOR >
::count array < TYPE, ARG_TYPE, DEFCONSTRUCTOR > ::
sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   ::count ca = 0;
   index iFind = 0;
   while(binary_search(t, iFind, fCompare, ia))
   {
      remove_at(iFind);
      index iIndex = ia[iFind];
      ia.remove_at(iFind);
      for(index i = 0; i < ia.get_size(); i++)
      {
         if(ia[i] > iIndex)
         {
            ia[i]--;
         }
      }
      iFind = 0;
      ca++;
   }
   return ca;
}





template <class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), void (* fSwap)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  fSwap(&element_at(iMPos), &element_at(iUPos));
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  fSwap(&element_at(iLPos), &element_at(iMPos));
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template <class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *))
{
   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(iMPos), &element_at(iUPos)) <= 0)
                  iUPos--;
               else
               {
                  swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(iLPos), &element_at(iMPos)) <= 0)
                  iLPos++;
               else
               {
                  swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template <class TYPE, class ARG_TYPE>
void raw_array<TYPE, ARG_TYPE>::quick_sort(index (* fCompare)(TYPE *, TYPE *), index_array & ia)
{

   // minimum check
   if(ia.get_size() != get_size())
      throw invalid_argument_exception(get_app());

   index_array stackLowerBound;
   index_array stackUpperBound;
   index iLowerBound;
   index iUpperBound;
   index iLPos, iUPos, iMPos;
   //   uint32_t t;

   if(get_size() >= 2)
   {
      stackLowerBound.push(0);
      stackUpperBound.push(get_upper_bound());
      while(true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while(true)
         {
            while(true)
            {
               if(iMPos == iUPos)
                  break;
               if(fCompare(&element_at(ia[iMPos]), &element_at(ia[iUPos])) <= 0)
                  iUPos--;
               else
               {
                  ia.swap(iMPos, iUPos);
                  break;
               }
            }
            if(iMPos == iUPos)
               break;
            iMPos = iUPos;
            while(true)
            {
               if(iMPos == iLPos)
                  break;
               if(fCompare(&element_at(ia[iLPos]), &element_at(ia[iMPos])) <= 0)
                  iLPos++;
               else
               {
                  ia.swap(iLPos, iMPos);
                  break;
               }
            }
            if(iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if(iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if(iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if(stackLowerBound.get_size() == 0)
            break;
      }
   }

}

template < class TYPE, class ARG_TYPE >
bool raw_array < TYPE, ARG_TYPE > ::
binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *)) const
{
   if(this->get_size() == 0)
   {
      return false;
   }

   index iLowerBound = 0;
   index iMaxBound   = get_upper_bound();
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *) &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < this->get_count())
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *) &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= this->get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[iIndex], (TYPE *)  &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}


template < class TYPE, class ARG_TYPE >
bool raw_array < TYPE, ARG_TYPE > ::
binary_search(ARG_TYPE t, index & iIndex, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia) const
{
   if(this->get_size() == 0)
   {
      return false;
   }

   index iLowerBound = 0;
   index iMaxBound   = get_upper_bound();
   index iUpperBound = iMaxBound;
   index iCompare;
   // do binary search
   iIndex = (iUpperBound + iLowerBound) / 2;
   while(iUpperBound - iLowerBound >= 8)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
      {
         return true;
      }
      else if(iCompare > 0)
      {
         iUpperBound = iIndex - 1;
         if(iUpperBound < 0)
         {
            iIndex = 0;
            break;
         }
      }
      else
      {
         iLowerBound = iIndex + 1;
         if(iLowerBound > iMaxBound)
         {
            iIndex = iMaxBound + 1;
            break;
         }
      }
      iIndex = (iUpperBound + iLowerBound) / 2;
   }
   // do sequential search
   while(iIndex < this->get_count())
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *) &t);
      if(iCompare == 0)
         return true;
      else if(iCompare < 0)
         iIndex++;
      else
         break;
   }
   if(iIndex >= this->get_count())
      return false;
   while(iIndex >= 0)
   {
      iCompare = fCompare((TYPE *) &this->m_pData[ia[iIndex]], (TYPE *)  &t);
      if(iCompare == 0)
         return true;
      else if(iCompare > 0)
         iIndex--;
      else
         break;
   }
   iIndex++;
   return false;

}

template < class TYPE, class ARG_TYPE >
index raw_array < TYPE, ARG_TYPE > ::
sort_add(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   index iIndex = 0;
   binary_search(t, iIndex, fCompare, ia);
   this->insert_at(iIndex, t);
   ia.add(iIndex);
   return iIndex;
}

template < class TYPE, class ARG_TYPE >
::count raw_array < TYPE, ARG_TYPE> ::
sort_add(const raw_array  < TYPE, ARG_TYPE> & a, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   for(index i = 0; i < a.get_size(); i++)
   {
      sort_add((ARG_TYPE) a[i], fCompare, ia);
   }
   return a.get_size();
}

template < class TYPE, class ARG_TYPE >
::count raw_array < TYPE, ARG_TYPE > ::
sort_remove(ARG_TYPE t, index ( * fCompare ) (TYPE *, TYPE *), index_array & ia)
{
   ::count ca = 0;
   index iFind = 0;
   while(binary_search(t, iFind, fCompare, ia))
   {
      remove_at(iFind);
      index iIndex = ia[iFind];
      ia.remove_at(iFind);
      for(index i = 0; i < ia.get_size(); i++)
      {
         if(ia[i] > iIndex)
         {
            ia[i]--;
         }
      }
      iFind = 0;
      ca++;
   }
   return ca;
}


namespace lemon
{

   namespace numeric_array
   {

      template < class ARRAY >
      typename ARRAY::BASE_TYPE big_average(const ARRAY & a)
      {
         ::count c = a.get_count();
         if(c == 0)
            return 0.0;
         typename ARRAY::BASE_TYPE f = 0.0;
         typename ARRAY::BASE_TYPE fCount = (typename ARRAY::BASE_TYPE) c;
         for(index i = 0; i < c; i++)
         {
            f += a.element_at(i) / fCount;
         }
         return f;
      }

   } // namespace numeric_array

} // namespace lemon




namespace lemon
{

   namespace array
   {

      template<class ARRAY>
      bool binary_search(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index & iIndex, index ( * fCompare ) (typename ARRAY::BASE_TYPE *, typename ARRAY::BASE_TYPE *), index_array & ia)
      {
         if(a.get_size() == 0)
         {
            return false;
         }

         index iLowerBound = 0;
         index iMaxBound   = a.get_upper_bound();
         index iUpperBound = iMaxBound;
         index iCompare;
         // do binary search
         iIndex = (iUpperBound + iLowerBound) / 2;
         while(iUpperBound - iLowerBound >= 8)
         {
            iCompare = fCompare((typename ARRAY::BASE_TYPE *) &a.m_pData[ia[iIndex]], (typename ARRAY::BASE_TYPE *) &t);
            if(iCompare == 0)
            {
               return true;
            }
            else if(iCompare > 0)
            {
               iUpperBound = iIndex - 1;
               if(iUpperBound < 0)
               {
                  iIndex = 0;
                  break;
               }
            }
            else
            {
               iLowerBound = iIndex + 1;
               if(iLowerBound > iMaxBound)
               {
                  iIndex = iMaxBound + 1;
                  break;
               }
            }
            iIndex = (iUpperBound + iLowerBound) / 2;
         }
         // do sequential search
         while(iIndex < a.get_count())
         {
            iCompare = fCompare((typename ARRAY::BASE_TYPE *) &a.m_pData[ia[iIndex]], (typename ARRAY::BASE_TYPE *) &t);
            if(iCompare == 0)
               return true;
            else if(iCompare < 0)
               iIndex++;
            else
               break;
         }
         if(iIndex >= a.get_count())
            return false;
         while(iIndex >= 0)
         {
            iCompare = fCompare((typename ARRAY::BASE_TYPE *) &a.m_pData[ia[iIndex]], (typename ARRAY::BASE_TYPE *)  &t);
            if(iCompare == 0)
               return true;
            else if(iCompare > 0)
               iIndex--;
            else
               break;
         }
         iIndex++;
         return false;

      }


      template<class ARRAY>
      index sort_add(ARRAY & a, typename ARRAY::BASE_ARG_TYPE t, index ( * fCompare ) (typename ARRAY::BASE_TYPE *, typename ARRAY::BASE_TYPE *), index_array & ia)
      {
         index iIndex = 0;
         binary_search(a, t, iIndex, fCompare, ia);
         a.insert_at(iIndex, t);
         ia.add(iIndex);
         return iIndex;
      }



   } // namespace array


} // namespace lemon



#ifdef MOVE_SEMANTICS
template <class TYPE>
inline numeric_array<TYPE> & numeric_array<TYPE>::operator = (numeric_array && a)
{

   raw_array < TYPE,const TYPE & >::operator = (a);

   return *this;

}

#endif
