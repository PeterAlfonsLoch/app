#include "StdAfx.h"
#include "WinStdioFile.h"

#include <errno.h>
#include <io.h>
#include <fcntl.h>

WinStdioFile::WinStdioFile(::ca::application * papp) :
   ::ca::ca(papp),
   WinFile(papp)
{
	m_pStream = NULL;
}

WinStdioFile::~WinStdioFile()
{
//	ASSERT_VALID(this);

//	if (m_pStream != NULL && m_bCloseOnDelete)
		//close();
	if (m_pStream != NULL)
		close();
}

BOOL WinStdioFile::open(const char * lpszFileName, UINT nOpenFlags,
	ex1::file_exception_sp* pException)
{
	ASSERT(pException == NULL || AfxIsValidAddress(pException, sizeof(ex1::file_exception_sp)));
	ASSERT(lpszFileName != NULL);
	ASSERT(AfxIsValidString(lpszFileName));

	m_pStream = NULL;
   if (!WinFile::open(lpszFileName, (nOpenFlags & ~::ex1::file::type_text), pException))
		return FALSE;

	ASSERT(m_hFile != hFileNull);
	ASSERT(m_bCloseOnDelete);

	char szMode[4]; // C-runtime open string
	int nMode = 0;

	// determine read/write mode depending on ex1::filesp mode
	if (nOpenFlags & mode_create)
	{
		if (nOpenFlags & modeNoTruncate)
			szMode[nMode++] = 'a';
		else
			szMode[nMode++] = 'w';
	}
	else if (nOpenFlags & mode_write)
		szMode[nMode++] = 'a';
	else
		szMode[nMode++] = 'r';

	// add '+' if necessary (when read/write modes mismatched)
	if (szMode[0] == 'r' && (nOpenFlags & mode_read_write) ||
		szMode[0] != 'r' && !(nOpenFlags & mode_write))
	{
		// current szMode mismatched, need to add '+' to fix
		szMode[nMode++] = '+';
	}

	// will be inverted if not necessary
	int nFlags = _O_RDONLY|_O_TEXT;
	if (nOpenFlags & (mode_write|mode_read_write))
		nFlags ^= _O_RDONLY;

	if (nOpenFlags & type_binary)
		szMode[nMode++] = 'b', nFlags ^= _O_TEXT;
	else
		szMode[nMode++] = 't';
	szMode[nMode++] = '\0';

	// open a C-runtime low-level file handle
	int nHandle = _open_osfhandle(m_hFile, nFlags);

	// open a C-runtime stream from that handle
	if (nHandle != -1)
		m_pStream = _fdopen(nHandle, szMode);

	if (m_pStream == NULL)
	{
		// an error somewhere along the way...
		if (pException != NULL)
		{
//			pException->m_lOsError = _doserrno;
//			pException->m_cause = ::ex1::file_exception::OsErrorToException(_doserrno);
		}

		WinFile::Abort(); // close m_hFile
		return FALSE;
	}

	return TRUE;
}

DWORD_PTR WinStdioFile::read(void * lpBuf, DWORD_PTR nCount)
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	if (nCount == 0)
		return 0;   // avoid Win32 "null-read"

	ASSERT(AfxIsValidAddress(lpBuf, nCount));

	UINT nRead = 0;

	if ((nRead = fread(lpBuf, sizeof(BYTE), nCount, m_pStream)) == 0 && !feof(m_pStream))
		vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno, m_wstrFileName);
	if (ferror(m_pStream))
	{
		clearerr(m_pStream);
		vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno, m_wstrFileName);
	}
	return nRead;
}

void WinStdioFile::write(const void * lpBuf, DWORD_PTR nCount)
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);
	ASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE));

	if (fwrite(lpBuf, sizeof(BYTE), nCount, m_pStream) != nCount)
		vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno, m_wstrFileName);
}

void WinStdioFile::WriteString(const char * lpsz)
{
	ASSERT(lpsz != NULL);
	ASSERT(m_pStream != NULL);

	if (_fputts(lpsz, m_pStream) == _TEOF)
		vfxThrowFileException(get_app(), ::ex1::file_exception::diskFull, _doserrno, m_wstrFileName);
}

LPTSTR WinStdioFile::ReadString(LPTSTR lpsz, UINT nMax)
{
	ASSERT(lpsz != NULL);
	ASSERT(AfxIsValidAddress(lpsz, nMax));
	ASSERT(m_pStream != NULL);

	LPTSTR lpszResult = _fgetts(lpsz, nMax, m_pStream);
	if (lpszResult == NULL && !feof(m_pStream))
	{
		clearerr(m_pStream);
		vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno, m_wstrFileName);
	}
	return lpszResult;
}

UINT WinStdioFile::ReadString(string & rString)
{
	ASSERT_VALID(this);

	//rString = &afxWchNil;    // empty string without deallocating
   rString.Empty();
	const int nMaxSize = 128;
	char * lpsz = rString.GetBuffer(nMaxSize);
	char * lpszResult;
	int nLen = 0;
	for (;;)
	{
		lpszResult = fgets(lpsz, nMaxSize+1, m_pStream);
		rString.ReleaseBuffer();

		// handle error/eof case
		if (lpszResult == NULL && !feof(m_pStream))
		{
			clearerr(m_pStream);
			vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno,
				m_wstrFileName);
		}

		// if string is read completely or EOF
		if (lpszResult == NULL ||
			(nLen = lstrlen(lpsz)) < nMaxSize ||
			lpsz[nLen-1] == '\n')
			break;

		nLen = rString.get_length();
		lpsz = rString.GetBuffer(nMaxSize + nLen) + nLen;
	}

	// remov '\n' from end of string if present
	lpsz = rString.GetBuffer(0);
	nLen = rString.get_length();
	if (nLen != 0 && lpsz[nLen-1] == '\n')
		rString.GetBufferSetLength(nLen-1);

	return lpszResult != NULL;
}

/*void WinStdioFile::WriteString(const char * lpsz)
{
	ASSERT(lpsz != NULL);
	ASSERT(m_pStream != NULL);

	if (fputws(lpsz, m_pStream) == _TEOF)
		vfxThrowFileException(get_app(), ::ex1::file_exception::diskFull, _doserrno, m_strFileName);
}*/

/*wchar_t * WinStdioFile::ReadString(wchar_t * lpsz, UINT nMax)
{
	ASSERT(lpsz != NULL);
	ASSERT(AfxIsValidAddress(lpsz, nMax));
	ASSERT(m_pStream != NULL);

	wchar_t * lpszResult = fgetws(lpsz, nMax, m_pStream);
	if (lpszResult == NULL && !feof(m_pStream))
	{
		clearerr(m_pStream);
		vfxThrowFileException(get_app(), ::ex1::file_exception::generic, _doserrno, m_strFileName);
	}
	return lpszResult;
}*/

INT_PTR WinStdioFile::seek(INT_PTR lOff, UINT nFrom)
{
	ASSERT_VALID(this);
	ASSERT(nFrom == begin || nFrom == end || nFrom == current);
	ASSERT(m_pStream != NULL);

	if (fseek(m_pStream, lOff, nFrom) != 0)
		vfxThrowFileException(get_app(), ::ex1::file_exception::badSeek, _doserrno,
			m_wstrFileName);

	long pos = ftell(m_pStream);
	return pos;
}

DWORD WinStdioFile::GetPosition() const
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	long pos = ftell(m_pStream);
	if (pos == -1)
		vfxThrowFileException(get_app(), ::ex1::file_exception::invalidFile, _doserrno,
			m_wstrFileName);
	return pos;
}

void WinStdioFile::Flush()
{
	ASSERT_VALID(this);

	if (m_pStream != NULL && fflush(m_pStream) != 0)
		vfxThrowFileException(get_app(), ::ex1::file_exception::diskFull, _doserrno,
			m_wstrFileName);
}

void WinStdioFile::close()
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	int nErr = 0;

	if (m_pStream != NULL)
		nErr = fclose(m_pStream);

	m_hFile = (UINT) hFileNull;
	m_bCloseOnDelete = FALSE;
	m_pStream = NULL;

	if (nErr != 0)
		vfxThrowFileException(get_app(), ::ex1::file_exception::diskFull, _doserrno,
			m_wstrFileName);
}

void WinStdioFile::Abort()
{
	ASSERT_VALID(this);

	if (m_pStream != NULL && m_bCloseOnDelete)
		fclose(m_pStream);  // close but ignore errors
	m_hFile = (UINT) hFileNull;
	m_pStream = NULL;
	m_bCloseOnDelete = FALSE;
}

ex1::file * WinStdioFile::Duplicate() const
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	AfxThrowNotSupportedException();
	return NULL;
}

void WinStdioFile::LockRange(DWORD /* dwPos */, DWORD /* dwCount */)
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	AfxThrowNotSupportedException();
}

void WinStdioFile::UnlockRange(DWORD /* dwPos */, DWORD /* dwCount */)
{
	ASSERT_VALID(this);
	ASSERT(m_pStream != NULL);

	AfxThrowNotSupportedException();
}

#ifdef _DEBUG
void WinStdioFile::Dump(CDumpContext & dumpcontext) const
{
	WinFile::Dump(dumpcontext);

	dumpcontext << "m_pStream = " << (void *)m_pStream;
	dumpcontext << "\n";
}
#endif



DWORD WinStdioFile::get_length() const
{
   ASSERT_VALID(this);

   LONG nCurrent;
   LONG nLength;
   LONG nResult;

   nCurrent = ftell(m_pStream);
   if (nCurrent == -1)
	  vfxThrowFileException(get_app(), ::ex1::file_exception::invalidFile, _doserrno,
		 m_wstrFileName);

   nResult = fseek(m_pStream, 0, SEEK_END);
   if (nResult != 0)
	  vfxThrowFileException(get_app(), ::ex1::file_exception::badSeek, _doserrno,
		 m_wstrFileName);

   nLength = ftell(m_pStream);
   if (nLength == -1)
	  vfxThrowFileException(get_app(), ::ex1::file_exception::invalidFile, _doserrno,
		 m_wstrFileName);
   nResult = fseek(m_pStream, nCurrent, SEEK_SET);
   if (nResult != 0)
	  vfxThrowFileException(get_app(), ::ex1::file_exception::badSeek, _doserrno,
		 m_wstrFileName);

   return nLength;
}
