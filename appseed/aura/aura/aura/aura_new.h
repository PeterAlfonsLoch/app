#define __NORMAL_BLOCK    1



#if defined(SOLARIS)

#define inplace_new_throw_spec
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()

#elif defined(MACOS)

#define inplace_new_throw_spec throw ()
#define new_throw_spec throw (std::bad_alloc)
#define del_throw_spec throw()

#else

#define inplace_new_throw_spec
#define new_throw_spec
#define del_throw_spec 

#endif


void * __cdecl operator new(size_t nSize, void * p) inplace_new_throw_spec;
void __cdecl operator delete(void * p, void * palloc) del_throw_spec;

void * __cdecl operator new(size_t nSize) new_throw_spec;
void __cdecl operator delete(void * p) del_throw_spec;

void * __cdecl operator new[](size_t nSize) new_throw_spec;
void __cdecl operator delete[](void * p) del_throw_spec;


CLASS_DECL_AURA void * __cdecl operator new(size_t nSize, const char * lpszFileName, int32_t nLine) new_throw_spec;
CLASS_DECL_AURA void __cdecl operator delete(void * p, const char * lpszFileName, int32_t nLine) del_throw_spec;
CLASS_DECL_AURA void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int32_t nLine) new_throw_spec;
CLASS_DECL_AURA void __cdecl operator delete[](void * p, const char * lpszFileName, int32_t nLine) del_throw_spec;


#define DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION \
   public: \
   void * operator new(size_t i, const char * lpszFileName, int32_t iLine) \
{ \
   return ::operator new(i, lpszFileName, iLine); \
} \
   void * operator new(size_t i) \
{ \
   return ::operator new(i); \
} \
   void * operator new(size_t size, void * p) \
{ \
   return ::operator new(size, p); \
} \
   void operator delete(void * p, const char * lpszFileName, int32_t iLine) \
{ \
   ::operator delete(p, lpszFileName, iLine); \
} \
   void operator delete(void * p) \
{ \
   ::operator delete(p); \
} \
   void operator delete(void * p, void * pvoid) \
{ \
   ::operator delete(p, pvoid); \
} \







void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine);
void __cdecl operator delete(void * p, int32_t nType, const char * lpszFileName, int32_t nLine);
void __cdecl operator delete[](void * p, int32_t nType, const char * lpszFileName, int32_t nLine);


