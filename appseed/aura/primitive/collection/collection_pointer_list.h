#pragma once


class CLASS_DECL_AXIS pointer_list :
   virtual public ::object
{
public:
	struct node
	{
		node* pNext;
		node* pPrev;
		void * data;
	};

// Construction
	pointer_list(::count nBlockSize = 10);
	virtual ~pointer_list();

// Attributes (head and tail)
	// ::count of elements
	::count get_count() const;
	::count get_size() const;
	bool is_empty() const;

	// peek at head or tail
	void *& get_head();
	const void * get_head() const;
	void *& get_tail();
	const void * get_tail() const;

// Operations
	// get head or tail (and remove it) - don't call on is_empty list!
	void * remove_head();
	void * remove_tail();

	// add before head or after tail
	POSITION add_head(void * newElement);
	POSITION add_tail(void * newElement);


	// add another list of elements before head or after tail
	void add_head(pointer_list* pNewList);
	void add_tail(pointer_list* pNewList);

	// remove all elements
	void remove_all();

	// iteration
	POSITION get_head_position() const;
	POSITION get_tail_position() const;
	void *& get_next(POSITION& rPosition); // return *position++
	const void * get_next(POSITION& rPosition) const; // return *position++
	void *& get_previous(POSITION& rPosition); // return *position--
	const void * get_previous(POSITION& rPosition) const; // return *position--

	// getting/modifying an element at a given position
	void *& get_at(POSITION position);
	const void * get_at(POSITION position) const;
	void set_at(POSITION pos, void * newElement);

	void remove_at(POSITION position);

	// inserting before or after a given position
	POSITION insert_before(POSITION position, void * newElement);
	POSITION insert_after(POSITION position, void * newElement);


	// helper functions (note: O(n) speed)
	POSITION find(void * searchValue, POSITION startAfter = NULL) const;
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
	void dump(dump_context &) const;
	void assert_valid() const;
	// local typedefs for class templates
	typedef void * BASE_TYPE;
	typedef void * BASE_ARG_TYPE;
};



inline ::count pointer_list::get_count() const
   { return m_nCount; }
inline ::count pointer_list::get_size() const
   { return m_nCount; }
inline bool pointer_list::is_empty() const
   { return m_nCount == 0; }
inline void *& pointer_list::get_head()
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline const void * pointer_list::get_head() const
   { ASSERT(m_pnodeHead != NULL);
      return m_pnodeHead->data; }
inline void *& pointer_list::get_tail()
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline const void * pointer_list::get_tail() const
   { ASSERT(m_pnodeTail != NULL);
      return m_pnodeTail->data; }
inline POSITION pointer_list::get_head_position() const
   { return (POSITION) m_pnodeHead; }
inline POSITION pointer_list::get_tail_position() const
   { return (POSITION) m_pnodeTail; }
inline void *& pointer_list::get_next(POSITION& rPosition) // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline const void * pointer_list::get_next(POSITION& rPosition) const // return *position++
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->pNext;
      return pNode->data; }
inline void *& pointer_list::get_previous(POSITION& rPosition) // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline const void * pointer_list::get_previous(POSITION& rPosition) const // return *position--
   { node* pNode = (node*) rPosition;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      rPosition = (POSITION) pNode->pPrev;
      return pNode->data; }
inline void *& pointer_list::get_at(POSITION position)
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->data; }
inline const void * pointer_list::get_at(POSITION position) const
   { node* pNode = (node*) position;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      return pNode->data; }
inline void pointer_list::set_at(POSITION pos, void * newElement)
   { node* pNode = (node*) pos;
      ASSERT(__is_valid_address(pNode, sizeof(node)));
      if( pNode == NULL )
         throw invalid_argument_exception(get_app());
      pNode->data = newElement; }
