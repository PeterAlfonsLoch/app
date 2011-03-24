#pragma once

namespace compress
{

   class CLASS_DECL_ca coder_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes Code(::ex1::reader * inStream, ::ex1::writer * outStream, const uint64 * inSize, const uint64 * outSize, progress_info_interface * progress) =0;
   };


} // namespace compress
