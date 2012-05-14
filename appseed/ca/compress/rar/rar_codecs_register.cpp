// RarCodecsRegister.cpp
// from 7-zip on 2012-12-23, dawn
#include "framework.h"

//#include "../Common/RegisterCodec.h"

/*#include "Rar1Decoder.h"
#include "Rar2Decoder.h"
#include "Rar3Decoder.h"*/

namespace compress
{

#define CREATE_CODEC(x)                                                                \
   static void *create_codec ## x()                                                    \
   {                                                                                   \
      return (void *)(coder_interface *)(new rar ## x::decoder);                       \
   }                                                                                   

   CREATE_CODEC(1)
   CREATE_CODEC(2)
   CREATE_CODEC(3)

#define RAR_CODEC(x, name) { create_codec ## x, 0, 0x040300 + x, "Rar" name, 1, false }

   static codec_info g_CodecsInfo[] =
   {
      RAR_CODEC(1, "1"),
      RAR_CODEC(2, "2"),
      RAR_CODEC(3, "3"),
   };

   REGISTER_CODECS(Rar)

} // namespace compress