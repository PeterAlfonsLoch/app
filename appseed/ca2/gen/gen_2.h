#pragma once

// General OLE features

#if (!defined _AFX_NO_OLE_SUPPORT) && (defined _OBJBASE_H_)

// Implementation structures
struct AFX_EVENT;               // Event sink implementation

// Classes declared in this file
class COleControlLock;

#endif

// OLE Automation features

#ifdef __AFXDISP_H__
// Classes declared in this file

//IStream
   class CArchiveStream;

// Functions declared in this file

// AfxBSTR2ABTSR
// AfxTaskStringA2W
// AfxTaskStringW2A

#endif

/////////////////////////////////////////////////////////////////////////////
// General OLE features

#if (!defined _AFX_NO_OLE_SUPPORT) && (defined _OBJBASE_H_)
#ifndef __AFXPRIV2_H__OLE__
#define __AFXPRIV2_H__OLE__

/////////////////////////////////////////////////////////////////////////////
// Implementation of event sink handling

struct AFX_EVENT
{
   enum
   {
      event,
      propRequest, propChanged,
      propDSCNotify
   };

   AFX_EVENT(int eventKind);

   AFX_EVENT(int eventKind, DISPID dispid, DISPPARAMS* pDispParams = NULL,
      EXCEPINFO* pExcepInfo = NULL, UINT* puArgError = NULL);

   int m_eventKind;
   DISPID m_dispid;
   DISPPARAMS* m_pDispParams;
   EXCEPINFO* m_pExcepInfo;
   UINT* m_puArgError;
   BOOL m_bPropChanged;
   HRESULT m_hResult;
   DSCSTATE m_nDSCState;
   DSCREASON m_nDSCReason;
};

inline AFX_EVENT::AFX_EVENT(int eventKind)
{
   m_eventKind = eventKind;
   m_dispid = DISPID_UNKNOWN;
   m_pDispParams = NULL;
   m_pExcepInfo = NULL;
   m_puArgError = NULL;
   m_hResult = NOERROR;
   m_nDSCState = dscNoState;
   m_nDSCReason = dscNoReason;
}

inline AFX_EVENT::AFX_EVENT(int eventKind, DISPID dispid,
   DISPPARAMS* pDispParams, EXCEPINFO* pExcepInfo, UINT* puArgError)
{
   m_eventKind = eventKind;
   m_dispid = dispid;
   m_pDispParams = pDispParams;
   m_pExcepInfo = pExcepInfo;
   m_puArgError = puArgError;
   m_hResult = NOERROR;
   m_nDSCState = dscNoState;
   m_nDSCReason = dscNoReason;
}

/////////////////////////////////////////////////////////////////////////////
// COleControlLock

class COleControlLock
{
// Constructors
public:
   explicit COleControlLock(REFCLSID clsid);

// Attributes
   CLSID m_clsid;
   LPCLASSFACTORY m_pClassFactory;
   COleControlLock* m_pNextLock;

// Implementation
public:
   virtual ~COleControlLock();
};

#endif // __AFXPRIV2_H__OLE__
#endif //(!defined _AFX_NO_OLE_SUPPORT) && (defined _OBJBASE_H_)

/////////////////////////////////////////////////////////////////////////////
// OLE Automation features

#ifdef __AFXDISP_H__
#ifndef __AFXPRIV2_H__DISP__
#define __AFXPRIV2_H__DISP__

/////////////////////////////////////////////////////////////////////////////
// CArchiveStream
/*
class CLASS_DECL_ca CArchiveStream : public IStream
{
public:
   CArchiveStream(CArchive* pArchive);

// Implementation
   CArchive* m_pArchive;

   STDMETHOD_(ULONG, AddRef)();
   STDMETHOD_(ULONG, Release)();
   ex1::HRes QueryInterface)(REFIID, LPVOID*);

   ex1::HRes read)(void *, ULONG, ULONG*);
   ex1::HRes write)(const void *, ::primitive::memory_size cb, ::primitive::memory_size*);
   ex1::HRes seek)(LARGE_INTEGER, DWORD, ULARGE_INTEGER*);
   ex1::HRes set_size)(ULARGE_INTEGER);
   ex1::HRes CopyTo)(LPSTREAM, ULARGE_INTEGER, ULARGE_INTEGER*,
      ULARGE_INTEGER*);
   ex1::HRes Commit)(DWORD);
   ex1::HRes Revert)();
   ex1::HRes LockRegion)(ULARGE_INTEGER, ULARGE_INTEGER,DWORD);
   ex1::HRes UnlockRegion)(ULARGE_INTEGER, ULARGE_INTEGER, DWORD);
   ex1::HRes Stat)(STATSTG*, DWORD);
   ex1::HRes Clone)(LPSTREAM*);
};
*/
/////////////////////////////////////////////////////////////////////////////
// Global UNICODE<>ANSI translation helpers

CLASS_DECL_ca void AfxBSTR2String(string* pStr, BSTR bstr);

#if !defined(_UNICODE)
CLASS_DECL_ca BSTR AfxBSTR2ABSTR(BSTR bstrW);
CLASS_DECL_ca wchar_t * AfxTaskStringA2W(const char * lpa);
CLASS_DECL_ca char * AfxTaskStringW2A(const wchar_t * lpw);
#endif

#endif // __AFXPRIV2_H__DISP__
#endif // __AFXDISP_H__

/////////////////////////////////////////////////////////////////////////////




