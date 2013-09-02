// from ICoder.h from 7-zip on 2010-12-20
#pragma once


namespace libcompress
{

   class CLASS_DECL_ca2 write_coder_properties_interface :
      virtual public object
   {
   public:
      virtual ::ca2::HRes WriteCoderProperties(::file::writer * outStream) = 0;
   };

} // namespace libcompress

