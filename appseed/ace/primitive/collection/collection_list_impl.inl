#pragma once

template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
   {

      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node * pNewNode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, NULL, this->m_phead);

      if(this->m_phead != NULL)
         this->m_phead->m_pprev = pNewNode;
      else
         this->m_ptail = pNewNode;

      this->m_phead = pNewNode;

      this->m_count++;

      return (POSITION) pNewNode;

   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node* pNewNode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, this->m_ptail, NULL);

      pNewNode->m_value = newElement;

      if (this->m_ptail != NULL)
         this->m_ptail->m_pnext = pNewNode;
      else
         this->m_phead = pNewNode;

      this->m_ptail = pNewNode;

      this->m_count++;

      return (POSITION) pNewNode;

   }


      template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_before(POSITION position, ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      if (position == NULL)
         return add_head(newElement); // insert before nothing -> head of the list

      // Insert it before position
      typename list_data < TYPE, ARG_TYPE >::node* pOldNode = (typename list_data < TYPE, ARG_TYPE >::node*) position;
      typename list_data < TYPE, ARG_TYPE >::node* pNewNode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, pOldNode->m_pprev, pOldNode);
      pNewNode->m_value = newElement;

      if (pOldNode->m_pprev != NULL)
      {
         ASSERT(__is_valid_address(pOldNode->m_pprev, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pOldNode->m_pprev->m_pnext = pNewNode;
      }
      else
      {
         ASSERT(pOldNode == this->m_phead);
         this->m_phead = pNewNode;
      }
      pOldNode->m_pprev = pNewNode;
      return (POSITION) pNewNode;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_after(POSITION position, ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      if (position == NULL)
         return add_tail(newElement); // insert after nothing -> tail of the list

      // Insert it before position
      typename list_data < TYPE, ARG_TYPE >::node* pOldNode = (typename list_data < TYPE, ARG_TYPE >::node*) position;
      ASSERT(__is_valid_address(pOldNode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
      typename list_data < TYPE, ARG_TYPE >::node* pNewNode = new typename list_data < TYPE, ARG_TYPE >::node(newElement, pOldNode, pOldNode->m_pnext);
      pNewNode->m_value = newElement;

      if (pOldNode->m_pnext != NULL)
      {
         ASSERT(__is_valid_address(pOldNode->m_pnext, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pOldNode->m_pnext->m_pprev = pNewNode;
      }
      else
      {
         ASSERT(pOldNode == this->m_ptail);
         this->m_ptail = pNewNode;
      }
      pOldNode->m_pnext = pNewNode;
      return (POSITION) pNewNode;
   }




