// from ICoder.h from 7-zip on 2010-12-20
#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE set_output_stream_interface :
      virtual public ::object
   {
   public:
      virtual HRes SetOutStream(::file::writer * outStream) = 0;
      virtual HRes ReleaseOutStream() = 0;
   };

} // namespace libcompress
