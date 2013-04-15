#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 get_sub_stream_size_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes GetSubStreamSize(uint64 subStream, uint64 *value) = 0;
   };

} // namespace libcompress
