// 7zFolderInStream.cpp
// from 7-zip on dawn of 13/01/2001 - Thursday
#include "StdAfx.h"


namespace n7z
{

   CFolderInStream::CFolderInStream()
   {
      _inStreamWithHashSpec = new ::compress::reader_with_crc;
      _inStreamWithHash = _inStreamWithHashSpec;
   }

   void CFolderInStream::Init(::compress::archive_update_callback_interface *updateCallback,
      const uint32 *fileIndices, uint32 numFiles)
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
         ::ca::smart_pointer < ::ex1::byte_input_stream > stream;
         HRESULT result = _updateCallback->GetStream(_fileIndices[_fileIndex], &stream.m_p);
         if (result != S_OK && result != S_FALSE)
            return result;
         _fileIndex++;
         _inStreamWithHashSpec->SetStream(stream);
         _inStreamWithHashSpec->Init();
         if (stream)
         {
            _fileIsOpen = true;
            ::ca::smart_pointer < ::ex1::stream_get_size > streamGetSize;
            streamGetSize = dynamic_cast < ::ex1::stream_get_size * > (stream.m_p);
            if (streamGetSize)
            {
               RINOK(streamGetSize->GetSize(&_currentSize));
               _currentSizeIsDefined = true;
            }
            return S_OK;
         }
         RINOK(_updateCallback->SetOperationResult(::compress::archive::NUpdate::NOperationResult::kOK));
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
      RINOK(_updateCallback->SetOperationResult(::compress::archive::NUpdate::NOperationResult::kOK));
      _inStreamWithHashSpec->ReleaseStream();
      _fileIsOpen = false;
      _currentSizeIsDefined = false;
      Processed.add(true);
      Sizes.add(_filePos);
      AddDigest();
      return S_OK;
   }

   ::primitive::memory_size CFolderInStream::read(void *data, ::primitive::memory_size size)
   {
      ::primitive::memory_size processedSize = 0;
      while (size > 0)
      {
         if (_fileIsOpen)
         {
            ::primitive::memory_size processed2;
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

   ex1::HRes CFolderInStream::GetSubStreamSize(uint64 subStream, uint64 *value)
   {
      *value = 0;
      index index2 = (index)subStream;
      if (index2 < 0 || (count) subStream > Sizes.get_count())
         return E_FAIL;
      if (index2 < Sizes.get_count())
      {
         *value = Sizes[index2];
         return S_OK;
      }
      if (!_currentSizeIsDefined)
         return S_FALSE;
      *value = _currentSize;
      return S_OK;
   }

} // namespace n7z
