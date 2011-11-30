#pragma once


#include "app-core/appseed/multimedia/iaudio/WaveStreamEffect.h"


class audWaveEffectDevocalizer  :
   virtual public iaudio::WaveStreamEffect 
{
public:


   class Chunk
   {
   public:


      audWaveEffectDevocalizer *       m_pparent;
      raw_array < short >              m_sha;


      void Initialize(audWaveEffectDevocalizer * pparent);
      bool Input(short * pshStream);
   };

   class Group :
      virtual public ::radix::object
   {
   public:


      class Channel :
         virtual public ::radix::object
      {
      public:


         Group *                          m_pgroup;

         double_array                     m_da1;
         double_array                     m_da2;
         double_array                     m_da3;
         raw_array < kiss_fft_cpx >       m_cpxa;
         sort_array < double, double >    m_faMax;
         int_array                        m_iaMax;


         Channel(::ca::application * papp);

         void Initialize(Group * pgroup);
         void Input(bool bFilter);
         void Output(sort_array < double, double > & faMax, int_array & iaMax);

      };

      audWaveEffectDevocalizer *                m_pparent;
      array_app_alloc < Channel, Channel & >    m_channela;
      raw_array < kiss_fft_cpx >                m_cpxa;
      double_array                              m_daMod;
      double                                    m_dDivisor;

      Group(::ca::application * papp);
      void Initialize(audWaveEffectDevocalizer * pparent);
      bool Input(short * pshStream);
      bool Output1(short * pshStream);
      bool Output2(short * pshStream);
      

   };

   sp(kissfft::fftd)                m_spfftd;
   sp(kissfft::ifftd)               m_spifftd;

   sort_array < sort_array < double, double >, sort_array < double, double > & > m_f2aMax;
   int2a                                  m_i2aMax;

   // Tuning Parameters
   int                                    m_iCancelNoteCount;
   int                                    m_iMin;
   int                                    m_iMax;
   double                                 m_wDiv;

   bool                                   m_bEnable;

   int                                    m_iDivisionCount;
   int                                    m_iFirstOutput;
   int                                    m_iOutputCount;
   int                                    m_iOutDivision;
   int                                    m_iOutChunk;
   

   int                                    m_iSamplesPerSecond;
   int                                    m_iSampleCount;
   int                                    m_iChannelCount;
   int                                    m_iGroupCount;
   
   int                                    m_iInputDivisionCount;
   int                                    m_iFirstInputDivision;
   int                                    m_iFirstChunk;
   int                                    m_iChunkCount;
   int                                    m_iFirstInputGroup;
   int                                    m_iInputGroupCount;
   int                                    m_iOutputGroup;

   int                                    m_iDivisionSampleCount;

   array_app_alloc < Group, Group & >     m_groupa;
   base_array < Chunk, Chunk & >          m_chunka;
   base_array < Chunk, Chunk & >          m_chunkaOut;
   Chunk                                  m_chunk;

   audWaveEffectDevocalizer(::ca::application * papp, bool bEnable, int iSampleCount, int iSamplesPerSecond, int iDivisionCount, int iGroupCount);
   virtual ~audWaveEffectDevocalizer();


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
