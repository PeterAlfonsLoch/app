// _vmsgenArchive.h: interface for the _vmsgenArchive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__VMSGENARCHIVE_H__0EA0978A_A98A_4C3B_8339_1B317386BFF4__INCLUDED_)
#define AFX__VMSGENARCHIVE_H__0EA0978A_A98A_4C3B_8339_1B317386BFF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

CLASS_DECL_VMSWIN void AFXAPI vfxThrowArchiveException(int cause,
	LPCSTR lpszArchiveName = NULL);

template<class TYPE>
void AFXAPI SerializeElements(Archive& ar, TYPE* pElements, int nCount)
{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, nCount * sizeof(TYPE)));

	// default is bit-wise read/write
	if (ar.IsStoring())
		ar.Write((void*)pElements, nCount * sizeof(TYPE));
	else
		ar.Read((void*)pElements, nCount * sizeof(TYPE));
}


/////////////////////////////////////////////////////////////////////////////
// Archives for serializing base_object data

// needed for implementation
class CPtrArray;
class CMapPtrToPtr;
class document;
class File;

class CLASS_DECL_VMSWIN Archive
{
public:
// Flag values
	enum Mode { store = 0, load = 1, bNoFlushOnDelete = 2, bNoByteSwap = 4 };

	Archive(File* pFile, UINT nMode, int nBufSize = 4096, void* lpBuf = NULL);
	~Archive();

// Attributes
	BOOL IsLoading() const;
	BOOL IsStoring() const;
	BOOL IsByteSwapping() const;
	BOOL IsBufferEmpty() const;

	File* GetFile() const;
	UINT GetObjectSchema(); // only valid when reading a base_object*
	void SetObjectSchema(UINT nSchema);

	// pointer to document being serialized -- must set to serialize
	//  COleClientItems in a document!
	document* m_pDocument;

// Operations
	UINT Read(void* lpBuf, UINT nMax);
	void Write(const void* lpBuf, UINT nMax);
	void Flush();
	void Close();
	void Abort();   // close and shutdown without exceptions

	// reading and writing strings
	void WriteString(LPCSTR lpsz);
	LPWSTR ReadString(LPWSTR lpsz, UINT nMax);
	void WriteString(LPCSTR lpsz);
	LPSTR ReadString(LPSTR lpsz, UINT nMax);
	BOOL ReadString(wstring& rString);

public:
	// Object I/O is pointer based to avoid added construction overhead.
	// Use the Serialize member function directly for embedded objects.
	friend Archive& AFXAPI operator<<(Archive& ar, const base_object* pOb);

	friend Archive& AFXAPI operator>>(Archive& ar, base_object*& pOb);
	friend Archive& AFXAPI operator>>(Archive& ar, const base_object*& pOb);

	// insertion operations
	Archive& operator<<(BYTE by);
	Archive& operator<<(WORD w);
	Archive& operator<<(LONG l);
	Archive& operator<<(DWORD dw);
	Archive& operator<<(float f);
	Archive& operator<<(double d);

	Archive& operator<<(int i);
	Archive& operator<<(short w);
	Archive& operator<<(char ch);
	Archive& operator<<(unsigned u);

	// extraction operations
	Archive& operator>>(BYTE& by);
	Archive& operator>>(WORD& w);
	Archive& operator>>(DWORD& dw);
	Archive& operator>>(LONG& l);
	Archive& operator>>(float& f);
	Archive& operator>>(double& d);

	Archive& operator>>(int& i);
	Archive& operator>>(short& w);
	Archive& operator>>(char& ch);
	Archive& operator>>(unsigned& u);

	// object read/write
	base_object* ReadObject(const CRuntimeClass* pClass);
	/* xxx void WriteObject(const base_object* pOb);
	// advanced object mapping (used for forced references)
	void MapObject(const base_object* pOb);

	// advanced versioning support
	void WriteClass(const CRuntimeClass* pClassRef);
	CRuntimeClass* ReadClass(const CRuntimeClass* pClassRefRequested = NULL,
		UINT* pSchema = NULL, DWORD* pObTag = NULL);
	void SerializeClass(const CRuntimeClass* pClassRef);*/

	// advanced operations (used when storing/loading many objects)
	void SetStoreParams(UINT nHashSize = 2053, UINT nBlockSize = 128);
	void SetLoadParams(UINT nGrowBy = 1024);

// Implementation
public:
	BOOL m_bForceFlat;  // for COleClientItem implementation (default TRUE)
	BOOL m_bDirectBuffer;   // TRUE if m_pFile supports direct buffering
	void FillBuffer(UINT nBytesNeeded);
	void CheckCount();  // throw exception if m_nMapCount is too large

	// special functions for reading and writing (16-bit compatible) counts
	DWORD ReadCount();
	void WriteCount(DWORD dwCount);

	// public for advanced use
	UINT m_nObjectSchema;
	wstring m_strFileName;

protected:
	// archive objects cannot be copied or assigned
	Archive(const Archive& arSrc);
	void operator=(const Archive& arSrc);

	BOOL m_nMode;
	BOOL m_bUserBuf;
	int m_nBufSize;
	File* m_pFile;
	BYTE* m_lpBufCur;
	BYTE* m_lpBufMax;
	BYTE* m_lpBufStart;

	// base_array/map for base_object* and CRuntimeClass* load/store
	UINT m_nMapCount;
	union
	{
		CPtrArray* m_pLoadArray;
		CMapPtrToPtr* m_pStoreMap;
	};
	// map to keep track of mismatched schemas
	CMapPtrToPtr* m_pSchemaMap;

	// advanced parameters (controls performance with large archives)
	UINT m_nGrowSize;
	UINT m_nHashSize;
};

class ArchiveException : public base_exception
{
	// DECLARE_DYNAMIC(ArchiveException)
public:
	enum {
		none,
		generic,
		readOnly,
		endOfFile,
		writeOnly,
		badIndex,
		badClass,
		badSchema
	};

// Constructor
	ArchiveException(int cause = ArchiveException::none,
		LPCSTR lpszArchiveName = NULL);

// Attributes
	int m_cause;
	wstring m_strFileName;

// Implementation
public:
	virtual ~ArchiveException();
#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual BOOL GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
		PUINT pnHelpContext = NULL);
};

// Archive
inline BOOL Archive::IsLoading() const
	{ return (m_nMode & Archive::load) != 0; }
inline BOOL Archive::IsStoring() const
	{ return (m_nMode & Archive::load) == 0; }
inline BOOL Archive::IsByteSwapping() const
	{ return (m_nMode & Archive::bNoByteSwap) == 0; }
inline BOOL Archive::IsBufferEmpty() const
	{ return m_lpBufCur == m_lpBufMax; }
inline File* Archive::GetFile() const
	{ return m_pFile; }
inline void Archive::SetObjectSchema(UINT nSchema)
	{ m_nObjectSchema = nSchema; }
inline void Archive::SetStoreParams(UINT nHashSize, UINT nBlockSize)
{
	ASSERT(IsStoring());
	ASSERT(m_pStoreMap == NULL);    // must be before first object written
	m_nHashSize = nHashSize;
	m_nGrowSize = nBlockSize;
}
inline void Archive::SetLoadParams(UINT nGrowBy)
{
	ASSERT(IsLoading());
	ASSERT(m_pLoadArray == NULL);   // must be before first object read
	m_nGrowSize = nGrowBy;
}
inline Archive& Archive::operator<<(int i)
	{ return Archive::operator<<((LONG)i); }
inline Archive& Archive::operator<<(unsigned u)
	{ return Archive::operator<<((LONG)u); }
inline Archive& Archive::operator<<(short w)
	{ return Archive::operator<<((WORD)w); }
inline Archive& Archive::operator<<(char ch)
	{ return Archive::operator<<((BYTE)ch); }
inline Archive& Archive::operator<<(BYTE by)
	{ if (m_lpBufCur + sizeof(BYTE) > m_lpBufMax) Flush();
		*(UNALIGNED BYTE*)m_lpBufCur = by; m_lpBufCur += sizeof(BYTE); return *this; }
#ifndef _AFX_BYTESWAP
inline Archive& Archive::operator<<(WORD w)
	{ if (m_lpBufCur + sizeof(WORD) > m_lpBufMax) Flush();
		*(UNALIGNED WORD*)m_lpBufCur = w; m_lpBufCur += sizeof(WORD); return *this; }
inline Archive& Archive::operator<<(LONG l)
	{ if (m_lpBufCur + sizeof(LONG) > m_lpBufMax) Flush();
		*(UNALIGNED LONG*)m_lpBufCur = l; m_lpBufCur += sizeof(LONG); return *this; }
inline Archive& Archive::operator<<(DWORD dw)
	{ if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax) Flush();
		*(UNALIGNED DWORD*)m_lpBufCur = dw; m_lpBufCur += sizeof(DWORD); return *this; }
inline Archive& Archive::operator<<(float f)
	{ if (m_lpBufCur + sizeof(float) > m_lpBufMax) Flush();
		*(UNALIGNED _AFX_FLOAT*)m_lpBufCur = *(_AFX_FLOAT*)&f; m_lpBufCur += sizeof(float); return *this;
	}
inline Archive& Archive::operator<<(double d)
	{ if (m_lpBufCur + sizeof(double) > m_lpBufMax) Flush();
		*(UNALIGNED _AFX_DOUBLE*)m_lpBufCur = *(_AFX_DOUBLE*)&d; m_lpBufCur += sizeof(double); return *this; }
#endif
inline Archive& Archive::operator>>(int& i)
	{ return Archive::operator>>((LONG&)i); }
inline Archive& Archive::operator>>(unsigned& u)
	{ return Archive::operator>>((LONG&)u); }
inline Archive& Archive::operator>>(short& w)
	{ return Archive::operator>>((WORD&)w); }
inline Archive& Archive::operator>>(char& ch)
	{ return Archive::operator>>((BYTE&)ch); }
inline Archive& Archive::operator>>(BYTE& by)
	{ if (m_lpBufCur + sizeof(BYTE) > m_lpBufMax)
			FillBuffer(sizeof(BYTE) - (UINT)(m_lpBufMax - m_lpBufCur));
		by = *(UNALIGNED BYTE*)m_lpBufCur; m_lpBufCur += sizeof(BYTE); return *this; }
#ifndef _AFX_BYTESWAP
inline Archive& Archive::operator>>(WORD& w)
	{ if (m_lpBufCur + sizeof(WORD) > m_lpBufMax)
			FillBuffer(sizeof(WORD) - (UINT)(m_lpBufMax - m_lpBufCur));
		w = *(UNALIGNED WORD*)m_lpBufCur; m_lpBufCur += sizeof(WORD); return *this; }
inline Archive& Archive::operator>>(DWORD& dw)
	{ if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax)
			FillBuffer(sizeof(DWORD) - (UINT)(m_lpBufMax - m_lpBufCur));
		dw = *(UNALIGNED DWORD*)m_lpBufCur; m_lpBufCur += sizeof(DWORD); return *this; }
inline Archive& Archive::operator>>(float& f)
	{ if (m_lpBufCur + sizeof(float) > m_lpBufMax)
			FillBuffer(sizeof(float) - (UINT)(m_lpBufMax - m_lpBufCur));
		*(_AFX_FLOAT*)&f = *(UNALIGNED _AFX_FLOAT*)m_lpBufCur; m_lpBufCur += sizeof(float); return *this; }
inline Archive& Archive::operator>>(double& d)
	{ if (m_lpBufCur + sizeof(double) > m_lpBufMax)
			FillBuffer(sizeof(double) - (UINT)(m_lpBufMax - m_lpBufCur));
		*(_AFX_DOUBLE*)&d = *(UNALIGNED _AFX_DOUBLE*)m_lpBufCur; m_lpBufCur += sizeof(double); return *this; }
inline Archive& Archive::operator>>(LONG& l)
	{ if (m_lpBufCur + sizeof(LONG) > m_lpBufMax)
			FillBuffer(sizeof(LONG) - (UINT)(m_lpBufMax - m_lpBufCur));
		l = *(UNALIGNED LONG*)m_lpBufCur; m_lpBufCur += sizeof(LONG); return *this; }
#endif
inline Archive::Archive(const Archive& /* arSrc */)
	{ }
inline void Archive::operator=(const Archive& /* arSrc */)
	{ }
inline Archive& AFXAPI operator<<(Archive& ar, const base_object* pOb)
	{ ar.WriteObject(pOb); return ar; }
inline Archive& AFXAPI operator>>(Archive& ar, base_object*& pOb)
	{ pOb = ar.ReadObject(NULL); return ar; }
inline Archive& AFXAPI operator>>(Archive& ar, const base_object*& pOb)
	{ pOb = ar.ReadObject(NULL); return ar; }

inline ArchiveException::ArchiveException(int cause,
	LPCSTR lpszFileName /* = NULL */)
	{ m_cause = cause; m_strFileName = lpszFileName; }
inline ArchiveException::~ArchiveException()
	{ }


#endif // !defined(AFX__VMSGENARCHIVE_H__0EA0978A_A98A_4C3B_8339_1B317386BFF4__INCLUDED_)
