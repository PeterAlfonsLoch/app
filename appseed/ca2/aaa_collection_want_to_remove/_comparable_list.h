#pragma once

template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = comparable_eq_list < TYPE, ARG_TYPE > >
class comparable_list :
   virtual public ARRAY_TYPE
{
public:
   comparable_list();
   comparable_list(const comparable_list & base_array);

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
template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_list()
{
}
template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
comparable_list(const comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE> & a) :
ARRAY_TYPE(a)
{
   operator = (a);
}




