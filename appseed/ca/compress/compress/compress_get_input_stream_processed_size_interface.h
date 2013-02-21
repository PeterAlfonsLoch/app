#pragma once

namespace libcompress
{

   class CLASS_DECL_ca get_input_stream_processed_size_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes GetInStreamProcessedSize(uint64_t *value) = 0;
   };

} // namespace libcompress
