#include "StdAfx.h"

namespace tarsila
{

socket::socket(::ca::application * papp)
: CAsyncProxySocket(papp), m_memfileSend(papp),
m_memfileBody(papp), m_memfileReceive(papp)
{
   m_osBody.m_pwriter = &m_memfileBody;
/*	m_strHead += "HTTP/1.1 200 OK\n";
	m_strHead += "Server: netnode/1.0 (Windows)\n";
	m_strHead += "Accept-Ranges: bytes\n";
	m_strHead += "Date: Mon, 23 May 2005 22:38:34 GMT\n";
	m_strHead += "Server: netnode/1.0 (Windows)\n";
	m_strHead += "Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n";
	//m_memfileSend += "Etag: "3f80f-1b6-3e1cb03b"";
	m_strHead += "Accept-Ranges: bytes\n";
	// m_memfileSend += "Content-Length: 438";
	//m_strHead += "Connection: close\n";

	/*m_memfileBody << "<html>\n";
	m_memfileBody << "<head>\n";
	m_memfileBody << "</head>\n";
	m_memfileBody << "<body>\n";
	m_memfileBody << "<h1>Ti Amo Carlos Gustavo Cecyn Lundgren de 15 de novembro de 1984!</h1>\n";
	m_memfileBody << "<h1>Assinado Camilo Sasuke Tsumanuma de 2 de abril de 1977!</h1>\n";
	m_memfileBody << "</body>\n";*/
	m_nBytesSent = 0;
	m_nBytesBufferSize = 1024;
	m_bPendingSend = false;
   m_storageReceive.Allocate(1024 * 64);
   m_iBodyStart = -1;
}

socket::~socket(void)
{
}

void socket::OnConnect(int nErrorCode)
{
	CAsyncProxySocket::OnConnect(nErrorCode);
   start();
}

void socket::OnReceive(int nErrorCode)
{
   CAsyncProxySocket::OnReceive(nErrorCode);

	int nRead;
   while((nRead = Receive(m_storageReceive.GetAllocation(), m_storageReceive.GetStorageSize())) > 0)
   {
      m_memfileReceive.Write(m_storageReceive.GetAllocation(), nRead);
   }
   bool bFoundHead = false;
   if(m_iBodyStart == -1)
   {
      m_iBodyStart = -1;
      for(int i = 0; i < m_memfileReceive.GetStorageSize_(); i++)
      {
         if(memcmp(m_memfileReceive.GetAllocation() + i, "\r\n\r\n", 4) == 0)
         {
            m_iBodyStart = i + 4;
            m_strHead = string((const char *) m_memfileReceive.GetAllocation(), m_iBodyStart);
            gen::property_set head;
            head.parse_http_headers(m_strHead);
            m_iContentLength = head["content-length"];
            bFoundHead = true;
            break;
         }
      }
   }
	
	if(nRead == 0)
	{
	}
	else if(nRead == SOCKET_ERROR)
	{
      DWORD dw = ::GetLastError();
      if(dw == WSAEWOULDBLOCK)
      {
      }
      else
      {
		   Close();
         TRACE("ERROR");
      }
		
	}
   if(m_iBodyStart + m_iContentLength == m_memfileReceive.GetStorageSize_())
   {

      OnReceiveBody();
      m_iBodyStart = -1;
      m_memfileReceive.Truncate(0);
   }
	CAsyncProxySocket::OnReceive(nErrorCode);
}


void socket::start()
{
   m_eaction = ActionSnapshot;
   m_bPendingSend = true;
   m_osBody << "GET /snapshoti.png\r\n";
   m_osBody << "\r\n";
   netshareSend();
}

void socket::OnReceiveBody()
{
   if(m_eaction == ActionSetCursor ||
      m_eaction == ActionEvent)
   {
      if(m_straEvent.get_size() > 0)
      {
         m_eaction = ActionEvent;
         m_bPendingSend = true;
         m_osBody << "GET ";
         m_osBody << m_straEvent[0];
         m_osBody << "\r\n\r\n";
         m_straEvent.remove_at(0);
         netshareSend();
      }
      else
      {
         m_eaction = ActionSnapshot;
         m_bPendingSend = true;
         m_osBody << "GET /snapshoti.png\r\n";
         m_osBody << "\r\n";
         netshareSend();
      }
   }
   else if(m_eaction == ActionSnapshot)
   {
      for(int i = 0; i < m_memfileReceive.GetStorageSize_(); i++)
      {
         if(memcmp(m_memfileReceive.GetAllocation() + i, "\r\n\r\n", 4) == 0)
         {
            break;
         }
      }
      FIMEMORY * pfimemory = FreeImage_OpenMemory(
         m_memfileReceive.GetAllocation() + m_iBodyStart, 
         m_memfileReceive.GetStorageSize_() - m_iBodyStart);
      DWORD dw1 = ::GetTickCount();
      FIBITMAP * pfi1 = FreeImage_LoadFromMemory(FIF_PNG, pfimemory, 0);
      DWORD dw2 = ::GetTickCount();
      DWORD dw21 = dw2 - dw1;
      FIBITMAP * pfi2 = FreeImage_ConvertTo32Bits(pfi1);
      DWORD dw3 = ::GetTickCount();
      DWORD dw32 = dw3 - dw2;
      CSingleLock sl(&m_parea->m_cs, TRUE);
      void * pdata = FreeImage_GetBits(pfi2);
//      if(str == "I")
      if(pdata != NULL)
      {
         memcpy(m_parea->m_dib1.m_Bits, pdata, 
            m_parea->m_dib1.m_size.cx * m_parea->m_dib1.m_size.cy * 4);
      }
  /*    else
      {
         memcpy(m_parea->m_dib2.m_Bits, pdata, 
            m_parea->m_dib2.m_size.cx * m_parea->m_dib2.m_size.cy * 4);
         m_parea->m_dib1.xor(&m_parea->m_dib2);
      }*/
      FreeImage_Unload(pfi2);
      FreeImage_Unload(pfi1);
      // always close the memory stream
      FreeImage_CloseMemory(pfimemory);
      m_memfileReceive.Truncate(0);

      m_pview->_001RedrawWindow();
         m_eaction = ActionSetCursor;
      m_bPendingSend = true;
      string strQuery;
      strQuery.Format("x=%d&y=%d", m_ptCursor.x, m_ptCursor.y);
      m_osBody << "GET /set_cursor_pos?" << strQuery << "\n";
      m_osBody << "\n";
      netshareSend();

   }
}


void socket::OnSend(int nErrorCode)
{
	netshareSend();
   CAsyncProxySocket::OnSend(nErrorCode);
}
void socket::OnOutOfBandData(int nErrorCode)
{
	CAsyncProxySocket::OnOutOfBandData(nErrorCode);
}
void socket::OnAccept(int nErrorCode)
{
	CAsyncProxySocket::OnAccept(nErrorCode);
}
void socket::OnClose(int nErrorCode)
{
	CAsyncProxySocket::OnClose(nErrorCode);
}

void socket::netshareSend()
{
	if(m_bPendingSend)
	{
		m_bPendingSend = false;
//		m_memfileSend << m_memfileBody.GetLength();
      m_memfileSend.Write(m_memfileBody.GetAllocation(), m_memfileBody.GetStorageSize_());
      m_memfileBody.Truncate(0);
	}
	else
	{
		return;
	}

//TRACE(m_memfileSend);

	m_nBytesBufferSize = m_memfileSend.GetLength();
	while (m_nBytesSent < m_nBytesBufferSize)
   {
      int dwBytes;

      if ((dwBytes = Send((LPCTSTR)m_memfileSend.GetAllocation() + m_nBytesSent, 
         m_nBytesBufferSize - m_nBytesSent)) == SOCKET_ERROR)
      {
         if (GetLastError() == WSAEWOULDBLOCK) break;
         else
         {
            TCHAR szError[256];
            wsprintf(szError, "Server Socket failed to send: %d", 
               GetLastError());
            Close();
            Application.simple_message_box (szError);
         }
      }
      else
      {
         m_nBytesSent += dwBytes;
      }
   }
	if (m_nBytesSent == m_nBytesBufferSize)
	{
     m_nBytesSent = m_nBytesBufferSize = 0;
     m_memfileSend.Truncate(0);
  }
}

void socket::get(LPCTSTR lpcsz)
{
	string str(lpcsz);
	if(str == "debug")
	{
	}
   AStrArray stra;
   stra.add_tokens(lpcsz, "?", TRUE);
 
		
}


void socket::set_cursor(int x, int y)
{
   m_ptCursor.x = x;
   m_ptCursor.y = y;
}


//This function has to be implemented by the derived classes. This function is 
//called when an error occurred during a SOCKS operation
void socket::OnProxyOperationFailed(int nOpID)
{
}
	

//Called when a listen socket was created successfully. Unlike the normal listen function,
//a socksified socket has to connect to the proxy to negotiate the details with the server
//on which the listen socket will be created
//The two parameters will contain the address of the listen socket on the server.
void socket::OnListenFinished(unsigned long &retProxyIp,int &retProxyPort)
{
}



} // namespace tarsila


