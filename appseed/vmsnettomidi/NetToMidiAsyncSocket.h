#if !defined(AFX_NETTOMIDIASYNCSOCKET_H__6BA84264_4D63_497C_A1FE_327274EACDF1__INCLUDED_)
#define AFX_NETTOMIDIASYNCSOCKET_H__6BA84264_4D63_497C_A1FE_327274EACDF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetToMidiAsyncSocket.h : header file
//


class NetToMidiPoint;
/////////////////////////////////////////////////////////////////////////////
// NetToMidiAsyncSocket command target

class NetToMidiAsyncSocket : public CAsyncSocket
{
// Attributes
public:
   NetToMidiPoint * m_pserver;

// Operations
public:
	NetToMidiAsyncSocket();
	virtual ~NetToMidiAsyncSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NetToMidiAsyncSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(NetToMidiAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETTOMIDIASYNCSOCKET_H__6BA84264_4D63_497C_A1FE_327274EACDF1__INCLUDED_)
