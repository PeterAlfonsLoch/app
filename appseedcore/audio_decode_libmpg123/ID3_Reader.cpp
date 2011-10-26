#include "StdAfx.h"
#include "ID3_Reader.h"

namespace audio_decode_libmpg123
{

   ID3_Reader::ID3_Reader()
   {
      m_pfile = NULL;

   }

   ID3_Reader::~ID3_Reader()
   {

   }

   file_position ID3_Reader::getEnd()
   {
      return (file_position) m_pfile->get_length();
   }

   void ID3_Reader::close()
   {
      m_pfile->close();
   }

   file_position ID3_Reader::getCur()
   {
      return m_pfile->get_position();
   }


   file_position ID3_Reader::setCur(file_position pos)
   {
      return m_pfile->seek((file_offset) pos, ::ex1::seek_begin);
   }

   bool ID3_Reader::peek(char * pch)
   {
      return m_pfile->peek(pch);
   }

   ::primitive::memory_size ID3_Reader::readChars(char buf[], ::primitive::memory_size len)
   {
      return m_pfile->read(buf, len);
   }


} // namespace audio_decode_libmpg123

