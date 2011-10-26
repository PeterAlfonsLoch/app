#pragma once



// WaveRecorder

class audWaveIn;

class CLASS_DECL_ca audWaveRecorder : 
   public ::radix::thread,
   public audWaveInListener
{
public:
   audWaveIn *                         m_pwavein;
   ex1::file *                         m_pfile;
   audio_decode::encoder *             m_pencoder;
   audio_decode::encoder_plugin_set_ex1   m_pluginset;
   event                              m_eventStopped;
   int                                 m_iOutBufferSampleCount;


   audWaveRecorder(::ca::application * papp); 
   virtual ~audWaveRecorder();


   void ExecuteStop();
   void ExecutePlay();

   bool IsRecording();

   virtual void WaveInDataProc(audWaveIn * pwavein, DWORD dwSampleTime, LPWAVEHDR lpwavehdr);

   void install_message_handling(::user::win::message::dispatch * pinterface);

public:
   virtual bool initialize_instance();
   virtual int exit_instance();

   bool audCommandMessageProcedure(audWaveRecorderCommand &command);
   void ExecuteCommand(audWaveRecorderCommand & command);
   DECL_GEN_SIGNAL(OnaudCommandMessage);


};


