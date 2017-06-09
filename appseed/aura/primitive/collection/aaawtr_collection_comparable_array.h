#pragma once



template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = array < TYPE,ARG_TYPE > >
class array :
   public ARRAY_TYPE
{
public:


   typedef ARRAY_TYPE BASE_ARRAY;
   //DECLARE_AND_IMPLEMENT_DEFAULT_CONSTRUCTION_AND_ASSIGNMENT(array, ARRAY_TYPE)

   array(::std::initializer_list < TYPE > l) : BASE_ARRAY(l) {   }
   array() {}
   array(::aura::application * papp) : object(papp), ARRAY_TYPE(papp) {}
   array(const array & array)
   {
      operator = (array);
   }
   array(array && array)
   {
      move(::move(array));
   }

   //void quick_sort(bool bAsc = true);


   array & operator = (const array & array)
   {
      BASE_ARRAY::operator = (array);
      return *this;
   }
   array & operator = (array && array)
   {
      move(::move(array));
      return *this;
   }
   array & move(array && array)
   {
      BASE_ARRAY::move(::move(array));
      return *this;
   }


};



//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//array()
//{
//
//}
//
//
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
//array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//array(const array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a)
//{
//
//   this->ARRAY_TYPE::operator = (a);
//
//}
//
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
//array<  TYPE,ARG_TYPE,ARRAY_TYPE>::
//array(array<  TYPE,ARG_TYPE,ARRAY_TYPE> && a)
//{
//
//   move(::move(a));
//
//}
//
//
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
//array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & array<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//operator = (const array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a)
//{
//
//   this->ARRAY_TYPE::operator = (a);
//   return *this;
//
//}
//
//template < class TYPE,class ARG_TYPE,class ARRAY_TYPE>
//array<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & array<  TYPE,ARG_TYPE,ARRAY_TYPE>::
//operator = (array<  TYPE,ARG_TYPE,ARRAY_TYPE> && a)
//{
//
//   return move(::move(a));
//
//}
//
//
//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//array<  TYPE, ARG_TYPE, ARRAY_TYPE> & array<  TYPE, ARG_TYPE, ARRAY_TYPE>::
//move(array<  TYPE, ARG_TYPE, ARRAY_TYPE> && a)
//{
//
//	this->ARRAY_TYPE::move(::move(a));
//
//	return *this;
//
//}
//
//
template < class TYPE,class ARG_TYPE = TYPE const &,class ARRAY_TYPE = array < TYPE,ARG_TYPE > >
class full_comparable_array:
   virtual public ARRAY_TYPE
{
public:
   full_comparable_array();
   full_comparable_array(const full_comparable_array & array);

   //inline bool sort_find(ARG_TYPE & arg,index & iIndex,index iStart,index iEnd) const
   //{
   //   if(this->get_size() == 0)
   //   {
   //      return false;
   //   }
   //   index iLowerBound = iStart;
   //   index iMaxBound = iEnd;
   //   index iUpperBound = iMaxBound;
   //   memory_offset_t iCompare;
   //   // do binary search
   //   iIndex = (iUpperBound + iLowerBound) / 2;
   //   while(iUpperBound - iLowerBound >= 8)
   //   {
   //      iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
   //      if(iCompare == 0)
   //      {
   //         return true;
   //      }
   //      else if(iCompare > 0)
   //      {
   //         iUpperBound = iIndex - 1;
   //         if(iUpperBound < 0)
   //         {
   //            iIndex = 0;
   //            break;
   //         }
   //      }
   //      else
   //      {
   //         iLowerBound = iIndex + 1;
   //         if(iLowerBound > iMaxBound)
   //         {
   //            iIndex = iMaxBound + 1;
   //            break;
   //         }
   //      }
   //      iIndex = (iUpperBound + iLowerBound) / 2;
   //   }
   //   // do sequential search
   //   while(iIndex < this->get_count())
   //   {
   //      iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
   //      if(iCompare == 0)
   //         return true;
   //      else if(iCompare < 0)
   //         iIndex++;
   //      else
   //         break;
   //   }
   //   if(iIndex >= this->get_count())
   //      return false;
   //   while(iIndex >= 0)
   //   {
   //      iCompare = COMPARE::CompareElements(&this->element_at(iIndex),arg);
   //      if(iCompare == 0)
   //         return true;
   //      else if(iCompare > 0)
   //         iIndex--;
   //      else
   //         break;
   //   }
   //   iIndex++;
   //   return false;

   //}


};



template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
full_comparable_array()
{
}
template < class TYPE,class ARG_TYPE,class ARRAY_TYPE >
full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE >::
full_comparable_array(const full_comparable_array<  TYPE,ARG_TYPE,ARRAY_TYPE > & a):
ARRAY_TYPE(a)
{
   this->operator = (a);
}


