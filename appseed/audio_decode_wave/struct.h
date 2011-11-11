#pragma once

namespace audio_decode_wave
{

void SzCopy(char * lpsz, const char * lpcsz, int iCount);

struct CHUNK_HEADER
{
	CHAR	         szChunkId[4];
	DWORD	         dwChunkSize;
   void WriteId(const char * lpcsz);

   void GetChunkId(char sz[5]);
};

inline void CHUNK_HEADER::GetChunkId(char sz5[5])
{
   sz5[0] = szChunkId[0];
   sz5[1] = szChunkId[1];
   sz5[2] = szChunkId[2];
   sz5[3] = szChunkId[3];
   sz5[4] = '\0';
}

struct WAVE_FORMAT
{
	WORD	         wFormatTag;
	WORD	         wChannels;
	DWORD	         dwSamplesPerSec;
	DWORD	         dwAvgBytesPerSec;
	WORD	         wBlockAlign;
	WORD	         wBitsPerSample;
};

struct RIFF_HEADER
{
   CHUNK_HEADER  chunkHeader; // 'R','I','F','F'
	TCHAR	         szRiffFormat[4];	// 'W','A','V','E'
};

struct FMT_BLOCK
{
	CHUNK_HEADER  chunkHeader;	// 'f','m','t',' '
	WAVE_FORMAT	   wavFormat;
};

struct DATA_BLOCK
{
	CHUNK_HEADER  chunkHeader;	// 'd','a','t','a'
};

inline bool SzEqual(const char * lpcsz1, const char * lpcsz2, int iCount)
{
   int i = 0;
   while(i < iCount)
   {
      if(lpcsz1[i] != lpcsz2[i])
         return false;
      i++;
   }
   return true;
}


inline void SzCopy(char * lpsz, const char * lpcsz, int iCount)
{
   int i = 0;
   while(i < iCount)
   {
      lpsz[i] = lpcsz[i];
      i++;
   }
}

inline void CHUNK_HEADER::WriteId(const char * lpcsz)
{
   SzCopy(szChunkId, lpcsz, 4);
}


} // namespace audio_decode_wave