// 7zFolderInStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday

#pragma once

namespace n7z
{

   class CFolderInStream:
      public ::ex1::reader,
      public ::compress::get_sub_stream_size_interface
   {
      ::compress::reader_with_crc *_inStreamWithHashSpec;
      ::ca::smart_pointer<::ex1::reader> _inStreamWithHash;
      ::ca::smart_pointer<::compress::archive_update_callback_interface> _updateCallback;

      bool _currentSizeIsDefined;
      bool _fileIsOpen;
      uint64 _currentSize;
      uint64 _filePos;
      const uint32 *_fileIndices;
      uint32 _numFiles;
      uint32 _fileIndex;

      HRESULT OpenStream();
      HRESULT CloseStream();
      void AddDigest();

   public:
      base_array<bool> Processed;
      base_array<uint32> CRCs;
      base_array<uint64> Sizes;

      DWORD_PTR read(void *data, DWORD_PTR size);
      virtual ex1::HRes GetSubStreamSize(uint64 subStream, uint64 *value);

      CFolderInStream();
      void Init(::compress::archive_update_callback_interface *updateCallback, const uint32 *fileIndices, uint32 numFiles);
      uint64 GetFullSize() const
      {
         uint64 size = 0;
         for (int i = 0; i < Sizes.get_count(); i++)
            size += Sizes[i];
         return size;
      }
   };

} // namespace n7z