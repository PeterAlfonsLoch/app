// ICoder.h
// from 7-zip
#pragma once

namespace libcompress
{

   class CLASS_DECL_CORE filter_interface :
      virtual public ::ca::object
   {
   public:
     virtual ::ca::HRes Init() = 0;
     virtual uint32 Filter(byte *data, uint32 size) = 0;
     // Filter converts as most as possible bytes
     // Filter return outSize (uint32)
     // if (outSize <= size): Filter have converted outSize bytes
     // if (outSize > size): Filter have not converted anything.
     //      and it needs at least outSize bytes to convert one block
     //      (it's for crypto block algorithms).
   };


} // namespace crypto
