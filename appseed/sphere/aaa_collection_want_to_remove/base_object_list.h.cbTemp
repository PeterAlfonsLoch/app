#pragma once

class CLASS_DECL_ca base_object_list :
   virtual public ::radix::object
{
public:

   struct node
	{
		node* pNext;
		node* pPrev;
		::radix::object* data;
	};

// Construction
	base_object_list(count nBlockSize = 10);
	virtual ~base_object_list();

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
	void add_head(base_object_list* pNewList);
	void add_tail(base_object_list* pNewList);

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
