#pragma once

/////////////////////////////////////////////////////////////////////////////
// simple_list (simple/small subset of list)

class CLASS_DECL_ca base_simple_list
{
public:
   base_simple_list(int32_t nNextOffset = 0);
   void Construct(int32_t nNextOffset);

// Operations
   bool is_empty() const;
   void add_head(void * p);
   void remove_all();
   void * get_head() const;
   void * get_next(void * p) const;
   bool remove(void * p);

// Implementation
   void * m_pHead;
   size_t m_nNextOffset;

   void ** GetNextPtr(void * p) const;   // somewhat trusting...
};

inline base_simple_list::base_simple_list(int32_t nNextOffset)
   { m_pHead = NULL; m_nNextOffset = nNextOffset; }
inline void base_simple_list::Construct(int32_t nNextOffset)
   { m_nNextOffset = nNextOffset; }
inline bool base_simple_list::is_empty() const
   { return m_pHead == NULL; }
inline void ** base_simple_list::GetNextPtr(void * p) const
   { return (void **)((BYTE*)p+m_nNextOffset); }
inline void base_simple_list::remove_all()
   { m_pHead = NULL; }
inline void * base_simple_list::get_head() const
   { return m_pHead; }
inline void * base_simple_list::get_next(void * prevElement) const
   { return *GetNextPtr(prevElement); }

template < class TYPE >
class simple_list : public base_simple_list
{
public:

   class item
   {
      item * m_pnext;
      TYPE m_value;
   };


   simple_list(int32_t nNextOffset = 0)
      : base_simple_list(nNextOffset) { }
   void add_head(TYPE p)
      { base_simple_list::add_head(p); }
   TYPE get_head()
      { return (TYPE)base_simple_list::get_head(); }
   TYPE get_next(TYPE p)
      { return (TYPE)base_simple_list::get_next(p); }
   bool remove(TYPE p)
      { return base_simple_list::remove((TYPE)p); }
   operator TYPE();      
};

template<class TYPE>
inline simple_list<TYPE>::operator TYPE()
{ 
   return (TYPE)simple_list::get_head(); 
}
