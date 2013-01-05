// 7zOut.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once



namespace n7z
{

   class CWriteBufferLoc
   {
      byte *_data;
      size_t _size;
      size_t _pos;
   public:
      CWriteBufferLoc(): _size(0), _pos(0) {}
      void Init(byte *data, size_t size)
      {
         _data = data;
         _size = size;
         _pos = 0;
      }
      void WriteBytes(const void *data, size_t size)
      {
         if (size > _size - _pos)
            throw 1;
         memcpy(_data + _pos, data, size);
         _pos += size;
      }
      void WriteByte(byte b)
      {
         if (_size == _pos)
            throw 1;
         _data[_pos++] = b;
      }
      size_t GetPos() const { return _pos; }
   };

   struct CHeaderOptions
   {
      bool CompressMainHeader;
      bool WriteCTime;
      bool WriteATime;
      bool WriteMTime;

      CHeaderOptions():
      CompressMainHeader(true),
         WriteCTime(false),
         WriteATime(false),
         WriteMTime(true)
      {}
   };

   class COutArchive :
      virtual public ::radix::object
   {
   public:
      uint64_t _prefixHeaderPos;

      HRESULT WriteDirect(const void *data, uint32_t size);

      uint64_t GetPos() const;
      void WriteBytes(const void *data, size_t size);
      void WriteBytes(const ::ex1::byte_buffer &data) { WriteBytes(data, data.GetCapacity()); }
      void WriteByte(byte b);
      void WriteUInt32(uint32_t value);
      void WriteUInt64(uint64_t value);
      void WriteNumber(uint64_t value);
      void WriteID(uint64_t value) { WriteNumber(value); }

      void WriteFolder(const CFolder &folder);
      HRESULT WriteFileHeader(const CFileItem &itemInfo);
      void WriteBoolVector(const bool_array &boolVector);
      void WriteHashDigests(
         const bool_array &digestsDefined,
         const base_array<uint32_t> &hashDigests);

      void WritePackInfo(
         uint64_t dataOffset,
         const base_array<file_size> &packSizes,
         const bool_array &packCRCsDefined,
         const base_array<uint32_t> &packCRCs);

      void WriteUnpackInfo(const array_ptr_alloc<CFolder> &folders);

      void WriteSubStreamsInfo(
         const array_ptr_alloc<CFolder> &folders,
         const base_array<CNum> &numUnpackStreamsInFolders,
         const base_array<file_size> &unpackSizes,
         const bool_array &digestsDefined,
         const base_array<uint32_t> &hashDigests);

      void SkipAlign(uint32_t pos, uint32_t alignSize);
      void WriteAlignedBoolHeader(const bool_array &v, int32_t numDefined, byte type, uint32_t itemSize);
      void WriteUInt64DefVector(const CUInt64DefVector &v, byte type);

      HRESULT EncodeStream(
         ::compress::codecs_info_interface *codecsInfo, const base_array < ::compress::codec_info_ex > *externalCodecs,
         CEncoder &encoder, const ::ex1::byte_buffer &data,
         base_array<file_size> &packSizes, array_ptr_alloc<CFolder> &folders);
      void WriteHeader(
         const CArchiveDatabase &db,
         const CHeaderOptions &headerOptions,
         uint64_t &headerOffset);

      bool _countMode;
      bool _writeToStream;
      size_t _countSize;
      uint32_t _crc;
      ex1::out_buffer _outByte;
      CWriteBufferLoc _outByte2;

      bool _endMarker;

      HRESULT WriteSignature();
      HRESULT WriteFinishSignature();
      HRESULT WriteStartHeader(const CStartHeader &h);
      HRESULT WriteFinishHeader(const CFinishHeader &h);
      ::ca::smart_pointer < ::ex1::byte_output_stream > Stream;

      COutArchive(::ca::application * papp);
      ::ca::smart_pointer < ::ex1::writer > SeqStream;
      HRESULT Create(::ex1::writer *stream, bool endMarker);
      void Close();
      HRESULT SkipPrefixArchiveHeader();
      HRESULT WriteDatabase(
         ::compress::codecs_info_interface *codecsInfo, const base_array < ::compress::codec_info_ex > *externalCodecs,
         const CArchiveDatabase &db,
         const CCompressionMethodMode *options,
         const CHeaderOptions &headerOptions);

      static uint32_t GetVolHeadersSize(uint64_t dataSize, int32_t nameLength = 0, bool props = false);
      static uint64_t GetVolPureSize(uint64_t volSize, int32_t nameLength = 0, bool props = false);

   };

} // namespace n7z
