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

   ::ID3_Reader::pos_type ID3_Reader::getEnd()
   {
      return m_pfile->get_length();
   }
   void ID3_Reader::close()
   {
      m_pfile->close();
   }
   ::ID3_Reader::pos_type ID3_Reader::getCur()
   {
      return m_pfile->GetPosition();
   }


   ::ID3_Reader::pos_type ID3_Reader::setCur(pos_type pos)
   {
      return m_pfile->seek(pos , ::ex1::seek_begin);
   }

   bool ID3_Reader::peek(char * pch)
   {
      return m_pfile->peek(pch);
   }

   ::ID3_Reader::size_type ID3_Reader::readChars(char buf[], size_type len)
   {
      return m_pfile->read(buf, len);
   }


} // namespace audio_decode_libmpg123

