#pragma once





template <class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, typename COMPARE = ::comparison::less < KEY >, bool m_bMultiKey = false >
class sort_map :
   virtual public ::object
{
public:


   typedef KEY          AXIS_KEY;
   typedef ARG_KEY      AXIS_ARG_KEY;
   typedef VALUE        AXIS_VALUE;
   typedef ARG_VALUE    AXIS_ARG_VALUE;
   typedef COMPARE      AXIS_COMPARE;


   class node :
      public ::pair < KEY,VALUE >
   {
   public:

      node * left;
      node * right;


      node()
      {
         left = NULL;
         right = NULL;
      }

      node(const KEY & element1)
      {
         m_element1 = element1;
         left = NULL;
         right = NULL;
      }

      node(const KEY & element1,const VALUE & element2)
      {
         m_element1 = element1;
         m_element2 = element2;
         left = NULL;
         right = NULL;
      }
      node(const pair < KEY,VALUE > & pair)
      {
         m_element1 = pair.m_element1;
         m_element2 = pair.m_element2;
         left = NULL;
         right = NULL;
      }


      void copy_value(const pair < KEY,VALUE > & key)
      {

         m_element1 = key.m_element1;

         m_element2 = key.m_element2;

      }


      node * min() const
      {
         if(left == NULL)
            return (node *) this;
         return left;
      }


      node * max() const
      {
         if(right == NULL)
            return (node *) this;
         return right;
      }

      ::count children_count() const
      {
         
         ::count c = 0;

         if(left != NULL)
            return left->children_count() + 1;

         if(right != NULL)
            return right->children_count() + 1;

         return c;

      }

      void remove_all()
      {

         if(left != NULL)
         {
            
            left->remove_all();

            delete left;

            left = NULL;

         }

         if(right != NULL)
         {

            right->remove_all();

            delete right;

            right = NULL;

         }

      }

   };



   class iterator
   {
   public:


      node *         m_pnode;
      sort_map *     m_pmap;


      iterator()
      {
         m_pnode  = NULL;
         m_pmap   = NULL;
      }

      iterator(const iterator & iterator)
      {
         m_pnode  = iterator.m_pnode;
         m_pmap   = iterator.m_pmap;
      }

      iterator(node * pnode, sort_map * pmap)
      {
         m_pnode  = pnode;
         m_pmap   = pmap;
      }


      node & operator * ()
      {

         return *m_pnode;

      }


      node * operator -> ()
      {
         return m_pnode;
      }

      node * operator -> () const
      {
         return m_pnode;
      }


      iterator & operator ++ ()
      {
         if(m_pnode != NULL && m_pmap != NULL)
            m_pnode = m_pmap->PGetNextAssoc(m_pnode);
         return *this;
      }

      iterator operator ++ (int32_t)
      {
         if(m_pnode != NULL && m_pmap != NULL)
            m_pnode = m_pmap->PGetNextAssoc(m_pnode);
         return *this;
      }

      bool operator == (const iterator & it) const
      {
         if(this == &it)
            return true;
         if(m_pnode == NULL && it.m_pnode == NULL && it.m_pmap == NULL)
            return true;
         if(m_pmap != it.m_pmap)
            return false;
         return m_pnode == it.m_pnode;
      }

      bool operator != (const iterator & it) const
      {
         return !operator == (it);
      }

      iterator & operator = (const iterator & it)
      {
         if(this != &it)
         {
            m_pmap         = it.m_pmap;
            m_pnode        = it.m_pnode;
         }
         return *this;
      }

   };

   class const_iterator
   {
   public:


      const node *         m_pnode;
      const sort_map *     m_pmap;


      const_iterator()
      {
         m_pnode  = NULL;
         m_pmap   = NULL;
      }

      const_iterator(const iterator & iterator)
      {
         m_pnode  = iterator.m_pnode;
         m_pmap   = iterator.m_pmap;
      }

      const_iterator(const const_iterator & iterator)
      {
         m_pnode  = iterator.m_pnode;
         m_pmap   = iterator.m_pmap;
      }

      const_iterator(const node * pnode, const sort_map * pmap)
      {
         m_pnode  = pnode;
         m_pmap   = pmap;
      }

      const node * operator -> ()
      {
         return m_pnode;
      }

      const node * operator -> () const
      {
         return m_pnode;
      }


      const_iterator & operator ++ ()
      {
         if(m_pnode != NULL && m_pmap != NULL)
            m_pnode = m_pmap->PGetNextAssoc(m_pnode);
         return *this;
      }

      const_iterator operator ++ (int32_t)
      {
         if(m_pnode != NULL && m_pmap != NULL)
            m_pnode = m_pmap->PGetNextAssoc(m_pnode);
         return *this;
      }

      bool operator == (const const_iterator & it) const
      {
         if(this == &it)
            return true;
         if(m_pnode == NULL && it.m_pnode == NULL && it.m_pmap == NULL)
            return true;
         if(m_pmap != it.m_pmap)
            return false;
         return m_pnode == it.m_pnode;
      }

      bool operator != (const const_iterator & it) const
      {
         return !operator == (it);
      }

      const_iterator & operator = (const const_iterator & it)
      {
         if(this != &it)
         {
            m_pmap         = it.m_pmap;
            m_pnode        = it.m_pnode;
         }
         return *this;
      }

      const_iterator & operator = (const iterator & it)
      {
         m_pmap         = it.m_pmap;
         m_pnode        = it.m_pnode;
         return *this;
      }

   };

   node * m_pnode;
   COMPARE m_compare;





   sort_map(::count nBlockSize = 10);
   sort_map(node nodes[], int32_t iCount, ::count nBlockSize = 10);
   virtual ~sort_map();



   void construct(::count nBlockSize = 10);


   void dump(dump_context &) const;
   void assert_valid() const;


   iterator begin()
   {
      return iterator(PGetFirstAssoc(), this);
   }


   iterator end()
   {
      return iterator(NULL, this);
   }

   const_iterator begin() const
   {
      return const_iterator(PGetFirstAssoc(), this);
   }


   const_iterator end() const
   {
      return const_iterator(NULL, this);
   }

   iterator lower_bound (ARG_KEY k);
   const_iterator lower_bound (ARG_KEY k) const;
   iterator upper_bound (ARG_KEY k);
   const_iterator upper_bound (ARG_KEY k) const;

   ::count get_size() const;
   ::count size() const;
   ::count count() const;
   bool is_empty() const;
   bool empty() const;

   // Lookup
   bool Lookup(ARG_KEY key, VALUE& rValue) const;
   const node *PLookup(ARG_KEY key) const;
   node *PLookup(ARG_KEY key);


   VALUE * pget(ARG_KEY key);

   // Operations
   // Lookup and add if not there
   VALUE & operator[](ARG_KEY key);

   // add a new (key, value) node
   void set_at(ARG_KEY key, ARG_VALUE newValue);

   // removing existing (key, ?) node
   ::count remove_key(ARG_KEY key);
   void erase(iterator it);
   ::count erase(const KEY & key);
   void erase ( iterator m_element1, iterator last );
   void remove_all();
   void clear();


   bool remove_node(node * pnode);

   bool delete_node(node * pnode, node * pnodeParent);


   ::count count(const KEY & t) const;
   bool has(const KEY & t) const;
   bool contains(const KEY & t) const;

   // iterating all (key, value) nodes
   POSITION get_start_position() const;

   const node *PGetFirstAssoc() const;
   node *PGetFirstAssoc();

   void get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const;

   const node *PGetNextAssoc(const node * pnode) const;
   node *PGetNextAssoc(const node * pnode);
   const node *PGetPrevAssoc(const node * pnode) const;
   node *PGetPrevAssoc(const node * pnode);

   VALUE get(ARG_KEY argkey, ARG_VALUE valueDefault);

   node * next(const node * pnode);
   const node * next(const node * pnode) const;
   node * prev(const node * pnode);
   const node * prev(const node * pnode) const;


   void set(sort_map & sort_map)
   {
      node * pnode = NULL;
      while(sort_map.next(pnode) != NULL)
      {
         set_at(pnode->m_element1, pnode->m_element2);
      }
   }

   node * parent_node(const node * pnode) const;

   node *   equally_keyed_next_node(const node * pnode) const;
   node *   equally_keyed_prev_node(const node * pnode) const;
   node *   find_node(ARG_KEY key) const;
   node *   rfind_node(ARG_KEY key) const;

   iterator find(ARG_KEY key);
   const_iterator find(ARG_KEY key) const;
   iterator rfind(ARG_KEY key);
   const_iterator rfind(ARG_KEY key) const;

   void    add_pair(ARG_KEY key, ARG_VALUE value);
   void    insert(const pair < KEY, VALUE  > & pair);

   node * min() const
   {
      if(m_pnode == NULL)
         return NULL;
      return m_pnode->min();
   }

   node * max() const
   {
      if(m_pnode == NULL)
         return NULL;
     return m_pnode->max();
   }


   inline bool compare(ARG_KEY a,ARG_KEY b) const
   {
      return m_compare(a,b);
   }

   inline bool is_equal(ARG_KEY a,ARG_KEY b) const
   {
      return !compare(a,b) && !compare(b,a);
   }

   inline bool compare(node a,node b) const
   {
      return compare(a.m_element1,b.m_element1);
   }

   inline bool is_equal(node a,node b) const
   {
      return !compare(a,b) && !compare(b,a);
   }


   ::count get_count() const
   {
      if(m_pnode == NULL)
         return 0;
      else
         return m_pnode->children_count() + 1;
   }

};

/////////////////////////////////////////////////////////////////////////////
// sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey > inline functions



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_size() const
{ 

   return this->get_count(); 

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::count() const
{

   return  this->get_count();

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline ::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::size() const
{

   return  this->get_count();

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::is_empty() const
{

   return m_pnode == NULL; 

}



template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
inline bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::empty() const
{

   return this->is_empty();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::set_at(ARG_KEY key, ARG_VALUE newValue)
{

   add_pair(key, newValue); 

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline POSITION sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_start_position() const
{

   return (m_pnode == 0) ? NULL : BEFORE_START_POSITION; 

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::PGetFirstAssoc() const
{

   return min();

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::PGetFirstAssoc()
{

   return min();

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::construct(::count nBlockSize)
{

   UNREFERENCED_PARAMETER(nBlockSize);

   m_pnode = NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::sort_map(::count nBlockSize)
{

   construct(nBlockSize);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::sort_map(node nodes[], int32_t iCount, ::count nBlockSize)
{

   construct(nBlockSize);

   for(int32_t i = 0; i < iCount; i++)
   {

      set_at(nodes[i].m_element1, nodes[i].m_element2);

   }

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::remove_all()
{

   if(m_pnode == NULL)
      return;

   m_pnode->remove_all();

   delete m_pnode;

   m_pnode = NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
inline void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::clear()
{

   remove_all();

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::~sort_map()
{

   remove_all();

}



template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::Lookup(ARG_KEY key, VALUE& rValue) const
{

   node * passoc = PLookup(key);

   if (passoc == NULL)
      return false;

   rValue = passoc->m_element2;

   return TRUE;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node* sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::PLookup(ARG_KEY key) const
{

   index i;

   if(!find_key(key, i))
      return NULL;

   return m_ptra[i];

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PLookup(ARG_KEY key)
{

   return find_node(key);

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
VALUE * sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::pget(ARG_KEY key)
{

   node * p = PLookup(key);

   if(p == NULL)
      return NULL;

   return &p->m_element2;

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
VALUE& sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::operator[](ARG_KEY key)
{

   ASSERT_VALID(this);

   node * pnode = PLookup(key);

   if(pnode == NULL)
   {

      add_pair(key, VALUE());

      pnode = PLookup(key);

      ASSERT(pnode != NULL);

   }

   return pnode->m_element2;  // return new reference

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::remove_key(ARG_KEY key)
{

   ::count c = 0;

   while(true)
   {

      node * pnode = find_node(key);

      if(pnode == NULL)
         break;

      remove_node(pnode);

   }

   return c;


}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::delete_node(node * pnode,node *pnodeParent)
{

   if(pnodeParent == NULL)
   {

      pnodeParent = parent_node(pnode);

   }

   if(pnodeParent != NULL)
   {

      if(pnodeParent->left == pnode)
      {

         pnodeParent->left = NULL;

      }
      else if(pnodeParent->right == pnode)
      {

         pnodeParent->right = NULL;

      }

      pnodeParent->copy_value(*pnode);

   }


   try
   {

      delete pnode;

   }
   catch(...)
   {

   }

   return true;

}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
bool sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::remove_node(node * pnode)
{

   if(pnode == m_pnode)
   {
      
      delete m_pnode;

      m_pnode = NULL;

      return true;

   }
   
   if(pnode->left != NULL)
   {
      if(pnode->right != NULL)
      {
         node * succ = pnode->right->min();
         pnode->copy_value(*succ);
         return remove_node(succ);
      }
      else
      {
         return delete_node(pnode->left,pnode);
      }
   }
   else if(pnode->right != NULL)
   {
      return delete_node(pnode->right,pnode);
   }
   else
   {

      return delete_node(pnode,NULL);

   }

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::equally_keyed_next_node(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
{

   if(pnode == NULL)
      return NULL;

   node * pnodeSearch = pnode->right;

   while(pnodeSearch != NULL)
   {

      if(compare(*pnode,*pnodeSearch))
      {

         pnodeSearch = pnodeSearch->left;

      }
      else if(compare(*pnodeSearch,*pnode))
      {

         pnodeSearch = pnodeSearch->right;

      }
      else
      {

         break;

      }

   }

   return pnodeSearch;

}




template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator 
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::find(ARG_KEY key)
{

   node * pnode = find_node(key);

   if(pnode == NULL)
      return end();

   return iterator(pnode, this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::find(ARG_KEY key) const
{

   node * pnode = find_node(key);

   if(pnode == NULL)
      return end();

   return const_iterator(pnode,this);

}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::parent_node(const node * pnode) const
{

   node * pnodeParent = NULL;

   node * pnodeSearch = m_pnode;

   while(pnodeSearch != NULL)
   {

      if(compare(*pnode,*pnodeSearch))
      {

         pnodeSearch = pnodeSearch->left;

      }
      else if(compare(*pnodeSearch,*pnode))
      {

         pnodeSearch = pnodeSearch->right;

      }
      else if(pnodeSearch == pnode)
      {

         return pnodeParent;

      }

      pnodeParent = pnodeSearch;

   }

   return NULL;

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::find_node(ARG_KEY key) const
{

   node * pnodeSearch = m_pnode;

   while(pnodeSearch != NULL)
   {

      if(compare(key,pnodeSearch->m_element1))
      {

         pnodeSearch = pnodeSearch->left;

      }
      else if(compare(pnodeSearch->m_element1,key))
      {

         pnodeSearch = pnodeSearch->right;

      }
      else
      {

         // in this ordinary tree, the highest nodes are the m_element1 ones inserted, even for multi key
         break;

      }

   }

   return pnodeSearch;

}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::equally_keyed_prev_node(const node * pnode) const
{

   node * pnodePrevious = NULL;

   node * pnodeSearch = m_pnode;

   while(pnodeSearch != NULL)
   {

      if(compare(*pnode,*pnodeSearch))
      {

         pnodeSearch = pnodeSearch->left;

      }
      else if(compare(*pnodeSearch,*pnode))
      {

         pnodeSearch = pnodeSearch->right;

      }
      else
      {

         if(pnodeSearch == pnode)
            break;

         pnodePrevious = pnodeSearch;

      }

   }

   return pnodePrevious;

}




template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node *
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::rfind_node(ARG_KEY key) const
{

   node * pnodeLast = NULL;

   node * pnodeSearch = m_pnode;

   while(pnodeSearch != NULL)
   {

      if(compare(key,pnodeSearch->m_element1))
      {

         pnodeSearch = pnodeSearch->left;

      }
      else if(compare(pnodeSearch->m_element1,key))
      {

         pnodeSearch = pnodeSearch->right;

      }
      else
      {

         pnodeLast = pnodeSearch;

      }

   }

   return pnodeLast;

}




template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator 
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::lower_bound (ARG_KEY k)
{

   node * pnode = find_node(k);

   if(pnode == NULL)
      return end();
   else
      return iterator(pnode, this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator 
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::lower_bound (ARG_KEY k) const
{

   node * pnode = find_node(k);

   if(pnode == NULL)
      return end();
   else
      return const_iterator(pnode,this);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::iterator
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::upper_bound (ARG_KEY k)
{

   node * pnode = rfind_node(k);

   if(pnode == NULL)
      return end();
   else
      return iterator(pnode,this);


}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::const_iterator 
sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::upper_bound (ARG_KEY k) const
{

   node * pnode = rfind_node(k);

   if(pnode == NULL)
      return end();
   else
      return const_iterator(pnode,this);


}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(const KEY & key)
{

   return remove_key(key) ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(iterator it)
{

   remove_key(it->m_element1);

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
::count sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::count(const KEY & key) const
{

   return this->PLookup(key) != NULL ? 1 : 0;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::has(const KEY & key) const
{

   return this->PLookup(key) != NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
bool sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::contains(const KEY & key) const
{

   return this->PLookup(key) != NULL;

}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::erase(iterator m_element1, iterator last)
{

   if(m_element1.m_pmap != this || last.m_pmap != this)
      return;

   node * pnode = m_element1.m_pnode;

   node * pnodeNext;

   while(pnode != NULL)
   {

      pnodeNext = next(pnode);

      remove_node(pnode);

      if(pnode == last.m_pnode)
         break;

      pnode = pnodeNext;

   }

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::get_next_assoc(POSITION& rNextPosition, KEY& rKey, VALUE& rValue) const
{

   ASSERT_VALID(this);

   ENSURE(m_ptra.get_count() > 0);  // never call on is_empty sort_map

   index iRet = (index) rNextPosition;

   if (iRet == (index) BEFORE_START_POSITION)
   {
      iRet = 1;
   }

   // find next association
   index iNext = iRet + 1;
   if(iNext > m_ptra.get_count())
   {

   }

   rNextPosition  = (POSITION) iNext;

   // fill in return data
   rKey           = m_ptra[iRet - 1]->m_element1;
   rValue         = m_ptra[iRet - 1]->m_element2;

}

template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::next(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
{

   return ((sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey > * ) this)->next(pnode);
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node*
   sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::next(const typename sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::node * pnode) 
{

   if(pnode->right != NULL)
      return pnode->right->min();

   node * pnodeNext = NULL;

   if(m_bMultiKey)
   {

      pnodeNext = equally_keyed_next_node(pnode);

      if(pnodeNext != NULL)
         return pnodeNext;

   }

   node * pnodeRoot = m_pnode;

   while(pnodeRoot != NULL)
   {

      if(compare(*pnode, *pnodeRoot))
      {

         pnodeNext = pnodeRoot;

         pnodeRoot = pnodeRoot->left;

      }
      else if(compare(*pnodeRoot,*pnode))
      {

         pnodeRoot = pnodeRoot->right;

      }
      else
      {

         break;

      }

   }

   return pnodeNext;

}

template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::prev(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode) const
{

   return ((sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey > *) this)->prev(pnode);
}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::prev(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node * pnode)
{

   if(pnode->right != NULL)
      return pnode->left->max();

   node * pnodePrev = NULL;

   if(m_bMultiKey)
   {

      pnodePrev = equally_keyed_prev_node(pnode);

      if(pnodePrev != NULL)
         return pnodePrev;

   }

   node * pnodeRoot = m_pnode;

   while(pnodeRoot != NULL)
   {

      if(compare(*pnodeRoot,*pnode))
      {

         pnodePrev = pnodeRoot;

         pnodeRoot = pnodeRoot->right;

      }
      else if(compare(*pnode,*pnodeRoot))
      {

         pnodeRoot = pnodeRoot->left;

      }
      else
      {

         break;

      }

   }

   return pnodePrev;

}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetNextAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode) const
{

   return next(pnode);

}

template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetNextAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode)
{


   return next(pnode);
   
}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetPrevAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode) const
{

   return prev(pnode);

}


template < class KEY,class ARG_KEY,class VALUE,class ARG_VALUE,class COMPARE,bool m_bMultiKey >
typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node*
sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::PGetPrevAssoc(const typename sort_map < KEY,ARG_KEY,VALUE,ARG_VALUE,COMPARE,m_bMultiKey >::node* pnode)
{

   return prev(pnode);

}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
VALUE sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey > ::
   get(ARG_KEY argkey, ARG_VALUE valueDefault)
{
   node * pnode = PLookup(argkey);
   if(pnode == NULL)
      return valueDefault;
   else
      return pnode->m_element2;
}


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::dump(dump_context & dumpcontext) const
{
   object::dump(dumpcontext);

   dumpcontext << "with " << get_count() << " elements";
   if (dumpcontext.GetDepth() > 0)
   {
      // Dump in format "[key] -> value"

      const node * pnode = PGetFirstAssoc();
      while (pnode != NULL)
      {
         pnode = PGetNextAssoc(pnode);
         dumpcontext << "\n\t[";
         dump_elements<KEY>(dumpcontext, &pnode->m_element1, 1);
         dumpcontext << "] = ";
         dump_elements<VALUE>(dumpcontext, &pnode->m_element2, 1);
      }
   }

   dumpcontext << "\n";
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class COMPARE, bool m_bMultiKey >
void sort_map < KEY, ARG_KEY, VALUE, ARG_VALUE, COMPARE, m_bMultiKey >::assert_valid() const
{

   object::assert_valid();

}



template < class type_map >
class sort_attrib_map :
   virtual public type_map
{
public:


   sort_attrib_map(int_ptr nBlockSize = 10);
   sort_attrib_map(const sort_attrib_map & sort_map);

   sort_attrib_map & operator = (const sort_attrib_map & sort_map);

   bool operator == (const sort_attrib_map & sort_map) const;


};


template < class type_map >
sort_attrib_map < type_map >::sort_attrib_map(int_ptr nBlockSize) :
   type_map(nBlockSize)
{
}

template < class type_map >
sort_attrib_map < type_map >::sort_attrib_map(const sort_attrib_map & attribmap)
{
   operator = (attribmap);
}


template < class type_map >
bool sort_attrib_map < type_map >::operator == (const sort_attrib_map & attribmap) const
{

   if(this == &attribmap)
      return true;

   if(this->m_ptra.get_size() != attribmap.get_size())
      return false;

   for(index i = 0; i < attribmap.m_ptra.get_count(); i++)
   {

      if(attribmap.m_ptra[i]->m_element1       != this->m_ptra[i]->m_element1
         || attribmap.m_ptra[i]->m_element2     != this->m_ptra[i]->m_element2)
      {

         return false;

      }

   }

   return true;

}


template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::less < string > >
class sort_string_map :
   virtual public sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >
{
public:


   sort_string_map(::count nBlockSize = 10);
   sort_string_map(const sort_string_map & sort_map);


   sort_string_map & operator = (const sort_string_map & sort_map);


};

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(::count nBlockSize) :
   sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE >::sort_string_map(const sort_string_map & sortmap) :
   sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_string_map < VALUE, ARG_VALUE, COMPARE > & sort_string_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_string_map & sortmap)
{

   if(this != &sortmap)
   {

      sort_attrib_map < sort_map < string, const string &, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);

   }

   return *this;

}

template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::strid_binary  >
class sort_strid_map :
   virtual public sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE, COMPARE > >
{
public:

   sort_strid_map(::count nBlockSize = 256);
   sort_strid_map(const sort_strid_map & sort_map);


   sort_strid_map & operator = (const sort_strid_map & sort_map);


};


template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE >::sort_strid_map(::count nBlockSize) :
   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE, COMPARE > > (nBlockSize)
{
}


template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE >::sort_strid_map(const sort_strid_map & sortmap) :
   sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_strid_map < VALUE, ARG_VALUE, COMPARE > & sort_strid_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_strid_map & sortmap)
{

   if(this != &sortmap)
   {
      sort_attrib_map < sort_map < id, const id &, VALUE, ARG_VALUE > >::operator = (sortmap);
   }

   return *this;

}

template < class VALUE, class ARG_VALUE = const VALUE &, class COMPARE = ::comparison::binary < int32_t > >
class sort_int_map :
   virtual public sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > >
{
public:

   sort_int_map(::count nBlockSize = 10);
   sort_int_map(const sort_int_map & sort_map);


   sort_int_map & operator = (const sort_int_map & sort_map);

};

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(::count nBlockSize) :
   sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > (nBlockSize)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE >::sort_int_map(const sort_int_map & sortmap) :
   sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > > (sortmap)
{
}

template < class VALUE, class ARG_VALUE, class COMPARE >
sort_int_map < VALUE, ARG_VALUE, COMPARE > & sort_int_map < VALUE, ARG_VALUE, COMPARE >::operator = (const sort_int_map & sortmap)
{

   if(this != &sortmap)
   {
      sort_attrib_map < sort_map < int32_t, int32_t, VALUE, ARG_VALUE, COMPARE > >::operator = (sortmap);
   }

   return *this;

}

typedef CLASS_DECL_AURA sort_attrib_map < sort_map < int32_t, int32_t, int32_t, int32_t > > sort_int_to_int;
typedef CLASS_DECL_AURA sort_attrib_map < sort_map < int32_t, int32_t, string, const string & > > sort_int_to_string;
typedef CLASS_DECL_AURA sort_string_map < void *, void * > sort_string_to_ptr;

template < class T >
class CLASS_DECL_AURA sort_string_to_pointer :
   virtual public string_to_ptr
{
public:

   class node
   {
   public:
      const string m_element1;
      T * m_element2;
   };

   bool Lookup(string key, T * & rValue) const
   {
      return string_to_ptr::Lookup(key, rValue);
   }
   const node *PLookup(string key) const
   {
      return reinterpret_cast < const sort_string_to_pointer::node * > (string_to_ptr::PLookup(key));
   }
   node *PLookup(string key)
   {
      return reinterpret_cast < sort_string_to_pointer::node * > (string_to_ptr::PLookup(key));
   }


   T ** pget(string key)
   {
      return (T**) string_to_ptr::pget(key);
   }
   T * get(string key)
   {
      T ** p = (T **) string_to_ptr::pget(key);
      if(p == NULL)
         return NULL;
      else
         return (T*) *p;
   }

   // Operations
   // Lookup and add if not there
   T * & operator[](string key)
   {
      return (T * &) string_to_ptr::operator[](key);
   }


   node * PGetFirstAssoc()
   {
      return (node *) string_to_ptr::PGetFirstAssoc();
   }

   node * PGetNextAssoc(node * & rPnode)
   {
      return (node *) string_to_ptr::PGetNextAssoc((string_to_ptr::node * &) rPnode);
   }

};





typedef CLASS_DECL_AURA sort_string_map < int_ptr, int_ptr > sort_string_to_intptr;

typedef CLASS_DECL_AURA sort_string_map < string, const string & > sort_string_to_string_map;






inline void sort_map_test()
{
   sort_string_to_intptr m;
   
   m.insert(pair< string, int_ptr>("Carlos",1));
   m.insert(pair< string,int_ptr>("Carlos",2));
   m.insert(pair< string,int_ptr>("Mummi",2));
   m.insert(pair< string,int_ptr>("Mummi",3));
   m.insert(pair< string,int_ptr>("Camilo",3));
   m.insert(pair< string,int_ptr>("Camilo",4));
   m.insert(pair< string,int_ptr>("Ca2",1));
   m.insert(pair< string,int_ptr>("Ca2",2));
   m.insert(pair< string,int_ptr>("Ca2",3));
   m.insert(pair< string,int_ptr>("Ca2",4));
   m.insert(pair< string,int_ptr>("Ca2",5));

   sort_string_to_intptr::node * p = m.PGetFirstAssoc();

   p = m.PGetNextAssoc(p);

   ::count c = m.get_count();

   sort_string_to_intptr::iterator lower = m.lower_bound("Ca2");
   sort_string_to_intptr::iterator upper = m.upper_bound("Ca2");
   
}


