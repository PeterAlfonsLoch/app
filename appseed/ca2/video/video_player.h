#pragma once


namespace mediaplay
{
   class document;
}

namespace video
{

   class document;

   class CLASS_DECL_ca player :
      virtual public ::radix::thread,
      virtual public ::audio::WavePlayerInterface
   {
   public:

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


      class CLASS_DECL_ca decode_thread :
         virtual public simple_thread
      {
      public:
         decode_thread(::ca::application * papp);
         player * m_pplayer;
         virtual int run();
      };


      class CLASS_DECL_ca play_thread :
         virtual public simple_thread
      {
      public:
         play_thread(::ca::application * papp);
         player * m_pplayer;
         virtual int run();
      };


      ::collection::list < player_command, player_command & > m_commandlistStopOpen;
      ::collection::list < player_command, player_command & > m_commandlistOpenPlay;

      video_decode::decoder_plugin_set_ex1         m_decodersetex1;
      video_decode::decoder_plugin_set             m_decoderset;
      ::user::interaction *                        m_hwndCallback;
      ::video_decode::decoder *                    m_pdecoder;
      ::audio_decode::decoder *                    m_paudiodecoder;
      mediaplay::document *                        m_pmediaplaydocument;
   
      EDeviceState                                 m_edevicestate;
      EDecoderState                                m_edecoderstate;
      e_state                                      m_estate;
      event                                        m_eventStopped;
      bool                                         m_bPlay;
      
      mutex                                        m_mutexBuffer;
      array_app_alloc < ::ca::dib, ::ca::dib >     m_diba;
      base_array < uint64_t, uint64_t >            m_ptsa;
      int_array                                    m_iaFrame;
      bool_array                                   m_scaleda;
      

      int                                          m_iPlayDib;
      int                                          m_iLastDib;

      size                                         m_sizeVideo;
      size                                         m_sizeView;
      point                                        m_ptView;
      rect                                         m_rectClient;

      


      



      int m_iOutBufferSampleCount;

      play_thread m_play;
      decode_thread m_decode;

      player(::ca::application * papp);
      virtual ~player();

      void ExecuteCommand(player_command & command);

      
      virtual void install_message_handling(::user::win::message::dispatch * pinterface);


      virtual void _001OnDraw(::ca::graphics * pdc);

      
      bool step();
      bool decode();


      virtual uint64_t get_pts();
      

      DECL_GEN_SIGNAL(_001OnSize)
      DECL_GEN_SIGNAL(_001OnCreate)
      DECL_GEN_SIGNAL(_001OnTimer)


   #ifdef _DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

   



      bool DecoderOpen(player_command & command);
      bool DecoderIsActive();
      void DecoderInitialize(ex1::file * pfile);
      void DecoderClose();
      void DecoderRun();


      bool CommandMessageProcedure(player_command & command);
      void FillTitleInfo(stringa & wstraFormat, string2a & wstr2aTitle);
      void FadeOutAndStop();
      void Devocalize(bool bSet);
      bool IsDevocalized();
      void SetState(e_state estate);
      bool ExecuteIsPaused();
      void SetCallback(::user::interaction *  hwnd);
      bool GetStopEnable();
      bool GetPlayEnable();
      static player * BeginThread(::ca::application * papp);
      bool IsPlaying();
      EDeviceState GetDeviceState();
      EDecoderState GetDecoderState();
      void SetDeviceState(EDeviceState estate);
      void SetDecoderState(EDecoderState estate);
      void OnEvent(e_event event);
      bool DeviceIsOpened();
      bool DecoderIsOpened();
      void AttachEndEvent(event * pevent);


      virtual bool initialize_instance();
      virtual int exit_instance();

      void _Stop();
      void ExecuteStop();
      DECL_GEN_SIGNAL(OnCommandMessage)


      virtual int get_free_frame();

      virtual void layout();

   };


} // namespace verisimplevideo
