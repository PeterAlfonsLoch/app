// InStreamWithCRC.cpp

#include "StdAfx.h"

#include "InStreamWithCRC.h"

STDMETHODIMP reader_with_crc::Read(void *data, uint32 size, uint32 *processedSize)
{
  uint32 realProcessedSize;
  HRESULT result = _stream->Read(data, size, &realProcessedSize);
  _size += realProcessedSize;
  if (size > 0 && realProcessedSize == 0)
    _wasFinished = true;
  _crc = CrcUpdate(_crc, data, realProcessedSize);
  if(processedSize != NULL)
    *processedSize = realProcessedSize;
  return result;
}

STDMETHODIMP ::compress::input_stream_with_crc::Read(void *data, uint32 size, uint32 *processedSize)
{
  uint32 realProcessedSize;
  HRESULT result = _stream->Read(data, size, &realProcessedSize);
  /*
  if (size > 0 && realProcessedSize == 0)
    _wasFinished = true;
  */
  _size += realProcessedSize;
  _crc = CrcUpdate(_crc, data, realProcessedSize);
  if(processedSize != NULL)
    *processedSize = realProcessedSize;
  return result;
}

STDMETHODIMP ::compress::input_stream_with_crc::Seek(Int64 offset, uint32 seekOrigin, uint64 *newPosition)
{
  if (seekOrigin != STREAM_SEEK_SET || offset != 0)
    return E_FAIL;
  _size = 0;
  _crc = CRC_INIT_VAL;
  return _stream->Seek(offset, seekOrigin, newPosition);
}
