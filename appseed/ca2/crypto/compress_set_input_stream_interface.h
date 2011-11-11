// from ICoder.h from 7-zip on 2010-12-20
#pragma once 

namespace compress
{

   class CLASS_DECL_ca set_input_stream_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetInStream(::ex1::reader * inStream) = 0;
      virtual ex1::HRes ReleaseInStream() = 0;
   };

} // namespace compress