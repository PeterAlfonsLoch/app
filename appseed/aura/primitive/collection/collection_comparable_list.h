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







//template<class TYPE, class ARG_TYPE>
//void comparable_list<TYPE, ARG_TYPE>::remove(ARG_TYPE elem)
//{
//
//   erase(find(elem));
//
//}
//
//template<class TYPE, class ARG_TYPE>
//typename comparable_list<TYPE, ARG_TYPE>::iterator comparable_list<TYPE, ARG_TYPE>::find(ARG_TYPE searchValue, iterator startAfter)
//{
//
//   ASSERT_VALID(this);
//
//   auto pnode = startAfter;
//
//   if (pnode == NULL)
//   {
//
//      pnode = this->m_phead;  // start at head
//
//   }
//   else
//   {
//
//      ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
//
//      pnode = pnode->m_pnext;  // start after the one specified
//
//   }
//
//   for (; pnode != NULL; pnode = pnode->m_pnext)
//   {
//
//      if (EqualElements(pnode->m_value, searchValue))
//      {
//
//         return (POSITION)pnode;
//
//      }
//
//   }
//
//   return NULL;
//
//}
//
