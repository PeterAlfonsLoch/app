// 7zFolderOutStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace n7z
{

   class CFolderOutStream:
      public ::file::writer,
      public ::libcompress::get_sub_stream_size_interface
   {
      ::libcompress::writer_with_crc *_crcStreamSpec;
      smart_pointer < ::file::writer > _crcStream;
      const CArchiveDatabaseEx *_db;
      const bool_array *_extractStatuses;
      smart_pointer < ::libcompress::archive_extract_callback_interface > _extractCallback;
      uint32_t _ref2Offset;
      uint32_t _startIndex;
      int32_t _currentIndex;
      bool _testMode;
      bool _checkCrc;
      bool _fileIsOpen;
      uint64_t _rem;

      ::ca2::HRes OpenFile();
      ::ca2::HRes CloseFileAndSetResult(int32_t res);
      ::ca2::HRes CloseFileAndSetResult();
      ::ca2::HRes ProcessEmptyFiles();
   public:

         CFolderOutStream();

      void write(const void *data, ::primitive::memory_size size, ::primitive::memory_size *processedSize);
      ::ca2::HRes  GetSubStreamSize(uint64_t subStream, uint64_t *value);

      ::ca2::HRes Init(
         const CArchiveDatabaseEx *db,
         uint32_t ref2Offset, uint32_t startIndex,
         const bool_array *extractStatuses,
         ::libcompress::archive_extract_callback_interface *extractCallback,
         bool testMode, bool checkCrc);
      ::ca2::HRes FlushCorrupted(int32_t resultEOperationResult);
      ::ca2::HRes WasWritingFinished() const
      { return (_currentIndex == _extractStatuses->get_count()) ? S_OK: E_FAIL; }
   };

} // namespace n7z
