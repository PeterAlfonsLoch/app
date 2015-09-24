#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE coder_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes Code(::ca::reader * inStream, ::ca::writer * outStream, const file_size_t * inSize, const file_size_t * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
