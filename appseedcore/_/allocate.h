#pragma once


extern HANDLE g_hmutexCa2Alloc;

#ifdef _DEBUG
// Special _CLIENT_BLOCK type to identifiy CObjects.
#define _AFX_CLIENT_BLOCK (_CLIENT_BLOCK|(0xc0<<16))
#endif

// Memory tracking allocation
#undef new
CLASS_DECL__ void * __cdecl operator new(size_t nSize, const char * lpszFileName, int nLine);
#define new DEBUG_NEW
CLASS_DECL__ void __cdecl operator delete(void * p, const char * lpszFileName, int nLine);

#undef new
void * __cdecl operator new[](size_t);
CLASS_DECL__ void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int nLine);
#define new DEBUG_NEW
CLASS_DECL__ void __cdecl operator delete[](void * p, const char * lpszFileName, int nLine);
void __cdecl operator delete[](void *);



CLASS_DECL__ extern void * (*g_pfnca2_alloc)(size_t size);
CLASS_DECL__ extern void * (*g_pfnca2_alloc_dbg)(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ extern void * (*g_pfnca2_realloc)(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ extern void   (*g_pfnca2_free)(void * pvoid, int iBlockType);

CLASS_DECL__ void * ca2_alloc(size_t size);
CLASS_DECL__ void * ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ void * ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ void   ca2_free(void * pvoid, int iBlockType);


CLASS_DECL__ void * _ca2_alloc(size_t size);
CLASS_DECL__ void * _ca2_alloc_dbg(size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ void * _ca2_realloc(void * pvoid, size_t nSize, int nBlockUse, const char * szFileName, int nLine);
CLASS_DECL__ void   _ca2_free(void * pvoid, int iBlockType);


#ifdef new
#undef new
#endif

void * __cdecl operator new(size_t nSize);

void __cdecl operator delete(void * p);
void * __cdecl operator new[](size_t nSize);
void __cdecl operator delete[](void * p);

//CLASS_DECL__ void __cdecl operator delete(void * p, int nType, const char * /* lpszFileName */, int nLine);
//CLASS_DECL__ void __cdecl operator delete[](void * p, int nType, const char * lpszFileName, int nLine);


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

void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine);
void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine);


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
   ::operator delete(pData);
}

inline void __cdecl operator delete[](void * pData, const char * /* lpszFileName */,  int /* nLine */)
{
   ::operator delete(pData);
}


inline void * __cdecl operator new(size_t nSize)
{
   return ca2_alloc(nSize);
}

inline void __cdecl operator delete(void * p)
{
   ca2_free(p, _NORMAL_BLOCK);
}

inline void * __cdecl operator new[](size_t nSize)
{
   return ::operator new(nSize);
}

inline void __cdecl operator delete[](void * p)
{
   ::operator delete(p);
}

inline void * __cdecl operator new(size_t nSize, int nType, const char * lpszFileName, int nLine)
{
   return ca2_alloc_dbg(nSize, nType, lpszFileName, nLine);
}

///*inline void __cdecl operator delete(void * p, int nType, const char * /* lpszFileName */, int /* nLine */)
//{
  // ca2_free(p, nType);
//}

inline void * __cdecl operator new[](size_t nSize, int nType, const char * lpszFileName, int nLine)
{
   return ::operator new(nSize, nType, lpszFileName, nLine);
}

/*inline void __cdecl operator delete[](void * p, int nType, const char * lpszFileName, int nLine)
{
   ::operator delete(p, nType, lpszFileName, nLine);
}*/




