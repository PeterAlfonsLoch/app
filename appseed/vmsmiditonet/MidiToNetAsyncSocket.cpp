// MidiToNetAsyncSocket.cpp : implementation file
//

#include "stdafx.h"
#include "vmsmiditonet.h"
#include "MidiToNetAsyncSocket.h"

#include "ConnectionSetupView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MidiToNetAsyncSocket

MidiToNetAsyncSocket::MidiToNetAsyncSocket()
{
   m_i = 0;
   m_bEmpty = true;
}

MidiToNetAsyncSocket::~MidiToNetAsyncSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(MidiToNetAsyncSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(MidiToNetAsyncSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// MidiToNetAsyncSocket member functions

void MidiToNetAsyncSocket::OnOutOfBandData(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}

void MidiToNetAsyncSocket::OnConnect(int nErrorCode) 
{
   m_bEmpty = true;
   m_i = 0;
   if (nErrorCode == 0)
   {
      m_pserver->OnConnection();
   }
   else
   {
      switch( nErrorCode )
      {
         case WSAEADDRINUSE: 
            AfxMessageBox("The specified address is already in use.\n");
            break;
         case WSAEADDRNOTAVAIL: 
            AfxMessageBox("The specified address is not available from \
               the local machine.\n");
            break;
         case WSAEAFNOSUPPORT: 
            AfxMessageBox("Addresses in the specified family cannot be \
               used with this socket.\n");
            break;
         case WSAECONNREFUSED: 
            AfxMessageBox("The attempt to connect was forcefully \
               rejected.\n");
            break;
         case WSAEDESTADDRREQ: 
            AfxMessageBox("A destination address is required.\n");
            break;
         case WSAEFAULT: 
            AfxMessageBox("The lpSockAddrLen argument is incorrect.\n");
            break;
         case WSAEINVAL: 
            AfxMessageBox("The socket is already bound to an \
               address.\n");
            break;
         case WSAEISCONN: 
            AfxMessageBox("The socket is already connected.\n");
            break;
         case WSAEMFILE: 
            AfxMessageBox("No more file descriptors are available.\n");
            break;
         case WSAENETUNREACH: 
            AfxMessageBox("The network cannot be reached from this host \
               at this time.\n");
            break;
         case WSAENOBUFS: 
            AfxMessageBox("No buffer space is available. The socket \
               cannot be connected.\n");
            break;
         case WSAENOTCONN: 
            AfxMessageBox("The socket is not connected.\n");
            break;
         case WSAENOTSOCK: 
            AfxMessageBox("The descriptor is a file, not a socket.\n");
            break;
         case WSAETIMEDOUT: 
            AfxMessageBox("The attempt to connect timed out without \
               establishing a connection. \n");
            break;
         default:
            TCHAR szError[256];
            wsprintf(szError, "OnConnect error: %d", nErrorCode);
            AfxMessageBox(szError);
            break;
      }
      AfxMessageBox("Please close the application");
      m_pserver->OnConnectionFailure(nErrorCode);
   }
   CAsyncSocket::OnConnect(nErrorCode);
}

void MidiToNetAsyncSocket::OnSend(int nErrorCode) 
{
	if(m_msga.GetSize() <= 0)
	{
      m_bEmpty = true;
   }
   else
   {
      SendBuffer();
   }
	CAsyncSocket::OnSend(nErrorCode);
}

void MidiToNetAsyncSocket::Post(MIDITONETMESSAGE &msg)
{
   m_msga.Add(msg);
   //if(m_bEmpty)
      SendBuffer();
}
void MidiToNetAsyncSocket::Post(
   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > &msga)
{
   m_msga.Append(msga);
   //if(m_bEmpty)
      SendBuffer();
}

void MidiToNetAsyncSocket::SendBuffer()
{
   if(m_msga.GetSize() > 0)
   {
      int iCount = m_msga.GetSize();
      m_bEmpty = false;
      MIDITONETMESSAGE * pmsg = m_msga.GetData();
      int i;
      i= Send(((LPBYTE) pmsg) + m_i, sizeof(MIDITONETMESSAGE) * iCount);
      if(i > 0)
      {
         m_i = i;
         m_msga.RemoveAt(0, m_i / sizeof(MIDITONETMESSAGE));
         m_i %= sizeof(MIDITONETMESSAGE); 
      }
   }

}

void MidiToNetAsyncSocket::OnAccept(int nErrorCode) 
{
   if(nErrorCode == 0)
   {
      m_pserver->OnAccept();
   }
   else
   {
      m_pserver->OnAcceptFailure(nErrorCode);
   }
	CAsyncSocket::OnAccept(nErrorCode);
}

void MidiToNetAsyncSocket::OnReceive(int nErrorCode) 
{
static int i=0;

   i++;

   TCHAR buff[4096];
   int nRead;
   nRead = Receive(buff, 4096); 
   
   switch (nRead)
   {
   case 0:
      Close();
      m_pserver->OnSocketAfterClose();
      break;
   case SOCKET_ERROR:
      if (GetLastError() != WSAEWOULDBLOCK) 
      {
         AfxMessageBox ("Error occurred");
         Close();
      }
      break;
   default:
      m_pserver->OnMessage((LPBYTE) buff, nRead);
   }
   CAsyncSocket::OnReceive(nErrorCode);
}
