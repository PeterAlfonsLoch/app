#include "stdafx.h"



namespace i2com
{


	namespace rtp
	{

      compressor::compressor(::ca::application * papp) :
         ca(papp)
      {
      }

	   void compressor::start_compressing(room * proom)
	   {
		   m_proom = proom;
		   AfxBeginThread(get_app(), &thread_proc_compress, (LPVOID) this);
	   }

	   UINT compressor::thread_proc_compress(LPVOID lpparam)
		{
         compressor * pcompressor = (compressor *) lpparam;
         pcompressor->compress();
         return 0;
		}

	   void compressor::compress()
		{

         gen::memory_file * pfile = &m_proom->m_memfileRaw;

         audio_decode::encoder_plugin_set encoderset(get_app());

         audio_decode::encoder_plugin * pencoderplugin = encoderset.LoadPlugin(0, "audio_decode_libmpg123.dll");

         audio_decode::encoder * pencoder = pencoderplugin->NewEncoder();

         pencoder->EncoderInitialize();

         gen::memory_file * pmemfileMp3 = &m_proom->m_memfileCompressed;

         pencoder->EncoderSetFile(pmemfileMp3);

         //m_pencoder->EncoderSetBitsPerSample(pdecoder->DecoderGetBitsPerSample());
         //m_pencoder->EncoderSetChannelCount(pdecoder->DecoderGetChannelCount());
         //m_pencoder->EncoderSetSamplesPerSec(pdecoder->DecoderGetSamplesPerSecond());
         pencoder->EncoderSetBitsPerSample(16);
         pencoder->EncoderSetChannelCount(2);
         pencoder->EncoderSetSamplesPerSec(44100);



         int iSize = 1024 * 2 * 2 * 4;

         char * bufferWav = (char *) malloc(iSize);
         char * bufferMp3 = (char *) malloc(iSize * 128);

         UINT uiRead;

		   while((uiRead = pfile->read(bufferWav, iSize)) > 0)
         {
            pencoder->EncoderWriteBuffer(bufferWav, iSize);
            if(pmemfileMp3->get_size() > 1024)
            {
               pmemfileMp3->seek_to_begin();
               while((uiRead = pmemfileMp3->read(bufferMp3,1024)) == 1024)
               {
                  for(int i = 0; m_proom->m_transmittera.get_count(); i++)
                  {
                     m_proom->m_transmittera[i].write(bufferMp3, 1024);
                  }
                  file_position dwLen = pmemfileMp3->get_position();
                  pmemfileMp3->remove_begin(NULL, (::primitive::memory_size) dwLen);
                  if(pmemfileMp3->get_size() < 1024)
                     break;
               }
               pmemfileMp3->seek_to_end();
            }
         }

		}


	} // 	namespace rtp


} // namespace i2com

