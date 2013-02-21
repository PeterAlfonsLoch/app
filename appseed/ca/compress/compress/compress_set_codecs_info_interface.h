#pragma once

namespace libcompress
{

   class CLASS_DECL_ca set_codecs_info_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes SetCompressCodecsInfo(codecs_info_interface *compressCodecsInfo) = 0;
   };

} // namespace libcompress
