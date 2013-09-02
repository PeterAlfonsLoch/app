// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 set_output_stream_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes SetOutStream(::file::writer * outStream) = 0;
      virtual ::ca2::HRes ReleaseOutStream() = 0;
   };

} // namespace libcompress
