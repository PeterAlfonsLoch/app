#include "StdAfx.h"

namespace video_decode
{

   decoder::decoder(::ca::application * papp) :
      ca(papp),
      m_memfileAudio(papp),
      m_memfileAudioBuffer(papp),
      m_transferfileAudio(papp, &m_memfileAudio)
   {
      m_transferfileAudio.m_ptimeoutfile->m_uiExpectedSize = (uint64_t) -2;
      m_iDib                     = 0;
      m_bDraw                    = false;
      m_iFrameDelayTolerance     = 2984;
      m_bEmpty                   = false;
      m_bStop                    = false;
   }

   decoder::~decoder()
   {

   }

   bool decoder::DecoderGetAttribute(EAttribute eattribute, string & str)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(eattribute);
      return false;
   }

   __int64 decoder::DecoderGetMillisLength()
   {
      UINT uiRate = DecoderGetSamplesPerSecond();
      if(uiRate != 0)
         return DecoderGetSampleCount() * 1000 / uiRate;
      else
         return 0;
   }

   bool decoder::DecoderSetSeekable(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return true;
   }

   int decoder::DecoderSetReadBlockSize(int iSize)
   {
      UNREFERENCED_PARAMETER(iSize);
      return -1;
   }

   void decoder::DecoderSeekEnd()
   {
   }

   bool decoder::DecoderSetNonStopOnEofMode(bool bSet)
   {
      UNREFERENCED_PARAMETER(bSet);
      return false;
   }

   bool decoder::step()
   {
      // wait until get full or return false immediatelly on end
      if(!decode())
         return false;
      return true;
   }

   bool decoder::decode()
   {
      if(!DecoderNextFrame())
         return false;
      return true;
   }
   
   ::ca::dib * decoder::decoder_get_frame(int iFrame)
   {
      UNREFERENCED_PARAMETER(iFrame);
      return NULL;
   }

} // namespace auddev


