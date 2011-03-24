// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "StdAfx.h"


namespace ex1
{

   DWORD_PTR limited_input_stream::read(void *data, DWORD_PTR size)
   {
      if (_virtPos >= _size)
      {
         if(_virtPos == _size)
            return 0;
         else
            throw system_exception(get_app(), E_FAIL);
      }
      uint64 rem = _size - _virtPos;
      if (rem < size)
         size = (uint32)rem;
      uint64 newPos = _startOffset + _virtPos;
      if (newPos != _physPos)
      {
         _physPos = newPos;
         RINOK(SeekToPhys());
      }
      size = _stream->read(data, size);
      _physPos += size;
      _virtPos += size;
      return size;
   }

   DWORD_PTR limited_input_stream::seek(INT_PTR offset, e_seek seekOrigin)
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



   HRESULT CreateLimitedInStream(input_stream *inStream, uint64 pos, uint64 size, reader **resStream)
   {
      *resStream = 0;
      limited_input_stream *streamSpec = new limited_input_stream;
      reader * streamTemp = streamSpec;
      streamSpec->SetStream(inStream);
      RINOK(streamSpec->InitAndSeek(pos, size));
      streamSpec->seek_to_begin();
      *resStream = streamTemp;
      return S_OK;
   }

} // namespace ex1