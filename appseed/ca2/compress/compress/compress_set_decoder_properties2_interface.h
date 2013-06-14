// ICoder.h
// from 7-zip
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 set_decoder_properties2_interface :
      virtual public ::ca2::object
   {
   public:
      virtual ::ca2::HRes SetDecoderProperties2(const byte *data, uint32_t size) = 0;
   };


} // namespace libcompress
