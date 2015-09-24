#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE coder2_interface :
      virtual public ::object
   {
   public:
      virtual HRes Code(spa(::file::reader) & InStreams, const file_size_t ** inSizes, spa(::file::writer) & OutStreams, const file_size_t ** outSizes,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
