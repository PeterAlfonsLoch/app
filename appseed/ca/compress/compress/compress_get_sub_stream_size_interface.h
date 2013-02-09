#pragma once

namespace libcompress
{

   class CLASS_DECL_ca get_sub_stream_size_interface :
      virtual public ::radix::object
   {
   public:
      virtual ::ex1::HRes GetSubStreamSize(uint64_t subStream, uint64_t *value) = 0;
   };

} // namespace libcompress
