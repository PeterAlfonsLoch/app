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
