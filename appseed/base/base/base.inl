#pragma once


template<class TYPE>
void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE), FALSE));
#ifdef WINDOWS
   &dumpcontext; // not used
   pElements;  // not used
   nCount; // not used
#endif
   // default does nothing
}


template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount)
{
   ENSURE(nCount == 0 || pDest != 0 && pSrc != 0);
   ASSERT(nCount == 0 ||
      __is_valid_address(pDest, (size_t)nCount * sizeof(TYPE)));
   ASSERT(nCount == 0 ||
      __is_valid_address(pSrc, (size_t)nCount * sizeof(TYPE)));

   // default is element-copy using assignment
   while (nCount--)
      *pDest++ = *pSrc++;
}



inline void * __cdecl operator new(size_t nSize) throw (std::bad_alloc)
{
   return memory_alloc(nSize);
}

inline void * __cdecl operator new(size_t nSize, void * p)
{
   UNREFERENCED_PARAMETER(nSize);
   return p;
}
#define __PLACEMENT_NEW_INLINE


inline void __cdecl operator delete(void * p, void * palloc)
{
   UNREFERENCED_PARAMETER(p);
   UNREFERENCED_PARAMETER(palloc);
}


inline void __cdecl operator delete(void * p)
{
   memory_free(p);
}

inline void * __cdecl operator new[](size_t nSize) throw (std::bad_alloc);
{
   return ::operator new(nSize);
}

inline void __cdecl operator delete[](void * p)
{
   ::operator delete(p);
}





//CLASS_DECL_c void initialize_primitive_heap();
//CLASS_DECL_c void finalize_primitive_heap();


class CLASS_DECL_c c_class
{
public:


   static c_class s_cclass;


   c_class();
   c_class(const c_class &);
   virtual ~c_class();


};

inline CLASS_DECL_c void * __cdecl operator new (size_t size, const c_class &)
{
   return memory_alloc(size);
}

inline CLASS_DECL_c void * __cdecl operator new[](size_t size, const c_class &)
{
   return memory_alloc(size);
}


#define C_NEW new(c_class::s_cclass)



#endif


inline void * __cdecl operator new(size_t nSize, const char * lpszFileName, int32_t nLine)
{
   return ::operator new(nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void * __cdecl operator new[](size_t nSize, const char * lpszFileName, int32_t nLine) throw (std::bad_alloc)
{
   return ::operator new[](nSize, _NORMAL_BLOCK, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * pData, const char * /* lpszFileName */,  int32_t /* nLine */)
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}

inline void __cdecl operator delete[](void * pData, const char * /* lpszFileName */,  int32_t /* nLine */) throw()
{
   ::operator delete(pData, _NORMAL_BLOCK, NULL, -1);
}



inline void * __cdecl operator new(size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   return memory_alloc_dbg(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete(void * p, int32_t nType, const char * /* lpszFileName */, int32_t /* nLine */)
{
   memory_free_dbg(p, nType);
}

inline void * __cdecl operator new[](size_t nSize, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   return ::operator new(nSize, nType, lpszFileName, nLine);
}

inline void __cdecl operator delete[](void * p, int32_t nType, const char * lpszFileName, int32_t nLine)
{
   ::operator delete(p, nType, lpszFileName, nLine);
}
