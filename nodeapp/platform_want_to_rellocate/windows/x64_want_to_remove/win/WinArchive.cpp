// _vmsgenArchive.cpp: implementation of the _vmsgenArchive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

// vmsgen
#include "WinArchive.h"
#include "WinFile.h"
#include "_vmsgenImpl.h"
#include "International.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////
// Serialize member functions for low level classes put here
// for code swapping improvements

#ifdef _AFX_BYTESWAP
Archive& Archive::operator<<(WORD w)
{
	if (m_lpBufCur + sizeof(WORD) > m_lpBufMax)
		Flush();

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(w, m_lpBufCur);
	else
		*(WORD*)m_lpBufCur = w;

	m_lpBufCur += sizeof(WORD);
	return *this;
}

Archive& Archive::operator<<(LONG l)
{
	ASSERT(sizeof(LONG) == sizeof(DWORD));
	return operator<<((DWORD) l);
}

Archive& Archive::operator<<(DWORD dw)
{
	if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax)
		Flush();

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(dw, m_lpBufCur);
	else
		*(DWORD*)m_lpBufCur = dw;

	m_lpBufCur += sizeof(DWORD);
	return *this;
}

Archive& Archive::operator<<(float f)
{
	if (m_lpBufCur + sizeof(float) > m_lpBufMax)
		Flush();

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(f, m_lpBufCur);
	else
		*(_AFXFLOAT*)m_lpBufCur = *(_AFXFLOAT*)&f;

	m_lpBufCur += sizeof(float);
	return *this;
}

Archive& Archive::operator<<(double d)
{
	if (m_lpBufCur + sizeof(double) > m_lpBufMax)
		Flush();

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(d, m_lpBufCur);
	else
		*(_AFXDOUBLE*)m_lpBufCur = *(_AFXDOUBLE*)&d;

	m_lpBufCur += sizeof(double);
	return *this;
}

Archive& Archive::operator>>(WORD& w)
{
	if (m_lpBufCur + sizeof(WORD) > m_lpBufMax)
		FillBuffer(sizeof(WORD) - (UINT)(m_lpBufMax - m_lpBufCur));

	w = *(WORD*)m_lpBufCur;
	m_lpBufCur += sizeof(WORD);

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(w, (BYTE*)&w);

	return *this;
}

Archive& Archive::operator>>(LONG& l)
{
	ASSERT(sizeof(LONG) == sizeof(DWORD));
	return operator>>((DWORD&) l);
}

Archive& Archive::operator>>(DWORD& dw)
{
	if (m_lpBufCur + sizeof(DWORD) > m_lpBufMax)
		FillBuffer(sizeof(DWORD) - (UINT)(m_lpBufMax - m_lpBufCur));

	dw = *(DWORD*)m_lpBufCur;
	m_lpBufCur += sizeof(DWORD);

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(dw, (BYTE*)&dw);

	return *this;
}

Archive& Archive::operator>>(float& f)
{
	if (m_lpBufCur + sizeof(float) > m_lpBufMax)
		FillBuffer(sizeof(float) - (UINT)(m_lpBufMax - m_lpBufCur));

	*(_AFXFLOAT*)&f = *(_AFXFLOAT*)m_lpBufCur;
	m_lpBufCur += sizeof(float);

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(f, (BYTE*)&f);

	return *this;
}

Archive& Archive::operator>>(double& d)
{
	if (m_lpBufCur + sizeof(double) > m_lpBufMax)
		FillBuffer(sizeof(double) - (UINT)(m_lpBufMax - m_lpBufCur));

	*(_AFXDOUBLE*)&d = *(_AFXDOUBLE*)m_lpBufCur;
	m_lpBufCur += sizeof(double);

	if (!(m_nMode & bNoByteSwap))
		_AfxByteSwap(d, (BYTE*)&d);

	return *this;
}
#endif //_AFX_BYTESWAP

// WString serialization code
// String format:
//      UNICODE strings are always prefixed by 0xff, 0xfffe
//      if < 0xff chars: len:BYTE, TCHAR chars
//      if >= 0xff characters: 0xff, len:WORD, TCHAR chars
//      if >= 0xfffe characters: 0xff, 0xffff, len:DWORD, TCHARs

Archive& AFXAPI operator<<(Archive& ar, const WString& string)
{
	// special signature to recognize unicode strings
#ifdef _UNICODE
	ar << (BYTE)0xff;
	ar << (WORD)0xfffe;
#endif

	if (string.GetData()->nDataLength < 255)
	{
		ar << (BYTE)string.GetData()->nDataLength;
	}
	else if (string.GetData()->nDataLength < 0xfffe)
	{
		ar << (BYTE)0xff;
		ar << (WORD)string.GetData()->nDataLength;
	}
	else
	{
		ar << (BYTE)0xff;
		ar << (WORD)0xffff;
		ar << (DWORD)string.GetData()->nDataLength;
	}
	ar.Write(string.m_pchData, string.GetData()->nDataLength*sizeof(TCHAR));
	return ar;
}

// return string length or -1 if UNICODE string is found in the archive
AFX_STATIC UINT AFXAPI _AfxReadStringLength(Archive& ar)
{
	DWORD nNewLen;

	// attempt BYTE length first
	BYTE bLen;
	ar >> bLen;

	if (bLen < 0xff)
		return bLen;

	// attempt WORD length
	WORD wLen;
	ar >> wLen;
	if (wLen == 0xfffe)
	{
		// UNICODE string prefix (length will follow)
		return (UINT)-1;
	}
	else if (wLen == 0xffff)
	{
		// read DWORD of length
		ar >> nNewLen;
		return (UINT)nNewLen;
	}
	else
		return wLen;
}

Archive& AFXAPI operator>>(Archive& ar, WString& string)
{
#ifdef _UNICODE
	int nConvert = 1;   // if we get ANSI, convert
#else
	int nConvert = 0;   // if we get UNICODE, convert
#endif

	UINT nNewLen = _AfxReadStringLength(ar);
	if (nNewLen == (UINT)-1)
	{
		nConvert = 1 - nConvert;
		nNewLen = _AfxReadStringLength(ar);
		ASSERT(nNewLen != -1);
	}

	// set length of string to new length
	UINT nByteLen = nNewLen;
#ifdef _UNICODE
	string.GetBufferSetLength((int)nNewLen);
	nByteLen += nByteLen * (1 - nConvert);  // bytes to read
#else
	nByteLen += nByteLen * nConvert;    // bytes to read
	if (nNewLen == 0)
		string.GetBufferSetLength(0);
	else
		string.GetBufferSetLength((int)nByteLen+nConvert);
#endif

	// read in the characters
	if (nNewLen != 0)
	{
		ASSERT(nByteLen != 0);

		// read new data
		if (ar.Read(string.m_pchData, nByteLen) != nByteLen)
			AfxThrowArchiveException(ArchiveException::endOfFile);

		// convert the data if as necessary
		if (nConvert != 0)
		{
#ifdef _UNICODE
			WStringData* pOldData = string.GetData();
			LPSTR lpsz = (LPSTR)string.m_pchData;
#else
			WStringData* pOldData = string.GetData();
			LPWSTR lpsz = (LPWSTR)string.m_pchData;
#endif
			lpsz[nNewLen] = '\0';    // must be NUL terminated
			string.Init();   // don't delete the old data
			string = lpsz;   // convert with operator=(LPWCSTR)
			delete[] (BYTE*)pOldData;
		}
	}
	return ar;
}

// specialized version of SerializeElements for WString (used in collections)
#if _MSC_VER >= 1100
template <> void AFXAPI SerializeElements<WString> (Archive& ar, WString* pElements, int nCount)
#else
void AFXAPI SerializeElements(Archive& ar, WString* pElements, int nCount)
#endif
{
	ASSERT(nCount == 0 ||
		AfxIsValidAddress(pElements, nCount * sizeof(WString)));

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

// Runtime class serialization code
/* xxx CRuntimeClass* PASCAL CRuntimeClass::Load(Archive& ar, UINT* pwSchemaNum)
	// loads a runtime class description
{
	WORD nLen;
	char szClassName[64];
	CRuntimeClass* pClass;

	WORD wTemp;
	ar >> wTemp; *pwSchemaNum = wTemp;
	ar >> nLen;

	if (nLen >= _countof(szClassName) ||
		ar.Read(szClassName, nLen*sizeof(char)) != nLen*sizeof(char))
	{
		return NULL;
	}
	szClassName[nLen] = '\0';

	// search app specific classes
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	AfxLockGlobals(CRIT_RUNTIMECLASSLIST);
	for (pClass = pModuleState->m_classList; pClass != NULL;
		pClass = pClass->m_pNextClass)
	{
		if (lstrcmpA(szClassName, pClass->m_lpszClassName) == 0)
		{
			AfxUnlockGlobals(CRIT_RUNTIMECLASSLIST);
			return pClass;
		}
	}
	AfxUnlockGlobals(CRIT_RUNTIMECLASSLIST);
#ifdef _AFXDLL
	// search classes in shared DLLs
	AfxLockGlobals(CRIT_DYNLINKLIST);
	for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL;
		pDLL = pDLL->m_pNextDLL)
	{
		for (pClass = pDLL->m_classList; pClass != NULL;
			pClass = pClass->m_pNextClass)
		{
			if (lstrcmpA(szClassName, pClass->m_lpszClassName) == 0)
			{
				AfxUnlockGlobals(CRIT_DYNLINKLIST);
				return pClass;
			}
		}
	}
	AfxUnlockGlobals(CRIT_DYNLINKLIST);
#endif

	TRACE1("Warning: Cannot load %hs from archive.  Class not defined.\n",
		szClassName);

	return NULL; // not found
}

void CRuntimeClass::Store(Archive& ar) const
	// stores a runtime class description
{
	WORD nLen = (WORD)lstrlenA(m_lpszClassName);
	ar << (WORD)m_wSchema << nLen;
	ar.Write(m_lpszClassName, nLen*sizeof(char));
}*/

////////////////////////////////////////////////////////////////////////////
// Archive object input/output

// minimum buffer size
enum { nBufSizeMin = 128 };

// default amount to grow m_pLoadArray upon insert
enum { nGrowSize = 64 };
// default size of hash table in m_pStoreMap when storing
enum { nHashSize = 137 };
// default size to grow collision blocks when storing
enum { nBlockSize = 16 };

////////////////////////////////////////////////////////////////////////////

Archive::Archive(File* pFile, UINT nMode, int nBufSize, void* lpBuf) :
	m_wstrFileName(pFile->GetFilePath())
{
	ASSERT_VALID(pFile);

	// initialize members not dependent on allocated buffer
	m_nMode = nMode;
	m_pFile = pFile;
	m_pSchemaMap = NULL;
	m_pLoadArray = NULL;
	m_pDocument = NULL;
	m_bForceFlat = TRUE;
	m_nObjectSchema = (UINT)-1; // start with invalid schema
	if (IsStoring())
		m_nGrowSize = nBlockSize;
	else
		m_nGrowSize = nGrowSize;
	m_nHashSize = nHashSize;

	// initialize the buffer.  minimum size is 128
	m_lpBufStart = (BYTE*)lpBuf;
	m_bUserBuf = TRUE;
	m_bDirectBuffer = FALSE;

	if (nBufSize < nBufSizeMin)
	{
		// force use of private buffer of minimum size
		m_nBufSize = nBufSizeMin;
		m_lpBufStart = NULL;
	}
	else
		m_nBufSize = nBufSize;

	nBufSize = m_nBufSize;
	if (m_lpBufStart == NULL)
	{
		// check for CFile providing buffering support
		m_bDirectBuffer = m_pFile->GetBufferPtr(CFile::bufferCheck);
		if (!m_bDirectBuffer)
		{
			// no support for direct buffering, allocate new buffer
			m_lpBufStart = new BYTE[m_nBufSize];
			m_bUserBuf = FALSE;
		}
		else
		{
			// CFile* supports direct buffering!
			nBufSize = 0;   // will trigger initial FillBuffer
		}
	}

	if (!m_bDirectBuffer)
	{
		ASSERT(m_lpBufStart != NULL);
		ASSERT(AfxIsValidAddress(m_lpBufStart, nBufSize, IsStoring()));
	}
	m_lpBufMax = m_lpBufStart + nBufSize;
	m_lpBufCur = (IsLoading()) ? m_lpBufMax : m_lpBufStart;

	ASSERT(m_pStoreMap == NULL);        // same as m_pLoadArray
}

Archive::~Archive()
{
	// Close makes m_pFile NULL. If it is not NULL, we must Close the Archive
	if (m_pFile != NULL && !(m_nMode & bNoFlushOnDelete))
		Close();

	Abort();    // abort completely shuts down the archive
}

void Archive::Abort()
{
	ASSERT(m_bDirectBuffer || m_lpBufStart == NULL ||
		AfxIsValidAddress(m_lpBufStart, m_lpBufMax - m_lpBufStart, IsStoring()));
	ASSERT(m_bDirectBuffer || m_lpBufCur == NULL ||
		AfxIsValidAddress(m_lpBufCur, m_lpBufMax - m_lpBufCur, IsStoring()));

	// disconnect from the file
	m_pFile = NULL;

	if (!m_bUserBuf)
	{
		ASSERT(!m_bDirectBuffer);
		delete[] m_lpBufStart;
		m_lpBufStart = NULL;
		m_lpBufCur = NULL;
	}

	delete m_pSchemaMap;
	m_pSchemaMap = NULL;

	// m_pStoreMap and m_pLoadArray are unioned, so we only need to delete one
	ASSERT((CObject*)m_pStoreMap == (CObject*)m_pLoadArray);
	delete (CObject*)m_pLoadArray;
	m_pLoadArray = NULL;
}

void Archive::Close()
{
	ASSERT_VALID(m_pFile);

	Flush();
	m_pFile = NULL;
}

UINT Archive::Read(void* lpBuf, UINT nMax)
{
	ASSERT_VALID(m_pFile);

	if (nMax == 0)
		return 0;

	ASSERT(lpBuf != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nMax));
	ASSERT(m_bDirectBuffer || m_lpBufStart != NULL);
	ASSERT(m_bDirectBuffer || m_lpBufCur != NULL);
	ASSERT(m_lpBufStart == NULL ||
		AfxIsValidAddress(m_lpBufStart, m_lpBufMax - m_lpBufStart, FALSE));
	ASSERT(m_lpBufCur == NULL ||
		AfxIsValidAddress(m_lpBufCur, m_lpBufMax - m_lpBufCur, FALSE));
	ASSERT(IsLoading());

	// try to fill from buffer first
	UINT nMaxTemp = nMax;
	UINT nTemp = min(nMaxTemp, (UINT)(m_lpBufMax - m_lpBufCur));
	memcpy(lpBuf, m_lpBufCur, nTemp);
	m_lpBufCur += nTemp;
	lpBuf = (BYTE*)lpBuf + nTemp;
	nMaxTemp -= nTemp;

	if (nMaxTemp != 0)
	{
		ASSERT(m_lpBufCur == m_lpBufMax);

		// read rest in buffer size chunks
		nTemp = nMaxTemp - (nMaxTemp % m_nBufSize);
		UINT nRead = 0;

		UINT nLeft = nTemp;
		UINT nBytes;
		do
		{
			nBytes = m_pFile->Read(lpBuf, nLeft);
			lpBuf = (BYTE*)lpBuf + nBytes;
			nRead += nBytes;
			nLeft -= nBytes;
		}
		while ((nBytes > 0) && (nLeft > 0));

		nMaxTemp -= nRead;

		// read last chunk into buffer then copy
		if (nRead == nTemp)
		{
			ASSERT(m_lpBufCur == m_lpBufMax);
			ASSERT(nMaxTemp < (UINT)m_nBufSize);

			// fill buffer (similar to Archive::FillBuffer, but no exception)
			if (!m_bDirectBuffer)
			{
				UINT nLeft = max(nMaxTemp, (UINT)m_nBufSize);
				UINT nBytes;
				BYTE* lpTemp = m_lpBufStart;
				nRead = 0;
				do
				{
					nBytes = m_pFile->Read(lpTemp, nLeft);
					lpTemp = lpTemp + nBytes;
					nRead += nBytes;
					nLeft -= nBytes;
				}
				while ((nBytes > 0) && (nLeft > 0) && nRead < nMaxTemp);

				m_lpBufCur = m_lpBufStart;
				m_lpBufMax = m_lpBufStart + nRead;
			}
			else
			{
				nRead = m_pFile->GetBufferPtr(CFile::bufferRead, m_nBufSize,
					(void**)&m_lpBufStart, (void**)&m_lpBufMax);
				ASSERT(nRead == (UINT)(m_lpBufMax - m_lpBufStart));
				m_lpBufCur = m_lpBufStart;
			}

			// use first part for rest of read
			nTemp = min(nMaxTemp, (UINT)(m_lpBufMax - m_lpBufCur));
			memcpy(lpBuf, m_lpBufCur, nTemp);
			m_lpBufCur += nTemp;
			nMaxTemp -= nTemp;
		}
	}
	return nMax - nMaxTemp;
}

void Archive::Write(const void* lpBuf, UINT nMax)
{
	ASSERT_VALID(m_pFile);

	if (nMax == 0)
		return;

	ASSERT(lpBuf != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nMax, FALSE));  // read-only access needed
	ASSERT(m_bDirectBuffer || m_lpBufStart != NULL);
	ASSERT(m_bDirectBuffer || m_lpBufCur != NULL);
	ASSERT(m_lpBufStart == NULL ||
		AfxIsValidAddress(m_lpBufStart, m_lpBufMax - m_lpBufStart));
	ASSERT(m_lpBufCur == NULL ||
		AfxIsValidAddress(m_lpBufCur, m_lpBufMax - m_lpBufCur));
	ASSERT(IsStoring());

	// copy to buffer if possible
	UINT nTemp = min(nMax, (UINT)(m_lpBufMax - m_lpBufCur));
	memcpy(m_lpBufCur, lpBuf, nTemp);
	m_lpBufCur += nTemp;
	lpBuf = (BYTE*)lpBuf + nTemp;
	nMax -= nTemp;

	if (nMax > 0)
	{
		Flush();    // flush the full buffer

		// write rest of buffer size chunks
		nTemp = nMax - (nMax % m_nBufSize);
		m_pFile->Write(lpBuf, nTemp);
		lpBuf = (BYTE*)lpBuf + nTemp;
		nMax -= nTemp;

		if (m_bDirectBuffer)
		{
			// sync up direct mode buffer to new file position
			VERIFY(m_pFile->GetBufferPtr(CFile::bufferWrite, m_nBufSize,
				(void**)&m_lpBufStart, (void**)&m_lpBufMax) == (UINT)m_nBufSize);
			ASSERT((UINT)m_nBufSize == (UINT)(m_lpBufMax - m_lpBufStart));
			m_lpBufCur = m_lpBufStart;
		}

		// copy remaining to active buffer
		ASSERT(nMax < (UINT)m_nBufSize);
		ASSERT(m_lpBufCur == m_lpBufStart);
		memcpy(m_lpBufCur, lpBuf, nMax);
		m_lpBufCur += nMax;
	}
}

void Archive::Flush()
{
	ASSERT_VALID(m_pFile);
	ASSERT(m_bDirectBuffer || m_lpBufStart != NULL);
	ASSERT(m_bDirectBuffer || m_lpBufCur != NULL);
	ASSERT(m_lpBufStart == NULL ||
		AfxIsValidAddress(m_lpBufStart, m_lpBufMax - m_lpBufStart, IsStoring()));
	ASSERT(m_lpBufCur == NULL ||
		AfxIsValidAddress(m_lpBufCur, m_lpBufMax - m_lpBufCur, IsStoring()));

	if (IsLoading())
	{
		// unget the characters in the buffer, seek back unused amount
		if (m_lpBufMax != m_lpBufCur)
			m_pFile->Seek(-(m_lpBufMax - m_lpBufCur), CFile::current);
		m_lpBufCur = m_lpBufMax;    // empty
	}
	else
	{
		if (!m_bDirectBuffer)
		{
			// write out the current buffer to file
			if (m_lpBufCur != m_lpBufStart)
				m_pFile->Write(m_lpBufStart, m_lpBufCur - m_lpBufStart);
		}
		else
		{
			// commit current buffer
			if (m_lpBufCur != m_lpBufStart)
				m_pFile->GetBufferPtr(CFile::bufferCommit, m_lpBufCur - m_lpBufStart);
			// get next buffer
			VERIFY(m_pFile->GetBufferPtr(CFile::bufferWrite, m_nBufSize,
				(void**)&m_lpBufStart, (void**)&m_lpBufMax) == (UINT)m_nBufSize);
			ASSERT((UINT)m_nBufSize == (UINT)(m_lpBufMax - m_lpBufStart));
		}
		m_lpBufCur = m_lpBufStart;
	}
}

void Archive::FillBuffer(UINT nBytesNeeded)
{
	ASSERT_VALID(m_pFile);
	ASSERT(IsLoading());
	ASSERT(m_bDirectBuffer || m_lpBufStart != NULL);
	ASSERT(m_bDirectBuffer || m_lpBufCur != NULL);
	ASSERT(nBytesNeeded > 0);
	ASSERT(nBytesNeeded <= (UINT)m_nBufSize);
	ASSERT(m_lpBufStart == NULL ||
		AfxIsValidAddress(m_lpBufStart, m_lpBufMax - m_lpBufStart, FALSE));
	ASSERT(m_lpBufCur == NULL ||
		AfxIsValidAddress(m_lpBufCur, m_lpBufMax - m_lpBufCur, FALSE));

	UINT nUnused = m_lpBufMax - m_lpBufCur;
	ULONG nTotalNeeded = ((ULONG)nBytesNeeded) + nUnused;

	// fill up the current buffer from file
	if (!m_bDirectBuffer)
	{
		ASSERT(m_lpBufCur != NULL);
		ASSERT(m_lpBufStart != NULL);
		ASSERT(m_lpBufMax != NULL);

		if (m_lpBufCur > m_lpBufStart)
		{
			// copy unused
			if ((int)nUnused > 0)
			{
				memmove(m_lpBufStart, m_lpBufCur, nUnused);
				m_lpBufCur = m_lpBufStart;
				m_lpBufMax = m_lpBufStart + nUnused;
			}

			// read to satisfy nBytesNeeded or nLeft if possible
			UINT nRead = nUnused;
			UINT nLeft = m_nBufSize-nUnused;
			UINT nBytes;
			BYTE* lpTemp = m_lpBufStart + nUnused;
			do
			{
				nBytes = m_pFile->Read(lpTemp, nLeft);
				lpTemp = lpTemp + nBytes;
				nRead += nBytes;
				nLeft -= nBytes;
			}
			while (nBytes > 0 && nLeft > 0 && nRead < nBytesNeeded);

			m_lpBufCur = m_lpBufStart;
			m_lpBufMax = m_lpBufStart + nRead;
		}
	}
	else
	{
		// seek to unused portion and get the buffer starting there
		if (nUnused != 0)
			m_pFile->Seek(-(LONG)nUnused, CFile::current);
		UINT nActual = m_pFile->GetBufferPtr(CFile::bufferRead, m_nBufSize,
			(void**)&m_lpBufStart, (void**)&m_lpBufMax);
		ASSERT(nActual == (UINT)(m_lpBufMax - m_lpBufStart));
		m_lpBufCur = m_lpBufStart;
	}

	// not enough data to fill request?
	if ((ULONG)(m_lpBufMax - m_lpBufCur) < nTotalNeeded)
		AfxThrowArchiveException(ArchiveException::endOfFile);
}

void Archive::WriteCount(DWORD dwCount)
{
	if (dwCount < 0xFFFF)
		*this << (WORD)dwCount;
	else
	{
		*this << (WORD)0xFFFF;
		*this << dwCount;
	}
}

DWORD Archive::ReadCount()
{
	WORD wCount;
	*this >> wCount;
	if (wCount != 0xFFFF)
		return wCount;

	DWORD dwCount;
	*this >> dwCount;
	return dwCount;
}

// special functions for text file input and output

void Archive::WriteString(LPCWSTR lpsz)
{
	ASSERT(AfxIsValidString(lpsz));
	Write(lpsz, lstrlenW(lpsz) * sizeof(WCHAR));
}

LPWSTR Archive::ReadString(LPWSTR lpsz, UINT nMax)
{
	// if nMax is negative (such a large number doesn't make sense given today's
	// 2gb address space), then assume it to mean "keep the newline".
	int nStop = (int)nMax < 0 ? -(int)nMax : (int)nMax;
	ASSERT(AfxIsValidAddress(lpsz, (nStop+1) * sizeof(TCHAR)));

	WCHAR ch;
	int nRead = 0;

	TRY
	{
		while (nRead < nStop)
		{
			*this >> ch;

			// stop and end-of-line (trailing '\n' is ignored)
			if (ch == '\n' || ch == '\r')
			{
				if (ch == '\r')
					*this >> ch;
				// store the newline when called with negative nMax
				if ((int)nMax != nStop)
					lpsz[nRead++] = ch;
				break;
			}
			lpsz[nRead++] = ch;
		}
	}
	CATCH(ArchiveException, e)
	{
		if (e->m_cause == ArchiveException::endOfFile)
		{
			DELETE_EXCEPTION(e);
			if (nRead == 0)
				return NULL;
		}
		else
		{
			THROW_LAST();
		}
	}
	END_CATCH

	lpsz[nRead] = '\0';
	return lpsz;
}

BOOL Archive::ReadString(WString& rString)
{
	rString = &afxWchNil;    // empty string without deallocating
	const int nMaxSize = 128;
	LPWSTR lpsz = rString.GetBuffer(nMaxSize);
	LPWSTR lpszResult;
	int nLen;
	for (;;)
	{
		lpszResult = ReadString(lpsz, (UINT)-nMaxSize); // store the newline
		rString.ReleaseBuffer();

		// if string is read completely or EOF
		if (lpszResult == NULL ||
			(nLen = lstrlenW(lpsz)) < nMaxSize ||
			lpsz[nLen-1] == '\n')
		{
			break;
		}

		nLen = rString.GetLength();
		lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;
	}

	// remove '\n' from end of string if present
	lpsz = rString.GetBuffer(0);
	nLen = rString.GetLength();
	if (nLen != 0 && lpsz[nLen-1] == '\n')
		rString.GetBufferSetLength(nLen-1);

	return lpszResult != NULL;
}

void Archive::WriteString(LPCSTR lpsz)
{
	ASSERT(AfxIsValidString(lpsz));
	Write(lpsz, lstrlenA(lpsz) * sizeof(CHAR));
}

LPSTR Archive::ReadString(LPSTR lpsz, UINT nMax)
{
	// if nMax is negative (such a large number doesn't make sense given today's
	// 2gb address space), then assume it to mean "keep the newline".
	int nStop = (int)nMax < 0 ? -(int)nMax : (int)nMax;
	ASSERT(AfxIsValidAddress(lpsz, (nStop+1) * sizeof(TCHAR)));

	CHAR ch;
	int nRead = 0;

	TRY
	{
		while (nRead < nStop)
		{
			*this >> ch;

			// stop and end-of-line (trailing '\n' is ignored)
			if (ch == '\n' || ch == '\r')
			{
				if (ch == '\r')
					*this >> ch;
				// store the newline when called with negative nMax
				if ((int)nMax != nStop)
					lpsz[nRead++] = ch;
				break;
			}
			lpsz[nRead++] = ch;
		}
	}
	CATCH(ArchiveException, e)
	{
		if (e->m_cause == ArchiveException::endOfFile)
		{
			DELETE_EXCEPTION(e);
			if (nRead == 0)
				return NULL;
		}
		else
		{
			THROW_LAST();
		}
	}
	END_CATCH

	lpsz[nRead] = '\0';
	return lpsz;
}

/////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
// Archive support for polymorphic reading/writing of CObjects

// Note: Starting with MFC 4.0, the file format written/read has been
//  extended to eliminate the previous 32k limit.  Files previously written
//  can still be read by old versions (even 16-bit versions).  In addition,
//  new files, unless they are large enough to take advantage of 32-bit tags,
//  can be read by old versions.

// Pointer mapping constants
#define wNullTag        ((WORD)0)           // special tag indicating NULL ptrs
#define wNewClassTag    ((WORD)0xFFFF)      // special tag indicating new CRuntimeClass
#define wClassTag       ((WORD)0x8000)      // 0x8000 indicates class tag (OR'd)
#define dwBigClassTag   ((DWORD)0x80000000) // 0x8000000 indicates big class tag (OR'd)
#define wBigObjectTag   ((WORD)0x7FFF)      // 0x7FFF indicates DWORD object tag
#define nMaxMapCount    ((DWORD)0x3FFFFFFE) // 0x3FFFFFFE last valid mapCount

// Note: tag value 0x8000 could be used for something in the future, since
//  it is currently an invalid tag (0x8000 means zero wClassTag, but zero
//  index is always reserved for a NULL pointer, and a NULL runtime class
//  does not make any sense).

// This is how the tags have been allocated currently:
//
//  0x0000              represents NULL pointer
//  0x0001 - 0x7FFE     "small" object tags
//  0x7FFF              header for "big" object/class tag
//  0x8000              reserved for future use
//  0x8001 - 0xFFFE     "small" class tag
//  0xFFFF              header for class definition
//
// The special value of 0x7FFF indicates that a DWORD tag follows.  This
// two part "big" tag is used for 32-bit tag values 0x7FFF and above.
// The tag value of 0x7FFF was unused in MFC versions prior to MFC 4.0.

////////////////////////////////////////////////////////////////////////////

void Archive::CheckCount()
{
	if (m_nMapCount >= nMaxMapCount)
		vfxThrowArchiveException(ArchiveException::badIndex, m_wstrFileName);
}

/*void Archive::WriteObject(const CObject* pOb)
{
	// object can be NULL
	ASSERT(IsStoring());    // proper direction

	DWORD nObIndex;
	ASSERT(sizeof(nObIndex) == 4);
	ASSERT(sizeof(wNullTag) == 2);
	ASSERT(sizeof(wBigObjectTag) == 2);
	ASSERT(sizeof(wNewClassTag) == 2);

	// make sure m_pStoreMap is initialized
	MapObject(NULL);

	if (pOb == NULL)
	{
		// save out null tag to represent NULL pointer
		*this << wNullTag;
	}
	else if ((nObIndex = (DWORD)(*m_pStoreMap)[(void*)pOb]) != 0)
		// assumes initialized to 0 map
	{
		// save out index of already stored object
		if (nObIndex < wBigObjectTag)
			*this << (WORD)nObIndex;
		else
		{
			*this << wBigObjectTag;
			*this << nObIndex;
		}
	}
	else
	{
		// write class of object first
		CRuntimeClass* pClassRef = pOb->GetRuntimeClass();
		WriteClass(pClassRef);

		// enter in stored object table, checking for overflow
		CheckCount();
		(*m_pStoreMap)[(void*)pOb] = (void*)m_nMapCount++;

		// cause the object to serialize itself
		((CObject*)pOb)->Serialize(*this);
	}
}

CObject* Archive::ReadObject(const CRuntimeClass* pClassRefRequested)
{
	ASSERT(pClassRefRequested == NULL ||
		AfxIsValidAddress(pClassRefRequested, sizeof(CRuntimeClass), FALSE));
	ASSERT(IsLoading());    // proper direction
	ASSERT(wNullTag == 0);
	ASSERT((wClassTag << 16) == dwBigClassTag);
	ASSERT((wNewClassTag & wClassTag) == wClassTag);

	// attempt to load next stream as CRuntimeClass
	UINT nSchema;
	DWORD obTag;
	CRuntimeClass* pClassRef = ReadClass(pClassRefRequested, &nSchema, &obTag);

	// check to see if tag to already loaded object
	CObject* pOb;
	if (pClassRef == NULL)
	{
		if (obTag > (DWORD)m_pLoadArray->GetUpperBound())
		{
			// tag is too large for the number of objects read so far
			AfxThrowArchiveException(ArchiveException::badIndex,
				m_strFileName);
		}

		pOb = (CObject*)m_pLoadArray->GetAt(obTag);
		if (pOb != NULL && pClassRefRequested != NULL &&
			 !pOb->IsKindOf(pClassRefRequested))
		{
			// loaded an object but of the wrong class
			AfxThrowArchiveException(ArchiveException::badClass,
				m_strFileName);
		}
	}
	else
	{
		// allocate a new object based on the class just acquired
		pOb = pClassRef->CreateObject();
		if (pOb == NULL)
			AfxThrowMemoryException();

		// Add to mapping array BEFORE de-serializing
		CheckCount();
		m_pLoadArray->InsertAt(m_nMapCount++, pOb);

		// Serialize the object with the schema number set in the archive
		UINT nSchemaSave = m_nObjectSchema;
		m_nObjectSchema = nSchema;
		pOb->Serialize(*this);
		m_nObjectSchema = nSchemaSave;
		ASSERT_VALID(pOb);
	}

	return pOb;
}*/

/////////////////////////////////////////////////////////////////////////////
// advanced versioning and back-pointer support

UINT Archive::GetObjectSchema()
{
	UINT nResult = m_nObjectSchema;
	m_nObjectSchema = (UINT)-1; // can only be called once per Serialize
	return nResult;
}

/*void Archive::MapObject(const CObject* pOb)
{
	if (IsStoring())
	{
		if (m_pStoreMap == NULL)
		{
			// initialize the storage map
			//  (use CMapPtrToPtr because it is used for HANDLE maps too)
			m_pStoreMap = new CMapPtrToPtr(m_nGrowSize);
			m_pStoreMap->InitHashTable(m_nHashSize);
			m_pStoreMap->SetAt(NULL, (void*)(DWORD)wNullTag);
			m_nMapCount = 1;
		}
		if (pOb != NULL)
		{
			CheckCount();
			(*m_pStoreMap)[(void*)pOb] = (void*)m_nMapCount++;
		}
	}
	else
	{
		if (m_pLoadArray == NULL)
		{
			// initialize the loaded object pointer array and set special values
			m_pLoadArray = new CPtrArray;
			m_pLoadArray->SetSize(1, m_nGrowSize);
			ASSERT(wNullTag == 0);
			m_pLoadArray->SetAt(wNullTag, NULL);
			m_nMapCount = 1;
		}
		if (pOb != NULL)
		{
			CheckCount();
			m_pLoadArray->InsertAt(m_nMapCount++, (void*)pOb);
		}
	}
}

void Archive::WriteClass(const CRuntimeClass* pClassRef)
{
	ASSERT(pClassRef != NULL);
	ASSERT(IsStoring());    // proper direction

	if (pClassRef->m_wSchema == 0xFFFF)
	{
		TRACE1("Warning: Cannot call WriteClass/WriteObject for %hs.\n",
			pClassRef->m_lpszClassName);
		AfxThrowNotSupportedException();
	}

	// make sure m_pStoreMap is initialized
	MapObject(NULL);

	// write out class id of pOb, with high bit set to indicate
	// new object follows

	// ASSUME: initialized to 0 map
	DWORD nClassIndex;
	if ((nClassIndex = (DWORD)(*m_pStoreMap)[(void*)pClassRef]) != 0)
	{
		// previously seen class, write out the index tagged by high bit
		if (nClassIndex < wBigObjectTag)
			*this << (WORD)(wClassTag | nClassIndex);
		else
		{
			*this << wBigObjectTag;
			*this << (dwBigClassTag | nClassIndex);
		}
	}
	else
	{
		// store new class
		*this << wNewClassTag;
		pClassRef->Store(*this);

		// store new class reference in map, checking for overflow
		CheckCount();
		(*m_pStoreMap)[(void*)pClassRef] = (void*)m_nMapCount++;
	}
}

CRuntimeClass* Archive::ReadClass(const CRuntimeClass* pClassRefRequested,
	UINT* pSchema, DWORD* pObTag)
{
	ASSERT(pClassRefRequested == NULL ||
		AfxIsValidAddress(pClassRefRequested, sizeof(CRuntimeClass), FALSE));
	ASSERT(IsLoading());    // proper direction

	if (pClassRefRequested != NULL && pClassRefRequested->m_wSchema == 0xFFFF)
	{
		TRACE1("Warning: Cannot call ReadClass/ReadObject for %hs.\n",
			pClassRefRequested->m_lpszClassName);
		AfxThrowNotSupportedException();
	}

	// make sure m_pLoadArray is initialized
	MapObject(NULL);

	// read object tag - if prefixed by wBigObjectTag then DWORD tag follows
	DWORD obTag;
	WORD wTag;
	*this >> wTag;
	if (wTag == wBigObjectTag)
		*this >> obTag;
	else
		obTag = ((wTag & wClassTag) << 16) | (wTag & ~wClassTag);

	// check for object tag (throw exception if expecting class tag)
	if (!(obTag & dwBigClassTag))
	{
		if (pObTag == NULL)
			AfxThrowArchiveException(ArchiveException::badIndex, m_strFileName);

		*pObTag = obTag;
		return NULL;
	}

	CRuntimeClass* pClassRef;
	UINT nSchema;
	if (wTag == wNewClassTag)
	{
		// new object follows a new class id
		if ((pClassRef = CRuntimeClass::Load(*this, &nSchema)) == NULL)
			AfxThrowArchiveException(ArchiveException::badClass, m_strFileName);

		// check nSchema against the expected schema
		if ((pClassRef->m_wSchema & ~VERSIONABLE_SCHEMA) != nSchema)
		{
			if (!(pClassRef->m_wSchema & VERSIONABLE_SCHEMA))
			{
				// schema doesn't match and not marked as VERSIONABLE_SCHEMA
				AfxThrowArchiveException(ArchiveException::badSchema,
					m_strFileName);
			}
			else
			{
				// they differ -- store the schema for later retrieval
				if (m_pSchemaMap == NULL)
					m_pSchemaMap = new CMapPtrToPtr;
				ASSERT_VALID(m_pSchemaMap);
				m_pSchemaMap->SetAt(pClassRef, (void*)nSchema);
			}
		}
		CheckCount();
		m_pLoadArray->InsertAt(m_nMapCount++, pClassRef);
	}
	else
	{
		// existing class index in obTag followed by new object
		DWORD nClassIndex = (obTag & ~dwBigClassTag);
		if (nClassIndex == 0 || nClassIndex > (DWORD)m_pLoadArray->GetUpperBound())
			AfxThrowArchiveException(ArchiveException::badIndex,
				m_strFileName);

		pClassRef = (CRuntimeClass*)m_pLoadArray->GetAt(nClassIndex);
		ASSERT(pClassRef != NULL);

		// determine schema stored against objects of this type
		void* pTemp;
		BOOL bFound = FALSE;
		nSchema = 0;
		if (m_pSchemaMap != NULL)
		{
			bFound = m_pSchemaMap->Lookup( pClassRef, pTemp );
			if (bFound)
				nSchema = (UINT)pTemp;
		}
		if (!bFound)
			nSchema = pClassRef->m_wSchema & ~VERSIONABLE_SCHEMA;
   }

	// check for correct derivation
	if (pClassRefRequested != NULL &&
		!pClassRef->IsDerivedFrom(pClassRefRequested))
	{
		AfxThrowArchiveException(ArchiveException::badClass, m_strFileName);
	}

	// store nSchema for later examination
	if (pSchema != NULL)
		*pSchema = nSchema;
	else
		m_nObjectSchema = nSchema;

	// store obTag for later examination
	if (pObTag != NULL)
		*pObTag = obTag;

	// return the resulting CRuntimeClass*
	return pClassRef;
}

void Archive::SerializeClass(const CRuntimeClass* pClassRef)
{
	if (IsStoring())
		WriteClass(pClassRef);
	else
		ReadClass(pClassRef);
}*/

////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
// character strings to use for dumping ArchiveException
static const LPCSTR rgszArchiveExceptionCause[] =
{
	"none",
	"generic",
	"readOnly",
	"endOfFile",
	"writeOnly",
	"badIndex",
	"badClass",
	"badSchema",
};
static const char szUnknown[] = "unknown";
#endif


BOOL ArchiveException::GetErrorMessage(LPTSTR lpszError, UINT nMaxError,
	PUINT pnHelpContext)
{
	ASSERT(lpszError != NULL && AfxIsValidString(lpszError, nMaxError));

	if (pnHelpContext != NULL)
		*pnHelpContext = m_cause + AFX_IDP_ARCH_NONE;

	// we can use WString here; archive errors aren't caused
	// by being out of memory.

	WString strMessage;
	WString strFileName = m_wstrFileName;
	if (strFileName.IsEmpty())
		strFileName.LoadString(AFX_IDS_UNNAMED_FILE);
	vfxFormatString1(strMessage,
		m_cause + AFX_IDP_ARCH_NONE, strFileName);
   International::UnicodeToMultiByte(CodePageACP, lpszError, nMaxError, strMessage);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// ArchiveException

#ifdef _DEBUG
void ArchiveException::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << " m_cause = ";
	if (m_cause >= 0 && m_cause < _countof(rgszArchiveExceptionCause))
		dc << rgszArchiveExceptionCause[m_cause];
	else
		dc << szUnknown;

	dc << "\n";
}
#endif //_DEBUG

void AFXAPI vfxThrowArchiveException(int cause,
	LPCWSTR lpszArchiveName /* = NULL */)
{
#ifdef _DEBUG
	LPCSTR lpsz;
	if (cause >= 0 && cause < _countof(rgszArchiveExceptionCause))
		lpsz = rgszArchiveExceptionCause[cause];
	else
		lpsz = szUnknown;
	TRACE1("CArchive exception: %hs.\n", lpsz);

#endif //_DEBUG

	THROW(new ArchiveException(cause, lpszArchiveName));
}


IMPLEMENT_DYNAMIC(ArchiveException, CException)
