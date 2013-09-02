#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 get_sub_stream_size_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes GetSubStreamSize(uint64_t subStream, uint64_t *value) = 0;
   };

} // namespace libcompress
