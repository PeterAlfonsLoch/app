// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca set_output_stream_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetOutStream(::ex1::writer * outStream) = 0;
      virtual ex1::HRes ReleaseOutStream() = 0;
   };

} // namespace libcompress
