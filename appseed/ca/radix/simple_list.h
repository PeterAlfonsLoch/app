#pragma once

/////////////////////////////////////////////////////////////////////////////
// simple_list (simple/small subset of list)

class CLASS_DECL_ca simple_list
{
public:
   simple_list(int nNextOffset = 0);
   void Construct(int nNextOffset);

// Operations
   WINBOOL is_empty() const;
   void add_head(void * p);
   void remove_all();
   void * get_head() const;
   void * get_next(void * p) const;
   WINBOOL remove(void * p);

// Implementation
   void * m_pHead;
   size_t m_nNextOffset;

   void ** GetNextPtr(void * p) const;   // somewhat trusting...
};

inline simple_list::simple_list(int nNextOffset)
   { m_pHead = NULL; m_nNextOffset = nNextOffset; }
inline void simple_list::Construct(int nNextOffset)
   { ASSERT(m_pHead == NULL); m_nNextOffset = nNextOffset; }
inline WINBOOL simple_list::is_empty() const
   { return m_pHead == NULL; }
inline void ** simple_list::GetNextPtr(void * p) const
   { ENSURE_ARG(p != NULL); return (void **)((BYTE*)p+m_nNextOffset); }
inline void simple_list::remove_all()
   { m_pHead = NULL; }
inline void * simple_list::get_head() const
   { return m_pHead; }
inline void * simple_list::get_next(void * prevElement) const
   { return *GetNextPtr(prevElement); }

template<class TYPE>
class typed_simple_list : public simple_list
{
public:
   typed_simple_list(int nNextOffset = 0)
      : simple_list(nNextOffset) { }
   void add_head(TYPE p)
      { simple_list::add_head(p); }
   TYPE get_head()
      { return (TYPE)simple_list::get_head(); }
   TYPE get_next(TYPE p)
      { return (TYPE)simple_list::get_next(p); }
   WINBOOL remove(TYPE p)
      { return simple_list::remove((TYPE)p); }
   operator TYPE();      
};
template<class TYPE>
inline typed_simple_list<TYPE>::operator TYPE()
{ 
   return (TYPE)simple_list::get_head(); 
}
