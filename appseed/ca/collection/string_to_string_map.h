#pragma once


class CLASS_DECL_ca base_string_to_string_map :
   public ::radix::object
{
public:


	class pair
	{
   public:
		const string m_key;
		string m_value;
      pair(const string & key) : m_key(key) {}
	};

	class assoc :
      public pair
	{
   public:
		friend class base_string_to_string_map;
		assoc* pNext;
		UINT nHashValue;
      assoc(const string & key) : pair(key) {}
	};


   base_string_to_string_map(INT_PTR nBlockSize = 10);
	virtual ~base_string_to_string_map();


// Attributes
	// number of elements
	count get_count() const;
	count get_size() const;
	bool is_empty(count countMinimum = 1) const;
   bool has_elements(count countMinimum = 1) const;

	// Lookup
	BOOL Lookup(const string & key, string & rValue) const;
	const pair *PLookup(const string & key) const;
	pair *PLookup(const string & key);
	BOOL LookupKey(const string & key, string & rKey) const;

// Operations
	// Lookup and add if not there
	string & operator[](const string & key);

	// add a new (key, value) pair
	void set_at(const string & key, const string & newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(const string & key);
	void remove_all();

	// iterating all (key, value) pairs
	POSITION get_start_position() const;

	const pair *PGetFirstAssoc() const;
	pair *PGetFirstAssoc();

	void get_next_assoc(POSITION& rNextPosition, string & rKey, string & rValue) const;

	const pair *PGetNextAssoc(const pair* pAssoc) const;
	pair *PGetNextAssoc(const pair* pAssoc);

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

   void _001ReplaceVars(string & str);


// Implementation
protected:
	assoc** m_pHashTable;
	UINT m_nHashTableSize;
	INT_PTR m_nCount;
	assoc* m_pFreeList;
	struct plex* m_pBlocks;
	INT_PTR m_nBlockSize;

	assoc* NewAssoc(const string & key);
	void FreeAssoc(assoc*);
	assoc* GetAssocAt(const string & , UINT&, UINT&) const;

public:

//	void Serialize(CArchive&);
	void dump(dump_context&) const;
	void assert_valid() const;

protected:
	// local typedefs for typed_pointer_map class template
	typedef string BASE_KEY;
	typedef const string & BASE_ARG_KEY;
	typedef string BASE_VALUE;
	typedef const string & BASE_ARG_VALUE;
};



inline INT_PTR base_string_to_string_map::get_count() const
   { return m_nCount; }
inline INT_PTR base_string_to_string_map::get_size() const
   { return m_nCount; }
inline bool base_string_to_string_map::is_empty(::count countMinimum) const
   { return m_nCount < countMinimum; }
inline bool base_string_to_string_map::has_elements(::count countMinimum) const
   { return m_nCount >= countMinimum; }
inline void base_string_to_string_map::set_at(const string & key, const string & newValue)
   { (*this)[key] = newValue; }
inline POSITION base_string_to_string_map::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT base_string_to_string_map::GetHashTableSize() const
   { return m_nHashTableSize; }




class CLASS_DECL_ca string_to_string_map :
   virtual public ex1::byte_serializable_map < ::collection::attrib_map < base_string_to_string_map >  >
{
public:


   string_to_string_map(INT_PTR nBlockSize = 10);
   string_to_string_map(const string_to_string_map & map);
	~string_to_string_map();


   string_to_string_map & operator = (const string_to_string_map & map);

};