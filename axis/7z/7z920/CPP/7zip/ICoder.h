// ICoder.h

#ifndef __ICODER_H
#define __ICODER_H

#include "IStream.h"

#define CODER_INTERFACE(i, x) DECL_INTERFACE(i, 4, x)

CODER_INTERFACE(ICompressProgressInfo, 0x04)
{
  STDMETHOD(SetRatioInfo)(const uint64 *inSize, const uint64 *outSize) PURE;
};

CODER_INTERFACE(ICompressCoder, 0x05)
{
  STDMETHOD(Code)(::ex1::reader *inStream, ISequentialOutStream *outStream,
      const uint64 *inSize, const uint64 *outSize,
      ICompressProgressInfo *progress) PURE;
};

CODER_INTERFACE(ICompressCoder2, 0x18)
{
  STDMETHOD(Code)(::ex1::reader **inStreams, const uint64 **inSizes, uint32 numInStreams,
      ISequentialOutStream **outStreams, const uint64 **outSizes, uint32 numOutStreams,
      ICompressProgressInfo *progress) PURE;
};

namespace NCoderPropID
{
  enum EEnum
  {
    kDefaultProp = 0,
    kDictionarySize,
    kUsedMemorySize,
    kOrder,
    kBlockSize,
    kPosStateBits,
    kLitContextBits,
    kLitPosBits,
    kNumFastBytes,
    kMatchFinder,
    kMatchFinderCycles,
    kNumPasses,
    kAlgorithm,
    kNumThreads,
    kEndMarker
  };
}

CODER_INTERFACE(ICompressSetCoderProperties, 0x20)
{
  STDMETHOD(SetCoderProperties)(const PROPID *propIDs, const PROPVARIANT *props, uint32 numProps) PURE;
};

/*
CODER_INTERFACE(ICompressSetCoderProperties, 0x21)
{
  STDMETHOD(SetDecoderProperties)(::ex1::reader *inStream) PURE;
};
*/

CODER_INTERFACE(ICompressSetDecoderProperties2, 0x22)
{
  STDMETHOD(SetDecoderProperties2)(const Byte *data, uint32 size) PURE;
};

CODER_INTERFACE(ICompressWriteCoderProperties, 0x23)
{
  STDMETHOD(WriteCoderProperties)(ISequentialOutStream *outStream) PURE;
};

CODER_INTERFACE(ICompressGetInStreamProcessedSize, 0x24)
{
  STDMETHOD(GetInStreamProcessedSize)(uint64 *value) PURE;
};

CODER_INTERFACE(ICompressSetCoderMt, 0x25)
{
  STDMETHOD(SetNumberOfThreads)(uint32 numThreads) PURE;
};

CODER_INTERFACE(ICompressGetSubStreamSize, 0x30)
{
  STDMETHOD(GetSubStreamSize)(uint64 subStream, uint64 *value) PURE;
};

CODER_INTERFACE(ICompressSetInStream, 0x31)
{
  STDMETHOD(SetInStream)(::ex1::reader *inStream) PURE;
  STDMETHOD(ReleaseInStream)() PURE;
};

CODER_INTERFACE(ICompressSetOutStream, 0x32)
{
  STDMETHOD(SetOutStream)(ISequentialOutStream *outStream) PURE;
  STDMETHOD(ReleaseOutStream)() PURE;
};

CODER_INTERFACE(ICompressSetInStreamSize, 0x33)
{
  STDMETHOD(SetInStreamSize)(const uint64 *inSize) PURE;
};

CODER_INTERFACE(ICompressSetOutStreamSize, 0x34)
{
  STDMETHOD(SetOutStreamSize)(const uint64 *outSize) PURE;
};

CODER_INTERFACE(ICompressSetBufSize, 0x35)
{
  STDMETHOD(SetInBufSize)(uint32 streamIndex, uint32 size) PURE;
  STDMETHOD(SetOutBufSize)(uint32 streamIndex, uint32 size) PURE;
};

CODER_INTERFACE(ICompressFilter, 0x40)
{
  STDMETHOD(Init)() PURE;
  STDMETHOD_(uint32, Filter)(Byte *data, uint32 size) PURE;
  // Filter converts as most as possible bytes
  // Filter return outSize (uint32)
  // if (outSize <= size): Filter have converted outSize bytes
  // if (outSize > size): Filter have not converted anything.
  //      and it needs at least outSize bytes to convert one block
  //      (it's for crypto block algorithms).
};

CODER_INTERFACE(ICompressCodecsInfo, 0x60)
{
  STDMETHOD(GetNumberOfMethods)(uint32 *numMethods) PURE;
  STDMETHOD(GetProperty)(uint32 index, PROPID propID, PROPVARIANT *value) PURE;
  STDMETHOD(CreateDecoder)(uint32 index, const GUID *iid, void **coder) PURE;
  STDMETHOD(CreateEncoder)(uint32 index, const GUID *iid, void **coder) PURE;
};
CODER_INTERFACE(ISetCompressCodecsInfo, 0x61)
{
  STDMETHOD(SetCompressCodecsInfo)(ICompressCodecsInfo *compressCodecsInfo) PURE;
};

CODER_INTERFACE(ICryptoProperties, 0x80)
{
  STDMETHOD(SetKey)(const Byte *data, uint32 size) PURE;
  STDMETHOD(SetInitVector)(const Byte *data, uint32 size) PURE;
};

/*
CODER_INTERFACE(ICryptoResetSalt, 0x88)
{
  STDMETHOD(ResetSalt)() PURE;
};
*/

CODER_INTERFACE(ICryptoResetInitVector, 0x8C)
{
  STDMETHOD(ResetInitVector)() PURE;
};

CODER_INTERFACE(ICryptoSetPassword, 0x90)
{
  STDMETHOD(CryptoSetPassword)(const Byte *data, uint32 size) PURE;
};

CODER_INTERFACE(ICryptoSetCRC, 0xA0)
{
  STDMETHOD(CryptoSetCRC)(uint32 crc) PURE;
};

//////////////////////
// It's for DLL file
namespace NMethodPropID
{
  enum EEnum
  {
    kID,
    kName,
    kDecoder,
    kEncoder,
    kInStreams,
    kOutStreams,
    kDescription,
    kDecoderIsAssigned,
    kEncoderIsAssigned
  };
}

#endif
