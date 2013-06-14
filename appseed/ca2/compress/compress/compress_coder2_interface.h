#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 coder2_interface :
      virtual public ::ca2::object
   {
   public:
      virtual ::ca2::HRes Code(spa(::ca2::reader) & InStreams, const file_size ** inSizes, spa(::ca2::writer) & OutStreams, const file_size ** outSizes,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
