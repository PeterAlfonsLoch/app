#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes Code(spa(::ca::reader) & InStreams, const file_size ** inSizes, spa(::ca::writer) & OutStreams, const file_size ** outSizes,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
