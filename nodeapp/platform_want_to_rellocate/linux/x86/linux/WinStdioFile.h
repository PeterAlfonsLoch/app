#pragma once

#include "WinFile.h"

/////////////////////////////////////////////////////////////////////////////
// STDIO file implementation

class WinStdioFile : 
   virtual public WinFile,
   virtual public ex1::text_file
{
public:
   WinStdioFile(::ca::application * papp);

// Attributes
	FILE* m_pStream;    // stdio FILE
						// m_hFile from base class is _fileno(m_pStream)

// Operations
	// reading and writing strings
	virtual void WriteString(const char * lpsz);
	virtual char * ReadString(char * lpsz, UINT nMax);
//	virtual void WriteString(const char * lpsz);
//	virtual wchar_t * ReadString(wchar_t * lpsz, UINT nMax);
	virtual UINT ReadString(string & rString);

// ementation
public:
	virtual ~WinStdioFile();
#ifdef _DEBUG
	void Dump(CDumpContext & dumpcontext) const;
#endif
	virtual DWORD_PTR GetPosition() const;
	virtual BOOL open(const char * lpszFileName, UINT nOpenFlags,
      ex1::file_exception_sp * pError = NULL);
	virtual DWORD_PTR read(void * lpBuf, DWORD_PTR nCount);
	virtual void write(const void * lpBuf, DWORD_PTR nCount);
	virtual INT_PTR seek(INT_PTR lOff, UINT nFrom);
	virtual void Abort();
	virtual void Flush();
	virtual void close();
   virtual DWORD_PTR get_length() const;

	// Unsupported APIs
	virtual ex1::file * Duplicate() const;
	virtual void LockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);
	virtual void UnlockRange(DWORD_PTR dwPos, DWORD_PTR dwCount);
};
