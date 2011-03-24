// LockedStream.cpp
// at sector8J on afternoon of 13/01/2011 - Thursday
#include "StdAfx.h"

namespace ex1
{

   DWORD_PTR locked_in_stream::read(uint64 startPos, void *data, DWORD_PTR size)
   {
      CSingleLock sl(&_criticalSection, TRUE);
      _stream->seek(startPos, ::ex1::seek_begin);
      return _stream->read(data, size);
   }

   DWORD_PTR locked_reader::read(void *data, DWORD_PTR size)
   {
      uint32 realProcessedSize = _lockedInStream->read(_pos, data, size);
      _pos += realProcessedSize;
      return realProcessedSize;
   }

} // // at sector8J on afternoon of 13/01/2011 - Thursday
