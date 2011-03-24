// Compress/CopyCoder.h
// from 7-zip
#pragma once

/*#include "../../Common/MyCom.h"

#include "../ICoder.h"*/

namespace compress 
{

   class copy_coder:
      public coder_interface,
      public get_input_stream_processed_size_interface
   {
   public:


      byte *_buffer;
      uint64 TotalSize;


      copy_coder();
      ~copy_coder();

      virtual ex1::HRes Code(::ex1::reader *inStream, ::ex1::writer *outStream, const uint64 *inSize, const uint64 *outSize, progress_info_interface *progress);
      virtual ex1::HRes GetInStreamProcessedSize(uint64 *value);
   };

   HRESULT CopyStream(::ex1::reader * inStream, ::ex1::writer * outStream, ::compress::progress_info_interface * progress);

} // namespace compress
