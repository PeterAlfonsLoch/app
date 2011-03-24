#pragma once


class netnodeApp;
class netnodeService;
class netnodeSocket;
class netnodeThread;

class netnodeListenSocket :
	public CAsyncSocket
{
public:
	netnodeListenSocket(netnodeThread * pthread);
	~netnodeListenSocket(void);

	netnodeThread * GetThread();

	comparable_array < netnodeSocket *, netnodeSocket * > m_ptraNetNodeSocket;
	::CCriticalSection m_csNetNodeSocket;

	netnodeThread * m_pthread;

	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void Remove(netnodeSocket * psocket);
};


inline netnodeThread * netnodeListenSocket::GetThread()
{
	return m_pthread;
}

