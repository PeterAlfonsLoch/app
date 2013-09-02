#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 get_input_stream_processed_size_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes GetInStreamProcessedSize(uint64_t *value) = 0;
   };

} // namespace libcompress
