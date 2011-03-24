#pragma once

#include "ca2api009_00003/AsyncProxySocket.h"



namespace netshareservercfg
{

class application;
class view;


class socket :
	public CAsyncProxySocket
{
public:
	socket(::ca::application * papp);
	virtual ~socket();

   enum EAction
   {
      ActionEvent,
      ActionSetCursor,
      ActionSnapshot,
   };

   EAction              m_eaction;
	memory_file           m_memfileSend;
	memory_file           m_memfileBody;
   memory_file           m_memfileReceive;
   memory        m_storageReceive;
	bool                 m_bPendingSend;
   point                m_pt;
   AStrArray            m_straEvent;

   ex1::output_stream2  m_osBody;

   int                  m_iBodyStart;
   int                  m_iContentLength;
   string m_strHead;

   view *               m_pview;
   area *               m_parea;

   void OnReceiveBody();
	int m_nBytesSent;
	int m_nBytesBufferSize;
   point m_ptCursor;

   DWORD m_dwLastITime;

	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnOutOfBandData(int nErrorCode);
	virtual void OnAccept(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);


   void set_cursor(int x, int y);
	void get(LPCTSTR lpcsz);
   void start();
	

   void netshareSend();

   void OnProxyOperationFailed(int nOpID);
   void OnListenFinished(unsigned long &retProxyIp,int &retProxyPort);

};


} // namespace netshareservercfg
