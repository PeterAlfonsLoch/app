// LimitedStreams.cpp
// from 7-zip on 2012-12-23, lunch time
#include "StdAfx.h"


namespace ex1
{


   DWORD_PTR clustered_input_stream::read(void *data, DWORD_PTR size)
   {
      DWORD_PTR processedSize = 0;
      if (_virtPos >= Size)
      {
         if(_virtPos == Size) 
            return 0;
         else
            throw system_exception(get_app(), E_FAIL);
      }

      if (_curRem == 0)
      {
         uint32 blockSize = (uint32)1 << BlockSizeLog;
         uint32 virtBlock = (uint32)(_virtPos >> BlockSizeLog);
         uint32 offsetInBlock = (uint32)_virtPos & (blockSize - 1);
         uint32 phyBlock = Vector[virtBlock];
         uint64 newPos = StartOffset + ((uint64)phyBlock << BlockSizeLog) + offsetInBlock;
         if (newPos != _physPos)
         {
            _physPos = newPos;
            RINOK(SeekToPhys());
         }
         _curRem = blockSize - offsetInBlock;
         for (int i = 1; i < 64 && (virtBlock + i) < (uint32)Vector.get_size() && phyBlock + i == Vector[virtBlock + i]; i++)
            _curRem += (uint32)1 << BlockSizeLog;
         uint64 rem = Size - _virtPos;
         if (_curRem > rem)
            _curRem = (uint32)rem;
      }
      if (size > _curRem)
         size = _curRem;
      size = Stream->read(data, size);
      processedSize = size;
      _physPos += size;
      _virtPos += size;
      _curRem -= size;
      return processedSize;
   }

   DWORD_PTR clustered_input_stream::seek(INT_PTR offset, e_seek seekOrigin)
   {
      uint64 newVirtPos = offset;
      switch(seekOrigin)
      {
      case STREAM_SEEK_SET: break;
      case STREAM_SEEK_CUR: newVirtPos += _virtPos; break;
      case STREAM_SEEK_END: newVirtPos += Size; break;
      default: 
         throw system_exception(get_app(), STG_E_INVALIDFUNCTION);
      }
      if (_virtPos != newVirtPos)
         _curRem = 0;
      _virtPos = newVirtPos;
      return newVirtPos;
   }

} // namespace ex1

