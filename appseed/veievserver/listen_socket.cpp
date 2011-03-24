#include "StdAfx.h"
#include "listen_socket.h"
#include "socket.h"

#include "thread.h"

namespace netshareserver
{

listen_socket::listen_socket(thread * pthread) :
   ::ca::ca(pthread->get_app()),
   CAsyncSocket(pthread->get_app())
{
	m_pthread = pthread;
}

listen_socket::~listen_socket(void)
{
}


void listen_socket::OnReceive(int nErrorCode)
{
	CAsyncSocket::OnReceive(nErrorCode);
}
void listen_socket::OnSend(int nErrorCode)
{
	CAsyncSocket::OnSend(nErrorCode);
}
void listen_socket::OnOutOfBandData(int nErrorCode)
{
	CAsyncSocket::OnOutOfBandData(nErrorCode);
}
void listen_socket::OnAccept(int nErrorCode)
{
	m_pthread->PostThreadMessage(WM_APP, 1, 	(LPARAM) this);

/*socket * psocket = new socket(this);
	CSingleLock sl(&m_cssocket);
	Accept(*psocket);
	m_ptrasocket.add(psocket);
	CAsyncSocket::OnAccept(nErrorCode);*/

}
void listen_socket::OnConnect(int nErrorCode)
{
	CAsyncSocket::OnConnect(nErrorCode);
}
void listen_socket::OnClose(int nErrorCode)
{
	CAsyncSocket::OnClose(nErrorCode);
}


void listen_socket::remove(class socket * psocket)
{
	CSingleLock sl(&m_cssocket);
	m_ptrasocket.remove(psocket);
	delete psocket;
}


} // namespace netshareserver