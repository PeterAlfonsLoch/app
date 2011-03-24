// 7zFolderOutStream.h
// from 7-zip on dawn of 13/01/2001 - Thursday
#pragma once

namespace n7z
{

   class CFolderOutStream:
      public ::ex1::writer,
      public ::compress::get_sub_stream_size_interface
   {
      ::compress::writer_with_crc *_crcStreamSpec;
      ::ca::smart_pointer<::ex1::writer> _crcStream;
      const CArchiveDatabaseEx *_db;
      const bool_array *_extractStatuses;
      ::ca::smart_pointer<::compress::archive_extract_callback_interface> _extractCallback;
      uint32 _ref2Offset;
      uint32 _startIndex;
      int _currentIndex;
      bool _testMode;
      bool _checkCrc;
      bool _fileIsOpen;
      uint64 _rem;

      ex1::HRes OpenFile();
      ex1::HRes CloseFileAndSetResult(int32 res);
      ex1::HRes CloseFileAndSetResult();
      ex1::HRes ProcessEmptyFiles();
   public:

         CFolderOutStream();

      void write(const void *data, DWORD_PTR size, DWORD_PTR *processedSize);
      ex1::HRes  GetSubStreamSize(uint64 subStream, uint64 *value);

      ex1::HRes Init(
         const CArchiveDatabaseEx *db,
         uint32 ref2Offset, uint32 startIndex,
         const bool_array *extractStatuses,
         ::compress::archive_extract_callback_interface *extractCallback,
         bool testMode, bool checkCrc);
      ex1::HRes FlushCorrupted(int32 resultEOperationResult);
      ex1::HRes WasWritingFinished() const
      { return (_currentIndex == _extractStatuses->get_count()) ? S_OK: E_FAIL; }
   };

} // namespace n7z