#pragma once

namespace audio_decode_wave
{


class InputFile
{
public:
   InputFile(void);

   ex1::file * m_pfile;

   void Construct();

	// Opens a wav file for reading. fails if not exists. throws tchar * exception
	void open(ex1::file * pfile);

   bool CheckRead(int & iPos, LPVOID lpdata, int iSize);

public:
   // once the wav has been opened for read, subclasses can directly access the individual chunks.
   int            m_iStartOfData;	// actual Wave Data
   int            m_iRiffHeader;    // start of Riff Chunk
   int            m_iFmtHeader;     // start of Fmt Chunk
   int            m_iFmtHeaderExSize;   
   int            m_iDataBlock;     // start of Data Block
public:
   RIFF_HEADER    m_riffheader;		// Riff chunk
   FMT_BLOCK      m_fmtheader;		// Fmt chunk
   DATA_BLOCK     m_datablock;		// Data header chunk

public:
   ~InputFile(void);
};

} // namespace audio_decode_wave