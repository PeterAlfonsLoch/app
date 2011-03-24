#pragma once


class netshareserver_application;
class netshareserver_service;

namespace netshareserver
{

class socket;
class thread;

class listen_socket :
	public CAsyncSocket
{
public:
	listen_socket(thread * pthread);
	~listen_socket(void);

	thread * GetThread();

	comparable_array < class socket *, class socket * > m_ptrasocket;
	::CCriticalSection m_cssocket;

	thread * m_pthread;

	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void remove(class socket * psocket);
};


inline thread * listen_socket::GetThread()
{
	return m_pthread;
}

} // namespace netshareserver