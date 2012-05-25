#pragma once

namespace compress
{

   class CLASS_DECL_ca get_input_stream_processed_size_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes GetInStreamProcessedSize(uint64 *value) = 0;
   };

} // namespace compress
