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
      uint64 TotalSize;


      copy_coder();
      ~copy_coder();

      virtual ::ca::HRes Code(::ca::reader *inStream, ::ca::writer *outStream, const file_size_t *inSize, const file_size_t *outSize, progress_info_interface *progress);
      virtual ::ca::HRes GetInStreamProcessedSize(uint64 *value);
   };

   HRESULT CopyStream(::ca::reader * inStream, ::ca::writer * outStream, ::libcompress::progress_info_interface * progress);

} // namespace libcompress
