#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE coder_interface :
      virtual public ::object
   {
   public:
      virtual HRes Code(::file::reader * inStream, ::file::writer * outStream, const file_size_t * inSize, const file_size_t * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
