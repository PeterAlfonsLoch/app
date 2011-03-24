// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace compress
{

   class CLASS_DECL_ca write_coder_properties_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes WriteCoderProperties(::ex1::writer * outStream) = 0;
   };

} // namespace compress

