// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_BASE set_input_stream_interface :
      virtual public object
   {
   public:
      virtual HRes SetInStream(::file::reader * inStream) = 0;
      virtual HRes ReleaseInStream() = 0;
   };

} // namespace libcompress
