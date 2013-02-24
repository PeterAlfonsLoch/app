#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder_interface :
      virtual public ::ca::object
   {
   public:
      virtual ca::HRes Code(::ca::reader * inStream, ::ca::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
