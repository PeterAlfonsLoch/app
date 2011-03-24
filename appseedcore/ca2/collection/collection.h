#pragma once

#include "raw_array.h"
#include "primitive_array.h"
#include "numeric_array.h"

#include "logic_array.h"

#include "list.h"
#include "comparable_eq_list.h"
#include "comparable_list.h"

#include "map.h"

#include "comparable_array.h"

#include "array_smart_ptr.h"
#include "array_ptr.h"
#include "array_ptr_copy.h"
#include "array_ptr_alloc.h"

#include "array_parent_alloc.h"

#include "array_app_alloc.h"

#include "sort_array.h"
#include "class_sort_array.h"


/////////////////////////////////////////////////////////////////////////////
// Classes declared in this file

//::radix::object
   // Arrays
   class byte_array;           // base_array of BYTE
   class word_array;           // base_array of WORD
   class dword_array;          // base_array of DWORD
   class CUIntArray;           // base_array of UINT
   class CPtrArray;            // base_array of void *
   class CObArray;             // base_array of ::radix::object*

   // Lists
   class pointer_list;             // list of void *
   class base_object_list;              // list of ::radix::object*

   // Maps (aka Dictionaries)
   class CMapWordToOb;         // ::collection::map from WORD to ::radix::object*
   class CMapWordToPtr;        // ::collection::map from WORD to void *
   class CMapPtrToWord;        // ::collection::map from void * to WORD
   class CMapPtrToPtr;         // ::collection::map from void * to void *

   // Special string variants
   class string_list;          // list of Strings
   class CMapStringToPtr;      // ::collection::map from string to void *
   class CMapStringToOb;       // ::collection::map from string to ::radix::object*
   class string_to_string_map;   // ::collection::map from string to string




/*
////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CPtrArray : public ::radix::object
{

   
public:

// Construction
   CPtrArray();

// Attributes
   INT_PTR get_size() const;
   INT_PTR get_count() const;
   BOOL is_empty() const;
   INT_PTR get_upper_bound() const;
   void set_size(INT_PTR nNewSize, INT_PTR nGrowBy = -1);

// Operations
   // Clean up
   void free_extra();
   void remove_all();

   // Accessing elements
   void * get_at(INT_PTR nIndex) const;
   void set_at(INT_PTR nIndex, void * newElement);

   void *& element_at(INT_PTR nIndex);

   // Direct Access to the element data (may return NULL)
   const void ** get_data() const;
   void ** get_data();

   // Potentially growing the base_array
   void set_at_grow(INT_PTR nIndex, void * newElement);

   INT_PTR add(void * newElement);

   INT_PTR append(const CPtrArray& src);
   void copy(const CPtrArray& src);

   // overloaded operator helpers
   void * operator[](INT_PTR nIndex) const;
   void *& operator[](INT_PTR nIndex);

   // Operations that move elements around
   void insert_at(INT_PTR nIndex, void * newElement, INT_PTR nCount = 1);

   void remove_at(INT_PTR nIndex, INT_PTR nCount = 1);
   void insert_at(INT_PTR nStartIndex, CPtrArray* pNewArray);

// Implementation
protected:
   void ** m_pData;   // the actual base_array of data
   INT_PTR m_nSize;     // # of elements (upperBound - 1)
   INT_PTR m_nMaxSize;  // max allocated
   INT_PTR m_nGrowBy;   // grow amount


public:
   ~CPtrArray();
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

protected:
   // local typedefs for class templates
   typedef void * BASE_TYPE;
   typedef void * BASE_ARG_TYPE;
};

*/

/*
////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CObArray : public ::radix::object
{

   // DECLARE_SERIAL(CObArray)
public:

// Construction
   CObArray();

// Attributes
   INT_PTR get_size() const;
   INT_PTR get_count() const;
   BOOL is_empty() const;
   INT_PTR get_upper_bound() const;
   void set_size(INT_PTR nNewSize, INT_PTR nGrowBy = -1);

// Operations
   // Clean up
   void free_extra();
   void remove_all();

   // Accessing elements
   ::radix::object* get_at(INT_PTR nIndex) const;
   void set_at(INT_PTR nIndex, ::radix::object* newElement);

   ::radix::object*& element_at(INT_PTR nIndex);

   // Direct Access to the element data (may return NULL)
   const ::radix::object** get_data() const;
   ::radix::object** get_data();

   // Potentially growing the base_array
   void set_at_grow(INT_PTR nIndex, ::radix::object* newElement);

   INT_PTR add(::radix::object* newElement);

   INT_PTR append(const CObArray& src);
   void copy(const CObArray& src);

   // overloaded operator helpers
   ::radix::object* operator[](INT_PTR nIndex) const;
   ::radix::object*& operator[](INT_PTR nIndex);

   // Operations that move elements around
   void insert_at(INT_PTR nIndex, ::radix::object* newElement, INT_PTR nCount = 1);

   void remove_at(INT_PTR nIndex, INT_PTR nCount = 1);
   void insert_at(INT_PTR nStartIndex, CObArray* pNewArray);

// Implementation
protected:
   ::radix::object** m_pData;   // the actual base_array of data
   INT_PTR m_nSize;     // # of elements (upperBound - 1)
   INT_PTR m_nMaxSize;  // max allocated
   INT_PTR m_nGrowBy;   // grow amount


public:
   ~CObArray();

   // void Serialize(CArchive&);
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

protected:
   // local typedefs for class templates
   typedef ::radix::object* BASE_TYPE;
   typedef ::radix::object* BASE_ARG_TYPE;
};
*/


#include "pointer_list.h"
#include "base_object_list.h"
#include "string_list.h"




class CLASS_DECL_ca CMapWordToPtr : public ::radix::object
{

   
protected:
   // Association
   struct assoc
   {
      assoc* pNext;
      void * value;
      WORD key;
   };

public:

// Construction
   /* explicit */ CMapWordToPtr(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(WORD key, void *& rValue) const;

// Operations
   // Lookup and add if not there
   void *& operator[](WORD key);

   // add a new (key, value) pair
   void set_at(WORD key, void * newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(WORD key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, WORD& rKey, void *& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(WORD key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(WORD, UINT&, UINT&) const;

public:
   ~CMapWordToPtr();
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif


protected:
   // local typedefs for typed_pointer_map class template
   typedef WORD BASE_KEY;
   typedef WORD BASE_ARG_KEY;
   typedef void * BASE_VALUE;
   typedef void * BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CMapPtrToWord : public ::radix::object
{

   
protected:
   // Association
   struct assoc
   {
      assoc* pNext;

      void * key;
      WORD value;
   };

public:

// Construction
   /* explicit */ CMapPtrToWord(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(void * key, WORD& rValue) const;

// Operations
   // Lookup and add if not there
   WORD& operator[](void * key);

   // add a new (key, value) pair
   void set_at(void * key, WORD newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(void * key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, void *& rKey, WORD& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(void * key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(void *, UINT&, UINT&) const;

public:
   ~CMapPtrToWord();
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif


protected:
   // local typedefs for typed_pointer_map class template
   typedef void * BASE_KEY;
   typedef void * BASE_ARG_KEY;
   typedef WORD BASE_VALUE;
   typedef WORD BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CMapPtrToPtr : public ::radix::object
{

   
protected:
   // Association
   struct assoc
   {
      assoc* pNext;

      void * key;
      void * value;
   };

public:

// Construction
   /* explicit */ CMapPtrToPtr(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(void * key, void *& rValue) const;

// Operations
   // Lookup and add if not there
   void *& operator[](void * key);

   // add a new (key, value) pair
   void set_at(void * key, void * newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(void * key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, void *& rKey, void *& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(void * key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(void *, UINT&, UINT&) const;

public:
   ~CMapPtrToPtr();
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

   void * GetValueAt(void * key) const;


protected:
   // local typedefs for typed_pointer_map class template
   typedef void * BASE_KEY;
   typedef void * BASE_ARG_KEY;
   typedef void * BASE_VALUE;
   typedef void * BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CMapWordToOb : public ::radix::object
{

   // DECLARE_SERIAL(CMapWordToOb)
protected:
   // Association
   struct assoc
   {
      assoc* pNext;
      ::radix::object* value;
      WORD key;
   };

public:

// Construction
   /* explicit */ CMapWordToOb(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(WORD key, ::radix::object*& rValue) const;

// Operations
   // Lookup and add if not there
   ::radix::object*& operator[](WORD key);

   // add a new (key, value) pair
   void set_at(WORD key, ::radix::object* newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(WORD key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, WORD& rKey, ::radix::object*& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(WORD key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(WORD, UINT&, UINT&) const;

public:
   ~CMapWordToOb();

//   void Serialize(CArchive&);
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif


protected:
   // local typedefs for typed_pointer_map class template
   typedef WORD BASE_KEY;
   typedef WORD BASE_ARG_KEY;
   typedef ::radix::object* BASE_VALUE;
   typedef ::radix::object* BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CMapStringToPtr : public ::radix::object
{

   
protected:
   // Association
   struct assoc
   {
      assoc* pNext;
      UINT nHashValue;  // needed for efficient iteration
      string key;
      void * value;
   };

public:

// Construction
   /* explicit */ CMapStringToPtr(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(const char * key, void *& rValue) const;
   BOOL LookupKey(const char * key, const char *& rKey) const;

// Operations
   // Lookup and add if not there
   void *& operator[](const char * key);

   // add a new (key, value) pair
   void set_at(const char * key, void * newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(const char * key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, string & rKey, void *& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(const char * key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(const char *, UINT&, UINT&) const;

public:
   ~CMapStringToPtr();
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

protected:
   // local typedefs for typed_pointer_map class template
   typedef string BASE_KEY;
   typedef const char * BASE_ARG_KEY;
   typedef void * BASE_VALUE;
   typedef void * BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CLASS_DECL_ca CMapStringToOb : public ::radix::object
{

   // DECLARE_SERIAL(CMapStringToOb)
protected:
   // Association
   struct assoc
   {
      assoc* pNext;
      UINT nHashValue;  // needed for efficient iteration
      string key;
      ::radix::object* value;
   };

public:

// Construction
   /* explicit */ CMapStringToOb(INT_PTR nBlockSize = 10);

// Attributes
   // number of elements
   INT_PTR get_count() const;
   INT_PTR get_size() const;
   BOOL is_empty() const;

   // Lookup
   BOOL Lookup(const char * key, ::radix::object*& rValue) const;
   BOOL LookupKey(const char * key, const char *& rKey) const;

// Operations
   // Lookup and add if not there
   ::radix::object*& operator[](const char * key);

   // add a new (key, value) pair
   void set_at(const char * key, ::radix::object* newValue);

   // removing existing (key, ?) pair
   BOOL RemoveKey(const char * key);
   void remove_all();

   // iterating all (key, value) pairs
   POSITION get_start_position() const;
   void get_next_assoc(POSITION& rNextPosition, string & rKey, ::radix::object*& rValue) const;

   // advanced features for derived classes
   UINT GetHashTableSize() const;
   void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see ::collection::map implementation for details)
   // Routine used to ::fontopus::user-provided hash keys
   UINT HashKey(const char * key) const;

// Implementation
protected:
   assoc** m_pHashTable;
   UINT m_nHashTableSize;
   INT_PTR m_nCount;
   assoc* m_pFreeList;
   struct plex* m_pBlocks;
   INT_PTR m_nBlockSize;

   assoc* NewAssoc();
   void FreeAssoc(assoc*);
   assoc* GetAssocAt(const char *, UINT&, UINT&) const;

public:
   ~CMapStringToOb();

//   void Serialize(CArchive&);
#ifdef _DEBUG
   void dump(dump_context&) const;
   void assert_valid() const;
#endif

protected:
   // local typedefs for typed_pointer_map class template
   typedef string BASE_KEY;
   typedef const char * BASE_ARG_KEY;
   typedef ::radix::object* BASE_VALUE;
   typedef ::radix::object* BASE_ARG_VALUE;
};


#include "string_to_string_map.h"
#include "bit_array.h"
#include "collection/string_array.h"
#include "gen/gen_var_array.h"
#include "gen/gen_property.h"
#include "gen/gen_international2.h"
#include "point_array.h"
#include "rect_array.h"


#include "string_to_string_map.h"

// inline
#include "collection.inl"


class CLASS_DECL_ca dword_2darray :
   public array_ptr_alloc < dword_array, dword_array & >
{
public:
};

class CLASS_DECL_ca index_2darray :
   public array_ptr_alloc < index_array, index_array & >
{
public:
};

#include "sort.h"

#include "array.h"

