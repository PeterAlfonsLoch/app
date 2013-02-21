#pragma once

class CLASS_DECL_ca object_list :
   public ::gen::object
{
public:

   struct node
	{


		node *               m_pnext;
		node *               m_pprevious;
		::gen::object *    m_pdata;


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
	::gen::object*& get_head();
	const ::gen::object* get_head() const;
	::gen::object*& get_tail();
	const ::gen::object* get_tail() const;

// Operations
	// get head or tail (and remove it) - don't call on is_empty list!
	::gen::object* remove_head();
	::gen::object* remove_tail();

	// add before head or after tail
	POSITION add_head(::gen::object* newElement);
	POSITION add_tail(::gen::object* newElement);


	// add another list of elements before head or after tail
	void add_head(object_list* pNewList);
	void add_tail(object_list* pNewList);

	// remove all elements
	void remove_all();

	// iteration
	POSITION get_head_position() const;
	POSITION get_tail_position() const;
	::gen::object*& get_next(POSITION& rPosition); // return *position++
	const ::gen::object* get_next(POSITION& rPosition) const; // return *position++
	::gen::object*& get_previous(POSITION& rPosition); // return *position--
	const ::gen::object* get_previous(POSITION& rPosition) const; // return *position--

	// getting/modifying an element at a given position
	::gen::object*& get_at(POSITION position);
	const ::gen::object* get_at(POSITION position) const;
	void set_at(POSITION pos, ::gen::object* newElement);

	void remove_at(POSITION position);

	// inserting before or after a given position
	POSITION insert_before(POSITION position, ::gen::object* newElement);
	POSITION insert_after(POSITION position, ::gen::object* newElement);


	// helper functions (note: O(n) speed)
	POSITION find(::gen::object* searchValue, POSITION startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found
	POSITION find_index(index nIndex) const;
						// get the 'nIndex'th element (may return NULL)

// Implementation
protected:
	node* m_pnodeHead;
	node* m_pnodeTail;
	int_ptr m_nCount;
	node* m_pnodeFree;
	struct plex* m_pBlocks;
	int_ptr m_nBlockSize;

	node* NewNode(node*, node*);
	void FreeNode(node*);

   public:


//	void Serialize(CArchive&);
	void dump(dump_context &) const;
	void assert_valid() const;
	// local typedefs for class templates
	typedef ::gen::object* BASE_TYPE;
	typedef ::gen::object* BASE_ARG_TYPE;
};


////////////////////////////////////////////////////////////////////////////

inline ::count object_list::get_count() const
   { return m_nCount; }
inline ::count object_list::get_size() const
   { return m_nCount; }
inline bool object_list::is_empty() const
   { return m_nCount == 0; }
inline ::gen::object*& object_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->m_pdata; }
inline const ::gen::object* object_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->m_pdata; }
inline ::gen::object*& object_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->m_pdata; }
inline const ::gen::object* object_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->m_pdata; }
inline POSITION object_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION object_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline ::gen::object*& object_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnext;
      return pNode->m_pdata; }
inline const ::gen::object* object_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pnext;
      return pNode->m_pdata; }
inline ::gen::object*& object_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pprevious;
      return pNode->m_pdata; }
inline const ::gen::object* object_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->m_pprevious;
      return pNode->m_pdata; }
inline ::gen::object*& object_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->m_pdata; }
inline const ::gen::object* object_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->m_pdata; }
inline void object_list::set_at(POSITION pos, ::gen::object* newElement)
   { node* pNode = (node*) pos;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      pNode->m_pdata = newElement; }
