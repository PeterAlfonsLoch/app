#pragma once


struct __POSITION {};
typedef __POSITION* POSITION;
#define BEFORE_START_POSITION ((POSITION)-1L)




//#include "_flags.h"


// the two functions below are deprecated.  Use a constructor/destructor instead.
//#pragma deprecated( DestructElements )
//#pragma deprecated( ConstructElements )

template<class TYPE>
inline void CopyElements(TYPE* pDest, const TYPE* pSrc, ::count nCount);
/*
template<class TYPE>
void SerializeElements(CArchive& ar, TYPE* pElements, ::count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE)));

   // default is bit-wise read/write
   if (ar.IsStoring())
   {
     TYPE* pData;
     uint_ptr nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToWrite;

       nElementsToWrite = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.write(pData, nElementsToWrite*sizeof(TYPE));
       nElementsLeft -= nElementsToWrite;
       pData += nElementsToWrite;
     }
   }
   else
   {
     TYPE* pData;
     uint_ptr nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToRead;

       nElementsToRead = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.EnsureRead(pData, nElementsToRead*sizeof(TYPE));
       nElementsLeft -= nElementsToRead;
       pData += nElementsToRead;
     }
   }
}

template<class TYPE>
void SerializeElementsInsertExtract(CArchive& ar, TYPE* pElements, 
   ::count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT((nCount == 0) || 
      (__is_valid_address(pElements, nCount*sizeof(TYPE))));

   if (nCount == 0 || pElements == NULL)
   {
      return;
   }

   if (ar.IsStoring())
   {
      for (; nCount--; ++pElements)
         ar << *pElements;
   }
   else
   {
      for (; nCount--; ++pElements)
         ar >> *pElements;
   }
}
*/

template<class TYPE>
inline void dump_elements(dump_context & dumpcontext, const TYPE* pElements, ::count nCount);


// the two functions below are deprecated.  Use a constructor/destructor instead.
//#pragma deprecated( DestructElements )
//#pragma deprecated( ConstructElements )

/*
template<class TYPE>
void SerializeElements(CArchive& ar, TYPE* pElements, ::count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT(nCount == 0 ||
      __is_valid_address(pElements, (size_t)nCount * sizeof(TYPE)));

   // default is bit-wise read/write
   if (ar.IsStoring())
   {
     TYPE* pData;
     uint_ptr nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToWrite;

       nElementsToWrite = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.write(pData, nElementsToWrite*sizeof(TYPE));
       nElementsLeft -= nElementsToWrite;
       pData += nElementsToWrite;
     }
   }
   else
   {
     TYPE* pData;
     uint_ptr nElementsLeft;

     nElementsLeft = nCount;
     pData = pElements;
     while( nElementsLeft > 0 )
     {
       UINT nElementsToRead;

       nElementsToRead = UINT(__min(nElementsLeft, INT_MAX/sizeof(TYPE)));
       ar.EnsureRead(pData, nElementsToRead*sizeof(TYPE));
       nElementsLeft -= nElementsToRead;
       pData += nElementsToRead;
     }
   }
}

template<class TYPE>
void SerializeElementsInsertExtract(CArchive& ar, TYPE* pElements, 
   ::count nCount)
{
   ENSURE(nCount == 0 || pElements != NULL);
   ASSERT((nCount == 0) || 
      (__is_valid_address(pElements, nCount*sizeof(TYPE))));

   if (nCount == 0 || pElements == NULL)
   {
      return;
   }

   if (ar.IsStoring())
   {
      for (; nCount--; ++pElements)
         ar << *pElements;
   }
   else
   {
      for (; nCount--; ++pElements)
         ar >> *pElements;
   }
}
*/



template<class TYPE, class ARG_TYPE>
bool CompareElements(const TYPE* pElement1, const ARG_TYPE* pElement2)
{
	ENSURE(pElement1 != NULL && pElement2 != NULL);
	ASSERT(__is_valid_address(pElement1, sizeof(TYPE), FALSE));
	ASSERT(__is_valid_address(pElement2, sizeof(ARG_TYPE), FALSE));

	return *pElement1 == *pElement2;
}







#define _TYPELIB_INDEX_LENGTH 10
#define _QUOTES_SPACE 2


/*
extern "C" const GUID LIBID_Lib;
extern "C" const CLSID CLSID_Registrar;
extern "C" const IID IID_IRegistrar;
extern "C" const IID IID_IAxWinHostWindow;
extern "C" const IID IID_IAxWinAmbientDispatch;
extern "C" const IID IID_IInternalConnection;
extern "C" const IID IID_IDocHostUIHandlerDispatch;
extern "C" const IID IID_IAxWinHostWindowLic;
extern "C" const IID IID_IAxWinAmbientDispatchEx;
*/

#ifndef _delayimp_h
//extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif




namespace core
{


#define _CATMAP_ENTRY_END 0
#define _CATMAP_ENTRY_IMPLEMENTED 1
#define _CATMAP_ENTRY_REQUIRED 2

/*typedef HRESULT (WINAPI _CREATORFUNC)(void * pv, REFIID riid, LPVOID* ppv);
typedef HRESULT (WINAPI _CREATORARGFUNC)(void * pv, REFIID riid, LPVOID* ppv, uint_ptr dw);
typedef HRESULT (WINAPI _MODULEFUNC)(uint_ptr dw);
typedef const char * (WINAPI _DESCRIPTIONFUNC)();
typedef const struct _CATMAP_ENTRY* (_CATMAPFUNC)();
typedef void (__stdcall _TERMFUNC)(uint_ptr dw);

struct _TERMFUNC_ELEM
{
   _TERMFUNC* pFunc;
   uint_ptr dw;
   _TERMFUNC_ELEM* pNext;
};
*/
/*
struct _OBJMAP_ENTRY20
{
   const CLSID* pclsid;
   HRESULT (WINAPI *pfnUpdateRegistry)(bool bRegister);
   _CREATORFUNC* pfnGetClassObject;
   _CREATORFUNC* pfnCreateInstance;
   IUnknown* pCF;
   uint32_t dwRegister;
   _DESCRIPTIONFUNC* pfnGetObjectDescription;
};
*/

// Can't inherit from _OBJMAP_ENTRY20
// because it messes up the OBJECT_MAP macros
/*struct _OBJMAP_ENTRY30
{
   const CLSID* pclsid;
   HRESULT (WINAPI *pfnUpdateRegistry)(bool bRegister);
   _CREATORFUNC* pfnGetClassObject;
   _CREATORFUNC* pfnCreateInstance;
   IUnknown* pCF;
   uint32_t dwRegister;
   _DESCRIPTIONFUNC* pfnGetObjectDescription;
   _CATMAPFUNC* pfnGetCategoryMap;
   HRESULT WINAPI RevokeClassObject()
   {
      if (dwRegister == 0)
         return S_OK;
      return CoRevokeClassObject(dwRegister);
   }
   HRESULT WINAPI RegisterClassObject(uint32_t dwClsContext, uint32_t dwFlags)
   {
      IUnknown* p = NULL;
      if (pfnGetClassObject == NULL)
         return S_OK;
      HRESULT hRes = pfnGetClassObject(pfnCreateInstance, __uuidof(IUnknown), (LPVOID*) &p);
      if (SUCCEEDED(hRes))
         hRes = CoRegisterClassObject(*pclsid, p, dwClsContext, dwFlags, &dwRegister);
      if (p != NULL)
         p->Release();
      return hRes;
   }
// Added in core 3.0
   void (WINAPI *pfnObjectMain)(bool bStarting);
};

typedef _OBJMAP_ENTRY30 _OBJMAP_ENTRY;*/

// Auto Object Map
/*extern "C"
{
__declspec(selectany) _OBJMAP_ENTRY* __pobjMapEntryFirst = NULL;
__declspec(selectany) _OBJMAP_ENTRY* __pobjMapEntryLast = NULL;
}


struct _REGMAP_ENTRY
{
   LPCOLESTR     szKey;
   LPCOLESTR     szData;
};

struct _gen_CreateWndData
{
   void * m_pThis;
   uint32_t m_dwThreadID;
   _gen_CreateWndData* m_pNext;
};
*/
/*
// perfmon registration/unregistration function definitions
typedef HRESULT (*_PERFREGFUNC)(HINSTANCE hDllInstance);
typedef HRESULT (*_PERFUNREGFUNC)();
__declspec(selectany) _PERFREGFUNC _pPerfRegFunc = NULL;
__declspec(selectany) _PERFUNREGFUNC _pPerfUnRegFunc = NULL;
*/
/////////////////////////////////////////////////////////////////////////////
// Threading Model Support
/*
template< class TLock >
class CComCritSecLock
{
public:
   CComCritSecLock( TLock& cs, bool bInitialLock = true );
   ~CComCritSecLock() throw();

   HRESULT lock() throw();
   void unlock() throw();

// Implementation
private:
   TLock& m_cs;
   bool m_bLocked;

// Private to avoid accidental use
   CComCritSecLock( const CComCritSecLock& ) throw();
   CComCritSecLock& operator=( const CComCritSecLock& ) throw();
};

template< class TLock >
inline CComCritSecLock< TLock >::CComCritSecLock( TLock& cs, bool bInitialLock ) :
   m_cs( cs ),
   m_bLocked( false )
{
   if( bInitialLock )
   {
      HRESULT hr;

      hr = lock();
      if( FAILED( hr ) )
      {
         throw hresult_exception( hr );
      }
   }
}

template< class TLock >
inline CComCritSecLock< TLock >::~CComCritSecLock() throw()
{
   if( m_bLocked )
   {
      unlock();
   }
}

template< class TLock >
inline HRESULT CComCritSecLock< TLock >::lock() throw()
{
   HRESULT hr;

   ASSERT( !m_bLocked );
   hr = m_cs.lock();
   if( FAILED( hr ) )
   {
      return( hr );
   }
   m_bLocked = true;

   return( S_OK );
}

template< class TLock >
inline void CComCritSecLock< TLock >::unlock() throw()
{
   ASSUME( m_bLocked );
   m_cs.unlock();
   m_bLocked = false;
}*/

/*class CComMultiThreadModelNoCS
{
public:
   static ULONG WINAPI Increment(LPLONG p) throw() {return InterlockedIncrement(p);}
   static ULONG WINAPI Decrement(LPLONG p) throw() {return InterlockedDecrement(p);}
   typedef CComFakeCriticalSection AutoCriticalSection;
   typedef CComFakeCriticalSection AutoDeleteCriticalSection;
   typedef CComFakeCriticalSection CriticalSection;
   typedef CComMultiThreadModelNoCS ThreadModelNoCS;
};*/

/*class CComMultiThreadModel
{
public:
   static ULONG WINAPI Increment(LPLONG p) throw() {return InterlockedIncrement(p);}
   static ULONG WINAPI Decrement(LPLONG p) throw() {return InterlockedDecrement(p);}
   typedef CComAutoCriticalSection AutoCriticalSection;
   typedef CComAutoDeleteCriticalSection AutoDeleteCriticalSection;
   typedef CComCriticalSection CriticalSection;
   typedef CComMultiThreadModelNoCS ThreadModelNoCS;
};*/

/*class CComSingleThreadModel
{
public:
   static ULONG WINAPI Increment(LPLONG p) throw() {return ++(*p);}
   static ULONG WINAPI Decrement(LPLONG p) throw() {return --(*p);}
   typedef CComFakeCriticalSection AutoCriticalSection;
   typedef CComFakeCriticalSection AutoDeleteCriticalSection;
   typedef CComFakeCriticalSection CriticalSection;
   typedef CComSingleThreadModel ThreadModelNoCS;
};*/

/*
typedef CComMultiThreadModel CComObjectThreadModel;
typedef CComMultiThreadModel CComGlobalsThreadModel;
*/


// Used by COM related code in core
/*struct _COM_MODULE70
{
   UINT cbSize;
   HINSTANCE m_hInstTypeLib;
   _OBJMAP_ENTRY** m_ppAutoObjMapFirst;
   _OBJMAP_ENTRY** m_ppAutoObjMapLast;
   CComCriticalSection m_csObjMap;
};
typedef _COM_MODULE70 _COM_MODULE;*/


// Used by Windowing code in core
/*struct _WIN_MODULE70
{
   UINT cbSize;
   CComCriticalSection m_csWindowCreate;
   _gen_CreateWndData* m_pCreateWndList;
   CSimpleArray<ATOM> m_rgWindowClassAtoms;
};
typedef _WIN_MODULE70 _WIN_MODULE;*/


/*struct _MODULE70
{
   UINT cbSize;
   LONG m_nLockCnt;
   _TERMFUNC_ELEM* m_pTermFuncs;
   CComCriticalSection m_csStaticDataInitAndTypeInfo;
};
typedef _MODULE70 _MODULE;*/


/////////////////////////////////////////////////////////////////////////////
//This define makes debugging asserts easier.
/*#define _SIMPLEMAPENTRY ((::core::_CREATORARGFUNC*)1)

struct _INTMAP_ENTRY
{
   const IID* piid;       // the interface id (IID)
   uint_ptr dw;
   _CREATORARGFUNC* pFunc; //NULL:end, 1:offset, n:ptr
};*/

/////////////////////////////////////////////////////////////////////////////
// Global Functions

/////////////////////////////////////////////////////////////////////////////
// QI Support

/*API gen_InternalQueryInterface(void * pThis,
   const _INTMAP_ENTRY* pEntries, REFIID iid, void ** ppvObject);*/

/////////////////////////////////////////////////////////////////////////////
// Inproc Marshaling helpers

/*API gen_FreeMarshalStream(IStream* pStream);
API gen_MarshalPtrInProc(IUnknown* pUnk, const IID& iid, IStream** ppStream);
API gen_UnmarshalPtr(IStream* pStream, const IID& iid, IUnknown** ppUnk);

API_(bool) gen_WaitWithMessageLoop(HANDLE hEvent);

/////////////////////////////////////////////////////////////////////////////
// Connection Point Helpers

API gen_Advise(IUnknown* pUnkCP, IUnknown* pUnk, const IID& iid, LPDWORD pdw);
API gen_Unadvise(IUnknown* pUnkCP, const IID& iid, uint32_t dw);
*/
/////////////////////////////////////////////////////////////////////////////
// IDispatch Error handling

//API gen_SetErrorInfo(const CLSID& clsid, LPCOLESTR lpszDesc,
  // uint32_t dwHelpID, LPCOLESTR lpszHelpFile, const IID& iid, HRESULT hRes,
//   HINSTANCE hInst);

/////////////////////////////////////////////////////////////////////////////
// Module

//API gen_ComModuleRegisterClassObjects(_COM_MODULE* pComModule, uint32_t dwClsContext, uint32_t dwFlags);
//API gen_ComModuleRevokeClassObjects(_COM_MODULE* pComModule);

//API gen_ComModuleGetClassObject(_COM_MODULE* pComModule, REFCLSID rclsid, REFIID riid, LPVOID* ppv);

//API gen_ComModuleRegisterServer(_COM_MODULE* pComModule, bool bRegTypeLib, const CLSID* pCLSID = NULL);
//API gen_ComModuleUnregisterServer(_COM_MODULE* pComModule, bool bUnRegTypeLib, const CLSID* pCLSID = NULL);

//API gen_RegisterClassCategoriesHelper( REFCLSID clsid, const struct _CATMAP_ENTRY* pCatMap, bool bRegister );

/*API gen_UpdateRegistryFromResourceD(HINSTANCE hInst, LPCOLESTR lpszRes,
   bool bRegister, struct _REGMAP_ENTRY* pMapEntries, IRegistrar* pReg = NULL);*/

/*API gen_RegisterTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex);
API gen_UnRegisterTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex);
API gen_LoadTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex, BSTR* pbstrPath, ITypeLib** ppTypeLib);

API_(uint32_t) gen_GetVersion(void * pReserved);*/

/*API gen_ModuleAddTermFunc(_MODULE* pModule, _TERMFUNC* pFunc, uint_ptr dw);
API_() gen_CallTermFunc(_MODULE* pModule);

API gen_WinModuleInit(_WIN_MODULE* pWinModule);
APIINL gen_WinModuleTerm(_WIN_MODULE* pWinModule, HINSTANCE hInst);

API_() gen_WinModuleAddCreateWndData(_WIN_MODULE* pWinModule, _AtlCreateWndData* pData, void * pObject);
API_(void *) gen_WinModuleExtractCreateWndData(_WIN_MODULE* pWinModule);
*/
/////////////////////////////////////////////////////////////////////////////
// get Registrar object from core DLL.

//extern "C" CLASS_DECL_AURA HRESULT __stdcall gen_CreateRegistrar(IRegistrar** ppReg);

/////////////////////////////////////////////////////////////////////////////
// GUID comparison
/*inline bool WINAPI InlineIsEqualUnknown(REFGUID rguid1)
{
   return (
     ((PLONG) &rguid1)[0] == 0 &&
     ((PLONG) &rguid1)[1] == 0 &&
#ifdef _BYTESWAP
     ((PLONG) &rguid1)[2] == 0xC0000000 &&
     ((PLONG) &rguid1)[3] == 0x00000046);
#else
     ((PLONG) &rguid1)[2] == 0x000000C0 &&
     ((PLONG) &rguid1)[3] == 0x46000000);
#endif
}
*/


/*template <class T>
const char * gen_DebugGetClassName(T*)
{
//#ifdef DEBUG
   const _INTMAP_ENTRY* pEntries = T::_GetEntries();
   return (const char *)pEntries[-1].dw;
//#else
//   return NULL;
//#endif
}*/

// Validation macro for OUT pointer
// Used in QI and CreateInstance
/*#define _VALIDATE_OUT_POINTER(x)\
   do {               \
   ASSERT(x != NULL);   \
   if (x == NULL)         \
      return E_POINTER;   \
   *x = NULL;            \
   } while(0)*/

   /////////////////////////////////////////////////////////////////////////////
   // Win32 libraries

   //#ifndef _NO_DEFAULT_LIBS
   /*#pragma comment(lib, "kernel32.lib")
   #pragma comment(lib, "user32.lib")
   #pragma comment(lib, "advapi32.lib")
   //#pragma comment(lib, "ole32.lib")
   #pragma comment(lib, "shell32.lib")
   //#pragma comment(lib, "oleaut32.lib")
   #pragma comment(lib, "uuid.lib")
   #pragma comment(lib, "shlwapi.lib")
   //#endif  // !_NO_DEFAULT_LIBS*/


   inline index add_throw(index i1, index i2)
   {
      if(i1 > 0 && i2 > 0 && (i1 + i2) < 0)
      {
         throw 0;
      }
      return i1 + i2;
   }

   inline index multiply_throw(index i1, index i2)
   {
      return i1 * i2;
   }

}   // namespace core







template < class T >
class base_class
{
public:


   template < class T2 >
   inline static bool bases(T2 * p) 
   {
      return dynamic_cast < T * > (p) != NULL; 
   }

   template < class T2 >
   inline static bool bases(const smart_pointer < T2 > & sp) 
   {
      return dynamic_cast < T * > ((T2 *) sp.m_p) != NULL; 
   }

};




#define ASSERT_KINDOF(class_name, object) ASSERT(base_class < class_name > ::bases(object))
#define DYNAMIC_DOWNCAST(class_name, object) (dynamic_cast < class_name * > (object))
#define STATIC_DOWNCAST(class_name, object) (dynamic_cast<class_name*>(object))
#define STATIC_DOWNCAST_T(class_name, T1, object) (static_cast<class_name<T1>*>(::core::StaticDownCast(RUNTIME_CLASS_T(class_name, T1), object)))
#define STATIC_DOWNCAST_T2(class_name, T1, T2, object) (static_cast<class_name<T1, T2>*>(::core::StaticDownCast(RUNTIME_CLASS_T2(class_name, T1, T2), object)))
