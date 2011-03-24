#ifdef _AFX_INLINE
#ifndef AFX_INL_INCLUDE_GUARD
#define AFX_INL_INCLUDE_GUARD

// ::radix::object
_AFX_INLINE ::radix::object::radix::object()
   { common_construct(); }
_AFX_INLINE void ::radix::object::common_construct()
   { }
_AFX_INLINE ::radix::object::~::radix::object()
   { }
//_AFX_INLINE void ::radix::object::Serialize(CArchive&)
//   { /* ::radix::object does not serialize anything by default */ }
#undef new
_AFX_INLINE void * PASCAL ::radix::object::operator new(size_t, void * p)
   { return p; }
#define new DEBUG_NEW
#ifndef _DEBUG
// _DEBUG versions in afxmem.cpp
_AFX_INLINE void PASCAL ::radix::object::operator delete(void * p)
   { ::operator delete(p); }
#if _MSC_VER >= 1200
_AFX_INLINE void PASCAL ::radix::object::operator delete(void * p, void *)
   { ::operator delete(p); }
#endif
_AFX_INLINE void * PASCAL ::radix::object::operator new(size_t nSize)
   { return ::operator new(nSize); }
// _DEBUG versions in objcore.cpp
//_AFX_INLINE void ::radix::object::AssertValid() const
//   { /* no asserts in release builds */ }
//_AFX_INLINE void ::radix::object::Dump(dump_context&) const
//   { /* no dumping in release builds */ }
#endif //!_DEBUG
/*_AFX_INLINE const ::radix::object* AFX_CDECL AfxDynamicDownCast(::ca::type_info info, const ::radix::object* pObject)
   { return (const ::radix::object*)AfxDynamicDownCast(info, (::radix::object*)pObject); }
#ifdef _DEBUG
_AFX_INLINE const ::radix::object* AFX_CDECL AfxStaticDownCast(::ca::type_info info, const ::radix::object* pObject)
   { return (const ::radix::object*)AfxStaticDownCast(info, (::radix::object*)pObject); }*/
#endif

// exceptions
_AFX_INLINE base_exception::~base_exception()
   { }
_AFX_INLINE simple_exception::simple_exception()
   { m_bInitialized = FALSE; m_bLoaded = FALSE; }
_AFX_INLINE simple_exception::simple_exception(BOOL bAutoDelete)
   : base_exception(bAutoDelete) { m_bInitialized = FALSE; m_bLoaded = FALSE; }
_AFX_INLINE simple_exception::~simple_exception()
   { }

_AFX_INLINE memory_exception::memory_exception()
   : simple_exception() { }
_AFX_INLINE memory_exception::memory_exception(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE memory_exception::~memory_exception()
   { }
_AFX_INLINE CNotSupportedException::CNotSupportedException()
   : simple_exception() { }
_AFX_INLINE CNotSupportedException::CNotSupportedException(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE CNotSupportedException::~CNotSupportedException()
   { }
_AFX_INLINE CInvalidArgException::CInvalidArgException()
   : simple_exception() { }
_AFX_INLINE CInvalidArgException::CInvalidArgException(BOOL bAutoDelete, UINT nResourceID)
   : simple_exception(bAutoDelete) { m_nResourceID = nResourceID; }
_AFX_INLINE CInvalidArgException::~CInvalidArgException()
   { }
/*_AFX_INLINE CArchiveException::CArchiveException(int cause,
   const char * lpszFileName /* = NULL *//*)
   { m_cause = cause; m_strFileName = lpszFileName; }
   
_AFX_INLINE CArchiveException::~CArchiveException()
   { }*/


// dump_context
_AFX_INLINE int dump_context::GetDepth() const
   { return m_nDepth; }
_AFX_INLINE void dump_context::SetDepth(int nNewDepth)
   { m_nDepth = nNewDepth; }
_AFX_INLINE dump_context::dump_context(const dump_context& /* graphicsSrc */)
   { }
_AFX_INLINE void dump_context::operator=(const dump_context& /* graphicsSrc */)
{ }

/////////////////////////////////////////////////////////////////////////////
#endif //AFX_INL_INCLUDE_GUARD
//#endif //_AFX_INLINE
