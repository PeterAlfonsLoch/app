// 7zFolderInStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "framework.h"


namespace n7z
{

   CFolderInStream::CFolderInStream()
   {
      _inStreamWithHashSpec = new ::libcompress::reader_with_crc;
      _inStreamWithHash = _inStreamWithHashSpec;
   }

   void CFolderInStream::Init(::libcompress::archive_update_callback_interface *updateCallback,
      const uint32_t *fileIndices, uint32_t numFiles)
   {
      _updateCallback = updateCallback;
      _numFiles = numFiles;
      _fileIndex = 0;
      _fileIndices = fileIndices;
      Processed.remove_all();
      CRCs.remove_all();
      Sizes.remove_all();
      _fileIsOpen = false;
      _currentSizeIsDefined = false;
   }

   HRESULT CFolderInStream::OpenStream()
   {
      _filePos = 0;
      while (_fileIndex < _numFiles)
      {
         smart_pointer < ::file::input_stream > stream;
         HRESULT result = _updateCallback->GetStream(_fileIndices[_fileIndex], &stream.m_p);
         if (result != S_OK && result != S_FALSE)
            return result;
         _fileIndex++;
         _inStreamWithHashSpec->SetStream(stream);
         _inStreamWithHashSpec->Init();
         if (stream)
         {
            _fileIsOpen = true;
            smart_pointer < ::file::stream_get_size > streamGetSize;
            streamGetSize = dynamic_cast < ::file::stream_get_size * > (stream.m_p);
            if (streamGetSize)
            {
               RINOK(streamGetSize->GetSize(&_currentSize));
               _currentSizeIsDefined = true;
            }
            return S_OK;
         }
         RINOK(_updateCallback->SetOperationResult(::libcompress::archive::NUpdate::NOperationResult::kOK));
         Sizes.add(0);
         Processed.add(result == S_OK);
         AddDigest();
      }
      return S_OK;
   }

   void CFolderInStream::AddDigest()
   {
      CRCs.add(_inStreamWithHashSpec->GetCRC());
   }

   HRESULT CFolderInStream::CloseStream()
   {
      RINOK(_updateCallback->SetOperationResult(::libcompress::archive::NUpdate::NOperationResult::kOK));
      _inStreamWithHashSpec->ReleaseStream();
      _fileIsOpen = false;
      _currentSizeIsDefined = false;
      Processed.add(true);
      Sizes.add(_filePos);
      AddDigest();
      return S_OK;
   }

   memory_size_t CFolderInStream::read(void *data, memory_size_t size)
   {
      memory_size_t processedSize = 0;
      while (size > 0)
      {
         if (_fileIsOpen)
         {
            memory_size_t processed2;
            processed2 = _inStreamWithHash->read(data, size);
            if (processed2 == 0)
            {
               RINOK(CloseStream());
               continue;
            }
            processedSize = processed2;
            _filePos += processed2;
            break;
         }
         if (_fileIndex >= _numFiles)
            break;
         RINOK(OpenStream());
      }
      return processedSize;
   }

   HRes CFolderInStream::GetSubStreamSize(uint64_t subStream, uint64_t *value)
   {
      *value = 0;
      index index1 = (index)subStream;
      if (index1 < 0 || (count) subStream > Sizes.get_count())
         return E_FAIL;
      if (index1 < Sizes.get_count())
      {
         *value = Sizes[index1];
         return S_OK;
      }
      if (!_currentSizeIsDefined)
         return S_FALSE;
      *value = _currentSize;
      return S_OK;
   }

} // namespace n7z
