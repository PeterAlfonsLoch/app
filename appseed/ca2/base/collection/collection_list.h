#pragma once


   template<class TYPE, class ARG_TYPE = const TYPE&>
   class list :
      public ::ca2::object
   {
   public:
      class node
      {
      public:
         node* pNext;
         node* pPrev;
         TYPE data;
      };


      class iterator
      {
      public:


         POSITION         m_pos;
         list *    m_plist;

         iterator()
         {
            m_pos = 0;
            m_plist = NULL;
         }

         iterator(POSITION i, list * plist)
         {
            m_pos = i;
            m_plist = plist;
         }

         iterator(const iterator & it)
         {
            operator = (it);
         }

         TYPE & operator * ()
         {
            return m_plist->get_at(m_pos);
         }

         const TYPE & operator * () const
         {
            return m_plist->get_at(m_pos);
         }

         iterator & operator = (const iterator & it)
         {
            if(this != &it)
            {
               m_pos      = it.m_pos;
               m_plist    = it.m_plist;
            }
            return *this;
         }

         bool operator == (const iterator & it)
         {
            if(this == &it)
               return true;
            if(m_plist != it.m_plist)
               return false;
            return m_pos == it.m_pos;
         }

         bool operator != (const iterator & it)
         {
            return !operator==(it);
         }

         iterator & operator ++()
         {
         
            if(m_pos == NULL || m_pos == m_plist->get_tail_position())
               return * this;

            m_plist->get_next(m_pos);

            return *this;

         }

         iterator & operator +(int32_t i)
         {

            while(m_pos != NULL && m_pos != m_plist->get_tail_position() && i > 0)
            {

               i--;
               m_plist->get_next(m_pos);

            }

            return *this;

         }

         iterator & operator --()
         {

            if(m_pos == NULL || m_pos == m_plist->get_head_position())
               return * this;

            m_plist->get_previous(m_pos);

            return *this;

         }

         iterator & operator -(int32_t i)
         {

            while(m_pos != NULL && m_pos != m_plist->get_head_position() && i > 0)
            {
               i--;
               m_plist->get_previous(m_pos);
            }

            return *this;

         }

      };


      class const_iterator
      {
      public:


         POSITION                m_pos;
         const list *     m_plist;

         const_iterator()
         {
            m_pos = 0;
            m_plist = NULL;
         }

         const_iterator(POSITION i, const list * plist)
         {
            m_pos = i;
            m_plist = plist;
         }

         const_iterator(const const_iterator & it)
         {
            operator = (it);
         }

         const TYPE & operator * ()
         {
            return m_plist->get_at(m_pos);
         }

         const TYPE & operator * () const
         {
            return m_plist->get_at(m_pos);
         }

         const_iterator & operator = (const const_iterator & it)
         {
            if(this != &it)
            {
               m_pos      = it.m_pos;
               m_plist    = it.m_plist;
            }
            return *this;
         }

         bool operator == (const const_iterator & it)
         {
            if(this == &it)
               return true;
            if(m_plist != it.m_plist)
               return false;
            return m_pos == it.m_pos;
         }

         bool operator != (const const_iterator & it)
         {
            return !operator==(it);
         }

         const_iterator & operator ++()
         {
         
            if(m_pos == NULL || m_pos == m_plist->get_tail_position())
               return * this;

            m_plist->get_next(m_pos);

            return *this;

         }

         const_iterator & operator +(int32_t i)
         {

            while(m_pos != NULL && m_pos != m_plist->get_tail_position() && i > 0)
            {

               i--;
               m_plist->get_next(m_pos);

            }

            return *this;

         }

         const_iterator & operator --()
         {

            if(m_pos == NULL || m_pos == m_plist->get_head_position())
               return * this;

            m_plist->get_previous(m_pos);

            return *this;

         }

         const_iterator & operator -(int32_t i)
         {

            while(m_pos != NULL && m_pos != m_plist->get_head_position() && i > 0)
            {
               i--;
               m_plist->get_previous(m_pos);
            }

            return *this;

         }

      };


      iterator begin()
      {
         return iterator(get_head_position(), this);
      }


      iterator end()
      {
         return iterator(NULL, this);
      }

      const_iterator begin() const
      {
         return const_iterator(get_head_position(), this);
      }


      const_iterator end() const
      {
         return const_iterator(NULL, this);
      }


      list(::count nBlockSize = 10);
      list(const class list & l);

   // Attributes (head and tail)
      // ::count of elements
      ::count get_count() const;
      ::count get_size() const;
      ::count size() const;
      bool is_empty(::count countMinimum = 1) const;
      bool has_elements(::count countMinimum = 1) const;

      // peek at head or tail
      TYPE& get_head();
      const TYPE& get_head() const;
      TYPE& get_tail();
      const TYPE& get_tail() const;

   // Operations
      // get head or tail (and remove it) - don't call on is_empty list !
      TYPE remove_head();
      TYPE remove_tail();

      // add before head or after tail
      POSITION add_head(ARG_TYPE newElement);
      POSITION add_tail(ARG_TYPE newElement);
      void push_back(ARG_TYPE newElement);

      // add another list of elements before head or after tail
      void add_head(list* pNewList);
      void add_tail(list* pNewList);

      // remove all elements
      void remove_all();
      void clear();

      TYPE & front();
      const TYPE & front() const;

      void pop_front();

      // iteration
      POSITION get_head_position() const;
      POSITION get_tail_position() const;
      TYPE& get_next(POSITION& rPosition); // return *position++
      const TYPE& get_next(POSITION& rPosition) const; // return *position++
      TYPE& get_previous(POSITION& rPosition); // return *position--
      const TYPE& get_previous(POSITION& rPosition) const; // return *position--

      // getting/modifying an element at a given position
      TYPE& get_at(POSITION position);
      const TYPE& get_at(POSITION position) const;
      void set_at(POSITION pos, ARG_TYPE newElement);
      void remove_at(POSITION position);

      // inserting before or after a given position
      POSITION insert_before(POSITION position, ARG_TYPE newElement);
      POSITION insert_after(POSITION position, ARG_TYPE newElement);

      void swap(POSITION position1, POSITION position2);

      // helper functions (note: O(n) speed)
      POSITION find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
         // defaults to starting at the HEAD, return NULL if not found
      POSITION find_index(index nIndex) const;
         // get the 'nIndex'th element (may return NULL)
      index position_index(POSITION pos) const;
         // get the 'nIndex' of the position (may return -1)

      list < TYPE, ARG_TYPE > & operator = (const class list & l);

   // Implementation
   protected:
      node* m_pnodeHead;
      node* m_pnodeTail;
      ::count m_nCount;
      node* m_pnodeFree;
      struct plex* m_pBlocks;
      ::count m_nBlockSize;

      node* NewNode(node*, node*);
      void FreeNode(node*);

   public:
      ~list();
      //void Serialize(CArchive&);
      void dump(dump_context &) const;
      void assert_valid() const;
   };

   /////////////////////////////////////////////////////////////////////////////
   // list<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_count() const
{
   return m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_size() const
{
   return m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::size() const
{
   return m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return m_nCount < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return m_nCount >= countMinimum;
}

   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_head()
      { ASSERT(m_pnodeHead != NULL);
         return m_pnodeHead->data; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_head() const
      { ASSERT(m_pnodeHead != NULL);
         return m_pnodeHead->data; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_tail()
      { ASSERT(m_pnodeTail != NULL);
         return m_pnodeTail->data; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_tail() const
      { ASSERT(m_pnodeTail != NULL);
         return m_pnodeTail->data; }
   template<class TYPE, class ARG_TYPE>
   inline POSITION list<TYPE, ARG_TYPE>::get_head_position() const
      { return (POSITION) m_pnodeHead; }
   template<class TYPE, class ARG_TYPE>
   inline POSITION list<TYPE, ARG_TYPE>::get_tail_position() const
      { return (POSITION) m_pnodeTail; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) // return *position++
      { node* pNode = (node*) rPosition;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         rPosition = (POSITION) pNode->pNext;
         return pNode->data; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) const // return *position++
      { node* pNode = (node*) rPosition;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         rPosition = (POSITION) pNode->pNext;
         return pNode->data; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) // return *position--
      { node* pNode = (node*) rPosition;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         rPosition = (POSITION) pNode->pPrev;
         return pNode->data; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) const // return *position--
      { node* pNode = (node*) rPosition;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         rPosition = (POSITION) pNode->pPrev;
         return pNode->data; }

template<class TYPE, class ARG_TYPE>
inline TYPE & list < TYPE, ARG_TYPE >::front()
{
   return get_at(get_head_position());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::front() const
{
   return get_at(get_head_position());
}

template<class TYPE, class ARG_TYPE>
inline void list < TYPE, ARG_TYPE >::pop_front()
{
   return remove_at(get_head_position());
}


   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position)
      { node* pNode = (node*) position;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         return pNode->data; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position) const
      { node* pNode = (node*) position;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         return pNode->data; }
   template<class TYPE, class ARG_TYPE>
   inline void list<TYPE, ARG_TYPE>::set_at(POSITION pos, ARG_TYPE newElement)
      { node* pNode = (node*) pos;
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         pNode->data = newElement; }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list(::count nBlockSize)
   {
      ASSERT(nBlockSize > 0);

      m_nCount          = 0;
      m_pnodeHead       = NULL;
      m_pnodeTail       = NULL;
      m_pnodeFree       = NULL;
      m_pBlocks         = NULL;
      m_nBlockSize      = nBlockSize;
   }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list(const class list & l)
   {
      
      m_nCount          = 0;
      m_pnodeHead       = NULL;
      m_pnodeTail       = NULL;
      m_pnodeFree       = NULL;
      m_pBlocks         = NULL;
      m_nBlockSize      = l.m_nBlockSize;

      POSITION pos      = l.get_head_position();

      while(pos != NULL)
      {
         add_tail(const_cast < TYPE & > (l.get_next(pos)));
      }

   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_all()
   {
      ASSERT_VALID(this);

      // destroy elements
      node* pNode;
      for (pNode = m_pnodeHead; pNode != NULL; pNode = pNode->pNext)
         pNode->data.~TYPE();

      m_nCount = 0;
      m_pnodeHead = m_pnodeTail = m_pnodeFree = NULL;
      m_pBlocks->FreeDataChain();
      m_pBlocks = NULL;
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::clear()
   {

      remove_all();

   }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::~list()
   {
      remove_all();
      ASSERT(m_nCount == 0);
   }

   /////////////////////////////////////////////////////////////////////////////
   // Node helpers
   //
   // Implementation note: node's are stored in plex blocks and
   //  chained together. Free blocks are maintained in a singly linked list
   //  using the 'pNext' member of node with 'm_pnodeFree' as the head.
   //  Used blocks are maintained in a doubly linked list using both 'pNext'
   //  and 'pPrev' as links and 'm_pnodeHead' and 'm_pnodeTail'
   //   as the head/tail.
   //
   // We never free a plex block unless the List is destroyed or remove_all()
   //  is used - so the total number of plex blocks may grow large depending
   //  on the maximum past size of the list.
   //

   template<class TYPE, class ARG_TYPE>
   typename list<TYPE, ARG_TYPE>::node *
   list<TYPE, ARG_TYPE>::NewNode(node* pPrev, node* pNext)
   {
      if (m_pnodeFree == NULL)
      {
         // add another block
         plex* pNewBlock = plex::create(m_pBlocks, m_nBlockSize, sizeof(node));

         // chain them into free list
         node* pNode = (node*) pNewBlock->data();
         // free in reverse order to make it easier to debug
         pNode += m_nBlockSize - 1;
         for (index i = m_nBlockSize-1; i >= 0; i--, pNode--)
         {
            pNode->pNext = m_pnodeFree;
            m_pnodeFree = pNode;
         }
      }
      ENSURE(m_pnodeFree != NULL);  // we must have something

      list::node* pNode = m_pnodeFree;
      m_pnodeFree = m_pnodeFree->pNext;
      pNode->pPrev = pPrev;
      pNode->pNext = pNext;
      m_nCount++;
      ASSERT(m_nCount > 0);  // make sure we don't overflow

   #undef new
      ::new( (void *)( &pNode->data ) ) TYPE;
   #define new DEBUG_NEW
      return pNode;
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::FreeNode(node* pNode)
   {
      pNode->data.~TYPE();
      pNode->pNext = m_pnodeFree;
      m_pnodeFree = pNode;
      m_nCount--;
      ASSERT(m_nCount >= 0);  // make sure we don't underflow

      // if no more elements, cleanup completely
      if (m_nCount == 0)
         remove_all();
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::add_head(ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      node* pNewNode = NewNode(NULL, m_pnodeHead);
      pNewNode->data = newElement;
      if (m_pnodeHead != NULL)
         m_pnodeHead->pPrev = pNewNode;
      else
         m_pnodeTail = pNewNode;
      m_pnodeHead = pNewNode;
      return (POSITION) pNewNode;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::add_tail(ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      node* pNewNode = NewNode(m_pnodeTail, NULL);
      pNewNode->data = newElement;
      if (m_pnodeTail != NULL)
         m_pnodeTail->pNext = pNewNode;
      else
         m_pnodeHead = pNewNode;
      m_pnodeTail = pNewNode;
      return (POSITION) pNewNode;
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement)
   {
      add_tail(newElement);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::add_head(list* pNewList)
   {
      ASSERT_VALID(this);

      ENSURE(pNewList != NULL);
      ASSERT_VALID(pNewList);

      // add a list of same elements to head (maintain order)
      POSITION pos = pNewList->get_tail_position();
      while (pos != NULL)
         add_head(pNewList->get_previous(pos));
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::add_tail(list* pNewList)
   {
      ASSERT_VALID(this);
      ENSURE(pNewList != NULL);
      ASSERT_VALID(pNewList);

      // add a list of same elements
      POSITION pos = pNewList->get_head_position();
      while (pos != NULL)
         add_tail(pNewList->get_next(pos));
   }

   template<class TYPE, class ARG_TYPE>
   TYPE list<TYPE, ARG_TYPE>::remove_head()
   {
      ASSERT_VALID(this);
      ASSERT(m_pnodeHead != NULL);  // don't call on is_empty list !!!
      ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));

      node* pOldNode = m_pnodeHead;
      TYPE returnValue = pOldNode->data;

      m_pnodeHead = pOldNode->pNext;
      if (m_pnodeHead != NULL)
         m_pnodeHead->pPrev = NULL;
      else
         m_pnodeTail = NULL;
      FreeNode(pOldNode);
      return returnValue;
   }

   template<class TYPE, class ARG_TYPE>
   TYPE list<TYPE, ARG_TYPE>::remove_tail()
   {
      ASSERT_VALID(this);
      ASSERT(m_pnodeTail != NULL);  // don't call on is_empty list !!!
      ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));

      node* pOldNode = m_pnodeTail;
      TYPE returnValue = pOldNode->data;

      m_pnodeTail = pOldNode->pPrev;
      if (m_pnodeTail != NULL)
         m_pnodeTail->pNext = NULL;
      else
         m_pnodeHead = NULL;
      FreeNode(pOldNode);
      return returnValue;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_before(POSITION position, ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      if (position == NULL)
         return add_head(newElement); // insert before nothing -> head of the list

      // Insert it before position
      node* pOldNode = (node*) position;
      node* pNewNode = NewNode(pOldNode->pPrev, pOldNode);
      pNewNode->data = newElement;

      if (pOldNode->pPrev != NULL)
      {
         ASSERT(__is_valid_address(pOldNode->pPrev, sizeof(node)));
         pOldNode->pPrev->pNext = pNewNode;
      }
      else
      {
         ASSERT(pOldNode == m_pnodeHead);
         m_pnodeHead = pNewNode;
      }
      pOldNode->pPrev = pNewNode;
      return (POSITION) pNewNode;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_after(POSITION position, ARG_TYPE newElement)
   {
      ASSERT_VALID(this);

      if (position == NULL)
         return add_tail(newElement); // insert after nothing -> tail of the list

      // Insert it before position
      node* pOldNode = (node*) position;
      ASSERT(__is_valid_address(pOldNode, sizeof(node)));
      node* pNewNode = NewNode(pOldNode, pOldNode->pNext);
      pNewNode->data = newElement;

      if (pOldNode->pNext != NULL)
      {
         ASSERT(__is_valid_address(pOldNode->pNext, sizeof(node)));
         pOldNode->pNext->pPrev = pNewNode;
      }
      else
      {
         ASSERT(pOldNode == m_pnodeTail);
         m_pnodeTail = pNewNode;
      }
      pOldNode->pNext = pNewNode;
      return (POSITION) pNewNode;
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::swap(POSITION position1, POSITION position2)
   {
      ASSERT_VALID(this);

      if(position1 == NULL)
      {
         if(position2 == NULL)
         {
            return;
         }
         else
         {
            node * pnode = (node *) position2;
            if(pnode != m_pnodeHead)
            {
               if(m_pnodeTail == pnode)
               {
                  m_pnodeTail = pnode->pPrev;
               }
               if(pnode->pPrev != NULL)
               {
                  pnode->pPrev->pNext = pnode->pNext;
               }
               if(pnode->pNext != NULL)
               {
                  pnode->pNext->pPrev = pnode->pPrev;
               }
               pnode->pPrev = NULL;
               pnode->pNext = m_pnodeHead;
               m_pnodeHead = pnode;
            }
         }
      }
      else if(position2 == NULL)
      {
         node * pnode = (node *) position1;
         if(pnode != m_pnodeTail)
         {
            if(m_pnodeHead == pnode)
            {
               m_pnodeHead = pnode->pNext;
            }
            if(pnode->pNext != NULL)
            {
               pnode->pPrev->pPrev = pnode->pPrev;
            }
            if(pnode->pNext != NULL)
            {
               pnode->pPrev->pNext = pnode->pNext;
            }
            pnode->pNext = NULL;
            pnode->pPrev = m_pnodeTail;
            m_pnodeTail = pnode;
         }
      }
      else
      {
         node * pnode1 = (node *) position1;
         node * pnode2 = (node *) position2;
         node * pnodeSwapPrev = pnode1->pPrev;
         node * pnodeSwapNext = pnode1->pNext;
         if(pnode1->pPrev != NULL)
         {
            pnode1->pPrev->pNext = pnode2;
         }
         if(pnode1->pNext != NULL)
         {
            pnode1->pNext->pPrev = pnode2;
         }
         if(pnode2->pPrev != NULL)
         {
            pnode2->pPrev->pNext = pnode1;
         }
         if(pnode2->pNext != NULL)
         {
            pnode2->pNext->pPrev = pnode1;
         }
         pnode1->pPrev = pnode2->pPrev;
         pnode1->pNext = pnode2->pNext;
         pnode2->pPrev = pnodeSwapPrev;
         pnode2->pNext = pnodeSwapNext;
         if(pnode1 == m_pnodeHead)
         {
            m_pnodeHead = pnode2;
         }
         if(pnode1 == m_pnodeTail)
         {
            m_pnodeTail = pnode2;
         }
         if(pnode2 == m_pnodeHead)
         {
            m_pnodeHead = pnode1;
         }
         if(pnode2 == m_pnodeTail)
         {
            m_pnodeTail = pnode1;
         }
      }


   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_at(POSITION position)
   {
      ASSERT_VALID(this);

      node* pOldNode = (node*) position;
      ASSERT(__is_valid_address(pOldNode, sizeof(node)));

      // remove pOldNode from list
      if (pOldNode == m_pnodeHead)
      {
         m_pnodeHead = pOldNode->pNext;
      }
      else
      {
         ASSERT(__is_valid_address(pOldNode->pPrev, sizeof(node)));
         pOldNode->pPrev->pNext = pOldNode->pNext;
      }
      if (pOldNode == m_pnodeTail)
      {
         m_pnodeTail = pOldNode->pPrev;
      }
      else
      {
         ASSERT(__is_valid_address(pOldNode->pNext, sizeof(node)));
         pOldNode->pNext->pPrev = pOldNode->pPrev;
      }
      FreeNode(pOldNode);
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::find_index(index nIndex) const
   {
      ASSERT_VALID(this);

      if (nIndex >= m_nCount || nIndex < 0)
         return NULL;  // went too far

      node* pNode = m_pnodeHead;
      while (nIndex--)
      {
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         pNode = pNode->pNext;
      }
      return (POSITION) pNode;
   }

   template<class TYPE, class ARG_TYPE>
   index list<TYPE, ARG_TYPE>::position_index(POSITION pos) const
   {
      ASSERT_VALID(this);

      node* pnode = m_pnodeHead;
      index i = 0;
      while(pnode != NULL)
      {
         if((node *) pos == pnode)
            return i;
         ASSERT(__is_valid_address(pnode, sizeof(node)));
         pnode = pnode->pNext;
         i++;
      }
      return -1;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::find(ARG_TYPE searchValue, POSITION startAfter) const
   {
      ASSERT_VALID(this);

      node* pNode = (node*) startAfter;
      if (pNode == NULL)
      {
         pNode = m_pnodeHead;  // start at head
      }
      else
      {
         ASSERT(__is_valid_address(pNode, sizeof(node)));
         pNode = pNode->pNext;  // start after the one specified
      }

      for (; pNode != NULL; pNode = pNode->pNext)
         if (::ca2::equals_type_arg_type < TYPE, ARG_TYPE > ::CompareElements(&pNode->data, searchValue))
            return (POSITION)pNode;
      return NULL;
   }
   /*

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
   {
      ASSERT_VALID(this);

      ::ca2::object::Serialize(ar);

      if (ar.IsStoring())
      {
         ar.WriteCount(m_nCount);
         for (node* pNode = m_pnodeHead; pNode != NULL; pNode = pNode->pNext)
         {
            ASSERT(__is_valid_address(pNode, sizeof(node)));
            TYPE* pData;
            //
            // in some cases the & operator might be overloaded, and we cannot use it to obtain
            //the address of a given object.  We then use the following trick to get the address
            //
            pData = reinterpret_cast< TYPE* >( &reinterpret_cast< int32_t& >( static_cast< TYPE& >( pNode->data ) ) );
            SerializeElements<TYPE>(ar, pData, 1);
         }
      }
      else
      {
         uint_ptr nNewCount = ar.ReadCount();
         while (nNewCount--)
         {
            TYPE newData[1];
            SerializeElements<TYPE>(ar, newData, 1);
            add_tail(newData[0]);
         }
      }
   }*/

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::dump(dump_context & dumpcontext) const
   {
      ::ca2::object::dump(dumpcontext);

      dumpcontext << "with " << m_nCount << " elements";
      if (dumpcontext.GetDepth() > 0)
      {
         POSITION pos = get_head_position();
         while (pos != NULL)
         {
            TYPE temp[1];
            temp[0] = ((list*)this)->get_next(pos);
            dumpcontext << "\n";
            dump_elements<TYPE>(dumpcontext, temp, 1);
         }
      }

      dumpcontext << "\n";
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::assert_valid() const
   {
      ::ca2::object::assert_valid();

      if (m_nCount == 0)
      {
         // is_empty list
         ASSERT(m_pnodeHead == NULL);
         ASSERT(m_pnodeTail == NULL);
      }
      else
      {
         // non-is_empty list
         ASSERT(__is_valid_address(m_pnodeHead, sizeof(node)));
         ASSERT(__is_valid_address(m_pnodeTail, sizeof(node)));
      }
   }

   template<class TYPE, class ARG_TYPE>
   list < TYPE, ARG_TYPE > &
   list<TYPE, ARG_TYPE>::operator = (const class list & l)
   {
      if(&l != this)
      {
         remove_all();
         m_nBlockSize = l.m_nBlockSize;
         POSITION pos = l.get_head_position();
         while(pos != NULL)
         {
            add_tail(const_cast < TYPE & > (l.get_next(pos)));
         }
      }
      return *this;
   }
