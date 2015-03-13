// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "framework.h"


namespace file
{

   ::primitive::memory_size limited_istream::read(void *data, ::primitive::memory_size size)
   {
      if (_virtPos >= _size)
      {
         if(_virtPos == _size)
            return 0;
         else
            throw system_exception(get_app(), E_FAIL);
      }
      uint64_t rem = _size - _virtPos;
      if (rem < size)
         size = (uint32_t)rem;
      uint64_t newPos = _startOffset + _virtPos;
      if (newPos != _physPos)
      {
         _physPos = newPos;
         //RINOK(SeekToPhys());
         SeekToPhys();
      }
      size = _stream->read(data, size);
      _physPos += size;
      _virtPos += size;
      return size;
   }

   file_position limited_istream::seek(file_offset offset, e_seek seekOrigin)
   {
      switch(seekOrigin)
      {
      case seek_begin: _virtPos = offset; break;
      case seek_current: _virtPos += offset; break;
      case seek_end: _virtPos = _size + offset; break;
      default: 
         throw system_exception(get_app(), STG_E_INVALIDFUNCTION);
      }
      return _virtPos;
   }



   reader * create_limited_istream(istream *inStream, uint64_t pos, uint64_t size)
   {
      limited_istream *streamSpec = new limited_istream;
      streamSpec->SetStream(inStream);
      streamSpec->InitAndSeek(pos, size);
      streamSpec->seek_to_begin();
      return streamSpec;
   }

} // namespace file
