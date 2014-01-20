#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE get_input_stream_processed_size_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes GetInStreamProcessedSize(uint64 *value) = 0;
   };

} // namespace libcompress
