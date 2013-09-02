#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 coder_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes Code(::file::reader * inStream, ::file::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
