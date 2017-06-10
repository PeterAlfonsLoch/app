#pragma once


template<class TYPE, class ARG_TYPE = const TYPE & >
class list;

template<class TYPE, class ARG_TYPE = const TYPE & >
class list_data :
   virtual public ::object
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


   class iterator
   {
   public:


      node *         m_pnode;
      list_data *    m_plist;

      iterator()
      {
         m_pnode = 0;
         m_plist = NULL;
      }

      iterator(POSITION i, list_data * plist)
      {
         m_pnode = (node *)i;
         m_plist = plist;
      }

      iterator(const iterator & it)
      {
         operator = (it);
      }

      TYPE & operator * ()
      {
         return m_pnode->m_value;
      }

      const TYPE & operator * () const
      {
         return m_pnode->m_value;
      }

      iterator & operator = (const iterator & it)
      {
         if (this != &it)
         {
            m_pnode = it.m_pnode;
            m_plist = it.m_plist;
         }
         return *this;
      }

      bool operator == (const iterator & it)
      {
         return m_pnode == it.m_pnode;
      }

      bool operator != (const iterator & it)
      {
         return !operator==(it);
      }

      iterator operator ++ (int)
      {

         if (m_pnode == NULL || m_pnode == (node *) m_plist->get_tail_position())
            return *this;

         iterator i(*this);

         m_pnode = m_pnode->m_pnext;

         return i;

      }

      iterator & operator ++ ()
      {

         if (m_pnode == NULL)
            return *this;

         if (m_pnode == (const node *)m_plist->get_tail_position())
         {
            m_pnode = NULL;
            return *this;
         }

         m_pnode = m_pnode->m_pnext;

         return *this;

      }

      iterator & operator +(int32_t i)
      {

         while (m_pnode != NULL && m_pnode != (node *)m_plist->get_tail_position() && i > 0)
         {

            i--;
            m_pnode = m_pnode->m_pnext;

         }

         return *this;

      }

      iterator operator -- (int)
      {

         if (m_pnode == NULL || m_pnode == (node *)m_plist->get_head_position())
            return *this;

         iterator it(*this);

         m_pnode = m_pnode->m_pprev;

         return it;

      }

      iterator & operator -- ()
      {

         if (m_pnode == NULL || m_pnode == (node *)m_plist->get_head_position())
            return *this;

         m_pnode = m_pnode->m_pprev;

         return *this;

      }

      iterator & operator -(int32_t i)
      {

         while (m_pnode != NULL && m_pnode != (node *)m_plist->get_tail_position() && i > 0)
         {
            i--;
            m_pnode = m_pnode->m_pprev;
         }

         return *this;

      }


      ::count operator -(const iterator & i) const
      {

         node * pnode = m_pnode;

         ::count c = 0;

         while (pnode != NULL)
         {
            
            if (pnode == i.m_pnode)
            {

               return c;

            }
            
            c++;

            pnode = pnode->m_pprev;

         }

         return -1;

      }

   };


   class const_iterator
   {
   public:


      const node *          m_pnode;
      const list_data *     m_plist;

      const_iterator()
      {
         m_pnode = 0;
         m_plist = NULL;
      }

      const_iterator(POSITION i, const list_data * plist)
      {
         m_pnode = (node *)i;
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
         return m_pnode->m_value;
      }

      const TYPE & operator * () const
      {
         return m_pnode->m_value;
      }

      const_iterator & operator = (const const_iterator & it)
      {
         if (this != &it)
         {
            m_pnode = it.m_pnode;
            m_plist = it.m_plist;
         }
         return *this;
      }

      const_iterator & operator = (const iterator & it)
      {
         m_pnode = it.m_pnode;
         m_plist = it.m_plist;
         return *this;
      }

      bool operator == (const const_iterator & it)
      {
         return m_pnode == it.m_pnode;
      }

      bool operator != (const const_iterator & it)
      {
         return !operator==(it);
      }

      const_iterator & operator ++()
      {

         if (m_pnode == NULL)
            return *this;

         if (m_pnode == (const node *)m_plist->get_tail_position())
         {
            m_pnode = NULL;
            return *this;
         }

         m_pnode = m_pnode->m_pnext;

         return *this;

      }

      const_iterator operator ++ (int)
      {

         if (m_pnode == NULL || (const node *)m_pnode ==(const node *) m_plist->get_tail_position())
            return *this;

         const_iterator i(*this);

         m_pnode = m_pnode->m_pnext;

         return i;

      }
      const_iterator & operator +(int32_t i)
      {

         while (m_pnode != NULL && m_pnode != (const node *)m_plist->get_tail_position() && i > 0)
         {

            i--;
            m_pnode = m_pnode->m_pnext;

         }

         return *this;

      }

      const_iterator & operator --()
      {

         if (m_pnode == NULL || m_pnode == (const node *)m_plist->get_head_position())
            return *this;

         m_pnode = m_pnode->m_pprev;

         return *this;

      }



      const_iterator operator -- (int)
      {

         if (m_pnode == NULL || m_pnode == (const node *)m_plist->get_head_position())
            return *this;

         const_iterator it(*this);

         m_pnode = m_pnode->m_pprev;

         return it;

      }


      const_iterator & operator -(int32_t i)
      {

         while (m_pnode != NULL && m_pnode != (const node *)m_plist->get_head_position() && i > 0)
         {
            i--;
            m_pnode = m_pnode->m_pprev;
         }

         return *this;

      }

      ::count operator -(const const_iterator & i) const
      {

         node * pnode = m_pnode;

         ::count c = 0;

         while (pnode != NULL)
         {

            if (pnode == i.m_pnode)
            {

               return c;

            }

            c++;

            pnode = pnode->m_pprev;

         }

         return -1;

      }

   };


   iterator lower_bound()
   {
      return iterator(NULL, this);
   }


   iterator begin()
   {
      return iterator(get_head_position(), this);
   }


   iterator end()
   {
      return iterator(NULL, this);
   }


   iterator upper_bound()
   {
      return iterator(get_tail_position(), this);
   }

   const_iterator lower_bound() const
   {
      return const_iterator(NULL, this);
   }


   const_iterator begin() const
   {
      return const_iterator(get_head_position(), this);
   }


   const_iterator end() const
   {
      return const_iterator(NULL, this);
   }

   const_iterator upper_bound() const
   {
      return const_iterator(get_tail_position(), this);
   }



   node *         m_phead;
   node *         m_ptail;
   ::count        m_count;

   inline list_data();
   inline list_data(const class list_data < TYPE, ARG_TYPE >  & l);
   inline list_data(const class list < TYPE, ARG_TYPE > & l);

   inline static void from(list_data < TYPE, ARG_TYPE >  & l, node * p);
   inline static list_data < TYPE, ARG_TYPE >  from(node * p);

   // helper functions (note: O(n) speed)
   // defaults to starting at the HEAD, return NULL if not found
   iterator index_iterator(index nIndex);
   // get the 'nIndex'th element (may return NULL)
   index iterator_index(iterator iterator);
   // get the reverse 'nIndex' of the position (may return -1)
   iterator reverse_index_iterator(int_ptr nIndex);



   const_iterator index_iterator(index nIndex) const
   {
      return ((list_data *)this)->index_iterator(nIndex);
   }

   const_iterator reverse_index_iterator(index nIndex) const
   {
      return ((list_data *)this)->reverse_index_iterator(nIndex);
   }


   index iterator_index(const_iterator it) const
   {
      return ((list_data *)this)->iterator_index(iterator((POSITION)(node *)it.m_pnode, (list_data *) this));
   }


   // getting/modifying an element at a given position
   TYPE& get_at(POSITION position);
   const TYPE& get_at(POSITION position) const;
   void set_at(POSITION pos, ARG_TYPE newElement);

   // iteration
   POSITION get_head_position() const;
   POSITION get_tail_position() const;
   /////////////////////////////////////////////////////////////////////////////
   // slow operations



};

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data()
{

   this->m_count = 0;
   this->m_phead = NULL;
   this->m_ptail = NULL;

}

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data(const class list_data < TYPE, ARG_TYPE >  & l)
{

   this->m_count = l.m_count;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

}


template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data(const class list < TYPE, ARG_TYPE > & l)
{

   this->m_count = l.m_count;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

}

template<class TYPE, class ARG_TYPE>
inline void list_data < TYPE, ARG_TYPE >::from(list_data < TYPE, ARG_TYPE >  & l, node * pnode)
{

   l.m_ptail = NULL;

   l.m_phead = pnode;

   l.m_count = 0;

   if (pnode == NULL)
      return;

   while (true)
   {

      if (pnode->m_pnext == NULL)
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
   public list_data < TYPE, ARG_TYPE >
{
public:



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
   void remove_head();
   void remove_tail();

   TYPE pop_head();
   TYPE pop_tail();

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

   TYPE& get_next(POSITION& rPosition); // return *position++
   const TYPE& get_next(POSITION& rPosition) const; // return *position++
   TYPE& get_previous(POSITION& rPosition); // return *position--
   const TYPE& get_previous(POSITION& rPosition) const; // return *position--


   void remove_at(index i);


   void erase(node * & pnode);
   void erase(POSITION & position);
   void erase(iterator & it);


   typename node * detach(node * pnode);
   typename node * detach(POSITION position);
   typename node * detach(iterator it);

   ::count detach(iterator first, iterator last);

   iterator insert(iterator position, ARG_TYPE newElement);
   iterator insert(iterator position, iterator it);
   iterator insert(iterator position, node * pnode);
   iterator insert(iterator position, list_data < TYPE, ARG_TYPE > & l);
   iterator insert(iterator position, iterator first, iterator last);

   iterator insert_before(iterator position, ARG_TYPE newElement);
   iterator insert_before(iterator position, iterator it);
   iterator insert_before(iterator position, node * pnode);
   iterator insert_before(iterator position, list_data < TYPE, ARG_TYPE > & l);
   iterator insert_before(iterator position, iterator first, iterator last);

   iterator insert_after(iterator position, ARG_TYPE newElement);
   iterator insert_after(iterator position, iterator it);
   iterator insert_after(iterator position, node * pnode);
   iterator insert_after(iterator position, list_data < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, iterator first, iterator last);

   POSITION insert(POSITION position, ARG_TYPE newElement);
   POSITION insert(POSITION position, iterator it);
   POSITION insert(POSITION position, node * pnode);
   POSITION insert(POSITION position, list_data < TYPE, ARG_TYPE > & l);
   POSITION insert(POSITION position, iterator first, iterator last);

   POSITION insert_before(POSITION position, ARG_TYPE newElement);
   POSITION insert_before(POSITION position, iterator it);
   POSITION insert_before(POSITION position, node * pnode);
   POSITION insert_before(POSITION position, list_data < TYPE, ARG_TYPE > & l);
   POSITION insert_before(POSITION position, iterator first, iterator last);

   POSITION insert_after(POSITION position, ARG_TYPE newElement);
   POSITION insert_after(POSITION position, iterator it);
   POSITION insert_after(POSITION position, node * pnode);
   POSITION insert_after(POSITION position, list_data < TYPE, ARG_TYPE > & l);
   POSITION insert_after(POSITION position, iterator first, iterator last);


   void splice(iterator position, list & l);
   void splice(iterator position, list & l, iterator i);
   void splice(iterator position, list & l, iterator first, iterator last);

   void swap(POSITION position1, POSITION position2);


   list < TYPE, ARG_TYPE > & operator = (const class list & l);
#ifdef MOVE_SEMANTICS
   list < TYPE, ARG_TYPE > & operator = (class list && l);
#endif

   void dump(dump_context &) const;
   void assert_valid() const;

};

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
{
   ASSERT(this->m_phead != NULL);
   return this->m_phead->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::get_head() const
{
   ASSERT(this->m_phead != NULL);
   return this->m_phead->m_value;
}
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::get_tail()
{
   ASSERT(this->m_ptail != NULL);
   return this->m_ptail->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::get_tail() const
{
   ASSERT(this->m_ptail != NULL);
   return this->m_ptail->m_value;
}
template<class TYPE, class ARG_TYPE>
inline POSITION list_data<TYPE, ARG_TYPE>::get_head_position() const
{
   return (POSITION) this->m_phead;
}
template<class TYPE, class ARG_TYPE>
inline POSITION list_data<TYPE, ARG_TYPE>::get_tail_position() const
{
   return (POSITION) this->m_ptail;
}
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) // return *position++
{
   node* pnode = (node*) rPosition;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   rPosition = (POSITION)pnode->m_pnext;
   return pnode->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::get_next(POSITION& rPosition) const // return *position++
{
   node* pnode = (node*) rPosition;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   rPosition = (POSITION)pnode->m_pnext;
   return pnode->m_value;
}
template<class TYPE, class ARG_TYPE>
inline TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) // return *position--
{
   node* pnode = (node*) rPosition;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   rPosition = (POSITION)pnode->m_pprev;
   return pnode->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list<TYPE, ARG_TYPE>::get_previous(POSITION& rPosition) const // return *position--
{
   node* pnode = (node*) rPosition;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   rPosition = (POSITION)pnode->m_pprev;
   return pnode->m_value;
}

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
   return erase(begin());
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
inline TYPE& list_data<TYPE, ARG_TYPE>::get_at(POSITION position)
{
   node* pnode = (node*) position;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   return pnode->m_value;
}
template<class TYPE, class ARG_TYPE>
inline const TYPE& list_data<TYPE, ARG_TYPE>::get_at(POSITION position) const
{
   node* pnode = (node*) position;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   return pnode->m_value;
}
template<class TYPE, class ARG_TYPE>
inline void list_data<TYPE, ARG_TYPE>::set_at(POSITION pos, ARG_TYPE newElement)
{
   node* pnode = (node*) pos;
   ASSERT(__is_valid_address(pnode, sizeof(node)));
   pnode->m_value = newElement;
}

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

   this->m_count = l.m_count;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

   l.m_phead = NULL;
   l.m_ptail = NULL;

}

#endif

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_all()
{

   ASSERT_VALID(this);


   node * pnode;

   node * pnext;

   for (pnode = this->m_phead; pnode != NULL; pnode = pnext)
   {

      pnext = pnode->m_pnext;

      try
      {

         delete pnode;

      }
      catch (...)
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

   node * pnode = l.m_ptail;

   while (pnode != NULL)
   {
      add_head(pnode->m_value);
      pnode = pnode->m_pprev;
   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_tail(const list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   node * pnode = l.m_ptail;

   while (pnode != NULL)
   {
      add_tail(pnode->m_value);
      pnode = pnode->m_pnext;
   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy(const list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   if (this == &l)
      return;

   remove_all();

   node * pnode = l.m_ptail;

   while (pnode != NULL)
   {
      add_head(pnode->m_value);
      pnode = pnode->m_pprev;
   }

}

template<class TYPE, class ARG_TYPE>
TYPE list<TYPE, ARG_TYPE>::pop_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_phead != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_phead, sizeof(node)));

   node* pOldNode = this->m_phead;
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
TYPE list<TYPE, ARG_TYPE>::pop_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_ptail != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));

   node* pOldNode = this->m_ptail;
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
void list<TYPE, ARG_TYPE>::remove_head()
{
   ASSERT_VALID(this);
   ASSERT(this->m_phead != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_phead, sizeof(node)));

   node* pOldNode = this->m_phead;

   this->m_phead = pOldNode->m_pnext;
   if (this->m_phead != NULL)
      this->m_phead->m_pprev = NULL;
   else
      this->m_ptail = NULL;
   delete pOldNode;

   this->m_count--;

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_tail()
{
   ASSERT_VALID(this);
   ASSERT(this->m_ptail != NULL);  // don't call on is_empty list !!!
   ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));

   node* pOldNode = this->m_ptail;

   this->m_ptail = pOldNode->m_pprev;
   if (this->m_ptail != NULL)
      this->m_ptail->m_pnext = NULL;
   else
      this->m_phead = NULL;
   this->m_count--;
   delete pOldNode;
}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, ARG_TYPE newElement) // same as insert before
{

   ASSERT(this == i.m_plist);

   return insert_before(i, newElement);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator it) // same as insert before
{

   ASSERT(this == i.m_plist);

   return insert_before(i, it);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, typename node * pnode)
{

   ASSERT(this == i.m_plist);

   return insert_before(i, pnode);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, list_data < TYPE, ARG_TYPE > & l)
{

   ASSERT(this == i.m_plist);

   return insert_before(i, l);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_plist);

   ASSERT(first.m_plist == last.m_plist);

   return insert_before(i, first, last);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, ARG_TYPE newElement)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_before((POSITION)i.m_pnode, newElement), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator it)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_before((POSITION)i.m_pnode, it), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, node * pnode)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_before((POSITION)i.m_pnode, pnode), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_before((POSITION)i.m_pnode, l), this);

}

template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_plist);

   ASSERT(first.m_plist == last.m_plist);

   return iterator((POSITION)insert_before((POSITION)i.m_pnode, first, last), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, ARG_TYPE newElement)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_after((POSITION)i.m_pnode, newElement), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator it)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_after((POSITION)i.m_pnode, it), this);

}
template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, node * pnode)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_after((POSITION)i.m_pnode, pnode), this);

}
template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT(this == i.m_plist);

   return iterator((POSITION)insert_after((POSITION)i.m_pnode, l), this);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator i, iterator first, iterator last)
{

   ASSERT(this == i.m_plist);

   ASSERT(first.m_plist == last.m_plist);

   return iterator((POSITION)insert_after((POSITION)i.m_pnode, first, last), this);

}


template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert(POSITION position, ARG_TYPE newElement)
{

   return insert_before(position, newElement);

}


template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert(POSITION position, iterator it)
{

   return insert_before(position, it);

}


template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert(POSITION position, node * pnode) // same as insert before
{

   return insert_before(position, pnode);

}

template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_before(POSITION position, node * pnode)
{

   list_data < TYPE, ARG_TYPE > l;

   list_data < TYPE, ARG_TYPE >::from(l, pnode);

   return insert_before(position, l);

}




template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_before(POSITION position, list_data < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   node * pnode = (node *) position;

   if (pnode != NULL)
   {

      if (pnode->m_pprev != NULL)
      {

         pnode->m_pprev->m_pnext = l.m_phead;

      }

      l.m_phead->m_pprev = pnode->m_pprev;

      pnode->m_pprev = l.m_ptail;

      if (pnode == this->m_phead)
      {

         this->m_phead = l.m_phead;

         this->m_phead->m_pprev = NULL;

      }

   }
   else
   {

      l.m_phead->m_pprev = this->m_ptail;

      this->m_ptail = l.m_phead;

      if (this->m_phead == NULL)
      {

         this->m_phead = l.m_phead;

      }

   }

   l.m_ptail->m_pnext = pnode;

   return (POSITION)l.m_phead;

}


template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_before(POSITION position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count < 0)
   {

      return NULL;

   }

   this->m_count += count;

   node * pnode = (node *)position;

   if (pnode != NULL)
   {

      if (pnode->m_pprev != NULL)
      {

         pnode->m_pprev->m_pnext = first.m_pnode;

      }

      first.m_pnode->m_pprev = pnode->m_pprev;

      pnode->m_pprev = last.m_pnode;

      if (pnode == this->m_phead)
      {

         this->m_phead = first.m_pnode;

         this->m_phead->m_pprev = NULL;

      }

   }
   else
   {

      first.m_pnode->m_pprev = this->m_ptail;

      this->m_ptail = first.m_pnode;

      if (this->m_phead == NULL)
      {

         this->m_phead = first.m_pnode;

      }

   }

   last.m_pnode->m_pnext = pnode;

   return (POSITION)first.m_pnode;

}


template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::insert_after(POSITION position, iterator it)
{

   return insert_after(position, (node *)it.m_pnode);

}

template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_after(POSITION position, node * pnode)
{

   list_data < TYPE, ARG_TYPE > l;

   list_data < TYPE, ARG_TYPE >::from(l, pnode);

   return insert_before(position, l);

}



template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_after(POSITION position, list_data < TYPE, ARG_TYPE > & l)
{

   if (l.m_count <= 0)
      return position;

   this->m_count += l.m_count;

   node * pnode = (node *) position;

   if (pnode != NULL)
   {

      if (pnode->m_pnext != NULL)
      {

         pnode->m_pnext->m_pprev = l.m_ptail;

      }

      l.m_ptail->m_pnext = pnode->m_pnext;

      pnode->m_pnext = l.m_phead;

      if (pnode == this->m_ptail)
      {

         this->m_ptail = l.m_ptail;

         this->m_ptail->m_pnext = NULL;

      }

   }
   else
   {

      l.m_phead->m_pnext = this->m_phead;

      this->m_phead = l.m_ptail;

      if (this->m_ptail == NULL)
      {

         this->m_ptail = l.m_ptail;

      }

   }

   l.m_phead->m_pprev = pnode;

   return (POSITION)l.m_phead;

}


template<class TYPE, class ARG_TYPE>
POSITION list < TYPE, ARG_TYPE > ::insert_after(POSITION position, iterator first, iterator last)
{

   ::count count = last - first;

   if (count <= 0)
   {

      return position;

   }

   this->m_count += count;

   node * pnode = (node *)position;

   if (pnode != NULL)
   {

      if (pnode->m_pnext != NULL)
      {

         pnode->m_pnext->m_pprev = last.m_pnode;

      }

      last.m_pnode->m_pnext = pnode->m_pnext;

      pnode->m_pnext = first.m_pnode;

      if (pnode == this->m_ptail)
      {

         this->m_ptail = last.m_pnode;

         this->m_ptail->m_pnext = NULL;

      }

   }
   else
   {

      first.m_pnode->m_pnext = this->m_phead;

      this->m_phead = last.m_pnode;

      if (this->m_ptail == NULL)
      {

         this->m_ptail = last.m_pnode;

      }

   }

   first.m_pnode->m_pprev = pnode;

   return (POSITION)first.m_pnode;

}



template<class TYPE, class ARG_TYPE>
POSITION list<TYPE, ARG_TYPE>::insert_before(POSITION position, iterator it)
{

   return insert_before(position, (node *)it.m_pnode);

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::swap(POSITION position1, POSITION position2)
{
   ASSERT_VALID(this);

   if (position1 == NULL)
   {
      if (position2 == NULL)
      {
         return;
      }
      else
      {
         node * pnode = (node *) position2;
         if (pnode != this->m_phead)
         {
            if (this->m_ptail == pnode)
            {
               this->m_ptail = pnode->m_pprev;
            }
            if (pnode->m_pprev != NULL)
            {
               pnode->m_pprev->m_pnext = pnode->m_pnext;
            }
            if (pnode->m_pnext != NULL)
            {
               pnode->m_pnext->m_pprev = pnode->m_pprev;
            }
            pnode->m_pprev = NULL;
            pnode->m_pnext = this->m_phead;
            this->m_phead = pnode;
         }
      }
   }
   else if (position2 == NULL)
   {
      node * pnode = (node *) position1;
      if (pnode != this->m_ptail)
      {
         if (this->m_phead == pnode)
         {
            this->m_phead = pnode->m_pnext;
         }
         if (pnode->m_pnext != NULL)
         {
            pnode->m_pprev->m_pprev = pnode->m_pprev;
         }
         if (pnode->m_pnext != NULL)
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
      node * pnode1 = (node *) position1;
      node * pnode2 = (node *) position2;
      node * pnodeSwapPrev = pnode1->m_pprev;
      node * pnodeSwapNext = pnode1->m_pnext;
      if (pnode1->m_pprev != NULL)
      {
         pnode1->m_pprev->m_pnext = pnode2;
      }
      if (pnode1->m_pnext != NULL)
      {
         pnode1->m_pnext->m_pprev = pnode2;
      }
      if (pnode2->m_pprev != NULL)
      {
         pnode2->m_pprev->m_pnext = pnode1;
      }
      if (pnode2->m_pnext != NULL)
      {
         pnode2->m_pnext->m_pprev = pnode1;
      }
      pnode1->m_pprev = pnode2->m_pprev;
      pnode1->m_pnext = pnode2->m_pnext;
      pnode2->m_pprev = pnodeSwapPrev;
      pnode2->m_pnext = pnodeSwapNext;
      if (pnode1 == this->m_phead)
      {
         this->m_phead = pnode2;
      }
      if (pnode1 == this->m_ptail)
      {
         this->m_ptail = pnode2;
      }
      if (pnode2 == this->m_phead)
      {
         this->m_phead = pnode1;
      }
      if (pnode2 == this->m_ptail)
      {
         this->m_ptail = pnode1;
      }
   }


}




template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::remove_at(index i)
{

   this->erase(index_iterator(i));

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase(node * &  pnode)
{

   ASSERT_VALID(this);

   auto pnodeNext = pnode->m_pnext;

   node * pnodeOld = detach(pnode);

   ASSERT(__is_valid_address(pnodeOld, sizeof(node)));

   delete pnodeOld;

   pnode = pnodeNext;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase(POSITION & pos)
{
   
   this->erase((node * &)pos);

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::erase(iterator & it)
{
   
   this->erase(it.m_pnode);

}



template < class TYPE, class ARG_TYPE >
typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(POSITION position)
{
   return detach((typename list_data < TYPE, ARG_TYPE >::node *) position);
}

template<class TYPE, class ARG_TYPE >
typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(iterator it)
{
   return detach(it.m_pnode);
}

template < class TYPE, class ARG_TYPE >
typename list_data < TYPE, ARG_TYPE >::node * list<TYPE, ARG_TYPE>::detach(node * pnode)
{

   ASSERT_VALID(this);

   if (pnode == NULL)
      return NULL;

   if (pnode == this->m_phead)
   {
      this->m_phead = pnode->m_pnext;
   }

   if (pnode->m_pprev != NULL)
   {
      ASSERT(__is_valid_address(pnode->m_pprev, sizeof(node)));
      pnode->m_pprev->m_pnext = pnode->m_pnext;
   }

   if (pnode == this->m_ptail)
   {
      this->m_ptail = pnode->m_pprev;
   }

   if (pnode->m_pnext != NULL)
   {
      ASSERT(__is_valid_address(pnode->m_pnext, sizeof(node)));
      pnode->m_pnext->m_pprev = pnode->m_pprev;
   }

   pnode->m_pprev = NULL;

   pnode->m_pnext = NULL;

   this->m_count--;

   return pnode;

}


template < class TYPE, class ARG_TYPE >
::count list<TYPE, ARG_TYPE>::detach(iterator first, iterator last)
{

   ASSERT_VALID(this);

   node * pnodeFirst = (node *) first.m_pnode;

   node * pnodeLast = (node *) last.m_pnode;

   if (pnodeLast != NULL)
   {

      if (pnodeLast == this->m_ptail)
      {
         this->m_ptail = pnodeLast->m_pprev;
      }
      else
      {
         ASSERT(__is_valid_address(pnodeLast->m_pnext, sizeof(node)));
         pnodeLast->m_pnext->m_pprev = pnodeLast->m_pprev;
      }

   }
   else
   {
      this->m_ptail = pnodeFirst->m_pprev;
   }

   if (pnodeFirst == this->m_phead)
   {
      this->m_phead = pnodeFirst->m_pnext;
   }
   else
   {
      ASSERT(__is_valid_address(pnodeFirst->m_pprev, sizeof(node)));
      pnodeFirst->m_pprev->m_pnext = pnodeFirst->m_pnext;
   }

   ::count count = 0;

   node * pnode = pnodeFirst;

   node * pprev = NULL;

   while (pnode != pnodeLast)
   {
      pprev = pnode;
      pnode = pnode->m_pnext;
      count++;
   }

   return count;

}


//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(iterator position, const_iterator i)
//{

//   return splice(position, *((list *) i.m_plist), i);

//}

//template < class TYPE, class ARG_TYPE >
//typename list < TYPE, ARG_TYPE >::iterator list<TYPE, ARG_TYPE>::splice(const_iterator position, const_iterator first, const_iterator last)
//{

//   return splice(position, *((list *) first.m_plist), first, last);

//}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l)
{

   auto first = l.begin();

   auto last = l.end();

   l.detach(first, last);

   insert_before(position, first, last);

}


template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator position, list & l, iterator i)
{

   UNREFERENCED_PARAMETER(l);

   l.detach(i);

   insert_before(position, i);

}

template < class TYPE, class ARG_TYPE >
void list<TYPE, ARG_TYPE>::splice(iterator i, list & l, iterator first, iterator last)
{

   UNREFERENCED_PARAMETER(l);

   l.detach(first, last);

   insert_before(i, first, last);

}


template<class TYPE, class ARG_TYPE>
typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::index_iterator(index index)
{

   ASSERT_VALID(this);

   if (index >= this->m_count || index < 0)
   {

      return end();

   }

   auto pnode = this->m_phead;

   while (index > 0)
   {

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pnext;

      index--;

   }

   return iterator((POSITION) pnode, this);

}


template<class TYPE, class ARG_TYPE>
index list_data<TYPE, ARG_TYPE>::iterator_index(iterator it)
{

   ASSERT_VALID(this);

   auto pnode = this->m_phead;

   index i = 0;

   while (pnode != NULL)
   {

      if (it.m_pnode == pnode)
      {

         return i;

      }

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pnext;

      i++;

   }

   return -1;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data < TYPE, ARG_TYPE >::iterator list_data < TYPE, ARG_TYPE >::reverse_index_iterator(int_ptr index)
{

   ASSERT_VALID(this);

   if (index >= m_count || index < 0)
   {

      return end();

   }

   auto * pnode = m_ptail;

   while (index > 0)
   {

      ASSERT(__is_valid_address(pnode, sizeof(decltype(*pnode))));

      pnode = pnode->m_pprev;

      index--;

   }

   return iterator((POSITION) pnode, this);

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
      for (node* pnode = this->m_phead; pnode != NULL; pnode = pnode->m_pnext)
      {
         ASSERT(__is_valid_address(pnode, sizeof(node)));
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
      ASSERT(__is_valid_address(this->m_phead, sizeof(node)));
      ASSERT(__is_valid_address(this->m_ptail, sizeof(node)));
   }
}

template<class TYPE, class ARG_TYPE>
list < TYPE, ARG_TYPE > &
list<TYPE, ARG_TYPE>::operator = (const class list & l)
{

   if (&l != this)
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

   if (&l != this)
   {

      this->m_count = l.m_count;
      this->m_phead = l.m_phead;
      this->m_ptail = l.m_ptail;

   }

   return *this;

}

#endif








