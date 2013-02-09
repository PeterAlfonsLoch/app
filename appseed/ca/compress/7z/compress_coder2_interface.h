#pragma once

namespace libcompress
{

   class CLASS_DECL_ca coder2_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes Code(::ex1::reader ** inStreams, const file_size ** inSizes, uint32 numInStreams,
         ::ex1::writer ** outStreams, const file_size ** outSizes, uint32 numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace libcompress
