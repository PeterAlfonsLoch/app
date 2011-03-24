#pragma once

#include "id3lib/reader.h"

namespace audio_decode_libmpg123
{

   class ID3_Reader :
      public ::ID3_Reader
   {
   public:
	   ID3_Reader();
	   virtual ~ID3_Reader();


      ex1::file *      m_pfile;

      virtual void close();
      virtual pos_type getCur();
      virtual pos_type setCur(pos_type pos);
      virtual bool peek(char * pch);
      virtual size_type readChars(char buf[], size_type len);
      virtual pos_type getEnd();


   };

} // namespace audio_decode_libmpg123
