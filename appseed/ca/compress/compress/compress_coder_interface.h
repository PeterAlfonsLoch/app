#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes Code(::ex1::reader * inStream, ::ex1::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
