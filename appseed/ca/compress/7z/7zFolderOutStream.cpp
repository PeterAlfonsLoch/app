// 7zFolderOutStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "StdAfx.h"

//#include "7zFolderOutStream.h"


namespace n7z
{

   CFolderOutStream::CFolderOutStream()
   {
      _crcStreamSpec = new ::compress::writer_with_crc;
      _crcStream = _crcStreamSpec;
   }

   ex1::HRes CFolderOutStream::Init(
      const CArchiveDatabaseEx *db,
      uint32 ref2Offset, uint32 startIndex,
      const bool_array *extractStatuses,
      ::compress::archive_extract_callback_interface *extractCallback,
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

   ex1::HRes CFolderOutStream::OpenFile()
   {
      int32 askMode = ((*_extractStatuses)[_currentIndex]) ? (_testMode ?
         ::compress::archive::extract::ask_mode_test :
      ::compress::archive::extract::ask_mode_extract) :
      ::compress::archive::extract::ask_mode_skip;
      ::ca::smart_pointer < ::ex1::writer > realOutStream;
      uint32 index = _startIndex + _currentIndex;
      RINOK(_extractCallback->GetStream(_ref2Offset + index, &realOutStream.m_p, askMode));
      _crcStreamSpec->SetStream(realOutStream);
      _crcStreamSpec->Init(_checkCrc);
      _fileIsOpen = true;
      const CFileItem &fi = _db->Files[index];
      _rem = fi.get_count;
      if (askMode == ::compress::archive::extract::ask_mode_extract && !realOutStream &&
         !_db->IsItemAnti(index) && !fi.IsDir)
         askMode = ::compress::archive::extract::ask_mode_skip;
      return _extractCallback->PrepareOperation(askMode);
   }

   ex1::HRes CFolderOutStream::CloseFileAndSetResult(int32 res)
   {
      _crcStreamSpec->ReleaseStream();
      _fileIsOpen = false;
      _currentIndex++;
      return _extractCallback->SetOperationResult(res);
   }

   ex1::HRes CFolderOutStream::CloseFileAndSetResult()
   {
      const CFileItem &fi = _db->Files[_startIndex + _currentIndex];
      return CloseFileAndSetResult(
         (fi.IsDir || !fi.CrcDefined || !_checkCrc || fi.Crc == _crcStreamSpec->GetCRC()) ?
         ::compress::archive::extract::operation_result_ok :
      ::compress::archive::extract::operation_result_CRCError);
   }

   ex1::HRes CFolderOutStream::ProcessEmptyFiles()
   {
      while (_currentIndex < _extractStatuses->get_count() && _db->Files[_startIndex + _currentIndex].get_count == 0)
      {
         RINOK(OpenFile());
         RINOK(CloseFileAndSetResult());
      }
      return S_OK;
   }

   void CFolderOutStream::write(const void *data, ::primitive::memory_size size, ::primitive::memory_size * processedSize)
   {
      if (processedSize != NULL)
         *processedSize = 0;
      while (size != 0)
      {
         if (_fileIsOpen)
         {
            ::primitive::memory_size cur = size < _rem ? size : (uint32)_rem;
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

   ex1::HRes CFolderOutStream::GetSubStreamSize(uint64 subStream, uint64 * value)
   {
      *value = 0;
      if ((int)subStream >= _extractStatuses->get_count())
         return S_FALSE;
      *value = _db->Files[_startIndex + (int)subStream].get_count;
      return S_OK;
   }

   ex1::HRes CFolderOutStream::FlushCorrupted(int32 resultEOperationResult)
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
