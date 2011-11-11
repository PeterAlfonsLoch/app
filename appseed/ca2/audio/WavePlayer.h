#pragma once


class stringa;

#define MessageKickBufferOut WM_APP + 120


namespace audio_decode
{
   class decoder;
};


class audWaveOut;
class audWavePreBuffer;


class CLASS_DECL_ca audWavePlayer :
   public ::radix::thread
{
public:

   friend class audWaveOut;

   enum EDeviceState
   {
      DeviceStateInitial,
      DeviceStateOpened,
      DeviceStatePlaying,
      DeviceStateStopping,
      DeviceStatePaused,
   };

   enum EDecoderState
   {
      DecoderStateInitial,
      DecoderStateOpened,
   };

   enum e_state
   {
      state_initial,
      StatePlaying,
      StatePaused,
      StateFadingOutToStop,
   };
   
   enum e_event
   {
      EventOpenDecoder,
      EventOpenDevice,
      EventPlay,
      EventStop,
      EventExecutePause,
      EventExecuteRestart,
      EventEOF,
      EventPlaybackEnd,
      EventStopped,
      EventCloseDevice,
      EventCloseDecoder,
      EventFadeOutAndStop,
   };

   ::collection::list < audWavePlayerCommand, audWavePlayerCommand & > m_commandlistStopOpen;
   ::collection::list < audWavePlayerCommand, audWavePlayerCommand & > m_commandlistOpenPlay;

   audio_decode::decoder_plugin_set_ex1      m_decodersetex1;
   audio_decode::decoder_plugin_set          m_decoderset;
   ph(::user::interaction)                   m_hwndCallback;
   sp(audio_decode::decoder)                 m_pdecoder;
   audWaveOut *                              m_pwaveout;
   
   EDeviceState                              m_edevicestate;
   EDecoderState                             m_edecoderstate;
   e_state                                   m_estate;
   int                                       m_iOutBufferSampleCount;
   int                                       m_iBufferId;


   audWavePlayer(::ca::application * papp);
   virtual ~audWavePlayer();
   
   
   bool DecoderOpen(audWavePlayerCommand & command);

   bool DecoderIsActive();
   void DecoderInitialize(ex1::file * pfile);
   void DecoderClose();
   void DecoderRun();

   void install_message_handling(::user::win::message::dispatch * pinterface);

   bool audCommandMessageProcedure(audWavePlayerCommand & command);
   void FillTitleInfo(stringa & wstraFormat, string2a & wstr2aTitle);
   void FadeOutAndStop();
   void Devocalize(bool bSet);
   bool IsDevocalized();
   void SetState(e_state estate);
   bool ExecuteIsPaused();
   void SetCallback(::user::interaction *  hwnd);
   bool GetStopEnable();
   bool GetPlayEnable();
   audWaveOut * GetWaveOut();
   static audWavePlayer * BeginThread(::ca::application * papp);
   bool IsPlaying();
   EDeviceState GetDeviceState();
   EDecoderState GetDecoderState();
   void SetDeviceState(EDeviceState estate);
   void SetDecoderState(EDecoderState estate);
   void OnEvent(e_event event);
   bool DeviceIsOpened();
   bool DecoderIsOpened();
   void AttachEndEvent(event * pevent);

   void ExecuteCommand(audWavePlayerCommand & command);

   

   virtual bool initialize_instance();
   virtual int exit_instance();

   void _Stop();
   void ExecuteStop();
   DECL_GEN_SIGNAL(OnaudCommandMessage)
   
};

