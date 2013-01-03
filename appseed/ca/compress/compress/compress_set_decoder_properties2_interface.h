// ICoder.h
// from 7-zip
#pragma once

namespace compress
{

   class CLASS_DECL_ca set_decoder_properties2_interface :
      virtual public ::radix::object
   {
   public:
      virtual ex1::HRes SetDecoderProperties2(const byte *data, uint32_t size) = 0;
   };


} // namespace compress