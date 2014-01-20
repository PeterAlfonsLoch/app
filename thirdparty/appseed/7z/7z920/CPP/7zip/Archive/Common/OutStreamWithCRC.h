// OutStreamWithCRC.h

#ifndef __OUT_STREAM_WITH_CRC_H
#define __OUT_STREAM_WITH_CRC_H

#include "../../../../C/7zCrc.h"

#include "../../../Common/MyCom.h"

#include "../../IStream.h"

class COutStreamWithCRC:
  public ISequentialOutStream,
  public CMyUnknownImp
{
  CMyComPtr<ISequentialOutStream> _stream;
  uint64 _size;
  uint32 _crc;
  bool _calculate;
public:
  MY_UNKNOWN_IMP
  STDMETHOD(Write)(const void *data, uint32 size, uint32 *processedSize);
  void SetStream(ISequentialOutStream *stream) { _stream = stream; }
  void ReleaseStream() { _stream.Release(); }
  void Init(bool calculate = true)
  {
    _size = 0;
    _calculate = calculate;
    _crc = CRC_INIT_VAL;
  }
  void InitCRC() { _crc = CRC_INIT_VAL; }
  uint64 GetSize() const { return _size; }
  uint32 GetCRC() const { return CRC_GET_DIGEST(_crc); }
};

#endif
