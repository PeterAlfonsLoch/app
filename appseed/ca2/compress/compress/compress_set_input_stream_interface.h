// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 set_input_stream_interface :
      virtual public ::ca2::object
   {
   public:
      virtual ::ca2::HRes SetInStream(::ca2::reader * inStream) = 0;
      virtual ::ca2::HRes ReleaseInStream() = 0;
   };

} // namespace libcompress
