// 7zIn.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday

#include "framework.h"

/*#include "../../../../C/7zCrc.h"
#include "../../../../C/CpuArch.h"

#include "../../Common/StreamObjects.h"
#include "../../Common/StreamUtils.h"

#include "7zDecode.h"
#include "7zIn.h"*/

#define Get16(p) GetUi16(p)
#define Get32(p) GetUi32(p)
#define Get64(p) GetUi64(p)

// define FORMAT_7Z_RECOVERY if you want to recover multivolume archives with empty StartHeader
#ifndef _SFX
#define FORMAT_7Z_RECOVERY
#endif


namespace n7z {

static void BoolVector_Fill_False(bool_array &v, int32_t size)
{
  v.remove_all();
  v.allocate(0, size);
  for (int32_t i = 0; i < size; i++)
    v.add(false);
}

static bool BoolVector_GetAndSet(bool_array &v, uint32_t index)
{
  if (index >= (uint32_t)v.get_count())
    return true;
  bool res = v[index];
  v[index] = true;
  return res;
}

bool CFolder::CheckStructure() const
{
  const int32_t kNumCodersMax = sizeof(uint32_t) * 8; // don't change it
  const int32_t kMaskSize = sizeof(uint32_t) * 8; // it must be >= kNumCodersMax
  const int32_t kNumBindsMax = 32;

  if (Coders.get_count() > kNumCodersMax || BindPairs.get_count() > kNumBindsMax)
    return false;

  {
    bool_array v;
    BoolVector_Fill_False(v, (int32_t) (BindPairs.get_count() + PackStreams.get_count()));

    int32_t i;
    for (i = 0; i < BindPairs.get_count(); i++)
      if (BoolVector_GetAndSet(v, BindPairs[i].InIndex))
        return false;
    for (i = 0; i < PackStreams.get_count(); i++)
      if (BoolVector_GetAndSet(v, PackStreams[i]))
        return false;

    BoolVector_Fill_False(v, (int32_t) UnpackSizes.get_count());
    for (i = 0; i < BindPairs.get_count(); i++)
      if (BoolVector_GetAndSet(v, BindPairs[i].OutIndex))
        return false;
  }

  uint32_t mask[kMaskSize];
  int32_t i;
  for (i = 0; i < kMaskSize; i++)
    mask[i] = 0;

  {
    int_array inStreamToCoder, outStreamToCoder;
    for (i = 0; i < Coders.get_count(); i++)
    {
      CNum j;
      const CCoderInfo &coder = Coders[i];
      for (j = 0; j < coder.NumInStreams; j++)
        inStreamToCoder.add(i);
      for (j = 0; j < coder.NumOutStreams; j++)
        outStreamToCoder.add(i);
    }

    for (i = 0; i < BindPairs.get_count(); i++)
    {
      const CBindPair &bp = BindPairs[i];
      mask[inStreamToCoder[bp.InIndex]] |= (1 << outStreamToCoder[bp.OutIndex]);
    }
  }

  for (i = 0; i < kMaskSize; i++)
    for (int32_t j = 0; j < kMaskSize; j++)
      if (((1 << j) & mask[i]) != 0)
        mask[i] |= mask[j];

  for (i = 0; i < kMaskSize; i++)
    if (((1 << i) & mask[i]) != 0)
      return false;

  return true;
}

class CInArchiveException {};

static void ThrowException() { throw CInArchiveException(); }
static inline void ThrowEndOfData()   { ThrowException(); }
static inline void ThrowUnsupported() { ThrowException(); }
static inline void ThrowIncorrect()   { ThrowException(); }
static inline void ThrowUnsupportedVersion() { ThrowException(); }

/*
class CInArchiveException
{
public:
  enum CCauseType
  {
    kUnsupportedVersion = 0,
    kUnsupported,
    kIncorrect,
    kEndOfData
  } Cause;
  CInArchiveException(CCauseType cause): Cause(cause) {};
};

static void ThrowException(CInArchiveException::CCauseType ca) { throw CInArchiveException(ca); }
static void ThrowEndOfData()   { ThrowException(CInArchiveException::kEndOfData); }
static void ThrowUnsupported() { ThrowException(CInArchiveException::kUnsupported); }
static void ThrowIncorrect()   { ThrowException(CInArchiveException::kIncorrect); }
static void ThrowUnsupportedVersion() { ThrowException(CInArchiveException::kUnsupportedVersion); }
*/

class CStreamSwitch
{
  CInArchive *_archive;
  bool _needRemove;
public:
  CStreamSwitch(): _needRemove(false) {}
  ~CStreamSwitch() { Remove(); }
  void Remove();
  void set(CInArchive *archive, const byte *data, size_t size);
  void set(CInArchive *archive, const ::file::byte_buffer &byteBuffer);
  void set(CInArchive *archive, const smart_pointer_array < ::file::byte_buffer > *dataVector);
};

void CStreamSwitch::Remove()
{
  if (_needRemove)
  {
    _archive->DeleteByteStream();
    _needRemove = false;
  }
}

void CStreamSwitch::set(CInArchive *archive, const byte *data, size_t size)
{
  Remove();
  _archive = archive;
  _archive->AddByteStream(data, size);
  _needRemove = true;
}

void CStreamSwitch::set(CInArchive *archive, const ::file::byte_buffer &byteBuffer)
{
  set(archive, byteBuffer, byteBuffer.GetCapacity());
}

void CStreamSwitch::set(CInArchive *archive, const smart_pointer_array < ::file::byte_buffer > *dataVector)
{
  Remove();
  byte external = archive->ReadByte();
  if (external != 0)
  {
    int32_t dataIndex = (int32_t)archive->ReadNum();
    if (dataIndex < 0 || dataIndex >= dataVector->get_count())
      ThrowIncorrect();
    set(archive, (*dataVector)[dataIndex]);
  }
}

byte CInByte2::ReadByte()
{
  if (_pos >= _size)
    ThrowEndOfData();
  return _buffer[_pos++];
}

void CInByte2::ReadBytes(byte *data, size_t size)
{
  if (size > _size - _pos)
    ThrowEndOfData();
  for (size_t i = 0; i < size; i++)
    data[i] = _buffer[_pos++];
}

void CInByte2::SkipData(file_size size)
{
  if (size > _size - _pos)
    ThrowEndOfData();
  _pos += (size_t)size;
}

void CInByte2::SkipData()
{
  SkipData(ReadNumber());
}

uint64_t CInByte2::ReadNumber()
{
  if (_pos >= _size)
    ThrowEndOfData();
  byte firstByte = _buffer[_pos++];
  byte mask = 0x80;
  uint64_t value = 0;
  for (int32_t i = 0; i < 8; i++)
  {
    if ((firstByte & mask) == 0)
    {
      uint64_t highPart = firstByte & (mask - 1);
      value += (highPart << (i * 8));
      return value;
    }
    if (_pos >= _size)
      ThrowEndOfData();
    value |= ((uint64_t)_buffer[_pos++] << (8 * i));
    mask >>= 1;
  }
  return value;
}

CNum CInByte2::ReadNum()
{
  uint64_t value = ReadNumber();
  if (value > kNumMax)
    ThrowUnsupported();
  return (CNum)value;
}

uint32_t CInByte2::ReadUInt32()
{
  if (_pos + 4 > _size)
    ThrowEndOfData();
  uint32_t res = Get32(_buffer + _pos);
  _pos += 4;
  return res;
}

uint64_t CInByte2::ReadUInt64()
{
  if (_pos + 8 > _size)
    ThrowEndOfData();
  uint64_t res = Get64(_buffer + _pos);
  _pos += 8;
  return res;
}

void CInByte2::ReadString(string &s)
{
  const byte *buf = _buffer + _pos;
  size_t rem = (_size - _pos) / 2 * 2;
  {
    size_t i;
    for (i = 0; i < rem; i += 2)
      if (buf[i] == 0 && buf[i + 1] == 0)
        break;
    if (i == rem)
      ThrowEndOfData();
    rem = i;
  }
  int32_t len = (int32_t)(rem / 2);
  if (len < 0 || (size_t)len * 2 != rem)
    ThrowUnsupported();
  s = ::str::international::unicode_to_utf8(wstring((wchar_t *) buf, len));
  _pos += rem + 2;
}

static inline bool TestSignature(const byte *p)
{
  for (int32_t i = 0; i < kSignatureSize; i++)
    if (p[i] != kSignature[i])
      return false;
  return crc_calc(p + 12, 20) == GetUi32(p + 8);
}

#ifdef FORMAT_7Z_RECOVERY
static inline bool TestSignature2(const byte *p)
{
  int32_t i;
  for (i = 0; i < kSignatureSize; i++)
    if (p[i] != kSignature[i])
      return false;
  if (crc_calc(p + 12, 20) == GetUi32(p + 8))
    return true;
  for (i = 8; i < kHeaderSize; i++)
    if (p[i] != 0)
      return false;
  return (p[6] != 0 || p[7] != 0);
}
#else
#define TestSignature2(p) TestSignature(p)
#endif

HRESULT CInArchive::FindAndReadSignature(::file::input_stream *stream, const file_position *searchHeaderSizeLimit)
{
   RINOK(::file::read_false(stream, _header, kHeaderSize));

  if (TestSignature2(_header))
    return S_OK;

  ::file::byte_buffer byteBuffer;
  const uint32_t kBufferSize = (1 << 16);
  byteBuffer.SetCapacity(kBufferSize);
  byte *buffer = byteBuffer;
  ::primitive::memory_size numPrevBytes = kHeaderSize;
  memcpy(buffer, _header, kHeaderSize);
  file_position curTestPos = _arhiveBeginStreamPosition;
  for (;;)
  {
    if (searchHeaderSizeLimit != NULL)
      if (curTestPos - _arhiveBeginStreamPosition > *searchHeaderSizeLimit)
        break;
    do
    {
      ::primitive::memory_size numReadBytes = kBufferSize - numPrevBytes;
      ::primitive::memory_size processedSize;
      processedSize = stream->read(buffer + numPrevBytes, numReadBytes);
      numPrevBytes += processedSize;
      if (processedSize == 0)
        return S_FALSE;
    }
    while (numPrevBytes <= kHeaderSize);
    ::count numTests = numPrevBytes - kHeaderSize;
    for (index pos = 0; pos < numTests; pos++)
    {
      for (; buffer[pos] != '7' && pos < numTests; pos++);
      if (pos == numTests)
        break;
      if (TestSignature(buffer + pos))
      {
        memcpy(_header, buffer + pos, kHeaderSize);
        curTestPos += pos;
        _arhiveBeginStreamPosition = curTestPos;
        stream->seek(curTestPos + kHeaderSize, ::file::seek_begin);
        return S_OK;
      }
    }
    curTestPos += numTests;
    numPrevBytes -= numTests;
    memmove(buffer, buffer + numTests, (size_t) numPrevBytes);
  }
  return S_FALSE;
}

      CInArchive::CInArchive(sp(::base::application) papp) :
         element(papp)
      {
      }
      CInArchive::~CInArchive()
      {
      }

// S_FALSE means that file is not archive
HRESULT CInArchive::Open(::file::input_stream *stream, const file_position *searchHeaderSizeLimit)
{
  HeadersSize = 0;
  Close();
  _arhiveBeginStreamPosition = stream->seek(0, ::file::seek_current);
  RINOK(FindAndReadSignature(stream, searchHeaderSizeLimit));
  _stream = stream;
  return S_OK;
}

void CInArchive::Close()
{
  ::release(_stream.m_p);
}

void CInArchive::ReadArchiveProperties(CInArchiveInfo & /* archiveInfo */)
{
  for (;;)
  {
    if (ReadID() == NID::kEnd)
      break;
    SkipData();
  }
}

void CInArchive::GetNextFolderItem(CFolder &folder)
{
  CNum numCoders = ReadNum();

  folder.Coders.remove_all();
  CNum numInStreams = 0;
  CNum numOutStreams = 0;
  CNum i;
  for (i = 0; i < numCoders; i++)
  {
    folder.Coders.add(new CCoderInfo());
    CCoderInfo &coder = *folder.Coders.last_element();

    {
      byte mainByte = ReadByte();
      int32_t idSize = (mainByte & 0xF);
      byte longID[15];
      ReadBytes(longID, idSize);
      if (idSize > 8)
        ThrowUnsupported();
      uint64_t id = 0;
      for (int32_t j = 0; j < idSize; j++)
        id |= (uint64_t)longID[idSize - 1 - j] << (8 * j);
      coder.MethodID = id;

      if ((mainByte & 0x10) != 0)
      {
        coder.NumInStreams = ReadNum();
        coder.NumOutStreams = ReadNum();
      }
      else
      {
        coder.NumInStreams = 1;
        coder.NumOutStreams = 1;
      }
      if ((mainByte & 0x20) != 0)
      {
        CNum propsSize = ReadNum();
        coder.Props.SetCapacity((size_t)propsSize);
        ReadBytes((byte *)coder.Props, (size_t)propsSize);
      }
      if ((mainByte & 0x80) != 0)
        ThrowUnsupported();
    }
    numInStreams += coder.NumInStreams;
    numOutStreams += coder.NumOutStreams;
  }

  CNum numBindPairs = numOutStreams - 1;
  folder.BindPairs.remove_all();
  folder.BindPairs.allocate(0, numBindPairs);
  for (i = 0; i < numBindPairs; i++)
  {
    CBindPair bp;
    bp.InIndex = ReadNum();
    bp.OutIndex = ReadNum();
    folder.BindPairs.add(bp);
  }

  if (numInStreams < numBindPairs)
    ThrowUnsupported();
  CNum numPackStreams = numInStreams - numBindPairs;
  folder.PackStreams.allocate(0, numPackStreams);
  if (numPackStreams == 1)
  {
    for (i = 0; i < numInStreams; i++)
      if (folder.FindBindPairForInStream(i) < 0)
      {
        folder.PackStreams.add(i);
        break;
      }
    if (folder.PackStreams.get_count() != 1)
      ThrowUnsupported();
  }
  else
    for (i = 0; i < numPackStreams; i++)
      folder.PackStreams.add(ReadNum());
}

void CInArchive::WaitAttribute(uint64_t attribute)
{
  for (;;)
  {
    uint64_t type = ReadID();
    if (type == attribute)
      return;
    if (type == NID::kEnd)
      ThrowIncorrect();
    SkipData();
  }
}

void CInArchive::ReadHashDigests(int32_t numItems,
    bool_array &digestsDefined,
    array<uint32_t> &digests)
{
  ReadBoolVector2(numItems, digestsDefined);
  digests.remove_all();
  digests.allocate(0, numItems);
  for (int32_t i = 0; i < numItems; i++)
  {
    uint32_t crc = 0;
    if (digestsDefined[i])
      crc = ReadUInt32();
    digests.add(crc);
  }
}

void CInArchive::ReadPackInfo(
    file_position &dataOffset,
    array<file_size> &packSizes,
    bool_array &packCRCsDefined,
    array<uint32_t> &packCRCs)
{
  dataOffset = ReadNumber();
  CNum numPackStreams = ReadNum();

  WaitAttribute(NID::kSize);
  packSizes.remove_all();
  packSizes.allocate(0, numPackStreams);
  for (CNum i = 0; i < numPackStreams; i++)
    packSizes.add((file_size) ReadNumber());

  uint64_t type;
  for (;;)
  {
    type = ReadID();
    if (type == NID::kEnd)
      break;
    if (type == NID::kCRC)
    {
      ReadHashDigests(numPackStreams, packCRCsDefined, packCRCs);
      continue;
    }
    SkipData();
  }
  if (packCRCsDefined.is_empty())
  {
    BoolVector_Fill_False(packCRCsDefined, numPackStreams);
    packCRCs.allocate(0, numPackStreams);
    packCRCs.remove_all();
    for (CNum i = 0; i < numPackStreams; i++)
      packCRCs.add(0);
  }
}

void CInArchive::ReadUnpackInfo(
    const smart_pointer_array < ::file::byte_buffer > *dataVector,
    smart_pointer_array < CFolder > &folders)
{
  WaitAttribute(NID::kFolder);
  CNum numFolders = ReadNum();

  {
    CStreamSwitch streamSwitch;
    streamSwitch.set(this, dataVector);
    folders.remove_all();
    folders.set_size(numFolders);
    for (CNum i = 0; i < numFolders; i++)
    {
      GetNextFolderItem(folders[i]);
    }
  }

  WaitAttribute(NID::kCodersUnpackSize);

  CNum i;
  for (i = 0; i < numFolders; i++)
  {
    CFolder &folder = folders[i];
    CNum numOutStreams = folder.GetNumOutStreams();
    folder.UnpackSizes.allocate(0, numOutStreams);
    for (CNum j = 0; j < numOutStreams; j++)
      folder.UnpackSizes.add((file_size) ReadNumber());
  }

  for (;;)
  {
    uint64_t type = ReadID();
    if (type == NID::kEnd)
      return;
    if (type == NID::kCRC)
    {
      bool_array crcsDefined;
      array<uint32_t> crcs;
      ReadHashDigests(numFolders, crcsDefined, crcs);
      for (i = 0; i < numFolders; i++)
      {
        CFolder &folder = folders[i];
        folder.UnpackCRCDefined = crcsDefined[i];
        folder.UnpackCRC = crcs[i];
      }
      continue;
    }
    SkipData();
  }
}

void CInArchive::ReadSubStreamsInfo(
    const smart_pointer_array<CFolder> &folders,
    array<CNum> &numUnpackStreamsInFolders,
    array<file_size> &unpackSizes,
    bool_array &digestsDefined,
    array<uint32_t> &digests)
{
  numUnpackStreamsInFolders.remove_all();
  numUnpackStreamsInFolders.allocate(0, folders.get_count());
  uint64_t type;
  for (;;)
  {
    type = ReadID();
    if (type == NID::kNumUnpackStream)
    {
      for (int32_t i = 0; i < folders.get_count(); i++)
        numUnpackStreamsInFolders.add(ReadNum());
      continue;
    }
    if (type == NID::kCRC || type == NID::kSize)
      break;
    if (type == NID::kEnd)
      break;
    SkipData();
  }

  if (numUnpackStreamsInFolders.is_empty())
    for (int32_t i = 0; i < folders.get_count(); i++)
      numUnpackStreamsInFolders.add(1);

  int32_t i;
  for (i = 0; i < numUnpackStreamsInFolders.get_count(); i++)
  {
    // v3.13 incorrectly worked with empty folders
    // v4.07: we check that folder is empty
    CNum numSubstreams = numUnpackStreamsInFolders[i];
    if (numSubstreams == 0)
      continue;
    uint64_t sum = 0;
    for (CNum j = 1; j < numSubstreams; j++)
      if (type == NID::kSize)
      {
        uint64_t size = ReadNumber();
        unpackSizes.add((file_size) size);
        sum += size;
      }
    unpackSizes.add((file_size) (folders[i].GetUnpackSize() - sum));
  }
  if (type == NID::kSize)
    type = ReadID();

  int32_t numDigests = 0;
  int32_t numDigestsTotal = 0;
  for (i = 0; i < folders.get_count(); i++)
  {
    CNum numSubstreams = numUnpackStreamsInFolders[i];
    if (numSubstreams != 1 || !folders[i].UnpackCRCDefined)
      numDigests += numSubstreams;
    numDigestsTotal += numSubstreams;
  }

  for (;;)
  {
    if (type == NID::kCRC)
    {
      bool_array digestsDefined2;
      array<uint32_t> digests2;
      ReadHashDigests(numDigests, digestsDefined2, digests2);
      int32_t digestIndex = 0;
      for (i = 0; i < folders.get_count(); i++)
      {
        CNum numSubstreams = numUnpackStreamsInFolders[i];
        const CFolder &folder = folders[i];
        if (numSubstreams == 1 && folder.UnpackCRCDefined)
        {
          digestsDefined.add(true);
          digests.add(folder.UnpackCRC);
        }
        else
          for (CNum j = 0; j < numSubstreams; j++, digestIndex++)
          {
            digestsDefined.add(digestsDefined2[digestIndex]);
            digests.add(digests2[digestIndex]);
          }
      }
    }
    else if (type == NID::kEnd)
    {
      if (digestsDefined.is_empty())
      {
        BoolVector_Fill_False(digestsDefined, numDigestsTotal);
        digests.remove_all();
        for (int32_t i = 0; i < numDigestsTotal; i++)
          digests.add(0);
      }
      return;
    }
    else
      SkipData();
    type = ReadID();
  }
}

void CInArchive::ReadStreamsInfo(
    const smart_pointer_array < ::file::byte_buffer > * dataVector,
    file_position & dataOffset,
    array < file_size > & packSizes,
    bool_array & packCRCsDefined,
    array < uint32_t > & packCRCs,
    smart_pointer_array < CFolder > & folders,
    array < CNum > & numUnpackStreamsInFolders,
    array < file_size > & unpackSizes,
    bool_array & digestsDefined,
    array < uint32_t > & digests)
{
  for (;;)
  {
    uint64_t type = ReadID();
    if (type > ((uint32_t)1 << 30))
      ThrowIncorrect();
    switch((uint32_t)type)
    {
      case NID::kEnd:
        return;
      case NID::kPackInfo:
      {
        ReadPackInfo(dataOffset, packSizes, packCRCsDefined, packCRCs);
        break;
      }
      case NID::kUnpackInfo:
      {
        ReadUnpackInfo(dataVector, folders);
        break;
      }
      case NID::kSubStreamsInfo:
      {
        ReadSubStreamsInfo(folders, numUnpackStreamsInFolders,
            unpackSizes, digestsDefined, digests);
        break;
      }
      default:
        ThrowIncorrect();
    }
  }
}

void CInArchive::ReadBoolVector(int32_t numItems, bool_array &v)
{
  v.remove_all();
  v.allocate(0, numItems);
  byte b = 0;
  byte mask = 0;
  for (int32_t i = 0; i < numItems; i++)
  {
    if (mask == 0)
    {
      b = ReadByte();
      mask = 0x80;
    }
    v.add((b & mask) != 0);
    mask >>= 1;
  }
}

void CInArchive::ReadBoolVector2(int32_t numItems, bool_array &v)
{
  byte allAreDefined = ReadByte();
  if (allAreDefined == 0)
  {
    ReadBoolVector(numItems, v);
    return;
  }
  v.remove_all();
  v.allocate(0, numItems);
  for (int32_t i = 0; i < numItems; i++)
    v.add(true);
}

void CInArchive::ReadUInt64DefVector(const smart_pointer_array < ::file::byte_buffer > & dataVector, CUInt64DefVector & v, int32_t numFiles)
{
  ReadBoolVector2(numFiles, v.Defined);

  CStreamSwitch streamSwitch;
  streamSwitch.set(this, &dataVector);
  v.Values.allocate(0, numFiles);

  for (int32_t i = 0; i < numFiles; i++)
  {
    uint64_t t = 0;
    if (v.Defined[i])
      t = ReadUInt64();
    v.Values.add(t);
  }
}

HRESULT CInArchive::ReadAndDecodePackedStreams(
    ::libcompress::codecs_info_interface *codecsInfo,
    const array < ::libcompress::codec_info_ex > *externalCodecs,
    file_position baseOffset,
    file_position & dataOffset,
    smart_pointer_array < ::file::byte_buffer > &dataVector
    #ifndef _NO_CRYPTO
    , ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
    #endif
    )
{

   UNREFERENCED_PARAMETER(codecsInfo);
   UNREFERENCED_PARAMETER(externalCodecs);
   UNREFERENCED_PARAMETER(getTextPassword);
   UNREFERENCED_PARAMETER(passwordIsDefined);

  array<file_size> packSizes;
  bool_array packCRCsDefined;
  array<uint32_t> packCRCs;
  smart_pointer_array<CFolder> folders;

  array<CNum> numUnpackStreamsInFolders;
  array<file_size> unpackSizes;
  bool_array digestsDefined;
  array<uint32_t> digests;

  ReadStreamsInfo(NULL,
    dataOffset,
    packSizes,
    packCRCsDefined,
    packCRCs,
    folders,
    numUnpackStreamsInFolders,
    unpackSizes,
    digestsDefined,
    digests);

  // db.ArchiveInfo.DataStartPosition2 += db.ArchiveInfo.StartPositionAfterHeader;

  CNum packIndex = 0;
  CDecoder decoder(get_app(),
    #ifdef _ST_MODE
    false
    #else
    true
    #endif
    );
  uint64_t dataStartPos = baseOffset + dataOffset;
  for (int32_t i = 0; i < folders.get_count(); i++)
  {
    const CFolder &folder = folders[i];
    dataVector.add(new ::file::byte_buffer());
    ::file::byte_buffer &data = *dataVector.last_element();
    uint64_t unpackSize64 = folder.GetUnpackSize();
    size_t unpackSize = (size_t)unpackSize64;
    if (unpackSize != unpackSize64)
      ThrowUnsupported();
    data.SetCapacity(unpackSize);

    throw "should implement below";
    /*CBufPtrSeqOutStream *outStreamSpec = new CBufPtrSeqOutStream;
    smart_pointer<::file::writer> outStream = outStreamSpec;
    outStreamSpec->Init(data, unpackSize);

    HRESULT result = decoder.Decode(
      EXTERNAL_CODECS_LOC_VARS
      _stream, dataStartPos,
      &packSizes[packIndex], folder, outStream, NULL
      #ifndef _NO_CRYPTO
      , getTextPassword, passwordIsDefined
      #endif
      #if !defined(_7ZIP_ST) && !defined(_SFX)
      , false, 1
      #endif
      );
    RINOK(result);*/

    if (folder.UnpackCRCDefined)
      if (crc_calc(data, unpackSize) != folder.UnpackCRC)
        ThrowIncorrect();
    for (int32_t j = 0; j < folder.PackStreams.get_count(); j++)
    {
      uint64_t packSize = packSizes[packIndex++];
      dataStartPos += packSize;
      HeadersSize += packSize;
    }
  }
  return S_OK;
}

HRESULT CInArchive::ReadHeader(
    ::libcompress::codecs_info_interface *codecsInfo,
    const array < ::libcompress::codec_info_ex > *externalCodecs,
    CArchiveDatabaseEx &db
    #ifndef _NO_CRYPTO
    , ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
    #endif
    )
{
  uint64_t type = ReadID();

  if (type == NID::kArchiveProperties)
  {
    ReadArchiveProperties(db.ArchiveInfo);
    type = ReadID();
  }

  smart_pointer_array < ::file::byte_buffer > dataVector;

  if (type == NID::kAdditionalStreamsInfo)
  {
    HRESULT result = ReadAndDecodePackedStreams(
        codecsInfo, externalCodecs,
        db.ArchiveInfo.StartPositionAfterHeader,
        db.ArchiveInfo.DataStartPosition2,
        dataVector
        #ifndef _NO_CRYPTO
        , getTextPassword, passwordIsDefined
        #endif
        );
    RINOK(result);
    db.ArchiveInfo.DataStartPosition2 += db.ArchiveInfo.StartPositionAfterHeader;
    type = ReadID();
  }

  array<file_size> unpackSizes;
  bool_array digestsDefined;
  array<uint32_t> digests;

  if (type == NID::kMainStreamsInfo)
  {
    ReadStreamsInfo(&dataVector,
        db.ArchiveInfo.DataStartPosition,
        db.PackSizes,
        db.PackCRCsDefined,
        db.PackCRCs,
        db.Folders,
        db.NumUnpackStreamsVector,
        unpackSizes,
        digestsDefined,
        digests);
    db.ArchiveInfo.DataStartPosition += db.ArchiveInfo.StartPositionAfterHeader;
    type = ReadID();
  }
  else
  {
    for (int32_t i = 0; i < db.Folders.get_count(); i++)
    {
      db.NumUnpackStreamsVector.add(1);
      CFolder &folder = db.Folders[i];
      unpackSizes.add(folder.GetUnpackSize());
      digestsDefined.add(folder.UnpackCRCDefined);
      digests.add(folder.UnpackCRC);
    }
  }

  db.Files.remove_all();

  if (type == NID::kEnd)
    return S_OK;
  if (type != NID::kFilesInfo)
    ThrowIncorrect();

  CNum numFiles = ReadNum();
//  db.Files.set_size(0, numFiles);
  CNum i;
  for (i = 0; i < numFiles; i++)
    db.Files.add(new CFileItem());

  db.ArchiveInfo.FileInfoPopIDs.add(NID::kSize);
  if (!db.PackSizes.is_empty())
    db.ArchiveInfo.FileInfoPopIDs.add(NID::kPackInfo);
  if (numFiles > 0  && !digests.is_empty())
    db.ArchiveInfo.FileInfoPopIDs.add(NID::kCRC);

  bool_array emptyStreamVector;
  BoolVector_Fill_False(emptyStreamVector, (int32_t)numFiles);
  bool_array emptyFileVector;
  bool_array antiFileVector;
  CNum numEmptyStreams = 0;

  for (;;)
  {
    uint64_t type = ReadID();
    if (type == NID::kEnd)
      break;
    uint64_t size = ReadNumber();
    size_t ppp = _inByteBack->_pos;
    bool addPropIdToList = true;
    bool isKnownType = true;
    if (type > ((uint32_t)1 << 30))
      isKnownType = false;
    else switch((uint32_t)type)
    {
      case NID::kName:
      {
        CStreamSwitch streamSwitch;
        streamSwitch.set(this, &dataVector);
        for (int32_t i = 0; i < db.Files.get_count(); i++)
          _inByteBack->ReadString(db.Files[i].Name);
        break;
      }
      case NID::kWinAttributes:
      {
        bool_array boolVector;
        ReadBoolVector2((int32_t) db.Files.get_count(), boolVector);
        CStreamSwitch streamSwitch;
        streamSwitch.set(this, &dataVector);
        for (i = 0; i < numFiles; i++)
        {
          CFileItem &file = db.Files[i];
          file.AttribDefined = boolVector[i];
          if (file.AttribDefined)
            file.Attrib = ReadUInt32();
        }
        break;
      }
      case NID::kEmptyStream:
      {
        ReadBoolVector(numFiles, emptyStreamVector);
        for (i = 0; i < (CNum)emptyStreamVector.get_count(); i++)
          if (emptyStreamVector[i])
            numEmptyStreams++;

        BoolVector_Fill_False(emptyFileVector, numEmptyStreams);
        BoolVector_Fill_False(antiFileVector, numEmptyStreams);

        break;
      }
      case NID::kEmptyFile:  ReadBoolVector(numEmptyStreams, emptyFileVector); break;
      case NID::kAnti:  ReadBoolVector(numEmptyStreams, antiFileVector); break;
      case NID::kStartPos:  ReadUInt64DefVector(dataVector, db.StartPos, (int32_t)numFiles); break;
      case NID::kCTime:  ReadUInt64DefVector(dataVector, db.CTime, (int32_t)numFiles); break;
      case NID::kATime:  ReadUInt64DefVector(dataVector, db.ATime, (int32_t)numFiles); break;
      case NID::kMTime:  ReadUInt64DefVector(dataVector, db.MTime, (int32_t)numFiles); break;
      case NID::kDummy:
      {
        for (uint64_t j = 0; j < size; j++)
          if (ReadByte() != 0)
            ThrowIncorrect();
        addPropIdToList = false;
        break;
      }
      default:
        addPropIdToList = isKnownType = false;
    }
    if (isKnownType)
    {
      if(addPropIdToList)
        db.ArchiveInfo.FileInfoPopIDs.add(type);
    }
    else
      SkipData(size);
    bool checkRecordsSize = (db.ArchiveInfo.Version.Major > 0 ||
        db.ArchiveInfo.Version.Minor > 2);
    if (checkRecordsSize && _inByteBack->_pos - ppp != size)
      ThrowIncorrect();
  }

  CNum emptyFileIndex = 0;
  CNum sizeIndex = 0;

  CNum numAntiItems = 0;
  for (i = 0; i < numEmptyStreams; i++)
    if (antiFileVector[i])
      numAntiItems++;

  for (i = 0; i < numFiles; i++)
  {
    CFileItem &file = db.Files[i];
    bool isAnti;
    file.HasStream = !emptyStreamVector[i];
    if (file.HasStream)
    {
      file.IsDir = false;
      isAnti = false;
      file.get_count = unpackSizes[sizeIndex];
      file.Crc = digests[sizeIndex];
      file.CrcDefined = digestsDefined[sizeIndex];
      sizeIndex++;
    }
    else
    {
      file.IsDir = !emptyFileVector[emptyFileIndex];
      isAnti = antiFileVector[emptyFileIndex];
      emptyFileIndex++;
      file.get_count = 0;
      file.CrcDefined = false;
    }
    if (numAntiItems != 0)
      db.IsAnti.add(isAnti);
  }
  return S_OK;
}


void CArchiveDatabaseEx::FillFolderStartPackStream()
{
  FolderStartPackStreamIndex.remove_all();
  FolderStartPackStreamIndex.allocate(0, Folders.get_count());
  CNum startPos = 0;
  for (int32_t i = 0; i < Folders.get_count(); i++)
  {
    FolderStartPackStreamIndex.add(startPos);
    startPos += (CNum)Folders[i].PackStreams.get_count();
  }
}

void CArchiveDatabaseEx::FillStartPos()
{
  PackStreamStartPositions.remove_all();
  PackStreamStartPositions.allocate(0, PackSizes.get_count());
  file_position startPos = 0;
  for (int32_t i = 0; i < PackSizes.get_count(); i++)
  {
    PackStreamStartPositions.add(startPos);
    startPos += PackSizes[i];
  }
}

void CArchiveDatabaseEx::FillFolderStartFileIndex()
{
  FolderStartFileIndex.remove_all();
  FolderStartFileIndex.allocate(0, Folders.get_count());
  FileIndexToFolderIndexMap.remove_all();
  FileIndexToFolderIndexMap.allocate(0, Files.get_count());

  int32_t folderIndex = 0;
  CNum indexInFolder = 0;
  for (int32_t i = 0; i < Files.get_count(); i++)
  {
    const CFileItem &file = Files[i];
    bool emptyStream = !file.HasStream;
    if (emptyStream && indexInFolder == 0)
    {
      FileIndexToFolderIndexMap.add(kNumNoIndex);
      continue;
    }
    if (indexInFolder == 0)
    {
      // v3.13 incorrectly worked with empty folders
      // v4.07: Loop for skipping empty folders
      for (;;)
      {
        if (folderIndex >= Folders.get_count())
          ThrowIncorrect();
        FolderStartFileIndex.add(i); // check it
        if (NumUnpackStreamsVector[folderIndex] != 0)
          break;
        folderIndex++;
      }
    }
    FileIndexToFolderIndexMap.add(folderIndex);
    if (emptyStream)
      continue;
    indexInFolder++;
    if (indexInFolder >= NumUnpackStreamsVector[folderIndex])
    {
      folderIndex++;
      indexInFolder = 0;
    }
  }
}

HRESULT CInArchive::ReadDatabase2(
    ::libcompress::codecs_info_interface *codecsInfo,
    const array < ::libcompress::codec_info_ex > *externalCodecs,
    CArchiveDatabaseEx &db
    #ifndef _NO_CRYPTO
    , ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
    #endif
    )
{
  db.clear();
  db.ArchiveInfo.StartPosition = _arhiveBeginStreamPosition;

  db.ArchiveInfo.Version.Major = _header[6];
  db.ArchiveInfo.Version.Minor = _header[7];

  if (db.ArchiveInfo.Version.Major != kMajorVersion)
    ThrowUnsupportedVersion();

  uint32_t crcFromArchive = Get32(_header + 8);
  uint64_t nextHeaderOffset = Get64(_header + 0xC);
  uint64_t nextHeaderSize = Get64(_header + 0x14);
  uint32_t nextHeaderCRC = Get32(_header + 0x1C);
  uint32_t crc = crc_calc(_header + 0xC, 20);

  #ifdef FORMAT_7Z_RECOVERY
  if (crcFromArchive == 0 && nextHeaderOffset == 0 && nextHeaderSize == 0 && nextHeaderCRC == 0)
  {
    uint64_t cur, cur2;
    cur = _stream->seek(0, ::file::seek_current);
    const int32_t kCheckSize = 500;
    byte buf[kCheckSize];
    cur2 = _stream->seek(0, ::file::seek_end);
    int32_t checkSize = kCheckSize;
    if (cur2 - cur < kCheckSize)
      checkSize = (int32_t)(cur2 - cur);
    cur2 = _stream->seek(-checkSize, ::file::seek_end);

    RINOK(::file::read_false(_stream, buf, (size_t)checkSize));

    int32_t i;
    for (i = (int32_t)checkSize - 2; i >= 0; i--)
      if ((buf[i] == 0x17 && buf[i + 1] == 0x6) || (buf[i] == 0x01 && buf[i + 1] == 0x04))
        break;
    if (i < 0)
      return S_FALSE;
    nextHeaderSize = checkSize - i;
    nextHeaderOffset = cur2 - cur + i;
    nextHeaderCRC = crc_calc(buf + i, (size_t)nextHeaderSize);
    _stream->seek(cur,::file::seek_current);
  }
  else
  #endif
  {
    if (crc != crcFromArchive)
      ThrowIncorrect();
  }

  db.ArchiveInfo.StartPositionAfterHeader = _arhiveBeginStreamPosition + kHeaderSize;

  if (nextHeaderSize == 0)
    return S_OK;

  if (nextHeaderSize > (uint64_t)0xFFFFFFFF)
    return S_FALSE;

  if ((int64_t)nextHeaderOffset < 0)
    return S_FALSE;

  _stream->seek(nextHeaderOffset, ::file::seek_current); // RINOK

  ::file::byte_buffer buffer2;
  buffer2.SetCapacity((size_t)nextHeaderSize);

  RINOK(::file::read_false(_stream, buffer2, (size_t)nextHeaderSize));
  HeadersSize += kHeaderSize + nextHeaderSize;
  db.PhySize = kHeaderSize + nextHeaderOffset + nextHeaderSize;

  if (crc_calc(buffer2, (uint32_t)nextHeaderSize) != nextHeaderCRC)
    ThrowIncorrect();

  CStreamSwitch streamSwitch;
  streamSwitch.set(this, buffer2);

  smart_pointer_array < ::file::byte_buffer > dataVector;

  uint64_t type = ReadID();
  if (type != NID::kHeader)
  {
    if (type != NID::kEncodedHeader)
      ThrowIncorrect();
    HRESULT result = ReadAndDecodePackedStreams(
        codecsInfo, externalCodecs,
        db.ArchiveInfo.StartPositionAfterHeader,
        db.ArchiveInfo.DataStartPosition2,
        dataVector
        #ifndef _NO_CRYPTO
        , getTextPassword, passwordIsDefined
        #endif
        );
    RINOK(result);
    if (dataVector.get_count() == 0)
      return S_OK;
    if (dataVector.get_count() > 1)
      ThrowIncorrect();
    streamSwitch.Remove();
    streamSwitch.set(this, dataVector[0]);
    if (ReadID() != NID::kHeader)
      ThrowIncorrect();
  }

  db.HeadersSize = HeadersSize;

  return ReadHeader(
    codecsInfo, externalCodecs,
    db
    #ifndef _NO_CRYPTO
    , getTextPassword, passwordIsDefined
    #endif
    );
}

HRESULT CInArchive::ReadDatabase(
    ::libcompress::codecs_info_interface *codecsInfo,
    const array < ::libcompress::codec_info_ex > *externalCodecs,
    CArchiveDatabaseEx &db
    #ifndef _NO_CRYPTO
    , ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
    #endif
    )
{
  try
  {
    return ReadDatabase2(
      codecsInfo, externalCodecs, db
      #ifndef _NO_CRYPTO
      , getTextPassword, passwordIsDefined
      #endif
      );
  }
  catch(CInArchiveException &) { return S_FALSE; }
}

}
