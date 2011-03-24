#pragma once

namespace audio_decode
{
   class decoder;
};


namespace iaudio
{
   class WaveStreamEffect;
};


   class audWaveEffectDevocalizer;

class CLASS_DECL_ca audWavePreBuffer :
   virtual public pha(audio_decode::decoder)
{
public:

   class Thread : public simple_thread
   {
   public:
      enum e_state
      {
         state_initial,
         StateStarting,
         StateRunning,
         StateStopping,
      };

      Thread(::ca::application * papp);
      ~Thread();
      void SetPreBuffer(audWavePreBuffer * pprebuffer);
      void Start();
      void Stop();
      void Step();
      e_state GetState();
   protected:
      e_state            m_estate;
      CEvent            m_evStep;
      audWavePreBuffer *   m_pprebuffer;    

      virtual int run();
   } m_thread;
   friend class Thread;



   class Chunk
   {
   public:
      void Reset();
      Chunk();
      short *     m_psh;
      int         m_iId;
   };

   class ChunkArray :
      public base_array < Chunk, Chunk & >
   {
   public:
      Chunk * GetChunkById(int iId);
      void Reset();
   };


   short *                       m_pshL1;
   short *                       m_pshL2;
   audWavePreBufferCallback *    m_pcallback;
   int                           m_iChannelCount;
   int                           m_iChunkCount;
   int                           m_iChunkSampleCount;
   ph(audio_decode::decoder)     m_pdecoder;

   audWaveEffectDevocalizer *    m_pdevocalizer;
   ChunkArray                    m_chunkaL1;
   ChunkArray                    m_chunkaL2;

   int                           m_iOutCount;
   int                           m_iMinFreeBuffer;

   critical_section              m_cs;
   bool                          m_bPlay;

   iaudio::WaveStreamEffect *    m_pstreameffectOut;

   imedia::position              m_position;

   void on_delete(::ca::ca * pdecoder);

   audWavePreBuffer(::ca::application * papp);
   virtual ~audWavePreBuffer();


   int _IdToChunk(int iId);
   bool _PreOutputId(Chunk * pchunk);
   bool _FreeId(int iId);
   bool _DeferKick();
   void _Kick();
   bool _UpdateBuffer(int iChannelCount, int iGroupCount, int iGroupSampleCount, int iMinL1BufferCount);
   void ClearBuffer();
   void Reset();
   bool IsEOF();
   void Devocalize(bool bSet);
   bool IsDevocalized();
   //void Kick();
   
   bool IdFree(int iChunkId);
   int GetChunkByteCount();
   short * GetInBuffer(int iChunk);
   int GetTotalChunkCount();
   short * GetOutBufferId(int iId);
   void SetDecoder(audio_decode::decoder * pinterface);
   bool open(audWavePreBufferCallback * pcallback, int iChannelCount, int iGroupCount, int iGroupSampleCount);
   bool SetMinL1BufferCount(int iCount);

   __int64 GetMillisLength();

   void Start(const imedia::position & position);
   void Stop(void);
};

inline audWavePreBuffer::Thread::e_state audWavePreBuffer::Thread::GetState()
{
   return m_estate;
}
