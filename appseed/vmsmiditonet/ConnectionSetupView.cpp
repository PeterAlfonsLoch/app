// ConnectionSetupView1.cpp : implementation file
//

#include "stdafx.h"
#include "vmsmiditonet.h"
#include "ConnectionSetupView.h"

#include "MidiToNetAsyncSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void SetAddress(CIPAddressCtrl & ctrl, LPCTSTR lpcsz);
void GetAddress(CIPAddressCtrl & ctrl, CString & str);


UINT grbChanMsgLen[] =
{ 
    0,                      /* 0x   not a status byte   */
    0,                      /* 1x   not a status byte   */
    0,                      /* 2x   not a status byte   */
    0,                      /* 3x   not a status byte   */
    0,                      /* 4x   not a status byte   */
    0,                      /* 5x   not a status byte   */
    0,                      /* 6x   not a status byte   */
    0,                      /* 7x   not a status byte   */
    3,                      /* 8x   Note off            */
    3,                      /* 9x   Note on             */
    3,                      /* Ax   Poly pressure       */
    3,                      /* Bx   Control change      */
    2,                      /* Cx   Program change      */
    2,                      /* Dx   Chan pressure       */
    3,                      /* Ex   Pitch bend change   */
    0,                      /* Fx   SysEx (see below)   */             
} ;


int MidiGetMessageLen(BYTE bEvent)
{
	return grbChanMsgLen[(bEvent >> 4) & 0x0F];
}

/////////////////////////////////////////////////////////////////////////////
// ConnectionSetupView

IMPLEMENT_DYNCREATE(ConnectionSetupView, CFormView)

ConnectionSetupView::ConnectionSetupView()
	: CFormView(ConnectionSetupView::IDD)
{
   m_psocket = NULL;
   m_psocketY = NULL;
   m_estate = StateInitial;
   m_econnmode = ConnModeNone;
   m_hmidiin = NULL;
	//{{AFX_DATA_INIT(ConnectionSetupView)
	m_uiRemoteServerPort = 0;
	m_uiLocalServerPort = 0;
	//}}AFX_DATA_INIT

   m_uiDevIn = -1;
   m_i = 0;
   AfxBeginThread(MidiOutThreadProc, this);
   m_bMidiInitOut = false;
}

ConnectionSetupView::~ConnectionSetupView()
{
}

void ConnectionSetupView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ConnectionSetupView)
	DDX_Control(pDX, IDC_LIST_MIDI_IN_DEVICES, m_listboxDev);
	DDX_Control(pDX, IDC_IPADDRESS_REMOTE_SERVER, m_ipaddressRemoteServer);
	DDX_Text(pDX, IDC_EDIT_REMOTE_SERVER_PORT, m_uiRemoteServerPort);
   DDX_Text(pDX, IDC_EDIT_LOCAL_SERVER_PORT, m_uiLocalServerPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ConnectionSetupView, CFormView)
	//{{AFX_MSG_MAP(ConnectionSetupView)
	ON_COMMAND(ID_ACTION_CALL, OnActionCall)
	ON_COMMAND(ID_ACTION_STOP, OnActionStop)
	ON_UPDATE_COMMAND_UI(ID_ACTION_CALL, OnUpdateActionCall)
	ON_UPDATE_COMMAND_UI(ID_ACTION_STOP, OnUpdateActionStop)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS_SERVER, OnFieldchangedIpaddressServer)
	ON_LBN_SELCHANGE(IDC_LIST_MIDI_IN_DEVICES, OnSelchangeListMidiInDevices)
	ON_COMMAND(ID_ACTION_LISTEN, OnActionListen)
	ON_UPDATE_COMMAND_UI(ID_ACTION_LISTEN, OnUpdateActionListen)
	ON_EN_CHANGE(IDC_EDIT_LOCAL_SERVER_PORT, OnChangeEditLocalServerPort)
	ON_EN_CHANGE(IDC_EDIT_REMOTE_SERVER_PORT, OnChangeEditRemoteServerPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ConnectionSetupView diagnostics

#ifdef _DEBUG
void ConnectionSetupView::AssertValid() const
{
	CFormView::AssertValid();
}

void ConnectionSetupView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// ConnectionSetupView message handlers

void ConnectionSetupView::OnActionStop() 
{
   Stop();
}

void ConnectionSetupView::OnActionCall() 
{
   Call();
}

void ConnectionSetupView::OnUpdateActionCall(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_estate == StateInitial);
}

void ConnectionSetupView::OnActionListen() 
{
   Listen();
}

void ConnectionSetupView::OnUpdateActionListen(CCmdUI* pCmdUI) 
{
   pCmdUI->Enable(m_estate == StateInitial);
}


void ConnectionSetupView::OnUpdateActionStop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_estate != StateInitial);
}



void ConnectionSetupView::Stop()
{
   StopMidiOut();
   StopMidiIn();
   StopSocket();



}

void ConnectionSetupView::Call()
{
   m_econnmode = ConnModeCaller;
   if(!InitSocket())
      return;

   m_estate = StateCalling;

}

void ConnectionSetupView::Listen()
{
   m_econnmode = ConnModeListener;
   if(!InitSocket())
      return;

   m_estate = StateListening;

}


void CALLBACK ConnectionSetupView::WinMidiInProc(HMIDIIN hMidiIn,UINT wMsg,DWORD dwInstance,
        DWORD dwParam1,DWORD dwParam2)
{
   ConnectionSetupView * pcallback = (ConnectionSetupView *) dwInstance;
//	int midicommand=MidiNull;
	if (wMsg==MIM_DATA){
		int cmd,par1,par2;
		cmd=dwParam1&0xff;
		if (cmd==0xfe) return;
		par1=(dwParam1>>8)&0xff;
		par2=dwParam1>>16;
		//printf("%x %x %x\n",cmd,par1,par2);fflush(stdout);
		int cmdchan=cmd&0x0f;
		int cmdtype=(cmd>>4)&0x0f;

      DWORD dwTimeStamp = dwParam2;

		int tmp=0;
//    		pthread_mutex_lock(&winmaster->mutex);
		switch(cmdtype)
      {
      case(0x8):// Note On
         pcallback->SendNoteOff(dwTimeStamp, cmdchan, par1, par2&0xff);
         break;
		case(0x9):// Note Off
         pcallback->SendNoteOn(dwTimeStamp, cmdchan, par1, par2&0xff);
			break;	
		case(0xb):// Control Change
		   pcallback->SendControlChange(dwTimeStamp, cmdchan, par1, par2&0xff); 
			break;
		case(0xc):// Program Change
		   pcallback->SendProgramChange(dwTimeStamp, cmdchan, par1, par2&0xff); 
			break;
		case(0xd):// Channel Pressure
		   pcallback->SendChannelPressure(dwTimeStamp, cmdchan, par1, par2&0xff); 
			break;
		case(0xe):// Pitch Wheel
		   pcallback->SendPitchBend(dwTimeStamp, cmdchan, par1, par2&0xff); 
			break;
		default:
         break;
		};
  //  		pthread_mutex_unlock(&winmaster->mutex);

	};
};

bool ConnectionSetupView::InitMidiIn()
{
	long int result = midiInOpen(&m_hmidiin,
         m_uiDevIn,(DWORD)WinMidiInProc, (DWORD) this,CALLBACK_FUNCTION);
   if(result != MMSYSERR_NOERROR)
      return false;

	result=midiInStart(m_hmidiin);
   if(result != MMSYSERR_NOERROR)
   {
      AfxMessageBox("Error opening Midi In Device");
      return false;
   }

   m_listboxDev.EnableWindow(false);

   return true;
}

bool ConnectionSetupView::StopMidiIn()
{
   long int result = midiInStop(m_hmidiin);
   result = midiInClose(m_hmidiin);
   return result == MMSYSERR_NOERROR;
}

bool ConnectionSetupView::InitSocket()
{
   UpdateData();
   m_psocket = new MidiToNetAsyncSocket();

   m_psocket->m_pserver = this;


   if(m_econnmode == ConnModeCaller)
   {

      BYTE  b1, b2, b3, b4;
      m_ipaddressRemoteServer.GetAddress(b1, b2, b3, b4);
      CString str;
      str.Format("%d.%d.%d.%d", b1, b2, b3, b4);

   

      m_psocket->Create(0, SOCK_STREAM, FD_READ | FD_WRITE | FD_OOB |
         FD_ACCEPT | FD_CONNECT | FD_CLOSE);

      if(!m_psocket->Connect(str, m_uiRemoteServerPort))
      {
         DWORD dwError = ::GetLastError();

         if(dwError == WSAEWOULDBLOCK)
         {
            return true;
         }


         return false;
      }
      return true;
   }
   else if(m_econnmode == ConnModeListener)
   {
      m_psocket->Create(m_uiLocalServerPort, SOCK_STREAM, FD_READ | FD_WRITE | FD_OOB |
         FD_ACCEPT | FD_CONNECT | FD_CLOSE);

      if(!m_psocket->Listen())
      {
         DWORD dwError = ::GetLastError();

         if(dwError == WSAEWOULDBLOCK)
         {
            return true;
         }


         return false;
      }
      return true;
   }
   else
   {
      ASSERT(FALSE);
      return false;
   }
}

bool ConnectionSetupView::StopSocket()
{
   m_psocket->Close();
   delete m_psocket;
   m_estate = StateInitial;
   return false;
}


void ConnectionSetupView::SendNoteOff(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   MIDITONETMESSAGE msg;
   DWORD dwPosition = dwTimeStamp;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg = 0x08;
   msg.uiChannel = nChannel;
   msg.uiParam1 = uiParam1;
   msg.uiParam2 = uiParam2;
   
   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}

void ConnectionSetupView::SendNoteOn(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   CSingleLock slMidiIn(&m_csMidiIn, TRUE);

   /*DWORD dwPosition = GetTickCount();*/
   DWORD dwPosition = dwTimeStamp;

   MIDITONETMESSAGE msg;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg      = 0x09;
   msg.uiChannel  = nChannel;
   msg.uiParam1   = uiParam1;
   msg.uiParam2   = uiParam2;

   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}

void ConnectionSetupView::SendControlChange(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   CSingleLock slMidiIn(&m_csMidiIn, TRUE);

   /*DWORD dwPosition = GetTickCount();*/
   DWORD dwPosition = dwTimeStamp;

   MIDITONETMESSAGE msg;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg      = 0x0b;
   msg.uiChannel  = nChannel;
   msg.uiParam1   = uiParam1;
   msg.uiParam2   = uiParam2;

   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}


void ConnectionSetupView::SendProgramChange(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   CSingleLock slMidiIn(&m_csMidiIn, TRUE);

   /*DWORD dwPosition = GetTickCount();*/
   DWORD dwPosition = dwTimeStamp;

   MIDITONETMESSAGE msg;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg      = 0x0c;
   msg.uiChannel  = nChannel;
   msg.uiParam1   = uiParam1;
   msg.uiParam2   = uiParam2;

   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}
void ConnectionSetupView::SendChannelPressure(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   CSingleLock slMidiIn(&m_csMidiIn, TRUE);

   /*DWORD dwPosition = GetTickCount();*/
   DWORD dwPosition = dwTimeStamp;

   MIDITONETMESSAGE msg;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg      = 0x0d;
   msg.uiChannel  = nChannel;
   msg.uiParam1   = uiParam1;
   msg.uiParam2   = uiParam2;

   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}

void ConnectionSetupView::SendPitchBend(DWORD dwTimeStamp, UINT nChannel, UINT uiParam1, UINT uiParam2)
{
   CSingleLock slMidiIn(&m_csMidiIn, TRUE);

   /*DWORD dwPosition = GetTickCount();*/
   DWORD dwPosition = dwTimeStamp;

   MIDITONETMESSAGE msg;
   msg.dwTimeStamp = dwTimeStamp;
   msg.uiDelta    = m_dwLastPosition - dwPosition;
   msg.uiMsg      = 0x0e;
   msg.uiChannel  = nChannel;
   msg.uiParam1   = uiParam1;
   msg.uiParam2   = uiParam2;

   m_msgaIn.Add(msg);

   m_dwLastPosition = dwPosition;
}

void ConnectionSetupView::OnConnection()
{
   m_psocketY = m_psocket;
   InitMidiIn();
   InitMidiOut();
}

void ConnectionSetupView::OnConnectionFailure(UINT nErrorCode)
{
   m_estate = StateInitial;
}

void ConnectionSetupView::OnAccept()
{
   m_psocketXXX = new MidiToNetAsyncSocket;
   m_psocketXXX->m_pserver = this;
   m_psocket->Accept(*m_psocketXXX);
   m_psocketY = m_psocketXXX;

   InitMidiIn();
   InitMidiOut();
}

void ConnectionSetupView::OnAcceptFailure(UINT nErrorCode)
{
   m_estate = StateInitial;
}

void ConnectionSetupView::OnTimer(UINT nIDEvent) 
{
   if(nIDEvent == 8734)
   {
      if(m_psocketY != NULL)
      {
         CSingleLock slMidiIn(&m_csMidiIn, TRUE);
         CSingleLock slMidiOut(&m_csMidiOut, TRUE);
         m_msgaOut.Append(m_msgaIn);
         m_msgaIn.RemoveAll();
         slMidiIn.Unlock();
         m_psocketY->Post(m_msgaOut);
         m_msgaOut.RemoveAll();
      }
   }
	CFormView::OnTimer(nIDEvent);
}

int ConnectionSetupView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
   SetTimer(8734, 1, NULL);	
	return 0;
}


void ConnectionSetupView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
   CString str;
   str = AfxGetApp()->GetProfileString("TCP Settings", "Remote Server IP Address", "127.0.0.1");
   SetAddress(m_ipaddressRemoteServer, str);	
   m_uiLocalServerPort = AfxGetApp()->GetProfileInt("TCP Settings", "Local Server Port", 8734);
   m_uiRemoteServerPort = AfxGetApp()->GetProfileInt("TCP Settings", "Remote Server Port", 8734);
   UpdateData(FALSE);

   m_listboxDev.ResetContent();

   UINT uiDevCount = midiInGetNumDevs();

   MIDIINCAPS mic;

   for(UINT uiDev = 0; uiDev < uiDevCount; uiDev++)
   {
      midiInGetDevCaps(uiDev, &mic, sizeof(mic));
      m_listboxDev.AddString(mic.szPname);
   }
	
}


void SetAddress(CIPAddressCtrl & ctrl, LPCTSTR lpcsz)
{
   UINT b1, b2, b3, b4;
   sscanf( lpcsz, "%u.%u.%u.%u", &b1, &b2, &b3, &b4 );
   ctrl.SetAddress(b1, b2, b3, b4);
}
void GetAddress(CIPAddressCtrl & ctrl, CString & str)
{
   UINT b1, b2, b3, b4;
   ctrl.GetAddress((BYTE & )b1, (BYTE & )b2, (BYTE & )b3, (BYTE & )b4);
   str.Format( "%u.%u.%u.%u", b1, b2, b3, b4 );
}

void ConnectionSetupView::OnFieldchangedIpaddressServer(NMHDR* pNMHDR, LRESULT* pResult) 
{
   CString str;
   GetAddress(m_ipaddressRemoteServer, str);	
   AfxGetApp()->WriteProfileString("TCP Settings", "Remote Server IP Address", str);
	*pResult = 0;
}


void ConnectionSetupView::OnSelchangeListMidiInDevices() 
{
   m_uiDevIn = m_listboxDev.GetCurSel();
}



void ConnectionSetupView::OnChangeEditLocalServerPort() 
{
   if(UpdateData())
   {
      AfxGetApp()->WriteProfileInt("TCP Settings", "Local Server Port", m_uiLocalServerPort);
   }
}

void ConnectionSetupView::OnChangeEditRemoteServerPort() 
{
   if(UpdateData())
   {
      AfxGetApp()->WriteProfileInt("TCP Settings", "Remote Server Port", m_uiRemoteServerPort);
   }
}


void ConnectionSetupView::OnMessage(LPBYTE lpbuf, int nRead)
{

   //if(nRead >= sizeof(MIDITONETMESSAGE))
   //{
   while(nRead > 0)
   {
      int iProcessed = min(sizeof(MIDITONETMESSAGE) - m_i, nRead);
      memcpy(((LPBYTE)&m_msg) + m_i, lpbuf, iProcessed);
      m_i += iProcessed;
      if(m_i == sizeof(MIDITONETMESSAGE))
      {
         m_msga.Add(m_msg);
         m_i = 0;
      }
      nRead -= iProcessed;
      lpbuf += iProcessed;
   }

   MIDITONETMESSAGE & msg = *((MIDITONETMESSAGE*)lpbuf);

   



}


UINT AFX_CDECL ConnectionSetupView::MidiOutThreadProc(
  LPVOID lpParameter   // thread data
)
{
   ConnectionSetupView * pserver = (ConnectionSetupView *) lpParameter;

   CEvent event;
   MMRESULT mmr;
   int iResolution = 5;
   DWORD dwWaitingDelay = 5;
   DWORD dwDelay = 5;
   DWORD dwLastDiff = GetTickCount() - 10000;
   int iSrcDestDiff = 0;
   DWORD dwSvr;
   DWORD dwPosition;
   DWORD dwOutDelay = 10;
   try
   {
      while(true)
      {
         mmr = timeSetEvent(
            dwDelay,
            iResolution,  // 5 ms resolution
            (LPTIMECALLBACK) (HANDLE) event,  
            NULL,      
            TIME_ONESHOT | TIME_CALLBACK_EVENT_SET);

         event.Lock();

        dwSvr = timeGetTime();
        dwPosition = dwSvr - pserver->m_dwStartPosition;

         if(pserver->m_msga.GetSize() == 0)
         {
            dwDelay = dwWaitingDelay;
         }
         else
         {
            while(pserver->m_msga.GetSize() > 0 &&
               dwPosition - pserver->m_dwStreamPosition > dwOutDelay)
            {
               pserver->MidiOut(pserver->m_msga[0]);
               pserver->m_msga.RemoveAt(0);
            }
            if(pserver->m_msga.GetSize() > 0)
            {
               dwDelay = pserver->m_msga[0].uiDelta + dwOutDelay - 
                  (dwPosition - pserver->m_dwStreamPosition);
            }
            else
            {
               dwDelay = dwWaitingDelay;
            }
         }

      }
   }
   catch(...)
   {
      try
      {
      }
      catch(...)
      {
         ASSERT(FALSE);
         return -3;
      }
   }
   return 0;


}


void ConnectionSetupView::MidiOut(MIDITONETMESSAGE &msg)
{
   ASSERT(m_bMidiInitOut);
   if(msg.uiMsg == 0x08)
   {
      DWORD dw;

      dw = (msg.uiMsg << 4) | msg.uiChannel;
      dw |= msg.uiParam1 << 8;

      LPMIDIHDR lpmidihdr = &m_midihdra[m_iBuffer];
      MIDIEVENT * lpmidiev = (MIDIEVENT *) m_midihdra[m_iBuffer].lpData;

      lpmidiev->dwDeltaTime = msg.uiDelta;
      lpmidiev->dwStreamID = 0;
      lpmidiev->dwEvent = MEVT_F_SHORT | MEVT_SHORTMSG;
      lpmidiev->dwEvent |= dw;

      lpmidihdr->dwBytesRecorded = 12;

      UINT result = midiStreamOut(m_hmidiout, lpmidihdr, sizeof(MIDIHDR));
      VERIFY(result == MMSYSERR_NOERROR);

      m_iBuffer++;
      m_iBuffer %= m_midihdra.GetSize();

   }
   else if(msg.uiMsg == 0x09)
   {
      DWORD dw;

      dw = (msg.uiMsg << 4) | msg.uiChannel;
      dw |= msg.uiParam1 << 8 | msg.uiParam2 << 16;

      LPMIDIHDR lpmidihdr = &m_midihdra[m_iBuffer];
      MIDIEVENT * lpmidiev = (MIDIEVENT *) m_midihdra[m_iBuffer].lpData;

      lpmidiev->dwDeltaTime = msg.uiDelta;
      lpmidiev->dwStreamID = 0;
      lpmidiev->dwEvent = MEVT_F_SHORT | MEVT_SHORTMSG;
      lpmidiev->dwEvent |= dw;

      lpmidihdr->dwBytesRecorded = 12;

      UINT result = midiStreamOut(m_hmidiout, lpmidihdr, sizeof(MIDIHDR));
      VERIFY(result == MMSYSERR_NOERROR);

      m_iBuffer++;
      m_iBuffer %= m_midihdra.GetSize();

   }
   else if(msg.uiMsg == 0x0b)
   {
      DWORD dw;

      dw = (msg.uiMsg << 4) | msg.uiChannel;
      dw |= msg.uiParam1 << 8 | msg.uiParam2 << 16;

      LPMIDIHDR lpmidihdr = &m_midihdra[m_iBuffer];
      MIDIEVENT * lpmidiev = (MIDIEVENT *) m_midihdra[m_iBuffer].lpData;

      lpmidiev->dwDeltaTime = msg.uiDelta;
      lpmidiev->dwStreamID = 0;
      lpmidiev->dwEvent = MEVT_F_SHORT | MEVT_SHORTMSG;
      lpmidiev->dwEvent |= dw;

      lpmidihdr->dwBytesRecorded = 12;

      UINT result = midiStreamOut(m_hmidiout, lpmidihdr, sizeof(MIDIHDR));
      VERIFY(result == MMSYSERR_NOERROR);

      m_iBuffer++;
      m_iBuffer %= m_midihdra.GetSize();

   }
   else // if(msg.uiMsg == 0x0b)
   {
      DWORD dw;

      dw = (msg.uiMsg << 4) | msg.uiChannel;
      dw |= msg.uiParam1 << 8 | msg.uiParam2 << 16;

      LPMIDIHDR lpmidihdr = &m_midihdra[m_iBuffer];
      MIDIEVENT * lpmidiev = (MIDIEVENT *) m_midihdra[m_iBuffer].lpData;

      lpmidiev->dwDeltaTime = msg.uiDelta;
      lpmidiev->dwStreamID = 0;
      lpmidiev->dwEvent = MEVT_F_SHORT | MEVT_SHORTMSG;
      lpmidiev->dwEvent |= dw;

      lpmidihdr->dwBytesRecorded = 12;

      UINT result = midiStreamOut(m_hmidiout, lpmidihdr, sizeof(MIDIHDR));
      VERIFY(result == MMSYSERR_NOERROR);

      m_iBuffer++;
      m_iBuffer %= m_midihdra.GetSize();

   }
   m_dwStreamPosition += msg.uiDelta;


}


bool ConnectionSetupView::InitMidiOut()
{
   if(m_bMidiInitOut)
      return true;
   m_i = 0;
   m_dwStartPosition = GetTickCount();;
   m_dwStreamPosition = 0;
   //UINT result = midiOutOpen(&m_hmidiout, 0, MidiOutProc, this, CALLBACK_FUNCTION);
   m_uiDevOut = MIDI_MAPPER;
//   UINT result = midiStreamOpen(&m_hmidiout, &m_uiDev, 1, MidiOutProc, this, CALLBACK_FUNCTION);
   UINT result = midiStreamOpen(&m_hmidiout, &m_uiDevOut, 1, NULL, (LPARAM) this, CALLBACK_NULL);

   if(result != MMSYSERR_NOERROR)
   {
      m_bMidiInitOut = false;
      return false;
   }

   m_midihdra.SetSize(16);
   m_midibufa.SetSize(16);

   int iSize = 1024;
   for(int i = 0; i < m_midihdra.GetSize(); i++)
   {
      m_midibufa[i] = (LPBYTE) malloc(iSize);
      m_midihdra[i].lpData = (char *) m_midibufa[i];
      m_midihdra[i].dwBufferLength = iSize;
      m_midihdra[i].dwBytesRecorded = 0;
      m_midihdra[i].dwUser = 0;
      m_midihdra[i].dwFlags = 0;
      m_midihdra[i].lpNext = NULL;
      m_midihdra[i].reserved = 0;
      m_midihdra[i].dwOffset = 0;
      if(MMSYSERR_NOERROR != midiOutPrepareHeader(
         (HMIDIOUT) m_hmidiout,            
         &m_midihdra[i],  
         sizeof(MIDIHDR)))
      {
         return false;
      }
   }

   m_iBuffer = 0;

   Sleep(1000);
   midiStreamRestart(m_hmidiout);


   if(result == MMSYSERR_NOERROR)
   {
      m_bMidiInitOut = true;
      return true;
   }
   else
   {
      AfxMessageBox("Error opening Midi Out Device");
      return false;
   }

}

bool ConnectionSetupView::StopMidiOut()
{
   if(!m_bMidiInitOut)
      return false;

   midiStreamClose(m_hmidiout);
   m_bMidiInitOut = false;
}

void ConnectionSetupView::OnSocketAfterClose()
{
   StopMidiIn(); 
   StopMidiOut();
   m_estate = StateInitial;
}
