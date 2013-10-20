#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE get_input_stream_processed_size_interface :
      virtual public object
   {
   public:
      virtual HRes GetInStreamProcessedSize(uint64_t *value) = 0;
   };

} // namespace libcompress
