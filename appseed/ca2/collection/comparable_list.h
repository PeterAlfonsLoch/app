#pragma once


template < class TYPE, class ARG_TYPE = const TYPE &, class ARRAY_TYPE = comparable_eq_list < TYPE, ARG_TYPE > >
class comparable_list :
   virtual public ARRAY_TYPE
{
public:
   comparable_list();
   comparable_list(const comparable_list & base_array);

   void QuickSort(bool bAsc = true);

   TYPE maximum(TYPE minimum);

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




template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
TYPE comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
maximum(TYPE maximum)
{
   POSITION pos = this->get_head_position();
   while(pos != NULL)
   {
      TYPE value = this->get_next(pos);
      if(value > maximum)
      {
         maximum = value;
      }
   }
   return maximum;
}




