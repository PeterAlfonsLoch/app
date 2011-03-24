// NetToMidiServer.h: interface for the NetToMidiServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETTOMIDISERVER_H__81D8C089_FBBE_4692_95FE_4CEC0C2BD98F__INCLUDED_)
#define AFX_NETTOMIDISERVER_H__81D8C089_FBBE_4692_95FE_4CEC0C2BD98F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class NetToMidiAsyncSocket;

namespace _vmsnettomidi
{
enum EState
{
   StateInitial,
   StateListening,
   StateCalling,
   StateActive,
};

enum EEvent
{
   EventListen,
   EventCall,
   EventAcceptSuccess,
   EventAcceptFailure,
   EventConnectionSuccess,
   EventConnectionFailure,
   EventEnd,
};

}


class NetToMidiPoint
{
public:

   CArray < MIDIHDR, MIDIHDR> m_midihdra;
   CArray < LPBYTE, LPBYTE> m_midibufa;

	void MidiOut(MIDITONETMESSAGE &msg);
	void OnMessage(LPBYTE lpbuf, int nRead);
	void StopMidi();
	bool InitMidi();
	void SetServerPort(UINT uiServerPort);
   void PulseEvent(_vmsnettomidi::EEvent eevent);
	_vmsnettomidi::EState GetState();
	NetToMidiPoint();
	virtual ~NetToMidiPoint();

   UINT m_uiDev;
   int m_iBuffer;

   static UINT AFX_CDECL MidiOutThreadProc(LPVOID lpParameter);


   CArray < MIDITONETMESSAGE, MIDITONETMESSAGE & > m_msga;

   static void CALLBACK MidiOutProc(
      HMIDIOUT hmo,      
      UINT wMsg,         
      DWORD dwInstance,  
      DWORD dwParam1,    
      DWORD dwParam2     
);

   MIDITONETMESSAGE m_msg;
   int m_i;
   CString m_strRemoteServerAddress;
   UINT m_uiRemoteServerPort;


private:
   NetToMidiAsyncSocket * m_psocketServer;
   NetToMidiAsyncSocket * m_psocketClient;
   NetToMidiAsyncSocket * m_psocketXXX;
   _vmsnettomidi::EState m_estate;
   HMIDISTRM m_hmidiout;
   UINT  m_uiServerPort;
   bool     m_bMidiInit;

   DWORD       m_dwStartPosition;
   DWORD       m_dwStreamPosition;

};

#endif // !defined(AFX_NETTOMIDISERVER_H__81D8C089_FBBE_4692_95FE_4CEC0C2BD98F__INCLUDED_)
