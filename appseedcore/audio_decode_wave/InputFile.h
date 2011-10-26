#pragma once

namespace audio_decode_wave
{


class InputFile
{
public:
   InputFile(void);

   ex1::filesp    m_pfile;

   void Construct();

	// Opens a wav file for reading. fails if not exists. throws tchar * exception
	void open(ex1::file * pfile);

   bool CheckRead(file_position & iPos, LPVOID lpdata, ::primitive::memory_size iSize);

public:
   // once the wav has been opened for read, subclasses can directly access the individual chunks.
   file_position           m_iStartOfData;	// actual Wave Data
   file_position           m_iRiffHeader;    // start of Riff Chunk
   file_position           m_iFmtHeader;     // start of Fmt Chunk
   file_size               m_iFmtHeaderExSize;   
   file_position           m_iDataBlock;     // start of Data Block
public:
   RIFF_HEADER             m_riffheader;		// Riff chunk
   FMT_BLOCK               m_fmtheader;		// Fmt chunk
   DATA_BLOCK              m_datablock;		// Data header chunk

public:
   ~InputFile(void);
};

} // namespace audio_decode_wave