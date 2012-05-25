#pragma once

namespace compress
{

   class CLASS_DECL_ca get_sub_stream_size_interface :
      virtual public ::radix::object
   {
   public:
      virtual ::ex1::HRes GetSubStreamSize(uint64 subStream, uint64 *value) = 0;
   };

} // namespace compress