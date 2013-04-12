// ICoder.h
// from 7-zip
#pragma once

namespace crypto
{

   class CLASS_DECL_ca2 set_password_interface :
      virtual public ::ca::object
   {
   public:
     virtual ::ca::HRes CryptoSetPassword(const byte *data, uint32_t size) = 0;
   };

} // namespace crypto