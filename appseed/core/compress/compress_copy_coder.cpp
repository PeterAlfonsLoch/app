// Compress/CopyCoder.cpp

#include "framework.h"

/*#include "../../../C/Alloc.h"

#include "../Common/StreamUtils.h"

#include "CopyCoder.h"*/

namespace libcompress
{

   static const uint32_t kBufferSize = 1 << 17;

   copy_coder::copy_coder() :
      TotalSize(0),
      _buffer(0)
   {

   }


   copy_coder::~copy_coder()
   {
      ::MidFree(_buffer);
   }

   HRes copy_coder::Code(::file::reader *inStream, ::file::writer *outStream, const file_size * /* inSize */, const file_size *outSize, progress_info_interface *progress)
   {
      if (_buffer == 0)
      {
         _buffer = (byte *)::MidAlloc(kBufferSize);
         if (_buffer == 0)
            return E_OUTOFMEMORY;
      }

      TotalSize = 0;
      for (;;)
      {
         memory_size_t size = kBufferSize;
         if (outSize != 0)
            if (size > *outSize - TotalSize)
               size = (uint32_t)(*outSize - TotalSize);
         size = inStream->read(_buffer, size);
         if (size == 0)
            break;
         if (outStream)
         {
            outStream->write(_buffer, size);
         }
         TotalSize += size;
         if (progress != NULL)
         {
            RINOK(progress->SetRatioInfo(&TotalSize, &TotalSize));
         }
      }
      return S_OK;
   }

   HRes copy_coder::GetInStreamProcessedSize(uint64_t *value)
   {
      *value = TotalSize;
      return S_OK;
   }

   HRESULT CopyStream(::file::reader * inStream, ::file::writer * outStream, progress_info_interface * progress)
   {
      sp(coder_interface) copyCoder;
      copyCoder = new copy_coder;
      return copyCoder->Code(inStream, outStream, NULL, NULL, progress);
   }

} // namespace libcompress
