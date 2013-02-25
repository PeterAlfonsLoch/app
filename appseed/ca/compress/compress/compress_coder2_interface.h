#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes Code(::ca::reader ** inStreams, const file_size ** inSizes, uint32_t numInStreams,
         ::ca::writer ** outStreams, const file_size ** outSizes, uint32_t numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
