#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder2_interface :
      virtual public ::gen::object
   {
   public:
      virtual gen::HRes Code(::gen::reader ** inStreams, const file_size ** inSizes, uint32_t numInStreams,
         ::gen::writer ** outStreams, const file_size ** outSizes, uint32_t numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
