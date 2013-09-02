#pragma once


inline void * fixed_alloc_sync::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   register int32_t i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   register void * p = NULL;
   m_protectptra.get_data()[i]->lock();
   try
   {
      p = m_allocptra.get_data()[i]->Alloc();
   }
   catch(...)
   {
   }
   m_protectptra.get_data()[i]->unlock();
   if(p == NULL)
      return NULL;
   ((int32_t *) p)[0] = i;
   return &((int32_t *)p)[1];
}

inline void fixed_alloc_sync::Free(void * p)
{
   if (p == NULL)
      return;
   register int32_t i = ((int32_t *)p)[-1];
   m_protectptra.get_data()[i]->lock();
   try
   {
      m_allocptra.get_data()[i]->Free(&((int32_t *)p)[-1]);
   }
   catch(...)
   {
   }
   m_protectptra.get_data()[i]->unlock();
}



inline void * fixed_alloc::Alloc()
{

   // veripseudo-random generator, don't need to be
   // perfectly sequential or perfectly distributed,
   // just fair well distributed
   // but very important is extremely fast
   register int32_t i = m_i;
   if(i >= m_iShareCount)
   {
      i = 0;
      m_i = 1;
   }
   else
   {
      m_i++;
   }


   register void * p  = m_allocptra.get_data()[i]->Alloc();

   ((int32_t *) p)[0] = i;

   return &((int32_t *)p)[1];

}

inline void fixed_alloc::Free(void * p)
{

   if (p == NULL)
      return;

   register int32_t i = ((int32_t *)p)[-1];

   m_allocptra.get_data()[i]->Free(&((int32_t *)p)[-1]);

}




//#ifndef DEBUG

#undef new

// DECLARE_FIXED_ALLOC -- used in class definition
/*#define DECLARE_FIXED_ALLOC(class_name) \
public: \
   void * operator new(size_t size) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void * operator new(size_t, void * p) \
      { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t size, const char *, int32_t) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void operator delete(void * p, const char *, int32_t) { s_alloc.Free(p); } \
protected: \
   static fixed_alloc s_alloc; \
public: \


// IMPLEMENT_FIXED_ALLOC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC(class_name, block_size) \
fixed_alloc class_name::s_alloc(sizeof(class_name), block_size) \

// DECLARE_FIXED_ALLOC -- used in class definition
#define DECLARE_FIXED_ALLOC_NOSYNC(class_name) \
public: \
   void * operator new(size_t size) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void * operator new(size_t, void * p) \
      { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t size, const char *, int32_t) \
   { \
      ASSERT(size == s_alloc.GetAllocSize()); \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
protected: \
   static fixed_alloc_no_sync s_alloc; \
public : \


// IMPLEMENT_FIXED_ALLOC_NOSYNC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC_NOSYNC(class_nbame, block_size) \
fixed_alloc_no_sync class_name::s_alloc(sizeof(class_name), block_size) \

#define new DEBUG_NEW

#else //!DEBUG

#define DECLARE_FIXED_ALLOC(class_name) // nothing in debug
#define IMPLEMENT_FIXED_ALLOC(class_name, block_size) // nothing in debug
#define DECLARE_FIXED_ALLOC_NOSYNC(class_name) // nothing in debug
#define IMPLEMENT_FIXED_ALLOC_NOSYNC(class_name, block_size) // nothing in debug

#endif //!DEBUG


*/


extern CLASS_DECL_c fixed_alloc_array g_fixedalloca;
