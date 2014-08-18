#pragma once


template<class TYPE, class ARG_TYPE = const TYPE & >
class list;

template<class TYPE, class ARG_TYPE = const TYPE & >
class list_data
{
public:

   class node
   {
   public:

      node *   m_pnext;
      node *   m_pprev;
      TYPE     m_value;

      node(ARG_TYPE t, node * pprev, node * pnext) : m_value(t), m_pprev(pprev), m_pnext(pnext) { }

   };


   node *         m_phead;
   node *         m_ptail;
   ::count        m_count;

   inline list_data();
   inline list_data(const class list_data < TYPE, ARG_TYPE >  & l);
   inline list_data(const class list < TYPE, ARG_TYPE > & l);

   inline static void from(list_data < TYPE, ARG_TYPE >  & l, node * p);
   inline static list_data < TYPE, ARG_TYPE >  from(node * p);

};

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data()
{

   this->m_count       = 0;
   this->m_phead       = NULL;
   this->m_ptail       = NULL;

}

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data (const class list_data < TYPE, ARG_TYPE >  & l)
{

   this->m_count              = l.m_count;
   this->m_phead        = l.m_phead;
   this->m_ptail        = l.m_ptail;

}


template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data (const class list < TYPE, ARG_TYPE > & l)
{

   this->m_count              = l.m_count;
   this->m_phead        = l.m_phead;
   this->m_ptail        = l.m_ptail;

}

template<class TYPE, class ARG_TYPE>
inline void list_data < TYPE, ARG_TYPE >::from(list_data < TYPE, ARG_TYPE >  & l, node * pnode)
{

   l.m_ptail = NULL;

   l.m_phead = pnode;

   l.m_count = 0;

   if(pnode == NULL)
      return;

   while(true)
   {

      if(pnode->m_pnext == NULL)
      {

         l.m_ptail = pnode;

         break;

      }

      pnode = pnode->m_pnext;

      l.m_count++;

   }

   l.m_count++;

}

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE > list_data < TYPE, ARG_TYPE >::from(node * p)
{

   list_data < TYPE, ARG_TYPE >  l;
   from(l, p);
   return l;

}

   template < class TYPE, class ARG_TYPE >
   class list :
      virtual public ::object,
      public list_data < TYPE, ARG_TYPE >
   {
   public:


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

         iterator operator ++ ( int )
         {

            if(m_pos == NULL || m_pos == m_plist->get_tail_position())
               return * this;

            iterator i(*this);

            m_plist->get_next(m_pos);

            return i;

         }

         iterator & operator ++ ()
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

         iterator operator -- ( int )
         {

            if(m_pos == NULL || m_pos == m_plist->get_head_position())
               return * this;

            iterator it(*this);

            m_plist->get_previous(m_pos);

            return it;

         }

         iterator & operator -- ()
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

         const_iterator(const iterator & it)
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

         const_iterator & operator = (const iterator & it)
         {
            m_pos      = it.m_pos;
            m_plist    = it.m_plist;
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



      list();
      list(const class list & l);
      list(const class list_data < TYPE, ARG_TYPE > & l);
#ifdef MOVE_SEMANTICS
      list(class list && l);
#endif
      virtual ~list();

      //void Serialize(CArchive&);
   // Attributes (head and tail)
      // ::count of elements
      ::count get_count() const;
      ::count get_size() const;
      ::count size() const;
      bool is_empty(::count countMinimum = 1) const;
      bool has_elements(::count countMinimum = 1) const;
      bool empty(::count countMinimum = 1) const;

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

      void push_front(ARG_TYPE newElement);
      void push_back(ARG_TYPE newElement);

      // add another list of elements before head or after tail
      void copy_head(const list_data < TYPE, ARG_TYPE > & l);
      void copy_tail(const list_data < TYPE, ARG_TYPE > & l);
      void copy(const list_data < TYPE, ARG_TYPE > & l);

      // remove all elements
      void remove_all();
      void clear();

      TYPE & front();
      const TYPE & front() const;
      TYPE & back();
      const TYPE & back() const;

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

      void remove_at(typename list_data < TYPE, ARG_TYPE >::node * pnode);
      void remove_at(POSITION position);
      void remove_at(const_iterator it);

      void remove(typename list_data < TYPE, ARG_TYPE >::node * pnode);
      void remove(POSITION position);
      void remove(const_iterator it);
      void remove(ARG_TYPE elem);

      void erase(typename list_data < TYPE, ARG_TYPE >::node * pnode);
      void erase(POSITION position);
      void erase(const_iterator it);
      void erase(ARG_TYPE elem);


      typename list_data < TYPE, ARG_TYPE >::node * detach(typename list_data < TYPE, ARG_TYPE >::node * pnode);
      typename list_data < TYPE, ARG_TYPE >::node * detach(POSITION position);
      typename list_data < TYPE, ARG_TYPE >::node * detach(const_iterator it);

      list_data < TYPE, ARG_TYPE > detach(const_iterator first, const_iterator last);
      list_data < TYPE, ARG_TYPE > slice(const_iterator first, const_iterator last);

      POSITION insert(POSITION position, ARG_TYPE newElement); // same as insert before
      POSITION insert(POSITION position, const_iterator it); // same as insert before
      POSITION insert(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode); // same as insert before

      iterator insert(const_iterator position, ARG_TYPE newElement); // same as insert before
      iterator insert(const_iterator position, const_iterator it); // same as insert before
      iterator insert(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode); // same as insert before
      iterator insert(const_iterator position, list_data < TYPE, ARG_TYPE > & l); // same as insert before


      // inserting before or after a given position
      POSITION insert_before(POSITION position, ARG_TYPE newElement);
      POSITION insert_after(POSITION position, ARG_TYPE newElement);
      POSITION insert_before(POSITION position, const_iterator it);
      POSITION insert_after(POSITION position, const_iterator it);
      POSITION insert_before(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode);
      POSITION insert_after(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode);
      POSITION insert_before(POSITION position, list_data < TYPE, ARG_TYPE > & l);
      POSITION insert_after(POSITION position, list_data < TYPE, ARG_TYPE > & l);

      iterator insert_before(const_iterator position, ARG_TYPE newElement);
      iterator insert_after(const_iterator position, ARG_TYPE newElement);
      iterator insert_before(const_iterator position, const_iterator it);
      iterator insert_after(const_iterator position, const_iterator it);
      iterator insert_before(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode);
      iterator insert_after(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode);
      iterator insert_before(const_iterator position, list_data < TYPE, ARG_TYPE > & l);
      iterator insert_after(const_iterator position, list_data < TYPE, ARG_TYPE > & l);


      iterator splice(const_iterator position, list & l);
      iterator splice(const_iterator position, list & l, const_iterator i);
      iterator splice(const_iterator position, list & l, const_iterator first, const_iterator last);
      iterator splice(const_iterator position, const_iterator i);
      iterator splice(const_iterator position, const_iterator first, const_iterator last);

      void swap(POSITION position1, POSITION position2);

      // helper functions (note: O(n) speed)
      POSITION find(ARG_TYPE searchValue, POSITION startAfter = NULL) const;
         // defaults to starting at the HEAD, return NULL if not found
      POSITION find_index(index nIndex) const;
         // get the 'nIndex'th element (may return NULL)
      index position_index(POSITION pos) const;
         // get the 'nIndex' of the position (may return -1)

      list < TYPE, ARG_TYPE > & operator = (const class list & l);
#ifdef MOVE_SEMANTICS
      list < TYPE, ARG_TYPE > & operator = (class list && l);
#endif

      void dump(dump_context &) const;
      void assert_valid() const;
   };

   /////////////////////////////////////////////////////////////////////////////
   // list<TYPE, ARG_TYPE> inline functions

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_count() const
{
   return this->m_count;
}

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::get_size() const
{
   return this->m_count;
}

template<class TYPE, class ARG_TYPE>
inline ::count list<TYPE, ARG_TYPE>::size() const
{
   return this->m_count;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::empty(::count countMinimum) const
{
   return this->m_count < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return this->m_count >= countMinimum;
}

   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_head()
      { ASSERT(this->m_phead != NULL);
         return this->m_phead->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_head() const
      { ASSERT(this->m_phead != NULL);
         return this->m_phead->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_tail()
      { ASSERT(this->m_ptail != NULL);
         return this->m_ptail->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_tail() const
      { ASSERT(this->m_ptail != NULL);
         return this->m_ptail->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline POSITION list<TYPE, ARG_TYPE>::get_head_position() const
      { return (POSITION) this->m_phead; }
   template<class TYPE, class ARG_TYPE>
   inline POSITION list<TYPE, ARG_TYPE>::get_tail_position() const
      { return (POSITION) this->m_ptail; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) // return *position++
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) rPosition;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         rPosition = (POSITION) pnode->m_pnext;
         return pnode->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) const // return *position++
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) rPosition;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         rPosition = (POSITION) pnode->m_pnext;
         return pnode->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) // return *position--
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) rPosition;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         rPosition = (POSITION) pnode->m_pprev;
         return pnode->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) const // return *position--
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) rPosition;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         rPosition = (POSITION) pnode->m_pprev;
         return pnode->m_value; }

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
inline TYPE & list < TYPE, ARG_TYPE >::back()
{
   return get_at(get_tail_position());
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list < TYPE, ARG_TYPE >::back() const
{
   return get_at(get_tail_position());
}

   template<class TYPE, class ARG_TYPE>
   inline TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position)
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) position;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         return pnode->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline const TYPE& list<TYPE, ARG_TYPE>::get_at(POSITION position) const
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) position;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         return pnode->m_value; }
   template<class TYPE, class ARG_TYPE>
   inline void list<TYPE, ARG_TYPE>::set_at(POSITION pos, ARG_TYPE newElement)
      { typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) pos;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode->m_value = newElement; }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list()
   {

   }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list(const class list & l)
   {

      copy(l);

   }

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list(const class list_data < TYPE, ARG_TYPE > & l)
   {

      this->m_count = l.m_count;
      this->m_phead = l.m_phead;
      this->m_ptail = l.m_ptail;

   }


#ifdef MOVE_SEMANTICS

   template<class TYPE, class ARG_TYPE>
   list<TYPE, ARG_TYPE>::list(class list && l)
   {

      this->m_count       = l.m_count;
      this->m_phead       = l.m_phead;
      this->m_ptail       = l.m_ptail;

      l.m_phead     = NULL;
      l.m_ptail     = NULL;

   }

#endif

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_all()
   {

      ASSERT_VALID(this);


      typename list_data < TYPE, ARG_TYPE >::node * pnode;

      typename list_data < TYPE, ARG_TYPE >::node * pnext;

      for (pnode = this->m_phead; pnode != NULL; pnode = pnext)
      {

         pnext = pnode->m_pnext;

         try
         {

            delete pnode;

         }
         catch(...)
         {

         }

      }

      this->m_phead = NULL;

      this->m_ptail = NULL;

      this->m_count = 0;

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
      ASSERT(this->m_count == 0);
   }

   
   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::push_front(ARG_TYPE newElement)
   {

      add_head(newElement);

   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement)
   {

      add_tail(newElement);

   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::copy_head(const list_data < TYPE, ARG_TYPE >  & l)
   {

      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node * pnode = l.m_ptail;

      while(pnode != NULL)
      {
         add_head(pnode->m_value);
         pnode = pnode->m_pprev;
      }

   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::copy_tail(const list_data < TYPE, ARG_TYPE >  & l)
   {

      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node * pnode = l.m_ptail;

      while(pnode != NULL)
      {
         add_tail(pnode->m_value);
         pnode = pnode->m_pnext;
      }

   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::copy(const list_data < TYPE, ARG_TYPE >  & l)
   {

      ASSERT_VALID(this);

      if(this == &l)
         return;

      remove_all();

      typename list_data < TYPE, ARG_TYPE >::node * pnode = l.m_ptail;

      while(pnode != NULL)
      {
         add_head(pnode->m_value);
         pnode = pnode->m_pprev;
      }

   }

   template<class TYPE, class ARG_TYPE>
   TYPE list<TYPE, ARG_TYPE>::remove_head()
   {
      ASSERT_VALID(this);
      ASSERT(this->m_phead != NULL);  // don't call on is_empty list !!!
      ASSERT(__is_valid_address(this->m_phead, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));

      typename list_data < TYPE, ARG_TYPE >::node* pOldNode = this->m_phead;
      TYPE returnValue = pOldNode->m_value;

      this->m_phead = pOldNode->m_pnext;
      if (this->m_phead != NULL)
         this->m_phead->m_pprev = NULL;
      else
         this->m_ptail = NULL;
      delete pOldNode;

      this->m_count--;

      return returnValue;
   }

   template<class TYPE, class ARG_TYPE>
   TYPE list<TYPE, ARG_TYPE>::remove_tail()
   {
      ASSERT_VALID(this);
      ASSERT(this->m_ptail != NULL);  // don't call on is_empty list !!!
      ASSERT(__is_valid_address(this->m_ptail, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));

      typename list_data < TYPE, ARG_TYPE >::node* pOldNode = this->m_ptail;
      TYPE returnValue = pOldNode->m_value;

      this->m_ptail = pOldNode->m_pprev;
      if (this->m_ptail != NULL)
         this->m_ptail->m_pnext = NULL;
      else
         this->m_phead = NULL;
      this->m_count--;
      delete pOldNode;
      return returnValue;
   }


   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert(POSITION position, ARG_TYPE newElement) // same as insert before
   {

      return insert_before(position, newElement);

   }


   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert(POSITION position, const_iterator it) // same as insert before
   {

      return insert_before(position, it);

   }


   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode) // same as insert before
   {

      return insert_before(position, pnode);

   }


   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert(const_iterator position, ARG_TYPE newElement) // same as insert before
   {

      return insert_before(position, newElement);

   }


   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert(const_iterator position, const_iterator it) // same as insert before
   {

      return insert_before(position, it);

   }


   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode) // same as insert before
   {

      return insert_before(position, pnode);

   }


   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert(const_iterator position, list_data < TYPE, ARG_TYPE > & l) // same as insert before
   {

      return insert_before(position, l);

   }


   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_before(const_iterator position, ARG_TYPE newElement)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_before(position.m_pos, newElement), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_after(const_iterator position, ARG_TYPE newElement)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_after(position.m_pos, newElement), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_before(const_iterator position, const_iterator it)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_before(position.m_pos, it), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_after(const_iterator position, const_iterator it)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_after(position.m_pos, it), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_before(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_before(position.m_pos, pnode), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_after(const_iterator position, typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_after(position.m_pos, pnode), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_before(const_iterator position, list_data < TYPE, ARG_TYPE >  & l)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_before(position.m_pos, l), this);
   }

   template<class TYPE, class ARG_TYPE>
   typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > :: insert_after(const_iterator position, list_data < TYPE, ARG_TYPE >  & l)
   {
      ASSERT(this == position.m_plist);
      return iterator(insert_after(position.m_pos, l), this);
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert_before(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {

      list_data < TYPE, ARG_TYPE > l;

      list_data < TYPE, ARG_TYPE >::from(l, pnode);

      return insert_before(position, l);

   }

   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert_after(POSITION position, typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {

      list_data < TYPE, ARG_TYPE > l;

      list_data < TYPE, ARG_TYPE >::from(l, pnode);

      return insert_before(position, l);

   }

   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert_before(POSITION position, list_data < TYPE, ARG_TYPE > & l)
   {

      if(l.m_count <= 0)
         return position;

      this->m_count += l.m_count;

      typename list_data < TYPE, ARG_TYPE >::node * pnode = (typename list_data < TYPE, ARG_TYPE >::node *) position;

      if(pnode != NULL)
      {

         if(pnode->m_pprev != NULL)
         {

            pnode->m_pprev->m_pnext = l.m_phead;

         }

         l.m_phead->m_pprev = pnode->m_pprev;

         pnode->m_pprev = l.m_ptail;

         if(pnode == this->m_phead)
         {

            this->m_phead = l.m_phead;

            this->m_phead->m_pprev = NULL;

         }

      }
      else
      {

         l.m_phead->m_pprev = this->m_ptail;

         this->m_ptail = l.m_phead;

         if(this->m_phead == NULL)
         {

            this->m_phead = l.m_phead;

         }

      }

      l.m_ptail->m_pnext = pnode;

      return (POSITION) l.m_phead;

   }


   template<class TYPE, class ARG_TYPE>
   POSITION list < TYPE, ARG_TYPE > :: insert_after(POSITION position, list_data < TYPE, ARG_TYPE > & l)
   {

      if(l.m_count <= 0)
         return position;

      this->m_count += l.m_count;

      typename list_data < TYPE, ARG_TYPE >::node * pnode = (typename list_data < TYPE, ARG_TYPE >::node *) position;

      if(pnode != NULL)
      {

         if(pnode->m_pnext != NULL)
         {

            pnode->m_pnext->m_pprev = l.m_ptail;

         }

         l.m_ptail->m_pnext = pnode->m_pnext;

         pnode->m_pnext = l.m_phead;

         if(pnode == this->m_ptail)
         {

            this->m_ptail = l.m_ptail;

            this->m_ptail->m_pnext = NULL;

         }

      }
      else
      {

         l.m_phead->m_pnext = this->m_phead;

         this->m_phead = l.m_ptail;

         if(this->m_ptail == NULL)
         {

            this->m_ptail = l.m_ptail;

         }

      }

      l.m_phead->m_pprev = pnode;

      return (POSITION) l.m_phead;

   }




   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_before(POSITION position, const_iterator it)
   {

      return insert_before(position, (typename list_data < TYPE, ARG_TYPE >::node *) it.m_pos);

   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::insert_after(POSITION position, const_iterator it)
   {

      return insert_after(position, (typename list_data < TYPE, ARG_TYPE >::node *) it.m_pos);

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
            typename list_data < TYPE, ARG_TYPE >::node * pnode = (typename list_data < TYPE, ARG_TYPE >::node *) position2;
            if(pnode != this->m_phead)
            {
               if(this->m_ptail == pnode)
               {
                  this->m_ptail = pnode->m_pprev;
               }
               if(pnode->m_pprev != NULL)
               {
                  pnode->m_pprev->m_pnext = pnode->m_pnext;
               }
               if(pnode->m_pnext != NULL)
               {
                  pnode->m_pnext->m_pprev = pnode->m_pprev;
               }
               pnode->m_pprev = NULL;
               pnode->m_pnext = this->m_phead;
               this->m_phead = pnode;
            }
         }
      }
      else if(position2 == NULL)
      {
         typename list_data < TYPE, ARG_TYPE >::node * pnode = (typename list_data < TYPE, ARG_TYPE >::node *) position1;
         if(pnode != this->m_ptail)
         {
            if(this->m_phead == pnode)
            {
               this->m_phead = pnode->m_pnext;
            }
            if(pnode->m_pnext != NULL)
            {
               pnode->m_pprev->m_pprev = pnode->m_pprev;
            }
            if(pnode->m_pnext != NULL)
            {
               pnode->m_pprev->m_pnext = pnode->m_pnext;
            }
            pnode->m_pnext = NULL;
            pnode->m_pprev = this->m_ptail;
            this->m_ptail = pnode;
         }
      }
      else
      {
         typename list_data < TYPE, ARG_TYPE >::node * pnode1 = (typename list_data < TYPE, ARG_TYPE >::node *) position1;
         typename list_data < TYPE, ARG_TYPE >::node * pnode2 = (typename list_data < TYPE, ARG_TYPE >::node *) position2;
         typename list_data < TYPE, ARG_TYPE >::node * pnodeSwapPrev = pnode1->m_pprev;
         typename list_data < TYPE, ARG_TYPE >::node * pnodeSwapNext = pnode1->m_pnext;
         if(pnode1->m_pprev != NULL)
         {
            pnode1->m_pprev->m_pnext = pnode2;
         }
         if(pnode1->m_pnext != NULL)
         {
            pnode1->m_pnext->m_pprev = pnode2;
         }
         if(pnode2->m_pprev != NULL)
         {
            pnode2->m_pprev->m_pnext = pnode1;
         }
         if(pnode2->m_pnext != NULL)
         {
            pnode2->m_pnext->m_pprev = pnode1;
         }
         pnode1->m_pprev = pnode2->m_pprev;
         pnode1->m_pnext = pnode2->m_pnext;
         pnode2->m_pprev = pnodeSwapPrev;
         pnode2->m_pnext = pnodeSwapNext;
         if(pnode1 == this->m_phead)
         {
            this->m_phead = pnode2;
         }
         if(pnode1 == this->m_ptail)
         {
            this->m_ptail = pnode2;
         }
         if(pnode2 == this->m_phead)
         {
            this->m_phead = pnode1;
         }
         if(pnode2 == this->m_ptail)
         {
            this->m_ptail = pnode1;
         }
      }


   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::erase(typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {
      this->remove(pnode);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::erase(ARG_TYPE elem)
   {
      this->remove(elem);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::erase(POSITION pos)
   {
      this->remove(pos);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::erase(const_iterator it)
   {
      this->remove(it);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove(POSITION pos)
   {
      this->remove_at(pos);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove(const_iterator it)
   {
      ASSERT(this == it.m_plist);
      this->remove_at(it);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove(typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {
      this->remove_at(pnode);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove(ARG_TYPE elem)
   {
      remove(find(elem));
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_at(POSITION pos)
   {
      this->remove_at((typename list_data < TYPE, ARG_TYPE >::node *) pos);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_at(const_iterator it)
   {
      ASSERT(this == it.m_plist);
      this->remove_at(it.m_pos);
   }

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::remove_at(typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {

      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node * pOldNode = detach(pnode);

      ASSERT(__is_valid_address(pOldNode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));

      delete pOldNode;

   }

   template < class TYPE, class ARG_TYPE >
   typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(POSITION position)
   {
      return detach((typename list_data < TYPE, ARG_TYPE >::node *) position);
   }

   template<class TYPE, class ARG_TYPE >
   typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(const_iterator it)
   {
      return detach(it.m_pos);
   }

   template < class TYPE, class ARG_TYPE >
   typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(typename list_data < TYPE, ARG_TYPE >::node * pnode)
   {

      ASSERT_VALID(this);

      if(pnode == NULL)
         return NULL;

      if(pnode == this->m_phead)
      {
         this->m_phead = pnode->m_pnext;
      }

      if(pnode->m_pprev != NULL)
      {
         ASSERT(__is_valid_address(pnode->m_pprev, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode->m_pprev->m_pnext = pnode->m_pnext;
      }

      if(pnode == this->m_ptail)
      {
         this->m_ptail = pnode->m_pprev;
      }

      if(pnode->m_pnext != NULL)
      {
         ASSERT(__is_valid_address(pnode->m_pnext, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode->m_pnext->m_pprev = pnode->m_pprev;
      }

      pnode->m_pprev = NULL;

      pnode->m_pnext = NULL;

      this->m_count--;

      return pnode;

   }

   template < class TYPE, class ARG_TYPE >
   list_data < TYPE, ARG_TYPE > list<TYPE, ARG_TYPE>::slice(const_iterator first, const_iterator last)
   {

      return detach(first, last);

   }

   template < class TYPE, class ARG_TYPE >
   list_data < TYPE, ARG_TYPE > list<TYPE, ARG_TYPE>::detach(const_iterator first, const_iterator last)
   {

      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node * pnodeFirst = (typename list_data < TYPE, ARG_TYPE >::node *) first.m_pos;

      typename list_data < TYPE, ARG_TYPE >::node * pnodeLast = (typename list_data < TYPE, ARG_TYPE >::node *) last.m_pos;

      if(pnodeLast != NULL)
      {

         if (pnodeLast == this->m_ptail)
         {
            this->m_ptail = pnodeLast->m_pprev;
         }
         else
         {
            ASSERT(__is_valid_address(pnodeLast->m_pnext, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
            pnodeLast->m_pnext->m_pprev = pnodeLast->m_pprev;
         }

      }
      else
      {
         this->m_ptail = pnodeFirst->m_pprev;
      }

      if(pnodeFirst == this->m_phead)
      {
         this->m_phead = pnodeFirst->m_pnext;
      }
      else
      {
         ASSERT(__is_valid_address(pnodeFirst->m_pprev, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnodeFirst->m_pprev->m_pnext = pnodeFirst->m_pnext;
      }

      ::count count = 0;

      typename list_data < TYPE, ARG_TYPE >::node * pnode = pnodeFirst;

      typename list_data < TYPE, ARG_TYPE >::node * pprev = NULL;

      while(pnode != pnodeLast)
      {
         pprev = pnode;
         pnode = pnode->m_pnext;
         count++;
      }

      this->m_count -= count;

      list l;

      l.m_phead     = pnodeFirst;
      l.m_ptail     = pprev;
      l.m_count         = count;

      return l;

   }

   template < class TYPE, class ARG_TYPE >
   typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator i)
   {

      return splice(position, *((list *) i.m_plist), i);

   }

   template < class TYPE, class ARG_TYPE >
   typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator first, const_iterator last)
   {

      return splice(position, *((list *) first.m_plist), first, last);

   }

   template < class TYPE, class ARG_TYPE >
   typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, list & l)
   {

      return insert_before(position, l);

   }

   template < class TYPE, class ARG_TYPE >
   typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, list & l, const_iterator i)
   {

      UNREFERENCED_PARAMETER(l);

      return insert_before(position, ((list *) i.m_plist)->detach(i));

   }

   template < class TYPE, class ARG_TYPE >
   typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, list & l, const_iterator first, const_iterator last)
   {

      UNREFERENCED_PARAMETER(l);

      return insert_before(position, ((list *) first.m_plist)->detach(first, last));

   }


   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::find_index(index nIndex) const
   {
      ASSERT_VALID(this);

      if (nIndex >= this->m_count || nIndex < 0)
         return NULL;  // went too far

      typename list_data < TYPE, ARG_TYPE >::node* pnode = this->m_phead;
      while (nIndex--)
      {
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode = pnode->m_pnext;
      }
      return (POSITION) pnode;
   }

   template<class TYPE, class ARG_TYPE>
   index list<TYPE, ARG_TYPE>::position_index(POSITION pos) const
   {
      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node* pnode = this->m_phead;
      index i = 0;
      while(pnode != NULL)
      {
         if((typename list_data < TYPE, ARG_TYPE >::node *) pos == pnode)
            return i;
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode = pnode->m_pnext;
         i++;
      }
      return -1;
   }

   template<class TYPE, class ARG_TYPE>
   POSITION list<TYPE, ARG_TYPE>::find(ARG_TYPE searchValue, POSITION startAfter) const
   {
      ASSERT_VALID(this);

      typename list_data < TYPE, ARG_TYPE >::node* pnode = (typename list_data < TYPE, ARG_TYPE >::node*) startAfter;
      if (pnode == NULL)
      {
         pnode = this->m_phead;  // start at head
      }
      else
      {
         ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         pnode = pnode->m_pnext;  // start after the one specified
      }

      for (; pnode != NULL; pnode = pnode->m_pnext)
         if (::comparison::equals_type_arg_type < TYPE, ARG_TYPE > ::CompareElements(&pnode->m_value, searchValue))
            return (POSITION)pnode;
      return NULL;
   }
   /*

   template<class TYPE, class ARG_TYPE>
   void list<TYPE, ARG_TYPE>::Serialize(CArchive& ar)
   {
      ASSERT_VALID(this);

      object::Serialize(ar);

      if (ar.IsStoring())
      {
         ar.WriteCount(this->m_count);
         for (typename list_data < TYPE, ARG_TYPE >::node* pnode = this->m_phead; pnode != NULL; pnode = pnode->m_pnext)
         {
            ASSERT(__is_valid_address(pnode, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
            TYPE* pData;
            //
            // in some cases the & operator might be overloaded, and we cannot use it to obtain
            //the address of a given object.  We then use the following trick to get the address
            //
            pData = reinterpret_cast< TYPE* >( &reinterpret_cast< int32_t& >( static_cast< TYPE& >( pnode->m_value ) ) );
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
      object::dump(dumpcontext);

      dumpcontext << "with " << this->m_count << " elements";
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
      object::assert_valid();

      if (this->m_count == 0)
      {
         // is_empty list
         ASSERT(this->m_phead == NULL);
         ASSERT(this->m_ptail == NULL);
      }
      else
      {
         // non-is_empty list
         ASSERT(__is_valid_address(this->m_phead, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
         ASSERT(__is_valid_address(this->m_ptail, sizeof(typename list_data < TYPE, ARG_TYPE >::node)));
      }
   }

   template<class TYPE, class ARG_TYPE>
   list < TYPE, ARG_TYPE > &
   list<TYPE, ARG_TYPE>::operator = (const class list & l)
   {

      if(&l != this)
      {

         copy(l);

      }

      return *this;

   }


#ifdef MOVE_SEMANTICS

   template<class TYPE, class ARG_TYPE>
   list < TYPE, ARG_TYPE > &
   list<TYPE, ARG_TYPE>::operator = (class list && l)
   {

      if(&l != this)
      {

         this->m_count        = l.m_count;
         this->m_phead    = l.m_phead;
         this->m_ptail    = l.m_ptail;

      }

      return *this;

   }

#endif
