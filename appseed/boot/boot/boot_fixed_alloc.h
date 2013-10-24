#pragma once


// after static initialization dawn at base library, fixed alloc can pragmatically be defined
// as MACRO from boot to upper.

// DECLARE_FIXED_ALLOC -- used in class definition
#define DECLARE_FIXED_ALLOC(class_name) \
public: \
   void * operator new(size_t) { return s_alloc.Alloc(); } \
   void * operator new(size_t, void * p) { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t, const char *, int32_t) { return s_alloc.Alloc(); } \
   void operator delete(void * p, const char *, int32_t) { s_alloc.Free(p); } \
   static fixed_alloc s_alloc;


// IMPLEMENT_FIXED_ALLOC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC(class_name, block_size) \
fixed_alloc class_name::s_alloc(sizeof(class_name), block_size)


// DECLARE_FIXED_ALLOC_NOSYNC -- used in class definition
#define DECLARE_FIXED_ALLOC_NOSYNC(class_name) \
public: \
   void * operator new(size_t size) \
   { \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
   void * operator new(size_t, void * p) \
      { return p; } \
   void operator delete(void * p) { s_alloc.Free(p); } \
   void * operator new(size_t size, const char *, int32_t) \
   { \
      UNUSED(size); \
      return s_alloc.Alloc(); \
   } \
protected: \
   static fixed_alloc_no_sync s_alloc; \
public : \


// IMPLEMENT_FIXED_ALLOC_NOSYNC -- used in class implementation file
#define IMPLEMENT_FIXED_ALLOC_NOSYNC(class_nbame, block_size) \
fixed_alloc_no_sync class_name::s_alloc(sizeof(class_name), block_size) \

