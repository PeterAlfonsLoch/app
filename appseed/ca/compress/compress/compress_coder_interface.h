#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes Code(::gen::reader * inStream, ::gen::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
