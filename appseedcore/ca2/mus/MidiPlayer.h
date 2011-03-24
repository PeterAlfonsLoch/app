///////////////////////////////////////////////////////////////////////////////
//
// File Name: MidiPlayer.h
// Long Name: Musical Interface for Digital Instruments Player
//
// Author: Camilo Sasuke Tsumanuma
//
// Creation Date: 1999-2000
//
// Purpose: Midi player is a thread object. Center high level functions of
//         a veriwell midi player.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once


typedef struct tag_midicallbackdata MIDICALLBACKDATA;

typedef struct  tagDouble
{
    double d;
} DOUBLESTRUCT, * LPDOUBLESTRUCT;

//#define MIDIPLAYERMESSAGE_PLAYBACKEND WM_USER + 30
#define MIDISEQUENCEMESSAGE_EVENT WM_USER + 30

#define MIDIPLAYERMESSAGE_COMMAND WM_USER + 50
//#define MIDIPLAYERMESSAGE_STREAMOUT WM_USER + 31
//#define   MIDIPLAYERMESSAGE_STOP WM_USER + 32


#define MIDIPLAYERMESSAGE_NOTIFYEVENT WM_APP + 40

class MidiPlayerCallback;
class MidiPlayerInterface;
class MidiSequenceThread;



class MidiPlayer;

class MidiPlayerCommand
{
   friend class MidiPlayer;
protected:
   MidiPlayerCommand();
public:
   enum eflag
   {
      flag_ticks,
      flag_dRate,
   };
   //MidiPlayerCommand(EMidiPlayerCommand ecommand, DWORD dwEllapse);

   static MidiPlayerCommand * CreateObject();

   void AddRef();
   void Release();

   DWORD GetEllapse();
   bool Lock();
   void OnFinish();
   EMidiPlayerCommand GetCommand();

public:
   EMidiPlayerCommand   m_ecommand;
   imedia::position                m_ticks;
   double               m_dRate;
   DWORD                m_dwEllapse;
   bool                 m_bReady;
   int                  m_iRefCount;
   flags < eflag >      m_flags;
protected:
   critical_section     m_csRefCount;
};


class CLASS_DECL_ca MidiPlayer :
   public ::radix::thread,
   public CMidiCentralListener
{
public:

   enum e_message 
   {
      MessageNotifyEvent = WM_APP + 40,
   };

   CEvent              m_eventPlaybackEnd;
   CEvent              m_evInitialized;
   
   MidiSequenceThread *    m_psequencethread;
   ::user::interaction *                   m_puie;
   MidiPlayerInterface *   m_pinterface;
   double                  m_dNextPositionRate;


   MidiPlayer(::ca::application * papp);
   virtual ~MidiPlayer();

#if !core_level_1
   using ::CMidiCentralListener::OnAttributeChange;
#endif

   void _001InstallMessageHandling(::user::win::message::dispatch * pinterface);



   void SendMmsgDone(::mus::midi::sequence *pSeq, ::mus::midi::LPMIDIDONEDATA lpmdd);
   void SetCallbackWindow(::user::interaction * puie);
   ::mus::midi::sequence & GetSequence();
   bool Play(double dRate = 0.0, DWORD dwEllapse = 584);
   bool Play(imedia::position tkStart, DWORD dwEllapse = 584);

   virtual bool initialize_instance();
   virtual int exit_instance();
   virtual void pre_translate_message(gen::signal_object * pobj);
   void OnMmsgDone(::mus::midi::sequence *pSeq);
   DECL_GEN_SIGNAL(OnUserMessage)
   void SaveFile(const char * lpszPathName);
   void SetPosition(double dRate);
   void Pause();
   void CloseFile();
     void SendReset();
   bool ExecuteCommand(EMidiPlayerCommand ecommand, DWORD dwEllapse);
   virtual void OnMidiOutDeviceChange();
   virtual void OnAttributeChange(mus::EMidiCentralAttribute eattribute);
   UINT GetMidiOutDevice();
   void PostNotifyEvent(::mus::midi::player::ENotifyEvent eevent);
   
   imedia::position RateToTicks(double dRate);
   
   bool SetTempoShift(int iTempoShift);
   
   bool SetMidiOutDevice(UINT uiDevice);

   VMSRESULT SetInterface(MidiPlayerInterface * pinterface);
   
   VMSRESULT Initialize(::radix::thread * pthread);
   
   bool IsPlaying();
   
   void PostGMReset();
   void PostTempoChange();
   void SendTempoChange(); // verificar


   DECL_GEN_SIGNAL(OnNotifyEvent)
   DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone)
   DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB)

};
