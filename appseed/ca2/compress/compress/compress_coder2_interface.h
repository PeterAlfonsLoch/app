#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 coder2_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes Code(spa(::file::reader) & InStreams, const file_size ** inSizes, spa(::file::writer) & OutStreams, const file_size ** outSizes,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
