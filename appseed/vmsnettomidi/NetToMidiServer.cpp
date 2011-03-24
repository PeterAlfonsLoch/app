// NetToMidiPoint.cpp: implementation of the NetToMidiPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vmsnettomidi.h"
#include "NetToMidiServer.h"
#include "NetToMidiAsyncSocket.h"

#include "../vmsmiditonet/_vmsmiditonet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

NetToMidiPoint::NetToMidiPoint()
{
   m_psocketXXX = NULL;
   m_bMidiInit = false;
   m_estate = _vmsnettomidi::StateInitial;

   m_psocketServer = new NetToMidiAsyncSocket();
   m_psocketServer->m_pserver = this;

   m_psocketClient = new NetToMidiAsyncSocket();
   m_psocketClient->m_pserver = this;


   AfxBeginThread(MidiOutThreadProc, this);

}

NetToMidiPoint::~NetToMidiPoint()
{
   if(m_psocketServer != NULL)
   {
      delete m_psocketServer;
   }

}

_vmsnettomidi::EState NetToMidiPoint::GetState()
{
   return m_estate;
}

void NetToMidiPoint::PulseEvent( _vmsnettomidi::EEvent eevent)
{
   switch(m_estate)
   {
   case  _vmsnettomidi::StateInitial:
      switch(eevent)
      {
      case  _vmsnettomidi::EventListen:
         if(!m_psocketServer->Create(m_uiServerPort))
         {
            ASSERT(FALSE);
         }
         if(!m_psocketServer->Listen())
         {
            ASSERT(FALSE);
         }
         m_estate = _vmsnettomidi::StateListening;
         break;
      case  _vmsnettomidi::EventCall:
         {
            if(!m_psocketClient->Create(0, SOCK_STREAM, FD_WRITE | FD_READ | FD_OOB |
                  FD_ACCEPT | FD_CONNECT | FD_CLOSE)
            )
            {
               ASSERT(FALSE);
               return;
            }
            m_estate = _vmsnettomidi::StateCalling;
            if(!m_psocketClient->Connect(m_strRemoteServerAddress, m_uiRemoteServerPort))
            {
               DWORD dwError = ::GetLastError();

               if(dwError == WSAEWOULDBLOCK)
               {
                  ASSERT(FALSE);
                  return;
               }
               ASSERT(FALSE);

               return;
            }
         }

         break;
      default:
         break;

      }
      break;
   case  _vmsnettomidi::StateListening:
      switch(eevent)
      {
      case  _vmsnettomidi::EventAcceptSuccess:
         m_estate = _vmsnettomidi::StateActive;
         InitMidi();
         ASSERT(m_psocketXXX == NULL);
         m_psocketXXX = new NetToMidiAsyncSocket;
         m_psocketXXX->m_pserver = this;

         m_psocketServer->Accept(*m_psocketXXX);
         break;
         break;
      default:
         break;

      }
      break;
   case  _vmsnettomidi::StateCalling:
      switch(eevent)
      {
      case  _vmsnettomidi::EventConnectionSuccess:
         m_estate = _vmsnettomidi::StateActive;
         InitMidi();
/*         ASSERT(m_psocketXXX == NULL);
         m_psocketXXX = new NetToMidiAsyncSocket;
         m_psocketXXX->m_pserver = this;

         m_psocketServer->Accept(*m_psocketXXX);*/
         break;
      default:
         break;

      }
      break;
   }

}

void NetToMidiPoint::SetServerPort(UINT uiServerPort)
{
   m_uiServerPort = uiServerPort;
}

bool NetToMidiPoint::InitMidi()
{
   if(m_bMidiInit)
      return true;
   m_i = 0;
   m_dwStartPosition = GetTickCount();;
   m_dwStreamPosition = 0;
   //UINT result = midiOutOpen(&m_hmidiout, 0, MidiOutProc, this, CALLBACK_FUNCTION);
   m_uiDev = MIDI_MAPPER;
//   UINT result = midiStreamOpen(&m_hmidiout, &m_uiDev, 1, MidiOutProc, this, CALLBACK_FUNCTION);
   UINT result = midiStreamOpen(&m_hmidiout, &m_uiDev, 1, NULL, (LPARAM) this, CALLBACK_NULL);

   if(result != MMSYSERR_NOERROR)
   {
      m_bMidiInit = false;
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
      m_bMidiInit = true;
      return true;
   }
   else
   {
      return false;
   }

}

void NetToMidiPoint::StopMidi()
{
   if(!m_bMidiInit)
      return;

   midiStreamClose(m_hmidiout);
   m_bMidiInit = false;
}


void CALLBACK NetToMidiPoint::MidiOutProc(
  HMIDIOUT hmo,      
  UINT wMsg,         
  DWORD dwInstance,  
  DWORD dwParam1,    
  DWORD dwParam2     
)
{
}

void NetToMidiPoint::OnMessage(LPBYTE lpbuf, int nRead)
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

UINT AFX_CDECL NetToMidiPoint::MidiOutThreadProc(
  LPVOID lpParameter   // thread data
)
{
   NetToMidiPoint * pserver = (NetToMidiPoint *) lpParameter;

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

void NetToMidiPoint::MidiOut(MIDITONETMESSAGE &msg)
{
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

   m_dwStreamPosition += msg.uiDelta;


}
