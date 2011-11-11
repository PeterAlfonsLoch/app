///////////////////////////////////////////////////////////////////////////////
//
// File Name: midi_player.h
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

class midi_player_callback;
class midi_player_interface;
class midi_sequence_thread;



class midi_player;


#include "midi_player_command.h"



class CLASS_DECL_ca midi_player :
   public ::radix::thread,
   public midi_central_listener
{
public:

   enum e_message 
   {
      MessageNotifyEvent = WM_APP + 40,
   };

   event              m_eventPlaybackEnd;
   event              m_evInitialized;
   
   midi_sequence_thread *    m_psequencethread;
   ::user::interaction *                   m_puie;
   midi_player_interface *   m_pinterface;
   double                  m_dNextPositionRate;


   midi_player(::ca::application * papp);
   virtual ~midi_player();

   using ::midi_central_listener::OnAttributeChange;

   void install_message_handling(::user::win::message::dispatch * pinterface);



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
   virtual void OnAttributeChange(mus::e_midi_central_attribute eattribute);
   UINT GetMidiOutDevice();
   void PostNotifyEvent(::mus::midi::player::ENotifyEvent eevent);
   
   imedia::position RateToTicks(double dRate);
   
   bool SetTempoShift(int iTempoShift);
   
   bool SetMidiOutDevice(UINT uiDevice);

   VMSRESULT SetInterface(midi_player_interface * pinterface);
   
   VMSRESULT Initialize(::radix::thread * pthread);
   
   bool IsPlaying();
   
   void PostGMReset();
   void PostTempoChange();
   void SendTempoChange(); // verificar


   DECL_GEN_SIGNAL(OnNotifyEvent)
   DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessageDone)
   DECL_GEN_SIGNAL(OnMultimediaMidiOutputMessagePositionCB)

};
