#pragma once

namespace compress
{

   class CLASS_DECL_ca coder2_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes Code(::ex1::reader ** inStreams, const uint64 ** inSizes, uint32 numInStreams,
         ::ex1::writer ** outStreams, const uint64 ** outSizes, uint32 numOutStreams,
         progress_info_interface * progress) = 0;
   };


} // namespace compress
