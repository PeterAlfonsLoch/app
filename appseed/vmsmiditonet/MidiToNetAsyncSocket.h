#if !defined(AFX_MIDITONETASYCNSOCKET_H__591A1BD6_5CE6_4966_BA08_9D5BD772086F__INCLUDED_)
#define AFX_MIDITONETASYCNSOCKET_H__591A1BD6_5CE6_4966_BA08_9D5BD772086F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MidiToNetAsyncSocket.h : header file
//

class ConnectionSetupView;

/////////////////////////////////////////////////////////////////////////////
// MidiToNetAsyncSocket command target

class MidiToNetAsyncSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	MidiToNetAsyncSocket();
	virtual ~MidiToNetAsyncSocket();

   ConnectionSetupView * m_pserver;

   int   m_i;
   bool m_bEmpty;

   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > m_msga;

// Overrides
public:
	void SendBuffer();
	void Post(MIDITONETMESSAGE &msg);
	void Post(CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > &msga);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MidiToNetAsyncSocket)
	public:
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(MidiToNetAsyncSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MIDITONETASYCNSOCKET_H__591A1BD6_5CE6_4966_BA08_9D5BD772086F__INCLUDED_)
