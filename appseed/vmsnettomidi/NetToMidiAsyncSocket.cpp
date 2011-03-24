// NetToMidiAsyncSocket.cpp : implementation file
//

#include "stdafx.h"
#include "vmsnettomidi.h"
#include "NetToMidiAsyncSocket.h"
#include "NetToMidiServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NetToMidiAsyncSocket

NetToMidiAsyncSocket::NetToMidiAsyncSocket()
{
}

NetToMidiAsyncSocket::~NetToMidiAsyncSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(NetToMidiAsyncSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(NetToMidiAsyncSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// NetToMidiAsyncSocket member functions


void NetToMidiAsyncSocket::OnConnect(int nErrorCode) 
{
   if (nErrorCode == 0)
   {
      m_pserver->PulseEvent(_vmsnettomidi::EventConnectionSuccess);
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
      m_pserver->PulseEvent(_vmsnettomidi::EventConnectionFailure);
   }
   CAsyncSocket::OnConnect(nErrorCode);
}



void NetToMidiAsyncSocket::OnReceive(int nErrorCode) 
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

void NetToMidiAsyncSocket::OnAccept(int nErrorCode) 
{
   if(nErrorCode == 0)
   {
      m_pserver->PulseEvent(_vmsnettomidi::EventAcceptSuccess);
   }
   else
   {
      m_pserver->PulseEvent(_vmsnettomidi::EventAcceptFailure);
   }
	// TODO: Add your specialized code here and/or call the base class
	
	CAsyncSocket::OnAccept(nErrorCode);
}
