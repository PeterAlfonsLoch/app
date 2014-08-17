#pragma once


class CLASS_DECL_BASE string_list :
   virtual public ::object
{
public:


   typedef string BASE_TYPE;
   typedef const char * BASE_ARG_TYPE;


   struct node
   {
      node *   m_pnodeNext;
      node *   m_pnodePrevious;
      string   data;
   };


   class iterator
   {
   public:


      POSITION         m_pos;
      string_list *    m_plist;

      iterator()
      {
         m_pos = 0;
         m_plist = NULL;
      }

      iterator(POSITION i, string_list * plist)
      {
         m_pos = i;
         m_plist = plist;
      }

      iterator(const iterator & it)
      {
         operator = (it);
      }

      string & operator * ()
      {
         return m_plist->get_at(m_pos);
      }

      const string & operator * () const
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
      const string_list *     m_plist;

      const_iterator()
      {
         m_pos = 0;
         m_plist = NULL;
      }

      const_iterator(POSITION i, const string_list * plist)
      {
         m_pos = i;
         m_plist = plist;
      }

      const_iterator(const const_iterator & it)
      {
         operator = (it);
      }

      const string & operator * ()
      {
         return m_plist->get_at(m_pos);
      }

      const string & operator * () const
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

protected:


   node *   m_pnodeHead;
   node *   m_pnodeTail;
   ::count m_nCount;
   node *   m_pnodeFree;
   plex *   m_pplex;
   ::count m_nBlockSize;


public:


   string_list(int_ptr nBlockSize = 10);
   virtual ~string_list();

   ::count get_count() const;
   ::count get_size() const;
   bool is_empty() const;
   bool has_elements(::count nMinimumCount = 1) const;

   string & get_head();
   const string & get_head() const;
   string & get_tail();
   const string & get_tail() const;

// Operations
   // get head or tail (and remove it) - don't call on is_empty list!
   string remove_head();
   string remove_tail();

   // add before head or after tail
   POSITION add_head(const char * newElement);
   POSITION add_tail(const char * newElement);

   POSITION add_head(const string & newElement);
   POSITION add_tail(const string & newElement);

   inline POSITION push_front(const char * newElement);
   inline POSITION push_back(const char * newElement);

   inline POSITION push_front(const string & newElement);
   inline POSITION push_back(const string & newElement);

   // add another list of elements before head or after tail
   void add_head(string_list* pNewList);
   void add_tail(string_list* pNewList);

   // remove all elements
   void remove_all();

   // iteration
   POSITION get_head_position() const;
   POSITION get_tail_position() const;
   string & get_next(POSITION& rPosition); // return *position++
   const string & get_next(POSITION& rPosition) const; // return *position++
   string & get_previous(POSITION& rPosition); // return *position--
   const string & get_previous(POSITION& rPosition) const; // return *position--

   // getting/modifying an element at a given position
   string & get_at(POSITION position);
   const string & get_at(POSITION position) const;
   void set_at(POSITION pos, const char * newElement);

   void set_at(POSITION pos, const string & newElement);

   void remove_at(POSITION position);

   // inserting before or after a given position
   POSITION insert_before(POSITION position, const char * newElement);
   POSITION insert_after(POSITION position, const char * newElement);

   POSITION insert_before(POSITION position, const string & newElement);
   POSITION insert_after(POSITION position, const string & newElement);


   // helper functions (note: O(n) speed)
   POSITION find(const char * searchValue, POSITION startAfter = NULL) const;
                  // defaults to starting at the HEAD
                  // return NULL if not found
   POSITION find_index(index nIndex) const;
                  // get the 'nIndex'th element (may return NULL)
   POSITION reverse_find_index(index nIndex) const;
                  // get the 'nIndex'th element (may return NULL)


//   void Serialize(CArchive&);
   void dump(dump_context &) const;
   void assert_valid() const;

protected:
   node* NewNode(node*, node*);
   void FreeNode(node*);

};


inline ::count string_list::get_count() const
   { return m_nCount; }
inline ::count string_list::get_size() const
   { return m_nCount; }
inline bool string_list::is_empty() const
   { return m_nCount == 0; }
inline bool string_list::has_elements(::count nMinimumCount) const
   { return m_nCount >= nMinimumCount; }
inline string & string_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline const string & string_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline string & string_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline const string & string_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline POSITION string_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION string_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline string & string_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline const string & string_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline string & string_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline const string & string_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline string & string_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->data; }
inline const string & string_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->data; }
inline void string_list::set_at(POSITION pos, const char * newElement)
   { node* pNode = (node*) pos;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      pNode->data = newElement; }

inline void string_list::set_at(POSITION pos, const string & newElement)
   { node* pNode = (node*) pos;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      pNode->data = newElement; }



inline POSITION string_list::push_front(const char * newElement)
{

   return add_head(newElement);

}

POSITION string_list::push_back(const char * newElement)
{

   return add_tail(newElement);

}

POSITION string_list::push_front(const string & newElement)
{

   return add_head(newElement);

}

POSITION string_list::push_back(const string & newElement)
{

   return add_tail(newElement);

}

