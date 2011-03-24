// 7zIn.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace n7z
{

   struct CInArchiveInfo
   {
      CArchiveVersion Version;
      uint64 StartPosition;
      uint64 StartPositionAfterHeader;
      uint64 DataStartPosition;
      uint64 DataStartPosition2;
      base_array<uint64> FileInfoPopIDs;
      void clear()
      {
         FileInfoPopIDs.remove_all();
      }
   };

   struct CArchiveDatabaseEx: public CArchiveDatabase
   {
      CInArchiveInfo ArchiveInfo;
      base_array<uint64> PackStreamStartPositions;
      base_array<CNum> FolderStartPackStreamIndex;
      base_array<CNum> FolderStartFileIndex;
      base_array<CNum> FileIndexToFolderIndexMap;

      uint64 HeadersSize;
      uint64 PhySize;

      void clear()
      {
         CArchiveDatabase::clear();
         ArchiveInfo.clear();
         PackStreamStartPositions.remove_all();
         FolderStartPackStreamIndex.remove_all();
         FolderStartFileIndex.remove_all();
         FileIndexToFolderIndexMap.remove_all();

         HeadersSize = 0;
         PhySize = 0;
      }

      void FillFolderStartPackStream();
      void FillStartPos();
      void FillFolderStartFileIndex();

      void Fill()
      {
         FillFolderStartPackStream();
         FillStartPos();
         FillFolderStartFileIndex();
      }

      uint64 GetFolderStreamPos(int folderIndex, int indexInFolder) const
      {
         return ArchiveInfo.DataStartPosition +
            PackStreamStartPositions[FolderStartPackStreamIndex[folderIndex] + indexInFolder];
      }

      uint64 GetFolderFullPackSize(int folderIndex) const
      {
         CNum packStreamIndex = FolderStartPackStreamIndex[folderIndex];
         const CFolder &folder = Folders[folderIndex];
         uint64 size = 0;
         for (int i = 0; i < folder.PackStreams.get_count(); i++)
            size += PackSizes[packStreamIndex + i];
         return size;
      }

      uint64 GetFolderPackStreamSize(int folderIndex, int streamIndex) const
      {
         return PackSizes[FolderStartPackStreamIndex[folderIndex] + streamIndex];
      }

      uint64 GetFilePackSize(CNum fileIndex) const
      {
         CNum folderIndex = FileIndexToFolderIndexMap[fileIndex];
         if (folderIndex != kNumNoIndex)
            if (FolderStartFileIndex[folderIndex] == fileIndex)
               return GetFolderFullPackSize(folderIndex);
         return 0;
      }
   };

   class CInByte2
   {
      const byte *_buffer;
      size_t _size;
   public:
      size_t _pos;
      void Init(const byte *buffer, size_t size)
      {
         _buffer = buffer;
         _size = size;
         _pos = 0;
      }
      byte ReadByte();
      void ReadBytes(byte *data, size_t size);
      void SkipData(uint64 size);
      void SkipData();
      uint64 ReadNumber();
      CNum ReadNum();
      uint32 ReadUInt32();
      uint64 ReadUInt64();
      void ReadString(string &s);
   };

   class CStreamSwitch;

   const uint32 kHeaderSize = 32;

   class CInArchive
   {
      friend class CStreamSwitch;

      ::ca::smart_pointer<::ex1::input_stream> _stream;

      array_ptr_alloc<CInByte2> _inByteVector;
      CInByte2 *_inByteBack;

      uint64 _arhiveBeginStreamPosition;

      byte _header[kHeaderSize];

      uint64 HeadersSize;

      void AddByteStream(const byte *buffer, size_t size)
      {
         _inByteVector.add(CInByte2());
         _inByteBack = &_inByteVector.last_element();
         _inByteBack->Init(buffer, size);
      }

      void DeleteByteStream()
      {
         _inByteVector.remove_last();
         if (!_inByteVector.is_empty())
            _inByteBack = &_inByteVector.last_element();
      }

   private:
      HRESULT FindAndReadSignature(::ex1::input_stream *stream, const uint64 *searchHeaderSizeLimit);

      void ReadBytes(byte *data, size_t size) { _inByteBack->ReadBytes(data, size); }
      byte ReadByte() { return _inByteBack->ReadByte(); }
      uint64 ReadNumber() { return _inByteBack->ReadNumber(); }
      CNum ReadNum() { return _inByteBack->ReadNum(); }
      uint64 ReadID() { return _inByteBack->ReadNumber(); }
      uint32 ReadUInt32() { return _inByteBack->ReadUInt32(); }
      uint64 ReadUInt64() { return _inByteBack->ReadUInt64(); }
      void SkipData(uint64 size) { _inByteBack->SkipData(size); }
      void SkipData() { _inByteBack->SkipData(); }
      void WaitAttribute(uint64 attribute);

      void ReadArchiveProperties(CInArchiveInfo &archiveInfo);
      void GetNextFolderItem(CFolder &itemInfo);
      void ReadHashDigests(int numItems,
         bool_array &digestsDefined, base_array<uint32> &digests);

      void ReadPackInfo(
         uint64 &dataOffset,
         base_array<uint64> &packSizes,
         bool_array &packCRCsDefined,
         base_array<uint32> &packCRCs);

      void ReadUnpackInfo(
         const array_ptr_alloc<::ex1::byte_buffer> *dataVector,
         array_ptr_alloc<CFolder> &folders);

      void ReadSubStreamsInfo(
         const array_ptr_alloc<CFolder> &folders,
         base_array<CNum> &numUnpackStreamsInFolders,
         base_array<uint64> &unpackSizes,
         bool_array &digestsDefined,
         base_array<uint32> &digests);

      void ReadStreamsInfo(
         const array_ptr_alloc<::ex1::byte_buffer> *dataVector,
         uint64 &dataOffset,
         base_array<uint64> &packSizes,
         bool_array &packCRCsDefined,
         base_array<uint32> &packCRCs,
         array_ptr_alloc<CFolder> &folders,
         base_array<CNum> &numUnpackStreamsInFolders,
         base_array<uint64> &unpackSizes,
         bool_array &digestsDefined,
         base_array<uint32> &digests);


      void ReadBoolVector(int numItems, bool_array &v);
      void ReadBoolVector2(int numItems, bool_array &v);
      void ReadUInt64DefVector(const array_ptr_alloc<::ex1::byte_buffer> &dataVector,
         CUInt64DefVector &v, int numFiles);
      HRESULT ReadAndDecodePackedStreams(
         ::compress::codecs_info_interface *codecsInfo, const base_array<::compress::codec_info_ex> *externalCodecs,
         uint64 baseOffset, uint64 &dataOffset,
         array_ptr_alloc<::ex1::byte_buffer> &dataVector,
         ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
         );
      HRESULT ReadHeader(
         ::compress::codecs_info_interface *codecsInfo, const base_array<::compress::codec_info_ex> *externalCodecs,
         CArchiveDatabaseEx &db,
         ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
         );
      HRESULT ReadDatabase2(
         ::compress::codecs_info_interface *codecsInfo, const base_array<::compress::codec_info_ex> *externalCodecs,
         CArchiveDatabaseEx &db,
         ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
         );
   public:
      HRESULT Open(::ex1::input_stream *stream, const uint64 *searchHeaderSizeLimit); // S_FALSE means is not archive
      void Close();

      HRESULT ReadDatabase(
         ::compress::codecs_info_interface *codecsInfo, const base_array<::compress::codec_info_ex> *externalCodecs,
         CArchiveDatabaseEx &db,
         ::crypto::get_text_password_interface *getTextPassword, bool &passwordIsDefined
         );
   };

} // namespace n7z
