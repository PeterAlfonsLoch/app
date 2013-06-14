#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 coder_interface :
      virtual public ::ca2::object
   {
   public:
      virtual ::ca2::HRes Code(::ca2::reader * inStream, ::ca2::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
