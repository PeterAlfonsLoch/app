#pragma once

class CStreamOnString : public IStream
{
public:
// Construction
	CStreamOnString()
	{
		m_current_index = 0;
	}

	CStreamOnString(LPCTSTR szData):
		m_strStream(szData)
	{
		m_current_index = 0;
	}

	// Copies the data currently held in this
	// object into a string
	BOOL CopyData(string& target)
	{
		target = m_strStream;
		return TRUE;
	}

	// Sets the value of 
	BOOL SetData(LPCTSTR szData)
	{
		_ATLTRY
		{
			m_strStream = szData;
		}
		_ATLCATCHALL()
		{
			return FALSE;
		}
		return TRUE;
	}

// Implementation
	STDMETHOD(QueryInterface)(REFIID iid, void **ppUnk)
	{
		if (ppUnk == NULL) 
		{ 
			return E_POINTER; 
		}
		if (::InlineIsEqualGUID(iid, IID_IUnknown) ||
			::InlineIsEqualGUID(iid, IID_IStream) ||
			::InlineIsEqualGUID(iid, IID_ISequentialStream))
		{
			*ppUnk = (void*)this;
			AddRef();
			return S_OK;
		}
		return E_NOINTERFACE;
	}

	ULONG STDMETHODCALLTYPE AddRef( void) 
	{
		return (ULONG)1;
	}

	ULONG STDMETHODCALLTYPE Release( void) 
	{
		return (ULONG)1;
	}

	STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead)
	{
		if (pcbRead)
			*pcbRead = 0;
		if (m_strAnsi.GetLength() == 0)
			m_strAnsi = m_strStream;

		if (!pv)
			return E_POINTER;

		unsigned int length = m_strAnsi.GetLength();
		char *pStream = m_strAnsi.GetBuffer();
		if (!pStream)
			return E_UNEXPECTED;

		UINT_PTR uSum = (UINT_PTR)pStream + length;
		if (uSum < static_cast<UINT_PTR>(length))
			return E_UNEXPECTED;
		char *pEnd = reinterpret_cast<char*>(uSum);

		uSum = (UINT_PTR)pStream + m_current_index;
		if (uSum < m_current_index)
			return E_UNEXPECTED;
		char *pStart = reinterpret_cast<char*>(uSum);

		if (pStart >= pEnd)
			return S_FALSE; // no more data to read
		
		int bytes_left = (int)(pEnd-pStart);
		int bytes_to_copy = (int)__min(bytes_left, (int)cb);
		if (bytes_to_copy <= 0)
		{
			// reset members so this stream can be used again
			m_current_index = 0;
			m_strAnsi.Empty();
			return S_FALSE;
		}

		::ATL::Checked::memcpy_s(pv, cb, (void*)uSum, bytes_to_copy);
		if (pcbRead)
			*pcbRead = (ULONG)bytes_to_copy;
		m_current_index += bytes_to_copy;
		m_strAnsi.ReleaseBuffer(0);
		return S_OK;
	}

	STDMETHOD(Write)(const void *pv, ULONG cb, ULONG *pcbWritten)
	{
		if (pcbWritten)
			*pcbWritten = 0;
		try
		{
#ifdef _UNICODE
			int flags = IS_TEXT_UNICODE_UNICODE_MASK;
			if (0 != IsTextUnicode((LPVOID)pv, cb, &flags))
			{
				// compiling UNICODE and got a UNICODE buffer
				UINT nCharsToSkip = flags & IS_TEXT_UNICODE_SIGNATURE ? 1 : 0;
				m_strStream.Append((wchar_t*)( ((wchar_t*)pv)+nCharsToSkip), (cb/sizeof(wchar_t))-nCharsToSkip);
				if (pcbWritten)
					*pcbWritten = cb-nCharsToSkip*sizeof(wchar_t);
			}
			else
			{
				// compiling UNICODE and got an ansi buffer
				// convert ansi buffer to UNICODE buffer
				StringW strTemp((LPCSTR)pv, cb);
				m_strStream.Append(strTemp);
				if (pcbWritten)
					*pcbWritten = cb;
				
			}
#else
			int flags = IS_TEXT_UNICODE_UNICODE_MASK;
			if (0 != IsTextUnicode((LPVOID)pv, cb, &flags))
			{
				// compiling ANSI and got a UNICODE buffer
				UINT nCharsToSkip = flags & IS_TEXT_UNICODE_SIGNATURE ? 1 : 0;
				StringA strTemp((const wchar_t*)pv + nCharsToSkip, (cb/sizeof(wchar_t))- nCharsToSkip);
				m_strStream.Append(strTemp);
				if (pcbWritten)
					*pcbWritten = cb-nCharsToSkip*sizeof(wchar_t);
			}
			else
			{
				// compiling ANSI and got an ANSI buffer
				m_strStream.Append((char*)pv, cb);
				if (pcbWritten)
					*pcbWritten = cb;
			}
#endif
		}
		catch (CMemoryException* e)
		{
			e->Delete();
			return E_OUTOFMEMORY;
		}
		return S_OK;
	}

	STDMETHOD(Seek)(LARGE_INTEGER , DWORD , ULARGE_INTEGER *)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(SetSize)(ULARGE_INTEGER )
	{
		return E_NOTIMPL;
	}

	STDMETHOD(CopyTo)(IStream *, ULARGE_INTEGER , ULARGE_INTEGER *,
		ULARGE_INTEGER *)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Commit)(DWORD )
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Revert)( void)
	{
		return E_NOTIMPL;
	}

	STDMETHOD(LockRegion)(ULARGE_INTEGER , ULARGE_INTEGER , DWORD )
	{
		return E_NOTIMPL;
	}

	STDMETHOD(UnlockRegion)(ULARGE_INTEGER , ULARGE_INTEGER ,
		DWORD )
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Stat)(STATSTG *, DWORD )
	{
		return E_NOTIMPL;
	}

	STDMETHOD(Clone)(IStream **)
	{
		return E_NOTIMPL;
	}

protected:
	string m_strStream;
	StringA m_strAnsi;
	UINT m_current_index;

};

