// FilterCoder.cpp
// from 7-zip on 2010-12-19
#include "framework.h"

/*#include "../../../C/Alloc.h"

#include "../../Common/Defs.h"

#include "FilterCoder.h"
#include "StreamUtils.h"*/

namespace libcompress
{

   static const uint32_t kBufferSize = 1 << 17;

   filter_coder::filter_coder()
   {
      _buffer = (byte *)::MidAlloc(kBufferSize);
      if (_buffer == 0)
         throw 1;
   }

   filter_coder::~filter_coder()
   {
      ::MidFree(_buffer);
   }

   HRESULT filter_coder::WriteWithLimit(::file::writer *outStream, uint32_t size)
   {
      if (_outSizeIsDefined)
      {
         uint64_t remSize = _outSize - _nowPos64;
         if (size > remSize)
            size = (uint32_t)remSize;
      }
      RINOK(::file::write(outStream, _buffer, size));
      _nowPos64 += size;
      return S_OK;
   }

   HRes filter_coder::Code(::file::reader *inStream, ::file::writer *outStream, const file_size * /* inSize */, const file_size *outSize, progress_info_interface *progress)
   {
      RINOK(Init());
      uint32_t bufferPos = 0;
      _outSizeIsDefined = (outSize != 0);
      if (_outSizeIsDefined)
         _outSize = *outSize;

      while (!_outSizeIsDefined || _nowPos64 < _outSize)
      {
         memory_size_t processedSize = kBufferSize - bufferPos;

         // Change it: It can be optimized using ReadPart
         RINOK(::file::read(inStream, _buffer + bufferPos, &processedSize));

         uint32_t endPos = bufferPos + (uint32_t)processedSize;

         bufferPos = Filter->Filter(_buffer, endPos);
         if (bufferPos > endPos)
         {
            for (; endPos < bufferPos; endPos++)
               _buffer[endPos] = 0;
            bufferPos = Filter->Filter(_buffer, endPos);
         }

         if (bufferPos == 0)
         {
            if (endPos == 0)
               return S_OK;
            return WriteWithLimit(outStream, endPos);
         }
         RINOK(WriteWithLimit(outStream, bufferPos));
         if (progress != NULL)
         {
            RINOK(progress->SetRatioInfo(&_nowPos64, &_nowPos64));
         }
         uint32_t i = 0;
         while (bufferPos < endPos)
            _buffer[i++] = _buffer[bufferPos++];
         bufferPos = i;
      }
      return S_OK;
   }

   HRes filter_coder::SetOutStream(::file::writer *outStream)
   {
      _bufferPos = 0;
      _outStream = outStream;
      return Init();
   }

   HRes filter_coder::ReleaseOutStream()
   {
      //_outStream.Release();
      return S_OK;
   }


   void filter_coder::write(const void * data, memory_size_t size, memory_size_t * processedSize)
   {
      if (processedSize != NULL)
         *processedSize = 0;
      while (size > 0)
      {
         memory_size_t sizeTemp = min(size, kBufferSize - _bufferPos);
         memcpy(_buffer + _bufferPos, data, sizeTemp);
         size -= sizeTemp;
         if (processedSize != NULL)
            *processedSize += sizeTemp;
         data = (const byte *)data + sizeTemp;
         uint32_t endPos = (uint32_t) (_bufferPos + sizeTemp);
         _bufferPos = Filter->Filter(_buffer, endPos);
         if (_bufferPos == 0)
         {
            _bufferPos = endPos;
            break;
         }
         if (_bufferPos > endPos)
         {
            if (size != 0)
               throw "E_FAIL";
            break;
         }
         WriteWithLimit(_outStream, _bufferPos);
         uint32_t i = 0;
         while (_bufferPos < endPos)
            _buffer[i++] = _buffer[_bufferPos++];
         _bufferPos = i;
      }
   }

   void filter_coder::flush()
   {
      if (_bufferPos != 0)
      {
         // _buffer contains only data refused by previous Filter->Filter call.
         uint32_t endPos = Filter->Filter(_buffer, _bufferPos);
         if (endPos > _bufferPos)
         {
            for (; _bufferPos < endPos; _bufferPos++)
               _buffer[_bufferPos] = 0;
            if (Filter->Filter(_buffer, endPos) != endPos)
               throw "E_FAIL";
         }
         if(FAILED(WriteWithLimit(_outStream, _bufferPos)))
            throw "E_FAIL";
         _bufferPos = 0;
      }
      ::file::output_stream_flush * pflush = dynamic_cast < ::file::output_stream_flush * > (_outStream) ;
      if(pflush)
         return pflush->flush();
   }


   HRes filter_coder::SetInStream(::file::reader *inStream)
   {
      _convertedPosBegin = _convertedPosEnd = _bufferPos = 0;
      _inStream = inStream;
      return Init();
   }

   HRes filter_coder::ReleaseInStream()
   {
      //_inStream.Release();
      return S_OK;
   }

   memory_size_t filter_coder::read(void *data, memory_size_t size)
   {
      uint_ptr processedSize = 0;
      while (size > 0)
      {
         if (_convertedPosBegin != _convertedPosEnd)
         {
            uint32_t sizeTemp = (uint32_t) min(size, _convertedPosEnd - _convertedPosBegin);
            memcpy(data, _buffer + _convertedPosBegin, sizeTemp);
            _convertedPosBegin += sizeTemp;
            data = (void *)((byte *)data + sizeTemp);
            size -= sizeTemp;
            processedSize += sizeTemp;
            break;
         }
         uint32_t i;
         for (i = 0; _convertedPosEnd + i < _bufferPos; i++)
            _buffer[i] = _buffer[_convertedPosEnd + i];
         _bufferPos = i;
         _convertedPosBegin = _convertedPosEnd = 0;
         memory_size_t processedSizeTemp = kBufferSize - _bufferPos;
         RINOK(::file::read(_inStream, _buffer + _bufferPos, &processedSizeTemp));
         _bufferPos += (uint32_t)processedSizeTemp;
         _convertedPosEnd = Filter->Filter(_buffer, _bufferPos);
         if (_convertedPosEnd == 0)
         {
            if (_bufferPos == 0)
               break;
            _convertedPosEnd = _bufferPos; // check it
            continue;
         }
         if (_convertedPosEnd > _bufferPos)
         {
            for (; _bufferPos < _convertedPosEnd; _bufferPos++)
               _buffer[_bufferPos] = 0;
            _convertedPosEnd = Filter->Filter(_buffer, _bufferPos);
         }
      }
      return processedSize;
   }

   HRes filter_coder::CryptoSetPassword(const byte *data, uint32_t size)
   {
      return _setPassword->CryptoSetPassword(data, size);
   }

   HRes filter_coder::SetCoderProperties(const int32_t  * propIDs, const var *properties, uint32_t numProperties)
   {
      return _SetCoderProperties->SetCoderProperties(propIDs, properties, numProperties);
   }

   HRes filter_coder::WriteCoderProperties(::file::writer *outStream)
   {
      return _writeCoderProperties->WriteCoderProperties(outStream);
   }

   /*
   HRes filter_coder::ResetSalt()
   {
   return _CryptoResetSalt->ResetSalt();
   }
   */

   HRes filter_coder::ResetInitVector()
   {
      return _CryptoResetInitVector->ResetInitVector();
   }

   HRes filter_coder::SetDecoderProperties2(const byte *data, uint32_t size)
   {
      return _setDecoderProperties->SetDecoderProperties2(data, size);
   }

} // namespace libcompress
