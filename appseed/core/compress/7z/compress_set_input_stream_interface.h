// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE set_input_stream_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetInStream(::ca::reader * inStream) = 0;
      virtual ::ca::HRes ReleaseInStream() = 0;
   };

} // namespace libcompress
