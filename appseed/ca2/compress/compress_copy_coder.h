// Compress/CopyCoder.h
// from 7-zip
#pragma once

/*#include "../../Common/MyCom.h"

#include "../ICoder.h"*/

namespace libcompress
{

   class copy_coder:
      public coder_interface,
      public get_input_stream_processed_size_interface
   {
   public:


      byte *_buffer;
      uint64_t TotalSize;


      copy_coder();
      ~copy_coder();

      virtual ::ca2::HRes Code(::ca2::reader *inStream, ::ca2::writer *outStream, const file_size *inSize, const file_size *outSize, progress_info_interface *progress);
      virtual ::ca2::HRes GetInStreamProcessedSize(uint64_t *value);
   };

   HRESULT CopyStream(::ca2::reader * inStream, ::ca2::writer * outStream, ::libcompress::progress_info_interface * progress);

} // namespace libcompress
