#include "StdAfx.h"
#include "encoder.h"

#define WAVE_FORMAT_PCM     1

void * __cdecl NewEncoderInterface(::ca::application * papp)
{
   return new audio_decode_lame::encoder(papp);
}

void __cdecl DeleteEncoderInterface(void * pdecoder)
{
   delete (audio_decode_lame::encoder *) pdecoder;
}


namespace audio_decode_lame
{

   encoder::encoder(::ca::application * papp) :
      ca(papp),
      ::audio_decode::encoder(papp)
   {
      gf = lame_init();
      //lame_set_errorf(gf, &frontend_errorf);
       //lame_set_debugf(gf, &frontend_debugf);
       //lame_set_msgf(gf, &frontend_msgf);
      m_memory.allocate(1024 * 1024);
   }

   encoder::~encoder(void)
   {
   }

   void encoder::EncoderSetSamplesPerSec(UINT user)
   {
      lame_set_in_samplerate(gf, user);
   }

   void encoder::EncoderSetChannelCount(UINT user)
   {
      lame_set_num_channels(gf, user);
   }

   void encoder::EncoderSetBitsPerSample(UINT user)
   {
      UNREFERENCED_PARAMETER(user);
      //throw not_implemented_exception();
   }

   bool encoder::EncoderSetFile(ex1::file * pfile)
   {
      m_pfile = pfile;
      return true;
   }

   bool encoder::EncoderInitialize()
   {
      if(lame_init_params(gf) == -1)
         return false;
      lame_set_VBR(gf, vbr_abr);
      lame_set_VBR_mean_bitrate_kbps(gf, 128);
      return true;
   }


   void encoder::EncoderWriteBuffer(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      int iEncode;
      while(true)
      {
         iEncode = lame_encode_buffer_interleaved(gf, 
            (short *)lpvoidBuffer,
            uiBufferSize / 4, (unsigned char *) m_memory.get_data(),
            m_memory.get_size());
         if(iEncode == -1)
         {
            m_memory.allocate_add_up(128 * 1024);
            continue;
         }
         else
         {
            break;
         }
         
      }
      if(iEncode > 0)
      {
         m_pfile->write(m_memory.get_data(), iEncode);
      }
   }

   bool encoder::EncoderFinalize()
   {
      return true;
   }

/////////////////////////////////////////////////////
} // namespace audio_decode_wave
/////////////////////////////////////////////////////
