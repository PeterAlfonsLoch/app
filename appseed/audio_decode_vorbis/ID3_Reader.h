#pragma once

#include "id3lib/reader.h"

namespace audio_decode_vorbis
{

   class ID3_Reader :
      public ::ID3_Reader
   {
   public:
	   ID3_Reader();
	   virtual ~ID3_Reader();


      ex1::file *      m_pfile;

      virtual void close();
      virtual file_position getCur();
      virtual file_position setCur(file_position pos);
      virtual bool peek(char * pch);
      virtual ::primitive::memory_size readChars(char buf[], ::primitive::memory_size len);
      virtual file_position getEnd();


   };

} // namespace audio_decode_vorbis
