#pragma once

namespace _vmskissfftf
{
   class Fftrd;
   class Fftri;
}

#include "iaudio/WaveStreamEffect.h"

class audWaveEffectDevocalizer  :
   public iaudio::WaveStreamEffect 
{
public:
   audWaveEffectDevocalizer(::ca::application * papp, bool bEnable, int iSampleCount, int iSamplesPerSecond, int iDivisionCount, int iGroupCount);

   virtual ~audWaveEffectDevocalizer();

   _vmskissfftf::Fftrd *  m_pfftd;
   _vmskissfftf::Fftri *  m_pffti;

   sort_array < sort_array < double, double >, sort_array < double, double > & > m_f2aMax;
   int2a          m_i2aMax;


   // Tuning Parameters
   int   m_iCancelNoteCount;
   int   m_iMin;
   int   m_iMax;
   double m_wDiv;

   bool  m_bEnable;

   class Chunk
   {
   public:
      void Initialize(audWaveEffectDevocalizer * pparent);
      bool Input(short * pshStream);
      short * m_psh;
      audWaveEffectDevocalizer *     m_pparent;
   };

   int m_iDivisionCount;
   int m_iFirstOutput;
   int m_iOutputCount;
   int m_iOutDivision;
   int m_iOutChunk;
   

   int m_iSamplesPerSecond;
   int m_iSampleCount;
   int m_iChannelCount;
   int m_iGroupCount;
   
   int m_iInputDivisionCount;
   int m_iFirstInputDivision;
   int m_iFirstChunk;
   int m_iChunkCount;
   int m_iFirstInputGroup;
   int m_iInputGroupCount;
   int m_iOutputGroup;

   int m_iDivisionSampleCount;

   class Group :
      virtual public ::radix::object
   {
   public:
      class Channel :
         virtual public ::radix::object
      {
      public:
         double *        m_pf1;
         double *        m_pf2;
         double *        m_pf3;
         kiss_fft_cpx * m_pcpx;
         Group *        m_pgroup;
         sort_array < double, double > m_faMax;
         int_array   m_iaMax;

         Channel(::ca::application * papp);

         void Initialize(Group * pgroup);
         void Input(bool bFilter);
         void Output(
            sort_array < double, double > & faMax,
            int_array & iaMax);

      };
   public:
      Group(::ca::application * papp);
      void Initialize(audWaveEffectDevocalizer * pparent);
      bool Input(short * pshStream);
      bool Output1(short * pshStream);
      bool Output2(short * pshStream);
      audWaveEffectDevocalizer *     m_pparent;
      double iDivisor;
      array_app_alloc <Channel, Channel &> m_channela;
      double *  m_pfMod;
      kiss_fft_cpx * m_pcpxR;

   };


   array_app_alloc <Group, Group &> m_groupa;
   base_array <Chunk, Chunk &> m_chunka;
   base_array <Chunk, Chunk &> m_chunkaOut;
   Chunk    m_chunk;


// virtual
public:
   int GetFrequencyIndex(double dFrequency);
   void ChunkToGroup();
   void InputChunk();
   void PrepareChunk(int iDivision);
   void Enable(bool bSet = true);
   bool IsEnabled();
   bool GroupToOutput();
   bool Output(short * pshIn);
   virtual int Process16bits(short * pshStream, int iCount);
   virtual bool Process(short * pshIn, short * pshOut);


};
