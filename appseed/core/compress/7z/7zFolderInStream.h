// 7zFolderInStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace n7z
{

   class CFolderInStream:
      public ::file::reader,
      public ::libcompress::get_sub_stream_size_interface
   {
      ::libcompress::reader_with_crc *_inStreamWithHashSpec;
      smart_pointer < ::file::reader > _inStreamWithHash;
      smart_pointer < ::libcompress::archive_update_callback_interface > _updateCallback;

      bool _currentSizeIsDefined;
      bool _fileIsOpen;
      uint64_t _currentSize;
      uint64_t _filePos;
      const uint32_t *_fileIndices;
      uint32_t _numFiles;
      uint32_t _fileIndex;

      HRESULT OpenStream();
      HRESULT CloseStream();
      void AddDigest();

   public:
      array<bool> Processed;
      array<uint32_t> CRCs;
      array<uint64_t> Sizes;

      memory_size_t read(void *data, memory_size_t size);
      virtual HRes GetSubStreamSize(uint64_t subStream, uint64_t *value);

      CFolderInStream();
      void Init(::libcompress::archive_update_callback_interface *updateCallback, const uint32_t *fileIndices, uint32_t numFiles);
      uint64_t GetFullSize() const
      {
         uint64_t size = 0;
         for (int32_t i = 0; i < Sizes.get_count(); i++)
            size += Sizes[i];
         return size;
      }
   };

} // namespace n7z
