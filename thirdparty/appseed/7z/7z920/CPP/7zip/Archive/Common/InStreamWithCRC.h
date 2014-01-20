// InStreamWithCRC.h

#ifndef __IN_STREAM_WITH_CRC_H
#define __IN_STREAM_WITH_CRC_H

#include "../../../../C/7zCrc.h"

#include "../../../Common/MyCom.h"

#include "../../IStream.h"

class reader_with_crc:
  public ::ex1::reader,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP

  STDMETHOD(Read)(void *data, uint32 size, uint32 *processedSize);
private:
  CMyComPtr<::ex1::reader> _stream;
  uint64 _size;
  uint32 _crc;
  bool _wasFinished;
public:
  void SetStream(::ex1::reader *stream) { _stream = stream;  }
  void Init()
  {
    _size = 0;
    _wasFinished = false;
    _crc = CRC_INIT_VAL;
  }
  void ReleaseStream() { _stream.Release(); }
  uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
  uint64 GetSize() const { return _size; }
  bool WasFinished() const { return _wasFinished; }
};

class ::compress::input_stream_with_crc:
  public ::ex1::input_stream,
  public CMyUnknownImp
{
public:
  MY_UNKNOWN_IMP1(::ex1::input_stream)

  STDMETHOD(Read)(void *data, uint32 size, uint32 *processedSize);
  STDMETHOD(Seek)(Int64 offset, uint32 seekOrigin, uint64 *newPosition);
private:
  CMyComPtr<::ex1::input_stream> _stream;
  uint64 _size;
  uint32 _crc;
  // bool _wasFinished;
public:
  void SetStream(::ex1::input_stream *stream) { _stream = stream;  }
  void Init()
  {
    _size = 0;
    // _wasFinished = false;
    _crc = CRC_INIT_VAL;
  }
  void ReleaseStream() { _stream.Release(); }
  uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
  uint64 GetSize() const { return _size; }
  // bool WasFinished() const { return _wasFinished; }
};

#endif
