// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca set_input_stream_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes SetInStream(::gen::reader * inStream) = 0;
      virtual gen::HRes ReleaseInStream() = 0;
   };

} // namespace libcompress
