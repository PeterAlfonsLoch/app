#pragma once

namespace libcompress
{

   class CLASS_DECL_BASE coder_interface :
      virtual public object
   {
   public:
      virtual HRes Code(::file::reader * inStream, ::file::writer * outStream, const file_size * inSize, const file_size * outSize, progress_info_interface * progress) = 0;
   };


} // namespace libcompress
