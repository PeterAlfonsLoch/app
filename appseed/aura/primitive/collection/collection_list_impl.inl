#pragma once


template<class TYPE, class ARG_TYPE>
typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::insert_first(ARG_TYPE newElement)
{

   ASSERT_VALID(this);

   typename list_data < TYPE, ARG_TYPE >::node * pnode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, NULL, this->m_phead);

   if (this->m_phead != NULL)
      this->m_phead->m_pprev = pnode;
   else
      this->m_ptail = pnode;

   this->m_phead = pnode;

   this->m_nCount++;

   return pnode;

}


template<class TYPE, class ARG_TYPE>
typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::add(ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   typename list_data < TYPE, ARG_TYPE >::node* pnode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, this->m_ptail, NULL);

   pnode->m_value = newElement;

   if (this->m_ptail != NULL)
   {

      this->m_ptail->m_pnext = pnode;

   }
   else
   {

      this->m_phead = pnode;

   }

   this->m_ptail = pnode;

   this->m_nCount++;

   return pnode;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_before(iterator position, ARG_TYPE newElement)
{
   ASSERT_VALID(this);

   if (position == NULL)
   {

      return insert_first(newElement); // insert before nothing -> head of the list

   }

   // Insert it before position
   node* pnodeOld =  position.m_pnode;
   node* pnodeNew = new node(newElement, pnodeOld->m_pprev, pnodeOld);
   pnodeNew->m_value = newElement;

   if (pnodeOld->m_pprev != NULL)
   {
      ASSERT(__is_valid_address(pnodeOld->m_pprev, sizeof(node)));
      pnodeOld->m_pprev->m_pnext = pnodeNew;
   }
   else
   {
      ASSERT(pnodeOld == this->m_phead);
      this->m_phead = pnodeNew;
   }
   pnodeOld->m_pprev = pnodeNew;

   return pnodeNew;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::insert_after(iterator position, ARG_TYPE newElement)
{
   
   ASSERT_VALID(this);

   if (position == NULL)
   {

      return add(newElement); // insert after nothing -> tail of the list

   }

   // Insert it before position
   node * pnodeOld = position.m_pnode;
   
   ASSERT(__is_valid_address(pnodeOld, sizeof(node)));
   
   node * pnodeNew = new node(newElement, pnodeOld, pnodeOld->m_pnext);
   
   pnodeNew->m_value = newElement;

   if (pnodeOld->m_pnext != NULL)
   {
      
      ASSERT(__is_valid_address(pnodeOld->m_pnext, sizeof(node)));
      
      pnodeOld->m_pnext->m_pprev = pnodeNew;

   }
   else
   {
      
      ASSERT(pnodeOld == this->m_ptail);
      
      this->m_ptail = pnodeNew;

   }

   pnodeOld->m_pnext = pnodeNew;

   return pnodeNew;

}




