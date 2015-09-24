#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE coder2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes Code(::ca::reader ** inStreams, const file_size_t ** inSizes, uint32 numInStreams,
         ::ca::writer ** outStreams, const file_size_t ** outSizes, uint32 numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
