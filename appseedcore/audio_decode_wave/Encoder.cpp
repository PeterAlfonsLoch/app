#include "StdAfx.h"
#include "encoder.h"

#define WAVE_FORMAT_PCM     1

void * __cdecl NewEncoderInterface(::ca::application * papp)
{
   return new audio_decode_wave::encoder(papp);
}

void __cdecl DeleteEncoderInterface(void * pdecoder)
{
   delete (audio_decode_wave::encoder *) pdecoder;
}


namespace audio_decode_wave
{

   encoder::encoder(::ca::application * papp) :
      ca(papp),
      ::audio_decode::encoder(papp)
   {
   }

   encoder::~encoder(void)
   {
   }

   void encoder::EncoderSetSamplesPerSec(UINT user)
   {
      m_outputfile.m_fmtheader.wavFormat.dwSamplesPerSec = user;
   }

   void encoder::EncoderSetChannelCount(UINT user)
   {
      m_outputfile.m_fmtheader.wavFormat.wChannels = (WORD) user;
   }

   void encoder::EncoderSetBitsPerSample(UINT user)
   {
      m_outputfile.m_fmtheader.wavFormat.wBitsPerSample = (WORD) user;
   }

   bool encoder::EncoderSetFile(ex1::file * pfile)
   {
      m_pfile = pfile;
      return true;
   }

   bool encoder::EncoderInitialize()
   {
      m_outputfile.m_fmtheader.wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	   m_outputfile.m_fmtheader.wavFormat.wBlockAlign = 
            m_outputfile.m_fmtheader.wavFormat.wBitsPerSample * 
            m_outputfile.m_fmtheader.wavFormat.wChannels / 8;
	   m_outputfile.m_fmtheader.wavFormat.dwAvgBytesPerSec =
            m_outputfile.m_fmtheader.wavFormat.dwSamplesPerSec * 
            m_outputfile.m_fmtheader.wavFormat.wBlockAlign;
      m_outputfile.open(m_pfile);
      return true;
   }


   void encoder::EncoderWriteBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      m_outputfile.write(lpvoidBuffer, uiBufferSize);
   }

   bool encoder::EncoderFinalize()
   {
      m_outputfile.close();
      return true;
   }

} // namespace audio_decode_wave
