#pragma once

#include "definition.h"

#include "core.h"


#include "simple_collection.h"
#include "exception.h"

#define _ATL_TYPELIB_INDEX_LENGTH 10
#define _ATL_QUOTES_SPACE 2


/*
extern "C" const GUID LIBID_ATLLib;
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




namespace _template
{


#define _ATL_CATMAP_ENTRY_END 0
#define _ATL_CATMAP_ENTRY_IMPLEMENTED 1
#define _ATL_CATMAP_ENTRY_REQUIRED 2

/*typedef HRESULT (WINAPI _ATL_CREATORFUNC)(void * pv, REFIID riid, LPVOID* ppv);
typedef HRESULT (WINAPI _ATL_CREATORARGFUNC)(void * pv, REFIID riid, LPVOID* ppv, DWORD_PTR dw);
typedef HRESULT (WINAPI _ATL_MODULEFUNC)(DWORD_PTR dw);
typedef const char * (WINAPI _ATL_DESCRIPTIONFUNC)();
typedef const struct _ATL_CATMAP_ENTRY* (_ATL_CATMAPFUNC)();
typedef void (__stdcall _ATL_TERMFUNC)(DWORD_PTR dw);

struct _ATL_TERMFUNC_ELEM
{
   _ATL_TERMFUNC* pFunc;
   DWORD_PTR dw;
   _ATL_TERMFUNC_ELEM* pNext;
};
*/
/*
struct _ATL_OBJMAP_ENTRY20
{
   const CLSID* pclsid;
   HRESULT (WINAPI *pfnUpdateRegistry)(BOOL bRegister);
   _ATL_CREATORFUNC* pfnGetClassObject;
   _ATL_CREATORFUNC* pfnCreateInstance;
   IUnknown* pCF;
   DWORD dwRegister;
   _ATL_DESCRIPTIONFUNC* pfnGetObjectDescription;
};
*/

// Can't inherit from _ATL_OBJMAP_ENTRY20
// because it messes up the OBJECT_MAP macros
/*struct _ATL_OBJMAP_ENTRY30
{
   const CLSID* pclsid;
   HRESULT (WINAPI *pfnUpdateRegistry)(BOOL bRegister);
   _ATL_CREATORFUNC* pfnGetClassObject;
   _ATL_CREATORFUNC* pfnCreateInstance;
   IUnknown* pCF;
   DWORD dwRegister;
   _ATL_DESCRIPTIONFUNC* pfnGetObjectDescription;
   _ATL_CATMAPFUNC* pfnGetCategoryMap;
   HRESULT WINAPI RevokeClassObject()
   {
      if (dwRegister == 0)
         return S_OK;
      return CoRevokeClassObject(dwRegister);
   }
   HRESULT WINAPI RegisterClassObject(DWORD dwClsContext, DWORD dwFlags)
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
// Added in _template 3.0
   void (WINAPI *pfnObjectMain)(bool bStarting);
};

typedef _ATL_OBJMAP_ENTRY30 _ATL_OBJMAP_ENTRY;*/

// Auto Object Map
/*extern "C"
{
__declspec(selectany) _ATL_OBJMAP_ENTRY* __pobjMapEntryFirst = NULL;
__declspec(selectany) _ATL_OBJMAP_ENTRY* __pobjMapEntryLast = NULL;
}


struct _ATL_REGMAP_ENTRY
{
   LPCOLESTR     szKey;
   LPCOLESTR     szData;
};

struct _AtlCreateWndData
{
   void * m_pThis;
   DWORD m_dwThreadID;
   _AtlCreateWndData* m_pNext;
};
*/
/*
// perfmon registration/unregistration function definitions
typedef HRESULT (*_ATL_PERFREGFUNC)(HINSTANCE hDllInstance);
typedef HRESULT (*_ATL_PERFUNREGFUNC)();
__declspec(selectany) _ATL_PERFREGFUNC _pPerfRegFunc = NULL;
__declspec(selectany) _ATL_PERFUNREGFUNC _pPerfUnRegFunc = NULL;
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
         AtlThrow( hr );
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

   ATLASSERT( !m_bLocked );
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
   ATLASSUME( m_bLocked );
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


// Used by COM related code in _template
/*struct _ATL_COM_MODULE70
{
   UINT cbSize;
   HINSTANCE m_hInstTypeLib;
   _ATL_OBJMAP_ENTRY** m_ppAutoObjMapFirst;
   _ATL_OBJMAP_ENTRY** m_ppAutoObjMapLast;
   CComCriticalSection m_csObjMap;
};
typedef _ATL_COM_MODULE70 _ATL_COM_MODULE;*/


// Used by Windowing code in _template
/*struct _ATL_WIN_MODULE70
{
   UINT cbSize;
   CComCriticalSection m_csWindowCreate;
   _AtlCreateWndData* m_pCreateWndList;
   CSimpleArray<ATOM> m_rgWindowClassAtoms;
};
typedef _ATL_WIN_MODULE70 _ATL_WIN_MODULE;*/


/*struct _ATL_MODULE70
{
   UINT cbSize;
   LONG m_nLockCnt;
   _ATL_TERMFUNC_ELEM* m_pTermFuncs;
   CComCriticalSection m_csStaticDataInitAndTypeInfo;
};
typedef _ATL_MODULE70 _ATL_MODULE;*/


/////////////////////////////////////////////////////////////////////////////
//This define makes debugging asserts easier.
/*#define _ATL_SIMPLEMAPENTRY ((_template::_ATL_CREATORARGFUNC*)1)

struct _ATL_INTMAP_ENTRY
{
   const IID* piid;       // the interface id (IID)
   DWORD_PTR dw;
   _ATL_CREATORARGFUNC* pFunc; //NULL:end, 1:offset, n:ptr
};*/

/////////////////////////////////////////////////////////////////////////////
// Global Functions

/////////////////////////////////////////////////////////////////////////////
// QI Support

/*ATLAPI AtlInternalQueryInterface(void * pThis,
   const _ATL_INTMAP_ENTRY* pEntries, REFIID iid, void ** ppvObject);*/

/////////////////////////////////////////////////////////////////////////////
// Inproc Marshaling helpers

/*ATLAPI AtlFreeMarshalStream(IStream* pStream);
ATLAPI AtlMarshalPtrInProc(IUnknown* pUnk, const IID& iid, IStream** ppStream);
ATLAPI AtlUnmarshalPtr(IStream* pStream, const IID& iid, IUnknown** ppUnk);

ATLAPI_(BOOL) AtlWaitWithMessageLoop(HANDLE hEvent);

/////////////////////////////////////////////////////////////////////////////
// Connection Point Helpers

ATLAPI AtlAdvise(IUnknown* pUnkCP, IUnknown* pUnk, const IID& iid, LPDWORD pdw);
ATLAPI AtlUnadvise(IUnknown* pUnkCP, const IID& iid, DWORD dw);
*/
/////////////////////////////////////////////////////////////////////////////
// IDispatch Error handling

//ATLAPI AtlSetErrorInfo(const CLSID& clsid, LPCOLESTR lpszDesc,
  // DWORD dwHelpID, LPCOLESTR lpszHelpFile, const IID& iid, HRESULT hRes,
//   HINSTANCE hInst);

/////////////////////////////////////////////////////////////////////////////
// Module

//ATLAPI AtlComModuleRegisterClassObjects(_ATL_COM_MODULE* pComModule, DWORD dwClsContext, DWORD dwFlags);
//ATLAPI AtlComModuleRevokeClassObjects(_ATL_COM_MODULE* pComModule);

//ATLAPI AtlComModuleGetClassObject(_ATL_COM_MODULE* pComModule, REFCLSID rclsid, REFIID riid, LPVOID* ppv);

//ATLAPI AtlComModuleRegisterServer(_ATL_COM_MODULE* pComModule, BOOL bRegTypeLib, const CLSID* pCLSID = NULL);
//ATLAPI AtlComModuleUnregisterServer(_ATL_COM_MODULE* pComModule, BOOL bUnRegTypeLib, const CLSID* pCLSID = NULL);

//ATLAPI AtlRegisterClassCategoriesHelper( REFCLSID clsid, const struct _ATL_CATMAP_ENTRY* pCatMap, BOOL bRegister );

/*ATLAPI AtlUpdateRegistryFromResourceD(HINSTANCE hInst, LPCOLESTR lpszRes,
   BOOL bRegister, struct _ATL_REGMAP_ENTRY* pMapEntries, IRegistrar* pReg = NULL);*/

/*ATLAPI AtlRegisterTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex);
ATLAPI AtlUnRegisterTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex);
ATLAPI AtlLoadTypeLib(HINSTANCE hInstTypeLib, LPCOLESTR lpszIndex, BSTR* pbstrPath, ITypeLib** ppTypeLib);

ATLAPI_(DWORD) AtlGetVersion(void * pReserved);*/

/*ATLAPI AtlModuleAddTermFunc(_ATL_MODULE* pModule, _ATL_TERMFUNC* pFunc, DWORD_PTR dw);
ATLAPI_(void) AtlCallTermFunc(_ATL_MODULE* pModule);

ATLAPI AtlWinModuleInit(_ATL_WIN_MODULE* pWinModule);
ATLAPIINL AtlWinModuleTerm(_ATL_WIN_MODULE* pWinModule, HINSTANCE hInst);

ATLAPI_(void) AtlWinModuleAddCreateWndData(_ATL_WIN_MODULE* pWinModule, _AtlCreateWndData* pData, void * pObject);
ATLAPI_(void *) AtlWinModuleExtractCreateWndData(_ATL_WIN_MODULE* pWinModule);
*/
/////////////////////////////////////////////////////////////////////////////
// get Registrar object from _template DLL.

//extern "C" CLASS_DECL_ca HRESULT __stdcall AtlCreateRegistrar(IRegistrar** ppReg);

/////////////////////////////////////////////////////////////////////////////
// GUID comparison
/*inline BOOL WINAPI InlineIsEqualUnknown(REFGUID rguid1)
{
   return (
     ((PLONG) &rguid1)[0] == 0 &&
     ((PLONG) &rguid1)[1] == 0 &&
#ifdef _ATL_BYTESWAP
     ((PLONG) &rguid1)[2] == 0xC0000000 &&
     ((PLONG) &rguid1)[3] == 0x00000046);
#else
     ((PLONG) &rguid1)[2] == 0x000000C0 &&
     ((PLONG) &rguid1)[3] == 0x46000000);
#endif
}
*/


/*template <class T>
const char * AtlDebugGetClassName(T*)
{
//#ifdef _DEBUG
   const _ATL_INTMAP_ENTRY* pEntries = T::_GetEntries();
   return (const char *)pEntries[-1].dw;
//#else
//   return NULL;
//#endif
}*/

// Validation macro for OUT pointer
// Used in QI and CreateInstance
/*#define _ATL_VALIDATE_OUT_POINTER(x)\
   do {               \
   ATLASSERT(x != NULL);   \
   if (x == NULL)         \
      return E_POINTER;   \
   *x = NULL;            \
   } while(0)*/

   /////////////////////////////////////////////////////////////////////////////
   // Win32 libraries

   //#ifndef _ATL_NO_DEFAULT_LIBS
   /*#pragma comment(lib, "kernel32.lib")
   #pragma comment(lib, "user32.lib")
   #pragma comment(lib, "advapi32.lib")
   //#pragma comment(lib, "ole32.lib")
   #pragma comment(lib, "shell32.lib")
   //#pragma comment(lib, "oleaut32.lib")
   #pragma comment(lib, "uuid.lib")
   #pragma comment(lib, "shlwapi.lib")
   //#endif  // !_ATL_NO_DEFAULT_LIBS*/


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

}   // namespace _template




