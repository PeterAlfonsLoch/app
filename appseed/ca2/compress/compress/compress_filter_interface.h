// ICoder.h
// from 7-zip
#pragma once

namespace libcompress
{

   class CLASS_DECL_ca2 filter_interface :
      virtual public object
   {
   public:
     virtual ::ca2::HRes Init() = 0;
     virtual uint32_t Filter(byte *data, uint32_t size) = 0;
     // Filter converts as most as possible bytes
     // Filter return outSize (uint32_t)
     // if (outSize <= size): Filter have converted outSize bytes
     // if (outSize > size): Filter have not converted anything.
     //      and it needs at least outSize bytes to convert one block
     //      (it's for crypto block algorithms).
   };


} // namespace crypto
