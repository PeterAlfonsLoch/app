#pragma once

namespace audio_decode_wave
{

   class CLASS_DECL_NOTSAD_WAV OutputFile
   {
   public:
      OutputFile(void);
      ~OutputFile(void);

      
   	void open(ex1::file * pfile);
      void close();
   	void write(LPVOID lpvoidBuffer, UINT uiBufferSize);

   public:
      RIFF_HEADER    m_riffheader;		// Riff chunk
      FMT_BLOCK      m_fmtheader;		// Fmt chunk
      DATA_BLOCK     m_datablock;		// Data header chunk

   protected:
      int               m_iStartOfData;	// actual Wave Data
      int               m_iDataBlock;     // start of Data Block
      critical_section  m_csFile;
      ex1::file *       m_pfile;


   };


} // namespace audio_decode_wave