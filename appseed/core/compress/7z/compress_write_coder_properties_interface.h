// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace libcompress
{

   class CLASS_DECL_CORE write_coder_properties_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes WriteCoderProperties(::ca::writer * outStream) = 0;
   };

} // namespace libcompress

