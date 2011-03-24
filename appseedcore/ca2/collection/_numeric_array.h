#pragma once

#include "_comparable_primitive_array.h"
#include "primitive/numeric_info.h"
#include "primitive/types.h"


template < class TYPE >
class numeric_array :
   public comparable_primitive_array < typename TYPE >
{
public:
   numeric_array();
   numeric_array(const numeric_array & base_array);

   index find_first_maximum_value();
   TYPE & get_maximum_value();

 	void CopySorted(
      const numeric_array  < TYPE > & base_array, // this base_array is sorted
      TYPE & tOffset,
      TYPE & tMin);

 	void Diff(
      const numeric_array  < TYPE > & array1,
      const numeric_array  < TYPE > & array2);

 	void divide(TYPE i);

 	void ElementDiff(
      const numeric_array  < TYPE > & array1,
      TYPE & tMax);

   TYPE GetMean();

   void Set(const TYPE & t, index iStart = 0, index iEnd = -1);

   index Cmp(const numeric_array  < TYPE > & array1);


   void QuickSort(bool bAsc = true)
   {
      if(bAsc)
      {
         sort::QuickSortAsc(*this);
      }
      else
      {
         sort::QuickSortDesc(*this);
      }
   }


};

template < class TYPE >
class unique_number_sort_array :
   public numeric_array < typename TYPE >
{
public:
   unique_number_sort_array(::ca::application * papp = NULL);
   unique_number_sort_array(const unique_number_sort_array & base_array);

   index add(const TYPE & newElement)
   {
      index iFind = 0;
      if(find(newElement, iFind))
      {
         return -1;
      }
      else
      {
         insert_at(iFind, newElement);
         return iFind;
      }
   }

   bool find(const TYPE &t, index & find) const
   {
      index iL = find;
      index iU = get_upper_bound();
      while(iU - iL > 5)
      {
         find = (iL + iU) / 2;
         TYPE tCmp = t - element_at(find);
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
      for(; find < get_size(); find++)
      {
         TYPE tCmp = t - element_at(find);
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
      const numeric_array  < TYPE > & base_array, // this base_array is sorted
      TYPE & tOffset,
      TYPE & tMin);

 	void Diff(
      const numeric_array  < TYPE > & array1,
      const numeric_array  < TYPE > & array2);*/

 	//void divide(int i);

 	//void ElementDiff(
     // const numeric_array  < TYPE > & array1,
      //TYPE & tMax);

   //TYPE GetMean();

   //void Set(const TYPE & t, int iStart = 0, int iEnd = -1);

   //int Cmp(const numeric_array  < TYPE > & array1);


   /*virtual void QuickSort(bool bAsc = true)
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
numeric_array(const numeric_array < TYPE > & a)
{
   operator = (a);
}


template < class TYPE >
index numeric_array < TYPE >::
Cmp(const numeric_array  < TYPE > & array1)
{
   count iMinSize = min(array1.get_size(), get_size());
   index i = 0;
   while(true)
   {
      if(i >= iMinSize)
      {
         return get_size() - array1.get_size();
      }
      if(element_at(i) > array1.element_at(i))
         return 1;
      else if(element_at(i) < array1.element_at(i))
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
   set_size(a.get_size());
   TYPE t;
   for(i = 0; i < a.get_size()
      && a.get_at(i) <= tStart; i++)
   {
      set_at(i, tMin);
   }
   for(; i < a.get_size(); i++)
   {
      t = a.get_at(i) + tOffset;
      set_at(i, t);
   }
}
template < class TYPE >
void numeric_array < TYPE >::Diff(
   const numeric_array  < TYPE > & array1,
   const numeric_array  < TYPE > & array2)
{
   ASSERT(array1.get_size() == array2.get_size());
   index i;
   set_size(array1.get_size());
   TYPE t;
   for(i = 0; i < array1.get_size(); i++)
   {
      t = array1.get_at(i) - array2.get_at(i); 
      set_at(i, t);
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
   set_size(a.get_size());
   if(a.get_size() > 0)
   {
      TYPE tLast = a[0];
      for(i = 1; i < a.get_size(); i++)
      {
         t = a[i];
         it =  t - tLast;
         set_at(i - 1, it);
         tLast = t;
      }
      it =  tMax - tLast;
      set_at(i - 1, it);
   }
}

template < class TYPE >
index numeric_array < TYPE >::find_first_maximum_value()
{
   TYPE tMax = element_at(0);
   for(index i = 1; i < m_nSize; i++)
   {
     if(element_at(i) > tMax)
         return i;
   }
   return -1;
}
template < class TYPE >
TYPE & numeric_array < TYPE >::
     get_maximum_value()
{
   ASSERT(m_nSize > 0);
   return element_at(find_first_maximum_value());
}

template < class TYPE >
TYPE numeric_array < TYPE >::GetMean()
{
   double dSum = 0.0;
   for(index i = 0; i < get_size(); i++)
   {
      dSum += element_at(i);
   }
   return (TYPE) (dSum / (double) get_size());
}

template < class TYPE >
void numeric_array < TYPE >::Set(const TYPE & t, index iStart, index iEnd)
{
   if(iEnd == -1)
      iEnd = get_upper_bound();
   for(index i = iStart; i <= iEnd; i++)
   {
      set_at(i, t);
   }
}


template < class TYPE >
void numeric_array < TYPE >::divide(TYPE div)
{
   index i;
   for(i = 0; i < get_size(); i++)
   {
      element_at(i) = element_at(i) / div;
   }
}

template < class TYPE >
unique_number_sort_array < TYPE >::
unique_number_sort_array(::ca::application * papp) :
   ca(papp)
{
}

template < class TYPE >
unique_number_sort_array < TYPE >::
unique_number_sort_array(const unique_number_sort_array < TYPE > & a) :
   ca(a.get_app())
{
   numeric_array < TYPE > ::operator = (a);
}


class CLASS_DECL_ca index_array : 
   virtual public numeric_array < index >
{
public:
   index_array(::ca::application * papp = NULL);
   index_array(const index_array & base_array);
   virtual ~index_array();

   index_array operator - (const index_array & inta) const;
   index_array operator + (const index_array & inta) const;
};

class CLASS_DECL_ca count_array : 
   virtual public numeric_array < count >
{
public:
   count_array(::ca::application * papp = NULL);
   count_array(const count_array & base_array);
   virtual ~count_array();

   count_array operator - (const count_array & inta) const;
   count_array operator + (const count_array & inta) const;
};


class CLASS_DECL_ca int_array : 
   virtual public numeric_array < int >
{
public:
   int_array(::ca::application * papp = NULL);
   int_array(const int_array & base_array);
   virtual ~int_array();

   int_array operator - (const int_array & inta) const;
   int_array operator + (const int_array & inta) const;
};


class CLASS_DECL_ca int64_array : 
   virtual public numeric_array < int64_t >
{
public:
   int64_array(::ca::application * papp = NULL);
   int64_array(const int64_array & base_array);
   virtual ~int64_array();

   int64_array operator - (const int64_array & inta) const;
   int64_array operator + (const int64_array & inta) const;
};

class CLASS_DECL_ca unique_int_sort_array : 
   virtual public unique_number_sort_array < int >
{
public:
   unique_int_sort_array(::ca::application * papp = NULL);
   unique_int_sort_array(const unique_int_sort_array & base_array);
   virtual ~unique_int_sort_array();

   unique_int_sort_array operator - (const unique_int_sort_array & inta) const;
   unique_int_sort_array operator + (const unique_int_sort_array & inta) const;
};

class CLASS_DECL_ca float_array : 
   virtual public numeric_array < float >
{
public:
   float_array();
   float_array(const float_array & base_array);
   virtual ~float_array();
};

class CLASS_DECL_ca double_array : 
   virtual public numeric_array < double >
{
public:
   double_array();
   double_array(const double_array & base_array);
   virtual ~double_array();
};

class CLASS_DECL_ca byte_array : 
   virtual public numeric_array < byte >
{
public:
	byte_array();
};


class CLASS_DECL_ca word_array : 
   virtual public numeric_array < word >
{
public:
	word_array();
};



class CLASS_DECL_ca dword_array :
   virtual public numeric_array < dword >  
{
public:
	
	dword_array();
	dword_array(const dword_array & base_array);
	virtual ~dword_array();

};


class CLASS_DECL_ca uint_array :
   public numeric_array < uint >  
{
public:
	uint_array();
	uint_array(const uint_array & base_array);
	virtual ~uint_array();
};




