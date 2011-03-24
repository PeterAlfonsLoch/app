#include "StdAfx.h"

namespace audio_decode_wave
{

   OutputFile::OutputFile(void)
   {
      m_pfile = NULL;
   }

   OutputFile::~OutputFile(void)
   {
      m_pfile = NULL;
   }

   void OutputFile::open(ex1::file * pfile)
   {

      m_pfile = pfile;

      m_riffheader.chunkHeader.WriteId("RIFF");
      SzCopy(m_riffheader.szRiffFormat, "WAVE", 4);
      m_riffheader.chunkHeader.dwChunkSize = 0;

      m_pfile->write(&m_riffheader, sizeof(m_riffheader));


      m_fmtheader.chunkHeader.WriteId("fmt ");
      m_fmtheader.chunkHeader.dwChunkSize = sizeof(m_fmtheader) - sizeof(CHUNK_HEADER);

      m_pfile->write(&m_fmtheader, sizeof(m_fmtheader));

      m_iDataBlock = m_pfile->GetPosition();

      m_datablock.chunkHeader.WriteId("data");
      m_datablock.chunkHeader.dwChunkSize = 4;
      m_pfile->write(&m_datablock, sizeof(m_datablock));
      m_iStartOfData = m_pfile->GetPosition();


   }

   void OutputFile::close()
   {
      CSingleLock slFile(&m_csFile);
      slFile.Lock();

      if(m_pfile != NULL)
      {
         m_pfile->seek(0, ::ex1::seek_begin);
         m_riffheader.chunkHeader.dwChunkSize = m_pfile->get_length() - sizeof(CHUNK_HEADER);
         m_pfile->write(&m_riffheader, sizeof(m_riffheader));

         m_pfile->seek(m_iDataBlock, ::ex1::seek_begin);
         m_datablock.chunkHeader.WriteId("data");
         m_datablock.chunkHeader.dwChunkSize = m_pfile->get_length() - m_iStartOfData;
         m_pfile->write(&m_datablock, sizeof(m_datablock));
         m_pfile->close();
         m_pfile = NULL;
      }
   }

   void OutputFile::write(LPVOID lpvoidBuffer, UINT uiBufferSize)
   {
      CSingleLock slFile(&m_csFile);
      slFile.Lock();

      if(m_pfile != NULL)
      {
         m_pfile->write(lpvoidBuffer, uiBufferSize);
      }
   }


/////////////////////////////////////////////////////
} // namespace audio_decode_wave
/////////////////////////////////////////////////////
