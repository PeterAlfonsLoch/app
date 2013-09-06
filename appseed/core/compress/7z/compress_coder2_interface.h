#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 coder2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes Code(::ca::reader ** inStreams, const file_size ** inSizes, uint32 numInStreams,
         ::ca::writer ** outStreams, const file_size ** outSizes, uint32 numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
