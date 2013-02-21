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

      virtual gen::HRes Code(::gen::reader *inStream, ::gen::writer *outStream, const file_size *inSize, const file_size *outSize, progress_info_interface *progress);
      virtual gen::HRes GetInStreamProcessedSize(uint64_t *value);
   };

   HRESULT CopyStream(::gen::reader * inStream, ::gen::writer * outStream, ::libcompress::progress_info_interface * progress);

} // namespace libcompress
