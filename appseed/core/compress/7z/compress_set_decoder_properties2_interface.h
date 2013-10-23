// ICoder.h
// from 7-zip
#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE set_decoder_properties2_interface :
      virtual public ::ca::object
   {
   public:
      virtual ::ca::HRes SetDecoderProperties2(const byte *data, uint32 size) = 0;
   };


} // namespace libcompress
