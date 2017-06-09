#pragma once


template < typename TYPE >
struct list_node
{
public:

   list_node *    m_pnext;
   list_node *    m_pprev;
   TYPE           m_value;

   list_node(const TYPE & t, list_node * pprev, list_node * pnext) : m_value(t), m_pprev(pprev), m_pnext(pnext) { }

};



template < typename LISTTYPE >
class list_iterator
{
public:

   typedef LISTTYPE TYPE;

   list_node < TYPE > *      m_pnode;

   list_iterator()
   {
      m_pnode = NULL;
   }

   list_iterator(list_node < TYPE > * pnode)
   {
      m_pnode = pnode;
   }

   list_iterator(const list_iterator & it)
   {
      operator = (it);
   }

   bool is_null() const
   {

      return m_pnode == NULL;

   }


   bool is_set() const
   {

      return !is_null();

   }

   TYPE * operator -> ()
   {
      return &m_pnode->m_value;
   }

   const TYPE * operator -> () const
   {
      return &m_pnode->m_value;
   }

   list_iterator & operator = (const list_iterator & it)
   {
      m_pnode = it.m_pnode;
      return *this;
   }

   bool operator == (const list_iterator & it)
   {
      return m_pnode == it.m_pnode;
   }

   list_iterator & operator ++()
   {

      m_pnode = m_pnode->m_pnext;

      return *this;

   }

   list_iterator & operator +(int32_t i)
   {

      while (i > 0)
      {

         operator ++();

         i--;

      }

      return *this;

   }

   list_iterator & operator --()
   {

      m_pnode = m_pnode->m_pprev;

      return *this;

   }

   list_iterator & operator -(int32_t i)
   {

      while (i > 0)
      {

         operator --();

         i--;

      }

      return *this;

   }


   bool operator != (const list_iterator & it)
   {

      return !operator==(it);

   }

   bool operator < (const list_iterator & it) const
   {

      return operator!=(it);

   }

   list_iterator operator ++(int)
   {

      list_iterator it = *this;
      operator ++();
      return it;

   }


   list_iterator operator --(int)
   {

      list_iterator it = *this;
      operator --();
      return it;

   }


   TYPE & operator * ()
   {

      return *(operator->());

   }

   const TYPE & operator * () const
   {

      return *(operator->());

   }

};


template < typename LISTTYPE >
class const_list_iterator
{
public:


   typedef LISTTYPE TYPE;

   const list_node < LISTTYPE > *   m_pnode;


   const_list_iterator()
   {

      m_pnode = NULL;

   }

   const_list_iterator(const list_node < LISTTYPE > * pnode)
   {

      m_pnode = pnode;

   }

   const_list_iterator(const list_iterator < LISTTYPE > & it)
   {
      operator = (it);
   }


   const_list_iterator(const const_list_iterator & it)
   {
      operator = (it);
   }


   bool is_null() const
   {

      return m_pnode == NULL;

   }


   bool is_set() const
   {

      return !is_null();

   }



   const TYPE * operator -> ()
   {
      return &m_pnode->m_value;
   }

   const TYPE * operator -> () const
   {
      return &m_pnode->m_value;
   }

   const_list_iterator & operator = (const const_list_iterator & it)
   {
      m_pnode = it.m_pnode;
      return *this;
   }

   bool operator == (const list_iterator < LISTTYPE > & it)
   {
      return m_pnode == it.m_pnode;
   }


   bool operator == (const const_list_iterator & it)
   {
      return m_pnode == it.m_pnode;
   }

   const_list_iterator & operator ++()
   {

      m_pnode = m_pnode->m_pnext;

      return *this;

   }

   const_list_iterator & operator +(int32_t i)
   {

      while (i > 0)
      {

         operator ++();

         i--;

      }

      return *this;

   }

   const_list_iterator & operator --()
   {

      m_pnode = m_pnode->m_pnext--;

      return *this;

   }

   const_list_iterator & operator -(int32_t i)
   {

      while (i > 0)
      {

         operator --();

         i--;

      }

      return *this;

   }


   bool operator != (const const_list_iterator & it)
   {

      return !operator==(it);

   }


   bool operator < (const const_list_iterator & it) const
   {

      return operator!=(it);

   }


   const_list_iterator operator ++(int)
   {

      const_list_iterator it = *this;
      operator ++();
      return it;

   }


   const_list_iterator operator --(int)
   {

      const_list_iterator it = *this;
      operator --();
      return it;

   }


   const TYPE & operator * ()
   {

      return *(operator->());

   }

   const TYPE & operator * () const
   {

      return *(operator->());

   }



};

template<class TYPE, class ARG_TYPE = const TYPE & >
class list;

template<class TYPE, class ARG_TYPE = const TYPE & >
class list_data :
   virtual public ::object
{
public:


   typedef TYPE BASE_TYPE;


   typedef list_iterator < TYPE > iterator;

   typedef const_list_iterator < TYPE > const_iterator;

   typedef list_node < TYPE > node;


   node *                        m_phead;
   node *                        m_ptail;
   ::count                       m_nCount;

   inline list_data();
   inline list_data(const class list_data < TYPE, ARG_TYPE >  & l);
   inline list_data(const class list < TYPE, ARG_TYPE > & l);

   inline static void from(list_data < TYPE, ARG_TYPE >  & l, node * p);
   inline static list_data < TYPE, ARG_TYPE >  from(node * p);

   iterator lower_bound();
   iterator begin();
   iterator end();
   iterator upper_bound();

   const_iterator lower_bound() const;
   const_iterator begin() const;
   const_iterator end() const;
   const_iterator upper_bound() const;


   ::count get_count() const;
   ::count get_size() const;
   ::count size() const;

   bool is_empty(::count countMinimum = 1) const;
   bool has_elements(::count countMinimum = 1) const;
   bool empty(::count countMinimum = 1) const;

   TYPE & first();
   const TYPE & first() const;
   TYPE & last();
   const TYPE & last() const;

   TYPE remove_first();
   TYPE remove_last();

   iterator insert_first(ARG_TYPE newElement);
   iterator add(ARG_TYPE newElement);

   void push_front(ARG_TYPE newElement);
   void push_back(ARG_TYPE newElement);


   void remove_at(index i);
   void remove_at(index i, ::count c);

   void erase(iterator & it);
   void erase(iterator & it, iterator last);

   void erase_count(iterator & it, count count);

   node * detach(iterator it);


   void iprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount) + 1;

      }

      if (last < 0)
      {

         last = m_nCount <= 0 ? 0 : m_nCount + (last % m_nCount) + 1;

      }

   }


   void riprepare_first_last(index & first, index & last) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount);

      }

      if (last < 0)
      {

         last = m_nCount <= 0 ? 0 : m_nCount + (last % m_nCount);

      }

   }


   void iprepare_first_count(index & first, ::count & count) const
   {

      if (first < 0)
      {

         first = m_nCount <= 0 ? 0 : m_nCount + (first % m_nCount) + 1;

      }

      if (count < 0)
      {

         count = m_nCount <= 0 ? 0 : (m_nCount + (count % m_nCount) + 1);

      }
      else
      {

         count += first;

      }

   }



   void prepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first = m_phead;

      }

   }

   void prepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first = m_phead;

      }

   }


   void rprepare_first_last(iterator & first, iterator & last) const
   {

      if (first.is_null())
      {

         first = m_ptail;

      }


   }

   void rprepare_first_last(const_iterator & first, const_iterator & last) const
   {

      if (first.is_null())
      {

         first = m_ptail;

      }

   }


   bool valid_iter(iterator current, iterator end) const
   {

      return current != end;

   }

   bool valid_iter(const_iterator current, const_iterator end) const
   {

      return current != end;

   }

   bool rvalid_iter(iterator current, iterator end) const
   {

      return current != end;

   }

   bool rvalid_iter(const_iterator current, const_iterator end) const
   {

      return current != end;

   }


   iterator index_iterator(index i)
   {

      if (i < 0)
      {

         return end();

      }

      auto it = begin();

      while (i > 0 && it != end())
      {

         i--;

         it++;

      }

      return it;

   }

   const_iterator index_iterator(index i) const
   {

      if (i < 0)
      {

         return end();

      }

      auto it = begin();

      while (i > 0 && it != end())
      {

         i--;

         it++;

      }

      return it;

   }

   TYPE & element_at(index i)
   {

      return *index_iterator(i);

   }
   const TYPE & element_at(index i) const
   {

      return *index_iterator(i);

   }

};

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data()
{

   this->m_nCount = 0;
   this->m_phead = NULL;
   this->m_ptail = NULL;

}

template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data(const class list_data < TYPE, ARG_TYPE >  & l)
{

   this->m_nCount = l.m_nCount;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

}


template<class TYPE, class ARG_TYPE>
inline list_data < TYPE, ARG_TYPE >::list_data(const class list < TYPE, ARG_TYPE > & l)
{

   this->m_nCount = l.m_nCount;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

}

template<class TYPE, class ARG_TYPE>
inline void list_data < TYPE, ARG_TYPE >::from(list_data < TYPE, ARG_TYPE >  & l, node * pnode)
{

   l.m_ptail = NULL;

   l.m_phead = pnode;

   l.m_nCount = 0;

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

      l.m_nCount++;

   }

   l.m_nCount++;

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
   public iterable < list_data < TYPE, ARG_TYPE > >
{
public:


   typedef list_data < TYPE, ARG_TYPE > listdata;
   typedef iterable < list_data < TYPE, ARG_TYPE > > Container;
   typedef typename listdata::node node;
   typedef typename Container::iterator iterator;
   typedef typename Container::const_iterator const_iterator;



   list();
   list(const class list & l);
   list(const class list_data < TYPE, ARG_TYPE > & l);
#ifdef MOVE_SEMANTICS
   list(class list && l);
#endif
   virtual ~list();


   // add another list of elements before head or after tail
   void copy_head(const list_data < TYPE, ARG_TYPE > & l);
   void append(const list_data < TYPE, ARG_TYPE > & l);
   void copy(const list_data < TYPE, ARG_TYPE > & l);

   // remove all elements
   void remove_all();
   void clear();


   //void pop_first();

   //void remove(iterator & it);
   //void remove(ARG_TYPE elem);


   //template < typename PRED >
   //bool pred_remove_first(PRED pred);

   //template < typename PRED >
   //const_iterator pred_find_first(PRED pred) const;

   //template < typename PRED >
   //iterator pred_find_first(PRED pred);


   list_data < TYPE, ARG_TYPE > detach(const_iterator first, const_iterator last);
   list_data < TYPE, ARG_TYPE > slice(const_iterator first, const_iterator last);

   iterator insert_at(iterator position, ARG_TYPE newElement);
   iterator insert_at(iterator position, list_data < TYPE, ARG_TYPE > & l);


   iterator insert_before(iterator position, ARG_TYPE newElement);
   iterator insert_after(iterator position, ARG_TYPE newElement);
   iterator insert_before(iterator position, list_data < TYPE, ARG_TYPE > & l);
   iterator insert_after(iterator position, list_data < TYPE, ARG_TYPE > & l);


   template < typename ITERABLE2 >
   void slice(ITERABLE2 & iterable, iterator index, ::count ca = -1);

   template < typename ITERABLE2 >
   void splice(const ITERABLE2 & iterable, iterator index, ::count ca = -1);

   template < typename ITERABLE2, typename ITERABLE3 >
   void splice(const ITERABLE2 & iterable, iterator index, ITERABLE3 & straRemoved, ::count ca = -1);

   void swap(iterator position1, iterator position2);

   // helper functions (note: O(n) speed)
   iterator find(ARG_TYPE searchValue, iterator startAfter = NULL) const;
   // defaults to starting at the HEAD, return NULL if not found
   iterator find_index(index nIndex) const;
   // get the 'nIndex'th element (may return NULL)
   index position_index(iterator pos) const;
   // get the 'nIndex' of the position (may return -1)

   list < TYPE, ARG_TYPE > & operator = (const class list & l);
#ifdef MOVE_SEMANTICS
   list < TYPE, ARG_TYPE > & operator = (class list && l);
#endif

   void dump(dump_context &) const;
   void assert_valid() const;
};

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

   this->m_nCount = l.m_nCount;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

}


#ifdef MOVE_SEMANTICS

template<class TYPE, class ARG_TYPE>
list<TYPE, ARG_TYPE>::list(class list && l)
{

   this->m_nCount = l.m_nCount;
   this->m_phead = l.m_phead;
   this->m_ptail = l.m_ptail;

   l.m_phead = NULL;
   l.m_ptail = NULL;

}

#endif

template<class TYPE, class ARG_TYPE>
inline ::count list_data<TYPE, ARG_TYPE>::get_count() const
{
   return this->m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline ::count list_data<TYPE, ARG_TYPE>::get_size() const
{
   return this->m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline ::count list_data<TYPE, ARG_TYPE>::size() const
{
   return this->m_nCount;
}

template<class TYPE, class ARG_TYPE>
inline bool list_data<TYPE, ARG_TYPE>::is_empty(::count countMinimum) const
{
   return this->m_nCount < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list_data<TYPE, ARG_TYPE>::empty(::count countMinimum) const
{
   return this->m_nCount < countMinimum;
}

template<class TYPE, class ARG_TYPE>
inline bool list_data<TYPE, ARG_TYPE>::has_elements(::count countMinimum) const
{
   return this->m_nCount >= countMinimum;
}



template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::lower_bound()
{

   return NULL;

}

template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::begin()
{

   return this->m_phead;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::end()
{

   return NULL;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::iterator list_data<TYPE, ARG_TYPE>::upper_bound()
{

   return this->m_ptail;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::const_iterator list_data<TYPE, ARG_TYPE>::lower_bound() const
{

   return NULL;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::const_iterator list_data<TYPE, ARG_TYPE>::begin() const
{

   return this->m_phead;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::const_iterator list_data<TYPE, ARG_TYPE>::end() const
{

   return NULL;

}


template<class TYPE, class ARG_TYPE>
inline typename list_data<TYPE, ARG_TYPE>::const_iterator list_data<TYPE, ARG_TYPE>::upper_bound() const
{

   return this->m_ptail;

}




template<class TYPE, class ARG_TYPE>
inline TYPE & list_data < TYPE, ARG_TYPE >::first()
{
   return *begin();
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list_data < TYPE, ARG_TYPE >::first() const
{
   return *begin();
}

//template<class TYPE, class ARG_TYPE>
//inline void list < TYPE, ARG_TYPE >::pop_first()
//{
//   return remove_at(begin());
//}
//
template<class TYPE, class ARG_TYPE>
inline TYPE & list_data < TYPE, ARG_TYPE >::last()
{
   return *upper_bound();
}

template<class TYPE, class ARG_TYPE>
inline const TYPE & list_data < TYPE, ARG_TYPE >::last() const
{
   return *upper_bound();
}



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

   this->m_nCount = 0;

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
   ASSERT(this->m_nCount == 0);
}


template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::push_front(ARG_TYPE newElement)
{

   insert_first(newElement);

}


template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::push_back(ARG_TYPE newElement)
{

   add(newElement);

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::copy_head(const list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   node * pnode = l.m_ptail;

   while (pnode != NULL)
   {
      insert_first(pnode->m_value);
      pnode = pnode->m_pprev;
   }

}

template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::append(const list_data < TYPE, ARG_TYPE >  & l)
{

   ASSERT_VALID(this);

   node * pnode = l.m_ptail;

   while (pnode != NULL)
   {
      add(pnode->m_value);
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
      insert_first(pnode->m_value);
      pnode = pnode->m_pprev;
   }

}

template<class TYPE, class ARG_TYPE>
TYPE list_data<TYPE, ARG_TYPE>::remove_first()
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

   this->m_nCount--;

   return returnValue;
}

template<class TYPE, class ARG_TYPE>
TYPE list_data<TYPE, ARG_TYPE>::remove_last()
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
   this->m_nCount--;
   delete pOldNode;
   return returnValue;
}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_at(iterator position, ARG_TYPE newElement)
{

   return insert_before(position, newElement);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_at(iterator position, list_data < TYPE, ARG_TYPE > & l)
{

   return insert_before(position, l);

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_before(iterator position, list_data < TYPE, ARG_TYPE > & l)
{

   if (l.m_nCount <= 0)
   {

      return position;

   }

   this->m_nCount += l.m_nCount;

   node * pnode = position.m_pnode;

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

   return l.m_phead;

}


template<class TYPE, class ARG_TYPE>
typename list < TYPE, ARG_TYPE >::iterator list < TYPE, ARG_TYPE > ::insert_after(iterator position, list_data < TYPE, ARG_TYPE > & l)
{

   if (l.m_nCount <= 0)
      return position;

   this->m_nCount += l.m_nCount;

   node * pnode = position.m_pnode;

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

   return (iterator)l.m_phead;

}


template<class TYPE, class ARG_TYPE>
void list<TYPE, ARG_TYPE>::swap(iterator position1, iterator position2)
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

         node * pnode = position2.m_pnode;

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

      node * pnode = position1.m_pnode;

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

      node * pnode1 = position1.m_pnode;

      node * pnode2 = position2.m_pnode;

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

//template<class TYPE, class ARG_TYPE>
//void list_data<TYPE, ARG_TYPE>::erase(ARG_TYPE elem)
//{
//
//   this->remove(elem);
//
//}


template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::remove_at(index i)
{

   auto it = index_iterator(i);

   erase(it);

}

template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::remove_at(index i, ::count c)
{

   auto it = index_iterator(i);

   erase_count(it, c);

}

template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::erase(iterator & it)
{


      node * pnode = it.m_pnode;

      it++;

      ASSERT_VALID(this);

      node * pOldNode = detach(pnode);

      ASSERT(__is_valid_address(pOldNode, sizeof(node)));

      delete pOldNode;

}

template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::erase(iterator & it, iterator last)
{

   while (it != last && it != end())
   {

      erase(it);

   }


}

template<class TYPE, class ARG_TYPE>
void list_data<TYPE, ARG_TYPE>::erase_count(iterator & it, count count)
{

   while (count > 0 && it != end())
   {

      erase(it);

      count--;

   }

}



//template<class TYPE, class ARG_TYPE>
//void list<TYPE, ARG_TYPE>::remove(ARG_TYPE elem)
//{
//   
//   remove(find(elem));

//}


//template<class TYPE, class ARG_TYPE>
//template < typename PRED >
//bool list<TYPE, ARG_TYPE>::pred_remove_first(PRED pred)
//{
//
//   return remove(pred_find_first(pred));
//
//}
//
//template<class TYPE, class ARG_TYPE>
//template < typename PRED >
//typename list<TYPE, ARG_TYPE>::const_iterator list<TYPE, ARG_TYPE>::pred_find_first(PRED pred) const
//{
//
//   auto it = this->begin()
//
//      for (; it != this->end(); it++)
//      {
//
//         if (pred(*it))
//         {
//
//            break;
//
//         }
//
//      }
//
//   return it;
//
//}
//
//template<class TYPE, class ARG_TYPE>
//template < typename PRED >
//typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::pred_find_first(PRED pred)
//{
//
//   auto it = this->begin();
//
//   for (; it != this->end(); it++)
//   {
//
//      if (pred(*it))
//      {
//
//         break;
//
//      }
//
//   }
//
//   return it;
//
//}

//template<class TYPE, class ARG_TYPE>
//void list<TYPE, ARG_TYPE>::remove(iterator & it)
//{
//   
//   this->remove_at(it);

//}



template < class TYPE, class ARG_TYPE >
typename list_data < TYPE, ARG_TYPE >::node * list_data<TYPE, ARG_TYPE>::detach(iterator it)
{

   node * pnode = it.m_pnode;

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

   this->m_nCount--;

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

   node * pnodeFirst = (node *)first.m_pnode;

   node * pnodeLast = (node *)last.m_pnode;

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

   this->m_nCount -= count;

   list l;

   l.m_phead = pnodeFirst;

   l.m_ptail = pprev;

   l.m_nCount = count;

   return l;

}


template < class TYPE, class ARG_TYPE >
template < typename ITERABLE >
void list<TYPE, ARG_TYPE> ::splice(const ITERABLE & iterable, iterator iOffset, ::count count)
{

   remove(iOffset, count);

   insert_iter_at(iOffset, iterable);

}



template < class TYPE, class ARG_TYPE >
template < typename ITERABLE2, typename ITERABLE3 >
void list<TYPE, ARG_TYPE> ::splice(const ITERABLE2 & iterable, iterator iOffset, ITERABLE3 & iterableRemoved, ::count count)
{

   slice(iterableRemoved, iOffset, count);

   remove(iOffset, count);

   insert_at(iOffset, iterable);

}



template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::find_index(index nIndex) const
{

   ASSERT_VALID(this);

   if (nIndex >= this->m_nCount || nIndex < 0)
      return NULL;  // went too far

   node* pnode = this->m_phead;
   while (nIndex--)
   {
      ASSERT(__is_valid_address(pnode, sizeof(node)));
      pnode = pnode->m_pnext;
   }
   return (iterator)pnode;
}


template<class TYPE, class ARG_TYPE>
index list<TYPE, ARG_TYPE>::position_index(iterator pos) const
{

   ASSERT_VALID(this);

   node* pnode = this->m_phead;

   index i = 0;

   while (pnode != NULL)
   {

      if (pos.m_pnode == pnode)
      {

         return i;

      }

      pnode = pnode->m_pnext;

      i++;

   }

   return -1;

}


template<class TYPE, class ARG_TYPE>
typename list<TYPE, ARG_TYPE>::iterator list<TYPE, ARG_TYPE>::find(ARG_TYPE searchValue, iterator startAfter) const
{

   ASSERT_VALID(this);

   node * pnode = startAfter.m_pnode;

   if (pnode == NULL)
   {

      pnode = this->m_phead;  // start at head

   }
   else
   {

      ASSERT(__is_valid_address(pnode, sizeof(node)));

      pnode = pnode->m_pnext;  // start after the one specified

   }

   for (; pnode != NULL; pnode = pnode->m_pnext)
   {

      if (EqualElements(pnode->m_value, searchValue))
      {

         return (iterator)pnode;

      }

   }

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
      ar.WriteCount(this->m_nCount);
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

   dumpcontext << "with " << this->m_nCount << " elements";

   if (dumpcontext.GetDepth() > 0)
   {

      const_iterator it = begin();

      while (it != end())
      {

         TYPE temp[1];

         temp[0] = *it;

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

   if (this->m_nCount == 0)
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

      this->m_nCount = l.m_nCount;
      this->m_phead = l.m_phead;
      this->m_ptail = l.m_ptail;

   }

   return *this;

}

#endif








