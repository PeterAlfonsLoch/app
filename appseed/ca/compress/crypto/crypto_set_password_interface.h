// ICoder.h
// from 7-zip
#pragma once

namespace crypto
{

   class CLASS_DECL_ca set_password_interface :
      virtual public ::gen::object
   {
   public:
     virtual gen::HRes CryptoSetPassword(const byte *data, uint32_t size) = 0;
   };

} // namespace crypto