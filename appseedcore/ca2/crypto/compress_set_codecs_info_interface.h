#pragma once

namespace compress
{

   class CLASS_DECL_ca set_codecs_info_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetCompressCodecsInfo(codecs_info_interface *compressCodecsInfo) = 0;
   };

} // namespace compress