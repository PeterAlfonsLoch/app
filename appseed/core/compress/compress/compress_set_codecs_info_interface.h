#pragma once

namespace libcompress
{

   class CLASS_DECL_BASE set_codecs_info_interface :
      virtual public object
   {
   public:
      virtual HRes SetCompressCodecsInfo(codecs_info_interface *compressCodecsInfo) = 0;
   };

} // namespace libcompress
