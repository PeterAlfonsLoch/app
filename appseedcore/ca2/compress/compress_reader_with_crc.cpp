// InStreamWithCRC.cpp
// at Sector8J from 7-zip on afternoon of 14/01/2001 - Friday

#include "StdAfx.h"

/*#include "InStreamWithCRC.h"*/

namespace compress
{


DWORD_PTR reader_with_crc::read(void *data, DWORD_PTR size)
{
  DWORD_PTR realProcessedSize = _stream->read(data, size);
  _size += realProcessedSize;
  if (size > 0 && realProcessedSize == 0)
    _wasFinished = true;
  _crc = crc_update(_crc, data, realProcessedSize);
  return realProcessedSize;
}

DWORD_PTR input_stream_with_crc::read(void *data, DWORD_PTR size)
{
  DWORD_PTR realProcessedSize = _stream->read(data, size);
  /*
  if (size > 0 && realProcessedSize == 0)
    _wasFinished = true;
  */
  _size += realProcessedSize;
  _crc = crc_update(_crc, data, realProcessedSize);
  return realProcessedSize;
}

DWORD_PTR input_stream_with_crc::seek(INT_PTR offset, ex1::e_seek seekOrigin)
{
  if (seekOrigin != ::ex1::seek_begin || offset != 0)
    throw E_FAIL;
  _size = 0;
  _crc = CRC_INIT_VAL;
  return _stream->seek(offset, seekOrigin);
}

} // namespace compress