#pragma once

class CLASS_DECL_ca object_list :
   public ::radix::object
{
public:

   struct node
	{


		node *               m_pnext;
		node *               m_pprevious;
		::radix::object *    m_pdata;


	};

// Construction
	object_list(count nBlockSize = 10);
	virtual ~object_list();

// Attributes (head and tail)
	// count of elements
	count get_count() const;
	count get_size() const;
	bool is_empty() const;

	// peek at head or tail
	::radix::object*& get_head();
	const ::radix::object* get_head() const;
	::radix::object*& get_tail();
	const ::radix::object* get_tail() const;

// Operations
	// get head or tail (and remove it) - don't call on is_empty list!
	::radix::object* remove_head();
	::radix::object* remove_tail();

	// add before head or after tail
	POSITION add_head(::radix::object* newElement);
	POSITION add_tail(::radix::object* newElement);


	// add another list of elements before head or after tail
	void add_head(object_list* pNewList);
	void add_tail(object_list* pNewList);

	// remove all elements
	void remove_all();

	// iteration
	POSITION get_head_position() const;
	POSITION get_tail_position() const;
	::radix::object*& get_next(POSITION& rPosition); // return *position++
	const ::radix::object* get_next(POSITION& rPosition) const; // return *position++
	::radix::object*& get_previous(POSITION& rPosition); // return *position--
	const ::radix::object* get_previous(POSITION& rPosition) const; // return *position--

	// getting/modifying an element at a given position
	::radix::object*& get_at(POSITION position);
	const ::radix::object* get_at(POSITION position) const;
	void set_at(POSITION pos, ::radix::object* newElement);

	void remove_at(POSITION position);

	// inserting before or after a given position
	POSITION insert_before(POSITION position, ::radix::object* newElement);
	POSITION insert_after(POSITION position, ::radix::object* newElement);


	// helper functions (note: O(n) speed)
	POSITION find(::radix::object* searchValue, POSITION startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found
	POSITION find_index(index nIndex) const;
						// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	node* m_pnodeHead;
	node* m_pnodeTail;
	INT_PTR m_nCount;
	node* m_pnodeFree;
	struct plex* m_pBlocks;
	INT_PTR m_nBlockSize;

	node* NewNode(node*, node*);
	void FreeNode(node*);

   public:


//	void Serialize(CArchive&);
#ifdef _DEBUG
	void dump(dump_context&) const;
	void assert_valid() const;
#endif
	// local typedefs for class templates
	typedef ::radix::object* BASE_TYPE;
	typedef ::radix::object* BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

inline ::count object_list::get_count() const
   { return m_nCount; }
inline ::count object_list::get_size() const
   { return m_nCount; }
inline bool object_list::is_empty() const
   { return m_nCount == 0; }
inline ::radix::object*& object_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->m_pdata; }
inline const ::radix::object* object_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->m_pdata; }
inline ::radix::object*& object_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->m_pdata; }
inline const ::radix::object* object_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->m_pdata; }
inline POSITION object_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION object_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline ::radix::object*& object_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnext;
      return pNode->m_pdata; }
inline const ::radix::object* object_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pnext;
      return pNode->m_pdata; }
inline ::radix::object*& object_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pprevious;
      return pNode->m_pdata; }
inline const ::radix::object* object_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      rPosition = (POSITION) pNode->m_pprevious;
      return pNode->m_pdata; }
inline ::radix::object*& object_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->m_pdata; }
inline const ::radix::object* object_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      return pNode->m_pdata; }
inline void object_list::set_at(POSITION pos, ::radix::object* newElement)
   { node* pNode = (node*) pos;
      ASSERT(fx_is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         AfxThrowInvalidArgException();
      pNode->m_pdata = newElement; }
