#pragma once


extern HANDLE g_hmutexCa2Alloc;

#ifdef _DEBUG
// Special _CLIENT_BLOCK type to identifiy CObjects.
#define _AFX_CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))
#endif

// Memory tracking allocation
#undef new
CLASS_DECL_ca void * __cdecl operator new(size_t nSize, const char * lpszFileName, int nLine);
#define new DEBUG_NEW
CLASS_DECL_ca void __cdecl operator delete(void * p, const char * lpszFileName, int nLine);

#undef new
void * __cdecl operator new[](size_t);
CLASS_DECL_ca void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int nLine);
#define new DEBUG_NEW
CLASS_DECL_ca void __cdecl operator delete[](void * p, const char * lpszFileName, int nLine);
void __cdecl operator delete[](void *);



/*CLASS_DECL_ca extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL_ca extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca extern void   (*g_pfnca2_free)(void * pvoid, int iBlockType);*/

/*CLASS_DECL_ca void * ca2_alloc(size_t size);
CLASS_DECL_ca void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void * ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void   ca2_free(void * pvoid, int iBlockType);*/


CLASS_DECL_ca void * _ca2_alloc(size_t size);
CLASS_DECL_ca void * _ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void * _ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL_ca void   _ca2_free(void * pvoid, int iBlockType);
CLASS_DECL_ca size_t _ca2_msize(void * pvoid, int iBlockType);

CLASS_DECL_ca void use_ca2_allocator();


#ifdef new
#undef new
#endif

void * __cdecl operator new(size_t nSize);

void __cdecl operator delete(void * p);
void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);



#define DECLARE_AND_IMPLEMENT_DEFAULT_ALLOCATION \
   public: \
      void * operator new(size_t i, const char * lpszFileName, int iLine) \
      { \
         return ::operator new(i, lpszFileName, iLine); \
      } \
      void * operator new(size_t i) \
      { \
         return ::operator new(i); \
      } \
      void operator delete(void * p, const char * lpszFileName, int iLine) \
      { \
         ::operator delete(p, lpszFileName, iLine); \
      } \
      void operator delete(void * p) \
      { \
         ::operator delete(p); \
      } \





void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine);
void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine);

/////////////////////////////////////////////////////////////////////////////
// Debug primitive::memory globals and implementation helpers

#undef new
#undef delete

void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine);
void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine);
CLASS_DECL_ca void __cdecl operator delete(void * p, int nType, const char * /* lpszFileName */, int nLine);
CLASS_DECL_ca void __cdecl operator delete[](void * p, int nType, const char * lpszFileName, int nLine);



inline void * __cdecl operator new(size_t nSize, const char * lpszFileName, int nLine)
{
   return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int nLine)
{
   return ::operator new[](nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * pData, const char * /* lpszFileName */,  int /* nLine */)
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}

inline void __cdecl operator delete[](void * pData, const char * /* lpszFileName */,  int /* nLine */)
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}



inline void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine)
{
   return ca2_alloc_dbg(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * p, int nType, const char * /* lpszFileName */, int /* nLine */)
{
    ca2_free_dbg(p, nType);
}

inline void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine)
{
   return ::operator new(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete[](void * p, int nType, const char * lpszFileName, int nLine)
{
   ::operator delete(p, nType, lpszFileName, nLine);
}




