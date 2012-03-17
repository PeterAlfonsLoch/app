// Compress/CopyCoder.cpp

#include "StdAfx.h"

/*#include "../../../C/Alloc.h"

#include "../Common/StreamUtils.h"

#include "CopyCoder.h"*/

namespace compress 
{

   static const uint32 kBufferSize = 1 << 17;

   copy_coder::copy_coder() :
      TotalSize(0),
      _buffer(0)
   {
         
   }


   copy_coder::~copy_coder()
   {
      ::MidFree(_buffer);
   }

   ex1::HRes copy_coder::Code(::ex1::reader *inStream, ::ex1::writer *outStream, const file_size * /* inSize */, const file_size *outSize, progress_info_interface *progress)
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
         ::primitive::memory_size size = kBufferSize;
         if (outSize != 0)
            if (size > *outSize - TotalSize)
               size = (uint32)(*outSize - TotalSize);
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

   ex1::HRes copy_coder::GetInStreamProcessedSize(uint64 *value)
   {
      *value = TotalSize;
      return S_OK;
   }

   HRESULT CopyStream(::ex1::reader * inStream, ::ex1::writer * outStream, progress_info_interface * progress)
   {
      sp(coder_interface) copyCoder;
      copyCoder(new copy_coder);
      return copyCoder->Code(inStream, outStream, NULL, NULL, progress);
   }

} // namespace compress
