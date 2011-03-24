// ICoder.h
// from 7-zip
#pragma once

namespace crypto
{

   class CLASS_DECL_ca set_password_interface :
      virtual public ::radix::object
   {
   public:
     virtual ex1::HRes CryptoSetPassword(const byte *data, uint32 size) = 0;
   };

} // namespace crypto