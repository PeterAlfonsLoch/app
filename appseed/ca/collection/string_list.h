#pragma once


class CLASS_DECL_ca string_list :
   virtual public ::radix::object
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

      iterator & operator +(int i)
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

      iterator & operator -(int i)
      {

         while(m_pos != NULL && m_pos != m_plist->get_head_position() && i > 0)
         {
            i--;
            m_plist->get_previous(m_pos);
         }

         return *this;

      }

   };


   typedef const iterator const_iterator;




protected:


   node *   m_pnodeHead;
   node *   m_pnodeTail;
   count    m_nCount;
   node *   m_pnodeFree;
   plex *   m_pplex;
   count    m_nBlockSize;


public:


   string_list(INT_PTR nBlockSize = 10);
   virtual ~string_list();

   count get_count() const;
   count get_size() const;
   bool is_empty() const;
   bool has_elements(count nMinimumCount = 1) const;

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
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

protected:
   node* NewNode(node*, node*);
   void FreeNode(node*);

};


inline INT_PTR string_list::get_count() const
   { return m_nCount; }
inline INT_PTR string_list::get_size() const
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
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline const string & string_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodeNext;
      return pNode->data; }
inline string & string_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline const string & string_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnodePrevious;
      return pNode->data; }
inline string & string_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline const string & string_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->data; }
inline void string_list::set_at(POSITION pos, const char * newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }

inline void string_list::set_at(POSITION pos, const string & newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->data = newElement; }
