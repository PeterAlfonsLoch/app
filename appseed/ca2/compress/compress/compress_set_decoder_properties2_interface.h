// ICoder.h
// from 7-zip
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca set_decoder_properties2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetDecoderProperties2(const byte *data, uint32_t size) = 0;
   };


} // namespace libcompress
