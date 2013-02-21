// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca set_output_stream_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes SetOutStream(::gen::writer * outStream) = 0;
      virtual gen::HRes ReleaseOutStream() = 0;
   };

} // namespace libcompress
