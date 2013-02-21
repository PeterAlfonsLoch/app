#pragma once


class CLASS_DECL_ca base_string_to_string_map :
   public ::gen::object
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


   class CLASS_DECL_ca iterator
   {
   public:


      pair *   m_ppair;
      base_string_to_string_map *    m_pmap;


      iterator()
      {
         m_ppair  = NULL;
         m_pmap   = NULL;
      }

      iterator(const iterator & iterator)
      {
         m_ppair  = iterator.m_ppair;
         m_pmap   = iterator.m_pmap;
      }

      iterator(pair * ppair, base_string_to_string_map * pmap)
      {
         m_ppair  = ppair;
         m_pmap   = pmap;
      }

      pair * operator -> ()
      {
         return m_ppair;
      }

      const pair * operator -> () const
      {
         return m_ppair;
      }


      iterator & operator ++ ()
      {
         if(m_ppair != NULL && m_pmap != NULL)
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      iterator operator ++ (int32_t)
      {
         if(m_ppair != NULL && m_pmap != NULL)
            m_ppair = m_pmap->PGetNextAssoc(m_ppair);
         return *this;
      }

      bool operator == (const iterator & it) const
      {
         if(this == &it)
            return true;
         if(m_ppair == NULL && it.m_ppair == NULL && it.m_pmap == NULL)
            return true;
         if(m_pmap != it.m_pmap)
            return false;
         return m_ppair == it.m_ppair;
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
            m_ppair        = it.m_ppair;
         }
         return *this;
      }

   };


   base_string_to_string_map(int_ptr nBlockSize = 10);
	virtual ~base_string_to_string_map();


// Attributes
	// number of elements
	::count get_count() const;
	::count get_size() const;
	bool is_empty(count countMinimum = 1) const;
   bool has_elements(count countMinimum = 1) const;

	// Lookup
	bool Lookup(const string & key, string & rValue) const;
	const pair *PLookup(const string & key) const;
	pair *PLookup(const string & key);
	bool LookupKey(const string & key, string & rKey) const;

// Operations
	// Lookup and add if not there
	string & operator[](const string & key);

	// add a new (key, value) pair
	void set_at(const string & key, const string & newValue);

	// removing existing (key, ?) pair
	bool RemoveKey(const string & key);
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
	void InitHashTable(UINT hashSize, bool bAllocNow = TRUE);

   void _001ReplaceVars(string & str);

   iterator begin()
   {
      return iterator(PGetFirstAssoc(), this);
   }


   iterator end()
   {
      return iterator(NULL, this);
   }

   ::count count(const string & strKey) const;
   bool has(const string & strKey) const;
   bool contains(const string & strKey) const;



// Implementation
protected:
	assoc** m_pHashTable;
	UINT m_nHashTableSize;
	int_ptr m_nCount;
	assoc* m_pFreeList;
	struct plex* m_pBlocks;
	int_ptr m_nBlockSize;

	assoc* NewAssoc(const string & key);
	void FreeAssoc(assoc*);
	assoc* GetAssocAt(const string & , UINT&, UINT&) const;

public:

//	void Serialize(CArchive&);
	void dump(dump_context &) const;
	void assert_valid() const;

protected:
	// local typedefs for typed_pointer_map class template
	typedef string BASE_KEY;
	typedef const string & BASE_ARG_KEY;
	typedef string BASE_VALUE;
	typedef const string & BASE_ARG_VALUE;
};



inline int_ptr base_string_to_string_map::get_count() const
   { return m_nCount; }
inline int_ptr base_string_to_string_map::get_size() const
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
inline ::count base_string_to_string_map::count(const string & strKey) const
{ return PLookup(strKey) != NULL ? 1 : 0; }
inline bool base_string_to_string_map::contains(const string & strKey) const
{ return PLookup(strKey) != NULL; }
inline bool base_string_to_string_map::has(const string & strKey) const
{ return PLookup(strKey) != NULL; }



class CLASS_DECL_ca string_to_string_map :
   virtual public gen::byte_serializable_map < ::collection::attrib_map < base_string_to_string_map >  >
{
public:


   string_to_string_map(int_ptr nBlockSize = 10);
   string_to_string_map(const string_to_string_map & map);
	~string_to_string_map();


   string_to_string_map & operator = (const string_to_string_map & map);

};
