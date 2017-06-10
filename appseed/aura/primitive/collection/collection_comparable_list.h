#pragma once


template < class TYPE, class ARG_TYPE = const TYPE &, class LIST_TYPE = comparable_eq_list < TYPE, ARG_TYPE > >
class comparable_list :
   virtual public LIST_TYPE
{
public:
   comparable_list();
   comparable_list(const comparable_list & array);

   void quick_sort(bool bAsc = true);

   TYPE maximum(TYPE minimum);

};

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_list()
{
}

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
comparable_list(const comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{
}




template < class TYPE, class ARG_TYPE, class LIST_TYPE>
TYPE comparable_list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
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




