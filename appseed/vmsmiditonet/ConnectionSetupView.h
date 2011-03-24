#if !defined(AFX_CONNECTIONSETUPVIEW1_H__6B95AEE0_0AA2_4627_819A_765EAB2AA801__INCLUDED_)
#define AFX_CONNECTIONSETUPVIEW1_H__6B95AEE0_0AA2_4627_819A_765EAB2AA801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectionSetupView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ConnectionSetupView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

enum EState
{
   StateInitial,
   StateListening,
   StateCalling,
   StateConnectionActive,
};

enum EConnMode
{
   ConnModeNone,
   ConnModeListener,
   ConnModeCaller,
};

class MidiToNetAsyncSocket;

class ConnectionSetupView : public CFormView
{
protected:
	ConnectionSetupView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(ConnectionSetupView)

// Form Data
public:
	//{{AFX_DATA(ConnectionSetupView)
	enum { IDD = IDR_CONNECTION_SETUP };
	CListBox	m_listboxDev;
	CIPAddressCtrl	m_ipaddressRemoteServer;
	UINT	m_uiRemoteServerPort;
   UINT	m_uiLocalServerPort;
	//}}AFX_DATA

// Attributes
public:
   HMIDIIN     m_hmidiin;
   DWORD       m_dwLastPosition;


   EState      m_estate;
   EConnMode   m_econnmode;
   
   MidiToNetAsyncSocket   *   m_psocket;
   MidiToNetAsyncSocket   *   m_psocketXXX;


   MidiToNetAsyncSocket   *   m_psocketY;

   CCriticalSection           m_csMidiIn;
   CCriticalSection           m_csMidiOut;

   UINT                       m_uiDevIn;
   UINT                       m_uiDevOut;


   HMIDISTRM m_hmidiout;
   CArray < MIDIHDR, MIDIHDR> m_midihdra;
   CArray < LPBYTE, LPBYTE> m_midibufa;
   bool m_bMidiInitOut;
   int m_iBuffer;
   DWORD       m_dwStartPosition;
   DWORD       m_dwStreamPosition;
   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > m_msga;
   MIDITONETMESSAGE m_msg;
   int                        m_i;

   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > m_msgaIn;
   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > m_msgaOut;


// Operations
public:
	void OnSocketAfterClose();
	void OnAccept();
	void OnAcceptFailure(UINT nErrorCode);
	void OnConnectionFailure(UINT nErrorCode);
	void OnConnection();
	void SendNoteOn(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);
	void SendNoteOff(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);
	void SendControlChange(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);
	void SendProgramChange(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);
	void SendChannelPressure(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);
  	void SendPitchBend(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2);

	void Call();
	void Listen();
	void Stop();

   bool InitSocket();
   bool StopSocket();

   bool InitMidiIn();
   bool InitMidiOut();
   static void CALLBACK WinMidiInProc(HMIDIIN hMidiIn,UINT wMsg,DWORD dwInstance,
        DWORD dwParam1,DWORD dwParam2);
   bool StopMidiIn();
   bool StopMidiOut();

   void OnMessage(LPBYTE lpbuf, int nRead);
   static UINT AFX_CDECL MidiOutThreadProc( LPVOID lpParameter);
   void MidiOut(MIDITONETMESSAGE &msg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ConnectionSetupView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ConnectionSetupView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(ConnectionSetupView)
	afx_msg void OnActionCall();
	afx_msg void OnActionStop();
	afx_msg void OnUpdateActionCall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateActionStop(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFieldchangedIpaddressServer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeListMidiInDevices();
	afx_msg void OnActionListen();
	afx_msg void OnUpdateActionListen(CCmdUI* pCmdUI);
	afx_msg void OnChangeEditLocalServerPort();
	afx_msg void OnChangeEditRemoteServerPort();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNECTIONSETUPVIEW1_H__6B95AEE0_0AA2_4627_819A_765EAB2AA801__INCLUDED_)
