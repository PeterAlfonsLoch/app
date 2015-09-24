// 7zFolderOutStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"

//#include "7zFolderOutStream.h"


namespace n7z
{

   CFolderOutStream::CFolderOutStream()
   {
      _crcStreamSpec = new ::libcompress::writer_with_crc;
      _crcStream = _crcStreamSpec;
   }

   HRes CFolderOutStream::Init(
      const CArchiveDatabaseEx *db,
      uint32_t ref2Offset, uint32_t startIndex,
      const bool_array *extractStatuses,
      ::libcompress::archive_extract_callback_interface *extractCallback,
      bool testMode, bool checkCrc)
   {
      _db = db;
      _ref2Offset = ref2Offset;
      _startIndex = startIndex;

      _extractStatuses = extractStatuses;
      _extractCallback = extractCallback;
      _testMode = testMode;
      _checkCrc = checkCrc;

      _currentIndex = 0;
      _fileIsOpen = false;
      return ProcessEmptyFiles();
   }

   HRes CFolderOutStream::OpenFile()
   {
      int32_t askMode = ((*_extractStatuses)[_currentIndex]) ? (_testMode ?
         ::libcompress::archive::extract::ask_mode_test :
      ::libcompress::archive::extract::ask_mode_extract) :
      ::libcompress::archive::extract::ask_mode_skip;
      smart_pointer < ::file::writer > realOutStream;
      uint32_t index = _startIndex + _currentIndex;
      RINOK(_extractCallback->GetStream(_ref2Offset + index, &realOutStream.m_p, askMode));
      _crcStreamSpec->SetStream(realOutStream);
      _crcStreamSpec->Init(_checkCrc);
      _fileIsOpen = true;
      const CFileItem &fi = _db->Files[index];
      _rem = fi.get_count;
      if (askMode == ::libcompress::archive::extract::ask_mode_extract && !realOutStream &&
         !_db->IsItemAnti(index) && !fi.IsDir)
         askMode = ::libcompress::archive::extract::ask_mode_skip;
      return _extractCallback->PrepareOperation(askMode);
   }

   HRes CFolderOutStream::CloseFileAndSetResult(int32_t res)
   {
      _crcStreamSpec->ReleaseStream();
      _fileIsOpen = false;
      _currentIndex++;
      return _extractCallback->SetOperationResult(res);
   }

   HRes CFolderOutStream::CloseFileAndSetResult()
   {
      const CFileItem &fi = _db->Files[_startIndex + _currentIndex];
      return CloseFileAndSetResult(
         (fi.IsDir || !fi.CrcDefined || !_checkCrc || fi.Crc == _crcStreamSpec->GetCRC()) ?
         ::libcompress::archive::extract::operation_result_ok :
      ::libcompress::archive::extract::operation_result_CRCError);
   }

   HRes CFolderOutStream::ProcessEmptyFiles()
   {
      while (_currentIndex < _extractStatuses->get_count() && _db->Files[_startIndex + _currentIndex].get_count == 0)
      {
         RINOK(OpenFile());
         RINOK(CloseFileAndSetResult());
      }
      return S_OK;
   }

   void CFolderOutStream::write(const void *data, memory_size_t size, memory_size_t * processedSize)
   {
      if (processedSize != NULL)
         *processedSize = 0;
      while (size != 0)
      {
         if (_fileIsOpen)
         {
            memory_size_t cur = size < _rem ? size : (uint32_t)_rem;
            _crcStream->write(data, cur, &cur);
            if (cur == 0)
               break;
            data = (const byte *)data + cur;
            size -= cur;
            _rem -= cur;
            if (processedSize != NULL)
               *processedSize += cur;
            if (_rem == 0)
            {
               CloseFileAndSetResult();
               ProcessEmptyFiles();
               continue;
            }
         }
         else
         {
            ProcessEmptyFiles();
            if (_currentIndex == _extractStatuses->get_count())
            {
               // we support partial extracting
               if (processedSize != NULL)
                  *processedSize += size;
               break;
            }
            OpenFile();
         }
      }
   }

   HRes CFolderOutStream::GetSubStreamSize(uint64_t subStream, uint64_t * value)
   {
      *value = 0;
      if ((int32_t)subStream >= _extractStatuses->get_count())
         return S_FALSE;
      *value = _db->Files[_startIndex + (int32_t)subStream].get_count;
      return S_OK;
   }

   HRes CFolderOutStream::FlushCorrupted(int32_t resultEOperationResult)
   {
      while (_currentIndex < _extractStatuses->get_count())
      {
         if (_fileIsOpen)
         {
            RINOK(CloseFileAndSetResult(resultEOperationResult));
         }
         else
         {
            RINOK(OpenFile());
         }
      }
      return S_OK;
   }

} // namespace n7z
