#pragma once


class CLASS_DECL_ca2 string_to_string_map :
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
		friend class string_to_string_map;
		assoc* pNext;
		UINT nHashValue;
      assoc(const string & key) : pair(key) {}
	};

   string_to_string_map(INT_PTR nBlockSize = 10);
	~string_to_string_map();


// Attributes
	// number of elements
	INT_PTR get_count() const;
	INT_PTR get_size() const;
	bool is_empty(count countMinimum = 1) const;
   bool has_elements(count countMinimum = 1) const;

	// Lookup
	BOOL Lookup(const char * key, string & rValue) const;
	const pair *PLookup(const char * key) const;
	pair *PLookup(const char * key);
	BOOL LookupKey(const char * key, const char *& rKey) const;

// Operations
	// Lookup and add if not there
	string & operator[](const char * key);

	// add a new (key, value) pair
	void set_at(const char * key, const char * newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(const char * key);
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

// Overridables: special non-virtual (see ::collection::map implementation for details)
	// Routine used to ::fontopus::user-provided hash keys
	UINT HashKey(const char * key) const;


   void _001ReplaceVars(string & str);


// Implementation
protected:
	assoc** m_pHashTable;
	UINT m_nHashTableSize;
	INT_PTR m_nCount;
	assoc* m_pFreeList;
	struct plex* m_pBlocks;
	INT_PTR m_nBlockSize;

	assoc* NewAssoc(const char * key);
	void FreeAssoc(assoc*);
	assoc* GetAssocAt(const char *, UINT&, UINT&) const;

public:

//	void Serialize(CArchive&);
#ifdef _DEBUG
	void dump(dump_context&) const;
	void assert_valid() const;
#endif

protected:
	// local typedefs for typed_pointer_map class template
	typedef string BASE_KEY;
	typedef const char * BASE_ARG_KEY;
	typedef string BASE_VALUE;
	typedef const char * BASE_ARG_VALUE;
};



inline INT_PTR string_to_string_map::get_count() const
   { return m_nCount; }
inline INT_PTR string_to_string_map::get_size() const
   { return m_nCount; }
inline bool string_to_string_map::is_empty(::count countMinimum) const
   { return m_nCount < countMinimum; }
inline bool string_to_string_map::has_elements(::count countMinimum) const
   { return m_nCount >= countMinimum; }
inline void string_to_string_map::set_at(const char * key, const char * newValue)
   { (*this)[key] = newValue; }
inline POSITION string_to_string_map::get_start_position() const
   { return (m_nCount == 0) ? NULL : BEFORE_START_POSITION; }
inline UINT string_to_string_map::GetHashTableSize() const
   { return m_nHashTableSize; }



