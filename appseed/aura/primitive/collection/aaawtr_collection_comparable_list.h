#pragma once


template < class TYPE, class ARG_TYPE = const TYPE &, class LIST_TYPE = list < TYPE, ARG_TYPE > >
class list :
   virtual public LIST_TYPE
{
public:
   list();
   list(const list & array);

   void quick_sort(bool bAsc = true);

};

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
list()
{
}

template < class TYPE, class ARG_TYPE, class LIST_TYPE>
list<  TYPE,  ARG_TYPE,  LIST_TYPE>::
list(const list<  TYPE,  ARG_TYPE,  LIST_TYPE> & l) :
LIST_TYPE(l)
{

}


